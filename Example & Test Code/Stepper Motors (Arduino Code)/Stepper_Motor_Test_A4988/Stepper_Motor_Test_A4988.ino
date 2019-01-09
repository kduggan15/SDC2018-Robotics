/*
This is a test control system for controlling the stepper motors which are used for the movement of the forks for the picking mechanism.
It uses a specific library which can be found here:
https://github.com/laurb9/StepperDriver

The stepper drivers which are being used are the Polulu A4988 breakout stepper drivers.
https://www.pololu.com/product/1182

The stepper drivers require two signals, Step and Direction, which control the step movement and direction of the stepper motor.
 */
#include "A4988.h"

//using a 200-step motor (most common)
#define MOTOR_STEPS 200

//Direction and Step pins used in the Arduino Mega for motor 1
#define DIR1 2
#define STEP1 3

//Direction and Step pins used in the Arduino Mega for motor 2 
#define DIR2 4
#define STEP2 5

//Stepper motor objects which are used to control the stepper motor drivers
A4988 stepper1(MOTOR_STEPS, DIR1, STEP1);
A4988 stepper2(MOTOR_STEPS, DIR2, STEP2);


//Steps per mm of travel (80 is an example value, needs to be calculated based on leadscrew motion)
int StepsPerMM1 = 80;
int StepsPerMM2 = 80;

//Maximum axis Size for each of the axis (200 is an example value, based on full travel of axis) 
int MaxSize1 = 200;
int MaxSize2 = 200;

//Temporary position values, keeps track of the position of the carriage.
int CurrentPos1 = 0; //should not be initialized, test only
int CurrentPos2 = 0; //should not be initialized, test only

//Temporary variable for storing distance in steps
int DistanceSteps;

//Stores the flag value which tells you if carriage will crash with the axis
int DistanceFlag;

//Setup function for stepper motors 
//MSpeed is the speed at which the motors will run in RPM
//MStep is the microstepping setting for the motors (usually 16)
int StepperSetup(int MSpeed, int MStep){

    //Initialization for first motor driver
    stepper1.begin(MSpeed);
    stepper1.setMicrostep(MStep);
    //Initialization for second motor driver
    stepper2.begin(MSpeed);
    stepper2.setMicrostep(MStep);

}

//Movement Functions for both stepper motors
//Distance is amount that needs to be moved in milimeters
//Direction is the direction in which we want to move. Forwards = 1, Backwards = -1. 
int StepperMovement1(int Distance, int Direction){
  int temp1;
  DistanceFlag = 0;

  //Checks to make sure the stepper motor is not going to go over the maximum limit of the axis.
  //If the motor tries to move higher than this value, it could end up damaging or destroying the axis.
  
  if (Direction == 1){
    temp1 = CurrentPos1;
    temp1 = temp1 + Distance;

     if(temp1 > MaxSize1){
        DistanceFlag = 1;
      }
      else{
        CurrentPos1 = CurrentPos1 + Distance;
      }
  }
  
  //Checks to make sure the stepper motor is not going to move beyond the lower limit of the axis. 
  //If the motor moves beyond the lower limit of the axis, it could destroy the carriage or part of the axis. 
  else if(Direction == -1){
     temp1 = CurrentPos1;   
     temp1 = temp1 - Distance;
      
      if(temp1 < 0){
          DistanceFlag = 1;
      }
      else{      
          CurrentPos1 = CurrentPos1 - Distance;
      }
  }

  
  //If everything is correct, sends the movement value to the stepper driver.
  if(DistanceFlag == 0){
        DistanceSteps = StepsPerMM1*Distance*Direction;
        stepper1.move(DistanceSteps);
        Serial.print("Position 1: "); //Prints position value for debugging
        Serial.println(CurrentPos1);
  }

}

//Same as the first motor except that some of the variables have been changed in order to keep values related to second motor.

int StepperMovement2(int Distance, int Direction){
  int temp2;
  DistanceFlag = 0;
  if (Direction == 1){
      temp2 = CurrentPos2;
      temp2 = temp2 + Distance;
      
      if(temp2 > MaxSize2){
         DistanceFlag = 1;
      }
      else{
         CurrentPos2 = CurrentPos2 + Distance;
      }
  }

  else if(Direction == -1){
      temp2 = CurrentPos2;
      temp2 = temp2 - Distance;
      
      if(temp2 < 0){
          DistanceFlag = 1;
      }
      else{
        CurrentPos2 = CurrentPos2 - Distance;
      }
  }

  if(DistanceFlag == 0){
      DistanceSteps = StepsPerMM2*Distance*Direction;
      stepper2.move(DistanceSteps);
      Serial.print("Position 2: ");
      Serial.println(CurrentPos2);
  }
}


//Actual code lol

void setup(){
    //Setup for both of the stepper motors Speed = 100, Microstepping = 1/16
    StepperSetup(100,16);
    Serial.begin(9600);
}

void loop(){
        //Moving Test
        StepperMovement1(10,1);
        StepperMovement2(20,1);
        StepperMovement1(10,1);
        StepperMovement2(20,1);
        StepperMovement1(20,-1);
        StepperMovement2(40,-1);
    
}
