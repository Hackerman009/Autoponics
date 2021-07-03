int phototran = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(phototran);
  Serial.println(sensorValue);
  delay(500);
}
