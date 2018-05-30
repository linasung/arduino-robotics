

void setup() {
 Serial.begin(19200);
 pinMode(A0, INPUT);
 pinMode(2, OUTPUT);
}
void loop() {
 int value;
 
 value = analogRead(A0);
 Serial.print(value);

tone(2, value);
delay(500);
noTone(2);
 
}
