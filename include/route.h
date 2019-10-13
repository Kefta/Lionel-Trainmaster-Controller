#ifndef TRAIN_H_ROUTE
#define TRAIN_H_ROUTE
#pragma once

#include "interface.h"	// IRoute, SystemHandle, SystemUnsignedData

#define TRAIN_ROUTE_MAXADDRESS 31
#define TRAIN_ROUTE_MAXCOMMAND 127

static const SystemUnsignedData Route_MaxAddress = TRAIN_ROUTE_MAXADDRESS;
static const SystemUnsignedData Route_MaxCommand = TRAIN_ROUTE_MAXCOMMAND;

void Route_SendCommand(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/, SystemUnsignedData uCommand /*[0, 127]*/);

void Route_Throw(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/);
void Route_Clear(SystemHandle hSystem, SystemUnsignedData uAddress /*[0, 31]*/);

static const struct IRoute Route = {
	.MaxAddress = TRAIN_ROUTE_MAXADDRESS,
	.MaxCommand = TRAIN_ROUTE_MAXCOMMAND,
	
	.SendCommand = Route_SendCommand,
	
	.Throw = Route_Throw,
	.Clear = Route_Clear
};

#endif