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
	//ÿ��������Update��
	//static unsigned int TimeLog = 0;
	//if(timeGetTime() - TimeLog >= 5000)
	//{
	//	TimeLog = timeGetTime();
	//	NeedGetAllData();//�������е���Դ
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
	//ȡ���Լ���ί��
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//��ʾ��Ҵ���
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//ָ��ί�в�����
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].SrcPlayerID != thePlayerRole.GetDBID())
	{
		//�����Լ�������ί�� ������ȡ��
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
	//ȡ���Ѿ���ȡ��ί��
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//��ʾ��Ҵ���
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//ָ��ί�в�����
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].DestPlayerID != thePlayerRole.GetDBID())
	{
		//�����Լ�������ί�� ����ȡ��
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
	//��ȡ�µ�ί��
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//��ʾ��Ҵ���
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//ָ��ί�в�����
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
		//��ǰ״̬�����Խ�ȡί��
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_JoinBuff));
		return false;
	}
	//�ж�Ѻ���Ƿ��㹻
	unsigned int MoneySum = m_Config.GetQuestMoneySum(QuestEntrustList[ID].SrcQuestID);
	if(!thePlayerRole.PackHasEnoughMoney(MoneySum))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonMoneySum));
		return false;
	}
	//�ж��Ƿ��Ѿ���ȡί����
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
	//�жϵ�ǰ�����Ƿ���Խ�ȡ
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
	//ˢ�°�ť
	NeedGetAllData();
	return true;
}
bool CUI_ID_FRAME_QuestEntrust::ID_BUTTON_GetRewardOnButtonClick( ControlObject* pSender )
{
	//�ύ����˵�ί��
	unsigned int ID = IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex())==1?IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()]:-1;
	if(ID == -1)
	{
		//��ʾ��Ҵ���
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_QuestIDError));
		return false;
	}
	if(QuestEntrustList.count(ID) == 0)
	{
		//ָ��ί�в�����
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonEntrust));
		return false;

	}
	if(QuestEntrustList[ID].DestPlayerID != thePlayerRole.GetDBID())
	{
		//�����Լ�������ί�� ����ȡ��
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_QuestEntrust_NonSec));
		return false;
	}
	//�ж������״̬
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
// װ��UI
bool CUI_ID_FRAME_QuestEntrust::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\QuestEntrust.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("��ȡ�ļ�[Data\\UI\\QuestEntrust.MEUI]ʧ��")
		return false;
	}
	return DoControlConnect();
}
// �����ؼ�
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
	// ж��UI
bool CUI_ID_FRAME_QuestEntrust::_UnLoadUI()
{
	m_pID_FRAME_QuestEntrust = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\QuestEntrust.MEUI" );
}
// �Ƿ����
bool CUI_ID_FRAME_QuestEntrust::_IsVisable()
{
	return m_pID_FRAME_QuestEntrust->IsVisable();
}
// �����Ƿ����
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
	// �ж��Ƿ���Ҫ �´��������
	if(m_IsNeedClear)
	{
		QuestEntrustList.clear();
		m_IsNeedClear = false;
	}
	for(int i =0;i<Sum;++i)
	{
		//���й��˴���
		//�ж��Ƿ���Խ�ȡ����
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
	//����UI������չʾ������
	if(!m_pID_FRAME_QuestEntrust)
		return;
	unsigned int NowID = 0;
	if(IndexToIDMap.count(m_pID_LIST_QuestEntrustName->GetCurSelIndex()) == 1)
		NowID = IndexToIDMap[m_pID_LIST_QuestEntrustName->GetCurSelIndex()];
	else
		NowID = -1;
	//��ȡ����ǰѡ���ID�� ���ǿ�ʼ���Ui
	//���µ�ֵ���õ�UI����ȥ
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
	//�����п��Խ�ȡ��ί�� ��ʾ����
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
	//��ʼ�����ݼ���UI����ȥ
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//���˵� �ҷ����� �� �ҽ�ȡ�� 
		if(Iter->second.IsSecc)
			continue;
		if(Iter->second.SrcPlayerID == thePlayerRole.GetDBID() || Iter->second.DestPlayerID != 0)
			continue;
		//�ж��Ƿ�Ϊһ�����ҵ�
		SQuest * pQuest = theQuestManager.GetQuest(Iter->second.DestQuestID);
		if(!pQuest || (pQuest->Country !=0 &&  pQuest->Country != thePlayerRole.GetCountry()) )
			continue;
		if(IsShowNeed && !IfCanJoinQuest(Iter->second.DestQuestID))
		{
			continue;
		}
		//1.�����ݼ��ص�Ui����ȥ
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.��ί�еľ�����Ϣ��ʾ����
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
	//��ʼ�����ݼ���UI����ȥ
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//���˵� �ҷ�����
		if(Iter->second.IsSecc)
			continue;
		if(Iter->second.SrcPlayerID != thePlayerRole.GetDBID())
			continue;
		//1.�����ݼ��ص�Ui����ȥ
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.��ί�еľ�����Ϣ��ʾ����
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
	//��ʼ�����ݼ���UI����ȥ
	//std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustList.begin();
	for(;Iter != QuestEntrustList.end();++Iter)
	{
		//���˵� �ҽ�ȡ��
		if(Iter->second.IsSecc)
			continue;
		if(thePlayerRole.GetDBID() != Iter->second.DestPlayerID)
			continue;
		//1.�����ݼ��ص�Ui����ȥ
		int Row = SetNameAndRewardToList(Iter->first);
		IndexToIDMap.insert(std::map<int,unsigned int>::value_type(Row,Iter->first));
		//2.��ί�еľ�����Ϣ��ʾ����
		if(Iter->first == SelectID)
		{
			SetSelectList(Row);
		}
		//3.���õ���ʱ m_LastTime ����ʱ�亯�� �жϵ�ǰʱ�䵽 ����11:59:59�� �Ǹ�����
		time_t joinTime = Iter->second.ReceiveLogTime;
		time_t EndTime = joinTime + GetConfig().GetLastTime()/1000;//���Ϻ��ʵ�����
		time_t StopTime = 0;
		if(joinTime/86400 != EndTime/86400)
		{
			StopTime = (joinTime - joinTime%86400) + 86399;
		}
		else
			StopTime = EndTime;
		//�ó�����ʱ��� �����ж�����
		m_LastTime = StopTime;
	}
}
void CUI_ID_FRAME_QuestEntrust::SetQuestEntrustInfoToUI(unsigned int ID)
{
	//��ʾ����ί�еľ�����Ϣ
	if(QuestEntrustList.empty() || QuestEntrustList.count(ID) == 0)
		return;
	QuestEntrustStates& pInfo = QuestEntrustList[ID];
	//���þ�����Ϣ ��������ID��ȡ���������
	SQuest* pQuestInfo = theQuestManager.GetQuest(pInfo.DestQuestID);
	if(!pQuestInfo )
		return;
	m_pID_TEXT_QuestEntrustName->SetText(pQuestInfo->GetQuestName());
	std::string infoStr = pQuestInfo->GetQuestInfo();
	m_pID_TEXT_QuestEntrustDepict->SetText( infoStr);

	CPlayerRole::QuestInfo* pQInfo = thePlayerRole.FindQuestInfoById( pInfo.DestQuestID );
	std::string targetStr = s_CUI_ID_FRAME_Task.GetQuestTargetInfo( pQuestInfo, pQInfo );
	m_pID_TEXT_QuestEntrustInfo->SetText( targetStr );

	//��ʾ����� ��һ��� Ԫ���Ľ���	
	std::string strMoney="";
	thePlayerRole.GetGSCStringFromMoney(pInfo.EntrustRewardSum,strMoney);
	m_pID_TEXT_QuestEntrustReward->SetText(strMoney.c_str());
	//��ʾ������Ʒ�Ľ���
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
	//�������� �� ���� 	
	std::string strMoney="";
	thePlayerRole.GetGSCStringFromMoney(pInfo.EntrustRewardSum,strMoney);
	ControlList::S_List pItems;
	pItems.SetData(strMoney.c_str());
	m_pID_LIST_QuestEntrustReward->AddItem(&pItems, NULL, false);
	pItems.clear();
	//����ί����������
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
	//1.����List��ѡ��
	m_pID_LIST_QuestEntrustReward->SetCurSelIndex(Row);
	m_pID_LIST_QuestEntrustName->SetCurSelIndex(Row);
	//2.���þ�����Ϣ����ʾ
	SetQuestEntrustInfoToUI(NowID);
}
void CUI_ID_FRAME_QuestEntrust::NeedGetAllData()
{
	MsgLoadQuestEntrustDataReq msg;
	GettheNetworkInput().SendMsg(&msg);
}
bool CUI_ID_FRAME_QuestEntrust::IfCanJoinQuest(unsigned int QuestID)
{
	//�ж�ָ�������Ƿ���Խ�ȡ
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
		return false;//ֻ��δ��ȡ������ſ����ٽ�ȡ

	SQuest::RequirementTypeItr itr = pQuest->stReceiveRequirement.begin();
    SQuest::RequirementTypeItr end = pQuest->stReceiveRequirement.end();
    for( ; itr != end; ++itr )
    {
        switch ( itr->byType )
        {
        case SQuest::eRequirement_Money:                    // ���Ǯ�Ƿ��㹻
            {
                if ( thePlayerRole.PackHasEnoughMoney( itr->Value))
                {
                    return false;
                }
            }       
            break;
        case SQuest::eRequirement_Item:                     //���õ��ߵĸ����Ƿ���������������
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
        case SQuest::eRequirement_Energy:                   // �жϻ���ֵ
            {
                if (thePlayerRole.GetCharInfo2().baseinfo.liveinfo.activity < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Level:                    // �жϵȼ�
            {
				if ( thePlayerRole.GetLevel() < itr->Value )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Reputation:               // �ж�����
            {
                if ( thePlayerRole.GetData(CPlayerRole::TYPE_Reputation) < itr->Value )
				{
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Sex:                      // �ж��Ա�
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
        case SQuest::eRequirement_Profession:               //��Ҫ���ڶ�������ƣ�1λ��ְҵ�ж�һ���Ƿ�������ְҵ
            {
                if ( ( itr->Value & ( 1 << thePlayerRole.GetCharInfo2().baseinfo.aptotic.usProfession ) ) == 0 )
                {
                    return false;
                }
            }
            break;
        case SQuest::eRequirement_Quest: // ǰ������
            {
				CPlayerRole::QuestInfo* pWQInfo = thePlayerRole.FindQuestInfoById(  itr->Value );
				if(pWQInfo && pWQInfo->chState == QuestManager::eQuestDone)
				{
					return false;
				}
            }
            break;
        case SQuest::eRequirement_WeakCountry: 
            { // ��������
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
		//����ʱ���ȡ������ַ���
		int Hour = SpanTime/3600;//Сʱ
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