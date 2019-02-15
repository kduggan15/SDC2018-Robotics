 
//This piece of code is used for generating sounds which can be used for events such as alarms, bootups, errors, etc. 
//Requires the usage of a proper timer library like 'timer' due to disruptive delays created by delay().
//https://playground.arduino.cc/Code/Timer
//library can be found here:
//https://github.com/JChristensen/Timer

#include "Alarm/Event.h"
#include "Alarm/Timer.h"
#include "Pitches.h" 
 
//Pin used for the piezo speaker 
#define PiezoPin 12

//Timer used for the speaker 
//Timer SpeakerTimer;

//Function to set up the Piezo Speaker
void PiezoAlarmSetup(){
  pinMode(PiezoPin, OUTPUT);  
}

//Function to generate the sounds for when connection with controller has not been extablished. 
void SoundAwaitingController(){
  tone(PiezoPin, NOTE_A6, 200);
  delay(100);
  tone(PiezoPin, NOTE_C6, 200);
  delay(100);
  tone(PiezoPin, NOTE_E6, 200);
  delay(100);
  tone(PiezoPin, NOTE_G6, 200);
  delay(100);
  tone(PiezoPin, NOTE_C6, 200);
  delay(300);
}

//Function to generate the sounds for when connection with the controller is established. 
void SoundControllerConnected(){
  tone(PiezoPin, NOTE_A6, 200);
  delay(100);
  tone(PiezoPin, NOTE_C6, 200);
  delay(100);
  tone(PiezoPin, NOTE_E6, 200);
  delay(100);
  tone(PiezoPin, NOTE_G6, 200);
  delay(100);
  tone(PiezoPin, NOTE_A6, 200);
  delay(300);
  
}

//Function to generate the Alarm sounds. 
void SoundAlarm(){
  tone(PiezoPin, NOTE_A6, 300);
  delay(300);
  tone(PiezoPin, NOTE_F6, 400);
  delay(300);
  tone(PiezoPin, NOTE_A6, 300);
  delay(300);
}

//Function to generate the Error sound.
void SoundError(){
  tone(PiezoPin, NOTE_F6, 400);
  delay(300);
  tone(PiezoPin, NOTE_F5, 400);
  delay(300);
}

//Function to generate the Bootup sound. 
void SoundBootup(){
  tone(PiezoPin, NOTE_E7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_E7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_E7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_C7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_E7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_G7, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, NOTE_G6, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
  tone(PiezoPin, 0, 1000/12);
  delay((1000/12)*1.30);
}
