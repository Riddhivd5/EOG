const int ledPin = 2; 

const int sensorPin = 34; 

int triggerLevel = 1925; // change according to your threshold

int ledState = LOW;

unsigned long lastBlinkTime = 0;   
unsigned long blinkCooldown = 500; 

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  Serial.begin(115200); 
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  unsigned long currentTime = millis();

  Serial.print(sensorValue);    
  Serial.print(" ");         
  Serial.println(triggerLevel); 

  if (currentTime - lastBlinkTime > blinkCooldown) {
    
    if (sensorValue > triggerLevel) {

      Serial.println("BLINK DETECTED!");

      ledState = !ledState;
      digitalWrite(ledPin, ledState);
     
      lastBlinkTime = currentTime;
    }
  } 
  
  delay(10); 
} 