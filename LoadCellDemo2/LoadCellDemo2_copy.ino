#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

// float for current value
float currentVal;
// float for time
int time;
// float of how much the scale is naturally off by
float calibrateVal;
// array for storing recent data over last 100 raw values
float lastHundredRaw[100];
// counter for last 100 raw values to tell which one it is
int rawCounter;
// array for averages of data over longer amount of time

// note: a pound is about 600000-605000
// verfied with 2lbs, 2.5lbs
// seems to fritz out greater than that (i.e. 5 pounds was off)

/**
 * Next steps:
 * Go to BDW, design better scale
 * Calibrate for pounds / grams
 * Write code that takes a difference and records weight
 */

/**
 * setup method
 * prints out message and resets values
 */
void setup() {
  Serial.begin(9600);
  Serial.println("After readings begin, place known weight on scale");
  resetTime();
  resetStoredValues();
  calibrate();
}

/**
 * method to zero the scale
 */
void calibrate() {
  Serial.println("calibrating...");
  calibrateVal = 0;
  for (int i = 0; i < 10; i++) {
    calibrateVal += scale.read();
  }
  calibrateVal = calibrateVal / 10;
  Serial.println("calibrated");
}

/**
 * method to reset all values of data stored
 */
void resetStoredValues() {
  for(int i = 0; i < 100; i++) {
    lastHundredRaw[i] = -1;
  }
  rawCounter = 0;
}

/**
 * method to reset time
 * set to 1 to avoid div by 0 errors
 */
void resetTime() {
  time = 1;
}

/**
 * TODO:
 * add functionality that
 * - saves recent data to the array
 * - calls concatData
 */

/**
 * loop:
 * get the currentVal using one of three methods
 * print value
 * save the value
 * calibrate if 'c' is entered
 * increment the time & raw counter
 */
void loop() {  
  // Use only one of these
  //currentVal = ((time-1)/time) * currentVal +  (1/time) * cell.read(); // take long term average
  //currentVal = (0.5 * currentVal + 0.5 * scale.read()); // take recent average
  currentVal = scale.read(); // most recent reading

  currentVal = currentVal - calibrateVal;
  
  Serial.println("The reading is:");
  
  Serial.println(currentVal); // this is the calibrated val
  // divide by 600000 to get value in lbs

  // save the value to rawData array
  lastHundredRaw[rawCounter] = currentVal;
  
  // recalibrate if the letter c is entered
  // will delay reading by about half a second
  if(Serial.available())
  {
    char input = Serial.read();
    if(input == 'c')
      calibrate();
  }
  time++;
  rawCounter++;
}

/**
 * TODO:
 * function that concatenates data so that we have averages over time
 * this data will be used to determine longer time weight changes
 */

/**
 * TODO:
 * function that looks at averages over time and calculates 
 * differences to get the weight of the discharge
 */

/**
 * TODO:
 * function that checks when someone has sat down
 */

/**
 * TODO:
 * function that checks when someone has stood up
 * calculate weight of discharge
 * if incalculatable, print that message
 * if not, push to leaderboard
 */