#ifndef stepper_included
#define stepper_included

#include <Arduino.h>
#include "MEGA_cpu_map.h"

class stepper
{
private:
    volatile uint8_t *stepPort;
    uint8_t stepBit;
    volatile uint8_t *directionPort;
    uint8_t directionBit;
    volatile uint8_t *enablePort;
    uint8_t enableBit;

    int32_t targetPossition;

    uint32_t stepDelay,
        lastStep,
        minVell,
        maxVell;

public:
    int32_t currentPosition;

    /**
     * @brief construtor da classe stepper
     * @param _stepPin: pino de passo do motor
     * @param _directionPin: pino de direção do motor
     * @param _enablePin: pino de habilitação do motor
     * @param _minVell: velocidade mínima do motor em microssegundos (valores mais altos significam velocidades mais baixas)
     * @param _maxVell: velocidade máxima do motor em microssegundos (valores mais baixos significam velocidades mais altas)
     * @example stepper motor(2, 5, 8, 7000, 800); // cria um objeto stepper chamado motor
     */
    stepper(volatile uint8_t *_stepPort,
            uint8_t _stepBit,
            volatile uint8_t *_directionPort,
            uint8_t _directionBit,
            volatile uint8_t *_enablePort,
            uint8_t _enableBit,
            uint32_t _minVell,
            uint32_t _maxVell);

    /**
     * @brief método para rotacionar o motor livremente
     * @param Vell: velocidade do motor valores negativos significam sentido anti-horário e valores positivos significam sentido horário
     * @example stepper.run(63); // gira o motor na metade da velocidade máxima no sentido horário
     */
    void run(int8_t Vell);

    /**
     * @brief método para rotacionar o motor até uma posição específica
     * @param _targetPossition: posição alvo do motor (em passos)
     * @param vell: velocidade do motor
     * @example stepper.stepTo(1000, 255); // gira o motor até a posição 1000 na velocidade máxima
     */
    void stepTo(int32_t _targetPossition, uint8_t vell);
};
#endif