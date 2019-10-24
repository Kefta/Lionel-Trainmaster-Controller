// -std=c11					// _Static_assert, anonymous unions inside of structs
// <windows.h> support		// BOOL, BYTE, CloseHandle, CreateFile, DWORD, FALSE, FILE_ATTRIBUTE_NORMAL, GENERIC_WRITE, LPCVOID, OPEN_EXISTING, TRUE, WriteFile

#include <stdio.h>			// stderr
#include <stdlib.h>			// EXIT_*

#include "accessory.h"		// Accessory
#include "config.h"			// TRAIN_OUTPUT_ERRORS, TRAIN_OUTPUT_EXIT
#include "engine.h"			// Engine
#include "group.h"			// Group
#include "interface.h"		// SystemCommand, SystemHandle, SystemSignedData, SystemUnsignedData
#include "menu.h"			// Menu_Option, Menu_Phrases, MENU_*
#include "route.h"			// Route
#include "switch.h"			// Switch
#include "system.h"			// System
#include "train.h"			// Train
#include "util.h"			// ARRAY_SIZE, PrintN


#define TRAIN_MENU(NAME, ...)					\
	const struct Menu_Option NAME##Menu[] = {	\
		__VA_ARGS__,							\
		TRAIN_MENU_RETURN("Return"),			\
		TRAIN_MENU_EXIT("Exit")					\
	};

#define TRAIN_MENU_COMPONENT(NAME, ...)											\
	TRAIN_MENU(NAME, __VA_ARGS__,												\
		TRAIN_MENU_SEPARATOR,													\
		TRAIN_MENU_COMMAND("Send command", NAME.SendCommand, NAME.MaxAddress),	\
		TRAIN_MENU_SEPARATOR)

// Non-inherit commands for the assignment menu
void AccelerateTrain(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uSpeed)
{
	Engine.ChangeSpeed(hSystem, uAddress, (SystemSignedData)uSpeed);
}

void DecelerateTrain(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uSpeed)
{
	Engine.ChangeSpeed(hSystem, uAddress, -(SystemSignedData)uSpeed);
}

void StopTrain(SystemHandle hSystem, SystemUnsignedData uAddress)
{
	Engine.SetSpeed(hSystem, uAddress, 0);
}

int main()
{
	SystemHandle hSystem = System.Create(TRAIN_HANDLE_FILE);

	if (hSystem == TRAIN_SYSTEM_INVALIDHANDLE)
	{
		#ifdef TRAIN_OUTPUT_ERRORS
			PrintN(stderr, "Failed to open serial port @ \"" TRAIN_HANDLE_FILE "\"");
		#endif
		
		#ifdef TRAIN_OUTPUT_EXIT
			PrintN(stdout, "Exiting with error");
		#endif
		
		return EXIT_FAILURE;
	}
	
	const struct Menu_Phrases tPhrases = {
		.MenuPrefix = NULL,
		.MenuSuffix = "Choice: ",
		.UnsignedData = "Amount [%zu, %zu]: ",
		.SignedData = "Amount [%zd, %zd]: ",
		.Address = "%s address [0, %zu]: ",
		.Command = "%s command as an integer [0, %zu]: ",
		.SystemCommand = "%s command as an integer [0, %zu]: "
	};
	
	TRAIN_MENU(Assignment,
		TRAIN_MENU_ADDRESS("Ring bell", Engine.RingBell),
		TRAIN_MENU_ADDRESS("Start train", Engine.SetMomentumLow),
		TRAIN_MENU_UDATA("Accelerate train", AccelerateTrain, 0, (SystemUnsignedData)(Engine.RelativeMaxSpeed)),
		TRAIN_MENU_ADDRESS("Move train", Engine.SetMomentumHigh),
		TRAIN_MENU_UDATA("Decelerate train", DecelerateTrain, 0, (SystemUnsignedData)(-Engine.RelativeMinSpeed)), // FIXME: What if this number is positive?
		TRAIN_MENU_ADDRESS("Stop train", StopTrain))

	TRAIN_MENU_COMPONENT(Switch,
		TRAIN_MENU_ADDRESS("throw THROUGH", Switch.ThrowThrough),
		TRAIN_MENU_ADDRESS("throw OUT", Switch.ThrowOut),
		TRAIN_MENU_ADDRESS("set address", Switch.SetAddress),
		TRAIN_MENU_UDATA("assign to route THROUGH", Switch.AssignToRouteThrough, 0, Route.MaxAddress),
		TRAIN_MENU_UDATA("assign to route OUT", Switch.AssignToRouteOut, 0, Route.MaxAddress))

	TRAIN_MENU_COMPONENT(Route,
		TRAIN_MENU_ADDRESS("Route throw", Route.Throw),
		TRAIN_MENU_ADDRESS("Route clear", Route.Clear))

	TRAIN_MENU_COMPONENT(Engine,
		TRAIN_MENU_ADDRESS("forward direction", Engine.ForwardDirection),
		TRAIN_MENU_ADDRESS("toggle Direction", Engine.ToggleDirection),
		TRAIN_MENU_ADDRESS("reverse direction", Engine.ReverseDirection),
		TRAIN_MENU_ADDRESS("Boost", Engine.Boost),
		TRAIN_MENU_ADDRESS("Brake", Engine.Brake),
		TRAIN_MENU_ADDRESS("open Front coupler", Engine.OpenFrontCoupler),
		TRAIN_MENU_ADDRESS("open Rear coupler", Engine.OpenRearCoupler),
		TRAIN_MENU_ADDRESS("blow Horn 1", Engine.BlowHorn1),
		TRAIN_MENU_ADDRESS("ring Bell", Engine.RingBell),
		TRAIN_MENU_ADDRESS("letoff sound", Engine.LetoffSound),
		TRAIN_MENU_ADDRESS("blow Horn 2", Engine.BlowHorn2),
		TRAIN_MENU_ADDRESS("AUX1 off", Engine.AUX1Off),
		TRAIN_MENU_ADDRESS("AUX1 option 1 (CAB AUX1 button)", Engine.AUX1Option1),
		TRAIN_MENU_ADDRESS("AUX1 option 2", Engine.AUX1Option2),
		TRAIN_MENU_ADDRESS("AUX1 on", Engine.AUX1On),
		TRAIN_MENU_ADDRESS("AUX2 off", Engine.AUX2Off),
		TRAIN_MENU_ADDRESS("AUX2 option 1 (CAB AUX2 button)", Engine.AUX2Option1),
		TRAIN_MENU_ADDRESS("AUX2 option 2", Engine.AUX2Option2),
		TRAIN_MENU_ADDRESS("AUX2 on", Engine.AUX2On),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_UDATA("assign to Train", Engine.AssignToTrain, 0, Train.MaxAddress),
		TRAIN_MENU_ADDRESS("assign as single unit forward direction", Engine.AssignSingleForward),
		TRAIN_MENU_ADDRESS("assign as single unit reverse direction", Engine.AssignSingleReverse),
		TRAIN_MENU_ADDRESS("assign as head-end unit forward direction", Engine.AssignHeadEndForward),
		TRAIN_MENU_ADDRESS("assign as head-end unit reverse direction", Engine.AssignHeadEndReverse),
		TRAIN_MENU_ADDRESS("assign as middle unit forward direction", Engine.AssignMiddleForward),
		TRAIN_MENU_ADDRESS("assign as middle unit reverse direction", Engine.AssignMiddleReverse),
		TRAIN_MENU_ADDRESS("assign as rear unit forward direction", Engine.AssignRearForward),
		TRAIN_MENU_ADDRESS("assign as rear unit reverse direction", Engine.AssignRearReverse),
		TRAIN_MENU_ADDRESS("set Momentum low", Engine.SetMomentumLow),
		TRAIN_MENU_ADDRESS("set Momentum medium", Engine.SetMomentumMedium),
		TRAIN_MENU_ADDRESS("set Momentum high", Engine.SetMomentumHigh),
		TRAIN_MENU_ADDRESS("set address", Engine.SetAddress),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_UDATA("set absolute speed", Engine.SetSpeed, 0, Engine.AbsoluteMaxSpeed),
		TRAIN_MENU_IDATA("change speed relative", Engine.ChangeSpeed, Engine.RelativeMinSpeed, Engine.RelativeMaxSpeed))

	TRAIN_MENU_COMPONENT(Train,
		TRAIN_MENU_ADDRESS("forward direction", Train.ForwardDirection),
		TRAIN_MENU_ADDRESS("toggle Direction", Train.ToggleDirection),
		TRAIN_MENU_ADDRESS("reverse direction", Train.ReverseDirection),
		TRAIN_MENU_ADDRESS("Boost", Train.Boost),
		TRAIN_MENU_ADDRESS("Brake", Train.Brake),
		TRAIN_MENU_ADDRESS("open Front coupler", Train.OpenFrontCoupler),
		TRAIN_MENU_ADDRESS("open Rear coupler", Train.OpenRearCoupler),
		TRAIN_MENU_ADDRESS("blow Horn 1", Train.BlowHorn1),
		TRAIN_MENU_ADDRESS("ring Bell", Train.RingBell),
		TRAIN_MENU_ADDRESS("letoff sound", Train.LetoffSound),
		TRAIN_MENU_ADDRESS("blow Horn 2", Train.BlowHorn2),
		TRAIN_MENU_ADDRESS("AUX1 off", Train.AUX1Off),
		TRAIN_MENU_ADDRESS("AUX1 option 1 (CAB AUX1 button)", Train.AUX1Option1),
		TRAIN_MENU_ADDRESS("AUX1 option 2", Train.AUX1Option2),
		TRAIN_MENU_ADDRESS("AUX1 on", Train.AUX1On),
		TRAIN_MENU_ADDRESS("AUX2 off", Train.AUX2Off),
		TRAIN_MENU_ADDRESS("AUX2 option 1 (CAB AUX2 button)", Train.AUX2Option1),
		TRAIN_MENU_ADDRESS("AUX2 option 2", Train.AUX2Option2),
		TRAIN_MENU_ADDRESS("AUX2 on", Train.AUX2On),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_ADDRESS("set Momentum low", Train.SetMomentumLow),
		TRAIN_MENU_ADDRESS("set Momentum medium", Train.SetMomentumMedium),
		TRAIN_MENU_ADDRESS("set Momentum high", Train.SetMomentumHigh),
		TRAIN_MENU_ADDRESS("set address", Train.SetAddress),
		TRAIN_MENU_ADDRESS("clear lash-up", Train.ClearLashUp),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_UDATA("set absolute speed", Train.SetSpeed, 0, Train.AbsoluteMaxSpeed),
		TRAIN_MENU_IDATA("change speed relative", Train.ChangeSpeed, Train.RelativeMinSpeed, Train.RelativeMaxSpeed))

	TRAIN_MENU_COMPONENT(Accessory,
		TRAIN_MENU_ADDRESS("AUX1 off", Accessory.AUX1Off),
		TRAIN_MENU_ADDRESS("AUX1 option 1", Accessory.AUX1Option1),
		TRAIN_MENU_ADDRESS("AUX1 option 2", Accessory.AUX1Option2),
		TRAIN_MENU_ADDRESS("AUX1 on", Accessory.AUX1On),
		TRAIN_MENU_ADDRESS("AUX2 off", Accessory.AUX2Off),
		TRAIN_MENU_ADDRESS("AUX2 option 1", Accessory.AUX2Option1),
		TRAIN_MENU_ADDRESS("AUX2 option 2", Accessory.AUX2Option2),
		TRAIN_MENU_ADDRESS("AUX2 on", Accessory.AUX2On),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_ADDRESS("all off", Accessory.AllOff),
		TRAIN_MENU_ADDRESS("all on", Accessory.AllOn),
		TRAIN_MENU_ADDRESS("set address", Accessory.SetAddress),
		TRAIN_MENU_UDATA("assign AUX1 to group", Accessory.AssignAUX1ToGroup, 0, Group.MaxAddress),
		TRAIN_MENU_UDATA("assign AUX2 to group", Accessory.AssignAUX2ToGroup, 0, Group.MaxAddress))

	TRAIN_MENU_COMPONENT(Group,
		TRAIN_MENU_ADDRESS("off", Group.Off),
		TRAIN_MENU_ADDRESS("option 1", Group.Option1),
		TRAIN_MENU_ADDRESS("option 2", Group.Option2),
		TRAIN_MENU_ADDRESS("on", Group.On),
		TRAIN_MENU_ADDRESS("clear", Group.Clear))

	TRAIN_MENU(System,
		TRAIN_MENU_SYSCOMMAND("Send command", System.SendCommand, 65535),
		TRAIN_MENU_SIMPLE("Halt", System.Halt),
		TRAIN_MENU_SIMPLE("NOP", System.NOP),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_SIMPLE("Reserved 11111110 11111111", System__Reserved1),
		TRAIN_MENU_SIMPLE("Reserved 11111111 11111110", System__Reserved2))

	TRAIN_MENU(Component,
		TRAIN_MENU_MENU("Switch", SwitchMenu),
		TRAIN_MENU_MENU("Route", RouteMenu),
		TRAIN_MENU_MENU("Engine", EngineMenu),
		TRAIN_MENU_MENU("Train", TrainMenu),
		TRAIN_MENU_MENU("Accessory", AccessoryMenu),
		TRAIN_MENU_MENU("Group", GroupMenu),
		TRAIN_MENU_MENU("System", SystemMenu))

	const struct Menu_Option StartMenu[] = {
		TRAIN_MENU_MENU("Assignment 2", AssignmentMenu),
		TRAIN_MENU_MENU("Full Command Menu", ComponentMenu),
		TRAIN_MENU_SEPARATOR,
		TRAIN_MENU_EXIT("Exit")
	};
	
	switch (Menu_ParseInput(stdout, stdin, stderr, hSystem, tPhrases, StartMenu, ARRAY_SIZE(StartMenu)))
	{
		#ifdef TRAIN_OUTPUT_EXIT
			case INPUT_SUCCESS:
				PrintN(stdout, "Exiting gracefully");
			break;
			
			case INPUT_FAIL:
				PrintN(stdout, "Exiting with error");
			break;
			
			case INPUT_EOF:
				PrintN(stdout, "Exiting from reaching EOF");
			break;
		#endif
	}
	
	System.Close(hSystem);
	
	return EXIT_SUCCESS;
}
