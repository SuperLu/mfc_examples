
// TabCtrlDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabCtrlDemo.h"
#include "TabCtrlDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabCtrlDemoDlg �Ի���



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


// CTabCtrlDemoDlg ��Ϣ�������

BOOL CTabCtrlDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTabCtrlDemoDlg::OnPaint()
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
HCURSOR CTabCtrlDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabCtrlDemoDlg::OnTcnSelchangeTabCtrlPage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
