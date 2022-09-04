/**
  Piano Tiles Bot
  Name: piano-tiles-bot
  Purpose: Automatically plays the game Piano Tiles.

  @author Lucas Vieira da Silva
  @version 1.0 4/9/22

  (other information may be added here)
*/
#include <Servo.h>
#include <AceRoutine.h>
using namespace ace_routine;

/* Setting Ports */
int PHOTO_SENSOR_PORT1 = 0;
int PHOTO_SENSOR_PORT2 = 1;
int PHOTO_SENSOR_PORT3 = 2;
int PHOTO_SENSOR_PORT4 = 3;

int SERVO_PORT1 = 4;
int SERVO_PORT2 = 5;
int SERVO_PORT3 = 6;
int SERVO_PORT4 = 7;

/* Initializing servo objects */
Servo SERVO_CONTROLLER1;
Servo SERVO_CONTROLLER2;
Servo SERVO_CONTROLLER3;
Servo SERVO_CONTROLLER4;

/* Util lists */
int lightCalibration;
int lightValue;

/* Constants */
const int CALIBRATION_BALANCE = 50;
const int DEFAULT_WAIT_TIME = 100;

void write_servo(int sensorPort, boolean isDark) {
  Servo servoObject;
  switch(sensorPort) {
    case 0:
      servoObject = SERVO_CONTROLLER1;
      break;
    case 1:
      servoObject = SERVO_CONTROLLER2;
      break;
    case 2:
      servoObject = SERVO_CONTROLLER3;
      break;
    case 3:
      servoObject = SERVO_CONTROLLER4;
      break;
  }
  int angle = isDark ? 120 : 0;
  servoObject.write(angle);
}

boolean check_photo_resistor(int sensorPort_) {
  lightValue[sensorPort] = analogRead(sensorPort);
  return 
    lightValue[sensorPort] < 
    (lightCalibration[sensorPort] - CALIBRATION_BALANCE);
}

COROUTINE(checkResistor1) {
  COROUTINE_LOOP() {
    write_servo(PHOTO_SENSOR_PORT1, check_photo_resistor(PHOTO_SENSOR_PORT1));
    COROUTINE_DELAY(DEFAULT_WAIT_TIME);
  }
}

COROUTINE(checkResistor2) {
  COROUTINE_LOOP() {
    write_servo(PHOTO_SENSOR_PORT2, check_photo_resistor(PHOTO_SENSOR_PORT2));
    COROUTINE_DELAY(DEFAULT_WAIT_TIME);
  }
}

COROUTINE(checkResistor3) {
  COROUTINE_LOOP() {
    write_servo(PHOTO_SENSOR_PORT3, check_photo_resistor(PHOTO_SENSOR_PORT3));
    COROUTINE_DELAY(DEFAULT_WAIT_TIME);
  }
}

COROUTINE(checkResistor4) {
  COROUTINE_LOOP() {
    write_servo(PHOTO_SENSOR_PORT4, check_photo_resistor(PHOTO_SENSOR_PORT4));
    COROUTINE_DELAY(DEFAULT_WAIT_TIME);
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  /*Avoid issues with serial taking a while to load*/
  while (!Serial);
  /*Attaching servos°*/
  SERVO_CONTROLLER1.attach(SERVO_PORT1);
  SERVO_CONTROLLER2.attach(SERVO_PORT2);
  SERVO_CONTROLLER3.attach(SERVO_PORT3);
  SERVO_CONTROLLER4.attach(SERVO_PORT4);
  /*Reseting servos to 0°*/
  SERVO_CONTROLLER1.write(0);
  SERVO_CONTROLLER2.write(0);
  SERVO_CONTROLLER3.write(0);
  SERVO_CONTROLLER4.write(0);
  /*Initializing calibration*/
  lightCalibration[] = {
    analogRead(PHOTO_SENSOR_PORT1),
    analogRead(PHOTO_SENSOR_PORT2),
    analogRead(PHOTO_SENSOR_PORT3),
    analogRead(PHOTO_SENSOR_PORT4),
  };
}

void loop() {
  checkResistor1.runCoroutine();
  checkResistor2.runCoroutine();
  checkResistor3.runCoroutine();
  checkResistor4.runCoroutine();
}
