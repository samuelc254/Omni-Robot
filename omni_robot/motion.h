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
    /**
     * @brief Construtor da classe omniRobot
     * @param _fl_motor: motor frontal esquerdo
     * @param _fr_motor: motor frontal direito
     * @param _bl_motor: motor traseiro esquerdo
     * @param _br_motor: motor traseiro direito
     * @example omniRobot robot(&fl_motor, &fr_motor, &bl_motor, &br_motor);
     */
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

    /**
     * @brief move o robô omnidirecional
     * @param _xAcell: aceleração no eixo x (de -127 a 127)
     * @param _yAcell: aceleração no eixo y (de -127 a 127)
     * @param _wAcell: aceleração no eixo de rotação (de -127 a 127)
     * @example robot.move(127, 127, 0); // move o robô para a diagonal superior direita
     */

    void move(int8_t _xAcell, int8_t _yAcell, int8_t _wAcell = 0)
    {

        uint8_t axis = 0;
        if (_xAcell != 0)
            axis++;
        if (_yAcell != 0)
            axis++;
        if (_wAcell != 0)
            axis++;

        if (axis > 0)
        {
            fl_speed = (_yAcell + _xAcell + _wAcell) / axis;
            fr_speed = (_yAcell - _xAcell - _wAcell) / axis;
            bl_speed = (_yAcell - _xAcell + _wAcell) / axis;
            br_speed = (_yAcell + _xAcell - _wAcell) / axis;

            fl_motor->run(fl_speed);
            fr_motor->run(fr_speed);
            bl_motor->run(bl_speed);
            br_motor->run(br_speed);
        }
        else
        {
            fl_speed = 0;
            fr_speed = 0;
            bl_speed = 0;
            br_speed = 0;
        }
    }
};
#endif