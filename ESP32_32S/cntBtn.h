// This library is used to control a Button trigger (pressed/released)
// on a esp32, even if the button has a lot of noise and when it is
// not possible to add a condensator in the circuit
// You need to create an instance of this class in the "setup" or "loop" part
// of your project. Trying to create a static instance in .ino declaration
// will fail during compilation. After the button instalce is created, assign
// a method to callback method "OnPressed" and/or "OnReleased" :
/* void messageButton(cntBtn *btn){
          Serial.printf("Button pin %d has been pressed %u times\n",btn->PIN, btn->numberKeyPresses);
}
...
void setup() {
    btn = new cntBtn(27);
    btn->setOnPressed(messageButton);
}
*/

#ifndef cntBtn_h
#define cntBtn_h

#include "Arduino.h"

class cntBtn {
  typedef void (*callback_t)(cntBtn *btn, void *parent);
  public:
    cntBtn(uint8_t pin);
    ~cntBtn();
    uint8_t PIN;
    uint32_t  numberKeyPresses = 0;
    uint32_t  lastDown = 0;
    bool      pressed = false;
    void      setOnPressed(callback_t _callback) {onPressed = _callback;}
    void      setOnReleased(callback_t _callback) {onReleased = _callback;}
    /* Methods */
    callback_t onPressed = NULL;
    callback_t onReleased= NULL;
  private:

};

#endif
