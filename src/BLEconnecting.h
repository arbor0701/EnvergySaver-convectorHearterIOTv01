#pragma once
#include "DataModel.h"
#include "MakingJson.h"

void Ble_v03_setup();
String Ble_v03_loop_read();
void Ble_v03_loop_write(SENSOR_data_BME280 *sensorData);
