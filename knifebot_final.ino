
#include <Servo.h>

int servoPin = 6;

int triggerPin = 11;
int echoPin = 12;

int led = 13;

int AIN1 = 8;
int AIN2 = 7;
int BIN1 = 9;
int BIN2 = 10;

Servo servo;

void setup() {
  Serial.begin(19200);
  servo.attach(servoPin);
  servo.write(180);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
  pinMode(led, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
}

float ping() {
  unsigned long maxTime = 20000;
  unsigned long us;
  float inches;
  // Hold triggerPin high for at least 10us
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Measure length of high pulse on echoPin
  us = pulseIn(echoPin, HIGH, maxTime);
  // pulseIn returns 0 on timeout. Assume worst case.
  if (us == 0) {
    us = maxTime;
  }
  // Convert roundtrip microseconds to inches
  inches = us * 0.013504 / 2;
  return inches;
}

void attack() {
  servo.write(130);
  delay(200);
  servo.write(35);
  delay(200);
  servo.write(130);
  delay(200);
  servo.write(35);
  delay(200);
  servo.write(130);
  delay(200);
  servo.write(35);
  delay(200);
  servo.write(130);
  delay(200);
  servo.write(35);
  delay(200);
  servo.write(130);
  delay(200);
  servo.write(35);
  delay(200);
}

void forward() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void backward() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void stop() {
  digitalWrite(led, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void left() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void right() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void loop() {
  float inches = ping();
  Serial.println(inches);
  delay(60);

  if (inches > 8) {
    forward();
  }
  else if (inches <= 8 && inches > 0.15) {
    stop();
    attack();
    servo.write(180);
    Serial.println(inches);
    delay(60);
    inches = ping();
    //checks if object moves
    if (inches > 8) {
      forward();
      inches = ping();
    } else {
      while (inches <= 8) {
        backward();
        delay(1000);
        stop();
        delay(500);
        left();
        delay(250);
        inches = ping();
        Serial.println(inches);
        delay(60);
      }
    }
  }
}







