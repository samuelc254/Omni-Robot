#include "../include/stepper.h"

stepper::stepper(uint8_t _stepPin,
                 uint8_t _directionPin,
                 uint8_t _enablePin,
                 uint32_t _minVell,
                 uint32_t _maxVell)
{
    stepPin = _stepPin;
    directionPin = _directionPin;
    enablePin = _enablePin;
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
    if (!stepDelay)
        return;

    stepDelay = (Vell > 0) ? Vell : -Vell;
    stepDelay = map(stepDelay, 0, 127, minVell, maxVell);

    if (micros() - lastStep >= stepDelay)
    {
        if (Vell > 0)
        {
            digitalWrite(directionPin, HIGH);
            currentPosition++;
        }
        else
        {
            digitalWrite(directionPin, LOW);
            currentPosition--;
        }

        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(stepPin, LOW);
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
                digitalWrite(directionPin, HIGH);
                currentPosition++;
            }
            else
            {
                digitalWrite(directionPin, LOW);
                currentPosition--;
            }
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(stepPin, LOW);
            lastStep = micros();
        }
    }
}