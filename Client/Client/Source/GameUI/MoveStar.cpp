/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\MoveStar.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "MoveStar.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "IconManagerClient.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "UIBase.h"
#include "StarLevelUpConfig.h"
#include "MeUI/ExpressionManager.h"
#include "color_config.h"
#include "EquipUIHelper.h"
#include "GlobalDef.h"
#include "Progress.h"
#include "Common.h"
#include "ScreenInfoManager.h"
#include "PackItemEnableManager.h"

#define SET_STAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_Star##n->SetVisable( true )
#define SET_NEXTSTAR_VISIBLE( n, star ) if( star == n )m_pID_PICTURE_NextStar##n->SetVisable( true )

#define MOVE_STAR_ITEM_ID 111

CUI_ID_FRAME_MoveStar s_CUI_ID_FRAME_MoveStar;
MAP_FRAME_RUN( s_CUI_ID_FRAME_MoveStar, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MoveStar, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_EspecialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_EspecialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_EspecialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_EspecialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LIST_ArmourPropertyOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LIST_TargetPropertyOnListSelectChange )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_Especial2OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_Especial2OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_Especial2OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_Especial2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_TargetOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_TargetOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_TargetOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MoveStar, ID_LISTIMG_TargetOnIconRButtonUp )
CUI_ID_FRAME_MoveStar::CUI_ID_FRAME_MoveStar()
{
	// Member
	ResetMembers();
	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;
}
void CUI_ID_FRAME_MoveStar::ResetMembers()
{
	m_pID_FRAME_MoveStar = NULL;
	m_pID_PICTURE_DI2 = NULL;
// 	m_pID_PICTURE_title2 = NULL;
// 	m_pID_PICTURE_title = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
// 	m_pID_TEXT_ItemWall = NULL;
// 	m_pID_PICTURE_ItemWall = NULL;
// 	m_pID_PICTURE_TargetWall = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Armour = NULL;
	//m_pID_LISTIMG_Especial = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	//m_pID_TEXT_TargetPrompt = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_LIST_ArmourProperty = NULL;
	m_pID_LIST_TargetProperty = NULL;
	//m_pID_PICTURE_Gray = NULL;
	//m_pID_PICTURE_Yellow = NULL;
	//m_pID_PICTURE_ItemGray = NULL;
	m_pID_PICTURE_Star9 = NULL;
	//m_pID_TEXT_Star = NULL;
	m_pID_PICTURE_Star18 = NULL;
	m_pID_PICTURE_Star17 = NULL;
	m_pID_PICTURE_Star16 = NULL;
	m_pID_PICTURE_Star15 = NULL;
	m_pID_PICTURE_Star14 = NULL;
	m_pID_PICTURE_Star13 = NULL;
	m_pID_PICTURE_Star12 = NULL;
	m_pID_PICTURE_Star11 = NULL;
	m_pID_PICTURE_Star10 = NULL;
	m_pID_PICTURE_Star8 = NULL;
	m_pID_PICTURE_Star7 = NULL;
	m_pID_PICTURE_Star6 = NULL;
	m_pID_PICTURE_Star5 = NULL;
	m_pID_PICTURE_Star4 = NULL;
	m_pID_PICTURE_Star3 = NULL;
	m_pID_PICTURE_Star2 = NULL;
	m_pID_PICTURE_Star1 = NULL;
	m_pID_PICTURE_Star0 = NULL;
	//m_pID_LISTIMG_Especial2 = NULL;
	m_pID_LISTIMG_Target = NULL;
	//m_pID_TEXT_NextStar = NULL;
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
	m_pID_PICTURE_NextStar8 = NULL;
	m_pID_PICTURE_NextStar7 = NULL;
	m_pID_PICTURE_NextStar6 = NULL;
	m_pID_PICTURE_NextStar5 = NULL;
	m_pID_PICTURE_NextStar4 = NULL;
	m_pID_PICTURE_NextStar3 = NULL;
	m_pID_PICTURE_NextStar2 = NULL;
	m_pID_PICTURE_NextStar1 = NULL;
	m_pID_PICTURE_NextStar0 = NULL;
// 	m_pID_PICTURE_Title = NULL;
	m_pID_PICTURE_MoveStarEffect = NULL;
	//m_pID_TEXT_TargetPrompt2 = NULL;
}
// Frame
bool CUI_ID_FRAME_MoveStar::OnFrameRun()
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

			SCharItem equip;
			SCharItem item;
			if ( thePlayerRole.m_bag.GetItem(m_equipBagIndex, &equip) &&
				 thePlayerRole.m_bag.GetItem(m_moveStarItemBagIndex, &item))
			{
				// 播放序列帧动画
				m_slideAnim.StartAnimation(HQ_TimeGetTime());
				m_bStartAnim = true;

				// 请求移星
				MsgMoveStarReq req;
				req.chOperate = m_type;

				req.chEquipBagType = BT_NormalItemBag;
				req.stEquipIndex = m_equipBagIndex;
				req.nEquipGuid = equip.itembaseinfo.nOnlyInt;

				req.chItemBagType = BT_NormalItemBag;
				req.stItemIndex = m_moveStarItemBagIndex;
				req.nItemGuid = item.itembaseinfo.nOnlyInt;

				GettheNetworkInput().SendMsg( &req );
			}
		}
	}

	if (!m_bNeedUpdate)
	{
		return false;
	}

	m_bNeedUpdate = false;

	RefreshAllBagEnable();
	SetAtomVisible(!m_equipEnable || !m_moveStarItemEnable);

	m_StarGroup.SetVisible(false);
	m_NextStarGroup.SetVisible(false);

	if (m_pID_LISTIMG_Armour->GetItemByIndex(0) == 0 || m_pID_LISTIMG_Armour->GetItemByIndex(0)->IsNull())
		m_equipBagIndex = -1;

	if (m_pID_LISTIMG_Material->GetItemByIndex(0) == 0 || m_pID_LISTIMG_Material->GetItemByIndex(0)->IsNull())
		m_moveStarItemBagIndex = -1;

	m_pID_LIST_ArmourProperty->SetVisable(false);
	m_pID_LIST_TargetProperty->SetVisable(false);

	// 显示星
	if (m_type == MsgMoveStarReq::ECD_MoveToItem)
	{
		SCharItem equip;
		if (thePlayerRole.m_bag.GetItem(m_equipBagIndex, &equip))
		{
			ShowStar( (int)equip.equipdata.ucLevel );
			UpdateInfo(&equip, m_pID_LIST_ArmourProperty);
			m_pID_LIST_ArmourProperty->SetVisable(true);
		}
		SCharItem item;
		if (thePlayerRole.m_bag.GetItem(m_moveStarItemBagIndex, &item))
		{
			ShowNextStar( (int)equip.equipdata.ucLevel );
			item.equipdata.ucLevel = equip.equipdata.ucLevel;
			item.SetBounded(true);
			UpdateInfo(&item, m_pID_LIST_TargetProperty);
			m_pID_LIST_TargetProperty->SetVisable(true);
		}

		ControlListImage::S_ListImg listImg;
		listImg.SetData(&item);
		m_pID_LISTIMG_Target->SetItem(&listImg, 0);
	}
	else
	{
		SCharItem equip;
		if (thePlayerRole.m_bag.GetItem(m_equipBagIndex, &equip))
		{
			ShowStar( (int)equip.equipdata.ucLevel );
			UpdateInfo(&equip, m_pID_LIST_ArmourProperty);
			m_pID_LIST_ArmourProperty->SetVisable(true);
		}
		SCharItem item;
		if (thePlayerRole.m_bag.GetItem(m_moveStarItemBagIndex, &item))
		{
			ShowNextStar( (int)item.equipdata.ucLevel );
			equip.equipdata.ucLevel = item.equipdata.ucLevel;
			UpdateInfo(&equip, m_pID_LIST_TargetProperty);
			m_pID_LIST_TargetProperty->SetVisable(true);
		}

		ControlListImage::S_ListImg listImg;
		listImg.SetData(&equip);
		m_pID_LISTIMG_Target->SetItem(&listImg, 0);
	}

	m_pID_BUTTON_Ok->SetEnable(m_equipBagIndex != -1 && m_moveStarItemBagIndex != -1);
	
	return true;
}
bool CUI_ID_FRAME_MoveStar::OnFrameRender()
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
				_SetVisable( false, m_type );
			}
		}
		if( m_bStartAnim )
		{
			RECT rc;
			m_pID_PICTURE_MoveStarEffect->GetRealRect(&rc);
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
// Button
// bool CUI_ID_FRAME_MoveStar::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_MoveStar::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_MoveStar )
		return false;
	return SetMoveStarItem_(pSender, pItemDrag);
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	SetMoveStarItemBagIndex(m_moveStarItemBagIndex, true);
	m_pID_LISTIMG_Material->Clear();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{	
	if( !m_pID_FRAME_MoveStar )
		return false;

	return SetEquip(pSender, pItemDrag);
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	ClearInfo();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_EspecialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															ControlIconDrag::S_ListImg* pItemDrag,
															ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_EspecialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_EspecialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_EspecialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_MoveStar::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	SCharItem equip;
	if (!thePlayerRole.m_bag.GetItem(m_equipBagIndex, &equip))
		return false;

	SCharItem item;
	if (!thePlayerRole.m_bag.GetItem(m_moveStarItemBagIndex, &item))
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
			s_CUI_Progress.ShowByTime( m_dwStartIntonateTime, m_nIntonateTime, true, 1, true, true, theXmlString.GetString(eText_MoveStar_Progress) );
		}
		else
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString(eClient_AddInfo_2slk_11) );
		}
	}

	return true;
}
// Button
bool CUI_ID_FRAME_MoveStar::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	_SetVisable(false, m_type);
	return true;
}
// List
void CUI_ID_FRAME_MoveStar::ID_LIST_ArmourPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return;
}
// List
void CUI_ID_FRAME_MoveStar::ID_LIST_TargetPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return;
}
// ListImg / ListEx
// bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_Especial2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 															 ControlIconDrag::S_ListImg* pItemDrag,
// 															 ControlIconDrag::S_ListImg* pItemSrc )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_Especial2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_Especial2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return false;
// }
// bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_Especial2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	if (!m_pID_FRAME_MoveStar)
// 		return false;
// 	return false;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_TargetOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_TargetOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_TargetOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}
bool CUI_ID_FRAME_MoveStar::ID_LISTIMG_TargetOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return false;
}

// 装载UI
bool CUI_ID_FRAME_MoveStar::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\MoveStar.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\MoveStar.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_MoveStar::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_MoveStar, s_CUI_ID_FRAME_MoveStarOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MoveStar, s_CUI_ID_FRAME_MoveStarOnFrameRender );
	//theUiManager.OnButtonClick( ID_FRAME_MoveStar, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_MoveStarID_BUTTON_CLOSEOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_MoveStar, ID_BUTTON_help, s_CUI_ID_FRAME_MoveStarID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStar, ID_LISTIMG_Material, s_CUI_ID_FRAME_MoveStarID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_MoveStarID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_MoveStarID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_MoveStarID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStar, ID_LISTIMG_Armour, s_CUI_ID_FRAME_MoveStarID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_MoveStarID_LISTIMG_EspecialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_MoveStarID_LISTIMG_EspecialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_MoveStarID_LISTIMG_EspecialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStar, ID_LISTIMG_Especial, s_CUI_ID_FRAME_MoveStarID_LISTIMG_EspecialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_MoveStar, ID_BUTTON_Ok, s_CUI_ID_FRAME_MoveStarID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MoveStar, ID_BUTTON_Cancel, s_CUI_ID_FRAME_MoveStarID_BUTTON_CancelOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_MoveStar, ID_LIST_ArmourProperty, s_CUI_ID_FRAME_MoveStarID_LIST_ArmourPropertyOnListSelectChange );
	theUiManager.OnListSelectChange( ID_FRAME_MoveStar, ID_LIST_TargetProperty, s_CUI_ID_FRAME_MoveStarID_LIST_TargetPropertyOnListSelectChange );
// 	theUiManager.OnIconDragOn( ID_FRAME_MoveStar, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_MoveStarID_LISTIMG_Especial2OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_MoveStar, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_MoveStarID_LISTIMG_Especial2OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_MoveStar, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_MoveStarID_LISTIMG_Especial2OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStar, ID_LISTIMG_Especial2, s_CUI_ID_FRAME_MoveStarID_LISTIMG_Especial2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_MoveStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_MoveStarID_LISTIMG_TargetOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_MoveStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_MoveStarID_LISTIMG_TargetOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_MoveStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_MoveStarID_LISTIMG_TargetOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MoveStar, ID_LISTIMG_Target, s_CUI_ID_FRAME_MoveStarID_LISTIMG_TargetOnIconRButtonUp );

	m_pID_FRAME_MoveStar = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MoveStar );
	m_pID_PICTURE_DI2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_DI2 );
	m_pID_PICTURE_title2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_title2 );
// 	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_title );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_BUTTON_help );
// 	m_pID_TEXT_ItemWall = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_ItemWall );
// 	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_ItemWall );
// 	m_pID_PICTURE_TargetWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_TargetWall );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LISTIMG_Material );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LISTIMG_Armour );
	//m_pID_LISTIMG_Especial = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LISTIMG_Especial );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_UseMoneyZ );
	//m_pID_TEXT_TargetPrompt = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_TargetPrompt );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_UseMoney );
	m_pID_LIST_ArmourProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LIST_ArmourProperty );
	m_pID_LIST_TargetProperty = (ControlList*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LIST_TargetProperty );
// 	m_pID_PICTURE_Gray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Gray );
// 	m_pID_PICTURE_Yellow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Yellow );
// 	m_pID_PICTURE_ItemGray = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_ItemGray );
	m_pID_PICTURE_Star9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star9 );
	//m_pID_TEXT_Star = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_Star );
	m_pID_PICTURE_Star18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star18 );
	m_pID_PICTURE_Star17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star17 );
	m_pID_PICTURE_Star16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star16 );
	m_pID_PICTURE_Star15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star15 );
	m_pID_PICTURE_Star14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star14 );
	m_pID_PICTURE_Star13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star13 );
	m_pID_PICTURE_Star12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star12 );
	m_pID_PICTURE_Star11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star11 );
	m_pID_PICTURE_Star10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star10 );
	m_pID_PICTURE_Star8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star8 );
	m_pID_PICTURE_Star7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star7 );
	m_pID_PICTURE_Star6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star6 );
	m_pID_PICTURE_Star5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star5 );
	m_pID_PICTURE_Star4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star4 );
	m_pID_PICTURE_Star3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star3 );
	m_pID_PICTURE_Star2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star2 );
	m_pID_PICTURE_Star1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star1 );
	m_pID_PICTURE_Star0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Star0 );
	//m_pID_LISTIMG_Especial2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LISTIMG_Especial2 );
	m_pID_LISTIMG_Target = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_LISTIMG_Target );
	//m_pID_TEXT_NextStar = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_NextStar );
	m_pID_PICTURE_NextStar18 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar18 );
	m_pID_PICTURE_NextStar17 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar17 );
	m_pID_PICTURE_NextStar16 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar16 );
	m_pID_PICTURE_NextStar15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar15 );
	m_pID_PICTURE_NextStar14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar14 );
	m_pID_PICTURE_NextStar13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar13 );
	m_pID_PICTURE_NextStar12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar12 );
	m_pID_PICTURE_NextStar11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar11 );
	m_pID_PICTURE_NextStar10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar10 );
	m_pID_PICTURE_NextStar9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar9 );
	m_pID_PICTURE_NextStar8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar8 );
	m_pID_PICTURE_NextStar7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar7 );
	m_pID_PICTURE_NextStar6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar6 );
	m_pID_PICTURE_NextStar5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar5 );
	m_pID_PICTURE_NextStar4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar4 );
	m_pID_PICTURE_NextStar3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar3 );
	m_pID_PICTURE_NextStar2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar2 );
	m_pID_PICTURE_NextStar1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar1 );
	m_pID_PICTURE_NextStar0 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_NextStar0 );
	//m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_Title );
	m_pID_PICTURE_MoveStarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_PICTURE_MoveStarEffect );
//	m_pID_TEXT_TargetPrompt2 = (ControlText*)theUiManager.FindControl( ID_FRAME_MoveStar, ID_TEXT_TargetPrompt2 );
// 	assert( m_pID_FRAME_MoveStar );
// 	assert( m_pID_PICTURE_DI2 );
// 	assert( m_pID_PICTURE_title2 );
// 	//assert( m_pID_PICTURE_title );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
// 	//assert( m_pID_TEXT_ItemWall );
// 	assert( m_pID_PICTURE_ItemWall );
// 	//assert( m_pID_PICTURE_TargetWall );
// 	assert( m_pID_LISTIMG_Material );
// 	assert( m_pID_LISTIMG_Armour );
// 	assert( m_pID_LISTIMG_Especial );
// 	assert( m_pID_BUTTON_Ok );
// 	assert( m_pID_BUTTON_Cancel );
// 	assert( m_pID_TEXT_UseMoneyZ );
// 	//assert( m_pID_TEXT_TargetPrompt );
// 	assert( m_pID_TEXT_UseMoney );
// 	assert( m_pID_LIST_ArmourProperty );
// 	assert( m_pID_LIST_TargetProperty );
// 	assert( m_pID_PICTURE_Gray );
// 	assert( m_pID_PICTURE_Yellow );
// 	assert( m_pID_PICTURE_ItemGray );
// 	assert( m_pID_PICTURE_Star9 );
// 	assert( m_pID_TEXT_Star );
// 	assert( m_pID_PICTURE_Star18 );
// 	assert( m_pID_PICTURE_Star17 );
// 	assert( m_pID_PICTURE_Star16 );
// 	assert( m_pID_PICTURE_Star15 );
// 	assert( m_pID_PICTURE_Star14 );
// 	assert( m_pID_PICTURE_Star13 );
// 	assert( m_pID_PICTURE_Star12 );
// 	assert( m_pID_PICTURE_Star11 );
// 	assert( m_pID_PICTURE_Star10 );
// 	assert( m_pID_PICTURE_Star8 );
// 	assert( m_pID_PICTURE_Star7 );
// 	assert( m_pID_PICTURE_Star6 );
// 	assert( m_pID_PICTURE_Star5 );
// 	assert( m_pID_PICTURE_Star4 );
// 	assert( m_pID_PICTURE_Star3 );
// 	assert( m_pID_PICTURE_Star2 );
// 	assert( m_pID_PICTURE_Star1 );
// 	assert( m_pID_PICTURE_Star0 );
// 	assert( m_pID_LISTIMG_Especial2 );
// 	assert( m_pID_LISTIMG_Target );
// 	assert( m_pID_TEXT_NextStar );
// 	assert( m_pID_PICTURE_NextStar18 );
// 	assert( m_pID_PICTURE_NextStar17 );
// 	assert( m_pID_PICTURE_NextStar16 );
// 	assert( m_pID_PICTURE_NextStar15 );
// 	assert( m_pID_PICTURE_NextStar14 );
// 	assert( m_pID_PICTURE_NextStar13 );
// 	assert( m_pID_PICTURE_NextStar12 );
// 	assert( m_pID_PICTURE_NextStar11 );
// 	assert( m_pID_PICTURE_NextStar10 );
// 	assert( m_pID_PICTURE_NextStar9 );
// 	assert( m_pID_PICTURE_NextStar8 );
// 	assert( m_pID_PICTURE_NextStar7 );
// 	assert( m_pID_PICTURE_NextStar6 );
// 	assert( m_pID_PICTURE_NextStar5 );
// 	assert( m_pID_PICTURE_NextStar4 );
// 	assert( m_pID_PICTURE_NextStar3 );
// 	assert( m_pID_PICTURE_NextStar2 );
// 	assert( m_pID_PICTURE_NextStar1 );
// 	assert( m_pID_PICTURE_NextStar0 );
// 	assert( m_pID_PICTURE_Title );
// 	assert( m_pID_PICTURE_MoveStarEffect );

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
	m_StarGroup.AddControl(m_pID_PICTURE_Star8);
	m_StarGroup.AddControl(m_pID_PICTURE_Star7);
	m_StarGroup.AddControl(m_pID_PICTURE_Star6);
	m_StarGroup.AddControl(m_pID_PICTURE_Star5);
	m_StarGroup.AddControl(m_pID_PICTURE_Star4);
	m_StarGroup.AddControl(m_pID_PICTURE_Star3);
	m_StarGroup.AddControl(m_pID_PICTURE_Star2);
	m_StarGroup.AddControl(m_pID_PICTURE_Star1);
	m_StarGroup.AddControl(m_pID_PICTURE_Star0);
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
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar8);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar7);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar6);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar5);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar4);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar3);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar2);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar1);
	m_NextStarGroup.AddControl(m_pID_PICTURE_NextStar0);
	m_NextStarGroup.SetVisible( false );

	m_pID_LIST_ArmourProperty->HaveSelBar( 0, 0 );	
	m_pID_LIST_TargetProperty->HaveSelBar( 0, 0 );

	m_pID_LISTIMG_Target->SetEnableDrag( false );

	m_bNeedUpdate = false;

	m_equipBagIndex = -1;
	m_equipEnable = true;

	m_moveStarItemBagIndex = -1;
	m_moveStarItemEnable = true;

	m_bShowError = true;

	m_bStartAnim = false;
	m_bStartIntonate = false;
	m_dwStartIntonateTime = 0;
	m_nIntonateTime = 0;

	RECT rc;
	m_pID_PICTURE_MoveStarEffect->GetRealRect(&rc);
	m_slideAnim.Initialize("Ui\\Common\\MoveStarEffect\\MoveStarEffect", 27, rc, 1800);

	SetAtomVisible(false);
	_SetVisable(false, MsgMoveStarReq::ECD_MoveToEquip);
	m_pID_FRAME_MoveStar->SetOnVisibleChangedFun(OnVisibleChanged);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_MoveStar::_UnLoadUI()
{
	ClearAnim();
	m_StarGroup.Clear();
	m_NextStarGroup.Clear();
	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\MoveStar.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_MoveStar::_IsVisable()
{
	if (!m_pID_FRAME_MoveStar)
		return false;
	return m_pID_FRAME_MoveStar->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_MoveStar::_SetVisable( const bool bVisable, MsgMoveStarReq::EConstDefine type )
{
    if(!m_pID_FRAME_MoveStar)
        return;

	m_pID_FRAME_MoveStar->SetVisable( bVisable );

	m_type = type;

	if (bVisable)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
		if ( pMe )
			m_vVisiblePos = *(Vector*)&pMe->GetPos();

// 		m_pID_TEXT_TargetPrompt->SetVisable(m_type == MsgMoveStarReq::ECD_MoveToEquip);
		//m_pID_TEXT_TargetPrompt2->SetVisable(m_type == MsgMoveStarReq::ECD_MoveToItem);

		s_CUI_ID_FRAME_PACK.SetVisable(true);
	}
	ClearAnim();
}

void CUI_ID_FRAME_MoveStar::RefreshAllBagEnable()
{
	if( m_equipBagIndex != -1 )
    {
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_equipBagIndex, true );
	}
	if( m_moveStarItemBagIndex!= -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
	}
}

void CUI_ID_FRAME_MoveStar::OnVisibleChanged(ControlObject* pSender)
{
	s_CUI_ID_FRAME_MoveStar.m_bNeedUpdate = false;
	s_CUI_ID_FRAME_MoveStar.ClearInfo();
	s_CUI_ID_FRAME_MoveStar.ClearAnim();
}

void CUI_ID_FRAME_MoveStar::SetEquip(ControlIconDrag::S_ListImg *pItem)
{
	int index = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItem );
	if (index != -1)
	{
		ControlIconDrag::S_ListImg item = *pItem;
		item.m_eEnable = eIcon_Enable;
		m_pID_LISTIMG_Armour->SetItem(&item, 0);

		SetEquipBagIndex(index, false);

		// 显示星
		if (m_type == MsgMoveStarReq::ECD_MoveToEquip)
		{
			ShowStar( (int)((SCharItem*)pItem->m_pkIconInfo->GetData())->equipdata.ucLevel );
			ShowNextStar( (int)((SCharItem*)pItem->m_pkIconInfo->GetData())->equipdata.ucLevel );
		}

		m_bShowError = false;
		SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_MoveStar::SetMoveStarItem_);
		m_bShowError = true;
	}
}

bool CUI_ID_FRAME_MoveStar::SetEquip(ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag)
{
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
			if (m_type == MsgMoveStarReq::ECD_MoveToItem && ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->equipdata.ucLevel < 1)
			{
				if (m_bShowError)
				{
					int errCode = 3800 + MsgMoveStarAck::ECD_EquipNotStar;
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString( errCode ) );
				}
				return false;
			}

			SetEquip(pItemDrag);
			return true;
		}
		else
		{
			return false;
		}
	}	
	return false;
}

void CUI_ID_FRAME_MoveStar::SetEquipBagIndex(int index, bool enable)
{
	if (m_equipBagIndex != -1)
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_equipBagIndex, true );
	}

	m_equipBagIndex = index;
	m_equipEnable = enable;
	m_bNeedUpdate = true;

	if( m_equipBagIndex != -1 )
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_equipBagIndex, true );
	}
}

void CUI_ID_FRAME_MoveStar::SetMoveStarItem(ControlIconDrag::S_ListImg *pItem)
{
	int index = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItem );
	if (index != -1)
	{
		ControlIconDrag::S_ListImg item = *pItem;
		item.m_eEnable = eIcon_Enable;
		m_pID_LISTIMG_Material->SetItem(&item, 0);

		SetMoveStarItemBagIndex(index, false);

		// 显示星
		if (m_type == MsgMoveStarReq::ECD_MoveToItem)
		{
			ShowStar( (int)((SCharItem*)pItem->m_pkIconInfo->GetData())->equipdata.ucLevel );
			ShowNextStar( (int)((SCharItem*)pItem->m_pkIconInfo->GetData())->equipdata.ucLevel );
		}
	}
}

bool CUI_ID_FRAME_MoveStar::SetMoveStarItem_(ControlObject *pSender, ControlIconDrag::S_ListImg *pItemDrag)
{
	if (m_equipBagIndex == -1)
		return false;

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon )
	{
		bool bMoveStar = false;
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
		{
			ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemCommon;
			if( pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_MoveStar )
				bMoveStar = true;
		}

		if( bMoveStar )
		{
			ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
			if( !pImageSender )
				return false;

			// 包裹里
			if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
			{	
				if (m_type == MsgMoveStarReq::ECD_MoveToEquip && ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->equipdata.ucLevel < 1)
				{
					if (m_bShowError)
					{
						int errCode = 3800 + MsgMoveStarAck::ECD_ItemNotStar;
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString( errCode ) );
					}
					return false;
				}
				else if (m_type == MsgMoveStarReq::ECD_MoveToItem && ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->equipdata.ucLevel > 0)
				{
					if (m_bShowError)
					{
						int errCode = 3800 + MsgMoveStarAck::ECD_MoveStarItemError;
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString( errCode ) );
					}
					return false;
				}

				SetMoveStarItem(pItemDrag);
				return true;
			}
		}
	}

	if (m_bShowError)
	{
		int errCode = 3800 + MsgMoveStarAck::ECD_MoveStarItemError;
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString( errCode ) );
	}
	return false;
}

void CUI_ID_FRAME_MoveStar::SetMoveStarItemBagIndex(int index, bool enable)
{
	if (m_moveStarItemBagIndex != -1)
	{
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
	}

	m_moveStarItemBagIndex = index;
	m_moveStarItemEnable = enable;
	m_bNeedUpdate = true;

	if( m_moveStarItemBagIndex != -1 )
    {
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_moveStarItemBagIndex, true );
	}
}

void CUI_ID_FRAME_MoveStar::ClearInfo()
{
    if(!m_pID_FRAME_MoveStar)
        return;

	SetEquipBagIndex(-1, true);
	SetMoveStarItemBagIndex(-1, true);

	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Material->Clear();
	//m_pID_LISTIMG_Especial->Clear();
	//m_pID_LISTIMG_Especial2->Clear();
	m_pID_LISTIMG_Target->Clear();
	m_pID_LIST_ArmourProperty->Clear();
	m_pID_LIST_TargetProperty->Clear();
	m_pID_TEXT_UseMoney->SetText("");
	m_pID_BUTTON_Ok->SetEnable(false);
	m_StarGroup.SetVisible( false );
	m_NextStarGroup.SetVisible( false );

	SetAtomVisible(false);

	m_bNeedUpdate = false;
}

void CUI_ID_FRAME_MoveStar::ShowStar( int nStar )
{
	nStar = min( SCharItem::EL_Max, nStar );
	m_StarGroup.SetVisible( false );
	SET_STAR_VISIBLE( 0, nStar );
	SET_STAR_VISIBLE( 1, nStar );
	SET_STAR_VISIBLE( 2, nStar );
	SET_STAR_VISIBLE( 3, nStar );
	SET_STAR_VISIBLE( 4, nStar );
	SET_STAR_VISIBLE( 5, nStar );
	SET_STAR_VISIBLE( 6, nStar );
	SET_STAR_VISIBLE( 7, nStar );
	SET_STAR_VISIBLE( 8, nStar );
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

void CUI_ID_FRAME_MoveStar::ShowNextStar( int nStar )
{
	nStar = min( SCharItem::EL_Max, nStar );
	m_NextStarGroup.SetVisible( false );
	SET_NEXTSTAR_VISIBLE( 0, nStar );
	SET_NEXTSTAR_VISIBLE( 1, nStar );
	SET_NEXTSTAR_VISIBLE( 2, nStar );
	SET_NEXTSTAR_VISIBLE( 3, nStar );
	SET_NEXTSTAR_VISIBLE( 4, nStar );
	SET_NEXTSTAR_VISIBLE( 5, nStar );
	SET_NEXTSTAR_VISIBLE( 6, nStar );
	SET_NEXTSTAR_VISIBLE( 7, nStar );
	SET_NEXTSTAR_VISIBLE( 8, nStar );
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

ControlIconDrag::S_ListImg* CUI_ID_FRAME_MoveStar::FindZeroStarItem()
{
	return 0;
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_MoveStar::FindStarItem()
{
	return 0;
}

void CUI_ID_FRAME_MoveStar::SetAtomVisible( bool bVisible )
{
// 	m_pID_TEXT_Star->SetVisable( bVisible );
// 	m_pID_TEXT_NextStar->SetVisable( bVisible );
	m_pID_LISTIMG_Target->SetVisable( bVisible );
// 	m_pID_PICTURE_ItemWall->SetVisable( bVisible );
// 	m_pID_PICTURE_TargetWall->SetVisable( bVisible );
// 	m_pID_PICTURE_Yellow->SetVisable( bVisible );
// 	if (m_type == MsgMoveStarReq::ECD_MoveToEquip)
// 		m_pID_TEXT_TargetPrompt->SetVisable(!bVisible);
// 	else
// 		m_pID_TEXT_TargetPrompt2->SetVisable(!bVisible);

	m_pID_LIST_ArmourProperty->SetVisable( bVisible );
	m_pID_LIST_TargetProperty->SetVisable( bVisible );
}

void CUI_ID_FRAME_MoveStar::MoveStar(char result, unsigned char chStarLevel, bool bBound)
{
	if( !m_pID_FRAME_MoveStar )
		return;
	switch (result)
	{
	case MsgMoveStarAck::ECD_SuccessToItem:
		{
			unsigned short id;
			if (!thePlayerRole.m_bag.IsHaveItem(m_moveStarItemBagIndex, &id))
				return;
			SCharItem& item = thePlayerRole.m_bag.m_pPackItem[m_moveStarItemBagIndex];
			item.equipdata.ucLevel = chStarLevel;
			item.SetBounded(bBound);
			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(m_moveStarItemBagIndex);

			if (thePlayerRole.m_bag.IsHaveItem(m_equipBagIndex, &id))
			{
				SCharItem& item = thePlayerRole.m_bag.m_pPackItem[m_equipBagIndex];
				item.equipdata.ucLevel = 0;
				s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(m_equipBagIndex);
			}

			ClearInfo();

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Success, theXmlString.GetString( 3801 ) );
			break;
		}
	case MsgMoveStarAck::ECD_SuccessToEquip:
		{
			unsigned short id;
			if (!thePlayerRole.m_bag.IsHaveItem(m_equipBagIndex, &id))
				return;
			SCharItem& item = thePlayerRole.m_bag.m_pPackItem[m_equipBagIndex];
			item.equipdata.ucLevel = chStarLevel;
 			item.SetBounded(bBound);
			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(m_equipBagIndex);

			ClearInfo();

			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Success, theXmlString.GetString( 3801 ) );
			break;
		}
	default:
		{
			int errCode = 3800 + result;
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_MoveStar_Failed, theXmlString.GetString( errCode ) );
		}
	}
}

void CUI_ID_FRAME_MoveStar::UpdateInfo(SCharItem *pItem, ControlList *pList)
{
	char szBuf[256] = {0};
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
	if( !pItemCommon )
		return;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return;

	int bNextLevel = 0;

	pList->Clear();
	ControlList::S_List sList;
	sList.UseSelColor = false;	
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
		// 远程攻击
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

		//if( pArmour->fAddtionPhysicsAttack > 0 )
		//{
		//	sList.clear();
		//	// 近程攻击
		//	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddShortAttack), 
		//		(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fAddtionPhysicsAttack, pItem->equipdata.ucLevel + (int)bNextLevel ) );
		//	sList.SetData( szBuf, 0, 0, 0xffffffff );
		//	pList->AddItem( &sList );
		//}

		//if( pArmour->fAddtionMagicAttack > 0 )
		//{
		//	sList.clear();
		//	// 远程攻击
		//	MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMagicAttack), 
		//		(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->fAddtionMagicAttack, pItem->equipdata.ucLevel + (int)bNextLevel ) );
		//	sList.SetData( szBuf, 0, 0, 0xffffffff );
		//	pList->AddItem( &sList );
		//}

		//物理防御
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
		* Author: 2012-10-11 21:20:19 liaojie
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
			// Mp
			MeSprintf_s( szBuf, sizeof(szBuf)/sizeof(char) - 1, "%s+%d", theXmlString.GetString(eTip_sAddMPMax), 
				(int)S_IconInfoHero::GetAttributeWithLevel( pArmour->ustEquipType, pArmour->Mp, pItem->equipdata.ucLevel + (int)bNextLevel ) );
			sList.SetData( szBuf, 0, 0, 0xffffffff );
			pList->AddItem( &sList );		
		}
	}
}

void CUI_ID_FRAME_MoveStar::ClearAnim()
{
	if( m_bStartIntonate )
	{
		m_bStartIntonate = false;
		s_CUI_Progress.SetProgressComplete();
	}
	if( m_bStartAnim )
	{
		m_bStartAnim = false;
		m_slideAnim.StopAnimation();
		m_slideAnim.UnRelativePicResource();
	}
}

void CUI_ID_FRAME_MoveStar::SetVisable( const bool bVisable, MsgMoveStarReq::EConstDefine type )
{
	CUIBase::SetVisable(bVisable);
	if (m_bUILoad)
		_SetVisable(bVisable,type);
}

bool CUI_ID_FRAME_MoveStar::IsPackItemBeUsing( __int64 nGuid )
{
    if( !IsVisable() || nGuid <= 0 )
        return false;

    // 此UI在Next里没用，且这里没保存Guid，故直接return false
    return false;
}
