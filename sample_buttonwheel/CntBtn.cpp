#include "CntBtn.h"


/*************************************************************
                          Constructor
*************************************************************/
CntBtn::CntBtn( uint8_t pin) {

  PIN = pin;
  attachInterruptArg(PIN, isr, &btns[i], CHANGE);
}

/*************************************************************
                          Methods
*************************************************************/
void IRAM_ATTR isr(void* arg) {
    Button* s = static_cast<Button*>(arg);
    if ((millis() - s->lastDown) > 300)
    {
      s->lastDown = millis();
      s->pressed = !s-> pressed; // true; //!digitalRead(s->PIN); //true;
      if (s->pressed)
        s->numberKeyPresses += 1; // !digitalRead(s->PIN);
    }
}
