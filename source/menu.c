// FIXME: Fix all size_t/uintmax_t and formatted usages

#include <stdio.h>		// EOF, getc, stdin, stderr
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL, FALSE, TRUE

#include "interface.h"	// SystemHandle
#include "util.h"		// PrintF, PrintN, INPUT_SUCCESS

inline size_t CommandMenu_PrintList(FILE* pStream, const char* sPrefix, const struct CommandMenu_Option* tOptions, size_t uLength, const char* sSuffix)
{
	const char* const sText;
	size_t uOptionCount = 0;

	if (*sPrefix != 0)
		PrintF(pStream, "%s\n", sPrefix);

	for (size_t i = 1; i <= uLength; ++i)
	{
		sText = (tOptions++)->Text;

		if (sText == NULL)
		{
			Print(pStream, "\n"); // Spacer
		}
		else
		{
			PrintF(pStream, "%zu. %s\n", i, sText); // Option
			++uOptionCount;
		}
	}

	if (*sSuffix != 0)
		PrintF(pStream, sSuffix);
	
	return uOptionCount;
}

enum InputState CommandMenu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const struct CommandMenu_Option* tOptions, size_t uLength, const CommandMenu_Phrases tStrings)
{
	size_t uOptions;
	const struct CommandMenu_Option* tOption;

	uintmax_t uInput;
	intmax_t iInput;
	uintmax_t uAddress;
	
	struct CommandMenu_Menu tMenuStack[TRAIN_MAXMENUS];
	struct CommandMenu_Menu* pCurMenuPos = tMenuStack;

	CommandMenu_ParseInput_PrintMenu:
		uOptions = CommandMenu_PrintList(pStream, tStrings.Prefix, tOptions, uLength, tStrings.Suffix);
		
		CommandMenu_ParseInput_MenuInput:
			switch (InputUnsigned(pStream, stderr, 1, uOptions, &uInput))
			{
				case INPUT_FAIL:
					PrintF("\nInvalid input, enter an integer [%zu, %zu]: ", 1, uOptions);
				goto CommandMenu_ParseInput_MenuInput;
				
				case INPUT_EOF:
					Print("\n");
				return INPUT_EOF;
				
				case INPUT_SUCCESS:
					// Move off of the user choice line
					Print("\n");
					
					// Iterate though the menu to find the option
					// We can't index tOptions directly since spacers take up elements
					tOption = tOptions;
					
					while (tOption->Text == NULL || --uInput != 0)
						++tOption;
					
					switch (tOption->Type)
					{
						case MENU_MENU:
							// Don't add a new menu to the stack if we've hit the limit
							if ((size_t)(pCurMenuPos - tMenuStack) >= TRAIN_MAXMENUS)
							{
								PrintF(pError, "Exceeded max menu limit of %zu\n", (size_t)TRAIN_MAXMENUS);
								
								return INPUT_FAIL;
							}

							// Add this menu to the stack so we can return to it
							*pCurMenuPos++ = {.Menu = tOptions, .Length = uLength};

							// Proceed to the next menu
							tOptions = tOption->Menu.Menu;
							uLength = tOption->Menu.Length;
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_SIMPLE:
							(tOption->Simple.Function)(hSystem);
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_UDATA:
							Print(tStrings.UnsignedData);
							
							CommandMenu_ParseInput_UDataInput:
								switch (InputUnsigned(pStream, stderr, 0, tOption->UnsignedData.Max, &uInput))
								{
									case INPUT_FAIL:
										PrintF("\nInvalid input, enter an integer [%zu, %zu]: ", 0, tOption->UnsignedData.Max);
									goto CommandMenu_ParseInput_UDataInput;
									
									case INPUT_EOF:
										Print("\n");
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										Print("\n\n");
										(tOption->UnsignedData.Function)(hSystem, (SystemUnsignedData)uInput);
								}
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_IDATA:
							Print(tStrings.SignedData);
							
							CommandMenu_ParseInput_IDataInput:
								switch (InputSigned(pStream, stderr, tOption->UnsignedData.Min, tOption->UnsignedData.Max, &iInput))
								{
									case INPUT_FAIL:
										PrintF("\nInvalid input, enter an integer [%zd, %zd]: ", tOption->SignedData.Min, tOption->SignedData.Max);
									goto CommandMenu_ParseInput_IDataInput;
									
									case INPUT_EOF:
										Print("\n");
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										Print("\n\n");
										(tOption->SignedData.Function)(hSystem, (SystemSignedData)iInput);
								}
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_COMMAND:
							// FIXME
							return INPUT_FAIL;

						case MENU_SYSCOMMAND:
							// FIXME
							return INPUT_FAIL;

						case MENU_RETURN:
							// Don't return to the previous menu if we don't have one
							if (pCurMenuPos - tMenuStack == 0)
							{
								Print(pError, "\nAttempted to return when no previous menu exists\n");
								
								return INPUT_FAIL;
							}

							// Return to the previous menu on the stack
							tOptions = (*--pCurMenuPos).Menu;
							uLength = (*pCurMenu).Length;
						goto CommandMenu_ParseInput_PrintMenu;
						
						case MENU_EXIT:
							Print("\n");
						return INPUT_SUCCESS;
							
						default:
					}
				
				default:
			}
	
	return INPUT_FAIL;
}
