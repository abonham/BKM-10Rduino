#include <Arduino.h>
#define IR_INPUT_PIN    8
#include "TinyIRReceiver.hpp"
#include "constants.h"

ControlCode *next;

void setup() {
  digitalWrite(9, HIGH);
  Serial.begin(38400);
  

  initPCIInterruptForTinyReceiver();
}

void loop() {
  if (next != NULL) {
    sendCode(next);
    next = NULL;
  }
}

void sendCode(ControlCode *code) {
  Serial.write(ISWBank);
  delay(50);
  
  Serial.write(keydown);
  Serial.write(code->group);
  Serial.write(code->code);
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  int x = sizeof(commands) / sizeof(Command);
  for (int i = 0; i < x; i++) {
    if (aAddress == commands[i].key.address) {
      if (aCommand == commands[i].key.code) {
        ControlCode *toSend = (ControlCode*)&commands[i].cmd;
        if (!isRepeat || (isRepeat && commands[i].repeats)) {
          next = toSend;
        }
        return;
      }
    }
  }
}
