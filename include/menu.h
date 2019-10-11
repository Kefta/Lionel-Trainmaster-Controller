#include <stdio.h>		// FILE
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL

#include "interface.h"	// SystemHandle

#define TRAIN_MAXMENUS 10 // FIXME

enum CommandMenu_OptionType
{
	MENU_MENU,			// Redirects to another menu, no command
	MENU_SIMPLE,		// No args
	MENU_UDATA,			// Unsigned data
	MENU_IDATA,			// Signed data
	MENU_COMMAND,		// Component command (Address + Command)
	MENU_SYSCOMMAND,	// System command

	MENU_RETURN,		// Go back to the previous menu
	MENU_EXIT			// Exit the program
};

struct CommandMenu_Menu
{
	const CommandMenu_Option* Menu;
	size_t Length;
};

struct CommandMenu_Simple
{
	void (*Function)(SystemHandle);
};

struct CommandMenu_UnsignedData
{
	void (*Function)(SystemHandle, SystemUnsignedData);
	size_t Max;
};

struct CommandMenu_SignedData
{
	void (*Function)(SystemHandle, SystemSignedData);
	size_t Min;
	size_t Max;
};

struct CommandMenu_Command
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemUnsignedData);
	size_t Max;
};

struct CommandMenu_SystemCommand
{
	void (*Function)(SystemHandle, SystemCommand);
};

struct CommandMenu_Option
{
	const char* const Text;	// NULL = spacer
	const enum CommandMenu_OptionType Type;
	
	union
	{
		const CommandMenu_Menu Menu;
		const CommandMenu_Simple Simple;
		const CommandMenu_UnsignedData UnsignedData;
		const CommandMenu_SignedData SignedData;
		const CommandMenu_Command Command;
		const CommandMenu_SystemCommand SystemCommand;
	};
};

size_t CommandMenu_PrintList(FILE* pStream, const char* sPrefix, const char* sSuffix, const char* CommandMenu_Option tOptions, size_t uLength);

struct CommandMenu_Strings
{
	const char* MenuPrefix;
	const char* MenuSuffix;
	const char* UnsignedData;
	const char* SignedData;
	const char* Address;
};

InputState CommandMenu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const CommandMenu_Option* tOptions, size_t uLength, const CommandMenu_Strings tStrings);