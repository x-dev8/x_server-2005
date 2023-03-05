/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\EquipUpgrade.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EquipUpgrade.h"
#include "ui/Pack.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIBase.h"
#include "MeUI/ExpressionManager.h"
#include "color_config.h"
#include "ScreenInfoManager.h"
#include "MessageDefine.h"
#include "ui/MessageBox.h"
#include "ui/Create.h"
#include "EquipUpgradeConfig.h"
#include "ChatInfoBox.h"
#include "Progress.h"
#include "Common.h"
#include "PackItemEnableManager.h"

extern const char* GetRootPath();

CUI_ID_FRAME_EquipUpgrade s_CUI_ID_FRAME_EquipUpgrade;
MAP_FRAME_RUN( s_CUI_ID_FRAME_EquipUpgrade, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_EquipUpgrade, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_M4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4OnIconRButtonUp )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_EquipUpgrade, ID_LIST_ChooseItemOnListSelectChange )
CUI_ID_FRAME_EquipUpgrade::CUI_ID_FRAME_EquipUpgrade()
{
	// Member
	m_pID_FRAME_EquipUpgrade = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_PICTURE_LeftMiddle = NULL;
// 	m_pID_PICTURE_RightMiddle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	//m_pID_PICTURE_LeftTitle = NULL;
	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_PICTURE_ExplainWall3 = NULL;
// 	m_pID_PICTURE_ItemWall2 = NULL;
// 	m_pID_TEXT_ArmourName = NULL;
	m_pID_TEXT_M1Name = NULL;
//	m_pID_TEXT_Word2 = NULL;
	m_pID_PICTURE_16595 = NULL;
	m_pID_LISTIMG_M1 = NULL;
	m_pID_TEXT_M1Num = NULL;
	m_pID_LISTIMG_M2 = NULL;
	m_pID_TEXT_M2Name = NULL;
	m_pID_TEXT_M2Num = NULL;
	m_pID_LISTIMG_M3 = NULL;
	m_pID_TEXT_M3Name = NULL;
	m_pID_TEXT_M3Num = NULL;
	m_pID_LISTIMG_M4 = NULL;
	m_pID_TEXT_M4Name = NULL;
	m_pID_TEXT_M4Num = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_LISTIMG_Armour1 = NULL;
	m_pID_LISTIMG_Armour2 = NULL;
	m_pID_LISTIMG_Armour3 = NULL;
	m_pID_LISTIMG_Armour4 = NULL;
	m_pID_TEXT_Armour1 = NULL;
	m_pID_TEXT_Armour2 = NULL;
	m_pID_TEXT_Armour3 = NULL;
	m_pID_TEXT_Armour4 = NULL;
	m_pID_LIST_ChooseItem = NULL;
	m_pID_PICTURE_WeaponTitleWord = NULL;
	m_pID_TEXT_WeaponExplain = NULL;
	m_pID_PICTURE_UpgradeEffect = NULL;

	m_bNeedUpdate = false;

	m_EquipItemBagIndex = -1;
	m_EquipItemEnable = true;
	m_nAimItemID = -1;
	m_needMoney = 0;
	m_bWeaponUpgrade = false;
	m_bStartAnim = false;

	for(int i = 0; i < EquipUpgradeMaxAimNumber; ++i)
	{
		m_pAimlListImage[i] = NULL;
		m_pID_TEXT_Aim[i] = NULL;
	}

	for(int i = EquipUpgradeAdditionalOne; i < EquipUpgradeMaxAdditional; ++i)
	{
		m_additionalItemBagIndex[i] = -1;
		m_additionalItemEnable[i] = true;
		m_pAdditionalListImage[i] = NULL;
		m_pID_TEXT_Additional[i] = NULL;
		m_pID_TEXT_AdditionalNumber[i] = NULL;
		m_bMaterialEnough[i] = false;
	}

	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}
// Frame
bool CUI_ID_FRAME_EquipUpgrade::OnFrameRun()
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

			// 请求升阶

			// 播放序列帧动画
			m_slideAnim.StartAnimation(HQ_TimeGetTime());
			m_bStartAnim = true;

			MsgEquipUpgradeReq EquipUpgradeReq;
			EquipUpgradeReq.ustEquipIndex = m_EquipItemBagIndex;
			SCharItem stItem;	
			thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
			EquipUpgradeReq.nEquipGuid = stItem.itembaseinfo.nOnlyInt;

			EquipUpgradeReq.ustUpToEquipID = m_nAimItemID;
			if (m_additionalItemBagIndex[EquipUpgradeAdditionalOptional] != -1 && (m_bMaterialEnough[EquipUpgradeAdditionalOptional]))
			{
				thePlayerRole.m_bagMaterial.GetItem( m_additionalItemBagIndex[EquipUpgradeAdditionalOptional], &stItem );
				EquipUpgradeReq.AddMaterial(stItem.itembaseinfo.ustItemID);
			}
			GettheNetworkInput().SendMsg( &EquipUpgradeReq );
		}
	}

	return true;
}
bool CUI_ID_FRAME_EquipUpgrade::OnFrameRender()
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
				SetVisable(false);
			}
		}
	}
	if( m_bStartAnim )
	{
		RECT rc;
		m_pID_PICTURE_UpgradeEffect->GetRealRect(&rc);
		m_slideAnim.Update(HQ_TimeGetTime(),&rc);
		if (!m_slideAnim.IsInAnimation())
		{
			m_bStartAnim = false;
			m_slideAnim.UnRelativePicResource();
		}
	}

	if (!m_bNeedUpdate)
	{
		return false;
	}

	bool bMoneyOk = true;

	if (m_EquipItemBagIndex != -1)
	{
		SCharItem stItem;	
		thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( pItemCommon )
		{
			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
			if ( pUpgradeData )
			{
				const UpToEquipInfo* pUpToEquip = pUpgradeData->GetUpToEquipByIndex(m_pID_LIST_ChooseItem->GetCurSelIndex());
				if (pUpToEquip && !thePlayerRole.HaveEnoughMoney(pUpToEquip->GetCostMoney())/*  thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) < pUpToEquip->GetCostMoney()*/)
					bMoneyOk = false;
			}
		}
	}

	m_bNeedUpdate = false;
	RefreshAllBagEnable();
	m_pID_BUTTON_Ok->SetEnable( false );
	bool bGetEnoughMustMaterial = false;
	if( m_iMustMaterialCount > 0 )
	{
		if( m_iMustMaterialCount == 1
			&& m_additionalItemBagIndex[EquipUpgradeAdditionalOne] != -1
			&& m_bMaterialEnough[EquipUpgradeAdditionalOne]
		)
			bGetEnoughMustMaterial = true;
		else if( m_iMustMaterialCount == 2
			&& 		m_additionalItemBagIndex[EquipUpgradeAdditionalOne] != -1
			&&		m_bMaterialEnough[EquipUpgradeAdditionalOne]
			&& 		m_additionalItemBagIndex[EquipUpgradeAdditionalTwo] != -1
			&&		m_bMaterialEnough[EquipUpgradeAdditionalTwo]
			)
			bGetEnoughMustMaterial = true;
	}
	if (m_EquipItemBagIndex != -1
		&&		bGetEnoughMustMaterial
		&&		bMoneyOk
	)
	{
		m_pID_BUTTON_Ok->SetEnable( true );
	}
	return true;
}
// Button
// bool CUI_ID_FRAME_EquipUpgrade::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_EquipUpgrade::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															  ControlIconDrag::S_ListImg* pItemDrag,
															  ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return false;
	}

	if (pItemSrc && pItemSrc->IsNull() == false)
		return false;

	if( CanItemUpgrade( pItemDrag->m_pkIconInfo->GetItemId() ))
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_NormalItemBag, pImageSender ) )
		{		
			SetEquipItem(pItemDrag);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString(eText_EquipUpgrade_Cannot) );
		return false;
	}
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return false;
	}

	SetEquipItemBagIndex(-1, true);
	m_pID_LISTIMG_Armour->Clear();
	//m_pID_TEXT_ArmourName->SetText("");
	m_pID_TEXT_UseMoney->SetText("");
	return false;
}
bool UpgradeEquip( const char bPressYesButton, void *pData )
{
	if (bPressYesButton)
	{
		s_CUI_ID_FRAME_EquipUpgrade.SendUpgradeEquipMsg();
	}
	return true;
}
// Button
bool CUI_ID_FRAME_EquipUpgrade::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return false;
	}

	bool bGetEnoughMustMaterial = false;
	if( m_iMustMaterialCount > 0 )
	{
		if( m_iMustMaterialCount == 1
			&& m_additionalItemBagIndex[EquipUpgradeAdditionalOne] != -1
			&& m_bMaterialEnough[EquipUpgradeAdditionalOne]
		)
			bGetEnoughMustMaterial = true;
		else if( m_iMustMaterialCount == 2
			&& 		m_additionalItemBagIndex[EquipUpgradeAdditionalOne] != -1
			&&		m_bMaterialEnough[EquipUpgradeAdditionalOne]
			&& 		m_additionalItemBagIndex[EquipUpgradeAdditionalTwo] != -1
			&&		m_bMaterialEnough[EquipUpgradeAdditionalTwo]
			)
			bGetEnoughMustMaterial = true;
	}
	if (m_EquipItemBagIndex == -1
		||		!bGetEnoughMustMaterial
		)
	{
		return false;
	}
	if (!thePlayerRole.HaveEnoughMoney(m_needMoney))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString(eText_Error_NotEnoughMoney) );
		return false;
	}

	if( !m_bStartIntonate )
	{
		if (m_additionalItemBagIndex[EquipUpgradeAdditionalOptional] == -1 || (!m_bMaterialEnough[EquipUpgradeAdditionalOptional]))
		{
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipUpgrade_NoOptional),"",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,UpgradeEquip);
		}
		else
		{
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipUpgrade_ClearStarAttribute),"",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,UpgradeEquip);
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_EquipUpgrade::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	// 		if (pItemSrc && pItemSrc->IsNull() == false)
	// 			return false;
	// 
	// 		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	// 		if( pItemCommon )
	// 		{
	// 			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
	// 			if (pUpgradeData)
	// 			{
	// 				ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	// 				if( !pImageSender )
	// 					return false;
	// 
	// 				// 包裹里
	// 				if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
	// 				{		
	// 					SetOptionalMaterial(pItemDrag,0);
	// 					return true;
	// 				}
	// 				else
	// 				{
	// 					return false;
	// 				}
	// 			}
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	// 		SetMaterialBagIndex(-1,true,0);
	// 		m_pAdditionalListImage[0]->Clear();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	// 		if (pItemSrc && pItemSrc->IsNull() == false)
	// 			return false;
	// 
	// 		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	// 		if( pItemCommon )
	// 		{
	// 			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
	// 			if (pUpgradeData)
	// 			{
	// 				ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	// 				if( !pImageSender )
	// 					return false;
	// 
	// 				// 包裹里
	// 				if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
	// 				{		
	// 					SetOptionalMaterial(pItemDrag,1);
	// 					return true;
	// 				}
	// 				else
	// 				{
	// 					return false;
	// 				}
	// 			}
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	// 		SetMaterialBagIndex(-1,true,1);
	// 		m_pAdditionalListImage[1]->Clear();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return false;
	}

	if (pItemSrc && pItemSrc->IsNull() == false)
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (IsOptionalMaterial(pItemDrag->m_pkIconInfo->GetItemId()))
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType( BT_MaterialBag, pImageSender ) )
		{		
			SetOptionalMaterial(pItemDrag,EquipUpgradeAdditionalOptional);
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return false;
	}

	SetMaterialBagIndex(-1,true,EquipUpgradeAdditionalOptional);
	m_pAdditionalListImage[EquipUpgradeAdditionalOptional]->Clear();
	m_pID_TEXT_Additional[EquipUpgradeAdditionalOptional]->SetText("");
	m_pID_TEXT_AdditionalNumber[EquipUpgradeAdditionalOptional]->SetText("");
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	// 		if (pItemSrc && pItemSrc->IsNull() == false)
	// 			return false;
	// 
	// 		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	// 		if (IsOptionalMaterial(pItemDrag->m_pkIconInfo->GetItemId()))
	// 		{
	// 			ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	// 			if( !pImageSender )
	// 				return false;
	// 
	// 			// 包裹里
	// 			if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
	// 			{		
	// 				SetOptionalMaterial(pItemDrag,3);
	// 				return true;
	// 			}
	// 			else
	// 			{
	// 				return false;
	// 			}
	// 		}
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_M4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	// 		SetMaterialBagIndex(-1,true,3);
	// 		m_pAdditionalListImage[3]->Clear();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_EquipUpgrade::ID_LISTIMG_Armour4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// List
void CUI_ID_FRAME_EquipUpgrade::ID_LIST_ChooseItemOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if(!m_pID_FRAME_EquipUpgrade)
	{
		assert(false&&"ui error");
		return ;
	}

	if (pItem)
	{
		m_nAimItemID = pItem->m_nID;
		const UpToEquipInfo* pUpToEquip = (UpToEquipInfo*)pItem->m_pData;
		m_needMoney = pUpToEquip->GetCostMoney();
	}
	RefreshMaterialUI();
}

// 装载UI
bool CUI_ID_FRAME_EquipUpgrade::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\EquipUpgrade.MEUI" , false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\EquipUpgrade.MEUI]失败")
			return false;
	}
	else if ( dwResult != 1/*文件版本号*/ )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\EquipUpgrade.MEUI]与源代码版本不一样")
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_EquipUpgrade::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_EquipUpgrade, s_CUI_ID_FRAME_EquipUpgradeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_EquipUpgrade, s_CUI_ID_FRAME_EquipUpgradeOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_EquipUpgrade, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EquipUpgradeID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_EquipUpgrade, ID_BUTTON_help, s_CUI_ID_FRAME_EquipUpgradeID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_EquipUpgrade, ID_BUTTON_Ok, s_CUI_ID_FRAME_EquipUpgradeID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_EquipUpgrade, ID_BUTTON_Cancel, s_CUI_ID_FRAME_EquipUpgradeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_M1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_M1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_M2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_M2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_M3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_M3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_M4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_M4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_M4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_M4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour1OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4, s_CUI_ID_FRAME_EquipUpgradeID_LISTIMG_Armour4OnIconRButtonUp );
	theUiManager.OnListSelectChange( ID_FRAME_EquipUpgrade, ID_LIST_ChooseItem, s_CUI_ID_FRAME_EquipUpgradeID_LIST_ChooseItemOnListSelectChange );

	m_pID_FRAME_EquipUpgrade = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_EquipUpgrade );
// 	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_RightTitle );
// 	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_MiddleTitle );
// 	m_pID_PICTURE_LeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_LeftMiddle );
// 	m_pID_PICTURE_RightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_RightMiddle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_BUTTON_help );
// 	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_UseMoney );
	//m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_LeftTitle );
	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_TitleWord );
// 	m_pID_PICTURE_ExplainWall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_ExplainWall3 );
// 	m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_ItemWall2 );
// 	m_pID_TEXT_ArmourName = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_ArmourName );
	m_pID_TEXT_M1Name = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M1Name );
	//m_pID_TEXT_Word2 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Word2 );
	m_pID_PICTURE_16595 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_16595 );
	m_pID_LISTIMG_M1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_M1 );
	m_pID_TEXT_M1Num = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M1Num );
	m_pID_LISTIMG_M2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_M2 );
	m_pID_TEXT_M2Name = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M2Name );
	m_pID_TEXT_M2Num = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M2Num );
	m_pID_LISTIMG_M3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_M3 );
	m_pID_TEXT_M3Name = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M3Name );
	m_pID_TEXT_M3Num = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M3Num );
	m_pID_LISTIMG_M4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_M4 );
	m_pID_TEXT_M4Name = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M4Name );
	m_pID_TEXT_M4Num = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_M4Num );
	m_pID_TEXT_Explain = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Explain );
	m_pID_LISTIMG_Armour1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour1 );
	m_pID_LISTIMG_Armour2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour2 );
	m_pID_LISTIMG_Armour3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour3 );
	m_pID_LISTIMG_Armour4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LISTIMG_Armour4 );
	m_pID_TEXT_Armour1 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Armour1 );
	m_pID_TEXT_Armour2 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Armour2 );
	m_pID_TEXT_Armour3 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Armour3 );
	m_pID_TEXT_Armour4 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_Armour4 );
	m_pID_LIST_ChooseItem = (ControlList*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_LIST_ChooseItem );
	m_pID_PICTURE_WeaponTitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_WeaponTitleWord );
	m_pID_TEXT_WeaponExplain = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_TEXT_WeaponExplain );
	m_pID_PICTURE_UpgradeEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipUpgrade, ID_PICTURE_UpgradeEffect );
// 	assert( m_pID_FRAME_EquipUpgrade );
// 	assert( m_pID_PICTURE_RightTitle );
// 	assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_PICTURE_LeftMiddle );
// 	assert( m_pID_PICTURE_RightMiddle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_PICTURE_ItemWall );
// 	assert( m_pID_LISTIMG_Armour );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_PICTURE_LeftTitle );
// 	assert( m_pID_PICTURE_TitleWord );
// 	assert( m_pID_PICTURE_ExplainWall3 );
// 	assert( m_pID_PICTURE_ItemWall2 );
// 	assert( m_pID_TEXT_ArmourName );
// 	assert( m_pID_TEXT_M1Name );
// 	assert( m_pID_TEXT_Word2 );
// 	assert( m_pID_PICTURE_16595 );
// 	assert( m_pID_LISTIMG_M1 );
// 	assert( m_pID_TEXT_M1Num );
// 	assert( m_pID_LISTIMG_M2 );
// 	assert( m_pID_TEXT_M2Name );
// 	assert( m_pID_TEXT_M2Num );
// 	assert( m_pID_LISTIMG_M3 );
// 	assert( m_pID_TEXT_M3Name );
// 	assert( m_pID_TEXT_M3Num );
// 	assert( m_pID_LISTIMG_M4 );
// 	assert( m_pID_TEXT_M4Name );
// 	assert( m_pID_TEXT_M4Num );
// 	assert( m_pID_TEXT_Explain );
// 	assert( m_pID_LISTIMG_Armour1 );
// 	assert( m_pID_LISTIMG_Armour2 );
// 	assert( m_pID_LISTIMG_Armour3 );
// 	assert( m_pID_LISTIMG_Armour4 );
// 	assert( m_pID_TEXT_Armour1 );
// 	assert( m_pID_TEXT_Armour2 );
// 	assert( m_pID_TEXT_Armour3 );
// 	assert( m_pID_TEXT_Armour4 );
// 	assert( m_pID_LIST_ChooseItem );
// 	assert( m_pID_PICTURE_WeaponTitleWord );
// 	assert( m_pID_TEXT_WeaponExplain );
// 	assert( m_pID_PICTURE_UpgradeEffect );
	m_pAimlListImage[0] = m_pID_LISTIMG_Armour1;
	m_pAimlListImage[1] = m_pID_LISTIMG_Armour2;
	m_pAimlListImage[2] = m_pID_LISTIMG_Armour3;
	m_pAimlListImage[3] = m_pID_LISTIMG_Armour4;

	m_pID_TEXT_Aim[0] = m_pID_TEXT_Armour1;
	m_pID_TEXT_Aim[1] = m_pID_TEXT_Armour2;
	m_pID_TEXT_Aim[2] = m_pID_TEXT_Armour3;
	m_pID_TEXT_Aim[3] = m_pID_TEXT_Armour4;

	m_pID_FRAME_EquipUpgrade->SetOnVisibleChangedFun(OnVisibleChanged);

	m_pAdditionalListImage[EquipUpgradeAdditionalOne] = m_pID_LISTIMG_M1;
	m_pAdditionalListImage[EquipUpgradeAdditionalTwo] = m_pID_LISTIMG_M2;
	m_pAdditionalListImage[EquipUpgradeAdditionalOptional] = m_pID_LISTIMG_M3;
	m_pAdditionalListImage[EquipUpgradeAdditionalBak] = m_pID_LISTIMG_M4;

	m_pID_TEXT_Additional[EquipUpgradeAdditionalOne] = m_pID_TEXT_M1Name;
	m_pID_TEXT_Additional[EquipUpgradeAdditionalTwo] = m_pID_TEXT_M2Name;
	m_pID_TEXT_Additional[EquipUpgradeAdditionalOptional] = m_pID_TEXT_M3Name;
	m_pID_TEXT_Additional[EquipUpgradeAdditionalBak] = m_pID_TEXT_M4Name;

	m_pID_TEXT_AdditionalNumber[EquipUpgradeAdditionalOne] = m_pID_TEXT_M1Num;
	m_pID_TEXT_AdditionalNumber[EquipUpgradeAdditionalTwo] = m_pID_TEXT_M2Num;
	m_pID_TEXT_AdditionalNumber[EquipUpgradeAdditionalOptional] = m_pID_TEXT_M3Num;
	m_pID_TEXT_AdditionalNumber[EquipUpgradeAdditionalBak] = m_pID_TEXT_M4Num;

	m_iMustMaterialCount = 0;
	m_bWeaponUpgrade = false;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
	RECT rc;
	m_pID_PICTURE_UpgradeEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\UpStarEffect\\UpStarEffect", 20, rc, 1400);

	SetVisable(false);

	if (!theEquipUpgradeConfig.IsLoadEquipUpgradeConfig())
	{
		char temp[2048];
		MeSprintf_s(temp,sizeof(temp)/sizeof(char) - 1,"%s\\Data\\Config\\EquipUpgrade.Config",GetRootPath());
		theEquipUpgradeConfig.LoadEquipUpgradeConfig(temp);
	}

	USE_SCRIPT( eUI_OBJECT_EquipUpgrade, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_EquipUpgrade::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_EquipUpgrade );
	m_pID_FRAME_EquipUpgrade = NULL;
// 	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_PICTURE_LeftMiddle = NULL;
// 	m_pID_PICTURE_RightMiddle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	//m_pID_PICTURE_LeftTitle = NULL;
	m_pID_PICTURE_TitleWord = NULL;
// 	m_pID_PICTURE_ExplainWall3 = NULL;
// 	m_pID_PICTURE_ItemWall2 = NULL;
// 	m_pID_TEXT_ArmourName = NULL;
	m_pID_TEXT_M1Name = NULL;
	//m_pID_TEXT_Word2 = NULL;
	m_pID_PICTURE_16595 = NULL;
	m_pID_LISTIMG_M1 = NULL;
	m_pID_TEXT_M1Num = NULL;
	m_pID_LISTIMG_M2 = NULL;
	m_pID_TEXT_M2Name = NULL;
	m_pID_TEXT_M2Num = NULL;
	m_pID_LISTIMG_M3 = NULL;
	m_pID_TEXT_M3Name = NULL;
	m_pID_TEXT_M3Num = NULL;
	m_pID_LISTIMG_M4 = NULL;
	m_pID_TEXT_M4Name = NULL;
	m_pID_TEXT_M4Num = NULL;
	m_pID_TEXT_Explain = NULL;
	m_pID_LISTIMG_Armour1 = NULL;
	m_pID_LISTIMG_Armour2 = NULL;
	m_pID_LISTIMG_Armour3 = NULL;
	m_pID_LISTIMG_Armour4 = NULL;
	m_pID_TEXT_Armour1 = NULL;
	m_pID_TEXT_Armour2 = NULL;
	m_pID_TEXT_Armour3 = NULL;
	m_pID_TEXT_Armour4 = NULL;
	m_pID_LIST_ChooseItem = NULL;
	m_pID_PICTURE_WeaponTitleWord = NULL;
	m_pID_TEXT_WeaponExplain = NULL;
	m_pID_PICTURE_UpgradeEffect = NULL;
	ClearAnim();
	return theUiManager.RemoveFrame( "Data\\UI\\EquipUpgrade.MEUI");
}
// 是否可视
bool CUI_ID_FRAME_EquipUpgrade::_IsVisable()
{
	if (!m_pID_FRAME_EquipUpgrade)
		return false;
	return m_pID_FRAME_EquipUpgrade->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_EquipUpgrade::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_EquipUpgrade)
		return;

	m_pID_FRAME_EquipUpgrade->SetVisable( bVisable );

	if( bVisable )
	{
		if( m_bWeaponUpgrade )	// 武器升阶
		{
			m_pID_PICTURE_WeaponTitleWord->SetVisable(true);
			m_pID_TEXT_WeaponExplain->SetVisable(true);
			m_pID_PICTURE_TitleWord->SetVisable(false);
			m_pID_TEXT_Explain->SetVisable(false);
		}
		else
		{
			m_pID_PICTURE_WeaponTitleWord->SetVisable(false);
			m_pID_TEXT_WeaponExplain->SetVisable(false);
			m_pID_PICTURE_TitleWord->SetVisable(true);
			m_pID_TEXT_Explain->SetVisable(true);
		}
		m_pID_BUTTON_Ok->SetEnable(false);
	}
	else
	{
		m_bWeaponUpgrade = false;
	}
	ClearAnim();
}

void CUI_ID_FRAME_EquipUpgrade::RefreshAllBagEnable()
{
	if( m_EquipItemBagIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_EquipItemBagIndex, true );
	}
	for(int i = 0; i < EquipUpgradeMaxAdditional; ++i)
	{
		if( m_additionalItemBagIndex[i] != -1 )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_additionalItemBagIndex[i], true );
		}
	}

}

void CUI_ID_FRAME_EquipUpgrade::SetEquipItemBagIndex( int index, bool enable )
{
	if (m_EquipItemBagIndex != -1)
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_EquipItemBagIndex, true );
	}

	m_EquipItemBagIndex = index;
	m_EquipItemEnable = enable;
	m_bNeedUpdate = true;

	if( m_EquipItemBagIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_EquipItemBagIndex, true );
	}
	RefreshAimUI();
}

void CUI_ID_FRAME_EquipUpgrade::SetEquipItem( ControlIconDrag::S_ListImg* pItem )
{
	int nItemBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItem );
	if (nItemBagIndex != -1)
	{
		ControlIconDrag::S_ListImg item = *pItem;
		item.m_eEnable = eIcon_Enable;
		m_pID_LISTIMG_Armour->SetItem(&item, 0);
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemCommon )
		{
			DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
			char strItemNameColor[MAX_PATH] = {0};
			MeSprintf_s(strItemNameColor,sizeof(strItemNameColor)/sizeof(char) - 1, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
// 			m_pID_TEXT_ArmourName->SetText(strItemNameColor);
		}
		SetEquipItemBagIndex(nItemBagIndex, false);

	}

}

void CUI_ID_FRAME_EquipUpgrade::ClearInfo()
{
	SetEquipItemBagIndex(-1, true);
	m_pID_LISTIMG_Armour->Clear();
	//m_pID_TEXT_ArmourName->SetText("");
	m_pID_TEXT_UseMoney->SetText("");
	ClearMaterialItemUI();
	m_bNeedUpdate = false;
	ClearAimUI();
	m_iMustMaterialCount = 0;
}

void CUI_ID_FRAME_EquipUpgrade::OnVisibleChanged( ControlObject* pSender )
{
	s_CUI_ID_FRAME_EquipUpgrade.ClearInfo();
	s_CUI_ID_FRAME_EquipUpgrade.ClearAnim();
}

void CUI_ID_FRAME_EquipUpgrade::SetMaterialBagIndex( int index, bool enable,int nAdditionType )
{
	if (m_additionalItemBagIndex[nAdditionType] != -1)
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_additionalItemBagIndex[nAdditionType], true );
	}

	m_additionalItemBagIndex[nAdditionType] = index;
	m_additionalItemEnable[nAdditionType] = enable;
	m_bNeedUpdate = true;

	if( m_additionalItemBagIndex[nAdditionType] != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_additionalItemBagIndex[nAdditionType], true );
	}
}

void CUI_ID_FRAME_EquipUpgrade::SetOptionalMaterial( ControlIconDrag::S_ListImg* pItem,int nAdditionType )
{
	assert(nAdditionType == EquipUpgradeAdditionalOptional);
	int nBagIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItem );
	if (nBagIndex != -1)
	{
		ControlIconDrag::S_ListImg item = *pItem;
		item.m_eEnable = eIcon_Enable;
		item.SetData(item.m_pkIconInfo->GetItemId(),0);
		m_pAdditionalListImage[nAdditionType]->SetItem(&item, 0);

		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
		if( pItemCommon )
		{
			// 材料名根据品质设颜色
			DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemCommon->ustLevel );
			char strItemNameColor[MAX_PATH] = {0};
			MeSprintf_s(strItemNameColor,sizeof(strItemNameColor)/sizeof(char) - 1, "{#%x=%s#}", dwColor, pItemCommon->GetItemName());
			m_pID_TEXT_Additional[nAdditionType]->SetText(strItemNameColor);

			int nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pItemCommon->ustItemID);


			const MaterialInfo* pInfo = NULL;
			SCharItem stItem;	
			thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
			if (pUpgradeData)
			{
				const UpToEquipInfo* pUpToEquip = pUpgradeData->GetUpToEquipByIndex(m_pID_LIST_ChooseItem->GetCurSelIndex());
				if (pUpToEquip)
				{
					for(int i = 0; i < pUpToEquip->GetMaterialCount(); ++i )
					{
						if (pUpToEquip->GetMaterialByIndex(i)->GetMaterialID() == pItemCommon->ustItemID)
						{
							pInfo = pUpToEquip->GetMaterialByIndex(i);
						}

					}
				}				
			}
			if (pInfo)
			{
				m_bMaterialEnough[nAdditionType] = (nItemCount >= pInfo->GetMaterialCount());
				char temp[32];
				if (m_bMaterialEnough[nAdditionType])
				{
					MeSprintf_s( temp,sizeof(temp)/sizeof(char) - 1, "{#FF00FF00=%ld / %ld#}", nItemCount, pInfo->GetMaterialCount() );
				}
				else
				{
					MeSprintf_s( temp,sizeof(temp)/sizeof(char) - 1, "{#FFFF0000=%ld / %ld#}", nItemCount, pInfo->GetMaterialCount() );
				}
				m_pID_TEXT_AdditionalNumber[nAdditionType]->SetText(temp);
			}
		}		

		SetMaterialBagIndex(nBagIndex, false,nAdditionType);
	}

}

void CUI_ID_FRAME_EquipUpgrade::RefreshAimUI()
{
	ClearAimUI();
	if (m_EquipItemBagIndex != -1)
	{
		SCharItem stItem;	
		thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( pItemCommon )
		{
			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
			if (pUpgradeData)
			{
				for(int i = 0; i < pUpgradeData->GetUpToEquipCount(); ++i )
				{
					if (i >= 4 )
					{
						break;
					}

					const UpToEquipInfo* pUpToEquip = pUpgradeData->GetUpToEquipByIndex(i);
					ItemDefine::SItemCommon* pItemAim = GettheItemDetail().GetItemByID( pUpToEquip->GetUpToEquipID() );

					if ( !pUpToEquip || !pItemAim )
						continue;

					ControlIconDrag::S_ListImg item;
					item.SetData(pUpToEquip->GetUpToEquipID(),0);
					item.m_eEnable = eIcon_Enable;
					m_pAimlListImage[i]->SetItem(&item, 0);

					DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemAim->ustLevel );
					char strItemNameColor[MAX_PATH] = {0};
					MeSprintf_s(strItemNameColor,sizeof(strItemNameColor)/sizeof(char) - 1 ,"{#%x=%s#}", dwColor, pItemAim->GetItemName());
					m_pID_TEXT_Aim[i]->SetText(strItemNameColor);
					if (i == 0)
					{
						m_nAimItemID = pUpToEquip->GetUpToEquipID();
						m_needMoney = pUpToEquip->GetCostMoney();
					}						
					ControlList::S_List temp;
					temp.SetData(pItemAim->GetItemName(),pUpToEquip->GetUpToEquipID(),(void*)pUpToEquip,dwColor);
					temp.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
					m_pID_LIST_ChooseItem->AddItem(&temp);
				}
			}
			m_pID_LIST_ChooseItem->SetCurSelIndex(0);
		}

		if( m_bWeaponUpgrade )	// 武器升阶
			m_pID_TEXT_WeaponExplain->SetVisable(false);
		else
			m_pID_TEXT_Explain->SetVisable(false);
	}
	RefreshMaterialUI();

}

void CUI_ID_FRAME_EquipUpgrade::RefreshMaterialUI()
{
	ClearMaterialItemUI();
	if (m_EquipItemBagIndex != -1)
	{
		SCharItem stItem;	
		thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
		ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( pItemCommon )
		{
			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
			if (pUpgradeData)
			{
				const UpToEquipInfo* pUpToEquip = pUpgradeData->GetUpToEquipByIndex(m_pID_LIST_ChooseItem->GetCurSelIndex());
				if (pUpToEquip)
				{
					int nMustCount = 0;
					m_iMustMaterialCount = 0;
					for(int i = 0; i < pUpToEquip->GetMaterialCount(); ++i )
					{
						const MaterialInfo* pInfo = pUpToEquip->GetMaterialByIndex(i);
						ItemDefine::SItemCommon* pItemMaterial = GettheItemDetail().GetItemByID( pInfo->GetMaterialID() );
						if (pItemMaterial == NULL)
						{
							continue;
						}
						// 必需材料个数
						if (pInfo->GetMaterialEffect() == MaterialInfo::ECD_Must)
						{
							++m_iMustMaterialCount;
						}
						else	// 可选材料，从下标为2的格子里开始放
						{
							if( nMustCount < 2 )
								nMustCount = 2;
						}

						{
							ControlIconDrag::S_ListImg item;
							item.SetData(pInfo->GetMaterialID(),0);
							item.m_eEnable = eIcon_Enable;
							m_pAdditionalListImage[nMustCount]->SetItem(&item, 0);
							m_pAdditionalListImage[nMustCount]->SetVisable(true);

							// 材料名根据品质设颜色
							DWORD dwColor = S_IconInfoHero::GetQualityColor( pItemMaterial->ustLevel );
							char strItemNameColor[MAX_PATH] = {0};
							MeSprintf_s(strItemNameColor,sizeof(strItemNameColor)/sizeof(char) - 1, "{#%x=%s#}", dwColor, pItemMaterial->GetItemName());
							if( pInfo->GetMaterialEffect() != MaterialInfo::ECD_Must )
								strcat(strItemNameColor, theXmlString.GetString(eText_Optional));
							m_pID_TEXT_Additional[nMustCount]->SetText(strItemNameColor);

							int nItemCount = thePlayerRole.m_bagMaterial.GetItemCount( pInfo->GetMaterialID());
							if (nItemCount > 0)
							{
								SetMaterialBagIndex(thePlayerRole.m_bagMaterial.GetItemIndexById(pInfo->GetMaterialID()), false,nMustCount);
							}
							m_bMaterialEnough[nMustCount] = (nItemCount >= pInfo->GetMaterialCount());
							char temp[32];
							if (m_bMaterialEnough[nMustCount])
							{
								sprintf( temp, "{#FF00FF00=%ld / %ld#}", nItemCount, pInfo->GetMaterialCount() );
							}
							else
							{
								sprintf( temp, "{#FFFF0000=%ld / %ld#}", nItemCount, pInfo->GetMaterialCount() );
							}

							m_pID_TEXT_AdditionalNumber[nMustCount]->SetText(temp);
							++nMustCount;
							if (nMustCount > 2)
							{
								break;
							}							
						}

					}
					DWORD dwMoney = pUpToEquip->GetCostMoney();
					{
						std::string text = "";
						thePlayerRole.GetGSCStringFromJiaoZi(dwMoney, text);

						//if (thePlayerRole.GetData( CPlayerRole::TYPE_MONEY ) >= dwMoney)
						if(thePlayerRole.HaveEnoughMoney(dwMoney))
							m_pID_TEXT_UseMoney->SetText(text);
						else
							m_pID_TEXT_UseMoney->SetText(text, D3DCOLOR_XRGB(255, 0, 0));
					}
				}

			}

		}
		m_pAdditionalListImage[EquipUpgradeAdditionalOptional]->SetVisable(true);
	}
}

void CUI_ID_FRAME_EquipUpgrade::ClearMaterialItemUI()
{
	for(int i = EquipUpgradeAdditionalOne; i < EquipUpgradeMaxAdditional; ++i)
	{
		SetMaterialBagIndex(-1,true,i);
		m_pAdditionalListImage[i]->Clear();
		m_pAdditionalListImage[i]->SetVisable(false);
		m_pID_TEXT_Additional[i]->Clear();
		m_pID_TEXT_AdditionalNumber[i]->Clear();
	}
}

bool CUI_ID_FRAME_EquipUpgrade::IsOptionalMaterial( unsigned short utItemID )
{
	if( !m_pID_FRAME_EquipUpgrade )
		return false;

	if (m_EquipItemBagIndex ==  -1)
	{
		return false;
	}
	SCharItem stItem;	
	thePlayerRole.m_bag.GetItem( m_EquipItemBagIndex, &stItem );
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
	if( pItemCommon )
	{
		const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
		if (pUpgradeData)
		{
			const UpToEquipInfo* pUpToEquip = pUpgradeData->GetUpToEquipByIndex(m_pID_LIST_ChooseItem->GetCurSelIndex());
			if (pUpToEquip)
			{
				for(int i = 0; i < pUpToEquip->GetMaterialCount(); ++i )
				{
					const MaterialInfo* pInfo = pUpToEquip->GetMaterialByIndex(i);
					if (pInfo->GetMaterialEffect() != MaterialInfo::ECD_Must)
					{
						if (pInfo->GetMaterialID() == utItemID)
						{
							return true;
						}
					}

				}
			}				
		}
	}		
	return false;
}

void CUI_ID_FRAME_EquipUpgrade::SendUpgradeEquipMsg()
{
	if( !m_pID_FRAME_EquipUpgrade )
		return;

	// 开始吟唱
	if( !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_Upgrade_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
}

void CUI_ID_FRAME_EquipUpgrade::EquipUpdateAck( MsgEquipUpgradeAck* pAck)
{
	if( !m_pID_FRAME_EquipUpgrade )
		return;
	switch (pAck->chResult)
	{
	case MsgEquipUpgradeAck::ECD_Success:
		{
			for(int i = EquipUpgradeAdditionalOne; i < EquipUpgradeMaxAdditional; ++i)
			{
				SetMaterialBagIndex(-1,true,i);
			}
			ClearInfo();
			int index = thePlayerRole.m_bag.GetItemIndexByGUID(pAck->nNewEquipGuid);
			if (-1 == index)
				return;
			SCharItem& item = thePlayerRole.m_bag.m_pPackItem[index];
			memcpy_s( item.equipdata.baseRands, sizeof( unsigned short ) * SCharItem::EConstDefine_BaseRandMaxCount, pAck->ustRand,
                sizeof(unsigned short) * SCharItem::EConstDefine_BaseRandMaxCount );
			item.itembaseinfo.value1 = pAck->nElemenet;
			item.SetBounded(pAck->bIsSoulBounded);
			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(index);

			// 刷新钱
			// 				int nMoney = m_needMoney;
			// 
			// 				int gold = nMoney / 10000;
			// 				int silver = (nMoney - gold * 10000) / 100;
			// 				int copper = nMoney - gold * 10000 - silver * 100;

			// 				std::stringstream sstr;
			// 				sstr << theXmlString.GetString(eText_YouLost);
			// 				if (gold > 0)
			// 					sstr << gold << theXmlString.GetString(eText_Money_Gold);
			// 				if (silver > 0)
			// 					sstr << silver << theXmlString.GetString(eText_Money_Silver);
			// 				if (copper > 0)
			// 					sstr << copper << theXmlString.GetString(eText_Money_Copper);
			// 				s_CUI_ChatInfoBox.AddInfo( sstr.str().c_str(), Color_Config.getColor( CC_SystemPromp ) );

			// 				thePlayerRole.Update( CPlayerRole::TYPE_MONEY, thePlayerRole.GetData(CPlayerRole::TYPE_MONEY) - nMoney );
			// 				s_CUI_ID_FRAME_PACK.RefreshMoney();


			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString( eText_EquipUpgrade_Success ) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_ErrorEquip:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString( eText_EquipUpgrade_Cannot ) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_CanNotUpgrade:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString( eText_EquipUpgrade_CanNotUpgrade ) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_LackMaterial:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString( eText_EquipUpgrade_LackMaterial ) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_ErrorMaterial:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString( eText_EquipUpgrade_ErrorMaterial ) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_NotEnoughMoney:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString(eText_Error_NotEnoughMoney) );
			break;
		}
	case MsgEquipUpgradeAck::ECD_PackageFull:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, theXmlString.GetString(eText_NormalPackFull) );
			break;
		}
	default:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_OldRiseStar_Failed, "升阶失败" );
			break;
		}
	}

}

void CUI_ID_FRAME_EquipUpgrade::ClearAimUI()
{
	for (int i = 0; i < EquipUpgradeMaxAimNumber ; ++i)
	{
		m_pAimlListImage[i]->Clear();
		m_pID_TEXT_Aim[i]->SetText("");
	}
	m_nAimItemID = -1;
	m_needMoney = 0;
	m_pID_LIST_ChooseItem->Clear();
	if( m_bWeaponUpgrade )	// 武器升阶
		m_pID_TEXT_WeaponExplain->SetVisable(true);
	else
		m_pID_TEXT_Explain->SetVisable(true);
}

bool CUI_ID_FRAME_EquipUpgrade::CanItemUpgrade( unsigned short ustItemId )
{
	bool bRet = false;
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustItemId );
	if( pItemCommon )
	{
		if( (m_bWeaponUpgrade && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
			|| (!m_bWeaponUpgrade && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR) )
		{
			const UpgradeData* pUpgradeData = theEquipUpgradeConfig.GetEquipUpgradeData(pItemCommon->ustItemID);
			if (pUpgradeData)
			{
				bRet = true;
			}
		}
	}
	return bRet;
}

void CUI_ID_FRAME_EquipUpgrade::ClearAnim()
{
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
	if( m_bStartIntonate )
	{
		m_bStartIntonate = false;
		s_CUI_Progress.SetProgressComplete();
	}
}

bool CUI_ID_FRAME_EquipUpgrade::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    // NEXT无此功能，直接返回 false
    return false;
}
