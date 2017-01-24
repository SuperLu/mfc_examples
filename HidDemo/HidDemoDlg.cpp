
// HidDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HidDemo.h"
#include "HidDemoDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHidDemoDlg 对话框



CHidDemoDlg::CHidDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HIDDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHidDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHidDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ENUM_HID_DEVICE, &CHidDemoDlg::OnBnClickedBtnEnumHidDevice)
END_MESSAGE_MAP()


// CHidDemoDlg 消息处理程序

BOOL CHidDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHidDemoDlg::OnPaint()
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
HCURSOR CHidDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHidDemoDlg::OnBnClickedBtnEnumHidDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<HID_DEVICE_INFO> hid_device_info;
	CString device_path;
	if (usbHid.EnumHidDeviceInfo(hid_device_info))
	{
		for (int i = 0;i<hid_device_info.size();i++)
		{
			device_path = hid_device_info[i].device_path;
			DEBUGMSG(ZONE_PRINT, (_T("HID VID:0x%04x,PID:0x%04x,REV:0x%04x,SerialNumber:%s,DevicePath:%s\r\n"),hid_device_info[i].attributes.VendorID,
																				hid_device_info[i].attributes.ProductID,
																				hid_device_info[i].attributes.VersionNumber,
																				hid_device_info[i].serial_number,
																				device_path));
		}
	}
}
