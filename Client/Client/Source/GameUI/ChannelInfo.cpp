/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\ChannelInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChannelInfo.h"
#include "SelectChannel.h"
#include "PlayerRole.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "GlobalDef.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_ChannelInfo s_CUI_ID_FRAME_ChannelInfo;

MAP_FRAME_RUN( s_CUI_ID_FRAME_ChannelInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChannelInfo, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChannelInfo, ID_BUTTON_ChangeOnButtonClick )
CUI_ID_FRAME_ChannelInfo::CUI_ID_FRAME_ChannelInfo()
{
	// Member
	m_pID_FRAME_ChannelInfo = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_BUTTON_Change = NULL;

}
CUI_ID_FRAME_ChannelInfo::~CUI_ID_FRAME_ChannelInfo()
{
}
// Frame
bool CUI_ID_FRAME_ChannelInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChannelInfo::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ChannelInfo::ID_BUTTON_ChangeOnButtonClick( ControlObject* pSender )
{
	if ( thePlayerRole.IsDie() )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_eChangeChannelRet_Dead), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
		return true;
	}

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		if ( theHeroGame.GetPlayerMgr()->GetMe()->HasFightFlag(eFighting) )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_eChangeChannelRet_Fight), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			return true;
		}
	}

	s_CUI_ID_FRAME_SelectChannel.SetChannelInfoOpen( true );
	s_CUI_ID_FRAME_SelectChannel.SetVisable( true );

	return true;
}

// 装载UI
bool CUI_ID_FRAME_ChannelInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChannelInfo.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChannelInfo.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ChannelInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChannelInfo, s_CUI_ID_FRAME_ChannelInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChannelInfo, s_CUI_ID_FRAME_ChannelInfoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChannelInfo, ID_BUTTON_Change, s_CUI_ID_FRAME_ChannelInfoID_BUTTON_ChangeOnButtonClick );

	m_pID_FRAME_ChannelInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChannelInfo );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_ChannelInfo, ID_TEXT_Name );
	m_pID_BUTTON_Change = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChannelInfo, ID_BUTTON_Change );
	assert( m_pID_FRAME_ChannelInfo );
	assert( m_pID_TEXT_Name );
	assert( m_pID_BUTTON_Change );

	m_pID_FRAME_ChannelInfo->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChannelInfo::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\ChannelInfo.meui" );
}
// 是否可视
bool CUI_ID_FRAME_ChannelInfo::_IsVisable()
{
	return m_pID_FRAME_ChannelInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ChannelInfo::_SetVisable( const bool bVisable )
{
	if ( bVisable )
	{
		ShowChannelName();
	}
	m_pID_FRAME_ChannelInfo->SetVisable( bVisable );
}

void CUI_ID_FRAME_ChannelInfo::InitializeAtEnterWorld()
{
	if ( s_CUI_ID_FRAME_SelectChannel.GetLastChannelIndex() == -1 )
	{
		SetVisable( false );
		return;
	}

	std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();
	if ( str.length() <= 0 )
	{
		SetVisable( false );
		return;
	}
	
	
	SetVisable( true );
}

void CUI_ID_FRAME_ChannelInfo::ShowChannelName()
{
	if ( !m_pID_TEXT_Name )
		return;

	m_pID_TEXT_Name->SetText("");

	std::string str = s_CUI_ID_FRAME_SelectChannel.GetChannelName();

	m_pID_TEXT_Name->SetText( str );
}