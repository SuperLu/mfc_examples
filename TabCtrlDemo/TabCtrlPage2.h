#pragma once


// CTabCtrlPage2 �Ի���

class CTabCtrlPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCtrlPage2)

public:
	CTabCtrlPage2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabCtrlPage2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
