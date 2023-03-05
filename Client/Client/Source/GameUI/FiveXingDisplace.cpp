/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\liuchuanpeng\桌面\FiveXingDisplace.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "FiveXingDisplace.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "SuitOperateConfig.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "EquipUIHelper.h"
#include "Common.h"

CUI_ID_FRAME_FiveXingDisplace s_CUI_ID_FRAME_FiveXingDisplace;
MAP_FRAME_RUN( s_CUI_ID_FRAME_FiveXingDisplace, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_FiveXingDisplace, OnFrameRender )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_BUTTON_helpOnButtonClick )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_ArmourOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_ArmourOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_ArmourOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_ArmourOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_MaterialOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_MaterialOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_MaterialOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_MaterialOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2OnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2OnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2OnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2OnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_AimOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_AimOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_AimOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_LISTIMG_AimOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_FiveXingDisplace, ID_BUTTON_CancelOnButtonClick )
CUI_ID_FRAME_FiveXingDisplace::CUI_ID_FRAME_FiveXingDisplace()
{
    // Member
    m_pID_FRAME_FiveXingDisplace = NULL;
    m_pID_PICTURE_MiddleTitle = NULL;
//     m_pID_BUTTON_CLOSE = NULL;
//     m_pID_BUTTON_help = NULL;
    m_pID_LISTIMG_Armour = NULL;
    m_pID_TEXT_UseMoneyZ = NULL;
    m_pID_TEXT_UseMoney = NULL;
    m_pID_PICTURE_LeftTitle = NULL;
    //m_pID_PICTURE_TitleWord = NULL;
    m_pID_LISTIMG_Material = NULL;
    m_pID_LISTIMG_Material2 = NULL;
    m_pID_PICTURE_Title = NULL;
    m_pID_LISTIMG_Aim = NULL;
    m_pID_PICTURE_Arrow = NULL;
    m_pID_BUTTON_Ok = NULL;
    m_pID_BUTTON_Cancel = NULL;
    m_pID_PICTURE_Jin = NULL;
    m_pID_PICTURE_Tu = NULL;
    m_pID_PICTURE_Huo = NULL;
    m_pID_PICTURE_Mu = NULL;
    m_pID_PICTURE_Shui = NULL;
    m_pID_PICTURE_Flash = NULL;
	m_pID_TEXT_Rate = NULL;
}
// Frame
bool CUI_ID_FRAME_FiveXingDisplace::OnFrameRun()
{
    return true;
}
bool CUI_ID_FRAME_FiveXingDisplace::OnFrameRender()
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
// bool CUI_ID_FRAME_FiveXingDisplace::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
//     return true;
// }
// // Button
// bool CUI_ID_FRAME_FiveXingDisplace::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
// {
//     return true;
// }
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_ArmourOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                                  ControlIconDrag::S_ListImg* pItemDrag,
                                                                  ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!m_pID_FRAME_FiveXingDisplace)
    {
        assert(0&&"UI Error");
        return false;
    }

    if(!pItemDrag)
        return false;

    //是否为普通包裹
    if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
        return false;

    //是否为五行道具
    char szError[256] = {0};
    if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,szError))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
        return false;
    }

    SCharItem *pItem = (SCharItem*)pItemDrag->m_pkIconInfo->GetData();
    if(!pItem)
        return false;

    if(pItem->GetElements() == ItemElements_Init)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_NoFiveXing) );
        return false;
    }


    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransAimItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    Clear();

    //保存数据
    SetFiveXingItem(pItemDrag,BT_NormalItemBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransItem);

    //更新道具
    UpdataItem(m_pID_LISTIMG_Armour,pItemDrag);

    //更新钱币
    SetMoneyUI(theSuitOperateConfig.GetElementMove().GetCostMoney());

    //刷新OK按钮
    RefreshOkButton();
    m_ControlGroup.SetVisible(false);

    ControlObject* pObject = m_ControlGroup.GetControl(pItem->GetElements() - 1);
    if(pObject)
       pObject->SetVisable(true);
    
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXingDisplace::SetMaterial0);
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_ArmourOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_ArmourOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_ArmourOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingDisplace)
        return false;

    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransAimItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    Clear();

    m_ControlGroup.SetVisible(false);
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    m_pID_BUTTON_Ok->SetEnable(false);
    SetMoneyUI(0);
    return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_MaterialOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                                    ControlIconDrag::S_ListImg* pItemDrag,
                                                                    ControlIconDrag::S_ListImg* pItemSrc )
{
    if(!pItemDrag)
        return false;

    if(!m_pID_FRAME_FiveXingDisplace)
        return false;

    if(m_FiveXing[0].m_nIndex == -1)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_HaveNotElement) );
        return false;
    }

    //是否为五行石头
    char szError[256] = {0};
    if(!IsFiveXingStone(pItemDrag,szError,sizeof(szError)/sizeof(char) - 1))
    {
        if(strlen(szError) > 0)
           CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
        return false;
    }

    SetMaterial0(pSender,pItemDrag);

    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_MaterialOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_MaterialOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_MaterialOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingDisplace)
    {
        assert(false&&"ui error");
        return false;
    }

    m_pID_LISTIMG_Material->Clear();
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    RefreshOkButton();

    return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_Material2OnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                                     ControlIconDrag::S_ListImg* pItemDrag,
                                                                     ControlIconDrag::S_ListImg* pItemSrc )
{
    SetMaterial1(pSender,pItemDrag);

    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_Material2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_Material2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_Material2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingDisplace)
    {
        assert(false&&"ui error");
        return false;
    }

    m_pID_LISTIMG_Material2->Clear();
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    RefreshOkButton();
    UpdateProb(0);

    return false;
}
// ListImg / ListEx
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_AimOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
                                                               ControlIconDrag::S_ListImg* pItemDrag,
                                                               ControlIconDrag::S_ListImg* pItemSrc )
{

    if(!m_pID_FRAME_FiveXingDisplace)
    {
        assert(0&&"UI Error");
        return false;
    }

    if(!pItemDrag)
        return false;

    if(m_FiveXing[0].m_nIndex == -1)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_HaveNotElement) );
        return false;
    }

    //是否为普通包裹
    if( !s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
        return false;

    //是否为五行道具
    char szError[256] = {0};
    if(!IsFiveXingItem(pItemDrag->m_pkIconInfo->GetItemId(),ItemDefine::ITEMTYPE_ARMOUR,0,0,szError))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, szError );
        return false;
    }

    //是否为相同的部位
    if(!IsSamePart(m_pID_LISTIMG_Armour->GetItemByIndex(0),pItemDrag))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eFiveXingDisplace_PartWrong) );
        return false;
    }

    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransAimItem);
    //ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    //m_pID_LISTIMG_Material->Clear();
    m_pID_LISTIMG_Material2->Clear();
    m_pID_LISTIMG_Aim->Clear();

    //保存数据
    SetFiveXingItem(pItemDrag,BT_NormalItemBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransAimItem);

    //更新道具
    UpdataItem(m_pID_LISTIMG_Aim,pItemDrag);

    //更新钱币
    SetMoneyUI(theSuitOperateConfig.GetElementMove().GetCostMoney());

    //刷新OK按钮
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    RefreshOkButton();

    UpdateProb(0);

    //SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXingDisplace::SetMaterial0);
    //SeachMaterialAndSetMaterial(this, &CUI_ID_FRAME_FiveXingDisplace::SetMaterial1);

    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_AimOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_AimOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    return false;
}
bool CUI_ID_FRAME_FiveXingDisplace::ID_LISTIMG_AimOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
    if(!m_pID_FRAME_FiveXingDisplace)
        return false;

    //m_pID_LISTIMG_Material->Clear();
    m_pID_LISTIMG_Material2->Clear();
    m_pID_LISTIMG_Aim->Clear();
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransAimItem);
    //ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    m_pID_BUTTON_Ok->SetEnable(false);
    SetMoneyUI(0);
    UpdateProb(0);
    return false;
}
// Button
bool CUI_ID_FRAME_FiveXingDisplace::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_FiveXingDisplace)
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

    if(!IsMoneyEnough(theSuitOperateConfig.GetElementMove().GetCostMoney()))
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eClient_FiveXingTipUpdateNoMoney) );
        return false;
    }
    ControlIconDrag::S_ListImg *pImg = m_pID_LISTIMG_Material2->GetItemByIndex(0);
    if(!pImg)
        return false;

    int nCount = 0;
    if(pImg->m_pkIconInfo->GetItemId() != InvalidLogicNumber)
       nCount = pImg->m_pkIconInfo->Count();

    MsgSuitElementMoveReq msg;
    
    msg.stSrcArmourIndex = m_FiveXing[enum_FiveXingTransItem].m_nIndex;         // 源装备背包索引
    msg.n64SrcArmourGuid = m_FiveXing[enum_FiveXingTransItem].m_nGuid;          // 源装备guid

    msg.stDestArmourIndex = m_FiveXing[enum_FiveXingTransAimItem].m_nIndex;     // 目标装备背包索引
    msg.n64DestArmourGuid = m_FiveXing[enum_FiveXingTransAimItem].m_nGuid;      // 目标装备guid

    msg.chCheckUpBagType = m_FiveXing[enum_FiveXingTransStone].m_eBagType;      // 五行石背包类型
    msg.stCheckUpIndex = m_FiveXing[enum_FiveXingTransStone].m_nIndex;          // 五行石背包索引
    msg.n64CheckUpGuid = m_FiveXing[enum_FiveXingTransStone].m_nGuid;           // 五行石guid

    msg.chModulusBagType = m_FiveXing[enum_FiveXingTransHelper].m_eBagType;     // 概率道具背包类型
    msg.stModulusIndex   = m_FiveXing[enum_FiveXingTransHelper].m_nIndex;       // 概率道具背包索引
    msg.n64ModulusGuid   = m_FiveXing[enum_FiveXingTransHelper].m_nGuid;        // 概率道具guid

    msg.ustModulusCount  = nCount;                                              // 概率道具数量

    GettheNetworkInput().SendMsg(&msg);

    m_pID_PICTURE_Flash->SetVisable(true);

	PlayAnim();
    return true;
}
// Button
bool CUI_ID_FRAME_FiveXingDisplace::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
    SetVisable(false);
    return true;
}

// 装载UI
bool CUI_ID_FRAME_FiveXingDisplace::_LoadUI()
{
    DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\FiveXingDisplace.MEUI",false,UI_Render_LayerThree );
    if ( dwResult == 0 )
    {
        MESSAGE_BOX("读取文件[Data\\UI\\FiveXingDisplace.MEUI]失败")
            return false;
    }
    return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_FiveXingDisplace::DoControlConnect()
{
    theUiManager.OnFrameRun( ID_FRAME_FiveXingDisplace, s_CUI_ID_FRAME_FiveXingDisplaceOnFrameRun );
    theUiManager.OnFrameRender( ID_FRAME_FiveXingDisplace, s_CUI_ID_FRAME_FiveXingDisplaceOnFrameRender );
//     theUiManager.OnButtonClick( ID_FRAME_FiveXingDisplace, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_FiveXingDisplaceID_BUTTON_CLOSEOnButtonClick );
//     theUiManager.OnButtonClick( ID_FRAME_FiveXingDisplace, ID_BUTTON_help, s_CUI_ID_FRAME_FiveXingDisplaceID_BUTTON_helpOnButtonClick );
    theUiManager.OnIconDragOn( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_ArmourOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_ArmourOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_ArmourOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Armour, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_ArmourOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_MaterialOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_MaterialOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_MaterialOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_MaterialOnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_Material2OnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_Material2OnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_Material2OnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_Material2OnIconRButtonUp );
    theUiManager.OnIconDragOn( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Aim, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_AimOnIconDragOn );
    theUiManager.OnIconLDBClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Aim, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_AimOnIconLDBClick );
    theUiManager.OnIconButtonClick( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Aim, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_AimOnIconButtonClick );
    theUiManager.OnIconRButtonUp( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Aim, s_CUI_ID_FRAME_FiveXingDisplaceID_LISTIMG_AimOnIconRButtonUp );
    theUiManager.OnButtonClick( ID_FRAME_FiveXingDisplace, ID_BUTTON_Ok, s_CUI_ID_FRAME_FiveXingDisplaceID_BUTTON_OkOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_FiveXingDisplace, ID_BUTTON_Cancel, s_CUI_ID_FRAME_FiveXingDisplaceID_BUTTON_CancelOnButtonClick );

    m_pID_FRAME_FiveXingDisplace = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_FiveXingDisplace );
    m_pID_PICTURE_MiddleTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_MiddleTitle );
    //m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_BUTTON_CLOSE );
    //m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_BUTTON_help );
    m_pID_LISTIMG_Armour = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Armour );
    m_pID_TEXT_UseMoneyZ = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_TEXT_UseMoneyZ );
    m_pID_TEXT_UseMoney = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_TEXT_UseMoney );
    m_pID_PICTURE_LeftTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_LeftTitle );
    //m_pID_PICTURE_TitleWord = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_TitleWord );
    m_pID_LISTIMG_Material = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material );
    m_pID_LISTIMG_Material2 = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Material2 );
    m_pID_PICTURE_Title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Title );
    m_pID_LISTIMG_Aim = (ControlListImage*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_LISTIMG_Aim );
    m_pID_PICTURE_Arrow = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Arrow );
    m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_BUTTON_Ok );
    m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_BUTTON_Cancel );
    m_pID_PICTURE_Jin = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Jin );
    m_pID_PICTURE_Tu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Tu );
    m_pID_PICTURE_Huo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Huo );
    m_pID_PICTURE_Mu = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Mu );
    m_pID_PICTURE_Shui = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Shui );
    m_pID_PICTURE_Flash = (ControlPicture*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_PICTURE_Flash );
	m_pID_TEXT_Rate = (ControlText*)theUiManager.FindControl( ID_FRAME_FiveXingDisplace, ID_TEXT_Rate );

    m_pID_FRAME_FiveXingDisplace->SetOnVisibleChangedFun(OnVisibleChange);

    assert( m_pID_FRAME_FiveXingDisplace );
    assert( m_pID_PICTURE_MiddleTitle );
//     assert( m_pID_BUTTON_CLOSE );
//     assert( m_pID_BUTTON_help );
    assert( m_pID_LISTIMG_Armour );
    assert( m_pID_TEXT_UseMoneyZ );
    assert( m_pID_TEXT_UseMoney );
    assert( m_pID_PICTURE_LeftTitle );
//    assert( m_pID_PICTURE_TitleWord );
    assert( m_pID_LISTIMG_Material );
    assert( m_pID_LISTIMG_Material2 );
    assert( m_pID_PICTURE_Title );
    assert( m_pID_LISTIMG_Aim );
    assert( m_pID_PICTURE_Arrow );
    assert( m_pID_BUTTON_Ok );
    assert( m_pID_BUTTON_Cancel );
    assert( m_pID_PICTURE_Jin );
    assert( m_pID_PICTURE_Tu );
    assert( m_pID_PICTURE_Huo );
    assert( m_pID_PICTURE_Mu );
    assert( m_pID_PICTURE_Shui );
    assert( m_pID_PICTURE_Flash );
	assert( m_pID_TEXT_Rate );

    m_pID_PICTURE_Flash->SetVisable(false);

    RECT rc;
    m_pID_PICTURE_Flash->GetRealRect(&rc);
    InitAnim(rc);

    m_ControlGroup.Clear();
    m_ControlGroup.AddControl(m_pID_PICTURE_Jin);
    m_ControlGroup.AddControl(m_pID_PICTURE_Mu);
    m_ControlGroup.AddControl(m_pID_PICTURE_Shui);
    m_ControlGroup.AddControl(m_pID_PICTURE_Huo);
    m_ControlGroup.AddControl(m_pID_PICTURE_Tu);

    m_ControlGroup.SetVisible(false);

    SetVisable(false);
    return true;
}
// 卸载UI
bool CUI_ID_FRAME_FiveXingDisplace::_UnLoadUI()
{
    m_pID_FRAME_FiveXingDisplace = NULL;
    return theUiManager.RemoveFrame( "Data\\UI\\FiveXingDisplace.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_FiveXingDisplace::_IsVisable()
{
    if(!m_pID_FRAME_FiveXingDisplace)
        return false;

    return m_pID_FRAME_FiveXingDisplace->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_FiveXingDisplace::_SetVisable( const bool bVisable )
{
    if(!m_pID_FRAME_FiveXingDisplace)
        return;

    m_pID_FRAME_FiveXingDisplace->SetVisable( bVisable );
    m_pID_BUTTON_Ok->SetEnable(false);
}

bool CUI_ID_FRAME_FiveXingDisplace::IsFiveXingDisplace(ControlObject *pSender)
{
    return (m_pID_FRAME_FiveXingDisplace == pSender);
}

void CUI_ID_FRAME_FiveXingDisplace::OnVisibleChange( ControlObject* pUIObject )
{
    s_CUI_ID_FRAME_FiveXingDisplace.ClearAll();
    s_CUI_ID_FRAME_FiveXingDisplace.UpdateProb(-1);
}

void CUI_ID_FRAME_FiveXingDisplace::Init()
{
    Clear();
}

void CUI_ID_FRAME_FiveXingDisplace::Clear()
{
    m_pID_LISTIMG_Armour->Clear();
    m_pID_LISTIMG_Material->Clear();
    m_pID_LISTIMG_Material2->Clear();
    m_pID_LISTIMG_Aim->Clear();

    UpdateProb(0);
    SetMoneyUI(0);
}

void CUI_ID_FRAME_FiveXingDisplace::ShowResult()
{

}

void CUI_ID_FRAME_FiveXingDisplace::SetMoneyUI(DWORD dwMoney)
{
    m_pID_TEXT_UseMoney->Clear();

    std::string strMoney;

    UpdateMoney(dwMoney,strMoney);

    DWORD dwColor = 0xffffffff;
    if(!IsMoneyEnough(dwMoney))
        dwColor = 0xffff0000;

    m_pID_TEXT_UseMoney->SetText(strMoney,dwColor);
}

void CUI_ID_FRAME_FiveXingDisplace::RefreshOkButton()
{
    if(!IsVisable())
        return;

    m_pID_BUTTON_Ok->SetEnable(true);

    //道具是否全部放置
    for (int i = 0;i < enum_FiveXingMax - 1;++i)
    {
        if(m_FiveXing[i].m_nIndex == -1)
        {
            m_pID_BUTTON_Ok->SetEnable(false);
            return;
        }
    }

    //钱是否足够
    if(!IsMoneyEnough(theSuitOperateConfig.GetElementMove().GetCostMoney()))
    {
        m_pID_BUTTON_Ok->SetEnable(false);
        return;
    }
}

void CUI_ID_FRAME_FiveXingDisplace::ClearAll()
{
    if(!m_pID_FRAME_FiveXingDisplace)
        return;

    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)enum_FiveXingTransItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)enum_FiveXingTransAimItem);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)enum_FiveXingTransStone);
    ClearFiveXingItemByIndex((CFiveXingBase::eFiveXing)enum_FiveXingTransHelper); 
    Clear();
    m_pID_BUTTON_Ok->SetEnable(false);
    m_pID_BUTTON_Cancel->SetVisable(true);

    m_ControlGroup.SetVisible(false);
}

bool CUI_ID_FRAME_FiveXingDisplace::IsFiveXingLuckStone(ControlIconDrag::S_ListImg *pItem)
{
    if(!pItem)
        return false;

    return theSuitOperateConfig.GetElementMove().GetMaterialID() == pItem->m_pkIconInfo->GetItemId();
}

bool CUI_ID_FRAME_FiveXingDisplace::IsFiveXingStone(ControlIconDrag::S_ListImg *pItem,char *pszError /*= NULL*/,int nLen/* = 0*/)
{
    if(!pItem)
        return false;

    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
    if(!pItemDetail)
        return false;
 
    if (pItemDetail->ucItemType != ItemDefine::ITEMTYPE_CHECKUP)
        return false;

    ItemDefine::SItemCheckUp* pItemCheckUp = (ItemDefine::SItemCheckUp*)pItemDetail;
    if(!pItemCheckUp)
        return false;

    if( pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Elements )
        return false;

    //类型判断
    SCharItem sCharItem;
    if(!thePlayerRole.m_bag.GetItem(m_FiveXing[0].m_nIndex,&sCharItem))
    {
        if(pszError != NULL&&nLen > 0)
           MeSprintf_s(pszError,nLen,"%s",theXmlString.GetString(eText_Error_HaveNotElement));
        return false;
    }
    //如果为五行鉴定符,判断等级
    if(pItemCheckUp->stCheckUpType != ItemDefine::SItemCheckUp::ECD_Elements||
        pItemCheckUp->stEffectType != ItemDefine::SItemCheckUp::ECD_ElementsMove)
        return false;
    
    ItemDefine::SItemCommon* pEquipItem = GettheItemDetail().GetItemByID(sCharItem.itembaseinfo.ustItemID);
    if(!pEquipItem)
        return false;

    ItemDefine::SItemCanEquip *pCanEquip = static_cast<ItemDefine::SItemCanEquip*>(pEquipItem);
    if(!pCanEquip)
        return false;

    if(pItemCheckUp->stEquipLevel < pCanEquip->stEquipLevelReq)
    {
        if(pszError != NULL && nLen > 0)
            MeSprintf_s(pszError,nLen,"%s",theXmlString.GetString(eFiveXingDisplace_JinDingLevel));
        return false;
    }
    return true;
}

bool CUI_ID_FRAME_FiveXingDisplace::SetMaterial0(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
{
    if(!pItemDrag)
        return false;

    if(m_FiveXing[0].m_nIndex == -1)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_HaveNotElement) );
        return false;
    }

    //是否为五行石头
    if(!IsFiveXingStone(pItemDrag))
        return false;

    //保存数据
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
        SetFiveXingItem(pItemDrag,BT_NormalItemBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);
    else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
        SetFiveXingItem(pItemDrag,BT_MaterialBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransStone);

    //刷新道具
    UpdataItem(m_pID_LISTIMG_Material,pItemDrag);
    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);
    RefreshOkButton();

    return true;
}

bool CUI_ID_FRAME_FiveXingDisplace::SetMaterial1(ControlObject* pSender, ControlIconDrag::S_ListImg *pItemDrag)
{
    if(!pItemDrag)
        return false;

    if(m_FiveXing[0].m_nIndex == -1)
    {
        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_AttrFive_Failed, theXmlString.GetString(eText_Error_HaveNotElement) );
        return false;
    }

    //是否为五行祝福石
    if(!IsFiveXingLuckStone(pItemDrag))
        return false;

    //保存数据
    if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) )
        SetFiveXingItem(pItemDrag,BT_NormalItemBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);
    else if( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_MaterialBag, pSender) )
        SetFiveXingItem(pItemDrag,BT_MaterialBag,(CFiveXingBase::eFiveXing)CFiveXingBase::enum_FiveXingTransHelper);


    int nCount = pItemDrag->m_pkIconInfo->Count();
    int nMaxCount = theSuitOperateConfig.GetElementMove().GetMaxCount();
    if(nCount > nMaxCount)
        nCount = nMaxCount;

    //刷新材料
    UpdataItem(m_pID_LISTIMG_Material2,pItemDrag,nCount);

    RefreshOkButton();

    //更新概率
    UpdateProb(nCount);

    theIconDragManager.SetIconStateAfterDrag(eIcon_Disable);

    return true;
}

bool CUI_ID_FRAME_FiveXingDisplace::IsMoneyEnough(DWORD dwMoney)
{
    //DWORD dwCurMoney = thePlayerRole.GetData(CPlayerRole::TYPE_MONEY);

    //return dwCurMoney  < dwMoney;
    return thePlayerRole.HaveEnoughMoney(dwMoney);
} 

void CUI_ID_FRAME_FiveXingDisplace::UpdateProb(int nCount)
{
    if(nCount ==  -1)
       m_pID_TEXT_Rate->SetText(theXmlString.GetString(eFiveXingDisplace_ProbTip));
    else
    {
        float fValue = theSuitOperateConfig.GetElementMove().GetBaseModulus();
        if(nCount > 0)
            fValue = theSuitOperateConfig.GetElementMove().GetModulus(nCount);

        char szText[256] = {0};
        MeSprintf_s(szText,sizeof(szText)/sizeof(char) - 1,"%s%d%%",theXmlString.GetString(eFiveXingDisplace_ProbTip),(int)(fValue * 100.0f));

        m_pID_TEXT_Rate->SetText(szText);
    }
}

bool CUI_ID_FRAME_FiveXingDisplace::IsSamePart(ControlIconDrag::S_ListImg *pItemSrc,ControlIconDrag::S_ListImg *pItemDrag)
{
    if(!pItemSrc||!pItemDrag)
        return false;

    if(pItemSrc->m_pkIconInfo->GetItemId() == InvalidLogicNumber || pItemDrag->m_pkIconInfo->GetItemId() == InvalidLogicNumber)
        return false;

    ItemDefine::SItemCommon* pItemCommon = NULL;
    ItemDefine::SItemArmour* pItemArmourSrc = NULL;
    ItemDefine::SItemArmour* pItemArmourDest = NULL;

    pItemCommon = GettheItemDetail().GetItemByID( pItemSrc->m_pkIconInfo->GetItemId() );
    if( !pItemCommon )
        return false;

    if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
        return false;
    
    pItemArmourSrc = static_cast<ItemDefine::SItemArmour*>(pItemCommon);
    if( !pItemArmourSrc)    
        return false;

    pItemCommon = GettheItemDetail().GetItemByID(pItemDrag->m_pkIconInfo->GetItemId());
    if(!pItemCommon)
        return false;

    if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR)
        return false;

    pItemArmourDest = static_cast<ItemDefine::SItemArmour*>(pItemCommon);
    if(!pItemArmourDest)
        return false;

    if(pItemArmourSrc->ustEquipType != pItemArmourDest->ustEquipType)
        return false;

    return true;
}
