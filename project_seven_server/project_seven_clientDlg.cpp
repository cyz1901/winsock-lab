//server
// project_seven_clientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_seven_client.h"
#include "project_seven_clientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <fstream>
using namespace std;
#include <fstream>


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CprojectsevenclientDlg 对话框



CprojectsevenclientDlg::CprojectsevenclientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_SEVEN_CLIENT_DIALOG, pParent)
	, m_strIP(_T(""))
	, m_nPort(0)
	, m_c_fileadd(_T(""))
	, m_s_fileadd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectsevenclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strIP);
	DDX_Text(pDX, IDC_EDIT1, m_nPort);
	//  DDX_Control(pDX, IDC_EDIT3, s_fileadd);
	DDX_Text(pDX, IDC_EDIT3, m_c_fileadd);
	DDX_Text(pDX, IDC_EDIT4, m_s_fileadd);
	DDX_Control(pDX, IDC_LISTEN, edit_listen);
}

BEGIN_MESSAGE_MAP(CprojectsevenclientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_LISTEN, &CprojectsevenclientDlg::OnClickedListen)
	ON_BN_CLICKED(IDC_CONNECT, &CprojectsevenclientDlg::OnClickedConnect)

END_MESSAGE_MAP()


// CprojectsevenclientDlg 消息处理程序

BOOL CprojectsevenclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData))
	{
		AfxMessageBox(_T("winsock startup failed"), MB_OKCANCEL | MB_ICONQUESTION, 0);
		PostMessage(WM_CLOSE);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprojectsevenclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CprojectsevenclientDlg::OnPaint()
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
HCURSOR CprojectsevenclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CprojectsevenclientDlg::OnClickedListen()
{	
	UpdateData(TRUE);
	// 声明并初始化一个服务端(本地)的地址结构 
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	server_addr.sin_port = htons(6001);

	// 创建socket 
	SOCKET m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_Socket)
	{
		printf("Create Socket Error!");
		exit(1);
	}

	//绑定socket和服务端(本地)地址 
	if (SOCKET_ERROR == bind(m_Socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)))
	{
		printf("Server Bind Failed: %d", WSAGetLastError());
		exit(1);
	}

	//监听 
	if (SOCKET_ERROR == listen(m_Socket, 10))
	{
		printf("Server Listen Failed: %d", WSAGetLastError());
		exit(1);
	}


	ofstream rfile;
	//rfile.open(m_s_fileadd, ios::binary);
	rfile.open(m_s_fileadd, ios::binary);
	string x;
	char buffer[512];

	printf("Listening To Server...\n");    //监听服务器需求


	sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	SOCKET m_New_Socket = accept(m_Socket, (sockaddr*)&client_addr, &client_addr_len);
	if (SOCKET_ERROR == m_New_Socket)
	{
		printf("Server Accept Failed: %d", WSAGetLastError());

	}

	memset(buffer, 0, 512);


	char file_name[1024 + 1];
	memset(file_name, 0, 1024 + 1);
	printf("%s\n", file_name);



	//rfile.open("D:\\happy.txt", ios::binary);
	//rfile.open("D:\\happy.txt", ios::binary);
	while (1)
	{

		edit_listen.EnableWindow(FALSE);
		int redlen = recv(m_New_Socket, buffer, 512, 0);
		x = buffer;
		if (redlen <= 0)
		{	
			TRACE("server OVER \n", buffer);;
			rfile.close();
			closesocket(m_New_Socket);
			break;
		}
		if (x == "client:send over!")
		{
			TRACE("server recv %s \n", buffer);;
			send(m_New_Socket, "server:recv over!", strlen("server:recv over!") + 1, 0);
			rfile.close();
			closesocket(m_New_Socket);
			break;
		}
		//
		
		rfile.write(buffer, redlen);
		TRACE("recv is %s the len is %d\n", buffer, redlen);
		send(m_New_Socket,"server:wait recv",strlen("server:wait recv")+1,0);
		closesocket(m_New_Socket);
		rfile.close();

	}
	rfile.close();

	closesocket(m_Socket);
	//释放winsock库 
	WSACleanup();
	edit_listen.EnableWindow(TRUE);

		
}


void CprojectsevenclientDlg::OnClickedConnect()
{
	
}


//void CprojectsevenclientDlg::OnClickedExitConect()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	WSACleanup();
//}


//void CprojectsevenclientDlg::OnClickedExitListen()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	m_bLoop = false;
//	WSACleanup();
//}


//bool CprojectsevenclientDlg::DoEvents()
//{
//	// TODO: 在此处添加实现代码.
//	MSG msg;
//	::GetMessage(&msg, 0, 0, 0);
//	if (msg.message == WM_QUIT){
//		PostQuitMessage(msg.wParam);
//		return FALSE;
//	}
//	else{
//         ::TranslateMessage(&msg);
//        ::DispatchMessage(&msg);
//         return TRUE;
//	}
//}
