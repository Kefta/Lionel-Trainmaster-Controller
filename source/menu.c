// FIXME: Fix all size_t/uintmax_t and formatted usages

#include <stdio.h>		// EOF, getc, stdin, stderr
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL, FALSE, TRUE

#include "interface.h"	// SystemHandle
#include "util.h"		// PrintF, PrintN, INPUT_SUCCESS

#include "menu.h"

inline size_t CommandMenu_PrintList(FILE* pStream, const char* sPrefix, const char* sSuffix, const struct CommandMenu_Option* tOptions, size_t uLength)
{
	const char* sText;
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

enum InputState CommandMenu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const struct CommandMenu_Phrases tStrings, const struct CommandMenu_Option* tOptions, size_t uLength)
{
	size_t uOptions;
	const struct CommandMenu_Option* tOption;

	uintmax_t uInput;
	intmax_t iInput;
	uintmax_t uAddress = 0; // FIXME: Need to take an address input from the user
	
	struct CommandMenu_Menu tMenuStack[TRAIN_MAXMENUS];
	struct CommandMenu_Menu* pCurMenuPos = tMenuStack;

	CommandMenu_ParseInput_PrintMenu:
		uOptions = CommandMenu_PrintList(pStream, tStrings.MenuPrefix, tStrings.MenuSuffix, tOptions, uLength);
		
		CommandMenu_ParseInput_MenuInput:
			switch (InputUnsigned(pStream, stderr, 1, uOptions, &uInput))
			{
				case INPUT_FAIL:
					PrintF(pError, "\nInvalid input, enter an integer [%zu, %zu]: ", 1, uOptions);
				goto CommandMenu_ParseInput_MenuInput;
				
				case INPUT_EOF:
					Print(pStream, "\n");
				return INPUT_EOF;
				
				case INPUT_SUCCESS:
					// Move off of the user choice line
					Print(pStream, "\n");
					
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
							(*pCurMenuPos).Menu = tOptions;
							(*pCurMenuPos).Length = uLength;
							++pCurMenuPos;

							// Proceed to the next menu
							tOptions = tOption->Menu.Menu;
							uLength = tOption->Menu.Length;
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_SIMPLE:
							(tOption->Simple.Function)(hSystem);
						goto CommandMenu_ParseInput_PrintMenu;
						
						case MENU_ADDRESS:
							(tOption->Address.Function)(hSystem, uAddress);
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_UDATA:
							Print(pStream, tStrings.UnsignedData);
							
							CommandMenu_ParseInput_UDataInput:
								switch (InputUnsigned(pStream, stderr, 0, tOption->UnsignedData.Max, &uInput))
								{
									case INPUT_FAIL:
										PrintF(pError, "\nInvalid input, enter an integer [%zu, %zu]: ", 0, tOption->UnsignedData.Max);
									goto CommandMenu_ParseInput_UDataInput;
									
									case INPUT_EOF:
										Print(pStream, "\n");
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										Print(pStream, "\n\n");
										(tOption->UnsignedData.Function)(hSystem, uAddress, (SystemUnsignedData)uInput);
								}
						goto CommandMenu_ParseInput_PrintMenu;

						case MENU_IDATA:
							Print(pStream, tStrings.SignedData);
							
							CommandMenu_ParseInput_IDataInput:
								switch (InputSigned(pStream, stderr, tOption->SignedData.Min, tOption->SignedData.Max, &iInput))
								{
									case INPUT_FAIL:
										PrintF(pError, "\nInvalid input, enter an integer [%zd, %zd]: ", tOption->SignedData.Min, tOption->SignedData.Max);
									goto CommandMenu_ParseInput_IDataInput;
									
									case INPUT_EOF:
										Print(pStream, "\n");
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										Print(pStream, "\n\n");
										(tOption->SignedData.Function)(hSystem, uAddress, (SystemSignedData)iInput);
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
							--pCurMenuPos;
							tOptions = (*pCurMenuPos).Menu;
							uLength = (*pCurMenuPos).Length;
						goto CommandMenu_ParseInput_PrintMenu;
						
						case MENU_EXIT:
							Print(pStream, "\n");
						return INPUT_SUCCESS;
							
						default:;
					}
				
				default:;
			}
	
	return INPUT_FAIL;
}
