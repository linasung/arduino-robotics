int led = 13;
int AIN1 = 7;
int AIN2 = 8;
int BIN1 = 10;
int BIN2 = 11;

void setup() {
 Serial.begin(19200);
 pinMode(led, OUTPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);
 pinMode(BIN1, OUTPUT);
 pinMode(BIN2, OUTPUT);
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

void loop() {
// forward();
// delay(2000);
// backward();
// delay(2000);
// left();
// delay(2000);
// right();
// delay(2000);
// stop();
// delay(1000);

 char c = Serial.read();
 
 if (c == 'f') {
 forward();
 Serial.println("I moved forward");
 delay(2000);
 stop();
 }

if (c == 'b') {
 backward();
 Serial.println("I moved backward");
 delay(2000);
 stop();
 }

if (c == 'l') {
 left();
 Serial.println("I moved left");
 delay(500);
 stop();
 }

if (c == 'r') {
 right();
 Serial.println("I moved right");
 delay(500);
 stop();
 }
}

