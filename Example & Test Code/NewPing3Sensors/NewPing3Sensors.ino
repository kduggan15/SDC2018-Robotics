


#include <NewPing.h>

//Stores value of Distance in the order Front Left, Front Right, Back, Left, Right. 
int ProximityArray[5] = {0, 0, 0, 0, 0}; 

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 300 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(44, 45, MAX_DISTANCE), //Front Left
  NewPing(46, 47, MAX_DISTANCE), //Front Right
  NewPing(48, 49, MAX_DISTANCE), //Back
  NewPing(50, 51, MAX_DISTANCE), //Left
  NewPing(52, 53, MAX_DISTANCE), //Right
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
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() { 
 DistanceGather();
 DistanceDisplay();
}
