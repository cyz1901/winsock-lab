
// project_fiveDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "project_five.h"
#include "project_fiveDlg.h"
#include "afxdialogex.h"
#include "Afxinet.h"

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


// CprojectfiveDlg 对话框



CprojectfiveDlg::CprojectfiveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_FIVE_DIALOG, pParent)
	, m_strFtp(_T(""))
	, m_strName(_T(""))
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojectfiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDOK, m_btnQuery);
	DDX_Control(pDX, IDC_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
}

BEGIN_MESSAGE_MAP(CprojectfiveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CprojectfiveDlg::OnQuery)
	ON_BN_CLICKED(IDC_DOWNLOAD, &CprojectfiveDlg::OnDownload)
	ON_BN_CLICKED(IDC_UPLOAD, &CprojectfiveDlg::OnUpload)
	ON_EN_CHANGE(IDC_EDIT_FTP, &CprojectfiveDlg::OnEnChangeEditFtp)
END_MESSAGE_MAP()


// CprojectfiveDlg 消息处理程序

BOOL CprojectfiveDlg::OnInitDialog()
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
	m_strFtp = _T(""); // 初始化服务器域名
	m_strName = _T(""); // 初始化登录用户名
	m_strPwd = _T(""); // 初始化登录口令
	UpdateData(FALSE); //更新界面
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprojectfiveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CprojectfiveDlg::OnPaint()
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
HCURSOR CprojectfiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CprojectfiveDlg::OnQuery()
{
	CInternetSession  pInternetCon(AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	m_pFtpConn = pInternetCon.GetFtpConnection(m_strFtp, m_strName, m_strPwd, 21);
	CFtpFileFind cfind(m_pFtpConn);
	bool cfindcheck = cfind.FindFile(_T("*"));
	while (cfindcheck)
	{
		cfindcheck = cfind.FindNextFile();
		m_listFile.AddString((LPCTSTR)cfind.GetFileName());
	}
	cfind.Close();
	m_pFtpConn->Close();
	UpdateData(FALSE); //更新界面
}


void CprojectfiveDlg::OnDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	CInternetSession  pInternetCon(AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	m_pFtpConn = pInternetCon.GetFtpConnection(m_strFtp, m_strName, m_strPwd, 21);
	Download((CString)"D:\\实验\server", (CString)"D:\\实验\local");
	m_pFtpConn->Close();
}


void CprojectfiveDlg::OnUpload()
{
	// TODO: 在此添加控件通知处理程序代码

	CInternetSession  pInternetCon(AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	m_pFtpConn = pInternetCon.GetFtpConnection(m_strFtp, m_strName, m_strPwd, 21);
	Upload((CString)"D:\\实验\local", (CString)"D:\\实验\server");
	m_pFtpConn->Close();
}


void CprojectfiveDlg::OnEnChangeEditFtp()
{	

	CDialogEx::OnOK();
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




bool CprojectfiveDlg::Download(CString strSName, CString strDName)
{

	// TODO: 在此处添加实现代码.
	return m_pFtpConn->GetFile(strSName, strDName);
}


bool CprojectfiveDlg::Upload(CString strSName, CString strDName)
{
	// TODO: 在此处添加实现代码.
	return false;
}
