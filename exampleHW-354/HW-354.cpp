#include "HW-354.h"

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     5000

void HW354::setParams(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPins)
{
  _pin1 = pin1; // always a PWM pin
  _pin2 = pin2; // can be a non-Pwm pin.
  _whichMode = decayMode;
  _numPwmPins = numPins;
  _channel1 = channel*2;
  _channel2 = _channel1+1;

  // configure LED PWM functionalitites
  ledcSetup(_channel1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcSetup(_channel2, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  /*ledcAttachPin(_channel1, _pin1);
  ledcAttachPin(_channel2, _pin2); */
  ledcAttachPin(_pin1, _channel1);
  ledcAttachPin(_pin2, _channel2);
}

HW354::HW354( uint8_t pin1, uint8_t pin2, uint8_t channel) {
  setParams(pin1, pin2, channel, FAST_DECAY, PWM_2PIN);
}

HW354::HW354(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPins) {
  setParams(pin1, pin2, channel, decayMode, numPins);
}

int HW354::getPWM() {
  return _pwmVal;
}

void HW354::stopMotor()
{
    #if defined(ARDUINO_ARCH_ESP32)
        ledcWrite(_channel1, LOW);
        ledcWrite(_channel2, LOW);
    #else
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, LOW);
    #endif
}

// Arduino like analogWrite
// value has to be between 0 and valueMax
void HW354::analogWrite(uint8_t channel, uint32_t value, uint32_t valueMax ) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  // write duty to LEDC
  ledcWrite(channel, duty);
}

void HW354::startMotor(long pwmSpeed) {
  _pwmVal = pwmSpeed;
  // if set decay mode is set as fast decay mode
  /*if (this->_whichMode == FAST_DECAY)
  {
    if (pwmSpeed >= 0)
    {  //if Speed > 0 then forward fast decay
      if(_numPwmPins == PWM_1PIN)
        digitalWrite(_pin2, LOW);
	    else
	      analogWrite(_channel2, 1);
        analogWrite(_channel1, pwmSpeed);
    }
    else
      if (this->_numPwmPins == PWM_2PIN)
      { // else reverse fast decay
        pwmSpeed *= -1;
  	     analogWrite(_channel1, 1);
        analogWrite(_channel2, pwmSpeed);
      }
      else if (this->_numPwmPins == PWM_1PIN)
      { // reverse slow decay
      pwmSpeed *= -1;
      digitalWrite(_pin2, HIGH);
      analogWrite(_channel1, pwmSpeed);
    }
  }
   // if decay mode is set as slow decay mode
  else {
    if (pwmSpeed >= 0) {                        // forward slow decay
      if(_numPwmPins == PWM_1PIN)
        digitalWrite(_pin1, HIGH);
      else
	      analogWrite(_channel1, LOW);
      analogWrite(_channel2, pwmSpeed);
    }
    else if (this->_numPwmPins == PWM_2PIN) { // reverse slow decay
      pwmSpeed *= -1;
	    analogWrite(_channel2, 0);
      analogWrite(_channel1, pwmSpeed);
    }
    else if (this->_numPwmPins == PWM_1PIN) { // reverse fast decay
      pwmSpeed *= -1;
      digitalWrite(_pin1, LOW);
      analogWrite(_channel2, pwmSpeed);
    }
  }*/
  if (pwmSpeed >0){
      analogWrite(_channel2, 0,255);
      analogWrite(_channel1, pwmSpeed, 255);
  }
  else {
      analogWrite(_channel1, 0, 255);
      analogWrite(_channel2, -pwmSpeed, 255);  
  }
  
}
