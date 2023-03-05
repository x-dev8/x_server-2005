/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\升星\StarMaterialUpgrade.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "StarMaterialUpgrade.h"
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
#include "Common.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_StarMaterialUpgrade s_CUI_ID_FRAME_StarMaterialUpgrade;
MAP_FRAME_RUN( s_CUI_ID_FRAME_StarMaterialUpgrade, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_StarMaterialUpgrade, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_ResultOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_ResultOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_ResultOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_ResultOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5OnIconRButtonUp )
CUI_ID_FRAME_StarMaterialUpgrade::CUI_ID_FRAME_StarMaterialUpgrade()
{
	// Member
	m_pID_FRAME_StarMaterialUpgrade = NULL;
	ResetObjects();
	ResetMembers();
}
void CUI_ID_FRAME_StarMaterialUpgrade::ResetObjects()
{
	m_pID_PICTURE_Material2 = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_LISTIMG_Result = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_Material = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	m_pID_PICTURE_Material3 = NULL;
	m_pID_LISTIMG_Material3 = NULL;
	m_pID_PICTURE_Material4 = NULL;
	m_pID_LISTIMG_Material4 = NULL;
	m_pID_PICTURE_Material5 = NULL;
	m_pID_LISTIMG_Material5 = NULL;
	m_pID_TEXT_RateZ = NULL;
	m_pID_TEXT_Rate = NULL;
	m_pID_PICTURE_Line2 = NULL;
	m_pID_PICTURE_Line5 = NULL;
	m_pID_PICTURE_Line3 = NULL;
	m_pID_PICTURE_Line4 = NULL;
	m_pID_PICTURE_Line = NULL;
	m_pID_PICTURE_StarUpgradeEffect = NULL;
}
void CUI_ID_FRAME_StarMaterialUpgrade::ResetMembers()
{
	for(int i=0; i<ECD_MaxCount; ++i)
	{
		m_xItem[i].uchItemBagType = 0;
		m_xItem[i].stItemIndex = -1;
		m_xItem[i].n64ItemGuid = 0;
	}
	m_uchMaterialBagType = 0;
	m_stMaterialIndex = -1;
	m_n64MaterialGuid = 0;
	m_iMaterialID = -1;
	m_pComposeData = NULL;
	m_iItemCount = 0;
	m_dwCostMoney = 0;
	m_iMainItemId = -1;
	m_bUpdateRateAndMoney = false;
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}
// Frame
bool CUI_ID_FRAME_StarMaterialUpgrade::OnFrameRun()
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
		
		if( m_bUpdateRateAndMoney )
		{
			RefreshRateAndMoney();
			m_bUpdateRateAndMoney = false;
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
				MsgItemComposeReq msg;
				// 需要的材料
				msg.xItem[MsgItemComposeReq::ECD_PlusItemIndex].uchItemBagType = m_uchMaterialBagType;
				msg.xItem[MsgItemComposeReq::ECD_PlusItemIndex].stItemIndex = m_stMaterialIndex;
				msg.xItem[MsgItemComposeReq::ECD_PlusItemIndex].n64ItemGuid = m_n64MaterialGuid;

				int n = 0;
				for(int i=0; i<ECD_MaxCount; ++i)
				{
					if( m_xItem[i].stItemIndex != -1 )
					{
						msg.xItem[n].uchItemBagType = m_xItem[i].uchItemBagType;
						msg.xItem[n].stItemIndex = m_xItem[i].stItemIndex;
						msg.xItem[n].n64ItemGuid = m_xItem[i].n64ItemGuid;
						++n;
					}
				}
				GettheNetworkInput().SendMsg( &msg );

				m_slideAnim.StartAnimation(HQ_TimeGetTime());
				m_bStartAnim = true;
			}
		}
	}
	return true;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::OnFrameRender()
{
	if( m_bStartAnim )
	{
		RECT rc;
		m_pID_PICTURE_StarUpgradeEffect->GetRealRect(&rc);
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
// bool CUI_ID_FRAME_StarMaterialUpgrade::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_StarMaterialUpgrade )
// 		return false;
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_StarMaterialUpgrade::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_StarMaterialUpgrade )
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_ResultOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index) )
				m_bUpdateRateAndMoney = true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_ResultOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_ResultOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_ResultOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	ClearMaterial();
	m_bUpdateRateAndMoney = true;
	return false;
}
// Button
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;

	if( CanUpgrate(true) )
	{
		// 吟唱
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if( pMe && !pMe->IsMoving() && !pMe->IsJumping() )
		{
			m_bStartIntonate = true;
			m_dwStartIntonateTime = HQ_TimeGetTime();
			m_nIntonateTime = 3000;
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_StarMaterialUpgrade_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}
	return true;
}
// Button
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index, 0 ) )
			{
				m_bUpdateRateAndMoney = true;
			}
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	// 清除主合成物，则把其他4个都清除
	for(int i=0; i<ECD_MaxCount; ++i)
		ClearItem(i);
	ClearMaterial();
	m_bUpdateRateAndMoney = true;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index, 1 ) )
				m_bUpdateRateAndMoney = true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	ClearItem(1);
	m_bUpdateRateAndMoney = true;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index, 2 ) )
				m_bUpdateRateAndMoney = true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	ClearItem(2);
	m_bUpdateRateAndMoney = true;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index, 3 ) )
				m_bUpdateRateAndMoney = true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	ClearItem(3);
	m_bUpdateRateAndMoney = true;
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	if( !pSender )
		return false;

	ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
	int iBagType = s_CUI_ID_FRAME_PACK.GetBagType(pImageSender);
	if( iBagType != -1 )
	{
		int index = pImageSender->GetItemIndex( pItemDrag );
		if( index != -1 )
		{
			if( PutItemFromPack( pSender, pItemDrag, iBagType, index, 4 ) )
				m_bUpdateRateAndMoney = true;
		}
	}
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return false;
}
bool CUI_ID_FRAME_StarMaterialUpgrade::ID_LISTIMG_Material5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	ClearItem(4);
	m_bUpdateRateAndMoney = true;
	return false;
}

	// 装载UI
bool CUI_ID_FRAME_StarMaterialUpgrade::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\StarMaterialUpgrade.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\StarMaterialUpgrade.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_StarMaterialUpgrade::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_StarMaterialUpgrade, s_CUI_ID_FRAME_StarMaterialUpgradeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_StarMaterialUpgrade, s_CUI_ID_FRAME_StarMaterialUpgradeOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_StarMaterialUpgradeID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_help, s_CUI_ID_FRAME_StarMaterialUpgradeID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_ResultOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_ResultOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_ResultOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Result, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_ResultOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_Ok, s_CUI_ID_FRAME_StarMaterialUpgradeID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_Cancel, s_CUI_ID_FRAME_StarMaterialUpgradeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5, s_CUI_ID_FRAME_StarMaterialUpgradeID_LISTIMG_Material5OnIconRButtonUp );

	m_pID_FRAME_StarMaterialUpgrade = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_StarMaterialUpgrade );
	m_pID_PICTURE_Material2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Material2 );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_help );
	m_pID_LISTIMG_Result = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Result );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_TEXT_UseMoney );
	m_pID_PICTURE_Material = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Material );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material );
	m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material2 );
	m_pID_PICTURE_Material3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Material3 );
	m_pID_LISTIMG_Material3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material3 );
	m_pID_PICTURE_Material4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Material4 );
	m_pID_LISTIMG_Material4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material4 );
	m_pID_PICTURE_Material5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Material5 );
	m_pID_LISTIMG_Material5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_LISTIMG_Material5 );
	m_pID_TEXT_RateZ = (ControlText*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_TEXT_RateZ );
	m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_TEXT_Rate );
	m_pID_PICTURE_Line = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Line );
	m_pID_PICTURE_Line2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Line2 );
	m_pID_PICTURE_Line5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Line5 );
	m_pID_PICTURE_Line3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Line3 );
	m_pID_PICTURE_Line4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_Line4 );
	m_pID_PICTURE_StarUpgradeEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_StarMaterialUpgrade, ID_PICTURE_StarUpgradeEffect );
	assert( m_pID_FRAME_StarMaterialUpgrade );
	assert( m_pID_PICTURE_Material2 );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_LISTIMG_Result );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_UseMoneyZ );
	assert( m_pID_TEXT_UseMoney );
	assert( m_pID_PICTURE_Material );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_LISTIMG_Material2 );
	assert( m_pID_PICTURE_Material3 );
	assert( m_pID_LISTIMG_Material3 );
	assert( m_pID_PICTURE_Material4 );
	assert( m_pID_LISTIMG_Material4 );
	assert( m_pID_PICTURE_Material5 );
	assert( m_pID_LISTIMG_Material5 );
	assert( m_pID_TEXT_RateZ );
	assert( m_pID_TEXT_Rate );
	assert( m_pID_PICTURE_Line2 );
	assert( m_pID_PICTURE_Line5 );
	assert( m_pID_PICTURE_Line3 );
	assert( m_pID_PICTURE_Line4 );
	assert( m_pID_PICTURE_Line );
	assert( m_pID_PICTURE_StarUpgradeEffect );

	RECT rc;
	m_pID_PICTURE_StarUpgradeEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\StarUpgradeEffect\\StarUpgradeEffect", 19, rc, 1400);

	SetVisable(false);
	m_pID_FRAME_StarMaterialUpgrade->SetOnVisibleChangedFun(OnVisibleChanged);

	USE_SCRIPT( eUI_OBJECT_StarMaterialUpgrade, this );
	return true;
}
	// 卸载UI
bool CUI_ID_FRAME_StarMaterialUpgrade::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_StarMaterialUpgrade );
	m_pID_FRAME_StarMaterialUpgrade = NULL;
	ClearAnim();
	ResetObjects();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\StarMaterialUpgrade.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_StarMaterialUpgrade::_IsVisable()
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;
	return m_pID_FRAME_StarMaterialUpgrade->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_StarMaterialUpgrade::_SetVisable( const bool bVisible )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;
	m_pID_FRAME_StarMaterialUpgrade->SetVisable( bVisible );

	if (bVisible)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();

		s_CUI_ID_FRAME_PACK.SetVisable(true);
		m_pID_BUTTON_Ok->SetEnable(false);

		m_pID_PICTURE_Line->SetVisable(false);
		m_pID_PICTURE_Line2->SetVisable(false);
		m_pID_PICTURE_Line3->SetVisable(false);
		m_pID_PICTURE_Line4->SetVisable(false);
		m_pID_PICTURE_Line5->SetVisable(false);
	}
	else
	{
		ClearAll();
		m_iItemCount = 0;
	}
	ClearAnim();
}

bool CUI_ID_FRAME_StarMaterialUpgrade::PutItemFromPack( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag, int iBagType, int iItemIndex,
													   int iItemSlot/* = -1*/ )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;

	if( !pSender || !pItemDrag || !pItemDrag->m_pkIconInfo || iItemIndex < 0 )
		return false;

	int iItemId = pItemDrag->m_pkIconInfo->GetItemId();
	if( iItemId == InvalidLogicNumber )
		return false;

	bool bPutToSlot = (iItemSlot != -1);
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( iItemId );
	if( !pItemCommon )
		return false;

	if( m_iItemCount == 0 )
	{
		// 判断合成物
		const ComposeData* pComposeData = theItemComposeConfig.GetItemComposeData(iItemId);
		if( !pComposeData )
			return false;

		if( pItemDrag->m_pkIconInfo->Count() > 1 )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString( eText_MaterialUpgrade_PutOneItem ) );
			return false;
		}

		// 放入第一个
		int iEmptySlot = 0;
		if( SetItem(iEmptySlot, iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
		{
			++m_iItemCount;
			m_iMainItemId = iItemId;

			ControlIconDrag::S_ListImg item = *pItemDrag;
			item.m_eEnable = eIcon_Enable;
			m_pID_LISTIMG_Material->Clear();
			m_pID_LISTIMG_Material->SetItem(&item, 0);
			m_pID_PICTURE_Line->SetVisable(true);

			m_pComposeData = (ComposeData*)pComposeData;
			m_iMaterialID = pComposeData->GetMaterialID();

			// 自动放入材料
			// 先找材料包
			if( m_iMaterialID != -1 )
			{
				int iMatIndex = thePlayerRole.m_bagMaterial.GetItemIndexById(m_iMaterialID);
				if( iMatIndex != -1 )
				{
					SCharItem item;
					if( thePlayerRole.m_bagMaterial.GetItem( iMatIndex, &item ) )
					{
						ControlIconDrag::S_ListImg* pItemMaterial = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_MaterialBag, iMatIndex);
						if( pItemMaterial && pItemMaterial->m_pkIconInfo
							&& SetMaterial(BT_MaterialBag, iMatIndex, pItemMaterial->m_pkIconInfo->GetOnlyId()) )
						{
							ControlIconDrag::S_ListImg item = *pItemMaterial;
							item.m_eEnable = eIcon_Enable;
							m_pID_LISTIMG_Result->Clear();
							m_pID_LISTIMG_Result->SetItem(&item, 0);

							m_bUpdateRateAndMoney = true;
							return true;
						}
					}
				}
				else	// 找普通包
				{
					iMatIndex = thePlayerRole.m_bag.GetItemIndexById(m_iMaterialID);
					if( iMatIndex != -1 )
					{
						SCharItem item;
						if( thePlayerRole.m_bag.GetItem( iMatIndex, &item ) )
						{
							ControlIconDrag::S_ListImg* pItemMaterial = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag, iMatIndex);
							if( pItemMaterial && pItemMaterial->m_pkIconInfo
								&& SetMaterial(BT_NormalItemBag, iMatIndex, pItemMaterial->m_pkIconInfo->GetOnlyId()) )
							{
								ControlIconDrag::S_ListImg item = *pItemMaterial;
								item.m_eEnable = eIcon_Enable;
								m_pID_LISTIMG_Result->Clear();
								m_pID_LISTIMG_Result->SetItem(&item, 0);

								m_bUpdateRateAndMoney = true;
								return true;
							}
						}
					}
				}
			}
			return true;
		}
	}
	else if( m_iItemCount > 0 )
	{
		if( !m_pComposeData )
		{
			m_pComposeData = (ComposeData*)theItemComposeConfig.GetItemComposeData(m_iMainItemId);
			if( !m_pComposeData )
				return false;
		}
		if( m_iMainItemId == -1 )
		{
			ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_Material->GetItemByIndex(0);
			if( !pItem || !pItem->m_pkIconInfo )
				return false;
			m_iMainItemId = pItem->m_pkIconInfo->GetItemId();
			if( m_iMainItemId == -1 )
				return false;
		}

		if( iItemId == m_iMainItemId )
		{
			if( m_iItemCount < ECD_MaxCount )
			{
				if( pItemDrag->m_pkIconInfo->Count() > 1 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString( eText_MaterialUpgrade_PutOneItem ) );
					return false;
				}

				// 可用槽
				int iEmptySlot = iItemSlot;
				if( iEmptySlot == -1 )
					iEmptySlot = FindEmptyItemSlot();
				if( iEmptySlot != -1 && SetItem(iEmptySlot, iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
				{
					// 材料个数加1
					++m_iItemCount;

					ControlIconDrag::S_ListImg item = *pItemDrag;
					item.m_eEnable = eIcon_Enable;
					switch(iEmptySlot)
					{
					case 1:
						m_pID_LISTIMG_Material2->Clear();
						m_pID_LISTIMG_Material2->SetItem(&item, 0);
						m_pID_PICTURE_Line2->SetVisable(true);
						break;
					case 2:
						m_pID_LISTIMG_Material3->Clear();
						m_pID_LISTIMG_Material3->SetItem(&item, 0);
						m_pID_PICTURE_Line3->SetVisable(true);
						break;
					case 3:
						m_pID_LISTIMG_Material4->Clear();
						m_pID_LISTIMG_Material4->SetItem(&item, 0);
						m_pID_PICTURE_Line4->SetVisable(true);
						break;
					case 4:
						m_pID_LISTIMG_Material5->Clear();
						m_pID_LISTIMG_Material5->SetItem(&item, 0);
						m_pID_PICTURE_Line5->SetVisable(true);
						break;
					default:
						break;
					}

					m_bUpdateRateAndMoney = true;
					return true;
				}
			}
		}
		else 
		{
			// 材料
			if( m_iMaterialID == -1 && m_pComposeData )
			{
				m_iMaterialID = m_pComposeData->GetMaterialID();
			}

			if( m_iMaterialID != -1 && iItemId == m_iMaterialID )
			{
				if( SetMaterial(iBagType, iItemIndex, pItemDrag->m_pkIconInfo->GetOnlyId()) )
				{
					ControlIconDrag::S_ListImg item = *pItemDrag;
					item.m_eEnable = eIcon_Enable;
					m_pID_LISTIMG_Result->Clear();
					m_pID_LISTIMG_Result->SetItem(&item, 0);

					m_bUpdateRateAndMoney = true;
					return true;
				}
			}
			else
			{
				// 材料不符，给提示
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString( eText_MaterialUpgrade_NotSameMaterial ) );
			}
		}
	}

	return false;
}

bool CUI_ID_FRAME_StarMaterialUpgrade::SetMaterial( int iBagType, int index, __int64 n64Guid )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;

	CItemBag2* pBag = 0;
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
    m_n64MaterialGuid = 0;
	EnableBagItem(true, m_uchMaterialBagType, m_stMaterialIndex);

	m_uchMaterialBagType = iBagType;
	m_stMaterialIndex = index;
	m_n64MaterialGuid = n64Guid;

	// 锁定包裹物品
	if( m_stMaterialIndex != -1 )
	{
		EnableBagItem(false, m_uchMaterialBagType, m_stMaterialIndex);
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}
	return true;
}

bool CUI_ID_FRAME_StarMaterialUpgrade::SetItem( int iSlot, int iBagType, int index, __int64 n64Guid )
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return false;

	if( iSlot < 0 || iSlot >= ECD_MaxCount )
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
    m_xItem[iSlot].n64ItemGuid = 0;
	EnableBagItem(true, m_xItem[iSlot].uchItemBagType, m_xItem[iSlot].stItemIndex);

	m_xItem[iSlot].uchItemBagType = iBagType;
	m_xItem[iSlot].stItemIndex = index;
	m_xItem[iSlot].n64ItemGuid = n64Guid;

	// 锁定包裹物品
	if( m_xItem[iSlot].stItemIndex != -1 )
	{
		EnableBagItem(false, m_xItem[iSlot].uchItemBagType, m_xItem[iSlot].stItemIndex);
		theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
	}
	return true;
}

int CUI_ID_FRAME_StarMaterialUpgrade::FindEmptyItemSlot()
{
	int iSlot = -1;
	if( m_iItemCount == 0 )
		iSlot = 0;
	else
	{
		for(int i=0; i<ECD_MaxCount; ++i)
		{
			if( m_xItem[i].stItemIndex == -1 )
			{
				iSlot = i;
				break;
			}
		}
	}
	if( iSlot >= ECD_MaxCount )
		iSlot = -1;
	return iSlot;
}

void CUI_ID_FRAME_StarMaterialUpgrade::ClearMaterial()
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;

	// 解锁物品
    m_n64MaterialGuid = 0;
	EnableBagItem(true, m_uchMaterialBagType, m_stMaterialIndex);

	m_uchMaterialBagType = 0;
	m_stMaterialIndex = -1;
	m_iMaterialID = -1;
	m_pComposeData = NULL;
	m_pID_LISTIMG_Result->Clear();
	m_pID_TEXT_Rate->SetText("");
	m_pID_TEXT_UseMoney->SetText("");
	m_dwCostMoney = 0;
}

void CUI_ID_FRAME_StarMaterialUpgrade::ClearItem(int id)
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;
	if( id < 0 || id >= ECD_MaxCount )
		return;

	// 物品解锁
	if( m_xItem[id].stItemIndex != -1 )
	{
        m_xItem[id].n64ItemGuid = 0;
		EnableBagItem(true, m_xItem[id].uchItemBagType, m_xItem[id].stItemIndex);

		--m_iItemCount;
		if( m_iItemCount < 0 )	// m_iMaterialCount不能小于0
			m_iItemCount = 0;
	}

	m_xItem[id].uchItemBagType = 0;
	m_xItem[id].stItemIndex = -1;
	m_xItem[id].n64ItemGuid = 0;
	if( id == 0 )
		m_iMainItemId = -1;
	// 清楚控件
	switch(id)
	{
	case 0:
		m_pID_LISTIMG_Material->Clear();
		m_pID_PICTURE_Line->SetVisable(false);
		break;
	case 1:
		m_pID_LISTIMG_Material2->Clear();
		m_pID_PICTURE_Line2->SetVisable(false);
		break;
	case 2:
		m_pID_LISTIMG_Material3->Clear();
		m_pID_PICTURE_Line3->SetVisable(false);
		break;
	case 3:
		m_pID_LISTIMG_Material4->Clear();
		m_pID_PICTURE_Line4->SetVisable(false);
		break;
	case 4:
		m_pID_LISTIMG_Material5->Clear();
		m_pID_PICTURE_Line5->SetVisable(false);
		break;
	}
}

void CUI_ID_FRAME_StarMaterialUpgrade::ClearAll()
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;

	ClearMaterial();
	for(int i=0; i<ECD_MaxCount; ++i)
		ClearItem(i);
	m_bUpdateRateAndMoney = true;
}

void CUI_ID_FRAME_StarMaterialUpgrade::ClearItems()
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;

	for(int i=0; i<ECD_MaxCount; ++i)
		ClearItem(i);
	m_bUpdateRateAndMoney = true;
}

void CUI_ID_FRAME_StarMaterialUpgrade::RefreshRateAndMoney()
{
	if( !m_pID_FRAME_StarMaterialUpgrade )
		return;

	// 显示成功率和消耗金钱
	if( m_iItemCount == 0 || m_stMaterialIndex == -1 || !m_pComposeData )
	{
		m_pID_TEXT_Rate->SetText("");
		m_pID_TEXT_UseMoney->SetText("");
		m_pID_BUTTON_Ok->SetEnable(false);
	}
	else
	{
		float fRate = m_pComposeData->GetModulus(m_iItemCount);
		char szBuff[256] = {0};
		MeSprintf_s(szBuff, sizeof(szBuff)/sizeof(char) -1, "%d%%", (int)(fRate * 100) );
		m_pID_TEXT_Rate->SetText(szBuff);

		m_dwCostMoney = m_pComposeData->GetCostMoney();
		std::string text = "";
		thePlayerRole.GetGSCStringFromJiaoZi(m_dwCostMoney, text);
		m_pID_TEXT_UseMoney->SetText(text.c_str());

		// 激活确定按钮
		m_pID_BUTTON_Ok->SetEnable(true);
	}
}

void CUI_ID_FRAME_StarMaterialUpgrade::OnVisibleChanged(ControlObject* pSender)
{
	s_CUI_ID_FRAME_StarMaterialUpgrade.ClearAll();
	s_CUI_ID_FRAME_StarMaterialUpgrade.ClearAnim();
}

bool CUI_ID_FRAME_StarMaterialUpgrade::CanUpgrate( bool bShowInfo )
{
	if( m_stMaterialIndex != -1 && m_iItemCount > 0 )
	{
		// 检查钱够不够
		//DWORD dwMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
		//if( dwMoney < m_dwCostMoney )
        if(!thePlayerRole.HaveEnoughMoney(m_dwCostMoney))
		{
			if( bShowInfo )
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Soul_Failed, theXmlString.GetString(eText_MaterialUpgradeFailed_NotEnoughMoney) );
			return false;
		}
		else
			return true;
	}
	return false;
}

void CUI_ID_FRAME_StarMaterialUpgrade::EnableBagItem( bool bEnable, int iBagType, int iItemIndex )
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

void CUI_ID_FRAME_StarMaterialUpgrade::ClearAnim()
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

bool CUI_ID_FRAME_StarMaterialUpgrade::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_n64MaterialGuid == nGuid )
    {
        return true;
    }
    return false;
}
