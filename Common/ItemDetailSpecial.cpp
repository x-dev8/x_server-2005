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

bool CItemDetail::AddSpecialItem( const char *szFileName )
{
    //const char* szFileName = "SpecialItem.slk";

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

        if(pCommon == NULL || pCommon->ucItemType !=ItemDefine::ITEMTYPE_SPECIAL)
        {
            OutputSlkLoadingMessage( "%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;  
        }

        ItemDefine::SItemSpecial *pItemSpecial = (ItemDefine::SItemSpecial *)pCommon;

        SLK_GET_INT( pItemSpecial->uchSpecialType, "SpecialType" );
        //SLK_GET_INT( pItemSpecial->bExclusive, "IsExclusive" );
        

        m_vecSpecialItem.push_back(pItemSpecial);
    }

    return true;
    
}


bool CItemDetailConfig::LoadSpecialItem    ( MeXmlDocument *pXmlDoc, int mode )//特殊物品
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

    int iValue = -1;

    MeXmlElement *pItemElement = pItemsType->FirstChildElement("Item");
    while ( pItemElement != NULL )
    {
        int itemId = 0;
        pItemElement->Attribute("Id", &itemId);

        ItemDefine::SItemSpecial *pSpecial = NULL;
        
        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pSpecial = (ItemDefine::SItemSpecial*)GetItemByID(itemId);
        }
        
        if ( NULL == pSpecial )
        { pSpecial = (ItemDefine::SItemSpecial*)AllocItem( 0, sizeof( ItemDefine::SItemSpecial ) ); }
        
        if( !pSpecial )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pSpecial->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pSpecial->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pSpecial->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pSpecial->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pSpecial->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pSpecial->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pSpecial->ustLevel = iValue;

        pSpecial->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pSpecial->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pSpecial->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pSpecial->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pSpecial->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pSpecial->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pSpecial->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pSpecial->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pSpecial->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pSpecial->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pSpecial->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pSpecial->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pSpecial->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pSpecial->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pSpecial->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pSpecial->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pSpecial->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pSpecial->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pSpecial->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pSpecial->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pSpecial->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pSpecial->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pSpecial->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pSpecial->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pSpecial->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pSpecial->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pSpecial->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pSpecial->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pSpecial->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pSpecial->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pSpecial->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pSpecial->nDropMaxCount = iValue;

        //加载特殊道具属性
        MeXmlElement *pSpecialAttr = pItemElement->FirstChildElement("Special");

        pSpecialAttr->Attribute("SpecialType", &iValue);
        pSpecial->uchSpecialType = iValue;

        //pSpecialAttr->Attribute("IsExclusive", &iValue);
        //pSpecial->bExclusive = iValue;

        m_vecSpecialItem.push_back(pSpecial);

        AddItemToContainer(pSpecial);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveSpecialItem     ( const char *szFileName )//+保存特殊物品
{
    if (szFileName == NULL )
    { return false; }

    MeXmlDocument MeXmlDoc;
    MeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = MeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pItems = pRoot->InsertEndChild(("Items"))->ToElement();
    if (pItems == NULL)
    { return false; }

    MeXmlElement *pSpecialType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pSpecialType == NULL)
    { return false; }

    pSpecialType->SetAttribute("Id",ItemDefine::ITEMTYPE_SPECIAL);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType !=ItemDefine::ITEMTYPE_SPECIAL  )
        { continue; }

        ItemDefine::SItemSpecial *pSpecialIter = (ItemDefine::SItemSpecial *)*iterBegin;

        MeXmlElement *pItem = pSpecialType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pSpecialIter->ustItemID);
        Common::_tstring strName = pSpecialIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pSpecialIter->ucItemType]);
        Common::_tstring strDescription = pSpecialIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pSpecialIter->nUseTime);
        pItem->SetAttribute("UserTarget", pSpecialIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pSpecialIter->ustLevel);
        pAppearance->SetAttribute("Rare", pSpecialIter->cItemClass);
        pAppearance->SetAttribute("Weight", pSpecialIter->fWeight);
        pAppearance->SetAttribute("IconID", pSpecialIter->ustIconId);
        Common::_tstring strIconFile = pSpecialIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pSpecialIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pSpecialIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pSpecialIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pSpecialIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pSpecialIter->nBill);
        pPrice->SetAttribute("CostType", pSpecialIter->costType);
        pPrice->SetAttribute("Cost", pSpecialIter->dwCost);
        pPrice->SetAttribute("CostItemID", pSpecialIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pSpecialIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pSpecialIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pSpecialIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pSpecialIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pSpecialIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pSpecialIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pSpecialIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pSpecialIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pSpecialIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pSpecialIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pSpecialIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pSpecialIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pSpecialIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pSpecialIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pSpecialIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pSpecialIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pSpecialIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pSpecialIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pSpecialIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pSpecialIter->nDropMaxCount);

        //宝箱属性
        MeXmlElement *pSpecial = pItem->InsertEndChild(("Special"))->ToElement();
        if (pSpecial == NULL)
        { continue; }

        pSpecial->SetAttribute("SpecialType", pSpecialIter->uchSpecialType);
        //pSpecial->SetAttribute("IsExclusive", pSpecialIter->bExclusive);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )