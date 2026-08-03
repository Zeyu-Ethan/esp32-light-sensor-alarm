// ESP32 Light Sensor Alarm System
// V3 Wi-Fi Web Server Test

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

void handleHomePage()
{
  server.send(200, "text/html", "<h1>ESP32 Web Server Test</h1><p>Wi-Fi web server is working.</p>");
}

void setup()
{
  Serial.begin(115200);

  Serial.println("ESP32 Wi-Fi web server test started");
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

  server.on("/", handleHomePage);
  server.begin();

  Serial.println("Web server started");
}

void loop()
{
  server.handleClient();
}