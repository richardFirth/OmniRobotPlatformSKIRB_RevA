


// these are the consants that will set the outputs on the shift register to the compass direction desired.
// i calculated them using an excel file


#define rightSpin 85
#define leftSpin 170

#define NORTH 153
#define EAST 165
#define SOUTH 102
#define WEST 90

#define NE 129
#define SE 36
#define NW 24
#define SW 66





// the robot only goes NORTH EAST WEST SOUTH.
// this could be greatly expanded by adding other compassess and creating options to vary speed
// when i tested this the movement was 'satisfying' and seemed intuative to me, so i kept it simple.
void movementLoop()
{
    if (UP_BUTTON) {
    goInDirection(NORTH);
    } else if (DOWN_BUTTON){
      goInDirection(SOUTH);
    } else if (LEFT_BUTTON){
      goInDirection(WEST);
    } else if (RIGHT_BUTTON){
      goInDirection(EAST);
    } else if (L_TRIG) {
      goInDirection(leftSpin);
    } else if (R_TRIG) {
      goInDirection(rightSpin);
    } else {
      goInDirection(0);
    }

}


void goInDirection(int theDirection)
{
  if(theDirection!=0) {
    analogWrite(PWM_1,160);
    analogWrite(PWM_2,160);
    analogWrite(PWM_3,160);
    analogWrite(PWM_4,160);
  } else {
    analogWrite(PWM_1,0);
    analogWrite(PWM_2,0);
    analogWrite(PWM_3,0);
    analogWrite(PWM_4,0);
  }
  sendDataToShiftReg(theDirection);
  delay(25);
}

