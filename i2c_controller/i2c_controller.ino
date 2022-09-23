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

#define led 15

#define deadzone 8

int8_t pins[] = {18, 19, 20},
       axis[3];

uint16_t reads[3],
         maxReads[] = {0, 0, 0},
         minReads[] = {0, 0, 0};

uint32_t lastBlink = 0;

void setup()
{
  Wire.begin();
  SerialBegin(9600);

  for (int i; i < 3; i++)
  {
    pinMode(pins[i], INPUT);
  }
  pinMode(led, OUTPUT);
}

void loop()
{
  if (millis() > (lastBlink + 100))
  {
    digitalWrite(led, !digitalRead(led));
    lastBlink = millis();
  }


  for (int i = 0; i < 3; i++)
  {
    reads[i] = analogRead(pins[i]);
    if (reads[i] > maxReads[i])
      maxReads[i] = reads[i];
    if (reads[i] < minReads[i])
      minReads[i] = reads[i];

    axis[i] = map(reads[i], minReads[i], maxReads[i], -127, 127);

    if ((axis[i] >= -deadzone) && (axis[i] <= deadzone))
      axis[i] = 0;
  }

  SerialPrint("x");
  SerialPrint(axis[0]);
  SerialPrint(" y");
  SerialPrint(axis[1]);
  SerialPrint(" w");
  SerialPrintln(axis[2]);

  Wire.beginTransmission(12);
  Wire.write(axis[0]); // axis X
  Wire.write(axis[1]); // axis Y
  Wire.write(axis[2]); // axis W
  Wire.endTransmission();
}
