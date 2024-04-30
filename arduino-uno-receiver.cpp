// ArduinoUno Receiver Code

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define buzzerPin 3 // PIN 3 BUZZER

SoftwareSerial BTSerial(11, 10);    // RX | TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD Display with 0x27 Address, 16x2 pixel

void setup()
{
    pinMode(buzzerPin, OUTPUT); // set the pin to output
    lcd.init();                 // initialize the LCD
    lcd.backlight();            // turn on LCD backlight
    Serial.begin(9600);
    BTSerial.begin(38400); // HC-05 default speed in AT command mode
    lcd.clear();           // clear the LCD Display
    lcd.print("Hello!");   // Print hello! to greet the user
    delay(3000);           // wait for 3 seconds
    lcd.clear();           // clear the LCD
}

void loop()
{
    const float tempLimit = 80.00; // set the temp limit threshold
    if (BTSerial.available())
    {
        String received = BTSerial.readStringUntil('\n'); // read String receive from BTSerial
        float temp = received.toFloat();                  // convert string to float data
        if (AnalyzeTiresTemperatureThreshold(temp, SetTiresTemperatureThreshold(temp)))
        {
            AlertDriver();
        }
        UpdateLCDDisplay(received); // update the LCD Display
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BT Not Connected");
    }
}

void AlertDriver()
{
    tone(buzzerPin, 1000); // Send 1kHz tone to buzzer
    delay(500);            // Tone on for 500ms
    noTone(buzzerPin);     // Stop tone
    delay(500);            // No tone for 500ms
    tone(buzzerPin, 1500); // Send 1.5kHz tone to buzzer
    delay(500);            // Tone on for 500ms
    noTone(buzzerPin);     // Stop tone
    delay(500);            // No tone for 500ms
}

void UpdateLCDDisplay(String received)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    String *formattedData = FormattingDataDisplay(received.toFloat());
    lcd.print("Temp: ");
    lcd.print(*formattedData);
    lcd.write(223); // Degree symbol
    lcd.print("C");
}

String *FormattingDataDisplay(float temperature)
{
    static String formattedData[1];
    formattedData[0] = String(temperature, 2); // Convert float to String with 2 decimal places
    return formattedData;
}

void UpdateTireTemperatureData(const char *text, int col, int row)
{
    lcd.setCursor(col, row);
    lcd.print(text);
}

float *SetTiresTemperatureThreshold(float temp)
{
    static float Thresholds[1];
    Thresholds[0] = tempLimit; // Set the threshold limit
    return Thresholds;
}

bool AnalyzeTiresTemperatureThreshold(float temp, float *threshold)
{
    if (temp > *threshold)
    {
        return true;
    }
    return false;
}
