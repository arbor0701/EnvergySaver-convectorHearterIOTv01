
#include <Arduino.h>
#include "SHT31controlling.h"
#include "MakingJson.h"
#include "BLEconnecting.h"
#include <FlashStorage.h>
#include "BME280controlling.h"

struct MySettingData
{
  float tempSet;
  float humidSet;
};
#define switch1 7
#define switch2 8

FlashStorage(myEEPROMData, MySettingData);
SENSOR_data sensor_data;
SENSOR_data_BME280 sensor_data_BME280;
MySettingData settingDataFromCentral;
MySettingData dataSetFromEEPROM = myEEPROMData.read();
StaticJsonDocument<200> jsonFromCentral;
String jsonStringFromCentral;
float tempSet;
float humidSet;

void setup()
{
  Serial.begin(9600);
  SHT31controllingSetup();
  Ble_v03_setup();
  tempSet = dataSetFromEEPROM.tempSet;
  humidSet = dataSetFromEEPROM.humidSet;
  BME280_sensor_setup();
  pinMode(switch1, OUTPUT);
  // Callback function with confirmation code when new device is pairing.
}

void loop()
{
  SHT31controllingReading(&sensor_data);
  // Data_to_json(&sensor_data, &jsonForm);
  // Serial.println(jsonForm.jsonFormContainer);
  // Ble_v03_loop_read();
  // Ble_v03_loop_read();
  BME280_sensor_loop(&sensor_data_BME280);
  jsonStringFromCentral = Ble_v03_loop_read();
  if (jsonStringFromCentral != "no data")
  {

    if (jsonStringFromCentral == "on")
    {
      Serial.println("on");
    }
    else if (jsonStringFromCentral == "ofddddf")
    {
      Serial.println("off");
      digitalWrite(switch1, HIGH);
    }
    else
    {
      deserializeJson(jsonFromCentral, jsonStringFromCentral);
      settingDataFromCentral.tempSet = jsonFromCentral["Temp"];
      settingDataFromCentral.humidSet = jsonFromCentral["Humid"];
      myEEPROMData.write(settingDataFromCentral);

      tempSet = myEEPROMData.read().tempSet;
      humidSet = myEEPROMData.read().humidSet;
    }
  }
  else if (jsonStringFromCentral == "disconnected")
  {
    Serial.println("disconnected");
    digitalWrite(switch1, HIGH);
  }
  Serial.print("Temp set: ");
  Serial.print(myEEPROMData.read().tempSet);
  Serial.print("saved Temp set:   ");
  Serial.print(dataSetFromEEPROM.tempSet);
  Serial.println(" C");
  Serial.print("Hum set: ");
  Serial.print(myEEPROMData.read().humidSet);
  Serial.print("saved Hum set:   ");
  Serial.print(dataSetFromEEPROM.humidSet);
  Serial.println("%");
  // Ble_v03_loop_write(&sensor_data);
  Ble_v03_loop_write(&sensor_data_BME280);
  // String to data
  String data = Ble_v03_loop_read();
  Serial.println(data);

  if (sensor_data.SHT31_TEMP > tempSet)
  {
    Serial.println("Temp is higher than the set value");
    sensor_data.Switch1State = 0;

    digitalWrite(switch1, HIGH);
  }
  else
  {
    Serial.println("Temp is lower than the set value");
    sensor_data.Switch1State = 1;
    digitalWrite(switch1, LOW);
  }
  if (sensor_data.SHT31_HUMID > humidSet)
  {
    Serial.println("Humid is higher than the set value");
    sensor_data.Switch2State = 0;
  }
  else
  {
    Serial.println("Humid is lower than the set value");
    sensor_data.Switch2State = 1;
  }

  delay(1000);
}
