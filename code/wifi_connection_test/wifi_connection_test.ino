#include <WiFi.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

void setup()
{
  Serial.begin(115200);

  Serial.println("ESP32 Wi-Fi connection test started");
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected successfully");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  
}