// ESP32 Light Sensor Alarm System
// LDR Threshold LED and Buzzer Alarm Test
// LDR module AO connected to GPIO34
// LED connected to GPIO25 through a current-limiting resistor
// ESPBlock onboard buzzer controlled by GPIO27
// The buzzer is active-low: LOW = ON, HIGH = OFF

const int ldrPin = 34;
const int ledPin = 25;
const int buzzerPin = 27;
const int threshold = 1200;

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

 digitalWrite(ledPin, LOW);
 digitalWrite(buzzerPin, HIGH);

  Serial.begin(115200);
  delay(1000);
 
  Serial.println("LDR threshold LED and buzzer alarm test started");
}

void loop()
{
  int ldrValue = analogRead(ldrPin);

  Serial.print("LDR AO value: ");
  Serial.print(ldrValue);

  if (ldrValue > threshold)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    Serial.println(" | Status: DARK - LED ON - BUZZER ON");
  }
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    Serial.println(" | Status: LIGHT - LED OFF - BUZZER OFF");
  }

  delay(500);
}