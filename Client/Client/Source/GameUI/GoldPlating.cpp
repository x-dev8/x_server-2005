/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\GoldPlating.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GoldPlating.h"
#include "PlayerRole.h"
#include "ui/Pack.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "MeUI/ExpressionManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "StarLevelUpConfig.h"
#include "RandPropertyEvaluate.h"
#include "MeUi/IconManager.h"
#include "IconManagerClient.h"
#include "Progress.h"
#include "Common.h"
#include "ScreenInfoManager.h"
#include "PackItemEnableManager.h"

extern int g_nTheRoleProfession;

//////////////////////////////////////////////////////////////////////////

DWORD dwYellow = 0xffffee03;
DWORD dwBlue   = 0xff06a2ff;
DWORD dwRed	   = 0xfffd1d11;
#define ITEM_SHOW_INT_PRETEXT(x, str, col)		if(x > 0) \
{									\
	sprintf( szTemp, "%s%s+%d",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
	sList.clear();	\
	sList.SetData( szTemp, 0, 0, col );\
	m_pID_LIST_Property->AddItem( &sList );	\
	sList.clear(); \
	m_pID_LIST_Quality->AddItem( &sList );\
}
#define ITEM_SHOW_FLOAT_PRETEXT(x, str, col)		if(x > 0.0f) \
{	\
	sprintf( szTemp, "%s%s%0.1f",theXmlString.GetString( eTip_PreText_Normal ), str, x );	\
	sList.clear();	\
	sList.SetData( szTemp, 0, 0, col );\
	m_pID_LIST_Property->AddItem( &sList );	\
	sList.clear(); \
	m_pID_LIST_Quality->AddItem( &sList );\
}
float GetAttributeWithLevel( int nEquipType, float fAttribute, short stLevel )
{
	return theStarLevelUpConfig.GetItemStarLevelModulus( nEquipType, stLevel ) * fAttribute;
}

int GetAttributeWithLevel( int nEquipType, int nAttribute, short stLevel )
{
	return theStarLevelUpConfig.GetItemStarLevelModulus( nEquipType, stLevel ) * nAttribute;
}
//////////////////////////////////////////////////////////////////////////



CUI_ID_FRAME_GoldPlating s_CUI_ID_FRAME_GoldPlating;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GoldPlating, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GoldPlating, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_BUTTON_CancelOnButtonClick )
//MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LIST_BasePropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LIST_PropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LIST_QualityOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_BUTTON_IdentifyOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_EspecialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_EspecialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_EspecialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GoldPlating, ID_LISTIMG_EspecialOnIconRButtonUp )
CUI_ID_FRAME_GoldPlating::CUI_ID_FRAME_GoldPlating()
{
	// Member
	m_pID_FRAME_GoldPlating = NULL;
// 	m_pID_PICTURE_DI2 = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_TEXT_Wall = NULL;
	//m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
// 	m_pID_TEXT_GoldPlating = NULL;
// 	m_pID_PICTURE_6105 = NULL;
	m_pID_TEXT_UseMoney = NULL;
	//m_pID_LIST_BaseProperty = NULL;
	m_pID_LIST_Property = NULL;
	//m_pID_PICTURE_LeftTitle = NULL;
	m_pID_TEXT_Prompt = NULL;
	m_pID_PICTURE_IdentifyTitle = NULL;
// 	m_pID_TEXT_Property = NULL;
// 	m_pID_TEXT_Identify = NULL;
	m_pID_PICTURE_GoldPlatingTitle = NULL;
	//m_pID_TEXT_EspecialProperty = NULL;
	m_pID_LIST_Quality = NULL;
	m_pID_BUTTON_Identify = NULL;
	m_pID_PICTURE_GoldPlatingEffect = NULL;
	m_pID_PICTURE_IdentifyEffect = NULL;
	m_pID_LISTIMG_Especial = NULL;

	m_stNormalBagIndex		= -1;        // 目标物品Index
    m_stNormalGuid          = 0;
	m_bNormalBagEnable		= true;
	m_stMaterialIndex		= -1	;		 // 鉴定/开光道具Index
	m_n64MaterialGuid		= 0;
	m_bMaterialBagEnable	= true;

	m_ePlatingType			= ePlatingType_Count;

	m_bDirty				= false;
	m_bStartAnim			= false;
	m_bStartIntonate		= false;
	m_dwStartIntonateTime	= 0;
	m_nIntonateTime			= 0;

    m_stMaterialBagType     = -1;

    m_stNeedMaterialBagType   = -1;   //回炉材料
    m_stNeedMaterialIndex     = -1;   //回炉材料索引
    m_n64NeedMaterialGuid     = 0;   //材料GUID
    m_bNeedMaterialBagEnable  = true; 
	m_ustNeedMaterialItemId	= InvalidLogicNumber;
}

// Frame
bool CUI_ID_FRAME_GoldPlating::OnFrameRun()
{
	if( IsVisable() )
	{
		// 走路或跳跃打断吟唱
		if( m_bStartIntonate )
		{
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
			if( pMe && (pMe->IsMoving() || pMe->IsJumping()) )
			{
				m_bStartIntonate = false;
				s_CUI_Progress.SetProgressComplete();
			}
		}
		// 吟唱结束
		if( m_bStartIntonate && m_dwStartIntonateTime + m_nIntonateTime < HQ_TimeGetTime() )
		{
			m_bStartIntonate = false;
			s_CUI_Progress.SetProgressComplete();

			// 请求鉴定/开光
			if( GetPlatingType() == ePlatingType_Identify )
				m_slideAnimIdentify.StartAnimation(HQ_TimeGetTime());
			else
				m_slideAnimGoldPlating.StartAnimation(HQ_TimeGetTime());
			m_bStartAnim = true;

			MsgEquipEvolve msgEvolve;
			MsgEquipEvolve::EEvolveType eType = MsgEquipEvolve::ET_OpenLight;
			if( GetPlatingType() == ePlatingType_Identify )
				eType = MsgEquipEvolve::ET_Identify;

			msgEvolve.nEvolveType = eType;
			msgEvolve.nNormalBagIndex = m_stNormalBagIndex;
			msgEvolve.nNormalGuid = m_stNormalGuid;
			msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= m_stMaterialBagType;
			msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stMaterialIndex;
			msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_n64MaterialGuid;

			msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType = m_stNeedMaterialBagType;
			msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex = m_stNeedMaterialIndex;
			msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid = m_n64NeedMaterialGuid;
//             msgEvolve.uchLevelupMaterialBagType = m_stMaterialBagType;
// 			msgEvolve.stLevelupMaterialIndex = m_stMaterialIndex;
// 			msgEvolve.n64LevelupMaterialGuid = m_n64MaterialGuid;
// 
//             msgEvolve.uchRateMaterialBagType1 = m_stNeedMaterialBagType;
//             msgEvolve.stRateMaterialIndex1    = m_stNeedMaterialIndex;
//             msgEvolve.n64RateMaterialGuid1    = m_n64NeedMaterialGuid;

			msgEvolve.SendEquipMsg();
			//GettheNetworkInput().SendMsg( &msgEvolve );
		}
	}

	if( !IsDirty() )
		return true;

	SetDirty( false );

	RefreshAllBagEnable();	

	if( m_pID_LISTIMG_Armour->GetNullItem() != -1 && m_stNormalBagIndex != -1) // 有空位，清空包裹id		
	{
        m_stNormalGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stNormalBagIndex, true );

		m_stNormalBagIndex = -1;
		SetDirty( true );
	}
	else
	{
		RefreshNeedMoney( thePlayerRole.m_bag.GetCharItemFromIdx( m_stNormalBagIndex ) );
	}

	if( m_pID_LISTIMG_Material->GetNullItem() != -1 && m_stMaterialIndex != -1 )
	{
        m_n64MaterialGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex, true );

		m_stMaterialIndex = -1;
		SetDirty( true );
	}

    if( m_pID_LISTIMG_Especial->GetNullItem() != -1 && m_stNeedMaterialIndex != -1 )
    {
        m_ustNeedMaterialItemId = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stNeedMaterialIndex, true );

        m_stNeedMaterialIndex = -1;
        SetDirty(true);
    }
    RefreshOkButton();
	return true;
}
bool CUI_ID_FRAME_GoldPlating::OnFrameRender()
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
		
// 		if( m_pID_LISTIMG_Armour->GetNullItem() == -1 )//有武器
// 		{
// 			m_pID_TEXT_GoldPlating->SetVisable( false );
// 			m_pID_TEXT_Identify->SetVisable( false );
// 		}
// 		else
// 		{
// 			if( m_ePlatingType == ePlatingType_KaiGuang )
// 				m_pID_TEXT_GoldPlating->SetVisable( true );
// 			else if( m_ePlatingType == ePlatingType_Identify )
// 				m_pID_TEXT_Identify->SetVisable( true );
// 		}

		// 序列帧动画
		if( m_bStartAnim )
		{
			RECT rc;
			if( m_ePlatingType == ePlatingType_Identify )
			{
				m_pID_PICTURE_IdentifyEffect->GetRealRect(&rc);
				m_slideAnimIdentify.Update(HQ_TimeGetTime(),&rc);
				if (!m_slideAnimIdentify.IsInAnimation())
				{
					m_bStartAnim = false;
					m_slideAnimIdentify.UnRelativePicResource();
				}
			}
			else
			{
				m_pID_PICTURE_GoldPlatingEffect->GetRealRect(&rc);
				m_slideAnimGoldPlating.Update(HQ_TimeGetTime(),&rc);
				if (!m_slideAnimGoldPlating.IsInAnimation())
				{
					m_bStartAnim = false;
					m_slideAnimGoldPlating.UnRelativePicResource();
				}
			}
		}
	}
	return true;
}
// Button
// bool CUI_ID_FRAME_GoldPlating::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_GoldPlating)
// 		return false;
// 	return true;
// }
// Button
// bool CUI_ID_FRAME_GoldPlating::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_GoldPlating)
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_GoldPlating )
		return false;

	if( !pItemDrag )
		return false;

    ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
    if( !pItemImg )
        return false;

    if(pItemImg->IsNull())
        return false;

	ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );
	OnFrameRun();

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
	{
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;

		if( ( pMaterial->stMaterialType != ItemDefine::ematerial_identify && GetPlatingType() == ePlatingType_Identify ) 
			/*|| ( pMaterial->stMaterialType != CItemDetail::ematerial_OpenLight && GetPlatingType() == ePlatingType_KaiGuang )*/ )
			return false;

		m_pID_LISTIMG_Material->Clear();			
		m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;		
		//物品在包裹里的id
		m_stMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );
		m_n64MaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
        m_stMaterialBagType = BT_MaterialBag;
		m_bMaterialBagEnable = false;
		SetDirty( true );
	}
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	m_bMaterialBagEnable = true;		
	m_pID_LISTIMG_Material->Clear();
	SetDirty( true );

	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_GoldPlating )
		return false;
	if( !pItemDrag )
		return false;

	ID_LISTIMG_ArmourOnIconRButtonUp( 0, 0 );
	OnFrameRun();	

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON ||
		pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR ) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

        ItemDefine::SItemCanEquip* pItemEquip = static_cast<ItemDefine::SItemCanEquip*>(pItemCommon);

		SCharItem sItem;
		if(!thePlayerRole.m_bag.GetItemByOnlyeID(pItemDrag->m_pkIconInfo->GetOnlyId(),&sItem))
			return false;
			 
        if(pItemEquip && (pItemEquip->bFashion || sItem.HasBaseRanded()))
        {
            if(m_ePlatingType == ePlatingType_Identify)
                 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eText_Intensify_CannotIdentify) );
            else if(m_ePlatingType == ePlatingType_KaiGuang)
                 CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eText_CannotIdentify) );
            return false;
        }

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
		{			
			m_stNormalBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
            
            SCharItem sItem;
            if(m_stNormalBagIndex != -1 && thePlayerRole.m_bag.GetItem(m_stNormalBagIndex,&sItem))
                m_stNormalGuid = sItem.itembaseinfo.nOnlyInt;
            else
                m_stNormalGuid = 0;
		}
		else
		{
			return false;
		}		

		m_bNormalBagEnable = false;			
		UpdateAccessory();
		RefreshArmour();

		SetDirty( true );

		ID_LISTIMG_MaterialOnIconRButtonUp( 0, 0 );
		OnFrameRun();
        SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_GoldPlating::SetMaterial0);
	}	
	
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	m_bMaterialBagEnable = true;
	m_bNormalBagEnable = true;			
// 	m_pID_LIST_BaseProperty->Clear();
	m_pID_LIST_Property->Clear();
	m_pID_LIST_Quality->Clear();
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Material->Clear();

    m_pID_LISTIMG_Especial->Clear();
    m_bNeedMaterialBagEnable = true;

	ClearMoney();
	SetDirty( true );	
	return false;
}
// Button
bool CUI_ID_FRAME_GoldPlating::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	// 开光
	if( GetPlatingType() != ePlatingType_KaiGuang )
		return false;

	// 开始吟唱
	if( !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_OpenLight_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_GoldPlating::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	SetVisable( false );
	return true;
}
// List
// void CUI_ID_FRAME_GoldPlating::ID_LIST_BasePropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
// {
// 	if (!m_pID_FRAME_GoldPlating)
// 		return;
// }
// List
void CUI_ID_FRAME_GoldPlating::ID_LIST_PropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return;
}

void CUI_ID_FRAME_GoldPlating::ID_LIST_QualityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return;
}
// Button
bool CUI_ID_FRAME_GoldPlating::ID_BUTTON_IdentifyOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	// 鉴定
	if( GetPlatingType() != ePlatingType_Identify )
		return false;

	// 开始吟唱
	if( !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_Identify_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Identify, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                               ControlIconDrag::S_ListImg* pItemDrag,
                                                               ControlIconDrag::S_ListImg* pItemSrc )
{
    if( !m_pID_FRAME_GoldPlating )
        return false;
    if( !pItemDrag )
        return false;

    ID_LISTIMG_EspecialOnIconRButtonUp( 0, 0 );
    OnFrameRun();	

    if(!IsReturnMaterial(pItemDrag))
        return false;

    if(!IsLevelAnaly(m_pID_LISTIMG_Armour->GetItemByIndex(0),pItemDrag))
        return false;

    if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag,pSender))
        return false;

    SCharItem sItem;
    if(!thePlayerRole.m_bag.GetItem(m_stNormalBagIndex,&sItem))
        return false;

    if(!IsHaveDone(&sItem))
        return false;

	int iNeedMatIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(BT_MaterialBag,pItemDrag);
	if(iNeedMatIndex == -1)
		return false;

	SCharItem sItemMat;
	if(!thePlayerRole.m_bagMaterial.GetItem(iNeedMatIndex,&sItemMat))
		return false;

	m_stNeedMaterialIndex = iNeedMatIndex;
    m_n64NeedMaterialGuid = sItemMat.itembaseinfo.nOnlyInt;
    m_bNeedMaterialBagEnable = false;
    m_stNeedMaterialBagType  = BT_MaterialBag;
	m_ustNeedMaterialItemId = sItemMat.itembaseinfo.ustItemID;

    m_pID_LISTIMG_Especial->Clear();			
    m_pID_LISTIMG_Especial->SetItem( pItemDrag, 0 );
    m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
    m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	

    SetDirty( true );
    return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
    return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
    return false;
}
bool CUI_ID_FRAME_GoldPlating::ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
    m_bNeedMaterialBagEnable = true;		
    m_pID_LISTIMG_Especial->Clear();
    SetDirty( true );

    return false;
}
// 装载UI
bool CUI_ID_FRAME_GoldPlating::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GoldPlating.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GoldPlating.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GoldPlating::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GoldPlating, s_CUI_ID_FRAME_GoldPlatingOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GoldPlating, s_CUI_ID_FRAME_GoldPlatingOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_GoldPlating, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GoldPlatingID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_GoldPlating, ID_BUTTON_help, s_CUI_ID_FRAME_GoldPlatingID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GoldPlating, ID_LISTIMG_Material, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GoldPlating, ID_LISTIMG_Material, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GoldPlating, ID_LISTIMG_Material, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GoldPlating, ID_LISTIMG_Material, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_GoldPlating, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GoldPlating, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GoldPlating, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GoldPlating, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_GoldPlating, ID_BUTTON_Ok, s_CUI_ID_FRAME_GoldPlatingID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GoldPlating, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GoldPlatingID_BUTTON_CancelOnButtonClick );
//	theUiManager.OnListSelectChange( ID_FRAME_GoldPlating, ID_LIST_BaseProperty, s_CUI_ID_FRAME_GoldPlatingID_LIST_BasePropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldPlating, ID_LIST_Property, s_CUI_ID_FRAME_GoldPlatingID_LIST_PropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_GoldPlating, ID_LIST_Quality, s_CUI_ID_FRAME_GoldPlatingID_LIST_QualityOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_GoldPlating, ID_BUTTON_Identify, s_CUI_ID_FRAME_GoldPlatingID_BUTTON_IdentifyOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_GoldPlating, ID_LISTIMG_Especial, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_EspecialOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_GoldPlating, ID_LISTIMG_Especial, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_EspecialOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_GoldPlating, ID_LISTIMG_Especial, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_EspecialOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_GoldPlating, ID_LISTIMG_Especial, s_CUI_ID_FRAME_GoldPlatingID_LISTIMG_EspecialOnIconRButtonUp );

	m_pID_FRAME_GoldPlating = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GoldPlating );
// 	m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_DI2 );
// 	m_pID_PICTURE_title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_title2 );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_BUTTON_help );
	m_pID_TEXT_Wall = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_Wall );
	//m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LISTIMG_Material );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_UseMoneyZ );
	//m_pID_TEXT_GoldPlating = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_GoldPlating );
	//m_pID_PICTURE_6105 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_6105 );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_UseMoney );
	//m_pID_LIST_BaseProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LIST_BaseProperty );
	m_pID_LIST_Property = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LIST_Property );
	//m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_LeftTitle );
	m_pID_TEXT_Prompt = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_Prompt );
	m_pID_PICTURE_IdentifyTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_IdentifyTitle );
// 	m_pID_TEXT_Property = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_Property );
// 	m_pID_TEXT_Identify = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_Identify );
	m_pID_PICTURE_GoldPlatingTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_GoldPlatingTitle );
	//m_pID_TEXT_EspecialProperty = (ControlText*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_TEXT_EspecialProperty );
	m_pID_LIST_Quality = (ControlList*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LIST_Quality );
	m_pID_BUTTON_Identify = (ControlButton*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_BUTTON_Identify );
	m_pID_PICTURE_GoldPlatingEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_GoldPlatingEffect );
	m_pID_PICTURE_IdentifyEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_PICTURE_IdentifyEffect );
	m_pID_LISTIMG_Especial = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GoldPlating, ID_LISTIMG_Especial );

	assert( m_pID_FRAME_GoldPlating );
// 	assert( m_pID_PICTURE_DI2 );
// 	assert( m_pID_PICTURE_title2 );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_TEXT_Wall );
// 	assert( m_pID_PICTURE_ItemWall );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_GoldPlating );
	//assert( m_pID_PICTURE_6105 );
	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_LIST_BaseProperty );
	assert( m_pID_LIST_Property );
// 	assert( m_pID_PICTURE_LeftTitle );
	assert( m_pID_TEXT_Prompt );
	assert( m_pID_PICTURE_IdentifyTitle );
// 	assert( m_pID_TEXT_Property );
// 	assert( m_pID_TEXT_Identify );
	assert( m_pID_PICTURE_GoldPlatingTitle );
	assert( m_pID_LIST_Quality );
	//assert( m_pID_TEXT_EspecialProperty );
	assert( m_pID_BUTTON_Identify );
	assert( m_pID_PICTURE_GoldPlatingEffect );
	assert( m_pID_PICTURE_IdentifyEffect );
	assert( m_pID_LISTIMG_Especial );

	m_pID_FRAME_GoldPlating->SetOnVisibleChangedFun( OnVisibleChange );
// 	m_pID_TEXT_Identify->SetVisable( false );
// 	m_pID_TEXT_GoldPlating->SetVisable( false );
	m_pID_PICTURE_GoldPlatingTitle->SetVisable( false );
	m_pID_PICTURE_IdentifyTitle->SetVisable( false );
	//m_pID_LIST_BaseProperty->HaveSelBar( 0, 0 );
	m_pID_LIST_Property->HaveSelBar( 0, 0 );
	m_pID_LIST_Quality->HaveSelBar( 0, 0 );
	m_pID_BUTTON_Identify->SetVisable(false);

	// 初始化序列帧图素
	RECT rc;
	m_pID_PICTURE_GoldPlatingEffect->GetRealRect(&rc);
	m_slideAnimGoldPlating.Initialize("Ui\\Common\\GoldPlatingEffect\\GoldPlatingEffect", 20, rc, 1400);
	m_pID_PICTURE_IdentifyEffect->GetRealRect(&rc);
	m_slideAnimIdentify.Initialize("Ui\\Common\\IdentifyEffect\\IdentifyEffect", 20, rc, 1400);
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GoldPlating::_UnLoadUI()
{
	m_pID_FRAME_GoldPlating = NULL;
// 	m_pID_PICTURE_DI2 = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_TEXT_Wall = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
// 	m_pID_TEXT_GoldPlating = NULL;
// 	m_pID_PICTURE_6105 = NULL;
	m_pID_TEXT_UseMoney = NULL;
//	m_pID_LIST_BaseProperty = NULL;
	m_pID_LIST_Property = NULL;
// 	m_pID_PICTURE_LeftTitle = NULL;
	m_pID_TEXT_Prompt = NULL;
	m_pID_PICTURE_IdentifyTitle = NULL;
// 	m_pID_TEXT_Property = NULL;
// 	m_pID_TEXT_Identify = NULL;
	m_pID_PICTURE_GoldPlatingTitle = NULL;
// 	m_pID_TEXT_EspecialProperty = NULL;
	m_pID_LIST_Quality = NULL;
	m_pID_BUTTON_Identify = NULL;
	m_pID_PICTURE_GoldPlatingEffect = NULL;
	m_pID_PICTURE_IdentifyEffect = NULL;
    m_pID_LISTIMG_Especial = NULL;
	ClearAnim();
	return theUiManager.RemoveFrame( "Data\\UI\\GoldPlating.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GoldPlating::_IsVisable()
{
	if (!m_pID_FRAME_GoldPlating)
		return false;
	return m_pID_FRAME_GoldPlating->IsVisable();
}
void CUI_ID_FRAME_GoldPlating::ClearMoney()
{
	s_CUI_ID_FRAME_GoldPlating.m_pID_TEXT_UseMoney->Clear();
}
// 设置是否可视
void CUI_ID_FRAME_GoldPlating::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_GoldPlating)
		return;
	if( bVisable )
	{
		s_CUI_ID_FRAME_GoldPlating.ClearAllList();
		ClearMoney();
		s_CUI_ID_FRAME_GoldPlating.UpdateAtomVisible();
		s_CUI_ID_FRAME_GoldPlating.SetDirty( true );
	}
	ClearAnim();
	m_pID_FRAME_GoldPlating->SetVisable( bVisable );
}
void CUI_ID_FRAME_GoldPlating::UpdateAccessory()
{
	if( !IsVisable() )
		return;	
}
void CUI_ID_FRAME_GoldPlating::UpdateAtomVisible()
{
    if(!m_pID_FRAME_GoldPlating)
        return;
	if( GetPlatingType() == ePlatingType_Identify )// 鉴定
	{
// 		m_pID_TEXT_Identify->SetVisable( true );
// 		m_pID_TEXT_GoldPlating->SetVisable( false );
// 
// 		m_pID_TEXT_Property->SetVisable( false );
// 		m_pID_TEXT_EspecialProperty->SetVisable( false );	

		m_pID_PICTURE_IdentifyTitle->SetVisable( true );
		m_pID_PICTURE_GoldPlatingTitle->SetVisable( false );
		m_pID_BUTTON_Identify->SetVisable(true);
		m_pID_BUTTON_Identify->SetCaption("");
		m_pID_BUTTON_Ok->SetVisable(false);
	}
	else if( GetPlatingType() == ePlatingType_KaiGuang )
	{
// 		m_pID_TEXT_Property->SetVisable( false );
// 		m_pID_TEXT_EspecialProperty->SetVisable( false );
// 
// 		m_pID_TEXT_GoldPlating->SetVisable( true );
// 		m_pID_TEXT_Identify->SetVisable( false );

		m_pID_PICTURE_IdentifyTitle->SetVisable( false );
		m_pID_PICTURE_GoldPlatingTitle->SetVisable( true );
		m_pID_BUTTON_Identify->SetVisable(false);
		m_pID_BUTTON_Ok->SetVisable(true);
		m_pID_BUTTON_Ok->SetCaption("");
	}
	if( m_pID_LISTIMG_Armour->GetNullItem() == -1 )//有武器
	{
// 		m_pID_TEXT_GoldPlating->SetVisable( false );
// 		m_pID_TEXT_Identify->SetVisable( false );
	}
}

bool CUI_ID_FRAME_GoldPlating::SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
{
	if( !pItemDrag )
		return false;

	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
	if( !pItemImg )
		return false;

	if(pItemImg->IsNull())
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
	{
		ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )pItemCommon;

		if( ( pMaterial->stMaterialType != ItemDefine::ematerial_identify && GetPlatingType() == ePlatingType_Identify ) 
			/*|| ( pMaterial->stMaterialType != CItemDetail::ematerial_OpenLight && GetPlatingType() == ePlatingType_KaiGuang ) */)
			return false;

		// 装备等级
		ControlIconDrag::S_ListImg* pArmorImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
		if( !pArmorImg )
			return false;
		ItemDefine::SItemCommon* pArmorItemCommon = GettheItemDetail().GetItemByID( pArmorImg->m_pkIconInfo->GetItemId() );
		if( !pArmorItemCommon ||
			(pArmorItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR && pArmorItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON) )
			return false;
		ItemDefine::SItemCanEquip* pArmorEquip = (ItemDefine::SItemCanEquip*)pArmorItemCommon;
		if(pMaterial->levelLowLimit > pArmorEquip->stEquipLevelReq || pMaterial->levelUpLimit < pArmorEquip->stEquipLevelReq )
			return false;

		m_pID_LISTIMG_Material->Clear();			
		m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
		m_pID_LISTIMG_Material->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;		
		//物品在包裹里的id
		m_stMaterialBagType = BT_MaterialBag;
		m_stMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem(m_stMaterialBagType, pItemDrag );
		m_n64MaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
		m_bMaterialBagEnable = false;
		SetDirty( true );
		return true;
	}
	return false;
}

bool CUI_ID_FRAME_GoldPlating::SetMaterial1(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
{
	if( !pItemDrag )
		return false;

	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Armour->GetItemByIndex(0);
	if( !pItemImg )
		return false;

	if(pItemImg->IsNull())
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
	{
		if( pItemDrag->m_pkIconInfo->GetItemId() != m_ustNeedMaterialItemId)
			return false;

		m_pID_LISTIMG_Especial->Clear();			
		m_pID_LISTIMG_Especial->SetItem( pItemDrag, 0 );
		m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
		m_pID_LISTIMG_Especial->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;		
		//物品在包裹里的id
		m_stNeedMaterialBagType  = BT_MaterialBag;
		m_stNeedMaterialIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( m_stMaterialBagType, pItemDrag );
		m_n64NeedMaterialGuid = pItemDrag->m_pkIconInfo->GetOnlyId();
		m_bNeedMaterialBagEnable = false;

		SetDirty( true );
		return true;
	}
	return false;
}

void CUI_ID_FRAME_GoldPlating::RefreshMaterial()
{
    if(!m_pID_FRAME_GoldPlating)
        return;

	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stMaterialBagType, m_stMaterialIndex );
	if( pItemImg && pItemImg->m_pkIconInfo->GetItemId() == InvalidLogicNumber )	
	{
		// 查找材料，有则自动塞进来
		m_bMaterialBagEnable = true;
		m_pID_LISTIMG_Material->Clear();
		SetDirty( true );
		SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_GoldPlating::SetMaterial0);
	}
	
	pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_stNeedMaterialBagType, m_stNeedMaterialIndex );
	if( pItemImg && pItemImg->m_pkIconInfo->GetItemId() == InvalidLogicNumber )	
	{
		// 查找相同ItemId材料，有则自动塞进来
		m_bNeedMaterialBagEnable = true;
		m_pID_LISTIMG_Especial->Clear();
		SetDirty( true );
		SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_GoldPlating::SetMaterial1);
	}
}

void CUI_ID_FRAME_GoldPlating::RefreshArmour()
{
    if(!m_pID_FRAME_GoldPlating)
        return;
	ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stNormalBagIndex );
	if( !pItemImg )
		return;

	UpdateAtomVisible();
	SetArmourInfo( pItemImg );
	UpdateArmourInfo( (SCharItem*)pItemImg->m_pkIconInfo->GetData(), m_pID_LIST_Property  );
}
void CUI_ID_FRAME_GoldPlating::UpdateArmourInfo( SCharItem* pItem, ControlList* pList )
{
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

// 	m_pID_LIST_BaseProperty->Clear();
	pList->Clear();
	m_pID_LIST_Quality->Clear();
	ControlList::S_List sList;
	sList.UseSelColor = false;
	// 随机属性
	if( pCanEquip->ucItemType != ItemDefine::ITEMTYPE_ARMOUR  && pCanEquip->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
		return;	

	// 显示鉴定等级ui
	unsigned short usRandEvalValue_Identify = S_IconInfoHero::GetEquipRandomEvaluate( pItemCommon, pCanEquip->ucItemType,
        CRandPropertyEvaluate::PropertyEvaluate_Identify, *pItem );
	unsigned short usRandEvalValue_OpenLight = S_IconInfoHero::GetEquipRandomEvaluate( pItemCommon, pCanEquip->ucItemType,
        CRandPropertyEvaluate::PropertyEvaluate_OpenLight, *pItem );	

	int nRandValue = 0;
	char szTemp[256] = {0};
	int nTipPreTextIndex = 0;
	// 鉴定还需要另外显示‘鉴定:’
	if( m_ePlatingType == ePlatingType_Identify && usRandEvalValue_Identify != InvalidLogicNumber )
	{
		MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "{#30%d}", usRandEvalValue_Identify );
		sList.clear();
		sList.SetData( szTemp, 0, 0, 0xffffffff );
		m_pID_LIST_Quality->AddItem( &sList );
		//去掉多余的行
		if( m_pID_LIST_Quality->GetListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 )->m_szText[0]
			== '\0' )
				m_pID_LIST_Quality->RemoveListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 );
	}
	

	for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; nloop++)
	{
		ItemDefine::SRandAttribute* pArmourRand = NULL;
		unsigned short usRand =pItem->equipdata.baseRands[nloop];
		//if( nloop >= pCanEquip->additiveRandCount )//&& ( nloop != ( SCharItem::e_AddRandIndex ) ) )//随机个数以内
		//	continue;

		if( usRand == InvalidLogicNumber )// 显示问号
		{   /*
			// 品质介于2-5，现在套装也显示
			if( pCanEquip->ustLevel >= 2 && pCanEquip->ustLevel <= 5 )
			{
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "%s %s", theXmlString.GetString( eTip_PreText_Addition1 + nTipPreTextIndex ),
                    theXmlString.GetString( eTip_PreText_NoIdentify ) );
				nTipPreTextIndex++;
				DWORD dwColor = dwBlue;
				if( nloop == ( SCharItem::e_AddRandIndex ) )
				{
					MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "%s %s", theXmlString.GetString( eTip_PreText_KaiGuang ),
                        theXmlString.GetString( eTip_PreText_NoKaiGuang ) );
					dwColor = dwYellow;
				}
				bool bShow = true;
				if( m_ePlatingType == ePlatingType_Identify && nloop == SCharItem::e_AddRandIndex )		// 鉴定不显示开光属性
				{
					bShow = false;
				}
				else if( m_ePlatingType == ePlatingType_KaiGuang && nloop != SCharItem::e_AddRandIndex )	// 开光不显示鉴定属性
				{
					bShow = false;
				}
				if( bShow )
				{
					sList.clear();
					sList.SetData( szTemp, 0, 0, dwColor );
					m_pID_LIST_Property->AddItem( &sList );
					sList.clear();			
					m_pID_LIST_Quality->AddItem( &sList );
				}
			}*/
			continue;
		}

		pArmourRand = GettheItemDetail().GetRandByID(pItem->equipdata.baseRands[nloop]);

		if (!pArmourRand)
			continue;

		for( int i = 0 ; i < ItemDefine::SRandAttribute::CD_TypeCount ; ++ i )
		{
            nRandValue = S_IconInfoHero::GetRandValueByType( pArmourRand, i );
			if( pArmourRand->type[i] == RT_None )continue;

			if( m_ePlatingType == ePlatingType_KaiGuang )//&& nloop == ( SCharItem::e_AddRandIndex ) )//开光
			{
                sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue );
                //theXmlString.GetString( eTip_PreText_KaiGuang ), 
				
				sList.clear();
				sList.SetData( szTemp, 0, 0, dwYellow );
				m_pID_LIST_Property->AddItem( &sList );
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) - 1, "{#30%d}", usRandEvalValue_OpenLight );
				sList.clear();
				sList.SetData( szTemp, 0, 0, 0xffffffff );
				m_pID_LIST_Quality->AddItem( &sList );
				//去掉多余的行
				if( m_pID_LIST_Quality->GetListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 )->m_szText[0]
				== '\0' )
					m_pID_LIST_Quality->RemoveListItem( m_pID_LIST_Quality->GetListItemCnt() - 1 );
				continue;
			}

			if( nRandValue != InvalidLogicNumber &&
				m_ePlatingType == ePlatingType_Identify )//&& nloop != SCharItem::e_AddRandIndex )		// 鉴定不显示开光属性
			{  
				sprintf( szTemp, "%s+%d", S_IconInfoHero::GetRandStringByType( pArmourRand->type[i] ).c_str(), nRandValue );
                //theXmlString.GetString( eTip_PreText_Addition1 + nTipPreTextIndex ), 
				nTipPreTextIndex ++ ;

				sList.clear();
				sList.SetData( szTemp, 0, 0, dwBlue );
				m_pID_LIST_Property->AddItem( &sList );
				sList.clear();
				m_pID_LIST_Quality->AddItem( &sList );
				
			}			
		}
	}		
	
}

void CUI_ID_FRAME_GoldPlating::SetArmourInfo( ControlIconDrag::S_ListImg* pListImg )
{
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Armour->SetItem( pListImg, 0 );
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
	m_pID_LISTIMG_Armour->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
}

void CUI_ID_FRAME_GoldPlating::RefreshAllBagEnable()
{
	if( m_stNormalBagIndex != -1 )
	{
        if( m_bNormalBagEnable )
        {
            m_stNormalGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stNormalBagIndex, true );
	}

	if( m_stMaterialIndex != -1 )
	{
        if( m_bMaterialBagEnable )
        {
            m_n64MaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex, true );
	}

    if(m_stNeedMaterialIndex != -1)
    {
        if( m_bNeedMaterialBagEnable )
        {
            m_n64NeedMaterialGuid = 0;
        }
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stNeedMaterialIndex, true );
    }
}

void CUI_ID_FRAME_GoldPlating::RefreshNeedMoney( SCharItem* pItem )
{
	if( !pItem )
		return;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return ;

	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return ;	

	int nFactor = 1;
	if( GetPlatingType() == ePlatingType_Identify )
		nFactor = 2;
	else if( GetPlatingType() == ePlatingType_KaiGuang )
		nFactor = 10;

	StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, 0 );
	if( !pData )
		return;

    DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    DWORD dwColor = 0xffffffff;
    if(!thePlayerRole.HaveEnoughMoney(pData->GetCostMoney() * nFactor))
    {
       dwColor = 0xffff0000;
    }
     
	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(pData->GetCostMoney() * nFactor, text);
    m_pID_TEXT_UseMoney->SetText(text,dwColor);
}

void CUI_ID_FRAME_GoldPlating::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_GoldPlating.ClearAllList();
	s_CUI_ID_FRAME_GoldPlating.m_pID_TEXT_UseMoney->Clear();
	s_CUI_ID_FRAME_GoldPlating.UpdateAtomVisible();
	s_CUI_ID_FRAME_GoldPlating.SetDirty( true );
	s_CUI_ID_FRAME_GoldPlating.ClearAnim();
}

void CUI_ID_FRAME_GoldPlating::ClearAllList()
{
	s_CUI_ID_FRAME_GoldPlating.SetDirty( true );
	s_CUI_ID_FRAME_GoldPlating.m_bMaterialBagEnable = true;
	s_CUI_ID_FRAME_GoldPlating.m_bNormalBagEnable = true;
	s_CUI_ID_FRAME_GoldPlating.RefreshAllBagEnable();	
	s_CUI_ID_FRAME_GoldPlating.m_pID_LISTIMG_Armour->Clear();
	s_CUI_ID_FRAME_GoldPlating.m_pID_LISTIMG_Material->Clear();
    s_CUI_ID_FRAME_GoldPlating.m_pID_LISTIMG_Especial->Clear();
// 	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_BaseProperty->Clear();
	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_Property->Clear();
	s_CUI_ID_FRAME_GoldPlating.m_pID_LIST_Quality->Clear();
}

void CUI_ID_FRAME_GoldPlating::SetPlatingType( ePlatingType eType )
{
	if( !m_pID_FRAME_GoldPlating )
		return;
	m_ePlatingType = eType;
	if( m_ePlatingType == ePlatingType_Identify )
	{
		m_pID_BUTTON_Identify->SetVisable(true);
		m_pID_BUTTON_Ok->SetVisable(false);
	}
	else
	{
		m_pID_BUTTON_Identify->SetVisable(false);
		m_pID_BUTTON_Ok->SetVisable(true);
	}
}

void CUI_ID_FRAME_GoldPlating::ShowBaseInfo( void* pItemDetail, INT nType, SCharItem* pstItem )
{
	guardfunc;

	ItemDefine::SItemCommon *pItem = NULL;

	if( pItemDetail )
	{
		pItem = (ItemDefine::SItemCommon *)pItemDetail;
	}
	//物品品质
	char szTemp [256] = {0};
	DWORD dwNameColor = 0xFFFF6400;

	if (!pItem)
	{
		return;
	}
	///	名称
	if( pItemDetail )
	{
		if (pstItem->itembaseinfo.ustItemID != CompoundItemID && pItem != NULL)
		{				
			Common::_tstring tstrName( pItem->GetItemName() );
			S_IconInfoHero::ReplaceSpecifiedName( pItem->ustLevel, tstrName );
			strncpy(szTemp, tstrName.c_str(), 255 );

		}
	}
	
	if ( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON
		|| pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
	{
		if( pItemDetail )
		{
			if (pstItem->equipdata.gemHoleCount > SCharItem::EConstDefine_GemHoleMaxCount)
			{
				pstItem->equipdata.gemHoleCount = 0;
			}

			if (pstItem->equipdata.gemHoleCount > 0)
			{
				dwNameColor = S_IconInfoHero::GetQualityColor(pItem->ustLevel);
			}
			else
			{
				dwNameColor = S_IconInfoHero::GetQualityColor( pItem->ustLevel );
			}
		}
	}
	else
	{
		//品质
		dwNameColor = S_IconInfoHero::GetQualityColor( pItem->ustLevel );
	}


	if (pstItem->equipdata.gemHoleCount == SCharItem::EConstDefine_GemHoleMaxCount)
	{
		dwNameColor = 0xFFA6A600;
	}

	ControlList::S_List sList;
	ControlList::S_List sTempList;
	sTempList.clear();
	sTempList.UseSelColor = false;

	sList.UseSelColor = false;		
	sList.clear();
	sList.SetData( szTemp, 0, 0, dwNameColor );
// 	m_pID_LIST_BaseProperty->AddItem( &sList );		

	if( pItemDetail )
	{
		if ( pstItem->itembaseinfo.szCreaterName[0] != 0 )
		{
			sprintf( szTemp," (%s)", pstItem->itembaseinfo.szCreaterName );
			sList.clear();
			sList.SetData( szTemp, 0, 0, 0xffffffff );
// 			m_pID_LIST_BaseProperty->AddItem( &sList );	
			m_pID_LIST_Quality->AddItem( &sTempList );
		}
	}
	// 绑定
	if( pItem && pItem->bIsCanBound )
	{
		if ( ( nType == ItemDefine::ITEMTYPE_ARMOUR || nType == ItemDefine::ITEMTYPE_WEAPON ) )
		{
			if ( pstItem->IsBounded())
			{				
				sList.clear();
				sList.SetData( theXmlString.GetString(eTip_BelongerDone), 0, 0, dwYellow );
				m_pID_LIST_Property->AddItem( &sList );
				m_pID_LIST_Quality->AddItem( &sTempList );	
			}
			else
			{
				if( !pItem->bIsCanTrade )
				{
					if ( pstItem->itembaseinfo.stPacketIdx != -1 ) //背包index不为-1说明在包里
					{						
						sList.clear();
						sList.SetData( theXmlString.GetString(eTip_BelongerDone), 0, 0, dwYellow );
						m_pID_LIST_Property->AddItem( &sList );	
						m_pID_LIST_Quality->AddItem( &sTempList );

					}
					else
					{					
						sList.clear();
						sList.SetData( theXmlString.GetString(eTip_PickBound), 0, 0, dwYellow );
						m_pID_LIST_Property->AddItem( &sList );	
						m_pID_LIST_Quality->AddItem( &sTempList );
					}
				}
				else
				{					
					sList.clear();
					sList.SetData( theXmlString.GetString(eText_Title_Bound), 0, 0, dwYellow );
					m_pID_LIST_Property->AddItem( &sList );	
					m_pID_LIST_Quality->AddItem( &sTempList );
				}

			}
		}			
	}

	return;
	unguard;
}
void CUI_ID_FRAME_GoldPlating::ShowCanWeapon( void* pItemDetail, INT nType, SCharItem* pItem )
{
	if( !pItem )
		return;

	char szTemp [256] = {0};

	if( nType == ItemDefine::ITEMTYPE_WEAPON ||
		nType == ItemDefine::ITEMTYPE_ARMOUR 
		)
	{
		ItemDefine::SItemCanEquip* pDeTail = NULL;
		if( pItemDetail )
		{
			pDeTail = (ItemDefine::SItemCanEquip*)pItemDetail;
		}		
		if (!pDeTail)
		{
			return;
		}
		INT	nHPMax = pDeTail->stHPMax;
		int nCurrHP = pItem->equipdata.usHP;		
		if ( nCurrHP < 0 )
		{
			nCurrHP = nHPMax;
		}

		ItemDefine::SItemCanEquip* pEquip = NULL;
		if (pItemDetail)
		{
			pEquip = (ItemDefine::SItemCanEquip*)pItemDetail;
		}	
		ControlList::S_List sList;
		sList.UseSelColor = false;
		int nAddPhyAtt = 0;
		int nAddPhyDef = 0;
		int nAddMagAtt = 0;
		int nAddMagDef = 0;
		int nNullGemCount = 0;		
		char szBuff[256] = {0};
		//时装没有星级
		if( !pDeTail->bFashion )
		{
			// 星级
			if( pItem->equipdata.ucLevel <= 9 )
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "{#100%d}", (int)pItem->equipdata.ucLevel );
			else
				MeSprintf_s( szTemp, sizeof(szTemp)/sizeof(char) -1, "{#130%d}", (int)pItem->equipdata.ucLevel-10 );
			sList.clear();
			sList.SetData( szTemp );
			m_pID_LIST_Property->AddItem( &sList );
			sList.clear();			
			m_pID_LIST_Quality->AddItem( &sList );
		}

		//需要等级
		const DWORD dwColor1 = 0xffffffff;	
		DWORD dwNeedColor = 0xffffffff;
		if( pItemDetail )
		{
			
			//级别需求			
			
			if( thePlayerRole.GetLevel() < pEquip->stEquipLevelReq )//red			
				dwNeedColor = dwRed;				
			
			MeSprintf_s( szBuff, sizeof(szBuff)/sizeof(char) - 1, "%s %d", theXmlString.GetString(eUI_NeedLevel), (int)pEquip->stEquipLevelReq );
			sList.clear();
			sList.SetData( szBuff, 0, 0, dwNeedColor );
// 			m_pID_LIST_BaseProperty->AddItem( &sList );

			char szSex[128] = {0};
			BOOL bNeedShowSex = true;
			//性别
			switch(pEquip->cEquipSexReq)
			{
			case -1:
				bNeedShowSex = false;
				break;
			case Sex_Male:
				sprintf( szSex, "%s", theXmlString.GetString( eSex_Man ) );
				break;
			case Sex_Female:
				sprintf( szSex, "%s", theXmlString.GetString( eSex_FeMan ) );
				break;
			default:
				bNeedShowSex = false;
				break;
			}
			if( bNeedShowSex)
			{
				//性别需求
				if( pEquip->cEquipSexReq  == thePlayerRole.GetSex() )				
					dwNeedColor = 0xffffffff;				
				else				
					dwNeedColor = dwRed;				
				char szTemp[256] = {0};
				sprintf( szTemp, "%s %s", theXmlString.GetString(eUI_NeedSex), szSex );
				sList.clear();
				sList.SetData( szTemp, 0, 0, dwNeedColor );
// 				m_pID_LIST_BaseProperty->AddItem( &sList );
			}
			int nProfession[EArmType_MaxSize - 1] = {0};
			BOOL bIsAllProfession = FALSE;
			INT nProCnt = 0;
			BOOL bIsMeIn = false;

			for( int i=0; i<EArmType_MaxSize - 1; i++ )
			{
				if( pEquip->arrayEquipArmsReq[i] )
				{
					nProCnt++;
					nProfession[i] = 1;
				}
				else
					nProfession[i] = 0;
			}
			if( nProCnt == EArmType_MaxSize - 1)
			{
				bIsAllProfession = true;
			}
			if( !bIsAllProfession )
			{
				char szProfession[128] = {0};
				char szProfessionTemp[10] = {0};
				//职业
				BOOL bIsFirst = true;
				for ( int n = 0; n < EArmType_MaxSize - 1 ; n++ )
				{
					if (nProfession[n] == 1)
					{
						int nStringEnum = 0;
						switch(n)
						{
						case EArmType_Mage:
							nStringEnum = eProfession_Mage;
							break;
						case EArmType_Taoist:
							nStringEnum = eProfession_Taoist;	
							break;
						case EArmType_Assassin:
							nStringEnum = eProfession_Assassin;					
							break;
						case EArmType_Warrior:
							nStringEnum = eProfession_Warrior;
							break;
						case EArmType_Hunter:
							nStringEnum = eProfession_Hunter;													
							break;
						default:
							break;
						}
						if (bIsFirst)
						{
							strcpy( szProfession, theXmlString.GetString(nStringEnum) );
							bIsFirst = false;
						}
						else
						{
							strcpy(szProfessionTemp," ");
							HelperFunc::AddNCpy(szProfessionTemp, theXmlString.GetString(nStringEnum),sizeof(szProfessionTemp));									
							HelperFunc::AddNCpy(szProfession,szProfessionTemp, sizeof(szProfession));
						}	
					}						
				}
				char szTemp[256] = {0};
				if( nProfession[g_nTheRoleProfession] == 1)				
					dwNeedColor = 0xffffffff;				
				else				
					dwNeedColor = dwRed;		
				sprintf( szTemp, "%s %s",theXmlString.GetString(eNeed_Profession), szProfession );
				sList.clear();
				sList.SetData( szTemp, 0, 0, dwNeedColor );
// 				m_pID_LIST_BaseProperty->AddItem( &sList );
			}
			else
			{	
				sList.clear();
				sList.SetData( theXmlString.GetString(eText_AllPro), 0, 0, 0xffffffff );
// 				m_pID_LIST_BaseProperty->AddItem( &sList );
			}				

		}
		//////////////////////////////////////////////////////////////////////////
		//耐久点数
		if( pItemDetail )
		{
			sprintf( szTemp, "%s %d/%d", theXmlString.GetString(eEquip_Durable), nCurrHP, nHPMax );			
			if( nCurrHP > 0 )
				dwNeedColor = 0xffffffff;
			else
				dwNeedColor = dwRed;
			sList.clear();
			sList.SetData( szTemp, 0, 0, dwNeedColor );
			m_pID_LIST_Property->AddItem( &sList );
			sList.clear();			
			m_pID_LIST_Quality->AddItem( &sList );
		}

		// end 显示耐久
	}	

	return;
}

void CUI_ID_FRAME_GoldPlating::ShowWeapon( void* pItemDetail, INT nType, SCharItem* pItem )
{
	
	char szTemp [256] = {0};
	if( nType != ItemDefine::ITEMTYPE_WEAPON )
		return;

	//武器类型	
	ItemDefine::SItemWeapon* pWeapon = NULL;
	if (pItemDetail)
	{
		pWeapon = (ItemDefine::SItemWeapon*)pItemDetail;
	}	
	if (pWeapon)
	{		
		ControlList::S_List sList;
		sList.UseSelColor = false;
		// 远程攻击
		if( pWeapon->attackMagic != 0 )  
		{  
			sprintf_s( szTemp, sizeof(szTemp)-1, "%s+%d", theXmlString.GetString( eTip_sAddMagicAttack ),
				(int)GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackMagic, pItem->equipdata.ucLevel ) );  
            //theXmlString.GetString( eTip_PreText_Normal ),
			sList.clear();
			sList.SetData( szTemp, 0, 0, 0xffffffff );
			m_pID_LIST_Property->AddItem( &sList );
			sList.clear();
			m_pID_LIST_Quality->AddItem( &sList );
		}		

		// 近程攻击
		if( pWeapon->attackPhysics != 0 )  
		{  
			sprintf_s( szTemp, sizeof(szTemp)-1, "%s+%d", theXmlString.GetString( eTip_sAddShortAttack ),
				(int)GetAttributeWithLevel( pWeapon->ustEquipType, pWeapon->attackPhysics, pItem->equipdata.ucLevel ) );
            //theXmlString.GetString( eTip_PreText_Normal ), 
			sList.clear();
			sList.SetData( szTemp, 0, 0, 0xffffffff );
			m_pID_LIST_Property->AddItem( &sList );
			sList.clear();
			m_pID_LIST_Quality->AddItem( &sList );
		}

		//// 附加伤害
		//if( pWeapon->usAddtionDamage != 0 )
		//{
		//	sprintf_s( szTemp, sizeof(szTemp)-1, "%s%s %d",theXmlString.GetString(eTip_PreText_Normal), theXmlString.GetString(eTip_sAddDamage),
		//		(int)pWeapon->usAddtionDamage );  
		//	sList.clear();
		//	sList.SetData( szTemp, 0, 0, 0xffffffff );
		//	m_pID_LIST_Property->AddItem( &sList );
		//	sList.clear();
		//	m_pID_LIST_Quality->AddItem( &sList );
		//}	
	}
}

void CUI_ID_FRAME_GoldPlating::ShowArmour( void* pItemDetail, INT nType, SCharItem* pItem )
{
	if( nType != ItemDefine::ITEMTYPE_ARMOUR )
		return;

	char szTemp [256] = {0};	
	ItemDefine::SItemArmour* pArmour = NULL;
	DWORD dwDestColor = 0xffffffff;

	if ( pItemDetail )
	{
		if( pItemDetail )
		{
			pArmour = (ItemDefine::SItemArmour*)pItemDetail;
		}
		ControlList::S_List sList;
		sList.UseSelColor = false;		
		//ITEM_SHOW_INT_PRETEXT( GetAttributeWithLevel( pArmour->ustEquipType, pArmour->nHpMax, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddHPMax),					dwDestColor );	 // 血气
		//ITEM_SHOW_INT_PRETEXT( GetAttributeWithLevel( pArmour->ustEquipType, pArmour->sMpMax, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddMPMax),					dwDestColor );	 // 法力
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fAddtionPhysicsAttack,pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddShortAttack),				dwDestColor );	 // 近程攻击
		//ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fAddtionMagicAttack,	pItem->equipdata.ucLevel ),   theXmlString.GetString(eTip_sAddMagicAttack),			dwDestColor );	 // 远程攻击
		//ITEM_SHOW_INT_PRETEXT((int) pArmour->usAddtionDamage,		theXmlString.GetString(eTip_sAddDamage),				dwDestColor );	 // 附加伤害
 	//	ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fPhysicsDefend, pItem->equipdata.ucLevel ),	theXmlString.GetString(eTip_sAddShortDefend),				dwDestColor );	 // 近防
 	//	ITEM_SHOW_INT_PRETEXT((int)GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fMagicDefend,  pItem->equipdata.ucLevel ),		theXmlString.GetString(eTip_sAddMagicDefend),			dwDestColor );	 // 远防
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType, pArmour->usAddDamageResist, pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddDamageResist),			dwDestColor );   // 附加伤害抗
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->critical,	pItem->equipdata.ucLevel ),				theXmlString.GetString(eTip_sAddCritical),				dwDestColor );	 // 暴击率
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->criticalIntensity,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddCriticalIntensity),		dwDestColor );	 // 暴击强度
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->criticalResist,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddCriticalResist),		dwDestColor );	 // 暴击抗性		
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->exact,		pItem->equipdata.ucLevel ),				theXmlString.GetString(eTip_sAddExact),					dwDestColor );	 // 命中
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->dodge,	pItem->equipdata.ucLevel ),					theXmlString.GetString(eTip_sAddDodge),					dwDestColor );	 // 闪避
		//ITEM_SHOW_INT_PRETEXT(pArmour->sHpRestore,					theXmlString.GetString(eTip_sAddHPRestoreRate),			dwDestColor );	 // 气血回复速度
		//ITEM_SHOW_INT_PRETEXT(pArmour->sMpRestore,					theXmlString.GetString(eTip_sAddMPRestoreRate),			dwDestColor );	 // 法力回复速度
		//ITEM_SHOW_FLOAT_PRETEXT(pArmour->fMoveSpeed,				theXmlString.GetString(eTip_sAddMoveSpeed),				dwDestColor );	 // 移动速度 
		//ITEM_SHOW_INT_PRETEXT(pArmour->sAttSpeedAdd,				theXmlString.GetString(eTip_sAddMoveSpeed),				dwDestColor );	 // 攻击速度
		//ITEM_SHOW_INT_PRETEXT(pArmour->sIntonateSpeed,				theXmlString.GetString(eTip_sCastSpeed),				dwDestColor );	 // 吟唱速度
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistDread,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddGiddyResist),			dwDestColor );	 // 眩晕抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistComa,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddStandResist),			dwDestColor );	 // 定身抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistSlow,pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddSlowdownResist),		dwDestColor );	 // 减速抗性
		//ITEM_SHOW_INT_PRETEXT(GetAttributeWithLevel( pArmour->ustEquipType,pArmour->resistSilence,	pItem->equipdata.ucLevel ),			theXmlString.GetString(eTip_sAddTorpidResist),			dwDestColor );	 // 麻痹抗性

	}
}

void CUI_ID_FRAME_GoldPlating::RefreshOkButton()
{
    if(!IsVisable())
        return;

    // 更新按钮状态
	if( m_ePlatingType == ePlatingType_Identify )
		m_pID_BUTTON_Identify->SetEnable( true );
	else
		m_pID_BUTTON_Ok->SetEnable( true );
    if( m_pID_LISTIMG_Armour->GetNullItem() != -1 ||
        m_pID_LISTIMG_Material->GetNullItem() != -1 )
    {
		if( m_ePlatingType == ePlatingType_Identify )
			m_pID_BUTTON_Identify->SetEnable( false );
		else
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

    int nFactor = 1;
    if( GetPlatingType() == ePlatingType_Identify )
        nFactor = 2;
    else if( GetPlatingType() == ePlatingType_KaiGuang )
        nFactor = 10;

    StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, 0 );
    if( !pData )
        return;

    int gold = pData->GetCostMoney() * nFactor;
    DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
    DWORD dwColor = 0xffffffff;
    if(!thePlayerRole.HaveEnoughMoney(pData->GetCostMoney() * nFactor))
    {
		if( m_ePlatingType == ePlatingType_Identify )
			m_pID_BUTTON_Identify->SetEnable(false);
		else
			m_pID_BUTTON_Ok->SetEnable(false);
        return;
    }
    
    RefreshNeedMoney((SCharItem*)(pImg->m_pkIconInfo->GetData()));
    return;
}

void CUI_ID_FRAME_GoldPlating::ClearAnim()
{
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnimGoldPlating.StopAnimation();
		m_slideAnimGoldPlating.UnRelativePicResource();
		m_slideAnimIdentify.StopAnimation();
		m_slideAnimIdentify.UnRelativePicResource();
	}
	if( m_bStartIntonate )
	{
		m_bStartIntonate = false;
		s_CUI_Progress.SetProgressComplete();
	}
}

bool CUI_ID_FRAME_GoldPlating::IsReturnMaterial(ControlIconDrag::S_ListImg *pItem)
{
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
    if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL )
        return false;

    ItemDefine::SCreateMaterial* pItemMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
    if(!pItemMaterial)
        return false;

    if(m_ePlatingType == ePlatingType_Identify&&pItemMaterial->stMaterialType != ItemDefine::ematerial_reidentify)
        return false;
    else if(m_ePlatingType == ePlatingType_KaiGuang&&pItemMaterial->stMaterialType != ItemDefine::ematerial_reidentify/*ematerial_ReOpenLight*/)
        return false;

    return true;
}

bool CUI_ID_FRAME_GoldPlating::IsLevelAnaly(ControlIconDrag::S_ListImg *pItemAmor,ControlIconDrag::S_ListImg *pItemMaterial)
{
    if(!pItemAmor||!pItemMaterial)
        return false;

    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pItemAmor->m_pkIconInfo->GetItemId());
    if(!pItemCommon)
        return false;

    if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON&&pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
        return false;

    ItemDefine::SItemCanEquip  *pEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
    if(!pEquip)
        return false;

    pItemCommon = GettheItemDetail().GetItemByID(pItemMaterial->m_pkIconInfo->GetItemId());
    if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
        return false;

    ItemDefine::SCreateMaterial *pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
    if(!pMaterial)
        return false;
	return pMaterial->levelLowLimit <= pEquip->stEquipLevelReq && pMaterial->levelUpLimit >= pEquip->stEquipLevelReq;
//     return pEquip->stEquipLevelReq < pMaterial->levelLimit;
}

bool CUI_ID_FRAME_GoldPlating::IsHaveDone(SCharItem *pItem)
{
    //if(!pItem)
    //    return false;

    //if(m_ePlatingType == ePlatingType_Identify)
    //{
    //    if(pItem->equipdata.baseRands[0] != InvalidLogicNumber)// 是否已经鉴定过
    //        return true;
    //}
    //else if(m_ePlatingType == ePlatingType_KaiGuang)
    //{
    //    if(pItem->equipdata.baseRands[SCharItem::e_AddRandIndex] != InvalidLogicNumber) //是否已经开光过
    //        return true;
    //}

	return false;
}

bool CUI_ID_FRAME_GoldPlating::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_stNormalGuid == nGuid || m_n64MaterialGuid == nGuid || m_n64NeedMaterialGuid == nGuid )
    {
        return true;
    }

    return false;
}
