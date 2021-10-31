
#include <Arduino.h>

#define IR_INPUT_PIN        8
#define BUTTON_DOWN_PIN     2
#define BUTTON_UP_PIN       3
#define BUTTON_MENU_PIN     7
#define BUTTON_ENTER_PIN    4
#define BUTTON_POWER_PIN    5
#define TX_ENABLE_PIN       12
#define LEARN_ENABLE_PIN    10

#include "TinyIRReceiver.hpp"

const byte keydown = 0x44;

const char ISWBank[] = "ISW";

struct RemoteKey {
  uint16_t address;
  uint8_t code;
} remoteKey;

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
} command;

struct ButtonCommand {
  struct ControlCode cmd;
  int button;
  int pin;
  bool repeats;
} buttonCommand;

const int buttonUp = 1;
const int buttonDown = 1 << 1;
const int buttonMenu = 1 << 2;
const int buttonEnter = 1 << 3;
const int buttonPwr = 1 << 4;

static RemoteKey remotePwr = { 0x6CD2, 0xCB };
static RemoteKey remoteEnter = { 0x6DD2, 0x97 };
static RemoteKey remoteMenu = { 0x6CD2, 0x53 };
static RemoteKey remoteUp = { 0x6DD2, 0x82 };
static RemoteKey remoteDown = { 0x6DD2, 0x83 };
static RemoteKey remoteOne = { 0x2D2, 0xD5 };
static RemoteKey remoteTwo = { 0x2D2, 0xD6 };
static RemoteKey remoteThree = { 0x2D2, 0xD7 };
static RemoteKey remoteFour = { 0x2D2, 0xD8 };
static RemoteKey remoteFive = { 0x2D2, 0xD9 };
static RemoteKey remoteSix = { 0x2D2, 0xDA };
static RemoteKey remoteSeven = { 0x2D2, 0xDB };
static RemoteKey remoteEight = { 0x2D2, 0xDC };
static RemoteKey remoteNine = { 0x2D2, 0xDD };
static RemoteKey remoteZero = { 0x2D2, 0xDE };
static RemoteKey remoteDel = { 0x6DD2, 0x95 };
static RemoteKey remoteEnt = { 0x6DD2, 0x5D };
static RemoteKey remoteOverscan = { 0x6CD2, 0x88 };
static RemoteKey remoteShift = { 0x6CD2, 0x54 };

static ControlCode pwrCode = { 0x01, 0x10 };
static ControlCode upCode = { 0x02, 0x40 };
static ControlCode downCode = { 0x02, 0x80 };
static ControlCode menuCode = { 0x02, 0x10 };
static ControlCode enterCode = { 0x02, 0x20 };
static ControlCode zeroCode = { 0x00, 0x01 }; // 0
static ControlCode oneCode = { 0x00, 0x02 }; // 1
static ControlCode twoCode = { 0x00, 0x04 }; // 2
static ControlCode threeCode = { 0x00, 0x08 }; // 3
static ControlCode fourCode = { 0x00, 0x10 }; // 4
static ControlCode fiveCode = { 0x00, 0x20 }; // 5
static ControlCode sixCode = { 0x00, 0x40 }; // 6
static ControlCode sevenCode = { 0x00, 0x80 }; // 7
static ControlCode eightCode = { 0x01, 0x01 }; // 8
static ControlCode nineCode = { 0x01, 0x02 }; // 9
static ControlCode delCode = { 0x01, 0x04 }; // Del
static ControlCode entCode = { 0x01, 0x08 }; // Ent
static ControlCode overscanCode = { 0x03, 0x02 };
static ControlCode shiftCode = { 0x03, 0x01 };

static Command pwrCmd = { pwrCode, remotePwr, false };
static Command menuCmd = { menuCode, remoteMenu, false};
static Command enterCmd = { enterCode, remoteEnter, false};
static Command upCmd = { upCode, remoteUp, true };
static Command downCmd = { downCode, remoteDown, true };
static Command zeroCmd = { zeroCode, remoteZero, false };
static Command oneCmd = { oneCode, remoteOne, false };
static Command twoCmd = { twoCode, remoteTwo, false };
static Command threeCmd = { threeCode, remoteThree, false };
static Command fourCmd = { fourCode, remoteFour, false };
static Command fiveCmd = { fiveCode, remoteFive, false };
static Command sixCmd = { sixCode, remoteSix, false };
static Command sevenCmd = { sevenCode, remoteSeven, false };
static Command eightCmd = { eightCode, remoteEight, false };
static Command nineCmd = { nineCode, remoteNine, false };
static Command delCmd = { delCode, remoteDel, true };
static Command entCmd = { entCode, remoteEnt, false };
static Command overscanCmd = { overscanCode, remoteOverscan, false };
static Command shiftCmd = {shiftCode, remoteShift, false };

const ButtonCommand pwrButton = { pwrCode, buttonPwr, BUTTON_POWER_PIN, false };
const ButtonCommand menuButton = { menuCode, buttonMenu, BUTTON_MENU_PIN, false };
const ButtonCommand enterButton = { enterCode, buttonEnter, BUTTON_ENTER_PIN, false };
const ButtonCommand upButton = { upCode, buttonUp, BUTTON_UP_PIN, true };
const ButtonCommand downButton = { downCode, buttonDown, BUTTON_DOWN_PIN, true };

static struct Command commands[] = {
  pwrCmd,
  menuCmd,
  enterCmd,
  upCmd,
  downCmd,
  shiftCmd,
  overscanCmd,
  zeroCmd,
  oneCmd,
  twoCmd,
  threeCmd,
  fourCmd,
  fiveCmd,
  sixCmd,
  sevenCmd,
  eightCmd,
  nineCmd,
  delCmd,
  entCmd,
};

const struct ButtonCommand buttonCommands[] = {
  pwrButton,
  menuButton,
  enterButton,
  upButton,
  downButton,
};
