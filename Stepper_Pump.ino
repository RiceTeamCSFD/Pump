#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200
#define redButton 3
#define greenButton 2
#define redLED 6
#define yellowLED 5
#define greenLED 4

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 11, 12, 13);  // OUT1, OUT2, OUT3, OUT4

// initialize state flags
int redButtonState = 0;
int greenButtonState = 0;
int abortState = 0;

void step(int steps)
{
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  stepper.step(steps);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void setup()
{
  // Motor pins
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  // User interface pins
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redButton, INPUT);
  pinMode(greenButton, INPUT);

  // set the speed of the motor in RPMs
  stepper.setSpeed(10);
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
  // read green button
  greenButtonState = digitalRead(greenButton);

  if (greenButtonState == HIGH){  // green button activates Gram stain protocol
    while(1){

        // indicate a stain is in progress
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH);

        // dispense crystal violet (5uL)
        step(100);

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
        step(100);

        // wait 20 seconds, check for abort
        for(int i = 0; i < 2000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense Gram's iodine
        step(100);

        // wait 60 seconds, check for abort
        for(int i = 0; i < 6000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense decolorizer
        step(100);

        // wait 10 seconds, check for abort
        for(int i = 0; i < 1000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense wash step (15 uL)
        step(100);

        for(int i = 0; i < 2000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense safranin (5 uL)
        step(100);

        // wait 30 seconds, check for abort
        for(int i = 0; i < 3000; i++){
          // If red button pressed, abort
          redButtonState = digitalRead(redButton);
          
          if (redButtonState == HIGH){
            digitalWrite(redLED, HIGH);
            delay(1000);
            break;
          }
          
          delay(10);
        }

        if (abortState){
          break;
        }

        // dispense wash step (15 uL)
        step(100);

        // wait for 5 seconds
        delay(5000);

        digitalWrite(yellowLED, LOW);
    
    }
  }       
}

// END FILE
