#ifndef TRAIN_H_SYSTEM
#define TRAIN_H_SYSTEM
#pragma once

#include "interface.h"	// ISystem, SystemCommand, SystemHandle

SystemHandle System_Create(const char* sFile);
void System_Close(SystemHandle hSystem);

void System_SendCommand(SystemHandle hSystem, SystemCommand uCommand);

void System_Halt(SystemHandle hSystem);
void System_NOP(SystemHandle hSystem);
void System__Reserved1(SystemHandle hSystem);
void System__Reserved2(SystemHandle hSystem);

static const struct ISystem System = {
	.Create = System_Create,
	.Close = System_Close,
	
	.SendCommand = System_SendCommand,

	.Halt = System_Halt,
	.NOP = System_NOP
	//._Reserved1 = System__Reserved1,
	//._Reserved2 = System__Reserved2
};

#endif
