/**
  Piano Tiles Bot
  Name: piano-tiles-bot
  Purpose: Automatically plays the game Piano Tiles.

  @author Lucas Vieira da Silva
  @version 1.0 4/9/22
*/

#include <Servo.h>

int PHOTO_SENSOR_PORT1 = 0;
int PHOTO_SENSOR_PORT2 = 1;
int PHOTO_SENSOR_PORT3 = 2;
int PHOTO_SENSOR_PORT4 = 3;

int SERVO_PORT1 = 4;
int SERVO_PORT2 = 5;
int SERVO_PORT3 = 6;
int SERVO_PORT4 = 7;

const int lightDiff = 50;
int Id = 0;

class ServoController {
  private:
    byte pin;
    Servo controller;
  public:
    ServoController(byte pin) {
      this->pin = pin;
      init();
    };
    void init() {
      controller.attach(pin);
      controller.write(0);
    };
    void change_state(boolean state) {
      controller.write(state ? 180 : 0);
    };
};

class PhotoresistorController {
  private:
    byte pin;
    int lightCalibration;
    int lightValue;
  public:
    PhotoresistorController(byte pin) {
      this->pin = pin;
      init();
    }
    void init() {
      byte pin = this->pin;
      pinMode(pin, OUTPUT);
      lightCalibration = analogRead(pin);
    }
    boolean senses_light() {
      return lightValue < (lightCalibration - lightDiff);
    }
};

class KeyController {
  private:
    /* Pin Variables */
    byte servoPin;
    byte PRPin;
    /* Object Variables */
    ServoController servo;
    PhotoresistorController photoresistor;
  public:
    KeyController(ServoController &s) : servo(s) {
      this->servo = s;
    }
    KeyController(PhotoresistorController &r) : photoresistor(r) {
      this->photoresistor = r;
    }
    KeyController(byte PRPin, byte servoPin) {
      this->servoPin = servoPin;
      this->PRPin = PRPin;
      init();
    }
    void init() {
      Id += 1;
      Serial.print("Running key (");
      Serial.print(Id);
      Serial.println(")");
    }
    void analyze_key() {
      boolean senses_light = photoresistor.senses_light();
      servo.change_state(senses_light);
    }
};

KeyController key1(PHOTO_SENSOR_PORT1, SERVO_PORT1)
KeyController key2(PHOTO_SENSOR_PORT2, SERVO_PORT2)
KeyController key3(PHOTO_SENSOR_PORT3, SERVO_PORT3)
KeyController key4(PHOTO_SENSOR_PORT4, SERVO_PORT4)

void setup() {
  delay(1000);
}

void loop() {
  key1.analyze_key();
  key2.analyze_key();
  key3.analyze_key();
  key4.analyze_key();
  delay(100);
}
