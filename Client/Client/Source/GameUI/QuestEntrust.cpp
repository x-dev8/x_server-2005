/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\QuestEntrust.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "QuestEntrust.h"
#include "QuestEntrustMessage.h"
#include "NetworkInput.h"
#include "QuestManager.h"
#include "PlayerRole.h"
#include "Task.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "GameMain.h"
CUI_ID_FRAME_QuestEntrust s_CUI_ID_FRAME_QuestEntrust;
MAP_FRAME_RUN( s_CUI_ID_FRAME_QuestEntrust, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_QuestEntrust, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustRewardOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustNameOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_CHECKBOX_AllQuestEntrustOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_CHECKBOX_MyQuestEntrustOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_CHECKBOX_JoinQuestEntrustOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_BUTTON_CanelMyQuestEntrustOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_BUTTON_DropQuestEntrustOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_BUTTON_JoinQuestEntrustOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_BUTTON_GetRewardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_BUTTON_UpdateOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_CHECKBOX_ShowCanJoinOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_QuestEntrust, ID_LISTIMG_ItemOnIconButtonClick )
CUI_ID_FRAME_QuestEntrust::CUI_ID_FRAME_QuestEntrust()
{
	// Member
	m_pID_FRAME_QuestEntrust = NULL;
	m_pID_LIST_QuestEntrustReward = NULL;
	m_pID_LIST_QuestEntrustName = NULL;
	m_pID_CHECKBOX_AllQuestEntrust = NULL;
	m_pID_CHECKBOX_MyQuestEntrust = NULL;
	m_pID_CHECKBOX_JoinQuestEntrust = NULL;
	m_pID_BUTTON_CanelMyQuestEntrust = NULL;
	m_pID_BUTTON_DropQuestEntrust = NULL;
	m_pID_TEXT_QuestEntrustName = NULL;
	m_pID_TEXT_QuestEntrustDepict = NULL;
	m_pID_TEXT_QuestEntrustInfo = NULL;
	m_pID_TEXT_QuestEntrustReward = NULL;
	m_pID_BUTTON_JoinQuestEntrust = NULL;
	m_pID_BUTTON_GetReward = NULL;
	m_pID_LISTIMG_Item = NULL;
	m_pID_BUTTON_Update = NULL;
	m_pID_CHECKBOX_ShowCanJoin=NULL;
	m_pID_TEXT_LastTime = NULL;
	m_pID_TEXT_MoneySum = NULL;

	m_IsNeedClear = false;
}
// Frame
bool CUI_ID_FRAME_QuestEntrust::OnFrameRun()
{
	//每隔多少秒Update下
	//static unsigned int TimeLog = 0;
	//if(timeGetTime() - TimeLog >= 5000)
	//{
	//	TimeLog = timeGetTime();
	//	NeedGetAllData();//更新所有的资源
	//}
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::OnFrameRender()
{
	ShowLastTime();
	return true;
}
// List
void CUI_ID_FRAME_QuestEntrust::ID_LIST_QuestEntrustRewardOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_QuestEntrust::ID_LIST_QuestEntrustNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	SetSelectList(m_pID_LIST_QuestEntrustName->GetCurSelIndex());
}
// CheckBox
void CUI_ID_FRAME_QuestEntrust::ID_CHECKBOX_AllQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(true);
	m_pID_CHECKBOX_ShowCanJoin->SetCheck(false);
	SetAllQuestEntrustToUI();
}
// CheckBox
void CUI_ID_FRAME_QuestEntrust::ID_CHECKBOX_MyQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(false);
	SetMyQuestEntrusrToUI();
}
// CheckBox
void CUI_ID_FRAME_QuestEntrust::ID_CHECKBOX_JoinQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(false);
	SetMyJoinQuestEntrustToUI();
}
void CUI_ID_FRAME_QuestEntrust::ID_CHECKBOX_ShowCanJoinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	if(!m_pID_CHECKBOX_AllQuestEntrust->IsChecked())
		return;
	SetAllQuestEntrustToUI(-1,m_pID_CHECKBOX_ShowCanJoin->IsChecked());
}
// Button
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_CanelMyQuestEntrustOnButtonClick( ControlObject* pSender )
{
	//取消自己的委托
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//提示玩家错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//指定委托不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].SrcPlayerID != thePlayerRole.GetDBID())
	{
		//不是自己发布的委托 不可以取消
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonDel));
		return false;
	}
	MsgDelQuestEntrustReq msg;
	msg.ID = ID;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
// Button
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_DropQuestEntrustOnButtonClick( ControlObject* pSender )
{
	//取消已经接取的委托
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//提示玩家错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//指定委托不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].DestPlayerID != thePlayerRole.GetDBID())
	{
		//不是自己发布的委托 可以取消
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonCanel));
		return false;
	}
	MsgUpdateCanelQuestEntrustReq msg;
	msg.ID = ID;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_JoinQuestEntrustOnButtonClick( ControlObject* pSender )
{
	//接取新的委托
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//提示玩家错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//指定委托不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].DestPlayerID != 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_Join));
		return false;
	}
	if(theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsHaveStatus(s_CUI_ID_FRAME_QuestEntrust.GetConfig().GetBuffID()))
	{
		//当前状态不可以接取委托
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_JoinBuff));
		return false;
	}
	//判断押金是否足够
	unsigned int MoneySum = m_Config.GetQuestMoneySum(QuestEntrustList[ID].SrcQuestID);
	if(!thePlayerRole.PackHasEnoughMoney(MoneySum))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonMoneySum));
		return false;
	}
	//判断是否已经接取委托了
	if(!QuestEntrustList.empty())
	{
		std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
		for(;Iter != QuestEntrustList.end();++Iter)
		{
			if(thePlayerRole.GetDBID() == Iter->second.DestPlayerID && !Iter->second.IsSecc)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_JoinDoubleQuestError));
				return false;
			}
		}
	}
	//判断当前任务是否可以接取
	if(!IfCanJoinQuest(QuestEntrustList[ID].DestQuestID))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_JoinQuest));
		return false;
	}
	MsgUpdateJoinQuestEntrustReq msg;
	msg.ID = ID;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_UpdateOnButtonClick(ControlObject* pSender)
{
	//刷新按钮
	NeedGetAllData();
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_GetRewardOnButtonClick( ControlObject* pSender )
{
	//提交完成了的委托
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//提示玩家错误
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//指定委托不存在
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].DestPlayerID != thePlayerRole.GetDBID())
	{
		//不是自己发布的委托 可以取消
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonSec));
		return false;
	}
	//判断任务的状态
	unsigned int DestID = QuestEntrustList[ID].DestQuestID;
	CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( DestID );
	if(!pInfo) 
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	MsgQuestEntrustSeccReq msg;
	msg.ID = ID;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_QuestEntrust::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_QuestEntrust::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_QuestEntrust::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// 装载UI
bool CUI_ID_FRAME_QuestEntrust::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\QuestEntrust.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\QuestEntrust.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_QuestEntrust::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_QuestEntrust, s_CUI_ID_FRAME_QuestEntrustOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_QuestEntrust, s_CUI_ID_FRAME_QuestEntrustOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustReward, s_CUI_ID_FRAME_QuestEntrustID_LIST_QuestEntrustRewardOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustName, s_CUI_ID_FRAME_QuestEntrustID_LIST_QuestEntrustNameOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_QuestEntrust, ID_CHECKBOX_AllQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_CHECKBOX_AllQuestEntrustOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_QuestEntrust, ID_CHECKBOX_MyQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_CHECKBOX_MyQuestEntrustOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_QuestEntrust, ID_CHECKBOX_JoinQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_CHECKBOX_JoinQuestEntrustOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_QuestEntrust, ID_BUTTON_CanelMyQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_BUTTON_CanelMyQuestEntrustOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_QuestEntrust, ID_BUTTON_DropQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_BUTTON_DropQuestEntrustOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_QuestEntrust, ID_BUTTON_JoinQuestEntrust, s_CUI_ID_FRAME_QuestEntrustID_BUTTON_JoinQuestEntrustOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_QuestEntrust, ID_BUTTON_GetReward, s_CUI_ID_FRAME_QuestEntrustID_BUTTON_GetRewardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_QuestEntrust, ID_BUTTON_Update, s_CUI_ID_FRAME_QuestEntrustID_BUTTON_UpdateOnButtonClick );

	theUiManager.OnIconDragOn( ID_FRAME_QuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_QuestEntrustID_LISTIMG_ItemOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_QuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_QuestEntrustID_LISTIMG_ItemOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_QuestEntrust, ID_LISTIMG_Item, s_CUI_ID_FRAME_QuestEntrustID_LISTIMG_ItemOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_QuestEntrust, ID_LISTIMG_Item,s_CUI_ID_FRAME_QuestEntrustID_LISTIMG_ItemOnIconButtonClick );

	theUiManager.OnCheckBoxCheck( ID_FRAME_QuestEntrust, ID_CHECKBOX_ShowCanJoin, s_CUI_ID_FRAME_QuestEntrustID_CHECKBOX_ShowCanJoinOnCheckBoxCheck );
	
	m_pID_FRAME_QuestEntrust = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_QuestEntrust );
	m_pID_LIST_QuestEntrustReward = (ControlList*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustReward );
	m_pID_LIST_QuestEntrustName = (ControlList*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_LIST_QuestEntrustName );
	m_pID_CHECKBOX_AllQuestEntrust = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_CHECKBOX_AllQuestEntrust );
	m_pID_CHECKBOX_MyQuestEntrust = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_CHECKBOX_MyQuestEntrust );
	m_pID_CHECKBOX_JoinQuestEntrust = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_CHECKBOX_JoinQuestEntrust );
	m_pID_BUTTON_CanelMyQuestEntrust = (ControlButton*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_BUTTON_CanelMyQuestEntrust );
	m_pID_BUTTON_DropQuestEntrust = (ControlButton*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_BUTTON_DropQuestEntrust );
	m_pID_TEXT_QuestEntrustName = (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_QuestEntrustName );
	m_pID_TEXT_QuestEntrustDepict = (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_QuestEntrustDepict );
	m_pID_TEXT_QuestEntrustInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_QuestEntrustInfo );
	m_pID_TEXT_QuestEntrustReward = (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_QuestEntrustReward );
	m_pID_BUTTON_JoinQuestEntrust = (ControlButton*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_BUTTON_JoinQuestEntrust );
	m_pID_BUTTON_GetReward= (ControlButton*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_BUTTON_GetReward );
	m_pID_LISTIMG_Item = (ControlListImage*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_LISTIMG_Item );
	m_pID_BUTTON_Update= (ControlButton*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_BUTTON_Update );
	m_pID_CHECKBOX_ShowCanJoin = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_CHECKBOX_ShowCanJoin );
	m_pID_TEXT_LastTime= (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_LastTime );
	m_pID_TEXT_MoneySum= (ControlText*)theUiManager.FindControl( ID_FRAME_QuestEntrust, ID_TEXT_MoneySum );
	assert( m_pID_FRAME_QuestEntrust );
	assert( m_pID_LIST_QuestEntrustReward );
	assert( m_pID_LIST_QuestEntrustName );
	assert( m_pID_CHECKBOX_AllQuestEntrust );
	assert( m_pID_CHECKBOX_MyQuestEntrust );
	assert( m_pID_CHECKBOX_JoinQuestEntrust );
	assert( m_pID_BUTTON_CanelMyQuestEntrust );
	assert( m_pID_BUTTON_DropQuestEntrust );
	assert( m_pID_TEXT_QuestEntrustName );
	assert( m_pID_TEXT_QuestEntrustDepict );
	assert( m_pID_TEXT_QuestEntrustInfo );
	assert( m_pID_TEXT_QuestEntrustReward );
	assert( m_pID_BUTTON_JoinQuestEntrust );
	assert( m_pID_BUTTON_GetReward );
	assert( m_pID_LISTIMG_Item);
	assert( m_pID_CHECKBOX_ShowCanJoin);
	assert(m_pID_TEXT_LastTime);
	assert(m_pID_TEXT_MoneySum);
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_QuestEntrust::_UnLoadUI()
{
	m_pID_FRAME_QuestEntrust = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\QuestEntrust.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_QuestEntrust::_IsVisable()
{
	return m_pID_FRAME_QuestEntrust->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_QuestEntrust::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		NeedGetAllData();
	}
	m_pID_FRAME_QuestEntrust->SetVisable( bVisable );
}
void CUI_ID_FRAME_QuestEntrust::LoadAllQuestEntrust(QuestEntrustStates* pList,int Sum)
{
	//QuestEntrustList.clear();
	// 判断是否需要 下次清楚数据
	if(m_IsNeedClear)
	{
		QuestEntrustList.clear();
		m_IsNeedClear = false;
	}
	for(int i =0;i<Sum;++i)
	{
		//进行过滤处理
		//判断是否可以接取任务
		/*if(pList[i].SrcPlayerID !=thePlayerRole.GetDBID() && pList[i].DestPlayerID !=thePlayerRole.GetDBID() && !IfCanJoinQuest(pList[i].DestQuestID))
			continue;*/
		if(QuestEntrustList.count(pList[i].ID) == 1)
		{
			QuestEntrustList.erase(pList[i].ID);
		}
		QuestEntrustList.insert(std::map<unsigned int,QuestEntrustStates>::value_type(pList[i].ID,pList[i]));
	}
	UpdateUI();
	//SetVisable(true);
}
void CUI_ID_FRAME_QuestEntrust::UpdateQuestEntrust(QuestEntrustStates& pInfo)
{
	if(QuestEntrustList.count(pInfo.ID) == 1)
	{
		QuestEntrustList.erase(pInfo.ID);
	}
	QuestEntrustList.insert(std::map<unsigned int,QuestEntrustStates>::value_type(pInfo.ID,pInfo));
	UpdateUI();
}
void CUI_ID_FRAME_QuestEntrust::UpdateUI()
{
	//更新UI上正在展示的数据
	if(!m_pID_FRAME_QuestEntrust)
		return;
	unsigned int NowID = 0;
	if(IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex()) == 1)
		NowID = IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()];
	else
		NowID = -1;
	//获取到当前选择的ID后 我们开始清空Ui
	//将新的值设置到UI上面去
	if(m_pID_CHECKBOX_AllQuestEntrust->IsChecked())
	{
		SetEmpty();
		SetAllQuestEntrustToUI(NowID,m_pID_CHECKBOX_ShowCanJoin->IsChecked());
	}
	else if(m_pID_CHECKBOX_MyQuestEntrust->IsChecked())
	{
		SetEmpty();
		SetMyQuestEntrusrToUI(NowID);
	}
	else if(m_pID_CHECKBOX_JoinQuestEntrust->IsChecked())
	{
		SetEmpty();
		SetMyJoinQuestEntrustToUI(NowID);
	}
}
void CUI_ID_FRAME_QuestEntrust::SetEmpty()
{
	m_pID_LIST_QuestEntrustReward->Clear();
	m_pID_LIST_QuestEntrustName->Clear();
	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(false);
	m_pID_BUTTON_CanelMyQuestEntrust->SetVisable(false);
	m_pID_BUTTON_DropQuestEntrust->SetVisable(false);
	m_pID_BUTTON_JoinQuestEntrust->SetVisable(true);
	m_pID_BUTTON_GetReward->SetVisable(false);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(true);
	m_pID_TEXT_LastTime->SetVisable(false);

	m_pID_TEXT_QuestEntrustName->SetText("");
	m_pID_TEXT_QuestEntrustDepict->SetText("");
	m_pID_TEXT_QuestEntrustInfo->SetText("");
	m_pID_TEXT_QuestEntrustReward->SetText("");
	m_pID_TEXT_MoneySum->SetText("");

	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);
}
void CUI_ID_FRAME_QuestEntrust::SetAllQuestEntrustToUI(unsigned int SelectID,bool IsShowNeed)
{
	//将所有可以接取的委托 显示出来
	m_pID_LIST_QuestEntrustReward->Clear();
	m_pID_LIST_QuestEntrustName->Clear();
	m_pID_TEXT_QuestEntrustName->SetText("");
	m_pID_TEXT_MoneySum->SetText("");
	m_pID_TEXT_QuestEntrustDepict->SetText("");
	m_pID_TEXT_QuestEntrustInfo->SetText("");
	m_pID_TEXT_QuestEntrustReward->SetText("");
	m_pID_BUTTON_CanelMyQuestEntrust->SetVisable(false);
	m_pID_BUTTON_DropQuestEntrust->SetVisable(false);
	m_pID_BUTTON_JoinQuestEntrust->SetVisable(true);
	m_pID_BUTTON_GetReward->SetVisable(false);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(true);
	m_pID_TEXT_LastTime->SetVisable(false);

	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(false);

	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);

	IndexToIDMap.clear();
	//开始将数据加载UI上面去
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//过滤掉 我发布的 和 我接取的 
		if(Iter->second.IsSecc)
			continue;
		if(Iter->second.SrcPlayerID == thePlayerRole.GetDBID() || Iter->second.DestPlayerID != 0)
			continue;
		//判断是否为一个国家的
		SQuest * pQuest = theQuestManager.GetQuest(Iter->second.DestQuestID);
		if(!pQuest || (pQuest->Country !=0 &&  pQuest->Country != thePlayerRole.GetCountry()) )
			continue;
		if(IsShowNeed && !IfCanJoinQuest(Iter->second.DestQuestID))
		{
			continue;
		}
		//1.将数据加载到Ui上面去
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.将委托的具体信息显示出来
		if(Iter->first == SelectID)
		{
			SetSelectList(Row);
		}
	}

}
void CUI_ID_FRAME_QuestEntrust::SetMyQuestEntrusrToUI(unsigned int SelectID)
{
	m_pID_LIST_QuestEntrustReward->Clear();
	m_pID_LIST_QuestEntrustName->Clear();
	m_pID_TEXT_QuestEntrustName->SetText("");
	m_pID_TEXT_MoneySum->SetText("");
	m_pID_TEXT_QuestEntrustDepict->SetText("");
	m_pID_TEXT_QuestEntrustInfo->SetText("");
	m_pID_TEXT_QuestEntrustReward->SetText("");
	m_pID_BUTTON_CanelMyQuestEntrust->SetVisable(true);
	m_pID_BUTTON_DropQuestEntrust->SetVisable(false);
	m_pID_BUTTON_JoinQuestEntrust->SetVisable(false);
	m_pID_BUTTON_GetReward->SetVisable(false);
	m_pID_TEXT_LastTime->SetVisable(false);

	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(false);

	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);

	IndexToIDMap.clear();
	//开始将数据加载UI上面去
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//过滤掉 我发布的
		if(Iter->second.IsSecc)
			continue;
		if(Iter->second.SrcPlayerID != thePlayerRole.GetDBID())
			continue;
		//1.将数据加载到Ui上面去
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.将委托的具体信息显示出来
		if(Iter->first == SelectID)
		{
			SetSelectList(Row);
		}
	}
}
void CUI_ID_FRAME_QuestEntrust::SetMyJoinQuestEntrustToUI(unsigned int SelectID)
{
	m_pID_LIST_QuestEntrustReward->Clear();
	m_pID_LIST_QuestEntrustName->Clear();
	m_pID_TEXT_QuestEntrustName->SetText("");
	m_pID_TEXT_MoneySum->SetText("");
	m_pID_TEXT_QuestEntrustDepict->SetText("");
	m_pID_TEXT_QuestEntrustInfo->SetText("");
	m_pID_TEXT_QuestEntrustReward->SetText("");
	m_pID_BUTTON_CanelMyQuestEntrust->SetVisable(false);
	m_pID_BUTTON_DropQuestEntrust->SetVisable(true);
	m_pID_BUTTON_JoinQuestEntrust->SetVisable(false);
	m_pID_BUTTON_GetReward->SetVisable(true);
	m_pID_TEXT_LastTime->SetVisable(true);

	m_pID_CHECKBOX_AllQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_MyQuestEntrust->SetCheck(false);
	m_pID_CHECKBOX_JoinQuestEntrust->SetCheck(true);
	m_pID_CHECKBOX_ShowCanJoin->SetVisable(false);

	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(0,0);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);

	IndexToIDMap.clear();
	m_LastTime = 0;
	//开始将数据加载UI上面去
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//过滤掉 我接取的
		if(Iter->second.IsSecc)
			continue;
		if(thePlayerRole.GetDBID() != Iter->second.DestPlayerID)
			continue;
		//1.将数据加载到Ui上面去
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.将委托的具体信息显示出来
		if(Iter->first == SelectID)
		{
			SetSelectList(Row);
		}
		//3.设置倒计时 m_LastTime 处理时间函数 判断当前时间到 今天11:59:59秒 那个近点
		time_t joinTime = Iter->second.ReceiveLogTime;
		time_t EndTime = joinTime + GetConfig().GetLastTime()/1000;//加上合适的秒数
		time_t StopTime = 0;
		if(joinTime/86400 != EndTime/86400)
		{
			StopTime = (joinTime - joinTime%86400) + 86399;
		}
		else
			StopTime = EndTime;
		//得出结束时间后 我们判断秒数
		m_LastTime = StopTime;
	}
}
void CUI_ID_FRAME_QuestEntrust::SetQuestEntrustInfoToUI(unsigned int ID)
{
	//显示任务委托的具体信息
	if(QuestEntrustList.empty() || QuestEntrustList.count(ID) == 0)
		return;
	QuestEntrustStates& pInfo = QuestEntrustList[ID];
	//设置具体信息 根据任务ID获取任务的名称
	SQuest* pQuestInfo = theQuestManager.GetQuest(pInfo.DestQuestID);
	if(!pQuestInfo )
		return;
	m_pID_TEXT_QuestEntrustName->SetText(pQuestInfo->GetQuestName());
	std::string infoStr = pQuestInfo->GetQuestInfo();
	m_pID_TEXT_QuestEntrustDepict->SetText( infoStr);

	CPlayerRole::QuestInfo* pQInfo = thePlayerRole.FindQuestInfoById( pInfo.DestQuestID );
	std::string targetStr = s_CUI_ID_FRAME_Task.GetQuestTargetInfo( pQuestInfo, pQInfo );
	m_pID_TEXT_QuestEntrustInfo->SetText( targetStr );

	//显示给予的 金币或者 元宝的奖励	
	std::string strMoney="";
	thePlayerRole.GetGSCStringFromMoney(pInfo.EntrustRewardSum,strMoney);
	m_pID_TEXT_QuestEntrustReward->SetText(strMoney.c_str());
	//显示给予物品的奖励
	ControlIconDrag::S_ListImg pItems;
	pItems.SetData(&pInfo.ItemInfo);
	m_pID_LISTIMG_Item->SetItem(&pItems,0);

	strMoney = "";
	unsigned int MoneySum = m_Config.GetQuestMoneySum(pInfo.SrcQuestID);
	thePlayerRole.GetGSCStringFromMoney(MoneySum,strMoney);
	m_pID_TEXT_MoneySum->SetText(strMoney.c_str());
}
int CUI_ID_FRAME_QuestEntrust::SetNameAndRewardToList(unsigned int ID)
{
	if(QuestEntrustList.empty() || QuestEntrustList.count(ID) == 0)
		return -1;
	QuestEntrustStates& pInfo = QuestEntrustList[ID];
	SQuest* pQuestInfo = theQuestManager.GetQuest(pInfo.DestQuestID);
	if(!pQuestInfo)
		return -1;
	//设置名称 和 奖励 	
	std::string strMoney="";
	thePlayerRole.GetGSCStringFromMoney(pInfo.EntrustRewardSum,strMoney);
	ControlList::S_List pItems;
	pItems.SetData(strMoney.c_str());
	m_pID_LIST_QuestEntrustReward->AddItem(&pItems, NULL, false);
	pItems.clear();
	//设置委托任务名称
	char Name[256] = {0};
	if(pInfo.DestPlayerID != 0)
	{
		sprintf_s(Name,256,"%s%s",pQuestInfo->GetQuestName(),theXmlString.GetString(eText_QuestEnterst_QuestStates));
	}
	else
	{
		strcpy_s(Name,256,pQuestInfo->GetQuestName());
	}
	pItems.SetData(Name,0,0,theHeroGame.GetPlayerMgr()->GetQuestRankColor(pQuestInfo));
	m_pID_LIST_QuestEntrustName->AddItem(&pItems, NULL, false);
	pItems.clear();
	return m_pID_LIST_QuestEntrustName->GetListItemCnt()-1;
}
void CUI_ID_FRAME_QuestEntrust::SetSelectList(unsigned int Row)
{
	unsigned int NowID = 0;
	if(IndexToIDMap.count(Row) == 1)
		NowID = IndexToIDMap[Row];
	else
		NowID = -1;
	if(NowID == -1)
		return;
	//1.设置List的选择
	m_pID_LIST_QuestEntrustReward->SetCurSelIndex(Row);
	m_pID_LIST_QuestEntrustName->SetCurSelIndex(Row);
	//2.设置具体信息的显示
	SetQuestEntrustInfoToUI(NowID);
}
void CUI_ID_FRAME_QuestEntrust::NeedGetAllData()
{
	MsgLoadQuestEntrustDataReq msg;
	GettheNetworkInput().SendMsg(&msg);
}
bool CUI_ID_FRAME_QuestEntrust::IfCanJoinQuest(unsigned int QuestID)
{
	//判断指定任务是否可以接取
	SQuest* pQuest = theQuestManager.GetQuest( QuestID );
    if ( pQuest == NULL )
		return false;
	CPlayerRole::QuestInfo* pQInfo = thePlayerRole.FindQuestInfoById( QuestID );
	if(!pQInfo)
		return false;
	uint8 countryID = thePlayerRole.GetCountry();
	if (pQuest->Country!=0 && countryID!=pQuest->Country)
		return false;
	if(pQInfo->chState != QuestManager::eQuestNotGain)
		return false;//只有未接取的任务才可以再接取

	SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
    SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
    for( ; itr != end; ++itr )
    {
        switch ( itr->byType )
        {
        case SQuest::eRequirement_Money:                    // 检查钱是否足够
            {
                if ( thePlayerRole.PackHasEnoughMoney( itr->Value))
                {
                    return false;
                }
            }       
            break;
        case SQuest::eRequirement_Item:                     //检查该道具的个数是否满足接任务的条件
            {
				int nCount =thePlayerRole.m_bagMaterial.GetItemCount(itr->Value)
					+ thePlayerRole.m_bag.GetItemCount(itr->Value)
					+ thePlayerRole.m_bagTask.GetItemCount(itr->Value);
                if( nCount < itr->MaxNum )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Energy:                   // 判断活力值
            {
                if (thePlayerRole.GetCharInfo2().baseinfo.liveinfo.activity < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Level:                    // 判断等级
            {
				if ( thePlayerRole.GetLevel() < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Reputation:               // 判断声望
            {
                if ( thePlayerRole.GetData(CPlayerRole::TYPE_Reputation) < itr->Value )
				{
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Sex:                      // 判断性别
            {
                if ( itr->Value != Sex_Max && itr->Value != thePlayerRole.GetCharInfo2().baseinfo.aptotic.ucSex )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_SocialRelation:
            {
            }
            break;
        case SQuest::eRequirement_Profession:               //主要用于多兵种限制，1位移职业判断一下是否存允许该职业
            {
                if ( ( itr->Value & ( 1 << thePlayerRole.GetCharInfo2().baseinfo.aptotic.usProfession ) ) == 0 )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Quest: // 前置任务
            {
				CPlayerRole::QuestInfo* pWQInfo = thePlayerRole.FindQuestInfoById(  itr->Value );
				if(pWQInfo && pWQInfo->chState == QuestManager::eQuestDone)
				{
					return false;
				}
            }
            break;
        case SQuest::eRequirement_WeakCountry: 
            { // 弱国任务
                if ( thePlayerRole.GetWeakCountryID() != thePlayerRole.GetCountry() )
                { return false; }
            }
            break;
        case SQuest::eRequirement_Status:
			{		
                if ( !theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsHaveStatus( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_NoStatus:   
            {
                if (theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsHaveStatus( itr->Value ) )
                { return false; }
            }
            break;
        case SQuest::eRequirement_XinFaLevel:   
            {
                if ( itr->Value == 0 )
                {
                    int nMaxLevel = 0;
                    for ( int i=0; i<thePlayerRole.m_xinFaBag.GetXinFaNum(); ++i )
                    {
                        SCharXinFa* pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByIndex( i );
                        if ( pCharXinFa != NULL && pCharXinFa->nXinFaLevel > nMaxLevel )
                        { nMaxLevel = pCharXinFa->nXinFaLevel; }
                    }

                    if ( itr->MaxNum > nMaxLevel  )
                    { return false; }
                }
                else
                {
                    SCharXinFa* pCharXinFa = thePlayerRole.m_xinFaBag.GetXinFaByID( itr->Value );
                    if ( pCharXinFa == NULL || itr->MaxNum > pCharXinFa->nXinFaLevel )
                    { return false; }
                }
            }
            break;
        case SQuest::eRequirement_PetNumber:
            {
                if ( itr->Value >thePlayerRole.GetPetCount())
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetLevel:       
            {
				uint16 MaxLevel = 0;
				for(size_t i=0;i<thePlayerRole.GetPetCount();++i)
				{
					if(thePlayerRole.GetPetByIndex(i).baseInfo.level > MaxLevel)
						MaxLevel = thePlayerRole.GetPetByIndex(i).baseInfo.level;
				}
				if ( itr->Value > MaxLevel  )
                { return false; }
            }
            break;
        case SQuest::eRequirement_PetID :     
            {
				bool IsExites = false;
				for(size_t i=0;i<thePlayerRole.GetPetCount();++i)
				{
					if(thePlayerRole.GetPetByIndex(i).baseInfo.petId == itr->Value)
					{
						IsExites = true;
						break;
					}
				}
				if(!IsExites)
					return false;
            }
            break;
        case SQuest::eRequirement_PetType:   
            {
				bool IsExites = false;
				for(size_t i=0;i<thePlayerRole.GetPetCount();++i)
				{
					if(thePlayerRole.GetPetByIndex(i).baseInfo.petType == itr->Value)
					{
						IsExites = true;
						break;
					}
				}
				if(!IsExites)
					return false;
            }
            break;
        case SQuest::eRequirement_PetActive: 
            {
				if ( thePlayerRole.GetActivedPetIndex() == -1 )
                { return false; }
            }
            break;
        default:
            break;
        };
    }
	return true;
}
void CUI_ID_FRAME_QuestEntrust::ShowLastTime()
{
	if(m_LastTime !=0)
	{
		time_t nowtime;
		time(&nowtime);
		nowtime +=theHeroGame.GetServerAndLocalOffsetTime();
		int SpanTime =m_LastTime - nowtime;
		if(SpanTime <0)
			SpanTime = 0;
		//根据时间获取具体的字符串
		int Hour = SpanTime/3600;//小时
		int Min = (SpanTime%3600)/60;
		int Sec = SpanTime%60;
		char TimeStr[64];
		sprintf_s(TimeStr,63,"%s %d:%d:%d",theXmlString.GetString(eText_QuestEntrust_EndTimeLast),Hour,Min,Sec);
		if(m_pID_TEXT_LastTime)
			m_pID_TEXT_LastTime->SetText(TimeStr);
	}
	else
	{
		if(m_pID_TEXT_LastTime)
			m_pID_TEXT_LastTime->SetText("");
	}
}