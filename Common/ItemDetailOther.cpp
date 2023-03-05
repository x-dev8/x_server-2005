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

bool CItemDetail::AddOtherItem( const char *szFileName )
{
    //const char* szFileName = "Other.slk";

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

        if(pCommon == NULL || pCommon->ucItemType !=ItemDefine::ITEMTYPE_OTHER)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemOther *pItemOther = (ItemDefine::SItemOther *)pCommon;

        SLK_GET_INT( pItemOther->otherType,     "OtherType"     );
        SLK_GET_INT( pItemOther->petType,       "PetType"       );

        m_vecOtherItem.push_back(pItemOther);
    }

    return true;

}

bool CItemDetailConfig::LoadOtherItem      ( MeXmlDocument *pXmlDoc, int mode )//其他
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

        ItemDefine::SItemOther *pOther = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pOther = (ItemDefine::SItemOther*)GetItemByID(itemId);
        }
        
        if ( NULL == pOther)
        { pOther = (ItemDefine::SItemOther*)AllocItem( 0, sizeof( ItemDefine::SItemOther ) );  }
        
        if( !pOther )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pOther->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pOther->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pOther->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pOther->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pOther->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pOther->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pOther->ustLevel = iValue;

        pOther->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pOther->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pOther->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pOther->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pOther->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pOther->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pOther->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pOther->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pOther->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pOther->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pOther->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pOther->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pOther->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pOther->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pOther->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pOther->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pOther->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pOther->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pOther->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pOther->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pOther->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pOther->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pOther->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pOther->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pOther->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pOther->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pOther->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pOther->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pOther->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pOther->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pOther->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pOther->nDropMaxCount = iValue;

        //加载属性
        MeXmlElement *pOtherAttr = pItemElement->FirstChildElement("Other");

        pOtherAttr->Attribute("OtherType", &iValue);
        pOther->otherType = iValue;

        pOtherAttr->Attribute("PetType", &iValue);
        pOther->petType = iValue;

        AddItemToContainer(pOther);
        m_vecOtherItem.push_back(pOther);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveOtherItem       ( const char *szFileName )//+保存其他
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

    MeXmlElement *pOtherType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pOtherType == NULL)
    { return false; }

    pOtherType->SetAttribute("Id",ItemDefine::ITEMTYPE_OTHER);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType !=ItemDefine::ITEMTYPE_OTHER  )
        { continue; }

        ItemDefine::SItemOther *pOtherIter = (ItemDefine::SItemOther *)*iterBegin;

        MeXmlElement *pItem = pOtherType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pOtherIter->ustItemID);
        Common::_tstring strName = pOtherIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pOtherIter->ucItemType]);
        Common::_tstring strDescription = pOtherIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pOtherIter->nUseTime);
        pItem->SetAttribute("UserTarget", pOtherIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pOtherIter->ustLevel);
        pAppearance->SetAttribute("Rare", pOtherIter->cItemClass);
        pAppearance->SetAttribute("Weight", pOtherIter->fWeight);
        pAppearance->SetAttribute("IconID", pOtherIter->ustIconId);
        Common::_tstring strIconFile = pOtherIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pOtherIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pOtherIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pOtherIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pOtherIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pOtherIter->nBill);
        pPrice->SetAttribute("CostType", pOtherIter->costType);
        pPrice->SetAttribute("Cost", pOtherIter->dwCost);
        pPrice->SetAttribute("CostItemID", pOtherIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pOtherIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pOtherIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pOtherIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pOtherIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pOtherIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pOtherIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pOtherIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pOtherIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pOtherIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pOtherIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pOtherIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pOtherIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pOtherIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pOtherIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pOtherIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pOtherIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pOtherIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pOtherIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pOtherIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pOtherIter->nDropMaxCount);

        //属性
        MeXmlElement *pOther = pItem->InsertEndChild(("Other"))->ToElement();
        if (pOther == NULL)
        { continue; }

        pOther->SetAttribute("OtherType", pOtherIter->otherType);
        pOther->SetAttribute("PetType", pOtherIter->petType);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )