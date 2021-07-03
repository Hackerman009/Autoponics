#include <Adafruit_Sensor.h>
#include <math.h>
#include <DHT.h>

#include <U8g2lib.h>
#include <U8x8lib.h>
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

#include <Arduino.h>
#include <SPI.h>

#define ThermistorPin A0
#define DHTPIN 9

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht = DHT(DHTPIN, DHTTYPE);

int phototran = A1;
int Vo;
float R1 = 10000; //defining the 1k thermistor value as R1
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int relay1 = 8;
int relay2 = 7;

void setup() {
  Serial.begin(9600);  // Begin serial communication at a baud rate of 9600:
  dht.begin();  // Setup sensor:
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  u8g2.begin();
}

void loop() {
  
  //HUMIDITY
  delay(500);  // Wait a few seconds between measurements:
  float h = dht.readHumidity();  // Read the humidity in %:
  if (isnan(h)) {  // Check if any reads failed and exit early (to try again):
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //PHOTOTRANSISTOR
  int sensorValue = analogRead(phototran);

  //THERMISTOR
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  //RELAY CONTROL
  //Heater turns on if temperature below 26.5C and Humidifier at below 85% humidity

  if (T < 26.5) {
    digitalWrite(relay2, HIGH);
  }
  if (T > 26.5) {
    digitalWrite(relay2, LOW);
  }

  if (h < 80) {
    digitalWrite(relay1, HIGH);
  }
  if (h > 80) {
    digitalWrite(relay1, LOW);
  }

  Serial.print("Temp: ");
  Serial.print(T);
  Serial.print("  Humidity: ");
  Serial.print(h);
  Serial.print("  Light: ");
  Serial.println(sensorValue);


  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_11_tf);

    //Temp level 
    u8g2.setCursor(0,13);
    u8g2.print("Temp: ");
    u8g2.setCursor(38,13);
    u8g2.print(T);
    u8g2.setCursor(73,13);
    u8g2.print("\xb0");
    u8g2.setCursor(79,13);
    u8g2.print("C");

    //Light level
    u8g2.setCursor(0,36);
    u8g2.print("Humidity: ");
    u8g2.setCursor(65,36);
    u8g2.print(h);
    u8g2.setCursor(100,36);
    u8g2.print("%");
    
    //Light level print
    u8g2.setCursor(0,58);
    u8g2.print("Light: ");
    u8g2.setCursor(44,58);
    u8g2.print(sensorValue);
        
  } while ( u8g2.nextPage() );
}
