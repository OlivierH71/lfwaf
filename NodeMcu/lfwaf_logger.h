/*
 *  Logger CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
 *
 */

#ifndef lfwaf_logger_h
#define lfwaf_logger_h

#include "lfwaf_logger.h"
#include "lfwaf_wifi.h"

enum logLevel { debug, info, warning, error };

class lfwaf_wifi;
class lfwaf_logger{
private:
  //const char *levelS[] = { "debug", "info",  "warning", "error"};
  char _buffer[1024]; // having a static buffer is the most efficient way so we don't allocate/deallocate memory for message concat
  lfwaf_wifi *_wifi;
public:
  bool isDebug;
  bool hasWifi = false;

  lfwaf_logger(bool withDebug);
  void log(logLevel lvl, String msg);
  void setWifi(lfwaf_wifi *_newWifi);
  void unsetWifi();
};


#endif
