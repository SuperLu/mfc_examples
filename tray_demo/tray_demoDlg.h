
// tray_demoDlg.h : ͷ�ļ�
//

#pragma once
#define WM_SHOWTASK (WM_USER +1)
#define WM_TRAY_MENU_SHOW (WM_USER+2)
// CTrayDemoDlg �Ի���
class CTrayDemoDlg : public CDialogEx
{
// ����
public:
	CTrayDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAY_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void DialogToTray();
	void DeleteTray();
};
