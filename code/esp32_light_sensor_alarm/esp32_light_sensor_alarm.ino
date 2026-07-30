// ESP32 Light Sensor Alarm System
// Alarm Enable, Buzzer Mute and LED Enable Switch Integration Test

const int ldrPin = 34;            // LDR module AO connected to GPIO34.
const int ledPin = 25;            // External LED connected to GPIO25.
const int buzzerPin = 27;         // ESPBlock onboard buzzer controlled by GPIO27.
const int alarmSwitchPin = 26;    // DIP switch 1 connected to GPIO26.
const int buzzerSwitchPin = 32;   // DIP switch 2 connected to GPIO32.
const int ledSwitchPin = 33;      // DIP switch 3 connected to GPIO33.

const int threshold = 2000;
const int confirmDelay = 1000;

void setup()
{
  pinMode(ldrPin, INPUT);
  pinMode(alarmSwitchPin, INPUT);
  pinMode(buzzerSwitchPin, INPUT);
  pinMode(ledSwitchPin, INPUT);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);  // Buzzer off because the ESPBlock onboard buzzer is active-low.

  Serial.begin(115200);

  Serial.println("Alarm enable, buzzer mute and LED enable switch integration test started");
}

void loop()
{
  int alarmSwitchState = digitalRead(alarmSwitchPin);
  int buzzerSwitchState = digitalRead(buzzerSwitchPin);
  int ledSwitchState = digitalRead(ledSwitchPin);

  // If the alarm enable switch is OFF, the system is disabled and all outputs stay off.
  if (alarmSwitchState == LOW)
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);

    Serial.println("Alarm disabled - LED OFF - BUZZER OFF");
    delay(500);
    return;
  }

  int ldrValue = analogRead(ldrPin);

  Serial.print("Alarm enabled");

  Serial.print(" | LED switch: ");
  if (ledSwitchState == HIGH)
  {
    Serial.print("ON");
  }
  else
  {
    Serial.print("OFF");
  }

  Serial.print(" | Buzzer switch: ");
  if (buzzerSwitchState == HIGH)
  {
    Serial.print("ON");
  }
  else
  {
    Serial.print("MUTED");
  }

  Serial.print(" | LDR AO value: ");
  Serial.print(ldrValue);

  if (ldrValue > threshold)  // Higher ADC value means darker condition for this LDR module.
  {
    delay(confirmDelay);  // Confirm that the dark condition remains present before triggering the alarm.

    int confirmedLdrValue = analogRead(ldrPin);

    Serial.print(" | Confirmed value: ");
    Serial.print(confirmedLdrValue);

    if (confirmedLdrValue > threshold)
    {
      Serial.print(" | Status: DARK CONFIRMED");

      if (ledSwitchState == HIGH)
      {
        digitalWrite(ledPin, HIGH);
        Serial.print(" - LED ON");
      }
      else
      {
        digitalWrite(ledPin, LOW);
        Serial.print(" - LED DISABLED");
      }

      if (buzzerSwitchState == HIGH)
      {
        digitalWrite(buzzerPin, LOW);
        Serial.println(" - BUZZER ON");
      }
      else
      {
        digitalWrite(buzzerPin, HIGH);
        Serial.println(" - BUZZER MUTED");
      }
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