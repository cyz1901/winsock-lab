
// project_threeDlg.h: 头文件
//

#pragma once


// CprojectthreeDlg 对话框
class CprojectthreeDlg : public CDialogEx
{
// 构造
public:
	CprojectthreeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_THREE_DIALOG };
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
	CString m_strName;
	CString m_strIP;
	CString m_strHostInfo;
	afx_msg void OnButtonQueryByName();
	afx_msg void OnButtonQueryByIp();
	afx_msg void OnDestroy();
};
