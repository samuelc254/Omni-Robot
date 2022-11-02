#include "./include/stepper.h"
#include "./include/motion.h"
#include <Wire.h>

#define DEBUG_MODE 0
#define DEBUG_LOG 0
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

stepper bl_motor(bl_motor_step_ddr, bl_motor_step_wPort, bl_motor_step_bit,
                 bl_motor_dir_ddr, bl_motor_dir_wPort, bl_motor_dir_bit,
                 motors_enable_ddr, motors_enable_wPort, motors_enable_bit,
                 minVell, maxVell);
stepper fl_motor(fl_motor_step_ddr, fl_motor_step_wPort, fl_motor_step_bit,
                 fl_motor_dir_ddr, fl_motor_dir_wPort, fl_motor_dir_bit,
                 motors_enable_ddr, motors_enable_wPort, motors_enable_bit,
                 minVell, maxVell);
stepper br_motor(br_motor_step_ddr, br_motor_step_wPort, br_motor_step_bit,
                 br_motor_dir_ddr, br_motor_dir_wPort, br_motor_dir_bit,
                 motors_enable_ddr, motors_enable_wPort, motors_enable_bit,
                 minVell, maxVell);
stepper fr_motor(fr_motor_step_ddr, fr_motor_step_wPort, fr_motor_step_bit,
                 fr_motor_dir_ddr, fr_motor_dir_wPort, fr_motor_dir_bit,
                 motors_enable_ddr, motors_enable_wPort, motors_enable_bit,
                 minVell, maxVell);

omniRobot robot(&fl_motor, &fr_motor, &bl_motor, &br_motor);

int8_t x = 0,
       y = 0,
       w = 0;

void setup()
{
  SerialBegin(2000000);
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
