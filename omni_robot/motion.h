#ifndef motion_included
#define motion_included

#include "stepper.h"

class omniRobot
{
private:
    int8_t fl_speed,
        fr_speed,
        bl_speed,
        br_speed;

    stepper *fl_motor,
        *fr_motor,
        *bl_motor,
        *br_motor;

public:
    omniRobot(stepper *_fl_motor,
              stepper *_fr_motor,
              stepper *_bl_motor,
              stepper *_br_motor)
    {
        this->fl_motor = _fl_motor;
        this->fr_motor = _fr_motor;
        this->bl_motor = _bl_motor;
        this->br_motor = _br_motor;
    }

    void move(int8_t _xAcell, int8_t _yAcell)
    {

        if ((_yAcell != 0) && (_xAcell == 0))
        {
            fl_speed = _yAcell;
            fr_speed = _yAcell;
            bl_speed = _yAcell;
            br_speed = _yAcell;
        }
        else if ((_yAcell == 0) && (_xAcell != 0))
        {
            fl_speed = _xAcell;
            fr_speed = -_xAcell;
            bl_speed = -_xAcell;
            br_speed = _xAcell;
        }
        else if ((_yAcell != 0) && (_xAcell != 0))
        {
            fl_speed = (_yAcell + _xAcell) / 2;
            fr_speed = (_yAcell - _xAcell) / 2;
            bl_speed = (_yAcell - _xAcell) / 2;
            br_speed = (_yAcell + _xAcell) / 2;
        }
        else
        {
            fl_speed = 0;
            fr_speed = 0;
            bl_speed = 0;
            br_speed = 0;
        }

        fl_motor->run(fl_speed);
        fr_motor->run(fr_speed);
        bl_motor->run(bl_speed);
        br_motor->run(br_speed);
    }
};
#endif