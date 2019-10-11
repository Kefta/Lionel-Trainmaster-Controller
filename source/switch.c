#include "interface.h"	// __TRAIN_SENDCOMMAND, __TRAIN_DATA, __TRAIN_UDATA

__TRAIN_SENDCOMMAND(Switch_SendCommand, Switch_MaxAddress, Switch_MaxCommand, 0x4000 /*01000000 00000000*/)

#define __TRAIN_SWITCH_DATA(NAME, COMMAND) __TRAIN_DATA(Switch_SendCommand, Switch_MaxAddress)
#define __TRAIN_SWITCH_UDATA(NAME, COMMAND, MAX) __TRAIN_UDATA(Switch_SecondCommand, Switch_MaxAddress)

__TRAIN_SWITCH_DATA(Switch_ThrowThrough, 0 /*0000000*/)
__TRAIN_SWITCH_DATA(Switch_ThrowOut, 31 /*0011111*/)
__TRAIN_SWITCH_DATA(Switch_SetAddress, 43 /*0101011*/)
__TRAIN_SWITCH_UDATA(Switch_AssignToRouteThrough, 64 /*1000000*/, Route_MaxAddress)
__TRAIN_SWITCH_UDATA(Switch_AssignToRouteOut, 96 /*1100000*/, Route_MaxAddress)
