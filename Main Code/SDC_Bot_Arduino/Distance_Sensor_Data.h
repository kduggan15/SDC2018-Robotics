 /* Code used to gather the data of each of the distance sensors. 
   The information of the sensors is stored in global variables which can be accessed from anywhere in the code. 
   
   This piece of code uses the NewPing.h library, more documentation about it can be found here:
   https://playground.arduino.cc/Code/NewPing
   
   Download link can be found here:
   https://github.com/microflo/NewPing
*/

#include <NewPing.h>


//Definition of the pins used for the distance sensors. 

//Pins used for front Left distance sensor
#define TriggerFrontLeft 44 
#define EchoFrontLeft 45

//Pins used for the front right distance sensor
#define TriggerFrontRight 46
#define EchoFrontRight 47

//Pins used for the back distance sensor 
#define TriggerBack 48 
#define EchoBack 49

//Pins used for the left side distance sensor
#define TriggerLeft 50
#define EchoLeft 51

//Pins used for the right side distance sensor
#define TriggerRight 52 
#define EchoRight 53  

//Stores value of Distance in the order Front Left, Front Right, Back, Left, Right. 
int ProximityArray[5] = {0, 0, 0, 0, 0}; 

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 300 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(TriggerFrontLeft, EchoFrontLeft, MAX_DISTANCE), //Front Left
  NewPing(TriggerFrontRight, EchoFrontRight, MAX_DISTANCE), //Front Right
  NewPing(TriggerBack, EchoBack, MAX_DISTANCE), //Back
  NewPing(TriggerLeft, EchoLeft, MAX_DISTANCE), //Left
  NewPing(TriggerRight, EchoRight, MAX_DISTANCE), //Right
};

void DistanceGather(){
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    ProximityArray[i] = sonar[i].ping_cm();
  }
}

//Debug Function that displays the value of the distance at a specific point.

void DistanceDisplay(){
  Serial.print("FL:");
  Serial.print(ProximityArray[0]);
  
  Serial.print(" ");

  Serial.print("FR:");
  Serial.print(ProximityArray[1]);
  
  Serial.print(" ");

  Serial.print("B:");
  Serial.print(ProximityArray[2]);
  
  Serial.print(" ");

  Serial.print("L:");
  Serial.print(ProximityArray[3]);
  
  Serial.print(" ");

  Serial.print("R:");
  Serial.println(ProximityArray[4]);
  
}
