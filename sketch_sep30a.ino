#define LED 19
void setup() {
pinMode (LED,OUTPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(LED,HIGH);
delay(250);
digitalWrite(LED,LOW);
delay(0);
}
