
// tray_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTrayDemoApp: 
// �йش����ʵ�֣������ tray_demo.cpp
//

class CTrayDemoApp : public CWinApp
{
public:
	CTrayDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrayDemoApp theApp;