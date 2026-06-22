#include <Arduino.h>
#include <Servo.h> 

#define SERVO_PIN 3 

Servo myServo;      
int currentAngle = 90; 

void setup() {
  Serial.begin(9600); 
  myServo.attach(SERVO_PIN); 
  myServo.write(currentAngle); 
  
  Serial.println("Система готова. Введите угол поворота от 0 до 180 градусов:");
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim(); 

    bool isNumeric = true;
    if (inputString.length() == 0) isNumeric = false;
    for (unsigned int i = 0; i < inputString.length(); i++) {
      if (!isDigit(inputString.charAt(i))) {
        isNumeric = false;
        break;
      }
    }

    if (isNumeric) {
      int targetAngle = inputString.toInt(); 

      if (targetAngle >= 0 && targetAngle <= 180) {
        
        if (targetAngle != currentAngle) {
          Serial.print("Перемещение сервопривода из ");
          Serial.print(currentAngle);
          Serial.print("° в ");
          Serial.print(targetAngle);
          Serial.println("°...");

          if (targetAngle > currentAngle) {
            for (int angle = currentAngle; angle <= targetAngle; angle++) {
              myServo.write(angle); 
              delay(15);            
            }
          } else {
            for (int angle = currentAngle; angle >= targetAngle; angle--) {
              myServo.write(angle); 
              delay(15);            
            }
          }

          currentAngle = targetAngle; 
          Serial.println("Перемещение завершено успешно.");
        } else {
          Serial.println("Ошибка: Сервопривод уже находится в этом положении.");
        }

      } else {
        Serial.println("Ошибка: Введите число строго в диапазоне от 0 до 180.");
      }
    } else {
      Serial.println("Ошибка: Введены некорректные данные. Пожалуйста, введите число.");
    }
  }
}