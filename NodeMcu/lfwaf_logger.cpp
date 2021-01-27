#include <LiquidCrystal.h>

/*
  lfwaf_wifi.cpp - Library for managinf lfwaf wifi
  see lfwaf_wifi.h
*/

#include "Arduino.h"
#include "lfwaf_logger.h"
#include "lfwaf_wifi.h"
#include <ESP8266WiFi.h>

lfwaf_logger::lfwaf_logger(bool withDebug){
    isDebug = withDebug;
    // record the logger instance
    Serial.begin(115200);
    Serial.println("    ");
    this->log(info,"lwaf_logger started.");
}

void lfwaf_logger::log(logLevel lvl, String msg){
  if (isDebug || lvl != debug){
    char buf1[20];
    // DateTime now = rtc.now();
    unsigned long myTime = millis();
    sprintf(buf1, "%f",  myTime / 1000);
    sprintf(_buffer,"%d:%s:%s\n", lvl, buf1, msg.c_str());
    if (hasWifi){
      // _wifiClient.say(_buffer);
    }
  }
}

void lfwaf_logger::setWifi(lfwaf_wifi *_newWifi){
    _wifi = _newWifi;
    hasWifi = true;
}

void lfwaf_logger::unsetWifi(){
  hasWifi = false;
}
