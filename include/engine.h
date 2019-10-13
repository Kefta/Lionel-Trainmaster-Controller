#ifndef TRAIN_H_ENGINE
#define TRAIN_H_ENGINE
#pragma once

#include "interface.h"	// IEngine, SystemHandle, SystemSignedData, SystemUnsignedData

#define TRAIN_ENGINE_MAXADDRESS 127
#define TRAIN_ENGINE_MAXCOMMAND 127
#define TRAIN_ENGINE_ABSOLUTEMAXSPEED 31
#define TRAIN_ENGINE_RELATIVEMINSPEED -16
#define TRAIN_ENGINE_RELATIVEMAXSPEED 15

static const SystemUnsignedData Engine_MaxAddress = TRAIN_ENGINE_MAXADDRESS;
static const SystemUnsignedData Engine_MaxCommand = TRAIN_ENGINE_MAXCOMMAND;
static const SystemUnsignedData Engine_AbsoluteMaxSpeed = TRAIN_ENGINE_ABSOLUTEMAXSPEED;
static const SystemSignedData Engine_RelativeMinSpeed = TRAIN_ENGINE_RELATIVEMINSPEED;
static const SystemSignedData Engine_RelativeMaxSpeed = TRAIN_ENGINE_RELATIVEMAXSPEED;

void Engine_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Engine_ForwardDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_ToggleDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_ReverseDirection(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_Boost(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_Brake(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_OpenFrontCoupler(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_OpenRearCoupler(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_BlowHorn1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_RingBell(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_LetoffSound(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_BlowHorn2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX1Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX1Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX1Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX1On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX2Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX2Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX2Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AUX2On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);

void Engine_AssignToTrain(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uTrain /*[0, 31]*/);
void Engine_AssignSingleForward(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignSingleReverse(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignHeadEndForward(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignHeadEndReverse(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignMiddleForward(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignMiddleReverse(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignRearForward(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_AssignRearReverse(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_SetMomentumLow(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_SetMomentumMedium(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_SetMomentumHigh(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Engine_SetAddress(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);

void Engine_SetSpeed(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uAbsoluteSpeed /*[0, 31]*/);
void Engine_ChangeSpeed(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemSignedData uRelativeSpeed /*[-16, 15]*/);

static const struct IEngine Engine = {
	.MaxAddress = TRAIN_ENGINE_MAXADDRESS,
	.MaxCommand = TRAIN_ENGINE_MAXCOMMAND,
	.AbsoluteMaxSpeed = TRAIN_ENGINE_ABSOLUTEMAXSPEED,
	.RelativeMinSpeed = TRAIN_ENGINE_RELATIVEMINSPEED,
	.RelativeMaxSpeed = TRAIN_ENGINE_RELATIVEMAXSPEED,
	
	.SendCommand = Engine_SendCommand,
	
	.ForwardDirection = Engine_ForwardDirection,
	.ToggleDirection = Engine_ToggleDirection,
	.ReverseDirection = Engine_ReverseDirection,
	.Boost = Engine_Boost,
	.Brake = Engine_Brake,
	.OpenFrontCoupler = Engine_OpenFrontCoupler,
	.OpenRearCoupler = Engine_OpenRearCoupler,
	.BlowHorn1 = Engine_BlowHorn1,
	.RingBell = Engine_RingBell,
	.LetoffSound = Engine_LetoffSound,
	.BlowHorn2 = Engine_BlowHorn2,
	.AUX1Off = Engine_AUX1Off,
	.AUX1Option1 = Engine_AUX1Option1,
	.AUX1Option2 = Engine_AUX1Option2,
	.AUX1On = Engine_AUX1On,
	.AUX2Off = Engine_AUX2Off,
	.AUX2Option1 = Engine_AUX2Option1,
	.AUX2Option2 = Engine_AUX2Option2,
	.AUX2On = Engine_AUX2On,
	
	.AssignToTrain = Engine_AssignToTrain,
	.AssignSingleForward = Engine_AssignSingleForward,
	.AssignSingleReverse = Engine_AssignSingleReverse,
	.AssignHeadEndForward = Engine_AssignHeadEndForward,
	.AssignHeadEndReverse = Engine_AssignHeadEndReverse,
	.AssignMiddleForward = Engine_AssignMiddleForward,
	.AssignMiddleReverse = Engine_AssignMiddleReverse,
	.AssignRearForward = Engine_AssignRearForward,
	.AssignRearReverse = Engine_AssignRearReverse,
	.SetMomentumLow = Engine_SetMomentumLow,
	.SetMomentumMedium = Engine_SetMomentumMedium,
	.SetMomentumHigh = Engine_SetMomentumHigh,
	.SetAddress = Engine_SetAddress,
	
	.SetSpeed = Engine_SetSpeed,
	.ChangeSpeed = Engine_ChangeSpeed
};

#endif
