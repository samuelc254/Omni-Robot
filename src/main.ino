#include "stepper.h"

motor bl_motor(2, 5, 8);
motor fl_motor(3, 6, 8);
motor br_motor(4, 7, 8);
motor fr_motor(12, 13, 8);

char fl_speed,
    fr_speed,
    bl_speed,
    br_speed;

unsigned long lastMillis = 0,
              radius = 200;

int angle = 0,
    x = 0,
    y = 0;

void move(char x, char y)
{

    if ((y != 0) && (x == 0))
    {
        fl_speed = y;
        fr_speed = y;
        bl_speed = y;
        br_speed = y;
    }
    else if ((y == 0) && (x != 0))
    {
        fl_speed = x;
        fr_speed = -x;
        bl_speed = -x;
        br_speed = x;
    }
    else if ((y != 0) && (x != 0))
    {
        fl_speed = (y + x) / 2;
        fr_speed = (y - x) / 2;
        bl_speed = (y - x) / 2;
        br_speed = (y + x) / 2;
    }
    else
    {
        fl_speed = 0;
        fr_speed = 0;
        bl_speed = 0;
        br_speed = 0;
    }

    fl_motor.run(fl_speed);
    fr_motor.run(fr_speed);
    bl_motor.run(bl_speed);
    br_motor.run(br_speed);
}

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

    move(x, y);
}
