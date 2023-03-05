/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\商城UI\ShopCenter.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ShopCenter.h"
#include "MeTerrain/stdafx.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/SwGlobal.h"
#include "wsRender.h"
#include "GameMain.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "TradeCenterConfig.h"
#include "TradeCenterInfo.h"
#include "BatchShop.h"
#include "Pack.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "MeFont/MeFont.h"
#include "ShopChangePoint.h"
#include "Cfg.h"
#include "color_config.h"
#include "ChatInfoBox.h"
#include "wsCamera.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "MapConfig.h"
#include "NpcInfo.h"
#include "Common.h"
#include "WealthProtect.h"
#include "PreventWallow.h"
#include "MeFont/MeFontSystem.h"
#include "Ui/InfoList.h"
#include "SystemConfig.h"
#include "MiniMapUI.h"

extern DWORD g_dwLastFrameCostTime;
extern DWORD g_dwLastFrameBeginTime;

static std::string s_strNewType = theXmlString.GetString(eText_ShopCenter_New);//"新品";
static std::string s_strHotType = theXmlString.GetString(eText_ShopCenter_Hot);//"热卖";

bool FindPathCallback( const char bPressYesButton, void *pData )
{
    guardfunc;
    if( pData &&bPressYesButton)
    {
		CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(s_CUI_ID_FRAME_ShopCenter.GetControlRadioGroup().GetSelectRadio()->GetData()->m_szCaption);
		if (!pTypeTrades)
			return true;

        unsigned int *ustItemID = (unsigned int*)pData;
        CTradeCenterInfo::cTradeItem* pItem = s_CUI_ID_FRAME_ShopCenter.FindItem(*ustItemID,pTypeTrades->chType);
        if(!pItem)
            return true;

        const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(pItem->m_nNpcId,pItem->m_nMapId);
        if(!pInfo)
            return true;

        if (!pInfo->_bPFPossible)
            return true;

        if(!theHeroGame.GetPlayerMgr())
            return true;

        theHeroGame.GetPlayerMgr()->MoveRoleToNPC(pInfo);        
    }

    return true;
    unguard;
}

CUI_ID_FRAME_ShopCenter s_CUI_ID_FRAME_ShopCenter;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ShopCenter, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ShopCenter, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_HelpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_ResetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_RightOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_LeftOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_PayOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_LastPageOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_FirstPageOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_PageDownOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_PageUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_ChangeOnButtonClick )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_TypeOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_LISTIMG_ItemOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_LISTIMG_ItemOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_LISTIMG_ItemOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_LISTIMG_ItemOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_FitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_BUTTON_BuyOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType7OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType8OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType9OnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_ShopCenter, ID_CHECKBOX_SubType10OnCheckBoxCheck )
CUI_ID_FRAME_ShopCenter::CUI_ID_FRAME_ShopCenter()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_ShopCenter::ResetMembers()
{
	m_pID_TEXT_IntegralShow = NULL;
	m_pID_FRAME_ShopCenter = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_PICTURE_TitleDi = NULL;
	m_pID_PICTURE_TitleWord = NULL;
	m_pID_PICTURE_TitleLeftMiddle = NULL;
	m_pID_PICTURE_TitleRightMiddle = NULL;
	m_pID_PICTURE_TitleLeft = NULL;
	m_pID_PICTURE_TitleRight = NULL;
	//m_pID_PICTURE_AllItemWall = NULL;
	m_pID_BUTTON_Close = NULL;
	m_pID_BUTTON_Help = NULL;
// 	m_pID_PICTURE_GoldWall = NULL;
// 	m_pID_PICTURE_GoldWall1 = NULL;
	m_pID_TEXT_Jinyuanbao = NULL;
	m_pID_PICTURE_Yingyuanbao = NULL;
	m_pID_PICTURE_money = NULL;
	m_pID_TEXT_Yingyuanbao = NULL;
	m_pID_TEXT_Yuanbao = NULL;
	m_pID_TEXT_Yuanbao22 = NULL;
 	m_pID_PICTURE_InfoWall = NULL;
// 	m_pID_TEXT_ShopInfo = NULL;
	m_pID_CHECKBOX_Type1 = NULL;
	m_pID_CHECKBOX_Type2 = NULL;
	m_pID_CHECKBOX_Type3 = NULL;
	m_pID_CHECKBOX_Type4 = NULL;
	m_pID_CHECKBOX_Type5 = NULL;
	m_pID_CHECKBOX_Type6 = NULL;
	m_pID_CHECKBOX_Type7 = NULL;
	m_pID_CHECKBOX_Type8 = NULL;
	m_pID_PICTURE_ModelWall = NULL;
	m_pID_BUTTON_Reset = NULL;
	m_pID_BUTTON_Right = NULL;
	m_pID_BUTTON_Left = NULL;
	m_pID_BUTTON_Pay = NULL;
	m_pID_PICTURE_ItemWall1 = NULL;
	m_pID_PICTURE_ItemWall2 = NULL;
	m_pID_PICTURE_ItemWall3 = NULL;
	m_pID_PICTURE_ItemWall4 = NULL;
	m_pID_PICTURE_ItemWall5 = NULL;
	m_pID_PICTURE_ItemWall6 = NULL;
	m_pID_PICTURE_ItemWall7 = NULL;
	m_pID_PICTURE_ItemWall8 = NULL;
	m_pID_PICTURE_ItemWall9 = NULL;
	m_pID_PICTURE_ItemWall10 = NULL;
	m_pID_PICTURE_ItemWall11 = NULL;
	m_pID_PICTURE_ItemWall12 = NULL;
	m_pID_PICTURE_ItemWall13 = NULL;
	m_pID_PICTURE_ItemWall14 = NULL;
	m_pID_PICTURE_ItemWall15 = NULL;
	m_pID_BUTTON_LastPage = NULL;
	m_pID_BUTTON_FirstPage = NULL;
	m_pID_BUTTON_PageDown = NULL;
	m_pID_BUTTON_PageUp = NULL;
	m_pID_TEXT_Page = NULL;
	m_pID_LISTIMG_Item1 = NULL;
	m_pID_LISTIMG_Item2 = NULL;
	m_pID_LISTIMG_Item3 = NULL;
	m_pID_LISTIMG_Item4 = NULL;
	m_pID_LISTIMG_Item5 = NULL;
	m_pID_LISTIMG_Item6 = NULL;
	m_pID_LISTIMG_Item7 = NULL;
	m_pID_LISTIMG_Item8 = NULL;
	m_pID_LISTIMG_Item9 = NULL;
	m_pID_LISTIMG_Item10 = NULL;
	m_pID_LISTIMG_Item11 = NULL;
	m_pID_LISTIMG_Item12 = NULL;
	m_pID_LISTIMG_Item13 = NULL;
	m_pID_LISTIMG_Item14 = NULL;
	m_pID_LISTIMG_Item15 = NULL;
	m_pID_TEXT_Item1 = NULL;
	m_pID_TEXT_Item2 = NULL;
	m_pID_TEXT_Item3 = NULL;
	m_pID_TEXT_Item4 = NULL;
	m_pID_TEXT_Item5 = NULL;
	m_pID_TEXT_Item6 = NULL;
	m_pID_TEXT_Item7 = NULL;
	m_pID_TEXT_Item8 = NULL;
	m_pID_TEXT_Item9 = NULL;
	m_pID_TEXT_Item10 = NULL;
	m_pID_TEXT_Item11 = NULL;
	m_pID_TEXT_Item12 = NULL;
	m_pID_TEXT_Item13 = NULL;
	m_pID_TEXT_Item14 = NULL;
	m_pID_TEXT_Item15 = NULL;
	m_pID_TEXT_ItemPrice1 = NULL;
	m_pID_TEXT_ItemPrice2 = NULL;
	m_pID_TEXT_ItemPrice3 = NULL;
	m_pID_TEXT_ItemPrice4 = NULL;
	m_pID_TEXT_ItemPrice5 = NULL;
	m_pID_TEXT_ItemPrice6 = NULL;
	m_pID_TEXT_ItemPrice7 = NULL;
	m_pID_TEXT_ItemPrice8 = NULL;
	m_pID_TEXT_ItemPrice9 = NULL;
	m_pID_TEXT_ItemPrice10 = NULL;
	m_pID_TEXT_ItemPrice11 = NULL;
	m_pID_TEXT_ItemPrice12 = NULL;
	m_pID_TEXT_ItemPrice13 = NULL;
	m_pID_TEXT_ItemPrice14 = NULL;
	m_pID_TEXT_ItemPrice15 = NULL;
	m_pID_TEXT_Hot1 = NULL;
	m_pID_TEXT_Hot2 = NULL;
	m_pID_TEXT_Hot3 = NULL;
	m_pID_TEXT_Hot4 = NULL;
	m_pID_TEXT_Hot5 = NULL;
	m_pID_TEXT_Hot6 = NULL;
	m_pID_TEXT_Hot7 = NULL;
	m_pID_TEXT_Hot8 = NULL;
	m_pID_TEXT_Hot9 = NULL;
	m_pID_TEXT_Hot10 = NULL;
	m_pID_TEXT_Hot11 = NULL;
	m_pID_TEXT_Hot12 = NULL;
	m_pID_TEXT_Hot13 = NULL;
	m_pID_TEXT_Hot14 = NULL;
	m_pID_TEXT_Hot15 = NULL;
	m_pID_TEXT_Wait = NULL;
    m_pID_CHECKBOX_SubType1 = NULL;
    m_pID_CHECKBOX_SubType2 = NULL;
    m_pID_CHECKBOX_SubType3 = NULL;
    m_pID_CHECKBOX_SubType4 = NULL;
    m_pID_CHECKBOX_SubType5 = NULL;
    m_pID_CHECKBOX_SubType6 = NULL;
    m_pID_CHECKBOX_SubType7 = NULL;
    m_pID_CHECKBOX_SubType8 = NULL;
	m_nCurrPreviewMountID = INVALID_VALUE;
//     m_pID_CHECKBOX_SubType9 = NULL;
//     m_pID_CHECKBOX_SubType10 = NULL;
}
// Frame
bool CUI_ID_FRAME_ShopCenter::OnFrameRun()
{
	if (m_bRotate && m_pID_BUTTON_Right->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		RenderAnim_RotateZ(true);
	}
	else if (m_bRotate && m_pID_BUTTON_Left->PtInObject(theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y))
	{
		RenderAnim_RotateZ(false);
	}
	else
		m_bRotate = false;

	// broadcast
	RECT picRC;
	m_pID_PICTURE_InfoWall->GetRealRect( &picRC );

	if (m_currMoveText.m_nCount > 0)
	{
		RECT rc;
		DWORD dwCurrTime = HQ_TimeGetTime();
		int nUseTime = dwCurrTime - m_currMoveText.m_dwStartTime;
		int nMove = nUseTime*m_currMoveText.m_fMoveSpeed;
		m_currMoveText.m_nX = picRC.right - nMove;

		rc.left = m_currMoveText.m_nX;
		rc.right = rc.left + (m_currMoveText.m_strText.size() + 2) * m_pID_FRAME_ShopCenter->GetFontSize();
		rc.top = picRC.top;
		rc.bottom = rc.top + m_pID_PICTURE_InfoWall->GetHeight();

		if (m_currMoveText.m_nX - picRC.left < -m_currMoveText.m_fWidth)
		{
			m_currMoveText.m_dwStartTime = dwCurrTime;
			m_currMoveText.m_nCount--;
		}
	}
	else
	{
		if ( m_broadcasts.size() > 0 )
		{
			m_currMoveText.m_strText = m_broadcasts[rand() % m_broadcasts.size()];
			m_currMoveText.m_nCount = 1;
			m_currMoveText.m_fWidth = (float)m_currMoveText.m_strText.length() * (float)m_pID_FRAME_ShopCenter->GetFontSize() / 2.f;
			m_currMoveText.m_nX = picRC.right;
			m_currMoveText.m_nY = 200;
			m_currMoveText.m_dwColor = m_pID_FRAME_ShopCenter->GetFontColor();
			m_currMoveText.m_fMoveSpeed = 0.05f;
		}
		m_currMoveText.m_dwStartTime = HQ_TimeGetTime();
	}

	if(IsVisable())
	{
		if( m_pID_TEXT_Wait )
		{
			if(m_bUpdateFlag)
			{
				m_pID_TEXT_Wait->SetVisable(false);
			}
			else
			{
				m_pID_TEXT_Wait->SetVisable(true);
			}
		}
	}

	return true;
}
bool CUI_ID_FRAME_ShopCenter::OnFrameRender()
{
	RECT rc;
	m_pID_PICTURE_ModelWall->GetRealRect(&rc);

	CViewportConfig *viewportCfg = GetSystemConfig()->GetTargetPackViewportCfg();
	RenderAnim_Update(rc.left, rc.top,
		(rc.right - rc.left) * ControlObject::GetSCALE(m_pID_FRAME_ShopCenter),
		(rc.bottom - rc.top) * ControlObject::GetSCALE(m_pID_FRAME_ShopCenter), D3DXVECTOR3(0, -12, 0));

	float scale = 0.0;
	if (theHeroGame.GetPlayerMgr()->GetMe()->GetSex() == Sex_Male)
		scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleMale;
	else
		scale = Config::m_fMdlSpaceScale * viewportCfg->m_fRoleScaleFemale;
	if (m_nCurrPreviewMountID!=INVALID_VALUE)
	{
		scale = scale*0.5;
	}
	if(RenderAnim_GetPlayer() 
		&& RenderAnim_GetPlayer()->GetAnim()
		&& RenderAnim_GetPlayer()->GetAnim()->GetAvatar() 
		&& RenderAnim_GetPlayer()->GetAnim()->GetAvatar()->GetComponent(eKeyAll_LHandItem))
	{
			RenderAnim_GetPlayer()->GetAnim()->GetAvatar()->GetComponent(eKeyAll_LHandItem)->SetCanSee(false);
	}
	RenderAnim(D3DXVECTOR3(0, -1.2, -2.5136), scale);

	// broadcast
	GetEngine()->GetRenderer()->EndScene();
	RenderBroadcast();
	GetEngine()->GetRenderer()->BeginScene();
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_HelpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	m_nCurrPreviewMountID = INVALID_VALUE;
	UpdatePlayerAnimCtrl();
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_RightOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_LeftOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	m_bRotate = false;
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_PayOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	ShellExecute( NULL, "open", gCfg.m_strPayWebAddress.c_str(), NULL, NULL, 0 );
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_ChangeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	NpcCoord::getInstance()->clickHyberToMiniMap(theXmlString.GetString(e_ChangeNpcName)/*"元宗"*/);
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_LastPageOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	m_nCurrPageIndex = m_nPageCount - 1;
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_FirstPageOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	m_nCurrPageIndex = 0;
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	++m_nCurrPageIndex;
	if (m_nCurrPageIndex > m_nPageCount - 1)
		m_nCurrPageIndex = m_nPageCount - 1;
	Refresh();
	return true;
}
// Button
bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	--m_nCurrPageIndex;
	if (m_nCurrPageIndex < 0)
		m_nCurrPageIndex = 0;
	Refresh();
	return true;
}

// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_TypeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
	if (pSender != m_tabs.GetSelectRadio())
    {
		m_nCurrPageIndex = 0;
        /*m_SubTabs.ToggleRadio(m_pID_CHECKBOX_SubType1);*/ //lyh--
		m_SubTabs.ToggleRadio(m_pID_CHECKBOX_SubType2);//lyh++
    }
	m_tabs.ToggleRadio(static_cast<ControlCheckBox*>(pSender));
	Refresh();
}
// ListImg / ListEx
bool CUI_ID_FRAME_ShopCenter::ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	return false;
}
bool CUI_ID_FRAME_ShopCenter::ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	return false;
}
bool CUI_ID_FRAME_ShopCenter::ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_ShopCenter::ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	if (!pItem)
		return false;
	return Buy(pItem->m_pkIconInfo->Id());
}

bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_FitOnButtonClick( ControlObject* pSender )
{
	if (m_pID_FRAME_ShopCenter == NULL)
		return false;
	for (int i = 0; i < m_itemFitBtns.size(); ++i)
	{
		if (pSender == m_itemFitBtns[i])
		{
			ControlIconDrag::S_ListImg *imgItem = m_itemImages[i]->GetItemByIndex(0);

			ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( imgItem->m_pkIconInfo->Id() );
			if (pItemDetail == NULL)
			{
				m_nCurrPreviewMountID = INVALID_VALUE;
				return false;
			}

			if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER)
			{
				ItemDefine::SItemOther* pOther = static_cast<ItemDefine::SItemOther*>(pItemDetail);
				if (pOther && pOther->otherType == ItemDefine::OtherType_Mount)
				{
					m_nCurrPreviewMountID = pOther->ustItemID;
					int nModelId = GetMexResMgr()->AddExternalFile( GettheItemDetail().GetDromeByID( pOther->ustItemID )->GetModelPath() );
					RenderAnim_SetModelID(nModelId);
				}
			}
			else
			{
				m_nCurrPreviewMountID = INVALID_VALUE;
				if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
				{
					ItemDefine::SItemArmour *pCanEquip = (ItemDefine::SItemArmour *) pItemDetail;

					CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
					if (me != NULL && me->GetSex() == pCanEquip->cEquipSexReq)
						UpdatePlayerAnimCtrl(imgItem->m_pkIconInfo->Id(), pCanEquip->ustModelID[me->GetProfession()][me->GetSex()][0]);
				}
			}
		}
	}
	return true;
}

bool CUI_ID_FRAME_ShopCenter::ID_BUTTON_BuyOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	for (int i = 0; i < m_itemBuyBtns.size(); ++i)
	{
		if (pSender == m_itemBuyBtns[i])
		{
			ID_LISTIMG_ItemOnIconRButtonUp(m_itemImages[i], m_itemImages[i]->GetItemByIndex(0));
		}
	}
	
	
	return true;
}

// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}

// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
   SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{    
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType8OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    SetSubTypeBoxCheck(pSender,pbChecked);
}
// CheckBox
// void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType9OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if( !m_pID_FRAME_ShopCenter )
// 		return;
//     SetSubTypeBoxCheck(pSender,pbChecked);
// }
// // CheckBox
// void CUI_ID_FRAME_ShopCenter::ID_CHECKBOX_SubType10OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if( !m_pID_FRAME_ShopCenter )
// 		return;
//     SetSubTypeBoxCheck(pSender,pbChecked);
// }
// 装载UI
bool CUI_ID_FRAME_ShopCenter::_LoadUI()
{

	s_CUI_ID_FRAME_ShopChangePoint.LoadUI();

	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ShopCenter.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ShopCenter.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ShopCenter::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ShopCenter, s_CUI_ID_FRAME_ShopCenterOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ShopCenter, s_CUI_ID_FRAME_ShopCenterOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Close, s_CUI_ID_FRAME_ShopCenterID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Help, s_CUI_ID_FRAME_ShopCenterID_BUTTON_HelpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Reset, s_CUI_ID_FRAME_ShopCenterID_BUTTON_ResetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Right, s_CUI_ID_FRAME_ShopCenterID_BUTTON_RightOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Left, s_CUI_ID_FRAME_ShopCenterID_BUTTON_LeftOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Pay, s_CUI_ID_FRAME_ShopCenterID_BUTTON_PayOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_LastPage, s_CUI_ID_FRAME_ShopCenterID_BUTTON_LastPageOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_FirstPage, s_CUI_ID_FRAME_ShopCenterID_BUTTON_FirstPageOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_PageDown, s_CUI_ID_FRAME_ShopCenterID_BUTTON_PageDownOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_PageUp, s_CUI_ID_FRAME_ShopCenterID_BUTTON_PageUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ShopCenter, ID_BUTTON_Change, s_CUI_ID_FRAME_ShopCenterID_BUTTON_ChangeOnButtonClick );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType1, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType1OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType2, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType2OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType3, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType3OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType4, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType4OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType5, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType5OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType6, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType6OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType7, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType7OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType8, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType8OnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType9, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType9OnCheckBoxCheck );
//     theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType10, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_SubType10OnCheckBoxCheck );

	m_pID_FRAME_ShopCenter = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ShopCenter );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_Wall1 );
	m_pID_PICTURE_TitleDi = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleDi );
	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleWord );
	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleLeftMiddle );
	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleRightMiddle );
	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleLeft );
	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_TitleRight );
	//m_pID_PICTURE_AllItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_AllItemWall );
	m_pID_BUTTON_Close = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Close );
	m_pID_BUTTON_Help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Help );
	//m_pID_PICTURE_GoldWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_GoldWall );
	//m_pID_PICTURE_GoldWall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_GoldWall1 );
	m_pID_TEXT_Jinyuanbao = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Jinyuanbao );
	m_pID_PICTURE_Yingyuanbao = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_Yingyuanbao );
	m_pID_PICTURE_money = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_money );
	m_pID_TEXT_Yingyuanbao = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Yingyuanbao );
	m_pID_TEXT_Yuanbao = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Yuanbao );
	m_pID_TEXT_Yuanbao22 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Yuanbao22 );
	m_pID_PICTURE_InfoWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_InfoWall );
	//m_pID_TEXT_ShopInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ShopInfo );
	m_pID_CHECKBOX_Type1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type1 );
	m_pID_CHECKBOX_Type2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type2 );
	m_pID_CHECKBOX_Type3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type3 );
	m_pID_CHECKBOX_Type4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type4 );
	m_pID_CHECKBOX_Type5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type5 );
	m_pID_CHECKBOX_Type6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type6 );
	m_pID_CHECKBOX_Type7 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type7 );
	m_pID_CHECKBOX_Type8 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_Type8 );
	m_pID_PICTURE_ModelWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ModelWall );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Reset );
	m_pID_BUTTON_Right = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Right );
	m_pID_BUTTON_Left = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Left );
	m_pID_BUTTON_Pay = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Pay );
	m_pID_PICTURE_ItemWall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall1 );
	m_pID_PICTURE_ItemWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall2 );
	m_pID_PICTURE_ItemWall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall3 );
	m_pID_PICTURE_ItemWall4 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall4 );
	m_pID_PICTURE_ItemWall5 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall5 );
	m_pID_PICTURE_ItemWall6 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall6 );
	m_pID_PICTURE_ItemWall7 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall7 );
	m_pID_PICTURE_ItemWall8 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall8 );
	m_pID_PICTURE_ItemWall9 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall9 );
	m_pID_PICTURE_ItemWall10 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall10 );
	m_pID_PICTURE_ItemWall11 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall11 );
	m_pID_PICTURE_ItemWall12 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall12 );
	m_pID_PICTURE_ItemWall13 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall13 );
	m_pID_PICTURE_ItemWall14 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall14 );
	m_pID_PICTURE_ItemWall15 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_PICTURE_ItemWall15 );
	m_pID_BUTTON_LastPage = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_LastPage );
	m_pID_BUTTON_FirstPage = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_FirstPage );
	m_pID_BUTTON_PageDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_PageDown );
	m_pID_BUTTON_PageUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_PageUp );
	m_pID_TEXT_Page = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Page );
	m_pID_LISTIMG_Item1 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item1 );
	m_pID_LISTIMG_Item2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item2 );
	m_pID_LISTIMG_Item3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item3 );
	m_pID_LISTIMG_Item4 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item4 );
	m_pID_LISTIMG_Item5 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item5 );
	m_pID_LISTIMG_Item6 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item6 );
	m_pID_LISTIMG_Item7 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item7 );
	m_pID_LISTIMG_Item8 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item8 );
	m_pID_LISTIMG_Item9 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item9 );
	m_pID_LISTIMG_Item10 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item10 );
	m_pID_LISTIMG_Item11 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item11 );
	m_pID_LISTIMG_Item12 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item12 );
	m_pID_LISTIMG_Item13 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item13 );
	m_pID_LISTIMG_Item14 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item14 );
	m_pID_LISTIMG_Item15 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_LISTIMG_Item15 );
	m_pID_TEXT_Item1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item1 );
	m_pID_TEXT_Item2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item2 );
	m_pID_TEXT_Item3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item3 );
	m_pID_TEXT_Item4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item4 );
	m_pID_TEXT_Item5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item5 );
	m_pID_TEXT_Item6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item6 );
	m_pID_TEXT_Item7 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item7 );
	m_pID_TEXT_Item8 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item8 );
	m_pID_TEXT_Item9 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item9 );
	m_pID_TEXT_Item10 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item10 );
	m_pID_TEXT_Item11 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item11 );
	m_pID_TEXT_Item12 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item12 );
	m_pID_TEXT_Item13 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item13 );
	m_pID_TEXT_Item14 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item14 );
	m_pID_TEXT_Item15 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Item15 );
	m_pID_TEXT_ItemPrice1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice1 );
	m_pID_TEXT_ItemPrice2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice2 );
	m_pID_TEXT_ItemPrice3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice3 );
	m_pID_TEXT_ItemPrice4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice4 );
	m_pID_TEXT_ItemPrice5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice5 );
	m_pID_TEXT_ItemPrice6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice6 );
	m_pID_TEXT_ItemPrice7 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice7 );
	m_pID_TEXT_ItemPrice8 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice8 );
	m_pID_TEXT_ItemPrice9 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice9 );
	m_pID_TEXT_ItemPrice10 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice10 );
	m_pID_TEXT_ItemPrice11 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice11 );
	m_pID_TEXT_ItemPrice12 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice12 );
	m_pID_TEXT_ItemPrice13 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice13 );
	m_pID_TEXT_ItemPrice14 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice14 );
	m_pID_TEXT_ItemPrice15 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_ItemPrice15 );
	m_pID_TEXT_Hot1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot1 );
	m_pID_TEXT_Hot2 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot2 );
	m_pID_TEXT_Hot3 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot3 );
	m_pID_TEXT_Hot4 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot4 );
	m_pID_TEXT_Hot5 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot5 );
	m_pID_TEXT_Hot6 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot6 );
	m_pID_TEXT_Hot7 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot7 );
	m_pID_TEXT_Hot8 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot8 );
	m_pID_TEXT_Hot9 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot9 );
	m_pID_TEXT_Hot10 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot10 );
	m_pID_TEXT_Hot11 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot11 );
	m_pID_TEXT_Hot12 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot12 );
	m_pID_TEXT_Hot13 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot13 );
	m_pID_TEXT_Hot14 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot14 );
	m_pID_TEXT_Hot15 = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Hot15 );
	m_pID_TEXT_Wait = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_Wait );

    m_pID_CHECKBOX_SubType1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType1 );
    m_pID_CHECKBOX_SubType2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType2 );
    m_pID_CHECKBOX_SubType3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType3 );
    m_pID_CHECKBOX_SubType4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType4 );
    m_pID_CHECKBOX_SubType5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType5 );
    m_pID_CHECKBOX_SubType6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType6 );
    m_pID_CHECKBOX_SubType7 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType7 );
    m_pID_CHECKBOX_SubType8 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType8 );

	m_pID_TEXT_IntegralShow = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_TEXT_IntegralShow );
	assert( m_pID_TEXT_IntegralShow );
//     m_pID_CHECKBOX_SubType9 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType9 );
//     m_pID_CHECKBOX_SubType10 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, ID_CHECKBOX_SubType10 );
	assert( m_pID_FRAME_ShopCenter );
    assert( m_pID_CHECKBOX_SubType1 );
    assert( m_pID_CHECKBOX_SubType2 );
    assert( m_pID_CHECKBOX_SubType3 );
    assert( m_pID_CHECKBOX_SubType4 );
    assert( m_pID_CHECKBOX_SubType5 );
    assert( m_pID_CHECKBOX_SubType6 );
    assert( m_pID_CHECKBOX_SubType7 );
    assert( m_pID_CHECKBOX_SubType8 );
//     assert( m_pID_CHECKBOX_SubType9 );
//     assert( m_pID_CHECKBOX_SubType10 );

	//====================================================================================================================
	//lyh 小标题 并设置 subType1 为选中
    m_SubTabs.Clear();
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType1);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType2);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType3);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType4);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType5);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType6);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType7);
    m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType8);
//     m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType9);
//     m_SubTabs.AddRadio(m_pID_CHECKBOX_SubType10);
   /* m_SubTabs.ToggleRadio(m_pID_CHECKBOX_SubType1);*/
	//选中第一个子项改为选中第二个 lyh++
	 m_SubTabs.ToggleRadio(m_pID_CHECKBOX_SubType2);
	//====================================================================================================================

	m_pID_TEXT_Wait->SetText(theXmlString.GetString(eText_WaitingServerUpdate));

	m_pID_BUTTON_Right->SetLButtonDownFun(UI_RightLBD);
	m_pID_BUTTON_Left->SetLButtonDownFun(UI_LeftLBD);

	ControlButton* pButtonChange = static_cast<ControlButton*>(theUiManager.FindControl( ID_FRAME_ShopCenter, ID_BUTTON_Change ) );
	pButtonChange->SetShowTip(true);
	pButtonChange->setTip(pButtonChange->GetData()->m_szCaption);

//===============================================================================================
	//lyh 商品列表
	char buf[64];
	int index = 1;
	sprintf(buf, "ID_LISTIMG_Item%d", index);
	ControlListImage* pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
	while (pListImg)
	{
		pListImg->ShowPressEffect(true);

		theUiManager.OnIconDragOn( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_LISTIMG_ItemOnIconDragOn );
		theUiManager.OnIconLDBClick( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_LISTIMG_ItemOnIconLDBClick );
		theUiManager.OnIconButtonClick( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_LISTIMG_ItemOnIconButtonClick );
		theUiManager.OnIconRButtonUp( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_LISTIMG_ItemOnIconRButtonUp );

		m_itemImages.push_back(pListImg);

		// name
		sprintf(buf, "ID_TEXT_Item%d", index);
		ControlText* pName = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemNames.push_back(pName);

		// price
		sprintf(buf, "ID_TEXT_ItemPrice%d", index);
		ControlText* pPrice = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemPrices.push_back(pPrice);

		//fit
		sprintf(buf, "ID_BUTTON_Fit%d", index);
		theUiManager.OnButtonClick( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_BUTTON_FitOnButtonClick );
		ControlButton* pFit = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemFitBtns.push_back(pFit);

        MeSprintf_s(buf,sizeof(buf)/sizeof(char) - 1,"ID_PICTURE_Fork%d",index);
		ControlPicture* pPicFork = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
        m_PitureFork.push_back(pPicFork);

		// state
		sprintf(buf, "ID_TEXT_Hot%d", index);
		ControlText* pState = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemStates.push_back(pState);

		// time limit
		sprintf(buf, "ID_TEXT_TimeLimit%d", index);
		ControlText* pTimeLimit = (ControlText*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemTimeLimits.push_back(pTimeLimit);

		// buy button
		sprintf(buf, "ID_BUTTON_Buy%d", index);
		theUiManager.OnButtonClick( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_BUTTON_BuyOnButtonClick );
		ControlButton* pBtn = (ControlButton*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemBuyBtns.push_back(pBtn);

		// background
		sprintf(buf, "ID_PICTURE_ItemWall%d", index);
		ControlPicture* pBackground = (ControlPicture*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
		m_itemBackgrounds.push_back(pBackground);

		++index;
		sprintf(buf, "ID_LISTIMG_Item%d", index);
		pListImg = (ControlListImage*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
	}
//===============================================================================================

//========================================================================================大标题 并显示热卖
	index = 1;
	sprintf(buf, "ID_CHECKBOX_Type%d", index);
	ControlCheckBox* pType = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
	while (pType)
	{
		theUiManager.OnCheckBoxCheck( ID_FRAME_ShopCenter, buf, s_CUI_ID_FRAME_ShopCenterID_CHECKBOX_TypeOnCheckBoxCheck );
		pType->SetVisable(false);
		m_tabs.AddRadio(pType);

		++index;
		sprintf(buf, "ID_CHECKBOX_Type%d", index);
		pType = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_ShopCenter, buf );
	}



	// 初始化类型
	if (m_tabs.GetControlSize() >= 2)
	{
		ControlCheckBox* pRadio = static_cast<ControlCheckBox*>(m_tabs.GetControl(0));
		pRadio->SetCaption(s_strNewType.c_str());
		pRadio->SetVisable(true);

		pRadio = static_cast<ControlCheckBox*>(m_tabs.GetControl(1));
		pRadio->SetCaption(s_strHotType.c_str());
		pRadio->SetVisable(true);
	}
	
	//显示热卖 改为 显示元宝商城
	//m_tabs.ToggleRadio(m_pID_CHECKBOX_Type2);
	m_tabs.ToggleRadio(m_pID_CHECKBOX_Type3);

//====================================================================================================

	m_nCurrPageIndex = 0;
	m_nCurrBuyItemId = -1;
	m_nCurrPreviewMountID = INVALID_VALUE;
	/*
	m_pPlayer = MeNew CPlayer();
	int nIndex = GetEffectMgr()->RegisterCharEffectContainer();
	if( nIndex >= 0 )
	{
		m_pPlayer->SetCharEffectContainer( GetEffectMgr()->GetCharEffectContainer( nIndex ) );
	}

	m_PlayerAnim = MeNew CPlayerAnim();
	m_pPlayer->SetAnim(m_PlayerAnim);
	m_PlayerAnim->SetPlayer(m_pPlayer);
	*/

	RenderAnim_Create(CUIRenderAnim::RTWUI_SHOP_FASION);

	for (int i = 0; i < MaxItem; ++i)
	{
		m_itemInfo[i].id = InvalidLogicNumber;
		m_itemInfo[i].count = 0;
	}
	m_nItemCount = 0;

	m_bUpdateFlag = false;
	m_bNeedUpdate = true;

	SetVisable(false);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ShopCenter::_UnLoadUI()
{
	/*
	if (m_pPlayer)
	{
		m_pPlayer->Destroy();	
		delete m_pPlayer;
		m_pPlayer = 0;
	}
	*/
	RenderAnim_Destroy();

	m_itemImages.clear();
	m_itemNames.clear();
	m_itemPrices.clear();
	m_itemStates.clear();
	m_itemBuyBtns.clear();
	m_itemBackgrounds.clear();
	m_itemTimeLimits.clear();
	m_tabs.Clear();
    m_SubTabs.Clear();
    m_PitureFork.clear();
	m_itemFitBtns.clear();
	ResetMembers();

	s_CUI_ID_FRAME_ShopChangePoint.UnLoadUI();

	return theUiManager.RemoveFrame( "Data\\UI\\ShopCenter.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ShopCenter::_IsVisable()
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	return m_pID_FRAME_ShopCenter->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ShopCenter::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_ShopCenter )
		return;
    if( thePlayerRole.GetLevel() < 5 && bVisable )
    {
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Shop_City, theXmlString.GetString(eText_UnderLevel15) );
        return;
    }
	m_pID_FRAME_ShopCenter->SetVisable( bVisable );
	if (bVisable)
	{
		UpdatePlayerAnimCtrl();

		//m_bRotate = false;
		//m_fRotateZ = 0.0f;

		m_nCurrPageIndex = 0;
		m_nCurrPreviewMountID = INVALID_VALUE;
		m_currMoveText.m_nCount = 0;

		Refresh();
		RefreshMoney();

		// 请求商城数据
		/*MsgGetShopCenter getShopCenter;
		GettheNetworkInput().SendMsg( &getShopCenter );*/

		if(m_bNeedUpdate)
		{
			MsgUpdateTradeShopConfigReq msg;
			GettheNetworkInput().SendMsg( &msg );
		}

		s_CUI_ID_FRAME_MiniMap.SetShopTextShow(false);
	}
}

void CUI_ID_FRAME_ShopCenter::UpdatePlayerAnimCtrl(int fashion_suit_item, int fashion_suit_model_id)
{
	if( !IsVisable() )
		return;

	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe != NULL && pMe->GetAnim() != NULL && RenderAnim_GetPlayer()->GetAnim() != NULL)
	{
		uint16 stVisualItemID[EEquipPartType_MaxEquitPart];
		uint8 equipIntensifyTime[EEquipPartType_MaxEquitPart];
		uint8 equipLevel[EEquipPartType_MaxEquitPart];
		uint8 equipElements[EEquipPartType_MaxEquitPart];
		CPlayer_SEquipment equip[eKeyAll_Max];

		memcpy(equip, pMe->GetEquip(), eKeyAll_Max * sizeof(CPlayer_SEquipment));
		equip[eKeyAll_AecorativeClothing].item.itembaseinfo.ustItemID = fashion_suit_item;
		equip[eKeyAll_AecorativeClothing].iModelID = fashion_suit_model_id;
		for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
		{
			int nPart = CEquipPartMap::Instance()->GetLogicPart(i);
			stVisualItemID[i] = equip[nPart].item.itembaseinfo.ustItemID;
			equipIntensifyTime[i] = equip[nPart].item.equipdata.gemHoleCount;
			equipLevel[i] = equip[nPart].item.equipdata.ucLevel;
			equipElements[i] = equip[nPart].item.itembaseinfo.value1;
		}

		RenderAnim_GetPlayer()->ShowAecpratove(true);
		RenderAnim_GetPlayer()->GetAnim()->ChangeSkeletonAndEquipAll(
			&equip,
			pMe->GetSex(),
			pMe->GetProfession(),
			pMe->GetHairColorIndex(),
			pMe->IsShowHelmet(), true, pMe->GetDefAvaterIndex(),
			theHeroGame.GetPlayerMgr()->GetMe()->GetHeroID(),pMe->IsSHowHero(),true);

		RenderAnim_GetPlayer()->GetAnim()->UpdateHardItem( pMe->HasFightFlag(eFighting),
			(void*)equip );
		RenderAnim_RotateReset();
		//RenderAnim_GetPlayer()->GetAnim()->SetPosition( 0.0f, 0.0f, 0.0f );

		/*
		if( pMe->IsHaveWeapon() )
		{
			// 是否拿旗子
			BOOL bHoldFlag = FALSE;
			if( RenderAnim_GetPlayer()->GetAnim()->IsHoldingFlagOnRightHand() )
				bHoldFlag = TRUE;

			RenderAnim_GetPlayer()->GetAnim()->ChangeWeaponAnim( RenderAnim_GetPlayer()->GetAnim()->GetWeaponActionModelId( pMe->GetProfession(), pMe->GetSex(), bHoldFlag ));

			RenderAnim_GetPlayer()->GetAnim()->PlayAnim2(	MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::single_idle,
				MexAnimCtrl::eNormalPlay );
		}
		else
		{
			RenderAnim_GetPlayer()->GetAnim()->PlayAnim2(	MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay, 
				0,
				MexAnimCtrl::eMaxLoopTimes, 
				MexAnimCtrl::eMaxTimeout, 
				MoreActionClient::Idle1,
				MexAnimCtrl::eNormalPlay );
		}

		RenderAnim_GetPlayer()->EquipByItemID(stVisualItemID, equipIntensifyTime, equipLevel, equipElements);
		RenderAnim_GetPlayer()->UpdateBones();
		*/
	}
}

bool CUI_ID_FRAME_ShopCenter::UI_RightLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_ShopCenter.m_bRotate = true;
	return true;
}

bool CUI_ID_FRAME_ShopCenter::UI_LeftLBD(INT nX, INT nY)
{
	s_CUI_ID_FRAME_ShopCenter.m_bRotate = true;
	return true;
}

bool CUI_ID_FRAME_ShopCenter::SetItemUI(const CTradeCenterInfo::cTradeItem& tradeItem, int nImageIndex)
{
	int nItemId = tradeItem.m_ItemID;
	int nItemCount = FindItemCount(nItemId);
	bool bEnable = nItemCount != 0;
	bEnable = true; //lyh++

	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( nItemId );
	if (!pItemDetail)
		return false;

	//积分和绑金设置物品绑定
	bool bBound = false;
	if ( tradeItem.m_ConsumeScore > 0 || tradeItem.m_TicketPrice > 0 )
		bBound = true;

	ControlIconDrag::S_ListImg stListImg;
	if (tradeItem.m_RefreshInterval == 0)
		stListImg.SetData(nItemId, 1, bEnable ? eIcon_Enable : eIcon_Disable, false, eTipFlag_Normal, false, bBound);
	else
		stListImg.SetData(nItemId, nItemCount, bEnable ? eIcon_Enable : eIcon_Disable, true, eTipFlag_Normal, false, bBound);

	stListImg.m_pkIconInfo->SetColorFrameType(eColorFrame_Level);

	m_itemImages[nImageIndex]->SetItem(&stListImg, 0);
	m_itemImages[nImageIndex]->SetVisable(true);

	DWORD dwNameColor = 0;
	if (gCfg.m_bShopCenterUseQualityColor)
		dwNameColor = S_IconInfoHero::GetQualityColor(pItemDetail->ustLevel);
	else
		dwNameColor = Color_Config.getColor(CC_NAME_POLICE);
	m_itemNames[nImageIndex]->SetText(pItemDetail->GetItemName(), dwNameColor);
	m_itemNames[nImageIndex]->SetVisable(true);

	bool bIsFashion = false; 
	bool bSameSex = false;
	if (pItemDetail->IsCanEquip())
	{
		ItemDefine::SItemCanEquip* pEquip = static_cast<ItemDefine::SItemCanEquip*>(pItemDetail);
		if (pEquip && pEquip->bFashion)
		{
			bIsFashion = true;
			CPlayer *me = theHeroGame.GetPlayerMgr()->GetMe();
			if (me != NULL && me->GetSex() == pEquip->cEquipSexReq)
				bSameSex = true;
		}
	}
	bool bIsMount = false;
	if (pItemDetail->ucItemType == ItemDefine::ITEMTYPE_OTHER)
	{
		ItemDefine::SItemOther* pOther = static_cast<ItemDefine::SItemOther*>(pItemDetail);
		if (pOther && pOther->otherType == ItemDefine::OtherType_Mount)
		{
			bIsMount = true;
		}
	}
	if (nImageIndex<m_itemFitBtns.size() && m_itemFitBtns[nImageIndex]!=NULL)
	{
		m_itemFitBtns[nImageIndex]->SetVisable(bIsFashion || bIsMount);
		m_itemFitBtns[nImageIndex]->SetEnable(bSameSex || bIsMount);
	}
    if(tradeItem.m_OriginalPrice > tradeItem.m_FinalDiscountPrice)
    {
        char szWord[256] = {0};

		MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeOriginPrice)*/"%d{#1103}",tradeItem.m_OriginalPrice);

		if(tradeItem.m_ConsumeScore > 0)
		{
          MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeOriginPrice)*/"%d{#1111}",tradeItem.m_OriginalPrice);
		}

		if(tradeItem.m_TicketPrice > 0)
		{
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeOriginPrice)*/"%d{#1104}",tradeItem.m_OriginalPrice);
		}
		
		

        m_itemTimeLimits[nImageIndex]->SetText(szWord);
        m_itemTimeLimits[nImageIndex]->SetVisable(true);

        m_PitureFork[nImageIndex]->SetVisable(true);
        m_itemStates[nImageIndex]->SetText("{#1105}");
        m_itemStates[nImageIndex]->SetVisable(true);
    }
    else
    {
        if (tradeItem.m_isHot || tradeItem.m_isNew)
        {
            if (tradeItem.m_isHot)
                m_itemStates[nImageIndex]->SetText("{#1101}");
            else if (tradeItem.m_isNew)
                m_itemStates[nImageIndex]->SetText("{#1102}");
            m_itemStates[nImageIndex]->SetVisable(true);
        }
    }


    m_itemPrices[nImageIndex]->SetText(GetTradeItemMoneyText(tradeItem));
    m_itemPrices[nImageIndex]->SetVisable(true);

	m_itemBuyBtns[nImageIndex]->SetVisable(true);

	m_itemBackgrounds[nImageIndex]->SetVisable(true);

	return true;
}

void CUI_ID_FRAME_ShopCenter::Refresh()
{
	if( !m_pID_FRAME_ShopCenter )
		return;
	struct SetPageButtonStatus 
	{
		~SetPageButtonStatus()
		{
			bool ret = s_CUI_ID_FRAME_ShopCenter.m_nCurrPageIndex > 0;
			s_CUI_ID_FRAME_ShopCenter.m_pID_BUTTON_FirstPage->SetEnable(ret);
			s_CUI_ID_FRAME_ShopCenter.m_pID_BUTTON_PageUp->SetEnable(ret);

			ret = s_CUI_ID_FRAME_ShopCenter.m_nCurrPageIndex < s_CUI_ID_FRAME_ShopCenter.m_nPageCount - 1;
			s_CUI_ID_FRAME_ShopCenter.m_pID_BUTTON_LastPage->SetEnable(ret);
			s_CUI_ID_FRAME_ShopCenter.m_pID_BUTTON_PageDown->SetEnable(ret);
		}
	};

	struct SortTrade
	{
		bool operator()(const CTradeCenterInfo::cTradeItem* v1, const CTradeCenterInfo::cTradeItem* v2)
		{
			return v1->m_Rank < v2->m_Rank;
		}
	};

  
    for (int n = 2 ; n < m_tabs.GetControlSize();++n)
    {
        ControlCheckBox* pRadio = static_cast<ControlCheckBox*>(m_tabs.GetControl(n));
        pRadio->SetVisable(false);
    }

    m_SubTabs.SetVisible(false);
	//zhuxincong 11.20 新增“全部”
	string strAll = theXmlString.GetString(eText_ShopCenter_All);//"全部"; //第一个改成全部
    if(m_SubTabs.GetControlSize() > 0)
    {
        ControlCheckBox* pCheckBox = static_cast<ControlCheckBox*>(m_SubTabs.GetControl(0));
		pCheckBox->SetCaption(strAll.c_str());
        pCheckBox->SetVisable(true);
    }

	//lyh 从第二个开始 设置大标题 分别为 元宝商城 绑金商城 积分商城
	for (int i = 0, c = 2; i < theTradeCenter.m_TradeMap.m_vecDisSet.size() && c < m_tabs.GetControlSize(); ++i, ++c)
	{
		ControlCheckBox* pRadio = static_cast<ControlCheckBox*>(m_tabs.GetControl(c));//设置大标题名字
		pRadio->SetCaption(theTradeCenter.m_TradeMap.m_vecDisSet[i].m_Name.c_str()); 
		pRadio->SetVisable(true);
	}

	SetPageButtonStatus setPageButtonStatus; //以下清空商品，开始入库

	for (int i = 0; i < m_itemImages.size(); ++i)
	{
		m_itemImages[i]->SetVisable(false);
	}
	for (int i = 0; i < m_itemNames.size(); ++i)
	{
		m_itemNames[i]->SetVisable(false);
	}
	for (int i = 0; i < m_itemPrices.size(); ++i)
	{
		m_itemPrices[i]->SetVisable(false);
	}
    for (int i = 0; i < m_PitureFork.size();++i)
    {
        m_PitureFork[i]->SetVisable(false);
    }
	for (int i = 0; i < m_itemStates.size(); ++i)
	{
		m_itemStates[i]->SetVisable(false);
	}
	for (int i = 0; i < m_itemBuyBtns.size(); ++i)
	{
		m_itemBuyBtns[i]->SetVisable(false);
	}
	for (int i = 0; i < m_itemBackgrounds.size(); ++i)
	{
		m_itemBackgrounds[i]->SetVisable(false);
	}
	for (int i = 0; i < m_itemTimeLimits.size(); ++i)
	{
		m_itemTimeLimits[i]->SetVisable(false);
	}
	for (int i = 0;i<m_itemFitBtns.size();++i)
	{
		if (m_itemFitBtns[i])
		{
			m_itemFitBtns[i]->SetVisable(false);
		}
	}
	m_broadcasts.clear();

	if (m_tabs.GetControlSize() == 0 || m_itemImages.empty())
		return;

	int nShowCount = m_itemImages.size(); // 每页显示的数量

	//控件移走，暂时不实用了，现在采用货币类型分类，新品热卖在大标题下 by vvx 2013.9.12
	// 新品 
	if (m_tabs.GetSelectRadio()->GetData()->m_szCaption == s_strNewType) //选择了新品
	{
		// 页数
		m_nPageCount = theTradeCenter.GetNewItemCount() / nShowCount;
		if (theTradeCenter.GetNewItemCount() % nShowCount > 0)
			++m_nPageCount;

		if (m_nPageCount == 0)
			m_nPageCount = 1;

		std::stringstream sstrPage;
		if (m_nPageCount > 1)
			sstrPage << m_nCurrPageIndex + 1 << "/" << m_nPageCount;
		else
			sstrPage << "1/1";
		m_pID_TEXT_Page->SetText(sstrPage.str());

		std::vector<CTradeCenterInfo::cTradeItem*> tradeItems;
		for (int i = 0; i < theTradeCenter.GetNewItemCount(); ++i)
		{
			CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetNewItem(i);
			if (!pTradeItem)
				continue;

			tradeItems.push_back(pTradeItem);
		}

		std::sort(tradeItems.begin(), tradeItems.end(), SortTrade());

		int nImageIndex = 0;
		int nTradeItemIndex = nShowCount * m_nCurrPageIndex; // 当前页第一个道具的索引
		for (int i = nTradeItemIndex; i < tradeItems.size() && nImageIndex < m_itemImages.size(); ++i)
		{
			CTradeCenterInfo::cTradeItem& tradeItem = *tradeItems[i];
			if (SetItemUI(tradeItem, nImageIndex))
				++nImageIndex;
		}

		return;
	}

	//控件移走，暂时不实用了，现在采用货币类型分类，新品热卖在大标题下 by vvx 2013.9.12
	// 热卖
	if (m_tabs.GetSelectRadio()->GetData()->m_szCaption == s_strHotType) //选择了热卖
	{
		// 页数
		m_nPageCount = theTradeCenter.GetHotItemCount() / nShowCount;
		if (theTradeCenter.GetHotItemCount() % nShowCount > 0)
			++m_nPageCount;

		if (m_nPageCount == 0)
			m_nPageCount = 1;

		std::stringstream sstrPage;
		if (m_nPageCount > 1)
			sstrPage << m_nCurrPageIndex + 1 << "/" << m_nPageCount;
		else
			sstrPage << "1/1";
		m_pID_TEXT_Page->SetText(sstrPage.str());
		std::vector<CTradeCenterInfo::cTradeItem*> tradeItems;
		for (int i = 0; i < theTradeCenter.GetHotItemCount(); ++i)
		{
			CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetHotItem(i);
			if (!pTradeItem)
				continue;

			tradeItems.push_back(pTradeItem);
		}

		std::sort(tradeItems.begin(), tradeItems.end(), SortTrade());

		int nImageIndex = 0;
		int nTradeItemIndex = nShowCount * m_nCurrPageIndex; // 当前页第一个道具的索引
		for (int i = nTradeItemIndex; i < tradeItems.size() && nImageIndex < m_itemImages.size(); ++i)
		{
			CTradeCenterInfo::cTradeItem& tradeItem = *tradeItems[i];
			if (SetItemUI(tradeItem, nImageIndex))
				++nImageIndex;
		}

		return;
	}

	//商城物品刷新真正开始by vvx 2013.9.12
    CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(m_tabs.GetSelectRadio()->GetData()->m_szCaption);
	if (!pTypeTrades)
		return;

    int nSubSize = pTypeTrades->m_vecSet.size();
	//zhuxincong 给容器中的第一个名字赋值。不然一打开商城显示的“全部”到这里会显示为空
	pTypeTrades->m_vecSet[0].m_NameSort = strAll;
    for (int i = 0;i < nSubSize &&i < m_SubTabs.GetControlSize();++i)
    {
        ControlCheckBox* pRadio = static_cast<ControlCheckBox*>(m_SubTabs.GetControl(i));
		
		pRadio->SetCaption(pTypeTrades->m_vecSet[i].m_NameSort.c_str());
		
		pRadio->SetVisable(true);
    }

    CTradeCenterInfo::cTradeSubSort *trades = theTradeCenter.GetTradeSubSort(pTypeTrades,m_SubTabs.GetSelectRadio()->GetData()->m_szCaption);
    if(!trades)
        return;

	// broadcast
	std::vector<int>::iterator it = trades->m_mapTradeInfo.begin();
	std::vector<int>::iterator end = trades->m_mapTradeInfo.end();
	for ( ; it != end; ++it)
	{
		CTradeCenterInfo::cTradeInfo* pInfo = theTradeCenter.GetTradeStringByIndex(*it);
		if (pInfo)
			m_broadcasts.push_back(pInfo->infoString);
	}

	int nTradeItemIndex = nShowCount * m_nCurrPageIndex; // 当前页第一个道具对应trades->m_vecItemIdSet的索引

	// 页数
	m_nPageCount = trades->m_vecItemIdSet.size() / nShowCount;
	if (trades->m_vecItemIdSet.size() % nShowCount > 0)
		++m_nPageCount;

	if (m_nPageCount == 0)
		m_nPageCount = 1;

	std::stringstream sstrPage;
	if (m_nPageCount > 1)
		sstrPage << m_nCurrPageIndex + 1 << "/" << m_nPageCount;
	else
		sstrPage << "1/1";
	m_pID_TEXT_Page->SetText(sstrPage.str());

	for (int nImageIndex = 0; nTradeItemIndex < trades->m_vecItemIdSet.size() && nImageIndex < m_itemImages.size(); ++nTradeItemIndex)
	{
		CTradeCenterInfo::cTradeItem* pTradeItem = theTradeCenter.GetTradeItemByItemID(trades->m_vecItemIdSet[nTradeItemIndex],pTypeTrades->chType);
		if (!pTradeItem)
			continue;

		CTradeCenterInfo::cTradeItem& tradeItem = *pTradeItem;
		if (SetItemUI(tradeItem, nImageIndex))
			++nImageIndex;
	}
}

void CUI_ID_FRAME_ShopCenter::RefreshMoney()
{
	if( !m_pID_FRAME_ShopCenter )
		return;
	m_pID_TEXT_Jinyuanbao->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_JinDing));
	m_pID_TEXT_Yingyuanbao->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao));
	m_pID_TEXT_IntegralShow->SetText(thePlayerRole.GetData(CPlayerRole::TYPE_ShopCenterScore));                   
}

int CUI_ID_FRAME_ShopCenter::FindItemCount(int nId)
{
	return 1;
	for (int i = 0; i < m_nItemCount; ++i)
	{
		if (m_itemInfo[i].id == nId)
			return m_itemInfo[i].count;
	}
	return 0;
}

CTradeCenterInfo::cTradeItem* CUI_ID_FRAME_ShopCenter::FindItem(int nId,char chtype)
{
	return theTradeCenter.GetTradeItemByItemID(nId,chtype);
}

std::string CUI_ID_FRAME_ShopCenter::GetTradeItemMoneyText(const CTradeCenterInfo::cTradeItem& item, int count)
{
	if( !m_pID_FRAME_ShopCenter )
		return "";
	if (count == 0)
		return "";

	std::stringstream str;
	if (item.m_FinalDiscountPrice > 0)
    {
        char szWord[256];
        if(item.m_OriginalPrice > item.m_FinalDiscountPrice)
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeFinalPrice)*/"%d",item.m_FinalDiscountPrice * count);
        else
            MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TradePrice),item.m_FinalDiscountPrice * count);
        
		   str << szWord<< "{#1103}  ";
    }
	if (item.m_TicketPrice > 0 )
	{
		char szWord[256];
		if(item.m_OriginalPrice > item.m_TicketPrice)
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeFinalPrice)*/"%d",item.m_TicketPrice * count);
		else
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TradePrice),item.m_TicketPrice * count);
		str << szWord << "{#1104}  ";
	}
//=========================================================
	//商城积分的操作
	if (item.m_ConsumeScore > 0)
	{
		char szWord[256];
		if(item.m_OriginalPrice > item.m_ConsumeScore) //设置原价格
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,/*theXmlString.GetString(eText_TradeFinalPrice)*/"%d",item.m_ConsumeScore * count);
		else
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_TradePrice),item.m_ConsumeScore * count);

		str << szWord<< "{#1111}  ";
	}
	


	return str.str();
}

bool CUI_ID_FRAME_ShopCenter::BuyCallback(const char* szInputData, void *pData)
{
	MsgShopCenterBuy* pMsg = (MsgShopCenterBuy*)pData;
	if( !pMsg )
		return false;
	int nCount = atoi( szInputData );
	if ( nCount <= 0 )
		return false;

	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pMsg->ustItemId );
	if (!pItemDetail)
		return false;

	//获得大标题的类型
	CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(s_CUI_ID_FRAME_ShopCenter.m_tabs.GetSelectRadio()->GetData()->m_szCaption);
	if (!pTypeTrades)
		return false;

	CTradeCenterInfo::cTradeItem* tradeItem = s_CUI_ID_FRAME_ShopCenter.FindItem(s_CUI_ID_FRAME_ShopCenter.m_nCurrBuyItemId,pTypeTrades->chType);
	if (!tradeItem)
		return false;

	// 没有足够的金锭
	if ( tradeItem->m_FinalDiscountPrice * nCount > thePlayerRole.GetData(CPlayerRole::TYPE_JinDing) )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NotEnoughJinDing) );
		return false;
	}	
	// 没有足够的金票
	if( tradeItem->m_TicketPrice * nCount > thePlayerRole.GetData(CPlayerRole::TYPE_JinPiao) )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_NotEnoughJinPiao ) );
		return false;
	}

	// 没有足够的积分
	if( tradeItem->m_ConsumeScore * nCount > thePlayerRole.GetData(CPlayerRole::TYPE_ShopCenterScore) )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_NotEnoughShopConsumeScore ) );
		return false;
	}

	pMsg->ustCount = nCount;
	pMsg->chType = pTypeTrades->chType;
	GettheNetworkInput().SendMsg( pMsg );
	return true;
}

void CUI_ID_FRAME_ShopCenter::EditDataChange(ControlObject *pSender, const char *szData)
{
	CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(s_CUI_ID_FRAME_ShopCenter.m_tabs.GetSelectRadio()->GetData()->m_szCaption);
	if (!pTypeTrades)
		return;

	CTradeCenterInfo::cTradeItem* tradeItem = s_CUI_ID_FRAME_ShopCenter.FindItem(s_CUI_ID_FRAME_ShopCenter.m_nCurrBuyItemId,pTypeTrades->chType);
	if (!tradeItem)
		return;

	int count = 0;
	if( s_CUI_ID_FRAME_BatchShop.GetEditNumberText() )
		count = atoi( s_CUI_ID_FRAME_BatchShop.GetEditNumberText() );
	s_CUI_ID_FRAME_BatchShop.SetTextTotalPrice( s_CUI_ID_FRAME_ShopCenter.GetTradeItemMoneyText(*tradeItem, count) );	
}

void CUI_ID_FRAME_ShopCenter::RenderBroadcast()
{
	if (m_currMoveText.m_nCount == 0)
		return;

	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	IRenderer* r = GetEngine()->GetRenderer();

	RECT picRC;
	m_pID_PICTURE_InfoWall->GetRealRect( &picRC );

	D3DVIEWPORT9 ViewPort;
	ViewPort.X = picRC.left;
	ViewPort.Y = picRC.top;
	ViewPort.Width = m_pID_PICTURE_InfoWall->GetWidth();
	ViewPort.Height = m_pID_PICTURE_InfoWall->GetHeight();
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;

	r->SetViewport( &ViewPort );
	r->BeginScene();
	r->Clear( 0L, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 255, 255, 255), 1.0f, 0L );

	{
		RECT rc;
		rc.left = m_currMoveText.m_nX;
		rc.right = rc.left + (m_currMoveText.m_strText.size() + 2) * m_pID_FRAME_ShopCenter->GetFontSize();
		rc.top = picRC.top;
		rc.bottom = rc.top + m_pID_PICTURE_InfoWall->GetHeight();

		FontSystem::DrawTextDirect( m_currMoveText.m_strText.c_str(),
			&rc, DT_LEFT,
			m_currMoveText.m_dwColor,
			m_pID_FRAME_ShopCenter->GetFontIndex(), true );
	}

	r->EndScene();

	getwsCamera()->ResetViewport();
}

bool CUI_ID_FRAME_ShopCenter::Buy(int nItemId)
{
	if( !m_pID_FRAME_ShopCenter )
		return false;
	ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( nItemId );
	if (!pItemDetail)
		return false;

	// 安全保护
	if( CWealthProtect::Instance().IsInProtectTime() || CPreventWallow::Instance().IsFCMNotHealthy() )
		return true;

	//获得大标题的类型
	CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(m_tabs.GetSelectRadio()->GetData()->m_szCaption);
	if (!pTypeTrades)
		return false;

	ControlListImage* pBagListImg = 0;
	CItemBag2* pBag = 0;
	int bagType = BT_NormalItemBag;
	switch (pItemDetail->ucItemType)
	{
	case ItemDefine::ITEMTYPE_MATERIAL:
	case ItemDefine::ITEMTYPE_GEM:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_MaterialBag);
		pBag = &thePlayerRole.m_bagMaterial;
		bagType = BT_MaterialBag;
		break;
	case ItemDefine::ITEMTYPE_TASK:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_TaskBag);
		pBag = &thePlayerRole.m_bagTask;
		bagType = BT_TaskBag;
		break;
	default:
		pBagListImg = s_CUI_ID_FRAME_PACK.GetListImageByBagType(BT_NormalItemBag);
		pBag = &thePlayerRole.m_bag;
		bagType = BT_NormalItemBag;
		break;
	}

	int nPackEmptyIndex = pBag->FindNullItemOffset();
	if (nPackEmptyIndex == -1)
	{
		switch (bagType)
		{
		case BT_MaterialBag:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_MaterialPackFull) );
			break;
		case BT_TaskBag:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_TaskPackFull) );
			break;
		default:
			s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NormalPackFull) );
			break;
		}
		return true;
	}

	CTradeCenterInfo::cTradeItem* tradeItem = s_CUI_ID_FRAME_ShopCenter.FindItem(nItemId,pTypeTrades->chType);
	if (!tradeItem)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NotItemShopCenter) );
		return false;
	}

	int nCount = tradeItem->m_RefreshInterval != 0 ? FindItemCount(nItemId) : CItemBag2::GetItemStackCount(nItemId);
	if (nCount <= 0)
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NotItemShopCenter) );
		return false;
	}

	if (pItemDetail->IsExclusive())
		nCount = 1; // 一次只能买一个
	else if (nCount > CItemBag2::GetItemStackCount(nItemId))
		nCount = CItemBag2::GetItemStackCount(nItemId);

	MsgShopCenterBuy msg;
	msg.ustItemId = nItemId;
	msg.ustCount = 1;
	msg.chType = pTypeTrades->chType;
	m_nCurrBuyItemId = msg.ustItemId;

	//请输入要购买的物品数量
	CUI_ID_FRAME_BatchShop::Show( "",
		true, true, CUI_ID_FRAME_ShopCenter::BuyCallback,
		&msg, sizeof(msg) );

	s_CUI_ID_FRAME_BatchShop.SetEditDataChangedCallback(CUI_ID_FRAME_ShopCenter::EditDataChange);
	s_CUI_ID_FRAME_BatchShop.SetMaxValue(nCount);
	s_CUI_ID_FRAME_BatchShop.SetEditNumber(1);
	return true;
}

void CUI_ID_FRAME_ShopCenter::SetSubTypeBoxCheck(ControlObject *pSender,bool *pbChecked)
{
    if(pSender != m_SubTabs.GetSelectRadio())
        m_nCurrPageIndex = 0;
    m_SubTabs.ToggleRadio(static_cast<ControlCheckBox*>(pSender));
    Refresh();
}


void CUI_ID_FRAME_ShopCenter::SetFindPath(unsigned int ustItemID)
{
	CTradeCenterInfo::cTypeSort* pTypeTrades = theTradeCenter.GetTradeParentSort(m_tabs.GetSelectRadio()->GetData()->m_szCaption);
	if (!pTypeTrades)
		return;

    CTradeCenterInfo::cTradeItem* pItem = FindItem(ustItemID,pTypeTrades->chType);
    if(!pItem)
        return;

    if(!pItem->m_bNeedNpc)
        return;

    if(pItem->m_nMapId < 0)
        return;

    if(pItem->m_nNpcId < 0)
        return;

    MapConfig::MapData* pData = theMapConfig.GetMapDataById(pItem->m_nMapId);
    if(!pData)
        return;

    NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(pItem->m_nNpcId,pItem->m_nMapId);
    if(!pNpc)
        return;

    char szWord[256] = {0};
    MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_ShopCenterFindPath)   \
        ,pData->MapName.c_str(),pNpc->name.c_str());

    s_CUI_ID_FRAME_MessageBox.Show(szWord," ",CUI_ID_FRAME_MessageBox::eTypeYesNo
        ,false,FindPathCallback,(void*)&pItem->m_ItemID,sizeof(pItem->m_ItemID));
}
