
// tray_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "tray_demo.h"
#include "tray_demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrayDemoDlg �Ի���



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


// CTrayDemoDlg ��Ϣ�������

BOOL CTrayDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTrayDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	switch (nType)
	{
	case SIZE_RESTORED:
		//AfxMessageBox(L"���񵽴��ڻ�ԭ��Ϣ");
		break;
	case SIZE_MINIMIZED:
		//AfxMessageBox(L"���񵽴�����С����Ϣ");
		DialogToTray();
		break;
	case SIZE_MAXIMIZED:
		//AfxMessageBox(L"���񵽴��������Ϣ");
		break;
	}
}

afx_msg LRESULT CTrayDemoDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�
	{ 
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//�õ����λ��
		CMenu menu;
		menu.CreatePopupMenu();//����һ������ʽ�˵�
								//���Ӳ˵���رա������������ϢWM_DESTROY�������ڽ����������
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�ر�")); //ȷ������ʽ�˵���λ��
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //��Դ����
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	} break;
	case WM_LBUTTONDBLCLK://˫������Ĵ���
	{ 
		this->ShowWindow(SW_SHOW);//��ʾ������
		DeleteTray();
	} break;
	default: break;
	}
	return 0;
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTrayDemoDlg::OnPaint()
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
	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy((char *)nid.szTip, "��������"); //��Ϣ��ʾ��
	Shell_NotifyIcon(NIM_ADD, &nid); //�����������ͼ��
	ShowWindow(SW_HIDE); //����������
}

void CTrayDemoDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy((char *)nid.szTip, "��������"); //��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
	Shell_NotifyIcon(NIM_DELETE, &nid); //��������ɾ��ͼ��
}

