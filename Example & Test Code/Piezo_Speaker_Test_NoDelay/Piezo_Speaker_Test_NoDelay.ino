//This piece of code is used for generating sounds which can be used for events such as alarms, bootups, errors, etc. 
//Requires the usage of a proper timer library like 'timer' due to disruptive delays created by delay().
//https://playground.arduino.cc/Code/Timer
//library can be found here:
//https://github.com/JChristensen/Timer

#include <Event.h>
#include <Timer.h>

//Pin used for the piezo speaker 
#define PiezoPin 5

Timer SpeakerTimer;

//Function to set up the Piezo Speaker
void PiezoAlarmSetup(){
  pinMode(PiezoPin, OUTPUT);  
}

//Function to generate the Alarm sounds. 
void SoundAlarm(){
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
}

//Function to generate the Error sound.
void SoundError(){
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
}

//Function to generate the Bootup sound. 
void SoundBootup(){
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
  SpeakerTimer.pulse(PiezoPin, 500, HIGH);
  SpeakerTimer.pulse(PiezoPin, 500, LOW);
}

void setup() {
  PiezoAlarmSetup();
}

void loop() {
  SoundAlarm();
}
