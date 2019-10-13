#ifndef TRAIN_H_UTIL
#define TRAIN_H_UTIL
#pragma once

#include <inttypes.h>	// intmax_t, uintmax_t
#include <stdio.h>		// FILE
#include <windows.h>	// BOOL, BYTE

#define __TOSTRING(X) #X
#define TOSTRING(X) __TOSTRING(X)

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

void Print(FILE* pStream, const char* sMessage);
void PrintN(FILE* pStream, const char* sMessage);
void PrintF(FILE* pStream, const char* sMessage, ...);
void PrintFV(FILE* pStream, const char* sMessage, va_list args);
void PrintFN(FILE* pStream, const char* sMessage, ...);
void PrintFVN(FILE* pStream, const char* sMessage, va_list args);

void PrintBinary(FILE* pStream, const BYTE* Object, size_t uLength);

BOOL InputEnter(FILE* pStream);

enum InputState
{
	INPUT_SUCCESS,
	INPUT_FAIL,
	INPUT_EOF
};

enum InputState InputUnsigned(FILE* pStream, uintmax_t uMin, uintmax_t uMax, uintmax_t* ret_uInput);
enum InputState InputSigned(FILE* pStream, intmax_t iMin, intmax_t iMax, intmax_t* ret_iInput);
enum InputState InputDecimal(FILE* pStream, long double nMin, long double nMax, long double* ret_nInput);

BOOL CheckUnsigned(uintmax_t uNumber, uintmax_t uMin, uintmax_t uMax);
BOOL CheckSigned(intmax_t iNumber, intmax_t iMin, intmax_t iMax);
BOOL CheckDecimal(long double nNumber, long double nMin, long double nMax);

#endif