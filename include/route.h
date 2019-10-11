#ifndef TRAIN_H_ROUTE
#define TRAIN_H_ROUTE
#pragma once

#include "interface.h"	// IRoute, SystemHandle, SystemUnsignedData

static const SystemUnsignedData Route_MaxAddress = 31;
static const SystemUnsignedData Route_MaxCommand = 127;

void Route_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Route_Throw(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/);
void Route_Clear(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/);

static const struct IRoute Route = {
	.MaxAddress = Route_MaxAddress,
	.MaxCommand = Route_MaxCommand,
	
	.SendCommand = Route_SendCommand,
	
	.Throw = Route_Throw,
	.Clear = Route_Clear
};

#endif