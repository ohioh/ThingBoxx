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
#ifndef LED_HPP
#define LED_HPP

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

void blinkRED(uint16_t times, uint16_t ms);

void blinkALERT(uint16_t times, uint16_t ms);

void blinkLEDBuildin();

void blinkGREEN(uint16_t times, uint16_t ms);
void blinkBLUE(uint16_t times, uint16_t ms);
void blinkWHITE(uint16_t times, uint16_t ms);
void blinkORANGE(uint16_t times, uint16_t ms);

#endif
