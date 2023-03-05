/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\家族\FamilyApply.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SystemFamily.h"
#include "FamilyMessage.h"
#include "NetworkInput.h"
#include "FamilyMessageBox.h"
#include "CountryFunction.h"
#include "ScreenInfoManager.h"
#include "Create.h"
#include "PlayerRole.h"
#include "FamilyConfig.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "FamilyApply.h"


extern HWND g_hWnd;

CUI_ID_FRAME_FamilyApply s_CUI_ID_FRAME_FamilyApply;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FamilyApply, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FamilyApply, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_BUTTON_ApplyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_LIST_GuildListOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_LIST_LevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_LIST_CDROnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_LIST_AmountOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_EDIT_GJZOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_BUTTON_SearchOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_FamilyApply, ID_LIST_NameOnListSelectChange )
CUI_ID_FRAME_FamilyApply::CUI_ID_FRAME_FamilyApply()
{
	// Member
	m_pID_FRAME_FamilyApply = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LIST_GuildList = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_CDR = NULL;
	m_pID_LIST_Amount = NULL;
	m_pID_TEXT_ZuZhang = NULL;
	m_pID_TEXT_ZhiYe = NULL;
	m_pID_TEXT_DengJi = NULL;
	m_pID_EDIT_GJZ = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_LIST_Name = NULL;
	m_bIsSreachResult = false;
}

bool InfoCompare( const FamilyDefine::FamilySimpleInfo info1, const FamilyDefine::FamilySimpleInfo info2 )
{
	if ( info1.GetLevel() > info2.GetLevel() )
	{
		return true;
	}
	else if ( info1.GetLevel() < info2.GetLevel() )
	{
		return false;
	}
	else	//如果相等 比较繁荣度
	{
		if ( info1.GetProsperity() > info2.GetProsperity() )
		{
			return true;
		}
		else if( info1.GetProsperity() < info2.GetProsperity() )
		{
			return false;
		}
		else	// 再比较人数
		{
			if ( info1.GetMemberCount() > info2.GetMemberCount() )
			{
				return true;
			}
			else if ( info1.GetMemberCount() < info2.GetMemberCount() )
			{
				return false;
			}
			else	//再比较名称
			{
				if ( strcmp( info1.GetFamilyName(), info2.GetFamilyName() ) > 0 )
				{
					return true;
				}
				else
				{
					return false;
				}
				
			}
			
		}
		
	}
	
	
}

bool CUI_ID_FRAME_FamilyApply::EditInputIsVisable()
{
	if ( m_pID_EDIT_GJZ == NULL )
	{
		return false;
	}
	return (m_pID_EDIT_GJZ == theUiManager.GetFocus());
}

void CUI_ID_FRAME_FamilyApply::InitialListValues()
{
	ClearValues();
	CSystemFamily::Instance()->GetAllInfo(m_vecSimpleInfoSet);
	std::sort( m_vecSimpleInfoSet.begin(), m_vecSimpleInfoSet.end(), InfoCompare );

	for ( FamilySimpleInfoSetIt_t it = m_vecSimpleInfoSet.begin(); it != m_vecSimpleInfoSet.end(); it ++ )
	{
		char strLevel[64] = {0};
		char strProsperity[64] = {0};
		char strMemberCount[64] = {0};
		sprintf( strLevel, "%u", it->GetLevel() );
		sprintf( strProsperity, "%u", it->GetProsperity() );
		sprintf( strMemberCount, "%u", it->GetMemberCount() );

		AddToList( it->GetFamilyName(), strLevel, strProsperity, strMemberCount, 0xFFFFFFFF );
	}

	m_bIsSreachResult = false;
	CheckList();
}

void CUI_ID_FRAME_FamilyApply::InitialSearchResult()
{
	ClearValues();
	std::sort( m_vecSearchResultSet.begin(), m_vecSearchResultSet.end(), InfoCompare );

	for ( FamilySimpleInfoSetIt_t it = m_vecSearchResultSet.begin(); it != m_vecSearchResultSet.end(); it ++ )
	{
		char strLevel[64] = {0};
		char strProsperity[64] = {0};
		char strMemberCount[64] = {0};
		sprintf( strLevel, "%u", it->GetLevel() );
		sprintf( strProsperity, "%u", it->GetProsperity() );
		sprintf( strMemberCount, "%u", it->GetMemberCount() );

		AddToList( it->GetFamilyName(), strLevel, strProsperity, strMemberCount, 0xFFFFFFFF );
	}

	m_bIsSreachResult = true;
	CheckList();
}

void CUI_ID_FRAME_FamilyApply::ClearValues()
{
	m_vecSimpleInfoSet.clear();
	m_pID_LIST_GuildList->Clear();
	m_pID_LIST_Level->Clear();
	m_pID_LIST_Amount->Clear();
	m_pID_LIST_CDR->Clear();
	m_pID_LIST_Name->Clear();
}

void CUI_ID_FRAME_FamilyApply::AddToList( const char* familyName, const char* level, const char* prosperity, const char* memberCount, DWORD clr )
{
	ControlList::S_List	stItem;

	//家族名称
	stItem.SetData(familyName, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Name->AddItem(&stItem, NULL, false);
	stItem.clear();

	//等级
	stItem.SetData(level, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Level->AddItem(&stItem, NULL, false);
	stItem.clear();

	//繁荣度
	stItem.SetData(prosperity, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Amount->AddItem(&stItem, NULL, false);
	stItem.clear();

	//人数
	stItem.SetData(memberCount, 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CDR->AddItem(&stItem, NULL, false);
	stItem.clear();

	//选择特效
	stItem.SetData("", 0, NULL, clr);
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildList->AddItem(&stItem, NULL, false);
	stItem.clear();
	

}

void CUI_ID_FRAME_FamilyApply::CheckList()
{
	if( m_pID_LIST_GuildList->GetListItemCnt() > 0 )
	{
		m_pID_BUTTON_Apply->SetEnable(true);
		m_pID_LIST_GuildList->SetCurSelIndex(0);
		ID_LIST_GuildListOnListSelectChange( NULL, NULL );
	}
	else
	{
		m_pID_BUTTON_Apply->SetEnable(false);

		m_pID_TEXT_DengJi->SetText( "" );
		m_pID_TEXT_ZuZhang->SetText( "" );
		m_pID_TEXT_ZhiYe->SetText( "" );
		m_pID_TEXT_Announcement->SetText( "" );
		
	}
}

void CUI_ID_FRAME_FamilyApply::OnMsgQueryFamilyInfoAck( Msg *pMsg )
{
	if ( m_pID_FRAME_FamilyApply == NULL )
	{
		return;
	}
	

	MsgQueryFamilyInfoAck* msgAck = (MsgQueryFamilyInfoAck*)pMsg;

	if( m_mapFamilyInfoAck.find( msgAck->info.GetFamilyID() ) == m_mapFamilyInfoAck.end() )
	{
		m_mapFamilyInfoAck[msgAck->info.GetFamilyID()] = *msgAck;
	}

	char tmpStr[256] = {0};
	sprintf( tmpStr, "%u", /*msgAck->info.GetFamilyLevel()*/msgAck->nLeaderLv );
	m_pID_TEXT_DengJi->SetText( tmpStr );

	m_pID_TEXT_ZuZhang->SetText( msgAck->szLeaderName );
	m_pID_TEXT_ZhiYe->SetText( CountryFunction::GetProfessionByID( msgAck->nPosition ).c_str() );
	m_pID_TEXT_Announcement->SetText( msgAck->info.GetFamilyAim() );
}

// Frame
bool CUI_ID_FRAME_FamilyApply::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_FamilyApply::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_FamilyApply::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_FamilyApply::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;
	return true;
}
// Button 申请加入
bool CUI_ID_FRAME_FamilyApply::ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;

	//ControlList::S_List* item = s_CUI_ID_FRAME_AboutPeople.m_pID_LIST_PeopleName->GetListItem( s_CUI_ID_FRAME_AboutPeople.m_pID_LIST_TeamEffect->GetCurSelIndex() );
	//if ( !item )
	//{
	//	return;
	//}

	CPlayer* me = theHeroGame.GetPlayerMgr()->GetMe();
	if( me && me->GetFamilyID() > 0 )	//已近有家族了，就不能再申请了
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyAlreadyHave) );
		return true;
	}

	if ( thePlayerRole.GetLevel() < FamilyConfig::Instance().GetJoinSetting().GetLevelLimit() )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
			theXmlString.GetString(eText_FamilyLevelNotEnogh) );
		return true;
	}
	

	if ( m_bIsSreachResult )
	{
		int idx = m_pID_LIST_GuildList->GetCurSelIndex();
		if ( idx >= 0 && idx < m_vecSearchResultSet.size() )
		{
			//MsgJoinFamilyReq msg;
			//msg.nFamilyID = m_vecSearchResultSet[idx].GetFamilyID();
			//GettheNetworkInput().SendMsg(&msg);
			QueryFamilyInfoAckIt_t it = m_mapFamilyInfoAck.find( m_vecSearchResultSet[idx].GetFamilyID() );
			if ( it != m_mapFamilyInfoAck.end() && it->second.bLeadOnLine == false )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
					theXmlString.GetString(eText_FamilyManagerOffline) );
				return true;
			}

			s_CUI_ID_FRAME_GUILD_FamilyMessageBox.ShowAsRequestMsgSend();
			s_CUI_ID_FRAME_GUILD_FamilyMessageBox.SetRequestFamilyInfo( m_vecSearchResultSet[idx].GetFamilyID(), m_vecSearchResultSet[idx].GetFamilyName() );
		}
	}
	else
	{
		int idx = m_pID_LIST_GuildList->GetCurSelIndex();
		if ( idx >= 0 && idx < m_vecSimpleInfoSet.size() )
		{
			//MsgJoinFamilyReq msg;
			//msg.nFamilyID = m_vecSimpleInfoSet[idx].GetFamilyID();
			//GettheNetworkInput().SendMsg(&msg);
			QueryFamilyInfoAckIt_t it = m_mapFamilyInfoAck.find( m_vecSimpleInfoSet[idx].GetFamilyID() );
			if ( it != m_mapFamilyInfoAck.end() && it->second.bLeadOnLine == false )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Family, 
					theXmlString.GetString(eText_FamilyManagerOffline) );
				return true;
			}

			s_CUI_ID_FRAME_GUILD_FamilyMessageBox.ShowAsRequestMsgSend();
			s_CUI_ID_FRAME_GUILD_FamilyMessageBox.SetRequestFamilyInfo( m_vecSimpleInfoSet[idx].GetFamilyID(), m_vecSimpleInfoSet[idx].GetFamilyName() );
		}
	}

	return true;
}
// Button
bool CUI_ID_FRAME_FamilyApply::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;
	return true;
}
// List
void CUI_ID_FRAME_FamilyApply::ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;


	if ( m_bIsSreachResult )
	{
		int idx = m_pID_LIST_GuildList->GetCurSelIndex();
		if ( idx >= 0 && idx < m_vecSearchResultSet.size() )
		{
			QueryFamilyInfoAckIt_t it = m_mapFamilyInfoAck.find( m_vecSearchResultSet[idx].GetFamilyID() );
			if ( it != m_mapFamilyInfoAck.end() )
			{
				OnMsgQueryFamilyInfoAck( &it->second );
				return;
			}
			
			MsgQueryFamilyInfoReq msg;
			msg.nFamilyID = m_vecSearchResultSet[idx].GetFamilyID();
			GettheNetworkInput().SendMsg(&msg);
		}
	}
	else
	{
		int idx = m_pID_LIST_GuildList->GetCurSelIndex();
		if ( idx >= 0 && idx < m_vecSimpleInfoSet.size() )
		{
			QueryFamilyInfoAckIt_t it = m_mapFamilyInfoAck.find( m_vecSimpleInfoSet[idx].GetFamilyID() );
			if ( it != m_mapFamilyInfoAck.end() )
			{
				OnMsgQueryFamilyInfoAck( &it->second );
				return;
			}

			MsgQueryFamilyInfoReq msg;
			msg.nFamilyID = m_vecSimpleInfoSet[idx].GetFamilyID();
			GettheNetworkInput().SendMsg(&msg);
		}
	}
}
// List
void CUI_ID_FRAME_FamilyApply::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
}
// List
void CUI_ID_FRAME_FamilyApply::ID_LIST_CDROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
}
// List
void CUI_ID_FRAME_FamilyApply::ID_LIST_AmountOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
}

// Edit
void CUI_ID_FRAME_FamilyApply::ID_EDIT_GJZOnEditEnter( ControlObject* pSender, const char* szData )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
}

// List
void CUI_ID_FRAME_FamilyApply::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
}

void CUI_ID_FRAME_FamilyApply::ListScrollPosChanged( OUT ControlObject* pSender, int n )
{
	if ( s_CUI_ID_FRAME_FamilyApply.m_pID_FRAME_FamilyApply == NULL )
	{
		return;
	}
	//s_CUI_ID_FRAME_FamilyApply.m_pID_LIST_GuildList->SetScrollValue(n);
	s_CUI_ID_FRAME_FamilyApply.m_pID_LIST_Level->SetScrollValue(n);
	s_CUI_ID_FRAME_FamilyApply.m_pID_LIST_CDR->SetScrollValue(n);
	s_CUI_ID_FRAME_FamilyApply.m_pID_LIST_Amount->SetScrollValue(n);
	s_CUI_ID_FRAME_FamilyApply.m_pID_LIST_Name->SetScrollValue(n);
}

// Button 搜索
bool CUI_ID_FRAME_FamilyApply::ID_BUTTON_SearchOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;
	std::string words = m_pID_EDIT_GJZ->GetText();
	if ( !words.empty() )
	{
		m_vecSearchResultSet.clear();
		m_vecSimpleInfoSet.clear();

		CSystemFamily::Instance()->GetAllInfo(m_vecSimpleInfoSet);
		std::sort( m_vecSimpleInfoSet.begin(), m_vecSimpleInfoSet.end(), InfoCompare );

		for ( FamilySimpleInfoSetIt_t it = m_vecSimpleInfoSet.begin(); it != m_vecSimpleInfoSet.end(); it ++ )
		{
			std::string familyName = it->GetFamilyName();
			size_t idx = familyName.find( words.c_str() );
			if ( idx != std::string.npos )
			{
				m_vecSearchResultSet.push_back(*it);
			}
		}

		InitialSearchResult();
	}
	else
	{
		//如果为空直接显示
		InitialListValues();
	}
	
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FamilyApply::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FamilyApply.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FamilyApply.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

static void UIFamilyApply_OnVisibleChanged(ControlObject* pSender)
{
	if (pSender && !pSender->IsVisable())
		ImmAssociateContext( g_hWnd, NULL );
}

void OnSearchTextChanged( ControlObject* pSender, const char *szData )
{
	s_CUI_ID_FRAME_FamilyApply.ID_BUTTON_SearchOnButtonClick(pSender);
}

// 关连控件
bool CUI_ID_FRAME_FamilyApply::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FamilyApply, s_CUI_ID_FRAME_FamilyApplyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FamilyApply, s_CUI_ID_FRAME_FamilyApplyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_FamilyApply, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FamilyApplyID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyApply, ID_BUTTON_HELP, s_CUI_ID_FRAME_FamilyApplyID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyApply, ID_BUTTON_Apply, s_CUI_ID_FRAME_FamilyApplyID_BUTTON_ApplyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FamilyApply, ID_BUTTON_Cancel, s_CUI_ID_FRAME_FamilyApplyID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_FamilyApply, ID_LIST_GuildList, s_CUI_ID_FRAME_FamilyApplyID_LIST_GuildListOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_FamilyApply, ID_LIST_Level, s_CUI_ID_FRAME_FamilyApplyID_LIST_LevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_FamilyApply, ID_LIST_CDR, s_CUI_ID_FRAME_FamilyApplyID_LIST_CDROnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_FamilyApply, ID_LIST_Amount, s_CUI_ID_FRAME_FamilyApplyID_LIST_AmountOnListSelectChange );
	theUiManager.OnEditEnter( ID_FRAME_FamilyApply, ID_EDIT_GJZ, s_CUI_ID_FRAME_FamilyApplyID_EDIT_GJZOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_FamilyApply, ID_BUTTON_Search, s_CUI_ID_FRAME_FamilyApplyID_BUTTON_SearchOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_FamilyApply, ID_LIST_Name, s_CUI_ID_FRAME_FamilyApplyID_LIST_NameOnListSelectChange );

	m_pID_FRAME_FamilyApply = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FamilyApply );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_BUTTON_CLOSE );
	m_pID_TEXT_Announcement = (ControlText*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_TEXT_Announcement );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_BUTTON_HELP );
	m_pID_BUTTON_Apply = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_BUTTON_Apply );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_BUTTON_Cancel );
	m_pID_LIST_GuildList = (ControlList*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_LIST_GuildList );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_LIST_Level );
	m_pID_LIST_CDR = (ControlList*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_LIST_CDR );
	m_pID_LIST_Amount = (ControlList*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_LIST_Amount );
	m_pID_TEXT_ZuZhang = (ControlText*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_TEXT_ZuZhang );
	m_pID_TEXT_ZhiYe = (ControlText*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_TEXT_ZhiYe );
	m_pID_TEXT_DengJi = (ControlText*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_TEXT_DengJi );
	m_pID_EDIT_GJZ = (ControlEdit*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_EDIT_GJZ );
	m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_BUTTON_Search );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_FamilyApply, ID_LIST_Name );

	m_pID_EDIT_GJZ->SetOnVisibleChangedFun(UIFamilyApply_OnVisibleChanged);
	m_pID_BUTTON_Search->SetVisable(false);	//采用实时搜索，所以将按钮隐藏
	m_pID_EDIT_GJZ->SetTextChangedFun( OnSearchTextChanged );

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	assert( m_pID_FRAME_FamilyApply );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Announcement );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_Apply );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_LIST_GuildList );
	assert( m_pID_LIST_Level );
	assert( m_pID_LIST_CDR );
	assert( m_pID_LIST_Amount );
	assert( m_pID_TEXT_ZuZhang );
	assert( m_pID_TEXT_ZhiYe );
	assert( m_pID_TEXT_DengJi );
	assert( m_pID_EDIT_GJZ );
	assert( m_pID_BUTTON_Search );
	assert( m_pID_LIST_Name );

	if ( m_pID_LIST_GuildList->GetScrollBar() )
	{
		m_pID_LIST_GuildList->GetScrollBar()->SetUpdatePosFun(ListScrollPosChanged);
	}

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FamilyApply::_UnLoadUI()
{
	m_pID_FRAME_FamilyApply = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_LIST_GuildList = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_CDR = NULL;
	m_pID_LIST_Amount = NULL;
	m_pID_TEXT_ZuZhang = NULL;
	m_pID_TEXT_ZhiYe = NULL;
	m_pID_TEXT_DengJi = NULL;
	m_pID_EDIT_GJZ = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_LIST_Name = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FamilyApply.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FamilyApply::_IsVisable()
{
	if ( !m_pID_FRAME_FamilyApply )
		return false;
	return m_pID_FRAME_FamilyApply->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FamilyApply::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_FamilyApply )
		return;
	m_pID_FRAME_FamilyApply->SetVisable( bVisable );
	if ( bVisable )
	{
		InitialListValues();
	}

	if( bVisable )
	{
		// 设置焦点	开启输入法
		m_pID_EDIT_GJZ->SetActivate( true );
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
	{
		// 关闭输入法
		ImmAssociateContext( g_hWnd, NULL );
	}
	
}
