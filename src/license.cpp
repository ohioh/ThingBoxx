#include "license.hpp"

#include <stdlib.h>
#include <stdint.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 1
//
//
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 2
//
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 3
//
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 4
//
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 5
// ORT: D07B6D60A124 

  uint32_t license[4] = {0x1F422496,0x5E714199,0x9C1DE407,0x88258332};

  uint8_t DevEui[] = {0x14, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x14, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x14, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 6
// ORT: DC796D60A124
/*
  uint32_t license[4] = {0xBB74D4A2,0x7E5A9D69,0xD4AF87EF,0x9910D37F};

  uint8_t DevEui[] = {0x15, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x15, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x15, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 7
// ORT: 607B6D60A124
/*
  uint32_t license[4] = {0x600FA411,0x9E7B4194,0x97FAA422,0x1925133E};

  uint8_t DevEui[] = {0x16, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x16, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x16, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 8
// ORT: BC7B6D60A124
/*
uint32_t license[4] = {0x60F6240C, 0x3E6D416F, 0x949AE4E5, 0xB90F8339};

uint8_t DevEui[] = {0x17, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
uint8_t AppEui[] = {0x17, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
uint8_t AppKey[] = {0x17, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 9
// ORT: Turnhalle2_c009 2C7B6D60A124
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Case 10
//
/*
  uint32_t license[4] = {0x5F6DA48B, 0x6E6C4166, 0x9498A7D8, 0x1D131335};

  uint8_t DevEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppEui[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x12};
  uint8_t AppKey[] = {0x18, 0x34, 0x56, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x12};
*/
