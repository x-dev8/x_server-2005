/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ActivityTrack.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ActivityTrack.h"
#include "ActivityList.h"
#include "PlayerRole.h"
#include "CountryDefine.h"
#include "Common.h"
#include "XmlStringLanguage.h"

CUI_ID_FRAME_ActivityTrack s_CUI_ID_FRAME_ActivityTrack;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ActivityTrack, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ActivityTrack, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityTrack, ID_BUTTON_PlusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ActivityTrack, ID_BUTTON_SubOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_ActivityTrack, ID_LIST_TRACKOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ActivityTrack, ID_CHECKBOX_FlexOnCheckBoxCheck )
CUI_ID_FRAME_ActivityTrack::CUI_ID_FRAME_ActivityTrack()
{
	// Member
	m_pID_FRAME_ActivityTrack = NULL;
	m_pID_LIST_TRACK = NULL;
// 	m_pID_TEXT_Track = NULL;
	m_pID_TEXT_Time = NULL;
	m_pID_TEXT_Remind = NULL;
	m_pID_CHECKBOX_Flex = NULL;

}
// Frame
bool CUI_ID_FRAME_ActivityTrack::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ActivityTrack::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_ActivityTrack::ID_LIST_TRACKOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	///*
	// *	Author 2012-11-20 zhuxincong
	// *	DESC: 尝试着把它显示出来
	// */
	//int nCountryID = thePlayerRole.GetCountry();
	//if (nCountryID != CountryDefine::Country_Init)
	//{
	//		ShowAllSpecial();
	//}
	//else
	//{
	//	char szText[128] = {0};
	//	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", "当前没有国家活动");
	//	m_pID_TEXT_Remind->SetText(szText);
	//}
	
}
// CheckBox
void CUI_ID_FRAME_ActivityTrack::ID_CHECKBOX_FlexOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_ActivityTrack )
		return;

	if( m_pID_CHECKBOX_Flex->IsChecked() )
	{
		HideAllSpecial();
		s_CUI_ID_FRAME_ActivityList.SetTrackShow( false );
	}
	else
	{
		ShowAllSpecial();
		s_CUI_ID_FRAME_ActivityList.SetTrackShow( true );
	}
}

bool CUI_ID_FRAME_ActivityTrack::ID_BUTTON_PlusOnButtonClick( ControlObject* pSender )
{
	ShowAllSpecial();
	s_CUI_ID_FRAME_ActivityList.SetTrackShow( true );
	m_pID_BUTTON_Plus->SetVisable( false );
	m_pID_BUTTON_Sub->SetVisable( true );

	m_pID_TEXT_Remind->SetVisable(true);
	return true;
}

bool CUI_ID_FRAME_ActivityTrack::ID_BUTTON_SubOnButtonClick( ControlObject* pSender )
{
	HideAllSpecial();
	s_CUI_ID_FRAME_ActivityList.SetTrackShow( false );
	m_pID_BUTTON_Plus->SetVisable( true );
	m_pID_BUTTON_Sub->SetVisable( false );

	m_pID_TEXT_Remind->SetVisable(false);
	/*int nCountryID = thePlayerRole.GetCountry();
	if (nCountryID != CountryDefine::Country_Init)
	{
		m_pID_TEXT_Remind->SetVisable(false);
		ShowAllSpecial();
	}
	else
	{
		m_pID_TEXT_Remind->SetVisable(true);
		char szText[128] = {0};
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", "当前没有国家活动");
		m_pID_TEXT_Remind->SetText(szText);
	}*/
	return true;
}

void CUI_ID_FRAME_ActivityTrack::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_ActivityTrack )
        return;

//     m_pID_LIST_TRACK->SetHyberOtherClick(HyberOtherClick);
    m_pID_LIST_TRACK->SetMsgHoldup(false);	//不接受消息
    m_pID_LIST_TRACK->HaveSelBar( false );	//没有绿色cur选中地图
    m_pID_LIST_TRACK->setShowTip(true);
    m_pID_LIST_TRACK->GetScrollBar()->SetEnable(false);

    m_pID_CHECKBOX_Flex->SetCheck( false );
}

// 装载UI
bool CUI_ID_FRAME_ActivityTrack::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ActivityTrack.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ActivityTrack.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ActivityTrack::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ActivityTrack, s_CUI_ID_FRAME_ActivityTrackOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ActivityTrack, s_CUI_ID_FRAME_ActivityTrackOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ActivityTrack, ID_BUTTON_Plus, s_CUI_ID_FRAME_ActivityTrackID_BUTTON_PlusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ActivityTrack, ID_BUTTON_Sub, s_CUI_ID_FRAME_ActivityTrackID_BUTTON_SubOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_ActivityTrack, ID_LIST_TRACK, s_CUI_ID_FRAME_ActivityTrackID_LIST_TRACKOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_ActivityTrack, ID_CHECKBOX_Flex, s_CUI_ID_FRAME_ActivityTrackID_CHECKBOX_FlexOnCheckBoxCheck );

	m_pID_FRAME_ActivityTrack = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ActivityTrack );
	m_pID_LIST_TRACK = (ControlList*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_LIST_TRACK );
// 	m_pID_TEXT_Track = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_TEXT_Track );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_TEXT_Time );
	m_pID_TEXT_Remind=(ControlText*)theUiManager.FindControl( ID_FRAME_ActivityTrack,ID_TEXT_Remind);
	m_pID_BUTTON_Plus = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_BUTTON_Plus );
	m_pID_BUTTON_Sub = (ControlButton*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_BUTTON_Sub );
	m_pID_CHECKBOX_Flex = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ActivityTrack, ID_CHECKBOX_Flex );

	assert( m_pID_FRAME_ActivityTrack );
	assert( m_pID_LIST_TRACK );
// 	assert( m_pID_TEXT_Track );
	assert( m_pID_TEXT_Time );
	assert( m_pID_TEXT_Remind);
	assert( m_pID_CHECKBOX_Flex );

	m_pID_BUTTON_Plus->SetVisable( false );
	m_pID_BUTTON_Sub->SetVisable( true );

    _SetVisable( false );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ActivityTrack::_UnLoadUI()
{
	m_pID_FRAME_ActivityTrack = NULL;
    m_pID_CHECKBOX_Flex = NULL;
    m_pID_LIST_TRACK = NULL;
//     m_pID_TEXT_Track = NULL;
    m_pID_TEXT_Time = NULL;
	m_pID_TEXT_Remind = NULL;

	return theUiManager.RemoveFrame( "Data\\UI\\ActivityTrack.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ActivityTrack::_IsVisable()
{
	if(!m_pID_FRAME_ActivityTrack)
		return false;

	return m_pID_FRAME_ActivityTrack->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ActivityTrack::_SetVisable( const bool bVisable )
{
	if(m_pID_FRAME_ActivityTrack)
		m_pID_FRAME_ActivityTrack->SetVisable( bVisable );
}

void CUI_ID_FRAME_ActivityTrack::HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId )
{
	s_CUI_ID_FRAME_ActivityList.MoveToTarget(nId);
}

int CUI_ID_FRAME_ActivityTrack::GetTrackListItemCnt()
{
	if(m_pID_LIST_TRACK)
		return m_pID_LIST_TRACK->GetListItemCnt();
	else
		assert(false);

	return 0;
}

void CUI_ID_FRAME_ActivityTrack::TrackAddItem( const ControlList::S_List* pItem, const bool bMoveDonw )
{
	if(m_pID_LIST_TRACK)
	{
		m_pID_TEXT_Remind->SetVisable(false);
		m_pID_LIST_TRACK->AddItem( pItem,NULL, bMoveDonw );
	}
	else
		assert(false);
}

ControlList::S_List* CUI_ID_FRAME_ActivityTrack::GetTrackListItem( int i )
{
	if(m_pID_LIST_TRACK)
		return m_pID_LIST_TRACK->GetListItem(i);
	else
		assert(false);

	return NULL;
}

void CUI_ID_FRAME_ActivityTrack::TrackClear( bool b )
{
	if(m_pID_LIST_TRACK)
		m_pID_LIST_TRACK->Clear( b );
	else
		assert(false);
}

int CUI_ID_FRAME_ActivityTrack::GetTrackStartIndex()
{
	if(m_pID_LIST_TRACK)
		return m_pID_LIST_TRACK->GetShowStartHeight();
	else
		assert(false);

	return 0;
}

int CUI_ID_FRAME_ActivityTrack::GetTrackItemShowCount()
{
	if(m_pID_LIST_TRACK)
		return m_pID_LIST_TRACK->GetItemShowCount();
	else
		assert(false);

	return 0;
}

void CUI_ID_FRAME_ActivityTrack::SetShowStartHeight( int i )
{
	if(m_pID_LIST_TRACK)
		m_pID_LIST_TRACK->SetShowStartHeight(i);
	else
		assert(false);
}

void CUI_ID_FRAME_ActivityTrack::SetTrackScrollValue( int i )
{
	if(m_pID_LIST_TRACK)
		m_pID_LIST_TRACK->SetScrollValue(i);
	else
		assert(false);
}

void CUI_ID_FRAME_ActivityTrack::SetTextTime(const char* chr)
{
	if(m_pID_LIST_TRACK && chr )
		m_pID_TEXT_Time->SetText(chr);
	else
		assert(false);
}

//added by zhuomeng.hu		[9/7/2010]
bool CUI_ID_FRAME_ActivityTrack::AddSpecialActivity( const SpecialActivity* activity )	
{
	if( m_specialActivityMap.count( activity->strName ) )
		return false;

	m_specialActivityMap.insert( make_pair( activity->strName, *activity ) );
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
	return true;
}

bool CUI_ID_FRAME_ActivityTrack::DelSpecialActivity( std::string strName )
{
	if( !m_specialActivityMap.count( strName ) )
		return false;

	m_specialActivityMap.erase( strName );
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
	return true;
}

SpecialActivity* CUI_ID_FRAME_ActivityTrack::GetSpecialActivityPtr( std::string strName )
{
	if( !m_specialActivityMap.count( strName ) )
		return 0;
	else
		return &m_specialActivityMap.find( strName )->second;
}

bool CUI_ID_FRAME_ActivityTrack::SetSpecialActivityVisable( std::string strName, bool bVisable )
{
	if( !m_specialActivityMap.count( strName ) )
		return false;

	m_specialActivityMap.find( strName )->second.bVisable = bVisable;
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
	return true;
}

void CUI_ID_FRAME_ActivityTrack::HideAllSpecial()
{
	std::map<std::string, SpecialActivity>::iterator it = m_specialActivityMap.begin();
	for( ; it != m_specialActivityMap.end(); ++it )
		it->second.bVisable = false;
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
}

void CUI_ID_FRAME_ActivityTrack::ShowAllSpecial()
{
	std::map<std::string, SpecialActivity>::iterator it = m_specialActivityMap.begin();
	for( ; it != m_specialActivityMap.end(); ++it )
		it->second.bVisable = true;
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
}

void CUI_ID_FRAME_ActivityTrack::RefreshAllSpecial()
{
	std::map<std::string, SpecialActivity>::iterator iter = m_specialActivityMap.begin();
	/*
	 *	Author 2012-11-22 zhuxincong
	 *	DESC: 如果国家没有发布任务的话，就显示当前没有国家活动
	 */
	if (m_specialActivityMap.empty())
	{
		m_pID_TEXT_Remind->SetVisable(true);
		char szText[128] = {0};
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%s", theXmlString.GetString(eText_CoutryActived));

		m_pID_TEXT_Remind->SetText(szText);
	}
	else
	{
		m_pID_TEXT_Remind->SetVisable(false);
	}

	for( ; iter != m_specialActivityMap.end(); ++iter )
	{
		if( !iter->second.bVisable )
			continue;

		std::vector<ControlList::S_List>::iterator it = iter->second.itemVec.begin();
		for( ; it != iter->second.itemVec.end(); ++it )
		{
			TrackAddItem( &( *it ), false );
		}	
	}
}

void CUI_ID_FRAME_ActivityTrack::ClearAllSpecial()
{
	m_specialActivityMap.clear();
	s_CUI_ID_FRAME_ActivityList.RefreshEvents();
}
