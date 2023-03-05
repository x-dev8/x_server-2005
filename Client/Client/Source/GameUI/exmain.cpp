/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\exmain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "exmain.h"
#include "Main.h"
#include "Skill.h"
#include "Pack.h"
////#include "Function.h"
#include "ActionUI.h"
#include "GameMain.h"
#include "ExpStage.h"
#include "../Player.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "ExitGame.h"
#include "MeUi/ControlIconDragManager.h"
#include "Me3d/Config.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "color_config.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "Pack_Ex.h"
#include "baseProperty.h"
#include "GameSettingUI.h"
#include "shortcutkey_configure.h"
#include "Pet.h"
#include "NewSkillMain.h"
#include "Main.h"
#include "bag/SkillBag.h"
#include "GameSetting.h"
#include "UserData.h"
#include "ui/GameSettingFunction.h"
#include "Action.h"
#include "SkillProduce.h"
#include "ScreenInfoManager.h"
#include "Target.h"
#include "zhujiangbianshen.h"
#include "SuAnimal.h"
#include "SuAnimalMain.h"

#define RIGHT_ROW_COUNT 6
extern CHeroGame* theApp;

CUI_ID_FRAME_Exmain s_CUI_ID_FRAME_Exmain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Exmain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Exmain, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_ExmainOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_ExmainOnIconLDBClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_ExmainOnIconRButtonUp )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_ExmainOnIconButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_Exmain2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_Exmain2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_Exmain2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_Exmain2OnIconRButtonUp )

MAP_ICON_DRAG_DISABLE_ON_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_HotkyeOnIconDisableDragOn )
MAP_ICON_DRAG_DISABLE_OUT_CALLBACK( s_CUI_ID_FRAME_Exmain, ID_LISTIMG_HotkyeOnIconDisableDragOut )

CUI_ID_FRAME_Exmain::CUI_ID_FRAME_Exmain()
{
	// SGuildMember
	m_pID_FRAME_Exmain = NULL;
	m_pID_LISTIMG_Exmain = NULL;
    m_pID_LISTIMG_Exmain2 = NULL;
}
// Frame
bool CUI_ID_FRAME_Exmain::OnFrameRun()
{
	theUiManager.ToTop( m_pID_FRAME_Exmain, s_CUI_ID_FRAME_MAIN.GetFrame()/*m_pID_FRAME_MAIN*/ );
	UpdateIconInfo();
	return true;
}
bool CUI_ID_FRAME_Exmain::OnFrameRender()
{
	return true;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_HotkyeOnIconDisableDragOn( ControlObject* pSender, ControlObject* pMe, 
										  ControlIconDrag::S_ListImg* pItemDrag,
										  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;

    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }
	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString(eText_DragLockWarning) );

	return true;
	unguard;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_HotkyeOnIconDisableDragOut( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;

	//GetShowScreenText() ->AddInfo( theXmlString.GetString(eText_DragLockWarning), Color_Config.getColor( CC_Center_WarningErrorInfo ), 1000 );

	return true;
	unguard;
}

// ListImg / ListEx
bool CUI_ID_FRAME_Exmain::ID_LISTIMG_ExmainOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														ControlIconDrag::S_ListImg* pItemDrag,
														ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

	if ( pItemDrag->IsNull()|| !pItemSrc )
		return false;
	UINT nHotkeyIndex = m_pID_LISTIMG_Exmain->GetItemIndex( pItemSrc );
	if ( nHotkeyIndex >= More_exMainUIMax )
		return false;

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if ( !pItem )
		return false;
	if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		return false;
	}

	// 自己
	if ( pSender == pMe )
	{
		UINT nSrcIndex = m_pID_LISTIMG_Exmain->GetItemIndex( pItemDrag );
		SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex];											//sbw_add
		thePlayerRole.m_pHotKeyBag[nHotkeyIndex] = thePlayerRole.m_pHotKeyBag[nSrcIndex];
		thePlayerRole.m_pHotKeyBag[nSrcIndex] = stTemp;                                         //ErrorUnsignedShortID;			//sbw_modify
	}
	else if( pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/ )
	{
		//UINT nSrcIndex = 0;
		//if( s_CUI_ID_FRAME_MAIN.nIndexHotKey == 0)
		//	nSrcIndex = s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );
		//else if( s_CUI_ID_FRAME_MAIN.nIndexHotKey == 1 )
		//	nSrcIndex = s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey2->GetItemIndex( pItemDrag );
		//else if( s_CUI_ID_FRAME_MAIN.nIndexHotKey == 2)
		//	nSrcIndex = s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey3->GetItemIndex( pItemDrag );

		UINT nSrcIndex = s_CUI_ID_FRAME_MAIN.GetHotKeyListImageIndex(pItemDrag);    //m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );

		SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex];											//sbw_add
		thePlayerRole.m_pHotKeyBag[nHotkeyIndex] = thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly];
        thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly] = stTemp;//ErrorUnsignedShortID;	
	}
    else if (pSender == s_CUI_ID_FRAME_NewSkillMain.GetListImage()/*m_pID_LISTIMG_Hotkey*/)
	{
		// 如果是被动技能
		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive || pSkill->sSkillCategory == ItemDefine::SCT_HeroPassive )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
			return true;
		}

		int nSkillIndex = -1;
		bool bHeroSkill = false;
		nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
		{
			nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
			if ( nSkillIndex == -1 )
				return true;

			bHeroSkill = true;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypeSkill;
		if ( bHeroSkill )
			pHotkey->ShortCut.BagType = BagTypeHeroSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();

		int nIndexDrag = s_CUI_ID_FRAME_NewSkillMain.GetListImageIndex(pItemDrag);//m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );
		s_CUI_ID_FRAME_NewSkillMain.RemoveSkill(nIndexDrag);
	}
    else if( s_CUI_ID_FRAME_SkillProduce.IsRecipeSkillList( pSender ) ) // 生活技能
    {
        ItemDefine::SItemSkill* pSkill = NULL; 
        pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1 );
        if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
            return true;
		}
        int nSkillIndex = -1;
        nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
        if ( nSkillIndex == -1 )
            return true;

        SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
        pHotkey->ShortCut.BagType = BagTypeSkill;
        pHotkey->ShortCut.BagIndex = nSkillIndex;
        pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
        s_CUI_ID_FRAME_SkillProduce.Refresh();
    }
	else if ( s_CUI_ID_FRAME_SKILL.IsSkillList( pSender )) // 如果是技能栏的东东
	{
		switch (pItemDrag->m_dwFlags)
		{
		case CUISkillMgr::eProfession:
		case CUISkillMgr::eXpSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
					return true;
				}
				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
					return true;

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
				pHotkey->ShortCut.BagType = BagTypeSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();

			}break;
		case CUISkillMgr::eMountSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeControl )
					return true;
				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_MountSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString( eText_Mount_NotActived ) );				
					return true;
				}

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
				pHotkey->ShortCut.BagType = BagTypeMountSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
			}break;
		case CUISkillMgr::ePetSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID(pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeControl )
					return true;

				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_PetSkillBag.GetSkillIndexById(pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString( eText_Mount_NotActived ) );				
					return true;
				}

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
				pHotkey->ShortCut.BagType = BagTypePetSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
			}
			break;
		case CUISkillMgr::eCommon:
			{
				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
				pHotkey->ShortCut.BagType = BagTypeActionUI;
				pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
                s_CUI_ID_FRAME_SKILL.RefreshCommon();
			}break;
		}
	}
	else if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag,pSender) ) // 背包
	{
		UINT nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
		if ( nPackIndex == -1 || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize()/*ITEM_BAGMAX */)
			return false;
		//物品加锁后禁止拖拉
		SCharItem stItems;
		thePlayerRole.m_bag.GetItem( nPackIndex, &stItems );
		if(stItems.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
			return false;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypePack;
		pHotkey->ShortCut.BagIndex = nPackIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	else if (pSender == s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_Exmain2)
	{
		int nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
		int nIndexSrc = s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_Exmain2->GetItemIndex(pItemDrag);

		SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nIndexSrc + nOffset];

		thePlayerRole.m_pHotKeyBag[nIndexSrc + nOffset] = thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		thePlayerRole.m_pHotKeyBag[nHotkeyIndex] = stTemp;
	}
	else if (s_CUI_ID_FRAME_Action.IsActionList( pSender ) ) // 表情动作
	{
		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypeExpressionAction;
		pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	else if (s_CUI_ID_FRAME_zhujiangbianshen.IsSkillList(pSender) || s_CUI_ID_FRAME_BaseProperty.IsHeroSkillList(pSender)) // 主将技能
	{
		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_HeroPassive )
		{
			return false;
		}
		int nSkillIndex = -1;
		nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
			return false;

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypeHeroSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	else if (pSender == s_CUI_ID_FRAME_SuAnimal.GetZhuDongListImage()
		|| s_CUI_ID_FRAME_SuAnimalMain.IsSubControlInFrame(pSender)) // 副将界面 或者 副将技能栏
	{
		// 如果是被动技能
		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pItemDrag->m_pkIconInfo->Id(), 1);
		if (pSkill == NULL || pSkill->sSkillCategory != ItemDefine::SCT_PetMasterManualControl)
			return false;

		int nSkillIndex = thePlayerRole.m_PetSkillBag.GetSkillIndexById(pItemDrag->m_pkIconInfo->Id());
		if (nSkillIndex == -1)
		{
			// 副将未出战
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Main_Display, theXmlString.GetString(eText_Mount_NotActived));
			return false;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypePetSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}

	s_CUI_ID_FRAME_Target.ForceUpdate();

	//属性HotKey
//	s_CUI_ID_FRAME_MAIN.RefeashHotKey();
//  RefeashHotNumber();

    // 更新快捷键给服务器
    thePlayerRole.SendHotKeyToServer();

	return false;
	unguard;
}
void CUI_ID_FRAME_Exmain::RefeashHotNumber()
{
	guardfunc;
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return ;
    }

	if( !m_pID_LISTIMG_Exmain )
		return;

    int nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
	m_pID_LISTIMG_Exmain->Clear();
	SMouseItem *pHotNumber = NULL;
	for(int i=0; i<More_exMainUIMax;  i++)
	{
		ControlIconDrag::S_ListImg stItem;
        pHotNumber = &thePlayerRole.m_pHotKeyBag[i];
		if ( pHotNumber->ShortCut.BagIndex >= 0 && pHotNumber->ShortCut.BagIndex < ITEM_BAGMAX )
		{
			pHotNumber->ItemData.itembaseinfo.value2 = 
                thePlayerRole.m_bag.m_pPackItem[pHotNumber->ShortCut.BagIndex].itembaseinfo.value2;

            if (pHotNumber->ShortCut.BagType == BagTypePack &&
				thePlayerRole.m_bag.m_pPackItem[pHotNumber->ShortCut.BagIndex].itembaseinfo.ustItemID ==
                InvalidLogicNumber)
            {
                pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
                for (int i  = 0; i < thePlayerRole.m_bag.GetNowBagSize(); ++i)
                {
                    if (thePlayerRole.m_bag.m_pPackItem[i].itembaseinfo.ustItemID ==
                        pHotNumber->ItemData.itembaseinfo.ustItemID)
                    {
                        pHotNumber->ShortCut.BagIndex = i;
                        break;
                    }
                }

                if (pHotNumber->ShortCut.BagIndex == ErrorUnsignedShortID)
                    pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
            }
		}

		bool bNullItem = false;
		if ( pHotNumber->ItemData.itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			switch( pHotNumber->ShortCut.BagType )
			{
			case BagTypeSkill:
				{
					int nSkillIndex = pHotNumber->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotNumber->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID )
					{
						pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					//stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
                      stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Enable, true, eTipFlag_SkillNoNextLevel ); //根据策划要求 技能一直要是亮的
					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex( nSkillIndex );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

                    if(i < nOffset  )
					   m_pID_LISTIMG_Exmain->SetItem( &stItem, i );	
                    else
                       m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
					break;
				}
			case BagTypeMountSkill:
				{
					int nSkillIndex = pHotNumber->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_MountSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotNumber->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID )
					{
						pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById( pSkill->ustSkillID );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

                    if(i < nOffset )
					    m_pID_LISTIMG_Exmain->SetItem( &stItem, i );
                     else
                        m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
					break;
				}
			case BagTypePetSkill:
				{
					int nSkillIndex = pHotNumber->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_PetSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotNumber->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID )
					{
						pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( pSkill->ustSkillID );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					if(i < nOffset)
						m_pID_LISTIMG_Exmain->SetItem(&stItem, i);
					else
						m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
				}
				break;
			case BagTypePack:
				{
					int nItemID = pHotNumber->ItemData.itembaseinfo.ustItemID;
					ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( nItemID );
					if ( !pItem )
					{
						bNullItem = true;
						break;
					}
					if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
					{
						bNullItem = true;
						break;
                    }

                    bool autoUseItem = false;
                    if ( pItem->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
                    {
                        ItemDefine::SItemRestore* itemRestore = static_cast<ItemDefine::SItemRestore*>(pItem);
                        autoUseItem = itemRestore->bHPAuto || itemRestore->bMPAuto || itemRestore->bAutoRelive;
                    }

                    if ( pItem->IsExclusive() && !autoUseItem )
					{
						int nIndex = thePlayerRole.m_bag.GetItemIndex( &pHotNumber->ItemData );
						if ( nIndex != -1 )
						{
							pHotNumber->ShortCut.BagIndex = nIndex;
							stItem.SetData( &pHotNumber->ItemData );

							AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
								(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
							stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

							//
							RestoreColdDown* pRestoreCoolDown = NULL;
							pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
							DWORD dwStartTiem,dwPeriod;
							if( pRestoreCoolDown->GetTime( pHotNumber->ItemData.itembaseinfo.ustItemID,
								&dwStartTiem, &dwPeriod ) == true )
							{
								stItem.SetTime( dwStartTiem,dwPeriod );
							}
							//

                            if(i < nOffset)
							   m_pID_LISTIMG_Exmain->SetItem( &stItem, i );
                            else
                               m_pID_LISTIMG_Exmain2->SetItem(&stItem, i - nOffset);
						}
					}
					else
					{
						int nCount = thePlayerRole.m_bag.GetItemCount( pHotNumber->ItemData.itembaseinfo.ustItemID );
						int nIndex = thePlayerRole.m_bag.GetItemIndexById( pHotNumber->ItemData.itembaseinfo.ustItemID );
						if ( nCount > 0 )
						{
							pHotNumber->ShortCut.BagIndex = nIndex;
							pHotNumber->ItemData.itembaseinfo.ustItemCount = nCount;

							stItem.SetData( &pHotNumber->ItemData );
							AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
								(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
							stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
							//
							RestoreColdDown* pRestoreCoolDown = NULL;
							pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
							DWORD dwStartTiem,dwPeriod;
							if( pRestoreCoolDown->GetTime( pHotNumber->ItemData.itembaseinfo.ustItemID,
								&dwStartTiem, &dwPeriod ) == true )
							{
								stItem.SetTime( dwStartTiem,dwPeriod );
							}
							//
                            if(i < nOffset)
							   m_pID_LISTIMG_Exmain->SetItem( &stItem, i );
                            else
                               m_pID_LISTIMG_Exmain2->SetItem(&stItem, i - nOffset);
						}
					}
					break;
				}

			case BagTypeFunction:
				{
					stItem.SetData( &pHotNumber->ItemData );
					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

                    if(i < nOffset)
					   m_pID_LISTIMG_Exmain->SetItem( &stItem, i );
                    else
                       m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
				}
				break;
			case BagTypeActionUI:
				{
					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pHotNumber->ItemData.itembaseinfo.ustItemID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					eIconDrawState eEnable = eIcon_Enable;
                    BOOL bInWater = FALSE;
                    if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsInWater() )
                        bInWater = TRUE;
					if ((CUI_ID_FRAME_BaseProperty::TYPE_SITDWON_ACTION == pHotNumber->ItemData.itembaseinfo.ustItemID 
						/*|| CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pHotNumber->ItemData.itembaseinfo.ustItemID*/) &&
						(thePlayerRole.IsFighting() || bInWater) )
						eEnable = eIcon_Disable;

					if ( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pHotNumber->ItemData.itembaseinfo.ustItemID &&
						(!s_CUI_ID_FRAME_Pet.IsActivedPet() || bInWater) )
						eEnable = eIcon_Disable;

					if (pHotNumber->ItemData.itembaseinfo.ustItemID >= CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK &&
						pHotNumber->ItemData.itembaseinfo.ustItemID <= CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND &&
						theHeroGame.GetPlayerMgr()->GetMe() &&
						!theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
					{
						eEnable = eIcon_Disable;
					}


					if (pHotNumber->ItemData.itembaseinfo.ustItemID > 1000)
					{
						SCharSkill *pSkill = 0;
						pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pHotNumber->ItemData.itembaseinfo.ustItemID );
						if ( !pSkill ||
							pSkill->ustSkillID == InvalidLogicNumber ||
							pHotNumber->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
						{
							pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
							pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
							bNullItem = true;
							break;
						}

						stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);

						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( pSkill->ustSkillID );
						if ( pTime )
						{
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
						}
					}
					else
					{
						stItem.SetData( &pHotNumber->ItemData, eEnable );
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);
					}

					if (pHotNumber->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}
					else if (pHotNumber->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2 );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
						continue; //lyh-- 防卡回城
					}
					else if (pHotNumber->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_MOUNT)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT_SKILL_ID );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );

						if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting())
							stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
					}

					if (s_CUI_ID_FRAME_BaseProperty.GetPetAIType() == pHotNumber->ItemData.itembaseinfo.ustItemID)
					{
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
					}

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
                    if(i < nOffset)
					    m_pID_LISTIMG_Exmain->SetItem( &stItem, i  );
                    else
                        m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
					break;
				}
			case BagTypeExpressionAction:
				{
					stItem.SetData( &pHotNumber->ItemData );
					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
					if(i < nOffset)
						m_pID_LISTIMG_Exmain->SetItem( &stItem, i  );
 					else
 						m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
				}
				break;
			/**********************************************************************/
			/* author:liaojie                                                     */
			/* Desc:  主将技能背包                                                */
			/**********************************************************************/
			case BagTypeHeroSkill:
				{
					int nSkillIndex = pHotNumber->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_HeroSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotNumber->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID )
					{
						pHotNumber->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotNumber->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_HeroSkillBag.GetColdTimeByIndex( nSkillIndex );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					if(i < nOffset  )
						m_pID_LISTIMG_Exmain->SetItem( &stItem, i );	
					else
						m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
					break;
				}
			default:
				bNullItem = true;
				break;
			}
		}
		else
			bNullItem = true;

		if (pHotNumber->ItemData.itembaseinfo.ustItemID == ErrorUnsignedShortID)
		{
			bNullItem = true;
		}

		if( bNullItem )
		{
			stItem.Clear();

			AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
				(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + i);
			stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

            if(i < nOffset)
			   m_pID_LISTIMG_Exmain->SetItem( &stItem, i );
            else
               m_pID_LISTIMG_Exmain2->SetItem(&stItem,i - nOffset);
		}
	}	
	unguard;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_ExmainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_ExmainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

	unsigned int nIndex = m_pID_LISTIMG_Exmain->GetItemIndex( pItem );
	if ( nIndex >= More_exMainUIMax )
		return false;
	//int VK_1 = VK_F1;
	//UIMain_MsgProc( WM_KEYUP, VK_1+nIndex, 255, false );

	int nKeyIndex = nIndex;
	s_CUI_ID_FRAME_MAIN.ClickHotkey(nKeyIndex);
	return false;
	unguard;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_ExmainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

	unsigned int nIndex = m_pID_LISTIMG_Exmain->GetItemIndex( pItem );
	if ( nIndex >= More_exMainUIMax )
		return false;

	int nKeyIndex = nIndex;
	s_CUI_ID_FRAME_MAIN.ClickHotkey( nKeyIndex, pItem->m_eEnable );
	return false;
	unguard;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_Exmain2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                         ControlIconDrag::S_ListImg* pItemDrag,
                                                         ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

    if ( pItemDrag->IsNull()|| !pItemSrc )
        return false;
    
    UINT nHotkeyIndex = m_pID_LISTIMG_Exmain2->GetItemIndex( pItemSrc );
    if ( nHotkeyIndex >= More_exMainUIMax )
        return false;

    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
    if ( !pItem )
        return false;

    if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
        return false;

    //这里这么写的原因是，原来是一个list现在变成两个list,因此需要加上偏移量（即原来的list的Size），杨晓勇[策划]
    int nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
    if ( pSender == pMe )
    {
        UINT nSrcIndex = m_pID_LISTIMG_Exmain2->GetItemIndex( pItemDrag );
        SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
        thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset] = thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset];
        thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset] = stTemp;
    }
    else if( pSender == s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_Exmain )
    {
        UINT nSrcIndex = m_pID_LISTIMG_Exmain->GetItemIndex(pItemDrag);

        SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
        thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset] = thePlayerRole.m_pHotKeyBag[nSrcIndex];
        thePlayerRole.m_pHotKeyBag[nSrcIndex] = stTemp;
    }
    else if( pSender == s_CUI_ID_FRAME_MAIN.GetHotKeyListImage()/*m_pID_LISTIMG_Hotkey*/ )
    {
        UINT nSrcIndex = s_CUI_ID_FRAME_MAIN.GetHotKeyListImageIndex(pItemDrag);//m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );

        SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
        thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset] = thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly];
        thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly] = stTemp;	
    }
    else if (pSender == s_CUI_ID_FRAME_NewSkillMain.GetListImage()/*m_pID_LISTIMG_Hotkey*/)
    {
        // 如果是被动技能
        ItemDefine::SItemSkill* pSkill = NULL; 
        pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
        if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive || pSkill->sSkillCategory == ItemDefine::SCT_HeroPassive )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
            return true;
		}
        int nSkillIndex = -1;
		bool bHeroSkill = false;

        nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
		{
			nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
			if ( nSkillIndex == -1 )
				return true;

			bHeroSkill = true;
		}

        SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
        pHotkey->ShortCut.BagType = BagTypeSkill;
		if ( bHeroSkill )
			pHotkey->ShortCut.BagType = BagTypeHeroSkill;
        pHotkey->ShortCut.BagIndex = nSkillIndex;
        pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();

        int nIndexDrag = s_CUI_ID_FRAME_NewSkillMain.GetListImageIndex(pItemDrag);//m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );
        s_CUI_ID_FRAME_NewSkillMain.RemoveSkill(nIndexDrag);
    }
    else if (s_CUI_ID_FRAME_SKILL.IsSkillList( pSender ))
    {
        switch (pItemDrag->m_dwFlags)
        {
        case CUISkillMgr::eProfession:
            {
                // 如果是被动技能
                ItemDefine::SItemSkill* pSkill = NULL; 
                pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
                if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
                    return true;

                int nSkillIndex = -1;
                nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
                if ( nSkillIndex == -1 )
                    return true;

                SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
                pHotkey->ShortCut.BagType = BagTypeSkill;
                pHotkey->ShortCut.BagIndex = nSkillIndex;
                pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
            }
            break;
        case CUISkillMgr::eMountSkill:
            {
                // 如果是被动技能
                ItemDefine::SItemSkill* pSkill = NULL; 
                pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
                if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeControl )
                    return true;

                int nSkillIndex = -1;
                nSkillIndex = thePlayerRole.m_MountSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
                if ( nSkillIndex == -1 )
                {
                    //GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_Mount_NotActived ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );				
                    return true;
                }

                SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
                pHotkey->ShortCut.BagType = BagTypeMountSkill;
                pHotkey->ShortCut.BagIndex = nSkillIndex;
                pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
            }
            break;
        case CUISkillMgr::eCommon:
            {
                SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
                pHotkey->ShortCut.BagType = BagTypeActionUI;
                pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
                pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
            }
            break;
        }
    }
    else if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
    {
        UINT nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
        if ( nPackIndex == -1 || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize())
            return false;

        //物品加锁后禁止拖拉
        SCharItem stItems;
        thePlayerRole.m_bag.GetItem( nPackIndex, &stItems );
        if(stItems.storageinfo.bIsLocked)
        {
            s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
            return false;
        }

        SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
        pHotkey->ShortCut.BagType = BagTypePack;
        pHotkey->ShortCut.BagIndex = nPackIndex;
        pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
    }
	// 表情动作
	else if( s_CUI_ID_FRAME_Action.IsActionList( pSender ) )
	{
		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + nOffset];
		pHotkey->ShortCut.BagType = BagTypeExpressionAction;
		pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}

	//主将技能
	else if (s_CUI_ID_FRAME_zhujiangbianshen.IsSkillList(pSender) || s_CUI_ID_FRAME_BaseProperty.IsHeroSkillList(pSender))
	{
		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill)
		{
			return false;
		}
		int nSkillIndex = -1;
		nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
			return false;

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex];
		pHotkey->ShortCut.BagType = BagTypeHeroSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}

    s_CUI_ID_FRAME_MAIN.RefeashHotKey();
    RefeashHotNumber();
    // 更新快捷键给服务器
    thePlayerRole.SendHotKeyToServer();

    return false;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_Exmain2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_Exmain2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

    unsigned int nIndex = m_pID_LISTIMG_Exmain2->GetItemIndex( pItem );
    unsigned int nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
    if ( nIndex + nOffset>= More_exMainUIMax )
        return false;

    int nKeyIndex = nIndex + nOffset;
    s_CUI_ID_FRAME_MAIN.ClickHotkey(nKeyIndex);
    return false;
}

bool CUI_ID_FRAME_Exmain::ID_LISTIMG_Exmain2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_Exmain)
    {
        assert(false&&"ui error");
        return false;
    }

    unsigned int nIndex = m_pID_LISTIMG_Exmain2->GetItemIndex( pItem );
    unsigned int nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
    if ( nIndex + nOffset >= More_exMainUIMax )
        return false;

    int nKeyIndex = nIndex + nOffset;
    s_CUI_ID_FRAME_MAIN.ClickHotkey(nKeyIndex);
    return false;
}

void CUI_ID_FRAME_Exmain::InitializeAtEnterWorld()
{
     if( !m_pID_FRAME_Exmain )
         return;

     m_pID_FRAME_Exmain->GetRealRect( &_rc );
     //m_pID_FRAME_Exmain->SetVisable(false);
     m_pID_LISTIMG_Exmain->ShowPressEffect(true);
     m_pID_LISTIMG_Exmain->SetShowAllInfo( true );
     m_pID_LISTIMG_Exmain->SetDisableCanbePick( true );
     m_pID_LISTIMG_Exmain->SetOnlyShowItemIcon(true);
     m_pID_LISTIMG_Exmain->SetDelayTime( g_ControlListImageShortDelayTime );

	 m_pID_LISTIMG_Exmain2->ShowPressEffect(true);
	 m_pID_LISTIMG_Exmain2->SetShowAllInfo( true );
	 m_pID_LISTIMG_Exmain2->SetDisableCanbePick( true );
	 m_pID_LISTIMG_Exmain2->SetOnlyShowItemIcon(true);
	 m_pID_LISTIMG_Exmain2->SetDelayTime( g_ControlListImageShortDelayTime );

     m_pID_FRAME_Exmain->SetVisable(false);
     m_pID_FRAME_Exmain->SetMsgHoldup(false);

     //m_pID_PICTURE_Lock->setShowTip( true );

     // modifed, jiayi, [2009.5.23]

     if (s_CUI_ID_FRAME_GameSetup.GetShowHotKey()/*.bShowHotkey*/)
     {
         m_pID_FRAME_Exmain->SetVisable( true );

         //s_CUI_ID_FRAME_Exmain.m_pID_FRAME_Exmain->SetPos( s_CUI_ID_FRAME_Exmain._rc.left, s_CUI_ID_FRAME_Exmain._rc.top );
     }
     //m_pID_FRAME_Exmain->SetMsgProcFun( UIMain_MsgProc );

     bool bLock = static_cast<bool>(GameSetting::Instance()->GetLevel(GameSetting::eSSC_SKILLLOCK));
     m_pID_LISTIMG_Exmain->SetEnableDrag( !bLock );
     // m_pID_LISTIMG_exmain2->SetEnableDrag(bLock);
//      s_CUI_ID_FRAME_MAIN.SetHotKeyListImageDrag(bLock);//m_pID_LISTIMG_Hotkey->SetEnableDrag( bLock );
     // m_pID_CHECKBOX_Lock->SetCheck(!bLock);

}

// 装载UI
bool CUI_ID_FRAME_Exmain::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\exmain.meui", true , UI_Render_LayerSecond);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\exmain.UI]失败")
			return false;
	}
// 	else if ( dwResult != 1511/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\exmain.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_Exmain::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_Exmain, s_CUI_ID_FRAME_ExmainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Exmain, s_CUI_ID_FRAME_ExmainOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_ExmainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_ExmainOnIconLDBClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_ExmainOnIconRButtonUp );
	theUiManager.OnIconButtonClick( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_ExmainOnIconButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_Exmain2OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_Exmain2OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_Exmain2OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_Exmain2OnIconRButtonUp );

	theUiManager.OnIconDisableDragOn( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_HotkyeOnIconDisableDragOn );
	theUiManager.OnIconDisableDragOn( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_HotkyeOnIconDisableDragOn );
	theUiManager.OnIconDisableDragOut( ID_FRAME_Exmain, ID_LISTIMG_Exmain, s_CUI_ID_FRAME_ExmainID_LISTIMG_HotkyeOnIconDisableDragOut );
	theUiManager.OnIconDisableDragOut( ID_FRAME_Exmain, ID_LISTIMG_Exmain2, s_CUI_ID_FRAME_ExmainID_LISTIMG_HotkyeOnIconDisableDragOut );


	m_pID_FRAME_Exmain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Exmain );
	m_pID_LISTIMG_Exmain = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Exmain, ID_LISTIMG_Exmain );
 	m_pID_LISTIMG_Exmain2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_Exmain, ID_LISTIMG_Exmain2 );	
    assert( m_pID_FRAME_Exmain );
	assert( m_pID_LISTIMG_Exmain );
	assert( m_pID_LISTIMG_Exmain2);

	m_pID_LISTIMG_Exmain->SetShiftLBClickFun( IconOnShiftLBClick );
    _SetVisable( false );
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_Exmain::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_Exmain = NULL;
	m_pID_LISTIMG_Exmain = NULL;
    m_pID_LISTIMG_Exmain2 = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\exmain.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_Exmain::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_Exmain )
		return false;
	return m_pID_FRAME_Exmain->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_Exmain::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_Exmain )
		return;
	m_pID_FRAME_Exmain->SetVisable( bVisable );
	unguard;
}
//bool CUI_ID_FRAME_Exmain::UIMain_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
//{
//	guardfunc;
//	switch(msg)
//	{
//	case WM_MOUSEMOVE:
//		{
//			int i = 0;
//			++i;
//		}
//		break;
//	}
//	return false;
//	unguard;
//}

void CUI_ID_FRAME_Exmain::UpdateIconInfo()
{
	POINT pos;
	RECT rect;
	GetCursorPos(&pos);
	GetWindowRect(g_hWnd, &rect);

	if(!theApp->IsFullScreen())
	{
		pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
		pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
	}

	POINT ptMouseOnSel;
	if ( m_pID_LISTIMG_Exmain->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true
		||m_pID_LISTIMG_Exmain2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
	{
		ControlListImage* pID_LISTIMG_EXMAIN;
		//位置偏移
		int nOffset = 0;
		if(m_pID_LISTIMG_Exmain->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
		{
			pID_LISTIMG_EXMAIN = m_pID_LISTIMG_Exmain;
		}
		else if(m_pID_LISTIMG_Exmain2->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true)
		{
			pID_LISTIMG_EXMAIN = m_pID_LISTIMG_Exmain2;
			nOffset = m_pID_LISTIMG_Exmain->GetItemCnt();
		}
		else
		{
			assert(false);
		}
		// added, jiayi, [2009/10/20]
		// 这里tip的位置取当前item的左边界
		// 这样就可以固定tip位置
		RECT rcItem;
		pID_LISTIMG_EXMAIN->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += pID_LISTIMG_EXMAIN->GetItemWidth() / 2;
		rcItem.top += pID_LISTIMG_EXMAIN->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = pID_LISTIMG_EXMAIN->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if( !pItem )
		{
			assert(false);
			return;
		}

		int nSrcIndex = pID_LISTIMG_EXMAIN->GetItemIndex( pItem );

		CItemBag2* pBag = NULL;
		//switch( thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset].ShortCut.BagType )
		//{
		//case BT_NormalItemBag:
		//	pBag = &thePlayerRole.m_bag;
		//	break;
		//case BT_MaterialBag:
		//	pBag = &thePlayerRole.m_bagMaterial;
		//	break;
		//case BT_TaskBag:
		//	pBag = &thePlayerRole.m_bagTask;
		//	break;
		//}

		if(pBag)
		{
			//更新图标信息
			SCharItem bagItem;
			if(pBag->GetItem( thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset].ShortCut.BagIndex , &bagItem ))
			{
				ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID( bagItem.itembaseinfo.ustItemID );
				if ( !pItemCommon )
					return;
				if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					return;
                }

				int nCount = thePlayerRole.m_bag.GetItemCount( bagItem.itembaseinfo.ustItemID );

				bagItem.itembaseinfo.ustItemCount = nCount;

				pItem->SetData(&bagItem);

				AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
					(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1 + nSrcIndex + nOffset );

				pItem->m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

				pID_LISTIMG_EXMAIN->SetItem( pItem, nSrcIndex + nOffset );
			}
		}
	}
}

void CUI_ID_FRAME_Exmain::SetCheckBoxLock( bool b )
{
// 	if(m_pID_CHECKBOX_Lock)
// 		m_pID_CHECKBOX_Lock->SetCheck(b);
// 	else
// 		assert(false&&"ui error");
}

bool CUI_ID_FRAME_Exmain::PtInOnlyFrame( int x,int y )
{
	if(m_pID_FRAME_Exmain)
		return m_pID_FRAME_Exmain->PtInOnlyFrame( x,y );
	else
		assert(false&&"ui error");

	return false;
}

ControlListImage* CUI_ID_FRAME_Exmain::GetpIDListImg()
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain;
	else
		assert(false&&"ui error");

	return NULL;
}

int CUI_ID_FRAME_Exmain::GetItemIndex1( const ControlListImage::S_ListImg *pItem )
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain->GetItemIndex( pItem );
	else
		assert(false&&"ui error");

	return 0;
}

int CUI_ID_FRAME_Exmain::GetItemIndex2( const ControlListImage::S_ListImg *pItem )
{
 	if(m_pID_LISTIMG_Exmain2)
 		return m_pID_LISTIMG_Exmain2->GetItemIndex( pItem );
 	else
 		assert(false&&"ui error");

	return 0;
}

bool CUI_ID_FRAME_Exmain::GetOnlyShowItemIcon1()
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain->GetOnlyShowItemIcon();
	else
		assert(false&&"ui error");

	return false;
}

bool CUI_ID_FRAME_Exmain::GetOnlyShowItemIcon2()
{
 	if(m_pID_LISTIMG_Exmain2)
 		return m_pID_LISTIMG_Exmain2->GetOnlyShowItemIcon();
 	else
 		assert(false&&"ui error");

	return false;
}

void CUI_ID_FRAME_Exmain::SetOnlyShowItemIcon1( bool b )
{
	if(m_pID_LISTIMG_Exmain)
	{
		m_pID_LISTIMG_Exmain->SetOnlyShowItemIcon( b );
		m_pID_LISTIMG_Exmain->GetFrameFather()->SetRedraw();
	}
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_Exmain::SetOnlyShowItemIcon2( bool b )
{
 	if(m_pID_LISTIMG_Exmain2)
 		m_pID_LISTIMG_Exmain2->SetOnlyShowItemIcon( b );
 	else
 		assert(false&&"ui error");
}

ControlListImage* CUI_ID_FRAME_Exmain::GetpIDListImageExmain1()
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain;
	else
		assert(false&&"ui error");

	return NULL;
}

ControlListImage* CUI_ID_FRAME_Exmain::GetpIDListImageExmain2()
{
 	if(m_pID_LISTIMG_Exmain2)
 		return m_pID_LISTIMG_Exmain2;
 	else
 		assert(false&&"ui error");

	return NULL;
}

bool CUI_ID_FRAME_Exmain::IsListImgExmain1Visable()
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain->IsVisable();
	else
		assert(false&&"ui error");

	return false;
}

bool CUI_ID_FRAME_Exmain::IsListImgExmain2Visable()
{
 	if(m_pID_LISTIMG_Exmain2)
 		return m_pID_LISTIMG_Exmain2->IsVisable();
 	else
 		assert(false&&"ui error");
	
	return false;
}

int CUI_ID_FRAME_Exmain::GetItemCnt1()
{
	if(m_pID_LISTIMG_Exmain)
		return m_pID_LISTIMG_Exmain->GetItemCnt();
	else
		assert(false&&"ui error");
	
	return 0;
}
int CUI_ID_FRAME_Exmain::GetItemCnt2()
{
 	if(m_pID_LISTIMG_Exmain2)
 		return m_pID_LISTIMG_Exmain2->IsVisable();
 	else
 		assert(false&&"ui error");
	
	return 0;
}

void CUI_ID_FRAME_Exmain::SetPressItemIndex1( int i )
{
	if(m_pID_LISTIMG_Exmain)
		m_pID_LISTIMG_Exmain->SetPressItemIndex(i);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_Exmain::SetPressItemIndex2( int i )
{
 	if(m_pID_LISTIMG_Exmain2)
 		m_pID_LISTIMG_Exmain2->SetPressItemIndex(i);
 	else
 		assert(false&&"ui error");
}

void CUI_ID_FRAME_Exmain::SetPos(int x,int y)
{
	if(m_pID_FRAME_Exmain)
		m_pID_FRAME_Exmain->SetPos(x,y);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_Exmain::SetPos1(int x,int y)
{
	if(m_pID_LISTIMG_Exmain)
		m_pID_LISTIMG_Exmain->SetPos(x,y);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_Exmain::SetPos2(int x,int y)
{
 	if(m_pID_LISTIMG_Exmain2)
 		m_pID_LISTIMG_Exmain2->SetPos(x,y);
 	else
 		assert(false&&"ui error");
}

bool CUI_ID_FRAME_Exmain::SetSkillAutoToListImage(SCharSkill* pSkill_)
{
	if (!pSkill_)
	{
		return false;
	}

	int nNullPlace = m_pID_LISTIMG_Exmain->GetNullItem();
	if (nNullPlace == -1)
	{
		return false;
	}

	ItemDefine::SItemSkill* pSkill = NULL; 
	pSkill = GettheItemDetail().GetSkillByID(pSkill_->ustSkillID, pSkill_->stSkillLevel);
	if ( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
	{
		return false;
	}
		
	int nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById(pSkill->ustItemID);
	if (nSkillIndex == -1)
	{
		return false;
	}

	SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nNullPlace];
	pHotkey->ShortCut.BagType = BagTypeSkill;
	pHotkey->ShortCut.BagIndex = nSkillIndex;
	pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustItemID;

	RefeashHotNumber();
	thePlayerRole.SendHotKeyToServer();

	return true;
}

void CUI_ID_FRAME_Exmain::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	assert(pItem != NULL);

	SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
	//assert(IsValidXinFaSkill(pCharSkill));
	if(NULL == pCharSkill)
	{
		pCharSkill = thePlayerRole.m_HeroSkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
		if (NULL == pCharSkill)
		{
			return;
		}
	}

	ItemDefine::SItemSkill* pItemSKill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
	if ( pItemSKill == NULL )
	{
		return;
	}

	CommonChatFrame::GetActiveChatFrame()->addHyberTextEx( pItemSKill->GetItemName(), MsgChat::HYBERTYPE_SKILL,  pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
}
