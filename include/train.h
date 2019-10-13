#ifndef TRAIN_H_TRAIN
#define TRAIN_H_TRAIN
#pragma once

#include "interface.h"	// ITrain, SystemHandle, SystemSignedData, SystemUnsignedData

#define TRAIN_TRAIN_MAXADDRESS 15
#define TRAIN_TRAIN_MAXCOMMAND 127
#define TRAIN_TRAIN_ABSOLUTEMAXSPEED 31
#define TRAIN_TRAIN_RELATIVEMINSPEED -16
#define TRAIN_TRAIN_RELATIVEMAXSPEED 15

static const SystemUnsignedData Train_MaxAddress = TRAIN_TRAIN_MAXADDRESS;
static const SystemUnsignedData Train_MaxCommand = TRAIN_TRAIN_MAXCOMMAND;
static const SystemUnsignedData Train_AbsoluteMaxSpeed = TRAIN_TRAIN_ABSOLUTEMAXSPEED;
static const SystemSignedData Train_RelativeMinSpeed = TRAIN_TRAIN_RELATIVEMINSPEED;
static const SystemSignedData Train_RelativeMaxSpeed = TRAIN_TRAIN_RELATIVEMAXSPEED;

void Train_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Train_ForwardDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_ToggleDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_ReverseDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_Boost(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_Brake(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_OpenFrontCoupler(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_OpenRearCoupler(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_BlowHorn1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_RingBell(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_LetoffSound(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_BlowHorn2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX1Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX1Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX1Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX1On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX2Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX2Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX2Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_AUX2On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);

void Train_SetMomentumLow(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_SetMomentumMedium(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_SetMomentumHigh(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_SetAddress(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Train_ClearLashUp(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);

void Train_SetSpeed(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/, SystemUnsignedData uAbsoluteSpeed /*[0, 31]*/);
void Train_ChangeSpeed(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/, SystemUnsignedData uRelativeSpeed /*[-16, 15]*/);

static const struct ITrain Train = {
	.MaxAddress = TRAIN_TRAIN_MAXADDRESS,
	.MaxCommand = TRAIN_TRAIN_MAXCOMMAND,
	.AbsoluteMaxSpeed = TRAIN_TRAIN_ABSOLUTEMAXSPEED,
	.RelativeMinSpeed = TRAIN_TRAIN_RELATIVEMINSPEED,
	.RelativeMaxSpeed = TRAIN_TRAIN_RELATIVEMAXSPEED,
	
	.SendCommand = Train_SendCommand,

	.ForwardDirection = Train_ForwardDirection,
	.ToggleDirection = Train_ToggleDirection,
	.ReverseDirection = Train_ReverseDirection,
	.Boost = Train_Boost,
	.Brake = Train_Brake,
	.OpenFrontCoupler = Train_OpenFrontCoupler,
	.OpenRearCoupler = Train_OpenRearCoupler,
	.BlowHorn1 = Train_BlowHorn1,
	.RingBell = Train_RingBell,
	.LetoffSound = Train_LetoffSound,
	.BlowHorn2 = Train_BlowHorn2,
	.AUX1Off = Train_AUX1Off,
	.AUX1Option1 = Train_AUX1Option1,
	.AUX1Option2 = Train_AUX1Option2,
	.AUX1On = Train_AUX1On,
	.AUX2Off = Train_AUX2Off,
	.AUX2Option1 = Train_AUX2Option1,
	.AUX2Option2 = Train_AUX2Option2,
	.AUX2On = Train_AUX2On,
	
	.SetMomentumLow = Train_SetMomentumLow,
	.SetMomentumMedium = Train_SetMomentumMedium,
	.SetMomentumHigh = Train_SetMomentumHigh,
	.SetAddress = Train_SetAddress,
	.ClearLashUp = Train_ClearLashUp,
	
	.SetSpeed = Train_SetSpeed,
	.ChangeSpeed = Train_ChangeSpeed
};

#endif
