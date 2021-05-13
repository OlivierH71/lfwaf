// #include<ESP8266WiFi> 
/*
 
*/

#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_wifi.h"
#include "lfwaf_helpers.h"

#define btnW_L_pin  D4
#define btnW_R_pin  D5
#define btnF_L_pin  D6
#define btnF_R_pin  D7

#define motW_L_pin  D0
#define motW_R_pin  D1
#define motF_L_pin  D2
#define motF_R_pin  D3

#define motorMinValue 135
#define motorMaxValue 1023

int cnvSpeed(int speed20){
  return (motorMaxValue-motorMinValue)/20 * speed20;
}


int speedW=cnvSpeed(10);
int speedF=cnvSpeed(10);
int wheelMove = 0;

lfwaf_logger _log(true);
lfwaf_settings _settings(&_log);

// Aftr an interrupt, we process what happened exactly
void processBtn( int btn, int Speed){
  //bool starting = false;
  // btnPressed
  if (digitalRead(btn) == LOW)
    //starting = true;
    switch(btn){
      case btnW_L_pin: wheelMove--; break;
      case btnW_R_pin: wheelMove++; break;
      case btnF_L_pin: analogWrite(motW_L_pin, cnvSpeed(_settings->values.focuserSpeed));break;
      case btnF_L_pin: analogWrite(motW_R_pin, cnvSpeed(_settings->values.focuserSpeed));break;
    }
   else
    switch(btn){
//      case btnW_L_pin: WheelMove--; break;  // nothing
//      case btnW_R_pin: WheelMove++; break;  // nothing
      case btnF_L_pin: analogWrite(motW_L_pin, 0);break;
      case btnF_L_pin: analogWrite(motW_R_pin, 0);break;
    }
}

// Handler for onboard buttons. We set one interrupt per button
void ICACHE_RAM_ATTR btnW_L_ISR(){ processBtn(btnW_L,_settings->values.fwSpeed); }
void ICACHE_RAM_ATTR btnW_L_ISR(){ processBtn(btnW_R,_settings->values.fwSpeed); }
void ICACHE_RAM_ATTR btnW_L_ISR(){ processBtn(btnF_L,_settings->values.focuserSpeed); }
void ICACHE_RAM_ATTR btnW_L_ISR(){ processBtn(btnF_R,_settings->values.focuserSpeed); }

void setup() {
  // Create logger
  _log.log(info, "lfwaf is starting");
  _log.log(debug, "setting pins");

  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(btnW_L_pin, INPUT);
  pinMode(btnW_R_pin, INPUT);
  pinMode(btnF_L_pin, INPUT);
  pinMode(btnF_R_pin, INPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  //Change frequency for PWM functions
  analogWriteFreq(50);

   // Set an interupt for each button
  attachInterrupt(digitalPinToInterrupt(btnW_L_pin),btnW_L_ISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(btnW_R_pin),btnW_R_ISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(btnF_L_pin),btnF_L_ISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(btnF_R_pin),btnF_R_ISR,CHANGE);
  
}

void loop() {
  //read the pushbutton value into a variable
  if (digitalRead(btnW_L_pin) == LOW){
    analogWrite(motW_L_pin,135);
  } else {
    analogWrite(motW_L_pin,0);
  }
  if (digitalRead(btnW_R_pin) == LOW){
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(motW_R_pin,1023);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(motW_R_pin,0);
  }
}
