 /* Code used to gather the data of each of the distance sensors. 
   The information of the sensors is stored in global variables which can be accessed from anywhere in the code. 
*/

//Definition of the pins used for the distance sensors. 

//Pins used for front Left distance sensor
#define TriggerFrontLeft 44 //working
#define EchoFrontLeft 45

//Pins used for the front right distance sensor
#define TriggerFrontRight 46
#define EchoFrontRight 47

//Pins used for the back distance sensor 
#define TriggerBack 48 //working
#define EchoBack 49

//Pins used for the left side distance sensor
#define TriggerLeft 50
#define EchoLeft 51

//Pins used for the right side distance sensor
#define TriggerRight 52 //working
#define EchoRight 53  

//Variables used for storing distance values of each of the sensors 
float DistanceFrontLeft = 0;
float DistanceFrontRight = 0;
float DistanceBack = 0;
float DistanceLeft = 0;
float DistanceRight = 0;

//Constant value used for the calculations of the distance value
const float DurationConstant = 0.034/2; 

//Maximum value that the sensor can measure before the data becomes unusable
const float MaximumDistance = 500.0; //100cm

//Function used to set up all the pins which will be used by the distance sensors. Should be added to the main code. 
void DistanceSensorSetup(){
  
  //Setup of all pins used by the distance sensors.
  pinMode(TriggerFrontLeft, OUTPUT); 
  pinMode(EchoFrontLeft, INPUT); 
  pinMode(TriggerFrontRight, OUTPUT); 
  pinMode(EchoFrontRight, INPUT); 
  pinMode(TriggerBack, OUTPUT); 
  pinMode(EchoBack, INPUT); 
  pinMode(TriggerLeft, OUTPUT); 
  pinMode(EchoLeft, INPUT); 
  pinMode(TriggerRight, OUTPUT); 
  pinMode(EchoRight, INPUT); 
  
}

void DistanceGatherFrontLeft(){
   float TempDuration;
   
  //Clears the Trigger Pin
  digitalWrite(TriggerFrontLeft, LOW);
  delayMicroseconds(2);
  //Sets the Trigger Pin on HIGH state for 10 micro seconds
  digitalWrite(TriggerFrontLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerFrontLeft, LOW);
  
  //Reads the Echo Pin, returns the sound wave travel time in microseconds
  TempDuration = pulseIn(EchoFrontLeft, HIGH);
  // Calculating the distance
  DistanceFrontLeft = TempDuration*DurationConstant;

  //Checks to see wether the distance value is greater than then maximum range of the distance sensor
  if(DistanceFrontLeft > MaximumDistance){
    //Debugging  
    Serial.print("FrontLeft - Target out of Range");
    DistanceFrontLeft = MaximumDistance; 
  }
 
  //Prints Distance in serial monitor (For debugging only)
  Serial.print("Distance FrontLeft: ");
  Serial.println(DistanceFrontLeft);
}

void DistanceGatherFrontRight(){
   float TempDuration;
   
  //Clears the Trigger Pin
  digitalWrite(TriggerFrontRight, LOW);
  delayMicroseconds(2);
  //Sets the Trigger Pin on HIGH state for 10 micro seconds
  digitalWrite(TriggerFrontRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerFrontRight, LOW);
  
  //Reads the Echo Pin, returns the sound wave travel time in microseconds
  TempDuration = pulseIn(EchoFrontRight, HIGH);
  //Calculating the distance
  DistanceFrontRight = TempDuration*DurationConstant;

  //Checks to see wether the distance value is greater than then maximum range of the distance sensor
  if(DistanceFrontRight > MaximumDistance){
    //Debugging  
    Serial.print("FrontRight - Target out of Range");
    DistanceFrontRight = MaximumDistance; 
  }
 
  //Prints Distance in serial monitor (For debugging only)
  Serial.print("Distance FrontRight: ");
  Serial.println(DistanceFrontRight); 
}

void DistanceGatherBack(){
  float TempDuration;
   
  //Clears the Trigger Pin
  digitalWrite(TriggerBack, LOW);
  delayMicroseconds(2);
  //Sets the Trigger Pin on HIGH state for 10 micro seconds
  digitalWrite(TriggerBack, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerBack, LOW);
  
  //Reads the Echo Pin, returns the sound wave travel time in microseconds
  TempDuration = pulseIn(EchoBack, HIGH);
  //Calculating the distance
  DistanceBack = TempDuration*DurationConstant;

  //Checks to see wether the distance value is greater than then maximum range of the distance sensor
  if(DistanceBack > MaximumDistance){
    //Debugging  
    Serial.print("Back - Target out of Range");
    DistanceBack = MaximumDistance; 
  }
 
  //Prints Distance in serial monitor (For debugging only)
  Serial.print("Distance Back: ");
  Serial.println(DistanceBack);
    
}

void DistanceGatherLeft(){
  float TempDuration;
   
  //Clears the Trigger Pin
  digitalWrite(TriggerLeft, LOW);
  delayMicroseconds(2);
  //Sets the Trigger Pin on HIGH state for 10 micro seconds
  digitalWrite(TriggerLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerLeft, LOW);
  
  //Reads the Echo Pin, returns the sound wave travel time in microseconds
  TempDuration = pulseIn(EchoLeft, HIGH);
  //Calculating the distance
  DistanceLeft = TempDuration*DurationConstant;

  //Checks to see wether the distance value is greater than then maximum range of the distance sensor
  if(DistanceLeft > MaximumDistance){
    //Debugging  
    Serial.print("Left - Target out of Range");
    DistanceLeft = MaximumDistance; 
  }
 
  //Prints Distance in serial monitor (For debugging only)
  Serial.print("Distance Left: ");
  Serial.println(DistanceLeft);
  
}

void DistanceGatherRight(){
  float TempDuration;
   
  //Clears the Trigger Pin
  digitalWrite(TriggerRight, LOW);
  delayMicroseconds(2);
  //Sets the Trigger Pin on HIGH state for 10 micro seconds
  digitalWrite(TriggerRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerLeft, LOW);
  
  //Reads the Echo Pin, returns the sound wave travel time in microseconds
  TempDuration = pulseIn(EchoRight, HIGH);
  //Calculating the distance
  DistanceRight = TempDuration*DurationConstant;

  //Checks to see wether the distance value is greater than then maximum range of the distance sensor
  if(DistanceRight > MaximumDistance){
    //Debugging  
    Serial.print("Right - Target out of Range");
    DistanceRight = MaximumDistance; 
  }
 
  //Prints Distance in serial monitor (For debugging only)
  Serial.print("Distance Right: ");
  Serial.println(DistanceRight);
  
}
