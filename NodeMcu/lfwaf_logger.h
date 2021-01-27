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

class lfwaf_logger{
private:
  //const char *levelS[] = { "debug", "info",  "warning", "error"};
  _buffer[1024]; // most efficient way so we don't allocate/deallocate memory for message concat
  lfwaf_wifi _wifi;
public:
  bool isDebug;
  bool hasWifi = false;

  enum level { debug, info, warning, error };
  lfwaf_logger(bool withDebug);
  void log(level lvl, String msg);
}


#endif
