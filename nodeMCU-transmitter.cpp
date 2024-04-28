#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT11

SoftwareSerial BTSerial(5, 4); // RX | TX
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    dht.begin();
    BTSerial.begin(38400); // Set HC-05 communication speed to 9600
    Serial.println("Master Bluetooth Device is Ready to Pair");
}

void loop()
{
    // reading temperature from DHT Sensor
    float t = dht.readTemperature();
    BTSerial.println(t);
    delay(100); // Add a delay to avoid spamming messages
}