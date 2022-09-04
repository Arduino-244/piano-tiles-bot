/**
  Piano Tiles Bot
  Name: piano-tiles-bot
  Purpose: Automatically plays the game Piano Tiles.

  @author Lucas Vieira da Silva
  @version 1.0 4/9/22

  (other information may be added here)
*/
#include <AceRoutine.h>
using namespace ace_routine;

const int 1_PHOTO_SENSOR_PORT = 0;
const int 2_PHOTO_SENSOR_PORT = 1;
const int 3_PHOTO_SENSOR_PORT = 2;
const int 4_PHOTO_SENSOR_PORT = 3;

const int 1_SERVO_PORT = 4;
const int 2_SERVO_PORT = 5;
const int 3_SERVO_PORT = 6;
const int 4_SERVO_PORT = 7;

int lightCalibration = [];
int lightValue = [];

const calibrationBalance = 50;

void check_photo_resistor(int sensor_port) {
  lightValue[sensor_port] = analogRead(sensor_port);
  if (lightValue[sensor_port] < lightCalibration[sensor_port] - calibrationBalance) {
    
  }
}

COROUTINE(blinkLed) {
  COROUTINE_LOOP() {
    digitalWrite(LED, LED_ON);
    COROUTINE_DELAY(500);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  /*Avoid issues with serial taking a while to load*/
  while (!Serial);
  /*Loading Pinmodes*/
  pinMode(1_SERVO_PORT, OUTPUT);
  pinMode(2_SERVO_PORT, OUTPUT);
  pinMode(3_SERVO_PORT, OUTPUT);
  pinMode(4_SERVO_PORT, OUTPUT);
  /*Initializing calibration*/
  lightCalibration[1_PHOTO_SENSOR_PORT] = analogRead(1_PHOTO_SENSOR_PORT);
  lightCalibration[2_PHOTO_SENSOR_PORT] = analogRead(2_PHOTO_SENSOR_PORT);
  lightCalibration[3_PHOTO_SENSOR_PORT] = analogRead(3_PHOTO_SENSOR_PORT);
  lightCalibration[4_PHOTO_SENSOR_PORT] = analogRead(4_PHOTO_SENSOR_PORT);
}

void loop() {
  blinkLed.runCoroutine();
  printHelloWorld.runCoroutine();
}
