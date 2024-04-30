// NodeMCU Transmitter code - Tires Temperature Monitoring System

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

SoftwareSerial BTSerial(5, 4); // RX | TX
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Structure to hold temperature data
struct TemperatureData
{
    float ambientTemp;
    float objectTemp;
};

TemperatureData temps; // Global variable to store temperature data

void setup()
{
    Serial.begin(9600);
    Wire.begin(14, 12);                                         // SDA, SCL
    BTSerial.begin(38400);                                      // Set HC-05 communication speed to 38400
    Serial.println("Master Bluetooth Device is Ready to Pair"); // print to tag the device as the master

    Serial.println("Adafruit MLX90614 test");

    if (!mlx.begin())
    {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (1)
            ;
    };
    mlx.writeEmissivity(0.95); // set emisivity or tires

    Serial.print("Emissivity = ");
    Serial.println(mlx.readEmissivity());
    Serial.println("================================================");
}

void loop()
{
    Serial.print("Emissivity = ");
    Serial.println(mlx.readEmissivity());
    Serial.println("================================================");
    DetectTiresTemperature();
}

// detect tires temp function
void DetectTiresTemperature()
{
    GetObjectAndAmbientTemperature();
    // Send the sensor data to BTSerial

    Serial.print("Ambient: ");
    Serial.print(temps.ambientTemp);
    Serial.print("C, Object: ");
    Serial.print(temps.objectTemp);
    Serial.println("C");

    BTSerial.println(CalculateObjectAndAmbientTemperatures());
    delay(2000); // Add a delay to avoid spamming
}

// get avg of object and ambient temp
float CalculateObjectAndAmbientTemperatures()
{
    return (temps.ambientTemp + temps.objectTemp) / 2.0;
}
// get temp data from MLX sensor
// Function to update global temps variable with data from MLX sensor
void GetObjectAndAmbientTemperature()
{
    temps.ambientTemp = mlx.readAmbientTempC(); // reading ambient temp
    temps.objectTemp = mlx.readObjectTempC();   // reading object temp data
}