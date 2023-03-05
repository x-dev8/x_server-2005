/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\功能菜单\MainMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MainMenu.h"
#include "Skill.h"
#include "Pack.h"
#include "Property.h"
#include "PrivateShop.h"
#include "FriendDlg.h"
#include "GameMain.h"
#include "ExpStage.h"
#include "../Player.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "MiniMap.h"
#include "ChatInfoBox.h"
#include "AddMember.h"
#include "Task.h"
#include "ExitGame.h"
#include "MeUi/ControlIconDragManager.h"
#include "EscDlg.h"
#include "ActionUI.h"
#include "baseProperty.h"
#include "Me3d/Config.h"
#include "Compound.h"
#include "Target.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "Bargaining.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "Gang.h"
#include "exmain.h"
#include "Select.h"
#include "Login.h"
#include "../Effect.h"
#include "exmain.h"
#include "Group_Me.h"
#include "../Cfg.h"
#include "Pack_Ex.h"
#include "..\MotionBillBoard.h"
#include "Achivement.h"
#include "shortcutkey_configure.h"
#include "FaceDlg1.h"
#include "GameSettingUI.h"
#include "GroupPanel.h"
#include "Pet.h"
#include "RightMainMenu.h"
#include "ui/ExMenu.h"
#include "MiniMapUI.h"
#include "ShopCenter.h"
#include "PickUp.h"
#include "Country.h"
#include "Gang.h"
#include "FriendDlg.h"
#include "GameDefinePlayer.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "ui/Team.h"
#include "SuAnimal.h"
#include "LoadMap.h"
#include "GuildDefine.h"
#include "Gang.h"
#include "BasePropertyBGFrame.h"
#include "Family.h"
#include "GamMenu.h"
#include "AdditionFuncMenu.h"
#include "ChangeCountry.h"
#include "TaskMenu.h"

extern int g_nCharacterDBID;
CUI_ID_FRAME_MainMenu s_CUI_ID_FRAME_MainMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MainMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MainMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_OtherOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_StateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_SkillOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_TaskOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_PackOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_GroupOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_SystemOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_ConcealMainOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_SuAnimalOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_GamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_OnMountOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_PlayerPointOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_SuAnimalPointOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_MountPointOnButtonClick)
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MainMenu, ID_BUTTON_AdditionFuncOnButtonClick)

CUI_ID_FRAME_MainMenu::CUI_ID_FRAME_MainMenu()
{
	// Member
	m_pID_FRAME_MainMenu = NULL;
	m_pID_BUTTON_Other = NULL;
	m_pID_BUTTON_State = NULL;
	m_pID_BUTTON_Skill = NULL;
	m_pID_BUTTON_Task = NULL;
	m_pID_BUTTON_Pack = NULL;
	m_pID_BUTTON_Group = NULL;
	m_pID_BUTTON_System = NULL;
	m_pID_BUTTON_ConcealMain = NULL;
	m_pID_PROGRESS_Friend = NULL;
	m_pID_PROGRESS_Achivement = NULL;
	m_pID_PROGRESS_State = NULL;
	m_pID_PROGRESS_Skill = NULL;
	m_pID_PROGRESS_Pet = NULL;
	m_pID_PROGRESS_Country = NULL;
	m_pID_PROGRESS_Task = NULL;
	m_pID_PROGRESS_Pack = NULL;
	m_pID_PROGRESS_Guild = NULL;
	m_pID_PROGRESS_System = NULL;
	m_pID_BUTTON_SuAnimal = NULL;
	m_pID_BUTTON_Gam = NULL;
	m_pID_BUTTON_OnMount = NULL;

	m_pID_TEXT_State = NULL;
	m_pID_TEXT_Pack = NULL;
	m_pID_TEXT_Skill = NULL;
	m_pID_TEXT_SuAnimal = NULL;
	m_pID_TEXT_Task = NULL;
	m_pID_TEXT_Gam = NULL;
	m_pID_TEXT_Other = NULL;
	m_pID_TEXT_System = NULL;
	m_pID_TEXT_OnMount = NULL;
	m_pID_BUTTON_PlayerPoint = NULL;
	m_pID_BUTTON_SuAnimalPoint = NULL;
	m_pID_BUTTON_MountPoint = NULL;
	m_pID_BUTTON_AdditionFunc = NULL;
}
// Frame
bool CUI_ID_FRAME_MainMenu::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	if( IsVisable() )
	{
		if (m_pID_BUTTON_PlayerPoint)
		{
			if (s_CUI_ID_FRAME_BaseProperty.GetNoUseSkillPoint() > 0 )
			{
				m_pID_BUTTON_PlayerPoint->SetVisable(true);
				if (m_pID_TEXT_PlayerPoint)
					m_pID_TEXT_PlayerPoint->SetVisable(true);
			}
			else
			{
				m_pID_BUTTON_PlayerPoint->SetVisable(false);
				if (m_pID_TEXT_PlayerPoint)
					m_pID_TEXT_PlayerPoint->SetVisable(false);
			}
		}

		bool bSuAnimalPoint = false;
		for (int i=0;i<ITEM_PET_MAXCOUNT;++i)
		{
			if (thePlayerRole.GetPetByIndex(i).baseInfo.nPotentialPoint>0)
			{
				bSuAnimalPoint = true;
				break;
			}
		}
		if (m_pID_BUTTON_SuAnimalPoint)
		{
			if (bSuAnimalPoint )
			{
				m_pID_BUTTON_SuAnimalPoint->SetVisable(true);
				if (m_pID_TEXT_SuAnimalPoint)
					m_pID_TEXT_SuAnimalPoint->SetVisable(true);
			}
			else
			{
				m_pID_BUTTON_SuAnimalPoint->SetVisable(false);
				if (m_pID_TEXT_SuAnimalPoint)
					m_pID_TEXT_SuAnimalPoint->SetVisable(false);
			}
		}

		bool bPetPoint = false;
		for (int i=0;i<ITEM_MOUNT_MAXCOUNT;++i)
		{
			if (thePlayerRole.GetMountByIndex(i).baseInfo.nPotentialPoint>0)
			{
				bPetPoint = true;
				break;
			}
		}
		if (m_pID_BUTTON_MountPoint)
		{
			if (bPetPoint )
			{
				m_pID_BUTTON_MountPoint->SetVisable(true);
				if (m_pID_TEXT_MountPoint)
					m_pID_TEXT_MountPoint->SetVisable(true);
			}
			else
			{
				m_pID_BUTTON_MountPoint->SetVisable(false);
				if (m_pID_TEXT_MountPoint)
					m_pID_TEXT_MountPoint->SetVisable(false);
			}
		}
		
	}
	else
	{
		if (!s_CUI_ID_FRAME_LoadMap.IsMapLoading()&&!s_CUI_ID_FRAME_ChangeCountry._IsVisable())
		{
			GetUIScriptMgr()->ShowUIInTimeOfLoadMap(true);
		}
	}
	return true;
}
bool CUI_ID_FRAME_MainMenu::OnFrameRender()
{
	return true;
}


// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_OtherOnButtonClick( ControlObject* pSender )
{

    if( !m_pID_FRAME_MainMenu )
        return false;
    s_CUI_ID_FRAME_ExMenu.SetVisable( !s_CUI_ID_FRAME_ExMenu.IsVisable() );
	s_CUI_ID_FRAME_AdditionFuncMenu.SetVisable(false);
	s_CUI_ID_FRAME_GamMenu.SetVisable(false);
	s_CUI_ID_FRAME_TaskMenu.SetVisable(false);
	SetOtherHighLight();
    return true;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_StateOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MainMenu )
		return false;
	if( s_CUI_ID_FRAME_BasePropertyBGFrame.IsVisable() )
	{
		s_CUI_ID_FRAME_BasePropertyBGFrame.SetVisable(false);
	}
	else
	{
		s_CUI_ID_FRAME_BasePropertyBGFrame.SetVisable(true);
	}
	SetNeedSpark(false, ekey_baseProperty);

	SetBasePropertyHighLight();
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_SkillOnButtonClick( ControlObject* pSender )
{
    guardfunc;
    if( !m_pID_FRAME_MainMenu )
        return false;
    if(s_CUI_ID_FRAME_SKILL.IsVisable())
		s_CUI_ID_FRAME_SKILL.SetVisableWherefore(false,CUI_ID_FRAME_SKILL::EWherefore_SkillBagLearn);
        //s_CUI_ID_FRAME_SKILL.SetVisable(false);
    else
		s_CUI_ID_FRAME_SKILL.SetVisableWherefore(true,CUI_ID_FRAME_SKILL::EWherefore_SkillBagLearn);
        //s_CUI_ID_FRAME_SKILL.SetVisable(true);
	SetNeedSpark(false, ekey_skill);

	SetSkillHighLight( false );
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_TaskOnButtonClick( ControlObject* pSender )
{
    guardfunc;
    if( !m_pID_FRAME_MainMenu )
        return false;
   /* if( s_CUI_ID_FRAME_Task.IsVisable() )
        s_CUI_ID_FRAME_Task.SetVisable( false);
    else
        s_CUI_ID_FRAME_Task.SetVisable( true );*/
	s_CUI_ID_FRAME_TaskMenu.SetVisable( !s_CUI_ID_FRAME_TaskMenu.IsVisable() );
	s_CUI_ID_FRAME_ExMenu.SetVisable( false );
	s_CUI_ID_FRAME_AdditionFuncMenu.SetVisable(false);
	s_CUI_ID_FRAME_GamMenu.SetVisable(false);

	SetTaskHighLight();
    return true;
    unguard;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_PackOnButtonClick( ControlObject* pSender )
{
 guardfunc;
	if ( !m_pID_FRAME_MainMenu )
		return false;

    if(s_CUI_ID_FRAME_PACK.IsVisable())
        s_CUI_ID_FRAME_PACK.SetVisable(false);
    else
        s_CUI_ID_FRAME_PACK.SetVisable(true);
	SetNeedSpark(false, ekey_bag);

	SetPackHighLight();
    return true;

    unguard;
}

bool CUI_ID_FRAME_MainMenu::ID_BUTTON_PlayerPointOnButtonClick(ControlObject* pSender)
{
	return ID_BUTTON_StateOnButtonClick(pSender);

}

bool CUI_ID_FRAME_MainMenu::ID_BUTTON_SuAnimalPointOnButtonClick(ControlObject* pSender)
{
	return ID_BUTTON_SuAnimalOnButtonClick(pSender);

}

bool CUI_ID_FRAME_MainMenu::ID_BUTTON_MountPointOnButtonClick(ControlObject* pSender)
{
	return ID_BUTTON_OnMountOnButtonClick(pSender);

}

bool CUI_ID_FRAME_MainMenu::ID_BUTTON_AdditionFuncOnButtonClick(ControlObject* pSender)
{
	s_CUI_ID_FRAME_AdditionFuncMenu.SetVisable(!s_CUI_ID_FRAME_AdditionFuncMenu.IsVisable());
	s_CUI_ID_FRAME_ExMenu.SetVisable(false);
	s_CUI_ID_FRAME_GamMenu.SetVisable(false);
	s_CUI_ID_FRAME_TaskMenu.SetVisable(false);
	return true;
}

bool CUI_ID_FRAME_MainMenu::ID_BUTTON_OnMountOnButtonClick(ControlObject* pSender)
{
	if ( !m_pID_FRAME_MainMenu )
		return false;

	s_CUI_ID_FRAME_Pet.SetVisable(!s_CUI_ID_FRAME_Pet.IsVisable());
	SetOnMountHighLight();
	return true;
	
}


// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_GroupOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_MainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_SystemOnButtonClick( ControlObject* pSender )
{
guardfunc;
    if( !m_pID_FRAME_MainMenu )
        return false;
    {	
        if ( s_CUI_ID_FRAME_ExitGame.IsVisable() )
        {
            s_CUI_ID_FRAME_ExitGame.SetVisable( false );
        }
        else
        {
            s_CUI_ID_FRAME_ExitGame.SetVisable( true );
        }
    }

	SetSystemHighLight();
    return true;
    unguard;;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_ConcealMainOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_MainMenu )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_SuAnimalOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_MainMenu )
		return false;
	s_CUI_ID_FRAME_SuAnimal.SetVisable(!s_CUI_ID_FRAME_SuAnimal.IsVisable());

	SetSuAnimalHighLight();
	return true;
}
// Button
bool CUI_ID_FRAME_MainMenu::ID_BUTTON_GamOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_MainMenu )
		return false;
	s_CUI_ID_FRAME_GamMenu.SetVisable(!s_CUI_ID_FRAME_GamMenu.IsVisable());
	s_CUI_ID_FRAME_ExMenu.SetVisable( false );
	s_CUI_ID_FRAME_AdditionFuncMenu.SetVisable(false);
	s_CUI_ID_FRAME_TaskMenu.SetVisable(false);

	SetGamHighLight();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_MainMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MainMenu.MEUI" , true, UI_Render_LayerFirst );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MainMenu.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MainMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MainMenu, s_CUI_ID_FRAME_MainMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MainMenu, s_CUI_ID_FRAME_MainMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Other, s_CUI_ID_FRAME_MainMenuID_BUTTON_OtherOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_State, s_CUI_ID_FRAME_MainMenuID_BUTTON_StateOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Skill, s_CUI_ID_FRAME_MainMenuID_BUTTON_SkillOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Task, s_CUI_ID_FRAME_MainMenuID_BUTTON_TaskOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Pack, s_CUI_ID_FRAME_MainMenuID_BUTTON_PackOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Group, s_CUI_ID_FRAME_MainMenuID_BUTTON_GroupOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_System, s_CUI_ID_FRAME_MainMenuID_BUTTON_SystemOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_ConcealMain, s_CUI_ID_FRAME_MainMenuID_BUTTON_ConcealMainOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_SuAnimal, s_CUI_ID_FRAME_MainMenuID_BUTTON_SuAnimalOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_Gam, s_CUI_ID_FRAME_MainMenuID_BUTTON_GamOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_OnMount, s_CUI_ID_FRAME_MainMenuID_BUTTON_OnMountOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_PlayerPoint, s_CUI_ID_FRAME_MainMenuID_BUTTON_PlayerPointOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_SuAnimalPoint, s_CUI_ID_FRAME_MainMenuID_BUTTON_SuAnimalPointOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_MountPoint, s_CUI_ID_FRAME_MainMenuID_BUTTON_MountPointOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MainMenu, ID_BUTTON_AdditionFunc, s_CUI_ID_FRAME_MainMenuID_BUTTON_AdditionFuncOnButtonClick );
	
	m_pID_FRAME_MainMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MainMenu );
	m_pID_BUTTON_AdditionFunc = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_AdditionFunc );
	m_pID_BUTTON_OnMount = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_OnMount );
	m_pID_BUTTON_Other = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Other );
	m_pID_BUTTON_State = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_State );
	m_pID_BUTTON_Skill = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Skill );
	m_pID_BUTTON_Task = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Task );
	m_pID_BUTTON_Pack = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Pack );
	m_pID_BUTTON_Group = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Group );
	m_pID_BUTTON_System = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_System );
	m_pID_BUTTON_ConcealMain = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_ConcealMain );
	m_pID_PROGRESS_Friend = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Friend );
	m_pID_PROGRESS_Achivement = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Achivement );
	m_pID_PROGRESS_State = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_State );
	m_pID_PROGRESS_Skill = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Skill );
	m_pID_PROGRESS_Pet = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Pet );
	m_pID_PROGRESS_Country = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Country );
	m_pID_PROGRESS_Task = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Task );
	m_pID_PROGRESS_Pack = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Pack );
	m_pID_PROGRESS_Guild = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_Guild );
	m_pID_PROGRESS_System = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_PROGRESS_System );
	m_pID_BUTTON_SuAnimal = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_SuAnimal); 
	m_pID_BUTTON_Gam = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_Gam );
	m_pID_BUTTON_PlayerPoint = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_PlayerPoint);
	m_pID_BUTTON_SuAnimalPoint = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_SuAnimalPoint);
	m_pID_BUTTON_MountPoint = (ControlButton*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_BUTTON_MountPoint);
	m_pID_TEXT_State = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_State );
	m_pID_TEXT_Pack = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_Pack );
	m_pID_TEXT_Skill = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_Skill );
	m_pID_TEXT_SuAnimal = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_SuAnimal );
	m_pID_TEXT_Task = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_Task );
	m_pID_TEXT_Gam = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_Gam );
	m_pID_TEXT_Other = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_Other );
	m_pID_TEXT_System = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_System );
	m_pID_TEXT_OnMount = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_OnMount );

	m_pID_TEXT_PlayerPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_PlayerPoint);
	m_pID_TEXT_SuAnimalPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_SuAnimalPoint);
	m_pID_TEXT_MountPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_MainMenu, ID_TEXT_MountPoint);

	assert( m_pID_TEXT_PlayerPoint );
	assert( m_pID_TEXT_SuAnimalPoint );
	assert( m_pID_TEXT_MountPoint );
	assert(m_pID_BUTTON_AdditionFunc);
	assert( m_pID_BUTTON_MountPoint );
	assert( m_pID_BUTTON_SuAnimalPoint);
	assert( m_pID_BUTTON_PlayerPoint );
	assert( m_pID_FRAME_MainMenu );
	assert(	m_pID_BUTTON_OnMount );
	assert( m_pID_BUTTON_Other );
	assert( m_pID_BUTTON_State );
	assert( m_pID_BUTTON_Skill );
	assert( m_pID_BUTTON_Task );
	assert( m_pID_BUTTON_Pack );
	assert( m_pID_BUTTON_Group );
	assert( m_pID_BUTTON_System );
	assert( m_pID_BUTTON_ConcealMain );
	assert( m_pID_PROGRESS_Friend );
	assert( m_pID_PROGRESS_Achivement );
	assert( m_pID_PROGRESS_State );
	assert( m_pID_PROGRESS_Skill );
	assert( m_pID_PROGRESS_Pet );
	assert( m_pID_PROGRESS_Country );
	assert( m_pID_PROGRESS_Task );
	assert( m_pID_PROGRESS_Pack );
	assert( m_pID_PROGRESS_Guild );
	assert( m_pID_PROGRESS_System );
	assert( m_pID_BUTTON_SuAnimal );
	assert( m_pID_BUTTON_Gam );
	assert( m_pID_TEXT_State );
	assert( m_pID_TEXT_Pack );
	assert( m_pID_TEXT_Skill );
	assert( m_pID_TEXT_SuAnimal );
	assert( m_pID_TEXT_Task );
	assert( m_pID_TEXT_Gam );
	assert( m_pID_TEXT_Other );
	assert( m_pID_TEXT_System );
	assert( m_pID_TEXT_OnMount);

	m_pID_TEXT_State->SetEnable(false);
	m_pID_TEXT_State->SetVisable(false);
	m_pID_TEXT_PlayerPoint->SetEnable(false);
	m_pID_TEXT_PlayerPoint->SetVisable(false);
	m_pID_TEXT_SuAnimalPoint->SetEnable(false);
	m_pID_TEXT_SuAnimalPoint->SetVisable(false);
	m_pID_TEXT_MountPoint->SetEnable(false);
	m_pID_TEXT_MountPoint->SetVisable(false);
	m_pID_TEXT_Pack->SetEnable(false);
	m_pID_TEXT_Pack->SetVisable(false);
	m_pID_TEXT_Skill->SetEnable(false);
	m_pID_TEXT_Skill->SetVisable(false);
	m_pID_TEXT_SuAnimal->SetEnable(false);
	m_pID_TEXT_SuAnimal->SetVisable(false);
	m_pID_TEXT_Task->SetEnable(false);
	m_pID_TEXT_Task->SetVisable(false);
	m_pID_TEXT_Gam->SetEnable(false);
	m_pID_TEXT_Gam->SetVisable(false);
	m_pID_TEXT_Other->SetEnable(false);
	m_pID_TEXT_Other->SetVisable(false);
	m_pID_TEXT_System->SetEnable(false);
	m_pID_TEXT_System->SetVisable(false);
	m_pID_TEXT_OnMount->SetEnable(false);
	m_pID_TEXT_OnMount->SetVisable(false);

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MainMenu::_UnLoadUI()
{
	m_pID_FRAME_MainMenu = NULL;
	m_pID_BUTTON_Other = NULL;
	m_pID_BUTTON_State = NULL;
	m_pID_BUTTON_Skill = NULL;
	m_pID_BUTTON_Task = NULL;
	m_pID_BUTTON_Pack = NULL;
	m_pID_BUTTON_Group = NULL;
	m_pID_BUTTON_System = NULL;
	m_pID_BUTTON_ConcealMain = NULL;
	m_pID_PROGRESS_Friend = NULL;
	m_pID_PROGRESS_Achivement = NULL;
	m_pID_PROGRESS_State = NULL;
	m_pID_PROGRESS_Skill = NULL;
	m_pID_PROGRESS_Pet = NULL;
	m_pID_PROGRESS_Country = NULL;
	m_pID_PROGRESS_Task = NULL;
	m_pID_PROGRESS_Pack = NULL;
	m_pID_PROGRESS_Guild = NULL;
	m_pID_PROGRESS_System = NULL;
	m_pID_BUTTON_SuAnimal = NULL;
	m_pID_BUTTON_Gam = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\MainMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MainMenu::_IsVisable()
{
	if ( !m_pID_FRAME_MainMenu )
		return false;
	return m_pID_FRAME_MainMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MainMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_MainMenu )
		return ;
	m_pID_FRAME_MainMenu->SetVisable( bVisable );
	if (bVisable)
	{
		refreshHotKey();
	}	
}
#define SET_BTN_TIP_HOTKEY( pui, bshow, key) \
    if( pui ) \
{\
    pui->SetShowTip( bshow ); \
    if( bshow && pui->GetData() ) \
{ \
    static std::string str##key = pui->GetData()->m_szCaption;	\
    std::string tip = str##key;	\
    if (strlen(g_shortcutKey_configure.getValueString(key)) > 0)	\
    tip = str##key + "(" + g_shortcutKey_configure.getValueString(key) + ")";	\
    pui->setTip( tip.c_str() );\
} \
}

#define SET_BTN_TEXT_HOTKEY( pui, key) \
    if( pui ) \
{\
    if( pui->GetCaption() ) \
{ \
    static std::string str##key = pui->GetCaption();	\
    std::string tip = str##key;	\
    if (strlen(g_shortcutKey_configure.getValueString(key)) > 0)	\
    tip = str##key + "(" + g_shortcutKey_configure.getValueString(key) + ")";	\
    pui->SetCaption( tip.c_str() );\
} \
}

void SetTipAndHotKey(ControlButton* pCtl, const char* szText, AN_Configure_ShortcutKey::ShortCutKey_Configure key)
{
	if (!pCtl || !szText)
	{
		return;
	}

	if (strlen(g_shortcutKey_configure.getValueString(key)) <= 0)
	{
		return;
	}

	char szContent[256] = {0};
	MeSprintf_s(szContent, sizeof(szContent)/sizeof(char) - 1, szText, g_shortcutKey_configure.getValueString(key));

	pCtl->setTip(szContent);
	pCtl->SetShowTip(true);
}

void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key)
{
	if (!pCtl)
	{
		return;
	}

	const char *desc = g_shortcutKey_configure.getDiscription(key);
	const char *keyValue = g_shortcutKey_configure.getValueString(key);
	if(!desc || strlen(desc) <= 0 /*|| !keyValue || strlen(keyValue) <= 0*/)
	{
		return;
	}
	if (!keyValue || strlen(keyValue) <= 0)
	{
		keyValue = "\0";
	}
	char szContent[256] = {0};
	MeSprintf_s(szContent, sizeof(szContent)/sizeof(char) - 1, "%s %s", desc, keyValue);

	pCtl->setTip(szContent);
	pCtl->SetShowTip(true);
}

void CUI_ID_FRAME_MainMenu::refreshHotKey()
{
    if(!m_pID_FRAME_MainMenu)
        return;
    using namespace AN_Configure_ShortcutKey;
	SetTipAndHotKey(m_pID_BUTTON_State, AN_SCKC_uiBaseProperty);
	SetTipAndHotKey(m_pID_BUTTON_SuAnimal, AN_SCKC_uiEpic);
	SetTipAndHotKey(m_pID_BUTTON_Skill, AN_SCKC_uiSkill);
	SetTipAndHotKey(m_pID_BUTTON_Pack, AN_SCKC_uiPack);
	//SetTipAndHotKey(m_pID_BUTTON_Task, AN_SCKC_uiTask);
	SetTipAndHotKey(m_pID_BUTTON_Other,An_SCK_Other);
	SetTipAndHotKey(m_pID_BUTTON_Gam,AN_SCK_Gam);
	SetTipAndHotKey(m_pID_BUTTON_System, AN_SCKC_uiHideOrSystem);
	SetTipAndHotKey(m_pID_BUTTON_OnMount, AN_SCKC_uiPet);
	if (m_pID_BUTTON_AdditionFunc)
	{
		m_pID_BUTTON_AdditionFunc->setTip(m_pID_BUTTON_AdditionFunc->GetRealCaption());
		m_pID_BUTTON_AdditionFunc->SetShowTip(true);
	}
	if (m_pID_BUTTON_Other)
	{
		m_pID_BUTTON_Other->setTip(m_pID_BUTTON_Other->GetRealCaption());
		m_pID_BUTTON_Other->SetShowTip(true);
	}
	if (m_pID_BUTTON_Gam)
	{
		m_pID_BUTTON_Gam->setTip(m_pID_BUTTON_Gam->GetRealCaption());
		m_pID_BUTTON_Gam->SetShowTip(true);
	}
    SET_BTN_TEXT_HOTKEY( s_CUI_ID_FRAME_PickUp.GetButtonPickAll(), AN_SCKC_PickAll );

	s_CUI_ID_FRAME_GamMenu.RefreshHotKey();
	s_CUI_ID_FRAME_ExMenu.RefreshHotKey();
	//s_CUI_ID_FRAME_TaskMenu.RefreshHotKey();
}
bool CUI_ID_FRAME_MainMenu::SetBtnPicture(AN_Configure_ShortcutKey::ShortCutKey_Configure Key_Value,bool m_statu )
{
	if (m_pID_FRAME_MainMenu != NULL  )
	{
		switch (Key_Value)
		{
		case AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty:
				m_pID_BUTTON_State->SetBtnPicture(m_statu);
				return true;
		case AN_Configure_ShortcutKey::AN_SCKC_uiPack:
			   m_pID_BUTTON_Pack->SetBtnPicture(m_statu);
			   return true;
		/*case AN_Configure_ShortcutKey::AN_SCKC_uiTask:
				m_pID_BUTTON_Task->SetBtnPicture(m_statu);
				return true;*/
		case AN_Configure_ShortcutKey::AN_SCKC_uiSkill:
				m_pID_BUTTON_Skill->SetBtnPicture(m_statu);
				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiCountry:
// 				m_pID_BUTTON_Country->SetBtnPicture(m_statu);
// 				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiGroup:
// 				m_pID_BUTTON_ZuDui->SetBtnPicture(m_statu);
// 				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiGuild:
// 				m_pID_BUTTON_Guild->SetBtnPicture(m_statu);
// 				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiFriend:
// 				m_pID_BUTTON_Fiend->SetBtnPicture(m_statu);
// 				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiPet:
// 				m_pID_BUTTON_Vehicle->SetBtnPicture(m_statu);
// 				return true;
		case AN_Configure_ShortcutKey::AN_SCKC_uiCompound:
				return true;
		case AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem:
				m_pID_BUTTON_System->SetBtnPicture(m_statu);
				return true;
// 		case AN_Configure_ShortcutKey::AN_SCKC_uiFamily:
// 				m_pID_BUTTON_Family->SetBtnPicture(m_statu);
// 				return true;
		default:
				return false;
		}
	}
	return false;

}

void CUI_ID_FRAME_MainMenu::SetNeedSpark(bool bNeed, eKeySpark key)
{
	if (key < 0 || key >= ekey_max)
	{
		return;
	}
	
	if (m_xEffectSrray[key])
	{
		m_xEffectSrray[key]->SetVisable(bNeed);
	}
}

void CUI_ID_FRAME_MainMenu::InitEffectAttr()
{
	m_xEffectSrray[ekey_baseProperty] = m_pID_PROGRESS_State;
	m_xEffectSrray[ekey_skill] = m_pID_PROGRESS_Skill;
	m_xEffectSrray[ekey_pet] = m_pID_PROGRESS_Pet;
	m_xEffectSrray[ekey_country] = m_pID_PROGRESS_Country;
	m_xEffectSrray[ekey_task] = m_pID_PROGRESS_Task;
	m_xEffectSrray[ekey_bag] = m_pID_PROGRESS_Pack;
	m_xEffectSrray[ekey_friend] = m_pID_PROGRESS_Friend;
	m_xEffectSrray[ekey_guild] = m_pID_PROGRESS_Guild;
	m_xEffectSrray[ekey_achivement] = m_pID_PROGRESS_Achivement;
	m_xEffectSrray[ekey_system] = m_pID_PROGRESS_System;

	for (int i = ekey_baseProperty; i < ekey_max; ++i)
	{
		if (m_xEffectSrray[i])
		{
			m_xEffectSrray[i]->SetVisable(false);
		}
	}
}

void CUI_ID_FRAME_MainMenu::CheckNeedSparkBaseProperty()
{
	__int64 dwExp = thePlayerRole.GetExpNotUsed();
	__int64 dwNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
	if (thePlayerRole.GetLevel() >= CHAR_AUTO_LEVELUP && dwExp > dwNeedExp && !s_CUI_ID_FRAME_BaseProperty.IsVisable())
	{
		SetNeedSpark(true, ekey_baseProperty);
	}
}

void CUI_ID_FRAME_MainMenu::CheckNeedSparkPack(uint8 itemSource)
{
	if (s_CUI_ID_FRAME_PACK.IsVisable())
	{
		return;
	}

	if (EIGS_OnlineReward == itemSource || EIGS_Quest == itemSource)
	{
		SetNeedSpark(true, ekey_bag);
	}
}

void CUI_ID_FRAME_MainMenu::CheckNeedSparkAchivement()
{
// 	if (!s_CUI_ID_FRAME_Achivement.IsVisable())
// 	{
// 		SetNeedSpark(true, ekey_achivement);
// 	}
}

void CUI_ID_FRAME_MainMenu::CheckNeedSparkFriend()
{
	if (!s_CUI_ID_FRAME_Friend.IsVisable())
	{
		SetNeedSpark(true, ekey_friend);
	}		

}

void CUI_ID_FRAME_MainMenu::SetBasePropertyHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_State->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetPackHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_Pack->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetSkillHighLight( bool bVisable )
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_Skill->SetVisable(bVisable);
}

void CUI_ID_FRAME_MainMenu::SetSuAnimalHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_SuAnimal->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetTaskHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_Task->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetGamHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_Gam->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetOtherHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_Other->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetSystemHighLight()
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_TEXT_System->SetVisable(false);
}

void CUI_ID_FRAME_MainMenu::SetSuanimalState(bool bValue)
{
	if(!m_pID_FRAME_MainMenu)
		return;

	m_pID_BUTTON_SuAnimal->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_MainMenu::SetOnMountPressPic()
{
	if (m_pID_BUTTON_OnMount)
	{
		m_pID_BUTTON_OnMount->SetPressPic();
	}
	else
	{
		assert(false&&"ui error");
	}
}

void CUI_ID_FRAME_MainMenu::SetOnMountNormalPic()
{
	if (m_pID_BUTTON_OnMount)
	{
		m_pID_BUTTON_OnMount->SetNormalPic();
	}
	else
	{
		assert(false&&"ui error");
	}
}

void CUI_ID_FRAME_MainMenu::SetOnMountHighLight()
{
	if (!m_pID_FRAME_MainMenu)
	{
		return;
	}

	m_pID_TEXT_OnMount->SetVisable(false);
}