#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

float calibrateVal;

// note: a pound is about 600000-605000
// verfied with 2lbs, 2.5lbs

/**
 * Next steps:
 * Go to BDW, design better scale
 * Calibrate for pounds / grams
 * Write code that takes a difference and records weight
 * 

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
