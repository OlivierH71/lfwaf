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

#include <EEPROM.h>

class lfwaf_settings{
  struct _values {
	  char key[9]; // = "lfwafSet" + char[0]
	  // Wifi settings
	  char wifi1_ssid[33];
	  char wifi1_pass[33];
	  char wifi2_ssid[33];
	  char wifi3_pass[33];
	  byte wifi_preference;	// 0: takes the one with the best signal, 1: wifi1, then wifi2, 2: wifi2 then wifi1
	  // FilterWheel Settings
	  byte currentFilter;
	  byte fwSpeed;
	  // focuser Settings
	  byte  focuserPos;
	  int  focuserSpeed;
  };
  private:

  public:
    bool isvalid;
	  _values values;
    lfwaf_settings();
    bool load();
    void save();
};

#endif
