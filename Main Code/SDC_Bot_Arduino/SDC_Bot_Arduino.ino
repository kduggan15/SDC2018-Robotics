
/*This is the main code used for the SDC CCNY robot.
 *
 *If you're having any issues compiling the code, and it's related to libraries, use the libraries in "libraries" folder. Drag them to the Arduino/libraries folder.
 */
#include "Door_Shell_DC_Motor.h"      //Motion for the DC motors used for the door and shell mechanism
#include "Motion_DC_Motors.h"         //Motion for the DC motors used for the mecanum wheels to move the robot
#include "Distance_Sensor_Data.h"     //Information adquired from distance sensors
#include "IMU_Data.h"                 //Information adquired from the innertial measurement unit
#include "Picking_Steppers.h"         //Motion for the stepper motors used for the picking mechanism
#include "Piezo_Sound.h"              //Signal sent to the piezo speaker
#include "Communications.h"           //Communications for sending and recieving information to the pi
#include "RC_Comms.h"                 //Recieves and processes information from the RC controller 
#include "PowerManagement.h"          //Deals with power management and battery voltages
#include "Control_System.h"           //All the code related to connecting all previous code together, call functions from this boy on the loop

boolean soundPlaying;

void setup() {
  BodyMotionSetup();
  MotionSetup();
  StepperSetup(100,16);
  StepperSetup(100,16);
  PiezoAlarmSetup();
  RC_CommsSetup();

  Serial.begin(9600);                 // Serial Communication for all modules that require it
}

void loop() {

 /* if(get_joy_RX() == -1500)
  if(!rc_isOn())
  {
    soundPlaying=true;
    SoundAwaitingController();
  }
  //Serial.println(get_joy_RX());
*/
  if(rc_isOn() && soundPlaying==true)
   {
    soundPlaying=false;
    SoundControllerConnected();
   }
   else
   {
    if(get_joy_RX() > 10)
      MecRight(100);
    else if(get_joy_RX() < -10)
      MecLeft(100);
    else if(get_joy_RY() > 10)
      MecForwards(100);
    else if(get_joy_RY() < -10)
      MecBackwards(100);
    else
      MecStop();
   }
  Serial.println(get_joy_RX());

}
