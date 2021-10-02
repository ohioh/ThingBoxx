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
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

void initializeDisplay(void);

void printTEST(void);
void pre(void);
void printBatteryState(int displayTime, int state);
void draw_bar(uint8_t c, uint8_t is_inverse);
void draw_ascii_row(uint8_t r, int start);
void connectDisplay();
void printCO2(int averageCO2);
void printCO2Store(int averageCO2Store , int displayTime);
void printDisplayTEXT(int displayTime, string text1, string text2, string text3);
void printTemperature(int temperature, int displayTime);
void printHumidity(int humidity, int displayTime);
void turnoffDisplay();
void printAlert(int displayTime);
void printAlertTemperature(int displayTime);
void printAlertCO2(int displayTime);
void printLoRaState(int displayTime, int state);
void printCOValue(int getCO2, int displayTime);
#endif
