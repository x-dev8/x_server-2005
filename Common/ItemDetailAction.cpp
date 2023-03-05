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

//装载动作数据
bool CItemDetail::AddActionItem( const char *szFileName )
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
    int iValue;
    std::string strTemp;
    int line = 0;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;
        iCol = 3;

        int nItemID = -1;
        if( !GetIntField( &pReader,"IconID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 IconID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_ACTION)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;  
        }

        ItemDefine::SItemAction *pItemAction = (ItemDefine::SItemAction *)pCommon;

        //动作ID
        if(!pReader.GetStringField(iCol, strTemp ))
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取动作名称出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取动作名称出错!" );
            continue;
        }
        pItemAction->ustActionID = FindActionIdByName( strTemp.c_str() );

        iCol++;

        //动作类型（0，基本动作 1，社群动作 2，社交动作）
        if(!pReader.GetStringField(iCol,strTemp))
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取动作类型出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取动作类型出错!" );
            continue;
        }
        pItemAction->stType = HelperFunc::GetIDByConstString((char*)strTemp.c_str(),
            ItemDefine::g_szActionType, sizeof(ItemDefine::g_szActionType)/sizeof(char *) );

        if( -1 == pItemAction->stType )
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取动作类型出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取动作类型出错!" );
            continue;
        }
        iCol ++;

        //单次播放时间
        if(!pReader.GetIntField(iCol,iValue))
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取单次播放时间出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取单次播放时间出错!" );
            continue;
        }
        pItemAction->stSinglePlayTime = iValue;
        iCol++;

        //持续播放时间
        if(!pReader.GetIntField(iCol,iValue))
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取持续播放时间出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取持续播放时间出错!" );
            continue;
        }
        pItemAction->stLastingPlayTime = iValue;
        iCol++;

        //保留最后一帧
        if(!pReader.GetIntField(iCol,iValue))
        {
            OutputSlkLoadingMessage( "Error:gameaction.slk读取保留最后一帧出错!\r\n" );
            GetErrorLog()->logString( "gameaction.slk中读取保留最后一帧出错!" );
            continue;
        }

        if(0 == iValue)
            pItemAction->bLastFrameRemain = false;
        else 
            pItemAction->bLastFrameRemain = true;
        iCol++;

        m_vecGameActionItem.push_back(pItemAction);
    }

    return true;
    
}


bool CItemDetailConfig::LoadActionItem     ( MeXmlDocument *pXmlDoc, int mode )//基本动作
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

        ItemDefine::SItemAction *pAction = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pAction = (ItemDefine::SItemAction*)GetItemByID(itemId);
        }
        
        if ( NULL == pAction )
        { pAction = (ItemDefine::SItemAction*)AllocItem( 0, sizeof( ItemDefine::SItemAction ) ); }
        
        if( !pAction )
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            GetErrorLog()->logString( "Error:内存分配出错!" );
            return false;    
        }

        pAction->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pAction->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        pAction->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pAction->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pAction->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pAction->byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pAction->ustLevel = iValue;

        pAction->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pAction->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pAction->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pAction->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pAction->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pAction->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pAction->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        pAction->nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pAction->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pAction->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pAction->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pAction->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pAction->dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pAction->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pAction->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pAction->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pAction->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pAction->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pAction->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pAction->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pAction->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pAction->bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pAction->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pAction->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pAction->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pAction->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pAction->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pAction->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pAction->bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pAction->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pAction->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pAction->nDropMaxCount = iValue;

        //加载动作属性
        MeXmlElement *pActionAttr = pItemElement->FirstChildElement("Action");
        Common::_tstring strActionID;
        strActionID.fromUTF8( pActionAttr->Attribute("ActionID"));
        pAction->ustActionID = FindActionIdByName( strActionID.c_str() );

        Common::_tstring strActionType;
        strActionType.fromUTF8( pActionAttr->Attribute("ActionType") );
        pAction->stType = HelperFunc::GetIDByConstString((char*)strActionType.c_str(),
            ItemDefine::g_szActionType, sizeof(ItemDefine::g_szActionType)/sizeof(char *) );

        if ( -1 == pAction->stType )
        {
            printf("动作类型读取出错！");
            return false;
        }

        pActionAttr->Attribute("SinglePlayTime", &iValue);
        pAction->stSinglePlayTime = iValue;

        pActionAttr->Attribute("CyclePlayTime", &iValue);
        pAction->stLastingPlayTime = iValue;

        pActionAttr->Attribute("IfLastFrame" ,&iValue);
        if(0 == iValue)
            pAction->bLastFrameRemain = false;
        else 
            pAction->bLastFrameRemain = true;

        AddItemToContainer(pAction);

        m_vecGameActionItem.push_back(pAction);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveActionItem      ( const char *szFileName )//+保存基本动作
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

    MeXmlElement *pActionType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pActionType == NULL)
    { return false; }

    pActionType->SetAttribute("Id", ItemDefine::ITEMTYPE_ACTION);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_ACTION  )
        { continue; }

        ItemDefine::SItemAction *pActionIter = (ItemDefine::SItemAction *)*iterBegin;

        MeXmlElement *pItem = pActionType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pActionIter->ustItemID);
        Common::_tstring strName = pActionIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pActionIter->ucItemType]);
        Common::_tstring strDescription = pActionIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pActionIter->nUseTime);
        pItem->SetAttribute("UserTarget", pActionIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pActionIter->ustLevel);
        pAppearance->SetAttribute("Rare", pActionIter->cItemClass);
        pAppearance->SetAttribute("Weight", pActionIter->fWeight);
        pAppearance->SetAttribute("IconID", pActionIter->ustIconId);
        Common::_tstring strIconFile = pActionIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pActionIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pActionIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pActionIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pActionIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pActionIter->nBill);
        pPrice->SetAttribute("CostType", pActionIter->costType);
        pPrice->SetAttribute("Cost", pActionIter->dwCost);
        pPrice->SetAttribute("CostItemID", pActionIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pActionIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pActionIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pActionIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pActionIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pActionIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pActionIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pActionIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pActionIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pActionIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pActionIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pActionIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pActionIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pActionIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pActionIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pActionIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pActionIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pActionIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pActionIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pActionIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pActionIter->nDropMaxCount);

        //动作属性
        MeXmlElement *pAction = pItem->InsertEndChild(("Action"))->ToElement();
        if (pAction == NULL)
        { continue; }


        if ( pActionIter->ustActionID >= 0 && pActionIter->ustActionID<65535 )
            pAction->SetAttribute("ActionID", FindActionStringByID(pActionIter->ustActionID));
        else
            pAction->SetAttribute("ActionID", "");

        pAction->SetAttribute("ActionType", ItemDefine::g_szActionType[pActionIter->stType]);
        pAction->SetAttribute("SinglePlayTime", pActionIter->stSinglePlayTime);
        pAction->SetAttribute("CyclePlayTime", pActionIter->stLastingPlayTime);
        pAction->SetAttribute("IfLastFrame", pActionIter->bLastFrameRemain);

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )