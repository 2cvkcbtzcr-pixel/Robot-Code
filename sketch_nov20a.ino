/*--------------------------------------------------------
Poker-Face, Stephen Dragos
Note: the start button must be pushed for 1s
  for the event to register. 
---------------------------------------------------------*/

// constants
#define WATCHLED    2         // LED is pin 2
#define STARTBUTTON 3         // start button is pin 3

#define STEPPER_PIN_1 9       // Stepper motor pins 9
#define STEPPER_PIN_2 10      // 10
#define STEPPER_PIN_3 11      // 11
#define STEPPER_PIN_4 12      // 12
#define DC_MOTOR_PIN 5        // DC motor pin 5


int step_number = 0;
const int steps[8][4] = {
  {1,0,0,0},
  {1,1,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,1},
  {0,0,0,1},
  {1,0,0,1}
};

const int DEG15 = 340;  // 15° on large gear


void setup()                    // run once, when program starts
{
  pinMode(WATCHLED, OUTPUT);    // sets the LED pin as output
  pinMode(STARTBUTTON,INPUT);   // sets the button pin as input
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(DC_MOTOR_PIN, OUTPUT);

  digitalWrite(DC_MOTOR_PIN, LOW);
  // *** Place your additional setup code here ***
}

void loop()
{

// Flash watchdog LED while waiting for button press
while (true) {
  // Flash LED
  digitalWrite(WATCHLED,HIGH);
  delay(250);
  digitalWrite(WATCHLED,LOW);
  delay(750);

  // Check button press
  if (digitalRead(STARTBUTTON) == LOW) {
    unsigned long pressTime = millis();

    // Wait while button is held
    while (digitalRead(STARTBUTTON) == LOW) {
      if (millis() - pressTime >= 1000) { // 1 second hold
        delay(2000); // optional pause before sequence
        runSequence(); // trigger robot sequence
        break; // exit the hold check
      }
    }
  }
}

 // return to flashing watchdog LED
}


void runSequence() 
{
  for (int repeat = 0; repeat < 2; repeat++) { // repeat twice
    step_number = 0;

    // Stepper LEFT
    StepMotor(DEG15, 1);
    delay(300);
    DC_MotorPulse();

    // Stepper MIDDLE
    StepMotor(DEG15, 0);
    delay(300);
    DC_MotorPulse();

    // Stepper RIGHT
    StepMotor(DEG15, 0);
    delay(300);
    DC_MotorPulse();
  }


 // Return to middle at end
  StepMotor(DEG15, 1);
  delay(300);
}


void DC_MotorPulse() {
  digitalWrite(DC_MOTOR_PIN, HIGH);
  delay(1000);  // run motor ~1s
  digitalWrite(DC_MOTOR_PIN, LOW);

}

void StepMotor(int stepsToMove, bool dir) {
  for (int i = 0; i < stepsToMove; i++) {
    OneStep(dir);
    delay(2); // adjust speed if needed
  }
}

void OneStep(bool dir) {
  digitalWrite(STEPPER_PIN_1, steps[step_number][0]);
  digitalWrite(STEPPER_PIN_2, steps[step_number][1]);
  digitalWrite(STEPPER_PIN_3, steps[step_number][2]);
  digitalWrite(STEPPER_PIN_4, steps[step_number][3]);

  if (dir) step_number++;
  else step_number--;

  if (step_number > 7) step_number = 0;
  if (step_number < 0) step_number = 7;
}

