/*
  lfwaf using NodeMCU ESP32-32S
*/
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_wifi.h"
#include "lfwaf_helpers.h"



lfwaf_logger _log(true);
lfwaf_settings _settings(&_log);
lfwaf_wifi _wifi(&_log, &_settings);
lfwaf_server _server(&_log, &_settings);



/*************************************************************
                        ARDUINO SETUP
*************************************************************/
void setup() {
  // Create logger
  _log = new lfwaf_logger(true);
  _log.log(info, "lfwaf is starting");


}

/*************************************************************
                        ARDUINO LOOP
*************************************************************/
void loop() {
  // Button actions are directly managed by interrupt
  // motors impulsions are driven by PWM
  

}
