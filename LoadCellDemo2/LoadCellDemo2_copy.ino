#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

// float of how much the scale is naturally off by
float calibrateVal;
// array for storing recent data over time
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


void setup() {
  Serial.begin(9600);
  Serial.println("After readings begin, place known weight on scale");
  calibrate();
}

void calibrate() {
  Serial.println("calibrating...");
  calibrateVal = 0;
  for (int i = 0; i < 10; i++) {
    calibrateVal += scale.read();
  }
  calibrateVal = calibrateVal / 10;
  Serial.println("calibrated");
}

long val = 0;
float count = 0;

/**
 * TODO:
 * add functionality that
 * - saves recent data to the array
 * - calls concatData
 */

void loop() {
  count = count + 1;
  
  // Use only one of these
  //val = ((count-1)/count) * val    +  (1/count) * cell.read(); // take long term average
  //val = (0.5 * val    +   0.5 * scale.read()); // take recent average
  val = scale.read(); // most recent reading
  
  Serial.println("Printing val");
  
  Serial.println(val - calibrateVal);
  
  if(Serial.available())
  {
    char input = Serial.read();
    if(input == 'c')
      calibrate();
  }

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