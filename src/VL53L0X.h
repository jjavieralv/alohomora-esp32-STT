#ifndef _VL53L0X_H
#define _VL53L0X_H

#include "Adafruit_VL53L0X.h"


class VL53L0X {
  public:
    VL53L0X();
    void check_start();
    bool measure(int min_distance, int num_of_measurements);
};

#endif