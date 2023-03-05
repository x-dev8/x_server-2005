/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Group_Me.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Group_Me.h"
#include "MediaPathManager.h"
#include "GameMain.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "../Player.h"
#include "SelfRBtnMenu.h"
#include "Group.h"
#include "SystemConfig.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "XmlStringLanguage.h"
#include "../Cfg.h"
#include "MessageBox.h"
#include "main.h"
#include "Me3d/Engine/RendererDx.h"
#include "MainMenu.h"
#include "CharacterExp.h"
#include "core/Name.h"
#include "HideGroupMe.h"
#include "PetMain.h"
#include "MeUI/ExpressionManager.h"
#include "ShowScreenText.h"
#include "ui/LoadMap.h"
#include "PetRbtnMenu.h"
#include "ui/baseProperty.h"
#include "ui/Main.h"
#include "ui/exmain.h"
#include "ui/Skill.h"
#include "ui/Protect.h"
#include "packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "wsCamera.h"
#include "Create.h"                 //added by ZhuoMeng.Hu		[9/19/2010]
#include "MeUi/ExpressionManager.h"
#include "GameDefinePlayer.h"
#include "ActionUI.h"
#include "GuildBattle.h"
#include "ScoreTip.h"
#include "ui/SuAnimalMenu.h"
#include "ItemHero.h"
#include "PlayerInfoMgr.h"
#include "GameSetting.h"
#include "ScreenInfoManager.h"
// 斗气动画帧纹理中的行数和列数
#define EXPOWER_TEX_ROW         6
#define EXPOWER_TEX_COL        10
#define EXPOWER_TOTAL_TIME   2000
//#define PSMOFFSET 5

CUI_ID_FRAME_Group_Me s_CUI_ID_FRAME_Group_Me;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Group_Me, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Group_Me, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PKCloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PKOpenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PKFuryOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_FactionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PKGuildOnButtonClick )

//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PlayerShowALLOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAmityOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PlayerHideALLOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAntagonizeOnButtonClick )
CUI_ID_FRAME_Group_Me::CUI_ID_FRAME_Group_Me()
{
	// SGuildMember
	ResetMembers();

	m_bShowHp = false;
	m_bShowMp = false;
	m_bShowFp = true;
	IsClicked = false;
    m_pExPowerEffect = NULL;
	m_bShowGuildBattleButton = false;
	m_bImageInited = false;
	m_bHeroImgInited = false;

	m_XLog = 0;
	m_YLog = 0;
}

void CUI_ID_FRAME_Group_Me::ResetMembers()
{
	m_pID_FRAME_Group_Me	= NULL;
	m_pID_TEXT_Name			= NULL;
	m_pID_PROGRESS_Hp		= NULL;
	m_pID_PROGRESS_Mp		= NULL;
	m_pID_TEXT_LVL			= NULL;
	m_pID_PICTURE_ChoosePet	= NULL;
	m_pID_PICTURE_pet = NULL;
	m_pID_TEXT_petname	= NULL;
	m_pID_TEXT_petlevel = NULL;
	m_pID_PROGRESS_petHp = NULL;
	m_pID_PICTURE_FacePic = NULL;

	m_pID_PICTURE_Assassin = NULL;
	m_pID_PICTURE_Mage = NULL;
	m_pID_PICTURE_Warrior = NULL;
	m_pID_PICTURE_Taoist = NULL;
	m_pID_PICTURE_Hunter = NULL;

	m_pID_PICTURE_PetHead = NULL;
	m_pID_PICTURE_Corps = NULL;
    m_pID_BUTTON_PKClose = NULL;
    m_pID_BUTTON_PKOpen = NULL;
    m_pID_BUTTON_PKFury = NULL;
    m_pID_PROGRESS_ExBar = NULL;
    m_pID_PROGRESS_Flame = NULL;
	m_pID_BUTTON_Faction = NULL;

	m_pID_PICTURE_BgPetHead1 = NULL;
	m_pID_PICTURE_PetHead1 = NULL;
	m_pID_TEXT_petname1 = NULL;
	m_pID_PICTURE_pet1 = NULL;
	m_pID_PROGRESS_petHp1 = NULL;
	m_pID_PICTURE_ChoosePet1 = NULL;
	m_pID_TEXT_petlevel1 = NULL;
	m_pID_TEXT_SelfMp = NULL;
	m_pID_TEXT_SelfHp = NULL;
	m_pID_TEXT_petHp = NULL;
	m_pID_TEXT_petHp1 = NULL;


	m_pID_BUTTON_PKGuild = NULL;
	m_pCurPlayerShowBtn = NULL;
	m_pID_TEXT_Hero = NULL;

	/*m_pID_BUTTON_PlayerShowALL = NULL;
	m_pID_BUTTON_PlayerShowAmity = NULL;
	m_pID_BUTTON_PlayerHideALL = NULL;
	m_pID_BUTTON_PlayerShowAntagonize = NULL;
	m_pCurPlayerShowBtn = NULL;
	m_bPlayerShowModeOpen = false;
	ShowPlayerBtnPosX = 0;
	ShowPlayerBtnPosY = 0;

	m_nPlayerRenderFlag = CPlayerMgr::EPlayerRenderFlag::EPRF_ALL;
		m_bCompositor = false;*/
	
}

void CUI_ID_FRAME_Group_Me::UpdataEquipView()
{
	guardfunc;
	CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if( DestPlayer && DestPlayer->GetAnim() && DestPlayer->GetEquip() )
	{
		return ;

		guard(Pack::001);
		CPlayer_SEquipment equip[ eKeyAll_Max ];
		memcpy( &equip, DestPlayer->GetEquip(), sizeof(CPlayer_SEquipment)* eKeyAll_Max );
		equip[eKeyAll_Helmet].item.itembaseinfo.ustItemID = InvalidLogicNumber;
		equip[eKeyAll_Helmet].iModelID = InvalidLogicNumber;
		equip[eKeyAll_Helmet].iModelID2 = InvalidLogicNumber;

		equip[eKeyAll_RHandItem].item.itembaseinfo.ustItemID = InvalidLogicNumber;
		equip[eKeyAll_RHandItem].iModelID = InvalidLogicNumber;
		equip[eKeyAll_RHandItem].iModelID2 = InvalidLogicNumber;

		/*equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask )].item.itembaseinfo.ustItemID = InvalidLogicNumber;
		equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask )].iModelID = InvalidLogicNumber;
		equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eLeftHandShieldPartMask )].iModelID2 = InvalidLogicNumber;*/

		equip[eKeyAll_LHandItem].item.itembaseinfo.ustItemID = InvalidLogicNumber;
		equip[eKeyAll_LHandItem].iModelID = InvalidLogicNumber;
		equip[eKeyAll_LHandItem].iModelID2 = InvalidLogicNumber;

		/*equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoulderPartMask )].item.itembaseinfo.ustItemID = InvalidLogicNumber;
		equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoulderPartMask )].iModelID = InvalidLogicNumber;
		equip[CStdCharSkeleton::GetPartMask( CStdCharSkeleton::eShoulderPartMask )].iModelID2 = InvalidLogicNumber;*/

		bool showHelmet = DestPlayer->IsShowHelmet() || DestPlayer->IsShowAecpratove();
		unguard;
	}
	unguard;
}

void CUI_ID_FRAME_Group_Me::SetTEXT_LVL( const char* text )
{
	if( !m_pID_FRAME_Group_Me || !m_pID_TEXT_LVL )
		return;

	if( !text )
		return;

	*m_pID_TEXT_LVL = text;


	
}

void CUI_ID_FRAME_Group_Me::SetTEXT_Name( const char* text, DWORD color )
{
	if( !m_pID_FRAME_Group_Me || !m_pID_TEXT_Name )
		return;

	if( !text )
		return;

	m_pID_TEXT_Name->SetText(text, color);
}

void CUI_ID_FRAME_Group_Me::SetHero_Name(const char* text, DWORD color)
{
	if( !m_pID_FRAME_Group_Me || !m_pID_TEXT_Hero )
		return;

	if( !text )
		return;

	m_pID_TEXT_Hero->SetText(text, color);
}

ControlProgress* CUI_ID_FRAME_Group_Me::GetPROGRESS_Hp()
{
	if( !m_pID_FRAME_Group_Me || !m_pID_PROGRESS_Hp )
		return NULL;
	return m_pID_PROGRESS_Hp;
}

ControlProgress* CUI_ID_FRAME_Group_Me::GetPROGRESS_Mp()
{
	//modified by zhuomeng.hu		[9/14/2010]
	if( !m_pID_FRAME_Group_Me || !m_pID_PROGRESS_Mp)
		return NULL;

	return m_pID_PROGRESS_Mp;
}

ControlProgress* CUI_ID_FRAME_Group_Me::GetPROGRESS_ExPower()
{
    if( !m_pID_FRAME_Group_Me || !m_pID_PROGRESS_ExBar )
        return NULL;
    return m_pID_PROGRESS_ExBar;
}

void CUI_ID_FRAME_Group_Me::SetTEXT_petname( const char* text )
{
	if( !m_pID_FRAME_Group_Me || !m_pID_TEXT_petname )
		return;
	if( !text )
		return;

	*m_pID_TEXT_petname = text;
}

void CUI_ID_FRAME_Group_Me::SetTEXT_petname1(const char* text)
{
	if (!m_pID_FRAME_Group_Me || !m_pID_TEXT_petname1)
	{
		return ;
	}
	if (!text)
	{
		return;
	}
	*m_pID_TEXT_petname1 = text;
}

void CUI_ID_FRAME_Group_Me::SetTEXT_petlevel( const char* text )
{
	if( !m_pID_FRAME_Group_Me || !m_pID_TEXT_petlevel )
		return;
	if( !text )
		return;

	*m_pID_TEXT_petlevel = text;
}

void CUI_ID_FRAME_Group_Me::SetTEXT_petlevel1(const char* text)
{
	if (!m_pID_FRAME_Group_Me || !m_pID_TEXT_petlevel1)
	{
		return ;
	}
	if (!text)
	{
		return ;
	}
	*m_pID_TEXT_petlevel1 = text;
}
ControlProgress* CUI_ID_FRAME_Group_Me::GetPROGRESS_petHp()
{
	if( !m_pID_FRAME_Group_Me || !m_pID_PROGRESS_petHp )
		return NULL;
	return m_pID_PROGRESS_petHp;
}

ControlProgress *CUI_ID_FRAME_Group_Me::GetPROGRESS_petHp1()
{
	if (!m_pID_PROGRESS_petHp1 || !m_pID_FRAME_Group_Me)
	{
		return NULL;
	}
	return m_pID_PROGRESS_petHp1;
}

void CUI_ID_FRAME_Group_Me::ID_FRAME_Group_MeOnMouseMove( ControlObject* pSender )
{
	guardfunc;

	if( thePlayerRole.GetTeamMemberNum() == 0 )
		return;

	if( s_CUI_ID_FRAME_Group_Me.IsClick() )
		return;

	if( s_CUI_ID_FRAME_SelfRBMenu.IsVisable() )
		return;

	char szchar[128] = {0};
	switch( thePlayerRole.GetAssignMode() )
	{
	case AssignMode_FreeMode:
		if( thePlayerRole.m_bCorps )
		{
			sprintf( szchar, theXmlString.GetString(eText_ClientCrops_assignMode0));
		}
		else
		{
			sprintf( szchar, theXmlString.GetString(eText_Client_show_assignMode_Freedom));
		}
		break;
	case AssignMode_Team:
		if( thePlayerRole.m_bCorps )
		{
			sprintf( szchar, theXmlString.GetString(eText_ClientCrops_assignMode1));
		}
		else
		{
			sprintf( szchar, theXmlString.GetString(eText_Client_show_assignMode_Team));
		}
		break;
	case AssignMode_Random:
		if( thePlayerRole.m_bCorps )
		{
			sprintf( szchar, theXmlString.GetString(eText_ClientCrops_assignMode2));
		}
		else
		{
			sprintf( szchar, theXmlString.GetString(eText_Client_show_assignMode_Random));
		}
		break;
	case AssignMode_Assign:
		if( thePlayerRole.m_bCorps )
		{
			sprintf( szchar, theXmlString.GetString(eText_ClientCrops_assignMode3));
		}
		else
		{
			sprintf( szchar, theXmlString.GetString(eText_Client_show_assignMode_Assign));
		}
		break;

	}

	unguard;
}
void CUI_ID_FRAME_Group_Me::ID_FRAME_Group_MeLevelMouseMove( ControlObject* pSender )
{
	guardfunc;
	s_CUI_ID_FRAME_Group_Me.SetIsClick(false);
	unguard;
}
bool CUI_ID_FRAME_Group_Me::ID_FRAME_Group_MeOnLBtnClick( ControlObject* pSender )
{
	guardfunc;

	if (!s_CUI_ID_FRAME_Group_Me.IsVisable())
		return false;

	s_CUI_ID_FRAME_Group_Me.SetIsClick(true);
	if( theHeroGame.GetPlayerMgr() )
        theHeroGame.GetPlayerMgr()->LockMe();

	s_CUI_Group.Refeash();
	return false;
	unguard;
}

bool CUI_ID_FRAME_Group_Me::ID_FRAME_Group_MeOnPetClick(ControlObject* pSender )
{
	guardfunc;
	if( theHeroGame.GetPlayerMgr()->GetMe() )
		theHeroGame.GetPlayerMgr()->SetLockNpc( theHeroGame.GetPlayerMgr()->GetMe()->GetPetID() );

	s_CUI_Group.Refeash();
	return true;

	unguard;
}
bool CUI_ID_FRAME_Group_Me::ID_FRAME_Group_MeOnClick( ControlObject* pSender )
{
	guardfunc;

	s_CUI_ID_FRAME_Group_Me.SetIsClick(true);
	if( !s_CUI_ID_FRAME_SelfRBMenu.IsVisable() )
		s_CUI_ID_FRAME_SelfRBMenu.SetVisable(true);
	else
		s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
	s_CUI_Group.Refeash();

	return false;
	unguard;
}
bool CUI_ID_FRAME_Group_Me::ID_FRAME_Pet_OnRClick( INT nX, INT nY  )
{
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(!s_CUI_ID_FRAME_SuAnimalMenu.IsVisable() );
	if (s_CUI_ID_FRAME_SuAnimalMenu.IsVisable() )
	{
		const char *m_name = s_CUI_ID_FRAME_Group_Me.GetPetNameControlText()->GetText();
		s_CUI_ID_FRAME_SuAnimalMenu.SetCurrentPetIndex(m_name);
	}
	return true;
}

//added by ZhuoMeng.Hu		[9/28/2010]
// 切换至PK模式    切回普通模式
void CUI_ID_FRAME_Group_Me::SetOpenPKModeButton()
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return;
	if(pMe->GetPKType() == PKMode_Normal)
	{
		//客户端
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
	}	
	else if(pMe->GetPKType() == PKMode_Fight)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
	}	
	else if(pMe->GetPKType() == PKMode_Guild)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
	}	
	else if(pMe->GetPKType() == PKMode_Critical)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
	}
}
bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PKCloseOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Group_Me )
        return false;

	//获取当前模式
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return false;
	if(pMe->GetPKType() == PKMode_Normal)
	{
		//客户端
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
		return true;
	}	
    MsgChangePKFlag msg;
    //msg.shFlag = PKMode_Fight;
	msg.shFlag = PKMode_Normal;
    GettheNetworkInput().SendMsg( &msg );

	SetOpenPKModeButton();
    return true;
}
// 切回普通模式  切回全体模式
bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PKOpenOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Group_Me )
        return false;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return false;
	if(pMe->GetPKType() == PKMode_Fight)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
		return true;
	}	
    MsgChangePKFlag msg;
    //msg.shFlag = PKMode_Normal;
	msg.shFlag = PKMode_Fight;
    GettheNetworkInput().SendMsg( &msg );

	SetOpenPKModeButton();

    return true;
}
//切回公会模式
bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PKGuildOnButtonClick(ControlObject* pSender)
{
	if( !m_pID_FRAME_Group_Me )
        return false;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return false;
	if(pMe->GetPKType() == PKMode_Guild)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
		return true;
	}	
	//判断有无公会
	if(thePlayerRole.GetGangMgr()->GetGuildID() == GuildDefine::InitID)
	{
		////提示玩家无公会不可以切换公会模式
		m_pPkBtn[PKMode_Normal]->SetVisable(false);
		m_pPkBtn[PKMode_Guild]->SetVisable(false);
		m_pPkBtn[PKMode_Fight]->SetVisable(false);
		RefreshPKShowPicture(pMe->GetPKType());
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon,theXmlString.GetString(eText_PKMode_NonGuid));
		return false;
	}
    MsgChangePKFlag msg;
    msg.shFlag = PKMode_Guild;
    GettheNetworkInput().SendMsg( &msg );

	SetOpenPKModeButton();
    return true;
}
// 狂暴模式30分钟后手动切换
bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PKFuryOnButtonClick( ControlObject* pSender )
{
    if( !m_pID_FRAME_Group_Me )
        return false;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe ) return false;
	if(pMe->GetPKType() == PKMode_Critical)
	{
		//客户端
		m_pPkBtn[PKMode_Normal]->SetVisable(!m_pPkBtn[PKMode_Normal]->IsVisable());
		m_pPkBtn[PKMode_Fight]->SetVisable(!m_pPkBtn[PKMode_Fight]->IsVisable());
		m_pPkBtn[PKMode_Guild]->SetVisable(!m_pPkBtn[PKMode_Guild]->IsVisable());
		return true;
	}	

    MsgChangePKFlag msg;
    //msg.shFlag = PKMode_Normal;
	msg.shFlag = PKMode_Critical;
    GettheNetworkInput().SendMsg( &msg );

	SetOpenPKModeButton();
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button //显示所有
//bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PlayerShowALLOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Group_Me )
//		return false;
//
//	SetRenderPlayerFlag(CPlayerMgr::EPlayerRenderFlag::EPRF_ALL);
//	SetPlayerModeOpenOrClose(pSender);
//	
//
//	return true;
//}
//// Button//显示友好的
//bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PlayerShowAmityOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Group_Me )
//		return false;
//
//	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME |
//		               CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM |
//					   CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | 
//					   CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | 
//					   CPlayerMgr::EPlayerRenderFlag::EPRF_AMITY);
//	SetPlayerModeOpenOrClose(pSender);
//	
//
//	/*SetRenderPlayerFlag(CPlayerMgr::EPlayerRenderFlag::EPRF_ALL);*/
//
//	return true;
//}
//// Button //显示主角自己
//bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PlayerHideALLOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Group_Me )
//		return false;
//	
//	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME | 
//		               CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | 
//					   CPlayerMgr::EPlayerRenderFlag::EPRF_NPC |
//					   CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER);
//	SetPlayerModeOpenOrClose(pSender);
//
//	return true;
//}
//// Button //显示敌对的
//bool CUI_ID_FRAME_Group_Me::ID_BUTTON_PlayerShowAntagonizeOnButtonClick( ControlObject* pSender )
//{
//	if( !m_pID_FRAME_Group_Me )
//		return false;
//
//	SetRenderPlayerFlag( CPlayerMgr::EPlayerRenderFlag::EPRF_ME | 
//		                CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | 
//		                CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | 
//		                CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | 
//		                CPlayerMgr::EPlayerRenderFlag::EPRF_ANTAGONIZE);
//    SetPlayerModeOpenOrClose(pSender);
//	
//
//	
//	
//	
//	return true;
//}
//
//void  CUI_ID_FRAME_Group_Me::SetPlayerModeOpenOrClose(ControlObject* pSender)
//{
//	if(!pSender) return;
//	if(!m_pCurPlayerShowBtn) return;
//
//	theHeroGame.GetPlayerMgr()->SetPlayerRenderFlag(GetRenderPlayerFlag());
//
//	if (pSender == m_pCurPlayerShowBtn)
//	{
//		
//		m_bCompositor = false;
//		if(m_bPlayerShowModeOpen) //展开状态则关闭
//		{ 
//			for (int i = 0 ; i < PSM_Max ; i++)
//			{
//				m_pPlayerShowBtn[i]->SetVisable(false);
//			}
//		}
//		else
//		{
//			for (int i = 0 ; i < PSM_Max ; i++)
//			{
//				m_pPlayerShowBtn[i]->SetVisable(true);
//			}
//		}
//		m_bPlayerShowModeOpen = !m_bPlayerShowModeOpen;
//		m_pCurPlayerShowBtn->SetVisable(true); //当前显示的按钮打开
//
//	}else
//	{
//		m_bCompositor = true;
//		m_bPlayerShowModeOpen = false;
//		m_pCurPlayerShowBtn = (ControlButton*)pSender;
//		for (int i = 0 ; i < PSM_Max ; i++)
//		{
//			m_pPlayerShowBtn[i]->SetVisable(false);
//		}
//
//		m_pCurPlayerShowBtn->SetVisable(true); //当前显示的按钮打开
//		compositor();
//		m_bCompositor = false;
//	}
//}
//
//
//void  CUI_ID_FRAME_Group_Me::compositor(bool IsChangeCurShowBtn) //排序
//{
//	if( !m_pID_FRAME_Group_Me )
//		return;
//
//	if(!m_bCompositor)
//        return;
//
//	m_pCurPlayerShowBtn->SetPos(ShowPlayerBtnPosX,ShowPlayerBtnPosY);
//	this->m_pID_FRAME_Group_Me->SetRedraw();
//	
//	RECT rcList;
//	m_pCurPlayerShowBtn->GetRealRect(&rcList);
//	int _Height = rcList.bottom - rcList.top; 
//
//    int Index = 1;
//	for (int i = 0 ; i < PSM_Max ; i++)
//	{
//		if(m_pPlayerShowBtn[i] == m_pCurPlayerShowBtn)
//			continue;
//
//		m_pPlayerShowBtn[i]->SetPos(ShowPlayerBtnPosX,ShowPlayerBtnPosY + (_Height + PSMOFFSET)* Index );
//		m_pPlayerShowBtn[i]->SetVisable(false);
//
//		Index++;
//
//	}
//
//	if (m_pCurPlayerShowBtn == m_pPlayerShowBtn[PSM_HideAll])
//	{
//		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,0 );
//		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 0 );
//		GameSetting::Instance()->CommitChanges();
//	}else
//	{
//		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,1 );
//		GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 1 );
//		GameSetting::Instance()->CommitChanges();
//	}
//	
//	
//
//	m_bCompositor = false;
//
//}
//

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Frame
bool CUI_ID_FRAME_Group_Me::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}

bool CUI_ID_FRAME_Group_Me::OnFrameRender()
{
	guardfunc;

	if( !m_pID_FRAME_Group_Me->IsVisable() )
	    return true;
    
    // 重做了斗气       added by zhuomeng.hu		[10/27/2010]
    __int64 nExPower = thePlayerRole.GetData( CPlayerRole::TYPE_ExPower );
    __int64 nExPowerMax = DEF_CHAR_XP_LIMIT;

    if( nExPower != nExPowerMax )
    {
        // 没满
        S_BaseData::S_Pic* pPic = m_pID_PROGRESS_ExBar->GetPic();
        if( !std::string( pPic->m_szPicName ).empty() && ( nExPower > 0 ) )
        {
            RECT dstRect, srcRect;
            m_pID_PROGRESS_ExBar->GetRealRect( &dstRect );
            srcRect = pPic->m_rcFrame;
            dstRect.top = dstRect.bottom - ( dstRect.bottom - dstRect.top ) * nExPower / nExPowerMax;
            srcRect.top = srcRect.bottom - ( srcRect.bottom - srcRect.top ) * nExPower / nExPowerMax;
            int nID = -1;
            theControlPictureManager.BitBlt( &nID, pPic->m_szPicName, &dstRect, &srcRect );
        }
    }
    else
    {
        // 满斗气
        RECT dstRect;
        m_pID_PROGRESS_Flame->GetRealRect( &dstRect );
        if( m_pExPowerEffect )
            m_pExPowerEffect->Display( dstRect );
    }
	
	ShowButtonSpark();
	return true;
	unguard;
}

void CUI_ID_FRAME_Group_Me::RefreshPKShowPicture( int pkFlag )
{
	if( !m_pID_FRAME_Group_Me )
		return;
	if( pkFlag < 0 || pkFlag >= PKMode_MaxValue )
		return;

	/*if(theHeroGame.GetPlayerMgr()->GetMe()->GetPKType() == pkFlag)
		return;*/
	if( pkFlag ==PKMode_AttackFight  || pkFlag == PKMode_AttackGuild )
	{
		if(m_pPkBtn[PKMode_Normal] && !m_pPkBtn[PKMode_Normal]->IsVisable())
		{
			//设置 普通模式进入 反击模式
			if(pkFlag ==PKMode_AttackFight)
				pkFlag =PKMode_Fight;
			else if(pkFlag ==PKMode_AttackGuild)
				pkFlag =PKMode_Guild;
		}
		else
			return;
	}
	int Sum = 0;
	for( int i = 0; i < PKMode_MaxValue; ++i )
	{
		if(m_pPkBtn[i] && m_pPkBtn[i]->IsVisable())
		{
			++Sum;
			m_pPkBtn[i]->SetVisable( false );
		}
	}
	bool isopen = false;
	if(Sum >=2)
		isopen = true;

	if ( m_pCurPlayerShowBtn )
	{
		RECT rcList;
		m_pCurPlayerShowBtn->GetRealRect(&rcList);
		m_XLog = rcList.left;
		m_YLog = rcList.top;
	}

	if(pkFlag == PKMode_Normal)
	{
		//普通模式显示 Pk模式的2个按钮
		/*if(m_pPkBtn[PKMode_Fight])
			m_pPkBtn[PKMode_Fight]->SetVisable( true );
		if(m_pPkBtn[PKMode_Guild])
			m_pPkBtn[PKMode_Guild]->SetVisable( true );*/
		m_pPkBtn[PKMode_Normal]->SetPos(m_XLog,m_YLog);
		m_pPkBtn[PKMode_Normal]->SetVisable( true );
		m_pCurPlayerShowBtn = m_pPkBtn[PKMode_Normal];

		m_pPkBtn[PKMode_Fight]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Normal]->GetHeight() +5);
		m_pPkBtn[PKMode_Guild]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Normal]->GetHeight() +5 + m_pPkBtn[PKMode_Fight]->GetHeight() + 5);

		if(isopen)
		{
			m_pPkBtn[PKMode_Fight]->SetVisable(true);
			m_pPkBtn[PKMode_Guild]->SetVisable(true);
		}
	}
	else if(pkFlag == PKMode_Fight)
	{
		/*if(m_pPkBtn[PKMode_Normal])
			m_pPkBtn[PKMode_Normal]->SetVisable( true );
		if(m_pPkBtn[PKMode_Guild])
			m_pPkBtn[PKMode_Guild]->SetVisable( true );*/

		m_pPkBtn[PKMode_Fight]->SetPos(m_XLog,m_YLog);
		m_pPkBtn[PKMode_Fight]->SetVisable( true );	
		m_pCurPlayerShowBtn = m_pPkBtn[PKMode_Fight];

		m_pPkBtn[PKMode_Normal]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Fight]->GetHeight() +5);
		m_pPkBtn[PKMode_Guild]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Fight]->GetHeight() +5 +m_pPkBtn[PKMode_Normal]->GetHeight() +5);

		if(isopen)
		{
			m_pPkBtn[PKMode_Normal]->SetVisable(true);
			m_pPkBtn[PKMode_Guild]->SetVisable(true);
		}
	}
	else if(pkFlag == PKMode_Guild)
	{
		/*if(m_pPkBtn[PKMode_Normal])
			m_pPkBtn[PKMode_Normal]->SetVisable( true );
		if(m_pPkBtn[PKMode_Fight])
			m_pPkBtn[PKMode_Fight]->SetVisable( true );*/

		m_pPkBtn[PKMode_Guild]->SetPos(m_XLog,m_YLog);
		m_pPkBtn[PKMode_Guild]->SetVisable( true );	
		m_pCurPlayerShowBtn = m_pPkBtn[PKMode_Guild];

		m_pPkBtn[PKMode_Normal]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Guild]->GetHeight() +5);
		m_pPkBtn[PKMode_Fight]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Guild]->GetHeight() +5  +m_pPkBtn[PKMode_Normal]->GetHeight() +5);

		if(isopen)
		{
			m_pPkBtn[PKMode_Normal]->SetVisable(true);
			m_pPkBtn[PKMode_Fight]->SetVisable(true);
		}
	}
	else if(pkFlag == PKMode_Critical)
	{
		/*if(m_pPkBtn[PKMode_Normal])
			m_pPkBtn[PKMode_Normal]->SetVisable( true );
		if(m_pPkBtn[PKMode_Fight])
			m_pPkBtn[PKMode_Fight]->SetVisable( true );
		if(m_pPkBtn[PKMode_Guild])
			m_pPkBtn[PKMode_Guild]->SetVisable( true );*/

		m_pPkBtn[PKMode_Critical]->SetPos(m_XLog,m_YLog);
		m_pPkBtn[PKMode_Critical]->SetVisable( true );	
		m_pCurPlayerShowBtn = m_pPkBtn[PKMode_Critical];

		m_pPkBtn[PKMode_Normal]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Critical]->GetHeight() +5);
		m_pPkBtn[PKMode_Fight]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Critical]->GetHeight() +5 +m_pPkBtn[PKMode_Normal]->GetHeight() +5);
		m_pPkBtn[PKMode_Guild]->SetPos(m_XLog,m_YLog+m_pPkBtn[PKMode_Critical]->GetHeight() +5  +m_pPkBtn[PKMode_Normal]->GetHeight() +5  +m_pPkBtn[PKMode_Fight]->GetHeight() +5);

		if(isopen)
		{
			m_pPkBtn[PKMode_Normal]->SetVisable(true);
			m_pPkBtn[PKMode_Fight]->SetVisable(true);
			m_pPkBtn[PKMode_Guild]->SetVisable(true);
		}
	}
	/*(if(m_pPkBtn[ pkFlag ])
		m_pPkBtn[ pkFlag ]->SetVisable( true );*/
}

// added by ZhuoMeng.Hu		[10/20/2010]
void CUI_ID_FRAME_Group_Me::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_Group_Me )
        return;

    // 消息响应    F11为切PK模式快捷键 lyh注销 ，f11为隐藏玩家的快捷键
  //  m_pID_FRAME_Group_Me->SetMsgProcFun( GroupMe_HotKey_MsgProc );

    m_pID_FRAME_Group_Me->SetOnClickFun( ID_FRAME_Group_MeOnLBtnClick );
    m_pID_FRAME_Group_Me->SetOnRBtnDown( ID_FRAME_Group_MeOnClick );
    m_pID_FRAME_Group_Me->SetMouseMoveOn( ID_FRAME_Group_MeOnMouseMove );
    m_pID_FRAME_Group_Me->SetMouseMoveLevel( ID_FRAME_Group_MeLevelMouseMove );
    m_pID_PICTURE_ChoosePet->SetRClickFun( ID_FRAME_Pet_OnRClick );
    m_pID_PICTURE_pet->SetButtonClickFun( ID_FRAME_Group_MeOnPetClick );

    // 显示不同职业MP槽
    m_pID_PROGRESS_Mp->SetVisable( true );

    // 设置头像
    //s_CUI_ID_FRAME_CREATE.LoadPortrait();
    //std::string portraitName = s_CUI_ID_FRAME_CREATE.GetPortraitName( thePlayerRole.GetSex(), thePlayerRole.m_charinfo.baseinfo.aptotic.ucHeadPic );
    //portraitName = "Data\\Ui\\" + portraitName;
    //m_pID_PICTURE_FacePic->SetPicName( portraitName.c_str() );
	CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if( DestPlayer )
	{
		char sex[2][32] = { "Male", "Female" };

		int hairId = DestPlayer->GetEquip()[eKeyAll_Hair].iModelID;
		int faceId = DestPlayer->GetEquip()[eKeyAll_Face].iModelID;

		char filename[256] = {0};
		MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead%d.dds",
			GetRootPath(), sex[DestPlayer->GetSex()], hairId);
		f_Handle* fp = packet_namespace::w_fopen(filename, "r");
		if (fp)
		{
			m_pID_PICTURE_HairPic->SetPicName(filename);
			packet_namespace::w_fclose(fp);
		}
		else
		{
			if (DestPlayer->GetSex() == 0)
				m_pID_PICTURE_HairPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
			else
				m_pID_PICTURE_HairPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
		}

		//MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sFaceHead%d.dds",
		//	GetRootPath(), sex[DestPlayer->GetSex()], faceId);
		//fp = packet_namespace::w_fopen(filename, "r");
		//if (fp)
		//{
		//	m_pID_PICTURE_FacePic->SetPicName(filename);
		//	packet_namespace::w_fclose(fp);
		//}
		//else
		//{
		//	if (DestPlayer->GetSex() == 0)
		//		m_pID_PICTURE_FacePic->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
		//	else
		//		m_pID_PICTURE_FacePic->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
		//}
	}


    // 职业标记
    m_proPicGroup.SetVisible( false );

    // PK模式
    m_pID_BUTTON_PKClose->SetShowTip( true );
    m_pID_BUTTON_PKOpen->SetShowTip( true );
    m_pID_BUTTON_PKFury->SetShowTip( true );
	m_pID_BUTTON_PKGuild->SetShowTip( true );

	/*for (int i = 0 ; i < PSM_Max ; i++)
	{
		m_pPlayerShowBtn[i]->SetShowTip(true);
	}*/

   // m_pID_BUTTON_PKClose->setTip( theXmlString.GetString( eText_PKMode_Off ) );
	//m_pID_BUTTON_PKGuild->setTip( theXmlString.GetString( eText_PKMode_GuildOn ) );
		
    for( int i = 0; i < PKMode_MaxValue; ++i )
    {
		if(m_pPkBtn[i])
			m_pPkBtn[i]->SetVisable( false );
    }

    m_pID_PICTURE_Corps->SetVisable( false );

    SetPetInfoVisable(false);
	SetPetInfoVisable_1(false);
    for(int i=0; i<BodyStatusType_Max; ++i)
    {
        _tBufStart[i] = 0;
        _tLastTime[i] = 0;
    }

    m_proPicGroup.Clear();
    m_proPicGroup.AddControl( m_pID_PICTURE_Warrior );
    m_proPicGroup.AddControl( m_pID_PICTURE_Mage );
    m_proPicGroup.AddControl( m_pID_PICTURE_Assassin );
    m_proPicGroup.AddControl( m_pID_PICTURE_Taoist );
    m_proPicGroup.AddControl( m_pID_PICTURE_Hunter );
    m_proPicGroup.SetVisible( false );

	switch( thePlayerRole.GetProfession() )
	{
		case EArmType_Warrior  : m_pID_PICTURE_Warrior->SetVisable(true); break;
		case EArmType_Mage     : m_pID_PICTURE_Mage->SetVisable(true); break;
		case EArmType_Assassin : m_pID_PICTURE_Assassin->SetVisable(true); break;
		case EArmType_Taoist   : m_pID_PICTURE_Taoist->SetVisable(true);   break;
		case EArmType_Hunter   : m_pID_PICTURE_Hunter->SetVisable(true);   break;
	}

    UpdataEquipView();

    Refeash();
}

void CUI_ID_FRAME_Group_Me::InitExPowerRect()
{
    if( !m_pID_FRAME_Group_Me )
        return;

    S_BaseData::S_Pic* pPic = m_pID_PROGRESS_Flame->GetPic();
    if( !pPic )
        return;

    std::string _strPicPath = pPic->m_szPicName;
    if( _strPicPath.empty() )
        return;
    RECT rc = pPic->m_rcFrame;

    if( m_pExPowerEffect )
        m_pExPowerEffect->Initialize( _strPicPath, EXPOWER_TEX_ROW, EXPOWER_TEX_COL, EXPOWER_TEX_ROW * EXPOWER_TEX_COL, rc, EXPOWER_TOTAL_TIME );
}


// 装载UI
bool CUI_ID_FRAME_Group_Me::_LoadUI()
{
	guardfunc;

	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Group_Me.meui", true, UI_Render_LayerSecond );
	//DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Group_Me.meui");
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Group_Me.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}

void CUI_ID_FRAME_Group_Me::Refeash()
{
	if( !m_pID_FRAME_Group_Me )
		return;

	if( thePlayerRole.m_bCorps )
	{
		std :: vector<TeamInfo> vecPlayer = thePlayerRole.GetTeamInfo();
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( pMe )
		{
			int MyIdx = -1;
			for( int i=0; i< vecPlayer.size(); i++ )
			{
				if( strcmp(vecPlayer[i].szName.c_str(),pMe->GetName()) == 0)
				{
					MyIdx = i;
				}
			}
		}
	}
}

// 关连控件
bool CUI_ID_FRAME_Group_Me::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Group_Me, s_CUI_ID_FRAME_Group_MeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Group_Me, s_CUI_ID_FRAME_Group_MeOnFrameRender, false );
    theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PKClose, s_CUI_ID_FRAME_Group_MeID_BUTTON_PKCloseOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PKOpen, s_CUI_ID_FRAME_Group_MeID_BUTTON_PKOpenOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PKFury, s_CUI_ID_FRAME_Group_MeID_BUTTON_PKFuryOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_Faction, s_CUI_ID_FRAME_Group_MeID_BUTTON_FactionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PKGuild, s_CUI_ID_FRAME_Group_MeID_BUTTON_PKGuildOnButtonClick );

	/*theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowALL, s_CUI_ID_FRAME_Group_MeID_BUTTON_PlayerShowALLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAmity, s_CUI_ID_FRAME_Group_MeID_BUTTON_PlayerShowAmityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PlayerHideALL, s_CUI_ID_FRAME_Group_MeID_BUTTON_PlayerHideALLOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAntagonize, s_CUI_ID_FRAME_Group_MeID_BUTTON_PlayerShowAntagonizeOnButtonClick );*/

	m_pID_FRAME_Group_Me = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Group_Me );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_Name );
	m_pID_PROGRESS_Hp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_Hp );
	m_pID_PROGRESS_Mp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_Mp );
	m_pID_TEXT_LVL = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_level );
	m_pID_PICTURE_ChoosePet = (ControlPicture*)theUiManager.FindControl(ID_FRAME_Group_Me, ID_PICTURE_ChoosePet);
	m_pID_PICTURE_pet = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_pet );
	m_pID_TEXT_petname = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_petname );
	m_pID_TEXT_petlevel = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_petlevel );
	m_pID_PROGRESS_petHp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_petHp );
	m_pID_PICTURE_FacePic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_FacePic);
	m_pID_PICTURE_HairPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_HairPic);
	
	m_pID_PICTURE_pet1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_PET1 );
	m_pID_PROGRESS_petHp1 = (ControlProgress*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_PETHP1 );
	m_pID_PICTURE_PetHead1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_PETHEAD1 );
	m_pID_PICTURE_ChoosePet1 = (ControlPicture*)theUiManager.FindControl(ID_FRAME_Group_Me, ID_PICTURE_CHOOSEPET1);
	m_pID_PICTURE_BgPetHead1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_BGPETHEAD1 );
	m_pID_TEXT_petlevel1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_PETLEVEL1 );
	m_pID_TEXT_petname1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_PETNAME1 );

	m_pID_PICTURE_Assassin	= (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Assassin );
	m_pID_PICTURE_Mage		= (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Mage );
	m_pID_PICTURE_Warrior	= (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Warrior );
	m_pID_PICTURE_Taoist	= (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Taoist );
	m_pID_PICTURE_Hunter	= (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Hunter );

	m_pID_PICTURE_PetHead = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_PetHead );
	m_pID_PICTURE_Corps = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_PICTURE_Corps );
    m_pID_BUTTON_PKClose = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PKClose );
    m_pID_BUTTON_PKOpen = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PKOpen );
    m_pID_BUTTON_PKFury = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PKFury );
	m_pID_BUTTON_PKGuild  = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PKGuild ); 

    m_pID_PROGRESS_ExBar = ( ControlProgress* )theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_ExBar );
    m_pID_PROGRESS_Flame = ( ControlProgress* )theUiManager.FindControl( ID_FRAME_Group_Me, ID_PROGRESS_Flame );
	m_pID_BUTTON_Faction = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_Faction);
	m_pID_TEXT_SelfHp = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_SelfHp );
	m_pID_TEXT_SelfMp = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_SelfMp );
	m_pID_TEXT_petHp = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_petHp );
	m_pID_TEXT_petHp1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_petHp1 );
	m_pID_TEXT_Hero = (ControlText*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_TEXT_Hero );

	/*m_pID_BUTTON_PKGuild = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PKGuild );
	m_pID_BUTTON_PlayerShowALL = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowALL );
	m_pID_BUTTON_PlayerShowAmity = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAmity );
	m_pID_BUTTON_PlayerHideALL = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PlayerHideALL );
	m_pID_BUTTON_PlayerShowAntagonize = (ControlButton*)theUiManager.FindControl( ID_FRAME_Group_Me, ID_BUTTON_PlayerShowAntagonize );*/

	assert( m_pID_TEXT_petHp );
	assert( m_pID_TEXT_petHp1 );
	assert( m_pID_TEXT_SelfMp );
	assert( m_pID_TEXT_SelfHp );
	assert( m_pID_FRAME_Group_Me );
	assert( m_pID_TEXT_Name );
	assert( m_pID_PROGRESS_Hp );
	assert( m_pID_PROGRESS_Mp );
	assert( m_pID_PICTURE_Corps );
	assert( m_pID_PICTURE_pet );
	assert( m_pID_TEXT_petname );
	assert( m_pID_TEXT_petlevel );
	assert( m_pID_PROGRESS_petHp );
	assert( m_pID_PICTURE_ChoosePet );
    assert( m_pID_BUTTON_PKClose );
    assert( m_pID_BUTTON_PKOpen );
    assert( m_pID_BUTTON_PKFury );
    assert( m_pID_PROGRESS_ExBar );
    assert( m_pID_PROGRESS_Flame );
	assert(m_pID_BUTTON_Faction);
	assert( m_pID_TEXT_Hero );


	/*assert( m_pID_BUTTON_PlayerShowALL );
	assert( m_pID_BUTTON_PlayerShowAmity );
	assert( m_pID_BUTTON_PlayerHideALL );
	assert( m_pID_BUTTON_PlayerShowAntagonize );*/


    m_pPkBtn[ PKMode_Normal ] = m_pID_BUTTON_PKClose;
    m_pID_BUTTON_PKClose->setTip( theXmlString.GetString( eText_PKMode_Off ) );

    m_pPkBtn[ PKMode_Fight ] = m_pID_BUTTON_PKOpen;
    m_pID_BUTTON_PKOpen->setTip( theXmlString.GetString( eText_PKMode_On ) );

    m_pPkBtn[ PKMode_Critical ] = m_pID_BUTTON_PKFury;
	m_pID_BUTTON_PKFury->setTip( theXmlString.GetString( eText_PKMode_Fury ) );

	m_pPkBtn[PKMode_Guild] = m_pID_BUTTON_PKGuild;
	m_pID_BUTTON_PKGuild->setTip( theXmlString.GetString( eText_PKMode_GuildOn ) );


	/*m_pPlayerShowBtn[ PSM_ShowAll ] = m_pID_BUTTON_PlayerShowALL;
	m_pID_BUTTON_PlayerShowALL->setTip( theXmlString.GetString( eText_ShowAllPlayer ) );
	m_pID_BUTTON_PlayerShowALL->SetVisable(true);

	m_pPlayerShowBtn[ PSM_HideAll ] = m_pID_BUTTON_PlayerHideALL;
	m_pID_BUTTON_PlayerHideALL->setTip( theXmlString.GetString( eText_HideAllPlayer ) );
	m_pID_BUTTON_PlayerHideALL->SetVisable(false);

	m_pPlayerShowBtn[ PSM_ShowAmity ] = m_pID_BUTTON_PlayerShowAmity;
	m_pID_BUTTON_PlayerShowAmity->setTip( theXmlString.GetString( eText_ShowAmityPlayer ) );
	m_pID_BUTTON_PlayerShowAmity->SetVisable(false);

	m_pPlayerShowBtn[PSM_ShowAntagonize] = m_pID_BUTTON_PlayerShowAntagonize;
	m_pID_BUTTON_PlayerShowAntagonize->setTip( theXmlString.GetString( eText_ShowAntagonizePlayer ) );
	m_pID_BUTTON_PlayerShowAntagonize->SetVisable(false);


	m_pCurPlayerShowBtn = m_pID_BUTTON_PlayerShowALL;
    m_bPlayerShowModeOpen = false;
	m_nPlayerRenderFlag = CPlayerMgr::EPlayerRenderFlag::EPRF_ALL;*/
	

	

	

	RECT rcList;
	m_pPkBtn[PKMode_Normal]->GetRealRect(&rcList);
	m_XLog = rcList.left;
	m_YLog = rcList.top;
	m_pCurPlayerShowBtn = m_pPkBtn[PKMode_Normal];

	////记录初始位置。
	//m_pPlayerShowBtn[ PSM_ShowAll ]->GetRectSize(&rcList);
	//ShowPlayerBtnPosX = rcList.left;
	//ShowPlayerBtnPosY = rcList.top;

	////第一次排序
	//m_bCompositor = true;
	//compositor();
	//m_bCompositor = false;


    m_pExPowerEffect = new CPlaneEffect;
    InitExPowerRect();
    
    //CreateProgressAni();
	
	InitEffectAttr();

	_SetVisable( false );

	return true;
	unguard;
}
void CUI_ID_FRAME_Group_Me::SetPetInfoVisable( bool bShow, const char* headPic )
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return;
	m_pID_PICTURE_pet->SetVisable(bShow);
	m_pID_TEXT_petname->SetVisable(bShow);
	m_pID_TEXT_petlevel->SetVisable(bShow);
	m_pID_PROGRESS_petHp->SetVisable(bShow);
	m_pID_PICTURE_PetHead->SetVisable(bShow);
	m_pID_PICTURE_ChoosePet->SetVisable(bShow);
	m_pID_TEXT_petHp->SetVisable(bShow);
	

	if ( headPic != NULL)
		m_pID_PICTURE_PetHead->SetPicName( headPic );
	
	if (!bShow && theHeroGame.GetPlayerMgr()->GetMe() && s_CUI_ID_FRAME_BaseProperty.GetPetAIType() != 0)
	{
		s_CUI_ID_FRAME_BaseProperty.SetPetAIType(0);
		s_CUI_ID_FRAME_MAIN.RefeashHotKey();
		s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
		s_CUI_ID_FRAME_SKILL.RefreshCommon();
	}
	unguard;
}

void CUI_ID_FRAME_Group_Me::SetPetInfoVisable_1(bool bShow1 ,const char* headpic1 )
{
	if( !m_pID_FRAME_Group_Me )
		return;

	m_pID_PICTURE_pet1->SetVisable(bShow1);
	m_pID_PICTURE_PetHead1->SetVisable(bShow1);
	m_pID_TEXT_petname1->SetVisable(bShow1);
	m_pID_PROGRESS_petHp1->SetVisable(bShow1);
	m_pID_PICTURE_ChoosePet1->SetVisable(bShow1);
	m_pID_TEXT_petlevel1->SetVisable(bShow1);
	m_pID_PICTURE_BgPetHead1->SetVisable(bShow1);
	m_pID_TEXT_petHp1->SetVisable(bShow1);
	if (headpic1 != NULL)
	{
		m_pID_PICTURE_PetHead1->SetPicName(headpic1);
	}

	if (!bShow1 && theHeroGame.GetPlayerMgr()->GetMe() && s_CUI_ID_FRAME_BaseProperty.GetPetAIType() != 0)
	{
		s_CUI_ID_FRAME_BaseProperty.SetPetAIType(0);
		s_CUI_ID_FRAME_MAIN.RefeashHotKey();
		s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
		s_CUI_ID_FRAME_SKILL.RefreshCommon();
	}
}

// 卸载UI
void CUI_ID_FRAME_Group_Me::Destory()
{
	if( !m_pID_FRAME_Group_Me )
		return;
}

bool CUI_ID_FRAME_Group_Me::_UnLoadUI()
{
	guardfunc;

    if( m_pExPowerEffect )
        delete m_pExPowerEffect;

	m_proPicGroup.Clear();
    s_CUI_ID_FRAME_Protect.UnLoadUI();
	s_CUI_ID_FRAME_HideGroupMe.UnLoadUI();
	s_CUI_ID_FRAME_CharacterExp.UnLoadUI();
	s_CUI_ID_FRAME_MAIN.UnLoadUI();
	s_CUI_ID_FRAME_Exmain.UnLoadUI();
	s_CUI_ID_FRAME_SKILL.UnLoadUI();

	for(int i=0; i<BodyStatusType_Max; ++i)
	{
		_tBufStart[i] = 0;
		_tLastTime[i] = 0;
	}
	ResetMembers();
	return theUiManager.RemoveFrame( "data\\ui\\Group_Me.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Group_Me::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return false;
	return m_pID_FRAME_Group_Me->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Group_Me::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return;
	char szPath[MAX_PATH] = {0};	
	m_pID_FRAME_Group_Me->SetVisable( bVisable );

	s_CUI_ID_FRAME_CharacterExp.SetVisable(bVisable);
	m_bImageInited = false;
	m_bHeroImgInited = false;
	SetGuildBattleButtonVisable(false);
	unguard;
}

//每桢更新 计算 每一个状态如果过了一秒将时间减少一 时间到了状态消失
void CUI_ID_FRAME_Group_Me::Updata()
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return;

	clock_t tmNow = clock();

	unguard;
}

void CUI_ID_FRAME_Group_Me::SetStatusTime(int nIndex, DWORD dwTime)
{
	guardfunc;
	if( nIndex >= BodyStatusType_Max && nIndex < 0)
		return;

	if(_tBufStart[nIndex] == 0)
	{
		_tBufStart[nIndex] = (int)dwTime;
		_tLastTime[nIndex] = _tBufStart[nIndex];
	}
	unguard;
}

bool CUI_ID_FRAME_Group_Me::NeedUpdata()
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return false;
	for(int i=0; i<BodyStatusType_Max; i++)
	{
		if(_tBufStart[i] != 0)
			return true;
	}
	return false;
	unguard;
}
void CUI_ID_FRAME_Group_Me::SetPicHeader( bool bHeader)		// 设置是否可视
{
	guardfunc;
	if( !m_pID_FRAME_Group_Me )
		return;
	m_pID_PICTURE_Corps->SetVisable( bHeader );
	s_CUI_ID_FRAME_Group_Me.Refeash();//zjj add

	unguard;
}

// F11 快捷键响应       added by ZhuoMeng.Hu		[9/28/2010]
bool CUI_ID_FRAME_Group_Me::GroupMe_HotKey_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
    guardfunc;
    if( !s_CUI_ID_FRAME_Group_Me.IsVisable() )
        return false;

    switch( msg ) 
    {		
    case WM_KEYUP:
        {
            if( wParam == VK_F11 )
            {

				//switch (s_CUI_ID_FRAME_Group_Me.m_nPlayerRenderFlag)
				//{
				//case CPlayerMgr::EPlayerRenderFlag::EPRF_ALL:
				//	//m_pCurPlayerShowBtn = m_pPlayerShowBtn[PSM_ShowAll];
				//	s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PlayerShowALLOnButtonClick( s_CUI_ID_FRAME_Group_Me.m_pID_BUTTON_PlayerShowALL );
				//	break;

				//	case   CPlayerMgr::EPlayerRenderFlag::EPRF_ME | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER:
				//	{
				//		//m_pCurPlayerShowBtn = m_pPlayerShowBtn[PSM_HideAll];
				//		s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PlayerHideALLOnButtonClick( s_CUI_ID_FRAME_Group_Me.m_pID_BUTTON_PlayerHideALL );

				//	}
				//	break;
				//	case CPlayerMgr::EPlayerRenderFlag::EPRF_ME | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_AMITY:
				//	{
				//		s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PlayerShowAmityOnButtonClick( s_CUI_ID_FRAME_Group_Me.m_pID_BUTTON_PlayerShowAmity );

				//	}
				//	break;
				//	case CPlayerMgr::EPlayerRenderFlag::EPRF_ME | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_TEAM | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_NPC | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_MONSTER | \
				//		CPlayerMgr::EPlayerRenderFlag::EPRF_ANTAGONIZE:
				//	{
				//		s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PlayerShowAntagonizeOnButtonClick( s_CUI_ID_FRAME_Group_Me.m_pID_BUTTON_PlayerShowAntagonize );

				//	}
				//	break;
				//default:
				//	return false;
				//}
			
          /*      if( s_CUI_ID_FRAME_Group_Me.m_pPkBtn[ PKMode_Normal ]->IsVisable() )
                {
                    s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PKCloseOnButtonClick( NULL );
                    return true;
                }
                else if( s_CUI_ID_FRAME_Group_Me.m_pPkBtn[ PKMode_Fight ]->IsVisable() )
                {
                    s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PKOpenOnButtonClick( NULL );
                    return true;
                }
                else if( s_CUI_ID_FRAME_Group_Me.m_pPkBtn[ PKMode_Critical ]->IsVisable() )
                {
                    s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PKFuryOnButtonClick( NULL );
                    return true;
                }
				else if( s_CUI_ID_FRAME_Group_Me.m_pPkBtn[ PKMode_Guild ]->IsVisable() )
				{
					  s_CUI_ID_FRAME_Group_Me.ID_BUTTON_PKGuildOnButtonClick( NULL );
                    return true;
				}*/
            }
        }
        break;
    }
    return false;
    unguard;
}

void CUI_ID_FRAME_Group_Me::CreateProgressAni()
{
    if( !IsUILoad() )
        return;

    char fullname[MAX_PATH] = {0};
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerHp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Hp->CreateAnimation( fullname );
    m_pID_PROGRESS_petHp->CreateAnimation( fullname );
    MeSprintf_s( fullname, sizeof( fullname ) / sizeof( char ) - 1, "%s\\data\\ui\\UIAni\\PlayerMp.2DAni", GetRootPath() );
    m_pID_PROGRESS_Mp->CreateAnimation( fullname );
}

void CUI_ID_FRAME_Group_Me::SetGuildBattleButtonVisable(bool bShow)
{
	if( !m_pID_FRAME_Group_Me )
		return;

	m_pID_BUTTON_Faction->SetVisable(bShow);
	s_CUI_ID_FRAME_ScoreTip.SetVisable(bShow);
	m_bShowGuildBattleButton = bShow;
	m_xEffectSrray.Restart();
}

bool CUI_ID_FRAME_Group_Me::ID_BUTTON_FactionOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Group_Me )
		return false;

	s_CUI_ID_FRAME_GuildBattle.SetVisable(true);
	return true;
}

void CUI_ID_FRAME_Group_Me::InitEffectAttr()
{
	char szFullPath[MAX_PATH] = {0};
	MeSprintf_s(szFullPath, sizeof(szFullPath)/sizeof(char) - 1, gCfg.m_xGuildCampButton.m_strPicPath.c_str(), GetRootPath());
	int nRow = gCfg.m_xGuildCampButton.m_nRow;
	int nCol = gCfg.m_xGuildCampButton.m_nColumn;
	int nCount = gCfg.m_xGuildCampButton.m_nCount;
	RECT rect = {gCfg.m_xGuildCampButton.m_nStartX, gCfg.m_xGuildCampButton.m_nStartY, gCfg.m_xGuildCampButton.m_nStartX + gCfg.m_xGuildCampButton.m_nPicLength, gCfg.m_xGuildCampButton.m_nStartY + gCfg.m_xGuildCampButton.m_nPicWidth};
	DWORD time = gCfg.m_xGuildCampButton.m_nFamePerTime *  nCount;
	m_xEffectSrray.Initialize(szFullPath, nRow, nCol, nCount, rect, time);
}

void CUI_ID_FRAME_Group_Me::RefreshHeadPic(bool force)
{
	CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->GetMe();
	if( DestPlayer )
	{
		char filename[MAX_PATH] = {0};
		//主将头像不显示
		//uint16 heroid = DestPlayer->GetHeroID();
		//CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(heroid);
		//if (pHero)
		//{
		//	if (m_bHeroImgInited && !force)
		//		return;
		//	
		//	//PlayerInfoMgr::Instance()->GetPlayerHeadPic(DestPlayer, filename);
		//	m_pID_PICTURE_HairPic->SetPicName(pHero->Pic_Head.c_str());
		//	m_bHeroImgInited = true;
		//}
		//else
		{
			if (m_bImageInited && !force)
				return;

			char sex[2][32] = { "Male", "Female" };

			int hairId = DestPlayer->GetEquip()[eKeyAll_Hair].iModelID;
			int faceId = DestPlayer->GetEquip()[eKeyAll_Face].iModelID;

			MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sHairHead_%d_%d.dds",
				GetRootPath(), sex[DestPlayer->GetSex()], hairId,faceId);
			f_Handle* fp = packet_namespace::w_fopen(filename, "r");
			if (fp)
			{
				m_pID_PICTURE_HairPic->SetPicName(filename);
				packet_namespace::w_fclose(fp);
			}
			else
			{
				if (DestPlayer->GetSex() == Sex_Male)
					m_pID_PICTURE_HairPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
				else
					m_pID_PICTURE_HairPic->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
			}

			/*MeSprintf_s(filename, sizeof(filename)/sizeof(char) - 1, "%s/Data/Ui/HeadPicture/Player/%sFaceHead%d.dds",
				GetRootPath(), sex[DestPlayer->GetSex()], faceId);
			fp = packet_namespace::w_fopen(filename, "r");
			if (fp)
			{
				m_pID_PICTURE_FacePic->SetPicName(filename);
				packet_namespace::w_fclose(fp);
			}
			else
			{
				if (DestPlayer->GetSex() == Sex_Male)
					m_pID_PICTURE_FacePic->SetPicName("Data/Ui/HeadPicture/Player/DefaultMale.dds");
				else
					m_pID_PICTURE_FacePic->SetPicName("Data/Ui/HeadPicture/Player/DefaultFemale.dds");
			}*/
			m_bImageInited = true;
		}		
	}
	
}

void CUI_ID_FRAME_Group_Me::ShowButtonSpark()
{
	if (!m_bShowGuildBattleButton)
	{
		return;
	}

	RECT rect = {0, 0, 0, 0};
	m_pID_BUTTON_Faction->GetRealRect(&rect);
	m_xEffectSrray.Display(rect);
}

ControlText *CUI_ID_FRAME_Group_Me::GetPetNameControlText()
{
	return m_pID_TEXT_petname;
}