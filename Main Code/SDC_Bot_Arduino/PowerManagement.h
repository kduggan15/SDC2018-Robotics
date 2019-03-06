//This piece of code is used for power management, it measures the voltages of the batteries in order to avoid any power related issues. 
//If confused about the use of voltage dividers, see https://learn.sparkfun.com/tutorials/voltage-dividers/all
//Voltage dividers are used in order to read the voltage of the battery by decreasing it to a readable voltage, since the battery will be between 13V-11V and the Arduino can only read 5V-0V

//Pins used in order to read the battery voltage. 
#define Battery1VoltagePin A0 //for battery 1
#define Battery2VoltagePin A1 //for battery 2

float BatteryVoltage1 = 0.0; //Variable used to store voltage of battery 1. 
float BatteryVoltage2 = 0.0; //Variable used to store voltage of battery 2. 

float BatteryVoltage1Temp = 0.0; //Variable used to store voltage of battery 1. Temp Value. 
float BatteryVoltage2Temp = 0.0; //Variable used to store voltage of battery 2. Temp Value. 

float VoltageDividerRatio1 = (10000.0/(10000.0+10000.0)); //Resistor divider constant used for voltage readout conversion for battery 1. Assumed to be R1=10k and R2=10k resistors.
float VoltageDividerRatio2 = (10000.0/(10000.0+10000.0)); //Resistor divider constant used for voltage readout conversion for battery 2. Assumed to be R1=10k and R2=10k resistors.

const float ChargedVoltage = 12.6; //Voltage at which the battery is full.
const float DischargeVoltage = 9.5; //Voltage at which battery is discharged, any lower than this and the battery could be damaged.

bool LowVoltageFlag = 0; 

//Reads the analog voltage value of the battery and and stores it in the two storage variables. 
void BatteryVoltageRead(){

  //Reads voltage for both batteries. 
  BatteryVoltage1Temp = analogRead(Battery1VoltagePin);
  BatteryVoltage2Temp = analogRead(Battery2VoltagePin);

  //Converts the digital voltage value into the actual voltage value of the battery. 
  BatteryVoltage1 = ((map(BatteryVoltage1Temp, 0, 1023, 0.0, 5.0))*VoltageDividerRatio1);
  BatteryVoltage2 = ((map(BatteryVoltage2Temp, 0, 1023, 0.0, 5.0))*VoltageDividerRatio2);
  
}
