#pragma once


// CMyFunsDlg 对话框

class CMyFunsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFunsDlg)

public:
	CMyFunsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyFunsDlg();

// 对话框数据
	enum { IDD = IDD_MYFUNS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
