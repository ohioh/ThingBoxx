/*##########################################################################################################
    LoRaWan.cpp
    Link:






   ########################################################################################################
*/
#include "Settings.hpp"
#include "Variables.hpp"
#include "LoRaWan.hpp"
#include "EEPROM.hpp"

#include <stdlib.h>
#include <stdint.h>
#include <Wire.h>
#include <bitset>
#include <cassert>
#include <string>

///////////////////////////////////////////////---CONVERT INTEGER TO BINARY---//////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int binPlatformDataTEST = 43;

//TODO: change the int to size_t
void decToBinary(int input)
{
  // array to store binary number
  //Serial.printf("\nGet Binary for %d \n", input);

  //Reset of the used Arrays and Values
  //TODO: overwrite tempBinaryArray with value:0
  //TODO: Controll the Size of writing width
  for (size_t counter = 0; counter < (arraySize); counter++)
  {
    invertedBinaryNum[counter] = 0;
  }

/*
  for (size_t counter = 0; counter < (arraySize); counter++) {
    int printValue = 0;
    printValue = invertedBinaryNum[counter];
    //Serial.println("Value in invertedBinaryNum:");
    //Serial.print(printValue);
    //Serial.println("\n");
  }
*/

  //TODO: overwrite BinaryArray with value:0
  //TODO: Controll the Size of writing width
  for (size_t counter = 0; counter < (arraySize); counter++)
  {
    binaryNum[counter] = 0;
  }

 /*
  for (size_t counter = 0; counter < (arraySize); counter++) {
    int printValue = 0;
    printValue = binaryNum[counter];
    //Serial.println("Value in BinaryNum:");
    //Serial.print(printValue);
    //Serial.println("\n");
  }
 */
  //TODO: overwrite binValue with 0
  //Check delivered value from uint32_t or byte for binValue
  //uint32_t binValue = 0;

  // counter for binary array
  int arraySizeCounter = 0;

  //Write the inverted binary to an array
  //highest place number in the array is the beginning of the binary
  while (input > 0)
  {
    // storing remainder in binary array
    invertedBinaryNum[arraySizeCounter] = input % 2;
    input = input / 2;
    arraySizeCounter++;  //length of value
  }

  // safing & printing binary array in reverse ("right" -> EU) order
  for (size_t counter = arraySizeCounter; counter >= 1; counter--)
  {
    int arrayPlace = arraySizeCounter - counter;
    binaryNum[arrayPlace] = invertedBinaryNum[counter - 1];
  }

  //Write bin Array Values with bitWrite to binSensorData
  size_t writeSpace = arraySizeCounter - 1;

  for (size_t binDataPlace = 0; binDataPlace < arraySizeCounter; binDataPlace ++) {
    byte transmitValue = invertedBinaryNum[binDataPlace];
    bitWrite(binSensorData, binDataPlace, transmitValue);  //Schreibe 1 auf das niedrigstwertige Bit von x
    writeSpace = writeSpace - 1;
  }
}


///////////////////////////////////////////---ZENNER PLATFORM LOGIC---/////////////////////////////////////////////////////////////////////
//
//  the number 6500 ( FD E8 ) gets E8DF in the Zenner Package View.
//  This is changed in this logic, because the transmitted value is switched to read logic of zenner-IoT
//  The Read out for the parser will be again the right number
//  binPlatformData is overwritten in each call -> use it convert the messurment
//  The Zenner converter is prepaired for 16 digits
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zennerParserPrepair()
{
  binPlatformData = 0b0000000000000000;
  //int writeDataPlace = 15;

  //Serial.println("#########---Zenner-Switch-1---##");
  // First (left Block switch to right block)
  for (size_t binDataPlace = 15; binDataPlace >= 8; binDataPlace --) {
    byte transmitValue = bitRead(binSensorData, binDataPlace);
    //Serial.println(transmitValue);
    bitWrite(binPlatformData, (binDataPlace - 8), transmitValue); //Schreibe 1 auf das niedrigstwertige Bit von x
  }

  //Serial.println("#########---Zenner-Switch-2---###");
  //Second (right Block switch to left)
  //Thi Output is inverted
  for (size_t binDataPlace = 0; binDataPlace <= 7; binDataPlace ++) {
    byte transmitValue = bitRead(binSensorData, binDataPlace);
    //Serial.println(transmitValue);
    bitWrite(binPlatformData, (binDataPlace + 8), transmitValue); //Schreibe 1 auf das niedrigstwertige Bit von x
  }

  Serial.println("[Zenner-Convert]: Done");
}



///////////////////////////////////////---PAYLOAD DATAFRAME BUILDER---/////////////////////////////////////////////////////////////////
//  Collecting Data from Sensors and ESP32 and prepair this values for payload transfer
//
//  Called Variables:
//    1.binaryHardwareStatus    7.PM1           13.qmPM2.5[soon]
//    2.binaryBatteryStatus     8.PM2.5         14.qmPM4[soon]
//    3.binaryTemperature       9.PM4           15.qmPM5[soon]
//    4.binaryHumidity         10.PM5           16.qmPM10[soon]
//    5.binaryCO2              11.PM10
//    6.binaryVOC              12.qmPM1[soon]
//
//  Mass concentration:   PM1.0, PM2.5, PM4 and PM10
//  Number concentration:  PM0.5, PM1.0, PM2.5, PM4 and PM10
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern uint16_t appData[];

void prepareTxFrame(uint8_t port)
{
  Serial.println("[Payload]: prepair TX Frame");
  /*
    //Size of values in Payload as binary
    //depends to uintXX_t appData[]
    appDataSize = 12; //AppDataSize max value is 64 -> each number is for 2 digits
    //Important: AppDataSize representate the number of transmitted bytes
    Parser:  [Elixier]: def parse(<<state::16,bat::16,cotwo::16>>, %{meta: %{frame_port: 2}}) do
  */
  decToBinary(averageCO2Store);
  zennerParserPrepair();
  appDataSize = 6;//AppDataSize max value is 64

  decToBinary(DEVICE_STATE);
  zennerParserPrepair();
  appData[0] = binPlatformData; //state
  delay(50);
  
  decToBinary(BatteryValue);
  zennerParserPrepair();
  appData[1] = binPlatformData;   //battery
  delay(50);
  
  decToBinary(averageCO2);
  zennerParserPrepair();
  appData[2] = binPlatformData;   //co2
  delay(50);

  Serial.println("FrameBuildDone");
}


///////////////////////////////////////////////---Use LoRaWan---//////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void useLoRaWan() {


}
