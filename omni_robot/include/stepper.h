#ifndef stepper_included
#define stepper_included

#include <Arduino.h>
#include "MEGA_cpu_map.h"

class stepper
{
private:
    volatile uint8_t *stepDdr;
    volatile uint8_t *stepPort;
    uint8_t stepBit;
    volatile uint8_t *directionDdr;
    volatile uint8_t *directionPort;
    uint8_t directionBit;
    volatile uint8_t *enableDdr;
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
     * @brief construtor da classe stepper sem inicialização dos pinos
     * @param _stepPort ponteiro para o registrador de porta do pino de passo
     * @param _stepBit bit do registrador de porta do pino de passo
     * @param _directionPort ponteiro para o registrador de porta do pino de direção
     * @param _directionBit bit do registrador de porta do pino de direção
     * @param _enablePort ponteiro para o registrador de porta do pino de habilitação
     * @param _enableBit bit do registrador de porta do pino de habilitação
     * @param _minVell microsegundos entre passos para velocidade minima do motor (valores mais altos fazem o motor andar mais devagar)
     * @param _maxVell microsegundos entre passos para velocidade maxima do motor (valores mais baixos fazem o motor andar mais rapido)
     * @example stepper motor(&PORTB, 0, &PORTB, 1, &PORTB, 2, 7000, 800); // cria um objeto motor com os pinos de passo em PB0, direção em PB1 e habilitação em PB2
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
     * @brief construtor da classe stepper com inicialização dos pinos
     * @param _stepDdr ponteiro para o registrador de direção de data do pino de passo
     * @param _stepPort ponteiro para o registrador de porta do pino de passo
     * @param _stepBit bit do registrador de porta do pino de passo
     * @param _directionDdr ponteiro para o registrador de direção de data do pino de direção
     * @param _directionPort ponteiro para o registrador de porta do pino de direção
     * @param _directionBit bit do registrador de porta do pino de direção
     * @param _enableDdr ponteiro para o registrador de direção de data do pino de habilitação
     * @param _enablePort ponteiro para o registrador de porta do pino de habilitação
     * @param _enableBit bit do registrador de porta do pino de habilitação
     * @param _minVell microsegundos entre passos para velocidade minima do motor (valores mais altos fazem o motor andar mais devagar)
     * @param _maxVell microsegundos entre passos para velocidade maxima do motor (valores mais baixos fazem o motor andar mais rapido)
     * @example stepper motor(&DDRB, &PORTB, 0, &DDRB, &PORTB, 1, &DDRB, &PORTB, 2, 7000, 800); // cria um objeto motor com os pinos de passo em PB0, direção em PB1 e habilitação em PB2
     */
    stepper(volatile uint8_t *_stepDdr,
            volatile uint8_t *_stepPort,
            uint8_t _stepBit,
            volatile uint8_t *_directionDdr,
            volatile uint8_t *_directionPort,
            uint8_t _directionBit,
            volatile uint8_t *_enableDdr,
            volatile uint8_t *_enablePort,
            uint8_t _enableBit,
            uint32_t _minVell,
            uint32_t _maxVell);

    /**
     * @brief método para rotacionar o motor livremente
     * @param Vell velocidade do motor valores negativos significam sentido anti-horário e valores positivos significam sentido horário
     * @example stepper.run(63); // gira o motor na metade da velocidade máxima no sentido horário
     */
    void run(int8_t Vell);

    /**
     * @brief método para rotacionar o motor até uma posição específica
     * @param _targetPossition posição alvo do motor (em passos)
     * @param vell velocidade do motor
     * @example stepper.stepTo(1000, 255); // gira o motor até a posição 1000 na velocidade máxima
     */
    void stepTo(int32_t _targetPossition, uint8_t vell);
};
#endif