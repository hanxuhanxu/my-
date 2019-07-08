#pragma once


// CMyNoticeDlg 对话框

class CMyNoticeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyNoticeDlg)

public:
	CMyNoticeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyNoticeDlg();

// 对话框数据
	enum { IDD = IDD_MYNOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
