#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define buzzerPin 3 // PIN 3 BUZZER

SoftwareSerial BTSerial(11, 10);    // RX | TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD Display with 0x27 Address, 16x2 pixel

void setup()
{

    // pin mode
    pinMode(buzzerPin, OUTPUT); // set the pin to output

    lcd.clear(); // clear the LCD Display
    Serial.begin(9600);
    BTSerial.begin(38400);                                     // HC-05 default speed in AT command mode
    Serial.println("Slave Bluetooth Device is Ready to Pair"); // tag as slave
    lcd.init();                                                // initialize the LCD
    lcd.backlight();                                           // turn on LCD backlight
    lcd.setCursor(0, 0);
    lcd.print("Hello!"); // Print hello! to greet the user
    delay(3000);         // wait for 3 seconds
    lcd.clear();         // clear the LCD
}

void loop()
{
    float temp;
    float tempLimit = 28.50; // set the temp limit threshold

    // check if BTSerial have input (from transmitter)
    if (BTSerial.available())
    {                                                     // If the data is coming from Software Serial Port
        String received = BTSerial.readStringUntil('\n'); // read String receive from BTSerial

        // display temperature data to LCD
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        received.remove(received.length() - 1); // remove last string (bug)
        lcd.print(received);
        lcd.print((char)223);     // the little square
        lcd.print("C");           // Celcius
        Serial.println(received); // Print received message to Serial Monitor

        // convert string to float data
        temp = received.toFloat();

        // Piezo function, ring the piezo buzzer if temp > tempLimit
        if (temp > tempLimit)
        {
            PiezoSound();
        }
        else
        {
            // cut of from the buzzer
            digitalWrite(buzzerPin, HIGH);
        }
    }
}

// Piezo ring sound
void PiezoSound()
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