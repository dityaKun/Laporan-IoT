#include <Arduino.h>

int Merah = 23;
int Hijau = 22;
int Kuning = 21;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(23, HIGH);
  digitalWrite(22, LOW);
  digitalWrite(21, LOW);
  delay(500); // this speeds up the simulation
  digitalWrite(23, LOW);
  delay(500);

  digitalWrite(23, LOW);
  digitalWrite(22, HIGH);
  digitalWrite(21, LOW);
  delay(500);
  digitalWrite(22, LOW);
  delay(500);

  digitalWrite(23, LOW);
  digitalWrite(22, LOW);
  digitalWrite(21, HIGH);
  delay(250);
  digitalWrite(21, LOW);
  delay(250);
}