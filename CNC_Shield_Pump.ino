/*
200 steps at 40 speed corresponds to air gaps of 35uL in the tubing
*/


#include <Stepper.h>

// set up motor pins
#define STEPS 200
#define pumpStepper 2
#define pumpDir 5
#define enable 8

// set up user interface pins
#define redButton 13
#define greenButton 12
#define redLED 11
#define yellowLED 10
#define greenLED 9

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, pumpStepper, pumpDir);

// initialize state flags
int redButtonState = 0;
int greenButtonState = 0;
int abortState = 0;

void step(int steps)
{
  digitalWrite(enable, LOW);
  digitalWrite(pumpStepper, HIGH);
  stepper.step(steps);
  digitalWrite(pumpStepper, LOW);
  digitalWrite(enable, HIGH);
}

void setup()
{
  // Motor pins
  pinMode(pumpStepper, OUTPUT);
  pinMode(pumpDir, OUTPUT);
  pinMode (enable, OUTPUT);
  digitalWrite(pumpStepper, LOW);
  digitalWrite(pumpDir, LOW);  // LOW = clockwise 
  digitalWrite(enable, HIGH);  // HIGH = disabled

  // User interface pins
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);

  // set the speed of the motor in RPMs
  stepper.setSpeed(80);
}

void loop()
{
  // reset LEDs to indicate ready
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // reset state flags
  redButtonState = 0;
  greenButtonState = 0;
  abortState = 0;

  // read buttons
  greenButtonState = digitalRead(greenButton);
  redButtonState = digitalRead(redButton);

  if (greenButtonState == HIGH && redButtonState == LOW){  // green button activates Gram stain protocol
    while(1){

        // indicate a stain is in progress
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH);

        // dispense crystal violet (5uL)
        step(1200);

        // wait 60 seconds, check for abort
        for(int i = 0; i < 6000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);

          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }

          delay(10);
        }

        if (abortState){
          break;
        }


        // dispense wash step (15 uL)
        step(600);

        // wait 20 seconds, check for abort
        for(int i = 0; i < 2000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense Gram's iodine
        step(600);

        // wait 60 seconds, check for abort
        for(int i = 0; i < 6000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense decolorizer
        step(600);

        // wait 10 seconds, check for abort
        for(int i = 0; i < 1000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense wash step (15 uL)
        step(700);

        for(int i = 0; i < 2000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense safranin (5 uL)
        step(700);

        // wait 30 seconds, check for abort
        for(int i = 0; i < 3000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            abortState = 1;
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense wash step (15 uL)
        step(700);

        // wait for 5 seconds
        delay(5000);

        digitalWrite(yellowLED, LOW);
        
        break;
    
    }
  }  

  // read buttons
  greenButtonState = digitalRead(greenButton);
  redButtonState = digitalRead(redButton);

  if (greenButtonState == HIGH && redButtonState == HIGH){
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
    step(400);
    delay(1000);
  }     
}

// END FILE
