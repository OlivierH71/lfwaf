#include "DirectMotor.h"

// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     50

void DirectMotor::setParams(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPins)
{
  _pin1 = pin1; // always a PWM pin
  _pin2 = pin2; // can be a non-Pwm pin.
  _whichMode = decayMode;
  _numPwmPins = numPins;
//   _channel1 = channel*2;
//   _channel2 = _channel1+1;

//   // configure LED PWM functionalitites
//   ledcSetup(_channel1, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
//   ledcSetup(_channel2, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
//   /*ledcAttachPin(_channel1, _pin1);
//   ledcAttachPin(_channel2, _pin2); */
//   ledcAttachPin(_pin1, _channel1);
//   ledcAttachPin(_pin2, _channel2);
}

DirectMotor::DirectMotor( uint8_t pin1, uint8_t pin2, uint8_t channel) {
  setParams(pin1, pin2, channel, FAST_DECAY, PWM_2PIN);
}

DirectMotor::DirectMotor(uint8_t pin1, uint8_t pin2, uint8_t channel, DecayMode decayMode, NumOfPwmPins numPins) {
  setParams(pin1, pin2, channel, decayMode, numPins);
}

int DirectMotor::getPWM() {
  return _pwmVal;
}

void DirectMotor::stopMotor()
{
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2, LOW);
    _pwmVal = 0;
}

// Arduino like analogWrite
// value has to be between 0 and valueMax
// void DirectMotor::analogWrite(uint8_t channel, uint32_t value, uint32_t valueMax ) {
//   // calculate duty, 8191 from 2 ^ 13 - 1
//   uint32_t duty = (8191 / valueMax) * min(value, valueMax);
//   // write duty to LEDC
//   ledcWrite(channel, duty);
// }

void DirectMotor::startMotor(long pwmSpeed) {
  _pwmVal = pwmSpeed;
  if (pwmSpeed >0){
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, HIGH);
  }
  else {
      digitalWrite(_pin2, LOW);
      digitalWrite(_pin1, HIGH);
  }
  
}
