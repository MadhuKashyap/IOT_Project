void setup() {
  // put your setup code here, to run once:
  pinMode(1,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(1,HIGH);
delay(1000);
analogWrite(1,LOW);
delay(1000);

}
