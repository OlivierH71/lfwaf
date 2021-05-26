/*
  lfwaf_settings.cpp - Library for loading/saving lfwaf settings
  see lfwaf_settings.h
*/

#include "Arduino.h"
#include "EEPROM.h"
#include "lfwaf_settings.h"
#include "lfwaf_logger.h"
#include "lfwaf_helpers.h"

lfwaf_settings::lfwaf_settings(lfwaf_logger *logger)
{
    _log = logger;
    isvalid = load();
    if (!isvalid){
      _log->log(debug,"Setting default");
      setWifi(1,"BB8","NOTRENOUVEAUWIFIESTLEPLUSFORT");
      values.wifi_preference = wifi_pref_wifi1;
      setFilterNum(1);
      setFilterName(1,"default");
    }
}

// Set one of the Wifi ssid and pwd
void lfwaf_settings::setWifi(int n, char* ssid, char* pwd){
  UpperStr(this->values.wifi_ssid[n-1]);
  strcpy(this->values.wifi_ssid[n-1], ssid );
  strcpy(this->values.wifi_pass[n-1], pwd );
  this->save();
}

// Change the current active Filter
void lfwaf_settings::setFilterNum(byte Filter){
  this->values.FilterNum = Filter;
  this->save();
}

// Chanbe one filter name
void lfwaf_settings::setFilterName(int n, char *name){
  strcpy(this->values.FilterNames[n-1], name);
  this->save();
}

// Change all filter names (only one "save" in EEPROM for all)
void lfwaf_settings::setFilterNames(int n, char **name){
  for (int i=0; i++; i< n){
      strcpy(this->values.FilterNames[i], name[i]);
  }
  this->save();
}

/* Load Settings from EEPROM */
bool lfwaf_settings::load()
{
    _log->log(debug, "Loading settings from device EEPROM");
    EEPROM.get(0, this->values);
    bool isValid = !strncmp(this->values.key, "lfwafSet", 8);
    if (isValid)
      _log->log(info,"Settings successfuly loaded from device");
    else
      _log->log(warning,"Settings in device are invalid, new, erased or older version device");
    return isValid;
}

/* Save Settings in EEPROM */
void lfwaf_settings::save()
{
  _log->log(debug, "Saving to device EEPROM.");
  strcpy(this->values.key, "lfwafSet");
  EEPROM.put(0, this->values);
  _log->log(debug, "Settings saved in device EEPROM.");
}
