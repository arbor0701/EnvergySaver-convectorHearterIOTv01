#pragma once
#include "DataModel.h"
#include <ArduinoJson.h>

void Data_to_json(SENSOR_data_BME280 *sensor_data, JSON_FORM *jsonFormContainer);