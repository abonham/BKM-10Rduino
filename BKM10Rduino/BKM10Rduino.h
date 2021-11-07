#include <Arduino.h>

#define COMMANDS_SIZE 19
#define IR_INPUT_PIN        7
#define TX_ENABLE_PIN       2
#define RX_ENABLE_LOW_PIN   3
#define LEARN_ENABLE_PIN    5

#include "TinyIRReceiver.hpp"
#include <EEPROM.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


/*
 * Holds any timestamps required for time based events
 */
struct Timers {
  unsigned long lastPoll;
  unsigned long learnHold;
  unsigned long lastInput;
};

const byte keydown = 0x44;
const char ISWBank[] = "ISW";

struct RemoteKey {
  uint16_t address;
  uint8_t code;
  uint8_t id;
} remoteKey;

/**
 * Provides a convenience subscript accessor to EEPROM for stored key codes
 * 
 * Treats EEPROM from address 0 as an array equivalent to `RemoteKey keys[]`
 */
struct StoredKey {
  RemoteKey operator [] (int i) {
    RemoteKey k;
    EEPROM.get(i * sizeof(RemoteKey), k);
    return k;
  };
};

/*
 * Two byte BKM-10R control code
 * 
 * Codes sent over RS485 as `keydown, group, code`
 */
struct ControlCode {
  byte group;
  byte code;
} controlCode;

struct Command {
  struct ControlCode cmd;
  bool repeats;
  uint8_t id;
} command;

const char power[] PROGMEM = "Power";
const char menu[] PROGMEM = "Menu";
const char enter[] PROGMEM = "Enter";
const char up[] PROGMEM = "Up";
const char down[] PROGMEM = "Down";
const char zero[] PROGMEM = "0";
const char one[] PROGMEM = "1";
const char two[] PROGMEM = "2";
const char three[] PROGMEM = "3";
const char four[] PROGMEM = "4";
const char five[] PROGMEM = "5";
const char six[] PROGMEM = "6";
const char seven[] PROGMEM = "7";
const char eight[] PROGMEM = "8";
const char nine[] PROGMEM = "9";
const char del[] PROGMEM = "Del";
const char ent[] PROGMEM = "Ent";
const char shiftSel[] PROGMEM = "Shift";
const char overscan[] PROGMEM = "Overscan";

const char * const names[] PROGMEM = {
  power,
  menu,
  enter,
  up,
  down,
  zero,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  del,
  ent,
  shiftSel,
  overscan,
};

#define BKM_POWER     { 0x01, 0x10 }
#define BKM_MENU      { 0x02, 0x10 }
#define BKM_ENTER     { 0x02, 0x20 }
#define BKM_UP        { 0x02, 0x40 }
#define BKM_DOWN      { 0x02, 0x80 }
#define BKM_ZERO      { 0x00, 0x01 }
#define BKM_ONE       { 0x00, 0x02 }
#define BKM_TWO       { 0x00, 0x04 }
#define BKM_THREE     { 0x00, 0x08 }
#define BKM_FOUR      { 0x00, 0x10 }
#define BKM_FIVE      { 0x00, 0x20 }
#define BKM_SIX       { 0x00, 0x40 }
#define BKM_SEVEN     { 0x00, 0x80 }
#define BKM_EIGHT     { 0x01, 0x01 }
#define BKM_NINE      { 0x01, 0x02 }
#define BKM_DEL       { 0x01, 0x04 }
#define BKM_ENT       { 0x01, 0x08 }
#define BKM_SHIFT     { 0x03, 0x01 }
#define BKM_OVERSCAN  { 0x03, 0x02 }

const struct Command commands[] = {
  { BKM_POWER, false, 0 },
  { BKM_MENU, false, 1},
  { BKM_ENTER, false, 2},
  { BKM_UP, true, 3},
  { BKM_DOWN, true, 4 },
  { BKM_ZERO, false, 5 },
  { BKM_ONE, false, 6 },
  { BKM_TWO, false, 7 },
  { BKM_THREE, false, 8 },
  { BKM_FOUR, false, 9 },
  { BKM_FIVE, false, 10 },
  { BKM_SIX, false, 11 },
  { BKM_SEVEN, false, 12 },
  { BKM_EIGHT, false, 13 },
  { BKM_NINE, false, 14 },
  { BKM_DEL, true, 15 },
  { BKM_ENT, false, 16 },
  { BKM_SHIFT, false, 17 },
  { BKM_OVERSCAN, false, 18 },
};

#ifdef USE_PHYSICAL_BUTTONS

#define BUTTON_DOWN_PIN     A7
#define BUTTON_UP_PIN       A6
#define BUTTON_MENU_PIN     A5
#define BUTTON_ENTER_PIN    A4
#define BUTTON_POWER_PIN    A3

#define buttonUp 1
#define buttonDown 1 << 1
#define buttonMenu 1 << 2
#define buttonEnter 1 << 3
#define buttonPwr 1 << 4

struct ButtonCommand {
  struct ControlCode cmd;
  int button;
  int pin;
  bool repeats;
} buttonCommand;

const struct ButtonCommand buttonCommands[] = {
    { BKM_POWER, buttonPwr, BUTTON_POWER_PIN, false };,
    { BKM_MENU, buttonMenu, BUTTON_MENU_PIN, false },
    { BKM_ENTER, buttonEnter, BUTTON_ENTER_PIN, false },
    { BKM_UP, buttonUp, BUTTON_UP_PIN, true },
    { BKM_DOWN, buttonDown, BUTTON_DOWN_PIN, true },
};
#endif
