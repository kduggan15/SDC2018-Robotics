/*Code that manages all the control systems of the bot and bring all the pieces of code from other files together.
 *  
 *  
 *  
 */ 

boolean soundPlaying;


//Checks battery level, does not allow the robot to run if the battery level is too low
 void BatteryCheck(){

   BatteryVoltageRead();

   //Checks for battery voltage
   if((BatteryVoltage1 <=DischargeVoltage) && (BatteryVoltage2 <= DischargeVoltage)){
    
    LowVoltageFlag = 1; //sets the low voltage flag
    MecStop(); //Stops DC Motors for mecanum wheels
    ShellEStop(); //Stops the shell motors
    DoorEStop(); //Stops the door lifting motors
    EmergencyStopEN(); //Disables the stepper motors
    SoundAlarm(); //Sounds alarm to alert the user that the battery voltage is low

    if(SystemDebug = 1){
      Serial.print("Warning: Battery Low Voltage: B1-");
      Serial.print(BatteryVoltage1); Serial.print("V");
      Serial.print(" B2-");
      Serial.print(BatteryVoltage2); Serial.println("V");
     }
   }

   else if((BatteryVoltage1 > DischargeVoltage) && (BatteryVoltage2 > DischargeVoltage)){
    
    LowVoltageFlag = 0; //resets the low voltage flag    
    EmergencyStopDis(); //enables the stepper motors

     if(SystemDebug = 1){
      Serial.print("Battery OK: B1-");
      Serial.print(BatteryVoltage1); Serial.print("V");
      Serial.print(" B2-");
      Serial.print(BatteryVoltage2); Serial.println("V");
     }
   }
 }

//Piece of code used to move the bot with the controller, previously located in the main file. 
void MovementController(){

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
   
  if(SystemDebug = 1){
  Serial.println(get_joy_RX());
  }
}
