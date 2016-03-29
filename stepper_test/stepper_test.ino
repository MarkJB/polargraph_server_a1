//Copyright Mark Benson 2016 License CC-BY-NC

// Make sure you have the serial console open (or reset the Arduino if you missed the menu)
// Menu should be self explanatory - you may need to change stepper speed (pluseDelay) or servo positions (servoUpPos/servoDownPos)

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int serialInputVal = 0;

//Min 500ms full stepping
//Min  5ms 1/32 stepping
int pulseDelay = 1000;
int x;
int dirPin1 = 2;
int stepPin1 = 3;
int dirPin2 = 4;
int stepPin2 = 5;
int numSteps = 3200;

int servoUpPos = 63;
int servoDownPos = 125;
int servoDelay = 150;

//Define micro stepping pins here
#define M0_PIN 8
#define M1_PIN 7
#define M2_PIN 6

//Set the micro stepping level here (Defaulting to 1/8th)
#define M0_STEP HIGH
#define M1_STEP HIGH
#define M2_STEP LOW

/*
DRV8825 Microstepping configuration

M0  M1  M2  STEP MODE
0   0   0   Full step (2-phase excitation) with 71% current
1   0   0   1/2 step (1-2 phase excitation)
0   1   0   1/4 step (W1-2 phase excitation)
1   1   0   8 microsteps/step
0   0   1   16 microsteps/step
1   0   1   32 microsteps/step
0   1   1   32 microsteps/step
1   1   1   32 microsteps/step

A4988 Microstepping configuration 
MS1   MS2   MS3   Microstep Resolution Excitation Mode
(M0)  (M1)  (M2)
L     L     L     Full Step 2 Phase
H     L     L     Half Step 1-2 Phase
L     H     L     Quarter Step W1-2 Phase
H     H     L     Eighth Step 2W1-2 Phase
H     H     H     Sixteenth Step 4W1-2 Phase
*/

void setup() 
{ 
	//pinMode(6,OUTPUT); // Enable 
	pinMode(dirPin1,OUTPUT); // 
	pinMode(stepPin1,OUTPUT); // 
	pinMode(dirPin2,OUTPUT); // 
	pinMode(stepPin2,OUTPUT); // 
	//digitalWrite(6,LOW); // Set Enable low 
	Serial.begin(9600);

	pinMode(M0_PIN, OUTPUT);
	pinMode(M1_PIN, OUTPUT);
	pinMode(M2_PIN, OUTPUT);
	digitalWrite(M0_PIN, M0_STEP);
	digitalWrite(M1_PIN, M1_STEP);
	digitalWrite(M2_PIN, M2_STEP);

  myservo.attach(A0);  // attaches the servo on pin A0 to the servo object

  Serial.println("Stepper test menu: Choose a test");
  Serial.println("");
  Serial.println("For hanging v-plotter e.g. a polargraph:");
  Serial.println("Stepper1 (P1) = Right Motor, Stepper2 (P2) = Left Motor");
  Serial.println("");
  Serial.println("1: Left Stepper - Clockwise");
  Serial.println("2: Left Stepper - Anti-clockwise");
  Serial.println("3: Right Stepper - Clockwise");
  Serial.println("4: Right Stepper - Anti-clockwise");
  Serial.println("5: Servo - Up");
  Serial.println("6: Servo - Down");

}

void loop() 
{
  
  while (Serial.available() == 0);
  int serialInputVal = Serial.parseInt();

  switch (serialInputVal)
  {
    case 1:
      stepper(1,1);
      break;
    case 2:
      stepper(1,0);
      break;
    case 3:
      stepper(2,1);
      break;
    case 4:
      stepper(2,0);
      break;
    case 5:
      servoUp(1);
      break;
    case 6:
      servoUp(0);
      break;
  }
}


void stepper(int whichStepper, boolean turnClockwise)
{
  //int dirPin1 = 4;
  //int stepPin1 = 5;
  //int dirPin2 = 2;
  //int stepPin2 = 3;  
  //Stepper 2 is the left motor
  //Stepper 1 is the right motor
  int stepPin = 0;
  int dirPin = 0;
  //Serial.println("Debug: whichStepper and direction are:");
  //Serial.println(whichStepper);
  //Serial.println(turnClockwise);
  if(whichStepper == 1)
  {
    stepPin = stepPin1;
    dirPin = dirPin1;
  }
  else
    {
    stepPin = stepPin2;
    dirPin = dirPin2;
  }
  digitalWrite(dirPin,turnClockwise); // Set Dir

  for(x = 0; x < numSteps; x++) // Loop 200 times 
  { 
    digitalWrite(stepPin,HIGH); // Output high 
    delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
    digitalWrite(stepPin,LOW); // Output low 
    delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
    //Serial.println("First loop");
  } 
delay(1000); // pause one second
}

void servoUp(bool servoArmState)
{
  if(servoArmState == 1)
  {
      //Serial.println("Debug: Servo up");
      myservo.write(servoUpPos);                  // sets the servo position according to the scaled value 
      delay(servoDelay);                           // waits for the servo to get there 
  }
  else
  { 
      //Serial.println("Debug: Servo down");
      myservo.write(servoDownPos);                  // sets the servo position according to the scaled value 
      delay(servoDelay);                           // waits for the servo to get there 
  }
}

