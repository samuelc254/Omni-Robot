#include <Wire.h>
#include "stepper.h"
#include "motion.h"

#define DEBUG_MODE 0
#define DEBUG_LOG 1
#define I2C_EVENT 1

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

#if DEBUG_MODE == 1
inline void debug_mode() __attribute__((always_inline));
void debug_mode()
{
  static uint32_t lastMillis = 0,
                  radius = 100;

  static int8_t angle = 0;

  if (millis() >= lastMillis + radius)
  {
    angle++;
    lastMillis = millis();
  }

  x = sin((angle * 3.14) / 180) * 127;
  y = cos((angle * 3.14) / 180) * 127;

  robot.move(x, y);
}
#endif

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
