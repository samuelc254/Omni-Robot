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

#define blueLed 15
#define redLed1 0
#define redLed2 1

#define deadzone 7

int8_t pins[] = {18, 19, 20},
       axis[3];

uint16_t reads[3],
    maxReads[] = {0, 0, 0},
    minReads[] = {1023, 1023, 1023};

uint32_t lastBlink = 0;

inline void readAxis() __attribute__((always_inline));

void setup()
{
  Wire.begin();
  SerialBegin(9600);

  pinMode(blueLed, OUTPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);

  for (int i = 0; i < 3; i++)
  {
    pinMode(pins[i], INPUT);
  }

  for (int i = 0; i < 3; i++)
  {
    while ((minReads[i] > 100) && (maxReads[i] < 923))
    {
      if (millis() > (lastBlink + 500))
      {
        digitalWrite(redLed1, !digitalRead(redLed1));
        digitalWrite(redLed2, !digitalRead(redLed2));
        lastBlink = millis();
      }
      readAxis();
    }
  }
}

void loop()
{
  if (millis() > (lastBlink + 100))
  {
    digitalWrite(blueLed, !digitalRead(blueLed));
    lastBlink = millis();
  }

  readAxis();

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

void readAxis()
{
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
}