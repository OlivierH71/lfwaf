/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#ifndef lfwaf_server_h
#define lfwaf_server_h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
////////////////////////////////////////////////////////////

//how many clients should be able to telnet to lwfaf? (one for indi and two for extern control)
#define MAX_SRV_CLIENTS 3
//#define TCP_PORT 23

class lfwaf_server {
  WiFiServer server(23); // TCP_PORT);
private:

  WiFiClient serverClients[MAX_SRV_CLIENTS];
  char clientMsgs[MAX_SRV_CLIENTS][64];
  byte clientMsgsIdx[MAX_SRV_CLIENTS];
  lfwaf_logger *_log;
  lfwaf_settings *_settings;
  void parseCmd(char *cmd);
public:

  lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings);
  void checkForClients();
  void processInputs();
  void announce(char *message);    // Default behavior is to answer or announce any event all connected telnet clients
};

#endif
