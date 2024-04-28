#include <LiquidCrystal.h>
#include "dht_nonblocking.h"

#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 2;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();

  /* Measure once every two seconds. */
  if (millis() - measurement_timestamp > 2000ul) {
    if (dht_sensor.measure(temperature, humidity) == true) {
      measurement_timestamp = millis();
      return true;
    }
  }
  return false;
}

void loop() {
  float temperature;
  float humidity;

  /* Measure temperature and humidity. If the functions returns
     true, then a measurement is available. */
  if (measure_environment(&temperature, &humidity) == true) {
    // Clear the LCD screen
    lcd.clear();

    // Display temperature on the first line
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print(" C");

    // Display humidity on the second line
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity, 1);
    lcd.print("%");
  }
}