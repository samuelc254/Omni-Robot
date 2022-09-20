#include <Wire.h>
#include "stepper.h"
#include "motion.h"

#define SERIAL_LOG 1
#if SERIAL_LOG == 1
#define SerialBegin(x) Serial.begin(x)
#define SerialPrint(x) Serial.print(String(x))
#define SerialPrintln(x) Serial.println(String(x))
#else
#define SerialBegin(x)
#define SerialPrint(x)
#define SerialPrintln(x)
#endif

#define minVell 7000
#define maxVell 500
#define adress 12

stepper bl_motor(2, 5, 8, minVell, maxVell);
stepper fl_motor(3, 6, 8, minVell, maxVell);
stepper br_motor(4, 7, 8, minVell, maxVell);
stepper fr_motor(12, 13, 8, minVell, maxVell);

omniRobot robot(&fl_motor, &fr_motor, &bl_motor, &br_motor);

/*
  uint32_t lastMillis = 0,
         radius = 200;
*/

int8_t x = 0,
       y = 0,
       w = 0;

void setup()
{
  Wire.begin(adress);
  Wire.onReceive(receiveEvent);

  SerialBegin(9600);
}

void loop()
{
  /*
    if (millis() >= lastMillis + radius)
    {
     angle++;
     lastMillis = millis();
    }

    x = sin((angle * 3.14) / 180) * 127;
    y = cos((angle * 3.14) / 180) * 127;
  */
  
  SerialPrint("x");
  SerialPrint(x);
  SerialPrint(" y");
  SerialPrint(y);
  SerialPrint(" w");
  SerialPrintln(w);
  
  robot.move(x, y, w);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    x = Wire.read();
    y = Wire.read();
    w = Wire.read();
  }
}
