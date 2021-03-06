/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#ifndef lfwaf_server_h
#define lfwaf_server_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
////////////////////////////////////////////////////////////

//how many clients should be able to telnet to lwfaf? (one for indi and two for extern control)
#define MAX_SRV_CLIENTS 3
//#define TCP_PORT 23

class lfwaf_server {
   // TCP_PORT);
public:
  lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings);
  void checkForClients();
  void processInputs();
  void announce(char *message);    // Default behavior is to answer or announce any event all connected telnet clients
private:
  WiFiServer server;
  WiFiClient serverClients[MAX_SRV_CLIENTS];
  char clientMsgs[MAX_SRV_CLIENTS][64];
  byte clientMsgsIdx[MAX_SRV_CLIENTS];
  lfwaf_logger *_log;
  lfwaf_settings *_settings;
  void parseCmd(char *cmd);

  void setWifi(int n, char* ssid, char* pwd);
  void changeFilterWNum(char *params);
  void changeFilterName(char *params);
  void changeFilterWSpeed(char *params);
  void setFilterNum(byte Filter);
  void setFilterName(int n, char *name);
  void setFilterNames(int n, char **name);
  void moveFocuser(byte dir, char *params);
  void changeHostName(char *params);
  void changeWifiSSID(char *params);
  void changeWifiPref(char *params);
};

#endif
