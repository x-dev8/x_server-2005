/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Amulet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Amulet.h"
#include "Pack.h"
#include "NetworkInput.h"
#include "PlayerRole.h"
#include "Core/Name.h"
#include "XmlStringLanguage.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "MeUI/ExpressionManager.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "IconManagerClient.h"
#include "Common.h"

CUI_ID_FRAME_Amulet s_CUI_ID_FRAME_Amulet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Amulet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Amulet, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_BUTTON_OkOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LIST_AmuletOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LIST_SymbolOnListSelectChange )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_AmuletOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_AmuletOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_AmuletOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_AmuletOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_SymbolOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_SymbolOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_SymbolOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Amulet, ID_LISTIMG_SymbolOnIconRButtonUp )
CUI_ID_FRAME_Amulet::CUI_ID_FRAME_Amulet()
{
	// Member
	m_pID_FRAME_EquipEvolve = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_LIST_Amulet = NULL;
	m_pID_LIST_Symbol = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Equip = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	ResetUIObjects();

}
	// Frame
	bool CUI_ID_FRAME_Amulet::OnFrameRun()
	{
		if (!OnDirty())
		{
			return true;
		}
		return true;
	}
	bool CUI_ID_FRAME_Amulet::OnFrameRender()
	{
		OnRender();
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Amulet::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Amulet::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable( false );
		return true;
	}
	// Button
	bool CUI_ID_FRAME_Amulet::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
	{
		OnOkClick();
		return true;
	}
	// List
	void CUI_ID_FRAME_Amulet::ID_LIST_AmuletOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// List
	void CUI_ID_FRAME_Amulet::ID_LIST_SymbolOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_AmuletOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
		if (!pCanEquip)
		{
			return false;
		}
		if (pCanEquip->ustEquipType != ItemDefine::equip_Amulet)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Amulet_Success, theXmlString.GetString(eWarning_Amulet_ItemType) );
			return false;
		}
		OnEquipDragOn(pItemDrag,pSender);
		
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_AmuletOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_AmuletOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_AmuletOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearEquip();
		return false;
	}
	// ListImg / ListEx
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_SymbolOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
	{
		SCharItem* psItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
		if (!psItem)
		{
			return false;
		}
		bool bFound = false;
		for (int i = 0; i < m_MatchMaterialArray.size();++i)
		{
			if (m_MatchMaterialArray[i] == psItem->GetItemID())
			{
				bFound = true;
				break;
			}
			
		}
		if (!bFound || psItem->equipdata.quality != ItemDefine::EQL_Blue)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Amulet_Success, theXmlString.GetString(eWarning_Amulet_Symbol) );
			return false;
		}
		ClearSymbol();
		OnDirty();
		ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
		if( !pImageSender )
			return false;

		m_nSelectMaterialIndex = 0;
		m_shMaterialBagType[0] = BT_MaterialBag;
		// 包裹里
		if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pImageSender) )
		{			
			m_stMaterialIndex[0] = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag );

			SCharItem item;
			if(m_stMaterialIndex[0] != -1 && thePlayerRole.m_bagMaterial.GetItem(m_stMaterialIndex[0],&item))
				m_n64MaterialGuid[0] = item.itembaseinfo.nOnlyInt;
			else
				m_n64MaterialGuid[0] = 0;
		}
		m_bMaterialBagEnable[0] = false;			
		m_pID_LISTIMG_Material->SetItem( pItemDrag, 0 );
		m_pSelectItem = m_pID_LISTIMG_Material->GetItemByIndex( 0 );
		m_pSelectItem->m_pkIconInfo->Count() = 1;
		m_pSelectItem->m_eEnable = eIcon_Enable;	
		FillBlueAttriList(m_pSelectItem,m_pID_LIST_Symbol);
		RefreshNeedMoney();
		m_pID_TEXT_Money->SetVisable(true);
		SetDirty(true);
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_SymbolOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_SymbolOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		return false;
	}
	bool CUI_ID_FRAME_Amulet::ID_LISTIMG_SymbolOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
	{
		ClearSymbol();
		return false;
	}

	// 装载UI
bool CUI_ID_FRAME_Amulet::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Amulet.MEUI" , false, UI_Render_LayerThree);
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\Amulet.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_Amulet::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_Amulet, s_CUI_ID_FRAME_AmuletOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_Amulet, s_CUI_ID_FRAME_AmuletOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_Amulet, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_AmuletID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_Amulet, ID_BUTTON_Cancel, s_CUI_ID_FRAME_AmuletID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_Amulet, ID_BUTTON_Ok, s_CUI_ID_FRAME_AmuletID_BUTTON_OkOnButtonClick );
theUiManager.OnListSelectChange( ID_FRAME_Amulet, ID_LIST_Amulet, s_CUI_ID_FRAME_AmuletID_LIST_AmuletOnListSelectChange );
theUiManager.OnListSelectChange( ID_FRAME_Amulet, ID_LIST_Symbol, s_CUI_ID_FRAME_AmuletID_LIST_SymbolOnListSelectChange );
theUiManager.OnIconDragOn( ID_FRAME_Amulet, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_AmuletID_LISTIMG_AmuletOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Amulet, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_AmuletID_LISTIMG_AmuletOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Amulet, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_AmuletID_LISTIMG_AmuletOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Amulet, ID_LISTIMG_Amulet, s_CUI_ID_FRAME_AmuletID_LISTIMG_AmuletOnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_Amulet, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_AmuletID_LISTIMG_SymbolOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_Amulet, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_AmuletID_LISTIMG_SymbolOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_Amulet, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_AmuletID_LISTIMG_SymbolOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_Amulet, ID_LISTIMG_Symbol, s_CUI_ID_FRAME_AmuletID_LISTIMG_SymbolOnIconRButtonUp );

		m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Amulet );
		m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_Amulet, ID_BUTTON_CLOSE );
		m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_Amulet, ID_TEXT_Money );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Amulet, ID_BUTTON_Cancel );
		m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Amulet, ID_BUTTON_Ok );
		m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_Amulet, ID_TEXT_Tip );
		m_pID_LIST_Amulet = (ControlList*)theUiManager.FindControl( ID_FRAME_Amulet, ID_LIST_Amulet );
		m_pID_LIST_Symbol = (ControlList*)theUiManager.FindControl( ID_FRAME_Amulet, ID_LIST_Symbol );
		m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Amulet, ID_PICTURE_Begin );
		m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Amulet, ID_LISTIMG_Amulet );
		m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Amulet, ID_LISTIMG_Symbol );
		m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Amulet, ID_PICTURE_StarEffect );
		m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_Amulet, ID_TEXT_TipAllDone );
		assert( m_pID_FRAME_EquipEvolve );
		assert( m_pID_BUTTON_CLOSE );
		assert( m_pID_TEXT_Money );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_BUTTON_Ok );
		assert( m_pID_TEXT_Tip );
		assert( m_pID_LIST_Amulet );
		assert( m_pID_LIST_Symbol );
		assert( m_pID_PICTURE_Begin );
		assert( m_pID_LISTIMG_Equip );
		assert( m_pID_LISTIMG_Material );
		assert( m_pID_PICTURE_StarEffect );
		assert( m_pID_TEXT_TipAllDone );
		m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
		EquipEvolveIntialize();

		m_pID_LIST_Amulet->HaveSelBar( 0, 0 );
		m_pID_LIST_Symbol->HaveSelBar( 0, 0 );
		m_pID_TEXT_TipAllDone->SetVisable(false);
		m_pID_TEXT_Money->SetVisable(false);
		m_pID_TEXT_Money->SetText("");
		SetDirty(true);
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_Amulet::_UnLoadUI()
	{
		ResetEquipEvolve();
		m_pID_FRAME_EquipEvolve = NULL;
		m_pSelectItem = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\Amulet.MEUI" );
	}

bool CUI_ID_FRAME_Amulet::IsEvolveAllDone( ControlIconDrag::S_ListImg * pImg )
{
	SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
	if (!psItem)
	{
		return false;
	}
	return GetBlueAttriCount(psItem) >= psItem->equipdata.quality;
}

void CUI_ID_FRAME_Amulet::ResetUIObjects()
{
	EquipEvolveUI::ResetUIObjects();
	m_pID_TEXT_Tip = NULL;
	m_pID_LIST_Amulet = NULL;
	m_pID_LIST_Symbol = NULL;
}

void CUI_ID_FRAME_Amulet::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_Amulet.SetDirty( true );
	s_CUI_ID_FRAME_Amulet.ClearEquip();	
	s_CUI_ID_FRAME_Amulet.ClearSymbol();	
	s_CUI_ID_FRAME_Amulet.RefreshAllBagEnable();

}

void CUI_ID_FRAME_Amulet::ClearEquip()
{
	m_bEquipBagEnable = true;				
	m_pID_LISTIMG_Equip->Clear();
	m_pID_TEXT_TipAllDone->SetVisable(false);
	SetDirty(true);
}

void CUI_ID_FRAME_Amulet::RefreshBeginPic()
{
	if (m_stEquipBagIndex == -1 && m_nSelectMaterialIndex == -1)
	{
		m_pID_PICTURE_Begin->SetVisable(true);
	}
	else
	{
		m_pID_PICTURE_Begin->SetVisable(false);
	}

}

void CUI_ID_FRAME_Amulet::ClearSymbol()
{
	for (int i = 0; i < m_nsMaxMaterialNum;++i)
	{
		if( m_stMaterialIndex[i] != -1 )
		{
			m_bMaterialBagEnable[i] = true;
		}
	}
	m_pID_LISTIMG_Material->Clear();
	{
		m_pID_TEXT_Money->SetText("");
	}
	m_pID_LIST_Symbol->Clear();
	m_pID_TEXT_Money->SetVisable(false);
	m_pSelectItem = NULL;
	m_nSelectMaterialIndex = -1;
	SetDirty(true);

}

void CUI_ID_FRAME_Amulet::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
	EquipEvolveUI::_RefreshEquipInfo(pListImg);
	FillBlueAttriList(pListImg,m_pID_LIST_Amulet);
}

bool CUI_ID_FRAME_Amulet::ProcessAllDone( ControlIconDrag::S_ListImg * pImg )
{
	bool bRet = EquipEvolveUI::ProcessAllDone(pImg);
	m_pID_LIST_Symbol->SetVisable(!bRet);
	m_pID_TEXT_Tip->SetVisable(!bRet);
	if (!bRet)
	{
		SCharItem* psItem = (SCharItem*)pImg->m_pkIconInfo->GetData();
		int nTotal = psItem->equipdata.quality;
		int nNowExisting = GetBlueAttriCount(psItem);
		char cTemp[256] = {0};
		sprintf_s(cTemp,256,theXmlString.GetString(eText_Amulet_Left),nTotal - nNowExisting);
		m_pID_TEXT_Tip->SetText(cTemp);
	}
	return bRet;
}

int CUI_ID_FRAME_Amulet::GetBlueAttriCount( SCharItem* psItem )
{
	int nCount = 0;
	for (int nloop=0;nloop<SCharItem::EConstDefine_BaseRandMaxCount;++nloop)
	{
		if (psItem->equipdata.baseRands[nloop] != InvalidLogicNumber)
		{
			++nCount;
		}
	}
	return nCount;
}

