#include "interface.h"	// __TRAIN_SENDCOMMAND, __TRAIN_DATA, __TRAIN_UDATA, __TRAIN_IDATA

__TRAIN_SENDCOMMAND(Engine_SendCommand, TRAIN_ENGINE_MAXADDRESS, TRAIN_ENGINE_MAXCOMMAND, 0 /*00000000 00000000*/)

#define __TRAIN_ENGINE_DATA(NAME, COMMAND) __TRAIN_DATA(Engine_SendCommand, TRAIN_ENGINE_MAXADDRESS)
#define __TRAIN_ENGINE_UDATA(NAME, COMMAND, MAX) __TRAIN_UDATA(Engine_SendCommand, TRAIN_ENGINE_MAXADDRESS)
#define __TRAIN_ENGINE_IDATA(NAME, COMMAND, MIN, MAX) __TRAIN_IDATA(Engine_SendCommand, TRAIN_ENGINE_MAXADDRESS)

__TRAIN_ENGINE_DATA(Engine_ForwardDirection, 0 /*0000000*/)
__TRAIN_ENGINE_DATA(Engine_ToggleDirection, 1 /*0000001*/)
__TRAIN_ENGINE_DATA(Engine_ReverseDirection, 3 /*0000011*/)
__TRAIN_ENGINE_DATA(Engine_Boost, 4 /*0000100*/)
__TRAIN_ENGINE_DATA(Engine_Brake, 7 /*0000111*/)
__TRAIN_ENGINE_DATA(Engine_OpenFrontCoupler, 5 /*0000101*/)
__TRAIN_ENGINE_DATA(Engine_OpenRearCoupler, 6 /*0000110*/)
__TRAIN_ENGINE_DATA(Engine_BlowHorn1, 28 /*0011100*/)
__TRAIN_ENGINE_DATA(Engine_RingBell, 29 /*0011101*/)
__TRAIN_ENGINE_DATA(Engine_LetoffSound, 30 /*0011110*/)
__TRAIN_ENGINE_DATA(Engine_BlowHorn2, 31 /*0011111*/)
__TRAIN_ENGINE_DATA(Engine_AUX1Off, 8 /*0001000*/)
__TRAIN_ENGINE_DATA(Engine_AUX1Option1, 9 /*0001001*/)
__TRAIN_ENGINE_DATA(Engine_AUX1Option2, 10 /*0001010*/)
__TRAIN_ENGINE_DATA(Engine_AUX1On, 11 /*0001011*/)
__TRAIN_ENGINE_DATA(Engine_AUX2Off, 12 /*0001100*/)
__TRAIN_ENGINE_DATA(Engine_AUX2Option1, 13 /*0001101*/)
__TRAIN_ENGINE_DATA(Engine_AUX2Option2, 14 /*0001110*/)
__TRAIN_ENGINE_DATA(Engine_AUX2On, 15 /*0001111*/)

__TRAIN_ENGINE_UDATA(Engine_AssignToTrain, 48 /*0110000*/, TRAIN_TRAIN_MAXADDRESS)
__TRAIN_ENGINE_DATA(Engine_AssignSingleForward, 32 /*0100000*/)
__TRAIN_ENGINE_DATA(Engine_AssignSingleReverse, 36 /*0100100*/)
__TRAIN_ENGINE_DATA(Engine_AssignHeadEndForward, 33 /*0100001*/)
__TRAIN_ENGINE_DATA(Engine_AssignHeadEndReverse, 37 /*0100101*/)
__TRAIN_ENGINE_DATA(Engine_AssignMiddleForward, 34 /*0100010*/)
__TRAIN_ENGINE_DATA(Engine_AssignMiddleReverse, 38 /*0100110*/)
__TRAIN_ENGINE_DATA(Engine_AssignRearForward, 35 /*0100011*/)
__TRAIN_ENGINE_DATA(Engine_AssignRearReverse, 39 /*0100111*/)
__TRAIN_ENGINE_DATA(Engine_SetMomentumLow, 40 /*0101000*/)
__TRAIN_ENGINE_DATA(Engine_SetMomentumMedium, 41 /*0101001*/)
__TRAIN_ENGINE_DATA(Engine_SetMomentumHigh, 42 /*0101010*/)
__TRAIN_ENGINE_DATA(Engine_SetAddress, 43 /*0101011*/)

__TRAIN_ENGINE_UDATA(Engine_SetSpeed, 96 /*1100000*/, TRAIN_ENGINE_ABSOLUTEMAXSPEED)
__TRAIN_ENGINE_IDATA(Engine_ChangeSpeed, 64 /*1000000*/, TRAIN_ENGINE_RELATIVEMINSPEED, TRAIN_ENGINE_RELATIVEMAXSPEED)