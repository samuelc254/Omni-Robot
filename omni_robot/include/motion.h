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
              stepper *_br_motor);

    /**
     * @brief move o robô omnidirecional
     * @param _xAcell: aceleração no eixo x (de -127 a 127)
     * @param _yAcell: aceleração no eixo y (de -127 a 127)
     * @param _wAcell: aceleração no eixo de rotação (de -127 a 127)
     * @example robot.move(127, 127, 0); // move o robô para a diagonal superior direita
     */
    void move(int8_t _xAcell, int8_t _yAcell, int8_t _wAcell = 0);
};
#endif