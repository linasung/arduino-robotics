#include <Servo.h>
#include <IRremote.h>

int servoPin = 6;
int RECV_PIN = 4;

Servo servo;
IRrecv irrecv(RECV_PIN);
decode_results results;

int curr_angle;

void setup() {
  servo.attach(servoPin);

  Serial.begin(19200);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  curr_angle = 0;
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == 0x61A0807F) {

      Serial.println("Forward");
      curr_angle = min(curr_angle + 10, 180);
      servo.write(curr_angle);
      Serial.println(curr_angle);
    }
    else if (results.value == 0x61A0E01F) {
      Serial.println("Backwards");
      curr_angle = max(curr_angle - 10, 0);
      servo.write(curr_angle);
      Serial.println(curr_angle);
    }
    else {
      //stop();
      Serial.print("Unrecognized: ");
      Serial.print(results.value, HEX);
      Serial.println();
    }
    irrecv.resume(); // Receive the next value
  }
}



