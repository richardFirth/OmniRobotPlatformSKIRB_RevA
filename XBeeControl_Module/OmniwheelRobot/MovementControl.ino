// ?

// the robot only goes NORTH EAST WEST SOUTH.
// this could be greatly expanded by adding other compassess and creating options to vary speed
// when i tested this the movement was 'satisfying' and seemed intuative to me, so i kept it simple.


void movementLoop()
{
  if (mySerialReceiver.UP_BUTTON) {
    OmniBot.goNorth();
  } else if (mySerialReceiver.DOWN_BUTTON) {
    OmniBot.goSouth();
  } else if (mySerialReceiver.LEFT_BUTTON) {
    OmniBot.goWest();
  } else if (mySerialReceiver.RIGHT_BUTTON) {
    OmniBot.goEast();
  } else if (mySerialReceiver.L_TRIG) {
    OmniBot.rotateCCW();
  } else if (mySerialReceiver.R_TRIG) {
    OmniBot.rotateCW();
  } else {
    OmniBot.stopRobot();
  }

}

