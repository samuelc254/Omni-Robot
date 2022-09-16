#include "stepper.h"
#include "motion.h"

#define minVell 7000
#define maxVell 500

stepper bl_motor(2, 5, 8, minVell, maxVell);
stepper fl_motor(3, 6, 8, minVell, maxVell);
stepper br_motor(4, 7, 8, minVell, maxVell);
stepper fr_motor(12, 13, 8, minVell, maxVell);

omniRobot robot(&fl_motor, &fr_motor, &bl_motor, &br_motor);

uint32_t lastMillis = 0,
         radius = 200;

int16_t angle = 0,
        x = 0,
        y = 0;

void setup()
{
}

void loop()
{
    if (millis() >= lastMillis + radius)
    {
        angle++;
        lastMillis = millis();
    }

    x = sin((angle * 3.14) / 180) * 127;
    y = cos((angle * 3.14) / 180) * 127;

    robot.move(x, y);
}