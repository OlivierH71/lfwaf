#include <Arduino.h>

struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    uint32_t lastDown;
    bool pressed;
};

Button button1 = {14, 0, false};
//Button button2 = {18, 0, false};

void IRAM_ATTR isr(void* arg) {
    Button* s = static_cast<Button*>(arg);
    if ((millis() - s->lastDown) > 500)
    {
      s->numberKeyPresses += 1;
      s->lastDown = millis();
      s->pressed = true;
    }
}

void IRAM_ATTR isr() {
//    button2.numberKeyPresses += 1;
//    button2.pressed = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(button1.PIN, INPUT_PULLUP);
    digitalWrite(button1.PIN, HIGH); 
    attachInterruptArg(button1.PIN, isr, &button1, FALLING);
    // pinMode(button2.PIN, INPUT_PULLUP);
    // attachInterrupt(button2.PIN, isr, FALLING);
}

void loop() {
    if (button1.pressed) {
        Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
        button1.pressed = false;
    }
    /*if (button2.pressed) {
        Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
        button2.pressed = false;
    }*/
    //delay(1000);
    //Serial.print(digitalRead(char(button1.PIN)));
    static uint32_t lastMillis = 0;
    if (millis() - lastMillis > 50000) {
      lastMillis = millis();
      detachInterrupt(button1.PIN);
    }
}
