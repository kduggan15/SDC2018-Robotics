
/*This is the main code used for the SDC CCNY robot. 
 * 
 */
 
#include "Distance_Sensor_Data.h"     //Information adquired from distance sensors
#include "IMU_Data.h"                 //Information adquired from the innertial measurement unit
#include "Picking_Steppers.h"         //Motion for the stepper motors used for the picking mechanism
#include "Door_Shell_DC_Motor.h"      //Motion for the DC motors used for the door and shell mechanism
#include "Motion_DC_Motors.h"         //Motion for the DC motors used for the mecanum wheels to move the body
#include "Piezo_Sound.h"              //Signal sent to the piezo speaker 
#include "Communications.h"           //Communications for sending and recieving information

void setup() {
  BodyMotionSetup();
  CommunicationsSetup();
  MotionSetup();
  StepperSetup(100,16);
  PiezoAlarmSetup();

  Serial.begin(9600);                 // Serial Communication for all modules that require it
}

void loop() {


}
