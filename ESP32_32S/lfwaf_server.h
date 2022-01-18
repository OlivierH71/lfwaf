/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#ifndef lfwaf_server_h
#define lfwaf_server_h

#include <WiFiClient.h>
#include <WiFi.h>
#include <Ticker.h>
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_engine.h"

////////////////////////////////////////////////////////////

//how many clients should be able to telnet to lwfaf? (one for indi and two for extern control)
#define MAX_SRV_CLIENTS 3
//#define TCP_PORT 23

class lfwaf_server {
   // TCP_PORT);
public:
  lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings, lfwaf_engine *engine);
  void checkForClients();
  void processInputs();
  void announce(char *message);    // Default behavior is to answer or announce any event all connected telnet clients
private:
  WiFiServer server;
  WiFiClient serverClients[MAX_SRV_CLIENTS];
  char clientMsgs[MAX_SRV_CLIENTS][64];
  byte clientMsgsIdx[MAX_SRV_CLIENTS];
  char serialMsg[64];
  byte serialMsgIdx = 0;

  lfwaf_logger *_log;
  lfwaf_settings *_settings;
  lfwaf_engine *_engine;

  void parseCmd(char *cmd);

  void acknowledge();
  void setWifi(int n, char* ssid, char* pwd);
  void setFilterName(char *params);
  void setFilterWSpeed(char *params);
  void setFilterNum(byte Filter);
  void getFilterName(char *params);
  void setFilterNames(int n, char **name);
  void setFocuserSpeed(char *params);
  void getFocuserSpeed(char *params);

  bool focuserMoving = false;
  void moveFocuser(bool up, char *params);
  Ticker focuserMoveTicker;
  static void focuserTickerStop();
  bool isFocuserMoving();
  void stopFocuser();

  bool filterWMoving = false;
  void changeFilterWNum(char *params);
  Ticker filterWMoveTicker;
  static void filterWTickerStop();
  bool isfilterWMoving();

  void setHostName(char *params);
  void getHostName(char *params);
  void setWifiSSID(char *params);
  void getWifiSSID(char *params);
  void setWifiPref(char *params);
  void getWifiPref(char *params);
};

#endif
