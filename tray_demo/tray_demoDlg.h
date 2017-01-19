
// tray_demoDlg.h : 头文件
//

#pragma once
#define WM_SHOWTASK (WM_USER +1)
#define WM_TRAY_MENU_SHOW (WM_USER+2)
// CTrayDemoDlg 对话框
class CTrayDemoDlg : public CDialogEx
{
// 构造
public:
	CTrayDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAY_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
