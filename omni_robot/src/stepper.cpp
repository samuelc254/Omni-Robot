#include "../include/stepper.h"

stepper::stepper(volatile uint8_t *_stepPort,
                 uint8_t _stepBit,
                 volatile uint8_t *_directionPort,
                 uint8_t _directionBit,
                 volatile uint8_t *_enablePort,
                 uint8_t _enableBit,
                 uint32_t _minVell,
                 uint32_t _maxVell)
{
    &stepPort = &_stepPort;
    &directionPort = &_directionPort;
    &enablePort = &_enablePort;
    stepBit = _stepBit;
    directionBit = _directionBit;
    enableBit = _enableBit;

    minVell = _minVell;
    maxVell = _maxVell;

    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    currentPosition = 0;
    targetPossition = 0;

    lastStep = 0;
}

void stepper::run(int8_t Vell)
{
    if (!Vell)
        return;

    stepDelay = (Vell > 0) ? Vell : -Vell;
    stepDelay = map(stepDelay, 0, 127, minVell, maxVell);

    if (micros() - lastStep >= stepDelay)
    {
        if (Vell > 0)
        {
            WriteBit(directionPort, directionBit, HIGH);
            currentPosition++;
        }
        else
        {
            WriteBit(directionPort, directionBit, LOW);
            currentPosition--;
        }

        WriteBit(stepPort, stepBit, HIGH);
        delayMicroseconds(1);
        WriteBit(stepPort, stepBit, LOW);
        lastStep = micros();
    }
}

void stepper::stepTo(int32_t _targetPossition, uint8_t vell)
{
    targetPossition = _targetPossition;
    stepDelay = map(vell, 0, 255, minVell, maxVell);

    if (targetPossition != currentPosition)
    {

        if (micros() - lastStep >= stepDelay)
        {
            if ((targetPossition - currentPosition) > 0)
            {
                WriteBit(directionPort, directionBit, HIGH);
                currentPosition++;
            }
            else
            {
                WriteBit(directionPort, directionBit, LOW);
                currentPosition--;
            }
            WriteBit(stepPort, stepBit, HIGH);
            delayMicroseconds(1);
            WriteBit(stepPort, stepBit, LOW);
            lastStep = micros();
        }
    }
}
