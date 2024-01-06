#include "VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

VL53L0X::VL53L0X(){
}

void VL53L0X::check_start(){
    while (! Serial) {
    delay(1);
  }
 
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

bool VL53L0X::measure(int min_distance, int num_of_measurements){
  VL53L0X_RangingMeasurementData_t measure;
  int tmp_measurement=0;
  bool enought_dist=false;
  //Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    for(int i=0;i<num_of_measurements;i++){
      tmp_measurement = tmp_measurement + measure.RangeMilliMeter/num_of_measurements;
    }
    
    Serial.print("Distance (mm): "); 
    Serial.println(tmp_measurement);
    if(tmp_measurement <= min_distance)
      enought_dist=true;
  }
   
  delay(100);
  return enought_dist;
}