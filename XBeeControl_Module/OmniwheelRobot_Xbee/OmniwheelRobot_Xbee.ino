



// @@@@@@ #include statements to bring in libraries @@@@@@
   #include <SoftwareSerial.h> // for communicating with the XBee
   #include "OmniRobot.h"

// @@@@@@ #define statements for Pin values @@@@@@
   #define XBEE_RX 2   //RX Pin For Software Serial
   #define XBEE_TX 3   //TX Pin For Software Serial
   #define PWM_1 5   //
   #define PWM_2 6   //
   #define PWM_3 9   //
   #define PWM_4 10   //

   #define BlueLED 12   //
   #define BatteryV A0   //


#define latchPin 4   //Pin connected to latch pin (ST_CP) of 74HC595
#define clockPin 7   //Pin connected to clock pin (SH_CP) of 74HC595
#define dataPin 8   //Pin connected to Data in (DS) of 74HC595

// for communication with remote. hold incoming values.
SoftwareSerial XBee(XBEE_RX,XBEE_TX); // RX, TX
boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
int verticalValue = 512, horizontalValue=512;
boolean JoystickBatteryGood;

OmniRobot OmniBot = OmniRobot(PWM_1,PWM_2,PWM_3,PWM_4,latchPin,clockPin,dataPin,BatteryV);


void setup() {

   Serial.begin(9600);
   Serial.println(F("OmniRobotRobot"));
   Serial.println(F("Last Modified 29Sep2017"));
   XBee.begin(9600);

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
  getLatestXBeeData(); // get latest xbee
  movementLoop(); // move robots

}
 

