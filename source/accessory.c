#include "interface.h"	// __TRAIN_SENDCOMMAND, __TRAIN_DATA, __TRAIN_UDATA

__TRAIN_SENDCOMMAND(Accessory_SendCommand, Accessory_MaxAddress, Accessory_MaxCommand, 0x8000 /*10000000 00000000*/)

#define __TRAIN_ACCESSORY_DATA(NAME, COMMAND) __TRAIN_DATA(Accessory_SendCommand, Accessory_MaxAddress)
#define __TRAIN_ACCESSORY_UDATA(NAME, COMMAND, MAX) __TRAIN_UDATA(Accessory_SendCommand, Accessory_MaxAddress)

__TRAIN_ACCESSORY_DATA(Accessory_AUX1Off, 8 /*0001000*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX1Option1, 9 /*0001001*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX1Option2, 10 /*0001010*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX1On, 11 /*0001011*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX2Off, 12 /*0001100*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX2Option1, 13 /*0001101*/)
__TRAIN_ACCESSORY_DATA(Accessory_AUX2Option2, 14 /*0001110*/) // This was printed as 0001111 but that is the same as Accessory_AUX2Off
__TRAIN_ACCESSORY_DATA(Accessory_AUX2Off, 15 /*0001111*/)
__TRAIN_ACCESSORY_DATA(Accessory_AllOff, 32 /*0100000*/)
__TRAIN_ACCESSORY_DATA(Accessory_AllOn, 47 /*0101111*/)
__TRAIN_ACCESSORY_DATA(Accessory_SetAddress, 43 /*0101011*/)
__TRAIN_ACCESSORY_UDATA(Accessory_AssignAUX1ToGroup, 32 /*0100000*/, Group_MaxAddress)
__TRAIN_ACCESSORY_UDATA(Accessory_AssignAUX2ToGroup, 48 /*0110000*/, Group_MaxAddress) // This was printed as 0100000 but that is the same as Accessory_AssignAUX1ToGroup
