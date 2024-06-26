#pragma once
#include <Wire.h>
#include "SHT31.h"
#include "DataModel.h"

void SHT31controllingSetup();
void SHT31controllingReading(SENSOR_data *sensor_data);