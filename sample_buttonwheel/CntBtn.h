//  This library is used to pilot a HW354 DC moter driver with an ESP32
#ifndef cntBtn_h
#define cntBtn_h

#include "Arduino.h"

class cntBtn {
  public:
    cntBtn(uint8_t pin);
  private:
    const uint8_t PIN;
    uint32_t  numberKeyPresses;
    uint32_t  lastDown;
    bool      pressed;
    /* Methods */
    void      IRAM_ATTR isr(void* arg);
};

#endif
