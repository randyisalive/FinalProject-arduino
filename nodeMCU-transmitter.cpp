#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 14     // D5 PIN
#define DHTTYPE DHT11 // DHT11 type sensor

SoftwareSerial BTSerial(5, 4); // RX | TX
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);                                         // set up Serial baud 9600
    dht.begin();                                                // function to call dht sensor
    BTSerial.begin(38400);                                      // Set HC-05 communication speed to 38400
    Serial.println("Master Bluetooth Device is Ready to Pair"); // print to tag the device as the master
}

void loop()
{
    //  reading temperature from DHT Sensor
    float t = dht.readTemperature();
    BTSerial.println(t); // send the sensor data to BtSerial
    delay(100);          // Add adelay to avoid spamming messages
}