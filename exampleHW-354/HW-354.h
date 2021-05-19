//  This library is used to pilot a HW354 DC moter driver with an ESP32
#ifndef HW354_h
#define HW354_h

#include "Arduino.h"

typedef enum
{
  FAST_DECAY = 0,  // set non-PWM pin low
  SLOW_DECAY = 1    // set non-PWM pin high
} DecayMode;

typedef enum
{
  PWM_1PIN  = 1,
  PWM_2PIN  = 2
} NumOfPwmPins;

class HW354 {
  public:
    HW354(uint8_t pin1, uint8_t pin2, uint8_t channel); // default fast decay, 2 pwm pins
    HW354(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPWM);
    void  startMotor(long pwmVal); //
    void  setResolution(unsigned int resolution);
    int   getPWM();
    void  stopMotor();
	  void  analogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255);
  private:
    void  setParams(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPins);
    uint8_t _pin1;
    uint8_t _pin2;
    uint8_t _channel1;
    uint8_t _channel2;
    int _pwmVal;
    DecayMode _whichMode;
    NumOfPwmPins _numPwmPins;
};

#endif
