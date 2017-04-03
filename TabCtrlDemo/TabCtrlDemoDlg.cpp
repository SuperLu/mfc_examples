
// TabCtrlDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TabCtrlDemo.h"
#include "TabCtrlDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabCtrlDemoDlg 对话框



CTabCtrlDemoDlg::CTabCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABCTRLDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CTRL_PAGE, m_tabCtrlPage);
}

BEGIN_MESSAGE_MAP(CTabCtrlDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTRL_PAGE, &CTabCtrlDemoDlg::OnTcnSelchangeTabCtrlPage)
END_MESSAGE_MAP()


// CTabCtrlDemoDlg 消息处理程序

BOOL CTabCtrlDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	//GetClientRect(&rect);
	m_tabCtrlPage.GetClientRect(&rect);
	m_tabCtrlPage.InsertItem(0, _T("PAGE1"));
	m_tabCtrlPage.InsertItem(1, _T("PAGE2"));
	rect.top += 21;
	rect.bottom -= 1;
	rect.left += 1;
	rect.right -= 1;
	m_page1.Create(IDD_DIALOG_PAGE1, GetDlgItem(IDC_TAB_CTRL_PAGE));
	m_page2.Create(IDD_DIALOG_PAGE2, GetDlgItem(IDC_TAB_CTRL_PAGE));
	m_page1.MoveWindow(&rect);
	m_page2.MoveWindow(&rect);
	m_page2.ShowWindow(SW_SHOW);
	m_tabCtrlPage.SetCurSel(1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTabCtrlDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTabCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabCtrlDemoDlg::OnTcnSelchangeTabCtrlPage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int nCurSel = m_tabCtrlPage.GetCurSel();
	switch (nCurSel)
	{
	case 0:
		m_page1.ShowWindow(SW_SHOW);
		m_page2.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_page1.ShowWindow(SW_HIDE);
		m_page2.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}
