/*
  lfwaf using NodeMCU ESP32-32S
*/
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_wifi.h"
#include "lfwaf_helpers.h"

/*************************************************************
  Manual Buttons Definitions
*************************************************************/
#define btnW_L_pin  19
#define btnW_R_pin  21
#define btnF_L_pin  22
#define btnF_R_pin  23

/*************************************************************
  Motor Definitions
*************************************************************/
#define motW_L_pin  26
#define motW_R_pin  27
#define motF_L_pin  32
#define motF_R_pin  33

#define motorMinValue 34
#define motorMaxValue 255

#define CHANNEL_W 0
#define CHANNEL_F 1

HW354 motorWheel(motW_L_pin, motW_R_pin, CHANNEL_W);
HW354 motorFocus(motF_L_pin, motF_R_pin, CHANNEL_F);

/*************************************************************
                          Helpers
*************************************************************/
int speedW = motorMinValue;
int speedF = motorMinValue;
int wheelMove = 0;

lfwaf_logger _log(true);
lfwaf_settings _settings(&_log);

// After an interrupt, we process what happened exactly
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

/*************************************************************
                        ARDUINO SETUP
*************************************************************/
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

/*************************************************************
                        ARDUINO LOOP
*************************************************************/
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
