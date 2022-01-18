/*
 *  Settings CLASS FOR LFAWF
 *
 *  Created By Deneb-l (olivier.hennebelle@gmail.com)
 *
 *  ¿How to use?
 *
 *  1 - Declare Settings type var after setup() [lfawf_settings* settings]
 *  2 - Instantiate new Settings in var created before [settings = new lfawf_settings()]
 * 		--> new var will load settings from EEPROM
 *  3 - Use predefined public methods [lfwaf_settings->method()]
 *
 *  Public Methods
 *
 *
 */

#ifndef lfwaf_settings_h
#define lfwaf_settings_h

#include "EEPROM.h"
// #include "lfwaf_logger.h"

enum wifi_preference { wifi_pref_stronger, wifi_pref_wifi1, wifi_pref_wifi2};

class lfwaf_logger;
struct Svalues {
	  char key[9]; // = "lfwafSet" + char[0]
    char hostname[33];
	  // Wifi settings
	  char wifi_ssid[2][33];
	  char wifi_pass[2][33];
	  byte wifi_preference;	// 0: takes the one with the best signal, 1: wifi1, then wifi2, 2: wifi2 then wifi1
	  // FilterWheel Settings
    char FilterNames[10][33];
	  byte FilterNum;
	  byte fwSpeed;
	  // focuser Settings
	  int  focuserPos;
    int  maxPos;
	  byte  focuserSpeed; // From 1 to 20...
  };
class lfwaf_settings{
  
  private:
    EEPROMClass *EPSET;//("lfwaf_set", sizeof(Svalues));
    lfwaf_logger *_log;
    void setWifi(int n, char* ssid, char* pwd);
    void setFilterNum(byte Filter);
    void setFilterName(int n, char *name);
    void setFilterNames(int n, char **name);
    void setHostName(char *hname);
  public:
    bool isvalid;
	  Svalues values;
    lfwaf_settings(lfwaf_logger *logger);
    bool load();
    void save();
};

#endif
