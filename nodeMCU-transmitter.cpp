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
    float ambientTemp = mlx.readAmbientTempC(); // reading ambient temp
    float objectTemp = mlx.readObjectTempC();
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = ");
    Serial.print(mlx.readObjectTempF());
    Serial.println("*F");

    float temp = TiresTemp(ambientTemp, objectTemp);

    BTSerial.println(temp); // send the sensor data to BtSerial
    delay(1000);            // Add adelay to avoid spamming messages
}

float TiresTemp(float x, float y)
{
    return x + y / 2;
}