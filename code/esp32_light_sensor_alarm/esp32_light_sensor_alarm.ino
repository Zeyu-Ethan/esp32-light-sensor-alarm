// ESP32 Light Sensor Alarm System
// Alarm Enable Switch Integration Test

const int ldrPin = 34;       // LDR module AO connected to GPIO34.
const int ledPin = 25;       // External LED connected to GPIO25.
const int buzzerPin = 27;    // ESPBlock onboard buzzer controlled by GPIO27.
const int alarmSwitchPin = 26;  // DIP switch 1 connected to GPIO26.

const int threshold = 2000;
const int confirmDelay = 1000;

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(alarmSwitchPin, INPUT);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);  // Buzzer off because it is active-low.

  Serial.begin(115200);

  Serial.println("Alarm enable switch integration test started");
}

void loop()
{
  int alarmSwitchState = digitalRead(alarmSwitchPin);

  if (alarmSwitchState == LOW)
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);

    Serial.println("Alarm disabled - LED OFF - BUZZER OFF");
    delay(500);
    return;
  }

  int ldrValue = analogRead(ldrPin);

  Serial.print("Alarm enabled | LDR AO value: ");
  Serial.print(ldrValue);

  if (ldrValue > threshold)  // Higher ADC value means darker condition for this LDR module.
  {
    delay(confirmDelay);

    int confirmedLdrValue = analogRead(ldrPin);

    Serial.print(" | Confirmed value: ");
    Serial.print(confirmedLdrValue);

    if (confirmedLdrValue > threshold)
    {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, LOW);
      Serial.println(" | Status: DARK CONFIRMED - LED ON - BUZZER ON");
    }
    else
    {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, HIGH);
      Serial.println(" | Status: FALSE TRIGGER - LED OFF - BUZZER OFF");
    }
  }
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    Serial.println(" | Status: LIGHT - LED OFF - BUZZER OFF");
  }

  delay(500);
}