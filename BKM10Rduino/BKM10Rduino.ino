#define LEARN_TIMEOUT 3000
#define SLEEP_TIMER 60000
#define CIRCULAR_BUFFER_INT_SAFE
//#define SERIAL_LOGGING
#define __ASSERT_USE_STDERR
#define POLL_RATE 33

#define LARGE_FONT u8x8_font_px437wyse700b_2x2_f
#define MEDIUM_FONT  u8x8_font_7x14_1x2_f
#define SMALL_FONT u8x8_font_chroma48medium8_r

//#define USE_PHYSICAL_BUTTONS 1
#define FULL_DUPLEX

#include "BKM10Rduino.h"
#include <CircularBuffer.h>

#include <assert.h>

CircularBuffer<void*, 4> commandBuffer;

#ifdef USE_PHYSICAL_BUTTONS
int buttonState = 0;
#endif

bool learning = false;
bool isHoldingLearnButton = false;
int learnIndex = 0;
struct RemoteKey *learningInput = malloc(sizeof(RemoteKey));
struct RemoteKey *lastLearnedInput = malloc(sizeof(RemoteKey));

struct Timers * timers = malloc(sizeof(Timers));
bool displaySleep = false;
bool rs485sleep = false;

//subscript accessor for RemoteKeys in EEPROM
StoredKey eeprom;

U8X8_SH1106_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFlipMode(1);
  u8x8.setFont(SMALL_FONT);
  showName();
  u8x8.setCursor(0, 7);
  u8x8.print(F(" starting up..."));
  Serial.begin(38400);

  *learningInput = { 0, 0 };
  *lastLearnedInput = { 0, 0 };

  if (!checkROMInit()) {
    erase();
    for (int i = 0; i < COMMANDS_SIZE; i++) {
      RemoteKey k = {i, i, i};
      EEPROM.put(i * sizeof(RemoteKey), k);
    }
    setROMInitFlag(true);
    learning = true;
  }

  initPCIInterruptForTinyReceiver();

#ifdef USE_PHYSICAL_BUTTONS
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_DOWN_PIN, INPUT);
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_MENU_PIN, INPUT);
  pinMode(BUTTON_ENTER_PIN, INPUT);
  pinMode(BUTTON_POWER_PIN, INPUT);
#endif

  pinMode(LEARN_ENABLE_PIN, INPUT_PULLUP);

  pinMode(TX_ENABLE_PIN, OUTPUT);
  pinMode(RX_ENABLE_LOW_PIN, OUTPUT);

  digitalWrite(TX_ENABLE_PIN, HIGH);
  digitalWrite(RX_ENABLE_LOW_PIN, LOW);

  timers->lastPoll = millis();
  timers->learnHold = millis();
  timers->lastInput = millis();

#ifdef SERIAL_LOGGING
  Serial.println("All keys saved in eeprom:\n");
  for (int i = 0; i < COMMANDS_SIZE; i++) {
    RemoteKey k = eeprom[i];
    assert(k.id == i);
    Serial.print("Address: ");
    Serial.print(k.address, HEX);
    Serial.print(", command: ");
    Serial.print(k.code, HEX);
    Serial.print(", id: ");
    Serial.println(k.id, DEC);
  }
#endif
  u8x8.clearLine(7);
}

void showName() {
  u8x8.clear();
  u8x8.home();
  u8x8.setCursor(1, 4);
  u8x8.print(F("BKM-10iRduino"));
}

void loop() {
  updateState();
  processControlMessages();
  processCommandBuffer();
}

void updateState() {
  if (millis() - timers->lastPoll > POLL_RATE) {
    updateIsLearning();

    if (learning && (learnIndex < COMMANDS_SIZE)) {
      u8x8.drawString(0, 3, "press key:");
      char buffer[18] = {};
      strcpy_P(buffer, (char*)pgm_read_word(&(names[learnIndex])));
#ifdef SERIAL_LOGGING
      Serial.println(buffer);
#endif
      int l = strlen(buffer);

      u8x8.setInverseFont(1);
      u8x8.setCursor(0, 5);
      if (l <= 8) {
        u8x8.setFont(LARGE_FONT);
        for (int i = 0; i < (8 - strlen(buffer)) / 2; i++) {
          u8x8.print(" ");
        }
        u8x8.print(buffer);
        for (int i = 0; i <= (8 - strlen(buffer)) / 2; i++) {
          u8x8.print(" ");
        }
      } else {
        u8x8.setFont(MEDIUM_FONT);
        u8x8.setCursor(0, 5);
        u8x8.print(buffer);
      }
      u8x8.setFont(SMALL_FONT);

      u8x8.setInverseFont(0);
    }

#ifdef USE_PHYSICAL_BUTTONS
    int previous = buttonState;
    readButtons();

    if (previous != buttonState) {
      sendButtonCommand();
    }
#endif

    timers->lastPoll = millis();
    powerSave();
  }
}

//MARK:- BKM-10R TX/RX methods
void processControlMessages() {
  if (Serial.available()) {

#ifdef SERIAL_LOGGING
    Serial.println("\ninput\n");
#endif
    char bank[3];
    Serial.readBytes(bank, 3);
    byte kDown = Serial.read();
    byte group = Serial.read();
    byte mask = Serial.read();
    u8x8.setFont(SMALL_FONT);
    u8x8.setCursor(0, 8);
    u8x8.print(bank);
    u8x8.print(" ");
    u8x8.print(kDown, HEX);
    u8x8.print(" ");
    u8x8.print(group, HEX);
    u8x8.print(" ");
    u8x8.print(mask, HEX);
  }
}

void processCommandBuffer() {
  //Don't send if currently receiving
  if (!Serial.available()) {
    while (!commandBuffer.isEmpty()) {
      ControlCode *code = (ControlCode*)commandBuffer.shift();
      sendCode(code);
    }
  } else {
#ifdef SERIAL_LOGGING
    Serial.println("has serial waiting");
#endif
  }
}

/*
   Sending is currently made a blocking op by Serial.flush().
   This is to ensure that the serial buffer is empty when setting
   the half duplex MAX485E read enable after sending.

   This should be fine as it's only ever sending 4 bytes at a time.
*/
void sendCode(ControlCode *code) {
  Serial.write(ISWBank);
  Serial.write(keydown);
  Serial.write(code->group);
  Serial.write(code->code);
}

//MARK:- IR receiver interupt handlers
void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  timers->lastInput = millis();
  if (!learning) {
    handleRemoteCommand(aAddress, aCommand, isRepeat);
  } else {
    learnRemoteCommand(aAddress, aCommand, isRepeat);
  }
}

void handleRemoteCommand(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  RemoteKey input = { aAddress, aCommand, 99 };
  int x = sizeof(commands) / sizeof(Command);
  for (int i = 0; i < x; i++) {
    RemoteKey k = eeprom[i];
    if (equals(k, input)) {
      ControlCode *toSend = (ControlCode*)&commands[i].cmd;
      if (!isRepeat || commands[i].repeats) { //remotes set isRepeat when holding down a button
        commandBuffer.push(toSend);
#ifdef SERIAL_LOGGING
        char buffer[20];
        strcpy_P(buffer, (char*)pgm_read_word(&(names[i])));
        Serial.println("\nWill send command: ");
        Serial.print("0x");
        Serial.print(toSend->code, HEX);
        Serial.print("(");
        Serial.print(buffer);
        Serial.println(")");
#endif
      }
      return;
    }
  }
#ifdef SERIAL_LOGGING
  Serial.print("\nunknown key: ");
  Serial.print(aAddress, HEX);
  Serial.print(" ");
  Serial.println(aCommand, HEX);
#endif
}

//MARK:- Learn remote control
void updateIsLearning() {
  int learnButtonState = digitalRead(LEARN_ENABLE_PIN);
  if (learnButtonState == HIGH) {
    isHoldingLearnButton = false;
  } else {
    timers->lastInput = millis();
  }

  if (!learning) {
    if (learnButtonState == LOW) {
      if (!isHoldingLearnButton) {
        u8x8.clear();
        u8x8.setCursor(0, 2);
        u8x8.print(F("Hold to start"));
        u8x8.setCursor(0, 3);
        u8x8.print(F("learning remote"));
        isHoldingLearnButton = true;
        timers->learnHold = millis();
      } else if (millis() - timers->learnHold > LEARN_TIMEOUT) {

#ifdef SERIAL_LOGGING
        dumpNames();
#endif
        u8x8.clear();
        learnIndex = 0;
        learning = true;
      }
    }
  } else if (learnButtonState == LOW && !isHoldingLearnButton && millis() - timers->learnHold > LEARN_TIMEOUT) {
    cancelLearning();
  } else {
    processLearnQueue();
  }
}

void cancelLearning() {
#ifdef SERIAL_LOGGING
  Serial.println("cancel learning");
#endif
  learning = false;
  learningInput->address = 0;
  learningInput->code = 0;
  lastLearnedInput->address = 0;
  lastLearnedInput->code = 0;
  learnIndex = 0;
  showName();
}

void processLearnQueue() {
  u8x8.setCursor(0, 2);
  u8x8.print(learnIndex + 1, DEC);
  u8x8.print(" of ");
  u8x8.print(COMMANDS_SIZE);
  if (learnIndex >= COMMANDS_SIZE) {
    cancelLearning();
    return;
  }

  if (learningInput->address == 0) {
    return;
  }

#ifdef SERIAL_LOGGING
  RemoteKey old = eeprom[learnIndex];
  Serial.print("old: ");
  Serial.print(old.address, HEX);
  Serial.println(old.code, HEX);
#endif

  RemoteKey newKey = { learningInput->address, learningInput->code, learnIndex };

#ifdef SERIAL_LOGGING
  Serial.print("new: ");
  Serial.print(newKey.address, HEX);
  Serial.println(newKey.code, HEX);
#endif

  EEPROM.put(learnIndex * sizeof(RemoteKey), newKey);

  lastLearnedInput->address = newKey.address;
  lastLearnedInput->code = newKey.code;
  learningInput->address = 0;
  learningInput->code = 0;
  learnIndex++;
  u8x8.clear();
}

void learnRemoteCommand(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  //Easy ignore for holding ir button too long
  if (isRepeat) return;

  //Don't double process keys that don't send isRepeat, like vol +/-
  if (aAddress == lastLearnedInput->address && aCommand == lastLearnedInput->code) return;

  //Since we are coming from an interupt, don't process if main thread hasn't finished processing last command
  if (learningInput->address) return;

  RemoteKey incoming = { aAddress, aCommand, 0 };

  if (!equals(incoming, *lastLearnedInput)) {
    learningInput->address = aAddress;
    learningInput->code = aCommand;
  }
}

//MARK:- Physical button handling
#ifdef USE_PHYSICAL_BUTTONS
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
#endif

//MARK:- Helpers
bool equals(RemoteKey lhs, RemoteKey rhs) {
  return lhs.address == rhs.address && lhs.code == rhs.code;
}

void dumpNames() {
  int s = sizeof(commands) / sizeof(Command);
  for (int i = 0; i < s; i++) {
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(names[i])));
    Serial.println(buffer);
  }
}

void idleRS485(bool willIdle) {
  if (willIdle) {
    digitalWrite(RX_ENABLE_LOW_PIN, HIGH);
    digitalWrite(TX_ENABLE_PIN, LOW);
    rs485sleep = true;
  } else {
    digitalWrite(RX_ENABLE_LOW_PIN, LOW);
    rs485sleep = false;
  }
}

void powerSave() {
  if ((millis() - timers->lastInput > SLEEP_TIMER) && !displaySleep) {
    cancelLearning();
    u8x8.setPowerSave(1);
    displaySleep = true;
    //    idleRS485(true);
  } else if ((millis() - timers->lastInput < SLEEP_TIMER) && displaySleep) {
    //    digitalWrite(RX_ENABLE_LOW_PIN, LOW);
    u8x8.setPowerSave(0);
    showName();
    displaySleep = false;
  }
}

//MARK:- EEPROM
bool checkROMInit() {
  return EEPROM.read(EEPROM.length() - 1) == 0xAA;
}

void setROMInitFlag(bool value) {
  int toWrite = value ? 0xAA : 0x00;
  EEPROM.write(EEPROM.length() - 1, toWrite);
}

void erase(void)
{
  for (int i = 0 ; i < EEPROM.length() ; i++)
    EEPROM.write(i, 0);
}

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  // transmit diagnostic informations through serial link.
  Serial.println(__func);
  Serial.println(__file);
  Serial.println(__lineno, DEC);
  Serial.println(__sexp);
  Serial.flush();
  // abort program execution.
  abort();
}
