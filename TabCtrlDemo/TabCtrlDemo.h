
// TabCtrlDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTabCtrlDemoApp: 
// �йش����ʵ�֣������ TabCtrlDemo.cpp
//

class CTabCtrlDemoApp : public CWinApp
{
public:
	CTabCtrlDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTabCtrlDemoApp theApp;