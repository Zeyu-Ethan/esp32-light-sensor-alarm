// ESP32 Light Sensor Alarm System
// Day 2 - GPIO Output and LED Blink Test
// LED connected to GPIO25 through a current-limiting resistor(330Ω)

const int ledPin = 25; //LED connected to GPIO25

void setup() {
  pinMode(ledPin, OUTPUT); //set ledPin as output

  Serial.begin(115200);
  delay(1000);

  Serial.println("LED GPIO output test started");
}

void loop() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(1000);
}
