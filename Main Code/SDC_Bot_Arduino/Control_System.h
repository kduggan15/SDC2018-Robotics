/*Code that manages all the control systems of the bot and bring all the pieces of code from other files together.
 *
 *
 *
 */
#define MODE_MOTION
#define MODE_PICKPLACE
#include "GateMovement.h"
boolean soundPlaying;
boolean vectorMode=1;
void StopAll(){

  MecStop(); //Stops DC Motors for mecanum wheels
  ShellEStop(); //Stops the shell motors
  DoorEStop(); //Stops the door lifting motors
//  EmergencyStopEN(); //Disables the stepper motors
}

//Checks battery level, does not allow the robot to run if the battery level is too low
 void BatteryCheck(){

   BatteryVoltageRead();

   //Checks for battery voltage
   if((BatteryVoltage1 <=DischargeVoltage) && (BatteryVoltage2 <= DischargeVoltage)){

    LowVoltageFlag = 1; //sets the low voltage flag
    StopAll();
//    SoundAlarm(); //Sounds alarm to alert the user that the battery voltage is low

    if(SystemDebug == 1){
      Serial.print("Warning: Battery Low Voltage: B1-");
      Serial.print(BatteryVoltage1); Serial.print("V");
      Serial.print(" B2-");
      Serial.print(BatteryVoltage2); Serial.println("V");
     }
   }

   else if((BatteryVoltage1 > DischargeVoltage) && (BatteryVoltage2 > DischargeVoltage)){

    LowVoltageFlag = 0; //resets the low voltage flag
//    EmergencyStopDis(); //enables the stepper motors

     if(SystemDebug == 1){
      Serial.print("Battery OK: B1-");
      Serial.print(BatteryVoltage1); Serial.print("V");
      Serial.print(" B2-");
      Serial.print(BatteryVoltage2); Serial.println("V");
     }
   }
 }

void autoForward(){
  GateOpen();
  for(int i=80; i<230; i++)//80-230-245
  {
    MecForwards(i);
    delay(i>>3);
  }
  GateClose();
  for (int i=230; i<240; i++)
  {
    MecForwards(i);
    delay(i>>3);
  }
}

//Piece of code used to move the bot with the controller, previously located in the main file.
void MovementController(){
  int speed;

  /*
  if(!rc_isOn())
  {
    soundPlaying=true;
    SoundAwaitingController();
    StopAll();
  }

   if(rc_isOn() && soundPlaying==true)
   {
    soundPlaying=false;
    SoundControllerConnected();
   }

   else
   {
*/
    if(get_LB1_press()==1)
    {
      Serial.println("AutoForward");
      autoForward();

    }
    else if(get_RB1_press()==1)
    {
      Serial.println("Open Shell");
      ShellExtend();
    }
    else if(get_RB2_press() == 1)
    {
      Serial.println("Close Shell");
      ShellRetract();
    }
    else if(get_RB3_press() == 1)
    {
      Serial.println("Open Door");
      DoorRaise();
    }
    else if(get_RB4_press() == 1)
    {
      Serial.println("Close Door");
      DoorLower();
    }
    //Rotate Clockwise
    else if(get_joy_LX()>20){
      speed = map(get_joy_LX(), 10, 420, 0, 255);
      //Here we move right as a hack to make the robot rotate. There's some pin mixup somewhere, but this makes it works.
      //The original command here was MecCW(speed)
      MecCW(speed);
      GateClose();
      if(SystemDebug==2)
      {
        Serial.print("Moving Clockwise by "); Serial.println(speed);
      }
    }
    //Rotate Counter-Clockwise
    else if(get_joy_LX()<-20){
      speed = map(get_joy_LX(), -10, -420, 0, 255);
      //Here we move left as a hack to make the robot rotate. There's some pin mixup somewhere, but this makes it works.
      //The original command here was MecCCW(speed)
      MecCCW(speed);
      GateClose();
      if(SystemDebug==2)
      {
        Serial.print("Moving Counter-Clockwise by "); Serial.println(speed);
      }
    }
    else if(vectorMode && abs(get_joy_RX())+abs(get_joy_RY()) >15){
      int x,y;
      x = map(get_joy_RX(), -370, 420, -240, 240);
      y = map(get_joy_RY(), -350, 320, -240, 240);
      if(y>0){
        GateOpen();
      }
      InputToOutput(x, y);
    }
    //Movement Right
    else if((get_joy_RX() > 10) && ((get_joy_RY() < 10) && (get_joy_RY() > -10))){
      speed = map(get_joy_RX(), 10, 420, 0, 255);
      //Here we move clockwise as a hack to make the robot straif. There's some pin mixup somewhere, but this makes it works.
      //The original command here was MecRight(speed)
      MecRight(speed);
      if(SystemDebug==2)
      {
        Serial.print("Moving Right by "); Serial.println(speed);
      }
    }
    //Movement Left
    else if((get_joy_RX() < -10) && ((get_joy_RY() < 10) && (get_joy_RY() > -10))){
      speed = map(get_joy_RX(), -10, -370, 0, 255);
      //Here we move counter-clockwise as a hack to make the robot straif. There's some pin mixup somewhere, but this makes it works.
      //The original command here was MecLeft(speed)
      MecLeft(speed);

      if(SystemDebug==2)
      {
        Serial.print("Moving Left by "); Serial.println(speed);
      }
    }

    //Movement Forwards
    else if((get_joy_RY() > 10) && ((get_joy_RX() < 10) && (get_joy_RX() > -10)) ){
      speed = map(get_joy_RY(), 10, 320, 0, 255);
      MecForwards(speed);
      if(speed>50){
        GateOpen();
      }

      if(SystemDebug==2)
      {
        Serial.print("Moving Forward by "); Serial.println(speed);
      }
    }

    //Movement Backwards
    else if((get_joy_RY() < -10) && ((get_joy_RX() < 10) && (get_joy_RX() > -10))){
      speed = map(get_joy_RY(), -10, -350, 0, 255);
      GateClose();
      MecBackwards(speed);

      if(SystemDebug==2)
      {
        Serial.print("Moving Backwards by "); Serial.println(speed);
      }
    }

    //Diagonal Left-Fowards
    else if((get_joy_RX() < -60) && (get_joy_RY() > 60)){
      speed = map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 497, 0, 255);
      MecFLeft(speed);

      if(SystemDebug==2)
      {
        Serial.print("Moving Diagonal Left-Foward by "); Serial.println(speed);
      }
    }

    //Diagonal Right-Forwards
    else if((get_joy_RX() > 60) && (get_joy_RY() > 60)){
      speed = map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 540, 0, 255);
      MecFRight(speed);

      if(SystemDebug==2)
      {
        Serial.print("Moving Diagonal Right-Foward by "); Serial.println(speed);
      }
    }

    //Diagonal Left-Back
    else if((get_joy_RX() < -60) && (get_joy_RY() < -60)){
      speed = map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 524, 0, 255);
      MecBLeft(speed);
      GateClose();

      if(SystemDebug==2)
      {
        Serial.print("Moving Diagonal Left-Back by "); Serial.println(speed);
      }
    }

    //Diagonal Right-Back
    else if((get_joy_RX() > 60) && (get_joy_RY() < -60)){
      speed = map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 570, 0, 255);
      MecBRight(speed);
      GateClose();

      if(SystemDebug==2)
      {
        Serial.print("Moving Diagonal Right-Back by "); Serial.println(speed);
      }
    }
    else{
      GateClose();
      MecStop();

      Serial.println("Stopped");
    }

    if(SystemDebug == 1){
      Serial.print("RightX=");
      Serial.print(get_joy_RX());

      Serial.print(" \tRightY=");
      Serial.print(get_joy_RY());

      Serial.print(" \tLeftX=");
      Serial.print(get_joy_LX());

      Serial.print(" \tLeftY=");
      Serial.print(get_joy_LY());

      Serial.print(" \tLButton=");
      Serial.print(get_joy_LNip());

      Serial.print(" \tRButton=");
      Serial.print(get_joy_RNip());

      Serial.print(" RB1 down:");
      Serial.println(get_RB1_press());
      }
    }

//}

//uses the motion sensors in order to detect any objects that might be in front or around the bot. Stops if too close to them.
void ManualDriveCollisionAvoidance(){

   if(!rc_isOn())
  {
    soundPlaying=true;
    SoundAwaitingController();
    StopAll();
  }

   if(rc_isOn() && soundPlaying==true)
   {
    soundPlaying=false;
    SoundControllerConnected();
   }

   else
   {

    //Movement Right
    if(((get_joy_RX() > 10) && ((get_joy_RY() < 10) && (get_joy_RY() > -10))) && (ProximityArray[4] > 1)){

      MecRight(map(get_joy_RX(), 10, 420, 0, 255));

      Serial.println("Moving Right");
    }
    //Movement Left
    else if(((get_joy_RX() < -10) && ((get_joy_RY() < 10) && (get_joy_RY() > -10))) && (ProximityArray[3] > 1)){
      MecLeft(map(get_joy_RX(), -10, -370, 0, 255));

     Serial.println("Moving Left");
    }

    //Movement Forwards
    else if(((get_joy_RY() > 10) && ((get_joy_RX() < 10) && (get_joy_RX() > -10))) && ( ProximityArray[1] > 1||ProximityArray[0] > 1)){
      MecForwards(map(get_joy_RY(), 10, 320, 0, 255));

      Serial.println("MovingForwards");
    }

    //Movement Backwards
    else if(((get_joy_RY() < -10) && ((get_joy_RX() < 10) && (get_joy_RX() > -10))) && (ProximityArray[2] > 1)){
      MecBackwards(map(get_joy_RY(), -10, -350, 0, 255));

      Serial.println("Moving Backwards");
    }

    //All of these ones need to have some sort of weird code to have them stop lol
    //Diagonal Left-Fowards
    else if((get_joy_RX() < -60) && (get_joy_RY() > 60)){
      MecFLeft(map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 497, 0, 255));

      Serial.println("Moving Diagonal Left-Forwards");
    }

    //Diagonal Right-Forwards
    else if((get_joy_RX() > 60) && (get_joy_RY() > 60)){
      MecFRight(map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 540, 0, 255));

      Serial.println("Moving Diagonal Right-Forwards");
    }

    //Diagonal Left-Back
    else if((get_joy_RX() < -60) && (get_joy_RY() < -60)){
    MecBLeft(map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 524, 0, 255));

      Serial.println("Moving Diagonal Left-Right");
    }

    //Diagonal Right-Back
    else if((get_joy_RX() > 60) && (get_joy_RY() < -60)){
     MecBRight(map(sqrt(pow(get_joy_RX(),2)+pow(get_joy_RY(),2)), 0, 570, 0, 255));

      Serial.println("Moving Diagonal Right-Back");
    }

    else{
      MecStop();

      Serial.println("Stopped");
    }

    if(SystemDebug == 2){
      Serial.print("RightX=");
      Serial.print(get_joy_RX());

      Serial.print(" RightY=");
      Serial.print(get_joy_RY());

      Serial.print(" LeftX=");
      Serial.print(get_joy_LX());

      Serial.print(" LeftY=");
      Serial.print(get_joy_LY());

      Serial.print(" RightButton=");
      Serial.print(get_joy_RNip());

      Serial.print(" RightButton=");
      Serial.println(get_joy_LNip());

      Serial.print("RB1 down:");
      Serial.println(get_RB1_press());
      }
      if(SystemDebug==2)
      {
        Serial.print("RB1 down:");
        Serial.println(get_RB1_press());
      }
    }
}
