/*##########################################################################################################
    SGP30.cpp
    Link:

    return absolute humidity [mg/m^3] with approximation formula
   @param temperature [°C]
   @param humidity [%RH]

   ########################################################################################################
*/
#include "Variables.hpp"
#include "SGP30.hpp"

#include "Adafruit_SGP30.h"
Adafruit_SGP30 sgp;

#include "LED.hpp"
#include "Display.hpp"
#include "LoRaWan.hpp"
#include "DHT22.hpp"
#include "EEPROM.hpp"

/////////////////////////////////////////////---CONNECT CO² AND VOC SENSOR---//////////////////////////////////////////////////////////
//  Variables:
//    unsigned int sensorDataVOC = 0;
//    uint16_t binaryVOC = 0b1100110011001100;
//
//    unsigned int sensorDataCO2 = 0;
//    uint16_t binaryCO2 = 0b1100110011001100;
//
//    CO2: 375-450   ppm is normal outdoor air ( ppm = parts per million )
//         450-800   ppm good air quality
//         800-1000  ppm acceptable
//         1000-1500 ppm infection risc high
//         1000-2000 ppm infection risc very high
//         2000-5000 ppm without infection risk not longer then 8 hours
//         5000-6000 ppm Questionable for health
//         6000+     ppm high risk for health (100k dangerous for life, 200k deadly)
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setAverage(uint16_t inputCO2, uint16_t inputVOC) {
  averageCO2 = ((averageCO2 + inputCO2) / 2 );
  averageVOC = ((averageVOC + inputVOC) / 2);
  write_int(90, averageCO2);
}

uint32_t getAbsoluteHumidity(float temperature, float humidity) {
  // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
  const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
  const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
  return absoluteHumidityScaled;
}

int counterSGP = 0;

void setSGP30Baseline() {
  sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
}


///////////////////////////////////////////---Initialize SGP30---/////////////////////////////////////////////////////////////////////////////
void initializeSGP30() {
  getTemperatureDHT22();
  delay(1000);
  getHumidityDHT22();
  Serial.println("---Temp and Hum---");
  Serial.println(gTEMPERATURE);
  Serial.println(gHUMIDITY);
  Serial.println("--------------------");
  if (! sgp.begin()) {
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}


///////////////////////////////////////////---Get CO2---///////////////////////////////////////////////////////////////////////////////
void getCO2andVOC()
{
  initializeSGP30();

  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  float temperature = gTEMPERATURE; // [°C]
  float humidity = gHUMIDITY; // [%RH]
  sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }
  Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.print(" \t");
  Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");

  delay(1000);


  for ( int count = 0; count <= 30; count++) {

    Serial.println("--------------------------------");
    Serial.println("SGP30 Counter");
    Serial.println(count);
    Serial.println("--------------------------------");
    getAbsoluteHumidity(gTEMPERATURE, gHUMIDITY);
    if (! sgp.IAQmeasure()) {
      Serial.println("Measurement failed");
      return;
    }
    Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
    Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
    uint16_t getCO2 = sgp.eCO2;
    uint16_t getVOC = sgp.TVOC;
    setAverage(getCO2, getVOC);

    if (! sgp.IAQmeasureRaw()) {
      Serial.println("Raw Measurement failed");
      return;
    }
    Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.print(" \t");
    Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");
    delay(1000);
    counterSGP++;

  }
  Serial.println("Counter");
  Serial.println(counterSGP);
  Serial.println(averageCO2);
  Serial.println(averageVOC);
  Serial.println("------------");

  if (counterSGP == 30) {
    counterSGP = 0;

    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }
    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
  Serial.println("Display CO2");
  
  
  blinkBLUE(2,1000);

}



///////////////////////////////////////////---PRINT VOC---/////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////---Get VOC---///////////////////////////////////////////////////////////////////////////////

void getVOC()
{


}
