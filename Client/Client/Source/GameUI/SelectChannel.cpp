/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SelectChannel.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelectChannel.h"
#include "GameMain.h"
#include "ExitGame.h"
#include "MessageBox.h"
#include "PlayerMgr.h"
#include "XmlStringLanguage.h"
#include "Select.h"
#include "Login.h"
#include "color_config.h"
#include "PlayerRole.h"
#include "Cfg.h"

extern bool isShowDisconnetMsg;
extern GAME_STATE g_GameState;

const ColorConfigure nChannelStatusColor[CUI_ID_FRAME_LOGIN::ES_Max] = 
{
	CC_PetColor_Green, //绿色
	CC_ItemTip_ItemBind,//黄色
	CC_OrangeName,//橙色
	CC_PetColor_Red,//红色
	CC_PetColor_Taupe,//灰色
};

const char* chChannelStatus[CUI_ID_FRAME_LOGIN::ES_Max] = 
{
	"{#66660}",
	"{#66661}",
	"{#66662}",
	"{#66663}",
	"{#66664}",
};

CUI_ID_FRAME_SelectChannel s_CUI_ID_FRAME_SelectChannel;

MAP_FRAME_RUN( s_CUI_ID_FRAME_SelectChannel, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelectChannel, OnFrameRender )

MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelectChannel, ID_LIST_NameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectChannel, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelectChannel, ID_LIST_StateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelectChannel, ID_LIST_SelectOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectChannel, ID_BUTTON_SelectRandomOnButtonClick )

CUI_ID_FRAME_SelectChannel::CUI_ID_FRAME_SelectChannel()
{
	// Member
	m_pID_FRAME_SelectChannel = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_State = NULL;
	m_pID_LIST_Select = NULL;
	m_pID_BUTTON_SelectRandom = NULL;

	dwStartTime = 0;
	dwAutoCloseTime = 0;
	m_nCurChannelIndex = -1;
	m_bSelect = false;
	m_nlastChannelIndex = -1;
	m_bChannelInfo_Open = false;

	m_vecChannelInfo.clear();
}
CUI_ID_FRAME_SelectChannel::~CUI_ID_FRAME_SelectChannel()
{
	m_vecChannelInfo.clear();
}
// Frame
bool CUI_ID_FRAME_SelectChannel::OnFrameRun()
{
	if ( !IsVisable() )
		return true;

	if ( m_bChannelInfo_Open )
		return true;

	int n = timeGetTime() - dwStartTime;
	int nTime = dwAutoCloseTime - n/1000;
	if ( nTime >= 0 )
	{
		char szInfo[32];
		sprintf_s( szInfo, sizeof( szInfo ) - 1, theXmlString.GetString(eClient_AddInfo_2slk_122), "", nTime );
		m_pID_TEXT_Time->SetText( szInfo );
	}
	else
	{
		SetVisable( false );

		if ( g_GameState == G_SELECT )
		{
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EnterGame_Error), "", 
				CUI_ID_FRAME_MessageBox::eTypeConfirm, true ,CUI_ID_FRAME_ExitGame::BackToLogin);
			s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(true);
			s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(true);

			isShowDisconnetMsg = true;
		}
		else if ( g_GameState == G_MAIN )
		{
			//s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectChannel_TimeOut), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true );
			SelectChannelRandom();
		}
		
	}
	return true;
}
bool CUI_ID_FRAME_SelectChannel::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_SelectChannel::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	
}

// List
void CUI_ID_FRAME_SelectChannel::ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_SelectChannel::ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	
}

extern bool ChangeMapServerBusy( const char bPressYesButton, void *pData );

void CUI_ID_FRAME_SelectChannel::ID_LIST_SelectOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	int nIndex = s_CUI_ID_FRAME_SelectChannel.m_pID_LIST_Select->GetCurSelIndex();
	if ( nIndex < 0 || nIndex >= s_CUI_ID_FRAME_SelectChannel.m_vecChannelInfo.size() )
		return;

	CPlayerMgr* playerMgr = theHeroGame.GetPlayerMgr();
	if ( !playerMgr )
		return;

	if ( !s_CUI_ID_FRAME_SelectChannel.m_bChannelInfo_Open )
		playerMgr->CheckChannel( &s_CUI_ID_FRAME_SelectChannel.m_vecChannelInfo[nIndex] );
	else
		playerMgr->ChangeChannel( s_CUI_ID_FRAME_SelectChannel.m_vecChannelInfo[nIndex].nServerId );

	s_CUI_ID_FRAME_SelectChannel.m_nCurChannelIndex = nIndex;
	s_CUI_ID_FRAME_SelectChannel.m_nlastChannelIndex = nIndex;

	if ( g_GameState == G_MAIN )
		s_CUI_ID_FRAME_SelectChannel.m_bSelect = true;

	s_CUI_ID_FRAME_SelectChannel.SetVisable( false );

	if ( g_GameState == G_SELECT )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_WaitEnterWorld), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, EnterWorldFailed);
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(30, false);

		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
		s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(false);
	}

	if ( g_GameState == G_MAIN && !s_CUI_ID_FRAME_SelectChannel.m_bChannelInfo_Open )
	{
		s_CUI_ID_FRAME_MessageBox.Show(
			theXmlString.GetString(eText_WaitForChangeMap),
			theXmlString.GetString(eText_WaitForChangeMap),
			CUI_ID_FRAME_MessageBox::eTypeConfirm,
			true,
			ChangeMapServerBusy );
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(60);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(false);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(false);
		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
		UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑
		thePlayerRole.SetShowingWaitforTransport(true);
	}
}

// Button
bool CUI_ID_FRAME_SelectChannel::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// Button
bool CUI_ID_FRAME_SelectChannel::ID_BUTTON_SelectRandomOnButtonClick( ControlObject* pSender )
{
	SelectChannelRandom();
	SetVisable( false );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SelectChannel::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SelectChannel.meui", false, UI_Render_LayerThree  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SelectChannel.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SelectChannel::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SelectChannel, s_CUI_ID_FRAME_SelectChannelOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SelectChannel, s_CUI_ID_FRAME_SelectChannelOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_SelectChannel, ID_LIST_Name, s_CUI_ID_FRAME_SelectChannelID_LIST_NameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SelectChannel, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SelectChannelID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SelectChannel, ID_LIST_State, s_CUI_ID_FRAME_SelectChannelID_LIST_StateOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_SelectChannel, ID_LIST_Select, s_CUI_ID_FRAME_SelectChannelID_LIST_SelectOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_SelectChannel, ID_BUTTON_SelectRandom, s_CUI_ID_FRAME_SelectChannelID_BUTTON_SelectRandomOnButtonClick );

	m_pID_FRAME_SelectChannel = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SelectChannel );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_LIST_Name );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_TEXT_Time );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_BUTTON_CLOSE );
	m_pID_LIST_State = (ControlList*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_LIST_State );
	m_pID_LIST_Select = (ControlList*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_LIST_Select );
	m_pID_BUTTON_SelectRandom = (ControlButton*)theUiManager.FindControl( ID_FRAME_SelectChannel, ID_BUTTON_SelectRandom );

	assert( m_pID_FRAME_SelectChannel );
	assert( m_pID_LIST_Name );
	assert( m_pID_TEXT_Time );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_State );
	assert( m_pID_LIST_Select );
	assert( m_pID_BUTTON_SelectRandom );

	m_pID_LIST_Name->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_Name->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_Name->SetCurSelIndex(-1);

	m_pID_LIST_State->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_State->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_State->SetCurSelIndex(-1);

	m_pID_LIST_Select->SetLDBClickFun(s_CUI_ID_FRAME_SelectChannel.ID_LIST_SelectOnLDBClick);

	//m_pID_FRAME_SelectChannel->SetOnEscResponseType(ControlFrame::EscResponse_SkipMe);

	m_pID_FRAME_SelectChannel->SetMsgProcFun( MessageBox_MsgProc );
	 m_pID_FRAME_SelectChannel->enableEscKey( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SelectChannel::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\SelectChannel.meui" );
}
// 是否可视
bool CUI_ID_FRAME_SelectChannel::_IsVisable()
{
	return m_pID_FRAME_SelectChannel->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SelectChannel::_SetVisable( const bool bVisable )
{
	dwStartTime = 0;
	dwAutoCloseTime = 0;
	m_pID_TEXT_Time->SetText("");

	if ( bVisable )
	{
		m_nCurChannelIndex = -1;
		m_bSelect = false;

		dwStartTime = timeGetTime();
		dwAutoCloseTime = 30;
		if ( g_GameState == G_MAIN )
			dwAutoCloseTime = 50;

		if ( m_bChannelInfo_Open )
			m_pID_BUTTON_CLOSE->SetVisable( true );
		else
			m_pID_BUTTON_CLOSE->SetVisable( false );

		s_CUI_ID_FRAME_MessageBox.closeAll( true );
		m_pID_FRAME_SelectChannel->SetArrayMode( ArrayMode_Top );
		Refresh();
	}
	
	m_pID_FRAME_SelectChannel->SetVisable( bVisable );
}

void CUI_ID_FRAME_SelectChannel::AddChannelInfo( MsgChannelInfo* pInfo )
{
	if ( !pInfo )
		return;

	m_vecChannelInfo.clear();

	for ( int i = 0; i < pInfo->nChannelsCount; i++ )
	{
		SChannelInfo* pChannelInfo = pInfo->GetChannelInfo(i);
		if ( pChannelInfo )
			m_vecChannelInfo.push_back( *pChannelInfo );
	}
}

void CUI_ID_FRAME_SelectChannel::Refresh()
{
	if ( m_vecChannelInfo.size() <= 0 )
	{
		SetVisable( false );
		return;
	}

	m_pID_LIST_Name->Clear();
	m_pID_LIST_State->Clear();
	m_pID_LIST_Select->Clear();

	for ( int i = 0; i < m_vecChannelInfo.size(); i++ )
	{
		ControlList::S_List stList;

		stList.SetData( "" );
		m_pID_LIST_Select->AddItem( &stList );

		stList.SetData( m_vecChannelInfo[i].szChannelName );
		stList.setColor( Color_Config.getColor( nChannelStatusColor[ m_vecChannelInfo[i].chChannelStatus % CUI_ID_FRAME_LOGIN::ES_Max ] ) );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Name->AddItem( &stList );

		stList.SetData( chChannelStatus[ m_vecChannelInfo[i].chChannelStatus % CUI_ID_FRAME_LOGIN::ES_Max ] );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_State->AddItem( &stList );
	}
	
}

void CUI_ID_FRAME_SelectChannel::ClearData()
{
	m_nCurChannelIndex = -1;
	m_vecChannelInfo.clear();
}

std::string CUI_ID_FRAME_SelectChannel::GetChannelName()
{
	std::string str = "";

	if ( m_nlastChannelIndex < 0 || m_nlastChannelIndex >= m_vecChannelInfo.size() )
		return str;

	bool IsRightMap = false;

	if ( g_GameState == G_MAIN )
	{
		for ( std::vector<int>::iterator it = gCfg.m_vecChannelMapId.begin(); it != gCfg.m_vecChannelMapId.end(); it++ )
		{
			if ( *it == theHeroGame.GetLandID() )
			{
				IsRightMap = true;
				break;
			}
		}

		if ( !IsRightMap )
			return str;
	}

	str = m_vecChannelInfo[m_nlastChannelIndex].szChannelName;

	return str;
}

bool CUI_ID_FRAME_SelectChannel::MessageBox_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if ( !s_CUI_ID_FRAME_SelectChannel.IsVisable() )
		return false;

	switch (msg)
	{
	case WM_KEYUP:
		{
			if( wParam == VK_ESCAPE )
				return true;
		}
		break;
	}
	
	return false;
}

void CUI_ID_FRAME_SelectChannel::SelectChannelRandom( int Index/* = -1*/ )
{
	int nIndex = -1;
	if ( Index == -1 )
	{
		nIndex = theRand.rand32() % m_vecChannelInfo.size();
		while( nIndex == m_nlastChannelIndex )
			nIndex = theRand.rand32() % m_vecChannelInfo.size();
	}
	else
		nIndex = Index;

	if ( nIndex < 0 || nIndex >= m_vecChannelInfo.size() )
		return;

	CPlayerMgr* playerMgr = theHeroGame.GetPlayerMgr();
	if ( !playerMgr )
		return;

	if ( !m_bChannelInfo_Open )
		playerMgr->CheckChannel( &m_vecChannelInfo[nIndex] );
	else
		playerMgr->ChangeChannel( m_vecChannelInfo[nIndex].nServerId );

	m_nCurChannelIndex = nIndex;
	m_nlastChannelIndex = nIndex;

	m_bSelect = true;

	if ( g_GameState == G_SELECT )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_WaitEnterWorld), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, EnterWorldFailed);
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(30, false);

		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
		s_CUI_ID_FRAME_MessageBox.SetButVisableCancel(false);
	}

	if ( g_GameState == G_MAIN && !m_bChannelInfo_Open )
	{
		s_CUI_ID_FRAME_MessageBox.Show(
			theXmlString.GetString(eText_WaitForChangeMap),
			theXmlString.GetString(eText_WaitForChangeMap),
			CUI_ID_FRAME_MessageBox::eTypeConfirm,
			true,
			ChangeMapServerBusy );
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(60);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmVisable(false);
		s_CUI_ID_FRAME_MessageBox.SetButConfirmEnable(false);
		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
		UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑
		thePlayerRole.SetShowingWaitforTransport(true);
	}
}

void CUI_ID_FRAME_SelectChannel::SelectTheRightChannel()
{
	if ( m_vecChannelInfo.size() <= 0 )
		return;

	int nIndex = 0;
	uint8 nState = m_vecChannelInfo[0].chChannelStatus;

	for ( int i = 1; i < m_vecChannelInfo.size(); i++ )
	{
		if ( nState > m_vecChannelInfo[i].chChannelStatus )
		{
			nIndex = i;
			nState = m_vecChannelInfo[i].chChannelStatus;
		}
	}

	if ( nIndex < 0 || nIndex >= m_vecChannelInfo.size() )
		return;

	m_nCurChannelIndex = nIndex;
	m_nlastChannelIndex = nIndex;

	CPlayerMgr* playerMgr = theHeroGame.GetPlayerMgr();

	if ( playerMgr )
		playerMgr->CheckChannel( &m_vecChannelInfo[nIndex] );
}