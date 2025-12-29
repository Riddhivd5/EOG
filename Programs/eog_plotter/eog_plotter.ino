const int sensorPin = 34;

void setup() {
  Serial.begin(115200); 
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(10); 
}