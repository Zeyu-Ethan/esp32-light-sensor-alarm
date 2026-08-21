// ESP32 Light Sensor Alarm System
// V3 Integrated alarm logic with local web monitoring
// Includes Wi-Fi connection timeout handling

#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

// Pin assignment.
const int ldrPin = 34;            // LDR module AO connected to GPIO34.
const int ledPin = 25;            // External LED connected to GPIO25.
const int buzzerPin = 27;         // ESPBlock onboard buzzer controlled by GPIO27.
const int alarmSwitchPin = 26;    // DIP switch 1: alarm enable control.
const int buzzerSwitchPin = 32;   // DIP switch 2: buzzer enable / mute control.
const int ledSwitchPin = 33;      // DIP switch 3: LED enable control.

// Alarm configuration.
const int threshold = 2000;               // ADC threshold for detecting a dark condition.
const unsigned long confirmDelay = 1000;  // Time required to confirm a dark condition.
const unsigned long updateInterval = 500; // Main sensor update interval.

// Wi-Fi configuration.
const unsigned long wifiTimeout = 20000;  // Maximum Wi-Fi connection wait time: 20 seconds.

// Web server on default HTTP port 80.
WebServer server(80);

// System state variables.
int ldrValue = 0;

bool alarmSwitchState = false;
bool buzzerSwitchState = false;
bool ledSwitchState = false;

bool darkCondition = false;
bool alarmTriggered = false;
bool ledOutputState = false;
bool buzzerOutputState = false;

// Records whether Wi-Fi connected and the web server started successfully.
bool wifiConnected = false;

// Variables used for non-blocking dark-condition confirmation.
bool darkTimingStarted = false;
unsigned long darkStartTime = 0;
unsigned long lastUpdateTime = 0;

// Function prototype for Python data output.
void printPythonData();

void updateAlarmSystem()
{
  ldrValue = analogRead(ldrPin);

  alarmSwitchState = digitalRead(alarmSwitchPin);
  buzzerSwitchState = digitalRead(buzzerSwitchPin);
  ledSwitchState = digitalRead(ledSwitchPin);

  // If the main alarm switch is OFF, disable all alarm outputs.
  if (alarmSwitchState == LOW)
  {
    darkCondition = false;
    alarmTriggered = false;
    ledOutputState = false;
    buzzerOutputState = false;
    darkTimingStarted = false;

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH); // Active-low buzzer: HIGH means OFF.

    printPythonData();

    return;
  }

  // Confirm that the dark condition lasts long enough before triggering.
  if (ldrValue > threshold)
  {
    if (darkTimingStarted == false)
    {
      darkTimingStarted = true;
      darkStartTime = millis();
    }

    if (millis() - darkStartTime >= confirmDelay)
    {
      darkCondition = true;
      alarmTriggered = true;
    }
    else
    {
      darkCondition = false;
      alarmTriggered = false;
    }
  }
  else
  {
    darkCondition = false;
    alarmTriggered = false;
    darkTimingStarted = false;
  }

  // Control the LED according to the alarm and LED switch states.
  if (alarmTriggered == true && ledSwitchState == HIGH)
  {
    ledOutputState = true;
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    ledOutputState = false;
    digitalWrite(ledPin, LOW);
  }

  // Control the active-low buzzer.
  if (alarmTriggered == true && buzzerSwitchState == HIGH)
  {
    buzzerOutputState = true;
    digitalWrite(buzzerPin, LOW); // Active-low buzzer: LOW means ON.
  }
  else
  {
    buzzerOutputState = false;
    digitalWrite(buzzerPin, HIGH); // Active-low buzzer: HIGH means OFF.
  }

  Serial.print("LDR AO value: ");
  Serial.print(ldrValue);

  Serial.print(" | Alarm switch: ");
  Serial.print(alarmSwitchState == HIGH ? "ON" : "OFF");

  Serial.print(" | LED switch: ");
  Serial.print(ledSwitchState == HIGH ? "ON" : "OFF");

  Serial.print(" | Buzzer switch: ");
  Serial.print(buzzerSwitchState == HIGH ? "ON" : "MUTED");

  Serial.print(" | Alarm status: ");
  Serial.println(alarmTriggered == true ? "TRIGGERED" : "NORMAL");

  printPythonData();
}

String getOnOffText(bool state)
{
  if (state == true)
  {
    return "ON";
  }
  else
  {
    return "OFF";
  }
}

String getAlarmStatusText()
{
  if (alarmSwitchState == LOW)
  {
    return "Alarm Disabled";
  }

  if (alarmTriggered == true)
  {
    return "Alarm Triggered";
  }

  return "Normal";
}

String getLightConditionText()
{
  if (darkCondition == true)
  {
    return "Dark";
  }
  else
  {
    return "Light";
  }
}

void printPythonData()
{
  /*
    This function prints one structured data line for the Python serial data logger.

    Format:
    DATA,LDR value,Light condition,Alarm status,Alarm switch,LED switch,
    Buzzer switch,LED output,Buzzer output
  */

  Serial.print("DATA,");
  Serial.print(ldrValue);
  Serial.print(",");
  Serial.print(getLightConditionText());
  Serial.print(",");
  Serial.print(getAlarmStatusText());
  Serial.print(",");
  Serial.print(alarmSwitchState == HIGH ? "ON" : "OFF");
  Serial.print(",");
  Serial.print(ledSwitchState == HIGH ? "ON" : "OFF");
  Serial.print(",");
  Serial.print(buzzerSwitchState == HIGH ? "ON" : "MUTED");
  Serial.print(",");
  Serial.print(ledOutputState == true ? "ON" : "OFF");
  Serial.print(",");
  Serial.println(buzzerOutputState == true ? "ON" : "OFF");
}

void handleHomePage()
{
  String html = "";

  html += "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ESP32 Light Sensor Alarm System</title>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 30px; }";
  html += "h1 { color: #222; }";
  html += "table { border-collapse: collapse; width: 420px; }";
  html += "td, th { border: 1px solid #ccc; padding: 8px; text-align: left; }";
  html += "th { background-color: #f2f2f2; }";
  html += "</style>";
  html += "</head>";

  html += "<body>";
  html += "<h1>ESP32 Light Sensor Alarm System</h1>";
  html += "<h2>Local Wi-Fi Alarm Monitoring</h2>";

  html += "<table>";
  html += "<tr><th>Parameter</th><th>Status</th></tr>";

  html += "<tr><td>LDR AO Value</td><td>";
  html += ldrValue;
  html += "</td></tr>";

  html += "<tr><td>Light Condition</td><td>";
  html += getLightConditionText();
  html += "</td></tr>";

  html += "<tr><td>Alarm Status</td><td>";
  html += getAlarmStatusText();
  html += "</td></tr>";

  html += "<tr><td>Alarm Switch</td><td>";
  html += alarmSwitchState == HIGH ? "ON" : "OFF";
  html += "</td></tr>";

  html += "<tr><td>LED Switch</td><td>";
  html += ledSwitchState == HIGH ? "ON" : "OFF";
  html += "</td></tr>";

  html += "<tr><td>Buzzer Switch</td><td>";
  html += buzzerSwitchState == HIGH ? "ON" : "MUTED";
  html += "</td></tr>";

  html += "<tr><td>LED Output</td><td>";
  html += getOnOffText(ledOutputState);
  html += "</td></tr>";

  html += "<tr><td>Buzzer Output</td><td>";
  html += getOnOffText(buzzerOutputState);
  html += "</td></tr>";

  html += "</table>";

  html += "<p>This page refreshes automatically every 2 seconds.</p>";
  html += "<p>Only devices on the same local Wi-Fi network can access this page.</p>";

  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void setup()
{
  pinMode(ldrPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(alarmSwitchPin, INPUT);
  pinMode(buzzerSwitchPin, INPUT);
  pinMode(ledSwitchPin, INPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, HIGH); // Active-low buzzer starts OFF.

  Serial.begin(115200);

  Serial.println("ESP32 Wi-Fi alarm monitoring system started");
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for Wi-Fi, but stop waiting after the timeout period.
  unsigned long wifiStartTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - wifiStartTime < wifiTimeout)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    wifiConnected = true;

    Serial.println("Wi-Fi connected successfully");

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleHomePage);
    server.begin();

    Serial.println("Web server started");
  }
  else
  {
    wifiConnected = false;

    Serial.println("Wi-Fi connection failed after 20 seconds.");
    Serial.println();
    Serial.println("Please check:");
    Serial.println("- The Wi-Fi name and password are correct.");
    Serial.println("- The router or mobile hotspot is turned on.");
    Serial.println("- The ESP32 is within Wi-Fi range.");
    Serial.println();
    Serial.println("Web monitoring is unavailable.");
    Serial.println("The hardware alarm and serial DATA output will continue running.");
    Serial.println();
    Serial.println("After fixing the Wi-Fi connection, press the ESP32 RESET button to try again.");
  }
}

void loop()
{
  // Handle web requests only if Wi-Fi connected and the server was started.
  if (wifiConnected == true)
  {
    server.handleClient();
  }

  // The alarm system runs whether Wi-Fi is available or not.
  if (millis() - lastUpdateTime >= updateInterval)
  {
    lastUpdateTime = millis();
    updateAlarmSystem();
  }
}