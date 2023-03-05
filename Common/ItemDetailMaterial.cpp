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

bool CItemDetail::AddMaterialItem( const char *szFileName )
{
    //const char* szFileName = "material.slk";

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

    float fValue = 0.0f;
    int   iValue = 0;
    std::string strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"ItemID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 RestoreID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_MATERIAL)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false; 
        }

        ItemDefine::SCreateMaterial *pItemMaterial = (ItemDefine::SCreateMaterial *)pCommon;

        SLK_GET_INT  ( pItemMaterial->stMaterialType,    "MaterialType"     );
        SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[0], "AddIntensifyRate1" );
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[1], "AddIntensifyRate2" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[2], "AddIntensifyRate3" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[3], "AddIntensifyRate4" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[4], "AddIntensifyRate5" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[5], "AddIntensifyRate6" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[6], "AddIntensifyRate7" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[7], "AddIntensifyRate8" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[8], "AddIntensifyRate9" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[9], "AddIntensifyRate10" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[10], "AddIntensifyRate11" );
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[11], "AddIntensifyRate12" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[12], "AddIntensifyRate13" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[13], "AddIntensifyRate14" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[14], "AddIntensifyRate15" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[15], "AddIntensifyRate16" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[16], "AddIntensifyRate17" ); 
		SLK_GET_FLOAT( pItemMaterial->fAddIntensifyRate[17], "AddIntensifyRate18" ); 

        SLK_GET_INT  ( pItemMaterial->useLevel,             "CharUseLevel"      );
        SLK_GET_INT  ( pItemMaterial->levelLowLimit,        "LevelLowLimit"     );
        SLK_GET_INT  ( pItemMaterial->levelUpLimit ,        "LevelUpLimit"      );
        SLK_GET_INT  ( pItemMaterial->starLevelLimit,       "StarLevelLimit"    );
        SLK_GET_INT  ( pItemMaterial->useCostMoney,         "UseCostMoney"      );
        SLK_GET_INT  ( pItemMaterial->equipQuality,         "EquipQuality"      );

        // 上限为 0 设置值为 255
        if ( pItemMaterial->levelUpLimit == 0 ) { pItemMaterial->levelUpLimit = 0xFF; }

        pItemMaterial->effectEquipPart = 0;
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
            { _SET_FLAG( pItemMaterial->effectEquipPart, 1 << equipPart ); }
            szStr = strtok( NULL,szSpn );
        }

        SLK_GET_INT( pItemMaterial->nValue, "Value" );

        m_vecMaterialItem.push_back(pItemMaterial);
    }

    return true;
    
}


bool CItemDetailConfig::LoadMaterialItem   ( MeXmlDocument *pXmlDoc, int mode )//材料
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

        ItemDefine::SCreateMaterial *pMaterial = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pMaterial = (ItemDefine::SCreateMaterial*)GetItemByID(itemId);
        }
        
        if ( NULL == pMaterial)
        { pMaterial = (ItemDefine::SCreateMaterial*)AllocItem( 0, sizeof( ItemDefine::SCreateMaterial ) ); }
        
        if( !pMaterial )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pMaterial->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pMaterial->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pMaterial->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pMaterial->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pMaterial->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pMaterial->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pMaterial->ustLevel = iValue;

        pMaterial->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pMaterial->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pMaterial->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pMaterial->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pMaterial->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pMaterial->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pMaterial->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pMaterial->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pMaterial->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pMaterial->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pMaterial->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pMaterial->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pMaterial->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pMaterial->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pMaterial->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pMaterial->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pMaterial->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pMaterial->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pMaterial->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pMaterial->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pMaterial->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pMaterial->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pMaterial->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pMaterial->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pMaterial->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pMaterial->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pMaterial->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pMaterial->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pMaterial->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pMaterial->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pMaterial->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pMaterial->nDropMaxCount = iValue;

        //加载原料属性
        MeXmlElement *pMaterialAttr = pItemElement->FirstChildElement("Material");

        pMaterialAttr->Attribute("MaterialType", &iValue);
        pMaterial->stMaterialType = iValue;

        pMaterialAttr->Attribute("AddIntensifyRate1", &dValue);
        pMaterial->fAddIntensifyRate[0] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate2", &dValue);
		pMaterial->fAddIntensifyRate[1] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate3", &dValue);
		pMaterial->fAddIntensifyRate[2] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate4", &dValue);
		pMaterial->fAddIntensifyRate[3] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate5", &dValue);
		pMaterial->fAddIntensifyRate[4] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate6", &dValue);
		pMaterial->fAddIntensifyRate[5] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate7", &dValue);
		pMaterial->fAddIntensifyRate[6] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate8", &dValue);
		pMaterial->fAddIntensifyRate[7] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate9", &dValue);
		pMaterial->fAddIntensifyRate[8] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate10", &dValue);
		pMaterial->fAddIntensifyRate[9] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate11", &dValue);
		pMaterial->fAddIntensifyRate[10] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate12", &dValue);
		pMaterial->fAddIntensifyRate[11] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate13", &dValue);
		pMaterial->fAddIntensifyRate[12] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate14", &dValue);
		pMaterial->fAddIntensifyRate[13] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate15", &dValue);
		pMaterial->fAddIntensifyRate[14] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate16", &dValue);
		pMaterial->fAddIntensifyRate[15] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate17", &dValue);
		pMaterial->fAddIntensifyRate[16] = dValue;
		pMaterialAttr->Attribute("AddIntensifyRate18", &dValue);
		pMaterial->fAddIntensifyRate[17] = dValue;

        pMaterialAttr->Attribute("CharUseLevel", &iValue);
        pMaterial->useLevel = iValue;

        pMaterialAttr->Attribute("LevelLowLimit", &iValue);
        pMaterial->levelLowLimit = iValue;

        pMaterialAttr->Attribute("LevelUpLimit", &iValue);
        pMaterial->levelUpLimit = iValue;

        // 上限为 0 设置值为 255
        if ( pMaterial->levelUpLimit == 0 ) { pMaterial->levelUpLimit = 0xFF; }

        pMaterialAttr->Attribute("StarLevelLimit", &iValue);
        pMaterial->starLevelLimit = iValue;

        pMaterialAttr->Attribute("UseCostMoney", &iValue);
        pMaterial->useCostMoney = iValue;

        pMaterialAttr->Attribute("EquipQuality", &iValue);
        pMaterial->equipQuality = iValue;

        pMaterial->effectEquipPart = 0;
        Common::_tstring strValue;
        strValue.fromUTF8( pMaterialAttr->Attribute("EffectEquipPart") );

        // 适用多个装备
        char* szSpn = ",";
        char* szStr;
        int equipPart =ItemDefine::equip_TypeMaxCount;
        szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
        while( szStr )
        {
            equipPart = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szEquipType, sizeof( ItemDefine::g_szEquipType )/sizeof(char*) );
            if( equipPart >= 0 && equipPart <ItemDefine::equip_TypeMaxCount )
            { _SET_FLAG( pMaterial->effectEquipPart, 1 << equipPart ); }
            szStr = strtok( NULL,szSpn );
        }

        pMaterialAttr->Attribute("Value", &iValue);
        pMaterial->nValue = iValue;

        AddItemToContainer(pMaterial);

        m_vecMaterialItem.push_back(pMaterial);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveMaterialItem    ( const char *szFileName )//+保存材料
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

    MeXmlElement *pMaterialType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pMaterialType == NULL)
    { return false; }

    pMaterialType->SetAttribute("Id", ItemDefine::ITEMTYPE_MATERIAL);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_MATERIAL  )
        { continue; }

        ItemDefine::SCreateMaterial *pMaterialIter = (ItemDefine::SCreateMaterial *)*iterBegin;

        MeXmlElement *pItem = pMaterialType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pMaterialIter->ustItemID);
        Common::_tstring strName = pMaterialIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pMaterialIter->ucItemType]);
        Common::_tstring strDescription = pMaterialIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pMaterialIter->nUseTime);
        pItem->SetAttribute("UserTarget", pMaterialIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pMaterialIter->ustLevel);
        pAppearance->SetAttribute("Rare", pMaterialIter->cItemClass);
        pAppearance->SetAttribute("Weight", pMaterialIter->fWeight);
        pAppearance->SetAttribute("IconID", pMaterialIter->ustIconId);
        Common::_tstring strIconFile = pMaterialIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pMaterialIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pMaterialIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pMaterialIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pMaterialIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pMaterialIter->nBill);
        pPrice->SetAttribute("CostType", pMaterialIter->costType);
        pPrice->SetAttribute("Cost", pMaterialIter->dwCost);
        pPrice->SetAttribute("CostItemID", pMaterialIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pMaterialIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pMaterialIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pMaterialIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pMaterialIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pMaterialIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pMaterialIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pMaterialIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pMaterialIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pMaterialIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pMaterialIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pMaterialIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pMaterialIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pMaterialIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pMaterialIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pMaterialIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pMaterialIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pMaterialIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pMaterialIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pMaterialIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pMaterialIter->nDropMaxCount);

        //原料属性
        MeXmlElement *pMaterial = pItem->InsertEndChild(("Material"))->ToElement();
        if (pMaterial == NULL)
        { continue; }

        pMaterial->SetAttribute("MaterialType", pMaterialIter->stMaterialType);
        pMaterial->SetDoubleAttribute("AddIntensifyRate1", pMaterialIter->fAddIntensifyRate[0]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate2", pMaterialIter->fAddIntensifyRate[1]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate3", pMaterialIter->fAddIntensifyRate[2]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate4", pMaterialIter->fAddIntensifyRate[3]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate5", pMaterialIter->fAddIntensifyRate[4]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate6", pMaterialIter->fAddIntensifyRate[5]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate7", pMaterialIter->fAddIntensifyRate[6]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate8", pMaterialIter->fAddIntensifyRate[7]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate9", pMaterialIter->fAddIntensifyRate[8]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate10", pMaterialIter->fAddIntensifyRate[9]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate11", pMaterialIter->fAddIntensifyRate[10]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate12", pMaterialIter->fAddIntensifyRate[11]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate13", pMaterialIter->fAddIntensifyRate[12]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate14", pMaterialIter->fAddIntensifyRate[13]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate15", pMaterialIter->fAddIntensifyRate[14]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate16", pMaterialIter->fAddIntensifyRate[15]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate17", pMaterialIter->fAddIntensifyRate[16]);
		pMaterial->SetDoubleAttribute("AddIntensifyRate18", pMaterialIter->fAddIntensifyRate[17]);
        pMaterial->SetAttribute("CharUseLevel", pMaterialIter->useLevel);
        pMaterial->SetAttribute("LevelLowLimit", pMaterialIter->levelLowLimit);
        pMaterial->SetAttribute("LevelUpLimit", pMaterialIter->levelUpLimit);
        pMaterial->SetAttribute("StarLevelLimit", pMaterialIter->starLevelLimit);
        pMaterial->SetAttribute("UseCostMoney", pMaterialIter->useCostMoney);
        pMaterial->SetAttribute("EquipQuality", pMaterialIter->equipQuality);

        Common::_tstring strValue;
        for ( int8 i=0; i<ItemDefine::equip_TypeMaxCount; ++i )
        {
            if ( _HAS_FLAG( pMaterialIter->effectEquipPart, 1 << i))
            {
               strValue += ItemDefine::g_szEquipType[i];
               strValue +=",";
            }
        }
        pMaterial->SetAttribute( "EffectEquipPart", strValue.toUTF8().c_str());
        pMaterial->SetAttribute( "Value",           pMaterialIter->nValue );
    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )