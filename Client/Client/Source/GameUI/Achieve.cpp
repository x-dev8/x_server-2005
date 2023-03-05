/********************************************************************
	Created by UIEditor.exe
	FileName: F:\work_hero\next\Program\trunk\Bin\Client\Data\Ui\Achieve.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PlayerRole.h"
#include "gamemain.h"
#include "Player.h"
#include "playermgr.h"
#include "Achieve.h"
#include "baseProperty.h"

//extern CHeroGame theHeroGame;

CUI_ID_FRAME_Achieve s_CUI_ID_FRAME_Achieve;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Achieve, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Achieve, OnFrameRender )
CUI_ID_FRAME_Achieve::CUI_ID_FRAME_Achieve()
{
	// Member
	m_pID_FRAME_Achieve = NULL;
	m_pID_PICTURE_BgLine = NULL;
	m_pID_PICTURE_Bg1 = NULL;
	m_pID_PICTURE_WordWall1 = NULL;
	m_pID_PICTURE_WordWall2 = NULL;
	m_pID_PICTURE_WordWall3 = NULL;
	m_pID_PICTURE_WordWall4 = NULL;
	m_pID_PICTURE_WordWall5 = NULL;
	m_pID_PICTURE_WordWall6 = NULL;
	m_pID_PICTURE_WordWall7 = NULL;
	m_pID_PICTURE_WordWall8 = NULL;
	m_pID_PICTURE_WordWall9 = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Line1 = NULL;
	m_pID_PICTURE_Line2 = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_TEXT_BaseAchieve = NULL;
	m_pID_TEXT_PrestigeText = NULL;
	m_pID_TEXT_GeniusText = NULL;
	m_pID_TEXT_GuildContributeText = NULL;
	m_pID_TEXT_ReputeText = NULL;
	m_pID_TEXT_BattleAchieve = NULL;
	m_pID_TEXT_PKValueText = NULL;
	m_pID_TEXT_GloryText = NULL;
	m_pID_TEXT_BattleValueText = NULL;
	m_pID_TEXT_BattleLevelText = NULL;
	m_pID_PICTURE_Line3 = NULL;
	m_pID_TEXT_SocialityAchieve = NULL;
	m_pID_TEXT_CharmText = NULL;
	m_pID_TEXT_Prestige = NULL;
	m_pID_TEXT_GuildContribute = NULL;
	m_pID_TEXT_Genius = NULL;
	m_pID_TEXT_Repute = NULL;
	m_pID_TEXT_PKValue = NULL;
	m_pID_TEXT_BattleValue = NULL;
	m_pID_TEXT_Glory = NULL;
	m_pID_TEXT_BattleLevel = NULL;
	m_pID_TEXT_Charm = NULL;
	m_pID_TEXT_CountryValue = NULL;
}
// Frame
bool CUI_ID_FRAME_Achieve::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_Achieve::OnFrameRender()
{
	return true;
}
// Button

// 装载UI
bool CUI_ID_FRAME_Achieve::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Achieve.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Achieve.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Achieve::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Achieve, s_CUI_ID_FRAME_AchieveOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Achieve, s_CUI_ID_FRAME_AchieveOnFrameRender );
	m_pID_FRAME_Achieve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Achieve );
	m_pID_PICTURE_BgLine = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_BgLine );
	m_pID_PICTURE_Bg1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_Bg1 );
	m_pID_PICTURE_WordWall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall1 );
	m_pID_PICTURE_WordWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall2 );
	m_pID_PICTURE_WordWall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall3 );
	m_pID_PICTURE_WordWall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall4 );
	m_pID_PICTURE_WordWall5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall5 );
	m_pID_PICTURE_WordWall6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall6 );
	m_pID_PICTURE_WordWall7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall7 );
	m_pID_PICTURE_WordWall8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall8 );
	m_pID_PICTURE_WordWall9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_WordWall9 );
	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_Title );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Achieve, ID_BUTTON_CLOSE );
	m_pID_PICTURE_Line1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_Line1 );
	m_pID_PICTURE_Line2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_Line2 );
	m_pID_TEXT_Tips = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Tips );
	m_pID_TEXT_BaseAchieve = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BaseAchieve );
	m_pID_TEXT_PrestigeText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_PrestigeText );
	m_pID_TEXT_GeniusText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_GeniusText );
	m_pID_TEXT_GuildContributeText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_GuildContributeText );
	m_pID_TEXT_ReputeText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_ReputeText );
	m_pID_TEXT_BattleAchieve = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BattleAchieve );
	m_pID_TEXT_PKValueText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_PKValueText );
	m_pID_TEXT_GloryText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_GloryText );
	m_pID_TEXT_BattleValueText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BattleValueText );
	m_pID_TEXT_BattleLevelText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BattleLevelText );
	m_pID_PICTURE_Line3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Achieve, ID_PICTURE_Line3 );
	m_pID_TEXT_SocialityAchieve = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_SocialityAchieve );
	m_pID_TEXT_CharmText = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_CharmText );
	m_pID_TEXT_Prestige = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Prestige );
	m_pID_TEXT_GuildContribute = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_GuildContribute );
	m_pID_TEXT_Genius = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Genius );
	m_pID_TEXT_Repute = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Repute );
	m_pID_TEXT_PKValue = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_PKValue );
	m_pID_TEXT_BattleValue = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BattleValue );
	m_pID_TEXT_Glory = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Glory );
	m_pID_TEXT_BattleLevel = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_BattleLevel );
	m_pID_TEXT_Charm = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_Charm );
	m_pID_TEXT_CountryValue = (ControlText*)theUiManager.FindControl( ID_FRAME_Achieve, ID_TEXT_CountryValue );

	//assert( m_pID_FRAME_Achieve );
	//assert( m_pID_PICTURE_BgLine );
	//assert( m_pID_PICTURE_Bg1 );
	//assert( m_pID_PICTURE_WordWall1 );
	//assert( m_pID_PICTURE_WordWall2 );
	//assert( m_pID_PICTURE_WordWall3 );
	//assert( m_pID_PICTURE_WordWall4 );
	//assert( m_pID_PICTURE_WordWall5 );
	//assert( m_pID_PICTURE_WordWall6 );
	//assert( m_pID_PICTURE_WordWall7 );
	//assert( m_pID_PICTURE_WordWall8 );
	//assert( m_pID_PICTURE_WordWall9 );
	//assert( m_pID_PICTURE_Title );
	//assert( m_pID_BUTTON_CLOSE );
	//assert( m_pID_PICTURE_Line1 );
	//assert( m_pID_PICTURE_Line2 );
	//assert( m_pID_TEXT_Tips );
	////assert( m_pID_CHECKBOX_Shengwang3 );
	////assert( m_pID_CHECKBOX_Shengwang4 );
	//assert( m_pID_CHECKBOX_Zhuangbei );
	//assert( m_pID_BUTTON_Title );
	//assert( m_pID_TEXT_BaseAchieve );
	//assert( m_pID_TEXT_PrestigeText );
	//assert( m_pID_TEXT_GeniusText );
	//assert( m_pID_TEXT_GuildContributeText );
	//assert( m_pID_TEXT_ReputeText );
	//assert( m_pID_TEXT_BattleAchieve );
	//assert( m_pID_TEXT_PKValueText );
	//assert( m_pID_TEXT_GloryText );
	//assert( m_pID_TEXT_BattleValueText );
	//assert( m_pID_TEXT_BattleLevelText );
	//assert( m_pID_PICTURE_Line3 );
	//assert( m_pID_TEXT_SocialityAchieve );
	//assert( m_pID_TEXT_CharmText );
	//assert( m_pID_TEXT_Prestige );
	//assert( m_pID_TEXT_GuildContribute );
	//assert( m_pID_TEXT_Genius );
	//assert( m_pID_TEXT_Repute );
	//assert( m_pID_TEXT_PKValue );
	//assert( m_pID_TEXT_BattleValue );
	//assert( m_pID_TEXT_Glory );
	//assert( m_pID_TEXT_BattleLevel );
	//assert( m_pID_TEXT_Charm );

	SetVisable(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_BaseProperty.GetFrame());
    Refresh();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Achieve::_UnLoadUI()
{
	m_pID_FRAME_Achieve = NULL;
	m_pID_PICTURE_BgLine = NULL;
	m_pID_PICTURE_Bg1 = NULL;
	m_pID_PICTURE_WordWall1 = NULL;
	m_pID_PICTURE_WordWall2 = NULL;
	m_pID_PICTURE_WordWall3 = NULL;
	m_pID_PICTURE_WordWall4 = NULL;
	m_pID_PICTURE_WordWall5 = NULL;
	m_pID_PICTURE_WordWall6 = NULL;
	m_pID_PICTURE_WordWall7 = NULL;
	m_pID_PICTURE_WordWall8 = NULL;
	m_pID_PICTURE_WordWall9 = NULL;
	m_pID_PICTURE_Title = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_PICTURE_Line1 = NULL;
	m_pID_PICTURE_Line2 = NULL;
	m_pID_TEXT_Tips = NULL;
	m_pID_TEXT_BaseAchieve = NULL;
	m_pID_TEXT_PrestigeText = NULL;
	m_pID_TEXT_GeniusText = NULL;
	m_pID_TEXT_GuildContributeText = NULL;
	m_pID_TEXT_ReputeText = NULL;
	m_pID_TEXT_BattleAchieve = NULL;
	m_pID_TEXT_PKValueText = NULL;
	m_pID_TEXT_GloryText = NULL;
	m_pID_TEXT_BattleValueText = NULL;
	m_pID_TEXT_BattleLevelText = NULL;
	m_pID_PICTURE_Line3 = NULL;
	m_pID_TEXT_SocialityAchieve = NULL;
	m_pID_TEXT_CharmText = NULL;
	m_pID_TEXT_Prestige = NULL;
	m_pID_TEXT_GuildContribute = NULL;
	m_pID_TEXT_Genius = NULL;
	m_pID_TEXT_Repute = NULL;
	m_pID_TEXT_PKValue = NULL;
	m_pID_TEXT_BattleValue = NULL;
	m_pID_TEXT_Glory = NULL;
	m_pID_TEXT_BattleLevel = NULL;
	m_pID_TEXT_Charm = NULL;
	m_pID_TEXT_CountryValue = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Achieve.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_Achieve::_IsVisable()
{
	if ( !m_pID_FRAME_Achieve )
		return false;
	return m_pID_FRAME_Achieve->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_Achieve::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_Achieve )
		return;
	m_pID_FRAME_Achieve->SetVisable( bVisable );
}


void CUI_ID_FRAME_Achieve::Refresh()
{
	if (m_pID_FRAME_Achieve== NULL)
	{
		return;
	}
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;

	m_pID_TEXT_Prestige->SetText(pMe->GetReputation()); //声望
	m_pID_TEXT_GuildContribute->SetText(pMe->GetGuildOffer());//帮供
	m_pID_TEXT_Genius->SetText(0);//天赋
	m_pID_TEXT_Repute->SetText(thePlayerRole.GetMasterValue());//威望

	m_pID_TEXT_PKValue->SetText(pMe->GetPKKillValue());//PK值
	m_pID_TEXT_BattleValue->SetText(0);//战场积分
// 	if (thePlayerRole.m_pBaseInfo)
// 	{
// 		m_pID_TEXT_Glory->SetText(thePlayerRole.m_pBaseInfo->liveinfo.honour);	
// 	}
// 	else
// 	{
// 		m_pID_TEXT_Glory->SetText(0);
// 	}
	m_pID_TEXT_Glory->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_Glory));
	
	m_pID_TEXT_BattleLevel->SetText(0);//战场等级

	if (thePlayerRole.m_pBaseInfo)
	{
		m_pID_TEXT_CountryValue->SetText(thePlayerRole.m_pBaseInfo->liveinfo.battleScore);	
	}
	else
	{
		m_pID_TEXT_CountryValue->SetText(0);
	}

	m_pID_TEXT_Charm->SetText(0);//魅力
}