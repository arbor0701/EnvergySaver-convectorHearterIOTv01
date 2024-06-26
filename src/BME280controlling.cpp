#include "BME280controlling.h"

BME280 bme280;

void BME280_sensor_setup()
{
  if (!bme280.init())
  {
    Serial.println("Device error!");
  }
}

void BME280_sensor_loop(SENSOR_data_BME280 *sensor_data)
{

  float temp = 1.0;
  float humid = 1.0;
  float pressure = 1.0;
  float altitude = 1.0;

  temp = bme280.getTemperature();
  humid = bme280.getHumidity();
  pressure = bme280.getPressure();
  altitude = bme280.calcAltitude(pressure);

  sensor_data->BME280_TEMP = temp;
  sensor_data->BME280_HUMID = humid;
  sensor_data->BME280_PRESSURE = pressure;
  sensor_data->BME280_ALTITUDE = altitude;

  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>BME280 sensor<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("C, Humidity: ");
  Serial.print(humid);
  Serial.print("%, Pressure: ");
  Serial.print(pressure);
  Serial.println("Pa");
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("m");
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>BME280 sensor<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
}