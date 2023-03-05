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
//#include "MonsterConfigXML.h"

#pragma warning( push, 0 )

bool CItemDetail::AddRestoreItem( const char *szFileName )
{
    //const char* szFileName = "Restore.slk";


    CSlkReader pReader;
    OutputSlkLoadingMessage( "���ڷ���%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "�Ҳ���%s�ļ�\r\n",szFileName);
        return false;
    }

    int offset = 3;
    int iRet;

    int iValue = 0;
    float fValue = 0.0f;
    char* pszItemType = 0;
    std::string strTemp;
    std::string strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"RestoreID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  ����:��ȡ RestoreID �����к� %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon ==NULL || pCommon->ucItemType !=ItemDefine::ITEMTYPE_RESTORE)
        {
            OutputSlkLoadingMessage( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s ����:ItemID: %d �� Item.slk ���޼�¼  \r\n",szFileName,nItemID);
            continue;
            //return false;   
        }

        ItemDefine::SItemRestore *pItemRestore = (ItemDefine::SItemRestore *)pCommon;

        //����Ʒ����
        if( !GetIntField( &pReader,"RestoreType",iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ��RestoreType���ݴ�!\r\n" );
            GetErrorLog()->logString( "restore.slk��RestoreType���ݴ�" );
            continue;
        }
        pItemRestore->nRestoreType = iValue;

        //����HP
        if( !GetIntField( &pReader,"RestoreHP",iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ��addHP���ݴ�!\r\n" );
            GetErrorLog()->logString( "restore.slk��addHP���ݴ�" );
            continue;
        }
        pItemRestore->dwAddHP = iValue;

        //����MP
        if( !GetIntField( &pReader,"RestoreMP",iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ��addMP���ݴ�!\r\n" );
            GetErrorLog()->logString( "restore.slk��addMP���ݴ�" );
            continue;
        }
        pItemRestore->dwAddMP = iValue;


        //����Exp
        if( !GetIntField( &pReader,"ExtraExp",iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ��addExp���ݴ�!\r\n" );
            continue;
        }
        pItemRestore->dwAddExp = iValue;


        // ����hunger
        if( !GetIntField( &pReader,"ReleaseHunger",iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:ҩƷ������hunger���ݴ�!\r\n" );
            continue;
        }
        pItemRestore->stSubHunger = iValue;


        //���״̬    
        if( !GetIntField( &pReader, "ReleaseStatus", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ�Ľ��״̬û��!\r\n" );
            pItemRestore->ustSubStatusID = InvalidLogicNumber;
        }
        else
        {
            iValue = (iValue == -1) ? InvalidLogicNumber : iValue;
            pItemRestore->ustSubStatusID = iValue;
        }


        //����״̬    
        if( !GetIntField( &pReader, "CauseStatus", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ�ĵ���״̬û��!\r\n" );
            pItemRestore->ustAddStatusID = InvalidLogicNumber;
        }
        else
        {
            iValue = (iValue == -1) ? InvalidLogicNumber : iValue;
            pItemRestore->ustAddStatusID = iValue;
        }


        //����״̬�ȼ�
        if( !GetIntField( &pReader, "CauseStatusLv", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ҩƷ�ĵ���״̬�ȼ�Ĭ��1!\r\n" );
            pItemRestore->ustAddStatusLevel = 1;
        }
        else
        {
            pItemRestore->ustAddStatusLevel = iValue;
        }


        // CoolDown
        if( !GetIntField( &pReader, "ColdDown", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��CoolDownĬ��0!\r\n" );
            pItemRestore->dwCoolDown = 0;
        }
        else
        {
            pItemRestore->dwCoolDown = iValue;
        }


        // type
        if( !GetIntField( &pReader, "ColdDownType", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��typeĬ��0!\r\n" );
            pItemRestore->stCoolDownType = -1;
        }
        else
        {
            pItemRestore->stCoolDownType = iValue;
        }


        // �Ƿ������
        if( !GetIntField( &pReader, "Expendable", iValue ) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��ExpendableĬ��true!\r\n" );
            pItemRestore->bExpendable = true;
        }
        else
        {
            pItemRestore->bExpendable = (iValue>0);
        }


        // �Ƿ񸴻���Ʒ
        if( !pReader.GetIntFieldByName("IsRelive",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��IsRelive��ƷĬ��true!\r\n" );
            pItemRestore->bIsReliveItem  = false;
        }
        else
        {
            if (iValue > 0)
            {
                pItemRestore->bIsReliveItem = true;
            }
            else
                pItemRestore->bIsReliveItem = false;            
        }
        
        // 
        if( !pReader.GetIntFieldByName("UseFightStatus",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk����ƷUseFightStatusĬ��0\r\n" );
            pItemRestore->nUseFightStatus = 0;
        }
        else
        {
            pItemRestore->nUseFightStatus = iValue;        
        }

        // ʹ�õȼ�
        if( !pReader.GetIntFieldByName("UseLevel",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk����ƷUseLevelĬ��0\r\n" );
            pItemRestore->stUseLevel = 0;
        }
        else
        {
            pItemRestore->stUseLevel = iValue;        
        }

        // ����ʹ�õȼ�
        if( !pReader.GetIntFieldByName("MountUseLevel",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk����ƷnMountLevelĬ��0\r\n" );
            pItemRestore->nMountUseLevel = 0;
        }
        else
        {
            pItemRestore->nMountUseLevel = iValue;        
        }

        // �Զ��ظ�HP
        if( !pReader.GetIntFieldByName("IsHPAuto",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��IsHPAuto��Ĭ��0\r\n" );
            pItemRestore->bHPAuto = 0;
        }
        else
        {
            pItemRestore->bHPAuto = iValue;
        }

        // �Զ��ظ�MP
        if( !pReader.GetIntFieldByName("IsMPAuto",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��IsMPAuto��Ĭ��0\r\n" );
            pItemRestore->bMPAuto = 0;
        }
        else
        {
            pItemRestore->bMPAuto = iValue;        
        }

        // �Ƿ���Ը���
        if( !pReader.GetIntFieldByName("IsAutoRelive",iValue) )
        {
            OutputSlkLoadingMessage( "\tError:restore.slk��IsAutoRelive��Ĭ��0\r\n" );
            pItemRestore->bAutoRelive = 0;
        }
        else
        {
            pItemRestore->bAutoRelive = iValue;        
        }

        //// �Ƿ��ռ
        //if( !pReader.GetIntFieldByName("IsExclusive",iValue) )
        //{
        //    OutputSlkLoadingMessage( "\tError:restore.slk��IsExclusive��Ĭ��0\r\n" );
        //    pItemRestore->bExclusive = 0;
        //}
        //else
        //{
        //    pItemRestore->bExclusive = iValue;        
        //}

        SLK_GET_INT( iValue, "SpecialFunction" );
        pItemRestore->specialFunction = iValue;

        SLK_GET_INT( iValue, "AddHPOnce" );
        pItemRestore->dwAddHPOnce = iValue;

        SLK_GET_INT( iValue, "AddMPOnce" );
        pItemRestore->dwAddMPOnce = iValue;

        SLK_GET_INT( iValue, "OpenSkillNum" );
        pItemRestore->openSkillNum = iValue;

        SLK_GET_INT( iValue, "ForgetSkillIndex" );
        pItemRestore->forgetSkillIndex = iValue;

        SLK_GET_INT( iValue, "PetSavvy" );
        pItemRestore->petSavvy = iValue;

        // ְҵ����
        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        {
            pItemRestore->arrayProfessionReq[ iLoop ] = false;
        }

        SLK_GET_STRING( strValue, "UseProfession");
        if ( strValue.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pItemRestore->arrayProfessionReq[ iLoop ] = true;
            }
        }
        else
        {  
            //���ö��ְҵ
            char *szSpn = ",";
            char *szStr;
            int iEquip;
            szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
            while( szStr )
            {

                iEquip = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iEquip >= 0 && iEquip < EArmType_MaxSize )
                {
                    pItemRestore->arrayProfessionReq[ iEquip ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        m_vecRestoreItem.push_back(pItemRestore);
    }

    return true;
}


bool CItemDetailConfig::LoadRestoreItem    ( MeXmlDocument *pXmlDoc, int mode )//�ָ���Ʒ
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

        ItemDefine::SItemRestore *pRestore = NULL;

        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }

            pRestore = (ItemDefine::SItemRestore*)GetItemByID(itemId);
        }

        if ( NULL == pRestore )
        { pRestore = (ItemDefine::SItemRestore*)AllocItem( 0, sizeof( ItemDefine::SItemRestore ) ); }

        if( !pRestore )
        {
            OutputSlkLoadingMessage( "\tError:�ڴ�������!\r\n" );
            GetErrorLog()->logString( "Error:�ڴ�������!" );
            return false;    
        }

        pRestore->ustItemID = itemId;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        pRestore->dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "���ݴ� ItemType��"  );
            return false;
        }

        pRestore->ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        pRestore->dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        pRestore->nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        pRestore->byUserTarget = iValue;

        //�����������
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        pAppearanceAttr->Attribute("Quality", &iValue);
        pRestore->ustLevel = iValue;

        pRestore->cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        pRestore->fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        pRestore->ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        pRestore->dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        pRestore->ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        pRestore->ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        pRestore->ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        if (iValue <= 0)    // ����ѵ����� <= 0 ��Ϊ�������� �����Ϊ1
        { iValue = 1;}
        pRestore->nStackNum = iValue;

        //���ؼ۸�����
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        pRestore->nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        pRestore->costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        pRestore->dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        pRestore->costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        pRestore->dwSpecialCost = iValue;

        //���ز�������
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        pRestore->bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        pRestore->bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        pRestore->bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        pRestore->bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        pRestore->bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        pRestore->bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        pRestore->bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        pRestore->bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        pRestore->bIsCanSplit = iValue;

        //������Ч����
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        pRestore->bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        pRestore->dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        pRestore->dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        pRestore->dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        pRestore->dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        pRestore->dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        pRestore->bCanSingingInterrupt = iValue;

        //������ֵ����
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        pRestore->nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        pRestore->bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        pRestore->nDropMaxCount = iValue;

        //////////////////////////////////////////////////////////////////////////
        //                      �ָ�������ֶ�˵��
        //  RestoreHP:����HP 
        //  RestoreMP:����MP 
        //  ExtraExp:����Exp 
        //  AddHPOnce:һ�λ�Ѫ 
        //  AddMPOnce:һ�λ�ħ
        //  ReleaseHunger:�������� 
        //  ReleaseStatus:���״̬ 
        //  CauseStatus:����״̬ 
        //  CauseStatusLv:����״̬�ȼ� 
        //  ColdDown:��ȴʱ�� 
        //  ColdDownType:��ȴʱ������ 
        //  Expendable:�Ƿ������ 
        //  IsRelive:�Ƿ񸴻���Ʒ 
        //  UseLevel:ʹ�õȼ� 
        //  IsHPAuto:�Զ��ָ�HP 
        //  IsMPAuto:�Զ��ָ�MP 
        //  IsAutoRelive:�Ƿ��Զ����� 
        //  IsExclusive:�Ƿ��ռ 
        //  SpecialFunction:���⹦�� 
        //////////////////////////////////////////////////////////////////////////


        //���ػָ�����
        MeXmlElement *pRestoreAttr = pItemElement->FirstChildElement("Restore");

        pRestoreAttr->Attribute("RestoreType", &iValue);
        pRestore->nRestoreType = iValue;

        pRestoreAttr->Attribute("RestoreHP", &iValue);
        pRestore->dwAddHP = iValue;

        pRestoreAttr->Attribute("RestoreMP", &iValue);
        pRestore->dwAddMP = iValue;

        pRestoreAttr->Attribute("ExtraExp", &iValue);
        pRestore->dwAddExp = iValue;

        pRestoreAttr->Attribute("AddHPOnce", &iValue);
        pRestore->dwAddHPOnce = iValue; 

        pRestoreAttr->Attribute("AddMPOnce", &iValue);
        pRestore->dwAddMPOnce = iValue;

        //����״̬�������
        MeXmlElement *pStatusAttr = pItemElement->FirstChildElement("Status");

        pStatusAttr->Attribute("ReleaseHunger", &iValue);
        pRestore->stSubHunger = iValue;

        pStatusAttr->Attribute("ReleaseStatus", &iValue);
        pRestore->ustSubStatusID = iValue;

        pStatusAttr->Attribute("CauseStatus", &iValue);
        iValue = (iValue == -1) ? InvalidLogicNumber : iValue;
        pRestore->ustAddStatusID = iValue;

        pStatusAttr->Attribute("CauseStatusLv", &iValue);
        iValue = (iValue == -1) ? InvalidLogicNumber : iValue;
        pRestore->ustAddStatusLevel = iValue;

        pStatusAttr->Attribute("ColdDown", &iValue);
        pRestore->dwCoolDown = iValue; 

        pStatusAttr->Attribute("ColdDownType", &iValue);
        pRestore->stCoolDownType = iValue; 

        //������������
        MeXmlElement *pOtherAttr = pItemElement->FirstChildElement("Other");

        pOtherAttr->Attribute("Expendable", &iValue);
        pRestore->bExpendable = iValue;

        pOtherAttr->Attribute("IsRelive", &iValue);
        pRestore->bIsReliveItem = iValue;

        pOtherAttr->Attribute("UseFightStatus", &iValue);
        pRestore->nUseFightStatus = iValue;

        pOtherAttr->Attribute("UseLevel", &iValue);
        pRestore->stUseLevel = iValue;

        pOtherAttr->Attribute("MountUseLevel", &iValue);
        pRestore->nMountUseLevel = iValue;

        pOtherAttr->Attribute("IsHPAuto", &iValue);
        pRestore->bHPAuto = iValue;

        pOtherAttr->Attribute("IsMPAuto", &iValue);
        pRestore->bMPAuto = iValue;

        pOtherAttr->Attribute("IsAutoRelive", &iValue);
        pRestore->bAutoRelive = iValue;

        //pOtherAttr->Attribute("IsExclusive", &iValue);
        //pRestore->bExclusive = iValue;

        pOtherAttr->Attribute("SpecialFunction", &iValue);
        pRestore->specialFunction = iValue;

        pOtherAttr->Attribute("OpenSkillNum", &iValue);
        pRestore->openSkillNum = iValue;

        pOtherAttr->Attribute("ForgetSkillIndex", &iValue);
        pRestore->forgetSkillIndex = iValue;

        pOtherAttr->Attribute("PetSavvy", &iValue);
        pRestore->petSavvy = iValue;

        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        {
            pRestore->arrayProfessionReq[ iLoop ] = false;
        }

        Common::_tstring strProfessionReq;
        strProfessionReq.fromUTF8( pOtherAttr->Attribute("UseProfession") );
        if ( strProfessionReq.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pRestore->arrayProfessionReq[ iLoop ] = true;
            }
        }
        else
        {  
            //���ö��ְҵ
            char *szSpn = ",";
            char *szStr;
            int iEquip;
            szStr = strtok( const_cast<char*>(strProfessionReq.c_str()),szSpn );
            while( szStr )
            {

                iEquip = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iEquip >= 0 && iEquip < EArmType_MaxSize )
                {
                    pRestore->arrayProfessionReq[ iEquip ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        AddItemToContainer(pRestore);
        m_vecRestoreItem.push_back(pRestore);

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}

bool CItemDetailConfig::SaveRestoreItem     ( const char *szFileName )//+���� �ָ���Ʒ
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

    MeXmlElement *pRestoreType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pRestoreType == NULL)
    { return false; }

    pRestoreType->SetAttribute("Id",ItemDefine::ITEMTYPE_RESTORE);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType !=ItemDefine::ITEMTYPE_RESTORE )
        { continue; }

        ItemDefine::SItemRestore *pRestoreIter = (ItemDefine::SItemRestore *)*iterBegin;

        MeXmlElement *pItem = pRestoreType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pRestoreIter->ustItemID);
        Common::_tstring strName = pRestoreIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pRestoreIter->ucItemType]);
        Common::_tstring strDescription = pRestoreIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pRestoreIter->nUseTime);
        pItem->SetAttribute("UserTarget", pRestoreIter->byUserTarget);

        //�������
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Quality", pRestoreIter->ustLevel);
        pAppearance->SetAttribute("Rare", pRestoreIter->cItemClass);
        pAppearance->SetAttribute("Weight", pRestoreIter->fWeight);
        pAppearance->SetAttribute("IconID", pRestoreIter->ustIconId);
        Common::_tstring strIconFile = pRestoreIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pRestoreIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pRestoreIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pRestoreIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pRestoreIter->nStackNum);

        //�۸�����
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pRestoreIter->nBill);
        pPrice->SetAttribute("CostType", pRestoreIter->costType);
        pPrice->SetAttribute("Cost", pRestoreIter->dwCost);
        pPrice->SetAttribute("CostItemID", pRestoreIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pRestoreIter->dwSpecialCost);

        //��������
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pRestoreIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pRestoreIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pRestoreIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pRestoreIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pRestoreIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pRestoreIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pRestoreIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pRestoreIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pRestoreIter->bIsCanSplit);

        //��Ч����
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pRestoreIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pRestoreIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pRestoreIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pRestoreIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pRestoreIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pRestoreIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pRestoreIter->bCanSingingInterrupt);

        //��ֵ����
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pRestoreIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pRestoreIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pRestoreIter->nDropMaxCount);

        //�ָ�����
        MeXmlElement *pRestore = pItem->InsertEndChild(("Restore"))->ToElement();
        if (pRestore == NULL)
        { continue; }

        pRestore->SetAttribute("RestoreType", pRestoreIter->nRestoreType);
        pRestore->SetAttribute("RestoreHP", pRestoreIter->dwAddHP);
        pRestore->SetAttribute("RestoreMP", pRestoreIter->dwAddMP);
        pRestore->SetAttribute("ExtraExp", pRestoreIter->dwAddExp);
        pRestore->SetAttribute("AddHPOnce", pRestoreIter->dwAddHPOnce);
        pRestore->SetAttribute("AddMPOnce", pRestoreIter->dwAddMPOnce);

        //״̬���
        MeXmlElement *pStatus = pItem->InsertEndChild(("Status"))->ToElement();
        if (pStatus == NULL)
        { continue; }

        pStatus->SetAttribute("ReleaseHunger", pRestoreIter->stSubHunger);
        pStatus->SetAttribute("ReleaseStatus", pRestoreIter->ustSubStatusID);
        pStatus->SetAttribute("CauseStatus", pRestoreIter->ustAddStatusID);
        pStatus->SetAttribute("CauseStatusLv", pRestoreIter->ustAddStatusLevel);
        pStatus->SetAttribute("ColdDown", pRestoreIter->dwCoolDown);
        pStatus->SetAttribute("ColdDownType", pRestoreIter->stCoolDownType);

        //��������
        MeXmlElement *pOther = pItem->InsertEndChild(("Other"))->ToElement();
        if (pOther == NULL)
        { continue; }

        pOther->SetAttribute("Expendable", pRestoreIter->bExpendable);
        pOther->SetAttribute("IsRelive", pRestoreIter->bIsReliveItem);
        pOther->SetAttribute("UseLevel", pRestoreIter->stUseLevel);
        pOther->SetAttribute("UseFightStatus", pRestoreIter->nUseFightStatus);
        pOther->SetAttribute("MountUseLevel", pRestoreIter->nMountUseLevel);
        pOther->SetAttribute("IsHPAuto", pRestoreIter->bHPAuto);
        pOther->SetAttribute("IsMPAuto", pRestoreIter->bMPAuto);
        pOther->SetAttribute("IsAutoRelive", pRestoreIter->bAutoRelive);
        //pOther->SetAttribute("IsExclusive", pRestoreIter->bExclusive);
        pOther->SetAttribute("SpecialFunction", pRestoreIter->specialFunction);
        pOther->SetAttribute("OpenSkillNum", pRestoreIter->openSkillNum);
        pOther->SetAttribute("ForgetSkillIndex", pRestoreIter->forgetSkillIndex);
        pOther->SetAttribute("PetSavvy", pRestoreIter->petSavvy);

        Common::_tstring strProfessionReq;
        Common::_tstring strSpn = ",";
        for (int i=0; i<EArmType_MaxSize; ++i)
        {
            if (pRestoreIter->arrayProfessionReq[i] == true)
            {
                strProfessionReq = strProfessionReq + string(ItemDefine::g_szProfessionType[i]);
                strProfessionReq = strProfessionReq + strSpn ;
            }
        } 
        pOther->SetAttribute("UseProfession" , strProfessionReq.substr(0,strProfessionReq.length() - 1).c_str());

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )