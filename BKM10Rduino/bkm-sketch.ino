const byte isw_bank[] = {0x49, 0x53, 0x57 };

const byte keydown = 0x44;

const byte pwr_group = 0x01;
const byte pwr_button = 0x10;

const byte power_cmd[] = {keydown, pwr_group, pwr_button};

const byte menu_group = 0x02;
const byte up = 0x40;
const byte down = 0x80;
const byte menu = 0x10;
const byte enter = 0x20;

const byte up_cmd[] = {keydown, menu_group, up};
const byte down_cmd[] = {keydown, menu_group, down};
const byte menu_cmd[] = {keydown, menu_group, menu};
const byte enter_cmd[] = {keydown, menu_group, enter};

const int buttonDownPin = 2;
const int buttonUpPin = 3;
const int buttonMenuPin = 7;
const int buttonEnterPin = 4;
const int buttonPwrPin = 5;

const int buttonUp = 1;
const int buttonDown = 1 << 1;
const int buttonMenu = 1 << 2;
const int buttonEnter = 1 << 3;
const int buttonPwr = 1 << 4;

int buttonState = 0;

const int txdEnablePin = 12;
const int rdxEnablePin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonDownPin, INPUT);
  pinMode(buttonUpPin, INPUT);
  pinMode(buttonMenuPin, INPUT);
  pinMode(buttonEnterPin, INPUT);
  pinMode(buttonPwrPin, INPUT);
  pinMode(txdEnablePin, OUTPUT);
  digitalWrite(txdEnablePin, HIGH);
  Serial.begin(38400, SERIAL_8N1);
}

void readButtons() {
  buttonState = LOW;

  if (digitalRead(buttonDownPin) == HIGH) {
    buttonState = buttonState | (0xFF & buttonDown);
  }
  if (digitalRead(buttonUpPin) == HIGH) {
    buttonState = buttonState | (0xFF & buttonUp);
  }
  if (digitalRead(buttonMenuPin) == HIGH) {
    buttonState = buttonState | (0xFF & buttonMenu);
  }

  if (digitalRead(buttonEnterPin) == HIGH) {
    buttonState = buttonState | (0xFF & buttonEnter);
  }

  if (digitalRead(buttonPwrPin) == HIGH) {
    buttonState = buttonState | (0xFF & buttonPwr);
  }
}

void sendButtonCommand() {
  if (!buttonState) {
    return;
  }
  Serial.write(isw_bank, sizeof(isw_bank));
  delay(100);

  if (buttonState & buttonMenu) {
    Serial.write(menu_cmd, sizeof(menu_cmd));
  }

  if (buttonState & buttonUp) {
    Serial.write(up_cmd, sizeof(up_cmd));
  }

  if (buttonState & buttonDown) {
    Serial.write(down_cmd, sizeof(down_cmd));
  }

  if (buttonState & buttonEnter) {
    Serial.write(enter_cmd, sizeof(enter_cmd));
  }

  if (buttonState & buttonPwr) {
    Serial.write(power_cmd, sizeof(power_cmd));
  }
  delay(100);
}

void loop() {

  int previous = buttonState;

  readButtons();

  if (previous != buttonState) {

    int on = buttonState ? HIGH : LOW;

    digitalWrite(LED_BUILTIN, on);

    sendButtonCommand();  
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
