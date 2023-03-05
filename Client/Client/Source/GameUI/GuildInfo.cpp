/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildInfo.h"
#include "PlayerRole.h"
#include "GuildBaseInfo.h"
#include "Common.h"
#include "Announce.h"
#include "GuildCampBattle.h"
#include "GuildConfig.h"
#ifndef STR_MAXLEN
#define STR_MAXLEN	255
#endif

CUI_ID_FRAME_GuildInfo s_CUI_ID_FRAME_GuildInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildInfo, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildInfo, ID_BUTTON_AnnouncementOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildInfo, ID_BUTTON_GuildCampBattleOnButtonClick )

CUI_ID_FRAME_GuildInfo::CUI_ID_FRAME_GuildInfo()
{
	// Member
	m_pID_FRAME_GuildInfo = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_RenShu = NULL;
	m_pID_TEXT_GuildExp = NULL;
	m_pID_TEXT_GuildMoney = NULL;
	m_pID_TEXT_GuildLevel = NULL;
	m_pID_TEXT_Warxishu = NULL;
	m_pID_TEXT_GuildMaster = NULL;
	m_pID_TEXT_Announcement = NULL;
	m_pID_BUTTON_Announcement = NULL;
	m_pID_BUTTON_GuildCampBattle=NULL;
	m_pID_TEXT_Mision = NULL;
	m_pID_TEXT_MaxPlayerSum=NULL;
}
// Frame
bool CUI_ID_FRAME_GuildInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildInfo::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildInfo::ID_BUTTON_AnnouncementOnButtonClick( ControlObject* pSender )
{
	//公告 公会
	if ( !m_pID_FRAME_GuildInfo )
		return false;
	s_CUI_ID_FRAME_Announce.SetGang(true);
	s_CUI_ID_FRAME_Announce.SetDlgType(CUI_ID_FRAME_Announce::E_Type_Announcement);
	s_CUI_ID_FRAME_Announce.SetVisable(true);
	return true;
}
bool CUI_ID_FRAME_GuildInfo::ID_BUTTON_GuildCampBattleOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildInfo )
		return false;
	//打开公会会员的权限设置
	s_CUI_ID_FRAME_CampBattle.SetVisable(!s_CUI_ID_FRAME_CampBattle.IsVisable());
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildInfo.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildInfo, s_CUI_ID_FRAME_GuildInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildInfo, s_CUI_ID_FRAME_GuildInfoOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildInfo, ID_BUTTON_Announcement, s_CUI_ID_FRAME_GuildInfoID_BUTTON_AnnouncementOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GuildInfo, ID_BUTTON_GuildCampBattle, s_CUI_ID_FRAME_GuildInfoID_BUTTON_GuildCampBattleOnButtonClick );
	m_pID_FRAME_GuildInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildInfo );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_Name );
	m_pID_TEXT_RenShu = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_RenShu );
	m_pID_TEXT_GuildExp = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_GuildExp );
	m_pID_TEXT_GuildMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_GuildMoney );
	m_pID_TEXT_GuildLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_GuildLevel );
	m_pID_TEXT_Warxishu = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_Warxishu );
	m_pID_TEXT_GuildMaster = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_GuildMaster );
	m_pID_TEXT_Announcement = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_Announcement );
	m_pID_BUTTON_Announcement = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_BUTTON_Announcement );
	m_pID_BUTTON_GuildCampBattle= (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_BUTTON_GuildCampBattle );

	m_pID_TEXT_MaxPlayerSum= (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_MaxPlayerSum );
	
	m_pID_TEXT_Mision = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildInfo, ID_TEXT_Mision );
	assert( m_pID_FRAME_GuildInfo );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_RenShu );
	assert( m_pID_TEXT_GuildExp );
	assert( m_pID_TEXT_GuildMoney );
	assert( m_pID_TEXT_GuildLevel );
	assert( m_pID_TEXT_Warxishu );
	assert( m_pID_TEXT_GuildMaster );
	assert( m_pID_TEXT_Announcement );
	assert( m_pID_BUTTON_Announcement );
	assert(m_pID_TEXT_Mision);
	assert(m_pID_BUTTON_GuildCampBattle);
	assert(m_pID_TEXT_MaxPlayerSum);
	

	m_pID_FRAME_GuildInfo->SetFather(s_CUI_ID_FRAME_GuildBaseInfo.GetFrame());
	SetVisable(false);
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_GuildInfo::_UnLoadUI()
{
	m_pID_FRAME_GuildInfo = NULL;
	m_pID_TEXT_Mision = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuildInfo::_IsVisable()
{
	return m_pID_FRAME_GuildInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildInfo::_SetVisable( const bool bVisable )
{
	if(bVisable)
		OnShow();
	m_pID_FRAME_GuildInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildInfo::OnShow()
{
	//当Ui显示的时候 设置UI上的值
	//1.军团名称
	m_pID_TEXT_Name->SetText(s_CUI_ID_FRAME_GuildBaseInfo.GetGuildName().c_str());
	//2.军团团长
	m_pID_TEXT_GuildMaster->SetText(s_CUI_ID_FRAME_GuildBaseInfo.GetGuildMastrName().c_str());
	//3.军团实力
	uint32 Strongth = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildStrongth();
	char sz[10] = {0};
	MeSprintf_s( sz, 10 - 1, "%u", Strongth );
	m_pID_TEXT_Warxishu->SetText(sz);
	//4.军团等级
	uint32 Level = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildLevel();
	char szLevel[10] = {0};
	MeSprintf_s( szLevel, 10 - 1, "%u", Level );
	m_pID_TEXT_GuildLevel->SetText(szLevel);
	//5.军团经验
	uint32 Exp = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildExp();
	char szExp[10] = {0};
	MeSprintf_s( szExp, 10 - 1, "%u", Exp );
	m_pID_TEXT_GuildExp->SetText(szExp);
	//6.军团金钱
	uint32 money = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildMoney();
	// 金银铜
	/*std::string	m_strMoney="";		
    uint32 nCopper = money % 100;
    uint32 nSiller = ( money / 100 ) % 100;
    uint32 nGold = money / 10000;
    char szMoney[ STR_MAXLEN ] = {0};
    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#83}", nCopper );
    if( nSiller )
        MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#82}%s", nSiller, m_strMoney.c_str() );
    if( nGold )
	    MeSprintf_s( szMoney, STR_MAXLEN - 1, "%u{#81}%s", nGold, m_strMoney.c_str() );*/
	string szMoney = "";
	thePlayerRole.GetGSCStringFromMoney(money,szMoney);
	m_pID_TEXT_GuildMoney->SetText(szMoney.c_str());
	//7.军团人数
	uint32 AllSum = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildAllSum();
	uint32 OnLineSum = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildOnLineSum();
	char szStr[24] = {0};
	MeSprintf_s( szStr, 24 - 1, "%u/%u",OnLineSum , AllSum);
	m_pID_TEXT_RenShu->SetText(szStr);
	//显示军团最大人数
	int MaxSum = theGuildConfig.GetLevelSetting(Level)->GetMaxCount();
	char szMS[10] = {0};
	MeSprintf_s( szMS, 10 - 1, "%u", MaxSum );
	m_pID_TEXT_MaxPlayerSum->SetText(szMS);
	//8.设置公告
	m_pID_TEXT_Announcement->SetText(s_CUI_ID_FRAME_GuildBaseInfo.GetGuildCommon().c_str());
	//9.设置公告按钮的状态
	m_pID_BUTTON_Announcement->SetEnable(s_CUI_ID_FRAME_GuildBaseInfo.IsCanCommonByMe());
	//10
	uint32 Mission = s_CUI_ID_FRAME_GuildBaseInfo.GetGuildMission();
	char szMission[10] = {0};
	MeSprintf_s( szMission, 10 - 1, "%u", Mission );
	m_pID_TEXT_Mision->SetText(szMission);
}
void CUI_ID_FRAME_GuildInfo::OnUpdateUiInfo()
{
	if(!IsVisable()) return;//UI没显示不需要更新
	OnShow();//更新UI的值
}