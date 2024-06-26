#pragma once

#include <WiFiNINA.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
// WiFi network name and password:
void WIFI_connect_setting();
void NetworkInfo_print();
void MQTT_connect_setting();