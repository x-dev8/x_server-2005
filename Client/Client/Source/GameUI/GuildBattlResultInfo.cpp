/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBattlResultInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildBattlResultInfo.h"
#include "PLayerRole.h"
#include "CampBattleGuild.h"
CUI_ID_FRAME_GuildBattleResult s_CUI_ID_FRAME_GuildBattleResult;

MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildBattleResult, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildBattleResult, OnFrameRender )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleResult, ID_BUTTON_CloseOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GuildBattleResult, ID_LISTIMG_RewardOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleResult, ID_LISTIMG_RewardOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GuildBattleResult, ID_LISTIMG_RewardOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildBattleResult, ID_LISTIMG_RewardOnIconButtonClick )
CUI_ID_FRAME_GuildBattleResult::CUI_ID_FRAME_GuildBattleResult()
{
	// Member
	m_pID_FRAME_GuildBattleResult = NULL;
	m_pID_TEXT_Reult = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_TEXT_KillSum = NULL;
	m_pID_LISTIMG_Reward = NULL;
	m_pID_TEXT_Name1 = NULL;
	m_pID_TEXT_KIllNum3 = NULL;
	m_pID_TEXT_KIllNum2 = NULL;
	m_pID_TEXT_KIllNum6 = NULL;
	m_pID_TEXT_Name6 = NULL;
	m_pID_TEXT_KIllNum1 = NULL;
	m_pID_TEXT_Name5 = NULL;
	m_pID_TEXT_Name4 = NULL;
	m_pID_TEXT_Name3 = NULL;
	m_pID_TEXT_Name2 = NULL;
	m_pID_TEXT_KIllNum10 = NULL;
	m_pID_TEXT_KIllNum9 = NULL;
	m_pID_TEXT_Name10 = NULL;
	m_pID_TEXT_Name9 = NULL;
	m_pID_TEXT_KIllNum5 = NULL;
	m_pID_TEXT_KIllNum4 = NULL;
	m_pID_TEXT_KIllNum8 = NULL;
	m_pID_TEXT_Name8 = NULL;
	m_pID_TEXT_KIllNum7 = NULL;
	m_pID_TEXT_Name7 = NULL;

}
CUI_ID_FRAME_GuildBattleResult::~CUI_ID_FRAME_GuildBattleResult()
{
}
// Frame
bool CUI_ID_FRAME_GuildBattleResult::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildBattleResult::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildBattleResult::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_GuildBattleResult.SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GuildBattleResult::ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_GuildBattleResult::ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GuildBattleResult::ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GuildBattleResult::ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_GuildBattleResult::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildBattlResultInfo.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildBattlResultInfo.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildBattleResult::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildBattleResult, s_CUI_ID_FRAME_GuildBattleResultOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildBattleResult, s_CUI_ID_FRAME_GuildBattleResultOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildBattleResult, ID_BUTTON_Close, s_CUI_ID_FRAME_GuildBattleResultID_BUTTON_CloseOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GuildBattleResult, ID_LISTIMG_Reward, s_CUI_ID_FRAME_GuildBattleResultID_LISTIMG_RewardOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GuildBattleResult, ID_LISTIMG_Reward, s_CUI_ID_FRAME_GuildBattleResultID_LISTIMG_RewardOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GuildBattleResult, ID_LISTIMG_Reward, s_CUI_ID_FRAME_GuildBattleResultID_LISTIMG_RewardOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_GuildBattleResult, ID_LISTIMG_Reward, s_CUI_ID_FRAME_GuildBattleResultID_LISTIMG_RewardOnIconButtonClick );

	m_pID_FRAME_GuildBattleResult = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildBattleResult );
	m_pID_TEXT_Reult = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Reult );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_BUTTON_Close );
	m_pID_TEXT_KillSum = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KillSum );
	m_pID_LISTIMG_Reward = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_LISTIMG_Reward );
	m_pID_TEXT_Name1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name1 );
	m_pID_TEXT_KIllNum3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum3 );
	m_pID_TEXT_KIllNum2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum2 );
	m_pID_TEXT_KIllNum6 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum6 );
	m_pID_TEXT_Name6 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name6 );
	m_pID_TEXT_KIllNum1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum1 );
	m_pID_TEXT_Name5 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name5 );
	m_pID_TEXT_Name4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name4 );
	m_pID_TEXT_Name3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name3 );
	m_pID_TEXT_Name2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name2 );
	m_pID_TEXT_KIllNum10 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum10 );
	m_pID_TEXT_KIllNum9 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum9 );
	m_pID_TEXT_Name10 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name10 );
	m_pID_TEXT_Name9 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name9 );
	m_pID_TEXT_KIllNum5 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum5 );
	m_pID_TEXT_KIllNum4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum4 );
	m_pID_TEXT_KIllNum8 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum8 );
	m_pID_TEXT_Name8 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name8 );
	m_pID_TEXT_KIllNum7 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_KIllNum7 );
	m_pID_TEXT_Name7 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleResult, ID_TEXT_Name7 );
	assert( m_pID_FRAME_GuildBattleResult );
	assert( m_pID_TEXT_Reult );
	assert( m_pID_BUTTON_Close );
	assert( m_pID_TEXT_KillSum );
	assert( m_pID_LISTIMG_Reward );
	assert( m_pID_TEXT_Name1 );
	assert( m_pID_TEXT_KIllNum3 );
	assert( m_pID_TEXT_KIllNum2 );
	assert( m_pID_TEXT_KIllNum6 );
	assert( m_pID_TEXT_Name6 );
	assert( m_pID_TEXT_KIllNum1 );
	assert( m_pID_TEXT_Name5 );
	assert( m_pID_TEXT_Name4 );
	assert( m_pID_TEXT_Name3 );
	assert( m_pID_TEXT_Name2 );
	assert( m_pID_TEXT_KIllNum10 );
	assert( m_pID_TEXT_KIllNum9 );
	assert( m_pID_TEXT_Name10 );
	assert( m_pID_TEXT_Name9 );
	assert( m_pID_TEXT_KIllNum5 );
	assert( m_pID_TEXT_KIllNum4 );
	assert( m_pID_TEXT_KIllNum8 );
	assert( m_pID_TEXT_Name8 );
	assert( m_pID_TEXT_KIllNum7 );
	assert( m_pID_TEXT_Name7 );

	m_NameList[0] = m_pID_TEXT_Name1;
	m_NameList[1] = m_pID_TEXT_Name2;
	m_NameList[2] = m_pID_TEXT_Name3;
	m_NameList[3] = m_pID_TEXT_Name4;
	m_NameList[4] = m_pID_TEXT_Name5;
	m_NameList[5] = m_pID_TEXT_Name6;
	m_NameList[6] = m_pID_TEXT_Name7;
	m_NameList[7] = m_pID_TEXT_Name8;
	m_NameList[8] = m_pID_TEXT_Name9;
	m_NameList[9] = m_pID_TEXT_Name10;

	m_KillNumList[0] = m_pID_TEXT_KIllNum1;
	m_KillNumList[1] = m_pID_TEXT_KIllNum2;
	m_KillNumList[2] = m_pID_TEXT_KIllNum3;
	m_KillNumList[3] = m_pID_TEXT_KIllNum4;
	m_KillNumList[4] = m_pID_TEXT_KIllNum5;
	m_KillNumList[5] = m_pID_TEXT_KIllNum6;
	m_KillNumList[6] = m_pID_TEXT_KIllNum7;
	m_KillNumList[7] = m_pID_TEXT_KIllNum8;
	m_KillNumList[8] = m_pID_TEXT_KIllNum9;
	m_KillNumList[9] = m_pID_TEXT_KIllNum10;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildBattleResult::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\GuildBattlResultInfo.meui" );
}
// 是否可视
bool CUI_ID_FRAME_GuildBattleResult::_IsVisable()
{
	return m_pID_FRAME_GuildBattleResult->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildBattleResult::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_GuildBattleResult->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildBattleResult::SetData(MsgCampGuildBattleRewardInfo * pMsg)
{
	//将战场的结果设置到UI上面去
	if(!thePlayerRole.GetGangMgr()||!IsVisable())
		return;
	/*if(!m_pID_FRAME_GuildBattleResult)
	{
		_LoadUI();
	}
	if(!m_pID_FRAME_GuildBattleResult)
		return;*/
	unsigned int GuildID = thePlayerRole.GetGangMgr()->GetGuildID();
	if(pMsg->nWinGuildID == GuildID)
	{
		//为胜利方
		m_pID_TEXT_Reult->SetText(theXmlString.GetString(eText_GuildBattle_Win));

		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(pMsg->WinItemID,1);
		m_pID_LISTIMG_Reward->SetItem(&pItems,0);
	}
	else if(pMsg->nLoseGuildID == GuildID)
	{
		//为失败方
		m_pID_TEXT_Reult->SetText(theXmlString.GetString(eText_GuildBattle_Lose));

		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(pMsg->LoseItemID,1);
		m_pID_LISTIMG_Reward->SetItem(&pItems,0); 
	}
	bool IsNeedOtherItem = false;
	for(int i =0;i<pMsg->OtherSum;++i)
	{
		unsigned int PlayerID = pMsg->PlayerID[i];
		unsigned int KissSum = pMsg->Point[i];
		if(PlayerID == thePlayerRole.GetDBID())
			IsNeedOtherItem = true;
		//同一公会的玩家
		m_NameList[i]->SetText(pMsg->Name[i]);
		char sInfo[8] = {0};
		itoa(KissSum,sInfo,10);
		m_KillNumList[i]->SetText(sInfo);
	}
	//设置自己的杀人数
	char Kill[8];
	itoa(pMsg->KissSum,Kill,10);
	m_pID_TEXT_KillSum->SetText(Kill);
	//设置自己是否获取奖励
	if(IsNeedOtherItem)
	{
		ControlIconDrag::S_ListImg pItems;
		pItems.SetData(pMsg->OtherItemID,1);
		m_pID_LISTIMG_Reward->SetItem(&pItems,1); 
	}
}
void CUI_ID_FRAME_GuildBattleResult::SetShowByNeed()
{
	time_t now;
	time(&now);
	string StrInfo;
	int States = s_CUI_ID_FRAME_CampBattleGuild.GetCampBattleInfo().m_Setting->GetTimeStates(now,StrInfo);
	if(States == 5)
		SetVisable(true);
	else
		SetVisable(false);
}