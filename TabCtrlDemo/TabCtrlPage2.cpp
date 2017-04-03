// TabCtrlPage2.cpp : 实现文件
//

#include "stdafx.h"
#include "TabCtrlDemo.h"
#include "TabCtrlPage2.h"
#include "afxdialogex.h"


// CTabCtrlPage2 对话框

IMPLEMENT_DYNAMIC(CTabCtrlPage2, CDialogEx)

CTabCtrlPage2::CTabCtrlPage2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PAGE2, pParent)
{

}

CTabCtrlPage2::~CTabCtrlPage2()
{
}

void CTabCtrlPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCtrlPage2, CDialogEx)
END_MESSAGE_MAP()


// CTabCtrlPage2 消息处理程序
