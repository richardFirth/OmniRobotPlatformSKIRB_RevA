#include <Wire.h>
#include <stdint.h>

const uint8_t SONIC_DISC_I2C_ADDRESS = 0x09;
#define MOTOR_I2C_ADDRESS 14
#define blinkOutLED 12

const uint8_t NUM_OF_SENSORS = 8; // No. of ultrasonic sensors on SonicDisc
// The packet contains NUM_OF_MEASUREMENTS measurements and an error code
const uint8_t I2C_PACKET_SIZE = NUM_OF_SENSORS + 1;
// The number of measurements from each sensor to filter
const uint8_t MEASUREMENTS_TO_FILTER = 5;
const uint8_t INT_PIN = 2;

// The max valid variance in a set of MEASUREMENTS_TO_FILTER measurements
const unsigned int VARIANCE_THRESHOLD = 3;

// Sonic Disc's operational states
enum State {
  STANDBY, // MCU and sensors are on but no measurements are being made
  MEASURING // Sonic Disc is conducting measurements using the sensors
};

// Values to be received via I2C from master
enum I2C_RECEIPT_CODE {
  STATE_TO_STANDBY = 0x0A,
  STATE_TO_MEASURING = 0x0B
};

// Error codes to be transmitted via I2c to the master
enum I2C_ERROR_CODE {
  NO_ERROR,
  IN_STANDBY,
  INCOMPLETE_MEASUREMENT
};

// Flag to indicate the SonicDisc is ready to send a new set of data
volatile bool newData = false;

uint8_t filterIndex = 0;
uint8_t filterBuffer[MEASUREMENTS_TO_FILTER][NUM_OF_SENSORS] = {0};
uint8_t filteredMeasurements[NUM_OF_SENSORS] = {0};
bool newFilteredMeasurements = false;

boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG,JOYSTICK_BUTTON;
int verticalValue = 512, horizontalValue=512;
boolean JoystickBatteryGood;


/**
   Requests an I2C packet from the SonicDisc
   @param  i2cInput         The array that will hold the incoming packet
   @param  transmissionSize The size/length of the incoming packet
   @return                  Error code contained inside the incoming packet
*/
I2C_ERROR_CODE requestPacket(uint8_t i2cInput[], const uint8_t transmissionSize = I2C_PACKET_SIZE) {
  
  Wire.requestFrom(SONIC_DISC_I2C_ADDRESS, transmissionSize);
  uint8_t packetIndex = 0;
  while (Wire.available() && packetIndex < transmissionSize) {
    i2cInput[packetIndex++] = Wire.read();
  }

  return i2cInput[0]; // Return the packet's error code
}


void setup() {
  Wire.begin();
  Serial.begin(38400);
 
  attachInterrupt(digitalPinToInterrupt(INT_PIN), newSonicDiscData, RISING);
  
  Serial.println("Requesting packet from SonicDisc");
  uint8_t dummyInput[I2C_PACKET_SIZE] = {1}; // A throw-away array
 boolean slaveConnected = false;
 
     while(!slaveConnected){
          // Do not proceed unless the SonicDisc is in "MEASURING" state
          sendDataToSonic(STATE_TO_MEASURING);
          
          I2C_ERROR_CODE theErr = requestPacket(dummyInput, I2C_PACKET_SIZE);
          printErrCode(theErr);
          if (theErr == NO_ERROR) slaveConnected = true;
          delay(500);
          Serial.println("Retry connection");
     }
     
 pinMode(blinkOutLED,OUTPUT);
 pinMode(INT_PIN,INPUT);
/*
      while (requestPacket(dummyInput, I2C_PACKET_SIZE) == IN_STANDBY) {
        Serial.println("Setting state to MEASURING");
        sendData(STATE_TO_MEASURING);
      }
*/
  Serial.println("Communication is established and SonicDisc is measuring distances");
}





void loop() {
 // Serial.println(newData);
 delay(10);
 
if (newData) {
    newData = false; // Indicate that we have read the latest data
    digitalWrite(blinkOutLED,HIGH);
    uint8_t sonicDiscInput[I2C_PACKET_SIZE] = {0};
    // Get the I2C packet
    I2C_ERROR_CODE ret = requestPacket(sonicDiscInput, I2C_PACKET_SIZE);
    // Now sonicDiscInput contains the latest measurements from the sensors.
    // However we need to make sure that the data is also of good quality
    // Process the packet only if it is a valid one
    if (ret == NO_ERROR) {
      addInputToFilterBuffer(sonicDiscInput, filterIndex);
      // When we have filled up the filter buffer, time to filter the measurements
      if (filterIndex + 1 == MEASUREMENTS_TO_FILTER) {
        // For each measurement
        sortMeasurements();
        filterMeasurements();
        // Indicate that the measurements are filtered
        newFilteredMeasurements = true;
      }
      // Move along the index
      filterIndex = (filterIndex + 1) % MEASUREMENTS_TO_FILTER;
    }
    digitalWrite(blinkOutLED,LOW);
  }


  if (newFilteredMeasurements) {
    newFilteredMeasurements = false;
    // Print the measurements nicely
    Serial.print("S");
    for (int i = 0; i < NUM_OF_SENSORS; i++) {
      Serial.print(",");
      Serial.print(filteredMeasurements[i]);
    }
    Serial.println(",");
   // digitalWrite(blinkOutLED,LOW);
  }
  

  
  getLatestSerialData();
  directionSelect();
}

void printErrCode(I2C_ERROR_CODE err){

    if(err == NO_ERROR) Serial.println("NO_ERROR");
    if(err == IN_STANDBY) Serial.println("IN_STANDBY");
    if(err == INCOMPLETE_MEASUREMENT) Serial.println("INCOMPLETE_MEASUREMENT");

}


void directionSelect(){
  if( UP_BUTTON) {
  goNorth();
} else if (DOWN_BUTTON) {
  goSouth();
}else if (LEFT_BUTTON) {
  goWest();
}else if (RIGHT_BUTTON) {
  goEast();
}else if (L_TRIG) {
  spinCCW();
}else if (R_TRIG) {
  spinCW();
} else {
  noMov();
}
}



/**
   ISR that raises a flag whenever SonicDisc is ready to transmit new data.
*/
void newSonicDiscData() {
  newData = true;
}

