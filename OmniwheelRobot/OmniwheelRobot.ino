



// @@@@@@ #include statements to bring in libraries @@@@@@
   #include <SoftwareSerial.h> // for communicating with the XBee


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
unsigned long lastRecieved;

#define lowVoltageSetting 693 // 11.1 lowV // Low V const precalculated so we're not going the same calculation every loop.
#define R_Batt 10000.0 // not used in code
#define R_GND 4700.0   // not used in code

void setup() {

   Serial.begin(9600);
   Serial.println(F("OmniwheelRobot"));
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

        for(int x = 1;x < 3;x++) // flash the shift register leds a bit to show that we're online.
        {
           sendDataToShiftReg(0);
           delay(250);
           sendDataToShiftReg(255);  
           delay(250);
        }
}



void loop() 
{
  getLatestXBeeData(); // get latest xbee
  movementLoop(); // move robots
  testLowVoltage(analogRead(A0)); //check batteries
}
 
void sendDataToShiftReg(int z) //generic code for controlling shift register
{
   shiftOut(dataPin, clockPin, MSBFIRST,z);
   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin, LOW);
}
