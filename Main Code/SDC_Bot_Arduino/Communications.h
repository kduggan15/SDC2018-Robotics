 
#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int x;

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}

void CommunicationsSetup(){
  Wire.begin(SLAVE_ADDRESS); 
  Wire.onReceive(receiveEvent);
}

