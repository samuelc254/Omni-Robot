#include "include/stepper.h"
#include "include/motion.h"
#include <Wire.h>

#define DEBUG_MODE 1
#define DEBUG_LOG 1
#define I2C_EVENT 0

#if DEBUG_LOG == 1
#define SerialBegin(x) Serial.begin(x)
#define SerialPrint(x) Serial.print(String(x))
#define SerialPrintln(x) Serial.println(String(x))
#else
#define SerialBegin(x)
#define SerialPrint(x)
#define SerialPrintln(x)
#endif

#define minVell 7000
#define maxVell 800
#define adress 12

stepper bl_motor(2, 5, 8, minVell, maxVell);
stepper fl_motor(3, 6, 8, minVell, maxVell);
stepper br_motor(4, 7, 8, minVell, maxVell);
stepper fr_motor(12, 13, 8, minVell, maxVell);

omniRobot robot(&fl_motor, &fr_motor, &bl_motor, &br_motor);

int8_t x = 0,
       y = 0,
       w = 0;

void setup()
{
  SerialBegin(9600);
#if I2C_EVENT == 1
  Wire.begin(adress);
  Wire.onReceive(receiveEvent);
#endif
}

void loop()
{
  SerialPrint("x");
  SerialPrint(x);
  SerialPrint(" y");
  SerialPrint(y);
  SerialPrint(" w");
  SerialPrint(w);
  SerialPrint(" fl");
  SerialPrint(robot.fl_speed);
  SerialPrint(" fr");
  SerialPrint(robot.fr_speed);
  SerialPrint(" bl");
  SerialPrint(robot.bl_speed);
  SerialPrint(" br");
  SerialPrintln(robot.br_speed);

#if DEBUG_MODE == 0
  robot.move(x, y, w);
#else
  x = 127;
  y = 100;
  robot.move(x, y);
#endif
}

#if I2C_EVENT == 1
void receiveEvent(int howMany)
{
  if (Wire.available())
  {
    x = Wire.read();
    y = Wire.read();
    w = Wire.read();
  }
}
#endif
