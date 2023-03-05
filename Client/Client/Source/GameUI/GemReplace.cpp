/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\GemReplace.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GemReplace.h"
#include "Common.h"
#include "IconManagerClient.h"
#include "GlobalDef.h"
#include "Pack.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "NetworkInput.h"
#include "PackItemEnableManager.h"

CUI_ID_FRAME_GemReplace s_CUI_ID_FRAME_GemReplace;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GemReplace, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GemReplace, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_BUTTON_OkOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LIST_GemFunction1OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LIST_GemFunction2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LIST_GemFunction3OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LIST_GemFunction4OnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_Hole4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemReplace, ID_LISTIMG_ArmourOnIconRButtonUp )
CUI_ID_FRAME_GemReplace::CUI_ID_FRAME_GemReplace()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_LIST_GemFunction1 = NULL;
	m_pID_LIST_GemFunction2 = NULL;
	m_pID_LIST_GemFunction3 = NULL;
	m_pID_LIST_GemFunction4 = NULL;
	m_pID_PICTURE_Open1 = NULL;
	m_pID_PICTURE_Open2 = NULL;
	m_pID_PICTURE_Open3 = NULL;
	m_pID_PICTURE_Open4 = NULL;
	m_pID_LISTIMG_Hole1 = NULL;
	m_pID_LISTIMG_Hole2 = NULL;
	m_pID_LISTIMG_Hole3 = NULL;
	m_pID_LISTIMG_Hole4 = NULL;
	m_pID_PICTURE_Lock1 = NULL;
	m_pID_PICTURE_Lock2 = NULL;
	m_pID_PICTURE_Lock3 = NULL;
	m_pID_PICTURE_Lock4 = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;

}
	// Frame
	bool CUI_ID_FRAME_GemReplace::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		else
		{
			RefreshNeedMoney();
		}
		return true;
	}
	bool CUI_ID_FRAME_GemReplace::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemReplace::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemReplace::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GemReplace::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// List
	void CUI_ID_FRAME_GemReplace::ID_LIST_GemFunction1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_GemReplace::ID_LIST_GemFunction2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_GemReplace::ID_LIST_GemFunction3OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_GemReplace::ID_LIST_GemFunction4OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return OnDragOnGem(0,pItemDrag, pSender);
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return OnGemRemove(0);
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return OnDragOnGem(1,pItemDrag, pSender);
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return OnGemRemove(1);
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return OnDragOnGem(2,pItemDrag, pSender);
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return OnGemRemove(2);
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		return OnDragOnGem(3,pItemDrag, pSender);
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_Hole4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return OnGemRemove(3);
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		if( !m_pID_FRAME_EquipEvolve )
			return false;
		if( !pItemDrag )
			return false;

		OnEquipDragOn(pItemDrag,pSender);
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_GemReplace::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_GemReplace::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GemReplace.MEUI" , false, UI_Render_LayerThree);
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\GemReplace.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GemReplace::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GemReplace, s_CUI_ID_FRAME_GemReplaceOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GemReplace, s_CUI_ID_FRAME_GemReplaceOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_GemReplace, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GemReplaceID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GemReplace, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GemReplaceID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GemReplace, ID_BUTTON_Ok, s_CUI_ID_FRAME_GemReplaceID_BUTTON_OkOnButtonClick );
theUiManager.OnListSelectChange( ID_FRAME_GemReplace, ID_LIST_GemFunction1, s_CUI_ID_FRAME_GemReplaceID_LIST_GemFunction1OnListSelectChange );
theUiManager.OnListSelectChange( ID_FRAME_GemReplace, ID_LIST_GemFunction2, s_CUI_ID_FRAME_GemReplaceID_LIST_GemFunction2OnListSelectChange );
theUiManager.OnListSelectChange( ID_FRAME_GemReplace, ID_LIST_GemFunction3, s_CUI_ID_FRAME_GemReplaceID_LIST_GemFunction3OnListSelectChange );
theUiManager.OnListSelectChange( ID_FRAME_GemReplace, ID_LIST_GemFunction4, s_CUI_ID_FRAME_GemReplaceID_LIST_GemFunction4OnListSelectChange );
theUiManager.OnIconDragOn( ID_FRAME_GemReplace, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole1OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole1OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole1OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemReplace, ID_LISTIMG_Hole1, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole1OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_GemReplace, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole2OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole2OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole2OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemReplace, ID_LISTIMG_Hole2, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole2OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_GemReplace, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole3OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole3OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole3OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemReplace, ID_LISTIMG_Hole3, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole3OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_GemReplace, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole4OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole4OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemReplace, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole4OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemReplace, ID_LISTIMG_Hole4, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_Hole4OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_GemReplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_ArmourOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_GemReplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_ArmourOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_GemReplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_ArmourOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_GemReplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_GemReplaceID_LISTIMG_ArmourOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GemReplace );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_TEXT_Money );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_BUTTON_Ok );
		m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_TEXT_Tip );
		m_pID_LIST_GemFunction1 = (ControlList*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LIST_GemFunction1 );
		m_pID_LIST_GemFunction2 = (ControlList*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LIST_GemFunction2 );
		m_pID_LIST_GemFunction3 = (ControlList*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LIST_GemFunction3 );
		m_pID_LIST_GemFunction4 = (ControlList*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LIST_GemFunction4 );
		m_pID_PICTURE_Open1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Open1 );
		m_pID_PICTURE_Open2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Open2 );
		m_pID_PICTURE_Open3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Open3 );
		m_pID_PICTURE_Open4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Open4 );
		m_pID_LISTIMG_Hole1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LISTIMG_Hole1 );
		m_pID_LISTIMG_Hole2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LISTIMG_Hole2 );
		m_pID_LISTIMG_Hole3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LISTIMG_Hole3 );
		m_pID_LISTIMG_Hole4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LISTIMG_Hole4 );
		m_pID_PICTURE_Lock1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Lock1 );
		m_pID_PICTURE_Lock2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Lock2 );
		m_pID_PICTURE_Lock3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Lock3 );
		m_pID_PICTURE_Lock4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Lock4 );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_StarEffect );
		m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_TEXT_TipAllDone );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_PICTURE_Begin );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemReplace, ID_LISTIMG_Armour );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip );
		assert( m_pID_LIST_GemFunction1 );
		assert( m_pID_LIST_GemFunction2 );
		assert( m_pID_LIST_GemFunction3 );
		assert( m_pID_LIST_GemFunction4 );
		assert( m_pID_PICTURE_Open1 );
		assert( m_pID_PICTURE_Open2 );
		assert( m_pID_PICTURE_Open3 );
		assert( m_pID_PICTURE_Open4 );
		assert( m_pID_LISTIMG_Hole1 );
		assert( m_pID_LISTIMG_Hole2 );
		assert( m_pID_LISTIMG_Hole3 );
		assert( m_pID_LISTIMG_Hole4 );
		assert( m_pID_PICTURE_Lock1 );
		assert( m_pID_PICTURE_Lock2 );
		assert( m_pID_PICTURE_Lock3 );
		assert( m_pID_PICTURE_Lock4 );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_TipAllDone );
		assert( m_pID_PICTURE_Begin );
		assert( m_pID_LISTIMG_Equip );
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		InitializeGemBase();
		m_GemInfoList[0] = m_pID_LIST_GemFunction1;
		m_GemInfoList[1] = m_pID_LIST_GemFunction2;
		//m_GemInfoList[2] = m_pID_LIST_GemFunction3;
		//m_GemInfoList[3] = m_pID_LIST_GemFunction4;
		for(int i = 0; i < m_nMaxHoleNum; ++i)
		{
			m_GemInfoList[i]->HaveSelBar( 0, 0 );	
		}
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GemReplace::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\GemReplace.MEUI" );
	}
bool CUI_ID_FRAME_GemReplace::IsEvolveAllDone( ControlIconDrag::S_ListImg * pImg )
{
	return (!_IsExistGem(pImg));
}

bool CUI_ID_FRAME_GemReplace::_IsExistGem( ControlIconDrag::S_ListImg * pImg )
{
	SCharItem* pItem = ((SCharItem*)pImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return false;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for (int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] != 0)
		{
			return true;
		}		
	}


	return true;

}

void CUI_ID_FRAME_GemReplace::ClearEquip()
{
	GemBaseUI::ClearEquip();
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_GemInfoList[i]->Clear();
	}

}

void CUI_ID_FRAME_GemReplace::ResetUIObjects()
{
	GemBaseUI::ResetUIObjects();
	m_pID_TEXT_Tip = NULL;
	for(int i = 0; i < m_nMaxHoleNum; ++i)
	{
		m_GemInfoList[i] = NULL;
	}

}

void CUI_ID_FRAME_GemReplace::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	GemBaseUI::_RefreshEquipInfo(pListImg);
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		// enable原材料的icon
		if( m_stMaterialIndex[i] != -1 )
		{
            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_stMaterialIndex[i], true );
			m_stMaterialIndex[i] = -1;
			m_shMaterialBagType[i] = -1;
			m_n64MaterialGuid[i] = 0;
			m_GemInfoList[i]->Clear();
		}
	}
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for(int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] != 0)
		{
			FillGemInfoInList(pItem->equipdata.gemIds[i],m_GemInfoList[i]);
		}
	}
}

void CUI_ID_FRAME_GemReplace::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_GemReplace.SetDirty( true );
	s_CUI_ID_FRAME_GemReplace.ClearEquip();	
	s_CUI_ID_FRAME_GemReplace.RefreshAllBagEnable();

}

bool CUI_ID_FRAME_GemReplace::UpdateGem()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	TipVisible(_IsExistGem(pImg));
	RefreshNeedMoney();
	SetDirty(true);
	return true;
}



int CUI_ID_FRAME_GemReplace::GetEmptyHole()
{

	if (m_stEquipBagIndex == -1)
	{
		return -1;
	}

	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return -1;
	}
	int nHole = pItem->equipdata.gemHoleCount;
	for(int i = 0; i < nHole; ++i)
	{
		if (pItem->equipdata.gemIds[i] == 0)
		{
			if (m_stMaterialIndex[i] == -1)
			{
				return i;
			}

		}
	}
	return -1;
}

bool CUI_ID_FRAME_GemReplace::IsGemTypeMatch(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}
	ControlIconDrag::S_ListImg* pItemImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemImg->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;
	ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if( !pCanEquip )
		return false;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if ( !pMe )
	{
		return false;
	}
	int nMeLevel = pMe->GetLevel();
	SCharItem* pItem = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData());
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID(pItem->GetItemID());
	if( pGem->levelLimit <= pCanEquip->stEquipLevelReq  //符合装备等级
		&& pGem->gemLevel <= nMeLevel																				//符合人物等级
		&& pGem->CanEquipPart(pCanEquip->ustEquipType)																//符合部位需求
		)			
	{
		return true;
	}

	return false;
}

bool CUI_ID_FRAME_GemReplace::OnDragOnGem( int index, ControlIconDrag::S_ListImg* pItemDrag, ControlObject* pSender )
{
	if (m_stEquipBagIndex == -1)
	{
		return false;
	}
	ControlIconDrag::S_ListImg* pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return false;
	}
	if (pItem->equipdata.gemIds[index] == 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_NotGemInHole) );
		return false;
	}
	if (!IsGemTypeMatch(pItemDrag))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemTypeError) );
		return false;
	}
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( pItemCommon && ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_GEM) )
	{
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pImageSender) )
		{			
			m_stMaterialIndex[index] = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );

			SCharItem item;
			if(m_stMaterialIndex[index] != -1 && thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[index],&item))
				m_n64MaterialGuid[index] = item.itembaseinfo.nOnlyInt;
			else
				m_n64MaterialGuid[index] = 0;
			m_shMaterialBagType[index] = BT_MaterialBag;
			ControlIconDrag::S_ListImg liGem;
			liGem.SetData( pItemDrag->m_pkIconInfo->GetItemId(),1,eIcon_Enable );
			m_pID_LISTIMG_Hole[index]->SetItem( &liGem, 0 );
			FillGemInfoInList(item.GetItemID(),m_GemInfoList[index]);
		}
		else
		{
			return false;
		}
		m_bMaterialBagEnable[index] = false;
		UpdateGem();
		SetDirty( true );
	}
	return true;
}

bool CUI_ID_FRAME_GemReplace::OnGemRemove( int index )
{
	if (m_stMaterialIndex[index] == -1)
	{
		return false;
	}
	m_pID_LISTIMG_Hole[index]->Clear();
	m_GemInfoList[index]->Clear();
	m_bMaterialBagEnable[index] = true;	
	ControlIconDrag::S_ListImg * pListImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
	SCharItem* pItem = ((SCharItem*)pListImg->m_pkIconInfo->GetData());
	if (NULL == pItem)
	{
		return false;
	}
	{
		if (pItem->equipdata.gemIds[index] != 0)
		{
			FillGemInfoInList(pItem->equipdata.gemIds[index],m_GemInfoList[index]);
			ControlIconDrag::S_ListImg liGem;
			liGem.SetData( pItem->equipdata.gemIds[index],1,eIcon_Enable );
			m_pID_LISTIMG_Hole[index]->SetItem( &liGem, 0 );
		}
	}
	SetDirty( true );
	return false;
}

int CUI_ID_FRAME_GemReplace::GetEvolveMoneyCost()
{
	int nMoney = 0;
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		if( m_stMaterialIndex[i] != -1 )
		{
			SCharItem item;
			thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[i],&item);
			ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )GettheItemDetail().GetItemByID(item.GetItemID());
			if (pGem)
			{
				nMoney += pGem->useCostMoney;
			}
		}
	}
	return nMoney;
}

void CUI_ID_FRAME_GemReplace::SendEvolveMsg()
{
	MsgEquipEvolve msgEvolve;
	msgEvolve.nEvolveType = GetEvolveType();

	msgEvolve.nNormalBagIndex = m_stEquipBagIndex;
	msgEvolve.nNormalGuid      = m_stEquipBagGuid;

	for(int i = 0; i < m_nsMaxMaterialNum; ++i)
	{
		msgEvolve.materials[i].bagType= m_shMaterialBagType[i];
		msgEvolve.materials[i].bagIndex = m_stMaterialIndex[i];
		msgEvolve.materials[i].guid = m_n64MaterialGuid[i];
	}
	msgEvolve.SendEquipMsg();
	//GettheNetworkInput().SendMsg( &msgEvolve );

}

bool CUI_ID_FRAME_GemReplace::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = GemBaseUI::ProcessAllDone(pImg);
	if (bRet)
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}
	return bRet;

}

void CUI_ID_FRAME_GemReplace::TipVisible( bool IsHoleExist )
{
	if (IsHoleExist)
	{
		m_pID_TEXT_Tip->SetVisable(true);
	}
	else
	{
		m_pID_TEXT_Tip->SetVisable(false);
	}

}

void CUI_ID_FRAME_GemReplace::RefreshDragEnable( SCharItem* pItem, int index )
{
// 	if (pItem->equipdata.gemIds[index] != 0)
	{
		m_pID_LISTIMG_Hole[index]->SetEnableDrag(true);
	}
// 	else
// 	{
// 		m_pID_LISTIMG_Hole[index]->SetEnableDrag(false);
// 	}

}

void CUI_ID_FRAME_GemReplace::RefreshAllBagEnable()
{
	GemBaseUI::RefreshAllBagEnable();
	m_nSelectMaterialIndex = -1;
	for (int index = 0; index < m_nMaxHoleNum; ++index)
	{
		if (m_stMaterialIndex[index] != -1)
		{
			m_nSelectMaterialIndex = index;
			break;
		}
	}
}