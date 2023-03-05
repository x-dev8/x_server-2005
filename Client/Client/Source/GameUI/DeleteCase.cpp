/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\DeleteCase.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "DeleteCase.h"
#include "Select.h"
#include "NetworkInput.h"
#include "Common.h"
#include "DumpInfo.h"
#include "GameMain.h"
#include "jwsmtp/jwsmtp.h"

CUI_ID_FRAME_DeleteCase s_CUI_ID_FRAME_DeleteCase;
MAP_FRAME_RUN( s_CUI_ID_FRAME_DeleteCase, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_DeleteCase, OnFrameRender )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_BUTTON_ResetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_BUTTON_DeleteOnButtonClick )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_CHECKBOX_Reason0OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_CHECKBOX_Reason1OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_CHECKBOX_Reason2OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_CHECKBOX_Reason3OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_CHECKBOX_Reason4OnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_DeleteCase, ID_EDIT_Reason0OnEditEnter )
CUI_ID_FRAME_DeleteCase::CUI_ID_FRAME_DeleteCase()
{
	// Member
	m_pID_FRAME_DeleteCase = NULL;
//	m_pID_PICTURE_BackGround = NULL;
	m_pID_TEXT_Title = NULL;
//	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_BUTTON_Delete = NULL;
// 	m_pID_CHECKBOX_Reason0 = NULL;
// 	m_pID_CHECKBOX_Reason1 = NULL;
// 	m_pID_CHECKBOX_Reason2 = NULL;
// 	m_pID_CHECKBOX_Reason3 = NULL;
// 	m_pID_CHECKBOX_Reason4 = NULL;
// 	m_pID_EDIT_Reason0 = NULL;
// 	m_pID_TEXT_Reason1 = NULL;
// 	m_pID_TEXT_Reason2 = NULL;
// 	m_pID_TEXT_Reason3 = NULL;
// 	m_pID_TEXT_Reason4 = NULL;
// 	m_pID_TEXT_Reason5 = NULL;

}
// Frame
bool CUI_ID_FRAME_DeleteCase::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_DeleteCase::OnFrameRender()
{
// 	if(	m_pID_CHECKBOX_Reason0->IsChecked()||
// 		m_pID_CHECKBOX_Reason1->IsChecked()||
// 		m_pID_CHECKBOX_Reason2->IsChecked()||
// 		m_pID_CHECKBOX_Reason3->IsChecked()||
// 		m_pID_CHECKBOX_Reason4->IsChecked())
// 	{
// 		m_pID_BUTTON_Delete->SetEnable(true);
// 	}
// 	else
	{
		//m_pID_BUTTON_Delete->SetEnable(false);
	}

// 	string text = m_pID_EDIT_Reason0->GetText();
// 	if(m_pID_CHECKBOX_Reason0->IsChecked()
// 		&&text=="")
// 	{
// 		m_pID_BUTTON_Delete->SetEnable(false);
// 	}
// 
// 	if(m_pID_CHECKBOX_Reason0->IsChecked())
// 	{
// 		m_pID_EDIT_Reason0->SetReadOnly(false);
// 	}
// 	else
// 	{
// 		m_pID_EDIT_Reason0->SetReadOnly(true);
// 	}

	return true;
}
// Button
// bool CUI_ID_FRAME_DeleteCase::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	SetVisable(false);
// 	return true;
// }
// Button
bool CUI_ID_FRAME_DeleteCase::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_DeleteCase::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	int nIndex = s_CUI_ID_FRAME_Select.GetCurSelIndex();
	if ( nIndex >= 0 && nIndex < MAX_PLAYER_COUNT )
	{
		if(!s_CUI_ID_FRAME_Select.GetDel(nIndex)/*m_bIsDel[*pnIndex]*/)
		{
			MsgDeleteChar msg;
			msg.stWhichSlot = s_CUI_ID_FRAME_Select.GetSlotByIndex(nIndex);
			GettheNetworkInput().SendMsg( &msg,msg.GetLength() );

			SetVisable(false);

			WriteBack();

	// 				m_pID_CHECKBOX_Reason0->SetCheck(false);
	// 				m_pID_CHECKBOX_Reason1->SetCheck(false);
	// 				m_pID_CHECKBOX_Reason2->SetCheck(false);
	// 				m_pID_CHECKBOX_Reason3->SetCheck(false);
	// 				m_pID_CHECKBOX_Reason4->SetCheck(false);
	// 
	// 				*m_pID_EDIT_Reason0 = "";
		}
	}
	
	return true;
}
// CheckBox
// void CUI_ID_FRAME_DeleteCase::ID_CHECKBOX_Reason0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// }
// // CheckBox
// void CUI_ID_FRAME_DeleteCase::ID_CHECKBOX_Reason1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// }
// // CheckBox
// void CUI_ID_FRAME_DeleteCase::ID_CHECKBOX_Reason2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// }
// // CheckBox
// void CUI_ID_FRAME_DeleteCase::ID_CHECKBOX_Reason3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// }
// // CheckBox
// void CUI_ID_FRAME_DeleteCase::ID_CHECKBOX_Reason4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// }
// Edit
void CUI_ID_FRAME_DeleteCase::ID_EDIT_Reason0OnEditEnter( ControlObject* pSender, const char* szData )
{
}

// 装载UI
bool CUI_ID_FRAME_DeleteCase::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\DeleteCase.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\DeleteCase.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_DeleteCase::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_DeleteCase, s_CUI_ID_FRAME_DeleteCaseOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_DeleteCase, s_CUI_ID_FRAME_DeleteCaseOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_DeleteCase, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_DeleteCaseID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DeleteCase, ID_BUTTON_Reset, s_CUI_ID_FRAME_DeleteCaseID_BUTTON_ResetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_DeleteCase, ID_BUTTON_Delete, s_CUI_ID_FRAME_DeleteCaseID_BUTTON_DeleteOnButtonClick );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason0, s_CUI_ID_FRAME_DeleteCaseID_CHECKBOX_Reason0OnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason1, s_CUI_ID_FRAME_DeleteCaseID_CHECKBOX_Reason1OnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason2, s_CUI_ID_FRAME_DeleteCaseID_CHECKBOX_Reason2OnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason3, s_CUI_ID_FRAME_DeleteCaseID_CHECKBOX_Reason3OnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason4, s_CUI_ID_FRAME_DeleteCaseID_CHECKBOX_Reason4OnCheckBoxCheck );
	theUiManager.OnEditEnter( ID_FRAME_DeleteCase, ID_EDIT_Reason0, s_CUI_ID_FRAME_DeleteCaseID_EDIT_Reason0OnEditEnter );

	m_pID_FRAME_DeleteCase = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_DeleteCase );
	//m_pID_PICTURE_BackGround = (ControlPicture*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_PICTURE_BackGround );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Title );
	//m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_BUTTON_Reset );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_BUTTON_Delete );
// 	m_pID_CHECKBOX_Reason0 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason0 );
// 	m_pID_CHECKBOX_Reason1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason1 );
// 	m_pID_CHECKBOX_Reason2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason2 );
// 	m_pID_CHECKBOX_Reason3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason3 );
// 	m_pID_CHECKBOX_Reason4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_CHECKBOX_Reason4 );
// 	m_pID_EDIT_Reason0 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_EDIT_Reason0 );
// 	m_pID_TEXT_Reason1 = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Reason1 );
// 	m_pID_TEXT_Reason2 = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Reason2 );
// 	m_pID_TEXT_Reason3 = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Reason3 );
// 	m_pID_TEXT_Reason4 = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Reason4 );
// 	m_pID_TEXT_Reason5 = (ControlText*)theUiManager.FindControl( ID_FRAME_DeleteCase, ID_TEXT_Reason5 );
	assert( m_pID_FRAME_DeleteCase );
	//assert( m_pID_PICTURE_BackGround );
	assert( m_pID_TEXT_Title );
	//assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Reset );
	assert( m_pID_BUTTON_Delete );
// 	assert( m_pID_CHECKBOX_Reason0 );
// 	assert( m_pID_CHECKBOX_Reason1 );
// 	assert( m_pID_CHECKBOX_Reason2 );
// 	assert( m_pID_CHECKBOX_Reason3 );
// 	assert( m_pID_CHECKBOX_Reason4 );
// 	assert( m_pID_EDIT_Reason0 );
// 	assert( m_pID_TEXT_Reason1 );
// 	assert( m_pID_TEXT_Reason2 );
// 	assert( m_pID_TEXT_Reason3 );
// 	assert( m_pID_TEXT_Reason4 );
// 	assert( m_pID_TEXT_Reason5 );

	//m_pID_EDIT_Reason0->SetForceNewLine( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_DeleteCase::_UnLoadUI()
{
	if(!m_pID_FRAME_DeleteCase)
		return false;

	m_pID_FRAME_DeleteCase = NULL;
	//m_pID_PICTURE_BackGround = NULL;
	m_pID_TEXT_Title = NULL;
	//m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_BUTTON_Delete = NULL;
// 	m_pID_CHECKBOX_Reason0 = NULL;
// 	m_pID_CHECKBOX_Reason1 = NULL;
// 	m_pID_CHECKBOX_Reason2 = NULL;
// 	m_pID_CHECKBOX_Reason3 = NULL;
// 	m_pID_CHECKBOX_Reason4 = NULL;
// 	m_pID_EDIT_Reason0 = NULL;
// 	m_pID_TEXT_Reason1 = NULL;
// 	m_pID_TEXT_Reason2 = NULL;
// 	m_pID_TEXT_Reason3 = NULL;
// 	m_pID_TEXT_Reason4 = NULL;
// 	m_pID_TEXT_Reason5 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\DeleteCase.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_DeleteCase::_IsVisable()
{
	if(!m_pID_FRAME_DeleteCase)
		return false;

	return m_pID_FRAME_DeleteCase->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_DeleteCase::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_DeleteCase)
		return;
	m_pID_FRAME_DeleteCase->SetVisable( bVisable );
}


void CUI_ID_FRAME_DeleteCase::WriteBack()
{

#ifdef _DEBUG //lyh屏蔽日志
	char filePath[512];

    SYSTEMTIME time;
    GetLocalTime(&time);

	MeSprintf(filePath,511,"Log\\WriteBack-%d_%d_%d_%d_%d.log", time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

    HANDLE hFile = ::CreateFileA( filePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL );

    if (hFile!=INVALID_HANDLE_VALUE)
    {
		DWORD num;
		string reason;
		char chr[512];

		MeSprintf(chr,511,"角色列表的角色数:%d\n",s_CUI_ID_FRAME_Select.GetTotalRole());
		reason += chr;
		MeSprintf(chr,511,"删除的角色等级:%d\n",s_CUI_ID_FRAME_Select.GetCurSelPlayerInfo().liveinfo.ustLevel);
		reason += chr;
		MeSprintf(chr,511,"删除的角色职业:%d\n",s_CUI_ID_FRAME_Select.GetCurSelPlayerInfo().aptotic.usProfession);
		reason += chr;
		MeSprintf(chr,511,"删除角色原由:");
		reason += chr;

// 		if(m_pID_CHECKBOX_Reason0->IsChecked())
// 		{
// 			MeSprintf(chr,511,"%d ",0);
// 			reason += chr;
// 		}
// 
// 		if(m_pID_CHECKBOX_Reason1->IsChecked())
// 		{
// 			MeSprintf(chr,511,"%d ",1);
// 			reason += chr;
// 		}
// 
// 		if(m_pID_CHECKBOX_Reason2->IsChecked())
// 		{
// 			MeSprintf(chr,511,"%d ",2);
// 			reason += chr;
// 		}
// 		
// 		if(m_pID_CHECKBOX_Reason3->IsChecked())
// 		{
// 			MeSprintf(chr,511,"%d ",3);
// 			reason += chr;
// 		}
// 
// 		if(m_pID_CHECKBOX_Reason4->IsChecked())
// 		{
// 			MeSprintf(chr,511,"%d ",4);
// 			reason += chr;
// 		}
// 
// 		if(m_pID_CHECKBOX_Reason0->IsChecked())
// 		{
// 			MeSprintf(chr,511,"\n%s",m_pID_EDIT_Reason0->GetText());
// 			reason += chr;
// 		}
		

		WriteFile(hFile,reason.c_str(),reason.length(),&num,NULL);

		CloseHandle(hFile);

		SendMail(filePath,"WriteBack");
    }
    else
    {
		assert(false&&"createFile error");
    }
#endif
}

void CUI_ID_FRAME_DeleteCase::SendMail(const char* pszFileName,string content)
{
	/*std::string to("chuanpeng.liu@tolez.com"); 
	std::string from("chuanpeng.liu@tolez.com"); 
	std::string smtpserver("mail.tolez.com"); 

	jwsmtp::mailer mail( to.c_str(), from.c_str(), pszFileName, content.c_str(), 
		smtpserver.c_str(), jwsmtp::mailer::SMTP_PORT, false ); 
	mail.username( "chuanpeng.liu@tolez.com" );
	mail.password( "tolez999" );

	mail.attach( pszFileName );

	mail.operator()();*/

	DumpInfo dumpinfo;

	dumpinfo.m_strContent = content;
	dumpinfo.m_strDumpFileName = pszFileName;

	dumpinfo.SaveDumpInfo();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	if( !::CreateProcess( TEXT("BugReporter.exe"),
		NULL,			  // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		)
	{
		dumpinfo.DeleteTempFile();
	}
}