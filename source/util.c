#include <inttypes.h>	// intmax_t, uintmax_t
#include <stdio.h>		// EOF, FILE, fprintf, getc, size_t, vfprintf
#include <windows.h>	// BOOL, BYTE, FALSE, TRUE

#include "util.h"

inline void Print(FILE* pStream, const char* sMessage)
{
	fprintf(pStream, "%s", sMessage);
}

inline void PrintN(FILE* pStream, const char* sMessage)
{
	fprintf(pStream, "%s\n", sMessage);
}

inline void PrintF(FILE* pStream, const char* sMessage, ...)
{
	va_list args;
	va_start(args, sMessage);
		// FIXME: This will fail for non-literal strings
		vfprintf(pStream, sMessage, args);
	va_end(args);
}

inline void PrintFV(FILE* pStream, const char* sMessage, va_list args)
{
	vfprintf(pStream, sMessage, args);
}

inline void PrintBinary(FILE* pStream, const BYTE* Object, size_t uLength)
{
	char tBinary[9];
	tBinary[9] = 0;

	char* pBinary;
	BYTE uObjectByte;
	
	size_t uMask;
	
	while (uLength-- != 0)
	{
		uObjectByte = *Object++;
		pBinary = tBinary;

		for (uMask = 128; uMask > 0; uMask >>= 1)
		{
			*pBinary++ = (uObjectByte & uMask) == uMask ? '1' : '0';
		}
		
		PrintF(pStream, "%s", tBinary);
	}
}

#define TRAIN_INPUT_ISDONE(x) (x == EOF || x == '\n' || x == '\r' || x == '\0')
#define __TRAIN_UTIL_INPUT_ERROR(FORMAT) "\nInvalid input, enter a number [FORMAT, FORMAT]: "

// FIXME: Change error stream arg to an error callback func
enum InputState InputUnsigned(FILE* pInput, uintmax_t uMin, uintmax_t uMax, uintmax_t* ret_uInput)
{	
	uintmax_t uOption = 0;
	size_t uCurPower = 1;
	
	BOOL bStarted = FALSE;
	BOOL bClearing = FALSE;
	BOOL bFail = FALSE;
	
	int iCurChar;
	
	while ((iCurChar = getc(pInput)) != EOF)
	{
		if (bClearing)
			continue;
		
		switch(iCurChar)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				bStarted = TRUE;
				
				uOption *= uCurPower; // Promote the last number to the next power
				uOption += iCurChar - '0'; // Add the next character to the ones place
				
				// If the option is already out of bounds, don't bother parsing the rest of the string
				if (uOption <= uMax)
				{
					uCurPower *= 10;

					break;
				}
			
			default:
				bClearing = TRUE;
				bFail = TRUE;
			goto INPUTUNSIGNED_FINISHED;
			
			case '\n':
				if (bStarted || bClearing)
					goto INPUTUNSIGNED_FINISHED;
			break;
			
			case '\0':
			case '\r':
			case '\t':
			case ' ':
				if (bStarted)
				{
					bClearing = TRUE;
				}
		}
	}
	
	INPUTUNSIGNED_FINISHED:
		if (!bStarted)
			return INPUT_EOF;
		
		if (bFail || uOption < uMin)
			return INPUT_FAIL;
		
		if (ret_uInput != NULL)
			*ret_uInput = uOption;
		
		return INPUT_SUCCESS;
}

enum InputState InputSigned(FILE* pInput, intmax_t iMin, intmax_t iMax, intmax_t* ret_iInput)
{	
	intmax_t iOption = 0;
	size_t uCurPower = 1;
	BOOL bNegative = FALSE;
	
	BOOL bStarted = FALSE;
	BOOL bClearing = FALSE;
	BOOL bFail = FALSE;
	
	int iCurChar;
	
	while ((iCurChar = getc(pInput)) != EOF)
	{
		if (bClearing)
			continue;
		
		switch(iCurChar)
		{
			case '-':
				if (bStarted)
					goto INPUTSIGNED_DEFAULT;
			
				bNegative = TRUE;
			break;
			
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				bStarted = TRUE;
				
				iOption *= uCurPower;
				
				if (bNegative)
					iOption -= iCurChar - '0';
				else
					iOption += iCurChar - '0';
				
				if (bNegative)
				{
					if (iOption >= iMin)
					{
						uCurPower *= 10;

						break;
					}
				}
				else if (iOption <= iMax)
				{
					uCurPower *= 10;
					
					break;
				}
			
			INPUTSIGNED_DEFAULT:
			default:
				bFail = TRUE;
			goto INPUTSIGNED_FINISHED;
			
			case '\n':
				if (bStarted || bClearing)
					goto INPUTSIGNED_FINISHED;
			break;
			
			case '\0':
			case '\r':
			case '\t':
			case ' ':
				if (bStarted)
				{
					bClearing = TRUE;
				}
		}
	}
	
	INPUTSIGNED_FINISHED:
		if (!bStarted)
			return INPUT_EOF;
		
		if (bFail || (bNegative && iOption > iMax) || (!bNegative && iOption < iMin))
			return INPUT_FAIL;
		
		if (ret_iInput != NULL)
			*ret_iInput = iOption;
		
		return INPUT_SUCCESS;
}
