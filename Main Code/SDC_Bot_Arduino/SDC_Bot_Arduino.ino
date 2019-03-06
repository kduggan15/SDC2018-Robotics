
/*This is the main code used for the SDC CCNY robot.
 *
 */

//#include "Distance_Sensor_Data.h"     //Information adquired from distance sensors
//#include "IMU_Data.h"                 //Information adquired from the innertial measurement unit
#include "Picking_Steppers.h"         //Motion for the stepper motors used for the picking mechanism
#include "Door_Shell_DC_Motor.h"      //Motion for the DC motors used for the door and shell mechanism
#include "Motion_DC_Motors.h"         //Motion for the DC motors used for the mecanum wheels to move the body
#include "Piezo_Sound.h"              //Signal sent to the piezo speaker
//#include "Communications.h"           //Communications for sending and recieving information
#include "RC_Comms.h"
#include "PowerManagement.h"


boolean soundPlaying;

void setup() {
  BodyMotionSetup();
  //CommunicationsSetup();
  MotionSetup();
  StepperSetup(100,16);
  //PiezoAlarmSetup();
  //StepperSetup(100,16);
  PiezoAlarmSetup();
  //DistanceSensorSetup()
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
