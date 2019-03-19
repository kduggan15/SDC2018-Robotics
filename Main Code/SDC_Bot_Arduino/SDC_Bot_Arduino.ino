
/*This is the main code used for the SDC CCNY robot.
 *
 *If you're having any issues compiling the code, and it's related to libraries, use the libraries in "libraries" folder. Drag them to the Arduino/libraries folder.
 */

//Systemwide Debug for Serial Output 0 = OFF, 1 = STANDARD, 2 = Analog stick debug.
//More can be added
int SystemDebug = 2;

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

void setup() {
  //Setups for all pieces of code that need setups.
  BodyMotionSetup();
  MotionSetup();
  StepperSetup(100,16);
  StepperSetup(100,16);
  PiezoAlarmSetup();
  RC_CommsSetup();
  IMU_setup();

  Serial.begin(9600);                 // Serial Communication for all modules that require it for debugging
}

void loop() {

  //BatteryCheck(); //Battery level check, does not allow any of the systems to run if battery is far too low

  //Anything that needs to run if battery is not too low goes here
  if(LowVoltageFlag == 0){
    MovementController();
    //DistanceGather();
    //ManualDriveCollisionAvoidance();
  }


}
