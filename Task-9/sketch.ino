#include <Arduino.h>

#define greenLedPin 9 
#define redLedPin 5   
#define sensorPin A0  

const unsigned long openDuration = 3000;

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  Serial.begin(9600);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Значение фоторезистора: ");
  Serial.println(sensorValue);

  if (sensorValue < 512) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    Serial.println("Человек подошёл — двери открываются");
    
    delay(openDuration); 
    
    sensorValue = analogRead(sensorPin); 
    if (sensorValue < 512) {
      Serial.println("Человек всё ещё рядом — двери остаются открытыми");
    } else {
      digitalWrite(redLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      Serial.println("Человек ушёл — двери закрываются");
    }
  } else {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    Serial.println("Человек далеко — двери закрыты");
  }
  
  delay(500);
}