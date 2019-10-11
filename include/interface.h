#ifndef TRAIN_H_INTERFACE
#define TRAIN_H_INTERFACE
#pragma once

#include <stdint.h>		// int8_t, uint8_t, uint16_t
#include <windows.h>	// HANDLE, INVALID_HANDLE_VALUE

_Static_assert(sizeof(int8_t) == 1, "int8_t is not 8 bits");
_Static_assert(sizeof(uint8_t) == 1, "uint8_t is not 8 bits");

// Uses the least significant bits in the specified range
typedef uint16_t SystemCommand;
typedef HANDLE SystemHandle;
typedef int8_t SystemSignedData;
typedef uint8_t SystemUnsignedData;

#define TRAIN_SYSTEM_INVALIDHANDLE INVALID_HANDLE_VALUE

struct ISwitch
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*ThrowThrough)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ThrowOut)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetAddress)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignToRouteThrough)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uRoute);
	void (*AssignToRouteOut)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uRoute);
};

struct IRoute
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*Throw)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Clear)(SystemHandle hSystem, SystemUnsignedData uAddress);
};

struct IEngine
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	const SystemUnsignedData AbsoluteMaxSpeed;
	const SystemSignedData RelativeMinSpeed;
	const SystemSignedData RelativeMaxSpeed;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*ForwardDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ToggleDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ReverseDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Boost)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Brake)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*OpenFrontCoupler)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*OpenRearCoupler)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*BlowHorn1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*RingBell)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*LetoffSound)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*BlowHorn2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1On)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2On)(SystemHandle hSystem, SystemUnsignedData uAddress);

	// Extended commands
	void (*AssignToTrain)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uTrain);
	void (*AssignSingleForward)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignSingleReverse)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignHeadEndForward)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignHeadEndReverse)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignMiddleForward)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignMiddleReverse)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignRearForward)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignRearReverse)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetMomentumLow)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetMomentumMedium)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetMomentumHigh)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetAddress)(SystemHandle hSystem, SystemUnsignedData uAddress);
	
	// Speed commands
	void (*SetSpeed)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uAbsoluteSpeed);
	void (*ChangeSpeed)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemSignedData uRelativeSpeed);
};

struct ITrain
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	const SystemUnsignedData AbsoluteMaxSpeed;
	const SystemSignedData RelativeMinSpeed;
	const SystemSignedData RelativeMaxSpeed;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*ForwardDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ToggleDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ReverseDirection)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Boost)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Brake)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*OpenFrontCoupler)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*OpenRearCoupler)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*BlowHorn1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*RingBell)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*LetoffSound)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*BlowHorn2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1On)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2On)(SystemHandle hSystem, SystemUnsignedData uAddress);

	// Extended commands
	void (*SetMomentumLow)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetMomentumMedium)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetMomentumHigh)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetAddress)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*ClearLashUp)(SystemHandle hSystem, SystemUnsignedData uAddress);
	
	// Speed commands
	void (*SetSpeed)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uAbsoluteSpeed);
	void (*ChangeSpeed)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uRelativeSpeed);
};

struct IAccessory
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*AUX1Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX1On)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AUX2On)(SystemHandle hSystem, SystemUnsignedData uAddress);
	
	// Extended commands
	void (*AllOff)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AllOn)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*SetAddress)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*AssignAUX1ToGroup)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uGroupID);
	void (*AssignAUX2ToGroup)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uGroupID);
};

struct IGroup
{
	const SystemUnsignedData MaxAddress;
	const SystemUnsignedData MaxCommand;
	
	void (*SendCommand)(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand);
	
	void (*Off)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Option1)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Option2)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*On)(SystemHandle hSystem, SystemUnsignedData uAddress);
	void (*Clear)(SystemHandle hSystem, SystemUnsignedData uAddress);
};

struct ISystem
{
	SystemHandle (*Create)(const char* sFile);
	void (*Close)(SystemHandle hSystem);
	
	void (*SendCommand)(SystemHandle hSystem, SystemCommand uCommand);

	void (*Halt)(SystemHandle hSystem);
	void (*NOP)(SystemHandle hSystem);
	//void (*_Reserved1)(SystemHandle hSystem);
	//void (*_Reserved2)(SystemHandle hSystem);
};

#ifdef TRAIN_OUTPUT_ERRORS
	#define __TRAIN_CHECKUNSIGNED(NUMBER, MIN, MAX, STREAM, ARG, NAME)														\
		if (CheckUnsigned(NUMBER, MIN, MAX))																				\
			PrintF(STREAM, "bad argument #%ju to '%s' (unsigned [%ju, %ju] expected, got %ju)", ARG, NAME, MIN, MAX, NUM);
#else
	#define __TRAIN_CHECKUNSIGNED(NUMBER, MIN, MAX, STREAM, ARG, NAME) CheckUnsigned(NUMBER, MIN, MAX)
#endif

#ifdef TRAIN_OUTPUT_ERRORS
	#define __TRAIN_CHECKSIGNED(NUMBER, MIN, MAX, STREAM, ARG, NAME)														\
		if (CheckSigned(NUMBER, MIN, MAX))																					\
			PrintF(STREAM, "bad argument #%jd to '%s' (unsigned [%jd, %jd] expected, got %jd)", ARG, NAME, MIN, MAX, NUM);
#else
	#define __TRAIN_CHECKSIGNED(NUMBER, MIN, MAX, STREAM, ARG, NAME) CheckSigned(NUMBER, MIN, MAX)
#endif

#define __TRAIN_SENDCOMMAND(NAME, MaxAddress, MaxCommand, TYPEID)										\
	inline void NAME(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uCommand)	\
	{																									\
		if (!__TRAIN_CHECKUNSIGNED(uAddress, 0, MaxAddress, stderr, 2, TOSTRING(NAME)))					\
			return;																						\
																										\
		if (!__TRAIN_CHECKUNSIGNED(uCommand, 0, MaxCommand, stderr, 3, TOSTRING(NAME)))					\
			return;																						\
																										\
		SystemCommand uSystemCommand = (SystemCommand)uCommand;											\
		uSystemCommand |= ((SystemCommand)uAddress << 7);												\
		uSystemCommand |= TYPEID;																		\
																										\
		System_SendCommand(hSystem, uSystemCommand);													\
	}

// Macro builder: must provide args NAME, COMMAND
#define __TRAIN_DATA(_SENDCOMMAND, _MAXADDRESS)											\
	inline void NAME(SystemHandle hSystem, SystemUnsignedData uAddress)					\
	{																					\
		if (!__TRAIN_CHECKUNSIGNED(uAddress, _MAXADDRESS, stderr, 2, TOSTRING(NAME)))	\
			return;																		\
																						\
		_SENDCOMMAND(hSystem, uAddress, COMMAND);										\
	}

// Macro builder: must provide args NAME, COMMAND, MAX
#define __TRAIN_UDATA(_SENDCOMMAND, _MAXADDRESS)													\
	inline void NAME(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uData)	\
	{																								\
		if (!__TRAIN_CHECKUNSIGNED(uAddress, 0, _MAXADDRESS, stderr, 2, TOSTRING(NAME)))			\
			return;																					\
																									\
		if (!__TRAIN_CHECKUNSIGNED(uData, 0, MAX, stderr, 3, TOSTRING(NAME)))						\
			return;																					\
																									\
		_SENDCOMMAND(hSystem, uAddress, uData | COMMAND);											\
	}

// Macro builder: must provide args NAME, COMMAND, MIN, MAX
#define __TRAIN_IDATA(_SENDCOMMAND, _MAXADDRESS)													\
	inline void NAME(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData iData)	\
	{																								\
		if (!__TRAIN_CHECKUNSIGNED(uAddress, _MAXADDRESS, stderr, 2, TOSTRING(NAME)))				\
			return;																					\
																									\
		if (!__TRAIN_CHECKSIGNED(iData, MIN, MAX, stderr, 3, TOSTRING(NAME)))						\
			return;																					\
																									\
		/* Reinterpret iData's bits as unsigned	*/													\
		_SENDCOMMAND(hSystem, uAddress, *((SomeUnsignedData*)&iData) | COMMAND);					\
	}

#endif
