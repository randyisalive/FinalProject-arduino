#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

SoftwareSerial BTSerial(5, 4); // RX | TX
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

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

    Serial.print("Emissivity = ");
    Serial.println(mlx.readEmissivity());
    Serial.println("================================================");
}

void loop()
{

    float *temps = GetObjectAndAmbientTemperature();

    float temp = TiresTemp(temps[0], temps[1]);

    BTSerial.println(temp); // send the sensor data to BtSerial
    delay(1000);            // Add adelay to avoid spamming messages
}

// detect tires temp function
float DetectTiresTemperature()
{
    float *temps = GetObjectAndAmbientTemperature();

    float temp = TiresTemp(temps[0], temps[1]);

    BTSerial.println(temp); // send the sensor data to BtSerial
}

// get avg of object and ambient temp
float CalculateObjectAndAmbientTemperatures(float x, float y)
{
    return x + y / 2;
}

// get temp data from MLX sensor
float *GetObjectAndAmbientTemperature()
{
    float ambientTemp = mlx.readAmbientTempC(); // reading ambient temp
    float objectTemp = mlx.readObjectTempC();   // reading object temp data
    static float temperatures[2];
    temperatures[0] = ambientTemp;
    temperatures[1] = objectTemp;

    return temperatures
}