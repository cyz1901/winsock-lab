﻿
// project_fourDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_four.h"
#include "project_fourDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include <WinSock2.h>
#include <afxpriv.h>
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


// CprojectfourDlg 对话框



CprojectfourDlg::CprojectfourDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_FOUR_DIALOG, pParent)
	, m_strIP(_T(""))
	, m_strMsg(_T(""))
	, m_strMsgReturned(_T(""))
	, m_nPort(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectfourDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_RETURNED, m_strMsgReturned);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
}

BEGIN_MESSAGE_MAP(CprojectfourDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CprojectfourDlg::OnButtonSend)
END_MESSAGE_MAP()


// CprojectfourDlg 消息处理程序

BOOL CprojectfourDlg::OnInitDialog()
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

void CprojectfourDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CprojectfourDlg::OnPaint()
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
HCURSOR CprojectfourDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectfourDlg::OnButtonSend()
{	

	SOCKET clientsocket;
	sockaddr_in socketaddr;



	char rebuff[100] = {0};
	//LPSTR p;
	socketaddr.sin_family = AF_INET;

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	socketaddr.sin_port = htons(m_nPort);

	USES_CONVERSION;


	socketaddr.sin_addr.S_un.S_addr = inet_addr(W2A(m_strIP));//htol将主机字节序long型转换为网络字节序


	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	if (connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr)) == SOCKET_ERROR) {
		printf("connect fail \n");
	}



		

	send(clientsocket, W2A(m_strMsg), strlen(W2A(m_strMsg))+1, 0);

	int recv_status = recv(clientsocket, rebuff, sizeof(rebuff), 0); //接收文件长度
	if (recv_status > 0) {
	m_strMsgReturned = rebuff;
	TRACE("success recevice\n");

	closesocket(clientsocket);

	}
	UpdateData(FALSE);
}
