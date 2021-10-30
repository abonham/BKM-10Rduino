const byte keydown = 0x44;

const char ISWBank[] = "ISW";

struct RemoteKey {
  uint16_t address;
  uint8_t code;
} remoteKey;

struct ControlCode {
  byte group;
  byte code;
} controlCode;

struct Command {
  struct ControlCode cmd;
  struct RemoteKey key;
  bool repeats;
} command;

const int buttonUp = 1;
const int buttonDown = 1 << 1;
const int buttonMenu = 1 << 2;
const int buttonEnter = 1 << 3;
const int buttonPwr = 1 << 4;

const RemoteKey remotePwr = { 0x6CD2, 0xCB };
const RemoteKey remoteEnter = { 0x6DD2, 0x97 };
const RemoteKey remoteMenu = { 0x6CD2, 0x53 };
const RemoteKey remoteUp = { 0x6DD2, 0x82 };
const RemoteKey remoteDown = { 0x6DD2, 0x83 };
const RemoteKey remoteOne = { 0x2D2, 0xD5 };
const RemoteKey remoteTwo = { 0x2D2, 0xD6 };
const RemoteKey remoteThree = { 0x2D2, 0xD7 };
const RemoteKey remoteFour = { 0x2D2, 0xD8 };
const RemoteKey remoteFive = { 0x2D2, 0xD9 };
const RemoteKey remoteSix = { 0x2D2, 0xDA };
const RemoteKey remoteSeven = { 0x2D2, 0xDB };
const RemoteKey remoteEight = { 0x2D2, 0xDC };
const RemoteKey remoteNine = { 0x2D2, 0xDD };
const RemoteKey remoteZero = { 0x2D2, 0xDE };
const RemoteKey remoteDel = { 0x6DD2, 0x95 };
const RemoteKey remoteEnt = { 0x6DD2, 0x5D };
const RemoteKey remoteOverscan = { 0x6CD2, 0x88 };
const RemoteKey remoteShift = { 0x6CD2, 0x54 };


const ControlCode pwrCode = { 0x01, 0x10 };
const ControlCode upCode = { 0x02, 0x40 };
const ControlCode downCode = { 0x02, 0x80 };
const ControlCode menuCode = { 0x02, 0x10 };
const ControlCode enterCode = { 0x02, 0x20 };
const ControlCode zeroCode = { 0x00, 0x01 }; // 0
const ControlCode oneCode = { 0x00, 0x02 }; // 1
const ControlCode twoCode = { 0x00, 0x04 }; // 2
const ControlCode threeCode = { 0x00, 0x08 }; // 3
const ControlCode fourCode = { 0x00, 0x10 }; // 4
const ControlCode fiveCode = { 0x00, 0x20 }; // 5
const ControlCode sixCode = { 0x00, 0x40 }; // 6
const ControlCode sevenCode = { 0x00, 0x80 }; // 7
const ControlCode eightCode = { 0x01, 0x01 }; // 8
const ControlCode nineCode = { 0x01, 0x02 }; // 9
const ControlCode delCode = { 0x01, 0x04 }; // Del
const ControlCode entCode = { 0x01, 0x08 }; // Ent
const ControlCode overscanCode = { 0x03, 0x02 };
const ControlCode shiftCode = { 0x03, 0x01 };

const Command pwrCmd = { pwrCode, remotePwr, false };
const Command menuCmd = { menuCode, remoteMenu, false};
const Command enterCmd = { enterCode, remoteEnter, false};
const Command upCmd = { upCode, remoteUp, true };
const Command downCmd = { downCode, remoteDown, true };
const Command zeroCmd = { zeroCode, remoteZero, false };
const Command oneCmd = { oneCode, remoteOne, false };
const Command twoCmd = { twoCode, remoteTwo, false };
const Command threeCmd = { threeCode, remoteThree, false };
const Command fourCmd = { fourCode, remoteFour, false };
const Command fiveCmd = { fiveCode, remoteFive, false };
const Command sixCmd = { sixCode, remoteSix, false };
const Command sevenCmd = { sevenCode, remoteSeven, false };
const Command eightCmd = { eightCode, remoteEight, false };
const Command nineCmd = { nineCode, remoteNine, false };
const Command delCmd = { delCode, remoteDel, true };
const Command entCmd = { entCode, remoteEnt, false };
const Command overscanCmd = { overscanCode, remoteOverscan, false };
const Command shiftCmd = {shiftCode, remoteShift, false };

const struct Command commands[]  = {
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

/*
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

 */
