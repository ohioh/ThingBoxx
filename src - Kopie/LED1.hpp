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
#ifndef LED1_HPP
#define LED1_HPP

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <cstddef>

void setLEDPins();
void setRGB();

//void setBlink(char color, byte times, unsigned int ms);

/*
void blinkRED(byte times, unsigned int ms);
void blinkGREEN(byte times, unsigned int ms);
void blinkBLUE(byte times, unsigned int ms);
void blinkWHITE(byte times, unsigned int ms);
*/

void blinkRED();
void blinkALERT();

void blinkLEDBuildin();

void blinkGREEN();
void blinkBLUE();
void blinkWHITE();
void blinkORANGE();

void mainCO22Signal(int averageCO2);

#endif
