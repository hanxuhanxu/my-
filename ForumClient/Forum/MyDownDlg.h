#pragma once


// CMyDownDlg 对话框

class CMyDownDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownDlg)

public:
	CMyDownDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDownDlg();

// 对话框数据
	enum { IDD = IDD_MYDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
