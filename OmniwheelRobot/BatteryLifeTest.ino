void testLowVoltage(int rawPinRead)
{
  if (rawPinRead < lowVoltageSetting)
  {
    lowVoltageAlarm();
  }

  if (!JoystickBatteryGood) // if the joystick battery is bad, alert the user and stop.
  {
    while(1)
    {
      digitalWrite(BlueLED,HIGH);
      delay(50);
      digitalWrite(BlueLED,LOW);
      delay(50);
    }
  }
  
}

void lowVoltageAlarm() // if the main battery is bad, alert the user and stop.
{
    digitalWrite(PWM_1,0);
    digitalWrite(PWM_2,0);
    digitalWrite(PWM_3,0);
    digitalWrite(PWM_4,0);
    // make cool looping thingy with LEDS to show low battery (robot)
  while(1){ 
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
float vBattFromRead(int theRead)
{
  float vPinLoc =  5.0*float(theRead)/1023.0;
  return dividerRatio()*vPinLoc;
}

float vPin(int theRead)
{
  return 5.0*float(theRead)/1023.0;
}

float vBatt(float vPin)
{
  return  dividerRatio()*vPin;
}

float dividerRatio()
{
return (R_Batt + R_GND) /R_GND ;
}
*/


