
/**
   Sends the supplied byte to the SonicDisc
   @param byteToSend The byte to be sent
*/
void sendDataToSonic(uint8_t byteToSend) {
  Wire.beginTransmission(SONIC_DISC_I2C_ADDRESS);
  Wire.write(byteToSend);
  Wire.endTransmission(SONIC_DISC_I2C_ADDRESS);
}

void sendDataToOmni(byte byteToSend) {
  Wire.beginTransmission(MOTOR_I2C_ADDRESS);
  Wire.write(byteToSend);
  Wire.endTransmission(MOTOR_I2C_ADDRESS);
}

void getBatteryVal(){
  Wire.requestFrom(14, 1);
  
  while (Wire.available()) { // slave may send less than requested
    int a = Wire.read(); // receive a byte as character

    Serial.println(a);
  }
  
}









/**
   ISR that raises a flag whenever SonicDisc is ready to transmit new data.
*/
/*
void newSonicDiscData() {
  newData = true;
}
*/


