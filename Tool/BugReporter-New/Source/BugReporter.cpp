// BugReporter.cpp : implementation file
//

#include "stdafx.h"
#include "BugReporter-New.h"
#include "BugReporter.h"
#include "DumpInfo.h"
#include "Jwsmtp/jwsmtp.h"

//declare
void SendDumpMail(DumpInfo& dumpinfo);

// BugReporter dialog

IMPLEMENT_DYNAMIC(CBugReporter, CDialog)

CBugReporter::CBugReporter(CWnd* pParent /*=NULL*/)
	: CDialog(CBugReporter::IDD, pParent)
{

}

CBugReporter::~CBugReporter()
{
}

void CBugReporter::CheckOptions( DumpInfo& dumpinfo )
{
	dumpinfo.m_strContent += "\n玩家选择了下列选项：";

	char str[256] = {0};
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CK_OPTION1 ) )
	{
		GetDlgItem(IDC_CK_OPTION1)->GetWindowText( str, 256 );
		dumpinfo.m_strContent += str;
		dumpinfo.m_strContent += "，";
	}

	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CK_OPTION2 ) )
	{
		GetDlgItem(IDC_CK_OPTION2)->GetWindowText( str, 256 );
		dumpinfo.m_strContent += str;
		dumpinfo.m_strContent += "，";
	}

	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CK_OPTION3 ) )
	{
		GetDlgItem(IDC_CK_OPTION3)->GetWindowText( str, 256 );
		dumpinfo.m_strContent += str;
		dumpinfo.m_strContent += "，";
	}

	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CK_OPTION4 ) )
	{
		GetDlgItem(IDC_CK_OPTION4)->GetWindowText( str, 256 );
		dumpinfo.m_strContent += str;
		dumpinfo.m_strContent += "，";
	}

	if ( BST_CHECKED == IsDlgButtonChecked( IDC_CK_OPTION5 ) )
	{
		GetDlgItem(IDC_CK_OPTION5)->GetWindowText( str, 256 );
		dumpinfo.m_strContent += str;
		dumpinfo.m_strContent += "，";
	}
}

void CBugReporter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, m_strText);
}

BEGIN_MESSAGE_MAP(CBugReporter, CDialog)
	ON_BN_CLICKED(IDOK, &CBugReporter::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBugReporter::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CBugReporter::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, FALSE);

	(CWnd*)GetDlgItem(IDC_EDIT)->SetFocus();
	return FALSE;
}

// BugReporter message handlers
void CBugReporter::OnBnClickedOk()
{
	OnOK();
	DumpInfo dumpinfo;
 	if( !dumpinfo.CheckDumpTempFile() )
 		return;

	if( !dumpinfo.LoadDumpInfo() )
		return ;
	
	CheckOptions(dumpinfo);
	
	dumpinfo.m_strContent += "\n玩家反馈：";
	dumpinfo.m_strContent += m_strText.GetString();
	SendDumpMail(dumpinfo);
}

//-----------------------------------------------------------------------------------
void SendDumpMail(DumpInfo& dumpinfo)
{
	/*if( !dumpinfo.CheckDumpTempFile() )
		return;

	if( !dumpinfo.LoadDumpInfo() )
		return ;*/

	std::string to("nextdump@wushen.com"); 
	std::string from("nextdump@wushen.com"); 
	std::string smtpserver("mail.wushen.com"); 

	jwsmtp::mailer mail( to.c_str(), from.c_str(), dumpinfo.m_strDumpFileName.c_str(), dumpinfo.m_strContent.c_str(), 
		smtpserver.c_str(), jwsmtp::mailer::SMTP_PORT, false ); 
	mail.username( "nextdump@wushen.com" );
	mail.password( "wushen999" );

	mail.attach( dumpinfo.m_strDumpFileName.c_str() ); 	
	mail.attach( dumpinfo.m_strCustomSystemSettingFile.c_str() );		
	mail.attach( dumpinfo.m_strCustomGameSettingFile.c_str() );

	mail.operator()();

	dumpinfo.DeleteTempFile();
}

void CBugReporter::OnBnClickedCancel()
{
	OnCancel();
	DumpInfo dumpinfo;
	if( !dumpinfo.CheckDumpTempFile() )
		return;

	if( !dumpinfo.LoadDumpInfo() )
		return ;

	CheckOptions(dumpinfo);

	dumpinfo.m_strContent += "\n玩家反馈：";
	dumpinfo.m_strContent += m_strText.GetString();
	SendDumpMail(dumpinfo);
}

void CBugReporter::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnBnClickedOk();

	CDialog::OnClose();
}
