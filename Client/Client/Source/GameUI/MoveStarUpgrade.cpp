/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\升星\MoveStarUpgrade.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MoveStarUpgrade.h"
#include "StarLevelUpConfig.h"
#include "GlobalDef.h"
#include "ui/Pack.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "UIMgr.h"
#include "XmlStringLanguage.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "Progress.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_MoveStarUpgrade s_CUI_ID_FRAME_MoveStarUpgrade;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MoveStarUpgrade, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MoveStarUpgrade, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_ResultOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_ResultOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_ResultOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_ResultOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_MaterialOnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2OnIconRButtonUp )
CUI_ID_FRAME_MoveStarUpgrade::CUI_ID_FRAME_MoveStarUpgrade()
{
	// Member
	m_pID_FRAME_MoveStarUpgrade = NULL;
// 	m_pID_PICTURE_Material2 = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_LISTIMG_Result = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_Material = NULL;
	m_pID_LISTIMG_Material = NULL;
	//m_pID_LISTIMG_Material2 = NULL;
	m_pID_TEXT_RateZ = NULL;
	m_pID_TEXT_Rate = NULL;
	m_pID_PICTURE_MoveStarUpgradeEffect = NULL;

	m_iMoveStarItemIndex = -1;
	m_n64MoveStarItemGuid = 0;
	m_iMoveStarItemId = -1;
	m_uchItemBagType1 = 0;
	m_iMaterialIndex1 = -1;
	m_n64MaterialGuid1 = 0;
#if 0
	m_uchItemBagType2 = 0;
	m_iMaterialIndex2 = -1;
	m_n64MaterialGuid2 = 0;
#endif
	m_iMaterialItemId = -1;
	m_fRate = 0.f;
	m_dwCostMoney = 0;
	m_fAdditionalRate = 0.f;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}
// Frame
bool CUI_ID_FRAME_MoveStarUpgrade::OnFrameRun()
{
	if( IsVisable() )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
		{
			float fMeX,fMeY,fMeZ;			
			pMe->GetPos( &fMeX, &fMeY, &fMeZ );
			Vector v;
			float dist = pMe->GetDistToTarget( m_vVisiblePos.x, m_vVisiblePos.y );			
			if( dist > 12.0f )
			{
				SetVisable( false );
			}
		}

		// 走路或跳跃打断吟唱
		if( m_bStartIntonate )
		{
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

			if( CanUpgrate(false) )
			{
				m_slideAnim.StartAnimation(HQ_TimeGetTime());
				m_bStartAnim = true;

				MsgMoveStarLevelUpReq msg;
				msg.ustItemIndex = m_iMoveStarItemIndex;
				msg.n64ItemGuid = m_n64MoveStarItemGuid;

				msg.uchItemBagType1 = m_uchItemBagType1;
				msg.ustMaterialIndex1 = m_iMaterialIndex1;
				msg.n64MaterialGuid1 = m_n64MaterialGuid1;
				msg.ustMaterialCount = m_shMaterialCount;

				//msg.uchItemBagType2 = m_uchItemBagType2;
				//msg.ustMaterialIndex2 = m_iMaterialIndex2;
				//msg.n64MaterialGuid2 = m_n64MaterialGuid2;
				GettheNetworkInput().SendMsg( &msg );
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_MoveStarUpgrade::OnFrameRender()
{
	if( m_bStartAnim )
	{
		RECT rc;
		m_pID_PICTURE_MoveStarUpgradeEffect->GetRealRect(&rc);
		m_slideAnim.Update(HQ_TimeGetTime(),&rc);
		if (!m_slideAnim.IsInAnimation())
		{
			m_bStartAnim = false;
			m_slideAnim.UnRelativePicResource();
		}
	}

	return true;
}
// Button
// bool CUI_ID_FRAME_MoveStarUpgrade::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_MoveStarUpgrade )
// 		return false;
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_MoveStarUpgrade::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_MoveStarUpgrade )
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_ResultOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
			PutItemFromPack( pSender, pItemDrag, iBagType, index);
	}

	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_ResultOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_ResultOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_ResultOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	ClearMoveStarItem();
	ClearMaterials();
	return false;
}
// Button
bool CUI_ID_FRAME_MoveStarUpgrade::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	if( CanUpgrate(true) && !m_bStartIntonate )
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			// 吟唱
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_MoveStarUpgrade_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_MoveStarUpgrade::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
			PutItemFromPack( pSender, pItemDrag, iBagType, index);
	}
	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	ClearMaterial1();
	m_pID_BUTTON_Ok->SetEnable(false);
	return false;
}
// ListImg / ListEx
//bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
//										ControlIconDrag::S_ListImg* pItemDrag,
//										ControlIconDrag::S_ListImg* pItemSrc )
//{
//	if( !m_pID_FRAME_MoveStarUpgrade )
//		return false;
//	if( !pSender )
//		return false;
//
//	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
//	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
//	if( iBagType != -1 )
//	{
//		int index = pImageSender->GetItemIndex( pItemDrag );
//		if( index != -1 )
//			PutItemFromPack( pSender, pItemDrag, iBagType, index);
//	}
//	return false;
//}
//bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_MoveStarUpgrade )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_MoveStarUpgrade )
//		return false;
//	return false;
//}
//bool CUI_ID_FRAME_MoveStarUpgrade::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
//{
//	if( !m_pID_FRAME_MoveStarUpgrade )
//		return false;
//#if 0
//	ClearMaterial2();
//#endif
//	return false;
//}

	// 装载UI
bool CUI_ID_FRAME_MoveStarUpgrade::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MoveStarUpgrade.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MoveStarUpgrade.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MoveStarUpgrade::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MoveStarUpgrade, s_CUI_ID_FRAME_MoveStarUpgradeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MoveStarUpgrade, s_CUI_ID_FRAME_MoveStarUpgradeOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_MoveStarUpgrade, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MoveStarUpgradeID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_MoveStarUpgrade, ID_BUTTON_help, s_CUI_ID_FRAME_MoveStarUpgradeID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_ResultOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_ResultOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_ResultOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_ResultOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_MoveStarUpgrade, ID_BUTTON_Ok, s_CUI_ID_FRAME_MoveStarUpgradeID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MoveStarUpgrade, ID_BUTTON_Cancel, s_CUI_ID_FRAME_MoveStarUpgradeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_MaterialOnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_Material2OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_Material2OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_Material2OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_MoveStarUpgradeID_LISTIMG_Material2OnIconRButtonUp );

	m_pID_FRAME_MoveStarUpgrade = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MoveStarUpgrade );
// 	m_pID_PICTURE_Material2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_PICTURE_Material2 );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_BUTTON_help );
	m_pID_LISTIMG_Result = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Result );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_TEXT_UseMoney );
	m_pID_PICTURE_Material = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_PICTURE_Material );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material );
	//m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_LISTIMG_Material2 );
	m_pID_TEXT_RateZ = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_TEXT_RateZ );
	m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_TEXT_Rate );
	m_pID_PICTURE_MoveStarUpgradeEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStarUpgrade, ID_PICTURE_MoveStarUpgradeEffect );
// 	assert( m_pID_FRAME_MoveStarUpgrade );
// 	assert( m_pID_PICTURE_Material2 );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	assert( m_pID_LISTIMG_Result );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_PICTURE_Material );
// 	assert( m_pID_LISTIMG_Material );
// 	assert( m_pID_LISTIMG_Material2 );
// 	assert( m_pID_TEXT_RateZ );
// 	assert( m_pID_TEXT_Rate );
// 	assert( m_pID_PICTURE_MoveStarUpgradeEffect );

	m_iMoveStarItemIndex = -1;
	m_n64MoveStarItemGuid = 0;
	m_iMoveStarItemId = -1;
	m_uchItemBagType1 = 0;
	m_iMaterialIndex1 = -1;
	m_n64MaterialGuid1 = 0;
#if 0
	m_uchItemBagType2 = 0;
	m_iMaterialIndex2 = -1;
	m_n64MaterialGuid2 = 0;
#endif
	m_iMaterialItemId = -1;
	m_fRate = 0.f;
	m_dwCostMoney = 0;
	m_fAdditionalRate = 0.f;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;

	RECT rc;
	m_pID_PICTURE_MoveStarUpgradeEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\StarUpgradeEffect\\StarUpgradeEffect", 19, rc, 1400);

	SetVisable(false);
	m_pID_FRAME_MoveStarUpgrade->SetOnVisibleChangedFun(OnVisibleChanged);

	USE_SCRIPT( eUI_OBJECT_MoveStarUpgrade, this );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MoveStarUpgrade::_UnLoadUI()
{
	if( IsVisable() )
		SetVisable(false);

	CLOSE_SCRIPT( eUI_OBJECT_MoveStarUpgrade );

	m_pID_FRAME_MoveStarUpgrade = NULL;
// 	m_pID_PICTURE_Material2 = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_LISTIMG_Result = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_Material = NULL;
	m_pID_LISTIMG_Material = NULL;
//	m_pID_LISTIMG_Material2 = NULL;
	m_pID_TEXT_RateZ = NULL;
	m_pID_TEXT_Rate = NULL;
	m_pID_PICTURE_MoveStarUpgradeEffect = NULL;
	ClearAnim();
	return theUiManager.RemoveFrame( "Data\\UI\\MoveStarUpgrade.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MoveStarUpgrade::_IsVisable()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	return m_pID_FRAME_MoveStarUpgrade->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MoveStarUpgrade::_SetVisable( const bool bVisible )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;
	m_pID_FRAME_MoveStarUpgrade->SetVisable( bVisible );

	if (bVisible)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();

		s_CUI_ID_FRAME_PACK.SetVisable(true);
		m_pID_BUTTON_Ok->SetEnable(false);
	}
	ClearAnim();
}

bool CUI_ID_FRAME_MoveStarUpgrade::PutItemFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;
	if( !pSender || !pItemDrag || !pItemDrag->m_pkIconInfo || iItemIndex < 0 )
		return false;

	int iItemId = pItemDrag->m_pkIconInfo->GetItemId();
	if( iItemId == InvalidLogicNumber )
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( iItemId );
	if( !pItemCommon )
		return false;

	// 是否移星石
	const MoveStarLevelUp* pMoveStarLevelUp = theStarLevelUpConfig.GetMoveStarLevelUp(iItemId);
	if( pMoveStarLevelUp )
	{
		if( SetMoveStarItemBagIndex(iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
		{
			m_iMoveStarItemId = iItemId;
			m_iMaterialItemId = pMoveStarLevelUp->GetMaterialID();
			//m_fRate = pMoveStarLevelUp->GetModulus();
			m_dwCostMoney = pMoveStarLevelUp->GetCostMoney();
			m_fAdditionalRate = 0.f;

			ControlIconDrag::S_ListImg item = *pItemDrag;
			item.m_eEnable = eIcon_Enable;
			m_pID_LISTIMG_Result->Clear();
			m_pID_LISTIMG_Result->SetItem(&item, 0);

			// 不确定玩家要放几个材料，所以不自动塞材料
#if 0
			// 自动放入升级材料
			// 先找材料包
			int iMatIndex = thePlayerRole.m_bagMaterial.GetItemIndexById(m_iMaterialItemId);
			if( iMatIndex != -1 )
			{
				SCharItem item;
				if( thePlayerRole.m_bagMaterial.GetItem( iMatIndex, &item ) )
				{
					ControlIconDrag::S_ListImg* pItemMaterial = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_MaterialBag, iMatIndex);
					if( pItemMaterial && pItemMaterial->m_pkIconInfo
						&& SetMaterial1(BT_MaterialBag, iMatIndex, pItemMaterial->m_pkIconInfo->GetOnlyId()) )
					{
						ControlIconDrag::S_ListImg item = *pItemMaterial;
						item.m_eEnable = eIcon_Enable;
						m_pID_LISTIMG_Material->Clear();
						m_pID_LISTIMG_Material->SetItem(&item, 0);

						// 显示成功率和消耗金钱
						RefreshRateAndMoney(m_fRate, m_dwCostMoney);

						// 激活确定按钮
						m_pID_BUTTON_Ok->SetEnable(true);
						return true;
					}
				}
			}
			else	// 找普通包
			{
				iMatIndex = thePlayerRole.m_bag.GetItemIndexById(m_iMaterialItemId);
				if( iMatIndex != -1 )
				{
					SCharItem item;
					if( thePlayerRole.m_bag.GetItem( iMatIndex, &item ) )
					{
						ControlIconDrag::S_ListImg* pItemMaterial = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag, iMatIndex);
						if( pItemMaterial && pItemMaterial->m_pkIconInfo
							&& SetMaterial1(BT_NormalItemBag, iMatIndex, pItemMaterial->m_pkIconInfo->GetOnlyId()) )
						{
							ControlIconDrag::S_ListImg item = *pItemMaterial;
							item.m_eEnable = eIcon_Enable;
							m_pID_LISTIMG_Material->Clear();
							m_pID_LISTIMG_Material->SetItem(&item, 0);

							// 显示成功率和消耗金钱
							RefreshRateAndMoney(m_fRate, m_dwCostMoney);

							// 激活确定按钮
							m_pID_BUTTON_Ok->SetEnable(true);
							return true;
						}
					}
				}
			}
#endif
			return true;
		}
	}
	// 升级材料
	else if( m_iMoveStarItemIndex != -1 && m_iMaterialItemId >= 0 && m_iMoveStarItemId >= 0 )
	{
		// 是否必需材料
		if( iItemId == m_iMaterialItemId )
		{
			MoveStarLevelUp* pMoveStarLevelUp = (MoveStarLevelUp*)theStarLevelUpConfig.GetMoveStarLevelUp(m_iMoveStarItemId);
			if( pMoveStarLevelUp && SetMaterial1(iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
			{
				m_shMaterialCount = min(pItemDrag->m_pkIconInfo->Count(), pMoveStarLevelUp->GetMaxCount());
				m_fRate = pMoveStarLevelUp->GetModulus(m_shMaterialCount);
				m_fAdditionalRate = 0.f;

				ControlIconDrag::S_ListImg item = *pItemDrag;
				item.m_eEnable = eIcon_Enable;
				item.m_pkIconInfo->SetData(pItemDrag->m_pkIconInfo->GetItemId(), m_shMaterialCount);
				m_pID_LISTIMG_Material->Clear();
				m_pID_LISTIMG_Material->SetItem(&item, 0);

				// 显示成功率和消耗金钱
				RefreshRateAndMoney(m_fRate+m_fAdditionalRate, m_dwCostMoney);

				// 激活确定按钮
				m_pID_BUTTON_Ok->SetEnable(true);
				return true;
			}
		}
		else
		{
			// 无辅助材料
#if 0
			// 是否辅助材料
			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( iItemId );
			if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL )
			{
				ItemDefine::SCreateMaterial* pMaterialCommon = static_cast< ItemDefine::SCreateMaterial* >( pItemCommon );
				if ( pMaterialCommon && pMaterialCommon->stMaterialType == CItemDetail::ematerial_addmodulus )
				{
					if( SetMaterial2(iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
					{
						ControlIconDrag::S_ListImg item = *pItemDrag;
						item.m_eEnable = eIcon_Enable;
						m_pID_LISTIMG_Material2->Clear();
						m_pID_LISTIMG_Material2->SetItem(&item, 0);

						m_fAdditionalRate = pMaterialCommon->fAddIntensifyRate;
						// 显示成功率和消耗金钱
						if( m_iMoveStarItemIndex != -1 )
							RefreshRateAndMoney(m_fRate+m_fAdditionalRate, m_dwCostMoney);

						return true;
					}
				}
			}
#endif
		}
	}
	return false;
}

bool CUI_ID_FRAME_MoveStarUpgrade::SetMoveStarItemBagIndex( int iBagType, int index, __int64 n64Guid )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;

	if( index < 0 || index >= thePlayerRole.m_bag.GetNowBagSize() )
		return false;

	// 原背包物品解锁
	int iOldIndex = m_iMoveStarItemIndex;
	if( iOldIndex != -1 )
	{
        m_n64MoveStarItemGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, iOldIndex, true );
	}

	m_iMoveStarItemIndex = index;
	m_n64MoveStarItemGuid = n64Guid;

	// 锁定包裹物品
	if( m_iMoveStarItemIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_iMoveStarItemIndex, true );
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}
	return true;
}

bool CUI_ID_FRAME_MoveStarUpgrade::SetMaterial1( int iBagType, int index, __int64 n64Guid )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;

	CItemBag2* pBag = NULL;
	switch (iBagType)
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	default:
		break;
	}
	if( !pBag )
		return false;

	if( index < 0 || index >= pBag->GetNowBagSize() )
		return false;

	// 原背包物品解锁
    m_n64MaterialGuid1 = 0;
	EnableBagItem(true, m_uchItemBagType1, m_iMaterialIndex1);

	m_uchItemBagType1 = iBagType;
	m_iMaterialIndex1 = index;
	m_n64MaterialGuid1 = n64Guid;

	// 锁定包裹物品
	if( m_iMaterialIndex1 != -1 )
	{
		EnableBagItem(false, m_uchItemBagType1, m_iMaterialIndex1);
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}
	return true;
}
#if 0
bool CUI_ID_FRAME_MoveStarUpgrade::SetMaterial2( int iBagType, int index, __int64 n64Guid )
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return false;

	CItemBag2* pBag = NULL;
	switch (iBagType)
	{
	case BT_NormalItemBag:
		pBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pBag = &thePlayerRole.m_bagMaterial;
		break;
	case BT_TaskBag:
		pBag = &thePlayerRole.m_bagTask;
		break;
	default:
		break;
	}
	if( !pBag )
		return false;

	if( index < 0 || index >= pBag->GetNowBagSize() )
		return false;

	// 原背包物品解锁
	EnableBagItem(true, m_uchItemBagType2, m_iMaterialIndex2);

	m_uchItemBagType2 = iBagType;
	m_iMaterialIndex2 = index;
	m_n64MaterialGuid2 = n64Guid;

	// 锁定包裹物品
	if( m_iMaterialIndex2 != -1 )
	{
		EnableBagItem(false, m_uchItemBagType2, m_iMaterialIndex2);
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}
	return true;
}
#endif
void CUI_ID_FRAME_MoveStarUpgrade::ClearMoveStarItem()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;
	if( m_iMoveStarItemIndex != -1 )
	{
        m_n64MoveStarItemGuid = 0;
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_iMoveStarItemIndex, true );
	}

	m_iMoveStarItemIndex = -1;
	m_n64MoveStarItemGuid = 0;
	m_pID_LISTIMG_Result->Clear();
	m_pID_TEXT_Rate->SetText("");
	m_pID_TEXT_UseMoney->SetText("");
}

void CUI_ID_FRAME_MoveStarUpgrade::ClearMaterial1()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;
    m_n64MaterialGuid1 = 0;
	EnableBagItem(true, m_uchItemBagType1, m_iMaterialIndex1);

	m_uchItemBagType1 = 0;
	m_iMaterialIndex1 = -1;
	m_pID_LISTIMG_Material->Clear();
	m_pID_TEXT_Rate->SetText("");
	m_pID_TEXT_UseMoney->SetText("");
	if( IsVisable() )
		m_pID_BUTTON_Ok->SetEnable(false);
}
#if 0
void CUI_ID_FRAME_MoveStarUpgrade::ClearMaterial2()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;
	EnableBagItem(true, m_uchItemBagType2, m_iMaterialIndex2);

	m_uchItemBagType2 = 0;
	m_iMaterialIndex2 = -1;
	m_n64MaterialGuid2 = 0;
	m_fAdditionalRate = 0.f;
	m_pID_LISTIMG_Material2->Clear();
	if( m_iMaterialIndex1 != -1 )
		RefreshRateAndMoney(m_fRate, m_dwCostMoney);
}
#endif
void CUI_ID_FRAME_MoveStarUpgrade::ClearAll()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;

	ClearMoveStarItem();
	ClearMaterials();
	if( IsVisable() )
		m_pID_BUTTON_Ok->SetEnable(false);
}

void CUI_ID_FRAME_MoveStarUpgrade::ClearMaterials()
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;
	ClearMaterial1();
	if( IsVisable() )
		m_pID_BUTTON_Ok->SetEnable(false);
#if 0
	ClearMaterial2();
#endif
}

void CUI_ID_FRAME_MoveStarUpgrade::RefreshRateAndMoney( float rate, DWORD dwMoney )
{
	char szBuff[256] = {0};
	sprintf_s(szBuff, sizeof(szBuff)/sizeof(char) -1, "%d%%", (int)(rate * 100) );
	m_pID_TEXT_Rate->SetText(szBuff);

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(dwMoney, text);

	*m_pID_TEXT_UseMoney = text;
}

void CUI_ID_FRAME_MoveStarUpgrade::OnVisibleChanged(ControlObject* pSender)
{
	s_CUI_ID_FRAME_MoveStarUpgrade.ClearAll();
	s_CUI_ID_FRAME_MoveStarUpgrade.ClearAnim();
}

bool CUI_ID_FRAME_MoveStarUpgrade::CanUpgrate(bool bShowInfo)
{
	if( m_iMoveStarItemIndex != -1 && m_iMaterialIndex1 != -1 )
	{
		// 检查钱够不够
        if(!thePlayerRole.HaveEnoughMoney(m_dwCostMoney))
		{
			if( bShowInfo )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eText_UpgradeFailed_NotEnoughMoney) );
			return false;
		}
		else
			return true;
	}
	return false;
}

void CUI_ID_FRAME_MoveStarUpgrade::OnUpgradeFailed()	// 刷新材料
{
	if( !m_pID_FRAME_MoveStarUpgrade )
		return;

	ClearMaterial1();
#if 0
	pItem = m_pID_LISTIMG_Material2->GetItemByIndex(0);
	if( pItem && !pItem->IsNull() )
	{
		pItem->ChangeCount(false, 1);
		if( !pItem->IsNull() )
		{
			EnableBagItem(false, m_uchItemBagType2, m_iMaterialIndex2);
		}
	}
#endif
}

void CUI_ID_FRAME_MoveStarUpgrade::EnableBagItem(bool bEnable, int iBagType, int iItemIndex )
{
	if( iItemIndex != -1 )
	{
		switch (iBagType)
		{
		case BT_NormalItemBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, iItemIndex, true );
			}
			break;
		case BT_MaterialBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, iItemIndex, true );
			}
			break;
		case BT_TaskBag:
			{
                // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
                CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagTask, iItemIndex, true );
			}
			break;
		default:
			break;
		}
	}
}

void CUI_ID_FRAME_MoveStarUpgrade::ClearAnim()
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

bool CUI_ID_FRAME_MoveStarUpgrade::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_n64MoveStarItemGuid == nGuid || m_n64MaterialGuid1 == nGuid )
    {
        return true;
    }
    return false;
}
