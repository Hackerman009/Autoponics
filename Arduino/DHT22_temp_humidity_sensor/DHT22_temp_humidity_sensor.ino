#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 9

// Set DHT type, uncomment whatever type you're using!
#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);
void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  // Setup sensor:
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements:
  delay(500);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read the humidity in %:
  float h = dht.readHumidity();
  // Read the temperature as Celsius:
  //float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again):
  Serial.print("Humidity: ");
  Serial.println(h);
  if (isnan(h)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}
