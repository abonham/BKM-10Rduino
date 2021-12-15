#define LEARN_TIMEOUT 3000
#define SLEEP_TIMER 60000
#define CIRCULAR_BUFFER_INT_SAFE
//#define SERIAL_LOGGING
#define __ASSERT_USE_STDERR
#define POLL_RATE 33
#define I2C_DISPLAY

#define LARGE_FONT u8x8_font_px437wyse700b_2x2_f
#define MEDIUM_FONT  u8x8_font_7x14_1x2_f
#define SMALL_FONT u8x8_font_chroma48medium8_r

//#define USE_PHYSICAL_BUTTONS 1

#include "BKM10Rduino.h"
#include <CircularBuffer.h>

#include <assert.h>

CircularBuffer<void*, 4> commandBuffer;

#ifdef USE_PHYSICAL_BUTTONS
volatile int buttonState = 0;
#endif

volatile bool learning = false;
volatile bool isHoldingLearnButton = false;
volatile int learnIndex = 0;
struct RemoteKey *learningInput = malloc(sizeof(RemoteKey));
struct RemoteKey *lastLearnedInput = malloc(sizeof(RemoteKey));

struct Timers * timers = malloc(sizeof(Timers));
volatile bool displaySleep = false;
volatile bool rs485sleep = false;
volatile uint16_t leds = 0;
volatile enum selectedBank bank = none;

volatile int group2LEDMask = 0;
volatile int group3LEDMask = 0;
volatile int group4LEDMask = 0;

//subscript accessor for RemoteKeys in EEPROM
StoredKey eeprom;

#ifdef I2C_DISPLAY
U8X8_SSD1306_128X64_NONAME_SW_I2C  u8x8(10, 9, U8X8_PIN_NONE);
#else
//U8X8_SH1106_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 9, /* dc=*/ 10, /* reset=*/ 12);
U8X8_SH1106_128X64_NONAME_4W_SW_SPI u8x8(13, 11, /* cs=*/ 9, /* dc=*/ 10, /* reset=*/ 8);
#endif

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
  //  dumpEEPROM();
#endif
  u8x8.clearLine(7);
}

void dumpEEPROM() {
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
    //    powerSave();
  }
}

int checkBank(byte* b) {
#ifdef SERIAL_LOGGING
  Serial.print(b[0], HEX);
  Serial.print(b[1], HEX);
  Serial.println(b[2], HEX);
  Serial.println((char*)b);
#endif

  if (strcmp(b, "ILE") == 0) {
    return ILE;
  }
  else if (strcmp(b, "ISW") == 0) {
    return ISW;
  }
  else if (strcmp(b, "IMT") == 0) {
    return IMT;
  }
  else if (strcmp(b, "IEN") == 0) {
    return IEN;
  }
  else if (strcmp(b, "ICC") == 0) {
    return ICC;
  }
  else if ((unsigned char)b[0] == 0x44) {
#ifdef SERIAL_LOGGING
    Serial.print(F("Group: "));
    Serial.println((unsigned char)b[1], HEX);
    Serial.print(F("Mask: "));
    Serial.println((unsigned char) b[2], HEX);
#endif
    return DATA;
  }
  else {
    return none;
  }
}

//MARK:- BKM-10R TX/RX methods
void processControlMessages() {
  if (Serial.available() >= 3) {
    byte incoming[4];                  //extra char for null termination
    Serial.readBytes(incoming, 3);
    incoming[3] = '\0';
    enum selectedBank packet = checkBank(incoming);
    if ((bank == ILE) && (packet == DATA)) {
      switch (incoming[1]) {
        case 0x02:
          group2LEDMask = incoming[2];
          break;
        case 0x03:
          group3LEDMask = incoming[2];
          break;
        case 0x04:
          group4LEDMask = incoming[2];
          break;
        default:
          break;
      }
#ifdef SERIAL_LOGGING
      Serial.println(F("In ILE Bank, process led status: "));
      Serial.println(group2LEDMask, HEX);
      Serial.println(group3LEDMask, HEX);
      Serial.println(group4LEDMask, HEX);
#endif
      u8x8.clear();
      updateLEDS();
    } else {
      bank = packet;
    }
  }
}

void updateLEDS() {
  u8x8.setFont(MEDIUM_FONT);
  u8x8.setCursor(0, 4);
  u8x8.setInverseFont(group2LEDMask & LED_PHASE);
  u8x8.print("Ph");
  u8x8.setCursor(3, 4);
  u8x8.setInverseFont(group2LEDMask & LED_CHROMA);
  u8x8.print("Ch");
  u8x8.setCursor(6, 4);
  u8x8.setInverseFont(group2LEDMask & LED_BRIGHT);
  u8x8.print("Br");
  u8x8.setCursor(9, 4);
  u8x8.setInverseFont(group2LEDMask & LED_CONTRAST);
  u8x8.print("Co");

  u8x8.setCursor(0, 0);
  u8x8.setInverseFont(group3LEDMask & LED_SHIFT);
  u8x8.print("Sh");
  u8x8.setCursor(3, 0);
  u8x8.setInverseFont(group3LEDMask & LED_OVERSCAN);
  u8x8.print("Ov");
  u8x8.setCursor(6, 0);
  u8x8.setInverseFont(group3LEDMask & LED_H_SYNC);
  u8x8.print("H");
  u8x8.setCursor(9, 0);
  u8x8.setInverseFont(group3LEDMask & LED_V_SYNC);
  u8x8.print("V");
  u8x8.setCursor(12, 0);
  u8x8.setInverseFont(group3LEDMask & LED_MONO);
  u8x8.print("Mo");

  u8x8.setCursor(0, 2);
  u8x8.setInverseFont(group4LEDMask & LED_APT);
  u8x8.print("Ap");
  u8x8.setCursor(3, 2);
  u8x8.setInverseFont(group4LEDMask & LED_COMB);
  u8x8.print("Cb");
  u8x8.setCursor(6, 2);
  u8x8.setInverseFont(group4LEDMask & LED_F1);
  u8x8.print("F1");
  u8x8.setCursor(9, 2);
  u8x8.setInverseFont(group4LEDMask & LED_F3);
  u8x8.print("F2");
  u8x8.setCursor(12, 2);
  u8x8.setInverseFont(group4LEDMask & LED_SAFE_AREA);
  u8x8.print("Sa");
}

void processCommandBuffer() {
  while (!commandBuffer.isEmpty()) {
    ControlCode *code = (ControlCode*)commandBuffer.shift();
    sendCode(code);
  }
}

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
  Serial.print("\nunknown key: ");
  Serial.print(aAddress, HEX);
  Serial.print(" ");
  Serial.println(aCommand, HEX);
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

void powerSave() {
  if ((millis() - timers->lastInput > SLEEP_TIMER) && !displaySleep) {
    cancelLearning();
    u8x8.setPowerSave(1);
    displaySleep = true;
  } else if ((millis() - timers->lastInput < SLEEP_TIMER) && displaySleep) {
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
