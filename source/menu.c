// FIXME: Fix all size_t/uintmax_t and formatted usages

#include <inttypes.h>	// intmax_t, uintmax_t
#include <stdio.h>		// EOF, getc, stdin, stderr
#include <stddef.h>		// size_t
#include <windows.h>	// BOOL, FALSE, TRUE

#include "interface.h"	// SystemHandle
#include "util.h"		// PrintF, PrintN, INPUT_SUCCESS

#include "menu.h"

inline size_t Menu_PrintList(FILE* pStream, const char* sPrefix, const char* sSuffix, const struct Menu_Option* tOptions, size_t uLength)
{
	if (tOptions == NULL)
		return 0; // FIXME
	
	const char* sText;
	size_t uOptionCount = 0;

	if (sPrefix != NULL)
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
			PrintF(pStream, "%zu. %s\n", ++uOptionCount, sText); // Option
		}
	}

	if (sSuffix != NULL)
		Print(pStream, sSuffix);
	
	return uOptionCount;
}

//#define __TRAIN_MENU_PARSEINPUT_INVALID_UNSIGNED 

enum InputState Menu_ParseInput(FILE* pStream, FILE* pInput, FILE* pError, SystemHandle hSystem, const struct Menu_Phrases tStrings, const struct Menu_Option* tOptions, size_t uLength)
{
	if (tOptions == NULL)
		return INPUT_SUCCESS; // FIXME
	
	size_t uOptions;
	const struct Menu_Option* tOption;

	uintmax_t uInput;
	intmax_t iInput;
	uintmax_t uAddress = 23; // FIXME: Need to take an address input from the user
	
	struct Menu_Menu tMenuStack[TRAIN_MENU_MAX];
	struct Menu_Menu* pCurMenuPos = tMenuStack;

	Menu_ParseInput_PrintMenu:
		uOptions = Menu_PrintList(pStream, tStrings.MenuPrefix, tStrings.MenuSuffix, tOptions, uLength);
		
		Menu_ParseInput_MenuInput:
			switch (InputUnsigned(pInput, 1, uOptions, &uInput))
			{
				case INPUT_FAIL:
					PrintF(pError, "Invalid input, enter an option [%zu, %zu]: ", 1, uOptions);
				goto Menu_ParseInput_MenuInput;
				
				case INPUT_EOF:
				return INPUT_EOF;
				
				case INPUT_SUCCESS:
					// Iterate though the menu to find the option
					// We can't index tOptions directly since spacers take up elements
					tOption = tOptions;
					
					while (tOption->Text == NULL || --uInput != 0)
						++tOption;
					
					switch (tOption->Type)
					{
						case MENU_MENU:
							// Don't add a new menu to the stack if we've hit the limit
							if ((size_t)(pCurMenuPos - tMenuStack) >= TRAIN_MENU_MAX)
							{
								PrintF(pError, "Exceeded max menu limit of %zu\n", (size_t)TRAIN_MENU_MAX);
								
								return INPUT_FAIL;
							}

							// Add this menu to the stack so we can return to it
							(*pCurMenuPos).Menu = tOptions;
							(*pCurMenuPos).Length = uLength;
							++pCurMenuPos;

							// Proceed to the next menu
							tOptions = tOption->Menu.Menu;
							uLength = tOption->Menu.Length;
						goto Menu_ParseInput_PrintMenu;

						case MENU_SIMPLE:
							(tOption->Simple.Function)(hSystem);
						goto Menu_ParseInput_PrintMenu;
						
						case MENU_ADDRESS:
							(tOption->Address.Function)(hSystem, uAddress);
						goto Menu_ParseInput_PrintMenu;

						case MENU_UDATA:
							PrintF(pStream, tStrings.UnsignedData, tOption->UnsignedData.Min, tOption->UnsignedData.Max);
							
							Menu_ParseInput_UDataInput:
								switch (InputUnsigned(pInput, tOption->UnsignedData.Min, tOption->UnsignedData.Max, &uInput))
								{
									case INPUT_FAIL:
										PrintF(pError, "Invalid input, enter an integer [%zu, %zu]: ", tOption->UnsignedData.Min, tOption->UnsignedData.Max);
									goto Menu_ParseInput_UDataInput;
									
									case INPUT_EOF:
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										(tOption->UnsignedData.Function)(hSystem, uAddress, (SystemUnsignedData)uInput);
								}
						goto Menu_ParseInput_PrintMenu;

						case MENU_IDATA:
							PrintF(pStream, tStrings.SignedData, tOption->SignedData.Min, tOption->SignedData.Max);
							
							Menu_ParseInput_IDataInput:
								switch (InputSigned(pInput, tOption->SignedData.Min, tOption->SignedData.Max, &iInput))
								{
									case INPUT_FAIL:
										PrintF(pError, "Invalid input, enter an integer [%zd, %zd]: ", tOption->SignedData.Min, tOption->SignedData.Max);
									goto Menu_ParseInput_IDataInput;
									
									case INPUT_EOF:
									return INPUT_EOF;
									
									case INPUT_SUCCESS:
										(tOption->SignedData.Function)(hSystem, uAddress, (SystemSignedData)iInput);
								}
						goto Menu_ParseInput_PrintMenu;

						case MENU_COMMAND:
							Print(pError, "Unimplemented\n");
						return INPUT_FAIL;

						case MENU_SYSCOMMAND:
							Print(pError, "Unimplemented\n");
						return INPUT_FAIL;

						case MENU_RETURN:
							// Don't return to the previous menu if we don't have one
							if (pCurMenuPos - tMenuStack == 0)
							{
								Print(pError, "Attempted to return when no previous menu exists\n");
								
								return INPUT_FAIL;
							}

							// Return to the previous menu on the stack
							--pCurMenuPos;
							tOptions = (*pCurMenuPos).Menu;
							uLength = (*pCurMenuPos).Length;
						goto Menu_ParseInput_PrintMenu;
						
						case MENU_EXIT:
						return INPUT_SUCCESS;
							
						default:;
					}
				
				default:;
			}
	
	return INPUT_FAIL;
}
