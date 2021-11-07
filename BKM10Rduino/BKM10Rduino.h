
#include <Arduino.h>

#define IR_INPUT_PIN        7
#define BUTTON_DOWN_PIN     A7
#define BUTTON_UP_PIN       A6
#define BUTTON_MENU_PIN     A5
#define BUTTON_ENTER_PIN    A4
#define BUTTON_POWER_PIN    A3
#define TX_ENABLE_PIN       2
#define LEARN_ENABLE_PIN    5

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#include "TinyIRReceiver.hpp"

const byte keydown = 0x44;

const char ISWBank[] = "ISW";

struct RemoteKey {
  uint16_t address;
  uint8_t code;
  uint8_t id;
} remoteKey;

struct StoredKey {
  RemoteKey operator [] (int) {
    return { 0x6CD2, 0xCB };
  };
};

bool equals(RemoteKey lhs, RemoteKey rhs) {
  return lhs.address == rhs.address && lhs.code == rhs.code;
}

struct ControlCode {
  byte group;
  byte code;
} controlCode;

struct Command {
  struct ControlCode cmd;
  struct RemoteKey key;
  bool repeats;
  char * desc;
} command;

struct ButtonCommand {
  struct ControlCode cmd;
  int button;
  int pin;
  bool repeats;
} buttonCommand;

struct Timers {
  long lastPoll;
  long learnHold;
  long lastInput;
};

#define buttonUp 1
#define buttonDown 1 << 1
#define buttonMenu 1 << 2
#define buttonEnter 1 << 3
#define buttonPwr 1 << 4

static RemoteKey remotePwr =      { 0x6CD2, 0xCB, 0   };
static RemoteKey remoteEnter =    { 0x6DD2, 0x97, 1   };
static RemoteKey remoteMenu =     { 0x6CD2, 0x53, 2   };
static RemoteKey remoteUp =       { 0x6DD2, 0x82, 3   };
static RemoteKey remoteDown =     { 0x6DD2, 0x83, 4   };
static RemoteKey remoteOne =      { 0x02D2, 0xD5, 5   };
static RemoteKey remoteTwo =      { 0x02D2, 0xD6, 6   };
static RemoteKey remoteThree =    { 0x02D2, 0xD7, 7   };
static RemoteKey remoteFour =     { 0x02D2, 0xD8, 8   };
static RemoteKey remoteFive =     { 0x02D2, 0xD9, 9   };
static RemoteKey remoteSix =      { 0x02D2, 0xDA, 10  };
static RemoteKey remoteSeven =    { 0x02D2, 0xDB, 11  };
static RemoteKey remoteEight =    { 0x02D2, 0xDC, 12  };
static RemoteKey remoteNine =     { 0x02D2, 0xDD, 13  };
static RemoteKey remoteZero =     { 0x02D2, 0xDE, 14  };
static RemoteKey remoteDel =      { 0x6DD2, 0x95, 15  };
static RemoteKey remoteEnt =      { 0x6DD2, 0x5D, 16  };
static RemoteKey remoteOverscan = { 0x6CD2, 0x88, 17  };
static RemoteKey remoteShift =    { 0x6CD2, 0x54, 18  };
//
//static ControlCode pwrCode = { 0x01, 0x10 };
//static ControlCode upCode = { 0x02, 0x40 };
//static ControlCode downCode = { 0x02, 0x80 };
//static ControlCode menuCode = { 0x02, 0x10 };
//static ControlCode enterCode = { 0x02, 0x20 };
//static ControlCode zeroCode = { 0x00, 0x01 }; // 0
//static ControlCode oneCode = { 0x00, 0x02 }; // 1
//static ControlCode twoCode = { 0x00, 0x04 }; // 2
//static ControlCode threeCode = { 0x00, 0x08 }; // 3
//static ControlCode fourCode = { 0x00, 0x10 }; // 4
//static ControlCode fiveCode = { 0x00, 0x20 }; // 5
//static ControlCode sixCode = { 0x00, 0x40 }; // 6
//static ControlCode sevenCode = { 0x00, 0x80 }; // 7
//static ControlCode eightCode = { 0x01, 0x01 }; // 8
//static ControlCode nineCode = { 0x01, 0x02 }; // 9
//static ControlCode delCode = { 0x01, 0x04 }; // Del
//static ControlCode entCode = { 0x01, 0x08 }; // Ent
//static ControlCode overscanCode = { 0x03, 0x02 };
//static ControlCode shiftCode = { 0x03, 0x01 };

//static Command pwrCmd = { pwrCode, remotePwr, false, "Power" };
//static Command menuCmd = { menuCode, remoteMenu, false, "Menu"};
//static Command enterCmd = { enterCode, remoteEnter, false, "Enter"};
//static Command upCmd = { upCode, remoteUp, true, "Menu up"};
//static Command downCmd = { downCode, remoteDown, true, "Menu down" };
//static Command zeroCmd = { zeroCode, remoteZero, false, "Num 0" };
//static Command oneCmd = { oneCode, remoteOne, false, "Num 1" };
//static Command twoCmd = { twoCode, remoteTwo, false, "Num 2" };
//static Command threeCmd = { threeCode, remoteThree, false, "Num 3" };
//static Command fourCmd = { fourCode, remoteFour, false, "Num 4" };
//static Command fiveCmd = { fiveCode, remoteFive, false, "Num 5" };
//static Command sixCmd = { sixCode, remoteSix, false, "Num 6" };
//static Command sevenCmd = { sevenCode, remoteSeven, false, "Num 7" };
//static Command eightCmd = { eightCode, remoteEight, false, "Num 8" };
//static Command nineCmd = { nineCode, remoteNine, false, "Num 9" };
//static Command delCmd = { delCode, remoteDel, true, "Num del" };
//static Command entCmd = { entCode, remoteEnt, false, "Num ent" };
//static Command overscanCmd = { overscanCode, remoteOverscan, false, "Overscan" };
//static Command shiftCmd = {shiftCode, remoteShift, false, "Shift" };

//const ButtonCommand pwrButton = { pwrCode, buttonPwr, BUTTON_POWER_PIN, false };
//const ButtonCommand menuButton = { menuCode, buttonMenu, BUTTON_MENU_PIN, false };
//const ButtonCommand enterButton = { enterCode, buttonEnter, BUTTON_ENTER_PIN, false };
//const ButtonCommand upButton = { upCode, buttonUp, BUTTON_UP_PIN, true };
//const ButtonCommand downButton = { downCode, buttonDown, BUTTON_DOWN_PIN, true };


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

static struct Command commands[] = {
  { { 0x01, 0x10 }, remotePwr, false, names[0] },
  { { 0x02, 0x10 }, remoteMenu, false, names[1]},
  { { 0x02, 0x20 }, remoteEnter, false, names[2]},
  { { 0x02, 0x40 }, remoteUp, true, names[3]},
  { { 0x02, 0x80 }, remoteDown, true, names[4] },
  { { 0x00, 0x01 }, remoteZero, false, names[5] },
  { { 0x00, 0x02 }, remoteOne, false, names[6] },
  { { 0x00, 0x04 }, remoteTwo, false, names[7] },
  { { 0x00, 0x08 }, remoteThree, false, names[8] },
  { { 0x00, 0x10 }, remoteFour, false, names[9] },
  { { 0x00, 0x20 }, remoteFive, false, names[10] },
  { { 0x00, 0x40 }, remoteSix, false, names[11] },
  { { 0x00, 0x80 }, remoteSeven, false, names[12] },
  { { 0x01, 0x01 }, remoteEight, false, names[13] },
  { { 0x01, 0x02 }, remoteNine, false, names[14] },
  { { 0x01, 0x04 }, remoteDel, true, names[15] },
  { { 0x01, 0x08 }, remoteEnt, false, names[16] },
  { { 0x03, 0x01 }, remoteShift, false, names[17] },
  { { 0x03, 0x02 }, remoteOverscan, false, names[18] },
};

const struct ButtonCommand buttonCommands[] = {
  //  pwrButton,
  //  menuButton,
  //  enterButton,
  //  upButton,
  //  downButton,
};
