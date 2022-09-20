#if DEBUG_LOG == 1
#define SerialBegin(x) Serial.begin(x)
#define SerialPrint(x) Serial.print(String(x))
#define SerialPrintln(x) Serial.println(String(x))
#else
#define SerialBegin(x)
#define SerialPrint(x)
#define SerialPrintln(x)
#endif

#if DEBUG_MODE == 1
inline void debug_mode() __attribute__((always_inline));
void debug_mode()
{
  static uint32_t lastMillis = 0,
                  radius = 200;

  static int8_t angle = 0;

  if (millis() >= lastMillis + radius)
  {
    angle++;
    lastMillis = millis();
  }

  x = sin((angle * 3.14) / 180) * 127;
  y = cos((angle * 3.14) / 180) * 127;

  robot.move(x, y);
}
#endif
