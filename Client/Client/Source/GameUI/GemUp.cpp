#include <assert.h>
#include "MeUi/UiManager.h"
#include "GemUp.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "Pack.h"
#include "ScreenInfoManager.h"
#include "PackItemEnableManager.h"
#include "ItemComposeConfig.h"
#include "ItemDetail.h"
#include "IconManagerClient.h"
#include "MessageBox.h"
#define DELAY_TIME 350
#define MAX_GEM_LEVEL 5

uint16 GetGemUpMaterialID(uint8 gemLevel)
{
	uint16 materialID = 0xffff;

	switch (gemLevel)
	{
	case 1:
		materialID = SID_GemUp_Level_One;
		break;
	case 2:
		materialID = SID_GemUp_Level_Two;
		break;
	case 3:
		materialID = SID_GemUp_Level_Three;
		break;
	case 4:
		materialID = SID_GemUp_Level_Four;
		break;
	default:
		break;
	}

	return materialID;
}

CUI_ID_FRAME_GemUp s_CUI_ID_FRAME_GemUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GemUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GemUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem6OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem6OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem6OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem1OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_BUTTON_HELPOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_LISTIMG_Gem5OnIconRButtonUp )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_CHECKBOX_X3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_CHECKBOX_X4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GemUp, ID_CHECKBOX_X5OnCheckBoxCheck )

CUI_ID_FRAME_GemUp::CUI_ID_FRAME_GemUp()
{
	// Member
	m_pID_FRAME_GemUp = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_Gem6 = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_PICTURE_StarEffect = NULL;
	m_pID_TEXT_TipAllDone = NULL;
	m_pID_PICTURE_Begin = NULL;
	m_pID_LISTIMG_Gem1 = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_Gem2 = NULL;
	m_pID_LISTIMG_Gem3 = NULL;
	m_pID_LISTIMG_Gem4 = NULL;
	m_pID_LISTIMG_Gem5 = NULL;
	m_pID_TEXT_SuccessRatio = NULL;
	m_bIsPocket = false;
	m_pID_TEXT_TipFalseRecipe = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_pID_CHECKBOX_X3 = NULL;
	m_pID_CHECKBOX_X4 = NULL;
	m_pID_CHECKBOX_X5 = NULL;
	m_SelectGemNum = 3;
	m_status = EffectStatus_No;
	m_money = 0;

	m_lastpSender = NULL;
	m_lastpSender2 = NULL;
	m_EquipBagType = BT_NormalItemBag;
	m_EquipBagIndex = -1;
	m_MaterialBagType = BT_MaterialBag;
	m_MaterialIndex = -1;

	m_pID_TEXT_Gem1_Name = NULL;
	m_pID_TEXT_Gem2_Name = NULL;
	m_pID_TEXT_MaterialName = NULL;

}
// Frame
bool CUI_ID_FRAME_GemUp::OnFrameRun()
{
	ProcessCloseUI();

	DWORD dwTimeNow = timeGetTime();
	switch (m_status)
	{
	case EffectStatus_Fail:
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(true);
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(dwTimeNow-dwBeginTime >= DELAY_TIME)
			m_status = EffectStatus_No;
		break;
	case EffectStatus_Success:
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(true);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		if(dwTimeNow-dwBeginTime >= DELAY_TIME) 
			m_status = EffectStatus_No;
		break;
	case EffectStatus_No:
		if(m_pID_TEXT_Success) m_pID_TEXT_Success->SetVisable(false);
		if(m_pID_TEXT_Fail) m_pID_TEXT_Fail->SetVisable(false);
		break;
	}

	return true;
}
bool CUI_ID_FRAME_GemUp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GemUp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem6OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	//ClearMaterial(m_pID_LISTIMG_Material);
	m_lastpSender2 = pSender;
    OnGemMaterialDragOn(m_pID_LISTIMG_Material,pItemDrag,pSender,BT_MaterialBag);
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearMaterial(m_pID_LISTIMG_Material);
	return false;
}

// Button
bool CUI_ID_FRAME_GemUp::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_GemUp::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	SendGemUpMsg();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if( !pItemCommon )
		return false;

	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_GEM )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eWarning_GemUp_ErrorType) );
		return false;
	}
	/*ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
	if (pCanEquip->ustEquipType == ItemDefine::equip_AecorativeClothing)
		return false;*/

	ClearGem(0,m_pID_LISTIMG_Gem1);
	m_lastpSender = pSender;
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(0,m_pID_LISTIMG_Gem1,pItemDrag,pSender,nBagType);	
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	//ClearGem(0,m_pID_LISTIMG_Gem1);
	ClearGems();
	return false;
}

// Button
bool CUI_ID_FRAME_GemUp::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(1,m_pID_LISTIMG_Gem2);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(1,m_pID_LISTIMG_Gem2,pItemDrag,pSender,nBagType);	
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(1,m_pID_LISTIMG_Gem2);
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(2,m_pID_LISTIMG_Gem3);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(2,m_pID_LISTIMG_Gem3,pItemDrag,pSender,nBagType);	
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(2,m_pID_LISTIMG_Gem3);
	return false;
}

// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(3,m_pID_LISTIMG_Gem4);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(3,m_pID_LISTIMG_Gem4,pItemDrag,pSender,nBagType);	
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(3,m_pID_LISTIMG_Gem4);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													 ControlIconDrag::S_ListImg* pItemDrag,
													 ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(4,m_pID_LISTIMG_Gem5);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(4,m_pID_LISTIMG_Gem5,pItemDrag,pSender,nBagType);	
	
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_GemUp::ID_LISTIMG_Gem5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(4,m_pID_LISTIMG_Gem5);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_GemUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GemUp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GemUp.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GemUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GemUp, s_CUI_ID_FRAME_GemUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GemUp, s_CUI_ID_FRAME_GemUpOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GemUp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GemUpID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem6, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem6OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem6, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem6OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem6, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem6OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem6, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem6OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemUpID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemUpID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemUpID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_GemUpID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_GemUp, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GemUpID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_GemUp, ID_BUTTON_Ok, s_CUI_ID_FRAME_GemUpID_BUTTON_OkOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem1, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem1OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem1, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem1OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem1, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem1OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem1, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem1OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_GemUp, ID_BUTTON_HELP, s_CUI_ID_FRAME_GemUpID_BUTTON_HELPOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem2, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem2, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem2, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem2, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem2OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem3, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem3OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem3, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem3OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem3, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem3OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem3, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem3OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem4, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem4OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem4, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem4OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem4, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem4OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem4, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem4OnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_GemUp, ID_LISTIMG_Gem5, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem5OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_GemUp, ID_LISTIMG_Gem5, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem5OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_GemUp, ID_LISTIMG_Gem5, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem5OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_GemUp, ID_LISTIMG_Gem5, s_CUI_ID_FRAME_GemUpID_LISTIMG_Gem5OnIconRButtonUp );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GemUp, ID_CHECKBOX_X3, s_CUI_ID_FRAME_GemUpID_CHECKBOX_X3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GemUp, ID_CHECKBOX_X4, s_CUI_ID_FRAME_GemUpID_CHECKBOX_X4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GemUp, ID_CHECKBOX_X5, s_CUI_ID_FRAME_GemUpID_CHECKBOX_X5OnCheckBoxCheck );


	m_pID_FRAME_GemUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GemUp );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemUp, ID_BUTTON_CLOSE );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Money );
	m_pID_LISTIMG_Gem6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem6 );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Material );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemUp, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemUp, ID_BUTTON_Ok );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Tip );
	m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemUp, ID_PICTURE_StarEffect );
	m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_TipAllDone );
	m_pID_PICTURE_Begin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GemUp, ID_PICTURE_Begin );
	m_pID_LISTIMG_Gem1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem1 );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_GemUp, ID_BUTTON_HELP );
	m_pID_LISTIMG_Gem2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem2 );
	m_pID_LISTIMG_Gem3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem3 );
	m_pID_LISTIMG_Gem4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem4 );
	m_pID_LISTIMG_Gem5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_GemUp, ID_LISTIMG_Gem5 );
	m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_SuccessRatio );
	m_pID_TEXT_TipFalseRecipe = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_TipFalseRecipe );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Fail );
	m_pID_CHECKBOX_X3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GemUp, ID_CHECKBOX_X3 );
	m_pID_CHECKBOX_X4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GemUp, ID_CHECKBOX_X4 );
	m_pID_CHECKBOX_X5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GemUp, ID_CHECKBOX_X5 );
	m_pID_TEXT_Gem1_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Gem1_Name );
	m_pID_TEXT_Gem2_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_Gem2_Name );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_GemUp, ID_TEXT_MaterialName );

	assert(m_pID_TEXT_TipFalseRecipe);
	assert( m_pID_FRAME_GemUp );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Money );
	assert( m_pID_LISTIMG_Gem6 );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Tip );
	assert( m_pID_PICTURE_StarEffect );
	assert( m_pID_TEXT_TipAllDone );
	assert( m_pID_PICTURE_Begin );
	assert( m_pID_LISTIMG_Gem1 );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LISTIMG_Gem2 );
	assert( m_pID_LISTIMG_Gem3 );
	assert( m_pID_LISTIMG_Gem4 );
	assert( m_pID_LISTIMG_Gem5 );
	assert( m_pID_TEXT_SuccessRatio );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_CHECKBOX_X3 );
	assert( m_pID_CHECKBOX_X4 );
	assert( m_pID_CHECKBOX_X5 );
	assert( m_pID_TEXT_Gem1_Name );
	assert( m_pID_TEXT_Gem2_Name );
	assert( m_pID_TEXT_MaterialName );

	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_FRAME_GemUp->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_LISTIMG_Gem6->SetEnableDrag(false);
	m_pID_TEXT_Tip->SetVisable(false);
	m_pID_TEXT_TipAllDone->SetVisable(false);
	m_pID_TEXT_TipFalseRecipe->SetVisable(false);
	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_CHECKBOX_X3->SetCheck(true);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_X5->SetCheck(false);

	m_pID_TEXT_Gem1_Name->SetText("");
	m_pID_TEXT_Gem2_Name->SetText("");
	m_pID_TEXT_MaterialName->SetText("");

	return true;
}

// 卸载UI
bool CUI_ID_FRAME_GemUp::_UnLoadUI()
{
	m_pID_FRAME_GemUp = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GemUp.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_GemUp::_IsVisable()
{
	if(!m_pID_FRAME_GemUp)
		return false;

	return m_pID_FRAME_GemUp->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_GemUp::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_GemUp)
		return;

	m_pID_FRAME_GemUp->SetVisable( bVisable );	
}

bool CUI_ID_FRAME_GemUp::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if(m_GemMaterial.n64Guid == nGuid)
		return true;

	for( int i = 0; i < nMaxGemNum; ++i )
	{
		if( m_Gems[i].n64Guid == nGuid )
		{
			return true;
		}
	}
	return false;
}

void CUI_ID_FRAME_GemUp::ProcessCloseUI()
{
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if (!pMe )
		return;

	Vector vPos;
	pMe->GetPos( &vPos.x, &vPos.y, &vPos.z );
	if(IsOverDistance(vPos) && !GetIsPocket())
		SetVisable(false);
}

bool CUI_ID_FRAME_GemUp::IsOverDistance(const Vector& vCurPos)
{
	float xoff = vCurPos.x - m_vVisiblePos.x;
	float yoff = vCurPos.y - m_vVisiblePos.y;
	float fDist = sqrtf( xoff*xoff + yoff*yoff );
	return (fDist > 12.0f);
}

void CUI_ID_FRAME_GemUp::ClearGems()
{
	if(!m_pID_FRAME_GemUp)
		return;

	ClearGem(0,m_pID_LISTIMG_Gem1);
	ClearGem(1,m_pID_LISTIMG_Gem2);
	ClearGem(2,m_pID_LISTIMG_Gem3);
	ClearGem(3,m_pID_LISTIMG_Gem4);
	ClearGem(4,m_pID_LISTIMG_Gem5);
	ClearGem(5,m_pID_LISTIMG_Gem6);

	ClearMaterial(m_pID_LISTIMG_Material);
	m_pID_TEXT_SuccessRatio->SetVisable(false);
	//m_pID_TEXT_Money->SetVisable(false);
	m_pID_TEXT_SuccessRatio->SetText("");
	m_pID_TEXT_Money->SetText("");
	m_pID_CHECKBOX_X3->SetCheck(true);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_X5->SetCheck(false);
	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_CHECKBOX_X3->SetEnable(true);
	m_pID_CHECKBOX_X4->SetEnable(true);
	m_pID_CHECKBOX_X5->SetEnable(true);
	m_SelectGemNum = 3;
	m_money = 0;
	m_lastpSender = NULL;
	m_lastpSender2 = NULL;

	m_pID_TEXT_Gem1_Name->SetText("");
	m_pID_TEXT_Gem2_Name->SetText("");
}


bool CUI_ID_FRAME_GemUp::OnGemDragOn(int nIndex,ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType/* = BT_NormalItemBag*/)
{
	if(nIndex < 0 ||  nIndex >= nMaxGemNum || !pTargetImg || !pItemDrag)
		return false;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;
	
	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_GEM && pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemUp_ErrorType) );
		return false;
	}

	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )pItemCommon;
	if (!pGem)
		return false;

	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	//ControlIconDrag::S_ListImg * pImg = pTargetImg->GetItemByIndex(0);

	CItemBag2* pdrag_bag;
	switch (stEquipBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	}

	/*int Index = -1;
	for (int i = 0; i < nMaxGemNum; ++i)
	{
		if(m_Gems[i].n64Guid == 0)
		{
			m_Gems[i].shBagType = stEquipBagType;
			m_Gems[i].shIndex   = s_CUI_ID_FRAME_PACK.GetIndexByItem( stEquipBagType, pItemDrag );

			SCharItem item;
			if(m_Gems[i].shIndex != -1 && pdrag_bag->GetItem(m_Gems[i].shIndex,&item))
				m_Gems[i].n64Guid = item.itembaseinfo.nOnlyInt;
			else
				m_Gems[i].n64Guid = 0;

			m_Gems[i].nCount = pItemDrag->m_pkIconInfo->Count();
			Index = i;
			break;
		}
	}*/

	m_Gems[nIndex].shBagType = stEquipBagType;
	m_Gems[nIndex].shIndex   = s_CUI_ID_FRAME_PACK.GetIndexByItem( stEquipBagType, pItemDrag );

	SCharItem item;
	if(m_Gems[nIndex].shIndex != -1 && pdrag_bag->GetItem(m_Gems[nIndex].shIndex,&item))
		m_Gems[nIndex].n64Guid = item.itembaseinfo.nOnlyInt;
	else
		m_Gems[nIndex].n64Guid = 0;

	m_Gems[nIndex].nCount = pItemDrag->m_pkIconInfo->Count();

	m_EquipBagType = stEquipBagType;
	m_EquipBagIndex = m_Gems[nIndex].shIndex;

	//设置值
	/*int ncount = pItemDrag->m_pkIconInfo->Count();
	if (pImg && !pImg->IsNull())
		ncount += pImg->m_pkIconInfo->Count();*/
	pTargetImg->Clear();
	ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(),/*ncount*/pItemDrag->m_pkIconInfo->Count(), eIcon_Enable, false, eTipFlag_Normal, false, item.IsBounded());
	pTargetImg->SetItem(&img);

	//if (Index != -1)
	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_Gems[nIndex].shIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	if (m_GemMaterial.shIndex != -1)
	{
		ControlIconDrag::S_ListImg * pMaterialImg = m_pID_LISTIMG_Material->GetItemByIndex(0);
		if (pMaterialImg && !pMaterialImg->IsNull())
		{
			uint16 materialID = GetGemUpMaterialID(pGem->gemLevel);
			if (materialID != pMaterialImg->m_pkIconInfo->GetItemId())
				ClearMaterial(m_pID_LISTIMG_Material);
		}
	}

	SetSelectCheck();

	unsigned short ustID = GetGemIdByGems();

	RefreshTargetGem(ustID);
	RefreshSuccessRatio();
	RefreshOkEnable();
	ShowGemName(m_pID_TEXT_Gem1_Name, pItemDrag);
	return true;
}

int CUI_ID_FRAME_GemUp::GetGemIdByGems()
{
	unsigned short ustID = 0;

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return 0;

	SCharItem* pCharItem[nMaxGemNum];
	for (int n =0;n < nMaxGemNum;n++)
	{
		pCharItem[n] = NULL;
	}	
	int nCount = 0;
	/*short id[nMaxGemNum];
	memset(id,0,nMaxGemNum);*/
	for (int i = 0;i < nMaxGemNum;i++)
	{
		if(m_Gems[i].n64Guid != 0)
		{
			CItemBag2* pdrag_bag;
			switch (m_Gems[i].shBagType)
			{
			case BT_NormalItemBag:
				pdrag_bag = &thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pdrag_bag = &thePlayerRole.m_bagMaterial;
				break;
			default:
				pdrag_bag = &thePlayerRole.m_bagMaterial;
				break;
			}
			pCharItem[i] = pdrag_bag->GetCharItemFromIdx(m_Gems[i].shIndex);
			//id[i] = -1;
			//if (pCharItem[i])
			//{
			//	id[i] = pCharItem[i]->itembaseinfo.ustItemID;
			//}
			++nCount;
		}
	}

	//char temp[512];
	//sprintf(temp,"count:%d,id0:%d,id1:%d,id2:%d,id3:%d,id4:%d",nCount,id[0],id[1],id[2],id[3],id[4]);
	//MessageBox(NULL,temp,"123",MB_OK);

	if(nCount > 0 && pImg->m_pkIconInfo->Count() >= m_SelectGemNum)
	{
		//const ComposeData2 *pData = theItemComposeConfig.GetComposeData(pCharItem,nCount);
		const ComposeData2 *pData = theItemComposeConfig.GetComposeDataNew(pCharItem[0]->GetItemID(), m_SelectGemNum);
		if(pData)
			ustID = pData->GetNewItemID();
	}

	return ustID;
}

void CUI_ID_FRAME_GemUp::ClearGem(int nIndex,ControlListImage *pTargetImg)
{
	if(nIndex < 0 ||  nIndex >= nMaxGemNum)
		return;

	if(pTargetImg)
	    pTargetImg->Clear();


	CItemBag2* pTargetBag;
	switch (m_Gems[nIndex].shBagType)
	{
	case BT_NormalItemBag:
		pTargetBag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pTargetBag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pTargetBag = &thePlayerRole.m_bagMaterial;
		break;
	}

	int nNum = m_Gems[nIndex].shIndex;
	m_Gems[nIndex].shBagType = -1;
	m_Gems[nIndex].shIndex   = -1;
	m_Gems[nIndex].n64Guid = 0;
	m_Gems[nIndex].nCount = 0;

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pTargetBag, nNum, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	m_EquipBagType = BT_NormalItemBag;
	m_EquipBagIndex = -1;

	unsigned short ustID = GetGemIdByGems();
	RefreshTargetGem(ustID);
	RefreshSuccessRatio();
	RefreshOkEnable();
}

void CUI_ID_FRAME_GemUp::ClearMaterial(ControlListImage *pTargetImg)
{
	if(pTargetImg)
		pTargetImg->Clear();

	int nIndex = m_GemMaterial.shIndex;
	m_GemMaterial.shBagType = BT_NormalItemBag;
	m_GemMaterial.shIndex = -1;
	m_GemMaterial.n64Guid = 0;
	m_GemMaterial.nCount = 0;

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	m_MaterialBagType = BT_MaterialBag;
	m_MaterialIndex = -1;

	m_pID_TEXT_MaterialName->SetText("");

	RefreshSuccessRatio();
}

bool CUI_ID_FRAME_GemUp::OnGemMaterialDragOn(ControlListImage *pTargetImg,ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType /*= BT_NormalItemBag*/)
{
	if(!pTargetImg || !pItemDrag || !pSender)
		return false;

	ControlIconDrag::S_ListImg * pGemImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
	if (!pGemImg || pGemImg->IsNull())
		return false;
	ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pGemImg->m_pkIconInfo->GetItemId() );
	if( !pCommon )
		return false;
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )pCommon;
	if (!pGem)
		return false;

	uint16 nMaterialID = GetGemUpMaterialID(pGem->gemLevel);
	if (nMaterialID == 0xffff)
		return false;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if (pItemCommon->ustItemID != nMaterialID)
		return false;

	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemUp_ErrorType) );
		return false;
	}

	ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
	if(pMaterial->stMaterialType != ItemDefine::ematerial_gemcomposerune)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Gem_Failed, theXmlString.GetString(eWarning_GemUp_ErrorType) );
		return false;
	}

	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		return false;

	m_GemMaterial.shBagType = stEquipBagType;
	m_GemMaterial.shIndex   = s_CUI_ID_FRAME_PACK.GetIndexByItem( stEquipBagType, pItemDrag );

	SCharItem item;
	if(m_GemMaterial.shIndex != -1 && thePlayerRole.m_bagMaterial.GetItem(m_GemMaterial.shIndex,&item))
		m_GemMaterial.n64Guid = item.itembaseinfo.nOnlyInt;
	else
		m_GemMaterial.n64Guid = 0;

	m_GemMaterial.nCount = pItemDrag->m_pkIconInfo->Count();

	m_MaterialBagType = stEquipBagType;
	m_MaterialIndex = m_GemMaterial.shIndex;

	//设置值
	m_pID_LISTIMG_Material->Clear();
	ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(),pItemDrag->m_pkIconInfo->Count());
	m_pID_LISTIMG_Material->SetItem(&img);

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_GemMaterial.shIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	RefreshSuccessRatio();
	ShowMaterialName(pItemDrag);
	return true;
}
bool GemUpMessageBoxResult(char bSend, void *pData )
{
	if( !bSend )
		return false;
	Msg* pMsg = static_cast<Msg*>(pData);
	GettheNetworkInput().SendMsg( pMsg );	
	return true;
}
void CUI_ID_FRAME_GemUp::SendGemUpMsg(bool CheckBounded)
{
	int nCount = 0;
	MsgItemComposeGem msgComposeGem;
	msgComposeGem.composeType = MsgItemComposeGem::ECT_GEM;

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;
	if (pImg->m_pkIconInfo->Count() < m_SelectGemNum)
		return;

	for (int i = 0;i < nMaxGemNum;++i)
	{
		if(m_Gems[i].n64Guid != 0)
		{
			msgComposeGem.materials[i].nItemBagType = m_Gems[i].shBagType;
			msgComposeGem.materials[i].nItemIndex   = m_Gems[i].shIndex;
			msgComposeGem.materials[i].nItemGuid    = m_Gems[i].n64Guid;
			msgComposeGem.materials[i].nCount       = m_Gems[i].nCount;
			++nCount;
		}
	}
	if(nCount == 0)
		return;
	msgComposeGem.nSelectGemNum = m_SelectGemNum;

	//如果只放了一个宝石，而且没有放升级材料也不给服务器发消息，以免增加服务器压力
	/*if (nCount == 1 &&  m_GemMaterial.shIndex == -1)
	{
		return;
	}*/
	msgComposeGem.nMaterialCount = nCount;
	msgComposeGem.composeRune.nItemBagType = m_GemMaterial.shBagType;
	msgComposeGem.composeRune.nItemIndex   = m_GemMaterial.shIndex;
	msgComposeGem.composeRune.nItemGuid    = m_GemMaterial.n64Guid;
	msgComposeGem.composeRune.nCount       = m_GemMaterial.nCount;

	//判断是否绑定
	if(CheckBounded)
	{
		SCharItem pEquip;
		if(thePlayerRole.GetBagItemByGUID(m_GemMaterial.n64Guid,&pEquip) && 
			pEquip.IsBounded())
		{
			//提示玩家绑定
			s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_EquipMaterialBound), "", CUI_ID_FRAME_MessageBox::eTypeYesNo, true,GemUpMessageBoxResult ,&msgComposeGem,msgComposeGem.GetLength());
		}
		else
			GettheNetworkInput().SendMsg( &msgComposeGem );
	}
	else
		GettheNetworkInput().SendMsg( &msgComposeGem );
}

void CUI_ID_FRAME_GemUp::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_GemUp.ClearGems();
	s_CUI_ID_FRAME_GemUp.RefreshOkEnable();
}

void CUI_ID_FRAME_GemUp::OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc)
{
	if(!pSender || !pItemDrag)
		return;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return;

	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
	{
		/*ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
		int ncount = 0;
		uint16 itemid = 0;
		if (pImg && !pImg->IsNull())
		{
			ncount = pImg->m_pkIconInfo->Count();
			itemid = pImg->m_pkIconInfo->GetItemId();
		}
		if (ncount >= nMaxGemNum)
			return;
		if (itemid && itemid != pItemDrag->m_pkIconInfo->GetItemId())
			return;*/
		if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_GEM )
		{
			ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )pItemCommon;
			if (!pGem)
				return;

			if (pGem->gemLevel >= MAX_GEM_LEVEL)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_ScreenCenterCommon, theXmlString.GetString(eText_GemUp_MaxLevel) );
				return;
			}
		}

		ID_LISTIMG_Gem1OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);

		/*for (int i = 0;i < nMaxGemNum;++i)
		{
			if(m_Gems[i].n64Guid == 0)
			{
				if(i == 0)
					ID_LISTIMG_Gem1OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 1)
					ID_LISTIMG_Gem2OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 2)
					ID_LISTIMG_Gem3OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 3)
					ID_LISTIMG_Gem4OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 4)
					ID_LISTIMG_Gem5OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 5)
					ID_LISTIMG_Gem6OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				break;
			}
		}*/
	}
	else if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
	{
		ItemDefine::SCreateMaterial *pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
		if(pMaterial->stMaterialType != ItemDefine::ematerial_gemcomposerune)
			return;
		if(m_pID_LISTIMG_Material->GetItemByIndex(0)->m_pkIconInfo->GetItemId() !=0)
			return;
		ID_LISTIMG_MaterialOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
	}
}

void CUI_ID_FRAME_GemUp::RefreshSuccessRatio(void)
{
	m_pID_TEXT_SuccessRatio->SetVisable(false);

	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;
	for (int i = 0;i < nMaxGemNum;++i )
	{
		if(m_Gems[i].n64Guid != 0)
			m_pID_TEXT_SuccessRatio->SetVisable(true);
	}

	unsigned short ratio = 0.0f;

	{//多个宝石自身的概率
		SCharItem *gemItems[nMaxGemNum];
		SCharItem items[nMaxGemNum];
		int count = 0;
		for(int i=0; i<nMaxGemNum; ++i)
		{
			CItemBag2* pTargetBag;
			switch (m_Gems[i].shBagType)
			{
			case BT_NormalItemBag:
				pTargetBag = &thePlayerRole.m_bag;
				break;
			case BT_MaterialBag:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			default:
				pTargetBag = &thePlayerRole.m_bagMaterial;
				break;
			}
			if(/*BT_MaterialBag == m_Gems[i].shBagType &&*/ m_Gems[i].shIndex >=0 && pTargetBag->GetItem(m_Gems[i].shIndex, items + count))
			{
				gemItems[count] = &items[count];
				++count;
			}
		}

		if(count > 0 && pImg->m_pkIconInfo->Count() >= m_SelectGemNum)
		{
			//const ComposeData2* pData = theItemComposeConfig.GetComposeData(gemItems, count);
			const ComposeData2 *pData = theItemComposeConfig.GetComposeDataNew(gemItems[0]->GetItemID(), m_SelectGemNum);
			if(pData != NULL)
			{
				ratio = pData->GetProbility();
				RefreshMoney(pData->GetCostMoney());
				m_money = pData->GetCostMoney();
			}
		}
	}
	
	float successRatio = (float)ratio;
	//镶嵌符
	if(BT_MaterialBag == m_GemMaterial.shBagType && m_GemMaterial.shIndex >= 0)
	{
		SCharItem materialItem;
		
		if(thePlayerRole.m_bagMaterial.GetItem(m_GemMaterial.shIndex, &materialItem))
		{
			ItemDefine::SCreateMaterial *pItem = (ItemDefine::SCreateMaterial *)GettheItemDetail().GetItemByID(materialItem.GetItemID());
			if(pItem != NULL)
			{
				successRatio += pItem->fAddIntensifyRate[0];
			}
		}
	}

	if(m_pID_TEXT_SuccessRatio != NULL)
	{
		if(successRatio > 100.0f)
			successRatio = 100.0f;

		char buf[32] = {0};
		MeSprintf_s(buf,sizeof(buf), "%d%%", (int)successRatio);
		m_pID_TEXT_SuccessRatio->SetText(buf);
	}
}

void CUI_ID_FRAME_GemUp::RefreshOkEnable()
{
	if(!m_pID_FRAME_GemUp)
		return;

	m_pID_BUTTON_Ok->SetEnable(false);
	ControlListImage::S_ListImg *pImg = m_pID_LISTIMG_Gem6->GetItemByIndex(0);
	if(!pImg)
		return;

	if(pImg->IsNull())
		return;

	if(!thePlayerRole.HaveEnoughMoney(m_money))
		return;

	m_pID_BUTTON_Ok->SetEnable(true);
}

void CUI_ID_FRAME_GemUp::RefreshTargetGem(unsigned short usItemID)
{
	m_pID_TEXT_Tip->SetVisable(false);
	m_pID_TEXT_TipFalseRecipe->SetVisable(false);
	if(usItemID == 0)
	{
		m_pID_LISTIMG_Gem6->Clear();
		m_pID_TEXT_Gem2_Name->SetText("");
		if (!m_pID_LISTIMG_Gem1->GetItemByIndex(0)->IsNull() && !m_pID_LISTIMG_Gem2->GetItemByIndex(0)->IsNull() && 
			!m_pID_LISTIMG_Gem3->GetItemByIndex(0)->IsNull() && !m_pID_LISTIMG_Gem4->GetItemByIndex(0)->IsNull() && 
			!m_pID_LISTIMG_Gem5->GetItemByIndex(0)->IsNull() )
		{
			if (m_pID_LISTIMG_Material->GetItemByIndex(0) == NULL)
			{
				if (m_pID_TEXT_Tip )
				{
					m_pID_TEXT_Tip->SetVisable(true);
				}
			}
			else
			{
				if (m_pID_TEXT_TipFalseRecipe)
				{
					m_pID_TEXT_TipFalseRecipe->SetVisable(true);
				}
			}
		}
	}
	else
	{
		ControlListImage::S_ListImg *img1 = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
		if ( !img1 || img1->IsNull() )
			return;
		SCharItem *pItem = (SCharItem*)img1->m_pkIconInfo->GetData();
		if ( !pItem )
			return;
		ControlListImage::S_ListImg img;
		img.SetData(usItemID,1,eIcon_Enable, false, eTipFlag_Normal, false, pItem->IsBounded());
		m_pID_LISTIMG_Gem6->SetItem(&img);

		ShowGemName(m_pID_TEXT_Gem2_Name, &img);
	}
}

// CheckBox
void CUI_ID_FRAME_GemUp::ID_CHECKBOX_X3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (!m_pID_CHECKBOX_X3 && !m_pID_CHECKBOX_X4 && !m_pID_CHECKBOX_X5)
		return;

	m_pID_CHECKBOX_X3->SetCheck(true);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_X5->SetCheck(false);
	m_SelectGemNum = 3;
	RefreshSuccessRatio();
	RefreshOkEnable();
}
// CheckBox
void CUI_ID_FRAME_GemUp::ID_CHECKBOX_X4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (!m_pID_CHECKBOX_X3 && !m_pID_CHECKBOX_X4 && !m_pID_CHECKBOX_X5)
		return;

	m_pID_CHECKBOX_X3->SetCheck(false);
	m_pID_CHECKBOX_X4->SetCheck(true);
	m_pID_CHECKBOX_X5->SetCheck(false);
	m_SelectGemNum = 4;
	RefreshSuccessRatio();
	RefreshOkEnable();
}
// CheckBox
void CUI_ID_FRAME_GemUp::ID_CHECKBOX_X5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (!m_pID_CHECKBOX_X3 && !m_pID_CHECKBOX_X4 && !m_pID_CHECKBOX_X5)
		return;

	m_pID_CHECKBOX_X3->SetCheck(false);
	m_pID_CHECKBOX_X4->SetCheck(false);
	m_pID_CHECKBOX_X5->SetCheck(true);
	m_SelectGemNum = 5;
	RefreshSuccessRatio();
	RefreshOkEnable();
}

void CUI_ID_FRAME_GemUp::SetSelectCheck()
{
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Gem1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;
	if (!m_pID_CHECKBOX_X3 && !m_pID_CHECKBOX_X4 && !m_pID_CHECKBOX_X5)
		return;
	int ncount = pImg->m_pkIconInfo->Count();

	m_pID_CHECKBOX_X3->SetEnable(true);
	m_pID_CHECKBOX_X4->SetEnable(true);
	m_pID_CHECKBOX_X5->SetEnable(true);

	if (ncount >= 5)
		return;

	if (ncount >= 4)
	{
		m_pID_CHECKBOX_X5->SetEnable(false);

		if (m_SelectGemNum > 4)
		{
			m_pID_CHECKBOX_X3->SetCheck(true);
			m_pID_CHECKBOX_X4->SetCheck(false);
			m_pID_CHECKBOX_X5->SetCheck(false);
			m_SelectGemNum = 3;
		}
		return;
	}

	if (ncount >= 3)
	{
		m_pID_CHECKBOX_X4->SetEnable(false);
		m_pID_CHECKBOX_X5->SetEnable(false);

		if (m_SelectGemNum > 3)
		{
			m_pID_CHECKBOX_X3->SetCheck(true);
			m_pID_CHECKBOX_X4->SetCheck(false);
			m_pID_CHECKBOX_X5->SetCheck(false);
			m_SelectGemNum = 3;
		}
		return;
	}
}

void CUI_ID_FRAME_GemUp::RefreshMoney(unsigned int nmoney)
{
	if (!m_pID_TEXT_Money)
		return;

	m_pID_TEXT_Money->SetText("");

	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(nmoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nmoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
	}

	m_pID_TEXT_Money->SetText(text,dwColor);
}

void CUI_ID_FRAME_GemUp::UpdateAll()
{
	if (!m_lastpSender && !m_lastpSender2)
		return;
	if (m_EquipBagIndex != -1)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_EquipBagType, m_EquipBagIndex );
		if( !pItemImg || pItemImg->IsNull())
		{
			ClearGems();
			return;
		}

		ID_LISTIMG_Gem1OnIconDragOn(m_lastpSender, NULL, pItemImg, 0);
	}

	if (m_MaterialIndex != -1)
	{
		ControlIconDrag::S_ListImg* pItemImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( m_MaterialBagType, m_MaterialIndex );
		if( !pItemImg || pItemImg->IsNull())
		{
			ClearMaterial(m_pID_LISTIMG_Material);
			return;
		}

		ID_LISTIMG_MaterialOnIconDragOn(m_lastpSender2, NULL, pItemImg, 0);
	}
}

void CUI_ID_FRAME_GemUp::ShowGemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pText || !pItemDrag)
		return;
	pText->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;
	ItemDefine::SItemGem* pGem = ( ItemDefine::SItemGem* )pItemCommon;

	// 一颗宝石2属性
	char szTemp[MAX_PATH] = {0};
	std::string strGemAttr;
	for( int j = 0; j < ItemDefine::SItemGem::CD_TypeCount; ++j )
	{
		strGemAttr = S_IconInfoHero::GetRandStringByType( pGem->type[j] );
		if( strGemAttr.empty() )
			continue;

		if( pGem->type[j] == RT_AddMoveSpeed )
		{
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%.2f", strGemAttr.c_str(), pGem->value[j].fValue );
			strGemAttr = szTemp;
			break;
		}
		else
		{
			MeSprintf_s( szTemp, sizeof( szTemp ) / sizeof( char ) - 1, "%s+%d", strGemAttr.c_str(), ( int )pGem->value[j].fValue );
			strGemAttr = szTemp;
			if( pGem->type[j] == RT_AddExpPer )
				strGemAttr += "%";
			break;
		}
	}

	pText->SetText(strGemAttr.c_str());
}

void CUI_ID_FRAME_GemUp::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!m_pID_TEXT_MaterialName || !pItemDrag)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());

	m_pID_TEXT_MaterialName->SetText(temp);
}