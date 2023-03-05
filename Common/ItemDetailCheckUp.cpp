#include "ItemDetailConfig.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"

#pragma warning( push, 0 )

bool CItemDetail::AddCheckUpItem( const char *szFileName )
{
    //const char* szFileName = "CheckUp.slk";
    
    CSlkReader pReader;
    OutputSlkLoadingMessage( "正在分析%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "找不到%s文件\r\n",szFileName);
        return false;
    }


    int offset = 3;
    int iRet;

    std::string strValue;
    int         iValue     = 0;
    float       fValue     = 0.0f;
    

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"ItemID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 ItemID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_CHECKUP)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false; 
        }

        ItemDefine::SItemCheckUp *pItemCheckUp = (ItemDefine::SItemCheckUp *)pCommon;

        //SLK_GET_INT( pItemCheckUp->bExclusive, "Exclusive" );
        SLK_GET_INT( pItemCheckUp->stCheckUpType, "CheckUpType" );
        SLK_GET_INT( pItemCheckUp->stEquipLevel, "EquipLevel" );
        SLK_GET_INT( pItemCheckUp->stEffectType, "EffectType" );
        SLK_GET_INT( pItemCheckUp->stEffectLevel, "EffectLevel" );
        SLK_GET_INT( pItemCheckUp->nValue1, "Value1" );
        SLK_GET_INT( pItemCheckUp->nValue2, "Value2" );
        
        
        m_vecCheckUpItem.push_back(pItemCheckUp);
    }

    return true;

}


bool CItemDetailConfig::LoadCheckUpItem    ( MeXmlDocument *pXmlDoc, int mode )//鉴定或者其他的一些物品
{
    if ( pXmlDoc == NULL )
    { return false; }

    MeXmlElement *pRoot = pXmlDoc->FirstChildElement("Project");
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement *pItemsTree = pRoot->FirstChildElement("Items");
    if( pItemsTree == NULL )
    { return false; }

    MeXmlElement *pItemsType = pItemsTree->FirstChildElement("Type");
    if( pItemsType == NULL )
    { return false; }

    MeXmlElement *pItemElement = pItemsType->FirstChildElement("Item");
    if( pItemElement == NULL )
    { return false; }

    int iValue = -1;

    while ( pItemElement != NULL )
    {
        int itemId = 0;
        pItemElement->Attribute("Id", &itemId);

        ItemDefine::SItemCheckUp *pCheckUp = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pCheckUp = (ItemDefine::SItemCheckUp*)GetItemByID(itemId);
        }

        if ( NULL == pCheckUp)
        { pCheckUp = (ItemDefine::SItemCheckUp*)AllocItem( 0, sizeof( ItemDefine::SItemCheckUp ) ); }
        
        if( !pCheckUp )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pCheckUp->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pCheckUp->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pCheckUp->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pCheckUp->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pCheckUp->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pCheckUp->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pCheckUp->ustLevel = iValue;

        pCheckUp->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pCheckUp->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pCheckUp->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pCheckUp->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pCheckUp->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pCheckUp->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pCheckUp->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        if (iValue <= 0)    // 如果堆叠数量 <= 0 ，为错误数据 则纠正为1
        { iValue = 1;}
        pCheckUp->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pCheckUp->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pCheckUp->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pCheckUp->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pCheckUp->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pCheckUp->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pCheckUp->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pCheckUp->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pCheckUp->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pCheckUp->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pCheckUp->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pCheckUp->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pCheckUp->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pCheckUp->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pCheckUp->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pCheckUp->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pCheckUp->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pCheckUp->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pCheckUp->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pCheckUp->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pCheckUp->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pCheckUp->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pCheckUp->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pCheckUp->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pCheckUp->nDropMaxCount = iValue;

        //加载鉴定属性
        MeXmlElement *pCheckUpAttr = pItemElement->FirstChildElement("CheckUp");

        //pCheckUpAttr->Attribute("Exclusive", &iValue);
        //pCheckUp->bExclusive = iValue;

        pCheckUpAttr->Attribute("CheckUpType", &iValue);
        pCheckUp->stCheckUpType = iValue;

        pCheckUpAttr->Attribute("EquipLevel", &iValue);
        pCheckUp->stEquipLevel = iValue;

        pCheckUpAttr->Attribute("EffectType", &iValue);
        pCheckUp->stEffectType = iValue;

        pCheckUpAttr->Attribute("EffectLevel", &iValue);
        pCheckUp->stEffectLevel = iValue;

        pCheckUpAttr->Attribute("Value1", &iValue);
        pCheckUp->nValue1 = iValue;

        pCheckUpAttr->Attribute("Value2", &iValue);
        pCheckUp->nValue2 = iValue;

        m_vecCheckUpItem.push_back(pCheckUp);

        AddItemToContainer(pCheckUp);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveCheckUpItem     ( const char *szFileName )//+保存鉴定或者其他的一些物品
{
    if (szFileName == NULL )
    { return false; }

    MeXmlDocument MeXmlDoc;
    MeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = MeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pItems = pRoot->InsertEndChild( ("Items"))->ToElement();
    if (pItems == NULL)
    { return false; }

    MeXmlElement *pCheckUpType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pCheckUpType == NULL)
    { return false; }

	pCheckUpType->SetAttribute("Id", ItemDefine::ITEMTYPE_CHECKUP);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_CHECKUP  )
        { continue; }

        ItemDefine::SItemCheckUp *pCheckUpIter = (ItemDefine::SItemCheckUp *)*iterBegin;

        MeXmlElement *pItem = pCheckUpType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pCheckUpIter->ustItemID);
        Common::_tstring strName = pCheckUpIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pCheckUpIter->ucItemType]);
        Common::_tstring strDescription = pCheckUpIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pCheckUpIter->nUseTime);
        pItem->SetAttribute("UserTarget", pCheckUpIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pCheckUpIter->ustLevel);
        pAppearance->SetAttribute("Rare", pCheckUpIter->cItemClass);
        pAppearance->SetAttribute("Weight", pCheckUpIter->fWeight);
        pAppearance->SetAttribute("IconID", pCheckUpIter->ustIconId);
        Common::_tstring strIconFile = pCheckUpIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pCheckUpIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pCheckUpIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pCheckUpIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pCheckUpIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pCheckUpIter->nBill);
        pPrice->SetAttribute("CostType", pCheckUpIter->costType);
        pPrice->SetAttribute("Cost", pCheckUpIter->dwCost);
        pPrice->SetAttribute("CostItemID", pCheckUpIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pCheckUpIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pCheckUpIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pCheckUpIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pCheckUpIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pCheckUpIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pCheckUpIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pCheckUpIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pCheckUpIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pCheckUpIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pCheckUpIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pCheckUpIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pCheckUpIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pCheckUpIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pCheckUpIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pCheckUpIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pCheckUpIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pCheckUpIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pCheckUpIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pCheckUpIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pCheckUpIter->nDropMaxCount);

        //宝箱属性
        MeXmlElement *pCheckUp = pItem->InsertEndChild(("CheckUp"))->ToElement();
        if (pCheckUp == NULL)
        { continue; }

        //pCheckUp->SetAttribute("Exclusive", pCheckUpIter->bExclusive);
        pCheckUp->SetAttribute("CheckUpType", pCheckUpIter->stCheckUpType);
        pCheckUp->SetAttribute("EquipLevel", pCheckUpIter->stEquipLevel);
        pCheckUp->SetAttribute("EffectType", pCheckUpIter->stEffectType);
        pCheckUp->SetAttribute("EffectLevel", pCheckUpIter->stEffectLevel);
        pCheckUp->SetAttribute("Value1", pCheckUpIter->nValue1);
        pCheckUp->SetAttribute("Value2", pCheckUpIter->nValue2);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )