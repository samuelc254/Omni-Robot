#include <Wire.h>
#include "stepper.h"
#include "motion.h"
#include "debug.h"

#define DEBUG_MODE 1
#define DEBUG_LOG 1
#define I2C_EVENT 0

#define minVell 7000
#define maxVell 500
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
  SerialPrintln(w);

#if DEBUG_MODE == 0
  robot.move(x, y, w);
#else
  debug_mode();
#endif
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    x = Wire.read();
    y = Wire.read();
    w = Wire.read();
  }
}
