#include <Arduino.h>
#define IR_INPUT_PIN    8
#include "TinyIRReceiver.hpp"
#include "constants.h"

bool processing = false;
bool sending = false;

void setup() {
  digitalWrite(2, HIGH);
  Serial.begin(38400);
  initPCIInterruptForTinyReceiver();
}

void loop() {

}

void sendCode(ControlCode code) {
  sending = true;
  Serial.write(ISWBank);
  delay(50);
  
  Serial.write(keydown);
  Serial.write(code.group);
  Serial.write(code.code);
  processing = false;
  sending = false;
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  if (isRepeat || sending) {
    return;
  }
  if (!processing) {
    processing = true;
  } else {
    return;
  }

  int x = sizeof(commands) / sizeof(Command);
  for (int i = 0; i < x; i++) {
    if (aAddress == commands[i].key.address) {
      if (aCommand == commands[i].key.code) {
        sendCode(commands[i].cmd);
        return;
      }
    }
  }

  processing = false;
}
