#include "stdafx.h"
#include "ApplicationManager.h"
#include "ApplicationInfoPage.h"
#include "ProcessManager.h"


// CApplicationInfoPage dialog

IMPLEMENT_DYNAMIC(CApplicationInfoPage, CDialog)

CApplicationInfoPage::CApplicationInfoPage(CWnd* pParent /*=NULL*/)
	: CDialog(CApplicationInfoPage::IDD, pParent)
{
    _bRunning = false;
}

CApplicationInfoPage::~CApplicationInfoPage()
{
    ProcessManager::Instance().TerminateProcess( _strApplicationPath );
}

void CApplicationInfoPage::SetApplicationPath( const std::string& strPath )
{
    GetDlgItem(IDC_EDIT_APPLICATIONNAME)->SetWindowText( strPath.c_str());
    _strApplicationPath = strPath;
}

#define MAX_LISTITEM_COUNT 29
int CApplicationInfoPage::HandleMessage( unsigned long ulMessageId, const std::string& strContent )
{
    if ( strContent.empty())
        return 0;

    ulMessageId = 0;

    int nCount = _listCtrl->GetCount();
    if ( nCount >= MAX_LISTITEM_COUNT)
    {
        _listCtrl->DeleteString(0);
    }
    _listCtrl->AddString( strContent.c_str());
    return 0;
}

void CApplicationInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);    
}


BEGIN_MESSAGE_MAP(CApplicationInfoPage, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_START, &CApplicationInfoPage::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CApplicationInfoPage message handlers
BOOL CApplicationInfoPage::OnInitDialog()
{
    CDialog::OnInitDialog();

    _buttonStart = (CButton*)GetDlgItem( IDC_BUTTON_START );

    _listCtrl = (CListBox*)GetDlgItem(IDC_LIST_OUTPUT);
    return TRUE;
}

void CApplicationInfoPage::OnCancel()
{

}

void CApplicationInfoPage::OnBnClickedButtonStart()
{
    if ( _bRunning )
    {
        //ProcessManager::Instance().TerminateProcess( _strApplicationPath );
        _buttonStart->SetWindowText( "&Start" );
        _bRunning = false;
    }
    else
    {
        if ( RESULT_FAIL(ProcessManager::Instance().AddProtectedProcess( _strApplicationPath, _strConfigPath )) )
        {
            MessageBox( "AddProtectedProcess Fail.", "Application Manager", MB_OK | MB_ICONERROR );
        }
        else
        {
            _buttonStart->SetWindowText( "&Running" );
            _bRunning = true;
        }
    }
}
