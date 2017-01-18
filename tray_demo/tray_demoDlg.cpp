
// tray_demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tray_demo.h"
#include "tray_demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrayDemoDlg 对话框



CTrayDemoDlg::CTrayDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAY_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrayDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrayDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTrayDemoDlg 消息处理程序

BOOL CTrayDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTrayDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	switch (nType)
	{
	case SIZE_RESTORED:
		//AfxMessageBox(L"捕获到窗口还原消息");
		break;
	case SIZE_MINIMIZED:
		//AfxMessageBox(L"捕获到窗口最小化消息");
		DialogToTray();
		break;
	case SIZE_MAXIMIZED:
		//AfxMessageBox(L"捕获到窗口最大化消息");
		break;
	}
}

afx_msg LRESULT CTrayDemoDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
	{ 
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单
								//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口将程序结束。
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭")); //确定弹出式菜单的位置
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //资源回收
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	} break;
	case WM_LBUTTONDBLCLK://双击左键的处理
	{ 
		this->ShowWindow(SW_SHOW);//显示主窗口
		DeleteTray();
	} break;
	default: break;
	}
	return 0;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrayDemoDlg::OnPaint()
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
HCURSOR CTrayDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrayDemoDlg::DialogToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd; nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy((char *)nid.szTip, "程序名称"); //信息提示条
	Shell_NotifyIcon(NIM_ADD, &nid); //在托盘区添加图标
	ShowWindow(SW_HIDE); //隐藏主窗口
}

void CTrayDemoDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy((char *)nid.szTip, "程序名称"); //信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE, &nid); //在托盘区删除图标
}

