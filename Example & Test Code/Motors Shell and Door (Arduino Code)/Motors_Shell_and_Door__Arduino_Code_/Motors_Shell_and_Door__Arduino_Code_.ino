/*
Code for extending and retracting the shell of the bot, as well as for raising and lowering the back door. 
This code uses 2 dc motors connected to one motor driver and 4 endstops connected directly to the Arduino Mega using pullups to pull signals to 5V. 
*/

//Pins used for motors and endstops related to the shell movement. 
#define MShellSpeed 10           //Pin for speed of shell motor (pwm).
#define MShellDir 30             //Pin for direction of shell motor.
#define ShellEndRetracted 23     //Pin for endstops for the retracted position.
#define ShellEndExtended 25      //Pin for endstop for the extended position.

//Pins used for motors and endstops related to the door movement. 
#define MDoorSpeed 11            //Pin for speed of the door motor (pwm).
#define MDoorDir 32              //Pin for direction of the door motor.
#define DoorEndRaised 27         //Pin for endstop for the raised position of door.
#define DoorEndLowered 29        //Pin for endstop for the lowered positon of door. 

//Constant speed variables for the shell and door motors (0-255).  
const int ShellMotorCSpeed = 100;
const int DoorMotorCSpeed = 100;

void BodyMotionSetup(){
  //Declaration of all pins, motors are outputs, endstops are inputs. 
  pinMode(MShellSpeed, OUTPUT);
  pinMode(MShellDir, OUTPUT);
  pinMode(ShellEndRetracted, INPUT);
  pinMode(ShellEndExtended, INPUT);
  pinMode(MDoorSpeed, OUTPUT);
  pinMode(MDoorDir, OUTPUT);
  pinMode(DoorEndRaised, INPUT);
  pinMode(DoorEndLowered, INPUT);
}

/* Shell Extensions and Retraction functions. 
 *  
 */

//Shell Retraction function.
void ShellRetract(){
  digitalWrite(MShellDir, LOW);
  
  while(digitalRead(ShellEndRetracted) != 1){
    analogWrite(MShellSpeed, ShellMotorCSpeed);
  }
  analogWrite(MShellSpeed, 0);
}

//Shell extension function.
void ShellExtend(){
  digitalWrite(MShellDir, HIGH);
  
  while(digitalRead(ShellEndExtended) != 1){
    analogWrite(MShellSpeed, ShellMotorCSpeed);
  }
  analogWrite(MShellSpeed, 0);
}

/* Door raising and lowering functions. 
 *  
 */

//Door raising function.
void DoorRaise(){
  digitalWrite(MDoorDir, LOW);
  
  while(digitalRead(DoorEndRaised) != 1){
    analogWrite(MDoorSpeed, DoorMotorCSpeed);
  }
  analogWrite(MDoorSpeed, 0);
}

//Door lowering function.
void DoorLower(){
  digitalWrite(MDoorDir, HIGH);
  
  while(digitalRead(DoorEndLowered) != 1){
    analogWrite(MDoorSpeed, DoorMotorCSpeed);
  }
  analogWrite(MDoorSpeed, 0);
}

/*Emergency Stop Functions
  These functions will provide a full stop function for the motors in case something goes wrong. 
  These functions should have higher priority than the previous ones.   
*/

//Emergency Stop function for shell movement
void ShellEStop(){
  analogWrite(MShellSpeed, 0);
}

//Emergency stop function for door movement
void DoorEStop(){
  analogWrite(MDoorSpeed, 0);
}

void setup() {
  // put your setup code here, to run once:
 BodyMotionSetup();
}

void loop() {
  // put your main code here, to run repeatedly:

}
