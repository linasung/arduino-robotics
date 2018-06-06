#include <IRremote.h>

int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

int led = 13;
int AIN1 = 5;
int AIN2 = 6;
int BIN1 = 9;
int BIN2 = 10;
int motorPWM = A3;
int curr_direction;
bool state;
int curr_speed;

void setup() {
 Serial.begin(19200);
 irrecv.enableIRIn(); // Start the receiver
 pinMode(led, OUTPUT);
 pinMode(motorPWM, INPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);
 pinMode(BIN1, OUTPUT);
 pinMode(BIN2, OUTPUT);
 pinMode(A0, INPUT);
 pinMode(A2, INPUT);
 curr_speed = 128;
}

void forward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, HIGH);
 digitalWrite(BIN1, HIGH);
 digitalWrite(BIN2, LOW);
 analogWrite(motorPWM, curr_speed);
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

bool mode() 
{
  if (irrecv.decode(&results)) {
    if (results.value == 0x10) {
      Serial.println("Engaging IR Mode");
      state = false;
    } else if (results.value == 0x410) {
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
    if (results.value == 0x810 && curr_direction != 0x810) {
       Serial.println("Button Up");
       forward();
    }
    else if (results.value == 0xE10 && curr_direction != 0xE10) {
       Serial.println("Button Down");
       backward();
    }
    else if (results.value == 0xC10 && curr_direction != 0xC10) {
       Serial.println("Button Left");
       left();
    }
    else if (results.value == 0xA10 && curr_direction != 0xA10) {
       Serial.println("Button Right");
       right();
    }
    else if (results.value == 0x210) {
      Serial.println("Stop");
      stop();
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


