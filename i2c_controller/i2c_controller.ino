#include <Wire.h>

#define DEBUG_LOG 0

#if DEBUG_LOG == 1
#define SerialBegin(x) Serial.begin(x)
#define SerialPrint(x) Serial.print(String(x))
#define SerialPrintln(x) Serial.println(String(x))
#else
#define SerialBegin(x)
#define SerialPrint(x)
#define SerialPrintln(x)
#endif

#define xPin A0
#define yPin A1
#define wPin A2
#define led 15

#define deadzone 8

int8_t x,
       y,
       w;

uint32_t lastBlink = 0;

void setup()
{
  Wire.begin();
  SerialBegin(9600);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(wPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  if (millis() > (lastBlink + 100))
  {
    digitalWrite(led, !digitalRead(led));
    lastBlink = millis();
  }

  x = map(analogRead(xPin), 0, 1023, -127, 127);
  y = map(analogRead(yPin), 0, 1023, -127, 127);
  w = map(analogRead(wPin), 0, 1023, -127, 127);

  if ((x >= -deadzone) && (x <= deadzone))
    x = 0;
  if ((y >= -deadzone) && (y <= deadzone))
    y = 0;
  if ((w >= -deadzone) && (w <= deadzone))
    w = 0;

  SerialPrint("x");
  SerialPrint(x);
  SerialPrint(" y");
  SerialPrint(y);
  SerialPrint(" w");
  SerialPrintln(w);

  Wire.beginTransmission(12);
  Wire.write(x);
  Wire.write(y);
  Wire.write(w);
  Wire.endTransmission();
}
