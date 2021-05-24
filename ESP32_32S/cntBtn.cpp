#include "cntBtn.h"
#include "Arduino.h"


/*************************************************************
                          Methods
*************************************************************/
static void IRAM_ATTR isr(void* arg) {
    cntBtn* s = static_cast<cntBtn*>(arg);
    if ((millis() - s->lastDown) > 100)
    {
      s->lastDown = millis();
      s->pressed = !s-> pressed; // true; //!digitalRead(s->PIN); //true;
      if (s->pressed){
        s->numberKeyPresses += 1; // !digitalRead(s->PIN);
        if (s->onPressed != NULL)
          s->onPressed(s);
      }
      else
        if (s->onReleased != NULL)
          s->onReleased(s);
    }
}

static void attach(uint8_t PIN, cntBtn *btn){
    pinMode(PIN, INPUT_PULLUP);
    Serial.printf("Attaching CHANGE to pin %d\n", btn->PIN);
    attachInterruptArg(PIN, isr, btn, CHANGE);
    btn->pressed = !digitalRead(PIN);
}

/*************************************************************
                          Constructor
*************************************************************/
cntBtn::cntBtn(uint8_t pin) {
  PIN = pin;
  attach(pin, this);
}

cntBtn::~cntBtn(){
  detachInterrupt(this->PIN);
}
