/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\PassWordCard.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PassWordCard.h"
#include "MessageDefine.h"
#include "MessageBox.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "Login.h"
CUI_ID_FRAME_PassWordCard s_CUI_ID_FRAME_PassWordCard;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PassWordCard, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PassWordCard, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PassWordCard, ID_EDIT_InfoAOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PassWordCard, ID_EDIT_InfoCOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_PassWordCard, ID_EDIT_InfoBOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PassWordCard, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PassWordCard, ID_BUTTON_CanelOnButtonClick )
CUI_ID_FRAME_PassWordCard::CUI_ID_FRAME_PassWordCard()
{
	// Member
	m_pID_FRAME_PassWordCard = NULL;
	m_pID_TEXT_PwdA = NULL;
	m_pID_TEXT_PwdC = NULL;
	m_pID_TEXT_PwdB = NULL;
	m_pID_EDIT_InfoA = NULL;
	m_pID_EDIT_InfoC = NULL;
	m_pID_EDIT_InfoB = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_TEXT_Time = NULL;
	m_LogTime = 0;
}
// Frame
bool CUI_ID_FRAME_PassWordCard::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PassWordCard::OnFrameRender()
{
	if(IsVisable() && m_LogTime != 0)
	{
		int Sec = (m_LogTime - HQ_TimeGetTime())/1000;
		if(Sec <= 0)
		{
			ID_BUTTON_CanelOnButtonClick(NULL);
			return true;
		}
		else
		{
			m_pID_TEXT_Time->SetText(Sec);
		}
	}
	return true;
}
// Edit
void CUI_ID_FRAME_PassWordCard::ID_EDIT_InfoAOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_PassWordCard::ID_EDIT_InfoCOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_PassWordCard::ID_EDIT_InfoBOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_PassWordCard::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	//发送命令道服务器端去 通知准备开始处理
	MsgPassWordCardAck msg;
	strcpy_s(msg.A,PwdCardLength,m_pID_EDIT_InfoA->GetText());
	strcpy_s(msg.B,PwdCardLength,m_pID_EDIT_InfoB->GetText());
	strcpy_s(msg.C,PwdCardLength,m_pID_EDIT_InfoC->GetText());
	GettheNetworkInput().SendMsg(&msg);
	SetVisable(false);
	s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eLogin_PassWordCard), "", CUI_ID_FRAME_MessageBox::eTypeNothing, true);
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(60, false);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
	m_LogTime = 0;
	return true;
}
bool CUI_ID_FRAME_PassWordCard::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	MsgPassWordCardCanel msg;
	GettheNetworkInput().SendMsg(&msg);
	SetVisable(false);
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(0);
	s_CUI_ID_FRAME_MessageBox.SetVisable(false);
	m_LogTime = 0;
	s_CUI_ID_FRAME_LOGIN.CancelLoginQueue(1,NULL);
	return true;
}
// 装载UI
bool CUI_ID_FRAME_PassWordCard::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PassWordCard.MEUI",true,UI_Render_LayerFour);//最上面
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PassWordCard.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PassWordCard::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PassWordCard, s_CUI_ID_FRAME_PassWordCardOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PassWordCard, s_CUI_ID_FRAME_PassWordCardOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_PassWordCard, ID_EDIT_InfoA, s_CUI_ID_FRAME_PassWordCardID_EDIT_InfoAOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_PassWordCard, ID_EDIT_InfoC, s_CUI_ID_FRAME_PassWordCardID_EDIT_InfoCOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_PassWordCard, ID_EDIT_InfoB, s_CUI_ID_FRAME_PassWordCardID_EDIT_InfoBOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_PassWordCard, ID_BUTTON_OK, s_CUI_ID_FRAME_PassWordCardID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_PassWordCard, ID_BUTTON_Canel, s_CUI_ID_FRAME_PassWordCardID_BUTTON_CanelOnButtonClick );

	m_pID_FRAME_PassWordCard = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PassWordCard );
	m_pID_TEXT_PwdA = (ControlText*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_TEXT_PwdA );
	m_pID_TEXT_PwdC = (ControlText*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_TEXT_PwdC );
	m_pID_TEXT_PwdB = (ControlText*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_TEXT_PwdB );
	m_pID_EDIT_InfoA = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_EDIT_InfoA );
	m_pID_EDIT_InfoC = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_EDIT_InfoC );
	m_pID_EDIT_InfoB = (ControlEdit*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_EDIT_InfoB );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_BUTTON_OK );
	m_pID_TEXT_OnlyID = (ControlText*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_TEXT_OnlyID );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_BUTTON_Canel );
	m_pID_TEXT_Time= (ControlText*)theUiManager.FindControl( ID_FRAME_PassWordCard, ID_TEXT_Time );
	
	assert( m_pID_FRAME_PassWordCard );
	assert( m_pID_TEXT_PwdA );
	assert( m_pID_TEXT_PwdC );
	assert( m_pID_TEXT_PwdB );
	assert( m_pID_EDIT_InfoA );
	assert( m_pID_EDIT_InfoC );
	assert( m_pID_EDIT_InfoB );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_TEXT_OnlyID );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_TEXT_Time );

	m_pID_EDIT_InfoA->SetMaxLength(3);
	m_pID_EDIT_InfoB->SetMaxLength(3);
	m_pID_EDIT_InfoC->SetMaxLength(3);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PassWordCard::_UnLoadUI()
{
	m_pID_FRAME_PassWordCard = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PassWordCard.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PassWordCard::_IsVisable()
{
	return m_pID_FRAME_PassWordCard->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PassWordCard::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_PassWordCard->SetVisable( bVisable );
}
void CUI_ID_FRAME_PassWordCard::SetShow(const char* A,const char* B,const char* C,const char* OnlyID)
{
	SetVisable(true);
	if(!m_pID_FRAME_PassWordCard)
		return;
	m_pID_TEXT_PwdA->SetText(A);
	m_pID_TEXT_PwdB->SetText(B);
	m_pID_TEXT_PwdC->SetText(C);
	m_pID_EDIT_InfoA->SetText("");
	m_pID_EDIT_InfoC->SetText("");
	m_pID_EDIT_InfoB->SetText("");
	m_pID_TEXT_Time->SetText(30);
	char OnlyStr[PwdCardSerialLength];
	strcpy_s(OnlyStr,PwdCardSerialLength,OnlyID);
	for(int i =4;i<strlen(OnlyStr)-4;++i)
		OnlyStr[i]='*';
	m_pID_TEXT_OnlyID->SetText(OnlyStr);
	//设置当前UI进行独占
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(0);
	s_CUI_ID_FRAME_MessageBox.SetVisable(false);
	m_LogTime = HQ_TimeGetTime() + 30000;
}