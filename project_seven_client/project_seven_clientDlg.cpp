//client and server
// project_seven_clientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_seven_client.h"
#include "project_seven_clientDlg.h"
#include "afxdialogex.h"
#include "resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <fstream>
#include <string>
using namespace std;


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
	addrlen = 0;
}

void CprojectsevenclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strIP);
	DDX_Text(pDX, IDC_EDIT1, m_nPort);
	//  DDX_Control(pDX, IDC_EDIT3, s_fileadd);
	DDX_Text(pDX, IDC_EDIT3, m_c_fileadd);
	DDX_Text(pDX, IDC_EDIT4, m_s_fileadd);
	//DDX_Control(pDX, IDC_LISTEN, edit_listen);
}

BEGIN_MESSAGE_MAP(CprojectsevenclientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//ON_BN_CLICKED(IDC_LISTEN, &CprojectsevenclientDlg::OnClickedListen)
	ON_BN_CLICKED(IDC_CONNECT, &CprojectsevenclientDlg::OnClickedConnect)

	ON_BN_CLICKED(IDC_banquan, &CprojectsevenclientDlg::OnClickedBanquan)
	ON_BN_CLICKED(IDC_LISTEN, &CprojectsevenclientDlg::OnClickedListen)
	ON_BN_CLICKED(IDC_BAOCUN, &CprojectsevenclientDlg::OnClickedBaocun)
	ON_BN_CLICKED(IDC_HELP, &CprojectsevenclientDlg::OnClickedHelp)
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
	AfxGetMainWnd()->SetWindowText(_T("计算机172 陈屹宙1732113426 陈奕楠1732111426"));
	// TODO: 在此添加额外的初始化代码
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData))
	{
		AfxMessageBox(_T("winsock startup failed"), MB_OKCANCEL | MB_ICONQUESTION, 0);
		PostMessage(WM_CLOSE);
	}

	// 初始化socket dll 
	//UpdateData(TRUE);
	//ifstream rfile;
	//ofstream ofile;
	//int n;
	//创建socket 
	//c_Socket = socket(AF_INET, SOCK_STREAM, 0);
	/*if (SOCKET_ERROR == c_Socket)
	{
		printf("Create Socket Error!");
		system("pause");
		exit(1);
	}
	*/


	addrlen = sizeof(struct sockaddr_in);
	//char s_buffer[512];
	//char r_buffer[512];
	//sockaddr_in	ss_addr, d_addr, cmp_daddr;

	//ss_addr赋值
	memset(&ss_addr, 0, addrlen);
	ss_addr.sin_family = AF_INET;
	USES_CONVERSION;
	ss_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ss_addr.sin_port = htons(6001);

	//d_addr赋值
	//memset(&d_addr, 0, addrlen);
	//d_addr.sin_family = AF_INET;
	//USES_CONVERSION;
	//d_addr.sin_addr.S_un.S_addr = inet_addr(W2A(m_strIP));
	//d_addr.sin_port = htons(m_nPort);

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




void CprojectsevenclientDlg::OnClickedConnect()
{
	// 初始化socket dll 
	UpdateData(TRUE);
	ifstream rfile;
	string check;
	char s_buffer[512];
	//创建socket 
	SOCKET c_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (SOCKET_ERROR == c_Socket)
	{
		TRACE("Create Socket Error!\n");

	}
	//d_addr赋值
	memset(&d_addr, 0, addrlen);
	d_addr.sin_family = AF_INET;
	USES_CONVERSION;
	d_addr.sin_addr.S_un.S_addr = inet_addr(W2A(m_strIP));
	d_addr.sin_port = htons(m_nPort);

	if (bind(c_Socket, (LPSOCKADDR)&ss_addr, addrlen)<0){
		TRACE("Can Not Connect To Client IP! ip is %s port is %d\n", W2A(m_strIP),(int)m_nPort);
	}
	int o;
	memset(s_buffer, 0, 512);

	rfile.open(m_c_fileadd, ios::binary);
	rfile.read(s_buffer, 512);
	o = sendto(c_Socket, s_buffer, strlen(s_buffer), 0, (LPSOCKADDR)&d_addr, addrlen);
	if (o <0) {
		TRACE("sendto error! is %d\n",o);
	}
	TRACE("have send %s |o is %d !\n",s_buffer,o);
	rfile.close();
	sendto(c_Socket, "over", strlen("over"), 0, (LPSOCKADDR)&d_addr, addrlen);
	closesocket(c_Socket);
}




void CprojectsevenclientDlg::OnClickedBanquan()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("计算机172 陈屹宙1732113426 陈奕楠1732111426"), MB_ICONQUESTION);
}


void CprojectsevenclientDlg::OnClickedListen()
{
	// TODO: 在此添加控件通知处理程序代码
	int n;
	ofstream ofile;
	string check;
	char r_buffer[512];
	memset(r_buffer, 0, 512);
	SOCKET c_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (SOCKET_ERROR == c_Socket)
	{
		TRACE("Create Socket Error!");
	}

	if (bind(c_Socket, (LPSOCKADDR)&ss_addr, addrlen) < 0) {
		TRACE("wtf\n");
	}
	while (1) {
		EnableWindow(FALSE);
		/* 接收信息并显示 */
		n = recvfrom(c_Socket, r_buffer, 512, 0, (LPSOCKADDR)&cmp_daddr, &addrlen);
		//ofile.open("D:/HAPP.txt", ios::binary);
		TRACE("rec buffer is %s!\n", r_buffer);
		check = r_buffer;
		if (n < 0) {
			memset(r_buffer, 0, 512);
			TRACE("rec error!\n");

		}
		if (check == "over") {
			TRACE("rec over!\n");
			AfxMessageBox(_T("传输完成 缓存文件存放于D:\\save.txt,请重定向文件存储位置"));
			break;
		}
		ofile.open("D:/save.txt", ios::binary);
		ofile.write(r_buffer, 512);
		ofile.close();
		memset(r_buffer, 0, 512);
	}

	closesocket(c_Socket);
	WSACleanup();

}


void CprojectsevenclientDlg::OnClickedBaocun()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ifstream input("D:/save.txt", ios::binary);
	ofstream output(m_s_fileadd, ios::binary);
	output << input.rdbuf();
}


void CprojectsevenclientDlg::OnClickedHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("帮助信息：\n  想使用本程序传输文件首先需要设置另一端的端口号和ip地址及文件地址\n然后接收端首先启动监听然后可以点击传输端的传输\n传输完成后默认文件缓存储存于D:/save.txt\n可使用保存功能重定向文件的储存地址"), MB_ICONQUESTION);
}
