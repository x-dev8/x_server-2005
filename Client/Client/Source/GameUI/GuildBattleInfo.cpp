/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBattleInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildBattleInfo.h"
#include "CampBattleGuild.h"
#include "PlayerRole.h"
#include "StringLanguage.h"

CUI_ID_FRAME_GuildBattleInfo s_CUI_ID_FRAME_GuildBattleInfo;

MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildBattleInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildBattleInfo, OnFrameRender )

#define BATTLE_MONSYER_HP_PER 100

CUI_ID_FRAME_GuildBattleInfo::CUI_ID_FRAME_GuildBattleInfo()
{
	// Member
	m_pID_FRAME_GuildBattleInfo = NULL;
	m_pID_TEXT_MyGuildPoint = NULL;
	m_pID_TEXT_OtherGuildPoint = NULL;
	m_pID_TEXT_TotleKillSumA = NULL;
	m_pID_TEXT_TotleKillSumB = NULL;
	m_pID_PROGRESS_BarracksA2 = NULL;
	m_pID_PROGRESS_BarracksA1 = NULL;
	m_pID_PROGRESS_BarracksA3 = NULL;
	m_pID_PROGRESS_BarracksB3 = NULL;
	m_pID_PROGRESS_BarracksB2 = NULL;
	m_pID_PROGRESS_BarracksB1 = NULL;
	m_pID_PROGRESS_BarracksA4 = NULL;
	m_pID_PROGRESS_BarracksB4 = NULL;
	m_pID_TEXT_BarracksA1 = NULL;
	m_pID_TEXT_BarracksA2 = NULL;
	m_pID_TEXT_BarracksA3 = NULL;
	m_pID_TEXT_BarracksA4 = NULL;
	m_pID_TEXT_BarracksB1 = NULL;
	m_pID_TEXT_BarracksB2 = NULL;
	m_pID_TEXT_BarracksB3 = NULL;
	m_pID_TEXT_GuildNameA = NULL;
	m_pID_TEXT_GuildNameB = NULL;
	m_pID_TEXT_BarracksB4 = NULL;

}
CUI_ID_FRAME_GuildBattleInfo::~CUI_ID_FRAME_GuildBattleInfo()
{
}
// Frame
bool CUI_ID_FRAME_GuildBattleInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GuildBattleInfo::OnFrameRender()
{
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildBattleInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildBattleInfo.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildBattleInfo.meui]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildBattleInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildBattleInfo, s_CUI_ID_FRAME_GuildBattleInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildBattleInfo, s_CUI_ID_FRAME_GuildBattleInfoOnFrameRender );

	m_pID_FRAME_GuildBattleInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildBattleInfo );
	m_pID_TEXT_MyGuildPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_MyGuildPoint );
	m_pID_TEXT_OtherGuildPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_OtherGuildPoint );
	m_pID_TEXT_TotleKillSumA = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_TotleKillSumA );
	m_pID_TEXT_TotleKillSumB = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_TotleKillSumB );
	m_pID_PROGRESS_BarracksA2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksA2 );
	m_pID_PROGRESS_BarracksA1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksA1 );
	m_pID_PROGRESS_BarracksA3 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksA3 );
	m_pID_PROGRESS_BarracksB3 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksB3 );
	m_pID_PROGRESS_BarracksB2 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksB2 );
	m_pID_PROGRESS_BarracksB1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksB1 );
	m_pID_PROGRESS_BarracksA4 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksA4 );
	m_pID_PROGRESS_BarracksB4 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_PROGRESS_BarracksB4 );
	m_pID_TEXT_BarracksA1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksA1 );
	m_pID_TEXT_BarracksA2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksA2 );
	m_pID_TEXT_BarracksA3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksA3 );
	m_pID_TEXT_BarracksA4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksA4 );
	m_pID_TEXT_BarracksB1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksB1 );
	m_pID_TEXT_BarracksB2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksB2 );
	m_pID_TEXT_BarracksB3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksB3 );
	m_pID_TEXT_BarracksB4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_BarracksB4 );

	m_pID_TEXT_GuildNameA = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_GuildNameA );
	m_pID_TEXT_GuildNameB = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildBattleInfo, ID_TEXT_GuildNameB );

	assert( m_pID_FRAME_GuildBattleInfo );
	assert( m_pID_TEXT_MyGuildPoint );
	assert( m_pID_TEXT_OtherGuildPoint );
	assert( m_pID_TEXT_TotleKillSumA );
	assert( m_pID_TEXT_TotleKillSumB );
	assert( m_pID_PROGRESS_BarracksA2 );
	assert( m_pID_PROGRESS_BarracksA1 );
	assert( m_pID_PROGRESS_BarracksA3 );
	assert( m_pID_PROGRESS_BarracksB3 );
	assert( m_pID_PROGRESS_BarracksB2 );
	assert( m_pID_PROGRESS_BarracksB1 );
	assert( m_pID_PROGRESS_BarracksA4 );
	assert( m_pID_PROGRESS_BarracksB4 );
	assert( m_pID_TEXT_BarracksA1 );
	assert( m_pID_TEXT_BarracksA2 );
	assert( m_pID_TEXT_BarracksA3 );
	assert( m_pID_TEXT_BarracksA4 );
	assert( m_pID_TEXT_BarracksB1 );
	assert( m_pID_TEXT_BarracksB2 );
	assert( m_pID_TEXT_BarracksB3 );
	assert( m_pID_TEXT_BarracksB4 );
	assert( m_pID_TEXT_GuildNameA );
	assert( m_pID_TEXT_GuildNameB );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuildBattleInfo::_UnLoadUI()
{
	return theUiManager.RemoveFrame( "Data\\UI\\GuildBattleInfo.meui" );
}
// 是否可视
bool CUI_ID_FRAME_GuildBattleInfo::_IsVisable()
{
	return m_pID_FRAME_GuildBattleInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuildBattleInfo::_SetVisable( const bool bVisable )
{
	m_pID_FRAME_GuildBattleInfo->SetVisable( bVisable );
}
void CUI_ID_FRAME_GuildBattleInfo::SetData(unsigned int GuildAID,unsigned int APoint,unsigned int AKillSum,float A1,float A2,float A3,float A4,unsigned int GuildBID,unsigned int BPoint,unsigned int BKillSum,float B1,float B2,float B3,float B4)
{
	if(!IsVisable())
		return;
	//将需要的数据设置到UI上面去
	char NameA[64];
	strcpy_s(NameA,63,thePlayerRole.GetGuildNameById(GuildAID));
	m_pID_TEXT_GuildNameA->SetText(NameA);

	char NameB[64];
	strcpy_s(NameB,63,thePlayerRole.GetGuildNameById(GuildBID));
	m_pID_TEXT_GuildNameB->SetText(NameB);

	char Info[64];
	m_pID_TEXT_MyGuildPoint->SetText(GetString(APoint,Info));
	m_pID_TEXT_OtherGuildPoint->SetText(GetString(BPoint,Info));
	m_pID_TEXT_TotleKillSumA->SetText(GetString(AKillSum,Info));
	m_pID_TEXT_TotleKillSumB->SetText(GetString(BKillSum,Info));
	m_pID_TEXT_BarracksA1->SetText(GetString(A1,Info));
	m_pID_TEXT_BarracksA2->SetText(GetString(A2,Info));
	m_pID_TEXT_BarracksA3->SetText(GetString(A3,Info));
	m_pID_TEXT_BarracksB1->SetText(GetString(B1,Info));
	m_pID_TEXT_BarracksB2->SetText(GetString(B2,Info));
	m_pID_TEXT_BarracksB3->SetText(GetString(B3,Info));
	m_pID_PROGRESS_BarracksA1->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksA2->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksA3->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB1->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB2->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB3->SetMaxValue(BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksA1->SetValue(A1 * BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksA2->SetValue(A2 * BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksA3->SetValue(A3 * BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB1->SetValue(B1 * BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB2->SetValue(B2 * BATTLE_MONSYER_HP_PER);
	m_pID_PROGRESS_BarracksB3->SetValue(B3 * BATTLE_MONSYER_HP_PER);

	m_pID_PROGRESS_BarracksA1->SetVisable(true);
	m_pID_PROGRESS_BarracksA2->SetVisable(true);
	m_pID_PROGRESS_BarracksA3->SetVisable(true);
	m_pID_PROGRESS_BarracksB1->SetVisable(true);
	m_pID_PROGRESS_BarracksB2->SetVisable(true);
	m_pID_PROGRESS_BarracksB3->SetVisable(true);

	if(A1 ==0.0f && A2 ==0.0f && A3 ==0.0f)
	{
		m_pID_TEXT_BarracksA4->SetText(GetString(A4,Info));
		m_pID_PROGRESS_BarracksA4->SetMaxValue(BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksA4->SetValue(A4 * BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksA4->SetVisable(true);
	}
	else
	{
		m_pID_PROGRESS_BarracksA4->SetMaxValue(BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksA4->SetValue(0);
		m_pID_PROGRESS_BarracksA4->SetVisable(true);
		m_pID_TEXT_BarracksA4->SetText(theXmlString.GetString(eText_GuildBattle_NoBoss));
	}
	if(B1 ==0.0f && B2 ==0.0f && B3 ==0.0f)
	{
		m_pID_TEXT_BarracksB4->SetText(GetString(B4,Info));
		m_pID_PROGRESS_BarracksB4->SetMaxValue(BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksB4->SetValue(B4 * BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksB4->SetVisable(true);
	}
	else
	{
		m_pID_PROGRESS_BarracksB4->SetMaxValue(BATTLE_MONSYER_HP_PER);
		m_pID_PROGRESS_BarracksB4->SetValue(0);
		m_pID_PROGRESS_BarracksB4->SetVisable(true);
		m_pID_TEXT_BarracksB4->SetText(theXmlString.GetString(eText_GuildBattle_NoBoss));
	}
}
char* CUI_ID_FRAME_GuildBattleInfo::GetString(unsigned int Num,char * Info)
{
	memset( Info, 0, 64 );
	_i64toa(Num,Info,10);
	return Info;
}
char* CUI_ID_FRAME_GuildBattleInfo::GetString(float Num,char * Info)
{
	memset( Info, 0, 64 );
	sprintf_s(Info,64,"%d%%",(int)(Num*100));
	return Info;
}
void CUI_ID_FRAME_GuildBattleInfo::SetShowByNeed()
{
	time_t now;
	time(&now);
	string StrInfo;
	int States = s_CUI_ID_FRAME_CampBattleGuild.GetCampBattleInfo().m_Setting->GetTimeStates(now,StrInfo);
	if(States == 2 || States == 3)
		SetVisable(true);
	else
		SetVisable(false);
}