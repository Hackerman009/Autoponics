int relay1 = 8;
int relay2 = 7;
int phototran = A1;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(phototran);
  Serial.println(sensorValue);

//light turns on when light level less than 100
  if (sensorValue < 100) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
  }

  else if (sensorValue > 100){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }

  delay(1000);
}
