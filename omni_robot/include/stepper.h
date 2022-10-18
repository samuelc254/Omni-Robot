#ifndef stepper_included
#define stepper_included

#include <Arduino.h>

class stepper
{
private:
    uint8_t stepPin,
        directionPin,
        enablePin;

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
    stepper(uint8_t _stepPin,
            uint8_t _directionPin,
            uint8_t _enablePin,
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