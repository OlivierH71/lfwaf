/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#include <WiFiClient.h>
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_helpers.h"
#include "lfwaf_server.h"

lfwaf_server::lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings) {
  _log = log;
  _settings = settings;
  //start server
  //WiFiServer server(23);
  _log->log(info,"Starting Wifi Server");
  server.begin(23);
  // IMPORTANT: Avoid Nagle, ie, wait for enough data to transmit packet. We need immediate communication
  server.setNoDelay(true);
  _log->log(info,"Ready! Use 'telnet' to connect");
  _log->setWifi(this);
}

void lfwaf_server::checkForClients(){
  if (server.hasClient()) {
    _log->log(debug, "Incoming client");
    //find free/disconnected client
    int i;
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
      if (!serverClients[i]) {
        serverClients[i] = server.available();
        _log->log(info, "New client #"+String(i+1));
        // Flush buffer index
        this->clientMsgsIdx[i] = 0;
        break;
      }

    //no free/disconnected spot so reject
    if (i == MAX_SRV_CLIENTS) {
      server.available().println("busy");
      _log->log(debug,String("server is busy with %d active connections\n" + i));
    }
  }
}

#define cmdSETFWNUM "SETFWNUM"
#define cmdSETFWNAME "SETFWNAME"
#define cmdSETFWSPEED "SETFWSPEED"
#define cmdFOCUSER_IN "FOCUSER_IN"
#define cmdFOCUSER_OUT "FOCUSER_OUT"
#define cmdSETHNAME "SETHNAME"
#define cmdSETWIFISSID "SETWIFISSID"
#define cmdSETWIFIPREF "SETWIFIPREF"

void lfwaf_server::changeFilterWNum(char *params){
    _log->log(debug,"changeFilterWNum");
}

void lfwaf_server::changeFilterName(char *params){
    _log->log(debug,"changeFilterName");
}

void lfwaf_server::changeFilterWSpeed(char *params){
    _log->log(debug,"changeFilterWSpeed");
}

void lfwaf_server::moveFocuser(byte dir, char *params){
    _log->log(debug,"moveFocuser");
}

void lfwaf_server::changeHostName(char *params){
    _log->log(debug,"changeHostName");
}

void lfwaf_server::changeWifiSSID(char *params){
    _log->log(debug,"changeWifiSSID");
}

void lfwaf_server::changeWifiPref(char *params){
    _log->log(debug,"changeWifiPref");
}

void lfwaf_server::parseCmd(char *cmd){
  _log->log(debug, "Parsing " + String(cmd));
  char leftCmd[64];
  char rightCmd[64];
  sscanf(cmd, "%s %s",leftCmd, rightCmd);
  if (leftCmd){
    UpperStr(leftCmd);
    if (!strcmp(leftCmd,cmdSETFWNUM)) changeFilterWNum(rightCmd);
    else if (!strcmp(leftCmd , cmdSETFWNAME)) changeFilterName(rightCmd);
    else if (!strcmp(leftCmd , cmdSETFWSPEED)) changeFilterWSpeed(rightCmd);
    else if (!strcmp(leftCmd , cmdFOCUSER_IN)) moveFocuser(0,rightCmd);
    else if (!strcmp(leftCmd , cmdFOCUSER_OUT)) moveFocuser(1,rightCmd);
    else if (!strcmp(leftCmd , cmdSETHNAME)) changeHostName(rightCmd);
    else if (!strcmp(leftCmd , cmdSETWIFISSID)) changeWifiSSID(rightCmd);
    else if (!strcmp(leftCmd , cmdSETWIFIPREF)) changeWifiPref(rightCmd);
    else _log->log(error, String(cmd) + ": Unknown command." );
  }
  else
    _log->log(error, String(cmd) + " is not well formated command." );
}

void lfwaf_server::processInputs(){
  //check TCP clients for data
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    while (this->serverClients[i].available()) {
      char c = this->serverClients[i].read();
      if ( c != '\n')
        this->clientMsgs[i][this->clientMsgsIdx[i]++] = c;
      else
      {
        this->clientMsgs[i][this->clientMsgsIdx[i]++] = 0x0;
        parseCmd(this->clientMsgs[i]);
        this->clientMsgsIdx[i] = 0;
      }
      if (this->clientMsgsIdx[i] > 63)
        this->clientMsgsIdx[i] = 63;
    }
}

// Most important method of class: sends a message to all clients
void lfwaf_server::announce(char *message){
  int lenmsg = strlen(message);
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    if (this->serverClients[i].connected()) {
      size_t tcp_sent = this->serverClients[i].write(message, lenmsg);
      if (tcp_sent != lenmsg) {
        Serial.println("Error while sending message via Telnet" ); // : message len :%zd tcp-write:%zd\n", lenmsg, tcp_sent);
      }
    }
}
