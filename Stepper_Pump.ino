#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200
#define redButton 3
#define greenButton 2

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 11, 12, 13);  // OUT1, OUT2, OUT3, OUT4

// the previous reading from the analog input
int previous = 0;

// initialize button state flag
int redButtonState = 0;
int greenButtonState = 0;

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
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    pinMode(redButton, INPUT);
    pinMode(greenButton, INPUT);

    // set the speed of the motor in RPMs
    stepper.setSpeed(10);
}

void loop()
{
  redButtonState = digitalRead(redButton);
    greenButtonState = digitalRead(greenButton);

  if (redButtonState == HIGH && greenButtonState == LOW){
    // jog just a bit
    step(10);
    delay(50);
  }

  if (greenButtonState == HIGH && redButtonState == LOW){  // green button activates Gram stain protocol
    /* dispense 5 uL fluid
    step(10);
    delay(1000);  // wait 1 sec
    */
    // dispense crystal violet
    step(100);
    delay(60000);  // wait 1 min

    // dispense wash step
    step(100);
    delay(20000);  // wait 10 sec

    // dispense Gram's iodine
    step(100);
    delay(60000);  // wait 1 min

    // dispense decolorizer
    step(100);
    delay(10000);  // wait 10 sec

    // dispense wash step
    step(100);
    delay(20000);  // wait 10 sec

    // dispense safranin
    step(100);
    delay(30000);  // wait 1 min

    // dispense wash step
    step(100);
    delay(10000);  // wait 5 sec
    
  }

  if (greenButtonState == HIGH && redButtonState == HIGH){
    step(200);
    delay(1000);
  }
}

// END FILE
