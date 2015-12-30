#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <dht11.h>
#include <BMP180.h>

dht11 DHT11;

#define DHT11PIN 8
Adafruit_PCD8544 display = Adafruit_PCD8544(2, 3, 4, 5, 6);
const int transmit_pin = 12; //transmitter

// Store an instance of the BMP180 sensor.
BMP180 barometer;
// We are going to use the on board LED for an indicator.
int indicatorLed = 13;
// Store the current sea level pressure at your location in Pascals.
float seaLevelPressure = 101325;
//init values
float RH = 0, TC = 0;

int lcdlight = 7;


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  
  
  // Set up the Indicator LED.
  pinMode(indicatorLed, OUTPUT);
  pinMode(lcdlight, OUTPUT);
  digitalWrite(lcdlight, HIGH);
  // We create an instance of our BMP180 sensor.
  barometer = BMP180();
  // We check to see if we can connect to the sensor.
  if (barometer.EnsureConnected())
  {
    digitalWrite(indicatorLed, HIGH); // Set our LED.

    // When we have connected, we reset the device to ensure a clean start.
    barometer.SoftReset();
    // Now we initialize the sensor and pull the calibration data.
    barometer.Initialize();
  }
  else
  {
    Serial.println("No BMP180 sensor found.");
    digitalWrite(indicatorLed, LOW); // Set our LED.
  }
  display.begin();
    display.setContrast(50);
  digitalWrite(lcdlight, LOW);
  delay(1000);

}


byte count = 1;


void loop()
{
 digitalWrite(indicatorLed, LOW);
 
  int chk = DHT11.read(DHT11PIN);

  if (chk == 0) {
    RH = DHT11.humidity;
    TC = DHT11.temperature;
  }

  // Retrive the current pressure in Pascals.
  float currentPressure = barometer.GetPressure()/100;
  float altitude = barometer.GetAltitude(seaLevelPressure);
  float currentTemperature = barometer.GetTemperature();
  float meanTC = (TC + currentTemperature) / 2;
  float dewpoint = meanTC - ((100 - DHT11.humidity) / 5);
  float TF=1.8 * meanTC + 32;
  String st; 
 
 
  digitalWrite(indicatorLed, HIGH); // Set our LED.
 
  display.clearDisplay();
display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
    display.print("TEMP:");
  display.print(meanTC);
  display.print("C");
  display.println();
  display.print("HUMI:");
  display.print(DHT11.humidity);
  display.print("%");
  display.println();
  display.print("PRES:");
  display.print(currentPressure);
  display.print("hpa");
 display.display();
   digitalWrite(indicatorLed, LOW); // Set our LED.
delay(5000);
  
}



