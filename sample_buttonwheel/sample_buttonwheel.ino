#include <Arduino.h>
#include "CntBtn.h"

const int nbBtns = 2;
/*cntBtn button14(14);
cntBtn button27(27);
*/

cntBtn *btns[nbBtns]; // = {button14, button27};

void messageButton(cntBtn *btn){
          Serial.printf("Button pin %d has been pressed %u times\n",btn->PIN, btn->numberKeyPresses);
}

void setup() {
    Serial.begin(115200);
    btns[0] = new cntBtn(5);
    btns[1] = new cntBtn(18);
    for (int i=0; i< nbBtns; i++) {
      btns[i]->setOnReleased(messageButton);
    }
}

void loop() {
    /*for (int i=0; i< nbBtns; i++) {
      if (btns[i]->pressed) {
          Serial.printf("Button pin %d has been pressed %u times\n",btns[i]->PIN, btns[i]->numberKeyPresses);
          btns[i]->pressed = false;
      }
    }*/

  

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
      detachInterrupt(btns[0]->PIN);
    }
}
