/*
 *  Wifi CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
 */

#ifndef lfwaf_wifi_h
#define lfwaf_wifi_h

#include "lfwaf_settings.h"
#include "lfwaf_logger.h"
#include "lfwaf_helpers.h"

class lfwaf_wifi {
private:
  lfwaf_logger *_log;
  lfwaf_settings *_settings;
public:

  lfwaf_wifi(lfwaf_logger *log, lfwaf_settings *settings);
  bool connected;
  String activeSSID;
  int  scan();
  byte connect();
  void recheck();
  void say(char* message);
  void disconnect();
};

#endif
