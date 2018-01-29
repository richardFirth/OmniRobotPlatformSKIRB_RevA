
import processing.serial.*;
SerialConnector sc;
Serial myPort;

SonicRing SR;

boolean UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON,L_TRIG,R_TRIG;
boolean SPD_H,SPD_M,SPD_L;

int sonic0 = 30;
int sonic1 = 30;
int sonic2 = 30;
int sonic3 = 30;

int sonic4 = 30;
int sonic5 = 30;
int sonic6 = 30;
int sonic7 = 30;

void setup(){
 size(1800,1000);
 
 sc = new SerialConnector(this,myPort);
 SR = new SonicRing();
 sc.changeBaud();
 
  rectMode(CENTER);
  sc.listPorts();
}

void draw(){
  if (sc.isConnected){
     background(50,60,50); 
  } else {
     background(60,50,50);       
  }
  
  /*
 *  7: always 0
 *  6: Joystick button state
 *  5: Left Trigger State
 *  4: Right trigger state
 *  3: up button state
 *  2: down button state
 *  1: left button state
 *  0: right button state
*/
  //packageSent = false;
  SR.drawSonicRing(sonic0,sonic1,sonic2,sonic3,sonic4,sonic5,sonic6,sonic7);
  sc.drawToScreen();
  
  if (keyPressed) {
  
    if (UP_BUTTON) sendPackage(customByte(false,false,false,false,true,false,false,false));
    if (LEFT_BUTTON) sendPackage(customByte(false,false,false,false,false,false,true,false));
    if (DOWN_BUTTON) sendPackage(customByte(false,false,false,false,false,true,false,false)); 
    if (RIGHT_BUTTON) sendPackage(customByte(false,false,false,false,false,false,false,true));
    if (L_TRIG) sendPackage(customByte(false,false,true,false,false,false,false,false));
    if (R_TRIG) sendPackage(customByte(false,false,false,true,false,false,false,false)); 
        
     if (SPD_H) sendPackage(customByte(true,true,false,false,false,false,false,false));
     if (SPD_M) sendPackage(customByte(true,false,true,false,false,false,false,false));
     if (SPD_L) sendPackage(customByte(true,false,false,true,false,false,false,false));
    
    
    delay(10);
  } else { 
    sendPackage(customByte(false,false,false,false,false,false,false,false)); 
    resetButtons();
  }
  
}

void keyPressed() {
  sc.KeyInputforConnection(key);

  if (key == 'q') {L_TRIG = true;} else {L_TRIG = false;}
  if (key == 'e') {R_TRIG = true;} else {R_TRIG = false;}
  if (key == 'w') {UP_BUTTON = true;} else {UP_BUTTON = false;}
  if (key == 's') {DOWN_BUTTON = true;} else {DOWN_BUTTON = false;}
  if (key == 'a') {LEFT_BUTTON = true;} else {LEFT_BUTTON = false;}
  if (key == 'd') {RIGHT_BUTTON = true;} else {RIGHT_BUTTON = false;}

   if (key == 'j') {SPD_H = true;} else {SPD_H = false;}
   if (key == 'k') {SPD_M = true;} else {SPD_M = false;}
   if (key == 'l') {SPD_L = true;} else {SPD_L = false;}

}



/*

  if (isSet(aByte,7)){   // unpack joystick & batteries

  //  byte H_val = customByte(false,false,false,false,false,isSet(aByte,5),isSet(aByte,4),isSet(aByte,3));
  //  byte V_val = customByte(false,false,false,false,false,isSet(aByte,2),isSet(aByte,1),isSet(aByte,0));
  //  JoystickBatteryGood = isSet(aByte,6);
  //  horizontalValue = unpackJoystick(H_val);
  //  verticalValue = unpackJoystick(V_val);

  if (isSet(aByte,6)) OmniBot.SetRobotSpeed(225);
  if (isSet(aByte,5)) OmniBot.SetRobotSpeed(160);
  if (isSet(aByte,4)) OmniBot.SetRobotSpeed(120);
  
  }

*/



void sendPackage(byte aByte){
     sc.writeToSerial(aByte);
     //sc.writeToSerial(customByte(true,true,true,false,false,false,false,true));
     
     sc.writeToSerial(-31);
}


void resetButtons(){
  UP_BUTTON = false;
  DOWN_BUTTON = false;
  LEFT_BUTTON = false;
  RIGHT_BUTTON = false;
  L_TRIG = false;
  R_TRIG = false;
  
}