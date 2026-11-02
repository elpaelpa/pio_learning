#include <Arduino.h>

constexpr uint8_t LDR_PIN = 5;
constexpr uint8_t LED_PIN = 4;

constexpr int duty_val = 255;
constexpr int setpoint = 1000;
constexpr float Kp = 0.05;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  ledcAttach(LED_PIN, 5000, 8);

}

void loop() {
  // put your main code here, to run repeatedly:
  int y = analogRead(LDR_PIN); //returns 0-4095
  int e = setpoint - y; //error

  float u = Kp * e; //output
  u = constrain(u, 0, 255);
  

  ledcWrite(LED_PIN,  (int)u);
  Serial.print(setpoint);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(u);
  delay(20);
}

