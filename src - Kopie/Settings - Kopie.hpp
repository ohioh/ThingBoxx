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
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <ESP32_LoRaWAN.h>

extern uint32_t license[4];
extern uint8_t DevEui[];
extern uint8_t AppKey[];
extern uint8_t AppEui[];

extern uint8_t NwkSKey[];
extern uint8_t AppSKey[];
extern uint32_t DevAddr;

extern uint16_t userChannelsMask[6];
extern DeviceClass_t loraWanClass;
extern uint32_t appTxDutyCycle;
extern bool overTheAirActivation;
extern bool loraWanAdr;
extern bool isTxConfirmed;
extern uint8_t appPort;
extern uint64_t chipid;

extern uint8_t confirmedNbTrials;
extern uint8_t debugLevel;
extern  LoRaMacRegion_t loraWanRegion;

#endif
