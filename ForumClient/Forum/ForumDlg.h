
// ForumDlg.h : ͷ�ļ�
//

#pragma once
#include"IMediator.h"
#include"Md5Encode.h"
#include"resource.h"
#include"HallDlg.h"

// CForumDlg �Ի���
class CForumDlg : public CDialogEx
{
// ����
public:
	CForumDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FORUM_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	IMediator* m_pMediator;//�н��ߵ�ָ��

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
