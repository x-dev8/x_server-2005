#include "FiveXingBase.h"
#include "MeUi/ExpressionManager.h"
#include "StarLevelUpConfig.h"
#include "PlayerRole.h"
#include "ShowScreenText.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "PackItemEnableManager.h"
#ifdef _DEBUG
#include "MeFont\MeFont.h"
#include "Common.h"
#include "MeFont/MeFontSystem.h"
#endif

CFiveXingBase::CFiveXingBase(void)
{
    Init();
    m_isPlaying = false;
    m_bCanShow  = false;
}

CFiveXingBase::~CFiveXingBase(void)
{

}

void CFiveXingBase::Init()
{
    m_vVisualPos.x = 0.0f;
    m_vVisualPos.y = 0.0f;
    m_vVisualPos.z = 0.0f;
}

void CFiveXingBase::UpdateMoney(DWORD dwMoney,std::string& strText)
{
	thePlayerRole.GetGSCStringFromJiaoZi(dwMoney, strText);
}


void CFiveXingBase::SetVisiblePosition(const Vector &vPos)
{
    m_vVisualPos.x = vPos.x;
    m_vVisualPos.y = vPos.y;
    m_vVisualPos.z = vPos.z;
}

bool CFiveXingBase::IsOverDistance(const Vector& vCurPos)
{
    float xoff = vCurPos.x - m_vVisualPos.x;
    float yoff = vCurPos.y - m_vVisualPos.y;
    float fDist = sqrtf( xoff*xoff + yoff*yoff );
    return (fDist > 12.0f);
}


void CFiveXingBase::UpdatePackItemEnable(CItemBag2 &bag,int nOldIndex,int nNewIndex,int bagType)
{
    if(nOldIndex != -1)
    {
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &bag, nOldIndex, true );
    }

    if(nNewIndex != -1)
    {
        // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
        CPackItemEnableManager::Instance()->RefreshBagItemEnable( &bag, nNewIndex, true );
    }
}

bool CFiveXingBase::IsFiveXingItem(unsigned short usItemID,unsigned char  ucItemType,unsigned char ucItemTypeSecond,unsigned char ucItemTypeThrid,char* pszTip)
{
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( usItemID );
    if( !pItemCommon )
        return false;

    switch(ucItemType)
    {
    case ItemDefine::ITEMTYPE_ARMOUR:
        {
            if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
            {
                ItemDefine::SItemArmour* pItemArmour = static_cast<ItemDefine::SItemArmour*>(pItemCommon);
                if( pItemArmour && pItemArmour->IsElementSuitEquip())
                {
                    return true;
                }
                else
                {
                    if(pszTip)
                        sprintf(pszTip,"%s",theXmlString.GetString(eClient_FiveXingTipUpdateNoCan));
                }
            }
        }
        break;
    case ItemDefine::ITEMTYPE_CHECKUP:
        {
            //未放置道具直接返回
            if(m_FiveXing[0].m_nIndex == -1)
                return false;

            if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_CHECKUP)
            {
                ItemDefine::SItemCheckUp *pItemCheckUp = static_cast<ItemDefine::SItemCheckUp*>(pItemCommon);
                if(!pItemCheckUp)
                    return false;

                //类型判断
                if(pItemCheckUp->stCheckUpType != ucItemTypeSecond||pItemCheckUp->stEffectType != ucItemTypeThrid)
                {
                    if(pszTip)
                       sprintf(pszTip,"%s",theXmlString.GetString(eClient_FiveXingTipMaterialError));
                    return false;
                }

                SCharItem sCharItem;
                if(!thePlayerRole.m_bag.GetItem(m_FiveXing[0].m_nIndex,&sCharItem))
                    return false;

                //如果为五行鉴定符,判断等级
                if(pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_Elements&&
                    pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsCheckUp)
                {

                    ItemDefine::SItemCommon* pEquipItem = GettheItemDetail().GetItemByID(sCharItem.itembaseinfo.ustItemID);
                    if(!pEquipItem)
                        return false;

                    ItemDefine::SItemCanEquip *pCanEquip = static_cast<ItemDefine::SItemCanEquip*>(pEquipItem);
                    if(!pCanEquip)
                        return false;

                    if(pItemCheckUp->stEquipLevel < pCanEquip->stEquipLevelReq)
                    {
                        if(pszTip)
                            sprintf(pszTip,"%s",theXmlString.GetString(eClient_FiveXingTipMaterialError));
                        return false;
                    }
                }

                //如果为提纯材料,属性判断
                if(pItemCheckUp->stCheckUpType == ItemDefine::SItemCheckUp::ECD_Suit
                    &&pItemCheckUp->stEffectType == ItemDefine::SItemCheckUp::ECD_ElementsSuitLevel)
                {
                    //因为6为通用属性，所以不用判断
                    if(pItemCheckUp->nValue1 != 6 &&pItemCheckUp->nValue1 != sCharItem.GetElements())
                    {
                        if(pszTip)
                            sprintf(pszTip,"%s",theXmlString.GetString(eClient_FiveXingTipMaterialError));
                        return false;
                    }
                }

                return true;
            }
        }
        break;
    default:
        assert(0);
        break;
    }

    return false;
}


void CFiveXingBase::UpdataItem(ControlListImage* pImg,ControlIconDrag::S_ListImg*  pListImg,int nCount /*= 1*/)
{
    if(!pImg || !pListImg)
        return;

    pImg->Clear();
    pImg->SetItem(pListImg,0);
    pImg->GetItemByIndex(0)->m_pkIconInfo->Count() = nCount;
    pImg->GetItemByIndex(0)->m_eEnable         = eIcon_Enable;
}

void CFiveXingBase::UpdateMoneyByItem(SCharItem* pItem,std::string &strText,bool bLevelUp)
{
    if( !pItem )
        return;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
    if( !pItemCommon )
        return ;

    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
    if( !pCanEquip )
        return ;

    //StarLevelUpData* pData = theSuitOperateConfig.GetElementEquipData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
   // const ElementSuitLevelUp* pData = theSuitOperateConfig.GetElementEquipData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
   // if( !pData )
   //     return;

    DWORD dwMoney = 0;
    if(bLevelUp)
        dwMoney = theSuitOperateConfig.GetElementSuitLevelUpCostMoney(pCanEquip->stEquipLevelReq);
    else
        dwMoney = theSuitOperateConfig.GetElementSuitChangeCostMoney(pCanEquip->stEquipLevelReq);
    UpdateMoney(dwMoney,strText);
}


void CFiveXingBase::SetFiveXingItem(ControlIconDrag::S_ListImg* pItemDrag,int nBagType,eFiveXing eIndex)
{
    if(!pItemDrag)
        return;

    if(eIndex >= enum_FiveXingMax)
        return;

    int nIndex = -1;
    SCharItem sCharItem;

    //普通背包
    if(nBagType == BT_NormalItemBag)
    {
        nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
        if(nIndex == -1)
            return;

        if(!thePlayerRole.m_bag.GetItem(nIndex,&sCharItem))
            return;

        UpdatePackItemEnable(thePlayerRole.m_bag,m_FiveXing[eIndex].m_nIndex,nIndex,m_FiveXing[eIndex].m_eBagType);

        m_FiveXing[eIndex].m_nIndex   = nIndex;
        m_FiveXing[eIndex].m_eBagType = nBagType;
        m_FiveXing[eIndex].m_nGuid    = sCharItem.itembaseinfo.nOnlyInt;
    }
    else if(nBagType == BT_MaterialBag)//材料背包
    {
        int nIndex = -1;
        nIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_MaterialBag, pItemDrag);
        if(nIndex == -1)
            return;

        SCharItem sCharItem;
        if(!thePlayerRole.m_bagMaterial.GetItem(nIndex,&sCharItem))
            return;

        UpdatePackItemEnable(thePlayerRole.m_bagMaterial,m_FiveXing[eIndex].m_nIndex,nIndex,m_FiveXing[eIndex].m_eBagType);

        m_FiveXing[eIndex].m_nIndex = nIndex;
        m_FiveXing[eIndex].m_eBagType = nBagType;
        m_FiveXing[eIndex].m_nGuid    = sCharItem.itembaseinfo.nOnlyInt;
    }
    else
        assert(0); //防止意外情况发生
}

void CFiveXingBase::ClearFiveXingItemByIndex(eFiveXing nIndex)
{
    if(nIndex >= enum_FiveXingMax)
        return;

    if(m_FiveXing[nIndex].m_eBagType == BT_NormalItemBag)
        UpdatePackItemEnable(thePlayerRole.m_bag,m_FiveXing[nIndex].m_nIndex,-1,m_FiveXing[nIndex].m_eBagType);
    else if(m_FiveXing[nIndex].m_eBagType == BT_MaterialBag)
        UpdatePackItemEnable(thePlayerRole.m_bagMaterial,m_FiveXing[nIndex].m_nIndex,-1,m_FiveXing[nIndex].m_eBagType);
    else if(m_FiveXing[nIndex].m_eBagType != -1)
        assert(0);

    m_FiveXing[nIndex].m_eBagType = -1;
    m_FiveXing[nIndex].m_nIndex = -1;
    m_FiveXing[nIndex].m_nGuid = 0;
}


bool CFiveXingBase::IsFiveXingReputationItem(ControlIconDrag::S_ListImg* pItem)
{
    if(!pItem)
        return false;

    const ElementSuitLevelUp* pCostInfo = GetChangeCostInfo();
    if(!pCostInfo)
        return false;

    unsigned short ustItemID   = pItem->m_pkIconInfo->GetItemId(); 

    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(ustItemID);
    if(!pItemCommon)
        return false;

    if(pCostInfo->GetCostType() != pItemCommon->costType)
        return false;

    if(pCostInfo->GetCostType() == ItemDefine::CT_Item)
    {
        if(pCostInfo->GetCostValue() != pItemCommon->costItemID || pCostInfo->GetCostCount() != pItemCommon->dwCost)
            return false;
    }
    else
    {
        if(pCostInfo->GetCostValue() != pItemCommon->dwCost)
            return false;
    }

    return true;
}

const ElementSuitLevelUp* CFiveXingBase::GetChangeCostInfo()
{
    if(m_FiveXing[0].m_nIndex == -1)
        return NULL;

    SCharItem sCharItem;
    bool bResult = false;

    if(m_FiveXing[0].m_eBagType == BT_NormalItemBag)
        bResult = thePlayerRole.m_bag.GetItem(m_FiveXing[0].m_nIndex,&sCharItem);
    else if(m_FiveXing[0].m_eBagType == BT_MaterialBag)
        bResult = thePlayerRole.m_bagMaterial.GetItem(m_FiveXing[0].m_nIndex,&sCharItem);
    else
        bResult = false;

    if(!bResult)
        return NULL;

    ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(sCharItem.itembaseinfo.ustItemID);
    if(!pItemCommon)
        return NULL;

    ItemDefine::SItemArmour *pItemArmour = static_cast<ItemDefine::SItemArmour*>(pItemCommon);
    if(!pItemArmour)
        return NULL;

    return theSuitOperateConfig.GetElementEquipData(pItemArmour->stEquipLevelReq,sCharItem.GetSuitLevel());
}

void CFiveXingBase::InitAnim(RECT rc)
{
    m_slideAnim.Initialize("Ui\\Common\\FiveXingSuitEffect\\HudFiveXingLight", 21, rc, 2000);
}

void CFiveXingBase::UpdateAnim(RECT rc)
{
    m_slideAnim.Update(HQ_TimeGetTime(), &rc);
}

void CFiveXingBase::PlayAnim()
{
    AnimationBegin();
    m_slideAnim.StartAnimation(HQ_TimeGetTime());
}

void CFiveXingBase::EndAnim()
{
    AnimationEnd();
	m_slideAnim.StopAnimation();
	m_slideAnim.UnRelativePicResource();
}


#ifdef _DEBUG
void CFiveXingBase::DebugInfo()
{
    for (int i = 0;i < enum_FiveXingMax;++i)
    {
        std::string strWord;
        strWord.clear();
        if(m_FiveXing[i].m_eBagType == BT_NormalItemBag)
            strWord += "普通背包";
        else if(m_FiveXing[i].m_eBagType == BT_MaterialBag)
            strWord += "材料背包";
        else
            strWord += "无背包";
        strWord += "   ";

        char szWord[256];
        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"索引:%d",m_FiveXing[i].m_nIndex);
        strWord += szWord;
        strWord += "   ";

        MeSprintf_s(szWord,sizeof(szWord)/sizeof(char) - 1,"GUID:%I64u",m_FiveXing[i].m_nGuid);
        strWord += szWord;
        strWord += "   ";

        FontSystem::DrawText(strWord.c_str(),100,200 + 25 * i,DT_NOCLIP,0xffff0000,2);
    }
}
#endif

bool CFiveXingBase::IsMoneyEnough(SCharItem* pItem,bool bLevelUp)
{
    if( !pItem )
        return false;

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
    if( !pItemCommon )
        return false;

    ItemDefine::SItemCanEquip* pCanEquip = ( ItemDefine::SItemCanEquip* )pItemCommon;
    if( !pCanEquip )
        return false;

    //StarLevelUpData* pData = theStarLevelUpConfig.GetStarLevelUpData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
   // const ElementSuitLevelUp* pData = theSuitOperateConfig.GetElementEquipData( pCanEquip->stEquipLevelReq, pItem->equipdata.ucLevel );
  //  if( !pData )
   //     return false;

    //DWORD dwMoney = theSuitOperateConfig.GetElementSuitChangeCostMoney(); //pData->GetCostValue() /** 5*/;
    DWORD dwMoney = 0;
    if(bLevelUp)
        dwMoney = theSuitOperateConfig.GetElementSuitLevelUpCostMoney(pCanEquip->stEquipLevelReq);
    else
        dwMoney = theSuitOperateConfig.GetElementSuitChangeCostMoney(pCanEquip->stEquipLevelReq);

    if(!thePlayerRole.HaveEnoughMoney(dwMoney))
        return false;

    return true;
}
