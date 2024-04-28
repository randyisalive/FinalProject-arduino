#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define buzzerPin 3

SoftwareSerial BTSerial(11, 10); // RX | TX
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{

    // pin mode
    pinMode(buzzerPin, OUTPUT);

    lcd.clear();
    Serial.begin(9600);
    BTSerial.begin(38400); // HC-05 default speed in AT command mode
    Serial.println("Slave Bluetooth Device is Ready to Pair");
    delay(3000);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello!");
    delay(2000);
    lcd.clear();
}

void loop()
{
    float temp;
    float tempLimit = 28;
    if (BTSerial.available())
    { // If the data is coming from Software Serial Port
        String received = BTSerial.readStringUntil('\n');
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        received.remove(received.length() - 1); // remove last string (bug)
        lcd.print(received);
        lcd.print((char)223);     // the little square
        lcd.print("C");           // Celcius
        Serial.println(received); // Print received message to Serial Monitor
        temp = received.toFloat();

        if (temp > tempLimit)
        {
            PiezoSound();
        }
        else
        {
            digitalWrite(buzzerPin, HIGH);
        }
    }
}

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