
// project_threeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_three.h"
#include "project_threeDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

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


// CprojectthreeDlg 对话框



CprojectthreeDlg::CprojectthreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_THREE_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strIP(_T(""))
	, m_strHostInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectthreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_HOST_INFORMATION, m_strHostInfo);
}

BEGIN_MESSAGE_MAP(CprojectthreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EIDT_QUERY_BY_NAME, &CprojectthreeDlg::OnButtonQueryByName)
	ON_BN_CLICKED(IDC_EIDT_QUERY_BY_IP, &CprojectthreeDlg::OnButtonQueryByIp)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CprojectthreeDlg 消息处理程序

BOOL CprojectthreeDlg::OnInitDialog()
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

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData))
	{
		AfxMessageBox(_T("winsock startup failed"), MB_OKCANCEL | MB_ICONQUESTION, 0);
		PostMessage(WM_CLOSE);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprojectthreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CprojectthreeDlg::OnPaint()
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
HCURSOR CprojectthreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectthreeDlg::OnButtonQueryByName()
{
	// TODO: 在此添加控件通知处理程序代码

//根据控件中的值更新对应变量的值
	UpdateData(TRUE);
	//如果域名为空， 则查询本机信息
	if (m_strName.IsEmpty())
	{
		char name[256];
		gethostname(name, 256);
		m_strName = name;


	} 
	hostent* host = gethostbyname((LPSTR)(LPCTSTR)m_strName);
	if (host)
	{
		m_strIP = inet_ntoa(*(in_addr*)host->h_addr_list[0]);
	} 
	m_strHostInfo = "主机名： ";
	m_strHostInfo += m_strName;
	m_strHostInfo += "\r\nIP 地址： ";
	m_strHostInfo += m_strIP;
	m_strHostInfo += "\r\n\r\n 作者：1732113426 计算机172 陈屹宙"; //请改为自

		UpdateData(FALSE); //根据变量的值更新对应控件的值
}


void CprojectthreeDlg::OnButtonQueryByIp()
{	
	// TODO: 在此添加控件通知处理程序代码
	hostent* host = NULL;
	UpdateData(TRUE);
	//如果域名为空， 则查询本机信息
	if (m_strIP.IsEmpty())
	{
		char ip[256];
		gethostname(ip, 256);
		m_strIP = ip;
		host = gethostbyname((LPSTR)(LPCTSTR)m_strName);

	}
	
	if (host)
	{
		m_strIP = inet_ntoa(*(in_addr*)host->h_addr_list[0]);
	}
	m_strHostInfo = "主机名： ";
	m_strHostInfo += m_strName;
	m_strHostInfo += "\r\nIP 地址： ";
	m_strHostInfo += m_strIP;
	m_strHostInfo += "\r\n\r\n 作者：1732113426 计算机172 陈屹宙"; //请改为自

	UpdateData(FALSE); //根据变量的值更新对应控件的值
}


void CprojectthreeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: Add your message handler code here
	WSACleanup();
	AfxMessageBox(_T("destroyed"), MB_OKCANCEL | MB_ICONQUESTION, 0);
	// TODO: 在此处添加消息处理程序代码
}
