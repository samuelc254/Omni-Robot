#define rx 9
byte val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(rx, INPUT);
}

void loop() {
  read_byte(val);
  Serial.println(val);
}

void read_byte(byte val) {
  if (!digitalRead(rx)) {
    delayMicroseconds(375);
    for (int i = 0; i < 8; i++) {
      bitWrite(val, i, digitalRead(rx));
      delayMicroseconds(250);
    }
  }
}