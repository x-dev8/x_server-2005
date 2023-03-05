/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\CLIENT\UI\SeekEquip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SeekEquip.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "target.h"
#include "SystemConfig.h"
#include "Pack.h"
#include "../cfg.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/RendererDx.h"
#include "Me3d/MoreAction.h"
#include "XmlStringLanguage.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "Common.h"
#include "me3d/ShaderManager.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/stdafx.h"
#include "wsRender.h"
#include "SeeBasePropertyBGFrame.h"
#include "ChatInfoBox.h"
#include "AddFriend.h"
#include "PlayerInfoMgr.h"

static int s_playerSex = 0;
static bool s_isShowHelmet = true;
static unsigned char s_nProfession = 0;
static int s_nHairColorIndex = 0;
static bool s_isShowHero = true;

CUI_ID_FRAME_SeekEqup s_CUI_ID_FRAME_SeekEqup;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SeekEqup, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SeekEqup, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_siliaoOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_addfriendOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_HeadOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_HeadOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_HeadOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ArmourOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ArmourOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rWeaponOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rWeaponOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rWeaponOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Temp1OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Temp1OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Temp1OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShoeOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShoeOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShoeOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AmuletOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AmuletOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AmuletOnIconLDBClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_17909OnButtonClick )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_SymbolOnIconDragOn )
// MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_SymbolOnIconDragOff )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_SymbolOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_GloveOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_GloveOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_GloveOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShieldOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShieldOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_ShieldOnIconLDBClick )

// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_TempOnIconDragOn )
// MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_TempOnIconDragOff )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_TempOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring1OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring1OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring1OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring2OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring2OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Ring2OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2OnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2OnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2OnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AccoutermentOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AccoutermentOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_AccoutermentOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_lWeaponOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_lWeaponOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_lWeaponOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_PACKOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_PACKOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_PACKOnIconLDBClick )

MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rubbishOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rubbishOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_rubbishOnIconLDBClick )

MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_LOCKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_UNLOCKOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_NecklaceOnIconDragOn )
MAP_ICON_DRAG_OFF_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_NecklaceOnIconDragOff )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_LISTIMG_NecklaceOnIconLDBClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_PetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_FashOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_BUTTON_Fash2OnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SeekEqup, ID_CHECKBOX_SelfInfoOnCheckBoxCheck )
CUI_ID_FRAME_SeekEqup::~CUI_ID_FRAME_SeekEqup()
{
	
}

CUI_ID_FRAME_SeekEqup::CUI_ID_FRAME_SeekEqup()
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_SeekEqup = NULL;
	ResetObjects();
	unguard;
}

void CUI_ID_FRAME_SeekEqup::ResetObjects()
{
	m_fRotateZ = 0.0f;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_LISTIMG_Head = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_LISTIMG_rWeapon = NULL;
	m_pID_LISTIMG_Weapon2 = NULL;
	m_pID_LISTIMG_Amulet = NULL;
	m_pID_LISTIMG_Temp1 = NULL;
	m_pID_LISTIMG_Shoe = NULL;
	/*m_pID_LISTIMG_Ring = NULL;*/
	//m_pID_LISTIMG_Symbol = NULL;
	m_pID_LISTIMG_Glove = NULL;
	m_pID_LISTIMG_Shield = NULL;
	m_pID_LISTIMG_Temp = NULL;
	m_pID_LISTIMG_Accouterment1 = NULL;
	m_pID_LISTIMG_Ring1 = NULL;
	m_pID_LISTIMG_Ring2 = NULL;
	m_pID_LISTIMG_Bangle1 = NULL;
	m_pID_LISTIMG_Bangle2 = NULL;
	m_pID_LISTIMG_Accouterment = NULL;
	m_pID_LISTIMG_lWeapon = NULL;
	m_pID_LISTIMG_Necklace = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	//m_pID_LISTIMG_Fashionhead = NULL;
	m_pID_LISTIMG_Fashionarmour = NULL;
	//m_pID_LISTIMG_Fashionglove = NULL;
	//m_pID_LISTIMG_Fashionshoe = NULL;
	m_pID_BUTTON_Pet = NULL;
	m_pID_TEXT_MingZi = NULL;
	m_pID_TEXT_ZDengJi = NULL;
	m_pID_TEXT_DengJi = NULL;
	m_pID_TEXT_ZZhiYe = NULL;
	m_pID_TEXT_ZhiYe = NULL;
	m_pID_LISTIMG_GangRing = NULL;
	m_pID_LISTIMG_GangSkillBox = NULL;
	m_pID_PICTURE_Fashion11 = NULL;
	m_pID_PICTURE_rWeapon1 = NULL;
	m_pID_PICTURE_fWeapon1 = NULL;
	//m_pID_TEXT_DBID = NULL;
	
	m_DestPlayerId = -1;
	m_DestPlayer = NULL;
	m_bRotate = false;
	m_pID_CHECKBOX_Zhuangbei = NULL;
	m_pID_CHECKBOX_SelfInfo	 = NULL;
	m_pID_BUTTON_siliao		 = NULL;
	m_pID_BUTTON_addfriend	 = NULL;
	m_BaseGroup.Clear();
	//m_EquipItemGroup.Clear();
	m_pID_TEXT_EquipScore = NULL;
}
// Frame
bool CUI_ID_FRAME_SeekEqup::OnFrameRun()
{
	if( !IsVisable() )
		return true;
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
	return true;
}
bool CUI_ID_FRAME_SeekEqup::OnFrameRender()
{
	guardfunc;
	RECT rc;
	m_pID_FRAME_SeekEqup->GetRealRect( &rc );

	CViewportConfig *viewportCfg = GetSystemConfig()->GetTargetPackViewportCfg();
	RenderAnim_Update(
		rc.left + viewportCfg->m_fX * ControlObject::GetSCALE(m_pID_FRAME_SeekEqup),
		rc.top + viewportCfg->m_fY * ControlObject::GetSCALE(m_pID_FRAME_SeekEqup),
		viewportCfg->m_fWidth * ControlObject::GetSCALE(m_pID_FRAME_SeekEqup),
		viewportCfg->m_fHeight * ControlObject::GetSCALE(m_pID_FRAME_SeekEqup),
		D3DXVECTOR3(0, -11, 0));

	float scale = 0.0;
	if (theHeroGame.GetPlayerMgr()->GetMe()->GetSex() == Sex_Male)
		scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleMale;
	else
		scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleFemale;
	RenderAnim(D3DXVECTOR3(0, 0, -2.5136), scale);

	return true;
	unguard;
}

BOOL CUI_ID_FRAME_SeekEqup::InitCamera()
{
	guardfunc;
	FLOAT fAspect = ((FLOAT)200.0f) / 300.0f;
	m_Camera.SetProjParams( D3DX_PI*(30/45.0f)/4, fAspect, 1.0f, 220.0f );

	m_ViewPort.X = 0;
	m_ViewPort.Y = 0;
	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinZ = 0;
	m_ViewPort.MaxZ = 1;

	return TRUE;
	unguard;
}

void CUI_ID_FRAME_SeekEqup::UpdataEquipView()
{
	guardfunc;
	if( !m_pID_FRAME_SeekEqup )
		return;
	if( RenderAnim_GetPlayer()->GetAnim() )
	{
		/*CPlayer_SEquipment equip[ EEquipPartType_MaxEquitPart ];*/
		/*memcpy( &equip, m_equips, sizeof(CPlayer_SEquipment)* EEquipPartType_MaxEquitPart);*/

        //bool showHelmet = s_isShowHelmet || m_isShowFashion;
		RenderAnim_GetPlayer()->GetAnim()->ChangeSkeletonAndEquipAll(
			&m_equips,
			s_playerSex,
			s_nProfession,
			s_nHairColorIndex,
            s_isShowHelmet, m_isShowFashion,0,m_DestPlayer->GetHeroID(),s_isShowHero);
		RenderAnim_GetPlayer()->GetAnim()->SetPosition( 0.0f, 0.0f, 0.0f );

		if( m_equips[eKeyAll_RHandItem].item.itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			RenderAnim_GetPlayer()->GetAnim()->ChangeWeaponAnim( RenderAnim_GetPlayer()->GetAnim()->GetWeaponActionModelId( s_nProfession, s_playerSex ));

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
		uint16 stVisualItemID[EEquipPartType_MaxEquitPart];
		uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart];
		uint8 equipLevel[EEquipPartType_MaxEquitPart];
		uint8 equipElements[EEquipPartType_MaxEquitPart];
		/*for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			stVisualItemID[i] = m_equips[i].item.itembaseinfo.ustItemID;
			equipIntensifyTime[i] = m_equips[i].item.equipdata.gemHoleCount;
			equipLevel[i] = m_equips[i].item.equipdata.ucLevel;
			equipElements[i] = m_equips[i].item.itembaseinfo.value1;
		}*/
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			int nPart = CEquipPartMap::Instance()->GetLogicPart(i);
			stVisualItemID[i] = m_equips[nPart].item.itembaseinfo.ustItemID;
			equipIntensifyTime[i] = m_equips[nPart].item.equipdata.gemHoleCount;
			equipLevel[i] = m_equips[nPart].item.equipdata.ucLevel;
			equipElements[i] = m_equips[nPart].item.itembaseinfo.value1;
		}
		RenderAnim_GetPlayer()->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
		RenderAnim_GetPlayer()->UpdateBones();
	}
	unguard;
}

// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_HeadOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_HeadOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_HeadOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ArmourOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rWeaponOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItemDrag,
														   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rWeaponOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rWeaponOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Temp1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Temp1OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Temp1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShoeOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShoeOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShoeOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_RingOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//														ControlIconDrag::S_ListImg* pItemDrag,
//														ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_RingOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
//														 ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_RingOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_17909OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return true;
}
// ListImg / ListEx
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_SymbolOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//														  ControlIconDrag::S_ListImg* pItemDrag,
//														  ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_SymbolOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
//														   ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_SymbolOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_GloveOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_GloveOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_GloveOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShieldOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShieldOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_ShieldOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_TempOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//														ControlIconDrag::S_ListImg* pItemDrag,
//														ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_TempOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
//														 ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_TempOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return false;
//	return false;
//}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Accouterment1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItemDrag,
																 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Accouterment1OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Accouterment1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring1OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring2OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Ring2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle1OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle2OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Bangle2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AmuletOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AmuletOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AmuletOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Weapon2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Weapon2OnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_Weapon2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AccoutermentOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AccoutermentOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
																 ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_AccoutermentOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_lWeaponOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItemDrag,
														   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_lWeaponOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_lWeaponOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_PACKOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_PACKOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_PACKOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rubbishOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														   ControlIconDrag::S_ListImg* pItemDrag,
														   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rubbishOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_rubbishOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_LOCKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_UNLOCKOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_NecklaceOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_NecklaceOnIconDragOff( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
bool CUI_ID_FRAME_SeekEqup::ID_LISTIMG_NecklaceOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	m_bRotate = false;
	return true;
}
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_PetOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	GameObjectId TargetPlayID = m_DestPlayerId;
	CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByID( TargetPlayID );
	if( pPlayer )
	{
		if( pPlayer->GetMonsterType() == eMT_IllusionMonster )
		{
			GameObjectId MasterPlayID = pPlayer->GetMasterID();
			CPlayer* pMasterPlayer = theHeroGame.GetPlayerMgr()->FindByID( MasterPlayID );

			if( pMasterPlayer )
				TargetPlayID = MasterPlayID;
			else
				return false;
		}

		MsgWantPeek msg;
		msg.type = MsgWantPeek::EPT_Mount;
		msg.stTargetID = TargetPlayID;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
}
// Button
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_FashOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	m_isShowFashion = true;
	UpdataEquipView();
	m_pID_BUTTON_Fash->SetVisable(false);
	m_pID_BUTTON_Fash2->SetVisable(true);
	return true;
}
bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_Fash2OnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_SeekEqup )
		return false;
	m_isShowFashion = false;
	UpdataEquipView();
	m_pID_BUTTON_Fash->SetVisable(true);
	m_pID_BUTTON_Fash2->SetVisable(false);
	return true;
}
bool CUI_ID_FRAME_SeekEqup::UISeekEquip_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SeekEqup.m_bRotate = true;
	return true;
}

bool CUI_ID_FRAME_SeekEqup::UISeekEquip_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_SeekEqup.m_bRotate = true;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SeekEqup::_LoadUI()
{
	guardfunc;
	RenderAnim_Create(CUIRenderAnim::RTWUI_TARGET_VIEW);
    RenderAnim_GetPlayer()->GetAnim()->EnableChildrenUpdateAndRender( false );

	int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
	if( nIndex >= 0 )
	{
		RenderAnim_GetPlayer()->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
	}

	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\SeekEquip.meui", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\SeekEquip.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_SeekEqup::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_SeekEqup, s_CUI_ID_FRAME_SeekEqupOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SeekEqup, s_CUI_ID_FRAME_SeekEqupOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SeekEqupID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_Pet, s_CUI_ID_FRAME_SeekEqupID_BUTTON_PetOnButtonClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Head, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_HeadOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Head, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_HeadOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ArmourOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Armour, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ArmourOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_rWeapon, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_rWeaponOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_rWeapon, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_rWeaponOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Weapon2OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Weapon2OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Temp1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Temp1OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Temp1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Temp1OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Shoe, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ShoeOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Shoe, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ShoeOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Ring1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring1OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Ring1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring1OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Ring2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring2OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Ring2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring2OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Bangle1OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Bangle1OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Bangle2OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_AmuletOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_AmuletOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Bangle2OnIconLDBClick );

	//theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_SymbolOnIconDragOn );

	//theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_SymbolOnIconLDBClick );*/

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Glove, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_GloveOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Glove, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_GloveOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Shield, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ShieldOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Shield, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_ShieldOnIconLDBClick );

	/*theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Temp, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_TempOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Temp, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_TempOnIconLDBClick );*/

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Accouterment1OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Accouterment1OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Ring1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring1OnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Ring1, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_Ring1OnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_AccoutermentOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_AccoutermentOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_lWeapon, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_lWeaponOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_lWeapon, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_lWeaponOnIconLDBClick );

	theUiManager.OnIconDragOn( ID_FRAME_SeekEqup, ID_LISTIMG_Necklace, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_NecklaceOnIconDragOn );

	theUiManager.OnIconLDBClick( ID_FRAME_SeekEqup, ID_LISTIMG_Necklace, s_CUI_ID_FRAME_SeekEqupID_LISTIMG_NecklaceOnIconLDBClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_Right, s_CUI_ID_FRAME_SeekEqupID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_Left, s_CUI_ID_FRAME_SeekEqupID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_Fash, s_CUI_ID_FRAME_SeekEqupID_BUTTON_FashOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_Fash2, s_CUI_ID_FRAME_SeekEqupID_BUTTON_Fash2OnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_siliao, s_CUI_ID_FRAME_SeekEqupID_BUTTON_siliaoOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SeekEqup, ID_BUTTON_addfriend, s_CUI_ID_FRAME_SeekEqupID_BUTTON_addfriendOnButtonClick);
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeekEqup, ID_CHECKBOX_Zhuangbei, s_CUI_ID_FRAME_SeekEqupID_CHECKBOX_ZhuangbeiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SeekEqup, ID_CHECKBOX_SelfInfo, s_CUI_ID_FRAME_SeekEqupID_CHECKBOX_SelfInfoOnCheckBoxCheck );

	m_pID_FRAME_SeekEqup = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SeekEqup );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_BUTTON_CLOSE );
	m_pID_LISTIMG_Head = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Head );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Armour );
	m_pID_LISTIMG_rWeapon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_rWeapon );
	m_pID_LISTIMG_Weapon2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Weapon2);
	m_pID_LISTIMG_Amulet = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Amulet);
	m_pID_LISTIMG_Temp1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Temp1 );
	m_pID_LISTIMG_Shoe = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Shoe );
	
	//m_pID_LISTIMG_Symbol = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Symbol );
	m_pID_LISTIMG_Glove = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Glove );
	m_pID_LISTIMG_Shield = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Shield );
	m_pID_LISTIMG_Temp = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Temp );
	m_pID_LISTIMG_Accouterment1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment1 );
	m_pID_LISTIMG_Ring1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Ring1 );
	m_pID_LISTIMG_Ring2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Ring2 );
	m_pID_LISTIMG_Bangle1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle1 );
	m_pID_LISTIMG_Bangle2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Bangle2 );
	m_pID_LISTIMG_Accouterment = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Accouterment );
	m_pID_LISTIMG_lWeapon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_lWeapon );
	m_pID_LISTIMG_Necklace = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Necklace );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_BUTTON_Left );
	m_pID_BUTTON_Pet = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_BUTTON_Pet );
	//m_pID_LISTIMG_Fashionhead = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Fashionhead );
	m_pID_LISTIMG_Fashionarmour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Fashionarmour );
	//m_pID_LISTIMG_Fashionglove = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Fashionglove );
	//m_pID_LISTIMG_Fashionshoe = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_Fashionshoe );
	m_pID_TEXT_MingZi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_MingZi );
	m_pID_TEXT_ZDengJi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_ZDengJi );
	m_pID_TEXT_DengJi = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_DengJi );
	m_pID_TEXT_ZZhiYe = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_ZZhiYe );
	m_pID_TEXT_ZhiYe = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_ZhiYe );
	m_pID_LISTIMG_GangRing = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_GangRing );
	m_pID_LISTIMG_GangSkillBox = (ControlListImage*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_LISTIMG_GangSkillBox );
	m_pID_BUTTON_siliao = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_BUTTON_siliao);
	m_pID_BUTTON_addfriend = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_BUTTON_addfriend);
	m_pID_CHECKBOX_Zhuangbei = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_CHECKBOX_Zhuangbei);
	m_pID_CHECKBOX_SelfInfo = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_CHECKBOX_SelfInfo);
	m_pID_BUTTON_Fash = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_BUTTON_Fash);
	m_pID_BUTTON_Fash2 = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup,ID_BUTTON_Fash2);
	m_pID_PICTURE_Fashion11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_PICTURE_Fashion11 );
	m_pID_PICTURE_rWeapon1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_PICTURE_rWeapon1 );
	m_pID_PICTURE_fWeapon1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_PICTURE_fWeapon1 );
	m_pID_TEXT_EquipScore = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_EquipScore );

	//m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_BUTTON_help );
	//m_pID_TEXT_DBID = (ControlText*)theUiManager.FindControl( ID_FRAME_SeekEqup, ID_TEXT_DBID );
	/*assert( m_pID_FRAME_SeekEqup );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_LISTIMG_Head );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_LISTIMG_rWeapon );
	assert( m_pID_LISTIMG_Temp1 );
	assert( m_pID_LISTIMG_Shoe );
	assert( m_pID_LISTIMG_Symbol );
	assert( m_pID_LISTIMG_Glove );
	assert( m_pID_LISTIMG_Shield );
	assert( m_pID_LISTIMG_Temp );
	assert( m_pID_LISTIMG_Accouterment1 );
	assert( m_pID_LISTIMG_Ring1 );
	assert( m_pID_LISTIMG_Accouterment );
	assert( m_pID_LISTIMG_lWeapon );
	assert( m_pID_LISTIMG_Fashionhead );
	assert( m_pID_LISTIMG_Fashionarmour );
	assert( m_pID_LISTIMG_Fashionglove );
	assert( m_pID_LISTIMG_Fashionshoe );
	assert( m_pID_LISTIMG_Necklace );
	assert( m_pID_BUTTON_Pet );
	assert( m_pID_TEXT_MingZi );
	assert( m_pID_TEXT_ZDengJi );
	assert( m_pID_TEXT_DengJi );
	assert( m_pID_TEXT_ZZhiYe );
	assert( m_pID_TEXT_ZhiYe );
	assert( m_pID_BUTTON_help );
	assert( m_pID_TEXT_DBID );*/
	assert(m_pID_BUTTON_siliao);
	assert(m_pID_BUTTON_addfriend);
	assert(m_pID_CHECKBOX_Zhuangbei);
	assert(m_pID_CHECKBOX_SelfInfo);
	assert( m_pID_PICTURE_Fashion11 );
	assert( m_pID_PICTURE_rWeapon1 );
	assert( m_pID_PICTURE_fWeapon1 );
	assert( m_pID_TEXT_EquipScore );
	InitCamera();

	//m_pID_BUTTON_help->SetButtonClickFun( helpOnClick );
	m_pID_FRAME_SeekEqup->SetFather(s_CUI_ID_FRAME_SeeBasePropertyBGFrame.GetFrame());
	m_pID_BUTTON_Right->SetLButtonDownFun(UISeekEquip_RightLBD);
	m_pID_BUTTON_Left->SetLButtonDownFun(UISeekEquip_LeftLBD);
	SortGroup();
	SetVisable(FALSE);
	return true;
	unguard;
}
bool CUI_ID_FRAME_SeekEqup::helpOnClick( ControlObject* pSender )
{
	guardfunc;
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_SeekEqup::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_SeekEqup = NULL;
	ResetObjects();

	RenderAnim_Destroy();
	return theUiManager.RemoveFrame( "data\\ui\\SeekEquip.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_SeekEqup::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_SeekEqup )
		return false;
	return m_pID_FRAME_SeekEqup->IsVisable();
	unguard;
}


bool CUI_ID_FRAME_SeekEqup::ClearListImg()
{	
	guardfunc;
	if( !m_pID_FRAME_SeekEqup )
		return false;
	m_pID_LISTIMG_rWeapon->Clear();
	m_pID_LISTIMG_Head->Clear();
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Shoe->Clear();
	m_pID_LISTIMG_Glove->Clear();
	m_pID_LISTIMG_Necklace->Clear();
	m_pID_LISTIMG_Ring1->Clear();
	m_pID_LISTIMG_Ring2->Clear();
	m_pID_LISTIMG_Bangle1->Clear();
	m_pID_LISTIMG_Bangle2->Clear();
	m_pID_LISTIMG_Amulet->Clear();
	m_pID_LISTIMG_Weapon2->Clear();
	m_pID_LISTIMG_Accouterment->Clear();
	m_pID_LISTIMG_Accouterment1->Clear();
	m_pID_LISTIMG_Temp->Clear();
	m_pID_LISTIMG_Temp1->Clear();
	m_pID_LISTIMG_GangRing->Clear();
	m_pID_LISTIMG_GangSkillBox->Clear();

	//m_pID_LISTIMG_Symbol->Clear();
	m_pID_LISTIMG_Shield->Clear();

	//m_pID_LISTIMG_Fashionhead->Clear();
	m_pID_LISTIMG_Fashionarmour->Clear();
	//m_pID_LISTIMG_Fashionglove->Clear();
	//m_pID_LISTIMG_Fashionshoe->Clear();
	if ( m_pID_TEXT_EquipScore )
		m_pID_TEXT_EquipScore->SetText("0");
	return true;
	unguard;
}

// 设置是否可视
void CUI_ID_FRAME_SeekEqup::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_SeekEqup )
		return;
	m_pID_FRAME_SeekEqup->SetVisable( bVisable );

	if( bVisable )
	{
		m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
		m_pID_CHECKBOX_SelfInfo->SetCheck(false);
		m_BaseGroup.SetVisible(true);
		m_pID_LISTIMG_Fashionarmour->SetVisable(false);
		m_isShowFashion = false;

		m_pID_BUTTON_Fash->SetVisable(true);
		m_pID_BUTTON_Fash2->SetVisable(false);
		m_pID_PICTURE_Fashion11->SetVisable(false);
	}
	else
	{
		m_BaseGroup.SetVisible(false);
		m_DestPlayerId = -1;
	}
	unguard;
}

//设定 所有的装备
//void CUI_ID_FRAME_SeekEqup::InitChangeSkeletonAndEquipAll(int iSex, SCharItem pItem[])
//{
//	ItemDefine::SItemCommon *pItemCommon = NULL;
//	for(int iLoop = 0 ; iLoop < EEquipPartType_MaxEquitPart; iLoop ++,pEquip ++,pItem ++)
//	{
//		pEquip->item = *pItem;
//
//		pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
//		if( !pItemCommon )
//		{			
//			pEquip->iModelID = InvalidLogicNumber;
//			pEquip->iModelID2 = InvalidLogicNumber;
//			pEquip->iModelID3 = InvalidLogicNumber;
//			continue;
//		}
//		switch( pItemCommon->ucItemType ) 
//		{
//		case ItemDefine::ITEMTYPE_WEAPON:
//			{
//				ItemDefine::SItemWeapon *pItemCanEquip = NULL;
//				pItemCanEquip = ( ItemDefine::SItemWeapon *) pItemCommon;
//				pEquip->iModelID  = pItemCanEquip->ustModelID[0];
//				pEquip->iModelID2  = pItemCanEquip->ustModelID[1];
//				pEquip->iModelID3 = pItemCanEquip->ustIdleModelID;
//			}
//			break;
//		case ItemDefine::ITEMTYPE_ARMOUR:
//			{
//				ItemDefine::SItemArmour *pItemCanEquip = NULL;
//				pItemCanEquip = ( ItemDefine::SItemArmour *) pItemCommon;
//
//				int nProfessionIndex=0;
//				for ( nProfessionIndex=0; nProfessionIndex<EArmType_MaxSize; nProfessionIndex++ )
//				{
//					if ( pItemCanEquip->ustModelID[nProfessionIndex][iSex][0] != 
//						InvalidLogicNumber 
//						|| pItemCanEquip->ustModelID[nProfessionIndex][iSex][1] != 
//						InvalidLogicNumber 
//						)
//					{
//						break;
//					}
//				}
//				pEquip->iModelID  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][0];
//				pEquip->iModelID2  = pItemCanEquip->ustModelID[nProfessionIndex][iSex][1];
//				pEquip->iModelID3 = InvalidLogicNumber;
//			}
//			break;
//		default:
//			pEquip->iModelID = InvalidLogicNumber;
//			pEquip->iModelID2  = InvalidLogicNumber;
//			pEquip->iModelID3  = InvalidLogicNumber;
//			break;
//		}
//	}
//}

//void CUI_ID_FRAME_SeekEqup::SetChangeSkeletonAndEquipAll(SCharItem equips[])
//{
//	if( !m_pID_FRAME_SeekEqup )
//		return;
//
//	m_isShowFashion = false;
//    m_pID_TEXT_MingZi->SetText("");
//    m_pID_TEXT_DengJi->SetText("");
//    m_pID_TEXT_ZhiYe->SetText("");
//
//	CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_DestPlayerId );
//	if( DestPlayer )
//	{
//		s_isShowHelmet = DestPlayer->IsShowHelmet();
//		s_playerSex = DestPlayer->GetSex();
//		s_nProfession = DestPlayer->GetProfession();
//		s_nHairColorIndex = DestPlayer->GetHairColorIndex();
//
//        m_pID_TEXT_MingZi->SetText(DestPlayer->GetName());
//        m_pID_TEXT_DengJi->SetText(DestPlayer->GetLevel());
//
//		switch( s_nProfession )
//        {
//        case EArmType_Warrior:
//            m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Warrior));
//            break;
//        case EArmType_Assassin:
//            m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Assassin));
//            break;
//        case EArmType_Mage:
//            m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Mage));
//            break;
//        case EArmType_Taoist:
//            m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Taoist));
//            break;
//        case EArmType_Hunter:
//            m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Hunter));
//            break;
//        }
//	}
//
//	InitChangeSkeletonAndEquipAll(DestPlayer->GetSex(), equips);
//
//	//清理ImgList
//	ClearListImg();
//
//	ControlIconDrag::S_ListImg stItem;
//	stItem.SetData( &equips[EEquipPartType_Weapon], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId );
//	if ( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_rWeapon->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_WeaponMinor], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId );
//	if ( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Weapon2->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Armour], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if ( !stItem.IsNull() )
//	{
//		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( equips[eKeyAll_Armour].itembaseinfo.ustItemID );
//		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//		{
//			ItemDefine::SItemArmour* pArmour = ( ItemDefine::SItemArmour* )pCommon;
//			if( pArmour->bFashion )
//				m_pID_LISTIMG_Fashionarmour->SetItem( &stItem , 0 );
//			else
//				m_pID_LISTIMG_Armour->SetItem( &stItem, 0 );
//		}		
//	}
//	stItem.SetData( &equips[EEquipPartType_Glove], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if ( !stItem.IsNull() )
//	{
//		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( equips[eKeyAll_Glove].itembaseinfo.ustItemID );
//		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//		{
//			ItemDefine::SItemArmour* pArmour = ( ItemDefine::SItemArmour* )pCommon;
//			m_pID_LISTIMG_Glove->SetItem( &stItem, 0 );
//		}	
//
//	}
//	stItem.SetData( &equips[EEquipPartType_Shoe], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if ( !stItem.IsNull() )
//	{
//		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( equips[eKeyAll_Shoe].itembaseinfo.ustItemID );
//		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//		{
//			ItemDefine::SItemArmour* pArmour = ( ItemDefine::SItemArmour* )pCommon;
//				m_pID_LISTIMG_Shoe->SetItem( &stItem, 0 );
//		}			
//	}
//	stItem.SetData( &equips[EEquipPartType_Necklace], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if ( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Necklace->SetItem( &stItem, 0 );
//	}
//	stItem.SetData( &equips[EEquipPartType_Ring1], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Ring1->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Ring2], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Ring2->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Bangle1], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Bangle1->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Bangle2], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Bangle2->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_LeaderCard], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		m_pID_LISTIMG_Accouterment1->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Helmet], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( equips[EEquipPartType_Helmet].itembaseinfo.ustItemID );
//		if( pCommon && pCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//		{
//			ItemDefine::SItemArmour* pArmour = ( ItemDefine::SItemArmour* )pCommon;
//				m_pID_LISTIMG_Head->SetItem( &stItem, 0 );
//		}		
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Sash], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		if( m_pID_LISTIMG_Temp1 )		
//			m_pID_LISTIMG_Temp1->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Badge], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		if( m_pID_LISTIMG_GangRing )		
//			m_pID_LISTIMG_GangRing->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_Manteau], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		if( m_pID_LISTIMG_GangSkillBox )		
//			m_pID_LISTIMG_GangSkillBox->SetItem( &stItem, 0 );
//	}
//
//	stItem.SetData( &equips[EEquipPartType_AecorativeClothing], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
//	if( !stItem.IsNull() )
//	{
//		if( m_pID_LISTIMG_Fashionarmour )		
//			m_pID_LISTIMG_Fashionarmour->SetItem( &stItem, 0 );
//	}
//
//	UpdataEquipView();
//}

//------------------------------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_SeekEqup::OnSeekEquip(Msg* pMsg_)
{	
	//s_CUI_ID_FRAME_SeekEqup.SetVisable(true);
	CHECK_MSGLEN( pMsg_, MsgPeekEquip);
	MsgPeekEquip *pMsg = (MsgPeekEquip*)pMsg_;

	CPlayer* DestPlayer = theHeroGame.GetPlayerMgr()->FindByID(pMsg->playerId);
	s_isShowHelmet = DestPlayer->IsShowHelmet();
	s_playerSex = DestPlayer->GetSex();
	s_nProfession = DestPlayer->GetProfession();
	s_nHairColorIndex = DestPlayer->GetHairColorIndex();
	s_isShowHero = DestPlayer->IsSHowHero();


	m_DestPlayerId = pMsg->playerId;
	
	for (int i = 0; i < eKeyAll_Max; ++i)
	{
		m_equips[i].Reset();
	}
	m_DestPlayer = DestPlayer;

	PlayerInfoMgr::Instance()->SetPlayerFaceAndHair(DestPlayer, pMsg->faceId, pMsg->hairId,
		m_equips[eKeyAll_Face].iModelID, m_equips[eKeyAll_Hair].iModelID);
	
	SetAllEquip(pMsg->playerequipitem);

	SetAllIconItem(pMsg);
	UpdataEquipView();
}

void CUI_ID_FRAME_SeekEqup::SetAllEquip(SCharItem EquipItem[EEquipPartType_MaxEquitPart])
{
	if (!EquipItem)
	{
		return;
	}
	ItemDefine::SItemCommon *pItemCommon = NULL;
	for(int i = 0 ; i < EEquipPartType_MaxEquitPart; ++i)
	{
		int j = CEquipPartMap::Instance()->GetLogicPart(i);
		m_equips[j].item = EquipItem[i];
		m_equips[j].iModelID = InvalidLogicNumber;
		m_equips[j].iModelID2 = InvalidLogicNumber;
		m_equips[j].iModelID3 = InvalidLogicNumber;
		pItemCommon = GettheItemDetail().GetItemByID(EquipItem[i].itembaseinfo.ustItemID);
		if(!pItemCommon)
		{			
			continue;
		}
		m_equips[j].item.itembaseinfo.ustItemID = EquipItem[i].itembaseinfo.ustItemID;

		switch( pItemCommon->ucItemType ) 
		{
		case ItemDefine::ITEMTYPE_WEAPON:
			{
				ItemDefine::SItemWeapon *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemWeapon *) pItemCommon;
				m_equips[j].iModelID  = pItemCanEquip->ustModelID[0];
				m_equips[j].iModelID2  = pItemCanEquip->ustModelID[1];
				m_equips[j].iModelID3 = pItemCanEquip->ustIdleModelID;
			}
			break;
		case ItemDefine::ITEMTYPE_ARMOUR:
			{
				ItemDefine::SItemArmour *pItemCanEquip = NULL;
				pItemCanEquip = ( ItemDefine::SItemArmour *) pItemCommon;
				m_equips[j].iModelID  = pItemCanEquip->ustModelID[s_nProfession][s_playerSex][0];
				m_equips[j].iModelID2  = pItemCanEquip->ustModelID[s_nProfession][s_playerSex][1];
				m_equips[j].iModelID3 = InvalidLogicNumber;
			}
			break;
		default:
			break;
		}
	}

}

void CUI_ID_FRAME_SeekEqup::SetAllIconItem(MsgPeekEquip *pMsg)
{
	if (!pMsg)
	{
		return;
	}

	CPlayer *DestPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_DestPlayerId );
	if( DestPlayer )
	{
		m_pID_TEXT_MingZi->SetText(DestPlayer->GetName());
		m_pID_TEXT_DengJi->SetText(DestPlayer->GetLevel());

		switch( s_nProfession )
		{
		case EArmType_Warrior:
			m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Warrior));
			break;
		case EArmType_Assassin:
			m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Assassin));
			break;
		case EArmType_Mage:
			m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Mage));
			break;
		case EArmType_Taoist:
			m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Taoist));
			break;
		case EArmType_Hunter:
			m_pID_TEXT_ZhiYe->SetText(theXmlString.GetString(eProfession_Hunter));
			break;
		}
	}

	//清理ImgList
	ClearListImg();

	ControlIconDrag::S_ListImg stItem;
    stItem.m_pkIconInfo->SetUsableEffEnable( false );
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Weapon], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId );
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_rWeapon->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_WeaponMinor], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId );
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Weapon2->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Armour], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Armour->SetItem( &stItem, 0 );
	}
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Glove], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Glove->SetItem( &stItem, 0 );
	}
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Shoe], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Shoe->SetItem( &stItem, 0 );
	}
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Necklace], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if ( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Necklace->SetItem( &stItem, 0 );
	}
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Ring1], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Ring1->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Ring2], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Ring2->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Bangle1], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Bangle1->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Bangle2], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Bangle2->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_LeaderCard], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Accouterment1->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Helmet], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		m_pID_LISTIMG_Head->SetItem( &stItem, 0 );
	}
	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Sash], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		if( m_pID_LISTIMG_Temp1 )		
			m_pID_LISTIMG_Temp1->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Badge], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		if( m_pID_LISTIMG_GangRing )		
			m_pID_LISTIMG_GangRing->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_Shoulder], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		if( m_pID_LISTIMG_GangSkillBox )		
			m_pID_LISTIMG_GangSkillBox->SetItem( &stItem, 0 );
	}

	stItem.SetData( &pMsg->playerequipitem[EEquipPartType_AecorativeClothing], eIcon_Enable, eTipFlag_Normal, false, m_DestPlayerId);
	if( !stItem.IsNull() )
	{
		if( m_pID_LISTIMG_Fashionarmour )		
			m_pID_LISTIMG_Fashionarmour->SetItem( &stItem, 0 );
	}

	int nscore = 0;

	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		if (pMsg->playerequipitem[i].itembaseinfo.ustItemID == InvalidLogicNumber)
			continue;

		nscore +=(int)pMsg->playerequipitem[i].equipdata.fScore;
	}

	m_pID_TEXT_EquipScore->SetText(nscore);
}

void CUI_ID_FRAME_SeekEqup::ID_CHECKBOX_ZhuangbeiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked)
{
	m_pID_CHECKBOX_Zhuangbei->SetCheck(true);
	m_pID_CHECKBOX_SelfInfo->SetCheck(false);
	m_BaseGroup.SetVisible(true);
	m_pID_LISTIMG_Fashionarmour->SetVisable(false);
	m_pID_PICTURE_Fashion11->SetVisable(false);
}

void CUI_ID_FRAME_SeekEqup::ID_CHECKBOX_SelfInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked)
{
	m_pID_CHECKBOX_Zhuangbei->SetCheck(false);
	m_pID_CHECKBOX_SelfInfo->SetCheck(true);
	m_BaseGroup.SetVisible(false);
	m_pID_LISTIMG_Fashionarmour->SetVisable(true);
	m_pID_PICTURE_Fashion11->SetVisable(true);
}

bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_siliaoOnButtonClick( ControlObject* pSender )
{
	if(m_DestPlayer !=NULL &&  m_DestPlayer->GetName() != NULL )
	{
		s_CUI_ChatInfoBox.Begin2Secret( m_DestPlayer->GetName() );
		s_CUI_ChatInfoBox.SetChatTypeChannel(CUI_ChatInfoBox::CHAT_PRIVATE);
	}
	return true;
}

bool CUI_ID_FRAME_SeekEqup::ID_BUTTON_addfriendOnButtonClick( ControlObject* pSender )
{
	if(m_DestPlayer !=NULL &&  m_DestPlayer->GetName() != NULL )
	{
		s_CUI_ID_FRAME_AddFriend.SetFrameType( CUI_ID_FRAME_AddFriend::eFrameType_ChangeFriendToGroup );
		s_CUI_ID_FRAME_AddFriend.SetPrivateName(m_DestPlayer->GetName());
		s_CUI_ID_FRAME_AddFriend.SetVisable(true);
	}
	return true;
}

void CUI_ID_FRAME_SeekEqup::SortGroup()
{
	m_BaseGroup.Clear();
	m_BaseGroup.AddControl(m_pID_LISTIMG_Head);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Armour);
	m_BaseGroup.AddControl(m_pID_LISTIMG_rWeapon);
	m_BaseGroup.AddControl(m_pID_LISTIMG_2Weapon2);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Amulet);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Temp1);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Shoe);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Glove);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Shield);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Temp);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Accouterment1);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Ring1);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Ring2);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Bangle1);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Bangle2);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Accouterment);
	m_BaseGroup.AddControl(m_pID_LISTIMG_lWeapon);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Weapon2);
	m_BaseGroup.AddControl(m_pID_LISTIMG_Necklace);
	m_BaseGroup.AddControl(m_pID_LISTIMG_GangSkillBox);
	m_BaseGroup.AddControl(m_pID_LISTIMG_GangSkillBox);
	m_BaseGroup.AddControl(m_pID_PICTURE_rWeapon1);
	m_BaseGroup.AddControl(m_pID_PICTURE_fWeapon1);		
	//m_BaseGroup.AddControl(m_pID_LISTIMG_Fashionarmour);
	m_BaseGroup.SetVisible(true);
}