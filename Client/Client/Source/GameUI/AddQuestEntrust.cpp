/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\AddQuestEntrust.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AddQuestEntrust.h"
#include "QuestEntrust.h"
#include "QuestManager.h"
#include "PlayerRole.h"
#include "Task.h"
#include "PackItemEnableManager.h"
#include "QuestEntrustMessage.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
CUI_ID_FRAME_AddQuestEntrust s_CUI_ID_FRAME_AddQuestEntrust;

MAP_FRAME_RUN( s_CUI_ID_FRAME_AddQuestEntrust, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AddQuestEntrust, OnFrameRender )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YinBiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YuanBaoOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_BUTTON_AddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_BUTTON_CanelOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_EDIT_JinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_EDIT_YinOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_EDIT_TonOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_EDIT_YuanBaoOnEditEnter )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_LISTIMG_ItemOnIconButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_AddQuestEntrust, ID_EDIT_ItemNumOnEditEnter )
CUI_ID_FRAME_AddQuestEntrust::CUI_ID_FRAME_AddQuestEntrust()
{
	// Member
	m_pID_FRAME_AddQuestEntrust = NULL;
	m_pID_TEXT_QuestEntruestName = NULL;
	m_pID_TEXT_QuestEntrustDepict = NULL;
	m_pID_TEXT_QuestEntrustInfo = NULL;
	m_pID_CHECKBOX_YinBi = NULL;
	m_pID_CHECKBOX_YuanBao = NULL;
	m_pID_BUTTON_Add = NULL;
	m_pID_BUTTON_Canel = NULL;
	m_pID_EDIT_Jin = NULL;
	m_pID_EDIT_Yin = NULL;
	m_pID_EDIT_Ton = NULL;
	m_pID_EDIT_YuanBao = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_EDIT_ItemNum = NULL;

}
CUI_ID_FRAME_AddQuestEntrust::~CUI_ID_FRAME_AddQuestEntrust()
{
}
// Frame
bool CUI_ID_FRAME_AddQuestEntrust::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_AddQuestEntrust::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_AddQuestEntrust::ID_CHECKBOX_YinBiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_YinBi->SetCheck(true);
	m_pID_CHECKBOX_YuanBao->SetCheck(false);

	m_pID_EDIT_Jin->SetVisable(true);
	m_pID_EDIT_Yin->SetVisable(true);
	m_pID_EDIT_Ton->SetVisable(true);
	m_pID_EDIT_YuanBao->SetVisable(false);

}
// CheckBox
void CUI_ID_FRAME_AddQuestEntrust::ID_CHECKBOX_YuanBaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_YinBi->SetCheck(false);
	m_pID_CHECKBOX_YuanBao->SetCheck(true);

	m_pID_EDIT_Jin->SetVisable(false);
	m_pID_EDIT_Yin->SetVisable(false);
	m_pID_EDIT_Ton->SetVisable(false);
	m_pID_EDIT_YuanBao->SetVisable(true);
}
// Button
bool CUI_ID_FRAME_AddQuestEntrust::ID_BUTTON_AddOnButtonClick( ControlObject* pSender )
{
	SendInfo();
	return true;
}
// Button
bool CUI_ID_FRAME_AddQuestEntrust::ID_BUTTON_CanelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Edit
void CUI_ID_FRAME_AddQuestEntrust::ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddQuestEntrust::ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddQuestEntrust::ID_EDIT_TonOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Edit
void CUI_ID_FRAME_AddQuestEntrust::ID_EDIT_YuanBaoOnEditEnter( ControlObject* pSender, const char* szData )
{
}
// ListImg / ListEx
bool CUI_ID_FRAME_AddQuestEntrust::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	//把物品拖拽上UI
	SetItem(pItemDrag->m_pkIconInfo->GetOnlyId());
	return true;
}
bool CUI_ID_FRAME_AddQuestEntrust::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_AddQuestEntrust::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	//清空当前物品栏上的物品
	SetEmpty();
	return false;
}
bool CUI_ID_FRAME_AddQuestEntrust::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Edit
void CUI_ID_FRAME_AddQuestEntrust::ID_EDIT_ItemNumOnEditEnter( ControlObject* pSender, const char* szData )
{
}
bool CUI_ID_FRAME_AddQuestEntrust::IsPackItemBeUsing( __int64 nGuid )
{
   	if(!IsVisable())
        return false;
	if(ItemID == nGuid)
		return true;
	else
		return false;
}
// 装载UI
bool CUI_ID_FRAME_AddQuestEntrust::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AddQuestEntrust.meui",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AddQuestEntrust.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AddQuestEntrust::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AddQuestEntrust, s_CUI_ID_FRAME_AddQuestEntrustOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AddQuestEntrust, s_CUI_ID_FRAME_AddQuestEntrustOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YinBi, s_CUI_ID_FRAME_AddQuestEntrustID_CHECKBOX_YinBiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YuanBao, s_CUI_ID_FRAME_AddQuestEntrustID_CHECKBOX_YuanBaoOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_AddQuestEntrust, ID_BUTTON_Add, s_CUI_ID_FRAME_AddQuestEntrustID_BUTTON_AddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AddQuestEntrust, ID_BUTTON_Canel, s_CUI_ID_FRAME_AddQuestEntrustID_BUTTON_CanelOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_AddQuestEntrust, ID_EDIT_Jin, s_CUI_ID_FRAME_AddQuestEntrustID_EDIT_JinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddQuestEntrust, ID_EDIT_Yin, s_CUI_ID_FRAME_AddQuestEntrustID_EDIT_YinOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddQuestEntrust, ID_EDIT_Ton, s_CUI_ID_FRAME_AddQuestEntrustID_EDIT_TonOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_AddQuestEntrust, ID_EDIT_YuanBao, s_CUI_ID_FRAME_AddQuestEntrustID_EDIT_YuanBaoOnEditEnter );
	theUiManager.OnIconDragOn( ID_FRAME_AddQuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_AddQuestEntrustID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_AddQuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_AddQuestEntrustID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_AddQuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_AddQuestEntrustID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_AddQuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_AddQuestEntrustID_LISTIMG_ItemOnIconButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_AddQuestEntrust, ID_EDIT_ItemNum, s_CUI_ID_FRAME_AddQuestEntrustID_EDIT_ItemNumOnEditEnter );

	m_pID_FRAME_AddQuestEntrust = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AddQuestEntrust );
	m_pID_TEXT_QuestEntruestName = (ControlText*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_TEXT_QuestEntruestName );
	m_pID_TEXT_QuestEntrustDepict = (ControlText*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_TEXT_QuestEntrustDepict );
	m_pID_TEXT_QuestEntrustInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_TEXT_QuestEntrustInfo );
	m_pID_CHECKBOX_YinBi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YinBi );
	m_pID_CHECKBOX_YuanBao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_CHECKBOX_YuanBao );
	m_pID_BUTTON_Add = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_BUTTON_Add );
	m_pID_BUTTON_Canel = (ControlButton*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_BUTTON_Canel );
	m_pID_EDIT_Jin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_EDIT_Jin );
	m_pID_EDIT_Yin = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_EDIT_Yin );
	m_pID_EDIT_Ton = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_EDIT_Ton );
	m_pID_EDIT_YuanBao = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_EDIT_YuanBao );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_LISTIMG_Item );
	m_pID_EDIT_ItemNum = (ControlEdit*)theUiManager.FindControl( ID_FRAME_AddQuestEntrust, ID_EDIT_ItemNum );
	assert( m_pID_FRAME_AddQuestEntrust );
	assert( m_pID_TEXT_QuestEntruestName );
	assert( m_pID_TEXT_QuestEntrustDepict );
	assert( m_pID_TEXT_QuestEntrustInfo );
	assert( m_pID_CHECKBOX_YinBi );
	assert( m_pID_CHECKBOX_YuanBao );
	assert( m_pID_BUTTON_Add );
	assert( m_pID_BUTTON_Canel );
	assert( m_pID_EDIT_Jin );
	assert( m_pID_EDIT_Yin );
	assert( m_pID_EDIT_Ton );
	assert( m_pID_EDIT_YuanBao );
	assert( m_pID_LISTIMG_Item );
	assert( m_pID_EDIT_ItemNum );

	m_pID_FRAME_AddQuestEntrust->SetOnVisibleChangedFun( OnVisibleChange );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AddQuestEntrust::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\AddQuestEntrust.meui" );
}
// 是否可视
bool CUI_ID_FRAME_AddQuestEntrust::_IsVisable()
{
	return m_pID_FRAME_AddQuestEntrust->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AddQuestEntrust::_SetVisable( const bool bVisable )
{
	if(!bVisable)
		SetEmpty();
	m_pID_FRAME_AddQuestEntrust->SetVisable( bVisable );
}
void CUI_ID_FRAME_AddQuestEntrust::LoadInfoToUI(unsigned int QuestID)
{
	//获取任务的配置信息
	SQuest* pQuestInfo = theQuestManager.GetQuest(QuestID);
	if(!pQuestInfo)
	{
		//提示玩家任务不存在 错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_NonQuest));
		return;
	}
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( QuestID );
	if ( !pInfo )
		return;
	if(pInfo->chState !=  QuestManager::eQuestGaining )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonStates));
		return;
	}
	unsigned int NewQuestID = s_CUI_ID_FRAME_QuestEntrust.GetConfig().GetChangeQuestID(QuestID);
	if(NewQuestID == 0)
	{
		//提示玩家 当前任务不可以设置委托
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_ErrorQuest));
		return;
	}
	pQuestInfo = theQuestManager.GetQuest(NewQuestID);
	if(!pQuestInfo)
	{
		//提示玩家任务不存在 错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_NonQuest));
		return;
	}
	pQuestInfo = theQuestManager.GetQuest(QuestID);
	SetVisable(true);
	//当前任务可以委托后 我们设置基本信息
	std::string name = pQuestInfo->GetQuestName();
	m_pID_TEXT_QuestEntruestName->SetText(name.c_str(),theHeroGame.GetPlayerMgr()->GetQuestRankColor(pQuestInfo));

	std::string infoStr = pQuestInfo->GetQuestInfo();
	m_pID_TEXT_QuestEntrustDepict->SetText( infoStr);

	std::string targetStr = s_CUI_ID_FRAME_Task.GetQuestTargetInfo( pQuestInfo, pInfo );
	m_pID_TEXT_QuestEntrustInfo->SetText( targetStr );
	m_QuestID = QuestID;
}
void CUI_ID_FRAME_AddQuestEntrust::SetItem(__int64 ItemOnceID)
{
	//设置委托的奖励 一件非绑定 非限时 可以交易的物品 
	//SetEmpty();
	SCharItem pItem;
	if(!thePlayerRole.GetBagItemByGUID(ItemOnceID,&pItem))
	{
		//提示玩家 物品不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_NonItem));
		return;
	}
	if(pItem.IsBounded())
	{
		//绑定的物品不可以设置
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_ItemError));
		return;
	}
	if(pItem.itembaseinfo.n64UseTime !=-1)
	{
		//时限物品不可以设置
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_ItemError));
		return;
	}
	//before:如果有物品则先把原来的拿下来
	SetEmpty();
	//1.设置数据
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(&pItem);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);
	//2.让背包黑下来
	CItemBag2* pBag = NULL;
	if(!thePlayerRole.GetBagByItemGUID(ItemOnceID, pBag) || !pBag)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_AddQuestEntrust_NonItem));
		pItems.SetData(0,0);
		m_pID_LISTIMG_Item->SetItem(&pItems,0);
		return;
	}
	ItemID = ItemOnceID;
	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag,pItem.itembaseinfo.nOnlyInt,true);
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
}
void CUI_ID_FRAME_AddQuestEntrust::SetEmpty()
{
	if(ItemID == 0)
		return;
	SCharItem pItem;
	if(!thePlayerRole.GetBagItemByGUID(ItemID,&pItem))
		return;
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);
	CItemBag2* pBag = NULL;
	if(!thePlayerRole.GetBagByItemGUID(ItemID, pBag) || !pBag)
		return;
	ItemID = 0;
	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pBag,pItem.itembaseinfo.nOnlyInt,true);
}
void CUI_ID_FRAME_AddQuestEntrust::SendInfo()
{
	//发送命令
	QuestEntrustStates states;
	states.ID = 0;
	states.SrcPlayerID = thePlayerRole.GetDBID();
	strcpy_s(states.ScrPlayerName,MaxPlayerNameLength,thePlayerRole.GetName());
	states.DestPlayerID = 0;
	states.SrcQuestID = m_QuestID;
	states.DestQuestID = s_CUI_ID_FRAME_QuestEntrust.GetConfig().GetChangeQuestID(m_QuestID);
	states.EntrustRewardType = QuestEntrust_YinBi;
	if(states.EntrustRewardType == QuestEntrust_YinBi)
	{
		unsigned int Jin = atoi(m_pID_EDIT_Jin->GetText());
		unsigned int Yin = atoi(m_pID_EDIT_Yin->GetText());
		unsigned int Ton = atoi(m_pID_EDIT_Ton->GetText());
		states.EntrustRewardSum = thePlayerRole.GetMoneyFromGSC(Jin,Yin,Ton);
		if(!thePlayerRole.PackHasEnoughMoney(states.EntrustRewardSum))
		{
			//提示玩家 金钱不够
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonMoney));
			return;
		}
	}
	else if(states.EntrustRewardType == QuestEntrust_YuanBao)
	{
		states.EntrustRewardSum= atoi(m_pID_EDIT_YuanBao->GetText());
	}
	states.ReceiveLogTime = 0;
	states.IsSecc = false;
	states.ItemInfo.itembaseinfo.nOnlyInt = ItemID;
	//组织命令
	MsgAddQuestEntrustReq msg;
	msg.info = states;
	GettheNetworkInput().SendMsg(&msg);
	//清空数据
	SetEmpty();
	m_pID_TEXT_QuestEntruestName->SetText("");
	m_pID_TEXT_QuestEntrustDepict->SetText("");
	m_pID_TEXT_QuestEntrustInfo->SetText("");
	m_pID_EDIT_Jin->SetText("");
	m_pID_EDIT_Yin->SetText("");
	m_pID_EDIT_Ton->SetText("");
	m_pID_EDIT_YuanBao->SetText("");
	m_pID_EDIT_ItemNum->SetText("");
	m_QuestID = 0;
	ItemID = 0;
	s_CUI_ID_FRAME_AddQuestEntrust.SetVisable(false);
}
void CUI_ID_FRAME_AddQuestEntrust::OnVisibleChange( ControlObject* pUIObject )
{
	if(pUIObject->IsVisable()) return;
	s_CUI_ID_FRAME_AddQuestEntrust.SetEmpty();
}