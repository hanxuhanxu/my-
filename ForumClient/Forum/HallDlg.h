#pragma once
#include"resource.h"
#include "afxwin.h"
#include"MyDlg.h"
#include"WritePegDlg.h"

// CHallDlg 对话框

class CHallDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHallDlg)

public:
	CHallDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHallDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_HALL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnUserInfoMsg(WPARAM,LPARAM);	
	afx_msg void OnBnClickedButton9();

public:
	CListBox m_LastArticle;
	CMyDlg * m_pMyDlg;  //个人主页
	CWritePegDlg  * m_pWritePegDlg;   //写文章
};
