#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

int triggerPin = 12;
int echoPin = 2;
int led = 13;
int AIN1 = 7;
int AIN2 = 8;
int BIN1 = 10;
int BIN2 = 11;
int motorPWMR = 5;
int motorPWML = 6;
int curr_direction;
bool state;
int curr_speed;

// IR buttons
int up = 0x810;
int down = 0xE10;
int left_const = 0xC10;
int right_const = 0xA10;
int stahp = 0x210 ;
int ir = 0x10;
int ps = 0x410;
int speed_up = 0x110;
int slow_down = 0x610;


void setup() {
 Serial.begin(19200);
 irrecv.enableIRIn(); // Start the receiver
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
 curr_speed = 128;
 analogWrite(motorPWMR, curr_speed);
 analogWrite(motorPWML, curr_speed);
}

void forward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, HIGH);
 digitalWrite(BIN1, HIGH);
 digitalWrite(BIN2, LOW);
}

void backward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, HIGH);
 digitalWrite(AIN2, LOW);
 digitalWrite(BIN1, LOW);
 digitalWrite(BIN2, HIGH);
}

void stop() {
 digitalWrite(led, LOW);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, LOW);
 digitalWrite(BIN1, LOW);
 digitalWrite(BIN2, LOW);
}

void right() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW); 
}

void left() {
  digitalWrite(led, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}


void loop()
{
 float inches = ping();
 Serial.println(inches);
 delay(60);
 
 if (mode()) {
  stop();
  //Some rotato stuff
   int left_sensor, right_sensor;
  left_sensor = analogRead(A0);
  Serial.println(left_sensor);
  right_sensor = analogRead(A2);
  Serial.println(right_sensor);
  double offset = abs(left_sensor - right_sensor) * 1.0 / max(left_sensor, right_sensor);
  if (offset < .1) {
    return;
  }
  if (left_sensor > right_sensor) {
    left();
  } else if (right_sensor > left_sensor) {
    right();
  }
  delay(10);
  stop();
 } else {
  ir_mode();
}
 
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

bool mode() 
{
  if (irrecv.decode(&results)) {
    if (results.value == ir) {
      Serial.println("Engaging IR Mode");
      state = false;
    } else if (results.value == ps) {
      Serial.println("Engaging Photosensor Mode");
      state = true;
    }
    irrecv.resume();
  }
  return state;
}

void ir_mode()
{
  if (irrecv.decode(&results)) {
    if (results.value == up && curr_direction != up) {
       Serial.println("Button Up");
       forward();
    }
    else if (results.value == down && curr_direction != down) {
       Serial.println("Button Down");
       backward();
    }
    else if (results.value == left_const && curr_direction != left_const) {
       Serial.println("Button Left");
       left();
    }
    else if (results.value == right_const && curr_direction != right_const) {
       Serial.println("Button Right");
       right();
    }
    else if (results.value == stahp) {
      Serial.println("Stop");
      stop();
    }
    else if (results.value == speed_up) {
      //speed up
      curr_speed += 5;
      if (curr_speed > 255) {
        curr_speed = 255;
      }
       Serial.println(curr_speed);
       analogWrite(motorPWMR, curr_speed);
       analogWrite(motorPWML, curr_speed);
    }
    else if (results.value == slow_down) {
      //slow down
      curr_speed -= 5;
      if (curr_speed < 0) {
        curr_speed = 0;
      }
      Serial.println(curr_speed);
      analogWrite(motorPWMR, curr_speed);
      analogWrite(motorPWML, curr_speed);
    }
    else {
    //stop();
    Serial.print("Unrecognized: ");
    Serial.print(results.value, HEX);
    Serial.println();
    }
    curr_direction = results.value;    
    irrecv.resume(); // Receive the next value
 }
}


