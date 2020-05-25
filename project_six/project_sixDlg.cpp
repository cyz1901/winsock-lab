
// project_sixDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_six.h"
#include "project_sixDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CprojectsixDlg 对话框



CprojectsixDlg::CprojectsixDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_SIX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectsixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}

BEGIN_MESSAGE_MAP(CprojectsixDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CprojectsixDlg::OnButtonRun)
	ON_BN_CLICKED(IDCANCEL, &CprojectsixDlg::OnCancel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CprojectsixDlg::OnButtonSave)
END_MESSAGE_MAP()


// CprojectsixDlg 消息处理程序

BOOL CprojectsixDlg::OnInitDialog()
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
	if (WSAStartup(MAKEWORD(1, 1), &wsaData)) //调用初始化函数， 版本号为 1.1
	{

		PostMessage(WM_CLOSE);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprojectsixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CprojectsixDlg::OnPaint()
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
HCURSOR CprojectsixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//void CprojectsixDlg::OnButtonRun()
//{
//	// TODO: 在此处添加实现代码.
//}


//void CprojectsixDlg::OnButtonSave()
//{
//	// TODO: 在此处添加实现代码.
//}


void CprojectsixDlg::OnButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	WSADATA wsaData;

	sockaddr_in socketaddr;//存放本地地址信息
	SOCKET responseSocket;
	const char* sendData = "hello i'am server";

	DWORD dwIPAddress = inet_addr("127.0.0.1");
	if (dwIPAddress == INADDR_NONE) {
		puts("Invalid Internet Address");
	}
	else {
		hostent* pHostEnt = gethostbyaddr((const char*)&dwIPAddress, 4, AF_INET);
		if (pHostEnt) {
			char* strIPAddress = inet_ntoa(*(in_addr*)pHostEnt->h_addr_list[0]);
			printf("name = %s, ip = %s\n", pHostEnt->h_name, strIPAddress);

			socketaddr.sin_family = AF_INET;
			socketaddr.sin_port = htons(6001);//htos用来将端口转换成字符，1024以上的数字即可
			socketaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htol将主机字节序long型转换为网络字节序

			m_listenSock = socket(AF_INET, SOCK_STREAM, 0);
			bind(m_listenSock, (SOCKADDR*)&socketaddr, sizeof(SOCKADDR));

			listen(m_listenSock, 5);
			int len = sizeof(SOCKADDR);
			char buff[100] = { 0 };
			while (1) {

				responseSocket = accept(m_listenSock, (SOCKADDR*)&socketaddr, &len);

				send(responseSocket, sendData, strlen(sendData), 0);


				recv(responseSocket, buff, sizeof(buff), 0);
				m_ctrlList.AddString((LPCTSTR)buff);


				UpdateData(FALSE);
				closesocket(responseSocket);

			}

			//closesocket(serversocket);
		}
	}
}


void CprojectsixDlg::OnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	closesocket(m_listenSock);
	WSACleanup();
	CDialogEx::OnCancel();
}


void CprojectsixDlg::OnButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
}
