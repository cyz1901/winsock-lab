
// project_fiveDlg.h: 头文件
//

#pragma once
#include "Afxinet.h"

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
	afx_msg void OnQuery();
	afx_msg void OnDownload();
	afx_msg void OnUpload();
//	CStatic m_staFtp;
//	CStatic m_staName;
//	CStatic m_staPwd;
	afx_msg void OnEnChangeEditFtp();
	CString m_strFtp;
	CEdit m_editFtp;
	CString m_strName;
	CEdit m_editName;
	CString m_strPwd;
	CEdit m_editPwd;
	CButton m_btnQuery;
	CButton m_btnUpload;
	CButton m_btnDownload;
	CListBox m_listFile;
	bool Download(CString strSName, CString strDName);
	bool Upload(CString strSName, CString strDName);

	CFtpConnection *m_pFtpConn;
};
