int led = 13;
int led2 = 8;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led2, HIGH);
  delay(750);
  digitalWrite(led2, LOW);
  delay(300);
  digitalWrite(led2, HIGH);
  delay(750);
  digitalWrite(led2, LOW);
  delay(300);
  digitalWrite(led2, HIGH);
  delay(750);
  digitalWrite(led2, LOW);
  delay(300);
   digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(2000);
}



