/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\HuntingQuest.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "HuntingQuest.h"
#include "HuntingQuestConfig.h"
#include "PlayerRole.h"
#include "QuestManager.h"
#include "IconManagerClient.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "Common.h"
#include "MessageBox.h"
#include "NpcCoord.h"
#include "MeTerrain/stdafx.h"
#include "CountryDefine.h"
#include "script_manager.h"
#include "TitleConfig.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_Hunting s_CUI_ID_FRAME_Hunting;

MAP_FRAME_RUN( s_CUI_ID_FRAME_Hunting, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Hunting, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_BUTTON_CLOSEOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LIST_NameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LIST_LevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LIST_StateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LIST_QuestOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_BUTTON_FreshGoldOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_BUTTON_FreshFreeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_BUTTON_FreshMoneyOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_RewardOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_RewardOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_RewardOnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_SecondItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_SecondItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_SecondItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_SecondItemOnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_ThirdItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_ThirdItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_ThirdItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_ThirdItemOnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_FourItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_FourItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_FourItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_LISTIMG_FourItemOnIconButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Hunting, ID_BUTTON_AccpetQuestOnButtonClick )
CUI_ID_FRAME_Hunting::CUI_ID_FRAME_Hunting()
{
	// Member
	m_pID_FRAME_Hunting = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LIST_Name = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_State = NULL;
	m_pID_LIST_Quest = NULL;
	m_pID_BUTTON_FreshGold = NULL;
	m_pID_TEXT_Gold = NULL;
	m_pID_BUTTON_FreshFree = NULL;
	m_pID_BUTTON_FreshMoney = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_TaskDepict = NULL;
	m_pID_TEXT_AdviseLevel = NULL;
	m_pID_TEXT_TaskInfo = NULL;
	m_pID_TEXT_Award = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_LISTIMG_SecondItem = NULL;
	m_pID_LISTIMG_ThirdItem = NULL;
	m_pID_LISTIMG_FourItem = NULL;
	m_pID_BUTTON_AccpetQuest = NULL;
	m_pID_TEXT_Aim = NULL;

	nLeftTime = 0;
	dwStartTime = 0;
}
CUI_ID_FRAME_Hunting::~CUI_ID_FRAME_Hunting()
{
}
// Frame
bool CUI_ID_FRAME_Hunting::OnFrameRun()
{
	if ( !IsVisable() )
		return true;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( pMe )
	{
		float fMeX,fMeY,fMeZ;			
		pMe->GetPos( &fMeX, &fMeY, &fMeZ );
		float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
		if( dist > 12.0f )			//距离太远
		{
			SetVisable( false );
		}
	}

	if ( nLeftTime == 0 )
		return true;

	int n = (timeGetTime() - dwStartTime)/1000;
	int nTime = nLeftTime - n;

	if ( nTime >= 0 )
	{
		int hour = nTime / 3600;
		int minute = (nTime - hour * 3600) / 60;
		int second = nTime % 60;

		char szText[32] = {0};
		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%02d:%02d", minute, second );

		//m_pID_BUTTON_FreshFree->SetEnable( false );
		m_pID_BUTTON_FreshFree->SetCaption( szText );
	}
	else
	{
		m_pID_BUTTON_FreshFree->SetEnable( true );
		m_pID_BUTTON_FreshFree->SetCaption( "" );
		nLeftTime = 0;
	}

	return true;
}
bool CUI_ID_FRAME_Hunting::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Hunting::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// List
void CUI_ID_FRAME_Hunting::ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Hunting::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Hunting::ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_Hunting::ID_LIST_QuestOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	InitIntroduce();
	SetIntroduce();
}
// Button
bool CUI_ID_FRAME_Hunting::ID_BUTTON_FreshGoldOnButtonClick( ControlObject* pSender )
{
	if ( !HasUnAcceptQuest() )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_Hunting_CannotRefresh), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return true;
	}

	int nPlayerGold = thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao);
	int nGold = theHuntingQuestConfig.GetFreshGold();

	if ( nPlayerGold < nGold )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_Hunting_NoJinPiao), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return true;
	}

	MsgReFreshHunting msg;
	msg.eType = MsgReFreshHunting::eFreshType_Gold;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}
// Button
bool CUI_ID_FRAME_Hunting::ID_BUTTON_FreshFreeOnButtonClick( ControlObject* pSender )
{
	if ( !HasUnAcceptQuest() )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_Hunting_CannotRefresh), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return true;
	}

	MsgReFreshHunting msg;
	msg.eType = MsgReFreshHunting::eFreshType_Free;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}
// Button
bool CUI_ID_FRAME_Hunting::ID_BUTTON_FreshMoneyOnButtonClick( ControlObject* pSender )
{
	if ( !HasUnAcceptQuest() )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_Hunting_CannotRefresh), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return true;
	}

	int nPlayerMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
	int nMoney = theHuntingQuestConfig.GetFreshMoney();

	if ( nPlayerMoney < nMoney )
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_BargainFailed_NoMoney), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		return true;
	}

	MsgReFreshHunting msg;
	msg.eType = MsgReFreshHunting::eFreshType_Money;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_ThirdItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_ThirdItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_ThirdItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_ThirdItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_FourItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_FourItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_FourItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_Hunting::ID_LISTIMG_FourItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_Hunting::ID_BUTTON_AccpetQuestOnButtonClick( ControlObject* pSender )
{
	int nIndex = m_pID_LIST_Quest->GetCurSelIndex();
	if ( nIndex < 0 )
		return true;
	if ( !m_pID_LIST_Quest->GetCurSelItem() )
		return true;

	int nQuestId = m_pID_LIST_Quest->GetCurSelItem()->m_nID;

	MsgHuntingAcceptQuest msg;
	msg.nId = nQuestId;
	GettheNetworkInput().SendMsg( &msg );

	return true;
}

// 装载UI
bool CUI_ID_FRAME_Hunting::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\HuntingQuest.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\HuntingQuest.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Hunting::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Hunting, s_CUI_ID_FRAME_HuntingOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Hunting, s_CUI_ID_FRAME_HuntingOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Hunting, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_HuntingID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_Hunting, ID_LIST_Name, s_CUI_ID_FRAME_HuntingID_LIST_NameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Hunting, ID_LIST_Level, s_CUI_ID_FRAME_HuntingID_LIST_LevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Hunting, ID_LIST_State, s_CUI_ID_FRAME_HuntingID_LIST_StateOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_Hunting, ID_LIST_Quest, s_CUI_ID_FRAME_HuntingID_LIST_QuestOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_Hunting, ID_BUTTON_FreshGold, s_CUI_ID_FRAME_HuntingID_BUTTON_FreshGoldOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Hunting, ID_BUTTON_FreshFree, s_CUI_ID_FRAME_HuntingID_BUTTON_FreshFreeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Hunting, ID_BUTTON_FreshMoney, s_CUI_ID_FRAME_HuntingID_BUTTON_FreshMoneyOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hunting, ID_LISTIMG_Reward, s_CUI_ID_FRAME_HuntingID_LISTIMG_RewardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hunting, ID_LISTIMG_Reward, s_CUI_ID_FRAME_HuntingID_LISTIMG_RewardOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hunting, ID_LISTIMG_Reward, s_CUI_ID_FRAME_HuntingID_LISTIMG_RewardOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Hunting, ID_LISTIMG_Reward, s_CUI_ID_FRAME_HuntingID_LISTIMG_RewardOnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hunting, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_SecondItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hunting, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_SecondItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hunting, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_SecondItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Hunting, ID_LISTIMG_SecondItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_SecondItemOnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hunting, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_ThirdItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hunting, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_ThirdItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hunting, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_ThirdItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Hunting, ID_LISTIMG_ThirdItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_ThirdItemOnIconButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_Hunting, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_FourItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Hunting, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_FourItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Hunting, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_FourItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Hunting, ID_LISTIMG_FourItem, s_CUI_ID_FRAME_HuntingID_LISTIMG_FourItemOnIconButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Hunting, ID_BUTTON_AccpetQuest, s_CUI_ID_FRAME_HuntingID_BUTTON_AccpetQuestOnButtonClick );

	m_pID_FRAME_Hunting = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Hunting );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hunting, ID_BUTTON_CLOSE );
	m_pID_LIST_Name = (ControlList*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LIST_Name );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LIST_Level );
	m_pID_LIST_State = (ControlList*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LIST_State );
	m_pID_LIST_Quest = (ControlList*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LIST_Quest );
	m_pID_BUTTON_FreshGold = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hunting, ID_BUTTON_FreshGold );
	m_pID_TEXT_Gold = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_Gold );
	m_pID_BUTTON_FreshFree = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hunting, ID_BUTTON_FreshFree );
	m_pID_BUTTON_FreshMoney = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hunting, ID_BUTTON_FreshMoney );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_Money );
	m_pID_TEXT_TaskDepict = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_TaskDepict );
	m_pID_TEXT_AdviseLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_AdviseLevel );
	m_pID_TEXT_TaskInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_TaskInfo );
	m_pID_TEXT_Award = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_Award );
	m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LISTIMG_Reward );
	m_pID_LISTIMG_SecondItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LISTIMG_SecondItem );
	m_pID_LISTIMG_ThirdItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LISTIMG_ThirdItem );
	m_pID_LISTIMG_FourItem = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Hunting, ID_LISTIMG_FourItem );
	m_pID_BUTTON_AccpetQuest = (ControlButton*)theUiManager.FindControl( ID_FRAME_Hunting, ID_BUTTON_AccpetQuest );
	m_pID_TEXT_Aim = (ControlText*)theUiManager.FindControl( ID_FRAME_Hunting, ID_TEXT_Aim );

	assert( m_pID_FRAME_Hunting );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LIST_Name );
	assert( m_pID_LIST_Level );
	assert( m_pID_LIST_State );
	assert( m_pID_LIST_Quest );
	assert( m_pID_BUTTON_FreshGold );
	assert( m_pID_TEXT_Gold );
	assert( m_pID_BUTTON_FreshFree );
	assert( m_pID_BUTTON_FreshMoney );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_TaskDepict );
	assert( m_pID_TEXT_AdviseLevel );
	assert( m_pID_TEXT_TaskInfo );
	assert( m_pID_TEXT_Award );
	assert( m_pID_LISTIMG_Reward );
	assert( m_pID_LISTIMG_SecondItem );
	assert( m_pID_LISTIMG_ThirdItem );
	assert( m_pID_LISTIMG_FourItem );
	assert( m_pID_BUTTON_AccpetQuest );
	assert( m_pID_TEXT_Aim );

	m_pID_LIST_Name->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_Name->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_Name->SetCurSelIndex(-1);

	m_pID_LIST_Level->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_Level->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_Level->SetCurSelIndex(-1);

	m_pID_LIST_State->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_State->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_State->SetCurSelIndex(-1);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Hunting::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\HuntingQuest.meui" );
}
// 是否可视
bool CUI_ID_FRAME_Hunting::_IsVisable()
{
	if ( !m_pID_FRAME_Hunting )
		return false;
	return m_pID_FRAME_Hunting->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Hunting::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Hunting )
		return;
	m_pID_FRAME_Hunting->SetVisable( bVisable );

	if ( bVisable )
	{
		MsgHuntingAskForList msg;
		GettheNetworkInput().SendMsg( &msg );

		SetReFreshGoldMoney();
		m_pID_BUTTON_FreshFree->SetEnable( true );
		m_pID_BUTTON_FreshFree->SetCaption( "" );
	}
}

void CUI_ID_FRAME_Hunting::SetReFreshGoldMoney()
{
	if ( !m_pID_TEXT_Gold || !m_pID_TEXT_Money )
		return;
	m_pID_TEXT_Gold->SetText("");
	m_pID_TEXT_Money->SetText("");

	int nGold = theHuntingQuestConfig.GetFreshGold();
	int nMoney = theHuntingQuestConfig.GetFreshMoney();

	std::string text;
	thePlayerRole.GetGSCStringFromMoney( nMoney, text );
	m_pID_TEXT_Money->SetText( text );

	std::stringstream str;
	str.str("");
	str << nGold << "{#1104} ";

	text = str.str();
	m_pID_TEXT_Gold->SetText( text );
}

void CUI_ID_FRAME_Hunting::SetLeftTime( int time )
{
	nLeftTime = time;

	if ( IsVisable() )
	{
		if ( nLeftTime > 0 )
			m_pID_BUTTON_FreshFree->SetEnable( false );
		else
		{
			m_pID_BUTTON_FreshFree->SetEnable( true );
			m_pID_BUTTON_FreshFree->SetCaption( "" );
		}
	}
}

void CUI_ID_FRAME_Hunting::Refresh()
{
	Init();
	SetListInfo();
	SetIntroduce();
}

void CUI_ID_FRAME_Hunting::Init()
{
	m_pID_LIST_Name->Clear();
	m_pID_LIST_Level->Clear();
	m_pID_LIST_State->Clear();
	m_pID_LIST_Quest->Clear();

	InitIntroduce();
}

void CUI_ID_FRAME_Hunting::InitIntroduce()
{
	m_pID_TEXT_TaskDepict->SetText("");
	m_pID_TEXT_AdviseLevel->SetText("");
	m_pID_TEXT_TaskInfo->SetText("");
	m_pID_TEXT_Award->SetText("");
	m_pID_LISTIMG_Reward->Clear();
	m_pID_LISTIMG_SecondItem->Clear();
	m_pID_LISTIMG_ThirdItem->Clear();
	m_pID_LISTIMG_FourItem->Clear();

	m_pID_BUTTON_AccpetQuest->SetEnable( true );
}

bool SortByLevel( const int& id1, const int& id2 )
{
	SQuest* pQuest1 = theQuestManager.GetQuest( id1 );
	SQuest* pQuest2 = theQuestManager.GetQuest( id2 );

	if ( pQuest1 && pQuest2 )
	{
		return pQuest1->GetPlayerReceiveQuestLevel() < pQuest2->GetPlayerReceiveQuestLevel();
	}

	return false;
}

bool SortByAccept( const int& id1, const int& id2 )
{
	CPlayerRole::QuestInfo* pInfo1 = thePlayerRole.FindQuestInfoById( id1 );
	CPlayerRole::QuestInfo* pInfo2 = thePlayerRole.FindQuestInfoById( id2 );
	bool IsInfo1Active = false;
	bool IsInfo2Active = false;

	if ( pInfo1 )
	{
		IsInfo1Active = theQuestManager.IsQuestActive( pInfo1->chState );
	}
	if ( pInfo2 )
	{
		IsInfo2Active = theQuestManager.IsQuestActive( pInfo2->chState );
	}

	if ( IsInfo1Active && !IsInfo2Active )
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void CUI_ID_FRAME_Hunting::SetListInfo()
{
	ControlList::S_List stList;

	char szText[128] = {0};

	std::vector< int > vecIds;
	vecIds.resize( MaxCount_Show, 0 );

	int nCount = 0;
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i] > 0 )
		{
			vecIds[nCount] =  thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i];
			nCount++;
		}

		if ( nCount == MaxCount_Show )
			break;
	}

	std::sort( vecIds.begin(), vecIds.end(), SortByLevel );
	std::sort( vecIds.begin(), vecIds.end(), SortByAccept );

	for ( int i = 0; i < MaxCount_Show; i++ )
	{
		int nQuestId = vecIds[i];
		if ( nQuestId <= 0 )
			continue;
		HuntingQuestConfig::SData* pData = theHuntingQuestConfig.GetBaseDataById( nQuestId );
		if ( !pData )
			continue;
		SQuest* pQuest = theQuestManager.GetQuest( nQuestId );
		if(!pQuest || (pQuest->Country !=0 &&  pQuest->Country != thePlayerRole.GetCountry()) )
			continue;

		stList.SetData( pQuest->GetQuestName() );
		stList.setColor( S_IconInfoHero::GetQualityColor( pData->nQuality ) );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Name->AddItem( &stList );

		stList.clear();
		memset(szText, 0, sizeof(szText));

		MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d", pQuest->GetPlayerReceiveQuestLevel() );
		stList.SetData( szText );
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_Level->AddItem( &stList );

		stList.clear();
		CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
		if ( !pInfo || !theQuestManager.IsQuestActive(pInfo->chState) )
		{
			stList.SetData( theXmlString.GetString( eText_Hunting_UnAccept ) );
			stList.setColor( Color_Config.getColor( CC_PetColor_Red ) );
		}
		else
		{
			stList.SetData( theXmlString.GetString( eText_Hunting_Accept ) );
		}
		stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
		m_pID_LIST_State->AddItem( &stList );

		stList.clear();
		stList.SetData("", nQuestId );
		m_pID_LIST_Quest->AddItem( &stList );
	}
	
	m_pID_LIST_Quest->SetCurSelIndex( 0 );
}

void CUI_ID_FRAME_Hunting::SetIntroduce()
{
	int nIndex = m_pID_LIST_Quest->GetCurSelIndex();
	if ( nIndex < 0 )
		return;
	if ( !m_pID_LIST_Quest->GetCurSelItem() )
		return;
	int nQuestId = m_pID_LIST_Quest->GetCurSelItem()->m_nID;

	HuntingQuestConfig::SData* pData = theHuntingQuestConfig.GetBaseDataById( nQuestId );
	if ( !pData )
		return;
	SQuest* pQuest = theQuestManager.GetQuest( nQuestId );
	if ( !pQuest )
		return;

	m_pID_TEXT_AdviseLevel->SetText( pData->nAdviseLevel );

	std::vector<UiCallbackDataBase*> CallBackDataArr;

	//任务描述
	std::string infoStr = pQuest->GetQuestInfo();
	CallBackDataArr.clear();
	NpcCoord::getInstance()->addNpcHyberForText( infoStr, NpcCoord::eQuestId, nQuestId,pQuest->ReplyTargetId, &CallBackDataArr );
	m_pID_TEXT_TaskDepict->SetText( infoStr, 0, &CallBackDataArr );

	// npc
	std::string npc = pQuest->GetRewardNpcName();
	const NpcCoordInfo *pNpcInfo = NpcCoord::getInstance()->getNpcCoord( pQuest->GetRewardNpcName() );
	if (pNpcInfo)
	{
		char cTip[256] = {0};
		CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(pNpcInfo->_mapId);
		if (pTile)
		{
			sprintf(cTip,"%s(%d,%d)",pTile->GetTileName(),(int)pNpcInfo->_pfMapX,(int)pNpcInfo->_pfMapY);
			m_pID_TEXT_TaskInfo->setTip(cTip);
			m_pID_TEXT_TaskInfo->setShowTip(true);
		}
	}
	NpcCoord::getInstance()->addNpcHyber(npc);
	m_pID_TEXT_TaskInfo->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	m_pID_TEXT_TaskInfo->SetText(npc);

	//任务奖励
	std::string strReward;
	strReward.clear();
	GetRewardItemInfo(pQuest,strReward);
	CallBackDataArr.clear();
	NpcCoord::getInstance()->addNpcHyberForText( strReward, NpcCoord::eQuestId, nQuestId,pQuest->ReplyTargetId, &CallBackDataArr );
	m_pID_TEXT_Award->SetText(strReward.c_str());

	//任务需求
	std::string strRequire;
	strRequire.clear();
	GetNeedItemInfo(pQuest,strRequire);
	CallBackDataArr.clear();
	NpcCoord::getInstance()->addNpcHyberForText( strRequire, NpcCoord::eQuestId, nQuestId,pQuest->ReplyTargetId, &CallBackDataArr );
	m_pID_TEXT_Aim->SetText(strRequire.c_str());

	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
	if ( pInfo && theQuestManager.IsQuestActive(pInfo->chState) )
		m_pID_BUTTON_AccpetQuest->SetEnable( false );
}

void CUI_ID_FRAME_Hunting::GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem)
{
	if(!pQuest)
		return;

	// 任务奖励
	SQuestReward *pReward = NULL;
	for ( int n=0; n<pQuest->stReward.size(); n++ )
	{
		pReward = &pQuest->stReward[n];
		switch( pReward->byType )
		{
		case SQuest::eReward_Money:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(money, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskGold);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_ScriptExp://脚本经验
			{
				// 各个值不同 
				char szWord[256] = {0};
				switch(pReward->Value)
				{
				case 1:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp1));
					break;
				case 2:
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskScriptExp),theXmlString.GetString(eText_Quest_ScriptExp2));
					break;
				}
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Exp:
			{
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					//计算经验值加成
					/*if(thePlayerRole.IsInWeakCountry())
						RewardValue = RewardValue*1.05;
					else if(thePlayerRole.IsInStrongCountry())
						RewardValue = RewardValue;
					else if(thePlayerRole.GetCountry() != CountryDefine::Country_Init)
						RewardValue = RewardValue * 1.1;*/

					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),RewardValue);
					strRewardItem += "\n";
					strRewardItem += szWord;
				}
				else
				{
					try
					{
						char filename[MAX_PATH] = {0};
						sprintf(filename, "%s/Data/Quest/CalculateExp.string", GetRootPath());

						try
						{
							//
							// 经验计算
							//
							LuaFunction<const char*> CalcExp( ScriptManager::instance().getLuaStateOwner(filename), "CalcExp" );
							const char* pszRewardValue = CalcExp( pQuest->Id, pQuest->RankId, thePlayerRole.GetLevel() );

							// 空指针不能进行std::string的比较
							if ( pszRewardValue && ( std::string("0") != pszRewardValue ) )
							{
								if(pszRewardValue != NULL)
								{
									int nValue = 0;
									//if(sscanf_s(RewardValue,"%d",&nValue) == 1)
									{
										nValue = atoi(pszRewardValue);
										char szWord[256] = {0};
										MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskExp),nValue);
										strRewardItem += "\n";
										strRewardItem += szWord;
									}
								}
								//*m_pID_TEXT_Exp = pszRewardValue;
							}
						}
						catch (LuaPlus::LuaException &e)
						{
							assert( 0 && "calculateexp.string" );
							::OutputDebugString(e.GetErrorMessage());
						}
					}
					catch (LuaPlus::LuaException &e)
					{
						assert( 0 && "calculateexp.string" );
						::OutputDebugString(e.GetErrorMessage());
					}

				}

			}
			break;
		case SQuest::eReward_CountryMoney:
			{
				//奖励国家资金
				int RewardValue = pReward->Value;
				if (0 != RewardValue)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromMoney(RewardValue, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_CountryMoney);
					strRewardItem += text.c_str();
				}
			}
			break;
		case SQuest::eReward_SkillExp:
			{
				int  nRewardValue = pReward->Value;
				if(0 != nRewardValue)
				{
					char szWord[256] = {0};
					MeSprintf_s(szWord,sizeof(szWord),"{#fff4db30=历练名望: %d#}",nRewardValue);
					strRewardItem += "\n";
					strRewardItem += szWord;
				}
			}
			break;
		case SQuest::eReward_Item:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number, eIcon_Enable, false, eTipFlag_Normal, false, true );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}

				if(m_pID_LISTIMG_Reward->GetNullItem() == 0)
					m_pID_LISTIMG_Reward->SetItem( &stItem );
				else if(m_pID_LISTIMG_SecondItem->GetNullItem() == 0)
					m_pID_LISTIMG_SecondItem->SetItem( &stItem );
				else if(m_pID_LISTIMG_ThirdItem->GetNullItem() == 0)
					m_pID_LISTIMG_ThirdItem->SetItem( &stItem );
				else if(m_pID_LISTIMG_FourItem->GetNullItem() == 0)
					m_pID_LISTIMG_FourItem->SetItem( &stItem );

			}
			break;
		case SQuest::eReward_Reputation:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskMingWang),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;

			}
			break;
		case SQuest::eReward_Exploit:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGongXun),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_Title:
			{
				TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID( pReward->Value );
				if( pTitle )
				{
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskTitle);
					strRewardItem += pTitle->GetName();
				}
			}
			break;
		case SQuest::eReward_GuildContribute:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskGuildContribute),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		case SQuest::eReward_SpecialItem:
			{
				ItemDefine::SItemCommon *pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pReward->Value );
				if( !pItemDetail )
					continue;
				ControlIconDrag::S_ListImg stItem;
				stItem.SetData( pItemDetail->ustItemID, pReward->Number );
				if ( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER ||
					pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					// 过滤职业装
					unsigned char cPro = thePlayerRole.GetProfession();
					if (!(pReward->shProfession & (1 << cPro)))
						continue;

					if (pReward->shSex != 2 && pReward->shSex != thePlayerRole.GetSex())
						continue;
				}
			}
			break;
		case SQuest::eReward_JiaoZi:
			{
				int money = pReward->Value;
				if (money > 0)
				{
					std::string text = "";
					thePlayerRole.GetGSCStringFromJiaoZi(money, text);
					strRewardItem += "\n";
					strRewardItem += theXmlString.GetString(eText_Quest_TaskJiaozi);
					strRewardItem += text;
				}
			}
			break;
		case SQuest::eReward_Honor:
			{
				char szWord[256] = {0};
				MeSprintf_s(szWord,sizeof(szWord),theXmlString.GetString(eText_Quest_TaskRongYu),pReward->Value);
				strRewardItem += "\n";
				strRewardItem += szWord;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
	if (strRewardItem.find_first_of("\n")==0)
	{
		strRewardItem.erase(strRewardItem.find_first_of("\n"),1);
	}
}

void CUI_ID_FRAME_Hunting::GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem)
{
	if(!pQuest)
		return;
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pQuest->Id );
	if(pInfo && pInfo->chState == QuestManager::eQuestEntrustDone)	
		return;

	strNeedItem.clear();
	if(pQuest->IsSingleRequirement)
		strNeedItem += theXmlString.GetString(eText_Quest_IsSingleRequirement);

	SQuestRequirement *pRequirement = NULL;
	for( int i = 0; i < pQuest->stCommitRequirement.size(); i++ )
	{
		bool bShowMapName = false;
		pRequirement = &pQuest->stCommitRequirement[i];
		char szInfo[256] = "";
		switch( pRequirement->byType )
		{
		case SQuest::eRequirement_Item:
			{
				ItemDefine::SItemCommon* pItemDetail = NULL;
				pItemDetail = GettheItemDetail().GetItemByID( pRequirement->Value );
				if( pItemDetail )
				{
					int nItemCount = thePlayerRole.m_bag.GetItemCount( pItemDetail->ustItemID );
					if (nItemCount < 1)
					{
						nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemDetail->ustItemID );
						if (nItemCount < 1)
							nItemCount = thePlayerRole.m_bagTask.GetItemCount( pItemDetail->ustItemID );
					}

					//需要任务物品
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString( eText_NeedItem ),
						pItemDetail->GetItemName(), nItemCount, pRequirement->MaxNum );
				}
			}
			break;
		case SQuest::eRequirement_Monster:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;
				ItemDefine::SMonster* pMonstor = GettheItemDetail().GetMonsterById(pRequirement->Value);
				if (pMonstor)
				{
					//需要
					sprintf( szInfo, "\n    %s %s (%ld/%ld)", theXmlString.GetString(eUI_NeedText),
						pMonstor->GetName(), nVar, pRequirement->MaxNum );

					bShowMapName = true;
				}
			}
			break;
		case SQuest::eRequirement_Action:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				sprintf( szInfo, "    %s (%ld/%ld)", theXmlString.GetString(pRequirement->Value),
					nVar, pRequirement->MaxNum );
			}
			break;
		case SQuest::eRequirement_Var:
			{
				int nVar = 0;
				CPlayerRole::QuestInfo* pVariableInfo = thePlayerRole.FindVariableInfoById( pRequirement->wVar );
				if( pVariableInfo )
					nVar = pVariableInfo->chState;

				if(nVar == pRequirement->MaxNum)
					continue;

				sprintf(szInfo, "\n    %s%s (%ld/%ld)", theXmlString.GetString(eText_Quest_TaskAim), theXmlString.GetString(pRequirement->nStringID), nVar, pRequirement->MaxNum);
				bShowMapName = true;			
			}
			break;
		default:
			break;
		}
		std::string strInfo = szInfo;
		NpcCoord::getInstance()->addNpcHyberForText(strInfo,NpcCoord::eQuestId,pQuest->Id,pQuest->ReplyTargetId,NULL,bShowMapName,false);

		strNeedItem += strInfo;
		/*if (pQuest->IsSingleRequirement)
		{
			break;
		}*/
	}
}

bool CUI_ID_FRAME_Hunting::HasVarId(int nId)
{
	bool bHas = false;
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		if ( thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i] > 0 
			&& thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i] == nId )
		{
			bHas = true;
			break;
		}
	}

	return bHas;
}

bool CUI_ID_FRAME_Hunting::HasUnAcceptQuest()
{
	for (int i = 0; i < More_nHuntingNum; i++ )
	{
		int nQuestId = thePlayerRole.GetCharInfo2().otherdataclient.sHunting.nCurRandIds[i];
		if ( nQuestId > 0 )
		{
			CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( nQuestId );
			if ( !pInfo || !theQuestManager.IsQuestActive(pInfo->chState) )
				return true;
		}
		
	}

	return false;
}