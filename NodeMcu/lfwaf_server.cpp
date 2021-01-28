/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/

#include "lfwaf_server.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

lfwaf_server::lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings){
  _log = log;
  _settings = settings;
  //start server
  server.begin();
  // IMPORTANT: Avoid Nagle, ie, wait for enough data to transmit packet. We need immediate communication
  server.setNoDelay(true);
  _log->log(info,"Ready! Use 'telnet' to connect");
  _log->setWifi();
}

void lfwaf_server::checkForClients(){
  if (server.hasClient()) {
    //find free/disconnected client
    int i;
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
      if (!serverClients[i]) {
        serverClients[i] = server.available();
        _log->log(info, String("New client #"+i).c_str());
        break;
      }

    //no free/disconnected spot so reject
    if (i == MAX_SRV_CLIENTS) {
      server.available().println("busy");
      _log->log(debug,"server is busy with %d active connections\n", i);
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

void changeFilterWNum(String params){
    _log->log(debug,"changeFilterWNum")
    String parts = params.split(':');
}

void changeFilterName(String params){
    _log->log(debug,"changeFilterName")
    String parts = params.split(':');
}

void changeFilterWSpeed(String params){
    _log->log(debug,"changeFilterWSpeed")
    String parts = params.split(':');
}

void moveFocuser(byte dir, String params){
    _log->log(debug,"moveFocuser")
    String parts = params.split(':');
}

void changeHostName(String params){
    _log->log(debug,"changeHostName")
    String parts = params.split(':');
}

void changeWifiSSID(String params){
    _log->log(debug,"changeWifiSSID")
    String parts = params.split(':');
}

void changeWifiPref(String params){
    _log->log(debug,"changeWifiPref")
    String parts = params.split(':');
}

void lfwaf_server::parseCmd(char *cmd){
  _log->log(debug, "Parsing " + String(cmd));
  String parts[] = String(cmd).split('=');
  if (parts.lenght() < 2){
    parts[0].toUpperCase();
    if (parts[0] == cmdSETFWNUM) changeFilterWNum(parts[1]);
    else if (parts[0] == cmdSETFWNAME) changeFilterName(parts[1]);
    else if (parts[0] == cmdSETFWSPEED) changeFilterWSpeed(parts[1]);
    else if (parts[0] == cmdFOCUSER_IN) moveFocuser(0,parts[1]);
    else if (parts[0] == cmdFOCUSER_OUT) moveFocuser(1,parts[1]);
    else if (parts[0] == cmdSETHNAME) changeHostName(parts[1]);
    else if (parts[0] == cmdSETWIFISSID) changeWifiSSID(parts[1]);
    else if (parts[0] == cmdSETWIFIPREF) changeWifiPref(parts[1]);
  }
  else
    _log.log(error, String(cmd) + " is not well formated command." );
}

void lfwaf_server::processInputs(){
  //check TCP clients for data
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    while (serverClients[i].available()) {
      char c = this.serverClients[i].read();
      if ( c != '\n')
        this.clientMsgs[i][this.clientMsgsIdx[i]++] = c;
      else
      {
        this.clientMsgs[i][this.clientMsgsIdx[i]++] = 0x0;
        parseCmd(this.clientMsgs[i]);
        this.clientMsgsIdx[i] = 0;
      }
      if (this.clientMsgsIdx[i] > 63)
        this.clientMsgsIdx[i] = 63;
    }
}

void lfwaf_server::announce(char *message){

}

void loop() {
// determine maximum output size "fair TCP use"
// client.availableForWrite() returns 0 when !client.connected()
size_t maxToTcp = 0;
for (int i = 0; i < MAX_SRV_CLIENTS; i++)
  if (serverClients[i]) {
    size_t afw = serverClients[i].availableForWrite();
    if (afw) {
      if (!maxToTcp) {
        maxToTcp = afw;
      } else {
        maxToTcp = std::min(maxToTcp, afw);
      }
    } else {
      // warn but ignore congested clients
      logger->println("one client is congested");
    }
  }

//check UART for data
size_t len = std::min((size_t)Serial.available(), maxToTcp);
len = std::min(len, (size_t)STACK_PROTECTOR);
if (len) {
  uint8_t sbuf[len];
  size_t serial_got = Serial.readBytes(sbuf, len);
  // push UART data to all connected telnet clients
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    // if client.availableForWrite() was 0 (congested)
    // and increased since then,
    // ensure write space is sufficient:
    if (serverClients[i].availableForWrite() >= serial_got) {
      size_t tcp_sent = serverClients[i].write(sbuf, serial_got);
      if (tcp_sent != len) {
        logger->printf("len mismatch: available:%zd serial-read:%zd tcp-write:%zd\n", len, serial_got, tcp_sent);
      }
    }
}
}
