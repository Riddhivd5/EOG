#include <Arduino.h>

const int ledPin = 2;
const int deniedLedPin = 4;
const int adminSensorPin = 34;
const int userSensorPin = 35;

const int adminTriggerLevel = 1900;
const int userTriggerLevel = 1900;

SemaphoreHandle_t adminLock;

int ledState = LOW;
unsigned long lockoutEndTime = 0;

const unsigned long blinkCooldown = 500;

void Task_Read_Admin(void *pvParameters) {
  unsigned long lastBlinkTime = 0;

  for (;;) {
    int sensorValue = analogRead(adminSensorPin);
    unsigned long currentTime = millis();

    if (sensorValue > adminTriggerLevel &&
        (currentTime - lastBlinkTime > blinkCooldown)) {

      lastBlinkTime = currentTime;

      if (xSemaphoreTake(adminLock, portMAX_DELAY) == pdTRUE) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        lockoutEndTime = currentTime + 5000;
        xSemaphoreGive(adminLock);
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void Task_Read_User(void *pvParameters) {
  unsigned long lastBlinkTime = 0;

  for (;;) {
    int sensorValue = analogRead(userSensorPin);
    unsigned long currentTime = millis();

    if (sensorValue > userTriggerLevel &&
        (currentTime - lastBlinkTime > blinkCooldown)) {

      lastBlinkTime = currentTime;

      if (xSemaphoreTake(adminLock, (TickType_t)10) == pdTRUE) {

        if (currentTime > lockoutEndTime) {
          ledState = !ledState;
          digitalWrite(ledPin, ledState);
        } else {
          digitalWrite(deniedLedPin, HIGH);
          delay(100);
          digitalWrite(deniedLedPin, LOW);
        }

        xSemaphoreGive(adminLock);
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(deniedLedPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  digitalWrite(deniedLedPin, LOW);

  adminLock = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    Task_Read_Admin,
    "AdminTask",
    1024,
    NULL,
    2,
    NULL,
    1);

  xTaskCreatePinnedToCore(
    Task_Read_User,
    "UserTask",
    1024,
    NULL,
    1,
    NULL,
    1);
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
