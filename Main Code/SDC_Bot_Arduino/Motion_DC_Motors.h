
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

//Motor 3 (Speed and Direction)
#define MSpeed3 8    // before was 9 here
#define MDir3 26

//Motor 4 (Speed and Direction)
#define MSpeed4 9   // before was 10 here
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

//Speeds need to be assigned as numbers between 0-255.
// HIGH = Forwards, LOW = Backwards
// Anywhere where Speed = 0, means that the motor is turned off.

//motor commands
void MotorCommand(int wFR,int wFL, int wBL, int wBR, bool wFRDir, bool wFLDir, bool wBRDir, bool wBLDir){
//Speeds
  digitalWrite(MDir1, wFLDir);
  digitalWrite(MDir2, wFRDir);
  digitalWrite(MDir3, wBLDir);
  digitalWrite(MDir4, wBRDir);
//Directions
  analogWrite(MSpeed1, wFL);
  analogWrite(MSpeed2, wFR);
  analogWrite(MSpeed3, wBL);
  analogWrite(MSpeed4, wBR);
}

//take controller inputs and convert to motor speeds
void InputToOutput(int x, int y){
  int wFR; int wFL; int wBL; int wBR;
  bool wFRDir, wFLDir, wBRDir, wBLDir;
  float m = sqrt(sq(x)+sq(y));
  if (m > 10){
    float a = atan2(y,x);
    //if (x<0){a = a + PI;}
    //if (x>=0 && y<0) {a = a + 2*PI;}
    if (y<0) {a = a + 2*PI;}

    if(0<=a && a<PI/2){
       if(SystemDebug == 4){
          Serial.print("Quadrant 1");
       }
      wFR = m*-cos(2*a);
      wFL = m;
      wBR = m;
      wBL = wFR;
    }
    else if (PI/2<=a && a<PI){
      if(SystemDebug == 4){
          Serial.print("Quadrant 2");
       }
      wFR = m;
      wFL = m*-cos(2*a);
      wBR = wFL;
      wBL = m;
    }
    else if (PI<=a && a<3*PI/2){
      if(SystemDebug == 4){
          Serial.print("Quadrant 3");
      }
      wFR = m*cos(2*a);
      wFL = -m;
      wBR = -m;
      wBL = wFR;
    }
    else if (3*PI/2<=a && a<=2*PI){
      if(SystemDebug == 4){
          Serial.print("Quadrant 4");
      }
      wFR = -m;
      wFL = m*cos(2*a);
      wBR = wFL;
      wBL = -m;
    }
    if (wFR > 0){
      wFRDir = HIGH;
    }
    else {
      wFRDir = LOW;
      //wFR = abs(wFR);
    }
    if (wFL > 0){
      wFLDir = HIGH;
    }
    else {
      wFLDir = LOW;
      //wFL = abs(wFL);
    }
    if (wBR > 0){
      wBRDir = HIGH;
    }
    else {
      wBRDir = LOW;
      //wBR = abs(wBR);
    }
    if (wBL > 0){
      wBLDir = HIGH;
    }
    else {
      wBLDir = LOW;
      //wBL = abs(wBL);
    }
    if(SystemDebug == 4){
      Serial.print("\nx: "); Serial.print(x);
      Serial.print("\ty: "); Serial.print(y);
      Serial.print("\ta: "); Serial.print(a);
      Serial.print("\tm: "); Serial.print(m);
      Serial.print("\twFR: "); Serial.print(wFR);
      Serial.print("\twFL: "); Serial.print(wFL);
      Serial.print("\twBL: "); Serial.print(wBL);
      Serial.print("\twBR: "); Serial.print(wBR);
      Serial.print("\twFRDir: "); Serial.print(wFRDir);
      Serial.print("\twFLDir: "); Serial.print(wFLDir);
      Serial.print("\twBLDir: "); Serial.print(wBLDir);
      Serial.print("\twBRDir: "); Serial.println(wBRDir);
    }
    MotorCommand(abs(wFR),abs(wFL), abs(wBL), abs(wBR), wFRDir, wFLDir, wBRDir, wBLDir);
  }
  else {
    MecStop();
  }
}
