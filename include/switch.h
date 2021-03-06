#ifndef TRAIN_H_SWITCH
#define TRAIN_H_SWITCH
#pragma once

#include "interface.h"	// ISwitch, SystemHandle, SystemUnsignedData

#define TRAIN_SWITCH_MAXADDRESS 127
#define TRAIN_SWITCH_MAXCOMMAND 127

static const SystemUnsignedData Switch_MaxAddress = TRAIN_SWITCH_MAXADDRESS;
static const SystemUnsignedData Switch_MaxCommand = TRAIN_SWITCH_MAXCOMMAND;

void Switch_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Switch_ThrowThrough(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_ThrowOut(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_SetAddress(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_AssignToRouteThrough(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uRouteID /*[0, 31]*/);
void Switch_AssignToRouteOut(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uRouteID /*[0, 31]*/);

static const struct ISwitch Switch = {
	.MaxAddress = TRAIN_SWITCH_MAXADDRESS,
	.MaxCommand = TRAIN_SWITCH_MAXCOMMAND,
	
	.SendCommand = Switch_SendCommand,
	
	.ThrowThrough = Switch_ThrowThrough,
	.ThrowOut = Switch_ThrowOut,
	.SetAddress = Switch_SetAddress,
	.AssignToRouteThrough = Switch_AssignToRouteThrough,
	.AssignToRouteOut = Switch_AssignToRouteOut
};

#endif