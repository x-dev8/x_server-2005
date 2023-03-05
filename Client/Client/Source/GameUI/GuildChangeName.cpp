/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildChangeName.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildChangeName.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "GuildBaseInfo.h"
#include "PlayerRole.h"
#include "Create.h"
#include "GameMain.h"
CUI_ID_FRAME_GuildChangeName s_CUI_ID_FRAME_GuildChangeName;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildChangeName, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildChangeName, OnFrameRender )

MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GuildChangeName, ID_EDIT_GuilldNameOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildChangeName, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildChangeName, ID_BUTTON_CanelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildChangeName, ID_BUTTON_CloseOnButtonClick )
CUI_ID_FRAME_GuildChangeName::CUI_ID_FRAME_GuildChangeName()
{
	// Member
	m_pID_FRAME_GuildChangeName = NULL;
	m_pID_EDIT_GuilldName = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Canel = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_TEXT_Info = NULL;

}
CUI_ID_FRAME_GuildChangeName::~CUI_ID_FRAME_GuildChangeName()
{
}
// Frame
bool CUI_ID_FRAME_GuildChangeName::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildChangeName::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_GuildChangeName::ID_EDIT_GuilldNameOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_GuildChangeName::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	//确定改名
	s_CUI_ID_FRAME_GuildBaseInfo.ChangeGuildName(m_pID_EDIT_GuilldName->GetText());
	return true;
}
// Button
bool CUI_ID_FRAME_GuildChangeName::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	m_pID_EDIT_GuilldName->SetText("");
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildChangeName::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	m_pID_EDIT_GuilldName->SetText("");
	SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildChangeName::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildChangeName.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildChangeName.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildChangeName::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildChangeName, s_CUI_ID_FRAME_GuildChangeNameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildChangeName, s_CUI_ID_FRAME_GuildChangeNameOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_GuildChangeName, ID_EDIT_GuilldName, s_CUI_ID_FRAME_GuildChangeNameID_EDIT_GuilldNameOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GuildChangeName, ID_BUTTON_OK, s_CUI_ID_FRAME_GuildChangeNameID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildChangeName, ID_BUTTON_Canel, s_CUI_ID_FRAME_GuildChangeNameID_BUTTON_CanelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildChangeName, ID_BUTTON_Close, s_CUI_ID_FRAME_GuildChangeNameID_BUTTON_CloseOnButtonClick );

	m_pID_FRAME_GuildChangeName = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildChangeName );
	m_pID_EDIT_GuilldName = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GuildChangeName, ID_EDIT_GuilldName );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildChangeName, ID_BUTTON_OK );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildChangeName, ID_BUTTON_Canel );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildChangeName, ID_BUTTON_Close );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildChangeName, ID_TEXT_Info );
	assert( m_pID_FRAME_GuildChangeName );
	assert( m_pID_EDIT_GuilldName );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_TEXT_Info );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildChangeName::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\GuildChangeName.meui" );
}
// 是否可视
bool CUI_ID_FRAME_GuildChangeName::_IsVisable()
{
	return m_pID_FRAME_GuildChangeName->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildChangeName::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		if(!thePlayerRole.GetGangMgr() || thePlayerRole.GetGangMgr()->GetGuildMasterID() != thePlayerRole.GetDBID())
		{
			//提示玩家 非公会会长不可以修改名称
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString( eText_GuildChangeName_NotMaster ) );
			return;
		}
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );		
	}
	else
	{
		m_pID_EDIT_GuilldName->SetText("");
		ImmAssociateContext( g_hWnd, NULL );
	}
	m_pID_FRAME_GuildChangeName->SetVisable( bVisable );
}
