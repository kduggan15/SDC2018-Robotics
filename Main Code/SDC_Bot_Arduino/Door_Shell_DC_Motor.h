#ifndef DOOR_SHELL_DC_MOTOR_H
#define DOOR_SHELL_DC_MOTOR_H

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
#define DoorEndRaised 31         //Pin for endstop for the raised position of door.
#define DoorEndLowered 33        //Pin for endstop for the lowered positon of door.

//Constant speed variables for the shell and door motors (0-255).
const int ShellMotorCSpeed = 25;
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
  long unsigned time = millis();
  long unsigned end_time = time + 10000;
  digitalWrite(MShellDir, HIGH);

  while(digitalRead(ShellEndRetracted) != 1 && millis()<end_time){
    if(SystemDebug == 2){
      Serial.print("Shell retract timout: ");
      Serial.print(end_time-millis());
      Serial.print("\tShell End Retracted pin: ");
      Serial.println(ShellEndRetracted);
    }
    analogWrite(MShellSpeed, ShellMotorCSpeed);
  }
  analogWrite(MShellSpeed, 0);
}

//Shell extension function.
void ShellExtend(){
  long unsigned time = millis();
  long unsigned end_time = time + 10000;
  digitalWrite(MShellDir, LOW);

  while(digitalRead(ShellEndExtended) != 1 && millis()<end_time){
    if(SystemDebug == 2){
      Serial.print("Shell extend timout: ");
      Serial.print(end_time-millis());
      Serial.print("\tShell End Extend pin: ");
      Serial.println(ShellEndExtended);
    }
    analogWrite(MShellSpeed, ShellMotorCSpeed);
  }
  analogWrite(MShellSpeed, 0);
}

/* Door raising and lowering functions.
 *
 */

//Door raising function.
void DoorRaise(){
  long unsigned time = millis();
  long unsigned end_time = time + 5000;
  digitalWrite(MDoorDir, LOW);

  while(digitalRead(DoorEndRaised) != 1 && millis()<end_time){
    analogWrite(MDoorSpeed, DoorMotorCSpeed);
    if(SystemDebug == 2){
      Serial.print("Door raised timout: ");
      Serial.print(end_time-millis());
      Serial.print("\tDoor End Raised pin: ");
      Serial.println(DoorEndRaised);
    }
  }
  analogWrite(MDoorSpeed, 0);
}

//Door lowering function.
void DoorLower(){
  long unsigned time = millis();
  long unsigned end_time = time + 5000;
  digitalWrite(MDoorDir, HIGH);

  while(digitalRead(DoorEndLowered) != 1 && millis()<end_time){
    analogWrite(MDoorSpeed, DoorMotorCSpeed);
    if(SystemDebug == 2){
      Serial.print("Door lowered timout: ");
      Serial.print(end_time-millis());
      Serial.print("\tDoor End Lowered pin: ");
      Serial.println(DoorEndLowered);
    }
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

#endif /* DOOR_SHELL_DC_MOTOR_H*/
