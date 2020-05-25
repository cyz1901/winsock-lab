
// project_sixDlg.h: 头文件
//

#pragma once


// CprojectsixDlg 对话框
class CprojectsixDlg : public CDialogEx
{
// 构造
public:
	CprojectsixDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_SIX_DIALOG };
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
	CListBox m_ctrlList;
//	void OnButtonRun();
//	void OnButtonSave();
	afx_msg void OnButtonRun();
	afx_msg void OnCancel();
	afx_msg void OnButtonSave();
	SOCKET m_listenSock;
};
