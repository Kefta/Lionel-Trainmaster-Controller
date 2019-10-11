#include "interface.h"	// __TRAIN_SENDCOMMAND, __TRAIN_DATA

__TRAIN_SENDCOMMAND(Group_SendCommand, Group_MaxAddress, Group_MaxCommand, 0xC000 /*11000000 00000000*/)

#define __TRAIN_GROUP_DATA(NAME, COMMAND) __TRAIN_DATA(Group_SendCommand, Group_MaxAddress)

__TRAIN_GROUP_DATA(Group_Off, 8 /*0001000*/)
__TRAIN_GROUP_DATA(Group_Option1, 9 /*0001001*/)
__TRAIN_GROUP_DATA(Group_Option2, 10 /*0001010*/) // This was printed as 0001011 but that is the same as Group_On
__TRAIN_GROUP_DATA(Group_On, 11 /*0001011*/)
__TRAIN_GROUP_DATA(Group_Clear, 44 /*0101100*/)
