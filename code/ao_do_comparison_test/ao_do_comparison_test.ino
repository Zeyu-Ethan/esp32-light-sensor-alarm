// ESP32 Light Sensor Alarm System
// V2 AO vs DO Comparison Test

const int ldrAoPin = 34;  // LDR module AO connected to GPIO34.
const int ldrDoPin = 35;  // LDR module DO connected to GPIO35.

void setup()
{
  pinMode(ldrAoPin, INPUT);
  pinMode(ldrDoPin, INPUT);

  Serial.begin(115200);

  Serial.println("AO vs DO Comparison Test started");
}

void loop()
{
  int ldrAoValue = analogRead(ldrAoPin);
  int ldrDoValue = digitalRead(ldrDoPin);

  Serial.print("LDR AO value: ");
  Serial.print(ldrAoValue);

  Serial.print(" | LDR DO state: ");

  if (ldrDoValue == HIGH)
  {
    Serial.println("HIGH");
  }
  else
  {
    Serial.println("LOW");
  }

  delay(500);
}