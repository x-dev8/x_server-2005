/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\HolyShit.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CountryBattleKillNum.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "CountryFunction.h"

CUI_ID_FRAME_HolyShit s_CUI_ID_FRAME_HolyShit;

MAP_FRAME_RUN( s_CUI_ID_FRAME_HolyShit, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_HolyShit, OnFrameRender )

CUI_ID_FRAME_HolyShit::CUI_ID_FRAME_HolyShit()
{
    ResetMembers();
}

void CUI_ID_FRAME_HolyShit::ResetMembers()
{
	m_pID_FRAME_HolyShit = NULL;
	m_pID_TEXT_Country[0] = NULL;
	m_pID_TEXT_Country[1] = NULL;
	m_pID_TEXT_Country[2] = NULL;
	m_pID_TEXT_CountryKill[0] = NULL;
	m_pID_TEXT_CountryKill[1] = NULL;
	m_pID_TEXT_CountryKill[2] = NULL;
}

// Frame
bool CUI_ID_FRAME_HolyShit::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_HolyShit::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_HolyShit::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\HolyShit.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\HolyShit.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_HolyShit::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_HolyShit, s_CUI_ID_FRAME_HolyShitOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_HolyShit, s_CUI_ID_FRAME_HolyShitOnFrameRender );

	m_pID_FRAME_HolyShit = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_HolyShit );
	m_pID_TEXT_Country[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_Country0 );
	m_pID_TEXT_Country[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_Country1 );
	m_pID_TEXT_Country[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_Country2 );
	m_pID_TEXT_CountryKill[0] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_CountryKill0 );
	m_pID_TEXT_CountryKill[1] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_CountryKill1 );
	m_pID_TEXT_CountryKill[2] = (ControlText*)theUiManager.FindControl( ID_FRAME_HolyShit, ID_TEXT_CountryKill2 );

	assert( m_pID_FRAME_HolyShit );
	assert( m_pID_TEXT_Country[0] );
	assert( m_pID_TEXT_Country[1] );
	assert( m_pID_TEXT_Country[2] );
	assert( m_pID_TEXT_CountryKill[0] );
	assert( m_pID_TEXT_CountryKill[1] );
	assert( m_pID_TEXT_CountryKill[2] );

    m_pID_FRAME_HolyShit->SetMsgHoldup( false );
    for( int i = 0; i < CountryDefine::Country_Max - 1; ++i )
    {
        m_pID_TEXT_Country[i]->SetSkipAllMsg( true );
        m_pID_TEXT_CountryKill[i]->SetSkipAllMsg( true );
    }

	SetVisable( false );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_HolyShit::_UnLoadUI()
{
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\HolyShit.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_HolyShit::_IsVisable()
{
	if ( !m_pID_FRAME_HolyShit )
		return false;
	return m_pID_FRAME_HolyShit->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_HolyShit::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_HolyShit )
		return;
	m_pID_FRAME_HolyShit->SetVisable( bVisable );
}

void CUI_ID_FRAME_HolyShit::SetCountryBattleShow( bool bShow )
{
    SetVisable( bShow );
    
    if( !IsUILoad() )
        return;

    for( int i = CountryDefine::Country_LouLan; i < CountryDefine::Country_Max; ++i )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp,sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_CountryName ),
            CountryFunction::GetCountryNameById( i ).c_str() );
        m_pID_TEXT_Country[i - 1]->SetText( szTemp );

        MeSprintf_s( szTemp,sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_KillNumber ), 0 );
        m_pID_TEXT_CountryKill[i - 1]->SetText( szTemp );
    }
}

void CUI_ID_FRAME_HolyShit::UpdateKillNumber( uint32* pArray )
{
    if( !pArray )
        return;

    if( !IsVisable() )
    {
        SetVisable( true );
    }

    if( !IsUILoad() )
        return;

    for( int i = CountryDefine::Country_LouLan; i < CountryDefine::Country_Max; ++i )
    {
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp,sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_CountryName ),
            CountryFunction::GetCountryNameById( i ).c_str() );
        m_pID_TEXT_Country[i - 1]->SetText( szTemp );

        MeSprintf_s( szTemp,sizeof( szTemp ) / sizeof( char ) - 1, theXmlString.GetString( eText_CountryBattle_KillNumber ), ( int )pArray[i] );
        m_pID_TEXT_CountryKill[i - 1]->SetText( szTemp );
    }
}
