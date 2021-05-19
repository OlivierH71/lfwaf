/*
 * Drives a DC Motor using a HW-354 (MX1508) from an ESP32
 * Motor can run one way or reverse using 2 PINS
 * Works with GPIO2,4,12,13,14,15,25,26,27,32,33
 * 
*/
#include "HW-354.h"

#define PINA 32
#define PINB 33
#define NUMPWM 2
#define CHANNELA 0

HW354 motorA(PINA,PINB, CHANNELA, FAST_DECAY, PWM_2PIN);
int rotSpeed;
int increment = 5;

void setup() {
  Serial.begin(115200);
  motorA.stopMotor();
  rotSpeed = 0;
}

void loop() {
  // set the brightness on LEDC channel 0
  Serial.printf("Motor Speed : %03d\n", rotSpeed);
  motorA.startMotor(rotSpeed+=increment);
  if (rotSpeed <= -255 || rotSpeed >= 255) {
    increment = -increment;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
