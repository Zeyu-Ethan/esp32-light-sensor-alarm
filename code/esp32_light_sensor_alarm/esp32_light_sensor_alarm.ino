// ESP32 Light Sensor Alarm System
// LDR Sensor Module Analog Input Test
// LDR module AO connected to GPIO34

const int ldrPin = 34;

void setup() {
  pinMode(ldrPin, INPUT);

  Serial.begin(115200);
  delay(1000);

  Serial.println("LDR analog input test started");
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  Serial.print("LDR AO value: ");
  Serial.println(ldrValue);

  delay(500);
}