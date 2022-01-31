/*
 *  Telnet Server CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
*/
#include <WiFiClient.h>
#include <Ticker.h>
#include "lfwaf_logger.h"
#include "lfwaf_settings.h"
#include "lfwaf_helpers.h"
#include "lfwaf_server.h"
#include "lfwaf_engine.h"
#include "lfwaf_protocol.h"

lfwaf_server *ZeServer; 

lfwaf_server::lfwaf_server(lfwaf_logger *log, lfwaf_settings *settings, lfwaf_engine *engine) {
  _log = log;
  _settings = settings;
  _engine = engine;
  //start server
  //WiFiServer server(23);
  _log->log(info,"Starting Wifi Server");
  server.begin(23);
  // IMPORTANT: Avoid Nagle, ie, wait for enough data to transmit packet. We need immediate communication
  server.setNoDelay(true);
  _log->log(info,"Ready! Use INDI or telnet (TCP23) to connect");
  _log->setWifi(this);
}

void lfwaf_server::acknowledge(){
  _log->log(info, "Ack-lfwaf");
}

// Check for new client (for main loop)
void lfwaf_server::checkForClients(){
  if (server.hasClient()) {
    _log->log(debug, "Incoming client");
    //find free/disconnected client
    int i;
    for (i = 0; i < MAX_SRV_CLIENTS; i++)
      if (!serverClients[i]) {
        serverClients[i] = server.available();
        _log->log(info, "Ack-lfwaf"+String(i+1));
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

// Move the filter wheel to filter position "params"
void lfwaf_server::changeFilterWNum(char *params){
    _log->log(debug,"changeFilterWNum");
  if (params){
    int fNum;
    sscanf(params, "%d", &fNum );
    _engine->filterWheelMoveTo(fNum);
    filterWMoving = true;
  }
  else
    _log->log(error,"Missing filter Num param");
}

// Record in memory the Filter name #
void lfwaf_server::setFilterName(char *params){
    char filtName[100];
    int num;
    _log->log(debug,"setFilterName");
    sscanf(params ,"%d%[^|]|%s", &num, filtName);
    strcpy(_settings->values.FilterNames[num], filtName);
    _settings->save();
    _log->log(info,"OK");
}

void lfwaf_server::getFilterName(char *params){
    _log->log(debug,"getFilterName");
    int num;
    sscanf(params ,"%d", &num);
    strcpy(params, _settings->values.FilterNames[num]);
    _log->log(info,"OK");
}

void lfwaf_server::setFilterWSpeed(char *params){
    _log->log(debug,"setFilterWSpeed");
    int num;
    sscanf(params ,"%d", &num);
    _settings->values.fwSpeed = num;
    _settings->save();
    _log->log(info,"OK");
}

void lfwaf_server::setFocuserSpeed(char *params){
    _log->log(debug,"setFocuserSpeed");
    int num;
    sscanf(params ,"%d", &num);
    _settings->values.focuserSpeed = num;
    _settings->save();
    _log->log(info,"OK");
}

void lfwaf_server::getFocuserSpeed(char *params){
    _log->log(debug,"getFocuserSpeed");
    int num;
    sprintf(params,"%d", _settings->values.focuserSpeed);
    _log->log(info, params);
}

void lfwaf_server::focuserTickerStop(){
    ZeServer->focuserMoveTicker.detach();
    ZeServer->_engine->focuserStop();
    ZeServer->focuserMoving = false;
    ZeServer->_log->log(info, "OK");
}

bool lfwaf_server::isFocuserMoving(){
    _log->log(info, focuserMoving ? "YES" : "NO");
}

// move Focuser up and down, params contains a string of how-many ticks
void lfwaf_server::moveFocuser(bool up, char *params){
  _log->log(debug,"moveFocuser");
  if (params){
    int steps;
    sscanf(params, "%d", &steps );
    _engine->focuserMove(up);
    focuserMoving = true;
    // We must use a static reference to the function,
    ZeServer = this; 
    ZeServer->focuserMoveTicker.attach_ms (5*steps,ZeServer->focuserTickerStop);
    //moveTicker.once_ms(5*steps, TickerStop, this);
    // delay(5*steps);
    //_engine->focuserStop();
  }
  else
    _log->log(error,"Missing steps param");
}

void lfwaf_server::stopFocuser(){
    _engine->focuserStop();
}


void lfwaf_server::filterWTickerStop(){
    ZeServer->filterWMoveTicker.detach();
    ZeServer->_engine->filterWheelStop();
    ZeServer->filterWMoving = false;
}

bool lfwaf_server::isfilterWMoving(){
    _log->log(info, filterWMoving ? "YES" : "NO");
}



// Set Wifi hostname
void lfwaf_server::setHostName(char *params){
    _log->log(debug,"setHostName");
    sscanf(params ,"%s", _settings->values.hostname);
    strcpy(_settings->values.hostname, params);
    _settings->save();
    _log->log(info,"OK");
}

// answers what is hostname
void lfwaf_server::getHostName(char *params){
    _log->log(debug,"getHostName");
    sprintf(params,"%s", params, _settings->values.hostname);
    _log->log(info, params);
}

// Change wifi SSIDs in memory
void lfwaf_server::setWifiSSID(char *params){
    _log->log(debug,"changeWifiSSID");
    sscanf(params, "%[^|]|%[^|]|%[^|]|%[^|]", _settings->values.wifi_ssid[0],
                                  _settings->values.wifi_pass[0],
                                  _settings->values.wifi_ssid[1],
                                  _settings->values.wifi_pass[1]);
    _settings->save();
    _log->log(info,"OK");
}

// returns to client the wifi SSID recorded
void lfwaf_server::getWifiSSID(char *params){
    _log->log(debug,"getWifiSSID");
    sprintf(params, "%s|%s|%s|%s#", _settings->values.wifi_ssid[0],
                                  _settings->values.wifi_pass[0],
                                  _settings->values.wifi_ssid[1],
                                  _settings->values.wifi_pass[1]);
    _log->log(info,params);
    //_log->log(info,"OK#");
}

// Change the wifi preference
void lfwaf_server::setWifiPref(char *params){
    _log->log(debug,"changeWifiPref");
    sscanf(params, "%d", &_settings->values.wifi_preference);
    _settings->save();
    _log->log(info,"OK");
}

// respond the current wifi prefs
void lfwaf_server::getWifiPref(char *params){
    _log->log(debug,"getWifiPref");
    sprintf(params, "%d#", &_settings->values.wifi_preference);
    _log->log(info,params);
}

// Parses the command sent by telnet Wifi or serial
void lfwaf_server::parseCmd(char *cmd){
  // Warning, if this is the first acknowledge command via Telnet, DO NOT sent anything BUT
  // Ack answer
  if (!strncmp(cmd,cmdACKNOWLEDGE, strlen(cmdACKNOWLEDGE)-2))
    acknowledge();
  else
  {
    _log->log(debug, "Parsing " + String(cmd));
    char leftCmd[64];
    char rightCmd[257];
    sscanf(cmd, "%s %s",leftCmd, rightCmd);
    if (leftCmd){
      UpperStr(leftCmd);
      if (!strcmp(leftCmd,cmdGOTOFILTNUM))        changeFilterWNum(rightCmd);
      else if (!strcmp(leftCmd , cmdSETFILTNAME)) setFilterName(rightCmd);
      else if (!strcmp(leftCmd , cmdSETFWSPEED))  setFilterWSpeed(rightCmd);
      else if (!strcmp(leftCmd , cmdSETFOSPEED))  setFocuserSpeed(rightCmd);
      else if (!strcmp(leftCmd , cmdGETFOSPEED))  getFocuserSpeed(rightCmd);
      else if (!strcmp(leftCmd , cmdFOCUSER_IN))  moveFocuser(false,rightCmd);
      else if (!strcmp(leftCmd , cmdFOCUSER_OUT)) moveFocuser(true,rightCmd);
      else if (!strcmp(leftCmd , cmdISFOCUSER_M)) isFocuserMoving();
      else if (!strcmp(leftCmd , cmdSTOPFOCUSER)) stopFocuser();
      else if (!strcmp(leftCmd , cmdSETHOSTNAME)) setHostName(rightCmd);
      else if (!strcmp(leftCmd , cmdGETHOSTNAME)) getHostName(rightCmd);
      else if (!strcmp(leftCmd , cmdSETWIFISSID)) setWifiSSID(rightCmd);
      else if (!strcmp(leftCmd , cmdGETWIFISSID)) getWifiSSID(rightCmd);
      else if (!strcmp(leftCmd , cmdSETWIFIPREF)) setWifiPref(rightCmd);
      else if (!strcmp(leftCmd , cmdGETWIFIPREF)) getWifiPref(rightCmd);
      else _log->log(error, String(cmd) + ": Unknown command." );
    }
    else
      _log->log(error, String(cmd) + " is not well formated command." );
  }
}

void lfwaf_server::processInputs(){
  //check TCP clients for data
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    while (this->serverClients[i].available()) {
      Serial.write(".");
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
    // check serial for data
    while(Serial.available()){
      char c = Serial.read();
      if ( c != '\n')
        this->serialMsg[this->serialMsgIdx++] = c;
      else
      {
        this->serialMsg[this->serialMsgIdx++] = 0x0;
        parseCmd(this->serialMsg);
        this->serialMsgIdx = 0;
      }    
      if (this->serialMsgIdx > 63)
        this->serialMsgIdx = 63;  
    }
}

// Most important method of class: sends a message to all clients
void lfwaf_server::announce(char *message) {
  int lenmsg = strlen(message);
  for (int i = 0; i < MAX_SRV_CLIENTS; i++)
    if (this->serverClients[i].connected()) {
      size_t tcp_sent = this->serverClients[i].write(message, lenmsg);
      if (tcp_sent != lenmsg) {
        Serial.println("Error while sending message via Telnet" ); // : message len :%zd tcp-write:%zd\n", lenmsg, tcp_sent);
      }
    }
}
