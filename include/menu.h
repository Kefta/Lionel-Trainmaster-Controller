#include <stdio.h>		// FILE
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL

#include "interface.h"	// SystemHandle
#include "util.h"		// ARRAY_SIZE

#define TRAIN_MENU_MAX 10 // FIXME

#define TRAIN_MENU_MENU(NAME, MENU) {NAME, MENU_MENU, .Menu = {.Menu = MENU, .Length = ARRAY_SIZE(MENU)}}
#define TRAIN_MENU_SIMPLE(NAME, FUNC) {NAME, MENU_SIMPLE, .Simple = {.Function = FUNC}}
#define TRAIN_MENU_ADDRESS(NAME, FUNC) {NAME, MENU_ADDRESS, .Address = {.Function = FUNC}}
#define TRAIN_MENU_UDATA(NAME, FUNC, MIN, MAX) {NAME, MENU_UDATA, .UnsignedData = {.Function = FUNC, .Min = MIN, .Max = MAX}}
#define TRAIN_MENU_IDATA(NAME, FUNC, MIN, MAX) {NAME, MENU_IDATA, .SignedData = {.Function = FUNC, .Min = MIN, .Max = MAX}}
#define TRAIN_MENU_COMMAND(NAME, FUNC, MAX) {NAME, MENU_COMMAND, .Command = {.Function = FUNC, .Max = MAX}}
#define TRAIN_MENU_SYSCOMMAND(NAME, FUNC, MAX) {NAME, MENU_SYSCOMMAND, .SystemCommand = {.Function = FUNC, .Max = MAX}}
#define TRAIN_MENU_RETURN(NAME) {NAME, MENU_RETURN}
#define TRAIN_MENU_EXIT(NAME) {NAME, MENU_EXIT}
#define TRAIN_MENU_SEPARATOR {NULL}

enum Menu_OptionType
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

struct Menu_Option;

struct Menu_Menu
{
	const struct Menu_Option* Menu; // Essentially a linked list of menu redirections
	size_t Length;
};

struct Menu_Simple
{
	void (*Function)(SystemHandle);
};

struct Menu_Address
{
	void (*Function)(SystemHandle, SystemUnsignedData);
};

struct Menu_UnsignedData
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemUnsignedData);
	uintmax_t Min;
	uintmax_t Max;
};

struct Menu_SignedData
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemSignedData);
	intmax_t Min;
	intmax_t Max;
};

struct Menu_Command
{
	void (*Function)(SystemHandle, SystemUnsignedData, SystemUnsignedData);
	uintmax_t Max;
};

struct Menu_SystemCommand
{
	void (*Function)(SystemHandle, SystemCommand);
	uintmax_t Max;
};

struct Menu_Option
{
	const char* const Text;	// NULL = spacer
	const enum Menu_OptionType Type;
	
	union
	{
		const struct Menu_Menu Menu;
		const struct Menu_Simple Simple;
		const struct Menu_Address Address;
		const struct Menu_UnsignedData UnsignedData;
		const struct Menu_SignedData SignedData;
		const struct Menu_Command Command;
		const struct Menu_SystemCommand SystemCommand;
	};
};

size_t Menu_PrintList(FILE* pStream, const char* sPrefix, const char* sSuffix, const struct Menu_Option* tOptions, size_t uLength);

struct Menu_Phrases
{
	const char* MenuPrefix;
	const char* MenuSuffix;
	const char* UnsignedData;
	const char* SignedData;
	const char* Address;
	const char* Command;
	const char* SystemCommand;
};

enum InputState Menu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const struct Menu_Phrases tStrings, const struct Menu_Option* tOptions, size_t uLength);