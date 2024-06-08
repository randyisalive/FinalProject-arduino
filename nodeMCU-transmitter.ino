// NodeMCU Transmitter code - Tires Temperature Monitoring System

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

SoftwareSerial BTSerial(5, 4);               // RX | TX
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); // declaration of the sensor

const char *ssid = "Rachmi";
const char *password = "Juwita79";
const String BASE_URL = "http://192.168.1.12:5000";
WiFiClient client;
HTTPClient http;

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
    WifiRequest();

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
    SendTempToWeb();
    GetDataFromServer();
}

// add wifi request
void WifiRequest()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
}

void GetDataFromServer()
{
    if (WiFi.status() == WL_CONNECTED)
    {

        http.begin(client, BASE_URL + "/api/get"); // Your Flask server URL

        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            StaticJsonDocument<200> doc;
            StaticJsonDocument<200> doc_output;
            deserializeJson(doc, response);
            String output;
            doc_output["value"] = doc["value"];
            doc_output["threshold"] = doc["threshold"];
            serializeJson(doc_output, output);
            Serial.println(httpResponseCode);
            BTSerial.println(output);
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(http.errorToString(httpResponseCode).c_str()); // More descriptive error
        }

        http.end(); // Close connection
    }
    else
    {
        Serial.println("WiFi not connected");
    }
}
void SendTempToWeb()
{

    if (WiFi.status() == WL_CONNECTED)
    {
        http.begin(client, BASE_URL + "/api/hello"); // Your Flask server URL
        http.addHeader("Content-Type", "application/json");

        // JSON data to send
        String temperatureValue = String(CalculateObjectAndAmbientTemperatures());
        String jsonData = "{\"sensor\":\"temperature\",\"value\":" + temperatureValue + "}";

        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0)
        {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(http.errorToString(httpResponseCode).c_str()); // More descriptive error
        }

        http.end(); // Close connection
    }
    else
    {
        Serial.println("WiFi not connected");
    }
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

    /*     BTSerial.println(CalculateObjectAndAmbientTemperatures()); // sending the data through bluetooth
     */
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