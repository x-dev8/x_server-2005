/********************************************************************
Created by UIEditor.exe
FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\EquipCopy.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "EquipCopy.h"
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
#include "PackItemEnableManager.h"

CUI_ID_FRAME_EquipCopy s_CUI_ID_FRAME_EquipCopy;
MAP_FRAME_RUN( s_CUI_ID_FRAME_EquipCopy, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_EquipCopy, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_BUTTON_CLOSEOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_BUTTON_OkOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip1OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip1OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip1OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip1OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_EquipCopy, ID_LISTIMG_Equip2OnIconRButtonUp )
CUI_ID_FRAME_EquipCopy::CUI_ID_FRAME_EquipCopy()
{
    // Member
    m_pID_FRAME_EquipEvolve = NULL;
    m_pID_BUTTON_CLOSE = NULL;
    m_pID_TEXT_Money = NULL;
    m_pID_LISTIMG_Material = NULL;
    m_pID_BUTTON_Cancel = NULL;
    m_pID_BUTTON_Ok = NULL;
    m_pID_TEXT_Tip2 = NULL;
    m_pID_LISTIMG_Equip = NULL;
    m_pID_PICTURE_StarEffect = NULL;
    m_pID_TEXT_Tip1 = NULL;
    m_pID_LISTIMG_Equip2 = NULL;
    m_pID_TEXT_TipAllDone = NULL;
    m_pID_PICTURE_Begin = NULL;
    m_pID_PICTURE_Begin1 = NULL;
    m_pID_PICTURE_BeginCross = NULL;

    ResetUIObjects();

}
// Frame
bool CUI_ID_FRAME_EquipCopy::OnFrameRun()
{
    if (!OnDirty())
    {
        return true;
    }
    return true;
}
bool CUI_ID_FRAME_EquipCopy::OnFrameRender()
{
    OnRender();
    return true;
}
// Button
bool CUI_ID_FRAME_EquipCopy::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
    SetVisable( false );
    return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                             ControlIconDrag::S_ListImg* pItemDrag,
                                                             ControlIconDrag::S_ListImg* pItemSrc )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
// Button
bool CUI_ID_FRAME_EquipCopy::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    SetVisable( false );
    return true;
}
// Button
bool CUI_ID_FRAME_EquipCopy::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
    OnOkClick();
    return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip1OnIconDragOn( ControlObject* pSender, ControlObject* pObject,
                                                           ControlIconDrag::S_ListImg* pItemDrag,
                                                           ControlIconDrag::S_ListImg* pItemSrc )
{
    SCharItem* psItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
    if (!psItem)
    {
        return false;
    }
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
    if (!pMe)
    {
        return false;
    }
    if (pMe->GetLevel() < gCfg.m_nMinEquipCopyPlayerLevel)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_PlayerLevel) );
        return false;
    }
    int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
    if(nLevel < gCfg.m_nMinEquipCopyItemLevel)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_ItemLevel) );
        return false;
    }
    if (psItem->equipdata.quality < ItemDefine::EQL_Purple)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_PurpleItem) );
        return false;
    }
    if (m_stTargetItemIndex != -1)
    {
        ControlIconDrag::S_ListImg* pTargetImg = m_pID_LISTIMG_Equip2->GetItemByIndex(0);
        if (!IsSamePart(pItemDrag,pTargetImg))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_SamePart) );
            return false;
        }		
        if (m_CrossCopy)
        {
            if(!IsInCrossLevel(pItemDrag,pTargetImg))
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_CrossMaintain_Level) );
                return false;
            }
        }
        else if (!IsSameLevel(pItemDrag,pTargetImg))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_NotSameLevel) );
            return false;
        }
    }
    OnEquipDragOn(pItemDrag,pSender);
    SetDirty( true );
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    EquipEvolveUI::ClearEquip();
    return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip2OnIconDragOn( ControlObject* pSender, ControlObject* pObject,
                                                           ControlIconDrag::S_ListImg* pItemDrag,
                                                           ControlIconDrag::S_ListImg* pItemSrc )
{
    SCharItem* psItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
    if (!psItem)
    {
        return false;
    }
    CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
    if (!pMe)
    {
        return false;
    }
    if (pMe->GetLevel() < gCfg.m_nMinEquipCopyPlayerLevel)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_PlayerLevel) );
        return false;
    }
    int nLevel = GetItemLevel(pItemDrag->m_pkIconInfo->GetItemId());
    if(nLevel < gCfg.m_nMinEquipCopyItemLevel)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_ItemLevel) );
        return false;
    }
    if (psItem->equipdata.quality < ItemDefine::EQL_Golden)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_GoldItem) );
        return false;
    }
    if (m_stEquipBagIndex != -1)
    {
        ControlIconDrag::S_ListImg* pEquipImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
        if (!IsSamePart(pEquipImg,pItemDrag))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_SamePart) );
            return false;
        }		
        if (m_CrossCopy)
        {
            if(!IsInCrossLevel(pEquipImg,pItemDrag))
            {
                CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_CrossMaintain_Level) );
                return false;
            }
        }
        else if (!IsSameLevel(pEquipImg,pItemDrag))
        {
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Maintain_Failed, theXmlString.GetString(eWarning_Maintain_NotSameLevel) );
            return false;
        }
    }
    ClearTargetEquip();
    OnDirty();	
    ControlListImage* pImageSender = dynamic_cast<ControlListImage*>( pSender );
    if( !pImageSender )
        return false;
    // 包裹里
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pImageSender) )
    {			
        m_stTargetItemIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );

        SCharItem item;
        if(m_stTargetItemIndex != -1 && thePlayerRole.m_bag.GetItem(m_stTargetItemIndex,&item))
            m_stTargetItemGuid = item.itembaseinfo.nOnlyInt;
        else
            m_stTargetItemGuid = 0;
    }
    else
    {
        return false;
    }		
    m_bTargetItemEnable = false;			
    RefreshEquipInfo();
    SetDirty( true );
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_EquipCopy::ID_LISTIMG_Equip2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    ClearTargetEquip();
    return false;
}

// 装载UI
bool CUI_ID_FRAME_EquipCopy::_LoadUI()
{
    DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\EquipCopy.MEUI" , false, UI_Render_LayerThree);
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[Data\\UI\\EquipCopy.MEUI]失败")
            return false;
    }
    return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_EquipCopy::DoControlConnect()
{
    theUiManager.OnFrameRun( ID_FRAME_EquipCopy, s_CUI_ID_FRAME_EquipCopyOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_EquipCopy, s_CUI_ID_FRAME_EquipCopyOnFrameRender );
    theUiManager.OnButtonClick( ID_FRAME_EquipCopy, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_EquipCopyID_BUTTON_CLOSEOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_EquipCopy, ID_LISTIMG_Material, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_MaterialOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_EquipCopy, ID_LISTIMG_Material, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_MaterialOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_EquipCopy, ID_LISTIMG_Material, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_MaterialOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_EquipCopy, ID_LISTIMG_Material, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_MaterialOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_EquipCopy, ID_BUTTON_Cancel, s_CUI_ID_FRAME_EquipCopyID_BUTTON_CancelOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_EquipCopy, ID_BUTTON_Ok, s_CUI_ID_FRAME_EquipCopyID_BUTTON_OkOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_EquipCopy, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip1OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_EquipCopy, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip1OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_EquipCopy, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip1OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_EquipCopy, ID_LISTIMG_Equip1, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip1OnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_EquipCopy, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip2OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_EquipCopy, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip2OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_EquipCopy, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip2OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_EquipCopy, ID_LISTIMG_Equip2, s_CUI_ID_FRAME_EquipCopyID_LISTIMG_Equip2OnIconRButtonUp );

    m_pID_FRAME_EquipEvolve = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_EquipCopy );
    m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_BUTTON_CLOSE );
    m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_TEXT_Money );
    m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_LISTIMG_Material );
    m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_BUTTON_Cancel );
    m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_BUTTON_Ok );
    m_pID_TEXT_Tip2 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_TEXT_Tip2 );
    m_pID_LISTIMG_Equip = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_LISTIMG_Equip1 );
    m_pID_PICTURE_StarEffect = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_PICTURE_StarEffect );
    m_pID_TEXT_Tip1 = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_TEXT_Tip1 );
    m_pID_LISTIMG_Equip2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_LISTIMG_Equip2 );
    m_pID_TEXT_TipAllDone = (ControlText*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_TEXT_TipAllDone );
    m_pID_PICTURE_Begin1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_PICTURE_Begin );
    m_pID_PICTURE_BeginCross = (ControlPicture*)theUiManager.FindControl( ID_FRAME_EquipCopy, ID_PICTURE_Begin2 );
    assert( m_pID_FRAME_EquipEvolve );
    assert( m_pID_BUTTON_CLOSE );
    assert( m_pID_TEXT_Money );
    assert( m_pID_LISTIMG_Material );
    assert( m_pID_BUTTON_Cancel );
    assert( m_pID_BUTTON_Ok );
    assert( m_pID_TEXT_Tip2 );
    assert( m_pID_LISTIMG_Equip );
    assert( m_pID_PICTURE_StarEffect );
    assert( m_pID_TEXT_Tip1 );
    assert( m_pID_LISTIMG_Equip2 );
    assert( m_pID_TEXT_TipAllDone );
    m_pID_TEXT_TipAllDone->SetVisable(false);
    m_pID_FRAME_EquipEvolve->SetOnVisibleChangedFun( OnVisibleChange );
    EquipEvolveIntialize();
    return true;
}
// 卸载UI
bool CUI_ID_FRAME_EquipCopy::_UnLoadUI()
{
    ResetEquipEvolve();
    m_pID_FRAME_EquipEvolve = NULL;
    return theUiManager.RemoveFrame( "Data\\UI\\EquipCopy.MEUI" );
}

void CUI_ID_FRAME_EquipCopy::SetEquipCopyVisable( const bool bVisable,bool isCross )
{
    m_CrossCopy = isCross;
    SetVisable(bVisable);
    if (bVisable)
    {
        if (m_CrossCopy)
        {
            m_pID_PICTURE_Begin = m_pID_PICTURE_BeginCross;
            m_pID_PICTURE_Begin1->SetVisable(false);
            m_EvolveType = MsgEquipEvolve::ET_MaintainCross;
            m_MaterialType = ItemDefine::ematerial_maintacross;
        }
        else
        {
            m_pID_PICTURE_Begin = m_pID_PICTURE_Begin1;
            m_pID_PICTURE_BeginCross->SetVisable(false);
            m_EvolveType = MsgEquipEvolve::ET_Maintain;
            m_MaterialType = ItemDefine::ematerial_maintain;
        }
        m_pID_PICTURE_Begin->SetVisable(true);
    }		
}

void CUI_ID_FRAME_EquipCopy::OnVisibleChange( ControlObject* pUIObject )
{
    s_CUI_ID_FRAME_EquipCopy.SetDirty( true );
    s_CUI_ID_FRAME_EquipCopy.ClearEquip();	
    s_CUI_ID_FRAME_EquipCopy.ClearTargetEquip();	
    s_CUI_ID_FRAME_EquipCopy.RefreshAllBagEnable();

}

void CUI_ID_FRAME_EquipCopy::RefreshOkButton()
{
    if( !m_pID_FRAME_EquipEvolve )
        return;
    if(!IsVisable())
        return;

    if (m_stEquipBagIndex == -1 || m_stTargetItemIndex == -1)
    {
        m_pID_PICTURE_Begin->SetVisable(true);
    }
    else
    {
        m_pID_PICTURE_Begin->SetVisable(false);
    }
    m_pID_BUTTON_Ok->SetEnable( true );
    if( m_stEquipBagIndex == -1 || m_stTargetItemIndex == -1)
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }
    ControlIconDrag::S_ListImg * pImg = m_pID_LISTIMG_Equip->GetItemByIndex(0);
    if(!pImg || pImg->IsNull())
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }
    ControlIconDrag::S_ListImg * pImg2 = m_pID_LISTIMG_Equip2->GetItemByIndex(0);
    if(!pImg2 || pImg2->IsNull())
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    if (m_nSelectMaterialIndex == -1)
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    int nNeedMoney = GetEvolveMoneyCost();
    if (nNeedMoney == -1)
    {
        m_pID_BUTTON_Ok->SetEnable( false );
        return;
    }

    if(!thePlayerRole.HaveEnoughMoney(nNeedMoney))
    {
        m_pID_BUTTON_Ok->SetEnable(false);
        return;
    }

}

void CUI_ID_FRAME_EquipCopy::ResetUIObjects()
{
    EquipEvolveUI::ResetUIObjects();
    m_CrossCopy = false;
    m_EvolveType = MsgEquipEvolve::ET_Maintain;
    m_MaterialType = ItemDefine::ematerial_maintain;
    m_pID_PICTURE_Begin1 = NULL;
    m_pID_PICTURE_BeginCross = NULL;
    m_stTargetItemIndex = -1;
    m_stTargetItemGuid = 0;
    m_bTargetItemEnable = true;
}


void CUI_ID_FRAME_EquipCopy::RefreshAllBagEnable()
{
    EquipEvolveUI::RefreshAllBagEnable();
    if( m_stTargetItemIndex != -1 )
    {
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_stTargetItemIndex, true );
        if (m_bTargetItemEnable)
        {
            m_stTargetItemIndex = -1;
        }
    }

}

void CUI_ID_FRAME_EquipCopy::TipVisible( bool IsMaterialExist )
{
    if (m_stTargetItemIndex != -1 && m_stEquipBagIndex != -1)
    {
        m_pID_TEXT_Tip1->SetVisable(true);
    }
    else
    {
        m_pID_TEXT_Tip1->SetVisable(false);
    }

    if (IsMaterialExist)
    {
        m_pID_TEXT_Tip2->SetVisable(false);
    }
    else
    {
        m_pID_TEXT_Tip2->SetVisable(true);
    }

}

void CUI_ID_FRAME_EquipCopy::ArmourOnIconDragOn( ControlObject* pSender, ControlIconDrag::S_ListImg* pItemDrag )
{
    if (m_stEquipBagIndex == -1)
    {
        ID_LISTIMG_Equip1OnIconDragOn(pSender,NULL,pItemDrag,NULL);
    }
    else
    {
        ID_LISTIMG_Equip2OnIconDragOn(pSender,NULL,pItemDrag,NULL);
    }

}

bool CUI_ID_FRAME_EquipCopy::IsSamePart( ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg )
{
    if( !pTargetImg || !pImg)
        return false;
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;

    ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetImg->m_pkIconInfo->GetItemId() );
    if( !pTargetItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pTargetCanEquip = ( ItemDefine::SItemCanEquip* )pTargetItemCommon;
    return pCanEquip->ustEquipType == pTargetCanEquip->ustEquipType;
}

bool CUI_ID_FRAME_EquipCopy::IsInCrossLevel( ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg )
{
    if( !pTargetImg || !pImg)
        return false;
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;

    ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetImg->m_pkIconInfo->GetItemId() );
    if( !pTargetItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pTargetCanEquip = ( ItemDefine::SItemCanEquip* )pTargetItemCommon;
    int nDeltaLevel = pTargetCanEquip->stEquipLevelReq - pCanEquip->stEquipLevelReq;
    return  nDeltaLevel < gCfg.m_nMaxEquipCopyItemCrossLevel && nDeltaLevel > 0;

}


bool CUI_ID_FRAME_EquipCopy::IsSameLevel( ControlIconDrag::S_ListImg * pImg,ControlIconDrag::S_ListImg * pTargetImg )
{
    if( !pTargetImg || !pImg)
        return false;
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pImg->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;

    ItemDefine::SItemCommon* pTargetItemCommon = GettheItemDetail().GetItemByID( pTargetImg->m_pkIconInfo->GetItemId() );
    if( !pTargetItemCommon )
        return false;
    ItemDefine::SItemCanEquip* pTargetCanEquip = ( ItemDefine::SItemCanEquip* )pTargetItemCommon;
    return pTargetCanEquip->stEquipLevelReq == pCanEquip->stEquipLevelReq;
}

void CUI_ID_FRAME_EquipCopy::ClearTargetEquip()
{
    m_bTargetItemEnable = true;				
    m_pID_LISTIMG_Equip2->Clear();
    SetDirty(true);

}

void CUI_ID_FRAME_EquipCopy::SendEvolveMsg()
{
    MsgEquipEvolve msgEvolve;
    msgEvolve.nEvolveType = GetEvolveType();

    msgEvolve.nNormalBagIndex = m_stTargetItemIndex;
    msgEvolve.nNormalGuid      = m_stTargetItemGuid;

    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagType= BT_NormalItemBag;
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].bagIndex = m_stEquipBagIndex;
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_DefaultMaterialIndex].guid = m_stEquipBagGuid;

    msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagType= m_shMaterialBagType[m_nSelectMaterialIndex];
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].bagIndex = m_stMaterialIndex[m_nSelectMaterialIndex];
    msgEvolve.materials[MsgEquipEvolve::EConstDefine_SecondMaterialIndex].guid = m_n64MaterialGuid[m_nSelectMaterialIndex];

	msgEvolve.SendEquipMsg();
   // GettheNetworkInput().SendMsg( &msgEvolve );

}

void CUI_ID_FRAME_EquipCopy::_RefreshEquipInfo( ControlIconDrag::S_ListImg* pListImg )
{
    EquipEvolveUI::_RefreshEquipInfo(pListImg);

    if (-1 != m_stTargetItemIndex)
    {
        ControlIconDrag::S_ListImg* pTargetImg = s_CUI_ID_FRAME_PACK.GetItemByIndex( BT_NormalItemBag, m_stTargetItemIndex );
        if( !pTargetImg )
            return;
        m_pID_LISTIMG_Equip2->Clear();
        m_pID_LISTIMG_Equip2->SetItem( pTargetImg, 0 );
        m_pID_LISTIMG_Equip2->GetItemByIndex( 0 )->m_pkIconInfo->Count() = 1;
        m_pID_LISTIMG_Equip2->GetItemByIndex( 0 )->m_eEnable = eIcon_Enable;	
    }
}

bool CUI_ID_FRAME_EquipCopy::IsPackItemBeUsing( __int64 nGuid )
{
    if( EquipEvolveUI::IsPackItemBeUsing( nGuid ) )
        return true;

    if( !IsVisable() || nGuid <= 0 )
        return false;

    if( m_stTargetItemGuid == nGuid )
        return true;

    return false;
}
