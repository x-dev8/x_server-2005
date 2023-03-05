/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildApply.cpp
*********************************************************************/
#include "MeUi/UiManager.h"
#include "GuildApply.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "GuildMessage.h"
#include "Common.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "TimeEx.h"
#include "ScreenInfoManager.h"
#include "Create.h"
bool SortByGreatLevel(CGuildInfo* s1, CGuildInfo* s2)
{
	return s1->GetLevel() > s2->GetLevel();
}

static void InitialChildList( ControlList* pLIST )
{
	pLIST->SetMsgHoldup(false);	//不接受消息
	pLIST->SetItemMaxCount( 100 );
	pLIST->HaveSelBar( false );	//没有绿色cur选中地图
	pLIST->SetCurSelIndex(-1);
	pLIST->SetDrawFlags(DT_CENTER|DT_NOCLIP);
}

const static DWORD ShowNumPerPage = 5;//每页显示的数据
long int CUI_ID_FRAME_GuildApply::m_sCurrentTime;
const static int CoolTime = 30000;
CUI_ID_FRAME_GuildApply s_CUI_ID_FRAME_GuildApply;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildApply, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildApply, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_ApplyOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_LIST_LevelOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_LIST_CDROnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_LIST_AmountOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_EDIT_4918OnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_BUTTON_SearchOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GuildApply, ID_LIST_GuildListOnListSelectChange )
CUI_ID_FRAME_GuildApply::CUI_ID_FRAME_GuildApply()
{
	// Member
	m_pID_FRAME_GuildApply = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_TEXT_GuildName = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_Member = NULL;
	m_pID_TEXT_GuildMaster = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_TEXT_CreateDate = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_BUTTON_Apply = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_LIST_Level = NULL;
	m_pID_LIST_CDR = NULL;
	m_pID_LIST_Amount = NULL;
	m_pID_TEXT_111 = NULL;
	m_pID_TEXT_222 = NULL;
	m_pID_TEXT_333 = NULL;
	m_pID_TEXT_444 = NULL;
	m_pID_EDIT_4918 = NULL;
	m_pID_BUTTON_Search = NULL;
	m_pID_LIST_GuildList = NULL;

	m_sCurrentTime = 0;
}
// Frame
bool CUI_ID_FRAME_GuildApply::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildApply::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	//上一页
	if(!m_pID_FRAME_GuildApply)
		return false;
	int Page = m_NowPage - 1;
	ShowGuildInfoByPage(Page);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	//下一页
	if(!m_pID_FRAME_GuildApply)
		return false;
	int Page = m_NowPage + 1;
	ShowGuildInfoByPage(Page);
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender )
{
	//申请加入公会
	//根据选择的公会
	if ( !m_pID_FRAME_GuildApply )
		return false;
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	char szTextTip[MAX_PATH] = {0};
	if(pGuild == NULL &&( !pGuild->GetGuildID() == GuildDefine::InitID))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, theXmlString.GetString(eText_Guild_AlreadyInGuild) );
		return false;
	}
	if (HQ_TimeGetTime() - m_sCurrentTime < CoolTime)
	{
		DWORD diff = (CoolTime - (HQ_TimeGetTime() - m_sCurrentTime)) * 0.001;
		sprintf_s(szTextTip, MAX_PATH - 1, theXmlString.GetString(eText_GuildApplyCooldownTip), diff);
		CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Guild_Belongs, szTextTip);
		return false;
	}
	if (theHeroGame.GetPlayerMgr()->GetMe()->GetLevel() >= 20)  //20级以上才可以申请加入帮会
	{
		ControlList::S_List* pItem = m_pID_LIST_GuildList->GetCurSelItem();
		if(!pItem) return false;
		char * GuildName = pItem->m_szText;
		std::vector<CGuildInfo*>::iterator Iter = m_vctGuild.begin();
		for(;Iter != m_vctGuild.end();++Iter)
		{
			if(_strcmpi((*Iter)->GetName(),GuildName) == 0)
			{
				MsgJoinGuildReq msg;
				msg.nGuildID = (*Iter)->GetID();
				GettheNetworkInput().SendMsg(&msg);
				ShowApplyingMessage();	
				break;
			}
		}
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Info_GuildInfo, theXmlString.GetString(eText_Guild_LessThanApplyLevel) );
	}
	m_sCurrentTime = HQ_TimeGetTime();
	return true;
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	//关闭
	return true;
}
// List
void CUI_ID_FRAME_GuildApply::ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildApply::ID_LIST_CDROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// List
void CUI_ID_FRAME_GuildApply::ID_LIST_AmountOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Edit
void CUI_ID_FRAME_GuildApply::ID_EDIT_4918OnEditEnter( ControlObject* pSender, const char* szData )
{
}
// Button
bool CUI_ID_FRAME_GuildApply::ID_BUTTON_SearchOnButtonClick( ControlObject* pSender )
{
	//搜索
	if ( !m_pID_FRAME_GuildApply )
		return false;
	std::string words = m_pID_EDIT_4918->GetText();
	if (!words.empty())
	{
		m_vctGuild.clear();
		if(theHeroGame.GetPlayerMgr()->GetMe())
		{
			unsigned char nMyCountry = theHeroGame.GetPlayerMgr()->GetMe()->GetRealCountry();
			int nAllGuild = thePlayerRole.GetGuildNum();
			for (int i = 0; i < nAllGuild; ++i)
			{
				if (!thePlayerRole.GetGuild(i))
					continue;
				if (thePlayerRole.GetGuild(i)->GetCountry() != nMyCountry)
					continue;
				std::string GuildName = thePlayerRole.GetGuild(i)->GetName();
				size_t index = GuildName.find(words.c_str());
				if (index != std::string.npos)
				{
					m_vctGuild.push_back(thePlayerRole.GetGuild(i));
				}
			}
			std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGreatLevel);
		}
		//数据设置完毕后
		ShowGuildInfoByPage();//显示数据
	}
	else
		OnInit();
	return true;
}
// List
void CUI_ID_FRAME_GuildApply::ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	//当玩家选择一个公会的时候 我们获取公会的ID
	if(!pItem) return;
	char * GuildName = pItem->m_szText;
	std::vector<CGuildInfo*>::iterator Iter = m_vctGuild.begin();
	for(;Iter != m_vctGuild.end();++Iter)
	{
		if(_strcmpi((*Iter)->GetName(),GuildName) == 0)
		{
			QueryGuildData((*Iter)->GetID());//设置获取公会的信息
			m_pID_BUTTON_Apply->SetEnable(true);
			break;
		}
	}
}
void CUI_ID_FRAME_GuildApply::QueryGuildData(int nGuildId)
{
	MsgQueryGuildDataReq msg;
	msg.nGuildID = nGuildId;
	GettheNetworkInput().SendMsg(&msg);
}
// 装载UI
bool CUI_ID_FRAME_GuildApply::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildApply.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildApply.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildApply::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildApply, s_CUI_ID_FRAME_GuildApplyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildApply, s_CUI_ID_FRAME_GuildApplyOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildApplyID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_PageUp, s_CUI_ID_FRAME_GuildApplyID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_HELP, s_CUI_ID_FRAME_GuildApplyID_BUTTON_HELPOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_PageDown, s_CUI_ID_FRAME_GuildApplyID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_Apply, s_CUI_ID_FRAME_GuildApplyID_BUTTON_ApplyOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GuildApplyID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildApply, ID_LIST_Level, s_CUI_ID_FRAME_GuildApplyID_LIST_LevelOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildApply, ID_LIST_CDR, s_CUI_ID_FRAME_GuildApplyID_LIST_CDROnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GuildApply, ID_LIST_Amount, s_CUI_ID_FRAME_GuildApplyID_LIST_AmountOnListSelectChange );
	theUiManager.OnEditEnter( ID_FRAME_GuildApply, ID_EDIT_4918, s_CUI_ID_FRAME_GuildApplyID_EDIT_4918OnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_GuildApply, ID_BUTTON_Search, s_CUI_ID_FRAME_GuildApplyID_BUTTON_SearchOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_GuildApply, ID_LIST_GuildList, s_CUI_ID_FRAME_GuildApplyID_LIST_GuildListOnListSelectChange );

	m_pID_FRAME_GuildApply = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildApply );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_CLOSE );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_PageUp );
	m_pID_TEXT_GuildName = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_GuildName );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_Level );
	m_pID_TEXT_Member = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_Member );
	m_pID_TEXT_GuildMaster = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_GuildMaster );
	m_pID_TEXT_Announcement = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_Announcement );
	m_pID_TEXT_CreateDate = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_CreateDate );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_HELP );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_PageDown );
	m_pID_BUTTON_Apply = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_Apply );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_Cancel );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_Page );
	m_pID_LIST_Level = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_LIST_Level );
	m_pID_LIST_CDR = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_LIST_CDR );
	m_pID_LIST_Amount = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_LIST_Amount );
	m_pID_TEXT_111 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_111 );
	m_pID_TEXT_222 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_222 );
	m_pID_TEXT_333 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_333 );
	m_pID_TEXT_444 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_TEXT_444 );
	m_pID_EDIT_4918 = (ControlEdit*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_EDIT_4918 );
	m_pID_BUTTON_Search = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_BUTTON_Search );
	m_pID_LIST_GuildList = (ControlList*)theUiManager.FindControl( ID_FRAME_GuildApply, ID_LIST_GuildList );
	assert( m_pID_FRAME_GuildApply );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_PageUp );
	assert( m_pID_TEXT_GuildName );
	assert( m_pID_TEXT_Level );
	assert( m_pID_TEXT_Member );
	assert( m_pID_TEXT_GuildMaster );
	assert( m_pID_TEXT_Announcement );
	assert( m_pID_TEXT_CreateDate );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_PageDown );
	assert( m_pID_BUTTON_Apply );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_Page );
	assert( m_pID_LIST_Level );
	assert( m_pID_LIST_CDR );
	assert( m_pID_LIST_Amount );
	assert( m_pID_TEXT_111 );
	assert( m_pID_TEXT_222 );
	assert( m_pID_TEXT_333 );
	assert( m_pID_TEXT_444 );
	assert( m_pID_EDIT_4918 );
	assert( m_pID_BUTTON_Search );
	assert( m_pID_LIST_GuildList );

	InitialChildList(m_pID_LIST_Level);
	InitialChildList(m_pID_LIST_Amount);
	InitialChildList(m_pID_LIST_CDR);

	m_pID_FRAME_GuildApply->SetVisable(false);
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_GuildApply::_UnLoadUI()
{
	m_pID_FRAME_GuildApply = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildApply.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildApply::_IsVisable()
{
	if(!m_pID_FRAME_GuildApply)
		return false;
	return m_pID_FRAME_GuildApply->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildApply::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GuildApply)
		return;
	if(bVisable)
	{
		OnInit();
		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	}
	else
		ImmAssociateContext( g_hWnd, NULL );

	m_pID_FRAME_GuildApply->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildApply::OnInit()
{
	//当UI打开的时候 我们怎么处理
	//让UI恢复到初始化状态
	//1.搜索栏清空
	m_pID_EDIT_4918->SetText("");
	//2.从新加载所有公会
	m_vctGuild.clear();
	if ((theHeroGame.GetPlayerMgr()->GetMe()))
	{
		unsigned char nMyCountry = theHeroGame.GetPlayerMgr()->GetMe()->GetRealCountry();
		int nAllGuild = thePlayerRole.GetGuildNum();
		for (int i = 0; i < nAllGuild; ++i)
		{
			if (!thePlayerRole.GetGuild(i))
				continue;
			if (thePlayerRole.GetGuild(i)->GetCountry() != nMyCountry)
				continue;
			m_vctGuild.push_back(thePlayerRole.GetGuild(i));
		}
		std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGreatLevel);
	}
	//3.公会数据加载到集合里面去了 我们应该讲数据显示到列表栏上面去了
	ShowGuildInfoByPage();
}
void CUI_ID_FRAME_GuildApply::ShowGuildInfoByPage(int Page)//用于翻页 或者初始化
{
	//1.设置Ui的状态 上一页 下一页
	m_pID_BUTTON_PageUp->SetEnable(false);
	m_pID_BUTTON_PageDown->SetEnable(false);
	m_pID_TEXT_Page->SetText("0/0");
	//2.清空列表上的数据
	m_pID_LIST_GuildList->Clear();
	m_pID_LIST_Level->Clear();
	m_pID_LIST_Amount->Clear();
	m_pID_LIST_CDR->Clear();
	//7.设置按钮的状态
	m_pID_BUTTON_Apply->SetEnable(false);
	//3.获取当前新的数据进行设置
	if(m_vctGuild.empty()) return;
	int GuildSum = m_vctGuild.size();
	int MaxPage =  GuildSum%ShowNumPerPage==0?(GuildSum/ShowNumPerPage):(GuildSum/ShowNumPerPage +1);//总页数
	if(Page > MaxPage)
		Page = MaxPage;
	if(Page<1)
		Page = 1;
	m_NowPage = Page;//记录当前页数
	//4.页数数据设置到UI上面去
	char szPageNum[256];
	MeSprintf_s(szPageNum, sizeof(szPageNum)/sizeof(char)-1,"%d/%d",Page,MaxPage);
	m_pID_TEXT_Page->SetText(szPageNum);
	//5.根据上一页 下一页 设置按钮的状态
	if(MaxPage == 1)
	{
		m_pID_BUTTON_PageUp->SetEnable(false);
		m_pID_BUTTON_PageDown->SetEnable(false);
	}
	else if(Page == 1)
	{
		m_pID_BUTTON_PageUp->SetEnable(false);
		m_pID_BUTTON_PageDown->SetEnable(true);
	}
	else if(Page == MaxPage)
	{
		m_pID_BUTTON_PageUp->SetEnable(true);
		m_pID_BUTTON_PageDown->SetEnable(false);
	}
	else
	{
		m_pID_BUTTON_PageUp->SetEnable(true);
		m_pID_BUTTON_PageDown->SetEnable(true);
	}
	//6.将集合里指定范围的数据设置到UI上面去
	int nStart = (Page - 1) *  ShowNumPerPage;
	int nEnd = Page * ShowNumPerPage;
	for (int i = nStart; i < m_vctGuild.size() && i < nEnd; ++i)
	{
		if(!m_vctGuild[i])
			continue;
		char str_name[64] = {0};
		char str_level[64] ={0};
		char str_num[64] ={0};
		char str_MasterName[64] ={0};
		MeSprintf_s(str_name, sizeof(str_name)/sizeof(char) - 1, "%s", m_vctGuild[i]->GetName());//名字
		MeSprintf_s(str_level,sizeof(str_level)/sizeof(char)-1,"%d",m_vctGuild[i]->GetLevel());//等级
		MeSprintf_s(str_num,sizeof(str_num)/sizeof(char)-1,"%d",m_vctGuild[i]->GetMemberNum());//人数
		MeSprintf_s(str_MasterName,sizeof(str_MasterName)/sizeof(char)-1,"%s",m_vctGuild[i]->GetMasterName() );//帮主
		AddToList(str_name,str_level,str_num,str_MasterName);
	}
}
void CUI_ID_FRAME_GuildApply::AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername)
{
	ControlList::S_List	pItem;
	pItem.SetData(m_GuildName, 0, NULL, 0);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_LEFT);
	m_pID_LIST_GuildList->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(level);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Level->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(num);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_Amount->AddItem(&pItem,NULL,false);

	pItem.clear();
	pItem.SetData(Mastername);
	pItem.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
	m_pID_LIST_CDR->AddItem(&pItem,NULL,false);	
}
void CUI_ID_FRAME_GuildApply::OnMsgQueryGuildData(Msg* pMsg_)
{
	if (!pMsg_)
	{
		return;
	}
	CHECK_MSGLEN( pMsg_, MsgQueryGuildDataAck);
	MsgQueryGuildDataAck* pMsg = (MsgQueryGuildDataAck*)pMsg_;

	m_pID_TEXT_GuildName->SetText(pMsg->szGuildName);
	m_pID_TEXT_Level->SetText(pMsg->uchLevel);
	m_pID_TEXT_Member->SetText(pMsg->ustMemberCount);
	m_pID_TEXT_GuildMaster->SetText(pMsg->szMasterName);
	m_pID_TEXT_Announcement->SetText(pMsg->szGuildAim);
	
	TimeEx createTime(pMsg->n64CreateTime);
	char szText[128] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%02d/%02d", createTime.GetYear(), createTime.GetMonth(), createTime.GetDay());
	m_pID_TEXT_CreateDate->SetText(szText);
}
inline void CUI_ID_FRAME_GuildApply::ShowApplyingMessage()
{
	char szText[256] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, theXmlString.GetString(eText_Guild_ApplyingMessageSending));
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Guild_Belongs, szText );
}
void CUI_ID_FRAME_GuildApply::SetNeedRefresh(bool bNeed)
{
	//设置当前Ui刷新
	if(!m_pID_FRAME_GuildApply)
		return;
	if(m_pID_FRAME_GuildApply->IsVisable() && bNeed)
	{
		std::string words = m_pID_EDIT_4918->GetText();
		if (!words.empty())
		{
			m_vctGuild.clear();
			if (theHeroGame.GetPlayerMgr()->GetMe())
			{
				unsigned char nMyCountry = theHeroGame.GetPlayerMgr()->GetMe()->GetRealCountry();
				int nAllGuild = thePlayerRole.GetGuildNum();
				for (int i = 0; i < nAllGuild; ++i)
				{
					if (!thePlayerRole.GetGuild(i))
						continue;
					if (thePlayerRole.GetGuild(i)->GetCountry() != nMyCountry)
						continue;
					std::string GuildName = thePlayerRole.GetGuild(i)->GetName();
					size_t index = GuildName.find(words.c_str());
					if (index != std::string.npos)
					{
						m_vctGuild.push_back(thePlayerRole.GetGuild(i));
					}
				}
				std::sort(m_vctGuild.begin(), m_vctGuild.end(), SortByGreatLevel);
			}
			//数据设置完毕后
			ShowGuildInfoByPage();//显示数据
		}
		else
		{
			OnInit();
		}
		
	}
}
bool CUI_ID_FRAME_GuildApply::EditInputIsVisable()
{
	if(m_pID_FRAME_GuildApply == NULL)  return false;
	if(m_pID_EDIT_4918 )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_4918);
	}
	return FALSE;
}
void CUI_ID_FRAME_GuildApply::InitializeAtEnterWorld()
{
	LoadUI();
}