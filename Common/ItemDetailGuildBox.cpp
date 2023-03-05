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

bool CItemDetail::AddGuildBoxItem( const char *szFileName )
{
    //const char* szFileName = "GuildItem.slk";

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
        if( !GetIntField( &pReader,"GuildItemId",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 ItemID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_GUILD)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;  
        }

        ItemDefine::SItemGuild *pItemGuild = (ItemDefine::SItemGuild *)pCommon;

        SLK_GET_INT( pItemGuild->uchType, "GuildItemType" );
        SLK_GET_INT( pItemGuild->nValue1, "Value1" );
        SLK_GET_INT( pItemGuild->nValue2, "Value2" );
        
        m_vecGuildBoxItem.push_back(pItemGuild);
    }

    return true;
    
}


bool CItemDetailConfig::LoadGuildBoxItem   ( MeXmlDocument *pXmlDoc, int mode )//工会宝箱
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

        ItemDefine::SItemGuild *pGuild = NULL;
        
        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pGuild = (ItemDefine::SItemGuild*)GetItemByID(itemId);
        }
        
        if ( NULL == pGuild)
        { pGuild = (ItemDefine::SItemGuild*)AllocItem( 0, sizeof( ItemDefine::SItemGuild ) ); }
        
        if( !pGuild )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pGuild->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pGuild->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pGuild->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pGuild->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pGuild->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pGuild->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pGuild->ustLevel = iValue;

        pGuild->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pGuild->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pGuild->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pGuild->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pGuild->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pGuild->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pGuild->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pGuild->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pGuild->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pGuild->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pGuild->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pGuild->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pGuild->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pGuild->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pGuild->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pGuild->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pGuild->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pGuild->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pGuild->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pGuild->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pGuild->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pGuild->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pGuild->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pGuild->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pGuild->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pGuild->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pGuild->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pGuild->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pGuild->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pGuild->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pGuild->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pGuild->nDropMaxCount = iValue;

        //加载道具属性
        MeXmlElement *pGuildAttr = pItemElement->FirstChildElement("Guild");

        pGuildAttr->Attribute("GuildItemType", &iValue);
        pGuild->uchType = iValue;

        pGuildAttr->Attribute("Value1", &iValue);
        pGuild->nValue1 = iValue;

        pGuildAttr->Attribute("Value2", &iValue);
        pGuild->nValue2 = iValue;

        m_vecGuildBoxItem.push_back(pGuild);

        AddItemToContainer(pGuild);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveGuildBoxItem    ( const char *szFileName )//+保存工会宝箱
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

    MeXmlElement *pGuildType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pGuildType == NULL)
    { return false; }

    pGuildType->SetAttribute("Id", ItemDefine::ITEMTYPE_GUILD);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_GUILD  )
        { continue; }

        ItemDefine::SItemGuild *pGuildIter = (ItemDefine::SItemGuild *)*iterBegin;

        MeXmlElement *pItem = pGuildType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pGuildIter->ustItemID);
        Common::_tstring strName = pGuildIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pGuildIter->ucItemType]);
        Common::_tstring strDescription = pGuildIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pGuildIter->nUseTime);
        pItem->SetAttribute("UserTarget", pGuildIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pGuildIter->ustLevel);
        pAppearance->SetAttribute("Rare", pGuildIter->cItemClass);
        pAppearance->SetAttribute("Weight", pGuildIter->fWeight);
        pAppearance->SetAttribute("IconID", pGuildIter->ustIconId);
        Common::_tstring strIconFile = pGuildIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pGuildIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pGuildIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pGuildIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pGuildIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pGuildIter->nBill);
        pPrice->SetAttribute("CostType", pGuildIter->costType);
        pPrice->SetAttribute("Cost", pGuildIter->dwCost);
        pPrice->SetAttribute("CostItemID", pGuildIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pGuildIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pGuildIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pGuildIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pGuildIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pGuildIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pGuildIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pGuildIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pGuildIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pGuildIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pGuildIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pGuildIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pGuildIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pGuildIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pGuildIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pGuildIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pGuildIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pGuildIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pGuildIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pGuildIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pGuildIter->nDropMaxCount);

        //宝箱属性
        MeXmlElement *pGuild = pItem->InsertEndChild(("Guild"))->ToElement();
        if (pGuild == NULL)
        { continue; }

        pGuild->SetAttribute("GuildItemType", pGuildIter->uchType);
        pGuild->SetAttribute("Value1", pGuildIter->nValue1);
        pGuild->SetAttribute("Value2", pGuildIter->nValue2);

    }

    return MeXmlDoc.SaveFile(szFileName);
}


#pragma warning( pop )