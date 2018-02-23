#include "OmniRobot.h"
#include "Arduino.h"

#define CWSpin 85
#define CCWSpin 170

#define NORTH 153
#define EAST 165
#define SOUTH 102
#define WEST 90

#define NorthEast 129
#define SouthEast 36
#define NorthWest 24
#define SouthWest 66

#define lowVoltageSetting 693 // 11.1 lowV // Low V const precalculated so we're not going the same calculation every loop.
#define R_Batt 10000.0 // not used in code
#define R_GND 4700.0   // not used in code

OmniRobot::OmniRobot(uint8_t PWM1in, uint8_t PWM2in, uint8_t PWM3in, uint8_t PWM4in, uint8_t latchPinIn, uint8_t clockPinIn, uint8_t dataPinIn, uint8_t battVin) {
  OM_PWM1pin = PWM1in;
  OM_PWM2pin = PWM2in;
  OM_PWM3pin = PWM3in;
  OM_PWM4pin = PWM4in;

  OM_latchPin = latchPinIn;
  OM_clockPin = clockPinIn;
  OM_dataPin = dataPinIn;
  OM_battV = battVin;

  // @@@@@@ set mode of output pins @@@@@@
  pinMode(OM_latchPin, OUTPUT);  //
  pinMode(OM_clockPin, OUTPUT);  //
  pinMode(OM_dataPin, OUTPUT);  //

  pinMode(OM_PWM1pin, OUTPUT);  //
  pinMode(OM_PWM2pin, OUTPUT);  //
  pinMode(OM_PWM3pin, OUTPUT);  //
  pinMode(OM_PWM4pin, OUTPUT);  //

  robotSpeed = 160;
  previousDirectionID = 0;
  disableLVA = false;
}

void OmniRobot::welcomeSequence() {
  for (int x = 1; x < 3; x++) // flash the shift register leds a bit to show that we're online.
  {
    sendDataToShiftReg(0);
    delay(250);
    sendDataToShiftReg(255);
    delay(250);
  }
}

void OmniRobot::goNorth() {
  goInDirection(NORTH, 1);
}
void OmniRobot::goSouth() {
  goInDirection(SOUTH, 2);
}
void OmniRobot::goEast() {
  goInDirection(EAST, 3);
}
void OmniRobot::goWest() {
  goInDirection(WEST, 4);
}
void OmniRobot::stopRobot() {
  goInDirection(0, 0);
}

void OmniRobot::rotateCW() {
  goInDirection(CWSpin, 5);
}
void OmniRobot::rotateCCW() {
  goInDirection(CCWSpin, 6);
}

uint8_t OmniRobot::GetRobotSpeed() {
  return robotSpeed;
}
void OmniRobot::SetRobotSpeed(uint8_t newRBTSpeed) {
  robotSpeed = newRBTSpeed;
}

void OmniRobot::disableLowVolageAlarm(boolean activeStatus) {
  disableLVA = activeStatus;
}

float OmniRobot::getBatteryVoltage() {
  int theRead = analogRead(OM_battV);
  float divRatio = (R_Batt + R_GND) / R_GND;
  float vPinLoc =  5.0 * float(theRead) / 1023.0;
  return divRatio * vPinLoc;
}

boolean OmniRobot::batterySafeVoltage()
{
  return (analogRead(OM_battV) > lowVoltageSetting);
}

void OmniRobot::lowVoltageAlarm() // if the main battery is bad, alert the user and stop.
{
  if (disableLVA) return;
  digitalWrite(OM_PWM1pin, 0);
  digitalWrite(OM_PWM2pin, 0);
  digitalWrite(OM_PWM3pin, 0);
  digitalWrite(OM_PWM4pin, 0);
  // make cool looping thingy with LEDS to show low battery (robot)
  while (1) {

    sendDataToShiftReg(1);
    delay(200);
    sendDataToShiftReg(2);
    delay(200);
    sendDataToShiftReg(4);
    delay(200);
    sendDataToShiftReg(8);
    delay(200);
    sendDataToShiftReg(16);
    delay(200);
    sendDataToShiftReg(32);
    delay(200);
    sendDataToShiftReg(64);
    delay(200);
    sendDataToShiftReg(128);
    delay(200);
  }
}

/*
  float dividerRatio()
  {
  return (R_Batt + R_GND) /R_GND ;
  }
*/

void OmniRobot::goInDirection(int theDirection, int currentDirectionID)
{
  if (!batterySafeVoltage()) lowVoltageAlarm();
  if ((theDirection != 0) && (currentDirectionID == previousDirectionID)) {
    analogWrite(OM_PWM1pin, robotSpeed);
    analogWrite(OM_PWM2pin, robotSpeed);
    analogWrite(OM_PWM3pin, robotSpeed);
    analogWrite(OM_PWM4pin, robotSpeed);
  } else {
    analogWrite(OM_PWM1pin, 0);
    analogWrite(OM_PWM2pin, 0);
    analogWrite(OM_PWM3pin, 0);
    analogWrite(OM_PWM4pin, 0);
  }
  this->sendDataToShiftReg(theDirection);
  delay(25);
  if (currentDirectionID != previousDirectionID) delay(50);
  previousDirectionID = currentDirectionID;
}

void OmniRobot::sendDataToShiftReg(int z) //generic code for controlling shift register
{
  shiftOut(OM_dataPin, OM_clockPin, MSBFIRST, z);
  digitalWrite(OM_latchPin, HIGH);
  delay(1);
  digitalWrite(OM_latchPin, LOW);
}


