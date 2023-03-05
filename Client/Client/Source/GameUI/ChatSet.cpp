/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Bin\Client\Data\Ui\ChatSet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChatSet.h"
#include "UserData.h"
#include "ChatChannelConfig.h"
#include "chat_list.h"
#include "Rename.h"
#include "MessageDefine.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "create.h"
#include "RapidXml/MeRapidXml.h"
#include "InfoList.h"

extern HWND g_hWnd;

#define CHATCHANNELCONFIG_USER_FILENAME "ChatChannelConfig.config"

extern int  MAX_CHAT_COUNT	;
CUI_ID_FRAME_ChatSet s_CUI_ID_FRAME_ChatSet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChatSet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChatSet, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_CancelOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_TeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_MiniGroupOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_NearOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_AotoChatOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_WorldOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_ZhenYingOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_CountryOnCheckBoxCheck )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_EDIT_AotoChatOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_helpOnButtonClick )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_CampOnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_LIST_ChannelListOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_DeleteOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_CreateOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_PrivateOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_SystemOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_AttackInfoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_HornOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_BUTTON_DefaultOnButtonClick )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_SCROLLBAREX_DiaphaneityOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_FamilyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ChatSet, ID_CHECKBOX_GuanYuanOnCheckBoxCheck )


ChatChannelConfig::ChatChannelInfoList s_TempChatChannelList;

CUI_ID_FRAME_ChatSet::CUI_ID_FRAME_ChatSet()
{
	// Member
	m_pID_FRAME_ChatSet = NULL;
	//m_pID_PICTURE_title_wall = NULL;
	m_pID_PICTURE_ChannelList = NULL;
	m_pID_PICTURE_imagewall = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Near = NULL;
	m_pID_TEXT_Team = NULL;
	m_pID_TEXT_Camp = NULL;
	m_pID_TEXT_MiniGroup = NULL;
	m_pID_TEXT_ChatInto = NULL;
	m_pID_TEXT_AotoChat = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_MiniGroup = NULL;
	m_pID_CHECKBOX_Near = NULL;
	m_pID_CHECKBOX_AotoChat = NULL;
	m_pID_TEXT_World = NULL;
	m_pID_CHECKBOX_World = NULL;
	m_pID_PICTURE_imagewall3 = NULL;
	m_pID_EDIT_AotoChat = NULL;
	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_25399 = NULL;
// 	m_pID_CHECKBOX_Camp = NULL;
	m_pID_LIST_ChannelList = NULL;
	m_pID_BUTTON_Delete = NULL;
	m_pID_BUTTON_Create = NULL;
	m_pID_TEXT_ChannelName = NULL;
	m_pID_TEXT_Private = NULL;
	m_pID_CHECKBOX_Private = NULL;
	m_pID_TEXT_System = NULL;
	m_pID_CHECKBOX_System = NULL;
    m_pID_CHECKBOX_AttackInfo = NULL;
    m_pID_TEXT_AttackInfo = NULL;
    m_pID_BUTTON_Default = NULL;
    m_pID_CHECKBOX_Horn = NULL;
    m_pID_SCROLLBAREX_Diaphaneity = NULL;
	m_pID_CHECKBOX_Family = NULL;
	m_pID_CHECKBOX_GuanYuan = NULL;

// 	m_pID_TEXT_ZhenYing = NULL;
// 	m_pID_CHECKBOX_ZhenYing = NULL;

}
// Frame
bool CUI_ID_FRAME_ChatSet::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChatSet::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_ChatSet::RefreshChannelList()
{
	m_pID_LIST_ChannelList->Clear();
	for( int i = 0 ; i < s_TempChatChannelList.size(); ++ i )
	{
		ControlList::S_List sItem;
		sItem.SetData( s_TempChatChannelList[i].m_strChannelName.c_str() );
		m_pID_LIST_ChannelList->AddItem( &sItem );
	}
}

void CUI_ID_FRAME_ChatSet::LoadChannelConfig()
{
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += CHATCHANNELCONFIG_USER_FILENAME;
	if( !ChatChannelConfig::Instance()->Load( filename.c_str() ) )
		return;

	s_TempChatChannelList = ChatChannelConfig::Instance()->GetChatChannelList();
    m_DefChatChannelList = ChatChannelConfig::Instance()->GetChatChannelList();

	s_CUI_ID_FRAME_chatInfoList.RefreshChannel();
}

void CUI_ID_FRAME_ChatSet::SaveChannelConfig()
{
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += CHATCHANNELCONFIG_USER_FILENAME;
	ChatChannelConfig::Instance()->SetChatChannelList( s_TempChatChannelList );
	if( !ChatChannelConfig::Instance()->Save( filename.c_str() ) )
		return;

	s_CUI_ID_FRAME_chatInfoList.RefreshChannel();
}

static void UIChatSet_OnVisibleChanged(ControlObject* pSender)
{
	if (pSender && !pSender->IsVisable())
		ImmAssociateContext( g_hWnd, NULL );
}
// Button
bool CUI_ID_FRAME_ChatSet::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return false;
	}

	SaveAutoReplyConfig();	
	SaveChannelConfig();
	SetVisable(false);	
	return true;
}
// Button
bool CUI_ID_FRAME_ChatSet::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return false;
	}

	LoadChannelConfig();
	RefreshChannelList();
	RefreshChannelInfo();
	SetVisable(false);
	return true;
}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_TERM )
    {
        m_pID_CHECKBOX_Team->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_TERM;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_TERM;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_TERM;
    }
}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_MiniGroupOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_GUILD )
    {
        m_pID_CHECKBOX_MiniGroup->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_GUILD;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_GUILD;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_GUILD;
    }
}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_NearOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_NORMAL )
    {
        m_pID_CHECKBOX_Near->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_NORMAL;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_NORMAL;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_NORMAL;
    }
}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_AotoChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
}

//lyh++ guanyuan chatSet
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_GuanYuanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}
	
	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;

	if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_COUNTRYOFFICIAL )
	{
		m_pID_CHECKBOX_GuanYuan->SetCheck( true );
		s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_COUNTRYOFFICIAL;
	}
	else
	{
		if( *pbChecked )
			s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_COUNTRYOFFICIAL;
		else
			s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_COUNTRYOFFICIAL;
	}


}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_WorldOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_HIGHSHOUT )
    {
        m_pID_CHECKBOX_World->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_HIGHSHOUT;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_HIGHSHOUT;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_HIGHSHOUT;
    }
}
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_SystemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_PROGRAM_SYSTEM & MsgChat::CHAT_TYPE_BULL & MsgChat::CHAT_TYPE_GAMEPROMPT )
    {
        m_pID_CHECKBOX_System->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_PROGRAM_SYSTEM | MsgChat::CHAT_TYPE_BULL | MsgChat::CHAT_TYPE_GAMEPROMPT;
    }
    else
    {
        if( *pbChecked )
        {
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_PROGRAM_SYSTEM;
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_BULL;
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_GAMEPROMPT;
        }
        else
        {
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_PROGRAM_SYSTEM;
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_BULL;
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_GAMEPROMPT;
        }
    }
}
// CheckBox
// void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_ZhenYingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ChatSet)
// 	{
// 		assert(false&&"ui error");
// 		return ;
// 	}
// 
// 	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
// 	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
// 		return;
// 	if( *pbChecked )
// 		s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_BATTLE;
// 	else
// 		s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_BATTLE;
// }

// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_CountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_COUNTRY )
    {
        m_pID_CHECKBOX_Country->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_COUNTRY;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_COUNTRY;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_COUNTRY;
    }
}

// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_FamilyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ChatSet )
		return;

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;

	if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_FAMILY )
	{
		m_pID_CHECKBOX_Family->SetCheck( true );
		s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_FAMILY;
	}
	else
	{
		if( *pbChecked )
			s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_FAMILY;
		else
			s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_FAMILY;
	}
}

// Edit
void CUI_ID_FRAME_ChatSet::ID_EDIT_AotoChatOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_ChatSet::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
// bool CUI_ID_FRAME_ChatSet::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// CheckBox
// void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_CampOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pID_FRAME_ChatSet)
// 	{
// 		assert(false&&"ui error");
// 		return ;
// 	}
// 
// 	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
// 	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
// 		return;
// 	if( *pbChecked )
// 		s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_LEAGUE;
// 	else
// 		s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_LEAGUE;
// }

bool CUI_ID_FRAME_ChatSet::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_ChatSet )
        return false;
    
    int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
    if( nIndex < 0 || nIndex >= m_DefChatChannelList.size() || nIndex >= s_TempChatChannelList.size() )
        return true;

    s_TempChatChannelList[nIndex].m_dwChannelType = m_DefChatChannelList[nIndex].m_dwChannelType;
    RefreshChannelInfo();
    return true;
}

void CUI_ID_FRAME_ChatSet::ID_SCROLLBAREX_DiaphaneityOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
    if ( !m_pID_FRAME_ChatSet )
        return;
    
    float fAlpha = ( float )n / 100.0f;
    //s_CUI_ID_FRAME_InfoList.SetRealAlpha( fAlpha );
    //s_CUI_ID_FRAME_chatInfoList.SetRealAlpha( fAlpha );
}

void CUI_ID_FRAME_ChatSet::RefreshCheckBoxsEnable( bool bEnable )
{
	if(!m_pID_FRAME_ChatSet)
		return;

	m_pID_CHECKBOX_MiniGroup->SetEnable( bEnable );
	m_pID_CHECKBOX_Private->SetEnable( bEnable );
	m_pID_CHECKBOX_Near->SetEnable( bEnable );
	m_pID_CHECKBOX_Team->SetEnable( bEnable );
	m_pID_CHECKBOX_World->SetEnable( bEnable );
	m_pID_CHECKBOX_System->SetEnable( bEnable );
	m_pID_CHECKBOX_AttackInfo->SetEnable( bEnable );
	//m_pID_CHECKBOX_ZhenYing->SetEnable( bEnable );
	m_pID_CHECKBOX_Country->SetEnable( bEnable );
	m_pID_CHECKBOX_Horn->SetEnable( bEnable );
	m_pID_CHECKBOX_Family->SetEnable( bEnable );
	m_pID_CHECKBOX_GuanYuan->SetEnable(bEnable);
}

void CUI_ID_FRAME_ChatSet::RefreshChannelInfo()
{
	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
	{
		if( m_pID_LIST_ChannelList->GetListItemCnt() <= 0 )
			return;
		nIndex = 0;
		m_pID_LIST_ChannelList->SetCurSelIndex( nIndex );		
	}

	// 专为水浒设计（NC）
//	RefreshCheckBoxsEnable( false );
//	if( nIndex == (int)s_TempChatChannelList.size() - 1 )
//	{
//		RefreshCheckBoxsEnable( true );
//	}
	// End of NC

	//m_pID_CHECKBOX_Camp->SetCheck( false );
	m_pID_CHECKBOX_MiniGroup->SetCheck( false );
	m_pID_CHECKBOX_Private->SetCheck( false );
	m_pID_CHECKBOX_Near->SetCheck( false );
	m_pID_CHECKBOX_Team->SetCheck( false );
	m_pID_CHECKBOX_World->SetCheck( false );
	m_pID_CHECKBOX_System->SetCheck( false );
    m_pID_CHECKBOX_AttackInfo->SetCheck( false);
	//m_pID_CHECKBOX_ZhenYing->SetCheck( false );
	m_pID_CHECKBOX_Country->SetCheck( false );
    m_pID_CHECKBOX_Horn->SetCheck( false );
	m_pID_CHECKBOX_Family->SetCheck( false );
    m_pID_CHECKBOX_GuanYuan->SetCheck(false); //lyh++


	ChatChannelConfig::ChatChannelInfo& info = s_TempChatChannelList[nIndex];
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_NORMAL ) //普通
		m_pID_CHECKBOX_Near->SetCheck( true );
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_GUILD )  // 公会
		m_pID_CHECKBOX_MiniGroup->SetCheck( true );
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_TERM )  // 组队
		m_pID_CHECKBOX_Team->SetCheck( true );
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_PRIVATE )  // 私聊
		m_pID_CHECKBOX_Private->SetCheck( true );
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_HIGHSHOUT )  // 世界
		m_pID_CHECKBOX_World->SetCheck( true );	
	if( info.m_dwChannelType & MsgChat::CHAT_TYPE_COUNTRY )  // 国家战场
		m_pID_CHECKBOX_Country->SetCheck( true );	
	if( ( info.m_dwChannelType & MsgChat::CHAT_TYPE_BULL ) &&       // 系统
		( info.m_dwChannelType & MsgChat::CHAT_TYPE_GAMEPROMPT ) &&
		( info.m_dwChannelType & MsgChat::CHAT_TYPE_PROGRAM_SYSTEM ) )
		m_pID_CHECKBOX_System->SetCheck( true );
   if( info.m_dwChannelType & MsgChat::CHAT_TYPE_FIGHTINFO )         // 战斗
        m_pID_CHECKBOX_AttackInfo->SetCheck( true );
   if( info.m_dwChannelType & MsgChat::CHAT_TYPE_HIGHSHOUT_VIP )
        m_pID_CHECKBOX_Horn->SetCheck( true );

   if( info.m_dwChannelType & MsgChat::CHAT_TYPE_COUNTRYOFFICIAL )
	   m_pID_CHECKBOX_GuanYuan->SetCheck( true );

   if( info.m_dwChannelType & MsgChat::CHAT_TYPE_FAMILY )
	   m_pID_CHECKBOX_Family->SetCheck( true );

	m_pID_BUTTON_Delete->SetEnable( true );
	if( nIndex == 0 )
		m_pID_BUTTON_Delete->SetEnable( false );

	m_pID_EDIT_AotoChat->SetText("");

		
}
// List
void CUI_ID_FRAME_ChatSet::ID_LIST_ChannelListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	RefreshChannelInfo();
}
// Button
bool CUI_ID_FRAME_ChatSet::ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return false;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return false;

	for( ChatChannelConfig::ChatChannelInfoList::iterator it = s_TempChatChannelList.begin() ; it != s_TempChatChannelList.end() ; ++ it )
	{
		if( (*it).m_strChannelName == s_TempChatChannelList[nIndex].m_strChannelName &&
			(*it).m_dwChannelType == s_TempChatChannelList[nIndex].m_dwChannelType &&
			(*it).m_dwChannelColor == s_TempChatChannelList[nIndex].m_dwChannelColor )
		{
			s_TempChatChannelList.erase( it );
			RefreshChannelList();
			RefreshChannelInfo();
			return true;
		}
	}

	return true;
}
void CUI_ID_FRAME_ChatSet::AddChannel( const char* pszName )
{
	ChatChannelConfig::ChatChannelInfo ccInfo;
	ccInfo.m_strChannelName = pszName;
	ccInfo.m_dwChannelType = 0;
	ccInfo.m_dwChannelColor = 0xffffffff;
    ccInfo.m_dwDefChannelType = 0;
	s_TempChatChannelList.push_back( ccInfo );
	RefreshChannelList();
	m_pID_LIST_ChannelList->SetCurSelIndex( s_TempChatChannelList.size() - 1 );
	RefreshChannelInfo();
}

// Button
bool CUI_ID_FRAME_ChatSet::ID_BUTTON_CreateOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return false;
	}

	if( s_TempChatChannelList.size() >= MAX_CHANNELTAB_COUNT )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_Error_MaxChatChannel ), theXmlString.GetString( eText_Error_MaxChatChannel ) );
		return true;
	}
	s_CUI_ID_FRAME_Rename.SetType(CUI_ID_FRAME_Rename::eChangeChatChannel);
	s_CUI_ID_FRAME_Rename.SetVisable( true );
	return true;
}
// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_PrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

	int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
	if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
		return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_PRIVATE )
    {
        m_pID_CHECKBOX_Private->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_PRIVATE;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_PRIVATE;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_PRIVATE;
    }
}

// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_AttackInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_ChatSet)
	{
		assert(false&&"ui error");
		return ;
	}

    int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
    if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
        return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_FIGHTINFO )
    {
        m_pID_CHECKBOX_AttackInfo->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_FIGHTINFO;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_FIGHTINFO;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_FIGHTINFO;
    }
}

// CheckBox
void CUI_ID_FRAME_ChatSet::ID_CHECKBOX_HornOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    if(!m_pID_FRAME_ChatSet)
    {
        assert(false&&"ui error");
        return ;
    }

    int nIndex = m_pID_LIST_ChannelList->GetCurSelIndex();
    if( nIndex < 0 || nIndex >= s_TempChatChannelList.size() )
        return;
    if( s_TempChatChannelList[nIndex].m_dwDefChannelType & MsgChat::CHAT_TYPE_HIGHSHOUT_VIP )
    {
        m_pID_CHECKBOX_Horn->SetCheck( true );
        s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_HIGHSHOUT_VIP;
    }
    else
    {
        if( *pbChecked )
            s_TempChatChannelList[nIndex].m_dwChannelType |= MsgChat::CHAT_TYPE_HIGHSHOUT_VIP;
        else
            s_TempChatChannelList[nIndex].m_dwChannelType &= ~MsgChat::CHAT_TYPE_HIGHSHOUT_VIP;
    }
}

// 装载UI
bool CUI_ID_FRAME_ChatSet::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChatSet.MEUI" ,false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChatSet.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ChatSet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChatSet, s_CUI_ID_FRAME_ChatSetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChatSet, s_CUI_ID_FRAME_ChatSetOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_Ok, s_CUI_ID_FRAME_ChatSetID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_Cancel, s_CUI_ID_FRAME_ChatSetID_BUTTON_CancelOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Team, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_TeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_MiniGroup, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_MiniGroupOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Near, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_NearOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_AotoChat, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_AotoChatOnCheckBoxCheck );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_ZhenYing, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_ZhenYingOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Country, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_CountryOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_World, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_WorldOnCheckBoxCheck );
	theUiManager.OnEditEnter( ID_FRAME_ChatSet, ID_EDIT_AotoChat, s_CUI_ID_FRAME_ChatSetID_EDIT_AotoChatOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ChatSetID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_help, s_CUI_ID_FRAME_ChatSetID_BUTTON_helpOnButtonClick );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Camp, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_CampOnCheckBoxCheck );
	theUiManager.OnListSelectChange( ID_FRAME_ChatSet, ID_LIST_ChannelList, s_CUI_ID_FRAME_ChatSetID_LIST_ChannelListOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_Delete, s_CUI_ID_FRAME_ChatSetID_BUTTON_DeleteOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_Create, s_CUI_ID_FRAME_ChatSetID_BUTTON_CreateOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Private, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_PrivateOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_System, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_SystemOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_AttackInfo, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_AttackInfoOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Horn, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_HornOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_ChatSet, ID_BUTTON_Default, s_CUI_ID_FRAME_ChatSetID_BUTTON_DefaultOnButtonClick );
    theUiManager.OnScrollBarExUpdatePos( ID_FRAME_ChatSet, ID_SCROLLBAREX_Diaphaneity,
        s_CUI_ID_FRAME_ChatSetID_SCROLLBAREX_DiaphaneityOnScrollBarExUpdatePos );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_Family, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_FamilyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ChatSet, ID_CHECKBOX_GuanYuan, s_CUI_ID_FRAME_ChatSetID_CHECKBOX_GuanYuanOnCheckBoxCheck );

	m_pID_FRAME_ChatSet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChatSet );
	//m_pID_PICTURE_title_wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_PICTURE_title_wall );
	m_pID_PICTURE_ChannelList = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_PICTURE_ChannelList );
	m_pID_PICTURE_imagewall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_PICTURE_imagewall );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_Cancel );
	m_pID_TEXT_Near = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_Near );
	m_pID_TEXT_Team = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_Team );
	m_pID_TEXT_Camp = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_Camp );
	m_pID_TEXT_MiniGroup = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_MiniGroup );
	m_pID_TEXT_ChatInto = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_ChatInto );
	m_pID_TEXT_AotoChat = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_AotoChat );
	m_pID_CHECKBOX_Team = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Team );
	m_pID_CHECKBOX_MiniGroup = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_MiniGroup );
	m_pID_CHECKBOX_Near = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Near );
	m_pID_CHECKBOX_AotoChat = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_AotoChat );
// 	m_pID_TEXT_ZhenYing = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_ZhenYing );
// 	m_pID_CHECKBOX_ZhenYing = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_ZhenYing );
	m_pID_CHECKBOX_Country = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Country );
	m_pID_TEXT_World = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_World );
	m_pID_CHECKBOX_World = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_World );
	m_pID_PICTURE_imagewall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_PICTURE_imagewall3 );
	m_pID_EDIT_AotoChat = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_EDIT_AotoChat );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_help );
// 	m_pID_PICTURE_25399 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_PICTURE_25399 );
// 	m_pID_CHECKBOX_Camp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Camp );
	m_pID_LIST_ChannelList = (ControlList*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_LIST_ChannelList );
	m_pID_BUTTON_Delete = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_Delete );
	m_pID_BUTTON_Create = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_Create );
	m_pID_TEXT_ChannelName = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_ChannelName );
	m_pID_TEXT_Private = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_Private );
	m_pID_CHECKBOX_Private = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Private );
	m_pID_TEXT_System = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_System );
	m_pID_CHECKBOX_System = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_System );
    m_pID_CHECKBOX_AttackInfo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_AttackInfo );
    m_pID_TEXT_AttackInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_TEXT_AttackInfo );	
    m_pID_CHECKBOX_Horn = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Horn );	
    m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_BUTTON_Default );
    m_pID_SCROLLBAREX_Diaphaneity = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_SCROLLBAREX_Diaphaneity );
	m_pID_CHECKBOX_Family = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_Family );
	m_pID_CHECKBOX_GuanYuan = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ChatSet, ID_CHECKBOX_GuanYuan ); //lyh++

	assert(m_pID_CHECKBOX_GuanYuan);

    assert( m_pID_FRAME_ChatSet );
	//assert( m_pID_PICTURE_title_wall );
	assert( m_pID_PICTURE_ChannelList );
	assert( m_pID_PICTURE_imagewall );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Near );
	assert( m_pID_TEXT_Team );
	//assert( m_pID_TEXT_Camp );
	assert( m_pID_TEXT_MiniGroup );
	assert( m_pID_TEXT_ChatInto );
	assert( m_pID_TEXT_AotoChat );
	assert( m_pID_CHECKBOX_Team );
	assert( m_pID_CHECKBOX_MiniGroup );
	assert( m_pID_CHECKBOX_Near );
	assert( m_pID_CHECKBOX_AotoChat );
// 	assert( m_pID_TEXT_ZhenYing );
// 	assert( m_pID_CHECKBOX_ZhenYing );
	assert( m_pID_TEXT_World );
	assert( m_pID_CHECKBOX_World );
	assert( m_pID_PICTURE_imagewall3 );
	assert( m_pID_EDIT_AotoChat );
	assert( m_pID_BUTTON_CLOSE );
//	assert( m_pID_BUTTON_help );
// 	assert( m_pID_PICTURE_25399 );
// 	assert( m_pID_CHECKBOX_Camp );
	assert( m_pID_LIST_ChannelList );
	assert( m_pID_BUTTON_Delete );
	assert( m_pID_BUTTON_Create );
	assert( m_pID_TEXT_ChannelName );
	assert( m_pID_TEXT_Private );
	assert( m_pID_CHECKBOX_Private );
	assert( m_pID_TEXT_System );
	assert( m_pID_CHECKBOX_System );
    assert( m_pID_CHECKBOX_AttackInfo );
    assert( m_pID_TEXT_AttackInfo );
    assert( m_pID_CHECKBOX_Horn );
    assert( m_pID_BUTTON_Default );
    assert( m_pID_SCROLLBAREX_Diaphaneity );
	assert( m_pID_CHECKBOX_Family );

	m_pID_FRAME_ChatSet->SetOnVisibleChangedFun(UIChatSet_OnVisibleChanged);
	m_pID_EDIT_AotoChat->SetMaxLength(MAX_CHAT_COUNT);	
    m_pID_SCROLLBAREX_Diaphaneity->SetMaxValue( 100 );
    m_pID_SCROLLBAREX_Diaphaneity->SetStepValue( 10 );
    m_pID_SCROLLBAREX_Diaphaneity->SetValue( 0 );
	LoadAutoReplyConfig();
	LoadChannelConfig();
	RefreshChannelList();
	RefreshChannelInfo();

    _SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChatSet::_UnLoadUI()
{
	m_pID_FRAME_ChatSet = NULL;
	//m_pID_PICTURE_title_wall = NULL;
	m_pID_PICTURE_ChannelList = NULL;
	m_pID_PICTURE_imagewall = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Near = NULL;
	m_pID_TEXT_Team = NULL;
	m_pID_TEXT_Camp = NULL;
	m_pID_TEXT_MiniGroup = NULL;
	m_pID_TEXT_ChatInto = NULL;
	m_pID_TEXT_AotoChat = NULL;
	m_pID_CHECKBOX_Team = NULL;
	m_pID_CHECKBOX_MiniGroup = NULL;
	m_pID_CHECKBOX_Near = NULL;
	m_pID_CHECKBOX_AotoChat = NULL;
	m_pID_TEXT_World = NULL;
	m_pID_CHECKBOX_World = NULL;
	m_pID_PICTURE_imagewall3 = NULL;
	m_pID_EDIT_AotoChat = NULL;
	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_25399 = NULL;
// 	m_pID_CHECKBOX_Camp = NULL;
	m_pID_LIST_ChannelList = NULL;
	m_pID_BUTTON_Delete = NULL;
	m_pID_BUTTON_Create = NULL;
	m_pID_TEXT_ChannelName = NULL;
	m_pID_TEXT_Private = NULL;
	m_pID_CHECKBOX_Private = NULL;
	m_pID_TEXT_System = NULL;
	m_pID_CHECKBOX_System = NULL;
    m_pID_CHECKBOX_AttackInfo = NULL;
    m_pID_TEXT_AttackInfo = NULL;
    m_pID_BUTTON_Default = NULL;
    m_pID_CHECKBOX_Horn = NULL;
    m_pID_SCROLLBAREX_Diaphaneity = NULL;
	m_pID_CHECKBOX_GuanYuan  = NULL;
// 	m_pID_TEXT_ZhenYing = NULL;
// 	m_pID_CHECKBOX_ZhenYing = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ChatSet.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ChatSet::_IsVisable()
{
    if(!m_pID_FRAME_ChatSet)
        return false;

	return m_pID_FRAME_ChatSet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ChatSet::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_ChatSet)
		return;

	m_pID_FRAME_ChatSet->SetVisable( bVisable );	

	m_pID_EDIT_AotoChat->SetActivate(true);
	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
}

void CUI_ID_FRAME_ChatSet::LoadAutoReplyConfig()
{
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += "ChatSetting.xml";

	MeXmlDocument doc;
	if (!doc.LoadFile(filename.c_str()))
		return;

	MeXmlElement* pElem = doc.FirstChildElement("Project")->FirstChildElement("Chat");
	if (pElem)
	{
		int checked = 0;

		pElem->QueryIntAttribute("IsAutoAck", &checked);
		m_pID_CHECKBOX_AotoChat->SetCheck(checked);

		const char* s = pElem->Attribute("AutoText");
		m_pID_EDIT_AotoChat->SetText(s ? s : "");
	}
}

void CUI_ID_FRAME_ChatSet::SaveAutoReplyConfig()
{
	std::string filename = CUserData::Instance()->GetUserDataPath();
	filename += "ChatSetting.xml";

	SetFileAttributes( filename.c_str(), FILE_ATTRIBUTE_NORMAL );

	MeXmlDocument doc;
	MeXmlDeclaration decl("1.0", "utf-8", "yes");
	doc.InsertEndChild(decl);

	MeXmlElement *project = doc.InsertEndChild("Project");
	project->SetAttribute("Name", "HeroOnline");
	project->SetAttribute("Version", "");

	MeXmlElement *chat = project->InsertEndChild("Chat");
	chat->SetAttribute("IsAutoAck", m_pID_CHECKBOX_AotoChat->IsChecked());
	chat->SetAttribute("AutoText", m_pID_EDIT_AotoChat->GetText());

// 	project.InsertEndChild(chat);

// 	doc.InsertEndChild(project);
	doc.SaveFile(filename.c_str());
}

BOOL CUI_ID_FRAME_ChatSet::EditInputIsVisable()
{
	if( m_pID_EDIT_AotoChat )
	{
		bool bRet = (theUiManager.GetFocus() ==m_pID_EDIT_AotoChat);
		return bRet;

	}
	return FALSE;

}