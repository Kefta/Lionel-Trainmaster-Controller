#include <inttypes.h>	// intmax_t, uintmax_t
#include <stdio.h>		// EOF, FILE, fprintf, getc, size_t, vfprintf
#include <windows.h>	// BOOL, BYTE, FALSE, TRUE

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
		vfprintf(pStream, "%s", sMessage, args);
	va_end(args);
}

inline void PrintFV(FILE* pStream, const char* sMessage, va_list args)
{
	vfprintf(pStream, "%s", sMessage, args);
}

inline void PrintFN(FILE* pStream, const char* sMessage, ...)
{
	va_list args;
	va_start(args, sMessage);
		vfprintf(pStream, "%s\n", sMessage, args);
	va_end(args);
}

inline void PrintFVN(FILE* pStream, const char* sMessage, va_list args)
{
	vfprintf(pStream, "%s\n", sMessage, args);
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

inline BOOL InputEnter(FILE* pStream)
{
	int iEnter;

	while ((iEnter = getc(pStream)) != '\r' && iEnter != '\n')
	{
		if (iEnter == EOF)
			return FALSE;
	}
	
	return TRUE;
}

// FIXME: Change error stream arg to an error callback func
BOOL InputUnsigned(FILE* pInput, FILE* pError, uintmax_t uMin, uintmax_t uMax, uintmax_t* ret_uInput)
{
	static const char* InputError = "\nInvalid input, enter a number [%zu, %zu]: ";
	
	uintmax_t uOption = 0;
	
	int iCurChar;
	size_t uCurPower;
	BOOL bStarted = FALSE;
	
	while ((iCurChar = getc(pInput)) != EOF)
	{
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
				
				// If the option is already out of bounds, don't bother reading the rest of the string
				if (uOption <= uMax)
				{
					uCurPower *= 10;

					break;
				}
			
			DEFAULT_INPUTUNSIGNED:
			default:
				PrintF(pError, InputError, uMin, uMax);
				
				return FALSE;
			
			case '\0':
			case '\n':
			case '\r':
			case '\t':
			case ' ':
				if (bStarted)
					break;
			
			goto DEFAULT_INPUTUNSIGNED;
		}
	}
	
	if (uOption < uMin)
	{
		PrintF(pError, InputError, uMin, uMax);
		
		return FALSE;
	}
	
	if (ret_uInput != NULL)
		*ret_uInput = uOption;
	
	return TRUE;
}

BOOL InputSigned(FILE* pStream, FILE* pError, intmax_t iMin, intmax_t iMax, intmax_t* ret_iInput)
{
	static const char* InputError = "\nInvalid input, enter a number [%zd, %zd]: ";
	
	intmax_t iOption = 0;
	
	int iCurChar;
	size_t uCurPower;
	BOOL bNegative, bStarted = FALSE, FALSE;
	
	while ((iCurChar = getc(pInput)) != EOF)
	{
		switch(iCurChar)
		{
			case '-':
				if (bStarted)
					goto DEFAULT_INPUTSIGNED;
			
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
			
			DEFAULT_INPUTSIGNED:
			default:
				PrintF(pError, InputError, iMin, iMax);
				
				return FALSE;
			
			case '\0':
			case '\n':
			case '\r':
			case '\t':
			case ' ':
				if (bStarted)
					break;
			
			goto DEFAULT_INPUTSIGNED;
		}
	}
	
	if (bNegative)
	{
		if (iOption > iMax)
		{
			PrintF(pError, InputError, iMin, iMax);
			
			return FALSE;
		}
	}
	else if (iOption < iMin)
	{
		PrintF(pError, InputError, iMin, iMax);
		
		return FALSE;
	}
	
	if (ret_iInput != NULL)
		*ret_iInput = iOption;
	
	return TRUE;
}

long double InputDecimal(FILE* pStream, FILE* pError, long double nMin, long double nMax, long double* ret_nInput)
{
	// FIXME
	return 0;
}

inline BOOL CheckUnsigned(uintmax_t uNumber, uintmax_t uMin, uintmax_t uMax)
{
	if (uNumber <= uMax)
		return TRUE;

	return FALSE;
}

inline BOOL CheckSigned(intmax_t iNumber, intmax_t iMin, intmax_t iMax)
{
	if (iNumber >= iMin && iNumber <= uMax)
		return TRUE;

	return FALSE;
}

inline BOOL CheckDecimal(long double nNumber, long double nMin, long double nMax)
{
	if (nNumber >= nMin && nNumber <= nMax)
		return TRUE;

	return FALSE;
}
