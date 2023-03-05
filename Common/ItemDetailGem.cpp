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

bool CItemDetail::AddGemItem( const char *szFileName  )
{
    CSlkReader pReader;
    OutputSlkLoadingMessage( "正在分析%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "找不到%s文件\r\n",szFileName);
        return false;
    }
    
    int offset = 3;
    int iRet;
    int iCol;

    int   iValue = 0;
    float fValue = 0.0f;
    std::string strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"ItemId",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 ItemId 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon* pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_GEM)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
        }

        ItemDefine::SItemGem* pItemGem = (ItemDefine::SItemGem*)pCommon;

        pItemGem->effectEquipPart = 0;
        SLK_GET_STRING( strValue, "EffectEquipPart");
        // 适用多个装备
        char *szSpn = ",";
        char *szStr;
        int equipPart =ItemDefine::equip_TypeMaxCount;
        szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
        while( szStr )
        {
            equipPart = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szEquipType, sizeof( ItemDefine::g_szEquipType )/sizeof(char*) );
            if( equipPart >= 0 && equipPart <ItemDefine::equip_TypeMaxCount )
            { _SET_FLAG( pItemGem->effectEquipPart, 1 << equipPart ); }
            szStr = strtok( NULL,szSpn );
        }

        SLK_GET_INT( pItemGem->gemType, "GemType");
        SLK_GET_INT( pItemGem->gemLevel, "GemLevel");
        SLK_GET_INT( pItemGem->preGemId, "PreGemId");
        SLK_GET_INT( pItemGem->preGemType, "PreGemType");
        SLK_GET_INT( pItemGem->useCostMoney, "UseCostMoney");
        SLK_GET_INT( pItemGem->levelLimit, "LevelLimit");

        for ( int i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            SLK_GET_INT( iValue, szTypeTmp);
            pItemGem->type[i] = iValue;

            SLK_GET_FLOAT( fValue, szValueTmp);
            pItemGem->value[i].fValue = fValue;
        }

        m_vecGemItem.push_back(pItemGem);
    }

    return true;
}

bool CItemDetailConfig::LoadGemItem( MeXmlDocument *pXmlDoc, int mode )//宝石
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
    double dValue = 0.0f;

    while ( pItemElement != NULL )
    {
        int itemId = 0;
        pItemElement->Attribute("Id", &itemId);

        ItemDefine::SItemGem *pGem = NULL ;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pGem = (ItemDefine::SItemGem*)GetItemByID(itemId);
        }
        
        if ( NULL == pGem )
        { pGem = (ItemDefine::SItemGem*)AllocItem( 0, sizeof( ItemDefine::SItemGem ) ); }
        
        if( !pGem )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pGem->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pGem->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pGem->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pGem->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pGem->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pGem->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pGem->ustLevel = iValue;

        pGem->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pGem->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pGem->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pGem->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pGem->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pGem->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pGem->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pGem->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pGem->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pGem->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pGem->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pGem->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pGem->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pGem->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pGem->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pGem->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pGem->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pGem->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pGem->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pGem->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pGem->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pGem->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pGem->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pGem->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pGem->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pGem->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pGem->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pGem->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pGem->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pGem->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pGem->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pGem->nDropMaxCount = iValue;

        //////////////////////////////////////////////////////////////////////////
        // 宝石属性
        MeXmlElement* pGemAttr = pItemElement->FirstChildElement("Gem");
        if (pGemAttr == NULL)
        { continue; }

        pGem->effectEquipPart = 0;
        Common::_tstring strEffectEquipPart;
        strEffectEquipPart.fromUTF8( pGemAttr->Attribute("EffectEquipPart") );
        // 适用多个装备
        char *szSpn = ",";
        char *szStr;
        int equipPart =ItemDefine::equip_TypeMaxCount;
        szStr = strtok( const_cast<char*>(strEffectEquipPart.c_str()),szSpn );
        while( szStr )
        {
            equipPart = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szEquipType, sizeof( ItemDefine::g_szEquipType )/sizeof(char*) );
            if( equipPart >= 0 && equipPart <ItemDefine::equip_TypeMaxCount )
            { _SET_FLAG( pGem->effectEquipPart, 1 << equipPart ); }
            szStr = strtok( NULL,szSpn );
        }

        pGemAttr->Attribute("GemType", &iValue);
        pGem->gemType = iValue;

        pGemAttr->Attribute("GemLevel", &iValue);
        pGem->gemLevel = iValue;

        pGemAttr->Attribute("PreGemId", &iValue);
        pGem->preGemId = iValue;

        pGemAttr->Attribute("PreGemType", &iValue);
        pGem->preGemType = iValue;

        pGemAttr->Attribute("UseCostMoney", &iValue);
        pGem->useCostMoney = iValue;

        pGemAttr->Attribute("LevelLimit", &iValue);
        pGem->levelLimit = iValue;

        for ( uint8 i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            pGemAttr->Attribute(szTypeTmp, &iValue);
            pGem->type[i] = iValue;

            pGemAttr->Attribute( szValueTmp, &dValue );
            pGem->value[i].fValue = dValue;
        }

		pGemAttr->Attribute("DownGradeID", &iValue);
		pGem->downGradeID = iValue;

        m_vecGemItem.push_back(pGem);

        AddItemToContainer(pGem);

        pItemElement = pItemElement->NextSiblingElement();
    }

    return true;
}


bool CItemDetailConfig::SaveGemItem         ( const char *szFileName )//+保存宝石
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

    MeXmlElement *pGemType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pGemType == NULL)
    { return false; }

	pGemType->SetAttribute("Id", ItemDefine::ITEMTYPE_GEM);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_GEM  )
        { continue; }

        ItemDefine::SItemGem *pGemIter = (ItemDefine::SItemGem *)*iterBegin;

        MeXmlElement *pItem = pGemType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pGemIter->ustItemID);
        Common::_tstring strName = pGemIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pGemIter->ucItemType]);
        Common::_tstring strDescription = pGemIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pGemIter->nUseTime);
        pItem->SetAttribute("UserTarget", pGemIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pGemIter->ustLevel);
        pAppearance->SetAttribute("Rare", pGemIter->cItemClass);
        pAppearance->SetAttribute("Weight", pGemIter->fWeight);
        pAppearance->SetAttribute("IconID", pGemIter->ustIconId);
        Common::_tstring strIconFile = pGemIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pGemIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pGemIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pGemIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pGemIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pGemIter->nBill);
        pPrice->SetAttribute("CostType", pGemIter->costType);
        pPrice->SetAttribute("Cost", pGemIter->dwCost);
        pPrice->SetAttribute("CostItemID", pGemIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pGemIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pGemIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pGemIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pGemIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pGemIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pGemIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pGemIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pGemIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pGemIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pGemIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pGemIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pGemIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pGemIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pGemIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pGemIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pGemIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pGemIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pGemIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pGemIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pGemIter->nDropMaxCount);

        //宝石属性
        MeXmlElement* pGemAttr = pItem->InsertEndChild(("Gem"))->ToElement();
        if (pGemAttr == NULL)
        { continue; }

        Common::_tstring strValue;
        for ( int8 i=0; i<ItemDefine::equip_TypeMaxCount; ++i )
        {
            if ( _HAS_FLAG( pGemIter->effectEquipPart, 1 << i))
            {
                strValue += ItemDefine::g_szEquipType[i];
                strValue += ",";
            }
        }
        pGemAttr->SetAttribute( "EffectEquipPart", strValue.toUTF8().c_str());

        pGemAttr->SetAttribute( "GemType"     , pGemIter->gemType       );
        pGemAttr->SetAttribute( "GemLevel"    , pGemIter->gemLevel      );
        pGemAttr->SetAttribute( "PreGemId"    , pGemIter->preGemId      );
        pGemAttr->SetAttribute( "PreGemType"  , pGemIter->preGemType    );
        pGemAttr->SetAttribute( "UseCostMoney", pGemIter->useCostMoney  );
        pGemAttr->SetAttribute( "LevelLimit"  , pGemIter->levelLimit    );

        for ( int i=0; i < ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            pGemAttr->SetAttribute(szTypeTmp, pGemIter->type[i]);
            pGemAttr->SetDoubleAttribute(szValueTmp, pGemIter->value[i].fValue);
        }
    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )