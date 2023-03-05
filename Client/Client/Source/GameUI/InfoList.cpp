/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\InfoList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "InfoList.h"
#include "MapConfig.h"
#include "GameMain.h"
#include "MeTerrain/stdafx.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "CrossMapPF.h"
#include "MiniMapUI.h"

#ifndef MESSAGE_MAXNUM
#define MESSAGE_MAXNUM			200
#endif

CUI_ID_FRAME_InfoList s_CUI_ID_FRAME_InfoList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_InfoList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_InfoList, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoList, ID_BUTTON_BottomOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoList, ID_BUTTON_ClearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoList, ID_BUTTON_ShowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_InfoList, ID_BUTTON_HideOnButtonClick )

CUI_ID_FRAME_InfoList::CUI_ID_FRAME_InfoList()
{
	// Member
	m_pID_FRAME_InfoList = NULL;
	m_pID_PICTURE_BgFrame = NULL;
	m_pID_BUTTON_Bottom = NULL;
	m_pID_TEXT_Info = NULL;
    m_pID_BUTTON_Show = NULL;
    m_pID_BUTTON_Hide = NULL;
    m_pID_BUTTON_Clear = NULL;

    m_fAlpha = 0.0f;
}
// Frame
bool CUI_ID_FRAME_InfoList::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_InfoList::OnFrameRender()
{
    if( !IsVisable() )
        return true;

	if( !s_CUI_ID_FRAME_InfoList.IsUILoad() || !m_pID_TEXT_Info )
		return false;

	theMouseManager.SetCanSetCursor(true);
	POINT ptMouse;

	GetCursorPos( &ptMouse );
	ScreenToClient( g_hWnd, &ptMouse );
	int nX = (int)ptMouse.x;
	int nY = (int)ptMouse.y;
	if(m_pID_TEXT_Info->PtInObject(nX,nY,false))
	{
		if( s_CUI_ID_FRAME_InfoList.GetRealAlpha() < 0.01f )
		{
			s_CUI_ID_FRAME_InfoList.SetTempAlpha( 0.20f );
		}
		s_CUI_ID_FRAME_InfoList.VisableBtns( true );
		m_pID_TEXT_Info->Run();
	}
	else
	{
		if( s_CUI_ID_FRAME_InfoList.GetRealAlpha() < 0.01f )
		{
			s_CUI_ID_FRAME_InfoList.SetTempAlpha( s_CUI_ID_FRAME_InfoList.GetRealAlpha() );
		}
		s_CUI_ID_FRAME_InfoList.VisableBtns( false );
	}
	

    if( m_groupAll.IsVisible() && m_pID_TEXT_Info->IsScrollBarVisable() )
        m_pID_BUTTON_Bottom->SetVisable( true );
    else
        m_pID_BUTTON_Bottom->SetVisable( false );

	theMouseManager.SetCanSetCursor(false);

	return true;
}

ControlFrame* CUI_ID_FRAME_InfoList::GetFrame()
{
    return m_pID_FRAME_InfoList;
}

// Button
bool CUI_ID_FRAME_InfoList::ID_BUTTON_BottomOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_InfoList )
		return false;

	m_pID_TEXT_Info->ScrollToTheLast();
	return true;
}

// Button
bool CUI_ID_FRAME_InfoList::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
    if ( !m_pID_FRAME_InfoList )
        return false;

    m_inbreakDeq.clear();
    ClearChat();
    return true;
}

bool CUI_ID_FRAME_InfoList::ID_BUTTON_ShowOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    ShowAll( true );
    m_pID_BUTTON_Show->SetVisable( false );
    m_pID_BUTTON_Hide->SetVisable( true );
    return true;
}

bool CUI_ID_FRAME_InfoList::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    ShowAll( false );
    m_pID_BUTTON_Show->SetVisable( true );
    m_pID_BUTTON_Hide->SetVisable( false );
    return true;
}

// 装载UI
bool CUI_ID_FRAME_InfoList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\InfoList.MEUI", true ,UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\InfoList.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_InfoList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_InfoList, s_CUI_ID_FRAME_InfoListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_InfoList, s_CUI_ID_FRAME_InfoListOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_InfoList, ID_BUTTON_Bottom, s_CUI_ID_FRAME_InfoListID_BUTTON_BottomOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_InfoList, ID_BUTTON_Clear, s_CUI_ID_FRAME_InfoListID_BUTTON_ClearOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_InfoList, ID_BUTTON_Show, s_CUI_ID_FRAME_InfoListID_BUTTON_ShowOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_InfoList, ID_BUTTON_Hide, s_CUI_ID_FRAME_InfoListID_BUTTON_HideOnButtonClick );

	m_pID_FRAME_InfoList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_InfoList );
	m_pID_PICTURE_BgFrame = (ControlPicture*)theUiManager.FindControl( ID_FRAME_InfoList, ID_PICTURE_BgFrame );
	m_pID_BUTTON_Bottom = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoList, ID_BUTTON_Bottom );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_InfoList, ID_TEXT_Info );
    m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoList, ID_BUTTON_Clear );
    m_pID_BUTTON_Show = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoList, ID_BUTTON_Show );
    m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_InfoList, ID_BUTTON_Hide );

	assert( m_pID_FRAME_InfoList );
	assert( m_pID_PICTURE_BgFrame );
	assert( m_pID_BUTTON_Bottom );
	assert( m_pID_TEXT_Info );
    assert( m_pID_BUTTON_Clear );
    assert( m_pID_BUTTON_Show );
    assert( m_pID_BUTTON_Hide );

    m_pID_FRAME_InfoList->SetMouseMoveOn( CUI_ID_FRAME_InfoList::FrameMouseEnter );
    m_pID_FRAME_InfoList->SetMouseMoveLevel( CUI_ID_FRAME_InfoList::FrameMouseLeave );

    m_groupAll.Clear();
    m_groupAll.AddControl( m_pID_PICTURE_BgFrame );
    m_groupAll.AddControl( m_pID_BUTTON_Bottom );
    m_groupAll.AddControl( m_pID_TEXT_Info );
    m_groupAll.AddControl( m_pID_BUTTON_Clear );
    m_groupAll.SetVisible( true );

	m_pID_BUTTON_Show->SetVisable( false );
	m_pID_FRAME_InfoList->SetMsgHoldup( false );

    _SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_InfoList::_UnLoadUI()
{
    m_groupAll.Clear();
	m_pID_FRAME_InfoList = NULL;
	m_pID_PICTURE_BgFrame = NULL;
	m_pID_BUTTON_Bottom = NULL;
	m_pID_TEXT_Info = NULL;
    m_pID_BUTTON_Clear = NULL;
    m_pID_BUTTON_Show = NULL;
    m_pID_BUTTON_Hide = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\InfoList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_InfoList::_IsVisable()
{
	if ( !m_pID_FRAME_InfoList )
		return false;
	return m_pID_FRAME_InfoList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_InfoList::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_InfoList )
		return;
	m_pID_FRAME_InfoList->SetVisable( bVisable );
}

bool CUI_ID_FRAME_InfoList::AddNewInfo( const char* str , bool bSkippSame)
{
	if (bSkippSame)
	{
		std::deque<SOverdueInfo>::iterator it = m_inbreakDeq.begin();
		for( ; it != m_inbreakDeq.end(); ++it )
		{
			if( (*it).m_info == str )
			{
				if (HQ_TimeGetTime() - (*it).m_BornedTime < theCountryConfig.GetSkipSameOverdueInfoTime())
				{
					return false;
				}
				else
				{
					it = m_inbreakDeq.erase( it );
					break;
				}			
			}
		}
	}
	
	SOverdueInfo info;
	info.m_info = str;
	info.m_BornedTime = HQ_TimeGetTime();
	m_inbreakDeq.push_back( info );
	while( m_inbreakDeq.size() > theCountryConfig.GetBordersFightCount() )
	{
		m_inbreakDeq.pop_front();
	}
	return true;
}

// void CUI_ID_FRAME_InfoList::DeleteOverdueInfo( std::string str )
// {
// 	std::deque<SOverdueInfo>::iterator it = m_inbreakDeq.begin();
// 	for( ; it != m_inbreakDeq.end(); it++ )
// 	{
// 		if( *it == str )
// 		{
// 			it = m_inbreakDeq.erase( it );
// 			DeleteOverdueInfo( str );
// 			return;
// 		}
// 	}
// }

bool CUI_ID_FRAME_InfoList::IsLocationOverdue( std::string str )
{
	std::deque<SOverdueInfo>::iterator it = m_inbreakDeq.begin();
	for( ; it != m_inbreakDeq.end(); ++it )
	{
		if( ( *it ).m_info.find( str ) != std::string::npos )
			return false;
	}
	return true;
}

void CUI_ID_FRAME_InfoList::ResetProperties()
{
// 	m_infoDeq.clear();
	m_inbreakDeq.clear();
// 	Refresh();
}

// void CUI_ID_FRAME_InfoList::Refresh()
// {
// 	while( m_infoDeq.size() > MESSAGE_MAXNUM )
// 	{
// 		m_infoDeq.pop_front();
// 	}

// 	while( m_inbreakDeq.size() > theCountryConfig.GetBordersFightCount() )
// 	{
// 		m_inbreakDeq.pop_front();
// 	}

//     if( m_infoDeq.size() > 0 )
//         SetVisable( true );
//     else
//         SetVisable( false );

//     if ( !m_pID_FRAME_InfoList )
//         return;
// 
// 	std::string strText;
// 	std::deque<std::string>::iterator it = m_infoDeq.begin();
// 	for( ; it != m_infoDeq.end(); it++ )
// 	{
// 		if( it + 1 == m_infoDeq.end() )
// 			strText += *it;
// 		else
// 			strText += *it + "\n";
// 	}
// 
// 	m_pID_TEXT_Info->SetText( strText );
// 	if( m_pID_TEXT_Info->IsScrollBarVisable() )
// 		m_pID_BUTTON_Bottom->SetVisable( true );
// 	else
// 		m_pID_BUTTON_Bottom->SetVisable( false );
// 
// 	m_pID_TEXT_Info->ScrollToTheLast();
// }

void CUI_ID_FRAME_InfoList::Task_HyberOtherClick( ControlObject* pSender, const char* szData )
{
	// 坐标过时
	if( s_CUI_ID_FRAME_InfoList.IsLocationOverdue( std::string( szData ) ) )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Fly_Overdue ) );
		return;
	}

	// 计算坐标
	char cContent[ eMAX_TEMP_BUFF ] = {0};
	MeSprintf_s( cContent, eMAX_TEMP_BUFF - 1, "%s", szData );
	int nLength = strlen( cContent );
	for( int i = 0; i < nLength; ++i )
	{
		if( cContent[i] == '(' || cContent[i] == ',' || cContent[i] == ')' )
		{
			cContent[i] = ' ';
		}
	}
	char cMapName[ eMAX_TEMP_BUFF ] = {0};
	int mapX, mapY;
	sscanf( cContent,"%s %d %d", cMapName, &mapX, &mapY );

	CWorldBuffer* pWorldBuf = SwGlobal::GetWorld()->GetWorldBuffer();
	if( !pWorldBuf )
		return;
	short nMeCountry = -1;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe)
	{
		nMeCountry = pMe->GetRealCountry();
	}
	CWorldTile* pTile = pWorldBuf->GetTileFromTileName( cMapName ,nMeCountry);
	if( NULL == pTile )
		return;

	if( ( mapX < 0.0f ) || ( mapX > pTile->GetWidth() - 1 ) || ( mapY < 0.0f ) || ( mapY > pTile->GetDepth() - 1 ) )
		return;

	// 左右捕飞边塞
	CPlayerMgr* pPlayerMgr = theHeroGame.GetPlayerMgr();
	if( !pPlayerMgr )
		return;
	CPlayer* pPlayer = pPlayerMgr->GetMe();
	if( !pPlayer )
		return;
	unsigned short title = ( unsigned short )pPlayer->GetCountryTitle();
	if( GetCountryRightByTitle( title ) & Right_FlyToBorders )
	{
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataByName( cMapName );
		if( !pMapData )
			return;
		MsgCountryFlyToBordersReq msg;
		msg.ustMapID = pMapData->Id;
		msg.ustPosX = mapX;
		msg.ustPosY = mapY;
		GettheNetworkInput().SendMsg( &msg );
		return;
	}

	// 其他人跑路
	CWorldTile* pCurrTile = CURRENTTILE;
	assert( pCurrTile );
    if( !pCurrTile )
        return;

    if( pCurrTile->GetCountry() == nMeCountry )
	{
        std::string _strTileName = pTile->GetTileName();
        char szTemp[MAX_PATH] = {0};
        MeSprintf_s( szTemp, MAX_PATH - 1, "%s %d %d", _strTileName.c_str(), mapX, mapY );
        std::string _strFindPath = szTemp;
        CommonChatFrame::Task_HyberOtherClick( NULL, _strFindPath, 0 );
	}
	else
	{
		// 路太远,不许跑
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Tip, theXmlString.GetString( eText_Country_Fly_NoRight ) );
	}
}

// 以下为接收的服务器消息
void CUI_ID_FRAME_InfoList::GetBorderFightInfo( const MsgTellCountryBordersFight* pMsg )
{
	if( !pMsg )
		return;

	// 边境入侵
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pMsg->ustMapID );
	if( !pMapData )
		return;
	std::string strMapName = pMapData->MapName;
	int x = pMsg->ustPosX;
	int y = pMsg->ustPosY;
	char szBorderFightInfo[ eMAX_TEMP_BUFF ] = {0};
	MeSprintf_s( szBorderFightInfo, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Border_Fight ), strMapName.c_str(), x, y );

// 	m_infoDeq.push_back( std::string( szBorderFightInfo ) );
	if(AddNewInfo( ( szBorderFightInfo ) ,true))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Break, szBorderFightInfo );
	}
// 	Refresh();	
}

void CUI_ID_FRAME_InfoList::GetBorderDefendInfo( const MsgTellCountryKillEnemy* pMsg )
{
	if( !pMsg )
		return;

	// 抵御入侵
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pMsg->ustMapID );
	if( !pMapData )
		return;
	std::string strMapName = pMapData->MapName;
	char szDefend[ eMAX_TEMP_BUFF ] = {0};
	MeSprintf_s( szDefend, eMAX_TEMP_BUFF - 1, theXmlString.GetString( eText_Country_Border_Defend ), pMsg->szPlayerName, strMapName.c_str() );
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_DefineBreak, szDefend );
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Country_Break, szDefend );
// 	Refresh();
}

void CUI_ID_FRAME_InfoList::InitializeAtEnterWorld()
{
    ResetProperties();
    m_pChatInfoText = m_pID_TEXT_Info;
    m_pChatInfoBox = m_pID_FRAME_InfoList;
    
    m_pID_BUTTON_Clear->SetShowTip( true );
    m_pID_BUTTON_Clear->setTip( m_pID_BUTTON_Clear->GetData()->m_szCaption );

    InitialCommonChat();
    m_pID_BUTTON_Bottom->SetVisable( false );

    m_pID_BUTTON_Clear->SetVisable( false );

	SetVisable( /*true*/!s_CUI_ID_FRAME_MiniMap.IsHideChatListChecked() );
    SetRealAlpha( m_fAlpha );
    VisableBtns( false );
}

void CUI_ID_FRAME_InfoList::ClearChat()
{
	CUI_ChatInfoBox::ClearChat();
	ResetProperties();
}

void CUI_ID_FRAME_InfoList::_AddInfo( const std::string& str, const D3DCOLOR col, const UINT nType, char *szToName, 
             char* itemData, int cntHyber, int nBagType, bool bAutoReply )
{
    CUI_ChatInfoBox::AddInfo( str, col, nType, szToName, itemData, cntHyber, nBagType, bAutoReply );
}

void CUI_ID_FRAME_InfoList::AddInfo( const std::string& str, const D3DCOLOR col, const UINT nType, char *szToName, 
                                    char* itemData, int cntHyber, int nBagType, bool bAutoReply )
{
    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldList_Info, str, szToName, itemData, cntHyber, nBagType );
}

void CUI_ID_FRAME_InfoList::SetRealAlpha( float fAlpha )
{
    if( !IsUILoad() )
        return;

    if( m_pID_FRAME_InfoList )
    {
        fAlpha = fAlpha > 1.0f ? 1.0f : fAlpha;
        fAlpha = fAlpha < 0.0f ? 0.0f : fAlpha;
        m_fAlpha = fAlpha;
        SetTempAlpha( fAlpha );
    }
}

float CUI_ID_FRAME_InfoList::GetRealAlpha()
{
    return m_fAlpha;
}

void CUI_ID_FRAME_InfoList::SetTempAlpha( float fAlpha )
{
    if( !IsUILoad() )
        return;

    if( m_pID_FRAME_InfoList )
    {
        fAlpha = fAlpha > 1.0f ? 1.0f : fAlpha;
        fAlpha = fAlpha < 0.0f ? 0.0f : fAlpha;
        m_pID_PICTURE_BgFrame->SetAlpha( fAlpha );
    }
}

void CUI_ID_FRAME_InfoList::ShowAll( bool bShow )
{
    if( !IsUILoad() )
        return;

    m_groupAll.SetVisible( bShow );
    if( bShow )
    {
       // m_pID_FRAME_InfoList->SetMsgHoldup( true );
        if( m_pID_TEXT_Info->IsScrollBarVisable() )
            m_pID_BUTTON_Bottom->SetVisable( true );
        else
            m_pID_BUTTON_Bottom->SetVisable( false );
        SetTempAlpha( m_fAlpha );
    }
    else
    {
        m_pID_FRAME_InfoList->SetMsgHoldup( false );
        m_pID_BUTTON_Bottom->SetVisable( false );
        SetTempAlpha( 0.0f );
    }
}

void CUI_ID_FRAME_InfoList::FrameMouseEnter( ControlObject* pSender )
{
   
}

void CUI_ID_FRAME_InfoList::FrameMouseLeave( ControlObject* pSender )
{
//     if( !s_CUI_ID_FRAME_InfoList.IsUILoad() )
//         return;
// 
//     if( s_CUI_ID_FRAME_InfoList.GetRealAlpha() < 0.01f )
//     {
//         s_CUI_ID_FRAME_InfoList.SetTempAlpha( s_CUI_ID_FRAME_InfoList.GetRealAlpha() );
//     }
//     s_CUI_ID_FRAME_InfoList.VisableBtns( false );
}

void CUI_ID_FRAME_InfoList::VisableBtns( bool bVisable )
{
    if( !IsUILoad() )
        return;

    m_pID_BUTTON_Clear->SetVisable( bVisable );
}
