/*##########################################################################################################
 * 
 *  Link: 
 * 
 * 
 * 
 * 
 * 
 * 
 * ########################################################################################################
 */
 
#include "DHT22.hpp"


#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "Variables.hpp"
#include "Display.hpp"


///////////////////////////////////////////---Definition---///////////////////////////////////////////////////////////////////
#define DHTPIN 33     // Digital pin connected to the DHT sensor 
// Heltec Wireless Stick: Pin 2 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)


///////////////////////////////////////////---VARIABLES---///////////////////////////////////////////////////////////////////

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
sensor_t sensor;
sensors_event_t event;



//////////////////////////////////////////---Activate DHT SENSOR---//////////////////////////////////////////////////////////
void activateDHT22()
{
  dht.begin();

  // Print sensor details.
  Serial.println(F("DHT Sensor Informations:"));
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("DHT22-Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.println(F("------------------------------------"));
}

///////////////////////////////////////////---PRINT TEMPERATURE---//////////////////////////////////////////////////////////

void sendTemperature()
{
  
}


///////////////////////////////////////////---PRINT HUMIDITY---//////////////////////////////////////////////////////////

void sendHumidity()
{
  
}


///////////////////////////////////////////---Get TEMPERATURE---//////////////////////////////////////////////////////////

void getTemperatureDHT22()
{
  // Delay between measurements.
  delay(delayMS);
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    gTEMPERATURE = event.temperature;
    Serial.print(gTEMPERATURE);
    Serial.println(F("°C"));
  }
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}


///////////////////////////////////////////---GET HUMIDITY---//////////////////////////////////////////////////////////
void getHumidityDHT22()
{
  // Get temperature event and print its value.
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    gHUMIDITY = event.relative_humidity;
    Serial.print(gHUMIDITY);
    Serial.println(F("%"));
  }
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}
