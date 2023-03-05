/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\liuchuanpeng\桌面\4xing\FiveXingChange.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FiveXingChange.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "PlayerRole.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "EquipUIHelper.h"
#include "Common.h"

CUI_ID_FRAME_FiveXingChange s_CUI_ID_FRAME_FiveXingChange;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FiveXingChange, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FiveXingChange, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_BUTTON_CancelOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material2OnIconRButtonUp )
// MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material3OnIconDragOn )
// MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material3OnIconLDBClick )
// MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material3OnIconButtonClick )
// MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_LISTIMG_Material3OnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingChange, ID_BUTTON_ResetOnButtonClick )
CUI_ID_FRAME_FiveXingChange::CUI_ID_FRAME_FiveXingChange()
{
	// Member
	m_pID_FRAME_FiveXingChange = NULL;
	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
	//m_pID_PICTURE_TitleWord = NULL;
	m_pID_PICTURE_Flash = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Material2 = NULL;
	//m_pID_LISTIMG_Material3 = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_BUTTON_Reset = NULL;
}
// Frame
bool CUI_ID_FRAME_FiveXingChange::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_FiveXingChange::OnFrameRender()
{
	if(!IsVisable() )
		return true;

#ifdef _DEBUG
	DebugInfo();
#endif
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();		
	if (!pMe )
		return true;

	Vector vPos;
	pMe->GetPos( &vPos.x, &vPos.y, &vPos.z );
	if(IsOverDistance(vPos))
		SetVisable(false);

	//特效播放
	if(IsAnimPlaying())
	{
		//如果动画已经结束
		if(!IsAnimOver())
		{
			//是否能显示结果
			if(IsCanShowResult())
			{
				ShowResult();
				EndShowResult();
			}
		}
		else
		{
			RECT rc;
			m_pID_PICTURE_Flash->GetRealRect(&rc);
			UpdateAnim(rc); 
		} 
	}
	return true;
}
// Button
// bool CUI_ID_FRAME_FiveXingChange::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// // Button
// bool CUI_ID_FRAME_FiveXingChange::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																ControlIconDrag::S_ListImg* pItemDrag,
																ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	if(!pItemDrag)
		return false;

	char szError[256];
	memset(szError,0L,sizeof(szError));
	//是否为五行道具
	if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,szError))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
		return false;
	}

	int nSuitLevel = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetSuitLevel();
	if(nSuitLevel < theSuitOperateConfig.GetMinElementSuitChangeLevel())
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_FiveXingUpdateNoLessThree) );
		return false;
	}
	int nSuitElem = ((SCharItem*)pItemDrag->m_pkIconInfo->GetData())->GetElements();
	if(nSuitElem == 0)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_FiveXingTipNoJianDing) );
		return false;
	}

	if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
		return false;

	ClearFiveXingItemByIndex(enum_FiveXingItem);
	ClearFiveXingItemByIndex(enum_FiveXingElement);
	ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	Clear();

	//保存数据
	SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingItem);

	//更新道具
	UpdataItem(m_pID_LISTIMG_Armour,pItemDrag);

	//更新钱币
	SetMoneyUI((SCharItem*)pItemDrag->m_pkIconInfo->GetData());

	//m_pID_BUTTON_Ok->SetEnable(true);
	RefreshOkButton();

	SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXingChange::SetMaterial0);
	SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXingChange::SetMaterial1);
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	Clear();
	ClearFiveXingItemByIndex(enum_FiveXingItem);
	ClearFiveXingItemByIndex(enum_FiveXingElement);
	ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	m_pID_BUTTON_Ok->SetEnable(false);
	return false;
}
// Button
bool CUI_ID_FRAME_FiveXingChange::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	for (int i = 0;i < enum_FiveXingMax - 1;++i)
		if(m_FiveXing[i].m_nIndex == -1)
			return true;

	//金钱判断
	SCharItem sCharItem;
	if(!thePlayerRole.m_bag.GetItem(m_FiveXing[0].m_nIndex,&sCharItem))
		return false;

	if(!IsMoneyEnough(&sCharItem,false))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_FiveXingTipUpdateNoMoney) );
		return false;
	}

	int nIndex    = m_FiveXing[enum_FiveXingItem].m_nIndex;
	__int64 nGuid = m_FiveXing[enum_FiveXingItem].m_nGuid;

	MsgSuitChangeReq msg;
	msg.chOperate    = MsgSuitChangeReq::ECD_ElementSuitChange;
	msg.stEquipIndex = nIndex;
	msg.nEquipGuid   = nGuid;

	msg.xItemInfo[0].chItemBagType = m_FiveXing[enum_FiveXingMaterial].m_eBagType;
	msg.xItemInfo[0].stItemIndex = m_FiveXing[enum_FiveXingMaterial].m_nIndex;
	msg.xItemInfo[0].nItemGuid = m_FiveXing[enum_FiveXingMaterial].m_nGuid;

	msg.xItemInfo[1].chItemBagType = m_FiveXing[enum_FiveXingElement].m_eBagType;
	msg.xItemInfo[1].stItemIndex = m_FiveXing[enum_FiveXingElement].m_nIndex;
	msg.xItemInfo[1].nItemGuid = m_FiveXing[enum_FiveXingElement].m_nGuid;

	GettheNetworkInput().SendMsg(&msg);

	m_pID_PICTURE_Flash->SetVisable(true);

	m_GroupMaterial.SetVisible(false);

	PlayAnim();
	return true;
}
// Button
bool CUI_ID_FRAME_FiveXingChange::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																  ControlIconDrag::S_ListImg* pItemDrag,
																  ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	if(!pItemDrag)
		return false;

	char szError[256];
	memset(szError,0L,sizeof(szError));
	//是否为五行灵珠
	if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
		ItemDefine::SItemCheckUp::ECD_Elements,ItemDefine::SItemCheckUp::ECD_ElementsCheckUp,szError))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
		return false;
	}

	//保存数据
	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
		SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingElement);
	else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingElement);

	//刷新道具
	UpdataItem(m_pID_LISTIMG_Material,pItemDrag);
	RefreshOkButton();

	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	ClearFiveXingItemByIndex(enum_FiveXingElement);
	m_pID_LISTIMG_Material->Clear();
	RefreshOkButton();
	return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
																   ControlIconDrag::S_ListImg* pItemDrag,
																   ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	if(!pItemDrag)
		return false;

	char szError[256];
	memset(szError,0L,sizeof(szError));
	//是否五行转换材料
	if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
		ItemDefine::SItemCheckUp::ECD_Suit,ItemDefine::SItemCheckUp::ECD_ElementsSuitChange,szError))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
		return false;
	}

	//保存数据
	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
		SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingMaterial);
	else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
		SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingMaterial);

	//刷新材料
	UpdataItem(m_pID_LISTIMG_Material2,pItemDrag);

	//         bool bEnable = true;
	//         for (int i = 0;i < enum_FiveXingMax - 1;++i)    
	//             if(m_FiveXing[i].m_nIndex == -1)
	//                 bEnable = false;
	// 
	//         m_pID_BUTTON_Ok->SetEnable(bEnable);
	RefreshOkButton();

	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingChange)
    {
        assert(false&&"ui error");
        return false;
    }

	m_pID_LISTIMG_Material2->Clear();
	ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	RefreshOkButton();
	return false;
}
// ListImg / ListEx
// bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material3OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
// 																   ControlIconDrag::S_ListImg* pItemDrag,
// 																   ControlIconDrag::S_ListImg* pItemSrc )
// {
//     if(!m_pID_FRAME_FiveXingChange)
//     {
//         assert(false&&"ui error");
//         return false;
//     }
// 
// 	if(!pItemDrag)
// 		return false;
// 
// 	char szError[256];
// 	memset(szError,0L,sizeof(szError));
// 	//是否五行转换材料
// 	if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_CHECKUP,  \
// 		ItemDefine::SItemCheckUp::ECD_Suit,ItemDefine::SItemCheckUp::ECD_ElementsSuitChange,szError))
// 	{
// 		GetShowScreenText() ->AddInfo( szError/*theXmlString.GetString(eClient_FiveXingTipUpdateNoMoney)*/, Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
// 		return false;
// 	}
// 	//保存数据
// 	if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
// 		SetFiveXingItem(pItemDrag,BT_NormalItemBag,CFiveXingBase::enum_FiveXingMaterial);
// 	else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
// 		SetFiveXingItem(pItemDrag,BT_MaterialBag,CFiveXingBase::enum_FiveXingMaterial);
// 
// 	//刷新材料
// 	UpdataItem(m_pID_LISTIMG_Material2,pItemDrag);
// 
// 	//         bool bEnable = true;
// 	//         for (int i = 0;i < enum_FiveXingMax - 1;++i)    
// 	//             if(m_FiveXing[i].m_nIndex == -1)
// 	//                 bEnable = false;
// 	// 
// 	//         m_pID_BUTTON_Ok->SetEnable(bEnable);
// 
// 	RefreshOkButton();
// 
// 	return false;
// }
// bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	return false;
// }
// bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
// 	return false;
// }
// bool CUI_ID_FRAME_FiveXingChange::ID_LISTIMG_Material3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
// {
//     if(!m_pID_FRAME_FiveXingChange)
//     {
//         assert(false&&"ui error");
//         return false;
//     }
// 
// 	m_pID_LISTIMG_Material3->Clear();
// 	ClearFiveXingItemByIndex(enum_FiveXingExploit);
// 	RefreshOkButton();
// 	return false;
// }
// Button
bool CUI_ID_FRAME_FiveXingChange::ID_BUTTON_ResetOnButtonClick( ControlObject* pSender )
{
	m_pID_TEXT_Word->SetVisable(false);
	m_pID_BUTTON_Reset->SetVisable(false);
	m_pID_PICTURE_Flash->SetVisable(false);
	m_pID_PICTURE_ItemWall->SetVisable(false);

	m_pID_BUTTON_Ok->SetEnable(true);
	m_pID_BUTTON_Cancel->SetEnable(true);

	m_GroupMaterial.SetVisible(true);

	ClearFiveXingItemByIndex(enum_FiveXingItem);
	ClearFiveXingItemByIndex(enum_FiveXingElement);
	ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	Clear();

	EndShowResult();
	EndAnim();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_FiveXingChange::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FiveXingChange.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\FiveXingChange.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_FiveXingChange::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_FiveXingChange, s_CUI_ID_FRAME_FiveXingChangeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_FiveXingChange, s_CUI_ID_FRAME_FiveXingChangeOnFrameRender );
// 	theUiManager.OnButtonClick( ID_FRAME_FiveXingChange, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FiveXingChangeID_BUTTON_CLOSEOnButtonClick );
// 	theUiManager.OnButtonClick( ID_FRAME_FiveXingChange, ID_BUTTON_help, s_CUI_ID_FRAME_FiveXingChangeID_BUTTON_helpOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_FiveXingChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_ArmourOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_ArmourOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_ArmourOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingChange, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_ArmourOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_FiveXingChange, ID_BUTTON_Ok, s_CUI_ID_FRAME_FiveXingChangeID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_FiveXingChange, ID_BUTTON_Cancel, s_CUI_ID_FRAME_FiveXingChangeID_BUTTON_CancelOnButtonClick );
	theUiManager.OnIconDragOn( ID_FRAME_FiveXingChange, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_MaterialOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_MaterialOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_MaterialOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingChange, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_MaterialOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_FiveXingChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material2OnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material2OnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material2OnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingChange, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material2OnIconRButtonUp );
// 	theUiManager.OnIconDragOn( ID_FRAME_FiveXingChange, ID_LISTIMG_Material3, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material3OnIconDragOn );
// 	theUiManager.OnIconLDBClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material3, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material3OnIconLDBClick );
// 	theUiManager.OnIconButtonClick( ID_FRAME_FiveXingChange, ID_LISTIMG_Material3, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material3OnIconButtonClick );
// 	theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingChange, ID_LISTIMG_Material3, s_CUI_ID_FRAME_FiveXingChangeID_LISTIMG_Material3OnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_FiveXingChange, ID_BUTTON_Reset, s_CUI_ID_FRAME_FiveXingChangeID_BUTTON_ResetOnButtonClick );

	m_pID_FRAME_FiveXingChange = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FiveXingChange );
	m_pID_PICTURE_RightTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_RightTitle );
// 	m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_MiddleTitle );
// 	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_BUTTON_CLOSE );
// 	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_BUTTON_help );
	m_pID_PICTURE_ItemWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_ItemWall );
	m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_LISTIMG_Armour );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_BUTTON_Cancel );
	m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_TEXT_UseMoneyZ );
	m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_TEXT_UseMoney );
	m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_LeftTitle );
//	m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_TitleWord );
	m_pID_PICTURE_Flash = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_PICTURE_Flash );
	m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_LISTIMG_Material );
	m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_LISTIMG_Material2 );
//	m_pID_LISTIMG_Material3 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_LISTIMG_Material3 );
	m_pID_TEXT_Word = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_TEXT_Word );
	m_pID_BUTTON_Reset = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingChange, ID_BUTTON_Reset );
	assert( m_pID_FRAME_FiveXingChange );
	assert( m_pID_PICTURE_RightTitle );
	//assert( m_pID_PICTURE_MiddleTitle );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_help );
	assert( m_pID_PICTURE_ItemWall );
	assert( m_pID_LISTIMG_Armour );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_UseMoneyZ );
	assert( m_pID_TEXT_UseMoney );
	assert( m_pID_PICTURE_LeftTitle );
//	assert( m_pID_PICTURE_TitleWord );
	assert( m_pID_PICTURE_Flash );
	assert( m_pID_LISTIMG_Material );
	assert( m_pID_LISTIMG_Material2 );
//	assert( m_pID_LISTIMG_Material3 );
	assert( m_pID_TEXT_Word );
	assert( m_pID_BUTTON_Reset );
	m_pID_FRAME_FiveXingChange->SetOnVisibleChangedFun(OnVisibleChange);

	m_pID_TEXT_Word->SetVisable(false);
	m_pID_BUTTON_Reset->SetVisable(false);
	m_pID_PICTURE_Flash->SetVisable(false);
	m_pID_PICTURE_ItemWall->SetVisable(false);

	m_GroupMaterial.Clear();
	m_GroupMaterial.AddControl(m_pID_LISTIMG_Material);
	m_GroupMaterial.AddControl(m_pID_LISTIMG_Material2);
	//m_GroupMaterial.AddControl(m_pID_LISTIMG_Material3);
	m_GroupMaterial.AddControl(m_pID_PICTURE_RightTitle);
	//m_GroupMaterial.AddControl(m_pID_PICTURE_MiddleTitle);
	m_GroupMaterial.AddControl(m_pID_PICTURE_LeftTitle);
	m_GroupMaterial.SetVisible(true);

	RECT rc;
	m_pID_PICTURE_Flash->GetRealRect(&rc);
	InitAnim(rc);

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_FiveXingChange::_UnLoadUI()
{
	m_pID_FRAME_FiveXingChange = NULL;
	m_pID_PICTURE_RightTitle = NULL;
// 	m_pID_PICTURE_MiddleTitle = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_help = NULL;
	m_pID_PICTURE_ItemWall = NULL;
	m_pID_LISTIMG_Armour = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_UseMoneyZ = NULL;
	m_pID_TEXT_UseMoney = NULL;
	m_pID_PICTURE_LeftTitle = NULL;
//	m_pID_PICTURE_TitleWord = NULL;
	m_pID_PICTURE_Flash = NULL;
	m_pID_LISTIMG_Material = NULL;
	m_pID_LISTIMG_Material2 = NULL;
//	m_pID_LISTIMG_Material3 = NULL;
	m_pID_TEXT_Word = NULL;
	m_pID_BUTTON_Reset = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\FiveXingChange.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FiveXingChange::_IsVisable()
{
	if( !m_pID_FRAME_FiveXingChange )
		return false;
	return m_pID_FRAME_FiveXingChange->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_FiveXingChange::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_FiveXingChange )
		return;
	ClearFiveXingItemByIndex(enum_FiveXingItem);
	ClearFiveXingItemByIndex(enum_FiveXingElement);
	ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	Clear();
	if(bVisable)
	{
		m_pID_BUTTON_Ok->SetEnable(false);
		m_GroupMaterial.SetVisible(true);
	}

	m_pID_FRAME_FiveXingChange->SetVisable( bVisable );
}

void CUI_ID_FRAME_FiveXingChange::Init()
{
	Clear();
}

void CUI_ID_FRAME_FiveXingChange::Clear()
{
	m_pID_LISTIMG_Armour->Clear();
	m_pID_LISTIMG_Material->Clear();
	m_pID_LISTIMG_Material2->Clear();
	//m_pID_LISTIMG_Material3->Clear();

	SetMoneyUI(NULL);
}


void CUI_ID_FRAME_FiveXingChange::SetMoneyUI(SCharItem *pItem)
{
	std::string strMoney;
	if(!pItem)
		//UpdateMoney(0,strMoney);
		m_pID_TEXT_UseMoney->Clear();
	else
		UpdateMoneyByItem(pItem,strMoney,false);

	DWORD dwColor = 0xffffffff;
	if(!IsMoneyEnough(pItem,false))
		dwColor = 0xffff0000;

	m_pID_TEXT_UseMoney->SetText(strMoney,dwColor);
	//*m_pID_TEXT_UseMoney = strMoney;
}

void CUI_ID_FRAME_FiveXingChange::OnAck(MsgSuitChangeAck* pAck)
{
	switch (pAck->uchResult)
	{
	case MsgSuitChangeAck::ECD_SuccessChagneSkillSuit:
		break;
	case MsgSuitChangeAck::ECD_SuccessChagneElementSuit:
		{
			SCharItem *pCharItem = thePlayerRole.m_bag.GetCharItemFromIdx(m_FiveXing[0].m_nIndex);
			if(!pCharItem)
				return;

			pCharItem->itembaseinfo.value1  = pAck->nValue; 

#ifdef _DEBUG
			int nSuit = pCharItem->GetSuitLevel();
			int nElem = pCharItem->GetElements();
			std::string  strDes;
			char szWord[256];
			MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"提存等级:%d",nSuit);
			strDes += szWord;
			switch(nElem)
			{
			case 1: //金
				strDes += "金";
				break;
			case 2: //木
				strDes += "木";
				break;
			case 3: //水
				strDes += "水";
				break;
			case 4: //火
				strDes += "火";
				break;
			case 5: //土
				strDes += "土";
				break;
			}

			::OutputDebugString(strDes.c_str());
#endif
			//s_CUI_ID_FRAME_PACK.ChangeMoney(pAck->nLeftMoney);
			s_CUI_ID_FRAME_PACK.RefreshNormalPackByIndex(m_FiveXing[0].m_nIndex);

			//GetShowScreenText() ->AddInfo(theXmlString.GetString(eClient_SkillSuitChangeSuccess), Color_Config.getColor(CC_Center_OtherInfo), FIGHTHINTMESSAGEROW);

			BeginShowResult();
		}
		break;
	case MsgSuitChangeAck::ECD_ChangeFailed:
		{
			m_GroupMaterial.SetVisible(true);
		}
		break;
	default:
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_SkillSuitChangeFailed) );
		}
		break;
	}

	//         ClearFiveXingItemByIndex(enum_FiveXingItem);
	//         ClearFiveXingItemByIndex(enum_FiveXingElement);
	//         ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	//         Clear();
}

void CUI_ID_FRAME_FiveXingChange::OnVisibleChange( ControlObject* pUIObject )
{
	s_CUI_ID_FRAME_FiveXingChange.ClearFiveXingItemByIndex(enum_FiveXingItem);
	s_CUI_ID_FRAME_FiveXingChange.ClearFiveXingItemByIndex(enum_FiveXingElement);
	s_CUI_ID_FRAME_FiveXingChange.ClearFiveXingItemByIndex(enum_FiveXingMaterial);
	s_CUI_ID_FRAME_FiveXingChange.Clear();
	s_CUI_ID_FRAME_FiveXingChange.m_pID_TEXT_Word->SetVisable(false);
	s_CUI_ID_FRAME_FiveXingChange.m_pID_PICTURE_ItemWall->SetVisable(false);
	s_CUI_ID_FRAME_FiveXingChange.m_pID_BUTTON_Ok->SetEnable(false);
	s_CUI_ID_FRAME_FiveXingChange.m_pID_BUTTON_Cancel->SetVisable(true);
	s_CUI_ID_FRAME_FiveXingChange.m_pID_BUTTON_Reset->SetVisable(false);
}

void CUI_ID_FRAME_FiveXingChange::ShowResult()
{   
	m_pID_PICTURE_Flash->SetVisable(false);
	m_pID_TEXT_Word->SetVisable(true);
	m_pID_BUTTON_Reset->SetVisable(true);
	m_pID_PICTURE_ItemWall->SetVisable(true);
	m_pID_BUTTON_Ok->SetEnable(false);
	m_pID_BUTTON_Cancel->SetEnable(false);

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Success, theXmlString.GetString(eClient_SkillSuitChangeSuccess) );

	ItemDefine::SRandAttribute* pArmourRand = NULL;
	ControlIconDrag::S_ListImg* pImg = s_CUI_ID_FRAME_PACK.GetItemByIndex(BT_NormalItemBag, m_FiveXing[0].m_nIndex);
	if(!pImg)
		return;

	SCharItem sCharItem;
	if(!thePlayerRole.m_bag.GetItem(m_FiveXing[0].m_nIndex,&sCharItem))
		return;

	int cElemType = sCharItem.GetElements();
	int cElemLevel = sCharItem.GetSuitLevel();

	char szWord[128];
	memset(szWord,0L,sizeof(szWord));
	MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,theXmlString.GetString(eText_FiveXingChangeResult),theXmlString.GetString(eText_FiveXingJin + cElemType - 1));

	m_pID_TEXT_Word->SetText(szWord);
}

void CUI_ID_FRAME_FiveXingChange::RefreshOkButton()
{
	if(!IsVisable())
		return;
	m_pID_BUTTON_Ok->SetEnable(true);

	for (int i = 0;i < enum_FiveXingMax - 1;++i)    
		if(m_FiveXing[i].m_nIndex == -1)
		{
			m_pID_BUTTON_Ok->SetEnable(false);
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

		DWORD dwMoney = 0;
		dwMoney = theSuitOperateConfig.GetElementSuitChangeCostMoney(pCanEquip->stEquipLevelReq);
// 		DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);
// 		if(dwCurMoney < dwMoney)
        if(!thePlayerRole.HaveEnoughMoney(dwMoney))
		{
			m_pID_BUTTON_Ok->SetEnable(false);
			return;
		}

		SetMoneyUI((SCharItem*)(pImg->m_pkIconInfo->GetData()));
}
