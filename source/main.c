/* TODO:
	- Add option to cancel choices with .
	- Remove windows.h dependence on everything but handles (define bools and bytes)
	- Add proper size asserts
	- Bit optimisations in commands
*/

//-std=c11					// _Static_assert, anonymous unions inside of structs

#include <stdio.h>			// stderr
#include <stdlib.h>			// EXIT_*

#include "accessory.h"		// Accessory
#include "engine.h"			// Engine
#include "group.h"			// Group
#include "interface.h"		// SystemCommand, SystemHandle, SystemSignedData, SystemUnsignedData
#include "menu.h"			// CommandMenu_Option, CommandMenu_Phrases, MENU_*
#include "route.h"			// Route
#include "switch.h"			// Switch
#include "system.h"			// System
#include "train.h"			// Train
#include "util.h"			// ARRAY_SIZE, PrintN

//// Config ////

#define TRAIN_FILE "\\\\.\\COM1"

// FIXME
//#define TRAIN_TEMPHANDLE		// Define to close the handle after a command has been sent and the program is awaiting user input
#define TRAIN_OUTPUT_COMMANDS	// Define to print successful command output
#define TRAIN_OUTPUT_ERRORS		// Define to print command errors
#define TRAIN_OUTPUT_MENU		// Define to print menu options

//// Config ////


#define __TRAIN_COMMANDMENU(NAME, ...)					\
	const struct CommandMenu_Option NAME##Menu[] = {	\
		__VA_ARGS__,									\
		{""},											\
		{"Return", MENU_RETURN},						\
		{"Exit", MENU_EXIT}								\
	};

#define __TRAIN_COMMANDMENU_COMPONENT(NAME, ...)								\
	__TRAIN_COMMANDMENU(NAME##Command, __VA_ARGS__,								\
		{""},																	\
		{"Send command", MENU_COMMAND, {NAME.SendCommand, NAME.MaxAddress}})

#define __TRAIN_COMMANDMENU_MENU(NAME) {NAME, ARRAY_SIZE(NAME)}

// Non inherit commands
void DecelerateTrain(SystemHandle hSystem, SystemUnsignedData uAddress, SystemUnsignedData uSpeed)
{
	Train.ChangeSpeed(hSystem, uAddress, -(SystemSignedData)uSpeed);
}

void StopTrain(SystemHandle hSystem, SystemUnsignedData uAddress)
{
	Train.SetSpeed(hSystem, uAddress, 0);
}

int main()
{
	SystemHandle hSystem = System.Create(TRAIN_FILE);

	if (hSystem == TRAIN_SYSTEM_INVALIDHANDLE)
	{
		#ifdef TRAIN_OUTPUT_ERRORS
			PrintN(stderr, "Failed to open serial port @ \"" TRAIN_FILE "\"");
		#endif
		
		return EXIT_FAILURE;
	}
	
	const struct CommandMenu_Phrases tPhrases = {
		.MenuPrefix = NULL,
		.MenuSuffix = "Choice: ",
		.UnsignedData = "Amount [0, %zu]: ",
		.SignedData = "Amount [%zd, %zd]: ",
		.Address = "%s address [0, %zu]: ",
		.Command = "%s command as an integer [0, %zu]: ",
		.SystemCommand = "%s command as an integer [0, %zu]: "
	};
	
	__TRAIN_COMMANDMENU(Assignment,
		{"Ring bell", MENU_SIMPLE, {Train.RingBell}},
		{"Start train", MENU_SIMPLE, {Train.SetMomentumLow}},
		{"Accelerate train", MENU_UDATA, {Train.ChangeSpeed, (SystemUnsignedData)(Train.RelativeMaxSpeed)}},
		{"Move train", MENU_SIMPLE, {Train.SetMomentumHigh}},
		{"Decelerate train", MENU_UDATA, {DecelerateTrain, (SystemUnsignedData)(-Train.RelativeMinSpeed)}},
		{"Stop train", MENU_SIMPLE, {StopTrain}})

	__TRAIN_COMMANDMENU_COMPONENT(Switch,
		{"throw THROUGH", MENU_SIMPLE, {Switch.ThrowThrough}},
		{"throw OUT", MENU_SIMPLE, {Switch.ThrowOut}},
		{"set address", MENU_SIMPLE, {Switch.SetAddress}},
		{"assign to route THROUGH", MENU_UDATA, {Switch.ThrowThrough, Route.MaxAddress}},
		{"assign to route OUT", MENU_UDATA, {Switch.ThrowOut, Route.MaxAddress}})

	__TRAIN_COMMANDMENU_COMPONENT(Route,
		{"Route throw", MENU_SIMPLE, {Route.Throw}},
		{"Route clear", MENU_SIMPLE, {Route.Clear}})

	__TRAIN_COMMANDMENU_COMPONENT(Engine,
		{"forward direction", MENU_SIMPLE, {Engine.ForwardDirection}},
		{"toggle Direction", MENU_SIMPLE, {Engine.ToggleDirection}},
		{"reverse direction", MENU_SIMPLE, {Engine.ReverseDirection}},
		{"Boost", MENU_SIMPLE, {Engine.Boost}},
		{"Brake", MENU_SIMPLE, {Engine.Brake}},
		{"open Front coupler", MENU_SIMPLE, {Engine.OpenFrontCoupler}},
		{"open Rear coupler", MENU_SIMPLE, {Engine.OpenRearCoupler}},
		{"blow Horn 1", MENU_SIMPLE, {Engine.BlowHorn1}},
		{"ring Bell", MENU_SIMPLE, {Engine.RingBell}},
		{"letoff sound", MENU_SIMPLE, {Engine.LetoffSound}},
		{"blow Horn 2", MENU_SIMPLE, {Engine.BlowHorn2}},
		{"AUX1 off", MENU_SIMPLE, {Engine.AUX1Off}},
		{"AUX1 option 1 (CAB AUX1 button)", MENU_SIMPLE, {Engine.AUX1Option1}},
		{"AUX1 option 2", MENU_SIMPLE, {Engine.AUX1Option2}},
		{"AUX1 on", MENU_SIMPLE, {Engine.AUX1On}},
		{"AUX2 off", MENU_SIMPLE, {Engine.AUX2Off}},
		{"AUX2 option 1 (CAB AUX2 button)", MENU_SIMPLE, {Engine.AUX2Option1}},
		{"AUX2 option 2", MENU_SIMPLE, {Engine.AUX2Option2}},
		{"AUX2 on", MENU_SIMPLE, {Engine.AUX2On}},
		{""},
		{"assign to Train", MENU_UDATA, {Engine.AssignToTrain, Train.MaxAddress}},
		{"assign as single unit forward direction", MENU_SIMPLE, {Engine.AssignSingleForward}},
		{"assign as single unit reverse direction", MENU_SIMPLE, {Engine.AssignSingleReverse}},
		{"assign as head-end unit forward direction", MENU_SIMPLE, {Engine.AssignHeadEndForward}},
		{"assign as head-end unit reverse direction", MENU_SIMPLE, {Engine.AssignHeadEndReverse}},
		{"assign as middle unit forward direction", MENU_SIMPLE, {Engine.AssignMiddleForward}},
		{"assign as middle unit reverse direction", MENU_SIMPLE, {Engine.AssignMiddleReverse}},
		{"assign as rear unit forward direction", MENU_SIMPLE, {Engine.AssignRearForward}},
		{"assign as rear unit reverse direction", MENU_SIMPLE, {Engine.AssignRearReverse}},
		{"set Momentum low", MENU_SIMPLE, {Engine.SetMomentumLow}},
		{"set Momentum medium", MENU_SIMPLE, {Engine.SetMomentumMedium}},
		{"set Momentum high", MENU_SIMPLE, {Engine.SetMomentumHigh}},
		{"set address", MENU_SIMPLE, {Engine.SetAddress}},
		{""},
		{"set absolute speed", MENU_UDATA, {Engine.SetSpeed, Engine.AbsoluteMaxSpeed}},
		{"change speed relative", MENU_UDATA, {Engine.ChangeSpeed, Engine.RelativeMinSpeed, Engine.RelativeMaxSpeed}})

	__TRAIN_COMMANDMENU_COMPONENT(Train,
		{"forward direction", MENU_SIMPLE, {Train.ForwardDirection}},
		{"toggle Direction", MENU_SIMPLE, {Train.ToggleDirection}},
		{"reverse direction", MENU_SIMPLE, {Train.ReverseDirection}},
		{"Boost", MENU_SIMPLE, {Train.Boost}},
		{"Brake", MENU_SIMPLE, {Train.Brake}},
		{"open Front coupler", MENU_SIMPLE, {Train.OpenFrontCoupler}},
		{"open Rear coupler", MENU_SIMPLE, {Train.OpenRearCoupler}},
		{"blow Horn 1", MENU_SIMPLE, {Train.BlowHorn1}},
		{"ring Bell", MENU_SIMPLE, {Train.RingBell}},
		{"letoff sound", MENU_SIMPLE, {Train.LetoffSound}},
		{"blow Horn 2", MENU_SIMPLE, {Train.BlowHorn2}},
		{"AUX1 off", MENU_SIMPLE, {Train.AUX1Off}},
		{"AUX1 option 1 (CAB AUX1 button)", MENU_SIMPLE, {Train.AUX1Option1}},
		{"AUX1 option 2", MENU_SIMPLE, {Train.AUX1Option2}},
		{"AUX1 on", MENU_SIMPLE, {Train.AUX1On}},
		{"AUX2 off", MENU_SIMPLE, {Train.AUX2Off}},
		{"AUX2 option 1 (CAB AUX2 button)", MENU_SIMPLE, {Train.AUX2Option1}},
		{"AUX2 option 2", MENU_SIMPLE, {Train.AUX2Option2}},
		{"AUX2 on", MENU_SIMPLE, {Train.AUX2On}},
		{NULL},
		{"set Momentum low", MENU_SIMPLE, {Train.SetMomentumLow}},
		{"set Momentum medium", MENU_SIMPLE, {Train.SetMomentumMedium}},
		{"set Momentum high", MENU_SIMPLE, {Train.SetMomentumHigh}},
		{"set address", MENU_SIMPLE, {Train.SetAddress}},
		{"clear lash-up", MENU_SIMPLE, {Train.ClearLashUp}})

	__TRAIN_COMMANDMENU_COMPONENT(Accessory,
		{"AUX1 off", MENU_SIMPLE, {Accessory.AUX1Off}},
		{"AUX1 option 1", MENU_SIMPLE, {Accessory.AUX1Option1}},
		{"AUX1 option 2", MENU_SIMPLE, {Accessory.AUX1Option2}},
		{"AUX1 on", MENU_SIMPLE, {Accessory.AUX1On}},
		{"AUX2 off", MENU_SIMPLE, {Accessory.AUX2Off}},
		{"AUX2 option 1", MENU_SIMPLE, {Accessory.AUX2Option1}},
		{"AUX2 option 2", MENU_SIMPLE, {Accessory.AUX2Option2}},
		{"AUX2 on", MENU_SIMPLE, {Accessory.AUX2On}},
		{NULL},
		{"all off", MENU_SIMPLE, {Accessory.AllOff}},
		{"all on", MENU_SIMPLE, {Accessory.AllOn}},
		{"set address", MENU_SIMPLE, {Accessory.SetAddress}},
		{"assign AUX1 to group", MENU_UDATA, {Accessory.AssignAUX1ToGroup, Group.MaxAddress}},
		{"assign AUX2 to group", MENU_UDATA, {Accessory.AssignAUX2ToGroup, Group.MaxAddress}})

	__TRAIN_COMMANDMENU_COMPONENT(Group,
		{"off", MENU_SIMPLE, {Group.Off}},
		{"option 1", MENU_SIMPLE, {Group.Option1}},
		{"option 2", MENU_SIMPLE, {Group.Option2}},
		{"on", MENU_SIMPLE, {Group.On}},
		{"clear", MENU_SIMPLE, {Group.Clear}})

	__TRAIN_COMMANDMENU(SystemCommand,
		{"Send command", MENU_SYSCOMMAND, {System.SendCommand}},
		{"Halt", MENU_SIMPLE, {System.Halt}},
		{"NOP", MENU_SIMPLE, {System.NOP}},
		{NULL},
		{"Reserved 11111110 11111111", MENU_SIMPLE, {System__Reserved1}},
		{"Reserved 11111111 11111110", MENU_SIMPLE, {System__Reserved2}})

	__TRAIN_COMMANDMENU(Component,
		{"Switch", MENU_MENU, __TRAIN_COMMANDMENU_MENU(SwitchCommandMenu)},
		{"Route", MENU_MENU, __TRAIN_COMMANDMENU_MENU(RouteCommandMenu)},
		{"Engine", MENU_MENU, __TRAIN_COMMANDMENU_MENU(EngineCommandMenu)},
		{"Train", MENU_MENU, __TRAIN_COMMANDMENU_MENU(TrainCommandMenu)},
		{"Accessory", MENU_MENU, __TRAIN_COMMANDMENU_MENU(AccessoryCommandMenu)},
		{"Group", MENU_MENU, __TRAIN_COMMANDMENU_MENU(GroupCommandMenu)},
		{"System", MENU_MENU, __TRAIN_COMMANDMENU_MENU(SystemCommandMenu)})

	const struct CommandMenu_Option StartMenu[] = {
		{"Assignment 2", MENU_MENU, __TRAIN_COMMANDMENU_MENU(AssignmentMenu)},
		{"Full Command Menu", MENU_MENU, __TRAIN_COMMANDMENU_MENU(ComponentMenu)},
		{""},
		{"Exit", MENU_EXIT}
	};
	
	switch (CommandMenu_ParseInput(stdout, stdin, stderr, hSystem, StartMenu, ARRAY_SIZE(StartMenu), tPhrases))
	{
		case INPUT_SUCCESS:
			PrintN(stdout, "Exiting gracefully");
		
		case INPUT_FAIL:
			PrintN(stdout, "Exiting with error");
		
		case INPUT_EOF:
			PrintN(stdout, "Exiting from reaching EOF");
	}
	
	System.Close(hSystem);
	
	return EXIT_SUCCESS;
}
