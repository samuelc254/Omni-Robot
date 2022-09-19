#include <Wire.h>

#define xPin A0
#define yPin A1
#define wPin A2
#define led 13

int8_t x,
       y,
       w;

uint32_t lastBlink = 0;

void setup()
{
  Wire.begin();

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(wPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  if (millis() > (lastBlink + 1000))
  {
    digitalWrite(led, !digitalRead(led));
    lastBlink = millis();
  }

  x = map(analogRead(xPin), 0, 1023, -127, 127);
  y = map(analogRead(yPin), 0, 1023, -127, 127);
  w = map(analogRead(wPin), 0, 1023, -127, 127);

  Wire.beginTransmission(12);
  Wire.write(x);
  Wire.write(y);
  Wire.write(w);
  Wire.endTransmission();
}
