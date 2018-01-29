/*
   Adds the specified i2c packet in the buffer to be sorted later.
*/
void addInputToFilterBuffer(uint8_t i2cInput[], const uint8_t bufferIndex) {
  // Copy the whole packet (except error code) in the specified row of the buffer
  for (int i = 0, j = 1; i < NUM_OF_SENSORS; i++, j++) {
    filterBuffer[bufferIndex][i] = i2cInput[j];
  }
}

/*
    Sorts the measurements of each sensor for every cycle of measurements.
*/
void sortMeasurements() {
  // For each sensor
  for (int s = 0; s < NUM_OF_SENSORS; s++) {
    // Use bubble sort to sort all measurements throughout the cycle
    for (int i = 0; i < MEASUREMENTS_TO_FILTER - 1; i++) {
      for (int j = 0; j < MEASUREMENTS_TO_FILTER - i - 1; j++) {
        if (filterBuffer[j][s] > filterBuffer[j + 1][s]) {
          uint8_t toSwap = filterBuffer[j][s];
          filterBuffer[j][s] = filterBuffer[j + 1][s];
          filterBuffer[j + 1][s] = toSwap;
        }
      }
    }
  }
}

/*
    Filter measurements depending on the variance.
    If variance is too high for a MEASUREMENTS_TO_FILTER measurements of a sensor
    then these measurements are disregarded. Otherwise the mean value is chosen.
*/
void filterMeasurements() {
  // Go through all the measurements taken for each sensor
  for (int i = 0; i < NUM_OF_SENSORS; i++) {
    // Calculate the variance across the different measurements
    // by subtracting the first and the last element
    // of the *sorted* measurement cycle.
    int variance = filterBuffer[0][i] - filterBuffer[MEASUREMENTS_TO_FILTER - 1][i];
    if (abs(variance) > VARIANCE_THRESHOLD) {
      filteredMeasurements[i] = 0;
    } else {
      filteredMeasurements[i] = filterBuffer[MEASUREMENTS_TO_FILTER / 2][i];
    }
  }
}
