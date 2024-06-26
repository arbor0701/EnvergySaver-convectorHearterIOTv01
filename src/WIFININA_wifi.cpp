#include "WIFININA_wifi.h"
#include <stdexcept>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

int status = WL_IDLE_STATUS;

void WIFI_connect_setting()
{
  // Connect to WPA/WPA2 network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to network: ");

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }

  if (status == WL_CONNECTED)
  {
    Serial.println("You're connected to the network");
    Serial.println("----------------------------------------");
    NetworkInfo_print();
    Serial.println("----------------------------------------");
  }
  else
  {
    Serial.println("Connection failed");
  }
}

void NetworkInfo_print()
{
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}

void MQTT_connect_setting()
{
  // Connect to MQTT Broker
  while (!mqttClient.connected())
  {

    mqttClient.setServer(MQTT_BROKER_ADD, 1883);
    delay(1000);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("MKR1010wifi", MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("connected");
      // Subscribe
      mqttClient.subscribe("esp32/output");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying

      delay(5000);
    }
  }
}