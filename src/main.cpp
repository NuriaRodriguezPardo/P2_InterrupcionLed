#include <Arduino.h>

const uint8_t LED1_PIN = 15;
const uint8_t LED2_PIN = 16;
const uint8_t BUTTON_PIN = 18;
const uint8_t RESET_BUTTON_PIN = 19;

uint32_t led1Interval = 1000;
uint32_t led2Interval = 500;  
uint32_t lastButtonPress = 0; 
uint32_t buttonPressCount = 0; 
void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  static unsigned long previousMillis1 = 0;
  static unsigned long previousMillis2 = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= led1Interval) {
    previousMillis1 = currentMillis;
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN)); 
  }

  if (currentMillis - previousMillis2 >= led2Interval) {
    previousMillis2 = currentMillis;
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN)); 
  }
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (currentMillis - lastButtonPress >= 500) {
      if (led1Interval == 1000) {
        led1Interval = 500;
      } else {
        led1Interval = 1000; 
      }
      lastButtonPress = currentMillis;
      buttonPressCount++; 
      Serial.print("Botón presionado ");
      Serial.print(buttonPressCount);
      Serial.println(" veces.");
    }
  }
  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
    buttonPressCount = 0;
    Serial.println("Contador de botón reiniciado.");
    delay(1000); 
  }
}
