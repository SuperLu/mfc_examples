
// HidDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HidDemo.h"
#include "HidDemoDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHidDemoDlg �Ի���



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


// CHidDemoDlg ��Ϣ�������

BOOL CHidDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHidDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHidDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHidDemoDlg::OnBnClickedBtnEnumHidDevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
