
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#define DEBUGZONE(n)  (g_debug_zone & (0x00000001<<(n)))

#define ZONE_ERROR_BIT		(0)
#define ZONE_WARN_BIT		(1)
#define ZONE_INFO_BIT		(2)
#define ZONE_LOG_BIT		(3)
#define ZONE_PRINT_BIT		(4)

#define ZONE_ERROR_MASK	(0x01 << ZONE_ERROR_BIT)
#define ZONE_WARN_MASK	(0x01 << ZONE_WARN_BIT)
#define ZONE_INFO_MASK		(0x01 << ZONE_INFO_BIT)
#define ZONE_LOG_MASK	        (0x01 << ZONE_LOG_BIT)
#define ZONE_PRINT_MASK	        (0x01 << ZONE_PRINT_BIT)

#define ZONE_ERROR		DEBUGZONE(ZONE_ERROR_BIT)
#define ZONE_WARN		DEBUGZONE(ZONE_WARN_BIT)
#define ZONE_INFO		DEBUGZONE(ZONE_INFO_BIT)
#define ZONE_LOG		DEBUGZONE(ZONE_LOG_BIT)
#define ZONE_PRINT		DEBUGZONE(ZONE_PRINT_BIT)

#define DEBUGMSG(cond, printf_exp) ((cond)?(DEBUGPRINT printf_exp): 1)


extern DWORD g_debug_zone;
void DEBUGPRINT(const TCHAR *szFormat, ...);
void LogFileA(char *file, char *mode, char *lpszFmt, ...);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


