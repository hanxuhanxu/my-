// WritePegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "WritePegDlg.h"
#include "afxdialogex.h"
#include"ForumDlg.h"
#include"afxole.h" 
#include"richole.h"
#include<fstream>

int ContentType=1;

// CWritePegDlg 对话框

IMPLEMENT_DYNAMIC(CWritePegDlg, CDialogEx)

	CWritePegDlg::CWritePegDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWritePegDlg::IDD, pParent)
{

}

CWritePegDlg::~CWritePegDlg()
{
}

void CWritePegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_MyTitle);
	DDX_Control(pDX, IDC_EDIT2, m_Content);
	DDX_Control(pDX, IDC_PROGRESS1, m_transFilePro);
}

BOOL CWritePegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


BEGIN_MESSAGE_MAP(CWritePegDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CWritePegDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CWritePegDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWritePegDlg 消息处理程序


void CWritePegDlg::OnBnClickedButton1()  //上传
{
	//打包文章包（用户名，文章题目title，文章正文body）
	STRU_ARTICLE_INFO  art ;
	art.m_nType = _DEF_PROTOCOL_HANDPEG_RQ;
	CString m_title ;
	CString m_body;
	m_Content.GetWindowText(m_body);  //文章标题
	art.ID=((CForumDlg*)GetParent())->GetMediator()->myinfo.m_userId; //上传者ID

	if(ContentType==1)  //普通上传
	{
		m_MyTitle.GetWindowText(m_title);
		WideCharToMultiByte(CP_ACP,0,m_body,-1,art.body,sizeof(art.body),0,0);
		WideCharToMultiByte(CP_ACP,0,m_title,-1,art.title,sizeof(art.title),0,0);
		
	
		((CForumDlg*)GetParent())->GetMediator()->SendDataTCP(_HOST_IP,(char *)&art,sizeof(art));
	}
	else if(ContentType==2) //上传文件
	{
		m_Content.GetWindowText(m_body); //得到文件路径
		FILE *pFile=NULL;
		USES_CONVERSION;
		std::string s(W2A(m_body));
 	    const char* path =s.c_str(); 
		fopen_s(&pFile,path,"rb");
		if(pFile == NULL)
			return;
		fseek(pFile,0,SEEK_END);
		int nFileSize = ftell(pFile);   //文件剩余大小
		art.fileLen=nFileSize;//文件实际大小
		int bytesRead = 0;  //一次读取的大小
		long fileOffset = 0;
		CString sendInfo;

		while (nFileSize > _MAX_READ_SIZE)
		{
			art.isfinished = FALSE;
			fseek(pFile,fileOffset,SEEK_SET);   //从头开始读取
			
			bytesRead = _MAX_READ_SIZE;

			fread_s(art.body/*目标缓冲区*/,_MAX_READ_SIZE,sizeof(char),_MAX_READ_SIZE,pFile);
			//发送到主窗口
			//WM_SUBTOMAIN	WM_USER+5
			art.fileOffset = fileOffset;  //偏移量
			art.transSize = bytesRead;  //一次传输大小
			((CForumDlg*)GetParent())->GetMediator()->SendDataTCP(_HOST_IP,((char *)&art),sizeof(art));
			
			sendInfo.Format(_T("文件发送进度:%d%%"), int(((double)fileOffset/art.fileLen)*100));
			m_transFilePro.SetPos(int(((double)fileOffset/art.fileLen)*100));
			GetDlgItem(IDC_SEND)->SetWindowText(sendInfo);

			fileOffset += bytesRead;
			nFileSize -= _MAX_READ_SIZE;

			Sleep(70);
		}

		fseek(pFile,fileOffset,SEEK_SET);

		if (nFileSize <= _MAX_READ_SIZE)
		{
			art.isfinished = TRUE;
			fread_s(art.body/*目标缓冲区*/,_MAX_READ_SIZE,sizeof(char),nFileSize,pFile);	
			art.fileOffset = fileOffset;
			art.transSize = bytesRead;
			((CForumDlg*)GetParent())->GetMediator()->SendDataTCP(_HOST_IP,((char *)&art),sizeof(art));
			
			sendInfo.Format(_T("文件发送进度:%d%%"), 100);
			m_transFilePro.SetPos(100);
			GetDlgItem(IDC_SEND)->SetWindowText(sendInfo);

			MessageBox(_T("文件发送完毕！"), _T("提示"));

			GetDlgItem(IDC_SEND)->ShowWindow(FALSE);
			GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
		}

		fclose(pFile);
		ContentType=1;

	}
	m_Content.Clear();
}


void CWritePegDlg::OnBnClickedButton3()             //上传附件
{
	// TODO: 在此添加控件通知处理程序代码
	ContentType=2;

	CFileDialog FileDlg(TRUE,0,0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,NULL,NULL);
	//int i=FileDlg.DoModal() ;
	if(FileDlg.DoModal() == IDOK) 
	{
		CString sname=FileDlg.GetFileName(); //得到文件名

		GetDlgItem(IDC_EDIT2)->SetWindowText(FileDlg.GetPathName());
		ShowWindow(SW_SHOW);
		UpdateData(TRUE);
	 }

}
