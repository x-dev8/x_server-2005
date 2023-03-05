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

bool CItemDetail::AddReelItem( const char *szFileName )
{
    //const char* szFileName = "reel.slk";

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

        if(pCommon == NULL || pCommon->ucItemType !=ItemDefine::ITEMTYPE_REEL)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemReel *pItemReel = (ItemDefine::SItemReel *)pCommon;
    
        SLK_GET_INT( pItemReel->skillId,      "SkillId"      );
        SLK_GET_INT( pItemReel->skillLevel,   "SkillLevel"   );

        char  szTemp[256] = {0};
        for ( int i=0; i< ItemDefine::SItemReel::ECD_RatioMaxSize; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "ReplaceRatio%d", i+1 );
            SLK_GET_INT( pItemReel->replaceRatio[i], szTemp );
        }

        SLK_GET_INT( pItemReel->mountTakeLevel,   "MountTakeLevel"  );
        SLK_GET_INT( pItemReel->mountLevel,       "MountLevel"      );

        SLK_GET_INT( pItemReel->petTakeLevel,     "PetTakeLevel"    );
        SLK_GET_INT( pItemReel->petLevel,         "PetLevel"        );
        SLK_GET_INT( pItemReel->costMoney,        "CostMoney"       );
        
        m_vecReelItem.push_back(pItemReel);
    }

    return true;

}


bool CItemDetailConfig::LoadReelItem       ( MeXmlDocument *pXmlDoc, int mode )//卷轴
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

        ItemDefine::SItemReel *pReel = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pReel = (ItemDefine::SItemReel*)GetItemByID(itemId);
        }
        
        if( NULL == pReel )
        {  pReel = (ItemDefine::SItemReel*)AllocItem( 0, sizeof( ItemDefine::SItemReel ) );  }

        if( !pReel )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pReel->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pReel->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pReel->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pReel->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pReel->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pReel->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pReel->ustLevel = iValue;

        pReel->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pReel->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pReel->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pReel->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pReel->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pReel->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pReel->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pReel->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pReel->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pReel->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pReel->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pReel->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pReel->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pReel->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pReel->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pReel->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pReel->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pReel->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pReel->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pReel->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pReel->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pReel->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pReel->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pReel->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pReel->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pReel->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pReel->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pReel->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pReel->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pReel->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pReel->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pReel->nDropMaxCount = iValue;

        //加载卷轴属性
        MeXmlElement *pReelAttr = pItemElement->FirstChildElement("Reel");

        pReelAttr->Attribute("SkillId", &iValue);
        pReel->skillId = iValue;

        pReelAttr->Attribute("SkillLevel", &iValue);
        pReel->skillLevel = iValue;

        char  szTemp[256] = {0};
        for ( int i=0; i< ItemDefine::SItemReel::ECD_RatioMaxSize; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "ReplaceRatio%d", i+1 );
            pReelAttr->Attribute(szTemp, &iValue);
            pReel->replaceRatio[i] = iValue;
        }

        pReelAttr->Attribute("MountTakeLevel", &iValue);
        pReel->mountTakeLevel = iValue;

        pReelAttr->Attribute("MountLevel", &iValue);
        pReel->mountLevel = iValue;

        pReelAttr->Attribute("PetTakeLevel", &iValue);
        pReel->petTakeLevel = iValue;

        pReelAttr->Attribute("PetLevel", &iValue);
        pReel->petLevel = iValue;

        pReelAttr->Attribute("CostMoney", &iValue);
        pReel->costMoney = iValue;

        AddItemToContainer(pReel);

        m_vecReelItem.push_back(pReel);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveReelItem        ( const char *szFileName )//+保存卷轴
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

    MeXmlElement *pReelType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pReelType == NULL)
    { return false; }

    pReelType->SetAttribute("Id",ItemDefine::ITEMTYPE_REEL);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType !=ItemDefine::ITEMTYPE_REEL  )
        { continue; }

        ItemDefine::SItemReel *pReelIter = (ItemDefine::SItemReel *)*iterBegin;

        MeXmlElement *pItem = pReelType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pReelIter->ustItemID);
        Common::_tstring strName = pReelIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pReelIter->ucItemType]);
        Common::_tstring strDescription = pReelIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pReelIter->nUseTime);
        pItem->SetAttribute("UserTarget", pReelIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pReelIter->ustLevel);
        pAppearance->SetAttribute("Rare", pReelIter->cItemClass);
        pAppearance->SetAttribute("Weight", pReelIter->fWeight);
        pAppearance->SetAttribute("IconID", pReelIter->ustIconId);
        Common::_tstring strIconFile = pReelIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pReelIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pReelIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pReelIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pReelIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pReelIter->nBill);
        pPrice->SetAttribute("CostType", pReelIter->costType);
        pPrice->SetAttribute("Cost", pReelIter->dwCost);
        pPrice->SetAttribute("CostItemID", pReelIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pReelIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pReelIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pReelIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pReelIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pReelIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pReelIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pReelIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pReelIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pReelIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pReelIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pReelIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pReelIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pReelIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pReelIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pReelIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pReelIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pReelIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pReelIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pReelIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pReelIter->nDropMaxCount);

        //卷轴属性
        MeXmlElement *pReel = pItem->InsertEndChild(("Reel"))->ToElement();
        if (pReel == NULL)
        { continue; }

        pReel->SetAttribute("SkillId", pReelIter->skillId);
        pReel->SetAttribute("SkillLevel", pReelIter->skillLevel);
        
        char  szTemp[256] = {0};
        for ( int i=0; i< ItemDefine::SItemReel::ECD_RatioMaxSize; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "ReplaceRatio%d", i+1 );
            pReel->SetAttribute(szTemp, pReelIter->replaceRatio[i]);
        }

        pReel->SetAttribute("MountTakeLevel", pReelIter->mountTakeLevel);
        pReel->SetAttribute("MountLevel", pReelIter->mountLevel);

        pReel->SetAttribute("PetTakeLevel", pReelIter->petTakeLevel);
        pReel->SetAttribute("PetLevel",     pReelIter->petLevel);
        pReel->SetAttribute("CostMoney",    pReelIter->costMoney);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )