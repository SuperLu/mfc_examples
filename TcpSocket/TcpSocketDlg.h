
// TcpSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CTcpSocketDlg �Ի���
class CTcpSocketDlg : public CDialogEx
{
// ����
public:
	CTcpSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTcpSocketDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCPSOCKET_DIALOG };
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
public:
	afx_msg void OnBnClickedButtonTcpServerStart();
	afx_msg void OnBnClickedButtonTcpServerSend();
	afx_msg void OnBnClickedButtonTcpClientConnect();
	afx_msg void OnBnClickedButtonTcpClientSend();
public:
	static DWORD WINAPI ServerSocketThreadProc(LPVOID lpParameter);
	BOOL ServerSocketHandleService();
	int ServerSocketInit();
	int ServerSocketClose();
	int ServerSocketSend();

	static DWORD WINAPI ClientSocketThreadProc(LPVOID lpParameter);
	BOOL ClientSocketHandleService();
	int ClientSocketInit();
	int ClientSocketClose();
	int ClientSocketSend();

private:
	CEdit m_editTcpServerPort;
	CEdit m_editTcpServerRecv;
	CEdit m_editTcpServerSend;
	CEdit m_editTcpClientIp;
	CEdit m_editTcpClientPort;
	CEdit m_editTcpClientRecv;
	CEdit m_editTcpClientSend;
	CButton m_btnTcpServerStart;
	CButton m_btnTcpServerSend;
	CButton m_btnTcpClientConnect;
	CButton m_btnTcpClientSend;

	//tcp server
private:
	SOCKET ServerForSaveClientParam;
	SOCKET ServerForListenClient;
	bool m_bServerIsConnected;

	HANDLE m_hServerThread;
	DWORD m_dwServerThreadId;
	//tcp client
private:
	SOCKET ClientSocket;
	bool m_bClientConnected;
	HANDLE m_hClientThread;
	DWORD m_dwClientThreadId;
	CStatic m_staticTcpServerStatus;
};
