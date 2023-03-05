/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Skill.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Skill.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "FuncPerformanceLog.h"
#include "ExpStage.h"
#include "XmlStringLanguage.h"
#include "SkillLearn.h"
#include "Main.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "ActionUI.h"
#include "SkillSpirit.h"
#include "baseProperty.h"
#include "Pet.h"
#include "Pack.h"
#include "SkillProduce.h"
#include "SkillEquip.h"
#include "SkillXp.h"
#include "MainMenu.h"
#include "PetMain.h"

CUI_ID_FRAME_SKILL s_CUI_ID_FRAME_SKILL;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SKILL, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SKILL, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_BUTTON_CLOSEOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_0OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_0OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_0OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_0OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_SKILL_2OnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_JobOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_CurrencyOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_SkillTreeOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_TongyongOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_TongyongOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_TongyongOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_LISTIMG_TongyongOnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_ProduceOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_PetOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_EquipOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SKILL, ID_CHECKBOX_XpSkillOnCheckBoxCheck )
CUI_ID_FRAME_SKILL::CUI_ID_FRAME_SKILL()
{
	// Member
	ResetMembers();
	m_bNeedRefresh = false;
}

void CUI_ID_FRAME_SKILL::ResetMembers()
{
	m_pID_FRAME_SKILL = NULL;
	//m_pID_PICTURE_Di = NULL;
	m_pID_BUTTON_CLOSE = NULL;
//	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_Title = NULL;
	//m_pID_PICTURE_skillback = NULL;
	m_pID_PICTURE_skillback0 = NULL;
	m_pID_PICTURE_skillback1 = NULL;
	m_pID_PICTURE_skillback2 = NULL;
	m_pID_LISTIMG_SKILL_0 = NULL;
	m_pID_LISTIMG_SKILL_1 = NULL;
	m_pID_LISTIMG_SKILL_2 = NULL;
	m_pID_CHECKBOX_Job = NULL;
	m_pID_CHECKBOX_Currency = NULL;
	m_pID_CHECKBOX_SkillTree = NULL;
	m_pID_TEXT_Fuzhu = NULL;
	m_pID_TEXT_Beidong = NULL;
	m_pID_TEXT_Zhudong = NULL;
	m_pID_PICTURE_TDi = NULL;
	m_pID_LISTIMG_Tongyong = NULL;
	m_pID_TEXT_SkillPoint = NULL;
// 	m_pID_PICTURE_Spear = NULL;
// 	m_pID_PICTURE_Sword = NULL;
// 	m_pID_PICTURE_Bow = NULL;
// 	m_pID_PICTURE_Fan = NULL;
// 	m_pID_PICTURE_Staff = NULL;
// 	m_pID_PICTURE_skillback20 = NULL;
	m_pID_CHECKBOX_Produce = NULL;
	m_pID_TEXT_SkillName1 = NULL;
	m_pID_TEXT_SkillName2 = NULL;
	m_pID_TEXT_SkillName3 = NULL;
	m_pID_TEXT_SkillName4 = NULL;
	m_pID_TEXT_SkillName5 = NULL;
	m_pID_TEXT_SkillName6 = NULL;
	m_pID_TEXT_SkillName7 = NULL;
	m_pID_TEXT_SkillName8 = NULL;
	m_pID_TEXT_SkillDesc1 = NULL;
	m_pID_TEXT_SkillDesc2 = NULL;
	m_pID_TEXT_SkillDesc3 = NULL;
	m_pID_TEXT_SkillDesc4 = NULL;
	m_pID_TEXT_SkillDesc5 = NULL;
	m_pID_TEXT_SkillDesc6 = NULL;
	m_pID_TEXT_SkillDesc7 = NULL;
	m_pID_TEXT_SkillDesc8 = NULL;
	m_pID_CHECKBOX_XpSkill = NULL;
// 	m_pID_TEXT_SkillName9 = NULL;
// 	m_pID_TEXT_SkillName10 = NULL;
// 	m_pID_TEXT_SkillName11 = NULL;
// 	m_pID_TEXT_SkillName12 = NULL;
// 	m_pID_TEXT_SkillDesc9 = NULL;
// 	m_pID_TEXT_SkillDesc10 = NULL;
// 	m_pID_TEXT_SkillDesc11 = NULL;
// 	m_pID_TEXT_SkillDesc12 = NULL;
// 	m_pID_CHECKBOX_Equip = NULL;

	m_pID_PICTURE_1 = NULL;
	m_pID_PICTURE_2 = NULL;
	m_pID_PICTURE_3 = NULL;
	m_pID_PICTURE_4 = NULL;
	m_pID_PICTURE_5 = NULL;
	m_pID_PICTURE_6 = NULL;
	m_pID_PICTURE_7 = NULL;

	m_pID_PICTURE_TongYong = NULL;
	m_pID_PICTURE_XinFa = NULL;
	m_pID_PICTURE_ShengChan = NULL;
}
// Frame
bool CUI_ID_FRAME_SKILL::OnFrameRun()
{
	if( !IsVisable() )
		return false;
	if( m_bNeedRefresh )
	{
		m_bNeedRefresh = false;
		Refresh();
	}
	return true;
}
bool CUI_ID_FRAME_SKILL::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SKILL::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return true;
}
// Button
// bool CUI_ID_FRAME_SKILL::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SKILL )
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_0OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_0OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_0OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_0OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_SKILL_2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	UseSkill(pItem);
	return true;
}
// CheckBox
void CUI_ID_FRAME_SKILL::ID_CHECKBOX_JobOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
	//ToggleProfession();
}
// CheckBox
void CUI_ID_FRAME_SKILL::ID_CHECKBOX_CurrencyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
	ToggleCommon();
}
// CheckBox
void CUI_ID_FRAME_SKILL::ID_CHECKBOX_SkillTreeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
	
	//ToggleSkillTree();
	//显示心法界面
	ToggleSkillSpirit();
}
// ListImg / ListEx
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_TongyongOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_TongyongOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_TongyongOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	if (pItem)
	{
 		s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
 		s_CUI_ID_FRAME_ActionUI.UseFunction();
	}
	return false;
}
bool CUI_ID_FRAME_SKILL::ID_LISTIMG_TongyongOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SKILL )
		return false;
	if (pItem)
	{
 		s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
 		s_CUI_ID_FRAME_ActionUI.UseFunction();
	}
	return false;
}
void CUI_ID_FRAME_SKILL::ID_CHECKBOX_ProduceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
    ToggleSkillProduce();

	//s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(true);
}

void CUI_ID_FRAME_SKILL::ID_CHECKBOX_XpSkillOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
	//ToggleSkillXpSkill();
}
// CheckBox
void CUI_ID_FRAME_SKILL::ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SKILL )
		return;
	TogglePet();
}
// CheckBox
// void CUI_ID_FRAME_SKILL::ID_CHECKBOX_EquipOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if( !m_pID_FRAME_SKILL )
// 		return;
// 	ToggleEquipSkill();
// }
// 装载UI
void CUI_ID_FRAME_SKILL::SetVisableWherefore(const bool bVisable,EWherefore eWherefore)
{
	switch (eWherefore)
	{
	case EWherefore_NpcLearn:
		SetVisable(bVisable);
		SetObjectVisable(GetSkillTree(),false);
		SetObjectVisable(GetCurrency(),false);
		SetObjectVisable(GetProduce(),false);
		break;
	case EWherefore_SkillBagLearn:
		SetVisable(bVisable);
		if (bVisable)
		{
			SetObjectVisable(GetSkillTree(),true);
			SetObjectVisable(GetCurrency(),true);
			SetObjectVisable(GetProduce(),true);
		}
		break;
	}
}

bool CUI_ID_FRAME_SKILL::_LoadUI()
{
	s_CUI_ID_FRAME_SKILL_LEARN.LoadUI();
	//s_CUI_ID_FRAME_Skill_Spirit.LoadUI();
    s_CUI_ID_FRAME_SkillProduce.LoadUI();
	s_CUI_ID_FRAME_SkillEquip.LoadUI();
	s_CUI_ID_FRAME_XpSkill.LoadUI();

	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Skill.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Skill.MEUI]失败")
			return false;
	}

	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SKILL::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SKILL, s_CUI_ID_FRAME_SKILLOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SKILL, s_CUI_ID_FRAME_SKILLOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SKILL, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SKILLID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_SKILL, ID_BUTTON_help, s_CUI_ID_FRAME_SKILLID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL, ID_LISTIMG_SKILL_0, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_0OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_0, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_0OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_0, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_0OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL, ID_LISTIMG_SKILL_0, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_0OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL, ID_LISTIMG_SKILL_1, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_1, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_1, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL, ID_LISTIMG_SKILL_1, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL, ID_LISTIMG_SKILL_2, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_2, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL, ID_LISTIMG_SKILL_2, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL, ID_LISTIMG_SKILL_2, s_CUI_ID_FRAME_SKILLID_LISTIMG_SKILL_2OnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_Job, s_CUI_ID_FRAME_SKILLID_CHECKBOX_JobOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_Currency, s_CUI_ID_FRAME_SKILLID_CHECKBOX_CurrencyOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_SkillTree, s_CUI_ID_FRAME_SKILLID_CHECKBOX_SkillTreeOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_SKILL, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SKILLID_LISTIMG_TongyongOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_SKILL, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SKILLID_LISTIMG_TongyongOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_SKILL, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SKILLID_LISTIMG_TongyongOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_SKILL, ID_LISTIMG_Tongyong, s_CUI_ID_FRAME_SKILLID_LISTIMG_TongyongOnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_Produce, s_CUI_ID_FRAME_SKILLID_CHECKBOX_ProduceOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_Pet, s_CUI_ID_FRAME_SKILLID_CHECKBOX_PetOnCheckBoxCheck );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_Equip, s_CUI_ID_FRAME_SKILLID_CHECKBOX_EquipOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SKILL, ID_CHECKBOX_XpSkill, s_CUI_ID_FRAME_SKILLID_CHECKBOX_XpSkillOnCheckBoxCheck );

	m_pID_FRAME_SKILL = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SKILL );
	//m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Di );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SKILL, ID_BUTTON_CLOSE );
	//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SKILL, ID_BUTTON_help );
// 	m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Title );
	//m_pID_PICTURE_skillback = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_skillback );
	m_pID_PICTURE_skillback0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_skillback0 );
	m_pID_PICTURE_skillback1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_skillback1 );
	m_pID_PICTURE_skillback2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_skillback2 );
	m_pID_LISTIMG_SKILL_0 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL, ID_LISTIMG_SKILL_0 );
	m_pID_LISTIMG_SKILL_1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL, ID_LISTIMG_SKILL_1 );
	m_pID_LISTIMG_SKILL_2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL, ID_LISTIMG_SKILL_2 );
	m_pID_CHECKBOX_Job = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_Job );
	m_pID_CHECKBOX_Currency = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_Currency );
	m_pID_CHECKBOX_SkillTree = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_SkillTree );
	m_pID_TEXT_Fuzhu = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_Fuzhu );
	m_pID_TEXT_Beidong = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_Beidong );
	m_pID_TEXT_Zhudong = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_Zhudong );
	m_pID_PICTURE_TDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_TDi );
	m_pID_LISTIMG_Tongyong = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SKILL, ID_LISTIMG_Tongyong );
	m_pID_TEXT_SkillPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillPoint );
// 	m_pID_PICTURE_Spear = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Spear );
// 	m_pID_PICTURE_Sword = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Sword );
// 	m_pID_PICTURE_Bow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Bow );
// 	m_pID_PICTURE_Fan = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Fan );
// 	m_pID_PICTURE_Staff = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_Staff );
// 	m_pID_PICTURE_skillback20 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_skillback20 );
	m_pID_CHECKBOX_Produce = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_Produce );
	m_pID_TEXT_SkillName1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName1 );
	m_pID_TEXT_SkillName2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName2 );
	m_pID_TEXT_SkillName3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName3 );
	m_pID_TEXT_SkillName4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName4 );
	m_pID_TEXT_SkillName5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName5 );
	m_pID_TEXT_SkillName6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName6 );
	m_pID_TEXT_SkillName7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName7 );
	m_pID_TEXT_SkillName8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName8 );
	m_pID_TEXT_SkillDesc1 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc1 );
	m_pID_TEXT_SkillDesc2 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc2 );
	m_pID_TEXT_SkillDesc3 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc3 );
	m_pID_TEXT_SkillDesc4 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc4 );
	m_pID_TEXT_SkillDesc5 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc5 );
	m_pID_TEXT_SkillDesc6 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc6 );
	m_pID_TEXT_SkillDesc7 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc7 );
	m_pID_TEXT_SkillDesc8 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc8 );
	m_pID_PICTURE_1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_1 );
	m_pID_PICTURE_2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_2 );
	m_pID_PICTURE_3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_3 );
	m_pID_PICTURE_4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_4 );
	m_pID_PICTURE_5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_5 );
	m_pID_PICTURE_6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_6 );
	m_pID_PICTURE_7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_7 );
//  	m_pID_TEXT_SkillName9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName9 );
//  	m_pID_TEXT_SkillName10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName10 );
//  	m_pID_TEXT_SkillName11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName11 );
//  	m_pID_TEXT_SkillName12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillName12 );
//  	m_pID_TEXT_SkillDesc9 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc9 );
//  	m_pID_TEXT_SkillDesc10 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc10 );
//  	m_pID_TEXT_SkillDesc11 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc11 );
//  	m_pID_TEXT_SkillDesc12 = (ControlText*)theUiManager.FindControl( ID_FRAME_SKILL, ID_TEXT_SkillDesc12 );
	m_pID_CHECKBOX_Pet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_Pet );
	m_pID_CHECKBOX_XpSkill = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_XpSkill );
	//m_pID_CHECKBOX_Equip = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SKILL, ID_CHECKBOX_Equip );

	m_pID_PICTURE_TongYong = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_TongYong );
	m_pID_PICTURE_XinFa = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_XinFa );
	m_pID_PICTURE_ShengChan = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SKILL, ID_PICTURE_ShengChan );

    assert( m_pID_FRAME_SKILL );
	//assert( m_pID_PICTURE_Di );
	assert( m_pID_BUTTON_CLOSE );
//	assert( m_pID_BUTTON_help );
// 	assert( m_pID_PICTURE_Title );
	//assert( m_pID_PICTURE_skillback );
	assert( m_pID_PICTURE_skillback0 );
	assert( m_pID_PICTURE_skillback1 );
	assert( m_pID_PICTURE_skillback2 );
	assert( m_pID_LISTIMG_SKILL_0 );
	assert( m_pID_LISTIMG_SKILL_1 );
	assert( m_pID_LISTIMG_SKILL_2 );
	assert( m_pID_CHECKBOX_Job );
	assert( m_pID_CHECKBOX_Currency );
	assert( m_pID_CHECKBOX_SkillTree );
	assert( m_pID_TEXT_Fuzhu );
	assert( m_pID_TEXT_Beidong );
	assert( m_pID_TEXT_Zhudong );
	assert( m_pID_PICTURE_TDi );
	assert( m_pID_LISTIMG_Tongyong );
	assert( m_pID_TEXT_SkillPoint );
// 	assert( m_pID_PICTURE_Spear );
// 	assert( m_pID_PICTURE_Sword );
// 	assert( m_pID_PICTURE_Bow );
// 	assert( m_pID_PICTURE_Fan );
// 	assert( m_pID_PICTURE_Staff );
// 	assert( m_pID_PICTURE_skillback20 );
	assert( m_pID_CHECKBOX_Produce );
	assert( m_pID_TEXT_SkillName1 );
	assert( m_pID_TEXT_SkillName2 );
	assert( m_pID_TEXT_SkillName3 );
	assert( m_pID_TEXT_SkillName4 );
	assert( m_pID_TEXT_SkillName5 );
	assert( m_pID_TEXT_SkillName6 );
	assert( m_pID_TEXT_SkillName7 );
	assert( m_pID_TEXT_SkillName8 );
	assert( m_pID_TEXT_SkillDesc1 );
	assert( m_pID_TEXT_SkillDesc2 );
	assert( m_pID_TEXT_SkillDesc3 );
	assert( m_pID_TEXT_SkillDesc4 );
	assert( m_pID_TEXT_SkillDesc5 );
	assert( m_pID_TEXT_SkillDesc6 );
	assert( m_pID_TEXT_SkillDesc7 );
	assert( m_pID_TEXT_SkillDesc8 );
	assert( m_pID_PICTURE_1 );
	assert( m_pID_PICTURE_2 );
	assert( m_pID_PICTURE_3 );
	assert( m_pID_PICTURE_4 );
	assert( m_pID_PICTURE_5 );
	assert( m_pID_PICTURE_6 );
	assert( m_pID_PICTURE_7 );
	assert( m_pID_CHECKBOX_XpSkill );
// 	assert( m_pID_TEXT_SkillName9 );
// 	assert( m_pID_TEXT_SkillName10 );
// 	assert( m_pID_TEXT_SkillName11 );
// 	assert( m_pID_TEXT_SkillName12 );
// 	assert( m_pID_TEXT_SkillDesc9 );
// 	assert( m_pID_TEXT_SkillDesc10 );
// 	assert( m_pID_TEXT_SkillDesc11 );
// 	assert( m_pID_TEXT_SkillDesc12 );

	m_professionGroup.AddControl(m_pID_PICTURE_skillback0);
	m_professionGroup.AddControl(m_pID_PICTURE_skillback1);
	m_professionGroup.AddControl(m_pID_PICTURE_skillback2);
	m_professionGroup.AddControl(m_pID_LISTIMG_SKILL_0);
	m_professionGroup.AddControl(m_pID_LISTIMG_SKILL_1);
	m_professionGroup.AddControl(m_pID_LISTIMG_SKILL_2);
	m_professionGroup.AddControl(m_pID_TEXT_Fuzhu);
	m_professionGroup.AddControl(m_pID_TEXT_Beidong);
	m_professionGroup.AddControl(m_pID_TEXT_Zhudong);

	m_commonGroup.AddControl(m_pID_PICTURE_TDi);
	m_commonGroup.AddControl(m_pID_LISTIMG_Tongyong);
	m_commonDescGroup.AddControl(m_pID_PICTURE_1);
	m_commonDescGroup.AddControl(m_pID_PICTURE_2);
	m_commonDescGroup.AddControl(m_pID_PICTURE_3);
	m_commonDescGroup.AddControl(m_pID_PICTURE_4);
	m_commonDescGroup.AddControl(m_pID_PICTURE_5);
	m_commonDescGroup.AddControl(m_pID_PICTURE_6);
	m_commonDescGroup.AddControl(m_pID_PICTURE_7);
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName1 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName2 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName3 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName4 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName5 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName6 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName7 );
    m_commonDescGroup.AddControl( m_pID_TEXT_SkillName8 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillName9 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillName10 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillName11 );
// 	m_commonDescGroup.AddControl( m_pID_TEXT_SkillName12 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc1 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc2 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc3 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc4 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc5 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc6 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc7 );
	m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc8 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc9 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc10 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc11 );
//     m_commonDescGroup.AddControl( m_pID_TEXT_SkillDesc12 );
	m_commonGroup.SetVisible(false);
	m_commonDescGroup.SetVisible(false);

	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_Job);
	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_Currency);
	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_SkillTree);
	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_Produce);
	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_Pet);
	//m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_Equip);
	m_skillTypeRadioGroup.AddRadio(m_pID_CHECKBOX_XpSkill);

	m_pID_LISTIMG_SKILL_0->SetDisableCanbePick(true);
	m_pID_LISTIMG_SKILL_0->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_SKILL_0->ShowPressEffect(true);
	m_pID_LISTIMG_SKILL_1->SetDisableCanbePick(true);
	m_pID_LISTIMG_SKILL_1->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_SKILL_1->ShowPressEffect(true);
	m_pID_LISTIMG_SKILL_2->SetDisableCanbePick(true);
	m_pID_LISTIMG_SKILL_2->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_SKILL_2->ShowPressEffect(true);
	m_pID_LISTIMG_Tongyong->SetDisableCanbePick(true);
	m_pID_LISTIMG_Tongyong->SetOnlyShowItemIcon(true);
	m_pID_LISTIMG_Tongyong->ShowPressEffect(true);

	m_pID_LISTIMG_Tongyong->SetShiftLBClickFun(IconOnShiftLBClick);

   // m_pID_PICTURE_skillback20->SetVisable(false);
//     m_pID_PICTURE_Spear->SetVisable(false);
//     m_pID_PICTURE_Sword->SetVisable(false);
//     m_pID_PICTURE_Bow->SetVisable(false);
//     m_pID_PICTURE_Fan->SetVisable(false);
//     m_pID_PICTURE_Staff->SetVisable(false);

// 	if( s_CUI_ID_FRAME_SkillTree.GetFrame() )
//  		s_CUI_ID_FRAME_SkillTree.GetFrame()->SetFather(m_pID_FRAME_SKILL);
// 	if( s_CUI_ID_FRAME_SkillProduce.GetFrame() )
// 		s_CUI_ID_FRAME_SkillProduce.GetFrame()->SetFather(m_pID_FRAME_SKILL);
// 	if( s_CUI_ID_FRAME_SkillEquip.GetFrame() )
// 		s_CUI_ID_FRAME_SkillEquip.GetFrame()->SetFather(m_pID_FRAME_SKILL);


	//ToggleSkillTree();
	//s_CUI_ID_FRAME_SkillTree.SetVisable(false);

	//如果角色当前有心法，则切换到心法页面，否则切换到通用页面
	if(thePlayerRole.m_xinFaBag.GetXinFaNum() > 0)
	{
		m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_SkillTree);
		ToggleSkillSpirit();
	}
	/*else
	{
		m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Currency);
		ToggleCommon();
	}*/

	m_bNeedRefresh = false;

	SetVisable( false );

	USE_SCRIPT( eUI_OBJECT_Skill, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SKILL::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_Skill );
	m_skillTypeRadioGroup.Clear();
	m_professionGroup.Clear();
	m_commonGroup.Clear();
	m_commonDescGroup.Clear();
	s_CUI_ID_FRAME_SKILL_LEARN.UnLoadUI();
	//s_CUI_ID_FRAME_Skill_Spirit.UnLoadUI();
    s_CUI_ID_FRAME_SkillProduce.UnLoadUI();
	s_CUI_ID_FRAME_SkillEquip.UnLoadUI();
	s_CUI_ID_FRAME_XpSkill.UnLoadUI();

	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Skill.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SKILL::_IsVisable()
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return m_pID_FRAME_SKILL->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SKILL::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_SKILL )
		return;
	m_pID_FRAME_SKILL->SetVisable( bVisable );

	if (bVisable)
	{
		CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
			GetPage(CUISkillMgr::ePetSkill);
		m_pID_CHECKBOX_Pet->SetVisable(pSkillTree && pSkillTree->UISkillIcons.GetLength() > 0);

		m_pID_TEXT_SkillPoint->SetText(thePlayerRole.GetData(CPlayerRole::TYPR_SKILLEXP)/*thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp*/);
		//ToggleSkillTree();
		ToggleSkillSpirit();

		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_skill);

		CheckClearAllCommonSkill();
	}
}
void CUI_ID_FRAME_SKILL::Refresh()
{
	if( !m_pID_FRAME_SKILL )
		return;
	m_pID_TEXT_SkillPoint->SetText(thePlayerRole.GetData(CPlayerRole::TYPR_SKILLEXP)/*thePlayerRole.m_pBaseInfo->liveinfo.dwSkillExp*/);

	if (m_pID_CHECKBOX_Job->IsChecked())
	{
		//RefreshProfession();
	}
	else if (m_pID_CHECKBOX_Currency->IsChecked())
	{
		RefreshCommon();
	}
	else if( m_pID_CHECKBOX_SkillTree->IsChecked() )
	{
		//RefreshSkillTree();
		RefreshSkillSpirit();
	}
    else if( m_pID_CHECKBOX_Produce->IsChecked() )
	{
		RefreshSkillProduce();
	}
	else if( m_pID_CHECKBOX_Pet->IsChecked() )
	{
		RefreshPet();
	}
	else if( m_pID_CHECKBOX_XpSkill->IsChecked() )
	{
		RefreshSkillXpSkill();
	}
// 	else if(m_pID_CHECKBOX_XpSkill->IsChecked())
// 	{
// 		RefreshSkillSpirit();
// 	}
}

/*
void CUI_ID_FRAME_SKILL::RefreshProfession()
{
	m_pID_LISTIMG_SKILL_0->Clear();
	m_pID_LISTIMG_SKILL_1->Clear();
	m_pID_LISTIMG_SKILL_2->Clear();

	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::eProfession);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for (size_t i = 0; i < thePlayerRole.m_SkillBag.GetSkillNum(); ++i)
	{
		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex(i);
		if (!pSkill)
			continue;
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID,pSkill->stSkillLevel);
		if (!pItemSkill)
			continue;
		const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(pSkill->ustSkillID);
		if (!pIcon)
			continue;


		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);

		switch (pItemSkill->sSkillCategory)
		{
		case ItemDefine::SCT_Attack:
			{
				stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillNoNextLevel );
				stItem.SetFlags(CUISkillMgr::eProfession);

				SkillBag::SColdTime *pTime = NULL;
				pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex( i );
				if ( pTime )
				{
					stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
				}
				m_pID_LISTIMG_SKILL_0->SetItem(&stItem);
			}
			break;
		case ItemDefine::SCT_Passive:
			{
				stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
				stItem.SetFlags(CUISkillMgr::eProfession);
				m_pID_LISTIMG_SKILL_1->SetItem(&stItem);
			}
			break;
		case ItemDefine::SCT_Assistant:
			{
				stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, 0, eTipFlag_SkillNoNextLevel );
				stItem.SetFlags(CUISkillMgr::eProfession);

				SkillBag::SColdTime *pTime = NULL;
				pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex( i );
				if ( pTime )
				{
					stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
				}
				m_pID_LISTIMG_SKILL_2->SetItem(&stItem);
			}
			break;
		}
	}
}
*/

void CUI_ID_FRAME_SKILL::RefreshCommon()
{
	if( !m_pID_FRAME_SKILL )
		return;
	if (m_pID_CHECKBOX_Pet->IsChecked())
	{
		RefreshPet();
		return;
	}

	if (!m_pID_CHECKBOX_Currency->IsChecked())
		return;

	m_pID_LISTIMG_Tongyong->Clear();

	CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::eCommon);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	int nTempIndex = 0;
	for (size_t i = 0; i< pSkillIcon->GetLength(); ++i)
	{
		const SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];

		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);

		eIconDrawState eEnable = eIcon_Enable;
        BOOL bInWater = FALSE;
        if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsInWater() )
            bInWater = TRUE;
		if ((CUI_ID_FRAME_BaseProperty::TYPE_SITDWON_ACTION == pIcon->iconid ||
			CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pIcon->iconid) &&
			(thePlayerRole.IsFighting() || bInWater) )
			eEnable = eIcon_Disable;

		if ( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pIcon->iconid &&
			(!s_CUI_ID_FRAME_Pet.IsActivedPet() || bInWater) )
			eEnable = eIcon_Disable;

		if (pIcon->iconid >= CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK &&
			pIcon->iconid <= CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND &&
			theHeroGame.GetPlayerMgr()->GetMe() &&
			!theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
		{
			eEnable = eIcon_Disable;
		}

		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pIcon->iconid );
		int nLvl = 1;
		if (pIcon->iconid > 1000)
		{
			if( !pSkill )
				continue;

			nLvl = pSkill->stSkillLevel;
			stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
			stItem.SetFlags(CUISkillMgr::eCommon);

			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( pSkill->ustSkillID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}
		else
		{
			stItem.SetData( pIcon->iconid, nLvl, eEnable, 0, eTipFlag_SkillNoNextLevel );
			stItem.SetFlags(CUISkillMgr::eCommon);
		}

		if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}
		else if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2 );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
			continue; //lyh-- 防卡回城
		}
		else if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_MOUNT)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT_SKILL_ID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);
		if (s_CUI_ID_FRAME_BaseProperty.GetPetAIType() == pIcon->iconid)
		{
			stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
		}

		m_pID_LISTIMG_Tongyong->SetItem(&stItem);
		
        // 更新Skill名字和描述
		s_CUI_ID_FRAME_SKILL.UpdateCommonSkillInfo(pIcon->iconid, nTempIndex);
		nTempIndex++;
	}
	if(!SuitSkillMap.empty())
	{
		std::map<unsigned short,unsigned short>::iterator Iter = SuitSkillMap.begin();
		for(;Iter != SuitSkillMap.end();++Iter)
		{
			unsigned short SkillID = Iter->first;
			unsigned short SkillLevel = Iter->second;
			
			ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(SkillID, SkillLevel);
			if (!pItemSkill)
				return;
			ControlIconDrag::S_ListImg stItem;
			SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(SkillID);
			if (iconSet)
				stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
			stItem.SetData( SkillID, SkillLevel, eIcon_Enable, true, eTipFlag_SkillTree );
			stItem.SetFlags(CUISkillMgr::eCommon);
			m_pID_LISTIMG_Tongyong->SetItem(&stItem);
			UpdateCommonSkillInfo(SkillID,nTempIndex);
			++nTempIndex;
		}
	}
}
void CUI_ID_FRAME_SKILL::AddCommonSkillBySuitEquip(unsigned short SkillID,unsigned short SkillLevel)
{
	//根据技能等级添加技能
	if(!m_pID_FRAME_SKILL)
	{
		_LoadUI();
		if(!m_pID_FRAME_SKILL)
			return;
	}
	SuitSkillMap.insert(std::map<unsigned short,unsigned short>::value_type(SkillID, SkillLevel));
	RefreshCommon();
}
void CUI_ID_FRAME_SKILL::ClearCommonSkillBySuitEquip(unsigned short SkillID)
{
	if(!m_pID_FRAME_SKILL)
	{
		_LoadUI();
		if(!m_pID_FRAME_SKILL)
			return;
	}
	if(SuitSkillMap.count(SkillID) == 0)
		return;
	SuitSkillMap.erase(SkillID);
	ClearCommonSkillInfo();
	RefreshCommon();
}
void CUI_ID_FRAME_SKILL::CheckClearAllCommonSkill()
{
	bool IsChange = false;
	std::map<unsigned short,unsigned short>::iterator Iter = SuitSkillMap.begin();
	for(;Iter != SuitSkillMap.end();)
	{
		unsigned short SkillID = Iter->first;
		unsigned short SkillLevel = Iter->second;
		if(!thePlayerRole.m_SkillBag.GetSkillByID( SkillID ))
		{
			Iter = SuitSkillMap.erase(Iter);
			IsChange = true;
		}
		else
			++Iter;
	}
	if(IsChange)
	{
		ClearCommonSkillInfo();
		RefreshCommon();
	}
}
// void CUI_ID_FRAME_SKILL::RefreshSkillTree()
// {
//  	s_CUI_ID_FRAME_SkillTree.RefreshSkillTree();
//  	s_CUI_ID_FRAME_SkillTree.RefreshSkillPoint();
// }

void  CUI_ID_FRAME_SKILL::RefreshSkillSpirit()
{
	//s_CUI_ID_FRAME_Skill_Spirit.Refresh();
	s_CUI_ID_FRAME_SKILL_LEARN.Refresh();
}

void CUI_ID_FRAME_SKILL::RefreshPet()
{
	if (!m_pID_CHECKBOX_Pet->IsChecked())
		return;

	m_pID_LISTIMG_Tongyong->Clear();

	CUISkillTreeConfig::SkillTreePage* pSkillTree = g_UISkillMgr.m_SkillTreeConfig.
		GetPage(CUISkillMgr::ePetSkill);
	if (!pSkillTree)
		return;

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for (size_t i = 0; i< pSkillIcon->GetLength(); ++i)
	{
		const SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];

		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);

		eIconDrawState eEnable = eIcon_Enable;
		BOOL bInWater = FALSE;
		if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsInWater() )
			bInWater = TRUE;
		if ((CUI_ID_FRAME_BaseProperty::TYPE_SITDWON_ACTION == pIcon->iconid ||
			CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pIcon->iconid) &&
			(thePlayerRole.IsFighting() || bInWater) )
			eEnable = eIcon_Disable;

		if ( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pIcon->iconid &&
			(!s_CUI_ID_FRAME_Pet.IsActivedPet() || bInWater) )
			eEnable = eIcon_Disable;

		if (pIcon->iconid >= CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK &&
			pIcon->iconid <= CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND &&
			theHeroGame.GetPlayerMgr()->GetMe() &&
			!theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
		{
			eEnable = eIcon_Disable;
		}

		SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pIcon->iconid );
		int nLvl = 1;
		if( pSkill )
		{
			nLvl = pSkill->stSkillLevel;
		}
		stItem.SetData( pIcon->iconid, nLvl, eEnable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::eCommon); // 和Common一致，行为一样，不需要ePetSkill

		if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}
		else if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2 );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
			continue;  //lyh取消防卡回城加入到通用技能。
		}
		else if (pIcon->iconid == CUI_ID_FRAME_BaseProperty::TYPE_MOUNT)
		{
			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT_SKILL_ID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);
		if (s_CUI_ID_FRAME_BaseProperty.GetPetAIType() == pIcon->iconid)
		{
			stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
		}

		m_pID_LISTIMG_Tongyong->SetItem(&stItem);

		// 更新Skill名字和描述，和Common共用一个界面
		s_CUI_ID_FRAME_SKILL.UpdateCommonSkillInfo(pIcon->iconid, i);
	}
}

void CUI_ID_FRAME_SKILL::RefreshEquipSkill()
{
	s_CUI_ID_FRAME_SkillEquip.Refresh();
}

// void CUI_ID_FRAME_SKILL::ToggleProfession()
// {
// 	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
//  	s_CUI_ID_FRAME_SkillTree.SetVisable(false);
// 	m_professionGroup.SetVisible(true);
// 	m_commonGroup.SetVisible(false);
// 	m_commonDescGroup.SetVisible(false);
// 	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Job);
// 	RefreshProfession();
// }

void CUI_ID_FRAME_SKILL::ToggleCommon()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
 	//s_CUI_ID_FRAME_Skill_Spirit.SetVisable(false);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(false);
    s_CUI_ID_FRAME_SkillProduce.SetVisable(/*false*/true);
	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(true);
	m_commonDescGroup.SetVisible(true);
	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Currency);

	{
		if(m_pID_PICTURE_TongYong)
			m_pID_PICTURE_TongYong->SetVisable(true);

		if(m_pID_PICTURE_XinFa)
			m_pID_PICTURE_XinFa->SetVisable(false);

		if(m_pID_PICTURE_ShengChan)
			m_pID_PICTURE_ShengChan->SetVisable(false);
	}

	RefreshCommon();
	RefreshSkillProduce();
}

void CUI_ID_FRAME_SKILL::ToggleSkillSpirit()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(true);
	//s_CUI_ID_FRAME_Skill_Spirit.SetVisable(true);
	s_CUI_ID_FRAME_SkillProduce.SetVisable(false);
	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(false);
	m_commonDescGroup.SetVisible(false);
	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_SkillTree);

	{
		if(m_pID_PICTURE_TongYong)
			m_pID_PICTURE_TongYong->SetVisable(false);

		if(m_pID_PICTURE_XinFa)
			m_pID_PICTURE_XinFa->SetVisable(true);

		if(m_pID_PICTURE_ShengChan)
			m_pID_PICTURE_ShengChan->SetVisable(false);
	}

	RefreshSkillSpirit();
}

// void CUI_ID_FRAME_SKILL::ToggleSkillTree()
// {
// 	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
//  	s_CUI_ID_FRAME_SkillTree.SetVisable(true);
//     s_CUI_ID_FRAME_SkillProduce.SetVisable(false);
// 	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
// 	m_professionGroup.SetVisible(false);
// 	m_commonGroup.SetVisible(false);
// 	m_commonDescGroup.SetVisible(false);
// 	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_SkillTree);
// 	RefreshSkillTree();
// }

void CUI_ID_FRAME_SKILL::RefreshSkillProduce()
{
    s_CUI_ID_FRAME_SkillProduce.Update();
}

void CUI_ID_FRAME_SKILL::ToggleSkillProduce()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(false);
    //s_CUI_ID_FRAME_Skill_Spirit.SetVisable(false);
    s_CUI_ID_FRAME_SkillProduce.SetVisable(true);
	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(false);
	m_commonDescGroup.SetVisible(false);
    m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Produce);

	{
		if(m_pID_PICTURE_TongYong)
			m_pID_PICTURE_TongYong->SetVisable(false);

		if(m_pID_PICTURE_XinFa)
			m_pID_PICTURE_XinFa->SetVisable(false);

		if(m_pID_PICTURE_ShengChan)
			m_pID_PICTURE_ShengChan->SetVisable(true);
	}

    RefreshSkillProduce();
}

void CUI_ID_FRAME_SKILL::TogglePet()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(false);
	//s_CUI_ID_FRAME_Skill_Spirit.SetVisable(false);
	s_CUI_ID_FRAME_SkillProduce.SetVisable(false);
	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(true);
	m_commonDescGroup.SetVisible(false);
	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Pet);
	RefreshPet();
}

void CUI_ID_FRAME_SKILL::ToggleEquipSkill()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(true);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(false);
 	//s_CUI_ID_FRAME_Skill_Spirit.SetVisable(false);
    s_CUI_ID_FRAME_SkillProduce.SetVisable(false);
	s_CUI_ID_FRAME_XpSkill.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(false);
	m_commonDescGroup.SetVisible(false);
	//m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_Equip);
	RefreshEquipSkill();
}

void CUI_ID_FRAME_SKILL::RefreshSkillXpSkill()
{
	s_CUI_ID_FRAME_XpSkill.Update();
}

void CUI_ID_FRAME_SKILL::ToggleSkillXpSkill()
{
	s_CUI_ID_FRAME_SkillEquip.SetVisable(false);
	s_CUI_ID_FRAME_SKILL_LEARN.SetVisable(false);
	//s_CUI_ID_FRAME_Skill_Spirit.SetVisable(false);
	s_CUI_ID_FRAME_XpSkill.SetVisable(true);
	s_CUI_ID_FRAME_SkillProduce.SetVisable(false);
	m_professionGroup.SetVisible(false);
	m_commonGroup.SetVisible(false);
	m_commonDescGroup.SetVisible(false);
	m_skillTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_XpSkill);
	RefreshSkillXpSkill();
}

bool CUI_ID_FRAME_SKILL::IsSkillList( const ControlObject* pObject )
{
    //if( s_CUI_ID_FRAME_SkillTree.IsSkillList( pObject ) 
	if(/*s_CUI_ID_FRAME_Skill_Spirit.IsSkillList(pObject)*/
		s_CUI_ID_FRAME_SKILL_LEARN.IsSkillList(pObject)
		|| s_CUI_ID_FRAME_Pet.IsSkillList( pObject ) 
		|| s_CUI_ID_FRAME_SkillEquip.IsLISTIMG_Tongyong( pObject ) 
		|| s_CUI_ID_FRAME_PetMain.IsSkillList( pObject ) 
		|| s_CUI_ID_FRAME_XpSkill.IsSkillList( pObject ) 
		)
    {
        return true;
    }
    else
    {
        if( !m_pID_FRAME_SKILL )
            return false;
        return ( m_pID_LISTIMG_SKILL_0 == pObject || m_pID_LISTIMG_SKILL_1 == pObject ||
            m_pID_LISTIMG_SKILL_2 == pObject || m_pID_LISTIMG_Tongyong == pObject );
    }
}

bool CUI_ID_FRAME_SKILL::InitSkillTree()
{
// 	if( !m_pID_FRAME_SKILL )
// 		return false;
	g_UISkillMgr.InitialAllProfession();
	g_UISkillMgr.Init( thePlayerRole.GetProfession() );
	return true;
}

void CUI_ID_FRAME_SKILL::UseSkill(ControlIconDrag::S_ListImg* pItem)
{
	if (!pItem)
		return;

	SCharSkill* pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pItem->m_pkIconInfo->Id() );
	if (!pSkill)
		return;

	theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
		pSkill->stSkillLevel );

	thePlayerRole.UpdateUI();
	theHeroGame.GetPlayerMgr()->OnSkill( false );
}

void CUI_ID_FRAME_SKILL::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	assert(pItem != NULL);

	//SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
	////assert(IsValidXinFaSkill(pCharSkill));
	//if(NULL == pCharSkill /*|| !IsValidXinFaSkill(pCharSkill)*/)
	//{
	//	return;
	//}

	ItemDefine::SItemSkill* pItemSKill = GettheItemDetail().GetSkillByID( pItem->m_pkIconInfo->Id(), 1 );
	if ( pItemSKill == NULL )
	{
		return;
	}

	CommonChatFrame::GetActiveChatFrame()->addHyberTextEx( pItemSKill->GetItemName(), MsgChat::HYBERTYPE_SKILL,  pItemSKill->ustItemID, 1 );	
}
void CUI_ID_FRAME_SKILL::ClearCommonSkillInfo()
{
	m_pID_TEXT_SkillName1->SetText("");
    m_pID_TEXT_SkillDesc1->SetText("");
	m_pID_TEXT_SkillName1->SetVisable(false);
	m_pID_TEXT_SkillDesc1->SetVisable(false);

	m_pID_TEXT_SkillName2->SetText("");
    m_pID_TEXT_SkillDesc2->SetText("");
	m_pID_TEXT_SkillName2->SetVisable(false);
	m_pID_TEXT_SkillDesc2->SetVisable(false);

	m_pID_TEXT_SkillName3->SetText("");
    m_pID_TEXT_SkillDesc3->SetText("");
	m_pID_TEXT_SkillName3->SetVisable(false);
	m_pID_TEXT_SkillDesc3->SetVisable(false);

	m_pID_TEXT_SkillName4->SetText("");
    m_pID_TEXT_SkillDesc4->SetText("");
	m_pID_TEXT_SkillName4->SetVisable(false);
	m_pID_TEXT_SkillDesc4->SetVisable(false);

	m_pID_TEXT_SkillName5->SetText("");
    m_pID_TEXT_SkillDesc5->SetText("");
	m_pID_TEXT_SkillName5->SetVisable(false);
	m_pID_TEXT_SkillDesc5->SetVisable(false);

	m_pID_TEXT_SkillName6->SetText("");
    m_pID_TEXT_SkillDesc6->SetText("");
	m_pID_TEXT_SkillName6->SetVisable(false);
	m_pID_TEXT_SkillDesc6->SetVisable(false);

	m_pID_TEXT_SkillName7->SetText("");
    m_pID_TEXT_SkillDesc7->SetText("");
	m_pID_TEXT_SkillName7->SetVisable(false);
	m_pID_TEXT_SkillDesc7->SetVisable(false);

	m_pID_TEXT_SkillName8->SetText("");
    m_pID_TEXT_SkillDesc8->SetText("");
	m_pID_TEXT_SkillName8->SetVisable(false);
	m_pID_TEXT_SkillDesc8->SetVisable(false);

}
void CUI_ID_FRAME_SKILL::UpdateCommonSkillInfo( int iIconId, int index )
{
    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(iIconId);
    if (!pItem)
        return;

    char szTemp[MAX_PATH] = {0};
    char szDesc[MAX_PATH] = {0};
    DWORD dwColor;
    strcpy(szTemp, pItem->GetItemDesc());
    sscanf(szTemp, "<#%8X%s>", &dwColor, &szDesc);

    switch( index )
    {
    case 0:
        m_pID_TEXT_SkillName1->SetText(pItem->GetItemName());
        m_pID_TEXT_SkillDesc1->SetText(szDesc);
		m_pID_TEXT_SkillName1->SetVisable(true);
		m_pID_TEXT_SkillDesc1->SetVisable(true);
        break;
    case 1:
        m_pID_TEXT_SkillName2->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc2->SetText(szDesc);
		m_pID_TEXT_SkillName2->SetVisable(true);
		m_pID_TEXT_SkillDesc2->SetVisable(true);
        break;
    case 2:
        m_pID_TEXT_SkillName3->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc3->SetText(szDesc);
		m_pID_TEXT_SkillName3->SetVisable(true);
		m_pID_TEXT_SkillDesc3->SetVisable(true);
        break;
    case 3:
        m_pID_TEXT_SkillName4->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc4->SetText(szDesc);
		m_pID_TEXT_SkillName4->SetVisable(true);
		m_pID_TEXT_SkillDesc4->SetVisable(true);
        break;
    case 4:
        m_pID_TEXT_SkillName5->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc5->SetText(szDesc);
		m_pID_TEXT_SkillName5->SetVisable(true);
		m_pID_TEXT_SkillDesc5->SetVisable(true);
        break;
    case 5:
        m_pID_TEXT_SkillName6->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc6->SetText(szDesc);
		m_pID_TEXT_SkillName6->SetVisable(true);
		m_pID_TEXT_SkillDesc6->SetVisable(true);
        break;
    case 6:
        m_pID_TEXT_SkillName7->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc7->SetText(szDesc);
		m_pID_TEXT_SkillName7->SetVisable(true);
		m_pID_TEXT_SkillDesc7->SetVisable(true);
        break;
    case 7:
        m_pID_TEXT_SkillName8->SetText(pItem->GetItemName());
		m_pID_TEXT_SkillDesc8->SetText(szDesc);
		m_pID_TEXT_SkillName8->SetVisable(true);
		m_pID_TEXT_SkillDesc8->SetVisable(true);
        break;
//     case 8:
//         m_pID_TEXT_SkillName9->SetText(pItem->GetItemName());
// 		m_pID_TEXT_SkillDesc9->SetText(szDesc);
// 		m_pID_TEXT_SkillName9->SetVisable(true);
// 		m_pID_TEXT_SkillDesc9->SetVisable(true);
//         break;
//     case 9:
//         m_pID_TEXT_SkillName10->SetText(pItem->GetItemName());
// 		m_pID_TEXT_SkillDesc10->SetText(szDesc);
// 		m_pID_TEXT_SkillName10->SetVisable(true);
// 		m_pID_TEXT_SkillDesc10->SetVisable(true);
//         break;
//     case 10:
//         m_pID_TEXT_SkillName11->SetText(pItem->GetItemName());
// 		m_pID_TEXT_SkillDesc11->SetText(szDesc);
// 		m_pID_TEXT_SkillName11->SetVisable(true);
// 		m_pID_TEXT_SkillDesc11->SetVisable(true);
//         break;
//     case 11:
//         m_pID_TEXT_SkillName12->SetText(pItem->GetItemName());
// 		m_pID_TEXT_SkillDesc12->SetText(szDesc);
// 		m_pID_TEXT_SkillName12->SetVisable(true);
// 		m_pID_TEXT_SkillDesc12->SetVisable(true);
//         break;
    }
}

//ControlPicture* CUI_ID_FRAME_SKILL::GetPICTURE_skillback20()
//{
//	//if( !m_pID_FRAME_SKILL )
//		return NULL;
//	//return m_pID_PICTURE_skillback20;
//}
//
//void CUI_ID_FRAME_SKILL::PICTURE_Staff_SetVisable( bool bVisible )
//{
//// 	if( !m_pID_FRAME_SKILL )
//// 		return;
//// 	m_pID_PICTURE_Staff->SetVisable(bVisible);
//}
//
//void CUI_ID_FRAME_SKILL::PICTURE_Spear_SetVisable( bool bVisible )
//{
//// 	if( !m_pID_FRAME_SKILL )
//// 		return;
//// 	m_pID_PICTURE_Spear->SetVisable(bVisible);
//}
//
//void CUI_ID_FRAME_SKILL::PICTURE_Sword_SetVisable( bool bVisible )
//{
//// 	if( !m_pID_FRAME_SKILL )
//// 		return;
//// 	m_pID_PICTURE_Sword->SetVisable(bVisible);
//}
//
//void CUI_ID_FRAME_SKILL::PICTURE_Bow_SetVisable( bool bVisible )
//{
//// 	if( !m_pID_FRAME_SKILL )
//// 		return;
//// 	m_pID_PICTURE_Bow->SetVisable(bVisible);
//}
//
//void CUI_ID_FRAME_SKILL::PICTURE_Fan_SetVisable( bool bVisible )
//{
//// 	if( !m_pID_FRAME_SKILL )
//// 		return;
//// 	m_pID_PICTURE_Fan->SetVisable(bVisible);
//}

bool CUI_ID_FRAME_SKILL::CHECKBOX_Job_IsChecked()
{
	if( !m_pID_FRAME_SKILL )
		return false;
	return m_pID_CHECKBOX_Job->IsChecked();
}


CUISkillMgr g_UISkillMgr;

CUISkillTreeConfig::CUISkillTreeConfig()
	: m_strProfession("robber")
{
}

bool CUISkillTreeConfig::loadXMLSettings( const char *path  )
{
	m_UISkillIconSet.clear();

	MeXmlDocument doc;
	if (!doc.LoadFile(path))
		return false;

	return loadXMLSettings( doc.FirstChildElement("Project") );
}

bool CUISkillTreeConfig::SetProfession( string szString )
{
	m_strProfession = szString;
	return true;
}

bool CUISkillTreeConfig::ReadProfession( MeXmlElement *element )
{
	if( !element )
		return false;

	MeXmlElement  *child   = NULL;
	child =	element->FirstChildElement("Profession");
	if( child )
		AddPos( child, CUISkillMgr::eProfession );

	child = element->FirstChildElement( "Common" );
	if( child )
		AddPos( child, CUISkillMgr::eCommon );

	child = element->FirstChildElement( "Produce" );
	if( child )
		AddPos( child, CUISkillMgr::eProduce );	

	child = element->FirstChildElement( "Pet" );
	if( child )
		AddPos( child, CUISkillMgr::ePetSkill );	

	child = element->FirstChildElement( "EquipSkill" );
	if( child )
		AddPos( child, CUISkillMgr::eEquipSkill );

	child = element->FirstChildElement( "XpSkill" );
	if( child )
		AddPos( child, CUISkillMgr::eXpSkill );

	return true;
}

bool CUISkillTreeConfig::AddPos( MeXmlElement *element, int type )
{
	SkillTreePage		skilltree;

	const char* bg = element->Attribute("Bg");
	if( bg )
		strncpy(skilltree.szBgPath,bg, MAX_PATH-1 );

	MeXmlElement *child = element->FirstChildElement("Icon");
	while (child)
	{
		SUIIconSet::SIconSet pt;

		int value = 0;
		child->QueryIntAttribute("Index", &value);
		pt.index = value;

		child->QueryIntAttribute("IconId", &value);
		pt.iconid = value;
		if (pt.iconid == 0)
		{
			child = child->NextSiblingElement("Icon");
			continue;
		}

		const char* str = child->Attribute("Image");
		if( str )
			pt.image = str;

		child->QueryIntAttribute("IconSize", &value);
		pt.iconSize = value;

		child->QueryIntAttribute("Row", &value);
		pt.row = value;

		child->QueryIntAttribute("Column", &value);
		pt.column = value;

		skilltree.UISkillIcons.AddAllPos( pt );		

		child = child->NextSiblingElement("Icon");	
	}
	m_UISkillIconSet[type] = skilltree;
	return true;
}

bool CUISkillTreeConfig::ReadMountSkill(MeXmlElement *element)
{
	if( !element )
		return false;

	return AddPos(element, CUISkillMgr::eMountSkill);
}

bool CUISkillTreeConfig::loadXMLSettings( MeXmlElement *element )
{
	if (!element)
		return false;

	MeXmlElement *child = element->FirstChildElement("SkillTreeConfig")->FirstChildElement("Profession");
	while (child)
	{
		const char* v = child->Attribute("Name");
		if (v && v == m_strProfession)
			ReadProfession( child );

		child = child->NextSiblingElement("Profession");
	}

	ReadMountSkill(element->FirstChildElement("SkillMount"));

	return true;
}

CUISkillMgr::CUISkillMgr():m_nProfession(-1)
{
}

CUISkillMgr::~CUISkillMgr()
{
	Release();
}

bool	CUISkillMgr::LearnSkill( ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool	CUISkillMgr::OnRButtonUP( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !pItem )
		return false;
	return true;
}

void CUISkillMgr::Release()
{
	m_vtSkillicon.clear();
	m_vtBgPic.clear();
	m_vtBtnSkillUp.clear();
}

void CUISkillMgr::AddBgPic( ControlPicture* pPic )
{
	if( pPic )
		m_vtBgPic.push_back( pPic );
}
void CUISkillMgr::AddButtonSkillUp(ControlButton* pBtn)
{
	if( pBtn )
		m_vtBtnSkillUp.push_back( pBtn );
}
void CUISkillMgr::AddBgSkillicon( ControlListImage* pImg )
{
	if( pImg )
		m_vtSkillicon.push_back( pImg );
}
void CUISkillMgr::Init( int nProfession )
{
// 	if (NULL == s_CUI_ID_FRAME_SKILL.GetPICTURE_skillback20())
// 	{
// 		return;
// 	}
	string strProfession = "Spear";
	m_nProfession = nProfession;
    //s_CUI_ID_FRAME_SKILL.GetPICTURE_skillback20()->SetVisable(true);
 	switch( m_nProfession )
 	{
 	case EArmType_Mage:
 		strProfession = "Staff";
       //  s_CUI_ID_FRAME_SKILL.PICTURE_Staff_SetVisable(true);
 		break;
 	case EArmType_Warrior:
 		strProfession = "Spear";
      //   s_CUI_ID_FRAME_SKILL.PICTURE_Spear_SetVisable(true);
 		break;
 	case EArmType_Assassin:
 		strProfession = "Sword";
      //   s_CUI_ID_FRAME_SKILL.PICTURE_Sword_SetVisable(true);
 		break;
 	case EArmType_Taoist:
 		strProfession = "Fan";
     //    s_CUI_ID_FRAME_SKILL.PICTURE_Bow_SetVisable(true);
 		break;
 	case EArmType_Hunter:
 		strProfession = "Bow";
     //    s_CUI_ID_FRAME_SKILL.PICTURE_Fan_SetVisable(true);
 		break;
 	default:
 		{
 			assert( false && "Profession error");
 			Init( EArmType_Warrior );
 			return;
 		}
 		break;
 	}

	m_SkillTreeConfig.SetProfession( strProfession );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	//m_xinFaIconConfig.LoadIconConfig("..\\Data\\Config\\xinFaIcon.config");
}

void CUISkillMgr::InitialAllProfession()
{
	m_SkillTreeConfig.SetProfession( "Staff" );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	m_vtAllSkillTreeConfig.push_back(m_SkillTreeConfig);
	m_SkillTreeConfig.SetProfession( "Spear" );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	m_vtAllSkillTreeConfig.push_back(m_SkillTreeConfig);
	m_SkillTreeConfig.SetProfession( "Sword" );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	m_vtAllSkillTreeConfig.push_back(m_SkillTreeConfig);
	m_SkillTreeConfig.SetProfession( "Fan" );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	m_vtAllSkillTreeConfig.push_back(m_SkillTreeConfig);
	m_SkillTreeConfig.SetProfession( "Bow" );
	m_SkillTreeConfig.loadXMLSettings("..\\Data\\Config\\SkillIcon.config");
	m_vtAllSkillTreeConfig.push_back(m_SkillTreeConfig);
	if ( m_nProfession >= 0 )
	{
		this->Init(m_nProfession);	//将当前的职业重置为该玩家的职业
	}
	
}

// const SUIIconSet::SIconSet* CUISkillMgr::GetXinFaIconSet(int id)
// {
// 	return m_xinFaIconConfig.GetXinFaIconSet(id);
// }

SUIIconSet::SIconSet* CUISkillMgr::GetSkillIconSet(int id)
{
	CUISkillTreeConfig::SkillTreePage *pSkillTree = m_SkillTreeConfig.GetPage(eProfession);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(eCommon);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(eProduce);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(eMountSkill);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(ePetSkill);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(eEquipSkill);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}
	pSkillTree = m_SkillTreeConfig.GetPage(eXpSkill);
	if( pSkillTree )
	{	
		SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
		for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
		{
			SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
			if (pIcon->iconid == id)
				return pIcon;
		}
	}

	return 0;
}

SUIIconSet::SIconSet* CUISkillMgr::GetAllSkillIconSet(int id)
{
	int treeCount = (int)m_vtAllSkillTreeConfig.size();
	for ( int i = 0; i < treeCount; i ++ )
	{
		CUISkillTreeConfig::SkillTreePage *pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eProfession);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eCommon);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eProduce);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eMountSkill);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(ePetSkill);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eEquipSkill);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
		pSkillTree = m_vtAllSkillTreeConfig[i].GetPage(eXpSkill);
		if( pSkillTree )
		{	
			SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;
			for( size_t i  = 0; i<pSkillIcon->GetLength(); i++ )
			{
				SUIIconSet::SIconSet* pIcon = &pSkillIcon->m_vtIcon[i];
				if (pIcon->iconid == id)
					return pIcon;
			}
		}
	}
	return 0;
}

CUIXinFaConfig::CUIXinFaConfig()
{

}

CUIXinFaConfig::~CUIXinFaConfig()
{
	m_icons.Clear();
}

bool CUIXinFaConfig::LoadIconConfig(const char *fileName_)
{
	m_icons.Clear();

	MeXmlDocument doc;
	if (!doc.LoadFile(fileName_))
		return false;

	MeXmlElement *pElement = doc.FirstChildElement("Project");
	assert(pElement != NULL);

	pElement = pElement->FirstChildElement("Icons");
	assert(pElement != NULL);

	pElement = pElement->FirstChildElement("Icon");
	while (pElement)
	{
		SUIIconSet::SIconSet pt;

		int value = 0;
		pElement->QueryIntAttribute("id", &value);
		if(value > 0)
		{
			pt.iconid = value;

			pElement->QueryIntAttribute("index", &value);
			pt.index = value;

			const char* str = pElement->Attribute("Image");
			if( str )
				pt.image = str;

			pElement->QueryIntAttribute("IconSize", &value);
			pt.iconSize = value;

			pElement->QueryIntAttribute("Row", &value);
			pt.row = value;

			pElement->QueryIntAttribute("Column", &value);
			pt.column = value;

			m_icons.AddAllPos( pt );	
		}
	
		pElement = pElement->NextSiblingElement("Icon");
	}

	return true;
}

const SUIIconSet::SIconSet* CUIXinFaConfig::GetXinFaIconSet(int id)
{
	return m_icons.GetValue(id);
}