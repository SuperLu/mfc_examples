
// TcpSocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TcpSocket.h"
#include "TcpSocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTcpSocketDlg 对话框



CTcpSocketDlg::CTcpSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TCPSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTcpSocketDlg::~CTcpSocketDlg()
{
	WSACleanup();
}

void CTcpSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TCP_SERVER_PORT, m_editTcpServerPort);
	DDX_Control(pDX, IDC_EDIT_TCP_SERVER_RECV, m_editTcpServerRecv);
	DDX_Control(pDX, IDC_EDIT_TCP_SERVER_SEND, m_editTcpServerSend);
	DDX_Control(pDX, IDC_EDIT_TCP_CLIENT_IP, m_editTcpClientIp);
	DDX_Control(pDX, IDC_EDIT_TCP_CLIENT_PORT, m_editTcpClientPort);
	DDX_Control(pDX, IDC_EDIT_TCP_CLIENT_RECV, m_editTcpClientRecv);
	DDX_Control(pDX, IDC_EDIT_TCP_CLIENT_SEND, m_editTcpClientSend);
	DDX_Control(pDX, IDC_BUTTON_TCP_SERVER_START, m_btnTcpServerStart);
	DDX_Control(pDX, IDC_BUTTON_TCP_SERVER_SEND, m_btnTcpServerSend);
	DDX_Control(pDX, IDC_BUTTON_TCP_CLIENT_CONNECT, m_btnTcpClientConnect);
	DDX_Control(pDX, IDC_BUTTON_TCP_CLIENT_SEND, m_btnTcpClientSend);
	DDX_Control(pDX, IDC_STATIC_TCP_SERVER_STATUS, m_staticTcpServerStatus);
}

BEGIN_MESSAGE_MAP(CTcpSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TCP_SERVER_START, &CTcpSocketDlg::OnBnClickedButtonTcpServerStart)
	ON_BN_CLICKED(IDC_BUTTON_TCP_SERVER_SEND, &CTcpSocketDlg::OnBnClickedButtonTcpServerSend)
	ON_BN_CLICKED(IDC_BUTTON_TCP_CLIENT_CONNECT, &CTcpSocketDlg::OnBnClickedButtonTcpClientConnect)
	ON_BN_CLICKED(IDC_BUTTON_TCP_CLIENT_SEND, &CTcpSocketDlg::OnBnClickedButtonTcpClientSend)
END_MESSAGE_MAP()


// CTcpSocketDlg 消息处理程序

BOOL CTcpSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTcpSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTcpSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTcpSocketDlg::OnBnClickedButtonTcpServerStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bServerIsConnected == false)
	{
		if (ServerSocketInit())
		{
			m_bServerIsConnected = true;
			m_hServerThread = CreateThread(NULL, 0, ServerSocketThreadProc, (LPVOID)this, 0, &m_dwServerThreadId);
			if (m_hServerThread == INVALID_HANDLE_VALUE)
			{
				return;
			}
			m_btnTcpServerStart.SetWindowText(_T("Stop"));
			m_staticTcpServerStatus.SetWindowText(_T("Disconnect"));
		}
	}
	else
	{
		m_bServerIsConnected = false;
		ServerSocketClose();
		m_btnTcpServerStart.SetWindowText(_T("Start"));
	}
}


void CTcpSocketDlg::OnBnClickedButtonTcpServerSend()
{
	// TODO: 在此添加控件通知处理程序代码
	ServerSocketSend();
}


void CTcpSocketDlg::OnBnClickedButtonTcpClientConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bClientConnected == false)
	{
		if (ClientSocketInit())
		{
			m_bClientConnected = true;
			m_hClientThread = CreateThread(NULL, 0, ClientSocketThreadProc, (LPVOID)this, 0, &m_dwClientThreadId);
			if (m_hClientThread == INVALID_HANDLE_VALUE)
			{
				return;
			}
			m_btnTcpClientConnect.SetWindowText(_T("Disconnect"));
		}
	}
	else
	{
		m_bClientConnected = false;
		ClientSocketClose();
		m_btnTcpClientConnect.SetWindowText(_T("Connect"));
	}
}


void CTcpSocketDlg::OnBnClickedButtonTcpClientSend()
{
	// TODO: 在此添加控件通知处理程序代码
	ClientSocketSend();
}

DWORD WINAPI CTcpSocketDlg::ServerSocketThreadProc(LPVOID lpParameter)
{
	((CTcpSocketDlg *)lpParameter)->ServerSocketHandleService();
	return 0;
}

BOOL CTcpSocketDlg::ServerSocketHandleService()
{
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	CString strConnectStatus;
	m_staticTcpServerStatus.SetWindowText(_T("wait for connect ..."));
	ServerForSaveClientParam = accept(ServerForListenClient, (SOCKADDR *)&remoteAddr, &nAddrlen);
	if (ServerForSaveClientParam == INVALID_SOCKET)
	{
		m_staticTcpServerStatus.SetWindowText(_T("accept error !"));
		return 1;
	}
	strConnectStatus.Format(_T("已连接：%s \r\n"), inet_ntoa(remoteAddr.sin_addr));
	m_staticTcpServerStatus.SetWindowText(strConnectStatus);
	while (m_bServerIsConnected)
	{
		//接收数据
		int ret = recv(ServerForSaveClientParam, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			m_editTcpServerRecv.SetWindowText((LPCTSTR)revData);
		}
	}
}

int CTcpSocketDlg::ServerSocketInit()
{
	//初始化WSA
	CString strPort;
	//创建套接字
	ServerForListenClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerForListenClient == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口
	m_editTcpServerPort.GetWindowText(strPort);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(strPort.GetBuffer()));
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(ServerForListenClient, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听
	if (listen(ServerForListenClient, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	return 1;
}

int CTcpSocketDlg::ServerSocketClose()
{
	closesocket(ServerForSaveClientParam);
	closesocket(ServerForListenClient);
	return 1;
}

int CTcpSocketDlg::ServerSocketSend()
{
	//发送数据
	CString strText;
	m_editTcpServerSend.GetWindowText(strText);
	return send(ServerForSaveClientParam, (char *)strText.GetBuffer(), strText.GetLength(), 0);
}

DWORD WINAPI CTcpSocketDlg::ClientSocketThreadProc(LPVOID lpParameter)
{
	((CTcpSocketDlg *)lpParameter)->ClientSocketHandleService();
	return 0;
}

BOOL CTcpSocketDlg::ClientSocketHandleService()
{
	while (m_bClientConnected)
	{
		char recData[255] = { 0 };
		int ret = recv(ClientSocket, recData, 255, 0);
		if (ret > 0)
		{
			recData[ret] = 0x00;
			m_editTcpClientRecv.SetWindowText((LPCTSTR)recData);
			OutputDebugStringA(recData);
		}
	}
	return TRUE;
}

int CTcpSocketDlg::ClientSocketInit()
{
	CString strIp;
	CString strPort;
	

	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0;
	}
	m_editTcpClientIp.GetWindowText(strIp);
	m_editTcpClientPort.GetWindowText(strPort);
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(atoi(strPort.GetBuffer()));
	serAddr.sin_addr.S_un.S_addr = inet_addr((char *)strIp.GetBuffer());
	if (connect(ClientSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		OutputDebugStringA("connect error !");
		closesocket(ClientSocket);
		return 0;
	}
	return 1;
}

int CTcpSocketDlg::ClientSocketClose()
{
	closesocket(ClientSocket);
	return 0;
}

int CTcpSocketDlg::ClientSocketSend()
{
	int ret;
	CString strText;
	m_editTcpClientSend.GetWindowText(strText);
	ret = send(ClientSocket, (char *)strText.GetBuffer(), strText.GetLength(), 0);
	if (ret <= 0)
	{
		AfxMessageBox(_T("发送失败"));
	}
	return 1;
}
