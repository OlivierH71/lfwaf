/*
 *  Engine Processor class  FOR LFWAF on ESP32-32S
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#include "lfwaf_engine.h"
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "cntBtn.h"
#include "HW-354.h"

lfwaf_engine::lfwaf_engine(lfwaf_logger *log){
    _log = log;

  _log->log(debug, "Setting buttons");

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
                          Methods
*************************************************************/
void lfwaf_engine::focuserMove(boolean toUp){
  if (toUp){
    if (digitalRead(btnEOC_up_pin)){
      _log->log(info, "Moving focuser up");
        motorFocus->startMotor(speedW);
      }
      else
      _log->log(info, "Cannot move focuser up, End of Course reached");
    }
    else {
      if (digitalRead(btnEOC_dn_pin)){
      _log->log(info, "Moving focuser down");
        motorFocus->startMotor(-speedW);
        }
      else
      _log->log(info, "Cannot move focuser down, End of Course is reached");
    }
}

// Handler for buttonPressed
void btnPressedHandler(cntBtn *btn, void *parent){
  lfwaf_engine* eng = static_cast<lfwaf_engine*>(parent);
  // Several cases:
  switch(btn->PIN){
    // End of course for focuser
    case btnEOC_up_pin: eng->motorFocus->stopMotor();break;
    case btnEOC_dn_pin: eng->motorFocus->stopMotor();break;
    // FilterWheel -
    case btnW_L_pin: wheelMove--; break;
    // FilterWheel +
    case btnW_R_pin: wheelMove++; break;
    // Move focuser up
    case btnF_L_pin: eng->focuserMove(true);break;
    // Move focuser down
    case btnF_R_pin: eng->focuserMove(false);break;
  }
}

// Handler for buttonReleased
void btnReleasedHandler(cntBtn *btn, void *parent){
  lfwaf_engine* eng = static_cast<lfwaf_engine*>(parent);
  eng->_log->log(info,"Stopping focuser");
  eng->motorFocus->stopMotor();
  /* switch(btn->PIN){
    case btnF_L_pin:  moto motorFocus.stopMotor();break;
    // Move focuser down
    case btnF_R_pin: motorFocus.stopMotor();break;
  } */
}
