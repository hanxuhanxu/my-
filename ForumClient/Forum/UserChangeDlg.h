#pragma once
#include "afxwin.h"
#include "res.h"
#include"IMediator.h"

// CUserChangeDlg 对话框

class CUserChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserChangeDlg)

public:
	CUserChangeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserChangeDlg();

// 对话框数据
	enum { IDD = IDD_USER_CHANGE_DLG };
private:
	IMediator* m_pMediator;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_userName;
	CComboBox m_Sex;
	CString m_date;
	CString m_Brief;
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
