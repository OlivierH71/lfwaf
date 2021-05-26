#include "cntBtn.h"
#include "Arduino.h"


/*************************************************************
                          Methods
*************************************************************/
static void IRAM_ATTR isr(void* btn) {
    cntBtn* s = static_cast<cntBtn*>(btn);
    if ((millis() - s->lastDown) > 100)
    {
      s->lastDown = millis();
      s->pressed = !s-> pressed; // true; //!digitalRead(s->PIN); //true;
      if (s->pressed){
        s->numberKeyPresses += 1; // !digitalRead(s->PIN);
        if (s->onPressed != NULL)
          s->onPressed(s,s->_parent);
      }
      else
        if (s->onReleased != NULL)
          s->onReleased(s,s->_parent);
    }
}

static void attach(uint8_t PIN, cntBtn *btn, void* parent){
    pinMode(PIN, INPUT_PULLUP);
    Serial.printf("Attaching CHANGE to pin %d\n", btn->PIN);
    attachInterruptArg(PIN, isr, btn, CHANGE);
    btn->pressed = !digitalRead(PIN);
}

/*************************************************************
                          Constructor
*************************************************************/
cntBtn::cntBtn(uint8_t pin, void *parent) {
  PIN = pin;
  _parent = parent;
  attach(pin, this, _parent);
}

cntBtn::~cntBtn(){
  detachInterrupt(this->PIN);
}
