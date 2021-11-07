#define QUEUE_SIZE 16
#define CIRCULAR_BUFFER_INT_SAFE

#define SERIAL_LOGGING 1

#include "BKM10Rduino.h"
#include <CircularBuffer.h>

//U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
U8X8_SH1106_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

CircularBuffer<void*, 4> commandBuffer;
int buttonState = 0;
unsigned long lastPoll;

bool learning = false;
bool isHoldingLearnButton = false;
unsigned long learnButtonTimer;

struct RemoteKey *learningInput;
struct RemoteKey *lastLearnedInput;
RemoteKey emptyLearning = {0, 0};
RemoteKey emptyLearned = {0, 0};

int learnIndex = 0;

#define DEBUG 1
#define DEBUG_BUTTON A7

void setup() {
  Serial.begin(38400);

  learningInput = &emptyLearning;
  lastLearnedInput = &emptyLearned;

  initPCIInterruptForTinyReceiver();


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_MENU_PIN, INPUT);
  pinMode(BUTTON_ENTER_PIN, INPUT);
  pinMode(BUTTON_POWER_PIN, INPUT);
  pinMode(TX_ENABLE_PIN, OUTPUT);
  digitalWrite(TX_ENABLE_PIN, HIGH);
  pinMode(LEARN_ENABLE_PIN, INPUT_PULLUP);

  lastPoll = millis();
  learnButtonTimer = millis();

  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  showName();
}

void showName() {
  u8x8.clear();
  u8x8.home();
  u8x8.print(F("BKM-10iRduino"));
}

void loop() {

  if (millis() - lastPoll > 150) {
    updateIsLearning();

    if (learning) {
      u8x8.clear();
      u8x8.drawString(0, 4, "press key:");
      //      if (learningBuffer.first() != NULL) {
      u8x8.setCursor(0, 5);
      char buffer[20];
      strcpy_P(buffer, (char*)pgm_read_word(&(names[learnIndex])));
      u8x8.print(buffer);
      //        #ifdef SERIAL_LOGGING
      //    Serial.println(learningBuffer.first()->id);
      //#endif
      //      } else {
      //        showName();
      //      }
    }

    int previous = buttonState;
    //    readButtons();

    if (previous != buttonState) {
      sendButtonCommand();
    }
    lastPoll = millis();
  }

  while (!commandBuffer.isEmpty()) {
    ControlCode *code = (ControlCode*)commandBuffer.shift();
#ifdef SERIAL_LOGGING
    Serial.println(code->code, HEX);
#endif
    sendCode(code);
  }
}

void updateIsLearning() {
  int learnButtonState = digitalRead(LEARN_ENABLE_PIN);
  if (learnButtonState == HIGH) {
    isHoldingLearnButton = false;
  }

  if (!learning) {
    if (learnButtonState == LOW) {
      if (!isHoldingLearnButton) {
        u8x8.drawString(0, 2, "Hold to start");
        u8x8.drawString(0, 3, "leaning keys");
        isHoldingLearnButton = true;
        learnButtonTimer = millis();
#ifdef SERIAL_LOGGING
        Serial.println("Maybe trying to learn");
#endif
      } else if (millis() - learnButtonTimer > 1000) {
        u8x8.clearLine(2);
        u8x8.clearLine(2);

        learnIndex = 0;

#ifdef SERIAL_LOGGING
        int s = sizeof(commands) / sizeof(Command);
        for (int i = 0; i < s; i++) {
          char buffer[20];
          strcpy_P(buffer, (char*)pgm_read_word(&(names[i])));
          Serial.println(buffer);
#endif
        }
        learning = true;
        learnButtonTimer = millis();
      }
    }
  } else if (learnButtonState == LOW && !isHoldingLearnButton && millis() - learnButtonTimer > 1000) {
    cancelLearning();
  } else {
    processLearnQueue();
  }
}

void cancelLearning() {
    learning = false;
    learningInput->address = 0;
    learningInput->code = 0;
    lastLearnedInput->address = 0;
    lastLearnedInput->code = 0;
    learnIndex = 0;
    u8x8.clear();
    showName();
}

void processLearnQueue() {
  if (learnIndex >= 19) {
    cancelLearning();

    return;
  }

  if (learningInput->address == 0) {
    return;
  }

  RemoteKey *newKey = &(commands[learnIndex].key);

  //#ifdef SERIAL_LOGGING
  //  Serial.print("old: ");
  //  Serial.print(newKey->address, HEX);
  //  Serial.println(newKey->code, HEX);
  //#endif

  newKey->address = learningInput->address;
  newKey->code = learningInput->code;

  //#ifdef SERIAL_LOGGING
  //  Serial.print("new: ");
  //  Serial.print(newKey->address, HEX);
  //  Serial.println(newKey->code, HEX);
  //#endif

  lastLearnedInput->address = newKey->address;
  lastLearnedInput->code = newKey->code;
  learningInput->address = 0;
  learningInput->code = 0;
  learnIndex++;
}

void sendCode(ControlCode *code) {
  Serial.write(ISWBank);
  delay(50);

  Serial.write(keydown);
  Serial.write(code->group);
  Serial.write(code->code);
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  if (!learning) {
    handleRemoteCommand(aAddress, aCommand, isRepeat);
  } else {
    learnRemoteCommand(aAddress, aCommand, isRepeat);
  }
}

void handleRemoteCommand(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  int x = sizeof(commands) / sizeof(Command);
  for (int i = 0; i < x; i++) {
    if (aAddress == commands[i].key.address) {
      if (aCommand == commands[i].key.code) {
        ControlCode *toSend = (ControlCode*)&commands[i].cmd;
        if (!isRepeat || (isRepeat && commands[i].repeats)) {
          commandBuffer.push(toSend);
        }
        return;
      }
    }
  }
}

void learnRemoteCommand(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  if (isRepeat) return;
  if (aAddress == lastLearnedInput->address && aCommand == lastLearnedInput->code) return;
  if (learningInput->address) return;

  Serial.println(lastLearnedInput->address, HEX);
  Serial.println(lastLearnedInput->code, HEX);


  uint32_t compare = aAddress;
  compare = compare << 8;
  compare += aCommand;
  uint32_t lastInput = lastLearnedInput->address;
  lastInput = lastInput << 8;
  lastInput += lastLearnedInput->code;

  RemoteKey incoming = { aAddress, aCommand, 0 };

  Serial.print("compare: ");
  Serial.print(compare, HEX);
  Serial.print(" & ");
  Serial.println(lastInput, HEX);

  if (!equals(incoming, *lastLearnedInput)) {
    //  if (compare != lastInput) {
    learningInput->address = aAddress;
    learningInput->code = aCommand;
  }
}

void readButtons() {
  buttonState = LOW;

  int newState = LOW;

  int x = sizeof(buttonCommands) / sizeof(ButtonCommand);
  for (int i = 0; i < x; i++) {
    newState |= digitalRead(buttonCommands[i].pin) == HIGH ? buttonCommands[i].button : newState;
  }

  buttonState = newState;
}

void sendButtonCommand() {
  if (!buttonState) {
    return;
  }

  int x = sizeof(buttonCommands) / sizeof(ButtonCommand);
  for (int i = 0; i < x; i++) {
    if (buttonState & buttonCommands[i].button) {
      ControlCode *toSend = (ControlCode*)&buttonCommands[i].cmd;
      commandBuffer.push(toSend);
    }
  }
}

/*** Thank you to the anonymous pastebin hero responsible for providing the control codes ***/

/*
  https://pastebin.com/aTUWf33J
  BKM-10R Protocol
  Version 1 - May 16, 2016
  License: CC0

  The BKM-10R is a remote control used for Sony BVM CRT televisions. It is
  required to control some CRTs without built in control, such as the BVM-20F1U.

  The protocol is vaguely similar to the one used to control Sony VCRs:
  ftp://ftp.sgi.com/sgi/video/rld/vidpage/s9pin.html

  This document currently only applies to the CONTROL connection, not to the
  REMOTE 1 input/output, though it's expected that they are similar.

  == Pinout ==

  The remote control and CRT are connected with straight through male-male DE9
  cable.

  Female DB-9, BKM-10R side:
  1. GND
  2. /TXD
  3. RXD
  4. GND
  5. +5V
  6. GND
  7. TXD
  8. /RXD
  9. GND

  Since a straight through cable is used, TXD on the remote side is RXD on the
  CRT side. +5V is supplied from the CRT to power the remote.

  == Protocol ==

  Full duplex RS-422, 38400 baud, 8N1 (the Sony VCR protocol uses odd parity, but
  that seems not to be the case here). If you only want to control the CRT,
  half duplex RS-485 is electrically compatible.

  == Bank ==

  There are multiple "banks" that can be switched via 3 byte commands:
  0x49 0x45 0x4E - "IEN" - encoders
  0x49 0x53 0x57 - "ISW" - switches
  0x49 0x4C 0x45 - "ILE" - leds
  0x49 0x43 0x43 - "ICC" - ??
  0x49 0x4d 0x54 - "IMT" - ??

  The remote lazily switches banks when needed.

  == Keypresses ==

  Each keydown sends 0x44, then group, then mask.
  0x44 <group> <mask>

  The SHIFT key is "just another key" - state is kept on the CRT. Shifted labels
  are listed after non-shifted labels.

  You must be in the "ISW" bank first.

  <group> <mask> - label
  0x03 0x01 - SHIFT
  0x03 0x02 - OVERSCAN / 16:9
  0x03 0x04 - HORIZ SYNC VIEW / SYNC
  0x03 0x08 - VERT SYNC VIEW / BLUE ONLY
  0x03 0x10 - MONO / R
  0x04 0x01 - APT / G
  0x04 0x02 - COMB / B
  0x04 0x04 - F1 / F3
  0x04 0x08 - F2 / F4
  0x04 0x10 - SAFE AREA / ADDRESS
  0x02 0x40 - UP
  0x02 0x80 - DOWN
  0x02 0x10 - MENU
  0x02 0x20 - ENTER
  0x02 0x08 - PHASE MANUAL
  0x02 0x04 - CHROMA MANUAL
  0x02 0x02 - BRIGHT MANUAL
  0x02 0x01 - CONTRAST MANUAL
  0x00 0x01 - 0
  0x00 0x02 - 1
  0x00 0x04 - 2
  0x00 0x08 - 3
  0x00 0x10 - 4
  0x00 0x20 - 5
  0x00 0x40 - 6
  0x00 0x80 - 7
  0x01 0x01 - 8
  0x01 0x02 - 9
  0x01 0x04 - Del
  0x01 0x08 - Ent
  0x01 0x10 - POWER (but see below)
  0x01 0x20 - DEGAUSS

  == POWER ==

  You only need to send a POWER keypress to turn on the monitor, but for some
  reason the remote does more.

  Power sends five 3-byte sequences:
  0x49 0x53 0x57 - switch bank
  0x44 0x01 0x10 - POWER switch
  (1s pause)
  0x49 0x43 0x43 - CC bank?
  0x49 0x4d 0x54 - MT bank?
  0x44 0x33 0x31 - switch?

  CRT responds with:
  0x49 0x43 0x43 - CC bank?
  <full led state report>
  0x49 0x4d 0x54 - MT bank?
  <full led state report>

  == Encoders ==

  Dials are rotary encoders that send 3 bytes:
  0x44 <encoder id id> <ticks>

  Ticks is a two's complement byte indicating how far the dial has turned since
  the last message. The remote sends messages about every 100ms when the dial
  is turning.

  You must be in the "IEN" bank first.

  0x03 - PHASE
  0x02 - CHROMA
  0x01 - BRIGHT
  0x00 - CONTRAST

  == LEDs ==

  LEDs use the same groups and masks as keypresses. Every time the CRT needs to
  change the lights, it changes to the LED bank:

  0x49 0x4c 0x45

  then sends changed switch groups:

  0x44 <group> <mask>

  where <mask> is all of the active LED masks OR'd together.

  == Memory Card ==

  Nobody cares.
*/
