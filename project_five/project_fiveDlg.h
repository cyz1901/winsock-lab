
// project_fiveDlg.h: 头文件
//

#pragma once


// CprojectfiveDlg 对话框
class CprojectfiveDlg : public CDialogEx
{
// 构造
public:
	CprojectfiveDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_FIVE_DIALOG };
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
	afx_msg void OnEnChangeEdit3();
	CString m_server_name;
	short m_server_port;
	CString m_send_message;
	CString m_send_view_message;
	CString m_rev_view_message;
};
