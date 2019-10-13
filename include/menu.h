#include <stdio.h>		// FILE
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL

#include "interface.h"	// SystemHandle

#define TRAIN_MAXMENUS 10 // FIXME

enum CommandMenu_OptionType
{
	MENU_MENU,			// Redirects to another menu, no command
	MENU_SIMPLE,		// No args
	MENU_ADDRESS,		// Address
	MENU_UDATA,			// Address + Unsigned data
	MENU_IDATA,			// Address + Signed data
	MENU_COMMAND,		// Component command (Address + Command)
	MENU_SYSCOMMAND,	// System command

	MENU_RETURN,		// Go back to the previous menu
	MENU_EXIT			// Exit the program
};

struct CommandMenu_Option;

struct CommandMenu_Menu
{
	const struct CommandMenu_Option* Menu;
	size_t Length;
};

struct CommandMenu_Simple
{
	void (*Function)(SystemHandle);
};

struct CommandMenu_Address
{
	void (*Function)(SystemHandle, SystemUnsignedData);
};

struct CommandMenu_UnsignedData
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemUnsignedData);
	size_t Max;
};

struct CommandMenu_SignedData
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemSignedData);
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
		const struct CommandMenu_Menu Menu;
		const struct CommandMenu_Simple Simple;
		const struct CommandMenu_Address Address;
		const struct CommandMenu_UnsignedData UnsignedData;
		const struct CommandMenu_SignedData SignedData;
		const struct CommandMenu_Command Command;
		const struct CommandMenu_SystemCommand SystemCommand;
	};
};

size_t CommandMenu_PrintList(FILE* pStream, const char* sPrefix, const char* sSuffix, const struct CommandMenu_Option* tOptions, size_t uLength);

struct CommandMenu_Phrases
{
	const char* MenuPrefix;
	const char* MenuSuffix;
	const char* UnsignedData;
	const char* SignedData;
	const char* Address;
	const char* Command;
	const char* SystemCommand;
};

enum InputState CommandMenu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const struct CommandMenu_Phrases tStrings, const struct CommandMenu_Option* tOptions, size_t uLength);