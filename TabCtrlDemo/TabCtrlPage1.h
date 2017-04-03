#pragma once


// CTabCtrlPage1 对话框

class CTabCtrlPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCtrlPage1)

public:
	CTabCtrlPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCtrlPage1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
