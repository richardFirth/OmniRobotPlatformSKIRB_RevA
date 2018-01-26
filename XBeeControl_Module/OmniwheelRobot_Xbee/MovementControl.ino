// ?

// the robot only goes NORTH EAST WEST SOUTH.
// this could be greatly expanded by adding other compassess and creating options to vary speed
// when i tested this the movement was 'satisfying' and seemed intuative to me, so i kept it simple.


void movementLoop()
{
    if (UP_BUTTON) {
      OmniBot.goNorth();
    } else if (DOWN_BUTTON){
      OmniBot.goSouth();
    } else if (LEFT_BUTTON){
      OmniBot.goWest();
    } else if (RIGHT_BUTTON){
      OmniBot.goEast();
    } else if (L_TRIG) {
      OmniBot.rotateCCW();
    } else if (R_TRIG) {
      OmniBot.rotateCW();
    } else {
      OmniBot.stopRobot();
    }

}

