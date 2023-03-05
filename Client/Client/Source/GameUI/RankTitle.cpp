/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\RankTitle.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "RankTitle.h"
#include "BasePropertyBGFrame.h"
#include "RankTitleConfig.h"
#include "PlayerRole.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "UiTitle.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"

CUI_ID_FRAME_RankTitle s_CUI_ID_FRAME_RankTitle;

MAP_FRAME_RUN( s_CUI_ID_FRAME_RankTitle, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_RankTitle, OnFrameRender )

MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_LIST_RankNameOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_BUTTON_ShowTitleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_BUTTON_HideTitleOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_LISTIMG_BuffOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_LISTIMG_BuffOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_LISTIMG_BuffOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_LISTIMG_BuffOnIconButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_BUTTON_GetSalaryOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_RankTitle, ID_BUTTON_AdvancementOnButtonClick )
CUI_ID_FRAME_RankTitle::CUI_ID_FRAME_RankTitle()
{
	// Member
	m_pID_FRAME_RankTitle = NULL;
	m_pID_LIST_RankName = NULL;
	m_pID_TEXT_CurRank = NULL;
	m_pID_BUTTON_ShowTitle = NULL;
	m_pID_BUTTON_HideTitle = NULL;
	m_pID_TEXT_Introduction = NULL;
	m_pID_TEXT_CurSalary = NULL;
	m_pID_LISTIMG_Buff = NULL;
	m_pID_TEXT_CurHonour = NULL;
	m_pID_TEXT_NeedHonour = NULL;
	m_pID_TEXT_NeedMoney = NULL;
	m_pID_BUTTON_GetSalary = NULL;
	m_pID_BUTTON_Advancement = NULL;

}
CUI_ID_FRAME_RankTitle::~CUI_ID_FRAME_RankTitle()
{
}
// Frame
bool CUI_ID_FRAME_RankTitle::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_RankTitle::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_RankTitle::ID_LIST_RankNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if ( !m_pID_FRAME_RankTitle )
		return;
	RefreshSelectChange();
}
// Button
bool CUI_ID_FRAME_RankTitle::ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankTitle )
		return false;

	if ( thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId < 0 )
		return true;
	if ( theHeroGame.GetPlayerMgr()->GetMe()->IsShowRankTitle() &&
		thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId == theHeroGame.GetPlayerMgr()->GetMe()->GetRankTitleId() )
		return true;

	MsgShowRankTitle msg;
	msg.bshowTitle = true;
	msg.shCurTitleId = thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId;
	GettheNetworkInput().SendMsg(&msg);

	theHeroGame.GetPlayerMgr()->GetMe()->ShowRankTitle(true);
	theHeroGame.GetPlayerMgr()->GetMe()->SetRankTitleId(msg.shCurTitleId);
	//s_CUI_ID_FRAME_Title.ID_BUTTON_HideTitleOnButtonClick(NULL);
	return true;
}
// Button
bool CUI_ID_FRAME_RankTitle::ID_BUTTON_HideTitleOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankTitle )
		return false;

	if ( thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId < 0 )
		return true;
	if ( !theHeroGame.GetPlayerMgr()->GetMe()->IsShowRankTitle() )
		return true;

	MsgShowRankTitle msg;
	msg.bshowTitle = false;
	GettheNetworkInput().SendMsg(&msg);

	theHeroGame.GetPlayerMgr()->GetMe()->ShowRankTitle(false);
	theHeroGame.GetPlayerMgr()->GetMe()->SetRankTitleId(msg.shCurTitleId);

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_RankTitle::ID_LISTIMG_BuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_RankTitle::ID_LISTIMG_BuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_RankTitle::ID_LISTIMG_BuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_RankTitle::ID_LISTIMG_BuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_RankTitle::ID_BUTTON_GetSalaryOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankTitle )
		return false;

	MsgAskGetSalary msg;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}
// Button
bool CUI_ID_FRAME_RankTitle::ID_BUTTON_AdvancementOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_RankTitle )
		return false;

	ControlList::S_List* pItem = m_pID_LIST_RankName->GetCurSelItem();
	if ( !pItem )
		return true;
	MsgAskAdvancement msg;
	msg.shTitleId = pItem->m_nID;
	GettheNetworkInput().SendMsg( &msg );
	return true;
}

// 装载UI
bool CUI_ID_FRAME_RankTitle::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\RankTitle.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\RankTitle.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_RankTitle::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_RankTitle, s_CUI_ID_FRAME_RankTitleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_RankTitle, s_CUI_ID_FRAME_RankTitleOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_RankTitle, ID_LIST_RankName, s_CUI_ID_FRAME_RankTitleID_LIST_RankNameOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_RankTitle, ID_BUTTON_ShowTitle, s_CUI_ID_FRAME_RankTitleID_BUTTON_ShowTitleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankTitle, ID_BUTTON_HideTitle, s_CUI_ID_FRAME_RankTitleID_BUTTON_HideTitleOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_RankTitle, ID_LISTIMG_Buff, s_CUI_ID_FRAME_RankTitleID_LISTIMG_BuffOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_RankTitle, ID_LISTIMG_Buff, s_CUI_ID_FRAME_RankTitleID_LISTIMG_BuffOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_RankTitle, ID_LISTIMG_Buff, s_CUI_ID_FRAME_RankTitleID_LISTIMG_BuffOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_RankTitle, ID_LISTIMG_Buff, s_CUI_ID_FRAME_RankTitleID_LISTIMG_BuffOnIconButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankTitle, ID_BUTTON_GetSalary, s_CUI_ID_FRAME_RankTitleID_BUTTON_GetSalaryOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_RankTitle, ID_BUTTON_Advancement, s_CUI_ID_FRAME_RankTitleID_BUTTON_AdvancementOnButtonClick );

	m_pID_FRAME_RankTitle = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_RankTitle );
	m_pID_LIST_RankName = (ControlList*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_LIST_RankName );
	m_pID_TEXT_CurRank = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_CurRank );
	m_pID_BUTTON_ShowTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_BUTTON_ShowTitle );
	m_pID_BUTTON_HideTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_BUTTON_HideTitle );
	m_pID_TEXT_Introduction = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_Introduction );
	m_pID_TEXT_CurSalary = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_CurSalary );
	m_pID_LISTIMG_Buff = (ControlListImage*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_LISTIMG_Buff );
	m_pID_TEXT_CurHonour = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_CurHonour );
	m_pID_TEXT_NeedHonour = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_NeedHonour );
	m_pID_TEXT_NeedMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_TEXT_NeedMoney );
	m_pID_BUTTON_GetSalary = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_BUTTON_GetSalary );
	m_pID_BUTTON_Advancement = (ControlButton*)theUiManager.FindControl( ID_FRAME_RankTitle, ID_BUTTON_Advancement );
	assert( m_pID_FRAME_RankTitle );
	assert( m_pID_LIST_RankName );
	assert( m_pID_TEXT_CurRank );
	assert( m_pID_BUTTON_ShowTitle );
	assert( m_pID_BUTTON_HideTitle );
	assert( m_pID_TEXT_Introduction );
	assert( m_pID_TEXT_CurSalary );
	assert( m_pID_LISTIMG_Buff );
	assert( m_pID_TEXT_CurHonour );
	assert( m_pID_TEXT_NeedHonour );
	assert( m_pID_TEXT_NeedMoney );
	assert( m_pID_BUTTON_GetSalary );
	assert( m_pID_BUTTON_Advancement );

	m_pID_FRAME_RankTitle->SetFather(s_CUI_ID_FRAME_BasePropertyBGFrame.GetFrame());
	_SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_RankTitle::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\RankTitle.meui" );
}
// 是否可视
bool CUI_ID_FRAME_RankTitle::_IsVisable()
{
	return m_pID_FRAME_RankTitle->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_RankTitle::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_RankTitle->SetVisable( bVisable );

	if ( bVisable )
	{
		Refresh();
	}
	
}

void CUI_ID_FRAME_RankTitle::Refresh()
{
	if ( !m_pID_FRAME_RankTitle )
		return;

	short shCurTitleId = thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId;

	m_pID_LIST_RankName->Clear();

	RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
	int nTitleShowCount = theRankTitleConfig.GetShowCount();

	for ( int i = /*vecTitle.size()*/nTitleShowCount - 1; i >= 0; i-- )
	{
		DWORD dwColor = 0xff33cc33;
		if ( shCurTitleId < vecTitle[i].nId )
			dwColor = 0xff808080;

		ControlList::S_List sItem;
		sItem.SetData( vecTitle[i].strName.c_str(), vecTitle[i].nId, 0, dwColor );
		sItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_RankName->AddItem( &sItem );
	}

	m_pID_TEXT_CurRank->SetText("");
	int nShowCount = m_pID_LIST_RankName->GetItemShowCount();
	if ( shCurTitleId != -1 && shCurTitleId < /*vecTitle.size()*/nTitleShowCount )
	{
		m_pID_TEXT_CurRank->SetText( vecTitle[shCurTitleId].strName );
		m_pID_LIST_RankName->SetCurSelIndex( /*vecTitle.size()*/nTitleShowCount - 1 - shCurTitleId );

		int nStart = /*vecTitle.size()*/nTitleShowCount - shCurTitleId - nShowCount + 2;
		if ( nStart < 0 )
			nStart = 0;
		m_pID_LIST_RankName->SetStartIndex( nStart );
	}
	else
	{
		m_pID_LIST_RankName->SetCurSelIndex( /*vecTitle.size()*/nTitleShowCount - 1 );

		int nStart = /*vecTitle.size()*/nTitleShowCount - nShowCount + 2;
		if ( nStart < 0 )
			nStart = 0;
		m_pID_LIST_RankName->SetStartIndex( nStart );
	}
	
	RefreshSelectChange();
}

void CUI_ID_FRAME_RankTitle::RefreshSelectChange()
{
	if ( !m_pID_FRAME_RankTitle )
		return;

	m_pID_TEXT_Introduction->SetText("");
	m_pID_TEXT_CurSalary->SetText("");
	m_pID_LISTIMG_Buff->Clear();
	m_pID_BUTTON_GetSalary->SetEnable( false );
	m_pID_BUTTON_Advancement->SetEnable( false );
	m_pID_TEXT_CurHonour->SetText("");
	m_pID_TEXT_NeedHonour->SetText("");
	m_pID_TEXT_NeedMoney->SetText("");

	ControlList::S_List* pItem = m_pID_LIST_RankName->GetCurSelItem();
	if ( !pItem )
		return;

	short shCurTitleId = thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.shCurRankTitleId;
	RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
	int nShowCount = theRankTitleConfig.GetShowCount();

	if ( pItem->m_nID < 0 || pItem->m_nID >= /*vecTitle.size()*/nShowCount )
		return;

	m_pID_TEXT_Introduction->SetText( vecTitle[ pItem->m_nID ].strDescription );

	std::string text;
	if ( pItem->m_nID < RankTitleConfig::ED_AnYuan )
		thePlayerRole.GetGSCStringFromJiaoZi( vecTitle[ pItem->m_nID ].nCurSalary, text );
	else
		thePlayerRole.GetGSCStringFromMoney( vecTitle[ pItem->m_nID ].nCurSalary, text );
	m_pID_TEXT_CurSalary->SetText( text );

	ItemDefine::SItemStatus* pItemStatus = NULL;
	pItemStatus = GettheItemDetail().GetStatus( vecTitle[ pItem->m_nID ].nBuffId, vecTitle[ pItem->m_nID ].nBuffLevel );

	if ( pItemStatus )
	{
		ControlIconDrag::S_ListImg stItem;
		stItem.SetData( vecTitle[ pItem->m_nID ].nBuffId, vecTitle[ pItem->m_nID ].nBuffLevel, eIcon_Enable, true, eTipFlag_Status );
		m_pID_LISTIMG_Buff->SetItem( &stItem );
	}

	m_pID_TEXT_CurHonour->SetText(thePlayerRole.m_charinfo.baseinfo.liveinfo.honour);

	if ( shCurTitleId < pItem->m_nID )
	{
		DWORD dwColor = 0xffffffff;
		if ( thePlayerRole.m_charinfo.baseinfo.liveinfo.honour < vecTitle[ pItem->m_nID ].nNeedHonour )
			dwColor = 0xffff0000;

		m_pID_TEXT_NeedHonour->SetText( vecTitle[ pItem->m_nID ].nNeedHonour, dwColor );

		thePlayerRole.GetGSCStringFromJiaoZi( vecTitle[ pItem->m_nID ].nNeedMoney, text );
		dwColor = 0xffffffff;
		if( !thePlayerRole.HaveEnoughMoney( vecTitle[ pItem->m_nID ].nNeedMoney ) )
			dwColor = 0xffff0000;
		
		m_pID_TEXT_NeedMoney->SetText( text, dwColor );

		if ( thePlayerRole.m_charinfo.baseinfo.liveinfo.honour >= vecTitle[ pItem->m_nID ].nNeedHonour && thePlayerRole.HaveEnoughMoney( vecTitle[ pItem->m_nID ].nNeedMoney ) )
		{
			if ( pItem->m_nID == shCurTitleId + 1 )
				m_pID_BUTTON_Advancement->SetEnable( true );
		}
	}

	if ( pItem->m_nID == shCurTitleId && thePlayerRole.GetCharInfo2().otherdataclient.rankTitle.bGetSalary == 0 )
		m_pID_BUTTON_GetSalary->SetEnable( true );
	
}