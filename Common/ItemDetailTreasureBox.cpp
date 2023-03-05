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

bool CItemDetail::AddTreasureBoxItem( const char *szFileName )
{
    //const char* szFileName = "TreasureBox.slk";

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

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_TREASUREBOX)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false; 
        }

        ItemDefine::SItemTreasureBox *pItemTreasureBox = (ItemDefine::SItemTreasureBox *)pCommon;
 
        SLK_GET_INT( pItemTreasureBox->uchBoxType, "BoxType");
        SLK_GET_INT( pItemTreasureBox->uchLevel, "BoxLevel");
        SLK_GET_INT( pItemTreasureBox->ustCorrItemID, "CorrItemID");
        SLK_GET_INT( pItemTreasureBox->ustNewItemID, "NewItemID" );
        

        m_vecTreasureBoxItem.push_back(pItemTreasureBox);
    }

    return true;

}


bool CItemDetailConfig::LoadTreasureBoxItem( MeXmlDocument *pXmlDoc, int mode )//宝箱
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

        ItemDefine::SItemTreasureBox *pTreasureBox = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pTreasureBox =  (ItemDefine::SItemTreasureBox*)GetItemByID(itemId);
        }
        
        if ( NULL == pTreasureBox)
        { pTreasureBox = (ItemDefine::SItemTreasureBox*)AllocItem( 0, sizeof( ItemDefine::SItemTreasureBox ) ); }
        
        if( !pTreasureBox )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pTreasureBox->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pTreasureBox->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pTreasureBox->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pTreasureBox->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pTreasureBox->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pTreasureBox->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pTreasureBox->ustLevel = iValue;

        pTreasureBox->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pTreasureBox->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pTreasureBox->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pTreasureBox->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pTreasureBox->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pTreasureBox->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pTreasureBox->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pTreasureBox->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pTreasureBox->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pTreasureBox->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pTreasureBox->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pTreasureBox->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pTreasureBox->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pTreasureBox->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pTreasureBox->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pTreasureBox->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pTreasureBox->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pTreasureBox->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pTreasureBox->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pTreasureBox->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pTreasureBox->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pTreasureBox->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pTreasureBox->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pTreasureBox->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pTreasureBox->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pTreasureBox->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pTreasureBox->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pTreasureBox->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pTreasureBox->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pTreasureBox->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pTreasureBox->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pTreasureBox->nDropMaxCount = iValue;

        //加载宝箱属性
        MeXmlElement *pTreasureBoxAttr = pItemElement->FirstChildElement("TreasureBox");

        pTreasureBoxAttr->Attribute("BoxType", &iValue);
        pTreasureBox->uchBoxType = iValue;

        pTreasureBoxAttr->Attribute("BoxLevel", &iValue);
        pTreasureBox->uchLevel = iValue;

        pTreasureBoxAttr->Attribute("CorrItemID", &iValue);
        pTreasureBox->ustCorrItemID = iValue;

        pTreasureBoxAttr->Attribute("NewItemID", &iValue);
        pTreasureBox->ustNewItemID = iValue;

        m_vecTreasureBoxItem.push_back(pTreasureBox);

        AddItemToContainer(pTreasureBox);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveTreasureBoxItem ( const char *szFileName )//+保存宝箱
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

    MeXmlElement *pTreasureBoxType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pTreasureBoxType == NULL)
    { return false; }

    pTreasureBoxType->SetAttribute("Id", ItemDefine::ITEMTYPE_TREASUREBOX);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_TREASUREBOX  )
        { continue; }

        ItemDefine::SItemTreasureBox *pTreasureBoxIter = (ItemDefine::SItemTreasureBox *)*iterBegin;

        MeXmlElement *pItem = pTreasureBoxType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pTreasureBoxIter->ustItemID);
        Common::_tstring strName = pTreasureBoxIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pTreasureBoxIter->ucItemType]);
        Common::_tstring strDescription = pTreasureBoxIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pTreasureBoxIter->nUseTime);
        pItem->SetAttribute("UserTarget", pTreasureBoxIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pTreasureBoxIter->ustLevel);
        pAppearance->SetAttribute("Rare", pTreasureBoxIter->cItemClass);
        pAppearance->SetAttribute("Weight", pTreasureBoxIter->fWeight);
        pAppearance->SetAttribute("IconID", pTreasureBoxIter->ustIconId);
        Common::_tstring strIconFile = pTreasureBoxIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pTreasureBoxIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pTreasureBoxIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pTreasureBoxIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pTreasureBoxIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pTreasureBoxIter->nBill);
        pPrice->SetAttribute("CostType", pTreasureBoxIter->costType);
        pPrice->SetAttribute("Cost", pTreasureBoxIter->dwCost);
        pPrice->SetAttribute("CostItemID", pTreasureBoxIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pTreasureBoxIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pTreasureBoxIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pTreasureBoxIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pTreasureBoxIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pTreasureBoxIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pTreasureBoxIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pTreasureBoxIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pTreasureBoxIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pTreasureBoxIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pTreasureBoxIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pTreasureBoxIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pTreasureBoxIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pTreasureBoxIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pTreasureBoxIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pTreasureBoxIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pTreasureBoxIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pTreasureBoxIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pTreasureBoxIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pTreasureBoxIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pTreasureBoxIter->nDropMaxCount);

        //宝箱属性
        MeXmlElement *pBox = pItem->InsertEndChild(("TreasureBox"))->ToElement();
        if (pBox == NULL)
        { continue; }

        pBox->SetAttribute("BoxType", pTreasureBoxIter->uchBoxType);
        pBox->SetAttribute("BoxLevel", pTreasureBoxIter->uchLevel);
        pBox->SetAttribute("CorrItemID", pTreasureBoxIter->ustCorrItemID);
        pBox->SetAttribute("NewItemID", pTreasureBoxIter->ustNewItemID);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )