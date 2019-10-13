#ifndef TRAIN_H_ACCESSORY
#define TRAIN_H_ACCESSORY
#pragma once

#include "interface.h"	// IAccessory, SystemHandle, SystemUnsignedData

#define TRAIN_ACCESSORY_MAXADDRESS 127
#define TRAIN_ACCESSORY_MAXCOMMAND 127

static const SystemUnsignedData Accessory_MaxAddress = TRAIN_ACCESSORY_MAXADDRESS;
static const SystemUnsignedData Accessory_MaxCommand = TRAIN_ACCESSORY_MAXCOMMAND;

void Accessory_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Accessory_AUX1Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX1Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX1Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX1On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX2Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX2Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX2Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AUX1On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);

void Accessory_AllOff(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AllOn(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_SetAddress(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Accessory_AssignAUX1ToGroup(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uGroupID /*[0, 15]*/);
void Accessory_AssignAUX2ToGroup(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uGroupID /*[0, 15]*/);

static const struct IAccessory Accessory = {
	.MaxAddress = TRAIN_ACCESSORY_MAXADDRESS,
	.MaxCommand = TRAIN_ACCESSORY_MAXCOMMAND,
	
	.SendCommand = Accessory_SendCommand,
	
	.AUX1Off = Accessory_AUX1Off,
	.AUX1Option1 = Accessory_AUX1Option1,
	.AUX1Option2 = Accessory_AUX1Option2,
	.AUX1On = Accessory_AUX1On,
	.AUX2Option1 = Accessory_AUX2Off,
	.AUX2Off = Accessory_AUX2Option1,
	.AUX2Option2 = Accessory_AUX2Option2,
	.AUX2On = Accessory_AUX1On,
	
	.AllOff = Accessory_AllOff,
	.AllOn = Accessory_AllOn,
	.SetAddress = Accessory_SetAddress,
	.AssignAUX1ToGroup = Accessory_AssignAUX1ToGroup,
	.AssignAUX2ToGroup = Accessory_AssignAUX2ToGroup
};

#endif