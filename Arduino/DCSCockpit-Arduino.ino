#include <Servo.h>
#include <AccelStepper.h>

#define STEPS 8 //4096 steps in total
#define S1 2
#define S2 4
#define KEY 7

AccelStepper stepperAlt(STEPS, 8, 10, 9, 11);
Servo servoBank;
Servo servoPitch;
byte val[5];
byte bank;
byte pitch;
byte stepperRevolutions;
byte stepperRemainder;
int currentStateCLK;
int lastStateCLK;
int counter = 0;
byte rotaryMode = 0;
unsigned long lastButtonPress = 0;

void setup() {
  servoBank.attach(3);
  servoPitch.attach(5);
  
  Serial.begin(9600);
  servoBank.write(85);
  servoPitch.write(90);
  stepperAlt.setMaxSpeed(1000);
  stepperAlt.setCurrentPosition(0);

  //Rotary Encoder
  pinMode(KEY, INPUT_PULLUP);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  lastStateCLK = digitalRead(S1);
}

void loop() {  
  int btnState = digitalRead(KEY);
  if (btnState == LOW){
    if (millis() - lastButtonPress > 50){
      rotaryMode++;
    }
    lastButtonPress = millis();
  }
  currentStateCLK = digitalRead(S1);

  if (rotaryMode == 0){
    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK){
      
      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      if (digitalRead(S2) != currentStateCLK) {
        counter = counter - 300;
      } else {
        // Encoder is rotating CW so increment
        counter  = counter + 300;
      }
      stepperAlt.moveTo(counter);
      stepperAlt.setSpeed(600);
      stepperAlt.runSpeedToPosition();
    }
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
  }

  if (rotaryMode == 1){
    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK){
      
      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      if (digitalRead(S2) != currentStateCLK) {
        counter = counter - 5;
      } else {
        // Encoder is rotating CW so increment
        counter  = counter + 5;
      }
      stepperAlt.moveTo(counter);
      stepperAlt.setSpeed(100);
      stepperAlt.runSpeedToPosition();
    }
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
  }

  if (rotaryMode == 2){
    stepperAlt.setCurrentPosition(0);
  }
  if (rotaryMode > 3){
    rotaryMode = 0;
  }

  if (Serial.available()){
    Serial.readBytes(val, 4);
    bank = val[0];
    pitch = val[1];
    servoBank.write(bank);
    servoPitch.write(pitch);

    stepperRevolutions = val[2];
    stepperRemainder = val[3];
    int stepperPos = (256 * stepperRevolutions + stepperRemainder) * 4.096;
    stepperAlt.moveTo(stepperPos);
    stepperAlt.setSpeed(700);
  }
  stepperAlt.runSpeedToPosition();
}
