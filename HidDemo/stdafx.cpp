
// stdafx.cpp : 只包括标准包含文件的源文件
// HidDemo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


#if !defined(_DEBUG)
#define _DEBUG_TO_FILE
#endif /* _DEBUG */

DWORD  g_debug_zone = ZONE_PRINT_MASK |
ZONE_ERROR_MASK |
ZONE_WARN_MASK |
ZONE_INFO_MASK |
ZONE_LOG_MASK ;

TCHAR g_out[4096];


extern TCHAR szLogPath[MAX_PATH];

#ifdef _DEBUG_TO_FILE
TCHAR g_szLogFile[MAX_PATH] = _T("HidDemo.log");
#endif /* _DEBUG_TO_FILE */

void DEBUGPRINT(const TCHAR *szFormat, ...)
{
#ifdef _DEBUG_TO_FILE
	FILE *stream;
	va_list arglist;
	SYSTEMTIME stime;

	stream = _tfopen(g_szLogFile, _T("a+b"));
	if (stream)
	{
		GetLocalTime(&stime);
		va_start(arglist, szFormat);
		_ftprintf(stream, _T("[%02d/%02d/%02d %02d:%02d:%02d]: "),
			stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
		_vftprintf(stream, szFormat, arglist);
		va_end(arglist);
		fclose(stream);
	}
#elif defined(_DEBUG)
	va_list vl;
	SYSTEMTIME stime;

	GetLocalTime(&stime);
	_stprintf(g_out, TEXT("[%02d/%02d/%02d %02d:%02d:%02d] "),
		stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond);
	va_start(vl, szFormat);
	_vstprintf(g_out, szFormat, vl);
	OutputDebugString(g_out);
	va_end(vl);
#endif /* _DEBUG_TO_FILE */
}


void LogFileA(char *file, char *mode, char *lpszFmt, ...)
{
	FILE *stream;
	va_list arglist;

	stream = fopen(file, mode);
	if (stream)
	{
		va_start(arglist, lpszFmt);
		vfprintf(stream, lpszFmt, arglist);
		va_end(arglist);
		fclose(stream);
	}
}