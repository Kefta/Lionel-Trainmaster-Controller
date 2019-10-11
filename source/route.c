#include "interface.h"	// __TRAIN_SENDCOMMAND, __TRAIN_DATA

__TRAIN_SENDCOMMAND(Route_SendCommand, Route_MaxAddress, Route_MaxCommand, 0xD000 /*11010000 00000000*/)

#define __TRAIN_ROUTE_DATA(NAME, COMMAND) __TRAIN_DATA(Route_SendCommand, Route_MaxAddress)

__TRAIN_ROUTE_DATA(Route_Throw, 31 /*0011111*/)
__TRAIN_ROUTE_DATA(Route_Clear, 44 /*0101100*/)
