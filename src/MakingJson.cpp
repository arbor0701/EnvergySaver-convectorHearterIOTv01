#include "MakingJson.h"
#include <math.h>

const int16_t jsonFormContainerSize = JSON_OBJECT_SIZE(10) + 100;
StaticJsonDocument<120> objectFormContainer;

// void Data_to_json(SENSOR_data *sensor_data, JSON_FORM *jsonFormContainer)
// {
//   objectFormContainer["SHT31_TEMP"] = round(sensor_data->SHT31_TEMP * 100.0) / 100.0;
//   objectFormContainer["SHT31_HUMID"] = round(sensor_data->SHT31_HUMID * 100.0) / 100.0;
//   objectFormContainer["Switch1State"] = sensor_data->Switch1State;
//   objectFormContainer["Switch2State"] = sensor_data->Switch2State;
//   ArduinoJson::serializeJson(objectFormContainer, jsonFormContainer->jsonFormContainer);
//   jsonFormContainer->jsonFormContainer[jsonFormContainerSize - 1] = '\0';
// }

void Data_to_json(SENSOR_data_BME280 *sensor_data, JSON_FORM *jsonFormContainer)
{
  objectFormContainer["SHT31_TEMP"] = round(sensor_data->BME280_TEMP * 100.0) / 100.0;
  objectFormContainer["SHT31_HUMID"] = round(sensor_data->BME280_HUMID * 100.0) / 100.0;
  objectFormContainer["Switch1State"] = sensor_data->Switch1State;
  objectFormContainer["Switch2State"] = sensor_data->Switch2State;
  ArduinoJson::serializeJson(objectFormContainer, jsonFormContainer->jsonFormContainer);
  jsonFormContainer->jsonFormContainer[jsonFormContainerSize - 1] = '\0';
}