
#ifndef OmniRobot_H
#define OmniRobot_H

#include <stdint.h>
#include "Arduino.h"

class OmniRobot {
public:
    /**
     * The default constructor of OmniBot 
     */
    OmniRobot(uint8_t PWM1in, uint8_t PWM2in,uint8_t PWM3in,uint8_t PWM4in,uint8_t latchPinIn,uint8_t clockPinIn,uint8_t dataPinIn,uint8_t battVin);
    
    void welcomeSequence();
    
    void goNorth();
    void goSouth();
    void goEast();
    void goWest();
    void stopRobot();

    void rotateCW();
    void rotateCCW();
      
    uint8_t GetRobotSpeed();
    void SetRobotSpeed(uint8_t newRBTSpeed);
    void disableLowVolageAlarm(boolean activeStatus);
    
    float getBatteryVoltage();
    boolean batterySafeVoltage();
    
private:
    uint8_t OM_PWM1pin, OM_PWM2pin, OM_PWM3pin, OM_PWM4pin;
    uint8_t OM_latchPin, OM_clockPin, OM_dataPin;
    uint8_t OM_battV;
    
    uint8_t robotSpeed;
    uint8_t previousDirectionID;
    boolean disableLVA;

    void lowVoltageAlarm();
    
    void goInDirection(int theDirection, int currentDirectionID);
    void sendDataToShiftReg(int z);

  
    
};

#endif

