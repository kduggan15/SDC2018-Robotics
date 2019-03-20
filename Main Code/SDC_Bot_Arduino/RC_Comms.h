#ifndef RC_COMMS_H
#define RC_COMMS_H

#include <PinChangeInterrupt.h>

#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  6

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4
#define RC_CH6  5

#define RC_CH1_INPUT  A8
#define RC_CH2_INPUT  A9
#define RC_CH3_INPUT  A10
#define RC_CH4_INPUT  A11
#define RC_CH5_INPUT  A12
#define RC_CH6_INPUT  A13

#define RC_CH1_INT  16
#define RC_CH2_INT  17
#define RC_CH3_INT  18
#define RC_CH4_INT  19
#define RC_CH5_INT  20
#define RC_CH6_INT  21

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];
boolean rc_on;
unsigned long rc_timer;

void rc_read_values() {
  noInterrupts();
  rc_timer = millis();//  Stores the time when the rc is last updated for determining if the rc is on
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  rc_on=true;
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }
void calc_ch5() { calc_input(RC_CH5, RC_CH5_INPUT); }
void calc_ch6() { calc_input(RC_CH6, RC_CH6_INPUT); }

int get_joy_RX()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH1];
  return value-1500;
}

int get_joy_RY()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH2];
  return value-1500;
}

int get_joy_LX()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH4]; /// JORGE: ORIGINALLY RC_CH3 WAS HERE THIS FIXED SERIAL MONITOR OUTPUT
  return value-1500;
}

int get_joy_LY()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH3]; // JORGE: ORIGINALLY RC_CH4 HERE THIS FIXED SERIAL MONITOR OUTPUT
  return value-1500;
}

int get_joy_RNip()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH5];
  return value;
}

int get_joy_LNip()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH6];
  return value;
}
#define BUTTON_TOL 8
#define RB1 1552
boolean get_RB1_press()
{
  int value;
  rc_read_values();
  value = rc_values[RC_CH5];
  return (value>RB1-BUTTON_TOL && value < RB1+BUTTON_TOL);
}

boolean rc_isOn()
{
  rc_on = true;
  if (millis()-rc_timer > 1000)
    rc_on = false;
  Serial.println(rc_on);
  return rc_on;
}

void RC_CommsSetup() {
  //Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);
  pinMode(RC_CH5_INPUT, INPUT);
  pinMode(RC_CH6_INPUT, INPUT);

  attachPinChangeInterrupt(RC_CH1_INT, calc_ch1, CHANGE);
  attachPinChangeInterrupt(RC_CH2_INT, calc_ch2, CHANGE);
  attachPinChangeInterrupt(RC_CH3_INT, calc_ch3, CHANGE);
  attachPinChangeInterrupt(RC_CH4_INT, calc_ch4, CHANGE);
  attachPinChangeInterrupt(RC_CH5_INT, calc_ch5, CHANGE);
  attachPinChangeInterrupt(RC_CH6_INT, calc_ch6, CHANGE);

  if(get_joy_RX() == -1500)
  {
    rc_on=false;
  }
  else
  {
    rc_on = true;
  }
}

#endif /* RC_COMMS_H*/
