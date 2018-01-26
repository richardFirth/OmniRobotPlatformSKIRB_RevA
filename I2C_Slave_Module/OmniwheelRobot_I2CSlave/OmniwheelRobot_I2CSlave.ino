



// @@@@@@ #include statements to bring in libraries @@@@@@
   #include <Wire.h> // for communicating with the XBee
   #include "OmniRobot.h"

// @@@@@@ #define statements for Pin values @@@@@@

   #define PWM_1 5   //
   #define PWM_2 6   //
   #define PWM_3 9   //
   #define PWM_4 10   //

   #define BlueLED 12   //
   #define BatteryV A0   //

  #define SLAVE_I2C_ADDRESS 14
  
#define latchPin 4   //Pin connected to latch pin (ST_CP) of 74HC595
#define clockPin 7   //Pin connected to clock pin (SH_CP) of 74HC595
#define dataPin 8   //Pin connected to Data in (DS) of 74HC595

// for communication with remote. hold incoming values.

boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
int verticalValue = 512, horizontalValue=512;
boolean JoystickBatteryGood;

OmniRobot OmniBot = OmniRobot(PWM_1,PWM_2,PWM_3,PWM_4,latchPin,clockPin,dataPin,BatteryV);

void setup() {

   Serial.begin(9600);
   Serial.println(F("OmniwheelRobot_I2CSlave"));
   Serial.println(F("Last Modified 26Dec2017"));
   
  Wire.begin(SLAVE_I2C_ADDRESS);                // join i2c bus with address #8
//  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(handleReceipts); // register event

  
// @@@@@@ set mode of output pins @@@@@@
   pinMode(latchPin,OUTPUT);   //
   pinMode(clockPin,OUTPUT);   //
   pinMode(dataPin,OUTPUT);   //

   pinMode(PWM_1,OUTPUT);   //
   pinMode(PWM_2,OUTPUT);   //
   pinMode(PWM_3,OUTPUT);   //
   pinMode(PWM_4,OUTPUT);   //
   
   pinMode(BlueLED,OUTPUT);   //

   OmniBot.welcomeSequence();
   if (OmniBot.getBatteryVoltage() < 6.0) OmniBot.disableLowVolageAlarm(true);
}



void loop() 
{
//  getLatestMasterData(); // get latest xbee
  movementLoop(); // move robots

}
 
void sendDataToShiftReg(int z) //generic code for controlling shift register
{
   shiftOut(dataPin, clockPin, MSBFIRST,z);
   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin, LOW);
}
