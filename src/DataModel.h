#pragma once

typedef struct
{
  float SHT31_TEMP;
  float SHT31_HUMID;
  int Switch1State;
  int Switch2State;

} SENSOR_data;

typedef struct
{
  float BME280_TEMP;
  float BME280_HUMID;
  float BME280_PRESSURE;
  float BME280_ALTITUDE;
  int Switch1State;
  int Switch2State;

} SENSOR_data_BME280;
struct JSON_FORM
{
  char jsonFormContainer[100] = ""; // specify a size for the array
};