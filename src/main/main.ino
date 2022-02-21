#include "stepper.h"

motor motor1(9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (motor1.getPos() != -50) {
    motor1.stepTo(-50, 100);
    Serial.println(motor1.getPos());
  }
  while (motor1.getPos() != 50) {
    motor1.stepTo(50, 100);
    Serial.println(motor1.getPos());
  }
}
