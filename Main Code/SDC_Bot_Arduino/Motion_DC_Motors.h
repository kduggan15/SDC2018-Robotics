
//This code is used for the movement of the Mecanum wheels for the robot.
//This uses the diagram found in the link below in order to generate the motion of the wheels.
//https://www.superdroidrobots.com/images/customPages/mecanum_drive_wheels_vectoring_robot.jpg
//This only requires the use PWM.


//First DC motor driver for movement

//Motor 1 (Speed and Direction)
#define MSpeed1 6
#define MDir1 22

//Motor 2 (Speed and Direction)
#define MSpeed2 7
#define MDir2 24


//Second DC motor driver for movement

//Motor 3 (Speed and Direction)
#define MSpeed3 9
#define MDir3 26

//Motor 4 (Speed and Direction)
#define MSpeed4 10
#define MDir4 28

//Easy initialization which can be called from other parts of the code.
void MotionSetup(){
  //Initialization of all the pins used for the mecanum motors
  pinMode(MSpeed1, OUTPUT);
  pinMode(MSpeed2, OUTPUT);
  pinMode(MSpeed3, OUTPUT);
  pinMode(MSpeed4, OUTPUT);
  pinMode(MDir1, OUTPUT);
  pinMode(MDir2, OUTPUT);
  pinMode(MDir3, OUTPUT);
  pinMode(MDir4, OUTPUT);
}

//Speeds need to be assigned as numbers between 0-255.
// HIGH = Forwards, LOW = Backwards
// Anywhere where Speed = 0, means that the motor is turned off.

//Forwards motion
void MecForwards(int speed){

//Speeds
  digitalWrite(MDir1, HIGH);
  digitalWrite(MDir2, HIGH);
  digitalWrite(MDir3, HIGH);
  digitalWrite(MDir4, HIGH);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);
}

//Backwards motion
void MecBackwards(int speed){

//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);

}

//Right stiffle motion
void MecRight(int speed){

//Speeds
  digitalWrite(MDir1, HIGH);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, HIGH);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);

}

//Left striffle motion
void MecLeft(int speed){

//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, HIGH);
  digitalWrite(MDir3, HIGH);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);

}

//Clockwise motion
void MecCW(int speed){

//Speeds
  digitalWrite(MDir1, HIGH);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, HIGH);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);

}

//CounterClockwise motion
void MecCCW(int speed){

//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, HIGH);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, HIGH);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, speed);

}

/*
 * Functions for diagonal motion
 */

//Moves the motor diagonally towards the front-left direction
void MecFLeft(int speed){
//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, HIGH);
  digitalWrite(MDir3, HIGH);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, 0);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, 0);

}

//Moves the motor diagonally towards the front-right direction
void MecFRight(int speed){
  //Speeds
  digitalWrite(MDir1, HIGH);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, HIGH);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, 0);
  analogWrite(MSpeed3, 0);
  analogWrite(MSpeed4, speed);
}

//Moves the motor diagonally towards the back-left direction
void MecBLeft(int speed){
  //Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, speed);
  analogWrite(MSpeed2, 0);
  analogWrite(MSpeed3, 0);
  analogWrite(MSpeed4, speed);
}

//Moves the motor diagonally towards the back-right direction
void MecBRight(int speed){
//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, 0);
  analogWrite(MSpeed2, speed);
  analogWrite(MSpeed3, speed);
  analogWrite(MSpeed4, 0);

}

//Emergency or regular stop function for the moving mechanism
void MecStop(){

//Speeds
  digitalWrite(MDir1, LOW);
  digitalWrite(MDir2, LOW);
  digitalWrite(MDir3, LOW);
  digitalWrite(MDir4, LOW);
//Directions
  analogWrite(MSpeed1, 0);
  analogWrite(MSpeed2, 0);
  analogWrite(MSpeed3, 0);
  analogWrite(MSpeed4, 0);

}
