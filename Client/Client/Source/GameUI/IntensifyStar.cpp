/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Star.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "IntensifyStar.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIBase.h"
#include "StarLevelUpConfig.h"
#include "MeUI/ExpressionManager.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Common.h"
#include "PackItemEnableManager.h"

#define SET_STAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_Star##n->SetVisable( true )
#define SET_NEXTSTAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_NextStar##n->SetVisable( true )

CUI_ID_FRAME_IntensifyStar s_CUI_ID_FRAME_IntensifyStar;
MAP_FRAME_RUN( s_CUI_ID_FRAME_IntensifyStar, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_IntensifyStar, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_EspecialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_EspecialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_EspecialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_EspecialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LIST_ArmourPropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LIST_TargetPropertyOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_Target2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_Target2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_Target2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_Target2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_TargetOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_TargetOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_TargetOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_IntensifyStar, ID_LISTIMG_TargetOnIconRButtonUp )
CUI_ID_FRAME_IntensifyStar::CUI_ID_FRAME_IntensifyStar()
{
	// Member
	ResetUIObjects();
	m_bStartAnim = false;
}
void CUI_ID_FRAME_IntensifyStar::ResetUIObjects()
{
	m_pID_FRAME_IntensifyStar = NULL;
	m_pID_PICTURE_DI2 = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_LISTIMG_Especial = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_LIST_ArmourProperty = NULL;
	m_pID_LIST_TargetProperty = NULL;
	m_pID_PICTURE_Star18 = NULL;
	m_pID_PICTURE_Star17 = NULL;
	m_pID_PICTURE_Star16 = NULL;
	m_pID_PICTURE_Star15 = NULL;
	m_pID_PICTURE_Star14 = NULL;
	m_pID_PICTURE_Star13 = NULL;
	m_pID_PICTURE_Star12 = NULL;
	m_pID_PICTURE_Star11 = NULL;
	m_pID_PICTURE_Star10 = NULL;
	m_pID_PICTURE_Star9 = NULL;
	m_pID_LISTIMG_Target2 = NULL;
	m_pID_PICTURE_NextStar18 = NULL;
	m_pID_PICTURE_NextStar17 = NULL;
	m_pID_PICTURE_NextStar16 = NULL;
	m_pID_PICTURE_NextStar15 = NULL;
	m_pID_PICTURE_NextStar14 = NULL;
	m_pID_PICTURE_NextStar13 = NULL;
	m_pID_PICTURE_NextStar12 = NULL;
	m_pID_PICTURE_NextStar11 = NULL;
	m_pID_PICTURE_NextStar10 = NULL;
	m_pID_PICTURE_NextStar9 = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_LISTIMG_Target = NULL;
	m_pID_TEXT_Rate = NULL;

	m_bNeedUpdate = false;
	m_stNormalBagIndex = -1;
	m_stNormalBagGuid = 0;

	m_bNormalBagEnable = true;
	m_stLevelupMaterialIndex = -1;  
	m_n64LevelupMaterialGuid = 0;
	m_bLevelupMaterialBagEnable = true;
	m_stRateMaterialIndex = -1;
	m_n64RateMaterialGuid = 0;
	m_bRateMaterialBagEnable = true;
    m_shRateMaterialBagType    = -1;
    m_shLevelupMaterialBagType = -1;
	m_shRateMaterialCount = 0;
}

void CUI_ID_FRAME_IntensifyStar::SetAtomVisible( bool bVisible )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	m_pID_LISTIMG_Target->SetVisable( bVisible );
	m_pID_LIST_ArmourProperty->SetVisable( bVisible );
	m_pID_LIST_TargetProperty->SetVisable( bVisible );
}
void CUI_ID_FRAME_IntensifyStar::RefreshAllBagEnable()
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	SetAtomVisible( false );
	if( m_stNormalBagIndex != -1 )
	{
        if( m_bNormalBagEnable )
        {
            m_stNormalBagGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stNormalBagIndex, true );
		SetAtomVisible( true );
	}

	if( m_stLevelupMaterialIndex != -1 )
	{
        if( m_bLevelupMaterialBagEnable )
        {
            m_n64LevelupMaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stLevelupMaterialIndex, true );
	}

	if( m_stRateMaterialIndex != -1 )
	{
        if( m_bRateMaterialBagEnable )
        {
            m_n64RateMaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stRateMaterialIndex, true );
	}	

}
// Frame
bool CUI_ID_FRAME_IntensifyStar::OnFrameRun()
{
	if( !IsDirty() )
		return true;
	
	SetDirty( false );

	RefreshAllBagEnable();	

	if( m_pID_LISTIMG_Armour->GetNullItem() != -1 && 
		m_stNormalBagIndex != -1) // 有空位，清空包裹id		
	{
		m_stNormalBagIndex = -1;
        m_stNormalBagGuid = 0;
		m_StarGroup.SetVisible( false );
		m_NextStarGroup.SetVisible( false );		
		SetDirty( true );
	}
	else
	{
		RefreshNeedMoney( thePlayerRole.m_bag.GetCharItemFromIdx( m_stNormalBagIndex ) );
	}

	if( m_pID_LISTIMG_Material->GetNullItem() != -1 && 
		m_stLevelupMaterialIndex != -1 )
	{
		m_stLevelupMaterialIndex = -1;
		SetDirty( true );
	}

	if( m_pID_LISTIMG_Especial->GetNullItem() != -1 && 
		m_stRateMaterialIndex != -1 )
	{
		m_stRateMaterialIndex = -1;
		SetDirty( true );
	}

    RefreshOkButton();

	return true;
}
bool CUI_ID_FRAME_IntensifyStar::OnFrameRender()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}
		if( m_bStartAnim )
		{
			RECT rc;
			m_pID_PICTURE_StarEffect->GetRealRect(&rc);
			m_slideAnim.Update(HQ_TimeGetTime(),&rc);
			if (!m_slideAnim.IsInAnimation())
			{
				m_bStartAnim = false;
				m_slideAnim.UnRelativePicResource();
			}
		}
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_IntensifyStar )
		return false;

	if( !pItemDrag )
		return false;

	ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );
	OnFrameRun();

	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pItemImg )
		return false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return false;

	if( !s_CUI_ID_FRAME_PACK.CanUseIntensifyGemById( pItemDrag->m_pkIconInfo->GetItemId(), pCanEquip->stEquipLevelReq ) )
		return false;

	ItemDefine::SItemCommon* pItemCommonDrag  = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommonDrag && pItemCommonDrag->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
	{
		m_pID_LISTIMG_Material->Clear();
		pItemDrag->m_eEnable = eIcon_Enable;
		m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;

		//物品在包裹里的id
		m_stLevelupMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
		m_n64LevelupMaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
		m_bLevelupMaterialBagEnable = false;
        m_shLevelupMaterialBagType  = BT_MaterialBag;
		SetDirty( true );
	}
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_IntensifyStar )
		return false;
	m_bLevelupMaterialBagEnable = true;
	m_pID_LISTIMG_Material->Clear();
	SetDirty( true );
	return false;
}

void CUI_ID_FRAME_IntensifyStar::UpdateAddRateGem()
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	if( !IsVisable() )
		return;

	if( m_pID_LISTIMG_Especial->GetNullItem() != -1 )// none
		return;

	// enable原材料的icon
	if( m_stRateMaterialIndex != -1 )
	{
        m_n64RateMaterialGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stRateMaterialIndex, true );
	}

	m_pID_LISTIMG_Especial->Clear();
	SetDirty( true );
}

void CUI_ID_FRAME_IntensifyStar::UpdateGem()
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	if( !IsVisable() )
		return;

	// enable原材料的icon
	if( m_stLevelupMaterialIndex != -1 )
	{
        m_n64LevelupMaterialGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stLevelupMaterialIndex, true );
	}

	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pItemImg )
		return;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	ControlIconDrag::S_ListImg* pGemImg = 0;
	// 先找与当前材料相同id的材料
	if( pGemImg = m_pID_LISTIMG_Material->GetItemByIndex( 0 ) )
	{
		pGemImg = s_CUI_ID_FRAME_PACK.GetIntensifyGemById( pGemImg->m_pkIconInfo->GetItemId(), pCanEquip->stEquipLevelReq );
	}
	// 没有与当前匹配的材料，自动找一个
	if( !pGemImg )
		pGemImg = s_CUI_ID_FRAME_PACK.GetIntensifyGem( pCanEquip->stEquipLevelReq );	
	
	if( pGemImg )
	{
		m_stLevelupMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pGemImg );
		m_n64LevelupMaterialGuid = pGemImg->m_pkIconInfo->GetOnlyId();
        m_shLevelupMaterialBagType = BT_MaterialBag;
		m_pID_LISTIMG_Material->SetItem( pGemImg, 0 );
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;
		m_bLevelupMaterialBagEnable = false;
	}
	else // 没有宝石了
	{
		m_pID_LISTIMG_Material->Clear();
	}
	SetDirty( true );
}
void CUI_ID_FRAME_IntensifyStar::ClearAllList()
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Material->Clear();
	m_pID_LISTIMG_Especial->Clear();
	m_pID_LISTIMG_Target->Clear();
    m_pID_TEXT_UseMoney->SetText("");
	m_pID_TEXT_Rate->SetText("");
}
void CUI_ID_FRAME_IntensifyStar::RefreshArmour()
{
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pItemImg )
		return;

	SetArmourAndTargetInfo( pItemImg );

	UpdateArmourInfo( (SCharItem*)pItemImg->m_pkIconInfo->GetData(), m_pID_LIST_ArmourProperty , false );
	UpdateArmourInfo( (SCharItem*)pItemImg->m_pkIconInfo->GetData(), m_pID_LIST_TargetProperty , true );

	// 显示星
	ShowStar( (int)((SCharItem*)pItemImg->m_pkIconInfo->GetData())->equipdata.ucLevel,GetItemLevel(pItemImg->m_pkIconInfo->GetItemId()) );
	ShowNextStar( (int)((SCharItem*)pItemImg->m_pkIconInfo->GetData())->equipdata.ucLevel + 1,GetItemLevel(pItemImg->m_pkIconInfo->GetItemId()) );
		
}
void CUI_ID_FRAME_IntensifyStar::UpdateArmourInfo( SCharItem* pItem, ControlList* pList, bool bNextLevel )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	char szBuf[256] = {0};
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	pList->Clear();
	ControlList::S_List sList;
	sList.UseSelColor = false;
	if( (pItem->equipdata.ucLevel >= SCharItem::EL_Max) )//max level
	{
		// 添加提示信息
		MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s", theXmlString.GetString(eText_StarAll) );
		sList.SetData( szBuf );
		pList->AddItem( &sList );
		return;
	}	
	// 添加名字
	Common::_tstring tstrName( pItemCommon->GetItemName() );
	S_IconInfoHero::ReplaceSpecifiedName( pItemCommon->ustLevel, tstrName );
	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s", tstrName.c_str() );
	sList.SetData( szBuf, 0, 0, S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel ) );	
	pList->AddItem( &sList );
	//添加影响的属性
	//仅气血、法术、攻击(2)、防御(2)
	//这里逐一判断
	if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
	{		
		ItemDefine::SItemWeapon* pWeapon = (ItemDefine::SItemWeapon*)pItemCommon;
		sList.clear();
		// 魔法攻击
		if( pWeapon->attackMagic != 0 )
		{
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicAttack), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );
		}
		
		sList.clear();
		// 物理攻击
		if( pWeapon->attackPhysics != 0 )  
		{  
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d",theXmlString.GetString( eTip_sAddShortAttack ),
				(int)S_IconInfoHero::GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, pItem->equipdata.ucLevel + (int)bNextLevel ) );  
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );
		}
	}
	else if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItemCommon;
		sList.clear();
		//// 血气
		//if( pArmour->nHpMax > 0 )
		//{
		//	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddHPMax),
		//		S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->nHpMax, pItem->equipdata.ucLevel + (int)bNextLevel ) );
		//	sList.SetData( szBuf, 0, 0, 0xffffffff );
		//	pList->AddItem( &sList );
		//}		

		//if( pArmour->sMpMax > 0 )
		//{
		//	sList.clear();
		//	// 法力
		//	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMPMax), 
		//		S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->sMpMax, pItem->equipdata.ucLevel + (int)bNextLevel ) );
		//	sList.SetData( szBuf, 0, 0, 0xffffffff );
		//	pList->AddItem( &sList );
		//}

		if( pArmour->attackPhysics > 0 )
		{
			sList.clear();
			// 近程攻击
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddShortAttack), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackPhysics, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );
		}

		if( pArmour->attackMagic > 0 )
		{
			sList.clear();
			// 远程攻击
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicAttack), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->attackMagic, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );
		}

		if( pArmour->defendPhysics > 0 )
		{
			sList.clear();
			// 近程防御
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddShortDefend), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendPhysics, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );
		}

		if( pArmour->defendMagic > 0 )
		{
			sList.clear();
			// 远程防御
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicDefend), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->defendMagic, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );		
		}
		/*
		 * Author: 2012-10-11 21:17:19 liaojie
		 * Desc:   
		 */
		if( pArmour->Hp > 0 )
		{
			sList.clear();
			// Hp
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddHPMax), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Hp, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );		
		}
		if( pArmour->Mp > 0 )
		{
			sList.clear();
			// Hp
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMPMax), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );		
		}
	}

}

void CUI_ID_FRAME_IntensifyStar::SetArmourAndTargetInfo( ControlIconDrag::S_ListImg* pListImg )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Target->Clear();
	m_pID_LISTIMG_Armour->SetItem( pListImg, 0 );
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	

    int nLevel = GetItemLevel(pListImg->m_pkIconInfo->GetItemId());
    if(nLevel <= 0)
        return;

	// 不能放入9星以下或60级以下的装备部件
	if (((SCharItem*)pListImg->m_pkIconInfo->GetData())->equipdata.ucLevel < 9 || nLevel <= 59)
	{
		// do something
	}
	else
	{
		m_pID_LISTIMG_Target->Clear();
		ControlIconDrag::S_ListImg liTarget;
		SCharItem sItem = *(SCharItem*)pListImg->m_pkIconInfo->GetData();
		sItem.equipdata.ucLevel++;
		liTarget.SetData( &sItem );
		m_pID_LISTIMG_Target->SetItem( &liTarget, 0 );
		m_pID_LISTIMG_Target->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;				
	}
}
// ListImg / ListEx
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_IntensifyStar )
		return false;
	if( !pItemDrag )
		return false;

    int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
    if(nLevel <= 0)
        return false;

    // 不能放入9星以下或60级以下的装备部件
    if (((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->equipdata.ucLevel < 9 )
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eText_IntensifyStarFailed_StarLimit) );
        return false;
    }
	if( nLevel <= 59 )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eText_IntensifyStarFailed_LevelLimit) );
		return false;
	}

	ID_LISTIMG_ArmourOnIconRButtonUp( 0, 0 );
	OnFrameRun();	

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
		pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
		{			
			m_stNormalBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );

            SCharItem item;
            if(m_stNormalBagIndex != -1 && thePlayerRole.m_bag.GetItem(m_stNormalBagIndex,&item))
                m_stNormalBagGuid = item.itembaseinfo.nOnlyInt;
            else
              m_stNormalBagGuid = 0;
		}
		else
		{
			return false;
		}		
		
		m_bNormalBagEnable = false;			
		UpdateGem();
		RefreshArmour();

		SetDirty( true );
	}	

	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{		
	if( !m_pID_FRAME_IntensifyStar )
		return false;
	m_bNormalBagEnable = true;				
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Target->Clear();
	m_bLevelupMaterialBagEnable = true;
	m_pID_LISTIMG_Material->Clear();
    m_pID_TEXT_UseMoney->SetText("");
	m_pID_TEXT_Rate->SetText("");
	SetDirty( true );

	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_IntensifyStar )
		return false;
	if( !pItemDrag )
		return false;

	// 是否有装备
	ControlIconDrag::S_ListImg* pEquipItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pEquipItemImg )
		return false;
	ItemDefine::SItemCommon* pEquipItemCommon = GettheItemDetail().GetItemByID( pEquipItemImg->m_pkIconInfo->GetItemId() );
	if( !pEquipItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pEquipItemCommon;
	if( !pCanEquip )
		return false;

	ID_LISTIMG_EspecialOnIconRButtonUp( 0, 0 );
	OnFrameRun();

// 	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
// 	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
// 	{
// 		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;
// 		// 写死id
// 		if( pMaterial->stMaterialType != CItemDetail::ematerial_addrate )
// 			return false;
// 		
// 		// 装备等级判断，加成等级判断
// 		int nLevelLimit = pMaterial->levelUpLimit / 100;
// 		int nStarLevelLimit = pMaterial->levelUpLimit % 100;
// 		if ( ( nLevelLimit > 0 && nLevelLimit < pCanEquip->stEquipLevelReq ) || 
// 			( nStarLevelLimit > 0 && nStarLevelLimit < ((SCharItem*)pEquipItemImg->m_pkIconInfo->GetData())->equipdata.ucLevel ) )
// 		{
// 			GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_IntensifyStarFailed_IncorrectRateMaterial ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 1000 );
// 			return false;
// 		}
// 
// 		//物品在包裹里的id
// 		m_stRateMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
// 		m_n64RateMaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
//         m_shRateMaterialBagType = BT_MaterialBag;
// 		m_bRateMaterialBagEnable = false;
// 		m_shRateMaterialCount = min(pItemDrag->m_pkIconInfo->Count(), 5);
// 
// 		ControlIconDrag::S_ListImg item = *pItemDrag;
// 		item.m_eEnable = eIcon_Enable;
// 		item.m_pkIconInfo->SetData(pItemDrag->m_pkIconInfo->GetItemId(), m_shRateMaterialCount);
// 		m_pID_LISTIMG_Especial->Clear();			
// 		m_pID_LISTIMG_Especial->SetItem( &item, 0 );
// 
// 		char szRate[256] = {0};
// 		MeSprintf_s(szRate, sizeof(szRate)/sizeof(char) - 1, "%s%d%%", theXmlString.GetString(eFiveXingDisplace_ProbTip), (int)(pMaterial->fAddIntensifyRate*m_shRateMaterialCount*100.f));
// 		m_pID_TEXT_Rate->SetText(szRate);
// 		SetDirty( true );
// 	}

	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_IntensifyStar )
		return false;
	m_bRateMaterialBagEnable = true;		
	m_pID_LISTIMG_Especial->Clear();
	m_pID_TEXT_Rate->SetText("");

	SetDirty( true );
	return false;
}
// Button
bool CUI_ID_FRAME_IntensifyStar::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{		
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	// 播放序列帧动画
	m_slideAnim.StartAnimation(HQ_TimeGetTime());
	m_bStartAnim = true;

	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = MsgEquipEvolve::ET_LevelUp;

	msgEvolve.nNormalBagIndex = m_stNormalBagIndex;
    msgEvolve.nNormalGuid      = m_stNormalBagGuid;

	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= m_shLevelupMaterialBagType;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stLevelupMaterialIndex;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_n64LevelupMaterialGuid;

	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType = m_shRateMaterialBagType;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex = m_stRateMaterialIndex;
	msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid = m_n64RateMaterialGuid;
//     msgEvolve.uchLevelupMaterialBagType = m_shLevelupMaterialBagType;
// 	msgEvolve.stLevelupMaterialIndex = m_stLevelupMaterialIndex;
// 	msgEvolve.n64LevelupMaterialGuid = m_n64LevelupMaterialGuid;
// 	
//     msgEvolve.uchRateMaterialBagType1 = m_shRateMaterialBagType;
//     msgEvolve.stRateMaterialIndex1 = m_stRateMaterialIndex;
// 	msgEvolve.n64RateMaterialGuid1 = m_n64RateMaterialGuid;
// 	msgEvolve.ustRateMaterialCount1 = m_shRateMaterialCount;
	
	msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );

	return true;
}
// Button
bool CUI_ID_FRAME_IntensifyStar::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	SetVisable( false );
	return true;
}
// List
void CUI_ID_FRAME_IntensifyStar::ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return;
}
// List
void CUI_ID_FRAME_IntensifyStar::ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return;
}
short CUI_ID_FRAME_IntensifyStar::GetItemMaterialType( unsigned short ustId )
{
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustId );
	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
	{
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;	
		return pMaterial->stMaterialType;			
	}
	return -1;
}
// ListImg / ListEx
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_Target2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_Target2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_Target2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_Target2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_IntensifyStar::ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_IntensifyStar::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\IntensifyStar.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\IntensifyStar.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_IntensifyStar::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_IntensifyStar, s_CUI_ID_FRAME_IntensifyStarOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_IntensifyStar, s_CUI_ID_FRAME_IntensifyStarOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_IntensifyStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IntensifyStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_IntensifyStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IntensifyStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_IntensifyStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_EspecialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_EspecialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_EspecialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IntensifyStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_EspecialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_IntensifyStar, ID_BUTTON_Ok, s_CUI_ID_FRAME_IntensifyStarID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_IntensifyStar, ID_BUTTON_Cancel, s_CUI_ID_FRAME_IntensifyStarID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_IntensifyStar, ID_LIST_ArmourProperty, s_CUI_ID_FRAME_IntensifyStarID_LIST_ArmourPropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_IntensifyStar, ID_LIST_TargetProperty, s_CUI_ID_FRAME_IntensifyStarID_LIST_TargetPropertyOnListSelectChange );
	theUiManager.OnIconDragOn( ID_FRAME_IntensifyStar, ID_LISTIMG_Target2, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_Target2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Target2, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_Target2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Target2, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_Target2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IntensifyStar, ID_LISTIMG_Target2, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_Target2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_IntensifyStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_TargetOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_TargetOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_IntensifyStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_TargetOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_IntensifyStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_IntensifyStarID_LISTIMG_TargetOnIconRButtonUp );

	m_pID_FRAME_IntensifyStar = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_IntensifyStar );
	m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_DI2 );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LISTIMG_Material );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LISTIMG_Armour );
	m_pID_LISTIMG_Especial = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LISTIMG_Especial );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_TEXT_UseMoney );
	m_pID_LIST_ArmourProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LIST_ArmourProperty );
	m_pID_LIST_TargetProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LIST_TargetProperty );
	m_pID_PICTURE_Star18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star18 );
	m_pID_PICTURE_Star17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star17 );
	m_pID_PICTURE_Star16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star16 );
	m_pID_PICTURE_Star15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star15 );
	m_pID_PICTURE_Star14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star14 );
	m_pID_PICTURE_Star13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star13 );
	m_pID_PICTURE_Star12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star12 );
	m_pID_PICTURE_Star11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star11 );
	m_pID_PICTURE_Star10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star10 );
	m_pID_PICTURE_Star9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_Star9 );
	m_pID_LISTIMG_Target2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LISTIMG_Target2 );
	m_pID_PICTURE_NextStar18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar18 );
	m_pID_PICTURE_NextStar17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar17 );
	m_pID_PICTURE_NextStar16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar16 );
	m_pID_PICTURE_NextStar15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar15 );
	m_pID_PICTURE_NextStar14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar14 );
	m_pID_PICTURE_NextStar13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar13 );
	m_pID_PICTURE_NextStar12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar12 );
	m_pID_PICTURE_NextStar11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar11 );
	m_pID_PICTURE_NextStar10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar10 );
	m_pID_PICTURE_NextStar9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_NextStar9 );
	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_PICTURE_StarEffect );
	m_pID_LISTIMG_Target = (ControlListImage*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_LISTIMG_Target );
	m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_IntensifyStar, ID_TEXT_Rate );
	assert( m_pID_FRAME_IntensifyStar );
	assert( m_pID_PICTURE_DI2 );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_LISTIMG_Especial );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_UseMoneyZ );
	assert( m_pID_TEXT_UseMoney );
	assert( m_pID_LIST_ArmourProperty );
	assert( m_pID_LIST_TargetProperty );
	assert( m_pID_PICTURE_Star18 );
	assert( m_pID_PICTURE_Star17 );
	assert( m_pID_PICTURE_Star16 );
	assert( m_pID_PICTURE_Star15 );
	assert( m_pID_PICTURE_Star14 );
	assert( m_pID_PICTURE_Star13 );
	assert( m_pID_PICTURE_Star12 );
	assert( m_pID_PICTURE_Star11 );
	assert( m_pID_PICTURE_Star10 );
	assert( m_pID_PICTURE_Star9 );
	assert( m_pID_LISTIMG_Target2 );
	assert( m_pID_PICTURE_NextStar18 );
	assert( m_pID_PICTURE_NextStar17 );
	assert( m_pID_PICTURE_NextStar16 );
	assert( m_pID_PICTURE_NextStar15 );
	assert( m_pID_PICTURE_NextStar14 );
	assert( m_pID_PICTURE_NextStar13 );
	assert( m_pID_PICTURE_NextStar12 );
	assert( m_pID_PICTURE_NextStar11 );
	assert( m_pID_PICTURE_NextStar10 );
	assert( m_pID_PICTURE_NextStar9 );
	assert( m_pID_PICTURE_StarEffect );
	assert( m_pID_LISTIMG_Target );
	assert( m_pID_TEXT_Rate );

	m_StarGroup.AddControl(m_pID_PICTURE_Star18);
	m_StarGroup.AddControl(m_pID_PICTURE_Star17);
	m_StarGroup.AddControl(m_pID_PICTURE_Star16);
	m_StarGroup.AddControl(m_pID_PICTURE_Star15);
	m_StarGroup.AddControl(m_pID_PICTURE_Star14);
	m_StarGroup.AddControl(m_pID_PICTURE_Star13);
	m_StarGroup.AddControl(m_pID_PICTURE_Star12);
	m_StarGroup.AddControl(m_pID_PICTURE_Star11);
	m_StarGroup.AddControl(m_pID_PICTURE_Star10);
	m_StarGroup.AddControl(m_pID_PICTURE_Star9);
	m_StarGroup.SetVisible( false );
	
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar18);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar17);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar16);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar15);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar14);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar13);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar12);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar11);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar10);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar9);
	m_NextStarGroup.SetVisible( false );

	m_pID_LIST_ArmourProperty->HaveSelBar( 0, 0 );	
	m_pID_LIST_TargetProperty->HaveSelBar( 0, 0 );
	m_pID_FRAME_IntensifyStar->SetOnVisibleChangedFun( OnVisibleChange );

	m_pID_LISTIMG_Target->SetEnableDrag( false );

	m_bStartAnim = false;
	RECT rc;
	m_pID_PICTURE_StarEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\UpStarEffect\\UpStarEffect", 20, rc, 1400);

	theUiManager.SetFrameLayout(UI_LAYOUT_1, m_pID_FRAME_IntensifyStar);
	SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_IntensifyStar::_UnLoadUI()
{
	theUiManager.RemoveFrameLayout(m_pID_FRAME_IntensifyStar);
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
	m_StarGroup.Clear();
	m_NextStarGroup.Clear();
	ResetUIObjects();
	return theUiManager.RemoveFrame( "Data\\UI\\IntensifyStar.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_IntensifyStar::_IsVisable()
{
	if (!m_pID_FRAME_IntensifyStar)
		return false;
	return m_pID_FRAME_IntensifyStar->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_IntensifyStar::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	m_pID_FRAME_IntensifyStar->SetVisable( bVisable );	
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
}

void CUI_ID_FRAME_IntensifyStar::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_IntensifyStar.SetDirty( true );
	s_CUI_ID_FRAME_IntensifyStar.m_bLevelupMaterialBagEnable = true;
	s_CUI_ID_FRAME_IntensifyStar.m_bNormalBagEnable = true;
	s_CUI_ID_FRAME_IntensifyStar.m_bRateMaterialBagEnable = true;
	s_CUI_ID_FRAME_IntensifyStar.RefreshAllBagEnable();
	s_CUI_ID_FRAME_IntensifyStar.ClearAllList();	
}

void CUI_ID_FRAME_IntensifyStar::ShowStar( int nStar ,int nLevel )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
    int nMaxLevel = 0;
    nMaxLevel = SCharItem::EL_Max;

	nStar = min( nMaxLevel, nStar );
	m_StarGroup.SetVisible( false );
	SET_STAR_VISIBLE( 9, nStar );
	SET_STAR_VISIBLE( 10, nStar );
	SET_STAR_VISIBLE( 11, nStar );
	SET_STAR_VISIBLE( 12, nStar );
	SET_STAR_VISIBLE( 13, nStar );
	SET_STAR_VISIBLE( 14, nStar );
	SET_STAR_VISIBLE( 15, nStar );
	SET_STAR_VISIBLE( 16, nStar );
	SET_STAR_VISIBLE( 17, nStar );
	SET_STAR_VISIBLE( 18, nStar );
}

void CUI_ID_FRAME_IntensifyStar::ShowNextStar( int nStar  ,int nLevel)
{
	if( !m_pID_FRAME_IntensifyStar )
		return;

	int nMaxLevel = 0;

	nMaxLevel = SCharItem::EL_Max;

	nStar = min( nMaxLevel, nStar );
	m_NextStarGroup.SetVisible( false );
	SET_NEXTSTAR_VISIBLE( 9, nStar );
	SET_NEXTSTAR_VISIBLE( 10, nStar );
	SET_NEXTSTAR_VISIBLE( 11, nStar );
	SET_NEXTSTAR_VISIBLE( 12, nStar );
	SET_NEXTSTAR_VISIBLE( 13, nStar );
	SET_NEXTSTAR_VISIBLE( 14, nStar );
	SET_NEXTSTAR_VISIBLE( 15, nStar );
	SET_NEXTSTAR_VISIBLE( 16, nStar );
	SET_NEXTSTAR_VISIBLE( 17, nStar );
	SET_NEXTSTAR_VISIBLE( 18, nStar );
}

void CUI_ID_FRAME_IntensifyStar::RefreshNeedMoney( SCharItem* pItem )
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
	if( !pItem )
		return;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return ;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return ;

	StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
	if( !pData )
		return;

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(pData->GetCostMoney(), text);

    DWORD dwColor = 0xffffffff;
    if(!thePlayerRole.HaveEnoughMoney(pData->GetCostMoney()))
    {
        dwColor = 0xffff0000;
    }
    m_pID_TEXT_UseMoney->SetText(text,dwColor);
}

void CUI_ID_FRAME_IntensifyStar::RefreshOkButton()
{
	if( !m_pID_FRAME_IntensifyStar )
		return;
    if(!IsVisable())
        return;

    m_pID_BUTTON_Ok->SetEnable( true );
    if( m_pID_LISTIMG_Armour->GetNullItem() != -1 ||
        m_pID_LISTIMG_Material->GetNullItem() != -1 ||
		m_pID_LISTIMG_Especial->GetNullItem() != -1 )
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
    if(!pImg)
        return;

    if(pImg->IsNull())
        return;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return ;

    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
    if( !pCanEquip )
        return ;	

    StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, ((SCharItem*)pImg->m_pkIconInfo->GetData())->equipdata.ucLevel );
    if( !pData )
        return;

    if(!thePlayerRole.HaveEnoughMoney(pData->GetCostMoney()))
    {
        m_pID_BUTTON_Ok->SetEnable(false);
        return;
    }

    RefreshNeedMoney((SCharItem*)(pImg->m_pkIconInfo->GetData()));

    return;
}

int CUI_ID_FRAME_IntensifyStar::GetItemLevel(unsigned short ustItemID )
{
    if(ustItemID < 0)
        return -1;

    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(ustItemID);
    if(!pItemCommon)
        return -1;

    ItemDefine::SItemCanEquip *pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
    if(!pCanEquip)
        return -1;

    return pCanEquip->stEquipLevelReq;
}

bool CUI_ID_FRAME_IntensifyStar::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_stNormalBagGuid == nGuid || m_n64LevelupMaterialGuid == nGuid || m_n64RateMaterialGuid == nGuid )
        return true;

    return false;
}
