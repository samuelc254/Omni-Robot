#ifndef motion_included
#define motion_included

#include "stepper.h"

class omniRobot
{
private:
    stepper *fl_motor,
        *fr_motor,
        *bl_motor,
        *br_motor;

public:
    int16_t fl_speed,
        fr_speed,
        bl_speed,
        br_speed;

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
        if (_xAcell == 0 && _yAcell == 0 && _wAcell == 0)
            return;

        fl_speed = (_yAcell + _xAcell + _wAcell);
        fr_speed = (_yAcell - _xAcell - _wAcell);
        bl_speed = (_yAcell - _xAcell + _wAcell);
        br_speed = (_yAcell + _xAcell - _wAcell);

        // check the greatest aceeleration module
        int8_t max_acell = abs(_xAcell);
        if (abs(_yAcell) > max_acell)
            max_acell = abs(_yAcell);
        if (abs(_wAcell) > max_acell)
            max_acell = abs(_wAcell);

        // check the greatest speed module
        int16_t max_speed = abs(fl_speed);
        if (abs(fr_speed) > max_speed)
            max_speed = abs(fr_speed);
        if (abs(bl_speed) > max_speed)
            max_speed = abs(bl_speed);
        if (abs(br_speed) > max_speed)
            max_speed = abs(br_speed);

        // normalize the speed values
        float speed_factor = (float)max_acell / (float)max_speed;
        fl_speed *= speed_factor;
        fr_speed *= speed_factor;
        bl_speed *= speed_factor;
        br_speed *= speed_factor;

        fl_motor->run(fl_speed);
        fr_motor->run(fr_speed);
        bl_motor->run(bl_speed);
        br_motor->run(br_speed);
    }
};
#endif