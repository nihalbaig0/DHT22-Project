/*  DHT22/11 temerature and humidity sensor demonstration sketch
 * 
 * This sketch reads the temperature and humidity from a DHT sensor.
 * 
 * This is a common digital sensor which is calibrated in factory
 * and outputs true values so that no further calculations are needed
 * on the Arduino.
 * 
 * This sketch was adapted for Arduino Step by Step by Peter Dalmaris from the 
 * demo sketch that ships with the Adafruit library.
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - A DHT22 or DHT11 sensor
 *  - 10 kOhm resistor to pull up the data pin
 *  
 *  Libraries
 *  ---------
 *  DHT.h
 *
 * Connections
 * -----------
 * 
 * Hold the sensor so that the grill is towards you. Here are the connections
 * 
 *     -----------
 *     | - |  -  |
 *     | - |  -  |
 *     | - |  -  |
 *     | - |  -  |
 *     -----------
 *     |  |  |  |
 *     |  |  |  |
 *     |  |  |  |
 *     |  |  |  |
 *    5V  2     GND
 *      data
 *    
 * Connect a 10KOhm resistor between the 5V and data pin (2)
 * 
 * Other information
 * -----------------
 * 
 * DHT22 datasheet: https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf
 * The Github repository for the library: https://github.com/adafruit/DHT-sensor-library
 * The DHT library requires Adafruit's Unified Sensor Driver. Install that by searching 
 * for "Adafruit Unified Sensor" in the Library Manager. 
 * Learn more about the Unified Driver: https://github.com/adafruit/Adafruit_Sensor
 * About the Heat Index:   
 * About pull up and pull down resistors:   
 * 
 * 
 * 
 *  Created on October 11 2016 by Peter Dalmaris
 * 
 */

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN1 2// what digital pin we're connected to
#define DHTPIN2 3
#define DHTPIN3 4
#define DHTPIN4 5
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(DHTPIN1, DHTTYPE), dht2(DHTPIN2, DHTTYPE),dht3(DHTPIN3, DHTTYPE),dht4(DHTPIN4, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();
   lcd.init();
    lcd.backlight();
    
    
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht1.readTemperature(true);

  float h2 = dht2.readHumidity();
  float h3 = dht3.readHumidity();
  float h4 = dht4.readHumidity();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(h2) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht1.computeHeatIndex(f, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht1.computeHeatIndex(t, h1, false);

  lcd.setCursor(0, 0);
  lcd.print("H1:");

  lcd.setCursor(3, 0);
  lcd.print(h1);

  lcd.setCursor(8, 0);
  lcd.print("H2:");

  lcd.setCursor(11, 0);
  lcd.print(h2);

  lcd.setCursor(0, 1);
  lcd.print("H3:");

  lcd.setCursor(3, 1);
  lcd.print(h3);

  lcd.setCursor(8, 1);
  lcd.print("H4:");

  lcd.setCursor(11, 1);
  lcd.print(h4);
  Serial.print("Humidity: ");
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
