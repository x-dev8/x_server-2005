/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_03.01\Data\Ui\zhujiangUp.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "zhujiangUp.h"
#include "UIMgr.h"
#include "Pack.h"
#include "PackItemEnableManager.h"
#include "ItemDetail.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "Core/Name.h"
#include "ItemComposeConfig.h"
#include "Common.h"

#define DELAY_TIME 350

CUI_ID_FRAME_ZhuJianUp s_CUI_ID_FRAME_ZhuJianUp;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ZhuJianUp, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ZhuJianUp, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_BUTTON_HELPOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5OnIconRButtonUp )
CUI_ID_FRAME_ZhuJianUp::CUI_ID_FRAME_ZhuJianUp()
{
	// Member
	m_pID_FRAME_ZhuJianUp = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_LISTIMG_ZJ6 = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_LISTIMG_ZJ1 = NULL;
	m_pID_BUTTON_HELP = NULL;
	m_pID_LISTIMG_ZJ2 = NULL;
	m_pID_LISTIMG_ZJ3 = NULL;
	m_pID_LISTIMG_ZJ4 = NULL;
	m_pID_LISTIMG_ZJ5 = NULL;
	m_pID_TEXT_SuccessRatio = NULL;
	m_pID_TEXT_Success = NULL;
	m_pID_TEXT_Fail = NULL;
	m_status = EffectStatus_No;

	m_lastpSender = NULL;
	m_lastpSender2 = NULL;
	m_EquipBagType = BT_NormalItemBag;
	m_EquipBagIndex = -1;
	m_MaterialBagType = BT_MaterialBag;
	m_MaterialIndex = -1;

	m_pID_TEXT_Tu1_Name = NULL;
	m_pID_TEXT_Tu2_Name = NULL;
	m_pID_TEXT_Tip = NULL;
	m_pID_TEXT_MaterialName = NULL;

}
// Frame
bool CUI_ID_FRAME_ZhuJianUp::OnFrameRun()
{
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
bool CUI_ID_FRAME_ZhuJianUp::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ZhuJianUp::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ6OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ6OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ6OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ6OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearMaterial(m_pID_LISTIMG_Material);
	m_lastpSender2 = pSender;
	OnGemMaterialDragOn(m_pID_LISTIMG_Material,pItemDrag,pSender,BT_MaterialBag);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearMaterial(m_pID_LISTIMG_Material);
	return false;
}
// Button
bool CUI_ID_FRAME_ZhuJianUp::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}
// Button

bool IsSendMsg(char bSend, void *pData )
{
	if( !bSend )
		return false;

	s_CUI_ID_FRAME_ZhuJianUp.SendZhuJiangUpMsg();
	return true;
}

bool CUI_ID_FRAME_ZhuJianUp::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	CItemBag2* pdrag_bag = NULL;
	switch (m_Gems[0].shBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	}

	bool bBounded = false;
	for (int i = 0; i < nMaxZhuJiangNum - 1; i++)
	{
		SCharItem item, item1;
		if (m_Gems[i].n64Guid != 0 && m_Gems[i+1].n64Guid != 0)
		{
			if(pdrag_bag->GetItem(m_Gems[i].shIndex,&item) && pdrag_bag->GetItem(m_Gems[i+1].shIndex,&item1))
			{
				if (item.IsBounded() != item1.IsBounded())
				{
					bBounded = true;
					break;
				}
			
			}
		}
	}

	if(m_GemMaterial.n64Guid != 0)
	{
		SCharItem pEquip;
		if(thePlayerRole.GetBagItemByGUID(m_GemMaterial.n64Guid,&pEquip))
		{
			if(pEquip.IsBounded())
			{
				//提示玩家会绑定
				s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_ZhuJiangUpBound), "",
				CUI_ID_FRAME_MessageBox::eTypeYesNo, true, IsSendMsg);
				return true;
			}
		}
	}
	SendZhuJiangUpMsg();
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ1OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(0,m_pID_LISTIMG_ZJ1);
	m_lastpSender = pSender;
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(0,m_pID_LISTIMG_ZJ1,pItemDrag,pSender,nBagType);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	//ClearGem(0,m_pID_LISTIMG_ZJ1);
	ClearGems();
	return false;
}
// Button
bool CUI_ID_FRAME_ZhuJianUp::ID_BUTTON_HELPOnButtonClick( ControlObject* pSender )
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(1,m_pID_LISTIMG_ZJ2);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(1,m_pID_LISTIMG_ZJ2,pItemDrag,pSender,nBagType);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(1,m_pID_LISTIMG_ZJ2);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(2,m_pID_LISTIMG_ZJ3);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(2,m_pID_LISTIMG_ZJ3,pItemDrag,pSender,nBagType);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(2,m_pID_LISTIMG_ZJ3);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ4OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(3,m_pID_LISTIMG_ZJ4);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(3,m_pID_LISTIMG_ZJ4,pItemDrag,pSender,nBagType);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(3,m_pID_LISTIMG_ZJ4);
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ5OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
										ControlIconDrag::S_ListImg* pItemDrag,
										ControlIconDrag::S_ListImg* pItemSrc )
{
	ClearGem(4,m_pID_LISTIMG_ZJ5);
	int nBagType = s_CUI_ID_FRAME_PACK.GetBagType(dynamic_cast<ControlListImage*>(pSender));
	OnGemDragOn(4,m_pID_LISTIMG_ZJ5,pItemDrag,pSender,nBagType);
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ5OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ5OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ZhuJianUp::ID_LISTIMG_ZJ5OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	ClearGem(4,m_pID_LISTIMG_ZJ5);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_ZhuJianUp::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\zhujiangUp.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\zhujiangUp.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ZhuJianUp::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ZhuJianUp, s_CUI_ID_FRAME_ZhuJianUpOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ZhuJianUp, s_CUI_ID_FRAME_ZhuJianUpOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_ZhuJianUp, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_ZhuJianUpID_BUTTON_CLOSEOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ6OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ6OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ6OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ6OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_MaterialOnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_MaterialOnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_MaterialOnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_Material, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_MaterialOnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_ZhuJianUp, ID_BUTTON_Cancel, s_CUI_ID_FRAME_ZhuJianUpID_BUTTON_CancelOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_ZhuJianUp, ID_BUTTON_Ok, s_CUI_ID_FRAME_ZhuJianUpID_BUTTON_OkOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ1OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ1OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ1OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ1OnIconRButtonUp );
theUiManager.OnButtonClick( ID_FRAME_ZhuJianUp, ID_BUTTON_HELP, s_CUI_ID_FRAME_ZhuJianUpID_BUTTON_HELPOnButtonClick );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ2OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ2OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ2OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ2OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ3OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ3OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ3OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ3OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ4OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ4OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ4OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ4OnIconRButtonUp );
theUiManager.OnIconDragOn( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ5OnIconDragOn );
theUiManager.OnIconLDBClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ5OnIconLDBClick );
theUiManager.OnIconButtonClick( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ5OnIconButtonClick );
theUiManager.OnIconRButtonUp( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5, s_CUI_ID_FRAME_ZhuJianUpID_LISTIMG_ZJ5OnIconRButtonUp );

	m_pID_FRAME_ZhuJianUp = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ZhuJianUp );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_BUTTON_CLOSE );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Money );
	m_pID_LISTIMG_ZJ6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ6 );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_Material );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_BUTTON_Ok );
	m_pID_LISTIMG_ZJ1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ1 );
	m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_BUTTON_HELP );
	m_pID_LISTIMG_ZJ2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ2 );
	m_pID_LISTIMG_ZJ3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ3 );
	m_pID_LISTIMG_ZJ4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ4 );
	m_pID_LISTIMG_ZJ5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_LISTIMG_ZJ5 );
	m_pID_TEXT_SuccessRatio = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_SuccessRatio );
	m_pID_TEXT_Success = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Success );
	m_pID_TEXT_Fail = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Fail );
	m_pID_TEXT_Tu1_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Tu1_Name );
	m_pID_TEXT_Tu2_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Tu2_Name );
	m_pID_TEXT_Tip = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_Tip );
	m_pID_TEXT_MaterialName = (ControlText*)theUiManager.FindControl( ID_FRAME_ZhuJianUp, ID_TEXT_MaterialName );

	assert( m_pID_FRAME_ZhuJianUp );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Money );
	assert( m_pID_LISTIMG_ZJ6 );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_LISTIMG_ZJ1 );
	assert( m_pID_BUTTON_HELP );
	assert( m_pID_LISTIMG_ZJ2 );
	assert( m_pID_LISTIMG_ZJ3 );
	assert( m_pID_LISTIMG_ZJ4 );
	assert( m_pID_LISTIMG_ZJ5 );
	assert( m_pID_TEXT_SuccessRatio );
	assert( m_pID_TEXT_Success );
	assert( m_pID_TEXT_Fail );
	assert( m_pID_TEXT_Tu1_Name );
	assert( m_pID_TEXT_Tu2_Name );
	assert( m_pID_TEXT_Tip );
	assert( m_pID_TEXT_MaterialName );

	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_FRAME_ZhuJianUp->SetOnVisibleChangedFun( OnVisibleChange );
	m_pID_LISTIMG_ZJ6->SetEnableDrag(false);
	m_pID_TEXT_Success->SetVisable(false);
	m_pID_TEXT_Fail->SetVisable(false);
	m_pID_TEXT_Tip->SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ZhuJianUp::_UnLoadUI()
{
	m_pID_FRAME_ZhuJianUp = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\zhujiangUp.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ZhuJianUp::_IsVisable()
{
	if (!m_pID_FRAME_ZhuJianUp)
		return false;
	return m_pID_FRAME_ZhuJianUp->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ZhuJianUp::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_ZhuJianUp)
		return;
	ClearGems();
	if (bVisable)
	{
		if (!s_CUI_ID_FRAME_PACK.IsVisable())
			s_CUI_ID_FRAME_PACK.SetVisable(true);

		ResetWindowPosition(m_pID_FRAME_ZhuJianUp, s_CUI_ID_FRAME_PACK.GetFrame());
	}
	m_pID_FRAME_ZhuJianUp->SetVisable( bVisable );
	m_status = EffectStatus_No;
}

bool CUI_ID_FRAME_ZhuJianUp::IsPackItemBeUsing( __int64 nGuid )
{
	if( !IsVisable() || nGuid <= 0 )
		return false;

	if(m_GemMaterial.n64Guid == nGuid)
		return true;

	for( int i = 0; i < nMaxZhuJiangNum; ++i )
	{
		if( m_Gems[i].n64Guid == nGuid )
		{
			return true;
		}
	}
	return false;
}

void CUI_ID_FRAME_ZhuJianUp::ClearGem(int nIndex,ControlListImage *pTargetImg)
{
	if(nIndex < 0 ||  nIndex >= nMaxZhuJiangNum)
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
	m_Gems[nIndex].ushItemId = 0;
	m_Gems[nIndex].unCount = 0;

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pTargetBag, nNum, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	m_EquipBagType = BT_NormalItemBag;
	m_EquipBagIndex = -1;
	
	ShowOutputImg();
	RefreshSuccessRatio();
	RefreshOkEnable();
}

void CUI_ID_FRAME_ZhuJianUp::RefreshOkEnable()
{
	if (!m_pID_FRAME_ZhuJianUp)
		return;
	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_TEXT_Money->SetText("");
	m_pID_TEXT_Tip->SetVisable(false);

	bool benable = true;
	/*int ncount = 1;

	for (int i = 0; i < nMaxZhuJiangNum - 1; i++)
	{
		if (m_Gems[i].ushItemId != 0 && m_Gems[i].ushItemId == m_Gems[i+1].ushItemId)
			ncount++;
		else
			benable = false;
	}

	if (ncount != nMaxZhuJiangNum)
		return;*/
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		benable = false;
	if (pImg && !pImg->IsNull())
	{
		if (pImg->m_pkIconInfo->Count() < nMaxZhuJiangNum)
		{
			m_pID_TEXT_Tip->SetVisable(true);
			benable = false;
		}
	}
	
	
	m_pID_BUTTON_Ok->SetEnable(benable);
	if (benable)
	{
		RefreshMoney();
		ShowOutputImg();
	}
}

void CUI_ID_FRAME_ZhuJianUp::ClearMaterial(ControlListImage *pTargetImg)
{
	if(pTargetImg)
		pTargetImg->Clear();

	int nIndex = m_GemMaterial.shIndex;
	m_GemMaterial.shBagType = BT_NormalItemBag;
	m_GemMaterial.shIndex = -1;
	m_GemMaterial.n64Guid = 0;
	m_GemMaterial.ushItemId = 0;
	m_GemMaterial.unCount = 0;

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, nIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	m_MaterialBagType = BT_MaterialBag;
	m_MaterialIndex = -1;

	m_pID_TEXT_MaterialName->SetText("");

	RefreshSuccessRatio();
}

void CUI_ID_FRAME_ZhuJianUp::ClearGems()
{
	if(!m_pID_FRAME_ZhuJianUp)
		return;

	ClearGem(0,m_pID_LISTIMG_ZJ1);
	ClearGem(1,m_pID_LISTIMG_ZJ2);
	ClearGem(2,m_pID_LISTIMG_ZJ3);
	ClearGem(3,m_pID_LISTIMG_ZJ4);
	ClearGem(4,m_pID_LISTIMG_ZJ5);
	m_pID_LISTIMG_ZJ6->Clear();

	ClearMaterial(m_pID_LISTIMG_Material);
	
	m_pID_TEXT_SuccessRatio->SetText("");
	m_pID_TEXT_Money->SetText("");
	m_lastpSender = NULL;
	m_lastpSender2 = NULL;
	m_pID_TEXT_Tu1_Name->SetText("");
	m_pID_TEXT_Tu2_Name->SetText("");
	m_pID_TEXT_Tip->SetVisable(false);
}

bool CUI_ID_FRAME_ZhuJianUp::OnGemDragOn(int nIndex,ControlListImage *pTargetImg,
				 ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType /*= BT_NormalItemBag*/)
{
	if(nIndex < 0 ||  nIndex >= nMaxZhuJiangNum || !pTargetImg || !pItemDrag)
		return false;
	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;
	if( !pItemCommon||pItemCommon->ucItemType != ItemDefine::ITEMTYPE_OTHER)
		return false;

	ItemDefine::SItemOther *pOhter = (ItemDefine::SItemOther *)pItemCommon;
	if (!pOhter||pOhter->otherType != ItemDefine::OtherType_ZhujiangIdentify)
		return false;
	// 包裹里
	if(!s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) && !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender))
		return false;

	//ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);

	if (!theItemComposeConfig.GetItemComposeData2(pItemDrag->m_pkIconInfo->Id()))
		return false;

	CItemBag2* pdrag_bag = NULL;
	switch (stEquipBagType)
	{
	case BT_NormalItemBag:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	case BT_MaterialBag:
		pdrag_bag = &thePlayerRole.m_bagMaterial;
		break;
	default:
		pdrag_bag = &thePlayerRole.m_bag;
		break;
	}

	/*int Index = -1;
	for (int i = 0; i < nMaxZhuJiangNum; ++i)
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

			m_Gems[i].ushItemId = pItemDrag->m_pkIconInfo->Id();
			m_Gems[i].unCount = pItemDrag->m_pkIconInfo->Count();
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

	m_Gems[nIndex].ushItemId = pItemDrag->m_pkIconInfo->Id();
	m_Gems[nIndex].unCount = pItemDrag->m_pkIconInfo->Count();

	m_EquipBagType = stEquipBagType;
	m_EquipBagIndex = m_Gems[nIndex].shIndex;

	//设置值
	/*int ncount = pItemDrag->m_pkIconInfo->Count();
	if (pImg && !pImg->IsNull())
		ncount += pImg->m_pkIconInfo->Count();*/
	pTargetImg->Clear();
	//ControlIconDrag::S_ListImg img;
	//img.SetData(pItemDrag->m_pkIconInfo->Id(), /*ncount*/pItemDrag->m_pkIconInfo->Count());
	//pTargetImg->SetItem(&img);
	pTargetImg->SetItem( pItemDrag, 0 );
	pTargetImg->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( pdrag_bag, m_Gems[nIndex].shIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	ShowItemName(m_pID_TEXT_Tu1_Name, pItemDrag);
	RefreshSuccessRatio();
	RefreshOkEnable();
	return true;
}

bool CUI_ID_FRAME_ZhuJianUp::OnGemMaterialDragOn(ControlListImage *pTargetImg,
						 ControlIconDrag::S_ListImg* pItemDrag,ControlObject* pSender,short stEquipBagType /*= BT_NormalItemBag*/)
{
	if(!pTargetImg || !pItemDrag || !pSender)
		return false;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return false;

	if (pItemCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
		return false;

	ItemDefine::SCreateMaterial* pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
	if(pMaterial->stMaterialType != ItemDefine::ematerial_zhujianguprune)
		return false;

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

	m_GemMaterial.ushItemId = pItemDrag->m_pkIconInfo->Id();
	m_GemMaterial.unCount = 1;

	m_MaterialBagType = stEquipBagType;
	m_MaterialIndex = m_GemMaterial.shIndex;

	//设置值
	pTargetImg->Clear();
	ControlIconDrag::S_ListImg img;
	img.SetData(pItemDrag->m_pkIconInfo->Id(), pItemDrag->m_pkIconInfo->Count());
	m_pID_LISTIMG_Material->SetItem(&img);

	CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bagMaterial, m_GemMaterial.shIndex, true );
	theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

	ShowMaterialName(pItemDrag);
	RefreshSuccessRatio();
	return true;
}

void CUI_ID_FRAME_ZhuJianUp::OnDragOn(ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc)
{
	if(!pSender || !pItemDrag)
		return;

	ItemDefine::SItemCommon* pItemCommon = ( ItemDefine::SItemCommon* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pItemCommon)
		return;
	ItemDefine::SItemOther *pOhter = (ItemDefine::SItemOther *)pItemCommon;
	
	if (pItemCommon->ucItemType == ItemDefine::ITEMTYPE_OTHER && pOhter->otherType == ItemDefine::OtherType_ZhujiangIdentify)
	{
		/*ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);
		int ncount = 0;
		uint16 itemid = 0;
		if (pImg && !pImg->IsNull())
		{
			ncount = pImg->m_pkIconInfo->Count();
			itemid = pImg->m_pkIconInfo->GetItemId();
		}
		if (ncount >= nMaxZhuJiangNum)
			return;
		if (itemid && itemid != pItemDrag->m_pkIconInfo->GetItemId())
			return;*/
		ID_LISTIMG_ZJ1OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);

		/*for (int i = 0; i < nMaxZhuJiangNum; ++i)
		{
			if(m_Gems[i].n64Guid == 0)
			{
				if(i == 0)
					ID_LISTIMG_ZJ1OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 1)
					ID_LISTIMG_ZJ2OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 2)
					ID_LISTIMG_ZJ3OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 3)
					ID_LISTIMG_ZJ4OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				else if(i == 4)
					ID_LISTIMG_ZJ5OnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
				break;
			}
		}*/
	}
	else if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_MATERIAL)
	{
		ItemDefine::SCreateMaterial *pMaterial = (ItemDefine::SCreateMaterial*)pItemCommon;
		if(pMaterial->stMaterialType != ItemDefine::ematerial_zhujianguprune)
			return;
		ID_LISTIMG_MaterialOnIconDragOn(pSender,pMe,pItemDrag,pItemSrc);
	}
}

void CUI_ID_FRAME_ZhuJianUp::SendZhuJiangUpMsg()
{
	int nCount = 0;
	MsgZhuJiangCompose msgCompose;
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		return;
	nCount = pImg->m_pkIconInfo->Count();

	for (int i = 0; i < nMaxZhuJiangNum; ++i)
	{
		if(m_Gems[i].n64Guid != 0)
		{
			msgCompose.materials[i].nItemBagType = m_Gems[i].shBagType;
			msgCompose.materials[i].nItemIndex   = m_Gems[i].shIndex;
			msgCompose.materials[i].nItemGuid    = m_Gems[i].n64Guid;
			msgCompose.materials[i].nItemId      = m_Gems[i].ushItemId;
			msgCompose.materials[i].nItemCount	 = m_Gems[i].unCount;
			//++nCount;
		}
	}
	if(nCount < nMaxZhuJiangNum)
		return;
	msgCompose.composeRune.nItemBagType = m_GemMaterial.shBagType;
	msgCompose.composeRune.nItemIndex   = m_GemMaterial.shIndex;
	msgCompose.composeRune.nItemGuid    = m_GemMaterial.n64Guid;
	msgCompose.composeRune.nItemId      = m_GemMaterial.ushItemId;
	msgCompose.composeRune.nItemCount	= m_GemMaterial.unCount;

	GettheNetworkInput().SendMsg( &msgCompose );
}

void CUI_ID_FRAME_ZhuJianUp::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_ZhuJianUp.ClearGems();
	s_CUI_ID_FRAME_ZhuJianUp.RefreshOkEnable();
}

void CUI_ID_FRAME_ZhuJianUp::RefreshMoney()
{
	if (!m_pID_TEXT_Money)
		return;

	m_pID_TEXT_Money->SetText("");
	const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2(m_Gems[0].ushItemId);
	if (!pData)
		return;
	int nMoney = pData->GetCostMoney();
	
	std::string text = "";
	thePlayerRole.GetGSCStringFromJiaoZi(nMoney, text);
	DWORD dwColor = 0xffffffff;
	if(!thePlayerRole.HaveEnoughMoney(nMoney))
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_StarLEvolveNoMomeny), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, true);
		dwColor = 0xffff0000;
		m_pID_BUTTON_Ok->SetEnable(false);
	}

	m_pID_TEXT_Money->SetText(text,dwColor);	
}

void CUI_ID_FRAME_ZhuJianUp::RefreshSuccessRatio()
{
	if (!m_pID_TEXT_SuccessRatio)
		return;
	m_pID_TEXT_SuccessRatio->SetText("");

	bool benable = true;
	/*int ncount = 1;

	for (int i = 0; i < nMaxZhuJiangNum - 1; i++)
	{
		if (m_Gems[i].ushItemId != 0 && m_Gems[i].ushItemId == m_Gems[i+1].ushItemId)
			ncount++;
		else
			benable = false;
	}

	if (ncount != nMaxZhuJiangNum)
		return;*/
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		benable = false;
	if (pImg && !pImg->IsNull())
	{
		if (pImg->m_pkIconInfo->Count() < nMaxZhuJiangNum)
			benable = false;
	}

	if (!benable)
		return;

	const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2(m_Gems[0].ushItemId);
	if (!pData)
		return;
	int prob = pData->GetProbility();

	ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(m_GemMaterial.ushItemId);
	if (pMaterial)
		prob += pMaterial->fAddIntensifyRate[0];
	if (prob > 100)
		prob = 100;

	char tmpStr[32] = {};
	MeSprintf( tmpStr, sizeof(tmpStr)/sizeof(char) - 1, "%d%%", prob );
	m_pID_TEXT_SuccessRatio->SetText(tmpStr);
}

void CUI_ID_FRAME_ZhuJianUp::ShowOutputImg()
{
	if (!m_pID_LISTIMG_ZJ6)
		return;
	m_pID_LISTIMG_ZJ6->Clear();

	bool benable = true;
	//int ncount = 1;

	/*for (int i = 0; i < nMaxZhuJiangNum - 1; i++)
	{
		if (m_Gems[i].ushItemId != 0 && m_Gems[i].ushItemId == m_Gems[i+1].ushItemId)
			ncount++;
		else
			benable = false;
	}

	if (ncount != nMaxZhuJiangNum)
		return;*/
	ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_ZJ1->GetItemByIndex(0);
	if (!pImg || pImg->IsNull())
		benable = false;
	if (pImg && !pImg->IsNull())
	{
		if (pImg->m_pkIconInfo->Count() < nMaxZhuJiangNum)
			benable = false;
	}

	if (!benable)
		return;

	const ComposeData2* pData = theItemComposeConfig.GetItemComposeData2(m_Gems[0].ushItemId);
	if (!pData)
		return;
	unsigned short newImageID = pData->GetNewItemID();

	ControlIconDrag::S_ListImg ImgItem;
	ImgItem.SetData(newImageID,1);
	m_pID_LISTIMG_ZJ6->SetItem( &ImgItem , 0);

	ShowItemName(m_pID_TEXT_Tu2_Name, &ImgItem);
}

void CUI_ID_FRAME_ZhuJianUp::UpdateAll()
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

		ID_LISTIMG_ZJ1OnIconDragOn(m_lastpSender, NULL, pItemImg, 0);
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

void CUI_ID_FRAME_ZhuJianUp::ShowItemName(ControlText* pText, ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pText || !pItemDrag)
		return;
	pText->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	char temp[128] = {0};
	sprintf(temp, "%s", pItemCommon->GetItemName());

	pText->SetText(temp, S_IconInfoHero::GetQualityColor( pItemCommon ->ustLevel ) );
}

void CUI_ID_FRAME_ZhuJianUp::ShowMaterialName(ControlIconDrag::S_ListImg* pItemDrag)
{
	if (!pItemDrag || !m_pID_TEXT_MaterialName)
		return;
	m_pID_TEXT_MaterialName->SetText("");

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->GetItemId() );
	if (!pItemCommon)
		return;

	ItemDefine::SCreateMaterial* pMaterial = ( ItemDefine::SCreateMaterial* )GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
	if (!pMaterial)
		return;
	int	prob = pMaterial->fAddIntensifyRate[0];

	char temp[128] = {0};
	sprintf(temp, theXmlString.GetString(eText_ZhuJianUp_Material), pItemCommon->GetItemName(), prob);

	m_pID_TEXT_MaterialName->SetText(temp);
}