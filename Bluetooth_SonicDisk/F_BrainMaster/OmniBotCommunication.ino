/*
 *  7: always 0
 *  6: Joystick button state
 *  5: Left Trigger State
 *  4: Right trigger state
 *  3: up button state
 *  2: down button state
 *  1: left button state
 *  0: right button state
 *  
  */

void goNorth(){
   sendDataToOmni(customByte(false,false,false,false,true,false,false,false));
}

void goSouth(){
   sendDataToOmni(customByte(false,false,false,false,false,true,false,false));
}

void goEast(){
   sendDataToOmni(customByte(false,false,false,false,false,false,false,true));
}

void goWest(){
   sendDataToOmni(customByte(false,false,false,false,false,false,true,false));
}

void spinCW(){
   sendDataToOmni(customByte(false,false,false,true,false,false,false,false));
}

void spinCCW(){
   sendDataToOmni(customByte(false,false,true,false,false,false,false,false));
}
void noMov(){
   sendDataToOmni(customByte(false,false,false,false,false,false,false,false));
}


void adjustSpeed(int sp){
  if (sp == 0) sendDataToOmni(customByte(true,false,false,true,false,false,false,false));
  if (sp == 1) sendDataToOmni(customByte(true,false,true,false,false,false,false,false));
  if (sp == 2) sendDataToOmni(customByte(true,true,false,true,false,false,false,false));
}








