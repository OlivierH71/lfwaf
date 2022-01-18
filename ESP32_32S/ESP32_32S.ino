/*
  lfwaf using NodeMCU ESP32-32S
  This project relies on many classes:

  lfwaf_logger    logger class: it sends messages on different level to serial com' and Wifi link when connected
  lfwaf_settings  class relying on EEPROM. Stores settings locally in the MicroController (incl Wifi setting, speed and btns/motors IO pins)
  lfwaf_wifi      class based on Wifi class. Scans and connect to wifi.
  lfwaf_server    Action Server: handles queries sent to lfwaf. In Theory, could receive instructions from Wifi, serial or BLE and tells engine to operate
  lfwaf_engine    Hardware Engine: Manage buttons and motors actions
*/

#include "lfwaf_helpers.h"
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_wifi.h"
#include "lfwaf_server.h"
#include "lfwaf_engine.h"

lfwaf_logger *_log;
lfwaf_settings *_settings;
lfwaf_wifi *_wifi;
lfwaf_server *_server;
lfwaf_engine *_engine;

/*************************************************************
                        ARDUINO SETUP
*************************************************************/
void setup()
{
  // Create logger
  _log = new lfwaf_logger(true);
  _log->log(info, "lfwaf is starting");
  _log->log(info, "Loading settings");
  _settings = new lfwaf_settings(_log);
  _log->log(info, "Settings loaded");

  _log->log(info, "Starting Wifi");
  _wifi = new lfwaf_wifi(_log, _settings);
  _wifi->connect();
  _log->log(info, "Wifi started");

  _log->log(info, "Starting Engine");
  _engine = new lfwaf_engine(_log, _settings);
  _log->log(info, "Engine started");

  _log->log(info, "Starting LFWAF Server");
  _server = new lfwaf_server(_log, _settings, _engine);
  _log->log(info, "LFWAF server started");
}
void nop()
{
}

/*************************************************************
                        ARDUINO LOOP
*************************************************************/
void loop()
{

  // Main loop is about server and engine: We always lookup for new clients and process inputs

  // Check for new client:
  _server->checkForClients();
  // Check for Manual buttons
  _engine->checkManualBtns();
  // Check for remote commands
  _server->processInputs();
}
