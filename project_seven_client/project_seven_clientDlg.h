
// project_seven_clientDlg.h: 头文件
//

#pragma once


// CprojectsevenclientDlg 对话框
class CprojectsevenclientDlg : public CDialogEx
{
// 构造
public:
	CprojectsevenclientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_SEVEN_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CString m_strIP;
	short m_nPort;
	afx_msg void OnClickedConnect();
	CString m_c_fileadd;
	CString m_s_fileadd;
	bool m_bLoop;
	CButton edit_listen;
	afx_msg void OnClickedBanquan();
	sockaddr_in ss_addr;
	sockaddr_in d_addr;
	sockaddr_in cmp_daddr;
	int addrlen;
	//SOCKET c_Socket;
	afx_msg void OnClickedListen();
	afx_msg void OnClickedBaocun();
	afx_msg void OnClickedHelp();
};
