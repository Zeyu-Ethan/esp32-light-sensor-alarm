// ESP32 Light Sensor Alarm System
// V3 Move Wi-Fi credentials to ignored secrets file

#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

const int ldrPin = 34;       // LDR module AO connected to GPIO34.

const int threshold = 2000;  // ADC threshold for detecting a dark condition.

WebServer server(80);        // Create a web server on the default HTTP port 80.

void handleHomePage()
{
  // Read the latest LDR value when the browser requests the page.
  int ldrValue = analogRead(ldrPin);

  String lightCondition;

  if (ldrValue > threshold)
  {
    lightCondition = "Dark";
  }
  else
  {
    lightCondition = "Light";
  }

  // Build a simple HTML page to display the sensor reading.
  String html = "";

  html += "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ESP32 Light Sensor Alarm System</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ESP32 Light Sensor Alarm System</h1>";
  html += "<h2>Local Web Monitoring</h2>";

  html += "<p><strong>LDR AO Value:</strong> ";
  html += ldrValue;
  html += "</p>";

  html += "<p><strong>Light Condition:</strong> ";
  html += lightCondition;
  html += "</p>";

  html += "<p>Refresh the page to update the sensor reading.</p>";
  html += "</body>";
  html += "</html>";

  // Send the generated HTML page back to the browser.
  server.send(200, "text/html", html);
}

void setup()
{
  pinMode(ldrPin, INPUT);

  Serial.begin(115200);

  Serial.println("ESP32 Wi-Fi light sensor monitoring test started");
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

  // Run handleHomePage() when a browser visits the root page "/".
  server.on("/", handleHomePage);

  server.begin();

  Serial.println("Web server started");
}

void loop()
{
  // Keep checking for browser requests.
  server.handleClient();
}