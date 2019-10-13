#include <windows.h>	// BYTE, CloseHandle, CreateFile, DWORD, FILE_ATTRIBUTE_NORMAL, GENERIC_WRITE, LPCVOID, OPEN_EXISTING, WriteFile
#include "interface.h"	// SystemCommand, SystemHandle, SystemUnsignedData
#include "util.h"		// Print, PrintBinary

#include "system.h"

inline SystemHandle System_Create(const char* sFile)
{
	return CreateFile(sFile, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

inline void System_Close(SystemHandle hSystem)
{
	CloseHandle(hSystem);
}

void System_SendCommand(SystemHandle hSystem, SystemCommand uCommand)
{
	const SystemUnsignedData tCommand[3] = {
		0x7F /*01111111*/,
		(SystemUnsignedData)(uCommand >> 8), // 8 MSB
		(SystemUnsignedData)uCommand // 8 LSB
	};
	
	DWORD uBytesWritten = 0;
	
	if (WriteFile(hSystem, (LPCVOID)tCommand, 3, &uBytesWritten, NULL))
	{
		#ifdef TRAIN_OUTPUT_COMMANDS
			Print(stdout, "Command written:");
			
			while (uBytesWritten-- != 0)
			{
				Print(stdout, " ");
				PrintBinary(stdout, (BYTE*)pCommand++, sizeof(SystemUnsignedData));
			}
			
			PrintN(stdout, "");
		#endif
	}
	else
	{
		#ifdef TRAIN_OUTPUT_ERRORS
			Print(stderr, "Failed to write command\n");
		#endif
	}
}

inline void System_Halt(SystemHandle hSystem)
{
	System_SendCommand(hSystem, 0xFFFF /*11111111 11111111*/);
}

inline void System_NOP(SystemHandle hSystem)
{
	System_SendCommand(hSystem, 0xFF80 /*11111111 10000000*/);
}

inline void System__Reserved1(SystemHandle hSystem)
{
	System_SendCommand(hSystem, 0xFFEF /*11111110 11111111*/);
}

inline void System__Reserved2(SystemHandle hSystem)
{
	System_SendCommand(hSystem, 0xFFFE /*11111111 11111110*/);
}
