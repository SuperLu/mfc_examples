#pragma once


// CTabCtrlPage1 �Ի���

class CTabCtrlPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCtrlPage1)

public:
	CTabCtrlPage1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCtrlPage1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
