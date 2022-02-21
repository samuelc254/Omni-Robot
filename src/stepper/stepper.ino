class motor
{
    int stepPin;
    int directionPin;
    int enablePin;

    long Iposition;
    long Cposition;
    long Oposition;

    unsigned long lastStep;

  public:
    motor(int Spin, int Dpin, int Epin) {

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

    long getPos() {
      return Cposition;
    }

    void stepTo(int Opos, unsigned int maxVel) {
      Oposition = Opos;
      if (Oposition != Cposition) {

        if (micros() - lastStep >= maxVel) {
          if ((Oposition - Cposition) > 0) {
            digitalWrite(directionPin, HIGH);
            Cposition++;
          } else {
            digitalWrite(directionPin, LOW);
            Cposition--;
          }
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(1);
          digitalWrite(stepPin, LOW);
          lastStep = micros();
        }

      } else {
        Iposition = Oposition;
      }
    }
    
};

motor motor1(9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (motor1.getPos() != -50) {
    motor1.stepTo(-50, 100);
    Serial.println(motor1.getPos());
  }
  while (motor1.getPos() != 50) {
    motor1.stepTo(50, 100);
    Serial.println(motor1.getPos());
  }
}
