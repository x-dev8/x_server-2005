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

bool CItemDetail::AddTalismanItem( const char *szFileName )
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

        if(pCommon == NULL || pCommon->ucItemType !=ItemDefine::ITEMTYPE_TALISMAN)
        {
            OutputSlkLoadingMessage( "%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;  
        }

        ItemDefine::SItemTalisman *pItemTalisman = (ItemDefine::SItemTalisman *)pCommon;

        SLK_GET_INT( pItemTalisman->iModelID, "ModelID");
        SLK_GET_INT( pItemTalisman->iSexReq,  "NeedSex");

        // 兵种需求
        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        { pItemTalisman->arrayEquipArmsReq[ iLoop ] = false; }

        SLK_GET_STRING( strValue, "NeedArms");
        if ( strValue.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pItemTalisman->arrayEquipArmsReq[ iLoop ] = true;
            }
        }
        else
        {  
            //适用多个职业
            char *szSpn = ",";
            char *szStr;
            int iEquip;
            szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
            while( szStr )
            {

                iEquip = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iEquip >= 0 && iEquip < EArmType_MaxSize )
                {
                    pItemTalisman->arrayEquipArmsReq[ iEquip ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        // 等级需求
        SLK_GET_INT( pItemTalisman->iEquipLevelReq,    "NeedLevel");

        // 法宝修炼属性池
        SLK_GET_INT( pItemTalisman->poolId,         "PoolID"        );

        SLK_GET_INT( pItemTalisman->skillId,        "SkillID"       );
        SLK_GET_INT( pItemTalisman->skillLevel,     "SkillLevel"    );

        // 道行
        SLK_GET_INT( pItemTalisman->daoxing,        "Daoxing"       );
        SLK_GET_INT( pItemTalisman->nimbusMax,      "NimbusMax"     );
        SLK_GET_INT( pItemTalisman->nimbusRestore,  "NimbusRestore" );
        

        m_vecTalismanItem.push_back(pItemTalisman);
    }

    return true;
    
}


bool CItemDetailConfig::LoadTalismanItem    ( MeXmlDocument *pXmlDoc, int mode ) 
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
    Common::_tstring strValue;

    MeXmlElement *pItemElement = pItemsType->FirstChildElement("Item");
    while ( pItemElement != NULL )
    {
        int itemId = 0;
        pItemElement->Attribute("Id", &itemId);

        ItemDefine::SItemTalisman *pTalisman = NULL;
        
        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pTalisman = (ItemDefine::SItemTalisman*)GetItemByID(itemId);
        }
        
        if ( NULL == pTalisman )
        { pTalisman = (ItemDefine::SItemTalisman*)AllocItem( 0, sizeof( ItemDefine::SItemTalisman ) ); }
        
        if( !pTalisman )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pTalisman->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pTalisman->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pTalisman->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pTalisman->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pTalisman->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pTalisman->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pTalisman->ustLevel = iValue;

        pTalisman->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pTalisman->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pTalisman->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pTalisman->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pTalisman->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pTalisman->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pTalisman->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pTalisman->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pTalisman->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pTalisman->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pTalisman->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pTalisman->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pTalisman->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pTalisman->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pTalisman->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pTalisman->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pTalisman->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pTalisman->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pTalisman->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pTalisman->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pTalisman->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pTalisman->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pTalisman->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pTalisman->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pTalisman->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pTalisman->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pTalisman->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pTalisman->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pTalisman->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pTalisman->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pTalisman->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pTalisman->nDropMaxCount = iValue;

        //法宝属性
        MeXmlElement *pTalismanAttr = pItemElement->FirstChildElement("Talisman");

        pTalismanAttr->Attribute("ModelID", &iValue);
        pTalisman->iModelID = iValue;

        pTalismanAttr->Attribute("NeedSex", &iValue);
        pTalisman->iSexReq = iValue;

        pTalismanAttr->Attribute("NeedLevel", &iValue);
        pTalisman->iEquipLevelReq = iValue;

        // 兵种需求
        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        { pTalisman->arrayEquipArmsReq[ iLoop ] = false; }

        strValue.fromUTF8( pEffectAttr->Attribute("NeedArms") );
        if ( strValue.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pTalisman->arrayEquipArmsReq[ iLoop ] = true;
            }
        }
        else
        {  
            //适用多个职业
            char *szSpn = ",";
            char *szStr;
            int iEquip;
            szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
            while( szStr )
            {

                iEquip = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iEquip >= 0 && iEquip < EArmType_MaxSize )
                {
                    pTalisman->arrayEquipArmsReq[ iEquip ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        pTalismanAttr->Attribute("SkillID", &iValue);
        pTalisman->skillId = iValue;

        pTalismanAttr->Attribute("SkillLevel", &iValue);
        pTalisman->skillLevel = iValue;

        pTalismanAttr->Attribute("Daoxing", &iValue);
        pTalisman->daoxing = iValue;

        pTalismanAttr->Attribute("PoolID", &iValue);
        pTalisman->poolId = iValue;

        pTalismanAttr->Attribute("NimbusMax", &iValue);
        pTalisman->nimbusMax = iValue;

        pTalismanAttr->Attribute("NimbusRestore", &iValue);
        pTalisman->nimbusRestore = iValue;

        m_vecSpecialItem.push_back(pTalisman);

        AddItemToContainer(pTalisman);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveTalismanItem     ( const char *szFileName ) 
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

    MeXmlElement *pTalismanType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pTalismanType == NULL)
    { return false; }

    pTalismanType->SetAttribute("Id",ItemDefine::ITEMTYPE_TALISMAN);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType !=ItemDefine::ITEMTYPE_TALISMAN  )
        { continue; }

        ItemDefine::SItemTalisman *pTalismanIter = (ItemDefine::SItemTalisman *)*iterBegin;

        MeXmlElement *pItem = pTalismanType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pTalismanIter->ustItemID);
        Common::_tstring strName = pTalismanIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pTalismanIter->ucItemType]);
        Common::_tstring strDescription = pTalismanIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pTalismanIter->nUseTime);
        pItem->SetAttribute("UserTarget", pTalismanIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pTalismanIter->ustLevel);
        pAppearance->SetAttribute("Rare", pTalismanIter->cItemClass);
        pAppearance->SetAttribute("Weight", pTalismanIter->fWeight);
        pAppearance->SetAttribute("IconID", pTalismanIter->ustIconId);
        Common::_tstring strIconFile = pTalismanIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pTalismanIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pTalismanIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pTalismanIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pTalismanIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pTalismanIter->nBill);
        pPrice->SetAttribute("CostType", pTalismanIter->costType);
        pPrice->SetAttribute("Cost", pTalismanIter->dwCost);
        pPrice->SetAttribute("CostItemID", pTalismanIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pTalismanIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pTalismanIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pTalismanIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pTalismanIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pTalismanIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pTalismanIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pTalismanIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pTalismanIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pTalismanIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pTalismanIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pTalismanIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pTalismanIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pTalismanIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pTalismanIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pTalismanIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pTalismanIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pTalismanIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pTalismanIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pTalismanIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pTalismanIter->nDropMaxCount);

        //法宝属性
        MeXmlElement *pTalisman = pItem->InsertEndChild(("Talisman"))->ToElement();
        if (pTalisman == NULL)
        { continue; }

        pTalisman->SetAttribute("SkillID", pTalismanIter->skillId);
        pTalisman->SetAttribute("SkillLevel", pTalismanIter->skillLevel);
        pTalisman->SetAttribute("Daoxing", pTalismanIter->daoxing);
        pTalisman->SetAttribute("PoolID", pTalismanIter->poolId);
        pTalisman->SetAttribute("NimbusMax", pTalismanIter->nimbusMax);
        pTalisman->SetAttribute("NimbusRestore ", pTalismanIter->nimbusRestore );
        pTalisman->SetAttribute("ModelID", pTalismanIter->iModelID );
        pTalisman->SetAttribute("NeedSex", pTalismanIter->iSexReq  );
        pTalisman->SetAttribute("NeedLevel", pTalismanIter->iEquipLevelReq  );


        // 兵种需求
        Common::_tstring strArmsNeed;
        Common::_tstring strSpn = ",";
        for (int i=0; i<EArmType_MaxSize; ++i)
        {
            if (pTalismanIter->arrayEquipArmsReq[i] == true)
            {
                strArmsNeed = strArmsNeed + string(ItemDefine::g_szProfessionType[i]);
                strArmsNeed = strArmsNeed + strSpn ;
            }
        } 
        pTalisman->SetAttribute("NeedArms" , strArmsNeed.substr(0,strArmsNeed.length() - 1).c_str());
    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )