#pragma once


// CMyBlogDlg 对话框

class CMyBlogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyBlogDlg)

public:
	CMyBlogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyBlogDlg();

// 对话框数据
	enum { IDD = IDD_MYBLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
