#pragma once

#include "Seeed_BME280.h"
#include "DataModel.h"

void BME280_sensor_setup();
void BME280_sensor_loop(SENSOR_data_BME280 *sensor_data);