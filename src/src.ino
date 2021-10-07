/*
   HelTec Automation(TM) LoRaWAN 1.0.2 OTAA example use OTAA, CLASS A

   Function summary:

   - use internal RTC(150KHz);

   - Include stop mode and deep sleep mode;

   - 15S data send cycle;

   - Informations output via serial(115200);

   - Only ESP32 + LoRa series boards can use this library, need a license
     to make the code run(check you license here: http://www.heltec.cn/search/);

   You can change some definition in "Commissioning.h" and "LoRaMac-definitions.h"

   HelTec AutoMation, Chengdu, China.
   成都惠利特自动化科技有限公司
   https://heltec.org
   support@heltec.cn

  this project also release in GitHub:
  https://github.com/HelTecAutomation/ESP32_LoRaWAN


*/

#include <ESP32_LoRaWAN.h>
#include "Arduino.h"
#include "LoRaWan.hpp"

/*---------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Variables.hpp"
#include "LED.hpp"
#include "DHT22.hpp"
#include "Battery.hpp"
#include "Storage.hpp"
#include "Time.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_CCS811 ccs;
uint64_t chipid;

RTC_DATA_ATTR int BaseLineCounter = 0;
/*---------------------------------------------------------------------------------------------------*/

/*license for Heltec ESP32 LoRaWan, quary your ChipID relevant license: http://resource.heltec.cn/search */
uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

/* OTAA para*/
uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};

/* ABP para*/
uint8_t NwkSKey[] = {0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda, 0x85};
uint8_t AppSKey[] = {0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef, 0x67};
uint32_t DevAddr = (uint32_t)0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/
bool overTheAirActivation = true;

/*ADR enable*/
bool loraWanAdr = true;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = true;

/* Application port */
uint8_t appPort = 2;

/*!
  Number of trials to transmit the frame, if the LoRaMAC layer did not
  receive an acknowledgment. The MAC performs a datarate adaptation,
  according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
  to the following table:

  Transmission nb | Data Rate
  ----------------|-----------
  1 (first)       | DR
  2               | DR
  3               | max(DR-1,0)
  4               | max(DR-1,0)
  5               | max(DR-2,0)
  6               | max(DR-2,0)
  7               | max(DR-3,0)
  8               | max(DR-3,0)

  Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
  the datarate, in case the LoRaMAC layer did not receive an acknowledgment
*/
uint8_t confirmedNbTrials = 8;

/*LoraWan debug level, select in arduino IDE tools.
  None : print basic info.
  Freq : print Tx and Rx freq, DR info.
  Freq && DIO : print Tx and Rx freq, DR, DIO0 interrupt and DIO1 interrupt info.
  Freq && DIO && PW: print Tx and Rx freq, DR, DIO0 interrupt, DIO1 interrupt and MCU deepsleep info.
*/
uint8_t debugLevel = LoRaWAN_DEBUG_LEVEL;

/*LoraWan region, select in arduino IDE tools*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;

int count = 1;

// Add your initialization code here
void setup()
{
  //Set ADC to read out the Battery status:
  setADC();



  Serial.begin(115200);

  //Pin to read Battery
  //pinMode( 21, OUTPUT );
  //digitalWrite( 21, LOW );

  delay(10);
  setESP32Time();
  delay(50);
  getESP32Time();

  setupDHT22();
  setLEDPins();

  while (!Serial)
    ;

  //Activate the LoRaWan-Module
  SPI.begin(SCK, MISO, MOSI, SS);
  Mcu.init(SS, RST_LoRa, DIO0, DIO1, license);
  deviceState = DEVICE_STATE_INIT;
  delay(500);
  LoRaWAN.init(loraWanClass, loraWanRegion);
  delay(500);
  LoRaWAN.join();
  delay(500);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  delay(500);
  display.clearDisplay();
  display.setCursor(2, 5);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("Thing");
  display.setCursor(55, 35);
  display.setTextSize(3);
  display.print("BOXX");
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setCursor(15, 15);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("CO2-AMPEL");
  display.setCursor(25, 35);
  display.setTextSize(1);
  display.print("Initializing...");
  display.display();
  delay(1000);

  //Start CCS811:
  Serial.println("CCS811 starting...");

  //TODO : Not working to set the Drive Mode
  //ccs.setDriveMode(2);
  if (!ccs.begin())
  {
    Serial.println("Failed to start CCS811 sensor! Please check wiring.");
    //while (1);
  }
  else
  {
    /**************************************************************************/
    /*!
        (es werden keine Messungen durchgeführt)
        Modus 1 IAQ Messung jede Sekunde
        Modus 2 IAQ Messung alle 10 Sekunden
        Modus 3 IAQ Messung alle 60 Sekunden
        Modus 4 IAQ Messung alle 250 ms
        (es wird nicht eCO2 und TVOC berechnet)
    */
    /**************************************************************************/
    Serial.println("CCS811 started");
  }

  // Wait for the sensor to be ready
  //while (!ccs.available());
}

// The loop function is called in an endless loop
void loop()
{
  /*
    chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
    Serial.printf("ESP32 Chip ID = %04X", (uint16_t)(chipid >> 32)); //print High 2 bytes
    Serial.printf("%08X\n", (uint32_t)chipid); //print Low 4bytes.
  */

  switch (deviceState)
  {
    case DEVICE_STATE_SEND:
      {
        //Read Voltage of pin
        //ReadVoltage(13);
        readADC();

        //read DHT22

        loopTemperature();
        loopHumidity();

        if (ccs.available())
        {
          ccs.setEnvironmentalData(humidity, temp);
          delay(50);

          if (BaseLineCounter == 0)
          {
            Serial.println("Set new Baseline [1]");
            uint16_t Baseline = ccs.getBaseline();
            ccs.setBaseline(Baseline);
          }
          else if (BaseLineCounter == 30)
          {
            Serial.println("Set new Baseline [30]");
            uint16_t Baseline = ccs.getBaseline();
            ccs.setBaseline(Baseline);
            BaseLineCounter = 0;
          }
          BaseLineCounter++;

          Serial.print("[Loop]:Baseline-Counter:");
          Serial.println(BaseLineCounter);
          Serial.println("------------------");



          delay(500);

          if (!ccs.readData())
          {

            // ---------------------------
            display.clearDisplay();

            display.setTextSize(1);
            display.setCursor(0, 0);
            display.print("Temperatur");

            display.setTextSize(5);
            display.setCursor(20, 20);
            display.print(temp);

            display.setTextSize(5);
            display.setCursor(87, 20);
            display.print("C");
            display.display();
            delay(2000);

            // ---------------------------
            display.clearDisplay();

            display.setTextSize(1);
            display.setCursor(0, 0);
            display.print("Luftfeuchtigkeit");

            display.setTextSize(5);
            display.setCursor(20, 20);
            display.print(humidity);

            display.setTextSize(5);
            display.setCursor(85, 20);
            display.print("%");
            display.display();
            delay(2000);

            // ---------------------------
            Serial.print("CO2: ");
            Co2 = ccs.geteCO2();
            Serial.print(Co2);
            Serial.print("ppm, TVOC: ");
            Serial.println(ccs.getTVOC());

            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(0, 0);
            display.print("CO2:");

            display.setTextSize(5);
            display.setCursor(5, 20);
            display.print(Co2);

            display.setTextSize(1);
            display.setCursor(110, 57);
            display.print("PPM");

            display.display();
            delay(2000);
          }
          else
          {
            Serial.println("ERROR!");
            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(0, 5);
            display.print("ERROR!");
            while (1)
              ;
          }
        }

        prepareTxFrame(appPort);
        LoRaWAN.send(loraWanClass);
        deviceState = DEVICE_STATE_CYCLE;
        delay(1000);
        Serial.println("Set LEDS");
        mainCO22Signal(Co2);
        delay(1000);
        break;
      }
    case DEVICE_STATE_CYCLE:
      {
        // Schedule next packet transmission
        Serial.println("[LOOP]: State");
        txDutyCycleTime = appTxDutyCycle + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
        LoRaWAN.cycle(txDutyCycleTime);
        deviceState = DEVICE_STATE_SLEEP;
        delay(1000);
        break;
      }
    case DEVICE_STATE_SLEEP:
      {
        /*Serial.println("[LOOP]: Sleep");
              Serial.println(txDutyCycleTime);
              Serial.println("Restarting in 10 seconds");
              delay(10000);
              ESP.restart();
        */
        LoRaWAN.sleep(loraWanClass, debugLevel);
        break;
      }
    default:
      {
        Serial.println("[LOOP]: default");
        deviceState = DEVICE_STATE_INIT;
        break;
      }
  }
}
