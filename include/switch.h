#ifndef TRAIN_H_SWITCH
#define TRAIN_H_SWITCH
#pragma once

#include "interface.h"	// ISwitch, SystemHandle, SystemUnsignedData

static const SystemUnsignedData Switch_MaxAddress = 127;
static const SystemUnsignedData Switch_MaxCommand = 127;

void Switch_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Switch_ThrowThrough(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_ThrowOut(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_SetAddress(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/);
void Switch_AssignToRouteThrough(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uRouteID /*[0, 31]*/);
void Switch_AssignToRouteOut(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 127]*/, SystemUnsignedData uRouteID /*[0, 31]*/);

static const struct ISwitch Switch = {
	.MaxAddress = Switch_MaxAddress,
	.MaxCommand = Switch_MaxCommand,
	
	.SendCommand = Switch_SendCommand,
	
	.ThrowThrough = Switch_ThrowThrough,
	.ThrowOut = Switch_ThrowOut,
	.SetAddress = Switch_SetAddress,
	.AssignToRouteThrough = Switch_AssignToRouteThrough,
	.AssignToRouteOut = Switch_AssignToRouteOut
};

#endif