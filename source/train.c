#include "interface.h"	// TRAIN_SENDCOMMAND, TRAIN_DATA, TRAIN_UDATA, TRAIN_IDATA

#include "train.h"

TRAIN_SENDCOMMAND(Train_SendCommand, TRAIN_TRAIN_MAXADDRESS, TRAIN_TRAIN_MAXCOMMAND, 0xC800 /*11001000 00000000*/)

#define TRAIN_TRAIN_DATA(NAME, COMMAND) TRAIN_DATA(NAME, COMMAND, Train_SendCommand, TRAIN_TRAIN_MAXADDRESS)
#define TRAIN_TRAIN_UDATA(NAME, COMMAND, MAX) TRAIN_UDATA(NAME, COMMAND, MAX, Train_SendCommand, TRAIN_TRAIN_MAXADDRESS)
#define TRAIN_TRAIN_IDATA(NAME, COMMAND, MIN, MAX) TRAIN_IDATA(NAME, COMMAND, MIN, MAX, Train_SendCommand, TRAIN_TRAIN_MAXADDRESS)

TRAIN_TRAIN_DATA(Train_ForwardDirection, 0 /*0000000*/)
TRAIN_TRAIN_DATA(Train_ToggleDirection, 1 /*0000001*/)
TRAIN_TRAIN_DATA(Train_ReverseDirection, 3 /*0000011*/)
TRAIN_TRAIN_DATA(Train_Boost, 4 /*0000100*/)
TRAIN_TRAIN_DATA(Train_Brake, 7 /*0000111*/)
TRAIN_TRAIN_DATA(Train_OpenFrontCoupler, 5 /*0000101*/)
TRAIN_TRAIN_DATA(Train_OpenRearCoupler, 6 /*0000110*/)
TRAIN_TRAIN_DATA(Train_BlowHorn1, 28 /*0011100*/)
TRAIN_TRAIN_DATA(Train_RingBell, 29 /*0011101*/)
TRAIN_TRAIN_DATA(Train_LetoffSound, 30 /*0011110*/)
TRAIN_TRAIN_DATA(Train_BlowHorn2, 31 /*0011111*/)
TRAIN_TRAIN_DATA(Train_AUX1Off, 8 /*0001000*/)
TRAIN_TRAIN_DATA(Train_AUX1Option1, 9 /*0001001*/)
TRAIN_TRAIN_DATA(Train_AUX1Option2, 10 /*0001010*/)
TRAIN_TRAIN_DATA(Train_AUX1On, 11 /*0001011*/)
TRAIN_TRAIN_DATA(Train_AUX2Off, 12 /*0001100*/)
TRAIN_TRAIN_DATA(Train_AUX2Option1, 13 /*0001101*/)
TRAIN_TRAIN_DATA(Train_AUX2Option2, 14 /*0001110*/)
TRAIN_TRAIN_DATA(Train_AUX2On, 15 /*0001111*/)

TRAIN_TRAIN_DATA(Train_SetMomentumLow, 40 /*0101000*/)
TRAIN_TRAIN_DATA(Train_SetMomentumMedium, 41 /*0101001*/)
TRAIN_TRAIN_DATA(Train_SetMomentumHigh, 42 /*0101010*/)
TRAIN_TRAIN_DATA(Train_SetAddress, 43 /*0101011*/)
TRAIN_TRAIN_DATA(Train_ClearLashUp, 44 /*0101100*/)

TRAIN_TRAIN_UDATA(Train_SetSpeed, 96 /*1100000*/, TRAIN_TRAIN_ABSOLUTEMAXSPEED)
TRAIN_TRAIN_IDATA(Train_ChangeSpeed, 64 /*1000000*/, TRAIN_TRAIN_RELATIVEMINSPEED, TRAIN_TRAIN_RELATIVEMAXSPEED)
