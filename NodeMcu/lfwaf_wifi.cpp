/*
  lfwaf_wifi.cpp - Library for managinf lfwaf wifi
  see lfwaf_wifi.h
*/

#include "Arduino.h"
#include "lfwaf_wifi.h"

lfwaf_wifi::lfwaf_wifi(lfwaf_logger log, lfwaf_settings settings)
{
    // record the logger instance
    _log = log;
    _settings = settings;
}

void lfwaf_wifi::scan(){
  _log.log(debug,"Starting Wifi scan");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    _log.log(info, "no wifi networks found");
  }
  else {
    _log.log(info,"Network found:");
    char buf1[100];
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      sprintf(buf1, "%d = %s (%d)", i+1, WiFi.SSID(i), WiFi.RSSI(i));
      _log.log(info,buf1);
    }
  }
  _log.log(debug,"Wifi Scan complete.")
}

bool lfwaf_wifi::connect()
{
  //
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Ensure we don't try to og to Wifi while we are connecting it
  _log.unsetWifi();
  _log.log(debug,"Connecting Wifi")
  
  // Gives 10 seconds to try
  i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    _log.log(info,".");
  }

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
    EEPROM.get(0, values);
    bool isValid = !strncmp(values.key, "lfwafSet", 8);
    return isValid;
}

void lfwaf_settings::save()
{
  strcpy("lfwafSet", values.key);
  EEPROM.put(0, values);
}
