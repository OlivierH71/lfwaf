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

/*************************************************************
                    Static Methods (GPIO handlers)
*************************************************************/
// Handler for buttonPressed
void btnPressedHandler(cntBtn *btn, void *parent){
  lfwaf_engine* eng = static_cast<lfwaf_engine*>(parent);
  // Several cases:
  switch(btn->PIN){
    // End of course for focuser
    case btnEOC_up_pin: eng->motorFocus->stopMotor();break;
    case btnEOC_dn_pin: eng->motorFocus->stopMotor();break;
    // FilterWheel -
    case btnW_L_pin: eng->wheelMove--; break;
    // FilterWheel +
    case btnW_R_pin: eng->wheelMove++; break;
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

/*************************************************************
                    lfwaf_engine class
*************************************************************/

lfwaf_engine::lfwaf_engine(lfwaf_logger *log, lfwaf_settings *settings){
  _log = log;
  _settings = settings;

  _log->log(debug, "Setting buttons");

  // Create Buttons instances
  btnW_L    = new cntBtn(btnW_L_pin, this);
  btnW_R    = new cntBtn(btnW_R_pin, this);
  btnF_L    = new cntBtn(btnF_L_pin, this);
  btnF_R    = new cntBtn(btnF_R_pin, this);
  btnEOC_up = new cntBtn(btnEOC_up_pin, this);
  btnEOC_dn = new cntBtn(btnEOC_dn_pin, this);

  // Set interupt handlers for pressing each button
  btnW_L->setOnPressed(btnPressedHandler);
  btnW_R->setOnPressed(btnPressedHandler);
  btnF_L->setOnPressed(btnPressedHandler);
  btnF_R->setOnPressed(btnPressedHandler);
  btnEOC_up->setOnPressed(btnPressedHandler);
  btnEOC_dn->setOnPressed(btnPressedHandler);

  // Set interupt handlers for releasing focuser buttons
  btnF_L->setOnReleased(btnReleasedHandler);
  btnF_R->setOnReleased(btnReleasedHandler);

}

/*************************************************************
                      Class Methods
*************************************************************/
void lfwaf_engine::focuserMove(boolean toUp){
  if (toUp){
    if (digitalRead(btnEOC_up_pin)){
      //_log->log(info, "Moving focuser up");
        motorFocus->startMotor(speedW);
      }
      else
      _log->log(info, "Cannot move focuser up, end of Course reached");
    }
    else {
      if (digitalRead(btnEOC_dn_pin)){
      //_log->log(info, "Moving focuser down");
        motorFocus->startMotor(-speedW);
        }
      else
      _log->log(info, "Cannot move focuser down, end of Course is reached");
    }
}


