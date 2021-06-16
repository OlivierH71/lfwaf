/*
 *  Engine Processor class  FOR LFWAF on ESP32-32S
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#include <Ticker.h>
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
// #include "cntBtn.h"
#include "lfwaf_helpers.h"
#include "HW-354.h"
#include "lfwaf_engine.h"

/*************************************************************
                    Static Methods (GPIO handlers)
*************************************************************/
// Handler for buttonPressed
/*void btnPressedHandler(cntBtn *btn, void *parent){
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
  } 
}
*/

/*************************************************************
                    lfwaf_engine class
*************************************************************/

lfwaf_engine::lfwaf_engine(lfwaf_logger *log, lfwaf_settings *settings){
  _log = log;
  _settings = settings;

  _log->log(debug, "Setting buttons");
   pinMode(btnW_L_pin, INPUT_PULLUP);
   pinMode(btnW_R_pin, INPUT_PULLUP);
   pinMode(btnF_L_pin, INPUT_PULLUP);
   pinMode(btnF_R_pin, INPUT_PULLUP);
   pinMode(btnEOC_up_pin, INPUT_PULLUP);
   pinMode(btnEOC_dn_pin, INPUT_PULLUP);

}

/*************************************************************
                      Class Methods
*************************************************************/
void lfwaf_engine::focuserMove(boolean toUp){
  if (toUp){
    if (!isPressed(btnEOC_up_pin)){
      //_log->log(info, "Moving focuser up");
        _log->log(info, "Moving focuser up...");
        motorFocus->startMotor(speedW);
      }
      else
      _log->log(error, "Cannot move focuser up, end of Course reached");
    }
    else {
      if (!isPressed(btnEOC_dn_pin)){
      //_log->log(info, "Moving focuser down");
        _log->log(info, "Moving focuser down...");
        motorFocus->startMotor(-speedW);
        }
      else
      _log->log(error, "Cannot move focuser down, end of Course is reached");
    }
}

void lfwaf_engine::focuserStop(){
  motorFocus->stopMotor();
}

void lfwaf_engine::filterWheelStop(){
  motorWheel->stopMotor();
}

static void callbackWheelStop(lfwaf_engine *eng){
  eng->filterWheelStop();
}

void lfwaf_engine::filterWheelMoveTo(int newFilter){
    // direction depend on the nearest. eg, if we are on filter 5, and want to 
    // go to filter 1, the nearest is to go up 1
    // to go to filter 4, the nearest is to go down 1
    s8_t direction = 1;
    u8_t nbFilter = 0;
    if (newFilter > currentFilter){
      if ((newFilter - currentFilter) > 2) {
        direction = -1;
        nbFilter = currentFilter + (5-newFilter);
      }
      else
        nbFilter = newFilter - currentFilter;    
    }
    else{
            if ((newFilter - currentFilter) > 2) {
        direction = -1;
        nbFilter = currentFilter + (5-newFilter);
      }
      else
        nbFilter = newFilter - currentFilter;    
    }
     // We use Ticker rather than Timer. Ticker is easier to program
     motorWheel->startMotor(direction*speedW);
     //delayMicroseconds(2200);
     wheelMovedTicker.once_ms (2200*nbFilter, callbackWheelStop, this);
}

void lfwaf_engine::checkManualBtns(){
  if (isPressed(btnW_L_pin))
    filterWheelMoveTo(currentFilter > 1 ? currentFilter-1 : 5);
  if (isPressed(btnW_R_pin))
    filterWheelMoveTo(currentFilter < 4 ? currentFilter+1 : 1);

  // Focuser Up Button pushed ?
  if (isPressed(btnF_L_pin))
    if (motorFocus->getPWM() <= 0)
    {
      _log->log(debug,"Button Focus Left is pressed");
      focuserMove(true);
    }
  else
    // Left button has been released while speed was positive, ie, we were going up
    if (motorFocus->getPWM() > 0)
    {
      _log->log(debug,"Button Focus Left is released");
      focuserStop();
    }

  // Focuser Down Button pushed ?
  if (isPressed(btnF_R_pin))
    if (motorFocus->getPWM() >= 0)
    {
      _log->log(debug,"Button Focus Right is pressed");
      focuserMove(false);
    }
  else
    // Left button has been released while speed was negative, ie, we were going up
    if (motorFocus->getPWM() < 0)
    {
      _log->log(debug,"Button Focus Right is released");
      focuserStop();
    }
}
