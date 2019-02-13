#ifndef RC_COMMS_H
#define RC_COMMS_H

#define THROTTLE_SIGNAL_X1_IN digitalPinToInterrupt(2) // INTERRUPT 0 = DIGITAL PIN 2 - use the interrupt number in attachInterrupt
#define THROTTLE_SIGNAL_Y1_IN digitalPinToInterrupt(3) // INTERRUPT 0 = DIGITAL PIN 3 - use the interrupt number in attachInterrupt
#define THROTTLE_SIGNAL_X2_IN digitalPinToInterrupt(18) // INTERRUPT 0 = DIGITAL PIN 18 - use the interrupt number in attachInterrupt
#define THROTTLE_SIGNAL_Y2_IN digitalPinToInterrupt(19) // INTERRUPT 0 = DIGITAL PIN 19 - use the interrupt number in attachInterrupt
#define THROTTLE_SIGNAL_X_IN_PIN 2 // INTERRUPT 0 = DIGITAL PIN 2 - use the PIN number in digitalRead
#define THROTTLE_SIGNAL_Y_IN_PIN 3 // INTERRUPT 0 = DIGITAL PIN 3 - use the PIN number in digitalRead

#define NEUTRAL_THROTTLE 1500 // this is the duration in microseconds of neutral throttle on an electric RC Car
#define NEUTRAL_TOLLERANCE 50 // Anything less than this is ignored
volatile int x1ThrottleIn = NEUTRAL_THROTTLE; // volatile, we set this in the Interrupt and read it in loop so it must be declared volatile
volatile int y1ThrottleIn = NEUTRAL_THROTTLE;
volatile int x2ThrottleIn = NEUTRAL_THROTTLE;
volatile int y2ThrottleIn = NEUTRAL_THROTTLE;


volatile unsigned long ulStartPeriod = 0; // set in the interrupt
volatile boolean bNewThrottleSignal = false; // set in the interrupt and read in the loop
// we could use nThrottleIn = 0 in loop instead of a separate variable, but using bNewThrottleSignal to indicate we have a new signal
// is clearer for this first example
void onX1Throttle(int throttle)
{
  Serial.print("X1 Throttle: ");
  Serial.println(throttle);
}
void onY1Throttle(int throttle)
{
  Serial.print("Y1 Throttle: ");
  Serial.println(throttle);
}
void onX2Throttle(int throttle)
{
  Serial.print("X2 Throttle: ");
  Serial.println(throttle);
}
void onY2Throttle(int throttle)
{
  Serial.print("Y2 Throttle: ");
  Serial.println(throttle);
}
void RC_Comms_Setup()
{
  // tell the Arduino we want the function calcInput to be called whenever INT0 (digital pin 2) changes from HIGH to LOW or LOW to HIGH
  // catching these changes will allow us to calculate how long the input pulse is
  attachInterrupt(THROTTLE_SIGNAL_X1_IN,calcInputX1,CHANGE);
  attachInterrupt(THROTTLE_SIGNAL_Y1_IN,calcInputY1,CHANGE);
}

void calcInputX1()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(THROTTLE_SIGNAL_X_IN_PIN) == HIGH)
  {
    // get the time using micros - when our code gets really busy this will become inaccurate, but for the current application its
    // easy to understand and works very well
    ulStartPeriod = micros();
  }
  else
  {
    // if the pin is low, its the falling edge of the pulse so now we can calculate the pulse duration by subtracting the
    // start time ulStartPeriod from the current time returned by micros()
    if(ulStartPeriod && (bNewThrottleSignal == false))
    {
      x1ThrottleIn = (int)(micros() - ulStartPeriod);
      ulStartPeriod = 0;

      // tell loop we have a new signal on the throttle channel
      // we will not update nThrottleIn until loop sets
      // bNewThrottleSignal back to false
      if (x1ThrottleIn<NEUTRAL_THROTTLE-NEUTRAL_TOLLERANCE || x1ThrottleIn>NEUTRAL_THROTTLE+NEUTRAL_TOLLERANCE && x1ThrottleIn>1000)
        onX1Throttle(x1ThrottleIn);
    }
  }
}

void calcInputY1()
{
  // if the pin is high, its the start of an interrupt
  if(digitalRead(THROTTLE_SIGNAL_Y_IN_PIN) == HIGH)
  {
    // get the time using micros - when our code gets really busy this will become inaccurate, but for the current application its
    // easy to understand and works very well
    ulStartPeriod = micros();
  }
  else
  {
    // if the pin is low, its the falling edge of the pulse so now we can calculate the pulse duration by subtracting the
    // start time ulStartPeriod from the current time returned by micros()
    if(ulStartPeriod && (bNewThrottleSignal == false))
    {
      y1ThrottleIn = (int)(micros() - ulStartPeriod);
      ulStartPeriod = 0;

      // tell loop we have a new signal on the throttle channel
      // we will not update nThrottleIn until loop sets
      // bNewThrottleSignal back to false
      if ((y1ThrottleIn<NEUTRAL_THROTTLE-NEUTRAL_TOLLERANCE || y1ThrottleIn>NEUTRAL_THROTTLE+NEUTRAL_TOLLERANCE) && y1ThrottleIn>1000)
      {
        Serial.println("y throttle is being called");
        onY1Throttle(y1ThrottleIn);
      }
    }
  }
}

#endif /* RC_COMMS_H*/
