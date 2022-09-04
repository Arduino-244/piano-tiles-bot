#include <AceRoutine.h>
using namespace ace_routine;

const int LED = LED_BUILTIN;
const int LED_ON = HIGH;
const int LED_OFF = LOW;

COROUTINE(blinkLed) {
  COROUTINE_LOOP() {
    digitalWrite(LED, LED_ON);
    COROUTINE_DELAY(100);
    digitalWrite(LED, LED_OFF);
    COROUTINE_DELAY(500);
  }
}

COROUTINE(printHelloWorld) {
  COROUTINE_LOOP() {
    Serial.print(F("Hello, "));
    Serial.flush();
    COROUTINE_DELAY(1000);
    Serial.println(F("World"));
    COROUTINE_DELAY(4000);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  while (!Serial); // Leonardo/Micro
  pinMode(LED, OUTPUT);
}

void loop() {
  blinkLed.runCoroutine();
  printHelloWorld.runCoroutine();
}