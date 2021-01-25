/*
 *  Settings CLASS FOR LFAWF
 *  
 *  Created By Deneb-l 
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
 *  setPins((int) step, (int) enable, (int) reset)
 *  setDirection((bool) direction) [0 Forward, 1 Reverse]
 *  setSpeed((int) speed) [Min 0, Max 255]
 *  toggleDirection()
 *  run()
 *  stop()
 *  
 */ 
#include "EEPROM.h"

class lfwaf_settings{
  struct _values {
	  char key[9] = "lfwafSet" + char[0]; // + char[0]
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
	  int  focuserPos;
	  int  focuserSpeed
  }
  private:
	EEPROM memory;
	
    uint8_t _stPin, _enPin, _rstPin; // Wiring
    int _pwmSpeed = 255; // 0~255
    bool _turnDirection = 0; // 0 Forward, 1 Reverse

    void _setPins(){
      pinMode(this->_stPin, OUTPUT);
      pinMode(this->_rstPin, OUTPUT);
      pinMode(this->_enPin, OUTPUT);
      
      digitalWrite(this->_rstPin, HIGH); // Active low
      digitalWrite(this->_enPin, HIGH); // Active low
    }

    void _motorDirection(){
      unsigned int pulseModulation = (this->_turnDirection)? 2:0;
      
      digitalWrite(this->_rstPin, LOW);
      delayMicroseconds(5);
      digitalWrite(this->_rstPin, HIGH);
      
      for(int i=0;i<pulseModulation;i++){
        digitalWrite(this->_stPin, HIGH);
        delayMicroseconds(800);
        digitalWrite(this->_stPin, LOW);
        delayMicroseconds(800);
      }
    }

    void _motorSpeed(){
      analogWrite(this->_enPin, this->_pwmSpeed);
    }

    void _motorStop(){
      digitalWrite(this->_enPin, HIGH);
    }
  
  public:
	_values values;
	
	
    void setPins(uint8_t stPin, uint8_t enPin, uint8_t rstPin){
      this->_stPin = stPin;
      this->_rstPin = rstPin;
      this->_enPin = enPin;
      this->_setPins();
    }

    void setDirection(bool turnDirection){ // 0 Forward, 1 Reverse
      this->_turnDirection = turnDirection;
      this->_motorDirection();
    }
    
    void setSpeed(int pwmSpeed){ // 0~255
      this->_pwmSpeed = (255 - pwmSpeed);
      this->_motorSpeed();
    }

    void toggleDirection(){
      if (this->_turnDirection) this->_turnDirection = 0; // Forward
      else this->_turnDirection = 1; // Reverse
      this->_motorDirection();
    }

    void run(){
      this->_motorDirection();
      this->_motorSpeed();
    }

    void stop(){
      this->_motorStop();
    }
};

