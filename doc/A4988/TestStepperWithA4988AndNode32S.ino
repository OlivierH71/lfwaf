/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin PA0
#define stepPin PA1
#define stepsPerRevolution 200
#define speed_low 5000
#define speed_med 1000
#define speed_fast 700


void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void turn(int nbt, int dir, int mspeed){
  digitalWrite(dirPin, dir);  
  // Spin the stepper motor 1 revolution 
  for (int i = 0; i < stepsPerRevolution * nbt; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mspeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(mspeed);
  }
  
}

void loop() {
  // Set the spinning direction clockwise:
  
  turn(3,HIGH, speed_fast); 
  delay(1000);

  turn(3,LOW, speed_fast); 
  delay(1000);

  turn(2,HIGH, speed_low); 
  delay(1000);

  turn(2,LOW, speed_low); 
  delay(10000);
}