// TabCtrlPage1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabCtrlDemo.h"
#include "TabCtrlPage1.h"
#include "afxdialogex.h"


// CTabCtrlPage1 �Ի���

IMPLEMENT_DYNAMIC(CTabCtrlPage1, CDialogEx)

CTabCtrlPage1::CTabCtrlPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PAGE1, pParent)
{

}

CTabCtrlPage1::~CTabCtrlPage1()
{
}

void CTabCtrlPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCtrlPage1, CDialogEx)
END_MESSAGE_MAP()


// CTabCtrlPage1 ��Ϣ�������
