
// TabCtrlDemoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TabCtrlPage1.h"
#include "TabCtrlPage2.h"

// CTabCtrlDemoDlg 对话框
class CTabCtrlDemoDlg : public CDialogEx
{
// 构造
public:
	CTabCtrlDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCTRLDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
