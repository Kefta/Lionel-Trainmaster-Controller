#ifndef TRAIN_H_GROUP
#define TRAIN_H_GROUP
#pragma once

#include "interface.h"	// IGroup, SystemHandle, SystemUnsignedData

static const SystemUnsignedData Group_MaxAddress = 15;
static const SystemUnsignedData Group_MaxCommand = 127;

void Group_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Group_Off(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Group_Option1(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Group_Option2(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Group_On(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);
void Group_Clear(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 15]*/);

static const struct IGroup Group = {
	.MaxAddress = Group_MaxAddress,
	.MaxCommand = Group_MaxCommand,
	
	.SendCommand = Group_SendCommand,

	.Off = Group_Off,
	.Option1 = Group_Option1,
	.Option2 = Group_Option2,
	.On = Group_On,
	.Clear = Group_Clear,
};

#endif