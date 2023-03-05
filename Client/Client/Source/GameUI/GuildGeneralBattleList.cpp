/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\GuildGeneralBattleList.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildGeneralBattleList.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "Common.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "ScreenInfoManager.h"
#include "Create.h"
#include "GameBattleDefine.h"
#include "GameBattleMessage.h"
#include "TimeEx.h"
#include "GuildBaseInfo.h"

const static int MAX_GUILDGENERALBATTLE_PAGEMAX = 9;

CUI_ID_FRAME_GuildGeneralBattleList s_CUI_ID_FRAME_GuildGeneralBattleList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildGeneralBattleList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildGeneralBattleList, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMasterNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildLevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildRoleSumOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMoneyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMIssionOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_MoneyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_BeginTimeOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_BUTTON_UpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_BUTTON_DownOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildGeneralBattleList, ID_LIST_AllOnListSelectChange )
CUI_ID_FRAME_GuildGeneralBattleList::CUI_ID_FRAME_GuildGeneralBattleList()
{
	// Member
	m_pID_FRAME_GuildGeneralBattleList = NULL;
	m_pID_LIST_GuildName = NULL;
	m_pID_LIST_GuildMasterName = NULL;
	m_pID_LIST_GuildLevel = NULL;
	m_pID_LIST_GuildRoleSum = NULL;
	m_pID_LIST_GuildMoney = NULL;
	m_pID_LIST_GuildMIssion = NULL;
	m_pID_LIST_Money = NULL;
	m_pID_LIST_BeginTime = NULL;
	m_pID_BUTTON_Up = NULL;
	m_pID_BUTTON_Down = NULL;
	m_pID_TEXT_PageInfo = NULL;
	m_pID_LIST_All = NULL;
	m_IsLoad = false;
	m_NowPage= 0;
}
// Frame
bool CUI_ID_FRAME_GuildGeneralBattleList::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildGeneralBattleList::OnFrameRender()
{
	return true;
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildMasterNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildRoleSumOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildMoneyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_GuildMIssionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_MoneyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_BeginTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
void CUI_ID_FRAME_GuildGeneralBattleList::ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_GuildGeneralBattleList::ID_BUTTON_UpOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GuildGeneralBattleList)
		return false;
	int Page = m_NowPage - 1;
	ShowGuildInfoByPage(Page);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildGeneralBattleList::ID_BUTTON_DownOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_GuildGeneralBattleList)
		return false;
	int Page = m_NowPage + 1;
	ShowGuildInfoByPage(Page);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildGeneralBattleList::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildGeneralBattleList.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildGeneralBattleList.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildGeneralBattleList::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildGeneralBattleList, s_CUI_ID_FRAME_GuildGeneralBattleListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildGeneralBattleList, s_CUI_ID_FRAME_GuildGeneralBattleListOnFrameRender );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildName, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMasterName, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildMasterNameOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildLevel, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildLevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildRoleSum, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildRoleSumOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMoney, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildMoneyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMIssion, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_GuildMIssionOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_Money, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_MoneyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildGeneralBattleList, ID_LIST_BeginTime, s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_BeginTimeOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GuildGeneralBattleList, ID_BUTTON_Up, s_CUI_ID_FRAME_GuildGeneralBattleListID_BUTTON_UpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildGeneralBattleList, ID_BUTTON_Down, s_CUI_ID_FRAME_GuildGeneralBattleListID_BUTTON_DownOnButtonClick );
	theUiManager.OnListSelectChange(ID_FRAME_GuildGeneralBattleList,ID_LIST_All,s_CUI_ID_FRAME_GuildGeneralBattleListID_LIST_AllOnListSelectChange);	

	m_pID_FRAME_GuildGeneralBattleList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildGeneralBattleList );
	m_pID_LIST_GuildName = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildName );
	m_pID_LIST_GuildMasterName = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMasterName );
	m_pID_LIST_GuildLevel = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildLevel );
	m_pID_LIST_GuildRoleSum = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildRoleSum );
	m_pID_LIST_GuildMoney = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMoney );
	m_pID_LIST_GuildMIssion = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_GuildMIssion );
	m_pID_LIST_Money = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_Money );
	m_pID_LIST_BeginTime = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_BeginTime );
	m_pID_BUTTON_Up = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_BUTTON_Up );
	m_pID_BUTTON_Down = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_BUTTON_Down );
	m_pID_TEXT_PageInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_TEXT_PageInfo );
	m_pID_LIST_All= (ControlList*)theUiManager.FindControl( ID_FRAME_GuildGeneralBattleList, ID_LIST_All );
	assert( m_pID_FRAME_GuildGeneralBattleList );
	assert( m_pID_LIST_GuildName );
	assert( m_pID_LIST_GuildMasterName );
	assert( m_pID_LIST_GuildLevel );
	assert( m_pID_LIST_GuildRoleSum );
	assert( m_pID_LIST_GuildMoney );
	assert( m_pID_LIST_GuildMIssion );
	assert( m_pID_LIST_Money );
	assert( m_pID_LIST_BeginTime );
	assert( m_pID_BUTTON_Up );
	assert( m_pID_BUTTON_Down );
	assert( m_pID_TEXT_PageInfo );
	assert( m_pID_LIST_All );
	m_pID_FRAME_GuildGeneralBattleList->SetFather(s_CUI_ID_FRAME_GuildBaseInfo.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildGeneralBattleList::_UnLoadUI()
{
	m_pID_FRAME_GuildGeneralBattleList = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildGeneralBattleList.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildGeneralBattleList::_IsVisable()
{
	return m_pID_FRAME_GuildGeneralBattleList->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildGeneralBattleList::_SetVisable( const bool bVisable )
{
	if(bVisable)
	{
		if(!m_IsLoad)
		{
			MsgLoadCampBattleDataReq msg;
			GettheNetworkInput().SendMsg(&msg);
			m_IsLoad = true;
		}
		OnInit();
	}
	m_pID_FRAME_GuildGeneralBattleList->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildGeneralBattleList::OnInit()
{
	//初始化UI
	ShowGuildInfoByPage();
}
void CUI_ID_FRAME_GuildGeneralBattleList::ShowGuildInfoByPage(int Page)
{
	//显示指定页面的数据
	if(!m_pID_FRAME_GuildGeneralBattleList)
		return;
	m_pID_BUTTON_Up->SetEnable(false);
	m_pID_BUTTON_Down->SetEnable(false);
	m_pID_TEXT_PageInfo->SetText("0/0");
	//2.清空列表上的数据
	m_pID_LIST_GuildName ->Clear();
	m_pID_LIST_GuildMasterName ->Clear();
	m_pID_LIST_GuildLevel ->Clear();
	m_pID_LIST_GuildRoleSum ->Clear();
	m_pID_LIST_GuildMoney ->Clear();
	m_pID_LIST_GuildMIssion ->Clear();
	m_pID_LIST_Money ->Clear();
	m_pID_LIST_BeginTime ->Clear();
	m_pID_LIST_All->Clear();
	//3.获取当前新的数据进行设置
	if(pList.empty()) return;
	int GuildSum = pList.size();
	int MaxPage =  GuildSum%MAX_GUILDGENERALBATTLE_PAGEMAX==0?(GuildSum/MAX_GUILDGENERALBATTLE_PAGEMAX):(GuildSum/MAX_GUILDGENERALBATTLE_PAGEMAX +1);//总页数
	if(Page > MaxPage)
		Page = MaxPage;
	if(Page<1)
		Page = 1;
	m_NowPage = Page;//记录当前页数
	//4.页数数据设置到UI上面去
	char szPageNum[256];
	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char)-1,"%d/%d",Page,MaxPage);
	m_pID_TEXT_PageInfo->SetText(szPageNum);
	//5.根据上一页 下一页 设置按钮的状态
	if(MaxPage == 1)
	{
		m_pID_BUTTON_Up->SetEnable(false);
		m_pID_BUTTON_Down->SetEnable(false);
	}
	else if(Page == 1)
	{
		m_pID_BUTTON_Up->SetEnable(false);
		m_pID_BUTTON_Down->SetEnable(true);
	}
	else if(Page == MaxPage)
	{
		m_pID_BUTTON_Up->SetEnable(true);
		m_pID_BUTTON_Down->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_Up->SetEnable(true);
		m_pID_BUTTON_Down->SetEnable(true);
	}
	//6.将集合里指定范围的数据设置到UI上面去
	int nStart = (Page - 1) *  MAX_GUILDGENERALBATTLE_PAGEMAX;
	int nEnd = Page * MAX_GUILDGENERALBATTLE_PAGEMAX;
	map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = pList.begin();
	int Index = 0;
	for(;Iter != pList.end(); ++Iter,++Index)
	{
		if(Index >= nStart && Index<nEnd)
		{
			char str_name[64] = {0};
			char str_level[64] ={0};
			char str_num[64] ={0};
			char str_MasterName[64] ={0};
			char str_GuildMission[64] = {0};
			char str_BeginTime[64] = {0};
			const CGuildInfo* pGuild = thePlayerRole.GetGuildById(Iter->second.SrcGuildID == thePlayerRole.GetGangMgr()->GetGuildID()?Iter->second.DestGuildID:Iter->second.SrcGuildID);
			if(!pGuild)
				continue;

			MeSprintf_s(str_name, sizeof(str_name)/sizeof(char) - 1, "%s", pGuild->GetName());//名字
			MeSprintf_s(str_level,sizeof(str_level)/sizeof(char)-1,"%d",pGuild->GetLevel());//等级
			MeSprintf_s(str_num,sizeof(str_num)/sizeof(char)-1,"%d",pGuild->GetMemberNum());//人数
			MeSprintf_s(str_MasterName,sizeof(str_MasterName)/sizeof(char)-1,"%s",pGuild->GetMasterName() );//帮主	
			std::string strGuildMoney="";
			if(Iter->second.GuildMoneySum != 0)
				thePlayerRole.GetGSCStringFromMoney(Iter->second.GuildMoneySum,strGuildMoney);
			std::string strMoney = "";
			if(Iter->second.MoneySum != 0)
				thePlayerRole.GetGSCStringFromMoney(Iter->second.MoneySum,strMoney);
			time_t tt = Iter->second.BeginTime;
			struct tm sysNowTime(*localtime(&tt));
			sprintf_s(str_BeginTime,63,"%d-%d %d:%d",sysNowTime.tm_mon+1,sysNowTime.tm_mday,sysNowTime.tm_hour,sysNowTime.tm_min);
			sprintf_s(str_GuildMission,63,"%d",Iter->second.GuildMissionSum);
			AddToList(str_name,str_level,str_num,str_MasterName,strGuildMoney.c_str(),strMoney.c_str(),str_GuildMission,str_BeginTime);
		}
	}
}
void CUI_ID_FRAME_GuildGeneralBattleList::ClearData()
{
	pList.clear();
	m_NowPage = 0;
	m_IsLoad = false;
}
void CUI_ID_FRAME_GuildGeneralBattleList::AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername,
													const char * GuildMoney,const char* Money,const char* GuildMission,const char* BeginTime)
{
	ControlList::S_List	pItem;
	pItem.SetData(m_GuildName, 0, NULL, 0);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
	m_pID_LIST_GuildName->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(level);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildLevel->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(num);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildRoleSum->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(Mastername);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildMasterName->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData(GuildMoney);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_RIGHT);
	m_pID_LIST_GuildMoney->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData(Money);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_RIGHT);
	m_pID_LIST_Money->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData(GuildMission);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_GuildMIssion->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData(BeginTime);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_BeginTime->AddItem(&pItem,NULL,false);	

	pItem.clear();
	pItem.SetData("");
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_All->AddItem(&pItem,NULL,false);	
}

void CUI_ID_FRAME_GuildGeneralBattleList::AddNewGuildGenetal(GameBattleDefine::GuildCampBattle& pData)
{
	//添加新的数据
	if(pList.count(pData.ID) != 0)
		return;
	pList.insert(map<unsigned int,GameBattleDefine::GuildCampBattle>::value_type(pData.ID,pData));
	ShowGuildInfoByPage(m_NowPage);
}
void CUI_ID_FRAME_GuildGeneralBattleList::LoadGuildGeneral(GameBattleDefine::GuildCampBattle& pData)
{
	if(pList.count(pData.ID) != 0)
		return;
	pList.insert(map<unsigned int,GameBattleDefine::GuildCampBattle>::value_type(pData.ID,pData));
}
void CUI_ID_FRAME_GuildGeneralBattleList::DelGuildGeneral(unsigned int ID)
{
	if(pList.count(ID) != 1)
		return;
	pList.erase(ID);
	ShowGuildInfoByPage(m_NowPage);
}
void CUI_ID_FRAME_GuildGeneralBattleList::OnUpdateUiInfo()
{
	
}
void CUI_ID_FRAME_GuildGeneralBattleList::OnShow()
{
	SetVisable(true);
}