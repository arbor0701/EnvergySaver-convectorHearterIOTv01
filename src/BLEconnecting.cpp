#include "BLEconnecting.h"
#include "ArduinoBLE.h"

BLEService Mkr1010Service("49B10000-E8F2-537E-4F6C-D104768A1214");
BLEStringCharacteristic Mkr1010Characteristic_read("49B10001-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite, 512);
BLEStringCharacteristic Mkr1010Characteristic_write("49B10001-E8F2-537E-4F6C-D104768A1216", BLERead | BLENotify, 512);
BLEUnsignedCharCharacteristic secretValue("49B10001-E8F2-537E-4F6C-D104768A1217", BLERead | BLEWrite);

unsigned long previousMillis = 0; // last time the battery level was checked, in ms
unsigned long pairingStarted = 0; // pairing start time when button is pressed

void Ble_v03_setup()
{
  // while (!Serial)
  //   ;

  while (1)
  {
    // begin initialization
    if (!BLE.begin())
    {
      Serial.println("starting BLE failed!");
      delay(200);
      continue;
    }
    Serial.println("BT init");
    delay(200);

    BLE.setDeviceName("MKR1010_01");
    // BLE.setLocalName("Mkr1010");
    BLE.setAdvertisedService(Mkr1010Service);
    Mkr1010Service.addCharacteristic(Mkr1010Characteristic_read);
    Mkr1010Service.addCharacteristic(Mkr1010Characteristic_write);
    Mkr1010Service.addCharacteristic(secretValue);

    BLE.addService(Mkr1010Service);
    secretValue.writeValue(0);
    delay(1000);

    Mkr1010Characteristic_write.writeValue("Hello World 6 from Mkr1010");
    BLE.advertise();
    if (!BLE.advertise())
    {
      Serial.println("failed to advertise bluetooth.");
      BLE.stopAdvertise();
      delay(500);
    }
    else
    {
      Serial.println("advertising...");
      break;
    }
    BLE.end();
    delay(100);
  }
  Serial.println("BLE Mkr1010 Peripheral");
}

String Ble_v03_loop_read()
{
  BLEDevice central = BLE.central();

  if (central.connected())
  {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    if (Mkr1010Characteristic_read.written())
    {
      return (String(Mkr1010Characteristic_read.value()));
    }
    else
    {
      return "no data";
    }
  }
  else
  {
    Serial.println("Disconnected from central");
    return "disconnected";
  }

  // or any other default value you want to return
}

JSON_FORM jsonForm;
void Ble_v03_loop_write(SENSOR_data_BME280 *sensorData)
{
  BLEDevice central = BLE.central();

  if (central && central.connected())
  {

    // check the battery level every 200ms
    // while the central is connected:
    long currentMillis = millis();
    // if 200ms have passed, check the battery level:
    if (currentMillis - previousMillis >= 1000)
    {
      previousMillis = currentMillis;
      Data_to_json(sensorData, &jsonForm);
      String sensorDataString = jsonForm.jsonFormContainer;
      Mkr1010Characteristic_write.writeValue(sensorDataString);
    }
  }
}
