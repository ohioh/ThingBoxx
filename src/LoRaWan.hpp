/*##########################################################################################################
 *  LoRaWan.hpp
 *  Link: 
 * 
 * 
 * 
 * 
 * 
 * 
 * ########################################################################################################
 */
#ifndef LORAWAN_HPP
#define LORAWAN_HPP

#pragma once

#include <stdlib.h>
#include <stdint.h>

void decToBinary(int input);
void zennerParserPrepair();
void prepareTxFrame(uint8_t port);
void useLoRaWan();

#endif
