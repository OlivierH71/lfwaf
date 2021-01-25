// #include<ESP8266WiFi> 
/*
 
*/

# include <EEPROM.h>

EEPROM memory;

#define btnW_L_pin  D0
#define btnW_R_pin  D1
#define btnF_L_pin  D7
#define btnF_R_pin  D5

#define motW_L_pin  D2
#define motW_R_pin  D3
#define motF_L_pin  D4
#define motF_R_pin  D8

#define motorMinValue 135
#define motorMaxValue 1023

int cnvSpeed(int speed20){
  return (motorMaxValue-motorMinValue)/20 * speed20;
}


int speedW=cnvSpeed(10);
int speedF=cnvSpeed(10);

void setup() {
  //start serial connection
  Serial.begin(115200);
  delay(10);
  Serial.println("lfwaf is starting");

  Serial.println("setting pins");
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(btnW_L_pin, INPUT);
  pinMode(btnW_R_pin, INPUT);
  pinMode(btnF_L_pin, INPUT);
  pinMode(btnF_R_pin, INPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  pinMode(motW_L_pin, OUTPUT);
  Serial.println();
  //Change frequency for PWM functions
  analogWriteFreq(50);
  
}

void loop() {
  //read the pushbutton value into a variable
  if (digitalRead(btnW_L_pin) == LOW){
    analogWrite(motW_L_pin,135);
  } else {
    analogWrite(motW_L_pin,0);
  }
  if (digitalRead(btnW_R_pin) == LOW){
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(motW_R_pin,1023);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    analogWrite(motW_R_pin,0);
  }
}
