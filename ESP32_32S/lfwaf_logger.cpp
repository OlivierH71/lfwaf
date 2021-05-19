#include <LiquidCrystal.h>

/*
  lfwaf_logger.cpp - Library for managinf lfwaf wifi
  see lfwaf_wifi.h
*/

#include "Arduino.h"
#include "lfwaf_logger.h"
#include <WiFi.h>


// Class constructor: setup serial connection for logging

lfwaf_logger::lfwaf_logger(bool withDebug){
    isDebug = withDebug;
    // record the logger instance
    Serial.begin(115200);
    Serial.println("    ");
    this->log(info,"lwaf_logger started.");
}

// most important function of this class: log a message
void lfwaf_logger::log(logLevel lvl, String msg){
  if (isDebug || lvl != debug){
    char buf1[20];
    // DateTime now = rtc.now();
    unsigned long myTime = millis();
    sprintf(buf1, "%f",  myTime / 1000);
    sprintf(_buffer,"%d:%s:%s\n", lvl, buf1, msg.c_str());
    if (hasWifi){
      _server->announce(_buffer);
    }
  }
}

// set the wifi stream
void lfwaf_logger::setWifi(lfwaf_server *_newServer){
    _server = _newServer;
    hasWifi = true;
}

// stop logging to wifi
void lfwaf_logger::unsetWifi(){
  hasWifi = false;
}
