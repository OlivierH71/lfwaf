#include <Arduino.h>

struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    uint32_t lastDown;
    bool pressed;
};

const int nbBtns = 6;
Button button14 = {14, 0, false};
Button button27 = {27, 0, false};
Button button26 = {26, 0, false};
Button button25 = {25, 0, false};
Button button32 = {32, 0, false};
Button button33 = {33, 0, false};

Button btns[nbBtns] = {button14, button27, button26, button25, button32, button33}; 

//Button button2 = {18, 0, false};



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

void IRAM_ATTR isr() {
//    button2.numberKeyPresses += 1;
//    button2.pressed = true;
}

void setup() {
    Serial.begin(115200);
    for (int i=0; i< nbBtns; i++) {
      pinMode(btns[i].PIN, INPUT_PULLUP);
      attachInterruptArg(btns[i].PIN, isr, &btns[i], CHANGE);
    }
    // pinMode(button14.PIN, INPUT_PULLUP);
    // digitalWrite(button1.PIN, HIGH); 
    // attachInterruptArg(button14.PIN, isr, &button14, FALLING);
    // pinMode(button2.PIN, INPUT_PULLUP);
    // attachInterrupt(button2.PIN, isr, FALLING);
}

void loop() {
    for (int i=0; i< nbBtns; i++) {
      if (btns[i].pressed) {
          Serial.printf("Button pin %d has been pressed %u times\n",btns[i].PIN, btns[i].numberKeyPresses);
          // btns[i].pressed = false;
      }
    }
  
    /*if (button14.pressed) {
        Serial.printf("Button 14 has been pressed %u times\n", button14.numberKeyPresses);
        button14.pressed = false;
    }*/
    /*if (button2.pressed) {
        Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
        button2.pressed = false;
    }*/
    //delay(1000);
    //Serial.print(digitalRead(char(button1.PIN)));
    static uint32_t lastMillis = 0;
    if (millis() - lastMillis > 2000000) {
      lastMillis = millis();
      detachInterrupt(button14.PIN);
    }
}
