class motor
{
    int stepPin;
    int directionPin;
    int enablePin;

    long Iposition;
    long Cposition;
    long Oposition;

    unsigned long stepDelay;
    unsigned long lastStep;

public:
    motor(int Spin, int Dpin, int Epin)
    {

        stepPin = Spin;
        directionPin = Dpin;
        enablePin = Epin;
        pinMode(stepPin, OUTPUT);
        pinMode(directionPin, OUTPUT);
        pinMode(enablePin, OUTPUT);

        Iposition = 0;
        Cposition = 0;
        Oposition = 0;

        lastStep = 0;
    }

    long getPos()
    {
        return Cposition;
    }

    void stepTo(int Opos, unsigned int maxVel)
    {
        Oposition = Opos;
        if (Oposition != Cposition)
        {

            if (micros() - lastStep >= maxVel)
            {
                if ((Oposition - Cposition) > 0)
                {
                    digitalWrite(directionPin, HIGH);
                    Cposition++;
                }
                else
                {
                    digitalWrite(directionPin, LOW);
                    Cposition--;
                }
                digitalWrite(stepPin, HIGH);
                delayMicroseconds(1);
                digitalWrite(stepPin, LOW);
                lastStep = micros();
            }
        }
        else
        {
            Iposition = Oposition;
        }
    }

    void run(char Vel)
    {

        if (micros() - lastStep >= stepDelay)
        {
            if (Vel > 0)
            {
                stepDelay = Vel;
                digitalWrite(directionPin, HIGH);
                Cposition++;
            }
            else if (Vel < 0)
            {
                stepDelay = -Vel;
                digitalWrite(directionPin, LOW);
                Cposition--;
            }
            else
                return;

            stepDelay = map(stepDelay, 0, 127, 500, 6000);

            digitalWrite(stepPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(stepPin, LOW);
            lastStep = micros();
        }
    }
};