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


bool CItemDetailConfig::LoadTaskItem       ( MeXmlDocument *pXmlDoc, int mode )//任务
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

        ItemDefine::SItemTask *pTask = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pTask = (ItemDefine::SItemTask*)GetItemByID(itemId);
        }
        
        if ( NULL == pTask)
        { pTask = (ItemDefine::SItemTask*)AllocItem( 0, sizeof( ItemDefine::SItemTask ) );  }
        
        if( !pTask )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pTask->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pTask->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pTask->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pTask->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pTask->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pTask->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pTask->ustLevel = iValue;

        pTask->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pTask->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pTask->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pTask->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pTask->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pTask->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pTask->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pTask->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pTask->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pTask->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pTask->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pTask->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pTask->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pTask->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pTask->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pTask->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pTask->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pTask->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pTask->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pTask->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pTask->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pTask->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pTask->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pTask->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pTask->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pTask->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pTask->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pTask->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pTask->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pTask->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pTask->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pTask->nDropMaxCount = iValue;

        AddItemToContainer(pTask);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveTaskItem        ( const char *szFileName )//+保存任务
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

    MeXmlElement *pTaskType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pTaskType == NULL)
    { return false; }

    pTaskType->SetAttribute("Id", ItemDefine::ITEMTYPE_TASK);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_TASK  )
        { continue; }

        ItemDefine::SItemTask *pTaskIter = (ItemDefine::SItemTask *)*iterBegin;

        MeXmlElement *pItem = pTaskType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pTaskIter->ustItemID);
        Common::_tstring strName = pTaskIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pTaskIter->ucItemType]);
        Common::_tstring strDescription = pTaskIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pTaskIter->nUseTime);
        pItem->SetAttribute("UserTarget", pTaskIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pTaskIter->ustLevel);
        pAppearance->SetAttribute("Rare", pTaskIter->cItemClass);
        pAppearance->SetAttribute("Weight", pTaskIter->fWeight);
        pAppearance->SetAttribute("IconID", pTaskIter->ustIconId);
        Common::_tstring strIconFile = pTaskIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pTaskIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pTaskIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pTaskIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pTaskIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pTaskIter->nBill);
        pPrice->SetAttribute("CostType", pTaskIter->costType);
        pPrice->SetAttribute("Cost", pTaskIter->dwCost);
        pPrice->SetAttribute("CostItemID", pTaskIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pTaskIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pTaskIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pTaskIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pTaskIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pTaskIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pTaskIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pTaskIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pTaskIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pTaskIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pTaskIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pTaskIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pTaskIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pTaskIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pTaskIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pTaskIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pTaskIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pTaskIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pTaskIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pTaskIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pTaskIter->nDropMaxCount);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )