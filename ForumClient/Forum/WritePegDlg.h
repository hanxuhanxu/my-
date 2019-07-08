#pragma once
#include "afxwin.h"
#include "UDPNet.h"
#include "afxcmn.h"
#include"resource.h"

// CWritePegDlg 对话框

class CWritePegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWritePegDlg)

public:
	CWritePegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWritePegDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_WRITEDLG };
	afx_msg void OnBnClickedButton1();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_MyTitle;     //标题
	CEdit m_Content;    //正文
public:
	afx_msg void OnBnClickedButton3();
	CProgressCtrl m_transFilePro;
};
