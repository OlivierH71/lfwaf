/*
  lfwaf_settings.cpp - Library for loading/saving lfwaf settings
  see lfwaf_settings.h
*/

#include "Arduino.h"
#include "lfwaf_settings.h"

lfwaf_settings::lfwaf_settings()
{
    isvalid = load();
}

bool lfwaf_settings::load()
{
    EEPROM.get(0, values);
    bool isValid = !strncmp(values.key, "lfwafSet", 8);
    return isValid;
}

void lfwaf_settings::save()
{
  strcpy("lfwafSet", values.key);
  EEPROM.put(0, values);
}
