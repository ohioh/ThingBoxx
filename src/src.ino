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
#include <EEPROM.h>//https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

#include "Variables.hpp"
#include "co2.hpp"
#include "LED1.hpp"
#include "DHT22.hpp"
#include "Battery.hpp"
#include "Storage.hpp"
#include "Time.hpp"
#include "Sleep.hpp"
#include "license.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Adafruit_CCS811 ccs;
uint64_t chipid;

RTC_DATA_ATTR int BaseLineCounter = 0;

//Production
//RTC_DATA_ATTR uint16_t nightTime = 21600000;

//Development
RTC_DATA_ATTR uint16_t nightTime = 2000;

TaskHandle_t  activeLoRaWanHandler ;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

int TimeTillToSend = 60;
int TimeCounter = 0;




/*---------------------------------------------------------------------------------------------------*/

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LEDPin 12 //LED light
void flashLED(uint8_t data, int ledPin)
{
  // lora_printf("data:%d\r\n",data);
  switch (data)
  {
    case 49:
      {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, HIGH);
        break;
      }
    case 50:
      {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
        break;
      }
    case 51:
      {
        break;
      }
    default:
      {
        break;
      }
  }
}

void flashLED1(uint8_t data, int ledPin)
{
  // lora_printf("data:%d\r\n",data);
  switch (data)
  {
    case 49:
      {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
        break;
      }
    case 50:
      {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, HIGH);
        break;
      }
    case 51:
      {
        break;
      }
    default:
      {
        break;
      }
  }
}

/*
  void downLinkDataHandle(McpsIndication_t *mcpsIndication)
  {
  lora_printf("+REV DATA:%s,RXSIZE %d,PORT %d\r\n", mcpsIndication->RxSlot ? "RXWIN2" : "RXWIN1", mcpsIndication->BufferSize, mcpsIndication->Port);
  lora_printf("+REV DATA:");
  flashLED(mcpsIndication->Buffer[0]);

  for (uint8_t i = 0; i < mcpsIndication->BufferSize; i++)
  {
    lora_printf("%02X", mcpsIndication->Buffer[i]);
  }
  lora_printf("\r\n");
  }
*/


void activeLoRaWan( void * Parameter )
{
  for (;;)    {
    Serial.print("LED-Task runs on Core: ");
    Serial.println(xPortGetCoreID());
    yield();
    delay (600);
    Serial.print ("Application CPU is on core:");   Serial.println (xPortGetCoreID());   delay (500);
    delay(1000);

    flashLED1(49, 4);
    delay(1000);
    flashLED1(50, 4);
    delay(1000);

  }
}

// Add your initialization code here
void setup()
{

  //Set ADC to read out the Battery status:
  setADC();

  //Set LED Pins:
  setLEDPins();

  Serial.begin(115200);
  Serial.println("-------------------------------------------------------------------------------------------------------------------------");
  Serial.println("Setup started");
  //Pin to read Battery
  //pinMode( 21, OUTPUT );
  //digitalWrite( 21, LOW );

  delay(10);
  setESP32Time();
  delay(50);
  getESP32Time();
  delay(50);
  storeESP32Time();
  delay(50);

  setupDHT22();

  //while (!Serial);



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
  delay(2000);


  int Temp = loopTemperature();
  display.clearDisplay();
  display.setCursor(2, 5);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("Temp:");
  display.setCursor(55, 35);
  display.setTextSize(3);
  display.print(Temp);
  display.setCursor(75, 35);
  display.print(" C");
  display.display();

  setupCO2();
  delay(1000);
  loopCO2();
  delay(1000);
  loopSleepTimeControll();
  /*loopCO2();
    delay(1000);


    xTaskCreatePinnedToCore(
    activeLoRaWan,        // Function that should be called
    "getCO2 Average",     // Name of the task (for debugging)
    10000,                // Stack size (bytes)
    NULL,                 // Parameter to pass
    1,                    // Task priority
    &activeLoRaWanHandler, // Task handle
    1); //Core
  */
  Serial.println("Waiting for messurment:");
  //Activate the LoRaWan-Module
  SPI.begin(SCK, MISO, MOSI, SS);
  Mcu.init(SS, RST_LoRa, DIO0, DIO1, license);
  deviceState = DEVICE_STATE_INIT;
}




// The loop function is called in an endless loop
void loop()
{
  /*
    chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
    Serial.printf("ESP32 Chip ID = %04X", (uint16_t)(chipid >> 32)); //print High 2 bytes
    Serial.printf("%08X\n", (uint32_t)chipid); //print Low 4bytes.
  */
  // TODO
  /*
    int address = 90;
    int readId;
    readId = EEPROM.read(address); //EEPROM.get(address,readId);

    if (readId == 1){
    ESP.restart();
    }
  */

  if ( TimeCounter < TimeTillToSend) {
    TimeCounter++;

    Serial.print(" Sending in: ");
    int timeLeft = TimeTillToSend - TimeCounter;
    Serial.println(timeLeft);
    display.clearDisplay();
    display.setCursor(2, 5);
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.println("CO2:");
    display.setCursor(55, 35);
    display.setTextSize(3);
    display.print(AverageC02Value);
    display.display();
    delay(1000);
  } else if (TimeCounter >= TimeTillToSend) {


    switch ( deviceState )
    {
      case DEVICE_STATE_INIT:
        {
          LoRaWAN.init(loraWanClass, loraWanRegion);
          Serial.print(" Sending in: ");
          int timeLeft = TimeTillToSend - TimeCounter;
          Serial.println(timeLeft);
          display.clearDisplay();
          display.setCursor(2, 5);
          display.setTextSize(3);
          display.setTextColor(WHITE);
          display.println("CO2:");
          display.setCursor(55, 35);
          display.setTextSize(3);
          display.print(AverageC02Value);
          display.display();
          delay(1000);
          break;
        }
      case DEVICE_STATE_JOIN:
        {
          LoRaWAN.join();
          break;
        }
      case DEVICE_STATE_SEND:
        {
          prepareTxFrame( appPort );
          LoRaWAN.send(loraWanClass);
          deviceState = DEVICE_STATE_CYCLE;
          break;
        }
      case DEVICE_STATE_CYCLE:
        {
          // Schedule next packet transmission
          txDutyCycleTime = appTxDutyCycle + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND )  ;
          Serial.print(" DUTY:");
          Serial.println(txDutyCycleTime);
          LoRaWAN.cycle(txDutyCycleTime);
          deviceState = DEVICE_STATE_SLEEP;
          break;
        }
      case DEVICE_STATE_SLEEP:
        {
          LoRaWAN.sleep(loraWanClass, debugLevel);
          break;
        }
      default:
        {
          deviceState = DEVICE_STATE_INIT;
          break;
        }
    }
  }
  //ESP.restart();
  /*
  */

}
