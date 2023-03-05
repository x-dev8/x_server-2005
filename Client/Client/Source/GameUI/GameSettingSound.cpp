/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\GAME\GameSettingSound.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSetting.h"
#include "GameSettingSound.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingSound s_CUI_ID_FRAME_GameSettingSound;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingSound, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingSound, OnFrameRender )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingSound, ID_SCROLLBAREX_yinyueOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingSound, ID_SCROLLBAREX_huanjingOnScrollBarExUpdatePos )
CUI_ID_FRAME_GameSettingSound::CUI_ID_FRAME_GameSettingSound()
{
	// Member
	m_pID_FRAME_GameSettingSound = NULL;
	m_pID_TEXT_yinyue = NULL;
	m_pID_TEXT_huanjing = NULL;
	m_pID_SCROLLBAREX_yinyue = NULL;
	m_pID_SCROLLBAREX_huanjing = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingSound::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingSound::OnFrameRender()
{
	return true;
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingSound::ID_SCROLLBAREX_yinyueOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUND, n );
	GameSetting::Instance()->CommitChanges();
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingSound::ID_SCROLLBAREX_huanjingOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUNDEFFECT, n );
	GameSetting::Instance()->CommitChanges();
}

// 装载UI
bool CUI_ID_FRAME_GameSettingSound::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingSound.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingSound.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingSound::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingSound, s_CUI_ID_FRAME_GameSettingSoundOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingSound, s_CUI_ID_FRAME_GameSettingSoundOnFrameRender );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingSound, ID_SCROLLBAREX_yinyue, s_CUI_ID_FRAME_GameSettingSoundID_SCROLLBAREX_yinyueOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingSound, ID_SCROLLBAREX_huanjing, s_CUI_ID_FRAME_GameSettingSoundID_SCROLLBAREX_huanjingOnScrollBarExUpdatePos );

	m_pID_FRAME_GameSettingSound = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingSound );
	m_pID_TEXT_yinyue = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSound, ID_TEXT_yinyue );
	m_pID_TEXT_huanjing = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSound, ID_TEXT_huanjing );
	m_pID_SCROLLBAREX_yinyue = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingSound, ID_SCROLLBAREX_yinyue );
	m_pID_SCROLLBAREX_huanjing = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingSound, ID_SCROLLBAREX_huanjing );
	assert( m_pID_FRAME_GameSettingSound );
	assert( m_pID_TEXT_yinyue );
	assert( m_pID_TEXT_huanjing );
	assert( m_pID_SCROLLBAREX_yinyue );
	assert( m_pID_SCROLLBAREX_huanjing );
	m_pID_FRAME_GameSettingSound->SetMsgHoldup( false );
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingSound::_UnLoadUI()
{
	m_pID_FRAME_GameSettingSound = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingSound.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingSound::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingSound )
		return false;
	return m_pID_FRAME_GameSettingSound->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingSound::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingSound ) 
		return;
	m_pID_FRAME_GameSettingSound->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}

void CUI_ID_FRAME_GameSettingSound::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingSound)
        return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{	
		case GameSetting::eGSC_SOUND:
			m_pID_SCROLLBAREX_yinyue->SetValue( nValue );
			break;		
		case GameSetting::eGSC_SOUNDEFFECT:
			m_pID_SCROLLBAREX_huanjing->SetValue( nValue );
			break;

		default:
			break;
		}
	}
}