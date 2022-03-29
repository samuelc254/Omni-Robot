#define tx 23

void setup() {
  pinMode(tx, OUTPUT);
  digitalWrite(tx, HIGH);
}

void loop() {
  for (byte i = 0; i < 256; i++) {
    send_byte(i);
    delay(100);
  }
}

void send_byte(byte a) {
  digitalWrite(tx, LOW);
  delayMicroseconds(250);
  for (int i = 0; i < 8; i++) {
    digitalWrite(tx, bitRead(a, i));
    delayMicroseconds(250);
  }
  digitalWrite(tx, HIGH);
}