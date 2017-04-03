
// TabCtrlDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TabCtrlPage1.h"
#include "TabCtrlPage2.h"

// CTabCtrlDemoDlg �Ի���
class CTabCtrlDemoDlg : public CDialogEx
{
// ����
public:
	CTabCtrlDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCTRLDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_tabCtrlPage;
	CTabCtrlPage1 m_page1;
	CTabCtrlPage2 m_page2;
public:
	afx_msg void OnTcnSelchangeTabCtrlPage(NMHDR *pNMHDR, LRESULT *pResult);
};
