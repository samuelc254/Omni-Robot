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
    stepPort = _stepPort;
    directionPort = _directionPort;
    enablePort = _enablePort;
    stepBit = _stepBit;
    directionBit = _directionBit;
    enableBit = _enableBit;

    minVell = _minVell;
    maxVell = _maxVell;

    currentPosition = 0;
    targetPossition = 0;

    lastStep = 0;
}

stepper::stepper(volatile uint8_t *_stepDdr,
                 volatile uint8_t *_stepPort,
                 uint8_t _stepBit,
                 volatile uint8_t *_directionDdr,
                 volatile uint8_t *_directionPort,
                 uint8_t _directionBit,
                 volatile uint8_t *_enableDdr,
                 volatile uint8_t *_enablePort,
                 uint8_t _enableBit,
                 uint32_t _minVell,
                 uint32_t _maxVell)
{
    stepDdr = _stepDdr;
    stepPort = _stepPort;
    stepBit = _stepBit;
    directionDdr = _directionDdr;
    directionPort = _directionPort;
    directionBit = _directionBit;
    enableDdr = _enableDdr;
    enablePort = _enablePort;
    enableBit = _enableBit;

    minVell = _minVell;
    maxVell = _maxVell;

    SetBit(*stepDdr, stepBit);
    SetBit(*directionDdr, directionBit);
    SetBit(*enableDdr, enableBit);

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
            SetBit(*directionPort, directionBit);
            currentPosition++;
        }
        else
        {
            ClrBit(*directionPort, directionBit);
            currentPosition--;
        }

        SetBit(*stepPort, stepBit);
        delayMicroseconds(1);
        ClrBit(*stepPort, stepBit);
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
                SetBit(*directionPort, directionBit);
                currentPosition++;
            }
            else
            {
                ClrBit(*directionPort, directionBit);
                currentPosition--;
            }
            SetBit(*stepPort, stepBit);
            delayMicroseconds(1);
            ClrBit(*stepPort, stepBit);
            lastStep = micros();
        }
    }
}
