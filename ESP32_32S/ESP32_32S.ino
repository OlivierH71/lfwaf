/*
  lfwaf using NodeMCU ESP32-32S
*/
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_wifi.h"
#include "lfwaf_helpers.h"
#include "cntBtn.h"
#include "HW-354.h"

/*************************************************************
  Manual Buttons Definitions
*************************************************************/
#define btnW_L_pin  19
#define btnW_R_pin  21
#define btnF_L_pin  22
#define btnF_R_pin  23
#define btnEOC_up_pin 5
#define btnEOC_dn_pin 18


cntBtn *btnW_L,*btnW_R, *btnF_L, *btnF_R, *btnEOC_up, *btnEOC_dn;

/*************************************************************
  Motor Definitions
*************************************************************/
#define motW_L_pin  26
#define motW_R_pin  27
#define motF_L_pin  32
#define motF_R_pin  33

#define motorMinValue 255
#define motorMaxValue 255

#define CHANNEL_W 0
#define CHANNEL_F 1

HW354 motorWheel(motW_L_pin, motW_R_pin, CHANNEL_W);
HW354 motorFocus(motF_L_pin, motF_R_pin, CHANNEL_F);

int speedW = motorMinValue;
int speedF = motorMinValue;
int wheelMove = 0;

lfwaf_logger _log(true);
lfwaf_settings _settings(&_log);
lfwaf_wifi _wifi(&_log, &_settings);
lfwaf_server _server(&_log, &_settings);

/*************************************************************
                          Methods
*************************************************************/
void focuserMove(boolean toUp){
  if (toUp){
    if (digitalRead(btnEOC_up_pin)){
      _log.log(info, "Moving focuser up");
        motorFocus.startMotor(speedW);
      }
      else
      _log.log(info, "Cannot move focuser up, End of Course reached");
    }
    else {
      if (digitalRead(btnEOC_dn_pin)){
      _log.log(info, "Moving focuser down");
        motorFocus.startMotor(-speedW);
        }
      else
      _log.log(info, "Cannot move focuser down, End of Course is reached");
    }
}

// Handler for buttonPressed
void btnPressedHandler(cntBtn *btn){
  // Several cases:
  switch(btn->PIN){
    // End of course for focuser
    case btnEOC_up_pin: motorFocus.stopMotor();break;
    case btnEOC_dn_pin: motorFocus.stopMotor();break;
    // FilterWheel -
    case btnW_L_pin: wheelMove--; break;
    // FilterWheel +
    case btnW_R_pin: wheelMove++; break;
    // Move focuser up
    case btnF_L_pin: focuserMove(true);break;
    // Move focuser down
    case btnF_R_pin: focuserMove(false);break;
  }
}

// Handler for buttonReleased
void btnReleasedHandler(cntBtn *btn){
  _log.log(info,"Stopping focuser");
  motorFocus.stopMotor();
  /* switch(btn->PIN){
    case btnF_L_pin:  moto motorFocus.stopMotor();break;
    // Move focuser down
    case btnF_R_pin: motorFocus.stopMotor();break;
  } */
}

/*************************************************************
                        ARDUINO SETUP
*************************************************************/
void setup() {
  // Create logger
  _log = new lfwaf_logger(true);
  _log.log(info, "lfwaf is starting");
  _log.log(debug, "Setting buttons");

  // Create Buttons instances
  btnW_L = new cntBtn(btnW_L_pin);
  btnW_R = new cntBtn(btnW_R_pin);
  btnF_L = new cntBtn(btnF_L_pin);
  btnF_R = new cntBtn(btnF_R_pin);
  btnEOC_up = new cntBtn(btnEOC_up_pin);
  btnEOC_dn = new cntBtn(btnEOC_dn_pin);

  // Set interupt handlers for each button
  btnW_L->setOnPressed(btnPressedHandler);
  btnW_R->setOnPressed(btnPressedHandler);
  btnF_L->setOnPressed(btnPressedHandler);
  btnF_R->setOnPressed(btnPressedHandler);
  btnEOC_up->setOnPressed(btnPressedHandler);
  btnEOC_dn->setOnPressed(btnPressedHandler);

  btnF_L->setOnReleased(btnReleasedHandler);
  btnF_R->setOnReleased(btnReleasedHandler);

}

/*************************************************************
                        ARDUINO LOOP
*************************************************************/
void loop() {
  // Button actions are directly managed by interrupt
  // motors impulsions are driven by PWM
  

}
