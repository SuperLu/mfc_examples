#pragma once


// CTabCtrlPage2 对话框

class CTabCtrlPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCtrlPage2)

public:
	CTabCtrlPage2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCtrlPage2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
