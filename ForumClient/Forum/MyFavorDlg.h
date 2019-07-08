#pragma once


// CMyFavorDlg 对话框

class CMyFavorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFavorDlg)

public:
	CMyFavorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyFavorDlg();

// 对话框数据
	enum { IDD = IDD_MYFAVOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
