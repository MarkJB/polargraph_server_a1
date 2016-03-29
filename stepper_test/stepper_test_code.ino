//Min 500ms full stepping
//Min  5ms 1/32 stepping
int pulseDelay = 5;
int x;
int dirPin1 = 4;
int stepPin1 = 5;
int dirPin2 = 2;
int stepPin2 = 3;
int numSteps = 6400;

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

}

void loop() 
{

digitalWrite(dirPin1,HIGH); // Set Dir high
digitalWrite(dirPin2,HIGH); // Set Dir high

for(x = 0; x < numSteps; x++) // Loop 200 times 
{ 
digitalWrite(stepPin1,HIGH); // Output high 
digitalWrite(stepPin2,HIGH); // Output high 
delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
digitalWrite(stepPin1,LOW); // Output low 
digitalWrite(stepPin2,LOW); // Output low 
delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
//Serial.println("First loop");
} 
delay(1000); // pause one second

digitalWrite(dirPin1,LOW); // Set Dir low
digitalWrite(dirPin2,LOW); // Set Dir low

for(x = 0; x < numSteps; x++) 
// Loop 2000 times 
{ 
digitalWrite(stepPin1,HIGH); // Output high 
digitalWrite(stepPin2,HIGH); // Output high 
delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
digitalWrite(stepPin1,LOW); // Output low 
digitalWrite(stepPin2,LOW); // Output low 
delayMicroseconds(pulseDelay); // Wait 1/2 a ms 
//Serial.println("Second loop");
}
delay(1000); // pause one second 
}


