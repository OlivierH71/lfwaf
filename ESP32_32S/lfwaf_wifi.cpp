/*
  lfwaf_wifi.cpp - Library for managinf lfwaf wifi
  see lfwaf_wifi.h
*/

#include "Arduino.h"
#include <WiFi.h>
#include "lfwaf_wifi.h"
#include "lfwaf_logger.h"

lfwaf_wifi::lfwaf_wifi(lfwaf_logger *log, lfwaf_settings *settings)
{
    // record the logger instance
    _log = log;
    _settings = settings;
}

int lfwaf_wifi::scan(){
  _log->log(debug,"Starting Wifi scan");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    _log->log(info, "no wifi networks found");
  }
  else {
    _log->log(info,"Network found:");
    char buf1[100];
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      sprintf(buf1, "%d = %s (%d)", i+1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      _log->log(info,buf1);
    }
  }
  _log->log(debug,"Wifi Scan complete.");
  return (n);
}

byte lfwaf_wifi::connect(){
  //
  WiFi.mode(WIFI_STA);
  // Ensure we don't try to og to Wifi while we are connecting it
  _log->unsetWifi();
  _log->log(debug,"Connecting Wifi... possible networks");
  _log->log(debug,_settings->values.wifi_ssid[0]);
  _log->log(debug,_settings->values.wifi_ssid[1]);

  // DEPENDING ON MODE: Either we scan and, if both available, takes the best values
  // Otherwise, start with the prefered and, if it fails, try the second one
  int n = this->scan();
  int RSSI[2];

  RSSI[0] = RSSI[1] = -1000;
  for (int i = 0; i < n; ++i) {
    char SSID[32];
    strtoupper(SSID, WiFi.SSID(i).c_str());
    if (!strcmp(SSID, _settings->values.wifi_ssid[0])){
      RSSI[0] = WiFi.RSSI(0);
    }
    else if (!strcmp(SSID, _settings->values.wifi_ssid[1])){
      RSSI[1] = WiFi.RSSI(1);
    }
  }
  int ssidNum = -1;
  switch (_settings->values.wifi_preference) {
    case wifi_pref_stronger: {
        if (RSSI[0] > RSSI[1])
          ssidNum = 0;
        else
          ssidNum =1;
    }
    break;
    case wifi_pref_wifi1:{
      if (RSSI[0] > -1000)
        ssidNum = 0;
      else if(RSSI[1] > -1000)
        ssidNum = 1;
      break;
    }
    case wifi_pref_wifi2:{
      if (RSSI[1] > -1000)
        ssidNum = 1;
      else if(RSSI[0] > -1000)
        ssidNum = 0;
      break;
    }
  }
  if ( ssidNum > -1){
    /*String ssid = String(_settings->values.wifi_ssid[ssidNum]);
    String passwd = String(_settings->values.wifi_pass[ssidNum]); */
    const char *ssid = _settings->values.wifi_ssid[ssidNum];
    const char *passwd = _settings->values.wifi_pass[ssidNum];

    _log->log(debug,"Selected wifi SSID for connection:" + String(ssid));
    WiFi.begin(ssid, passwd);
    // Gives 10 seconds to try
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && i <20) {
      delay(500);
      _log->log(debug,".");
      i++;
    }
    if (WiFi.status() == WL_CONNECTED){
      _log->log(info,"WiFi connected");
      _log->log(info,"IP address: " + WiFi.localIP().toString());
    }
    else
      _log->log(error,"Wifi ''" + String(ssid) + "' was seen but connection failed.");
  }
  else
    _log->log(error,"No wifi candidate could be seen in area (are you too far?)");
  }
