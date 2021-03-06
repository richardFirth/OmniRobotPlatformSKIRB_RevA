
// @@@@@@ #include statements to bring in libraries @@@@@@
   #include <SoftwareSerial.h> // for communicating with the XBee
   #include "OmniRobot.h"
   #include "SerialReceiver.h"
// @@@@@@ #define statements for Pin values @@@@@@
   #define SS_RX 2   //RX Pin For Software Serial
   #define SS_TX 3   //TX Pin For Software Serial
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
SoftwareSerial SSConnection(SS_RX,SS_TX); // RX, TX
SerialReceiver mySerialReceiver(&SSConnection);
OmniRobot OmniBot = OmniRobot(PWM_1,PWM_2,PWM_3,PWM_4,latchPin,clockPin,dataPin,BatteryV);

void setup() {
   Serial.begin(9600);
   Serial.println(F("OmniRobotRobot"));
   Serial.println(F("Last Modified 22Feb2018"));
   mySerialReceiver.startReceiver(9600); // change this to 38400 if using bluetooth
// @@@@@@ set mode of output pins @@@@@@
   pinMode(BlueLED,OUTPUT);   //
   OmniBot.welcomeSequence();
   if (OmniBot.getBatteryVoltage() < 6.0) OmniBot.disableLowVolageAlarm(true); // disable low voltage alarm if we are powering over serial port
}

void loop() 
{
  mySerialReceiver.getLatestData(); // get latest data
  movementLoop(); // move robots
}
 
