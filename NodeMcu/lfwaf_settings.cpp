/*
  lfwaf_settings.cpp - Library for loading/saving lfwaf settings
  see lfwaf_settings.h
*/

#include "Arduino.h"
#include "lfwaf_settings.h"

lfwaf_settings::lfwaf_settings()
{
    memory = new(EEPROM);
    isvalid = load();
}

bool lfwaf_settings::load()
{
    values = memory.get(0);
    isValid = !strncmp(values, "lfwafSet" + char[0], 9);
    return isValid;
}

void lfwaf_settings::save()
{
  setmem(values.key, "lfwafSet" + char[0]);
  memory.put(0, values);
}