/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildCampBattle.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildCampBattle.h"
#include "XmlStringLanguage.h"
#include "GuildBaseInfo.h"
#include "ScreenInfoManager.h"
#include "GuildCampBattleConfig.h"
#include "PlayerRole.h"
CUI_ID_FRAME_CampBattle s_CUI_ID_FRAME_CampBattle;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CampBattle, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CampBattle, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattle, ID_LIST_CampBattleTypeOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattle, ID_LIST_ExitesOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CampBattle, ID_BUTTON_AddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CampBattle, ID_BUTTON_DelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_CampBattle, ID_LIST_NoneOnListSelectChange )
CUI_ID_FRAME_CampBattle::CUI_ID_FRAME_CampBattle()
{
	// Member
	m_pID_FRAME_CampBattle = NULL;
	m_pID_LIST_CampBattleType = NULL;
	m_pID_LIST_Exites = NULL;
	m_pID_BUTTON_Add = NULL;
	m_pID_BUTTON_Del = NULL;
	m_pID_LIST_None = NULL;

}
// Frame
bool CUI_ID_FRAME_CampBattle::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_CampBattle::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_CampBattle::ID_LIST_CampBattleTypeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	OnSelectCampBattleType();
}
// List
void CUI_ID_FRAME_CampBattle::ID_LIST_ExitesOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	
}
// Button
bool CUI_ID_FRAME_CampBattle::ID_BUTTON_AddOnButtonClick( ControlObject* pSender )
{
	//当添加指定玩家到指定类型的战场的时候
	OnAddToCampBattle();
	return true;
}
// Button
bool CUI_ID_FRAME_CampBattle::ID_BUTTON_DelOnButtonClick( ControlObject* pSender )
{
	OnDelToCampBattle();
	return true;
}
// List
void CUI_ID_FRAME_CampBattle::ID_LIST_NoneOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}

// 装载UI
bool CUI_ID_FRAME_CampBattle::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildCampBattle.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildCampBattle.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_CampBattle::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CampBattle, s_CUI_ID_FRAME_CampBattleOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CampBattle, s_CUI_ID_FRAME_CampBattleOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattle, ID_LIST_CampBattleType, s_CUI_ID_FRAME_CampBattleID_LIST_CampBattleTypeOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattle, ID_LIST_Exites, s_CUI_ID_FRAME_CampBattleID_LIST_ExitesOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_CampBattle, ID_BUTTON_Add, s_CUI_ID_FRAME_CampBattleID_BUTTON_AddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_CampBattle, ID_BUTTON_Del, s_CUI_ID_FRAME_CampBattleID_BUTTON_DelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_CampBattle, ID_LIST_None, s_CUI_ID_FRAME_CampBattleID_LIST_NoneOnListSelectChange );

	m_pID_FRAME_CampBattle = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CampBattle );
	m_pID_LIST_CampBattleType = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattle, ID_LIST_CampBattleType );
	m_pID_LIST_Exites = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattle, ID_LIST_Exites );
	m_pID_BUTTON_Add = (ControlButton*)theUiManager.FindControl( ID_FRAME_CampBattle, ID_BUTTON_Add );
	m_pID_BUTTON_Del = (ControlButton*)theUiManager.FindControl( ID_FRAME_CampBattle, ID_BUTTON_Del );
	m_pID_LIST_None = (ControlList*)theUiManager.FindControl( ID_FRAME_CampBattle, ID_LIST_None );
	assert( m_pID_FRAME_CampBattle );
	assert( m_pID_LIST_CampBattleType );
	assert( m_pID_LIST_Exites );
	assert( m_pID_BUTTON_Add );
	assert( m_pID_BUTTON_Del );
	assert( m_pID_LIST_None );
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_CampBattle::_UnLoadUI()
{
	m_pID_FRAME_CampBattle = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildCampBattle.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_CampBattle::_IsVisable()
{
	return m_pID_FRAME_CampBattle->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_CampBattle::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnShow();
	m_pID_FRAME_CampBattle->SetVisable( bVisable );
}
void CUI_ID_FRAME_CampBattle::OnShow()
{
	//当UI显示的时候
	SetCampBattleType();
}
void CUI_ID_FRAME_CampBattle::SetCampBattleType()
{
	if(!m_pID_FRAME_CampBattle)
		return;
	m_pID_LIST_CampBattleType->Clear();

	ControlList::S_List stItem;
	//1.国王战
	strcpy_s(stItem.m_szText,255,theXmlString.GetString(eText_GuildCampBattle_Country));
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CampBattleType->AddItem(&stItem, NULL, false);
	stItem.clear();
	//2.公会战
	strcpy_s(stItem.m_szText,255,theXmlString.GetString(eText_GuildCampBattle_Guild));
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CampBattleType->AddItem(&stItem, NULL, false);
	stItem.clear();
	//3.公会联合站
	/*strcpy_s(stItem.m_szText,255,theXmlString.GetString(eText_GuildCampBattle_GuildUnion));
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CampBattleType->AddItem(&stItem, NULL, false);
	stItem.clear();*/
	//4.公会约战
	strcpy_s(stItem.m_szText,255,theXmlString.GetString(eText_GuildGeneralBattle_Name));
	stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CampBattleType->AddItem(&stItem, NULL, false);
	stItem.clear();

	m_pID_LIST_CampBattleType->SetCurSelIndex(0);
	OnSelectCampBattleType();
}
void CUI_ID_FRAME_CampBattle::OnSelectCampBattleType()
{
	if(!m_pID_FRAME_CampBattle)
		return;
	m_pID_LIST_Exites->Clear();
	m_pID_LIST_None->Clear();

	m_ExitesIndexToID.clear();
	m_NonIndexToID.clear();

	int Index = m_pID_LIST_CampBattleType->GetCurSelIndex();
	unsigned int Value = 0;
	switch(Index)
	{
	case 0:
		Value = GuildDefine::CampBattleCountry;
		break;
	case 1:
		Value = GuildDefine::CampBattleGuild;
		break;
	/*case 2:
		Value = GuildDefine::CampBattleGuildUnion;
		break;*/
	case 2:
		Value = GuildDefine::GameBattleGuildGeneral;
		break;
	}
	//变量所有的公会成员信息
	vector<GuildMember*>& vecListOnLine = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildOnLineMember();
	if(!vecListOnLine.empty())
	{
		vector<GuildMember*>::iterator Iter = vecListOnLine.begin();
		for(;Iter != vecListOnLine.end();++Iter)
		{
			ControlList::S_List stItem;
			strcpy_s(stItem.m_szText,255,(*Iter)->GetName());
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			if((*Iter)->GetCampBattleValue() & Value)
			{
				m_pID_LIST_Exites->AddItem(&stItem, NULL, false);
				m_ExitesIndexToID.push_back((*Iter)->GetID());
			}
			else
			{
				if(IsCanAddToCampBattle(*Iter,Value))
				{
					m_pID_LIST_None->AddItem(&stItem, NULL, false);
					m_NonIndexToID.push_back((*Iter)->GetID());
				}
			}
		}
	}
	vector<GuildMember*>& vecListNon = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildNonOnLineMember();
	if(!vecListNon.empty())
	{
		vector<GuildMember*>::iterator Iter = vecListNon.begin();
		for(;Iter != vecListNon.end();++Iter)
		{
			ControlList::S_List stItem;
			strcpy_s(stItem.m_szText,255,(*Iter)->GetName());
			stItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
			if((*Iter)->GetCampBattleValue() & Value)
			{	
				m_pID_LIST_Exites->AddItem(&stItem, NULL, false);
				m_ExitesIndexToID.push_back((*Iter)->GetID());
			}
			else
			{
				if(IsCanAddToCampBattle(*Iter,Value))
				{
					m_pID_LIST_None->AddItem(&stItem, NULL, false);
					m_NonIndexToID.push_back((*Iter)->GetID());
				}
			}
		}
	}
	//设置人数显示
	GuildCampBattleSetting * pSetting = NULL;
	switch(Value)
	{
	case GuildDefine::CampBattleCountry:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_CountrySetting;
		break;
	case GuildDefine::CampBattleGuild:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildSetting;
		break;
	/*case GuildDefine::CampBattleGuildUnion:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildUnionSetting;
		break;*/
	case GuildDefine::GameBattleGuildGeneral:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildGeneralSetting;
		break;
	}
	if(!pSetting) return;
	char szText[128] = {0};
	sprintf_s(szText, sizeof(szText)-1,"%d / %d",m_ExitesIndexToID.size(),pSetting->MaxSum);
	//将字符串设置到UI上面去
}
bool CUI_ID_FRAME_CampBattle::IsCanAddToCampBattle(GuildMember* pMember,unsigned int Value)
{	
	if(!pMember)
		return false;
	else if(pMember->GetCampBattleValue() & Value)
		return false;
	GuildCampBattleSetting * pSetting = NULL;
	switch(Value)
	{
	case GuildDefine::CampBattleCountry:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_CountrySetting;
		break;
	case GuildDefine::CampBattleGuild:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildSetting;
		break;
	/*case GuildDefine::CampBattleGuildUnion:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildUnionSetting;
		break;*/
	case GuildDefine::GameBattleGuildGeneral:
		pSetting  = &s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCampBattleConfig().m_GuildGeneralSetting;
		break;
	}
	if(!pSetting)
		return false;
	else if(pSetting->MinLevel > pMember->GetLevel())
		return false;
	else if(pSetting->Profession != pMember->GetProfession() && pSetting->Profession != 0)
		return false;
	else if(pSetting->Offer > pMember->GetOffer())
		return false;
	return true;
}
void CUI_ID_FRAME_CampBattle::OnAddToCampBattle()
{
	//将未加入列表的添加到列表去 一个列表转移到另外一个列表去
	//1.判断目标玩家是否存在
	ControlList::S_List * stItem = m_pID_LIST_None->GetCurSelItem();
	int Index = m_pID_LIST_None->GetCurSelIndex();
	if(!stItem || Index == -1)
	{
		//提示玩家 未选择
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_NonSelect));	
		return;
	}
	//2.获取目标的指针
	GuildMember * pMember = thePlayerRole.GetGangMgr()->FindByDBId(m_NonIndexToID[Index]);
	if(!pMember)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_NonSelect));	
		return;
	}
	//4.需要添加的权限值
	unsigned int NowValue = 0;
	switch(m_pID_LIST_CampBattleType->GetCurSelIndex())
	{
	case 0:
		NowValue = GuildDefine::CampBattleCountry;
		break;
	case 1:
		NowValue = GuildDefine::CampBattleGuild;
		break;
	/*case 2:
		NowValue = GuildDefine::CampBattleGuildUnion;
		break;*/
	case 2:
		NowValue = GuildDefine::GameBattleGuildGeneral;
		break;
	}
	s_CUI_ID_FRAME_GuildBaseInfo.SetMemberCampBattleValue(NowValue,pMember);
}
void CUI_ID_FRAME_CampBattle::OnDelToCampBattle()
{
	//移除一个玩家的权限
	ControlList::S_List * stItem = m_pID_LIST_Exites->GetCurSelItem();
	int Index = m_pID_LIST_Exites->GetCurSelIndex();
	if(!stItem || Index == -1)
	{
		//提示玩家 未选择
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_NonSelect));	
		return;
	}
	//2.获取目标的指针
	GuildMember * pMember = thePlayerRole.GetGangMgr()->FindByDBId(m_ExitesIndexToID[Index]);
	if(!pMember)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_GuildCampBattle_NonSelect));	
		return;
	}
	unsigned int NowValue = 0;
	switch(m_pID_LIST_CampBattleType->GetCurSelIndex())
	{
	case 0:
		NowValue = GuildDefine::CampBattleCountry;
		break;
	case 1:
		NowValue = GuildDefine::CampBattleGuild;
		break;
	/*case 2:
		NowValue = GuildDefine::CampBattleGuildUnion;
		break;*/
	case 2:
		NowValue = GuildDefine::GameBattleGuildGeneral;
		break;
	}
	s_CUI_ID_FRAME_GuildBaseInfo.DelMemberCampBattleValue(NowValue,pMember);
}	
void CUI_ID_FRAME_CampBattle::OnUpdateMemberInfo()
{
	OnSelectCampBattleType();
}