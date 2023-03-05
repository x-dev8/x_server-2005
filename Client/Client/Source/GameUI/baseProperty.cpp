/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\baseProperty.cpp
*********************************************************************/
#include <assert.h>
#include "MeTerrain/stdafx.h"
#include "MeUi/UiManager.h"
#include "baseProperty.h"
#include "Me3d/Engine/RendererDx.h"
#include "PropertyDlg.h"
#include "me3d/ShaderManager.h"
#include "Shop.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "GameMain.h"
#include "ui/UiTitle.h"
#include "ui/AreaExperience.h"
#include "Ui/Achieve.h"
#include "Ui/SelfInfo.h"
//#include "Pet.h"
#include "UiTitle.h"
#include "ui/Experience.h"
#include "Skill.h"
#include "CountryDefine.h"
#include "Suit.h"
#include "ShopCenter.h"
#include "exmain.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "color_config.h"
#include "InfoTips.h"
#include "GameDefinePlayer.h"
#include "CountryFunction.h"
#include "ScreenInfoManager.h"
#include "CommonChatFrame.h"
#include "MeUi/ControlObject.h"
#include "MainMenu.h"
#include "MeUi/Animation/XmlAnimation.h"
#include "ui/SelfInfo.h"
#include "ui/OtherInfo.h"
#include "BasePropertyBGFrame.h"
#include "PlayerRole.h"
#include "ItemHero.h"
#include <sstream>
#include "PlayerInfoMgr.h"
#include <map>
#include "SuAnimal.h"
#include "ManualLevelUp.h"
#include "StarLevelUpConfig.h"
#include "meui/ExpressionManager.h"

//#include "ShowPet.h"
extern CHeroGame* theApp;

static std::string g_strGuildNull;
static std::string g_strLoverNull;

static bool isShowProperty = true;
extern CHeroGame* theApp;
extern BOOL g_bMultiThreadLoadingMex;

#define MAX_HERO_SKILL_COUNT	3

void CUI_ID_FRAME_BaseProperty::UpdateBestEquipTip( int x, int y )
{
	int part = -1;
	for ( int idx = 0; idx < EEquipPartType_MaxEquitPart; ++idx )
	{
		if ( m_BestEquipPic[idx] 
			&& m_BestEquipPic[idx]->IsVisable() 
			&& m_BestEquipPic[idx]->PtInObject( x, y ) 
			)
		{
			part = idx;
			break;
		}
	}

	// 如果有进入part不会=-1，等于-1证明最佳装备的TIP就不会显示了
	if ( part != -1 )
	{
		//if ( mIconMgrBestEquip->GetFlag() == FLAG_HIDEING )
		{
			RECT rect;
			m_BestEquipPic[part]->GetRealRect( &rect );

			POINT pt;
			pt.x = rect.right;
			pt.y = rect.bottom;

			EArmType careerId = (EArmType)thePlayerRole.GetProfession();
			int level = thePlayerRole.GetLevel();

			mIconMgrBestEquip->SetRenderPt( pt );
			mIconMgrBestEquip->SetData( careerId, (EEquipPartType)part, level );
			mIconMgrBestEquip->SetVisable( true );
//			mIconMgrBestEquip->SetFlag( FLAG_SHOWING );
		}
	}
	else
	{
		//if ( mIconMgrBestEquip->GetFlag() == FLAG_SHOWING )
		{
			mIconMgrBestEquip->SetVisable( false );
//			mIconMgrBestEquip->SetFlag( FLAG_HIDEING );
		}
	}
}

void CUI_ID_FRAME_BaseProperty::UpdateIconInfo()
{
	POINT pos;
	RECT rect;
	GetCursorPos(&pos);
	GetWindowRect(g_hWnd, &rect);

	if(!theApp->IsFullScreen())
	{
		pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
		pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
	}

	POINT ptMouseOnSel;
	if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_rWeapon->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_rWeapon->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Weapon].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Weapon],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );

	}

	if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Weapon2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Weapon2->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_WeaponMinor].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_WeaponMinor],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );		
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Armour->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Armour->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Armour].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Armour],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Shoe->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Shoe->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Shoe].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Shoe],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Glove->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Glove->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Glove].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Glove],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Necklace->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Necklace->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Necklace].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Necklace],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Ring1->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Ring1->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Ring1].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Ring1],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Ring2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Ring2->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Ring2].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Ring2],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Bangle1->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Bangle1->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Bangle1].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Bangle1],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Bangle2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Bangle2->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Bangle2].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Bangle2],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Temp1->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Temp1->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Sash].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Sash],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Head->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Head->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Helmet].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Helmet],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Accouterment1->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Accouterment1->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_LeaderCard].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_LeaderCard],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Amulet->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Amulet->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Amulet].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Amulet],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_GangRing->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_GangRing->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Badge].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Badge],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_GangSkillBox->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_GangSkillBox->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_Shoulder].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_Shoulder],bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}

	else if ( s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Fashionarmour->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		eIconDrawState bIconEnable = eIcon_Disable;

		ControlIconDrag::S_ListImg *pItem = s_CUI_ID_FRAME_BaseProperty.m_pID_LISTIMG_Fashionarmour->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );

		if( thePlayerRole.m_pVisual->equipitem[EEquipPartType_AecorativeClothing].equipdata.usHP != 0 )
			bIconEnable = eIcon_Enable;

		pItem->SetData(&thePlayerRole.m_pVisual->equipitem[EEquipPartType_AecorativeClothing], bIconEnable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );
	}
}

CUI_ID_FRAME_BaseProperty s_CUI_ID_FRAME_BaseProperty;
MAP_FRAME_RUN( s_CUI_ID_FRAME_BaseProperty, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BaseProperty, OnFrameRender )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_BaseProperty, OnFrameRenderNeedRedraw )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ShiZhuangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ChenhaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_PetOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_PropertyOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_OnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ChengZhangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ShowHelmOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ShowFasionOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_AchieveOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_SelfInfoOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_LevelUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_SureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_ShuFaAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_ShuFaMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_TiZhiAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_TiZhiMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_MinJieAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_MinJieMinusOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_LiLiangAddOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_LiLiangMinusOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_QiTaOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ElementDownOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ElementUpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_BaseOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ShuXingOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ZiLiaoOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_ShengwangOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_OtherOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_FASHOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_CHECKBOX_TouKuiOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_SymbolOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_SymbolOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_SymbolOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_LISTIMG_SymbolOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_FASH2OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_HeroOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_NotHeroOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_BaseProperty, ID_BUTTON_OpenTitleOnButtonClick )
CUI_ID_FRAME_BaseProperty::CUI_ID_FRAME_BaseProperty()
{
	// Member
	m_pID_FRAME_BaseProperty = NULL;
// 	m_pID_PICTURE_DI2 = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_PICTURE_title = NULL;
	//m_pID_BUTTON_CLOSE = NULL;
	//m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_Fenge = NULL;
	//m_pID_PICTURE_char = NULL;
	m_pID_CHECKBOX_Zhuangbei = NULL;
	m_pID_CHECKBOX_ShiZhuang = NULL;
//	m_pID_CHECKBOX_Shengwang = NULL;
	m_pID_CHECKBOX_Chenhao = NULL;
	//m_pID_CHECKBOX_Pet = NULL;
	m_pID_LISTIMG_Symbol = NULL;
	m_pID_LISTIMG_Glove = NULL;
	m_pID_LISTIMG_Accouterment1 = NULL;
	m_pID_LISTIMG_Ring1 = NULL;
	m_pID_LISTIMG_Ring2 = NULL;
	m_pID_LISTIMG_Bangle1 = NULL;
	m_pID_LISTIMG_Bangle2 = NULL;
	m_pID_LISTIMG_Amulet = NULL;
	m_pID_LISTIMG_Head = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_LISTIMG_Temp1 = NULL;
//	m_pID_LISTIMG_Temp = NULL;
	m_pID_LISTIMG_Shoe = NULL;
	m_pID_LISTIMG_Necklace = NULL;
	m_pID_LISTIMG_rWeapon = NULL;
	m_pID_LISTIMG_Weapon2 = NULL;
	//m_pID_LISTIMG_Ring = NULL;
 	m_pID_BUTTON_FASH = NULL;
// 	m_pID_BUTTON_Pack = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	//m_pID_LISTIMG_Fashionhead = NULL;
	m_pID_LISTIMG_Fashionarmour = NULL;
// 	m_pID_LISTIMG_Fashionglove = NULL;
// 	m_pID_LISTIMG_Fashionshoe = NULL;
//	m_pID_TEXT_HuoLi = NULL;
	m_pID_TEXT_ZHuoLi = NULL;
	m_pID_TEXT_ZPK = NULL;
//	m_pID_TEXT_ZPeiOu = NULL;
// 	m_pID_TEXT_ZGongHui = NULL;
	m_pID_TEXT_PK = NULL;
	//m_pID_TEXT_PeiOu = NULL;
	m_pID_TEXT_GongHui = NULL;
	m_pID_CHECKBOX_ChengZhang = NULL;
	m_pID_TEXT_Country = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_TEXT_GongHui = NULL;
	m_pID_TEXT_Group = NULL;
	m_pID_TEXT_ExpCurrent = NULL;
	m_pID_TEXT_ExpLevelUp = NULL;
// 	m_pID_TEXT_ZGongXun = NULL;
// 	m_pID_TEXT_GongXun = NULL;
// 	m_pID_TEXT_ZMingWang = NULL;
// 	m_pID_TEXT_MingWang = NULL;
// 	m_pID_BUTTON_Title = NULL;
// 	m_pID_TEXT_BangGong = NULL;
// 	m_pID_TEXT_ZBangGong = NULL;
	m_pID_LISTIMG_GangRing = NULL;
	//m_pID_PICTURE_5907 = NULL;
	m_pID_LISTIMG_GangSkillBox = NULL;
	
	m_pID_CHECKBOX_ShowHelm = NULL;
	m_pID_CHECKBOX_ShowFasion = NULL;
	m_pID_CHECKBOX_Achieve = NULL;
	m_pID_CHECKBOX_SelfInfo = NULL;
	m_pID_PICTURE_Effect = NULL;
	m_pID_BUTTON_LevelUp = NULL;
    m_pID_PICTURE_FrameTitle1 = NULL;
    m_pID_PICTURE_FrameTitle2 = NULL;
    m_pID_PICTURE_FrameTitle3 = NULL;
    m_pID_PICTURE_FrameTitle4 = NULL;

	m_pID_TEXT_JinChengGongJi = NULL;
	m_pID_TEXT_MoFaGongJi = NULL;
	m_pID_TEXT_JinChengFangYu = NULL;
	m_pID_TEXT_MoFaFangYu = NULL;
	m_pID_TEXT_MingZhong = NULL;
	m_pID_TEXT_ShanBi = NULL;
	m_pID_TEXT_BaoJi = NULL;
	m_pID_TEXT_BaoJiKang = NULL;
	m_pID_TEXT_HP = NULL;
	m_pID_TEXT_MP = NULL;

	m_pID_TEXT_DaoHang = NULL;
	m_pID_TEXT_Jingli = NULL;
	m_pID_TEXT_Huoli = NULL;

	m_pID_TEXT_DianShu = NULL;
	m_pID_BUTTON_Sure = NULL;
	m_pID_TEXT_ShuFa = NULL;
	m_pID_BUTTON_ShuFaAdd = NULL;
	m_pID_BUTTON_ShuFaMinus = NULL;
	m_pID_TEXT_TiZhi = NULL;
	m_pID_BUTTON_TiZhiAdd = NULL;
	m_pID_BUTTON_TiZhiMinus = NULL;
	m_pID_TEXT_MinJie = NULL;
	m_pID_BUTTON_MinJieAdd = NULL;
	m_pID_BUTTON_MinJieMinus = NULL;
	m_pID_TEXT_LiLiang = NULL;
	m_pID_BUTTON_LiLiangAdd = NULL;
	m_pID_BUTTON_LiLiangMinus = NULL;

	m_pID_PROGRESS_Exp = NULL;

	m_pID_TEXT_BaoJiBei = NULL;
	m_pID_TEXT_BeiXi = NULL;
	m_pID_TEXT_BeiXiKang = NULL;
	m_pID_TEXT_YiDong = NULL;

	m_pID_PICTURE_Base = NULL;
	m_pID_PICTURE_Element = NULL;
	m_pID_PICTURE_Other = NULL;

	m_pID_CHECKBOX_QiTa = NULL;
	m_pID_CHECKBOX_ElementDown = NULL;
	m_pID_CHECKBOX_ElementUp = NULL;
	m_pID_CHECKBOX_Base = NULL;

	m_pID_PICTURE_State5 = NULL;
	m_pID_PICTURE_State4 = NULL;
	m_pID_PICTURE_State3 = NULL;
	m_pID_PICTURE_State2 = NULL;
	m_pID_PICTURE_State1 = NULL;
	m_pID_TEXT_State1_1 = NULL;
	m_pID_TEXT_State1_2 = NULL;
	m_pID_TEXT_State2_1 = NULL;
	m_pID_TEXT_State2_2 = NULL;
	m_pID_TEXT_State3_1 = NULL;
	m_pID_TEXT_State3_2 = NULL;
	m_pID_TEXT_State4_1 = NULL;
	m_pID_TEXT_State4_2 = NULL;
	m_pID_TEXT_State5_1 = NULL;
	m_pID_TEXT_State5_2 = NULL;

	//m_pID_CHECKBOX_ShuXing = NULL;
	m_pID_CHECKBOX_Shengwang = NULL;
// 	m_pID_CHECKBOX_ZiLiao = NULL;
// 	m_pID_CHECKBOX_Other = NULL;

	m_pID_TEXT_Exp = NULL;
	m_pID_PICTURE_ZhanShi = NULL;
	m_pID_PICTURE_CiKe = NULL;
	m_pID_PICTURE_YueShi = NULL;
	m_pID_PICTURE_TianShi = NULL;
	m_pID_PICTURE_NuShou = NULL;
	m_pID_CHECKBOX_TouKui = NULL;

	m_pID_PICTURE_Head1 = NULL;
	m_pID_PICTURE_Symbol1 = NULL;
	m_pID_PICTURE_Armour1 = NULL;
	m_pID_PICTURE_Glove1 = NULL;
	m_pID_PICTURE_Temp11 = NULL;
	m_pID_PICTURE_Shoe1 = NULL;
	m_pID_PICTURE_Necklace1 = NULL;
	m_pID_PICTURE_Ring11 = NULL;
	m_pID_PICTURE_Ring21 = NULL;
	m_pID_PICTURE_Fabao1 = NULL;

	m_pID_PICTURE_rWeapon1 = NULL;
	m_pID_PICTURE_fWeapon1 = NULL;

	m_pID_PICTURE_Fashion11 = NULL;
	m_pID_PICTURE_Fashion21 = NULL;
	m_pID_LISTIMG_Fashion1 = NULL;
	m_pID_LISTIMG_Fashion2 = NULL;

	m_pID_LISTIMG_Fabao = NULL;

	m_pID_TEXT_Level = NULL;
	m_pID_BUTTON_FASH = NULL;
	m_pID_BUTTON_FASH2 = NULL;

	m_pID_BUTTON_Hero = NULL;
	m_pID_BUTTON_NotHero = NULL;

	m_pID_PICTURE_Ring31 = NULL;
	m_pID_PICTURE_Ring41 = NULL;

	//主将属性相关
	m_pID_PICTURE_HeadPic = NULL;
	m_pID_PICTURE_AttrPic = NULL;
	m_pID_LISTIMG_HeroSkill = NULL;
	m_pID_PICTURE_WarPro = NULL;
	m_pID_TEXT_HeroInfo = NULL;
	m_pID_PICTURE_HidePic = NULL;

	m_pID_LISTIMG_fWeapon = NULL;
	mIconMgrBestEquip = NULL;
	m_pCoolDownAni = NULL;
	m_dwStartTime = 0;
	m_pID_BUTTON_OpenTitle = NULL;
	m_pID_PICTURE_WeiGuo = NULL;
	m_pID_PICTURE_ShuGuo = NULL;
	m_pID_PICTURE_WuGuo = NULL;

	m_pID_TEXT_SuitAttr = NULL;

	m_pID_TEXT_PetPoint = NULL;
	m_pID_TEXT_EquipScore = NULL;

	memset( m_BestEquipPic, 0, sizeof( m_BestEquipPic ) );

    Reset();
}

CUI_ID_FRAME_BaseProperty::~CUI_ID_FRAME_BaseProperty()
{
    //DestroyAnimCtrl();
}

//added by ZhuoMeng.Hu		[10/18/2010]
void CUI_ID_FRAME_BaseProperty::Reset()
{
    m_fRotateZ = 0;
    m_bRotate = false;
	RenderAnim_Destroy();
    m_bLvlupHasShown = false;
    PetAIType = 0;

    m_fLightTry1 = 0.6f;
    m_fLightTry2 = 1.0f;
    m_fLightTry3 = 1.0f;
}

// Frame
bool CUI_ID_FRAME_BaseProperty::OnFrameRun()
{
	if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		RenderAnim_RotateZ(true);
		//m_fRotateZ += 1.5f * theHeroGame.GetFrameElapsedTime();
	}
	else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		RenderAnim_RotateZ(false);
		//m_fRotateZ -= 1.5f * theHeroGame.GetFrameElapsedTime();
	}
	else
		m_bRotate = false;

	if(s_CUI_ID_FRAME_BaseProperty.IsVisable())
	{
		UpdateIconInfo();
		//UpdateBestEquipTip( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
	}
	return true;
}

extern bool g_RenderTips;
bool CUI_ID_FRAME_BaseProperty::OnFrameRender()
{
	
	if ( m_pID_FRAME_BaseProperty && g_RenderTips)
	{
		RECT rc;
		m_pID_FRAME_BaseProperty->GetRealRect(&rc);

		CViewportConfig *viewportCfg = GetSystemConfig()->GetPackViewportCfg();
		RenderAnim_Update(
			rc.left + viewportCfg->m_fX * ControlObject::GetSCALE(m_pID_FRAME_BaseProperty),
			rc.top + viewportCfg->m_fY * ControlObject::GetSCALE(m_pID_FRAME_BaseProperty),
			viewportCfg->m_fWidth * ControlObject::GetSCALE(m_pID_FRAME_BaseProperty),
			viewportCfg->m_fHeight * ControlObject::GetSCALE(m_pID_FRAME_BaseProperty),
			D3DXVECTOR3(0, -11, 0));

		float scale = 0.0;
		if (theHeroGame.GetPlayerMgr()->GetMe()->GetSex() == Sex_Male)
			scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleMale;
		else
			scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleFemale;
		RenderAnim(D3DXVECTOR3(0, 0, -2.5136), scale);
	}

	return true;
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_PetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//if(!m_pID_FRAME_BaseProperty)
	//{
	//	assert(false&&"ui error");
	//	return ;
	//}

	//m_EquipGroup.SetVisible(false);
	//s_CUI_ID_FRAME_AreaExperience.SetVisable( false );	
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(false);
	//s_CUI_ID_FRAME_Title.SetVisable(false);
	//s_CUI_ID_FRAME_Achieve.SetVisable(false);
	//s_CUI_ID_FRAME_SelfInfo.SetVisable(false);

	//m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	////m_pID_CHECKBOX_Shengwang->SetCheck(false);
	//m_pID_CHECKBOX_Chenhao->SetCheck(false);
	////m_pID_CHECKBOX_Pet->SetCheck(true);
	//m_pID_CHECKBOX_ChengZhang->SetCheck( false );
	//m_pID_CHECKBOX_Achieve->SetCheck(false);
	//m_pID_CHECKBOX_SelfInfo->SetCheck(false);
}

//---------------------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return ;
	}

	m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
	m_pID_CHECKBOX_ShiZhuang->SetCheck(false);
	if (m_pID_PICTURE_Fashionarmour)
	{
		m_pID_PICTURE_Fashionarmour->SetVisable(false);
	}
	m_EquipItemGroup.SetVisible(true);
	m_FashGroup.SetVisible(false);
	/*s_CUI_ID_FRAME_AreaExperience.SetVisable( false );
	m_pID_CHECKBOX_Pet->SetCheck(false);
	m_pID_CHECKBOX_Shengwang->SetCheck(false);
	m_pID_CHECKBOX_ChengZhang->SetCheck( false );*/
	
	m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(true);
	
	m_pID_CHECKBOX_Chenhao->SetCheck(false);
	s_CUI_ID_FRAME_Title.SetVisable(false);
	
	m_pID_CHECKBOX_Achieve->SetCheck(false);
	s_CUI_ID_FRAME_Achieve.SetVisable(false);
	
	m_pID_CHECKBOX_SelfInfo->SetCheck(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);

    m_pID_PICTURE_FrameTitle1->SetVisable( true );
    m_pID_PICTURE_FrameTitle2->SetVisable( false );
    m_pID_PICTURE_FrameTitle3->SetVisable( false );
    m_pID_PICTURE_FrameTitle4->SetVisable( false );
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ShiZhuangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	m_pID_CHECKBOX_ShiZhuang->SetCheck(true);
	m_EquipItemGroup.SetVisible(false);
	m_FashGroup.SetVisible(true);
	if (m_pID_PICTURE_Fashionarmour)
	{
		m_pID_PICTURE_Fashionarmour->SetVisable(true);
	}
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ChenhaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return ;
	}

	/*s_CUI_ID_FRAME_AreaExperience.SetVisable( false );
	m_pID_CHECKBOX_Pet->SetCheck(false);
	m_pID_CHECKBOX_Shengwang->SetCheck(false);
	m_pID_CHECKBOX_ChengZhang->SetCheck( false );*/

	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(false);

	m_pID_CHECKBOX_Chenhao->SetCheck(true);
	s_CUI_ID_FRAME_Title.SetVisable(true);

	m_pID_CHECKBOX_Achieve->SetCheck(false);
	s_CUI_ID_FRAME_Achieve.SetVisable(false);

	m_pID_CHECKBOX_SelfInfo->SetCheck(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);

    m_pID_PICTURE_FrameTitle1->SetVisable( false );
    m_pID_PICTURE_FrameTitle2->SetVisable( false );
    m_pID_PICTURE_FrameTitle3->SetVisable( true );
    m_pID_PICTURE_FrameTitle4->SetVisable( false );
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_AchieveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return ;
	}

	/*s_CUI_ID_FRAME_AreaExperience.SetVisable( false );
	m_pID_CHECKBOX_Pet->SetCheck(false);
	m_pID_CHECKBOX_Shengwang->SetCheck(false);
	m_pID_CHECKBOX_ChengZhang->SetCheck( false );*/

	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(false);

	m_pID_CHECKBOX_Chenhao->SetCheck(false);
	s_CUI_ID_FRAME_Title.SetVisable(false);

	m_pID_CHECKBOX_Achieve->SetCheck(true);
	s_CUI_ID_FRAME_Achieve.SetVisable(true);

	m_pID_CHECKBOX_SelfInfo->SetCheck(false);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(false);

    m_pID_PICTURE_FrameTitle1->SetVisable( false );
    m_pID_PICTURE_FrameTitle2->SetVisable( false );
    m_pID_PICTURE_FrameTitle3->SetVisable( false );
    m_pID_PICTURE_FrameTitle4->SetVisable( true );
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_SelfInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return ;
	}

	/*s_CUI_ID_FRAME_AreaExperience.SetVisable( false );
	m_pID_CHECKBOX_Pet->SetCheck(false);
	m_pID_CHECKBOX_Shengwang->SetCheck(false);
	m_pID_CHECKBOX_ChengZhang->SetCheck( false );*/

	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(false);

	m_pID_CHECKBOX_Chenhao->SetCheck(false);
	s_CUI_ID_FRAME_Title.SetVisable(false);

	m_pID_CHECKBOX_Achieve->SetCheck(false);
	s_CUI_ID_FRAME_Achieve.SetVisable(false);

	m_pID_CHECKBOX_SelfInfo->SetCheck(true);
	s_CUI_ID_FRAME_SelfInfo.SetVisable(true);

    m_pID_PICTURE_FrameTitle1->SetVisable( false );
    m_pID_PICTURE_FrameTitle2->SetVisable( true );
    m_pID_PICTURE_FrameTitle3->SetVisable( false );
    m_pID_PICTURE_FrameTitle4->SetVisable( false );
}

//----------------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ChengZhangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return ;
	}

	s_CUI_ID_FRAME_AreaExperience.SetVisable( false );
	
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(false);

	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	//m_pID_CHECKBOX_Shengwang->SetCheck(false);
	m_pID_CHECKBOX_Chenhao->SetCheck(false);
	//m_pID_CHECKBOX_Pet->SetCheck( false );
	m_pID_CHECKBOX_ChengZhang->SetCheck( true );
}

bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	m_bRotate = false;
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	m_bRotate = false;
	return true;
}

bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_PropertyOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return false;
	}

	isShowProperty = !isShowProperty;
	//s_CUI_ID_FRAME_PropertyDlg.SetVisable(!s_CUI_ID_FRAME_PropertyDlg.IsVisable());
	//if (s_CUI_ID_FRAME_PropertyDlg.IsVisable())
	//	s_CUI_ID_FRAME_ShowPet.SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return false;
	}

	s_CUI_ID_FRAME_PACK.Equip(pSender,
		pMe, pItemDrag, pItemSrc);
	return false;
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return false;
	}

	return Repair(pItem);
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
		return false;
	}

	if (!pItem)
		return true;

	int index = -1;
	if( s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag) )
		index = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag)->GetNullItem();
	if (index == -1 || index >= thePlayerRole.m_bag.GetNowBagSize())
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
		return true;
	}
	s_CUI_ID_FRAME_PACK.dropIconFromEquip(index, pItem);
	return true;
}

void CUI_ID_FRAME_BaseProperty::InitializeAtEnterWorld()
{
    if (s_CUI_ID_FRAME_AreaExperience.IsExistFrameAreaExperience())
    {
        s_CUI_ID_FRAME_AreaExperience.SetFrameAreaExperienceFather( m_pID_FRAME_BaseProperty );
    }

    Reset();
	RenderAnim_Create(CUIRenderAnim::RTWUI_CHARACTER_PROPERTY);

    int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
    if (RenderAnim_GetPlayer() != NULL && nIndex >= 0)
    {
        RenderAnim_GetPlayer()->SetCharEffectContainer(GetEffectMgr()->GetCharEffectContainer(nIndex));
    }

    InitCamera();

    if( !m_pID_FRAME_BaseProperty )
        return;

    m_pID_LISTIMG_Ring2->SetEnableCompare( false );
    m_pID_LISTIMG_Bangle1->SetEnableCompare( false );
    m_pID_LISTIMG_Bangle2->SetEnableCompare( false );
    m_pID_LISTIMG_Weapon2->SetEnableCompare( false );

    m_pID_LISTIMG_Glove->SetEnableCompare( false );
    m_pID_LISTIMG_Accouterment1->SetEnableCompare( false );
    m_pID_LISTIMG_Ring1->SetEnableCompare( false );
    m_pID_LISTIMG_Head->SetEnableCompare( false );
    m_pID_LISTIMG_Armour->SetEnableCompare( false );
    m_pID_LISTIMG_Temp1->SetEnableCompare( false );
    //m_pID_LISTIMG_Temp->SetEnableCompare( false );
    m_pID_LISTIMG_Shoe->SetEnableCompare( false );
    m_pID_LISTIMG_Necklace->SetEnableCompare( false );
    m_pID_LISTIMG_rWeapon->SetEnableCompare( false );
    //m_pID_LISTIMG_Ring->SetEnableCompare( false );
    //m_pID_LISTIMG_Fashionhead->SetEnableCompare( false );
    m_pID_LISTIMG_Fashionarmour->SetEnableCompare( false );
    //m_pID_LISTIMG_Fashionglove->SetEnableCompare( false );
    //m_pID_LISTIMG_Fashionshoe->SetEnableCompare( false );
    m_pID_LISTIMG_GangRing->SetEnableCompare( false );
    m_pID_LISTIMG_GangSkillBox->SetEnableCompare( false );

    for (int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
        m_pEquipListImg[i] = NULL;

    //for ( int i=0; i<FPT_Count; i++ )
    //	m_pFashionEquipListImg[i] = NULL;

    m_pEquipListImg[EEquipPartType_Weapon] = m_pID_LISTIMG_rWeapon;
    m_pEquipListImg[EEquipPartType_WeaponMinor] = m_pID_LISTIMG_Weapon2;
    m_pEquipListImg[EEquipPartType_Armour] = m_pID_LISTIMG_Armour;
    m_pEquipListImg[EEquipPartType_Shoe] = m_pID_LISTIMG_Shoe;
    m_pEquipListImg[EEquipPartType_Glove] = m_pID_LISTIMG_Glove;
    m_pEquipListImg[EEquipPartType_Necklace] = m_pID_LISTIMG_Necklace;
    m_pEquipListImg[EEquipPartType_Ring1] = m_pID_LISTIMG_Ring1;
    m_pEquipListImg[EEquipPartType_Ring2] = m_pID_LISTIMG_Ring2;
    m_pEquipListImg[EEquipPartType_Bangle1] = m_pID_LISTIMG_Bangle1;
    m_pEquipListImg[EEquipPartType_Bangle2] = m_pID_LISTIMG_Bangle2;
    m_pEquipListImg[EEquipPartType_Sash] = m_pID_LISTIMG_Temp1;
    m_pEquipListImg[EEquipPartType_Helmet] = m_pID_LISTIMG_Head;
    m_pEquipListImg[EEquipPartType_LeaderCard] = m_pID_LISTIMG_Accouterment1;
    m_pEquipListImg[EEquipPartType_Badge] = m_pID_LISTIMG_GangRing;
    m_pEquipListImg[EEquipPartType_Amulet] = m_pID_LISTIMG_Amulet;
    m_pEquipListImg[EEquipPartType_Shoulder] = m_pID_LISTIMG_GangSkillBox;			

    m_pEquipListImg[EEquipPartType_AecorativeClothing] = m_pID_LISTIMG_Fashionarmour;

    for( int i=0; i < EEquipPartType_MaxEquitPart; i++ )
    {
        if (m_pEquipListImg[i])
        {
            m_pEquipListImg[i]->ShowPressEffect(true);

            theUiManager.OnIconDragOn( ID_FRAME_BaseProperty, m_pEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_OnIconDragOn );
            theUiManager.OnIconLDBClick( ID_FRAME_BaseProperty, m_pEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_OnIconLDBClick );
            theUiManager.OnIconButtonClick( ID_FRAME_BaseProperty, m_pEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_OnIconButtonClick );
            theUiManager.OnIconRButtonUp( ID_FRAME_BaseProperty, m_pEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_OnIconRButtonUp );
        }
    }

    /*for( int i=0; i<FPT_Count; i++ )
    {
    if (m_pFashionEquipListImg[i])
    {
    m_pFashionEquipListImg[i]->ShowPressEffect(true);

    theUiManager.OnIconDragOn( ID_FRAME_BaseProperty, m_pFashionEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_FashionOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_BaseProperty, m_pFashionEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_FashionOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_BaseProperty, m_pFashionEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_FashionOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_BaseProperty, m_pFashionEquipListImg[i]->GetData()->m_szID, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_FashionOnIconRButtonUp );
    }
    }*/

    m_pID_LISTIMG_Head->SetDisableCanbePick(true);
    m_pID_LISTIMG_Head->ShowPressEffect(true);
    m_pID_LISTIMG_Armour->SetDisableCanbePick(true);
    m_pID_LISTIMG_Armour->ShowPressEffect(true);
    m_pID_LISTIMG_Glove->SetDisableCanbePick(true);
    m_pID_LISTIMG_Glove->ShowPressEffect(true);
    m_pID_LISTIMG_Shoe->SetDisableCanbePick(true);
    m_pID_LISTIMG_Shoe->ShowPressEffect(true);
    m_pID_LISTIMG_Ring1->SetDisableCanbePick(true);
    m_pID_LISTIMG_Ring1->ShowPressEffect(true);
    m_pID_LISTIMG_Ring2->SetDisableCanbePick(true);
    m_pID_LISTIMG_Ring2->ShowPressEffect(true);
    m_pID_LISTIMG_Bangle1->SetDisableCanbePick(true);
    m_pID_LISTIMG_Bangle1->ShowPressEffect(true);
    m_pID_LISTIMG_Bangle2->SetDisableCanbePick(true);
    m_pID_LISTIMG_Bangle2->ShowPressEffect(true);
    m_pID_LISTIMG_Amulet->SetDisableCanbePick(true);
    m_pID_LISTIMG_Amulet->ShowPressEffect(true);
    m_pID_LISTIMG_rWeapon->SetDisableCanbePick(true);
    m_pID_LISTIMG_rWeapon->ShowPressEffect(true);
    m_pID_LISTIMG_Weapon2->SetDisableCanbePick(true);
    m_pID_LISTIMG_Weapon2->ShowPressEffect(true);
    m_pID_LISTIMG_Necklace->SetDisableCanbePick(true);
    m_pID_LISTIMG_Necklace->ShowPressEffect(true);
    m_pID_LISTIMG_Temp1->SetDisableCanbePick(true);
    m_pID_LISTIMG_Temp1->ShowPressEffect(true);
    m_pID_LISTIMG_Accouterment1->SetDisableCanbePick(true);
    m_pID_LISTIMG_Accouterment1->ShowPressEffect(true);
    m_pID_LISTIMG_GangRing->SetDisableCanbePick(true);
    m_pID_LISTIMG_GangRing->ShowPressEffect(true);
    m_pID_LISTIMG_GangSkillBox->SetDisableCanbePick(true);
    m_pID_LISTIMG_GangSkillBox->ShowPressEffect(true);

    m_pID_LISTIMG_Fashionarmour->SetDisableCanbePick(true);
    m_pID_LISTIMG_Fashionarmour->ShowPressEffect(true);

    //m_pID_FRAME_BaseProperty->SetOnVisibleChangedFun(OnVisibleChanged);

    m_pID_BUTTON_Right->SetLButtonDownFun(UIBaseProperty_RightLBD);
    m_pID_BUTTON_Left->SetLButtonDownFun(UIBaseProperty_LeftLBD);
    
    m_pID_BUTTON_LevelUp->SetEnable( false );

    g_strGuildNull = m_pID_TEXT_GongHui->GetText();
    //	g_strLoverNull = m_pID_TEXT_PeiOu->GetText();
    // 	s_CUI_ID_FRAME_PropertyDlg.SetFrameFather(m_pID_FRAME_BaseProperty);
    // 
    // 	if( s_CUI_ID_FRAME_Title.GetFrame() )
    // 		s_CUI_ID_FRAME_Title.GetFrame()->SetFather(m_pID_FRAME_BaseProperty);
    // 
    // 	if( s_CUI_ID_FRAME_SelfInfo.GetFrame() )
    // 		s_CUI_ID_FRAME_SelfInfo.GetFrame()->SetFather(m_pID_FRAME_BaseProperty);
    // 
    // 	if( s_CUI_ID_FRAME_Achieve.GetFrame() )
    // 		s_CUI_ID_FRAME_Achieve.GetFrame()->SetFather(m_pID_FRAME_BaseProperty);

    _SetVisable( false );

	// 防止下次进游戏的时候，标记有问题
	mIconMgrBestEquip->SetFlag( FLAG_HIDEING );
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_SureOnButtonClick( ControlObject* pSender )
{
	if(thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential) <= 0)
		return true;

	MsgCharAssignPotential msg;
	for (int i = 0;i < (int)EBaseAttr_MaxSize;++i)
		msg.nValue[i] = m_nValue[i];

	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_ShuFaAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Intelligence];  
		Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_ShuFaMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Intelligence] > 0)
	{
		--m_nValue[EBaseAttr_Intelligence];  
		Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_TiZhiAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Stamina];  
		Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_TiZhiMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Stamina] > 0)
	{
		--m_nValue[EBaseAttr_Stamina];  
		Refresh();
	}
	return true;
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_MinJieAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Agility];  
		Refresh();
	}
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_MinJieMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Agility] > 0)
	{
		--m_nValue[EBaseAttr_Agility];
		Refresh();
	}

	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_LiLiangAddOnButtonClick( ControlObject* pSender )
{
	if(GetNoUseSkillPoint() > 0)
	{
		++m_nValue[EBaseAttr_Strength];  
		Refresh();
	}

	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_LiLiangMinusOnButtonClick( ControlObject* pSender )
{
	if(m_nValue[EBaseAttr_Strength] >0)
	{
		--m_nValue[EBaseAttr_Strength];
		Refresh();
	}

	return true;
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_QiTaOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_OtherGroup.IsVisible())
		return;
	m_BaseGroup.SetVisible(false);
	m_ElementGroup.SetVisible(false);
	m_OtherGroup.SetVisible(true);
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ElementDownOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_ElementGroup.IsVisible())
		return;

	m_BaseGroup.SetVisible(false);
	m_ElementGroup.SetVisible(true);
	m_OtherGroup.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ElementUpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_ElementGroup.IsVisible())
		return;

	m_BaseGroup.SetVisible(false);
	m_ElementGroup.SetVisible(true);
	m_OtherGroup.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_BaseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(m_BaseGroup.IsVisible())
		return;
	m_BaseGroup.SetVisible(true);
	m_ElementGroup.SetVisible(false);
	m_OtherGroup.SetVisible(false);
}

// CheckBox
void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ShengwangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{

}

// CheckBox
// void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ShuXingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	//m_pID_CHECKBOX_ShuXing->SetCheck(true);
// }

// CheckBox
// void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ZiLiaoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	m_BaseGroup.SetVisible(false);
// 	m_ElementGroup.SetVisible(false);
// 	m_OtherGroup.SetVisible(false);
// 	m_EquipItemGroup.SetVisible(false);
// 	m_FashGroup.SetVisible(false);
// 	s_CUI_ID_FRAME_SelfInfo.SetVisable(*pbChecked);
// 	//s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
// }

// CheckBox
// void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_OtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	s_CUI_ID_FRAME_OtherInfo.SetVisable(*pbChecked);
// 	//s_CUI_ID_FRAME_BaseProperty.SetVisable(false);
// }

bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_FASHOnButtonClick( ControlObject* pSender )
{
	m_pID_BUTTON_FASH->SetVisable(false);
	m_pID_BUTTON_FASH2->SetVisable(true);

	MsgSwitchSuit msg;
	msg.nSuitIndex = 1;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_TouKuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;

	pMe->ShowHelmetAndSendMsg(*pbChecked);

	BOOL bMultiThreadLoadingMex = g_bMultiThreadLoadingMex;
	if( IsVisable() )
	{
		g_bMultiThreadLoadingMex = FALSE;
	}

	RefreshEquip();
	pMe->ChangeSkeletonAndEquipAllItem(pMe->HasFightFlag(eFighting));

	if( IsVisable() )
	{
		g_bMultiThreadLoadingMex = bMultiThreadLoadingMex;
	}
}


// ListImg / ListEx
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_SymbolOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_SymbolOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_SymbolOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_BaseProperty::ID_LISTIMG_SymbolOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_FASH2OnButtonClick( ControlObject* pSender )
{
	m_pID_BUTTON_FASH2->SetVisable(false);
	m_pID_BUTTON_FASH->SetVisable(true);

	MsgSwitchSuit msg;
	msg.nSuitIndex = 0;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}
// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_HeroOnButtonClick( ControlObject* pSender )
{
	m_pID_BUTTON_Hero->SetVisable(false);
	m_pID_BUTTON_NotHero->SetVisable(true);

	MsgShowHeroSuit msg;
	msg.flag = MsgShowHeroSuit::eHeroSuitFlag::eHeroSuitFlag_show;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_NotHeroOnButtonClick( ControlObject* pSender )
{
	m_pID_BUTTON_Hero->SetVisable(true);
	m_pID_BUTTON_NotHero->SetVisable(false);
	MsgShowHeroSuit msg;
	msg.flag = MsgShowHeroSuit::eHeroSuitFlag::eHeroSuitFlag_notshow;
	GettheNetworkInput().SendMsg(&msg);
	return true;
}

// Button
bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_OpenTitleOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_Title.SetVisable(!s_CUI_ID_FRAME_Title.IsVisable());
	return true;
}

// 装载UI
bool CUI_ID_FRAME_BaseProperty::_LoadUI()
{
	//s_CUI_ID_FRAME_Pet.LoadUI();
// 	s_CUI_ID_FRAME_Experience.LoadUI();
	s_CUI_ID_FRAME_Title.LoadUI();
	s_CUI_ID_FRAME_Achieve.LoadUI();
	//s_CUI_ID_FRAME_SelfInfo.LoadUI();

	//s_CUI_ID_FRAME_PropertyDlg.LoadUI();
	s_CUI_ID_FRAME_AreaExperience.LoadUI();
	//s_CUI_ID_FRAME_Title.LoadUI();
	//s_CUI_ID_FRAME_ShowPet.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\baseProperty.MEUI",false,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\baseProperty.MEUI]失败")
			return false;
	}
// 	else if ( dwResult != 1/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\baseProperty.MEUI]与源代码版本不一样")
// 	}
	return DoControlConnect();
}

bool CUI_ID_FRAME_BaseProperty::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_BaseProperty, s_CUI_ID_FRAME_BasePropertyOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_BaseProperty, s_CUI_ID_FRAME_BasePropertyOnFrameRender );
	
	//theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_BasePropertyID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Zhuangbei, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ZhuangbeiOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ShiZhuang, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ShiZhuangOnCheckBoxCheck );	
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Chenhao, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ChenhaoOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Pet, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_PetOnCheckBoxCheck );
	
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_Right, s_CUI_ID_FRAME_BasePropertyID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_Left, s_CUI_ID_FRAME_BasePropertyID_BUTTON_LeftOnButtonClick );
	
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_Property, s_CUI_ID_FRAME_BasePropertyID_BUTTON_PropertyOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ChengZhang, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ChengZhangOnCheckBoxCheck );

	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ShowHelm, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ShowHelmOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ShowFasion, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ShowFasionOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Achieve, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_AchieveOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_SelfInfo, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_SelfInfoOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_LevelUp, s_CUI_ID_FRAME_BasePropertyID_BUTTON_LevelUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_Sure, s_CUI_ID_FRAME_BasePropertyID_BUTTON_SureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_ShuFaAdd, s_CUI_ID_FRAME_BasePropertyID_BUTTON_ShuFaAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_ShuFaMinus, s_CUI_ID_FRAME_BasePropertyID_BUTTON_ShuFaMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_TiZhiAdd, s_CUI_ID_FRAME_BasePropertyID_BUTTON_TiZhiAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_TiZhiMinus, s_CUI_ID_FRAME_BasePropertyID_BUTTON_TiZhiMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_MinJieAdd, s_CUI_ID_FRAME_BasePropertyID_BUTTON_MinJieAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_MinJieMinus, s_CUI_ID_FRAME_BasePropertyID_BUTTON_MinJieMinusOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_LiLiangAdd, s_CUI_ID_FRAME_BasePropertyID_BUTTON_LiLiangAddOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_LiLiangMinus, s_CUI_ID_FRAME_BasePropertyID_BUTTON_LiLiangMinusOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_QiTa, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_QiTaOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ElementDown, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ElementDownOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ElementUp, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ElementUpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Base, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_BaseOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_FASH, s_CUI_ID_FRAME_BasePropertyID_BUTTON_FASHOnButtonClick );
    theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_TouKui, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_TouKuiOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_BaseProperty, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_SymbolOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_BaseProperty, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_SymbolOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_BaseProperty, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_SymbolOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_BaseProperty, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_BasePropertyID_LISTIMG_SymbolOnIconRButtonUp );
    //theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ShuXing, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ShuXingOnCheckBoxCheck );
    //theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_ZiLiao, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ZiLiaoOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Shengwang, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_ShengwangOnCheckBoxCheck );
    //theUiManager.OnCheckBoxCheck( ID_FRAME_BaseProperty, ID_CHECKBOX_Other, s_CUI_ID_FRAME_BasePropertyID_CHECKBOX_OtherOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_FASH2, s_CUI_ID_FRAME_BasePropertyID_BUTTON_FASH2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_Hero, s_CUI_ID_FRAME_BasePropertyID_BUTTON_HeroOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_NotHero, s_CUI_ID_FRAME_BasePropertyID_BUTTON_NotHeroOnButtonClick);
	theUiManager.OnButtonClick( ID_FRAME_BaseProperty, ID_BUTTON_OpenTitle, s_CUI_ID_FRAME_BasePropertyID_BUTTON_OpenTitleOnButtonClick);

	m_pID_FRAME_BaseProperty = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_BaseProperty );
    m_pID_PICTURE_BaseBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_BaseBg );
    m_pID_PICTURE_EquipBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_EquipBg );
    //m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_CLOSE );
    m_pID_PICTURE_Fenge = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Fenge );
    m_pID_PICTURE_BgLine = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_BgLine );
    m_pID_CHECKBOX_Zhuangbei = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Zhuangbei );
	m_pID_CHECKBOX_ShiZhuang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ShiZhuang );
	m_pID_CHECKBOX_Chenhao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Chenhao );
    //m_pID_CHECKBOX_Pet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Pet );
    m_pID_LISTIMG_Glove = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Glove );	
    m_pID_LISTIMG_Accouterment1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Accouterment1 );
	m_pID_LISTIMG_Ring1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Ring1 );
	m_pID_LISTIMG_Ring2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Ring2);
	m_pID_LISTIMG_Bangle1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Bangle1);
	
	m_pID_LISTIMG_Bangle2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Bangle2);
	m_pID_LISTIMG_Head = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Head );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Armour );
	m_pID_LISTIMG_Temp1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Temp1 );
	m_pID_LISTIMG_Shoe = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Shoe );
	m_pID_LISTIMG_Amulet = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Amulet);
	m_pID_LISTIMG_Necklace = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Necklace );
	m_pID_LISTIMG_rWeapon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_rWeapon );
	m_pID_LISTIMG_Fabao = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Fabao );

	m_pID_LISTIMG_Weapon2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Weapon2);
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_Left );
	m_pID_LISTIMG_Fashionarmour = (ControlListImage*)theUiManager.FindControl(ID_FRAME_BaseProperty, ID_LISTIMG_Fashionarmour);
	m_pID_TEXT_ZHuoLi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ZHuoLi );
	m_pID_TEXT_ZPK = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ZPK );
// 	m_pID_TEXT_ZGongHui = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ZGongHui );
	m_pID_TEXT_PK = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_PK );
	m_pID_TEXT_GongHui = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_GongHui );
	m_pID_CHECKBOX_ChengZhang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ChengZhang );
	m_pID_LISTIMG_GangRing = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_GangRing );
	m_pID_LISTIMG_GangSkillBox = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_GangSkillBox );	
	m_pID_CHECKBOX_ShowHelm = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ShowHelm );
	m_pID_CHECKBOX_ShowFasion = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ShowFasion );
	m_pID_CHECKBOX_Achieve = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Achieve );
	m_pID_CHECKBOX_SelfInfo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_SelfInfo );
	m_pID_BUTTON_LevelUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_LevelUp );

	m_pID_TEXT_Country = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Country);
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Title);
	m_pID_TEXT_GongHui = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_GongHui);
	m_pID_TEXT_Group = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Group);
	m_pID_TEXT_ExpCurrent = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ExpCurrent);
	m_pID_TEXT_ExpLevelUp = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ExpLevelUp);
		
    m_pID_PICTURE_FrameTitle1 = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_FrameTitle1 );
    m_pID_PICTURE_FrameTitle2 = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_FrameTitle2 );
    m_pID_PICTURE_FrameTitle3 = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_FrameTitle3 );
    m_pID_PICTURE_FrameTitle4 = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_FrameTitle4 );

	m_pID_TEXT_JinChengGongJi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_JinChengGongJi );
	m_pID_TEXT_MoFaGongJi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_MoFaGongJi );
	m_pID_TEXT_JinChengFangYu = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_JinChengFangYu );
	m_pID_TEXT_MoFaFangYu = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_MoFaFangYu );
	m_pID_TEXT_MingZhong = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_MingZhong );
	m_pID_TEXT_ShanBi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ShanBi );
	m_pID_TEXT_BaoJi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_BaoJi );
	m_pID_TEXT_BaoJiKang = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_BaoJiKang );
	m_pID_TEXT_HP = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_HP );
	m_pID_TEXT_MP = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_MP );
	m_pID_TEXT_DaoHang = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_DaoHang );
	m_pID_TEXT_Jingli = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Jingli );
	m_pID_TEXT_Huoli = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Huoli );

	m_pID_TEXT_DianShu = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_DianShu );
	m_pID_BUTTON_Sure = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_Sure );
	m_pID_TEXT_ShuFa = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_ShuFa );
	m_pID_BUTTON_ShuFaAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_ShuFaAdd );
	m_pID_BUTTON_ShuFaMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_ShuFaMinus );
	m_pID_TEXT_TiZhi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_TiZhi );
	m_pID_BUTTON_TiZhiAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_TiZhiAdd );
	m_pID_BUTTON_TiZhiMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_TiZhiMinus );
	m_pID_TEXT_MinJie = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_MinJie );
	m_pID_BUTTON_MinJieAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_MinJieAdd );
	m_pID_BUTTON_MinJieMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_MinJieMinus );
	m_pID_TEXT_LiLiang = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_LiLiang );
	m_pID_BUTTON_LiLiangAdd = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_LiLiangAdd );
	m_pID_BUTTON_LiLiangMinus = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_LiLiangMinus );

	m_pID_PROGRESS_Exp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PROGRESS_Exp );

	m_pID_TEXT_BaoJiBei = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_BaoJiBei );
	m_pID_TEXT_BeiXi = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_BeiXi );
	m_pID_TEXT_BeiXiKang = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_BeiXiKang );
	m_pID_TEXT_YiDong = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_YiDong );

	m_pID_PICTURE_Effect = ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Effect );

	m_pID_PICTURE_Base = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Base );
	m_pID_PICTURE_Element = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Element );
	m_pID_PICTURE_Other = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Other );

	m_pID_CHECKBOX_QiTa = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_QiTa );
	m_pID_CHECKBOX_ElementDown = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ElementDown );
	m_pID_CHECKBOX_ElementUp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ElementUp );
	m_pID_CHECKBOX_Base = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Base );

	m_pID_PICTURE_State5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_State5 );
	m_pID_PICTURE_State4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_State4 );
	m_pID_PICTURE_State3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_State3 );
	m_pID_PICTURE_State2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_State2 );
	m_pID_PICTURE_State1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_State1 );
	m_pID_TEXT_State1_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State1_1 );
	m_pID_TEXT_State1_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State1_2 );
	m_pID_TEXT_State2_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State2_1 );
	m_pID_TEXT_State2_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State2_2 );
	m_pID_TEXT_State3_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State3_1 );
	m_pID_TEXT_State3_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State3_2 );
	m_pID_TEXT_State4_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State4_1 );
	m_pID_TEXT_State4_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State4_2 );
	m_pID_TEXT_State5_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State5_1 );
	m_pID_TEXT_State5_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_State5_2 );

	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Exp );
	m_pID_PICTURE_ZhanShi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_ZhanShi );
	m_pID_PICTURE_CiKe = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_CiKe );
	m_pID_PICTURE_YueShi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_YueShi );
	m_pID_PICTURE_TianShi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_TianShi );
	m_pID_PICTURE_NuShou = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_NuShou );

	m_pID_BUTTON_FASH = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_FASH );
	m_pID_CHECKBOX_TouKui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_TouKui );

	m_pID_PICTURE_Head1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Head1 );
	m_pID_PICTURE_Symbol1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Symbol1 );
	m_pID_PICTURE_Armour1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Armour1 );
	m_pID_PICTURE_Glove1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Glove1 );
	m_pID_PICTURE_Temp11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Temp11 );
	m_pID_PICTURE_Shoe1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Shoe1 );
	m_pID_PICTURE_Necklace1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Necklace1 );
	m_pID_PICTURE_Ring11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring11 );
	m_pID_PICTURE_Ring21 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring21 );
	m_pID_PICTURE_Fabao1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Fabao1 );

	m_pID_LISTIMG_fWeapon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_fWeapon );
	m_pID_PICTURE_fWeapon1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_fWeapon1 );
	m_pID_PICTURE_rWeapon1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_rWeapon1 );

	m_pID_PICTURE_Fashion11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Fashion11 );
	m_pID_PICTURE_Fashion21 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Fashion21 );
	m_pID_PICTURE_Fashionarmour = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Fashionarmour );
	m_pID_LISTIMG_Fashion1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Fashion1 );
	m_pID_LISTIMG_Fashion2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Fashion2 );

	m_pID_LISTIMG_Symbol = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_Symbol );

	//m_pID_CHECKBOX_ShuXing = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ShuXing );
	m_pID_CHECKBOX_Shengwang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Shengwang );
	//m_pID_CHECKBOX_ZiLiao = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_ZiLiao );
	//m_pID_CHECKBOX_Other = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_CHECKBOX_Other );

	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_Level );
	m_pID_BUTTON_FASH2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_FASH2 );

	m_pID_BUTTON_Hero = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_Hero );
	m_pID_BUTTON_NotHero = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_NotHero );

	m_pID_PICTURE_Ring31 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring31 );
	m_pID_PICTURE_Ring41 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring41 );

	//主将相关
	m_pID_PICTURE_HeadPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_HeadPic );
	m_pID_PICTURE_AttrPic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_AttrPic );
	m_pID_LISTIMG_HeroSkill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_LISTIMG_HeroSkill );
	m_pID_PICTURE_WarPro = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_WarPro );
	m_pID_TEXT_HeroInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_HeroInfo );
	m_pID_PICTURE_HidePic = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_HidePic );

	m_pID_BUTTON_OpenTitle = (ControlButton*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_BUTTON_OpenTitle );
	m_pID_PICTURE_WeiGuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_WeiGuo );
	m_pID_PICTURE_ShuGuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_ShuGuo );
	m_pID_PICTURE_WuGuo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_WuGuo );
	m_pID_TEXT_SuitAttr = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_SuitAttr );

	m_pID_TEXT_PetPoint = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_PetPoint );
	m_pID_TEXT_EquipScore = (ControlText*)theUiManager.FindControl( ID_FRAME_BaseProperty, ID_TEXT_EquipScore );

	m_BestEquipPic[EEquipPartType_Helmet]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Head );
	m_BestEquipPic[EEquipPartType_Armour]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Armour );
	m_BestEquipPic[EEquipPartType_Glove]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Glove );
	m_BestEquipPic[EEquipPartType_Shoe]					= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Shoe );
	m_BestEquipPic[EEquipPartType_Weapon]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_rWeapon );
	m_BestEquipPic[EEquipPartType_WeaponMinor]			= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Weapon2 );
	m_BestEquipPic[EEquipPartType_Ring1]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring1 );
	m_BestEquipPic[EEquipPartType_Ring2]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Ring2 );
	m_BestEquipPic[EEquipPartType_Bangle1]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Bangle1 );
	m_BestEquipPic[EEquipPartType_Bangle2]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Bangle2 );
	m_BestEquipPic[EEquipPartType_Shoulder]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_GangSkillBox );
	m_BestEquipPic[EEquipPartType_Necklace]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Necklace );
	m_BestEquipPic[EEquipPartType_Sash]					= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_Temp1 );
	m_BestEquipPic[EEquipPartType_Badge]				= ( ControlPicture* )theUiManager.FindControl( ID_FRAME_BaseProperty, ID_PICTURE_GangRing );

	assert( m_pID_PICTURE_WeiGuo);
	assert( m_pID_PICTURE_ShuGuo);
	assert( m_pID_PICTURE_WuGuo);
	assert( m_pID_BUTTON_OpenTitle );
    assert( m_pID_CHECKBOX_ChengZhang );
    assert( m_pID_FRAME_BaseProperty );
// 	assert( m_pID_PICTURE_DI2 );
// 	assert( m_pID_PICTURE_title2 );
// 	assert( m_pID_PICTURE_title );
//	assert( m_pID_BUTTON_CLOSE );
//	assert( m_pID_BUTTON_help );
	assert( m_pID_PICTURE_Fenge );
	//assert( m_pID_PICTURE_char );
	assert( m_pID_CHECKBOX_Zhuangbei );
	assert( m_pID_CHECKBOX_ShiZhuang );
	//assert( m_pID_CHECKBOX_Shengwang );
	assert( m_pID_CHECKBOX_Chenhao );
	//assert( m_pID_CHECKBOX_Pet );
	assert( m_pID_LISTIMG_Symbol );
	assert( m_pID_LISTIMG_Glove );
	assert( m_pID_LISTIMG_Accouterment1 );
	assert( m_pID_LISTIMG_Ring1 );
	assert( m_pID_LISTIMG_Head );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_LISTIMG_Temp1 );
	//assert( m_pID_LISTIMG_Temp );
	assert( m_pID_LISTIMG_Shoe );
	assert( m_pID_LISTIMG_Necklace );
	assert( m_pID_LISTIMG_rWeapon );
	//assert( m_pID_LISTIMG_Ring );
	//assert( m_pID_BUTTON_FASH );
//	assert( m_pID_BUTTON_Pack );
	assert( m_pID_BUTTON_Right );
	assert( m_pID_BUTTON_Left );
	//assert( m_pID_LISTIMG_Fashionhead );
	assert( m_pID_LISTIMG_Fashionarmour );
	//assert( m_pID_LISTIMG_Fashionglove );
	//assert( m_pID_LISTIMG_Fashionshoe );
	//assert( m_pID_TEXT_HuoLi );
	assert( m_pID_TEXT_ZHuoLi );
	assert( m_pID_TEXT_ZPK );
	//assert( m_pID_TEXT_ZPeiOu );
// 	assert( m_pID_TEXT_ZGongHui );
	assert( m_pID_TEXT_PK );
//	assert( m_pID_TEXT_PeiOu );
	assert( m_pID_TEXT_GongHui );
    assert( m_pID_PICTURE_FrameTitle1 );
    assert( m_pID_PICTURE_FrameTitle2 );
    assert( m_pID_PICTURE_FrameTitle3 );
    assert( m_pID_PICTURE_FrameTitle4 );

	assert( m_pID_PICTURE_Effect );
	
	assert( m_pID_TEXT_JinChengGongJi );
	assert( m_pID_TEXT_MoFaGongJi );
	assert( m_pID_TEXT_JinChengFangYu );
	assert( m_pID_TEXT_MoFaFangYu );
	assert( m_pID_TEXT_MingZhong );
	assert( m_pID_TEXT_ShanBi );
	assert( m_pID_TEXT_BaoJi );
	assert( m_pID_TEXT_BaoJiKang );
	assert( m_pID_TEXT_HP );
	assert( m_pID_TEXT_MP );
	assert( m_pID_TEXT_DaoHang );
	assert( m_pID_TEXT_Jingli );
	assert( m_pID_TEXT_Huoli );

	assert( m_pID_TEXT_DianShu );
	assert( m_pID_BUTTON_Sure );
	assert( m_pID_TEXT_ShuFa );
	assert( m_pID_BUTTON_ShuFaAdd );
	assert( m_pID_BUTTON_ShuFaMinus );
	assert( m_pID_TEXT_TiZhi );
	assert( m_pID_BUTTON_TiZhiAdd );
	assert( m_pID_BUTTON_TiZhiMinus );
	assert( m_pID_TEXT_MinJie );
	assert( m_pID_BUTTON_MinJieAdd );
	assert( m_pID_BUTTON_MinJieMinus );
	assert( m_pID_TEXT_LiLiang );
	assert( m_pID_BUTTON_LiLiangAdd );
	assert( m_pID_BUTTON_LiLiangMinus );
	assert( m_pID_PROGRESS_Exp );

	assert( m_pID_TEXT_BaoJiBei );
	assert( m_pID_TEXT_BeiXi );
	assert( m_pID_TEXT_BeiXiKang );
	assert( m_pID_TEXT_YiDong );
	assert( m_pID_PICTURE_Base );
	assert( m_pID_PICTURE_Element );
	assert( m_pID_PICTURE_Other );

	assert( m_pID_CHECKBOX_QiTa );
	assert( m_pID_CHECKBOX_ElementDown );
	assert( m_pID_CHECKBOX_ElementUp );
	assert( m_pID_CHECKBOX_Base );

	assert( m_pID_PICTURE_State5 );
	assert( m_pID_PICTURE_State4 );
	assert( m_pID_PICTURE_State3 );
	assert( m_pID_PICTURE_State2 );
	assert( m_pID_PICTURE_State1 );
	assert( m_pID_TEXT_State1_1 );
	assert( m_pID_TEXT_State1_2 );
	assert( m_pID_TEXT_State2_1 );
	assert( m_pID_TEXT_State2_2 );
	assert( m_pID_TEXT_State3_1 );
	assert( m_pID_TEXT_State3_2 );
	assert( m_pID_TEXT_State4_1 );
	assert( m_pID_TEXT_State4_2 );
	assert( m_pID_TEXT_State5_1 );
	assert( m_pID_TEXT_State5_2 );

	assert( m_pID_TEXT_Exp );
	assert( m_pID_PICTURE_ZhanShi );
	assert( m_pID_PICTURE_CiKe );
	assert( m_pID_PICTURE_YueShi );
	assert( m_pID_PICTURE_TianShi );
	assert( m_pID_PICTURE_NuShou );
	assert( m_pID_BUTTON_FASH );
	assert( m_pID_CHECKBOX_TouKui );

	assert( m_pID_PICTURE_Head1 );
	assert( m_pID_PICTURE_Symbol1 );
	assert( m_pID_PICTURE_Armour1 );
	assert( m_pID_PICTURE_Glove1 );
	assert( m_pID_PICTURE_Temp11 );
	assert( m_pID_PICTURE_Shoe1 );
	assert( m_pID_PICTURE_Necklace1 );
	assert( m_pID_PICTURE_Ring11 );
	assert( m_pID_PICTURE_Ring21 );
	assert( m_pID_PICTURE_Fabao1 );
	assert( m_pID_LISTIMG_fWeapon );
	assert( m_pID_PICTURE_fWeapon1 );
	assert( m_pID_PICTURE_rWeapon1 );
	assert( m_pID_PICTURE_Fashion11 );
	assert( m_pID_PICTURE_Fashion21 );
	assert( m_pID_LISTIMG_Fashion1 );
	assert( m_pID_LISTIMG_Fashion2 );
	assert( m_pID_LISTIMG_Symbol );
	assert( m_pID_LISTIMG_Fabao );
	assert( m_pID_TEXT_Level );
	assert( m_pID_BUTTON_FASH2 );
	assert( m_pID_BUTTON_FASH );
	assert( m_pID_BUTTON_Hero );
	assert( m_pID_BUTTON_NotHero );

	assert( m_pID_PICTURE_Ring31 );
	assert( m_pID_PICTURE_Ring41 );

	assert(	m_pID_PICTURE_HeadPic);
	assert(	m_pID_PICTURE_AttrPic);
	assert(	m_pID_LISTIMG_HeroSkill);
	assert( m_pID_PICTURE_WarPro);
	assert( m_pID_TEXT_HeroInfo);
	assert(m_pID_PICTURE_HidePic);
	assert( m_pID_PICTURE_Fashionarmour );
	assert( m_pID_TEXT_SuitAttr );

	assert( m_pID_TEXT_PetPoint );
	assert( m_pID_TEXT_EquipScore );

	assert( m_BestEquipPic[EEquipPartType_Helmet] );
	assert( m_BestEquipPic[EEquipPartType_Armour] );
	assert( m_BestEquipPic[EEquipPartType_Glove] );
	assert( m_BestEquipPic[EEquipPartType_Shoe] );
	assert( m_BestEquipPic[EEquipPartType_Weapon] );
	assert( m_BestEquipPic[EEquipPartType_WeaponMinor] );
	assert( m_BestEquipPic[EEquipPartType_Ring1] );
	assert( m_BestEquipPic[EEquipPartType_Ring2] );
	assert( m_BestEquipPic[EEquipPartType_Bangle1] );
	assert( m_BestEquipPic[EEquipPartType_Bangle2] );
	assert( m_BestEquipPic[EEquipPartType_Shoulder] );
	assert( m_BestEquipPic[EEquipPartType_Necklace] );
	assert( m_BestEquipPic[EEquipPartType_Sash] );
	assert( m_BestEquipPic[EEquipPartType_Badge] );

	if (m_pID_PICTURE_WeiGuo && m_pID_PICTURE_ShuGuo && m_pID_PICTURE_WuGuo)
	{
		m_pID_PICTURE_WeiGuo->SetVisable(false);
		m_pID_PICTURE_ShuGuo->SetVisable(false);
		m_pID_PICTURE_WuGuo->SetVisable(false);
	}
	for ( int idx = 0; idx < EEquipPartType_MaxEquitPart; ++idx )
	{
		if ( m_BestEquipPic[idx] )
		{
			m_BestEquipPic[idx]->SetOnMouseOn( OnMouseMoveForShowBest );
		}
	}

	mIconMgrBestEquip = IconMgrBestEquip::Instance();

	//m_pID_FRAME_BaseProperty->SetMsgProcFun( Frame_MsgProc );
	//m_BestEquipPic[EEquipPartType_Ring1]->SetOnMouseOn( OnMouseMoveForShowBest );	
	//m_BestEquipPic[EEquipPartType_Ring2]->SetOnMouseOn( OnMouseMoveForShowBest );
	m_pID_FRAME_BaseProperty->SetFather(s_CUI_ID_FRAME_BasePropertyBGFrame.GetFrame());
	m_pID_FRAME_BaseProperty->SetRenderNeedRedraw(s_CUI_ID_FRAME_BasePropertyOnFrameRenderNeedRedraw);

	_SetVisable(false);
	SortControl();
	m_EquipItemGroup.SetVisible(true);
	m_FashGroup.SetVisible(false);
	return true;
}

bool CUI_ID_FRAME_BaseProperty::Frame_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
	//if( bMsgUsed || !s_CUI_ID_FRAME_BaseProperty.IsVisable() )
	//	return false;

	//switch(msg)
	//{
	//case WM_LBUTTONDOWN:
	//	{
	//		//GetAdvancedMiniMap()->ProcessMinimapMouseDownL(LOWORD(lParam), HIWORD(lParam));
	//	}
	//	break;
	//case WM_MOUSEMOVE:
	//	{
	//		s_CUI_ID_FRAME_BaseProperty.UpdateBestEquipTip( LOWORD(lParam),HIWORD(lParam) );
	//		return true;
	//	}
	//	break;
	//default:
	//	break;
	//}
	return false;
}

// 卸载UI
bool CUI_ID_FRAME_BaseProperty::_UnLoadUI()
{
	//s_CUI_ID_FRAME_Pet.UnLoadUI();
// 	s_CUI_ID_FRAME_Experience.UnLoadUI();
	//s_CUI_ID_FRAME_PropertyDlg.UnLoadUI();
	s_CUI_ID_FRAME_AreaExperience.UnLoadUI();
	s_CUI_ID_FRAME_Title.UnLoadUI();
	s_CUI_ID_FRAME_Achieve.UnLoadUI();
	//s_CUI_ID_FRAME_SelfInfo.UnLoadUI();

	//s_CUI_ID_FRAME_ShowPet.UnLoadUI();
	m_BaseGroup.Clear();
	m_ElementGroup.Clear();
	m_OtherGroup.Clear();
	m_EquipItemGroup.Clear();
	m_FashGroup.Clear();

	for ( int i=0; i<EEquipPartType_MaxEquitPart; i++ )
		m_pEquipListImg[i] = NULL;
	//for( int i=0;i<FPT_Count;++i)
	//	m_pFashionEquipListImg[i] = NULL;

	m_pID_FRAME_BaseProperty = NULL;
// 	m_pID_PICTURE_DI2 = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_PICTURE_title = NULL;
	//m_pID_BUTTON_CLOSE = NULL;
//	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_Fenge = NULL;
	//m_pID_PICTURE_char = NULL;
	m_pID_CHECKBOX_Zhuangbei = NULL;
	//m_pID_CHECKBOX_Shengwang = NULL;
	m_pID_CHECKBOX_Chenhao = NULL;
	//m_pID_CHECKBOX_Pet = NULL;
	m_pID_LISTIMG_Symbol = NULL;
	m_pID_LISTIMG_Glove = NULL;
	m_pID_LISTIMG_Accouterment1 = NULL;
	m_pID_LISTIMG_Ring1 = NULL;
	m_pID_LISTIMG_Ring2 = NULL;
	m_pID_LISTIMG_Bangle1 = NULL;
	m_pID_LISTIMG_Bangle2 = NULL;
	m_pID_LISTIMG_Head = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_LISTIMG_Temp1 = NULL;
//	m_pID_LISTIMG_Temp = NULL;
	m_pID_LISTIMG_Shoe = NULL;
	m_pID_LISTIMG_Necklace = NULL;
	m_pID_LISTIMG_rWeapon = NULL;
	m_pID_LISTIMG_Weapon2 = NULL;
	m_pID_LISTIMG_Amulet = NULL;
// 	m_pID_BUTTON_FASH = NULL;
// 	m_pID_BUTTON_Pack = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	//m_pID_LISTIMG_Fashionhead = NULL;
	m_pID_LISTIMG_Fashionarmour = NULL;
//	m_pID_LISTIMG_Fashionglove = NULL;
//	m_pID_LISTIMG_Fashionshoe = NULL;
	//m_pID_TEXT_HuoLi = NULL;
	m_pID_TEXT_ZHuoLi = NULL;
	m_pID_TEXT_ZPK = NULL;
	//m_pID_TEXT_ZPeiOu = NULL;
// 	m_pID_TEXT_ZGongHui = NULL;
	m_pID_TEXT_PK = NULL;
	//m_pID_TEXT_PeiOu = NULL;
	m_pID_TEXT_GongHui = NULL;
	m_pID_CHECKBOX_ChengZhang = NULL;
	//m_pID_TEXT_ZGongXun = NULL;
//	m_pID_TEXT_GongXun = NULL;
	//m_pID_TEXT_ZMingWang = NULL;
// 	m_pID_TEXT_MingWang = NULL;
// 	m_pID_BUTTON_Title = NULL;
// 	m_pID_TEXT_BangGong = NULL;
// 	m_pID_TEXT_ZBangGong = NULL;
	m_pID_LISTIMG_GangRing = NULL;
	//m_pID_PICTURE_5907 = NULL;
	m_pID_LISTIMG_GangSkillBox = NULL;
    m_pID_PICTURE_FrameTitle1 = NULL;
    m_pID_PICTURE_FrameTitle2 = NULL;
    m_pID_PICTURE_FrameTitle3 = NULL;
    m_pID_PICTURE_FrameTitle4 = NULL;

	m_pID_PICTURE_HeadPic =NULL;
	m_pID_PICTURE_AttrPic = NULL;
	m_pID_LISTIMG_HeroSkill = NULL;
	m_pID_PICTURE_WarPro = NULL;
	m_pID_TEXT_HeroInfo = NULL;
	m_pID_PICTURE_HidePic = NULL;

	if(m_pCoolDownAni)
	{
		delete m_pCoolDownAni;
		m_pCoolDownAni = NULL;
	}

	RenderAnim_Destroy();
	return theUiManager.RemoveFrame( "Data\\UI\\baseProperty.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_BaseProperty::_IsVisable()
{
	if( !m_pID_FRAME_BaseProperty )
		return false;
	return m_pID_FRAME_BaseProperty->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_BaseProperty::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_BaseProperty )
		return;
	m_pID_FRAME_BaseProperty->SetVisable( bVisable );

	m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
	ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck(0, 0);

    m_pID_CHECKBOX_SelfInfo->SetCheck(false);
	m_pID_CHECKBOX_Chenhao->SetCheck(false);
    m_pID_CHECKBOX_Achieve->SetCheck(false);
	//m_pID_CHECKBOX_Pet->SetCheck(false);

    m_pID_PICTURE_FrameTitle1->SetVisable( true );
    m_pID_PICTURE_FrameTitle2->SetVisable( false );
    m_pID_PICTURE_FrameTitle3->SetVisable( false );
    m_pID_PICTURE_FrameTitle4->SetVisable( false );

	if (bVisable)
    {
		// 刷新装备
		RefreshEquip();

        Refresh();
		RefreshProperty();
		m_BaseGroup.SetVisible(true);
		m_ElementGroup.SetVisible(false);
		m_OtherGroup.SetVisible(false);

		//m_pID_CHECKBOX_ShuXing->SetCheck(true);
		//m_pID_CHECKBOX_ZiLiao->SetCheck(false);
		m_pID_CHECKBOX_Shengwang->SetCheck(false);
		//m_pID_CHECKBOX_Other->SetCheck(false);

		ChangeProfession();

		m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
		m_pID_CHECKBOX_ShiZhuang->SetCheck(false);

		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if (pMe != NULL)
		{
			if (pMe->IsShowAecpratove())
			{
				m_pID_BUTTON_FASH->SetVisable(false);
				m_pID_BUTTON_FASH2->SetVisable(true);				
			}
			else
			{
				m_pID_BUTTON_FASH->SetVisable(true);
				m_pID_BUTTON_FASH2->SetVisable(false);
			}

			if (pMe->IsSHowHero())
			{
				m_pID_BUTTON_Hero->SetVisable(false);
				m_pID_BUTTON_NotHero->SetVisable(true);
			}
			else
			{
				m_pID_BUTTON_Hero->SetVisable(true);
				m_pID_BUTTON_NotHero->SetVisable(false);
			}

			if ( pMe->IsShowHelmet() )
			{
				m_pID_CHECKBOX_TouKui->SetCheck( true );
			}
			else
			{
				m_pID_CHECKBOX_TouKui->SetCheck( false );
			}
			RefreshHeroInfo();
		}

		int nUsePoint = thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential);
		SetDianShuControlEnable(nUsePoint > 0);

		UpdatePetPoint();
    }
	else
    {
		//s_CUI_ID_FRAME_PropertyDlg.SetVisable( false );
    }
	
	if (bVisable)
	{
		s_CUI_ID_FRAME_MainMenu.SetNeedSpark(false, CUI_ID_FRAME_MainMenu::ekey_baseProperty);
	}
}
void CUI_ID_FRAME_BaseProperty::UpdatePetPoint()
{
	int Point = thePlayerRole.GetCharInfo2().otherdataclient.PetDuration;
	char xxPetPoint[8];
	itoa(Point,xxPetPoint,10);
	m_pID_TEXT_PetPoint->SetText(xxPetPoint);
}
void CUI_ID_FRAME_BaseProperty::Refresh()
{
     // 10级后每次重新登录显示升级小泡泡		added by zhuomeng.hu		[10/11/2010]
    m_pID_BUTTON_LevelUp->SetEnable( false );
    __int64 dwExp = thePlayerRole.GetExpNotUsed();
    __int64 dwNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
    if( ( thePlayerRole.GetLevel() >= CHAR_AUTO_LEVELUP ) && ( dwExp > dwNeedExp ) )
    {
        if( IsUILoad() && m_pID_BUTTON_LevelUp )
		{
            m_pID_BUTTON_LevelUp->SetEnable( true );
			m_dwStartTime = HQ_TimeGetTime();
		}

        /*if( !m_bLvlupHasShown )
        {
            s_CUI_ID_FRAME_InfoTips.AddPlayerLevelUpTip();
            m_bLvlupHasShown = true;
        }*/
    }

	/*if( ( thePlayerRole.GetLevel() >= CHAR_AUTO_LEVELUP ) && ( dwExp < dwNeedExp ) && m_bLvlupHasShown )
	{
		s_CUI_ID_FRAME_InfoTips.DeleteTip( CUI_ID_FRAME_InfoTips::eButton_Usage_PlayerLevelUp );
		m_bLvlupHasShown = false;
	}*/
	

	if( !m_pID_FRAME_BaseProperty )
		return;
	//s_CUI_ID_FRAME_PropertyDlg.Refresh();
	RefreshProperty();
	s_CUI_ID_FRAME_AreaExperience.Update();
	s_CUI_ID_FRAME_Achieve.Refresh();

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;

	int nKill = -pMe->GetPKKillValue();
	m_pID_TEXT_PK->SetText(nKill);

	if (thePlayerRole.GetGangMgr()->GetGuildName() && strlen(thePlayerRole.GetGangMgr()->GetGuildName()) > 0)
		m_pID_TEXT_GongHui->SetText(thePlayerRole.GetGangMgr()->GetGuildName());
	else
		m_pID_TEXT_GongHui->SetText(g_strGuildNull);

    // 改为阵营
    m_pID_TEXT_Country->SetText( CountryFunction::GetDefaultCountryNameById( pMe->GetRealCountry() ) );

	std::string strTitle = pMe->GetTitle();//s_CUI_ID_FRAME_Title.GetCurrentSelectTitle();
	if ( !strTitle.empty() )
	{
		m_pID_TEXT_Title->SetText( strTitle.c_str() );
	}
	m_pID_TEXT_GongHui->SetText(pMe->GetGuildName());
	/*m_pID_TEXT_Group;*/

    // 经验显示
	m_pID_TEXT_ExpCurrent->SetText( dwExp );
    m_pID_TEXT_ExpLevelUp->SetText( dwNeedExp );

	RefreshProperty();
	RefreshExpProgress();
	RefreshHeroInfo();
}

void CUI_ID_FRAME_BaseProperty::RefreshHeroInfo()
{
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return;
	}
	uint16 ustHeroID = pMe->GetHeroID();
	CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(ustHeroID);
	if (!pHero)
	{
		m_pID_PICTURE_HeadPic->SetVisable(false);
		m_pID_PICTURE_AttrPic->SetVisable(false);
		m_pID_LISTIMG_HeroSkill->SetVisable(false);
		m_pID_PICTURE_WarPro->SetVisable(false);
		m_pID_TEXT_HeroInfo->SetVisable(false);
		m_pID_PICTURE_HidePic->SetVisable(true);
	}
	else
	{
		m_pID_PICTURE_HidePic->SetVisable(true);
		m_pID_PICTURE_HeadPic->SetVisable(true);
		m_pID_PICTURE_HeadPic->SetPicName(pHero->Pic_BasePro.c_str());
		//m_pID_PICTURE_HeadPic->SetPicName(PlayerInfoMgr::Instance()->GetPlayerHeadPic(pHero));
		m_pID_PICTURE_AttrPic->SetVisable(true);
		m_pID_PICTURE_AttrPic->SetPicName(pHero->icon_addr.c_str());
		m_pID_PICTURE_WarPro->SetVisable(true);
		m_pID_PICTURE_WarPro->SetPicName(pHero->proPicAddr.c_str());
		m_pID_TEXT_HeroInfo->SetVisable(true);
		m_pID_TEXT_HeroInfo->Clear();
		m_pID_TEXT_HeroInfo->SetText(pHero->explain_hero);
		m_pID_LISTIMG_HeroSkill->SetVisable(true);
		int skillArray[MAX_HERO_SKILL_COUNT] = {pHero->hero_skill1,pHero->hero_skill2,pHero->hero_skill3};
		int skillLevel[MAX_HERO_SKILL_COUNT] = {pHero->skill1_lv,pHero->skill2_lv,pHero->skill3_lv};
		for (int i=0;i<MAX_HERO_SKILL_COUNT;i++)
		{
			if (0==skillArray[i] || 0xffffffff== skillArray[i])
			{
				continue;
			}
			ControlIconDrag::S_ListImg stListItem;
			SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(skillArray[i]);
			if (iconSet)
				stListItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
			bool bEnable = eIcon_Enable;

			ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( skillArray[i],
				skillLevel[i] );
			//属于被动技能就不让拖动icon
			if (NULL!=pItemSkill && (ItemDefine::generaltype_passive == pItemSkill->stGeneralType  ||ItemDefine::generaltype_trigger == pItemSkill->stGeneralType ) )
			{
				bEnable = eIcon_Disable;
			}

			stListItem.SetData( skillArray[i], skillLevel[i], bEnable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
			//stListItem.SetData( skillArray[i],skillLevel[i], ( bEnable ? eIcon_Enable : eIcon_Disable ));
			stListItem.SetSparkEnable( false );
			m_pID_LISTIMG_HeroSkill->SetItem( &stListItem, i );	
		}

	}

}

void CUI_ID_FRAME_BaseProperty::ClearEquipList()
{
	m_pID_LISTIMG_Head->Clear();
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Glove->Clear();
	m_pID_LISTIMG_Shoe->Clear();
	m_pID_LISTIMG_Ring1->Clear();
	m_pID_LISTIMG_Ring2->Clear();
	m_pID_LISTIMG_Bangle1->Clear();
	m_pID_LISTIMG_Bangle2->Clear();
	m_pID_LISTIMG_rWeapon->Clear();
	m_pID_LISTIMG_Weapon2->Clear();
	m_pID_LISTIMG_Necklace->Clear();
	m_pID_LISTIMG_Amulet->Clear();
	m_pID_LISTIMG_Temp1->Clear();
	m_pID_LISTIMG_Accouterment1->Clear();
	m_pID_LISTIMG_GangRing->Clear();
	m_pID_LISTIMG_GangSkillBox->Clear();
	m_pID_LISTIMG_Fashionarmour->Clear();

	//for( int i = 0 ; i < FPT_Count ; ++ i )
	//{
	//	m_pFashionEquipListImg[i]->Clear();
	//}
}

struct SuitIDAction
{
	SuitIDAction()
	{
		bAction = FALSE;
		SuitID = -1;
	}
	short SuitID;
	short SuitCurNum;
	BOOL  bAction;
};

void CUI_ID_FRAME_BaseProperty::RefreshEquip()
{
	if( !m_pID_FRAME_BaseProperty )
		return;
	thePlayerRole.suitManager.ApplyToPlayer();

	// 有更新装备就刷新次最佳装备的小图标
	RefreshBastEquipPic();

	UpdateEquipUI();
	UpdatePlayerAnimCtrl();

	RefreshSuitAttr();
	RefreshEquipScore();

	s_CUI_ID_FRAME_SKILL.RefreshEquipSkill();
	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
}

void CUI_ID_FRAME_BaseProperty::RefreshBastEquipPic()
{
	SCharItem* pVisual = thePlayerRole.m_pVisual->GetVisualArray();

	if ( !pVisual )
	{
		return ;
	}

	for( int idx = 0; idx < EEquipPartType_MaxEquitPart; idx++ )
	{
		bool isShow = false;
		if( pVisual[idx].itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			isShow = false;
		}
		else
		{
			isShow = true;
		}

		if ( m_BestEquipPic[idx] != NULL )
		{
			m_BestEquipPic[idx]->SetVisable( isShow );
		}
	}

}

void CUI_ID_FRAME_BaseProperty::UpdateEquipUI()
{
	if( !m_pID_FRAME_BaseProperty )
		return;
	//清理ImgList
	ClearEquipList();

	BOOL bPartDoll[CEquipmentDoll::ePart_Max];  // 是否显示装备要修复图标
	BOOL bDisable[CEquipmentDoll::ePart_Max];   // 是否使装备栏里的图标变灰
	for( int i=0; i< CEquipmentDoll::ePart_Max; i++ )
	{
		bPartDoll[i] = FALSE;
		bDisable[i] = FALSE;
	}

	thePlayerRole.m_doll.m_bRender = FALSE;

	// 以属性套装来计算装备破损程度。
	SCharItem* pVisual = thePlayerRole.m_pVisual->GetVisualArray();

	BOOL bEnable = TRUE;
	INT	 BadRef = 0;

	std::vector<SuitIDAction> SuitActions;

	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		if(	pVisual[i].itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			ItemDefine::SItemCommon* pConmmon = GettheItemDetail().GetItemByID( pVisual[i].itembaseinfo.ustItemID );
			if( pConmmon 
				&& 
				pConmmon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
				)
			{
				ItemDefine::SItemArmour *pArmour = (ItemDefine::SItemArmour *)pConmmon;

				SuitIDAction *pSelAction = NULL;
				if( pArmour->sSuitID != -1 )
				{
					for( int SuitLoop = 0; SuitLoop< SuitActions.size(); SuitLoop++ )
					{
						if( SuitActions[SuitLoop].SuitID == pArmour->sSuitID )
						{
							pSelAction = &SuitActions[SuitLoop];
						}
					}
					if( pSelAction )
					{
						pSelAction->SuitCurNum++;
						if( pSelAction->SuitCurNum == pArmour->sPartCount )
						{
							pSelAction->bAction = TRUE;
						}
					}
					else
					{

						SuitIDAction Action;
						Action.SuitID = pArmour->sSuitID;
						Action.SuitCurNum = 1;
						SuitActions.push_back(Action);
					}
				}
			}
		}
	}

	SCharItem* pAttriEquips = thePlayerRole.m_charinfo.visual.GetVisualArray();
	for( int i=0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		// 设置修复图标
		if(	pAttriEquips[i].itembaseinfo.ustItemID 
			!= InvalidLogicNumber &&
			pAttriEquips[i].equipdata.usHP == 0 )
		{
			bEnable = FALSE;
			if( EEquipPartType_Weapon == i )
				bPartDoll[CEquipmentDoll::ePart_WeaponMain] = TRUE;
			else if( EEquipPartType_WeaponMinor == i )
                bPartDoll[CEquipmentDoll::ePart_WeaponMinor] = TRUE;
			else if( EEquipPartType_Armour == i )
				bPartDoll[CEquipmentDoll::ePart_Armour] = TRUE;
			else if( EEquipPartType_Glove == i )
				bPartDoll[CEquipmentDoll::ePart_Glove] = TRUE;
			else if( EEquipPartType_Shoe == i )
				bPartDoll[CEquipmentDoll::ePart_Shoe] = TRUE;
			else if( EEquipPartType_Helmet == i )
				bPartDoll[CEquipmentDoll::ePart_Helmet] = TRUE;
			else if( EEquipPartType_Sash == i )
				bPartDoll[CEquipmentDoll::ePart_Sash] = TRUE;
			else if( EEquipPartType_Bangle1 == i )
				bPartDoll[CEquipmentDoll::ePart_Bangle] = TRUE;
			else if( EEquipPartType_Bangle2 == i )
				bPartDoll[CEquipmentDoll::ePart_Bangle] = TRUE;
			else if( EEquipPartType_Ring1 == i )
				bPartDoll[CEquipmentDoll::ePart_Ring] = TRUE;
			else if( EEquipPartType_Ring2 == i )
				bPartDoll[CEquipmentDoll::ePart_Ring] = TRUE;
			else if( EEquipPartType_Necklace == i )
				bPartDoll[CEquipmentDoll::ePart_Necklace] = TRUE;
			else if (EEquipPartType_Shoulder == i) //lyh++ 护肩 毁坏
			    bPartDoll[CEquipmentDoll::ePart_Shoulder] = TRUE;
			else if (EEquipPartType_Trousers == i) //lyh++ 裤子
				bPartDoll[CEquipmentDoll::ePart_WeaponMinor] = TRUE;
			    
		}
		else
        {
			bEnable = TRUE;
        }

		//////////////////////////////////////////////////////////////////////////
		BOOL bSuitAction = FALSE;
		INT SuitIdx = -1;
		ItemDefine::SItemCommon* pConmmon = GettheItemDetail().GetItemByID( pVisual[i].itembaseinfo.ustItemID );
		if( pConmmon 
			&& 
			pConmmon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
			)
		{
			ItemDefine::SItemArmour *pArmour = (ItemDefine::SItemArmour *)pConmmon;

			for( int iLoop=0; iLoop<SuitActions.size(); iLoop++ )
			{
				if( SuitActions[iLoop].bAction 
					&& pArmour->sSuitID == SuitActions[iLoop].SuitID )
				{
					bSuitAction = TRUE;
				}
				if( pArmour->sSuitID == SuitActions[iLoop].SuitID )
				{
					SuitIdx = iLoop;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////
		ControlIconDrag::S_ListImg stItem;
		if( SuitActions.size() == 0  || SuitIdx == -1 )
		{
			stItem.SetData( &pVisual[i], bEnable ? eIcon_Enable:eIcon_Disable, eTipFlag_Normal, NULL,0 );
		}
		else
		{
			stItem.SetData( &pVisual[i], bEnable ? eIcon_Enable:eIcon_Disable, eTipFlag_Normal, NULL, theApp->GetPlayerMgr()->GetMyID() );			
		}

		if ( !stItem.IsNull() )
		{
			stItem.m_pkIconInfo->SetCost( 0 );
			if(m_pEquipListImg[i])
				m_pEquipListImg[i]->SetItem( &stItem, 0 );
		}
		else
		{
			if( EEquipPartType_Weapon == i && !bPartDoll[CEquipmentDoll::ePart_WeaponMain] )
				bDisable[CEquipmentDoll::ePart_WeaponMain] = TRUE;

            if( EEquipPartType_WeaponMinor == i && !bPartDoll[CEquipmentDoll::ePart_WeaponMinor] )
                bDisable[CEquipmentDoll::ePart_WeaponMinor] = TRUE;
		}
	}


	for( int i=0; i<CEquipmentDoll::ePart_Max; i++ )
	{
		thePlayerRole.m_doll.m_parts[i].bNeedRepair = bPartDoll[i];
		thePlayerRole.m_doll.m_parts[i].bDisable = bDisable[i];
		if( thePlayerRole.m_doll.m_parts[i].bNeedRepair )
		{
			thePlayerRole.m_doll.m_bRender = TRUE;
		}
	}
}
void CUI_ID_FRAME_BaseProperty::UpdatePlayerAnimCtrl()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( !pMe )
		return;

	if (pMe->GetAnim() && RenderAnim_GetPlayer()->GetAnim() != NULL)
	{
		uint16 stVisualItemID[EEquipPartType_MaxEquitPart];
		uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart];
		uint8 equipLevel[EEquipPartType_MaxEquitPart];
		uint8 equipElements[EEquipPartType_MaxEquitPart];
		CPlayer_SEquipment equip[eKeyAll_Max];

		memcpy(equip, pMe->GetEquip(), eKeyAll_Max * sizeof(CPlayer_SEquipment));
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			int nPart = CEquipPartMap::Instance()->GetLogicPart(i);
			stVisualItemID[i] = equip[nPart].item.itembaseinfo.ustItemID;
			equipIntensifyTime[i] = equip[nPart].item.equipdata.gemHoleCount;
			equipLevel[i] = equip[nPart].item.equipdata.ucLevel;
			equipElements[i] = equip[nPart].item.itembaseinfo.value1;
		}

		//bool showHelmet = pMe->IsShowHelmet() || pMe->IsShowAecpratove();
		RenderAnim_GetPlayer()->GetAnim()->ChangeSkeletonAndEquipAll(
			&equip,
			pMe->GetSex(),
			pMe->GetProfession(),
			pMe->GetHairColorIndex(),
			pMe->IsShowHelmet(), pMe->IsShowAecpratove(),pMe->GetDefAvaterIndex(),
			theHeroGame.GetPlayerMgr()->GetMe()->GetHeroID(),pMe->IsSHowHero());

		RenderAnim_GetPlayer()->GetAnim()->UpdateHardItem( pMe->HasFightFlag(eFighting),
			(void*)equip );
		//RenderAnim_GetPlayer()->GetAnim()->SetPosition( 0.0f, 0.0f, 0.0f );

		if( pMe->IsHaveWeapon() )
		{
            // 是否拿旗子
            BOOL bHoldFlag = FALSE;
            if( RenderAnim_GetPlayer()->GetAnim()->IsHoldingFlagOnRightHand() )
                bHoldFlag = TRUE;

			RenderAnim_GetPlayer()->GetAnim()->ChangeWeaponAnim( RenderAnim_GetPlayer()->GetAnim()->GetWeaponActionModelId( pMe->GetProfession(), pMe->GetSex(), bHoldFlag ));

			RenderAnim_GetPlayer()->GetAnim()->PlayAnim2(	MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			RenderAnim_GetPlayer()->GetAnim()->PlayAnim2(	MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay );
		}

		// 五行
		RenderAnim_GetPlayer()->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
		RenderAnim_GetPlayer()->UpdateBones();
	}

	s_CUI_ID_FRAME_ShopCenter.UpdatePlayerAnimCtrl();
}

BOOL CUI_ID_FRAME_BaseProperty::InitCamera()
{
	FLOAT fAspect = ((FLOAT)200.0f) / 300.0f;
	m_Camera.SetProjParams( D3DX_PI*(30/45.0f)/4, fAspect, 1.0f, 220.0f );

	m_ViewPort.X = 0;
	m_ViewPort.Y = 0;
	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinZ = 0;
	m_ViewPort.MaxZ = 1;

	return TRUE;
}
bool CUI_ID_FRAME_BaseProperty::IsList( const ControlObject* pObject )
{
	if (!pObject)
		return false;

	for( int i=0; i<EEquipPartType_MaxEquitPart; i++ )
	{
		if (m_pEquipListImg[i] == pObject)
			return true;
	}
	//// added, jiayi, [2009/10/12]
	//for( int i=0; i< FPT_Count; i++ )
	//{
	//	if (m_pFashionEquipListImg[i] == pObject)
	//		return true;
	//}
	return false;
}

int	CUI_ID_FRAME_BaseProperty::GetWhere( const ControlIconDrag::S_ListImg* pList )
{
	for( int i=0; i<EEquipPartType_MaxEquitPart; i++ )
	{
		if (m_pEquipListImg[i] && m_pEquipListImg[i]->GetItemIndex( pList ) != -1)
			return i;
	}
	/*for( int i = 0 ; i < FPT_Count ; ++ i )
	{
		if( m_pFashionEquipListImg[i] && m_pFashionEquipListImg[i]->GetItemIndex( pList ) != -1 )
			return i;
	}*/
	return -1;
}

bool CUI_ID_FRAME_BaseProperty::Repair(ControlIconDrag::S_ListImg* pItem)
{
	if (s_CUI_ID_FRAME_SHOP.GetRepair())
	{
		if ( pItem->IsNull() )
			return false;
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pItem->m_pkIconInfo->Id());			
		if ( !pItemCommon )
			return false;

		if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
			pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
		{
			//装备需求
			ItemDefine::SItemCanEquip *pCanEquip = (ItemDefine::SItemCanEquip *)pItemCommon;
			if (pCanEquip)
			{
				int i = 0;
				for ( ; i < EEquipPartType_MaxEquitPart; ++i)
				{
					if (pCanEquip->arrayCanEquip[i])
						break;
				}
				s_CUI_ID_FRAME_SHOP.RepairEquip(i);
			}
			return true;
		}
	}
	return false;
}

bool CUI_ID_FRAME_BaseProperty::UIBaseProperty_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_BaseProperty.m_bRotate = true;
	return true;
}

bool CUI_ID_FRAME_BaseProperty::UIBaseProperty_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_BaseProperty.m_bRotate = true;
	return true;
}

void CUI_ID_FRAME_BaseProperty::OnMouseMoveForShowBest( ControlObject* pSender )
{
	if ( s_CUI_ID_FRAME_BaseProperty.IsVisable() )
	{
		s_CUI_ID_FRAME_BaseProperty.UpdateBestEquipTip( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
	}
}

void CUI_ID_FRAME_BaseProperty::OnSetDragItem(ControlIconDrag* pList, ControlIconDrag::S_ListImg* pItem)
{
	//if (s_CUI_ID_FRAME_BaseProperty.IsList(pList))
	//{
	//}
}

void CUI_ID_FRAME_BaseProperty::OnClearDragItem(ControlIconDrag* pDstList, ControlIconDrag* pSrcList, ControlIconDrag::S_ListImg* pSrcListItem)
{
	//if (!pDstList && s_CUI_ID_FRAME_BaseProperty.IsList(pSrcList))
	//{
	//	s_CUI_ID_FRAME_PropertyDlg.Refresh();
	//}
}

void CUI_ID_FRAME_BaseProperty::OnPicMoveEnter( ControlObject* pList )
{

}

void CUI_ID_FRAME_BaseProperty::OnPicMoveLevel( ControlObject* pList )
{

}

void CUI_ID_FRAME_BaseProperty::SetTextGongXun( DWORD dw )
{
// 	if(m_pID_TEXT_GongXun)
// 		m_pID_TEXT_GongXun->SetText(dw);
// 	else
// 		assert(false&&"ui error");
}

void CUI_ID_FRAME_BaseProperty::SetTextMingWang( DWORD dw )
{
// 	if(m_pID_TEXT_MingWang)
// 		m_pID_TEXT_MingWang->SetText(dw);
// 	else
// 		assert(false&&"ui error");
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ShowHelmOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
	}

	MsgShowHelmet msg;
	msg.showHelmet = true;
	if (thePlayerRole.m_charinfo.visual.IsShowHelmet())
	{
		msg.showHelmet = false;
	}

	m_pID_CHECKBOX_ShowHelm->SetCheck(msg.showHelmet);
	GettheNetworkInput().SendMsg(&msg);

	CPlayer* me = theHeroGame.GetPlayerMgr()->GetMe();
	if (me)
	{
		me->ShowHelmetAndSendMsg(msg.showHelmet);
		me->ChangeSkeletonAndEquipAllItem( me->HasFightFlag( eFighting ) );
		s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
		thePlayerRole.UpdateUI();
	}
}

void CUI_ID_FRAME_BaseProperty::ID_CHECKBOX_ShowFasionOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_BaseProperty)
	{
		assert(false&&"ui error");
	}

	MsgSwitchSuit msg;
	msg.nSuitIndex = 1;
	if (thePlayerRole.m_charinfo.visual.IsShowAecorative())
	{
		msg.nSuitIndex = 0;
	}
	CPlayer* me = theHeroGame.GetPlayerMgr()->GetMe();
	if (me)
	{
		me->ShowAecpratove(msg.nSuitIndex);
	}

	m_pID_CHECKBOX_ShowFasion->SetCheck(msg.nSuitIndex);
	GettheNetworkInput().SendMsg(&msg);
}

bool CUI_ID_FRAME_BaseProperty::ID_BUTTON_LevelUpOnButtonClick( ControlObject* pSender )
{
    // 经验不足直接返回
   /* int64 nCurExp = thePlayerRole.GetExpNotUsed();
    int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
    if( nCurExp <= nNeedExp )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_LevelUp_Belongs, theXmlString.GetString( eText_LevelUp_ExpNotEnough ) );
        return true;
    }

    MsgCharacterLevelup msg;
    GettheNetworkInput().SendMsg( &msg );*/
	s_CUI_ID_FRAME_ManualLevelUp._SetVisable(true);
	return true;
}

void CUI_ID_FRAME_BaseProperty::ResetLevelUpTip()
{
    m_bLvlupHasShown = false;
}

void CUI_ID_FRAME_BaseProperty::TryLight( float fLight1, float fLight2, float fLight3 )
{
    m_fLightTry1 = fLight1;
    m_fLightTry2 = fLight2;
    m_fLightTry3 = fLight3;
}

CSmartAnimation* CUI_ID_FRAME_BaseProperty::GetCoolDownAniNotNULL()
{
	if (NULL == m_pCoolDownAni)
	{
		char fullname[MAX_PATH] = {0};
		MeSprintf_s(fullname,sizeof(fullname)/sizeof(char) - 1, "%s\\data\\ui\\UIAni\\LvUp.2DAni", GetRootPath());
		m_pCoolDownAni = new CXmlAnimation( m_pID_FRAME_BaseProperty->GetFrameRender() );

		MeXmlDocument doc;
		if(!doc.LoadFile(fullname))
		{
			assert(0);
			return m_pCoolDownAni;
		}
		MeXmlElement* pElement = doc.FirstChildElement("LvUp");
		if (pElement)
		{
			CXmlAnimation* pSmart = (CXmlAnimation*)m_pCoolDownAni;
			pSmart->Initialize(pElement);
		}

		RECT rcPlay;
		m_pID_PICTURE_Effect->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, rcPlay.right -rcPlay.left, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, rcPlay.bottom - rcPlay.top, NULL );
	}
	return m_pCoolDownAni;

}

void CUI_ID_FRAME_BaseProperty::ResetDevice()
{
	if(m_pCoolDownAni  )
	{
		RECT rcPlay;
		m_pID_PICTURE_Effect->GetRealRect(&rcPlay);
		int nWidth = rcPlay.right -rcPlay.left;
		int nHeight = rcPlay.bottom - rcPlay.top;
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Width, rcPlay.right -rcPlay.left, NULL );
		m_pCoolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Height, rcPlay.bottom - rcPlay.top, NULL );
	}

}

bool CUI_ID_FRAME_BaseProperty::OnFrameRenderNeedRedraw()
{
	if (m_pID_BUTTON_LevelUp->IsVisable() && m_pID_BUTTON_LevelUp->IsEnable())
	{
		DWORD dwCurTime = HQ_TimeGetTime();
		// 未创建动画则创建
		CSmartAnimation* coolDownAni = GetCoolDownAniNotNULL();
		if( !coolDownAni->IsInAnimation() )
		{
			m_pID_FRAME_BaseProperty->GetUiAniManageNotNULL()->AddAnimation( coolDownAni );

			coolDownAni->StartAnimation( dwCurTime,dwCurTime - m_dwStartTime, true );
		}
		else
		{
			RECT rcPlay;
			m_pID_PICTURE_Effect->GetRealRect(&rcPlay);
			int nWidth = rcPlay.right -rcPlay.left;
			int nHeight = rcPlay.bottom - rcPlay.top;
			coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_X, rcPlay.left + nWidth/2, NULL );
			coolDownAni->InitializeFunctor( CSmartAnimation::EFunctorType_Y, rcPlay.top + nHeight/2, NULL );
			coolDownAni->Redraw(dwCurTime);
		}
	}
	else
	{
		if (NULL != m_pCoolDownAni)
		{
			m_pID_FRAME_BaseProperty->GetUiAniManageNotNULL()->StopAnimation(m_pCoolDownAni);
			m_dwStartTime = 0;
		}
	}	
	return true;

}


void CUI_ID_FRAME_BaseProperty::RefreshProperty()
{
	// 人名 等级 职业
	if( !m_pID_FRAME_BaseProperty )
		return;

	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (!pMe)
	{
		return;
	}
	DWORD dwColor = Color_Config.getColor(CC_ZhuJiang_Attr);
	if (0==dwColor)
	{
		dwColor = 0xffffd700;
	}
	uint16 uHeroID = pMe->GetHeroID();
	CItemHero::SItemHero* pItemHero = theItemHero.FindHeroByHeroID(uHeroID);
	char szInfo[256] = {0};

	if (uHeroID == INVALID_HERO_ID || uHeroID==0 || !pItemHero)
	{
		//物理攻击
		*m_pID_TEXT_JinChengGongJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_ATTACKPHYSICS);

		//物理防御
		*m_pID_TEXT_JinChengFangYu = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_DefendPhysics);

		//魔法攻击
		*m_pID_TEXT_MoFaGongJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_AttackMagic);   

		//魔法防御
		*m_pID_TEXT_MoFaFangYu = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_DefendMagic);

		// 命中
		m_pID_TEXT_MingZhong->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_EXACT));

		// 闪避
		m_pID_TEXT_ShanBi->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_DODGE));

		// 暴击
		*m_pID_TEXT_BaoJi = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLE);

		// 韧性或暴击抗性
		if(m_pID_TEXT_BaoJiKang)
		{
			int Sum = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_TENACITY);
			char ss[128];
			m_pID_TEXT_BaoJiKang->SetText(itoa(Sum,ss,10));
		}
		//*m_pID_TEXT_BaoJiKang = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_TENACITY);

		//HP上限
		__int64 nMaxHp = thePlayerRole.GetData( CPlayerRole::TYPE_HPMAX );
		MeSprintf_s(szInfo,sizeof(szInfo),"%I64u",nMaxHp);
		m_pID_TEXT_HP->SetText(szInfo);

		//MP上限
		__int64 nMaxMp = thePlayerRole.GetData( CPlayerRole::TYPE_MPMAX );
		MeSprintf_s(szInfo,sizeof(szInfo),"%I64u",nMaxMp);
		m_pID_TEXT_MP->SetText(szInfo);

		////道行
		//__int64 nMaxDaoxing = thePlayerRole.GetData(CPlayerRole::TYPE_Daoxing);
		//MeSprintf_s(szInfo,sizeof(szInfo),"%I64u %s",nMaxDaoxing,theXmlString.GetString(eText_Day));
		//m_pID_TEXT_DaoHang->SetText(szInfo);

		////活力
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d/%d", 
		//	thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY ),
		//	thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY_MAX ) );
		//m_pID_TEXT_Huoli->SetText(szInfo);

		////精力	
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d/%d", 
		//	thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR ),
		//	thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR_MAX ) );
		//m_pID_TEXT_Jingli->SetText(szInfo);
	}
	else
	{
		SCharFightAttr fightAttr = thePlayerRole.GetCharInfo2().baseinfo.baseProperty.fightAttr;
		SCharFightAttr lastAttr = thePlayerRole.m_charLastBaseProperty.fightAttr;
#define GET_HERO_ADD_ATTR(attrHero,attrFinal)\
	int(attrHero)==0?MeSprintf_s(szInfo,sizeof(szInfo),"%d",int(attrFinal)):MeSprintf_s(szInfo,sizeof(szInfo),"%d{#%x=(+%d)#}",int(attrFinal),dwColor,int(attrHero));
		//物理攻击
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.attackPhysics.final),int(fightAttr.attackPhysics.hero));
		GET_HERO_ADD_ATTR(fightAttr.attackPhysics.hero,fightAttr.attackPhysics.final);
		m_pID_TEXT_JinChengGongJi->SetText(szInfo);
		//物理防御
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.defendPhysics.final),int(fightAttr.defendPhysics.hero));
		GET_HERO_ADD_ATTR(fightAttr.defendPhysics.hero,fightAttr.defendPhysics.final);
		m_pID_TEXT_JinChengFangYu->SetText(szInfo);
		//魔法攻击
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.attackMagic.final),int(fightAttr.attackMagic.hero));
		GET_HERO_ADD_ATTR(fightAttr.attackMagic.hero,fightAttr.attackMagic.final);
		m_pID_TEXT_MoFaGongJi->SetText(szInfo);  
		//魔法防御
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.defendMagic.final),int(fightAttr.defendMagic.hero));
		GET_HERO_ADD_ATTR(fightAttr.defendMagic.hero,fightAttr.defendMagic.final);
		m_pID_TEXT_MoFaFangYu->SetText(szInfo);  
		//命中
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.exact.final),int(fightAttr.exact.hero));
		GET_HERO_ADD_ATTR(fightAttr.exact.hero,fightAttr.exact.final);
		m_pID_TEXT_MingZhong->SetText(szInfo); 
		//闪避
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.dodge.final),int(fightAttr.dodge.hero));
		GET_HERO_ADD_ATTR(fightAttr.dodge.hero,fightAttr.dodge.final);
		m_pID_TEXT_ShanBi->SetText(szInfo);
		//暴击
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.critical.final),int(fightAttr.critical.hero));
		GET_HERO_ADD_ATTR(fightAttr.critical.hero,fightAttr.critical.final);
		m_pID_TEXT_BaoJi->SetText(szInfo);
		//韧性或暴击抗性
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.tenacity.final),int(fightAttr.tenacity.hero));
		GET_HERO_ADD_ATTR(fightAttr.tenacity.hero,fightAttr.tenacity.final);
		m_pID_TEXT_BaoJiKang->SetText(szInfo);
		//HP上限
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.hpMax.final),int(fightAttr.hpMax.hero));
		GET_HERO_ADD_ATTR(fightAttr.hpMax.hero,fightAttr.hpMax.final);
		m_pID_TEXT_HP->SetText(szInfo);
		//MP上限
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",int(fightAttr.mpMax.final),int(fightAttr.mpMax.hero));
		GET_HERO_ADD_ATTR(fightAttr.mpMax.hero,fightAttr.mpMax.final);
		m_pID_TEXT_MP->SetText(szInfo);
	}

	//道行
	__int64 nMaxDaoxing = thePlayerRole.GetData(CPlayerRole::TYPE_Daoxing);
	MeSprintf_s(szInfo,sizeof(szInfo),"%I64u %s",nMaxDaoxing,theXmlString.GetString(eText_Day));
	m_pID_TEXT_DaoHang->SetText(szInfo);
	//活力
	MeSprintf_s( szInfo, sizeof(szInfo), "%d/%d", 
		thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY ),
		thePlayerRole.GetData( CPlayerRole::TYPE_ENERGY_MAX ) );
	m_pID_TEXT_Huoli->SetText(szInfo);
	//精力	
	MeSprintf_s( szInfo, sizeof(szInfo), "%d/%d", 
		thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR ),
		thePlayerRole.GetData( CPlayerRole::TYPE_VIGOR_MAX ) );
	m_pID_TEXT_Jingli->SetText(szInfo);

	//基本属性
	// 四围
	float fFactor = 0.0f;
	int nLiLiang = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Strength) + fFactor) + m_nValue[EBaseAttr_Strength];
	int nMinJie = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Agility) + fFactor) + m_nValue[EBaseAttr_Agility];
	int nTiZhi = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Stamina) + fFactor) + m_nValue[EBaseAttr_Stamina];
	int nShuFa = (int)(thePlayerRole.GetData(CPlayerRole::TYPE_Intelligence) + fFactor) + m_nValue[EBaseAttr_Intelligence];
	
	if (uHeroID==INVALID_HERO_ID || uHeroID==0 || !pItemHero)
	{
		*m_pID_TEXT_LiLiang = nLiLiang;
		*m_pID_TEXT_MinJie = nMinJie;
		*m_pID_TEXT_TiZhi = nTiZhi;
		*m_pID_TEXT_ShuFa = nShuFa;
	}
	else
	{
		int addAttr[EBaseAttr_MaxSize];
		map<int,int> mapAttr;
		mapAttr.insert(map<int,int>::value_type(EBaseAttr_Strength,nLiLiang));
		mapAttr.insert(map<int,int>::value_type(EBaseAttr_Agility,nMinJie));
		mapAttr.insert(map<int,int>::value_type(EBaseAttr_Stamina,nTiZhi));
		mapAttr.insert(map<int,int>::value_type(EBaseAttr_Intelligence,nShuFa));
		for (int i=0;i<EBaseAttr_MaxSize;i++)
		{
			//addAttr[i] = mapAttr[i]/(1+pItemHero->heroAttr[i]*0.01)*pItemHero->heroAttr[i]*0.01;
			/*SBaseAttrType baseAttrValue = thePlayerRole.m_charinfo.baseinfo.baseProperty.baseAttr.baseAttrValue[i];
			addAttr[i] = baseAttrValue.final-baseAttrValue.nohero_final;*/
			addAttr[i] = pItemHero->heroAttr[i];
		}
#define Hero_Base_Add_Attr(BaseAttrType,finalAttr)  \
	addAttr[BaseAttrType]==0?MeSprintf_s( szInfo, sizeof(szInfo), "%d",finalAttr):MeSprintf_s( szInfo, sizeof(szInfo), "%d{#%x=(+%d)#}",finalAttr,dwColor,addAttr[BaseAttrType])
		
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",nLiLiang,addAttr[EBaseAttr_Strength]);
		Hero_Base_Add_Attr(EBaseAttr_Strength,nLiLiang);
		m_pID_TEXT_LiLiang->SetText(szInfo);
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",nMinJie,addAttr[EBaseAttr_Agility]);
		Hero_Base_Add_Attr(EBaseAttr_Agility,nMinJie);
		m_pID_TEXT_MinJie->SetText(szInfo);
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",nTiZhi,addAttr[EBaseAttr_Stamina]);
		Hero_Base_Add_Attr(EBaseAttr_Stamina,nTiZhi);
		m_pID_TEXT_TiZhi->SetText(szInfo);
		//MeSprintf_s( szInfo, sizeof(szInfo), "%d{#ffff0000=(+%d)#}",nShuFa,addAttr[EBaseAttr_Intelligence]);
		Hero_Base_Add_Attr(EBaseAttr_Intelligence,nShuFa);
		m_pID_TEXT_ShuFa->SetText(szInfo);

		/*SetHeroText(CPlayerRole::TYPE_Strength,nLiLiang-addAttr[EBaseAttr_Strength],addAttr[EBaseAttr_Strength]);
		SetHeroText(CPlayerRole::TYPE_Agility,nMinJie-addAttr[EBaseAttr_Agility],addAttr[EBaseAttr_Agility]);
		SetHeroText(CPlayerRole::TYPE_Stamina,nTiZhi-addAttr[EBaseAttr_Stamina],addAttr[EBaseAttr_Stamina]);
		SetHeroText(CPlayerRole::TYPE_Intelligence,nShuFa-addAttr[EBaseAttr_Intelligence],addAttr[EBaseAttr_Intelligence]);*/
		
	}
	
 
	//剩余点数
	*m_pID_TEXT_DianShu = (int)GetNoUseSkillPoint();

	//元素属性
	//破甲抗性
	*m_pID_TEXT_State1_1 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_BreakStrike);
	//破甲伤害
	int nBreakResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_BreakResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nBreakResist);
	m_pID_TEXT_State1_2->SetText(szInfo);
	//*m_pID_TEXT_State1_2 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_BreakResist);

	//贯穿抗性
	*m_pID_TEXT_State2_1 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_StabStrike);
	//贯穿伤害
	int nStabResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_StabResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nStabResist);
	m_pID_TEXT_State2_2->SetText(szInfo);
	//*m_pID_TEXT_State2_2 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_StabResist);

	//元素伤害
	*m_pID_TEXT_State3_1 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ElementStrike);
	//元素抗性
	int nElementResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ElementResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nElementResist);
	m_pID_TEXT_State3_2->SetText(szInfo);
	//*m_pID_TEXT_State3_2 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ElementResist);

	//毒素伤害
	*m_pID_TEXT_State4_1 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ToxinStrike);
	//毒素抗性
	int nToxinResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ToxinResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nToxinResist);
	m_pID_TEXT_State4_2->SetText(szInfo);
	//*m_pID_TEXT_State4_2 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_ToxinResist);

	//精神伤害
	*m_pID_TEXT_State5_1 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_SpiritStrike);
	//精神抗性
	int nSpiritResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_SpiritResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nSpiritResist);
	m_pID_TEXT_State5_2->SetText(szInfo);
	//*m_pID_TEXT_State5_2 = (int)thePlayerRole.GetData(CPlayerRole::TYPE_SpiritResist);

	//其他属性
	// 暴击伤害
	int nCRITICLEINTENSITY = (int)thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLEINTENSITY);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nCRITICLEINTENSITY);
	m_pID_TEXT_BaoJiBei->SetText(szInfo);
	//*m_pID_TEXT_BaoJiBei = ( int )thePlayerRole.GetData(CPlayerRole::TYPE_CRITICLEINTENSITY);
	//背袭强度
	int nBackStrike = (int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrike);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nBackStrike);
	m_pID_TEXT_BeiXi->SetText(szInfo);
	//m_pID_TEXT_BeiXi->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrike));
	//背袭抗性
	int nBackStrikeResist = (int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrikeResist);
	MeSprintf_s(szInfo,sizeof(szInfo),"%d%%",nBackStrikeResist);
	m_pID_TEXT_BeiXiKang->SetText(szInfo);
	//m_pID_TEXT_BeiXiKang->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_BackStrikeResist));
	//移动速度
	//char buf[32] = {0};
	//sprintf_s( buf, sizeof(buf)/sizeof(char) -1, "%.2f", (float)thePlayerRole.GetData(CPlayerRole::TYPE_MOVESPEED) );
	m_pID_TEXT_YiDong->SetText((int)thePlayerRole.GetData(CPlayerRole::TYPE_MOVESPEED));

	
	// 	//m_pID_TEXT_BulletText->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_BackStrikeResist));
	// 

// 	*m_pID_TEXT_MingZi = thePlayerRole.GetName();
 	*m_pID_TEXT_Level = thePlayerRole.GetLevel();
	//显示角色国家
	if (m_pID_PICTURE_WeiGuo && m_pID_PICTURE_ShuGuo && m_pID_PICTURE_WuGuo)
	{
		switch (thePlayerRole.GetCountry())
		{
		case CountryDefine::Country_LouLan:
			m_pID_PICTURE_WeiGuo->SetVisable(true);
			m_pID_PICTURE_ShuGuo->SetVisable(false);
			m_pID_PICTURE_WuGuo->SetVisable(false);
			break;
		case CountryDefine::Country_KunLun:
			m_pID_PICTURE_WeiGuo->SetVisable(false);
			m_pID_PICTURE_ShuGuo->SetVisable(true);
			m_pID_PICTURE_WuGuo->SetVisable(false);
			break;
		case CountryDefine::Country_DunHuang:
			m_pID_PICTURE_WeiGuo->SetVisable(false);
			m_pID_PICTURE_ShuGuo->SetVisable(false);
			m_pID_PICTURE_WuGuo->SetVisable(true);
			break;
		default:
			m_pID_PICTURE_WeiGuo->SetVisable(false);
			m_pID_PICTURE_ShuGuo->SetVisable(false);
			m_pID_PICTURE_WuGuo->SetVisable(false);
			break;
		}
	}
	
// 	
// 	CProfessionInfo *pInfo = GetSystemConfig()->GetProessionInfoFromID( thePlayerRole.GetProfession() );
//     if (pInfo)
//     {
//         *m_pID_TEXT_Job = pInfo->m_strProShow;
//     }
// 
// 	const SCharBaseInfo	*pBaseInfo = thePlayerRole.m_pBaseInfo;
// 	char szTemp[eMAX_TEMP_BUFF] = {0};
// 
//     // 生命和魔法值
//     __int64 nHp = thePlayerRole.GetData( CPlayerRole::TYPE_HP );
// 
//     __int64 nMp = thePlayerRole.GetData( CPlayerRole::TYPE_MP );
// 
// 
// 	// 生命上限
//  	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%I64u / %I64u", nHp, nMaxHp );
//  	*m_pID_TEXT_SHp = szTemp;
// 	m_pID_PROGRESS_Hp->SetMaxValue( nMaxHp );
// 	m_pID_PROGRESS_Hp->SetValue( nHp );
// 	// 法力上限
//  	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%I64u / %I64u", nMp, nMaxMp );
//  	*m_pID_TEXT_SMp = szTemp;
// 
// 	m_pID_PROGRESS_Mp->SetMaxValue( nMaxMp );
// 	m_pID_PROGRESS_Mp->SetValue( nMp );
//     // 换成Tip显示了。 2小时后，又改回来了……
//     //std::stringstream tipInfoAllInOne;
//     //tipInfoAllInOne << theXmlString.GetString(eTip_sAddHPMax) << ":" << nHp << "/" << nMaxHp << "\n";
//     switch( thePlayerRole.GetProfession() )
//     {
//     case EArmType_Warrior:
//         //tipInfoAllInOne << theXmlString.GetString( eText_Fp ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Fury->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     case EArmType_Mage:
//         //tipInfoAllInOne << theXmlString.GetString( eTip_sAddMPMax ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Mp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     case EArmType_Taoist:
//         //tipInfoAllInOne << theXmlString.GetString( eTip_sAddMPMax ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Mp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     case EArmType_Assassin:
//         //tipInfoAllInOne << theXmlString.GetString( eText_Ep ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Energy->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     case EArmType_Hunter:
//         //tipInfoAllInOne << theXmlString.GetString( eText_Ap ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Arrow->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     case EArmType_Sniper:
//         //tipInfoAllInOne << theXmlString.GetString( eText_Bp ) << ":" << nMp << "/" << nMaxMp << "\n";
//         //m_pID_PROGRESS_Arrow->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
//         break;
//     default:
//         break;
//     }
//     //m_pID_PROGRESS_Hp->setTipName( tipInfoAllInOne.str().c_str(), DT_LEFT );
// 








// 	*m_pID_TEXT_YuanChengGongJi = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.attackMagic.final;
// 	*m_pID_TEXT_YuanChengFangYu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.defendMagic.final;




	// 3免
// 	*m_pID_TEXT_JinChenJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateShort.final;
// 	*m_pID_TEXT_YuanChenJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateLong.final;
// 	*m_pID_TEXT_MoFaJianMian = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.derateMagic.final;
	// 回血
	//*m_pID_TEXT_HPHuiFu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.hpRestore.final;
	// 回魔
//*m_pID_TEXT_MPHuiFu = ( int )thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.energyRestore.final;
	// 移动速度
	//MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%.1f", thePlayerRole.m_pBaseInfo->baseProperty.fight.moveSpeed.final);

	// 4抗
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Coma ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistComa.final );
// 	m_pID_PICTURE_State1->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Dread ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistDread.final );
// 	m_pID_PICTURE_State2->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Silence ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSilence.final );
// 	m_pID_PICTURE_State3->setTip( szTemp );
// 	MeSprintf_s( szTemp, eMAX_TEMP_BUFF - 1, "%s %d", theXmlString.GetString( eTip_Resist_Slow ), 
// 		(int)thePlayerRole.m_pBaseInfo->baseProperty.fightAttr.resistSlow.final );
// 	m_pID_PICTURE_State4->setTip( szTemp );



// 	// 图形 暂无此功能
// 	m_nMaxValue = max( nLiLiang, 0 );
// 	m_nMaxValue = max( nMinJie, m_nMaxValue );
// 	m_nMaxValue = max( nTiZhi, m_nMaxValue );
// 	m_nMaxValue = max( nShuFa, m_nMaxValue );
// 
// 	if (m_nMaxValue > 0)
// 	{
// 		m_fLiLiangRate = ( float )( nLiLiang / m_nMaxValue );
// 		m_fMinJieRate = ( float )( nMinJie / m_nMaxValue );
// 		m_fTiZhiRate = ( float )( nTiZhi / m_nMaxValue );
// 		m_fShuFaRate = ( float )( nShuFa / m_nMaxValue );
// 	}
// 	else
// 	{
// 		m_fLiLiangRate = 0.0f;
// 		m_fMinJieRate = 0.0f;
// 		m_fTiZhiRate = 0.0f;
// 		m_fShuFaRate = 0.0f;
// 	}

}

void CUI_ID_FRAME_BaseProperty::RefreshExpProgress()
{
	if( !m_pID_FRAME_BaseProperty )
		return;

	// 经验条   
	int64 nCurExp = thePlayerRole.GetExpNotUsed();
	int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
	if( nCurExp < 0 )
		nCurExp = 0;

	__int64 nExpPercent = nCurExp * 1000 / nNeedExp;
	m_pID_PROGRESS_Exp->SetValue(nExpPercent);


	char szExp[128] = {0};
	MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "%I64u / %I64u" , nCurExp, nNeedExp );
	m_pID_TEXT_Exp->SetText(szExp);
}

void CUI_ID_FRAME_BaseProperty::SortControl()
{
	if( !m_pID_FRAME_BaseProperty )
		return;

	m_BaseGroup.Clear();
	m_BaseGroup.AddControl(m_pID_PICTURE_Base);
	m_BaseGroup.AddControl(m_pID_TEXT_DianShu);
	m_BaseGroup.AddControl(m_pID_BUTTON_Sure);
	m_BaseGroup.AddControl(m_pID_TEXT_ShuFa);
	m_BaseGroup.AddControl(m_pID_BUTTON_ShuFaAdd);
	m_BaseGroup.AddControl(m_pID_BUTTON_ShuFaMinus);
	m_BaseGroup.AddControl(m_pID_TEXT_TiZhi);
	m_BaseGroup.AddControl(m_pID_BUTTON_TiZhiAdd);
	m_BaseGroup.AddControl(m_pID_BUTTON_TiZhiMinus);
	m_BaseGroup.AddControl(m_pID_TEXT_MinJie);
	m_BaseGroup.AddControl(m_pID_BUTTON_MinJieAdd);
	m_BaseGroup.AddControl(m_pID_BUTTON_MinJieMinus);
	m_BaseGroup.AddControl(m_pID_TEXT_LiLiang);
	m_BaseGroup.AddControl(m_pID_BUTTON_LiLiangAdd);
	m_BaseGroup.AddControl(m_pID_BUTTON_LiLiangMinus);

	m_ElementGroup.Clear();
	m_ElementGroup.AddControl(m_pID_PICTURE_Element);
	m_ElementGroup.AddControl(m_pID_PICTURE_State5);
	m_ElementGroup.AddControl(m_pID_PICTURE_State4);
	m_ElementGroup.AddControl(m_pID_PICTURE_State3);
	m_ElementGroup.AddControl(m_pID_PICTURE_State2);
	m_ElementGroup.AddControl(m_pID_PICTURE_State1);
	m_ElementGroup.AddControl(m_pID_TEXT_State1_1);
	m_ElementGroup.AddControl(m_pID_TEXT_State1_2);
	m_ElementGroup.AddControl(m_pID_TEXT_State2_1);
	m_ElementGroup.AddControl(m_pID_TEXT_State2_2);
	m_ElementGroup.AddControl(m_pID_TEXT_State3_1);
	m_ElementGroup.AddControl(m_pID_TEXT_State3_2);
	m_ElementGroup.AddControl(m_pID_TEXT_State4_1);
	m_ElementGroup.AddControl(m_pID_TEXT_State4_2);
	m_ElementGroup.AddControl(m_pID_TEXT_State5_1);
	m_ElementGroup.AddControl(m_pID_TEXT_State5_2);

	m_OtherGroup.Clear();
	m_OtherGroup.AddControl(m_pID_PICTURE_Other);
	m_OtherGroup.AddControl(m_pID_TEXT_BaoJiBei);
	m_OtherGroup.AddControl(m_pID_TEXT_BeiXi);
	m_OtherGroup.AddControl(m_pID_TEXT_BeiXiKang);
	m_OtherGroup.AddControl(m_pID_TEXT_YiDong);

	m_EquipItemGroup.Clear();
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Head1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Symbol1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Armour1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Glove1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Temp11);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Shoe1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Necklace1);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Ring11);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Ring21);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Fabao1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Head);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Symbol);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Armour);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Glove);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Temp1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Shoe);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Necklace);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Ring1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Ring2);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Fabao);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_rWeapon);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_rWeapon1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_fWeapon);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_fWeapon1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_GangSkillBox);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Bangle1);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Bangle2);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Ring31);
	m_EquipItemGroup.AddControl(m_pID_PICTURE_Ring41);
	m_EquipItemGroup.AddControl(m_pID_LISTIMG_Weapon2);

	m_FashGroup.Clear();
	m_FashGroup.AddControl(m_pID_PICTURE_Fashion11);
	m_FashGroup.AddControl(m_pID_LISTIMG_Fashionarmour);

	//m_FashGroup.AddControl(m_pID_PICTURE_Fashion21);
	//m_FashGroup.AddControl(m_pID_LISTIMG_Fashion1);
	//m_FashGroup.AddControl(m_pID_LISTIMG_Fashion2);
}


int CUI_ID_FRAME_BaseProperty::GetNoUseSkillPoint()
{
	int nTotoal = 0;
	for (int i = 0;i < (int)EBaseAttr_MaxSize;++i)
		nTotoal += m_nValue[i];

	return thePlayerRole.GetData(CPlayerRole::TYPE_BasePotential) - nTotoal; 
}

void CUI_ID_FRAME_BaseProperty::ChangeProfession()
{
	if( !m_pID_FRAME_BaseProperty )
		return;

	m_pID_PICTURE_ZhanShi->SetVisable(false);
	m_pID_PICTURE_CiKe->SetVisable(false);
	m_pID_PICTURE_YueShi->SetVisable(false);
	m_pID_PICTURE_TianShi->SetVisable(false);
	m_pID_PICTURE_NuShou->SetVisable(false);

	switch( thePlayerRole.GetProfession() )
	{
	case EArmType_Warrior://戟
	    m_pID_PICTURE_ZhanShi->SetVisable(true);
		break;
	case EArmType_Mage://刀
	    m_pID_PICTURE_YueShi->SetVisable(true);
		break;
	case EArmType_Taoist://枪
		m_pID_PICTURE_TianShi->SetVisable(true);
		break;
	case EArmType_Assassin://剑
	   m_pID_PICTURE_CiKe->SetVisable(true);
		break;
	case EArmType_Hunter://舞
	    m_pID_PICTURE_NuShou->SetVisable(true);
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_BaseProperty::SetDianShuControlEnable(bool bEnable)
{
	if(!m_pID_FRAME_BaseProperty)
		return;

	m_pID_BUTTON_Sure->SetEnable(bEnable);
	m_pID_BUTTON_ShuFaAdd->SetEnable(bEnable);
	m_pID_BUTTON_ShuFaMinus->SetEnable(bEnable);
	m_pID_BUTTON_TiZhiAdd->SetEnable(bEnable);
	m_pID_BUTTON_TiZhiMinus->SetEnable(bEnable);
	m_pID_BUTTON_MinJieAdd->SetEnable(bEnable);
	m_pID_BUTTON_MinJieMinus->SetEnable(bEnable);
	m_pID_BUTTON_LiLiangAdd->SetEnable(bEnable);
	m_pID_BUTTON_LiLiangMinus->SetEnable(bEnable);
}

void CUI_ID_FRAME_BaseProperty::SetHeroText(CPlayerRole::enUpdataType enType, unsigned int originalData, unsigned int addData)
{
	std::stringstream finalstr;
	finalstr<<originalData<<"+"<<addData;
	switch (enType)
	{
	case CPlayerRole::TYPE_Strength:
		{
			m_pID_TEXT_LiLiang->SetText(finalstr.str());
			//m_pID_TEXT_LiLiang = finalstr.str();
		}
		break;
	case CPlayerRole::TYPE_Agility:
		{
			m_pID_TEXT_MinJie->SetText(finalstr.str());
			//m_pID_TEXT_MinJie = SetText(finalstr.str());
		}
		break;
	case CPlayerRole::TYPE_Stamina:
		{
			m_pID_TEXT_TiZhi->SetText(finalstr.str());
			//m_pID_TEXT_TiZhi = SetText(finalstr.str());
		}
		break;
	case CPlayerRole::TYPE_Intelligence:
		{
			m_pID_TEXT_ShuFa->SetText(finalstr.str());
			//m_pID_TEXT_ShuFa = SetText(finalstr.str());
		}
		break;
	default:
		return;
	}
}

bool CUI_ID_FRAME_BaseProperty::IsHeroSkillList(const ControlObject* pObject)
{
	return pObject==m_pID_LISTIMG_HeroSkill;
}

void CUI_ID_FRAME_BaseProperty::RefreshSuitAttr()
{
	if (!m_pID_TEXT_SuitAttr)
		return;

	m_pID_TEXT_SuitAttr->SetText("");
	m_pID_TEXT_SuitAttr->setShowTip(false);

	SCharItem* pVisual = /*thePlayerRole.m_pVisual->GetVisualArray();*/thePlayerRole.m_charinfo.visual.GetVisualArray();
	std::map< unsigned char, unsigned char  > starLevelCounter;   // 同星个数计数

	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		if (pVisual[i].itembaseinfo.ustItemID == InvalidLogicNumber)
			continue;
		if ( pVisual[i].equipdata.usHP <= 0.0f )
			continue;

		// 累计同星个数
		if ( pVisual[i].equipdata.ucLevel >= SStarActivation::EConstDefine_StarActivationStartLevel )
		{ 
			for( int j = SStarActivation::EConstDefine_StarActivationStartLevel ; j <= pVisual[i].equipdata.ucLevel; ++j )
			{
				starLevelCounter[j] += 1;
			}
		}
	}

	// 附加套装星激活属性
	for ( std::map< unsigned char, unsigned char  >::reverse_iterator it = starLevelCounter.rbegin(); it != starLevelCounter.rend(); ++it )
	{
		SStarActivation::SEffect* pEffect = theStarLevelUpConfig.GetStarActivationEffect( it->first, it->second );
		if ( !pEffect )
			continue;

		SuitAttrShow(it->first, pEffect->type, pEffect->value.fValue, pEffect->startCount);
		break;
	}
}

void CUI_ID_FRAME_BaseProperty::SuitAttrShow(uint8 level, uint8 type, float value, uint8 startCount)
{
	char temp[256] = {0};
	char buff[128] = {0};

	if( level <= 9 )
		sprintf_s( temp, sizeof(temp)/sizeof(char) -1, "#100%d", (int)level );
	else
		sprintf_s( temp, sizeof(temp)/sizeof(char) -1, "#130%d", (int)level - 10 );

	std::string strText(temp);
	ExpressionManager::GetInstance().AddExpressionAni( strText );
	m_pID_TEXT_SuitAttr->SetText(strText);

	memset(temp, 0, sizeof(temp));

	sprintf_s( temp, sizeof(temp)/sizeof(char) -1, theXmlString.GetString(eText_SuitAffect), (int)startCount, (int)level );

	std::string strtip(temp);

	strtip += S_IconInfoHero::GetRandStringByType( type );
	strtip += "+";
	strtip += itoa((int)value, buff, 10);

	m_pID_TEXT_SuitAttr->setShowTip(true);
	m_pID_TEXT_SuitAttr->setTip(strtip.c_str());
}

void CUI_ID_FRAME_BaseProperty::RefreshEquipScore()
{
	if ( !m_pID_TEXT_EquipScore )
		return;
	m_pID_TEXT_EquipScore->SetText("0");
	int nscore = 0;

	SCharItem* pVisual = thePlayerRole.m_charinfo.visual.GetVisualArray();
	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		if (pVisual[i].itembaseinfo.ustItemID == InvalidLogicNumber)
			continue;

		nscore +=(int)pVisual[i].equipdata.fScore;
	}

	m_pID_TEXT_EquipScore->SetText(nscore);
}