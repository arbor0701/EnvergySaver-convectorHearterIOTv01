#include "SHT31controlling.h"

SHT31 sht31 = SHT31();

void SHT31controllingSetup()
{
  // put your setup code here, to run once:
  // while (!Serial)
  //   ;
  sht31.begin();
}

void SHT31controllingReading(SENSOR_data *sensor_data)
{
  // put your main code here, to run repeatedly:
  float temp = sht31.getTemperature();
  float hum = sht31.getHumidity();
  sensor_data->SHT31_TEMP = temp;
  sensor_data->SHT31_HUMID = hum;

  Serial.print("Temp = ");
  Serial.print(temp);
  Serial.println(" C"); // The unit for  Celsius because original arduino don't support speical symbols
  Serial.print("Hum = ");
  Serial.print(hum);
  Serial.println("%");
  Serial.println();
}