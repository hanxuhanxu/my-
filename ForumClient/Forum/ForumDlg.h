
// ForumDlg.h : 头文件
//

#pragma once
#include"IMediator.h"
#include"Md5Encode.h"
#include"resource.h"
#include"HallDlg.h"

// CForumDlg 对话框
class CForumDlg : public CDialogEx
{
// 构造
public:
	CForumDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FORUM_DIALOG };
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

private:
	IMediator* m_pMediator;//中介者的指针

public:	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnLineMsg(WPARAM,LPARAM);
	afx_msg LRESULT OnTestMsg(WPARAM,LPARAM);
	
public:
	CString m_UserName;
	CString m_Password;
	CString m_myname;
	CHallDlg * m_pHallDlg;

public:
	IMediator* GetMediator()
	{
		return m_pMediator;
	}
};
