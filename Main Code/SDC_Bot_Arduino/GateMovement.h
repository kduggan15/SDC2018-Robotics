/*This is the code that is used for the two servos that open and close the gates.
 *
 * Pinout:
 * ServoLeft = 12
 * ServoRight = 13
 * Both pins are PWM enabled pins
 */

 /*Note 1:
  * In order for servos to move to a specific position, you need to send it an pwm value that will send it it's positon.
  * Our problem is the following, the two servo motors are placed in opposite directions, as one moves clockwise, the other will move counterclockwise.
  * The problem here is that servos consider their 0 degrees position is relative to the clockwise direction, the higher you in degrees, the more you move clockwise.
  * Why is this a problem? because one of the motors is opposite, instead of for instance, going to 30 degrees as commanded, it will be basically be going to 150 degrees.
  * To correct this, we inverse the values being sent to one of the motors, so instead of sending it 30, we send it 150, which will turn the motor to the 30 position lol
  * that is what the function does.
  */
#ifndef GATE_MOVEMENT_H
#define GATE_MOVEMENT_H
#include <Servo.h>

#define ServoPinLeft 12   //Pin used for the left servo signal
#define ServoPinRight 44  //Pin used for the right servo signal

Servo ServoLeft;          //Object initialization for the left servo
Servo ServoRight;         //Object initialization for the right servo

//Position values for opening and closing the door, these need to be calibrated before being set.

const int OpenPosition = 180;     //Value in degrees at which the gate will swing open
const int ClosedPosition = 20;   //Value in degrees at which the gate will swing closed
const int OpenPositionRight = 0;
const int ClosedPositionRight = 160;
int GateStatus = 0;             //Flag that stores position of the gate, 0 = No position assigned, 1 = Open, 2 = closed.

//Setup for the servos, add this to the main setup.
void ServoSetup(){
    //Initialization of servos based on the library setup, just gives the object, the pin it needs to use.
    ServoLeft.attach(ServoPinLeft); //initialization Left servo
    ServoRight.attach(ServoPinRight); //Initialization Right Servo.
}

//Opens the gate, using the values given by the constant position values of position.
void GateOpen(){

  ServoLeft.write(OpenPosition);                        //Sends position information to left servo
  ServoRight.write(OpenPositionRight);  //Sends posiition information to right servo (Check note 1)
  GateStatus = 1; //Gate opened

  //Prints the status of the gate and position value if debugging is enabled
  if(SystemDebug == 3){
    Serial.print("Gate Status:"); //Status printing
    Serial.println("Open");

    Serial.print(" Position: "); //Position printing
    Serial.print(OpenPosition);
    Serial.print(" Degrees");
  }
}

//Closes the gate, using the values given by the constant position values of position.
void GateClose(){

  ServoLeft.write(ClosedPosition);                        //Sends position information to left servo
  ServoRight.write(ClosedPositionRight);  //Sends posiition information to right servo
  GateStatus = 2; //Gate closed

  //Prints the status of the gate and position value if debugging is enabled
  if(SystemDebug == 3){
    Serial.print("Gate Status:"); //Status Printing
    Serial.print("Closed");

    Serial.print(" Position: "); //Position Printing
    Serial.print(ClosedPosition);
    Serial.print(" Degrees");
  }
}

/*
This is a function that will allow you to move the servos to a specified angle. Call the function and give it the angle
you would like both servos to move to. This will allow you to choose the angle at which the servos will open and close
the gate.

This would be kind of hard to do manually with the controller, so just changing the function value in the code and reflashing
should be fine. ;-)
*/

void ServoCalibration(int TestAngleServo){

  ServoLeft.write(TestAngleServo);                        //Sends position information to left servo
  ServoRight.write(TestAngleServo);

  //Prints the value of the test angle position
  Serial.print("Gate Test Position: ");
  Serial.print(TestAngleServo);         //Position Printing
  Serial.println(" Degrees");

}

/*
 * Top 10 people angel loves:
 * kieran
 * jorge
 * andy
 * brian
 * johnny
 * jade
 * umut
 * brandon
 * balbina
 * thanos with waves and airpods
 */
 #endif /*GATE_MOVEMENT_H*/
