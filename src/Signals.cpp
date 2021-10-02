/*##########################################################################################################
    Alert.cpp
    Task: Takes the original messurment Data and controll the exceed to create visual Alert Signal

    _dangerLevel
    _riskLevel
    _dangerLevel
   ########################################################################################################
*/

//    CO2: 375-450   ppm is normal outdoor air ( ppm = parts per million )
//         450-800   ppm good air quality
//         800-1000  ppm acceptable
//         1000-1500 ppm infection risc high
//         1000-2000 ppm infection risc very high
//         2000-5000 ppm without infection risk not longer then 8 hours
//         5000-6000 ppm Questionable for health
//         6000+     ppm high risk for health (100k dangerous for life, 200k deadly)

#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>

#include "Variables.hpp"
#include "Signals.hpp"
#include "Display.hpp"
#include "LED.hpp"
