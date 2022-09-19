#include <Wire.h>

#define xPin A0
#define yPin A1
#define wPin A2

void setup() {
  Wire.begin();
  pinMode(xPin,INPUT);
}

void loop() {
  Wire.beginTransmission(12);
  Wire.write(55);
  Wire.write(100);
  Wire.write(-10);
  Wire.endTransmission();
}
