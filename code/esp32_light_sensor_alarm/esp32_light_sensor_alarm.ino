// ESP32 Light Sensor Alarm System
// LDR Threshold LED Control Test
// LDR module AO connected to GPIO34
// LED connected to GPIO25 through a current-limiting resistor

const int ldrPin = 34;
const int ledPin = 25;
const int threshold = 1200;

void setup()
 {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  delay(1000);

  Serial.println("LDR threshold LED control test started");
}

void loop() 
{
  int ldrValue = analogRead(ldrPin);

  Serial.print("LDR AO value: ");
  Serial.print(ldrValue);

  if (ldrValue > threshold) 
  {
    digitalWrite(ledPin, HIGH);
    Serial.println(" | Status: DARK - LED ON");
  } 
  else 
  {
    digitalWrite(ledPin, LOW);
    Serial.println(" | Status: LIGHT - LED OFF");
  }

  delay(500);
}