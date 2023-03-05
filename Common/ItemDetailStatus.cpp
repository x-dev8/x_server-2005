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

ItemDefine::SItemStatus* CItemDetail::GetStatusBySkill( const ItemDefine::SItemSkill *pSkill )
{ //获取状态的相关函数
    if( pSkill )
    {
        if( pSkill->ustMeAddStatusID[0] != -1 )
            return GetStatus( pSkill->ustMeAddStatusID[0], pSkill->ustMeAddStatusLevel[0] );

        if( pSkill->ustDstAddStatusID[0] != -1 )
            return GetStatus( pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0] );
    }

    return NULL;
}

ItemDefine::SItemStatus* CItemDetail::GetMeStatusBySkill( const ItemDefine::SItemSkill *pSkill , uint8 index )
{
    if ( index > ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize )
    { return NULL; }

    if( pSkill )
    {
        if( pSkill->ustMeAddStatusID[index] != -1 )
        { return GetStatus( pSkill->ustMeAddStatusID[index], pSkill->ustMeAddStatusLevel[index] ); }
    }

    return NULL;
}

ItemDefine::SItemStatus* CItemDetail::GetDstStatusBySkill( const ItemDefine::SItemSkill *pSkill )
{
    if( pSkill )
    {
        if( pSkill->ustDstAddStatusID[0] != -1 )
        { return GetStatus( pSkill->ustDstAddStatusID[0], pSkill->ustDstAddStatusLevel[0] ); }
    }

    return NULL;
}

//获取状态的相关函数
ItemDefine::SItemStatus* CItemDetail::GetStatus( unsigned short ustStatusItemID, unsigned short ustStatusLevel )
{
    if( ustStatusItemID < ItemDefine::StartID_Status )
        return NULL;

    int index;
    index = ustStatusItemID - ItemDefine::StartID_Status;

    if( index < 0 || index >= ItemDefine::MaxNum_Status )
        return 0;

    if( ustStatusLevel < 0 || ustStatusLevel >= ItemDefine::MaxLevel_Status )
        return 0;

    return &(m_StatusArray[index][ustStatusLevel]);
}

bool CItemDetail::AddStatusItem( const char *szFileName )
{
    CSlkReader pReader;
    OutputSlkLoadingMessage( "正在分析%s\r\n",szFileName );
    if( !pReader.ReadFromFile( szFileName ) )
    {        
        OutputSlkLoadingMessage( "找不到%s文件\r\n",szFileName);
        return false;
    }

    int offset = 3;
    int line = 0;  
    int iRet;

    int   iValue;
    float fValue;

    std::string strTemp;
    std::string strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"StatusID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 StatusID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_STATUS)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemStatus *pItemStatus = (ItemDefine::SItemStatus *)pCommon;

        //状态等级
        if(!GetIntField( &pReader, "StatusLevel", iValue ))
        {
            OutputSlkLoadingMessage( "Warning:本状态缺省等级=1!\r\n" );    
            pItemStatus->ustLevel = 1;
        }
        else
        {
            pItemStatus->ustLevel = iValue;
        }


        if ( !pReader.GetStringFieldByName( "StatusEffect", strTemp ) )
        {
            OutputSlkLoadingMessage( "Error:读取status.slk字段[状态特效]出错\r\n" );
        }
        pItemStatus->dwStatusEffectAddr = AllocStringCopy( strTemp.c_str() );

        if ( !pReader.GetStringFieldByName( "StatusAction", strTemp ) )
        {
            OutputSlkLoadingMessage( "Error:读取status.slk字段[状态动作]出错\r\n" );
        }
        pItemStatus->dwStatusActionAddr = AllocStringCopy( strTemp.c_str() );


        SLK_GET_INT( pItemStatus->bAvail,           "IfStatusAdvantageous" );

        SLK_GET_INT( pItemStatus->iDurationTime,     "KeepTimeOfStatus(ms)" );
        SLK_GET_INT( pItemStatus->iBalanceDelayTime, "EffectIntervalTime" );
        SLK_GET_INT( pItemStatus->stType,            "StatusType" );
        SLK_GET_INT( pItemStatus->stPriority,        "PriorLevel" );
        SLK_GET_INT( pItemStatus->bIsCanCong,       "CanReplacable" );

        //使用结算公式
        if( !GetStringField( &pReader, "StatusFormula", strTemp ) )
        {
            OutputSlkLoadingMessage( "Error:读取使用结算公式出错!\r\n" );
            GetErrorLog()->logString( "status.slk中读取使用结算公式出错" );
            continue;
        }
        pItemStatus->stBalanceType = HelperFunc::GetIDByConstString( (char*)strTemp.c_str(),
            ItemDefine::g_szStatusBalanceType, sizeof(ItemDefine::g_szStatusBalanceType)/sizeof(char*) );


        SLK_GET_INT  ( pItemStatus->bAttckedNoStatus,    "IfDispelWhenGetAtk" );
        SLK_GET_INT  ( pItemStatus->bAttckNoStatus,      "IfDispelWhenAtk" );
        SLK_GET_INT  ( pItemStatus->changePhyAttackPer ,  "ChangePhyAttackPer"   );
        SLK_GET_FLOAT( pItemStatus->changePhyAttack    ,  "ChangePhyAttack"      );
        SLK_GET_INT  ( pItemStatus->changeMagAttackPer ,  "ChangeMagAttackPer"   );
        SLK_GET_FLOAT( pItemStatus->changeMagAttack    ,  "ChangeMagAttack"      );
        SLK_GET_INT  ( pItemStatus->changeDefendPer[EDefendType_Physical], "ChangeShortDefendPer" );
        //SLK_GET_INT  ( pItemStatus->changeDefendPer[EDefendType_Long] , "ChangeLongDefendPer"  );
        SLK_GET_INT  ( pItemStatus->changeDefendPer[EDefendType_Magic], "ChangeMagicDefendPer" );
        SLK_GET_INT  ( pItemStatus->changeDefend[EDefendType_Physical], "ChangeShortDefend" );
        //SLK_GET_INT  ( pItemStatus->changeDefend[EDefendType_Long] , "ChangeLongDefend"  );
        SLK_GET_INT  ( pItemStatus->changeDefend[EDefendType_Magic], "ChangeMagicDefend" );
        SLK_GET_INT  ( pItemStatus->changeHPMaxPer          , "MaxHpPer"      );
        SLK_GET_INT  ( pItemStatus->stChanged_HPMax         , "MaxHp"         );
        SLK_GET_INT  ( pItemStatus->changeMPMaxPer          , "MaxMpPer"      );
        SLK_GET_INT  ( pItemStatus->stChanged_MPMax         , "MaxMp"         );
        SLK_GET_INT  ( pItemStatus->resumeHPPer             , "RecoverHPPer"  );
        SLK_GET_INT  ( pItemStatus->resumeHP                , "RecoverHP"     );
        SLK_GET_INT  ( pItemStatus->resumeMPPer             , "RecoverMPPer"  ); 
        SLK_GET_INT  ( pItemStatus->resumeMP                , "RecoverMP"     ); 
        SLK_GET_INT  ( pItemStatus->stChanged_HP            , "ChangeHp"      );
        SLK_GET_INT  ( pItemStatus->recoverHPBasePer         , "ChangeHpPer"   );
        SLK_GET_INT  ( pItemStatus->recoverHPMaxPer         , "ChangeHpMaxPer"   );
        SLK_GET_INT  ( pItemStatus->stChanged_MP            , "ChangeMp"      );
        SLK_GET_INT  ( pItemStatus->recoverMPBasePer         , "ChangeMpPer"   );
        SLK_GET_INT  ( pItemStatus->recoverMPMaxPer         , "ChangeMpMaxPer"   );
        SLK_GET_INT  ( pItemStatus->changeActivityMax         , "ChangeActivityMax"   );
        SLK_GET_INT  ( pItemStatus->stChanged_Hit           , "AddtionalHit"  ); 
        SLK_GET_INT  ( pItemStatus->stChanged_Hedge         , "AddtionalFlee" );
        SLK_GET_INT  ( pItemStatus->changed_Critical        , "ChangeCritical"              ); 
        SLK_GET_INT  ( pItemStatus->changed_CriticalIntensity      , "ChangeCriticalIntensity"       );
        SLK_GET_FLOAT( pItemStatus->fChanged_ReboundVal     , "DamReflect%"            );
        SLK_GET_INT  ( pItemStatus->nDamageReflectProability, "DamageReflectProability");
        SLK_GET_INT  ( pItemStatus->stAbsorbExtraHPVal      , "AbsorbHp"         ); 
        SLK_GET_FLOAT( pItemStatus->fSuckHpRate,              "SuckHpRate"       );
        SLK_GET_INT  ( pItemStatus->nSuckHpProbability      , "SuckHpProbability");
        SLK_GET_FLOAT( pItemStatus->fMoveSpeedChanged       , "MoveSpeed"        );
        SLK_GET_INT  ( pItemStatus->nMoveSpeedPer           , "MoveSpeedPer"       );
        SLK_GET_FLOAT( pItemStatus->fAttSpeedPer            , "AtkSpeed%"        ); 
        SLK_GET_INT  ( pItemStatus->bIsMove                 , "CanMove"          ); 
        SLK_GET_INT  ( pItemStatus->bIsAtt                  , "CanPhyAtk"        ); 
        SLK_GET_INT  ( pItemStatus->bIsUsingMagic           , "CanSkillUse"      ); 
        SLK_GET_INT  ( pItemStatus->bIsBePhyAttack          , "CanBePhyAttack"   ); 
        SLK_GET_INT  ( pItemStatus->bIsBeMagAttack          , "CanBeMagAttack"   ); 
        SLK_GET_INT  ( pItemStatus->bIsUsingTools           , "CanItemUse"       ); 
        SLK_GET_INT  ( pItemStatus->stMagicShield           , "IfManaShield"     ); 
        SLK_GET_FLOAT( pItemStatus->fSuckDamagePer,     "AbsorbDam%"         );
        SLK_GET_INT  ( pItemStatus->stSuckDamageMax,    "MaxAbsorb"          );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttr[EBaseAttr_Strength],     "AdditionalStr" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttr[EBaseAttr_Agility],      "AdditionalAgi" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttr[EBaseAttr_Stamina], "AdditionalCon" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttr[EBaseAttr_Intelligence], "AdditionalInt" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttrPer[EBaseAttr_Strength],     "AdditionalStrPer" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttrPer[EBaseAttr_Agility],      "AdditionalAgiPer" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttrPer[EBaseAttr_Stamina], "AdditionalConPer" );
        SLK_GET_INT  ( pItemStatus->stAddBaseAttrPer[EBaseAttr_Intelligence], "AdditionalIntPer" );
        SLK_GET_FLOAT( pItemStatus->bUseStateColour   , "IfUseStatusColour"     );
        SLK_GET_FLOAT( pItemStatus->fStateColourR     , "StatusColour(Red)"     );
        SLK_GET_FLOAT( pItemStatus->fStateColourG     , "StatusColour(Green)"   );
        SLK_GET_FLOAT( pItemStatus->fStateColourB     , "StatusColour(Blue)"    );
        SLK_GET_FLOAT( pItemStatus->fChangActionTime  , "ChangeAnimationPlay"   );
        SLK_GET_INT  ( pItemStatus->bIsChangActionTime, "IfChangeAnimationPlay" );
        SLK_GET_INT  ( pItemStatus->bIsHide           , "IfHide"                );
        SLK_GET_INT  ( pItemStatus->bIsFlyAir         , "IsFlyAir"              );
        SLK_GET_INT  ( pItemStatus->bIsClearDamgeStatus, "IfClearStatus"        );
        SLK_GET_INT  ( pItemStatus->bIsReplaceOldStatus, "IsReplaceOldStatus"   );
        SLK_GET_INT  ( pItemStatus->nChangeMonsterID   , "monsterid"            );
        SLK_GET_INT  ( pItemStatus->bIsAddBufferBeCSed      , "IsBeCsedAddBuffer"   );
        SLK_GET_INT  ( pItemStatus->stBeCsedAddBufferMeId   , "BeCSedAddBufferID"   );
        SLK_GET_INT  ( pItemStatus->stBeCsedAddBufferMeLevel, "BeCSedAddBufferLevel");
        SLK_GET_INT  ( pItemStatus->bIsAddDeBufferToAttacker, "IsAddDeBufferForAttacker"   );
        SLK_GET_FLOAT( pItemStatus->fAddDeBufferByHpPer     , "AddDeBufferForAttackerByHp" );
        SLK_GET_INT  ( pItemStatus->stAddDeBufferID         , "AddDeBufferID"       );
        SLK_GET_INT  ( pItemStatus->stAddDeBufferLevel      , "AddDeBufferLevel"    );
        SLK_GET_INT  ( pItemStatus->nSuperpositionCount     , "AddStatusCount"      );
        SLK_GET_INT  ( pItemStatus->restoreType             , "RestoreType"         );
        SLK_GET_INT  ( pItemStatus->nStandingEnmity         , "StandingEnmity"      );
        SLK_GET_FLOAT( pItemStatus->fAddExpMul              , "AddExpMul"           );
        SLK_GET_FLOAT( pItemStatus->fAddSkillExpMul         , "AddSkillExpMul"      );
        SLK_GET_STRING( strValue, "StatusAnim" );
        pItemStatus->nStatusAnim = HelperFunc::GetIDByConstString( (char*)strValue.c_str(), ItemDefine::g_szStatusAnimType, sizeof(ItemDefine::g_szStatusAnimType)/sizeof( char* ) );
        SLK_GET_INT  ( pItemStatus->bIsClearByDead,        "ClearStatusByDead" );
        SLK_GET_INT  ( pItemStatus->stActualTime,           "ActualTime"       );
        SLK_GET_INT  ( pItemStatus->bIsRandRun,              "IsRandRun"         );
        SLK_GET_INT  ( pItemStatus->bBackAttckedDispel,              "IfDispelWhenBackAttack");
        SLK_GET_INT  ( pItemStatus->bMoveDispel,                     "IfDispelWhenMove"      );
        SLK_GET_INT  ( pItemStatus->stChangedFightPoint,             "ChangedFightPoint"         );

        for ( int i=0; i<ItemDefine::SItemStatus::ECD_TimeExpMulModulusCount; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "TimeExpMulModulus%d",i+1);
            SLK_GET_FLOAT( pItemStatus->timeExpModulus[i], szTmp );
        }

        SLK_GET_FLOAT ( pItemStatus->timeExpMul, "TimeExpMul"    );
        SLK_GET_STRING( strValue,                "AnimationName" );
        pItemStatus->dwAnimationAddr = AllocStringCopy( strValue.c_str() );

        SLK_GET_INT( pItemStatus->bInvincible,          "Invincible" );
        SLK_GET_INT( pItemStatus->negativeType,        "NegativeType" );
        SLK_GET_INT( pItemStatus->damagetohp,          "DamagetoHp"   );
        SLK_GET_INT( pItemStatus->bDisableCallGraphic,  "IfDisableCallGraphic");
        SLK_GET_INT( iValue,                            "ActionMapConfigId"   );
        if ( iValue <= 0)
        { pItemStatus->actionMapConfigId = InvalidLogicNumber; }
        else
        { pItemStatus->actionMapConfigId = iValue; }

        SLK_GET_INT( pItemStatus->canCancel, "CanCancel" );
        SLK_GET_INT( pItemStatus->hurtImmunity, "HurtImmunity" );

        SLK_GET_INT( pItemStatus->attackModulus, "AttackModulus" );
        SLK_GET_INT( pItemStatus->defendModulus, "DefendModulus" );
        SLK_GET_INT( pItemStatus->ifConsumeEnergy, "IfConsumeEnergy" );
        SLK_GET_INT( pItemStatus->ifStatusIntonate, "IfStatusIntonate" );

        SLK_GET_INT( pItemStatus->changeTenacity, "AddtionalTenacity" );

        for ( int i=0; i<ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize; ++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillId%d",i+1);
            SLK_GET_INT( pItemStatus->changeSkillIds[i], szTmp );

            sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillTimes%d",i+1);
            SLK_GET_INT( pItemStatus->changeSkillTimes[i], szTmp );
        }

        SLK_GET_FLOAT( pItemStatus->activityMul, "ActivityMul" );

        SLK_GET_INT( pItemStatus->reduceTax, "ReduceTax" );
        SLK_GET_INT( pItemStatus->deathDurabilityPer, "DeathDurabilityPer" );
        SLK_GET_INT( pItemStatus->deathMountHPDropPer, "DeathMountHPDropPer" );

        SLK_GET_INT( pItemStatus->addMoney,         "AddMoney"      );
        SLK_GET_INT( pItemStatus->addReputation,    "AddReputation" );
        SLK_GET_INT( pItemStatus->addExploit,       "AddExploit"    );
        SLK_GET_INT( pItemStatus->addHonour,        "AddHonour"     );
        SLK_GET_INT( pItemStatus->addMasterValue,   "AddMasterValue");
        SLK_GET_INT( pItemStatus->addBattleScore,   "AddBattleScore");

        SLK_GET_FLOAT ( pItemStatus->reputationMul, "ReputationMul" );
        SLK_GET_FLOAT ( pItemStatus->exploitMul,    "ExploitMul"    );
        SLK_GET_FLOAT ( pItemStatus->honourMul,     "HonourMul"     );
        SLK_GET_FLOAT ( pItemStatus->masterValueMul,"MasterValueMul");
        SLK_GET_FLOAT ( pItemStatus->battleScoreMul,"BattleScoreMul");

        SLK_GET_INT( pItemStatus->addHonourLimit,   "AddHonourLimit");

        SLK_GET_INT( pItemStatus->lapoverNum,       "LapoverNum"    );
        SLK_GET_INT( pItemStatus->lapoverValue,     "LapoverValue"  );
        SLK_GET_INT( pItemStatus->lapoverMod,       "LapoverMod"    );

        SLK_GET_INT( pItemStatus->breakStrike,       "BreakStrike"      );
        SLK_GET_INT( pItemStatus->stabStrike,        "StabStrike"       );
        SLK_GET_INT( pItemStatus->elementStrike,     "ElementStrike"    );
        SLK_GET_INT( pItemStatus->toxinStrike,       "ToxinStrike"      );
        SLK_GET_INT( pItemStatus->spiritStrike,      "SpiritStrike"     );

        SLK_GET_INT( pItemStatus->breakResist,       "BreakResist"      );
        SLK_GET_INT( pItemStatus->stabResist,        "StabResist"       );
        SLK_GET_INT( pItemStatus->elementResist,     "ElementResist"    );
        SLK_GET_INT( pItemStatus->toxinResist,       "ToxinResist"      );
        SLK_GET_INT( pItemStatus->spiritResist,      "SpiritResist"     );

        SLK_GET_INT( pItemStatus->addEquipAttrType,       "AddEquipAttrType"    );
        SLK_GET_INT( pItemStatus->addEquipAttrValuePer,   "AddEquipAttrValuePer"    );

        SLK_GET_INT( pItemStatus->addCatchPetRate,       "AddCatchRate"    );
		SLK_GET_INT( pItemStatus->canRide,				 "CanRide"    );
		SLK_GET_INT( pItemStatus->BeDamagePerHpMax,				 "BeDamagePerHpMax"    );

		SLK_GET_INT( pItemStatus->canGetHonour,				 "CanGetHonour"    );
		SLK_GET_INT( pItemStatus->canBeGetHonour,			 "CanBeGetHonour"    );

        // 建立一个状态数组
        if(pItemStatus->ustItemID>=ItemDefine::StartID_Status)
        {
            int index;
            index = pItemStatus->ustItemID-ItemDefine::StartID_Status;
            m_StatusArray[index][pItemStatus->ustLevel] = *pItemStatus;

            if(pItemStatus->ustLevel==1)
            {
                m_StatusArray[index][ 0 ] = *pItemStatus;
            }
        }

        m_vecStatusItem.push_back(pItemStatus);

    }

    return true;
}


bool CItemDetailConfig::LoadStatusItem     ( MeXmlDocument *pXmlDoc, int mode )//状态
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
        if ( mode != ConfigLoadMode_Normal)
        {
            int updateSignal = 0;
            pItemElement->Attribute(ITEM_UPDATE_SIGNAL, &updateSignal);
            if (updateSignal != 1)
            {
                pItemElement = pItemElement->NextSiblingElement();
                continue; 
            }
        }

      ItemDefine::SItemCommon itemCommon;

        pItemElement->Attribute("Id", &iValue);
        itemCommon.ustItemID = iValue;        

        Common::_tstring itemName;
        itemName.fromUTF8( pItemElement->Attribute("ItemName") );
        itemCommon.dwItemNameAddr = AllocStringCopy(itemName.c_str());

        int nItemType = -1;
        Common::_tstring strTemp = "";
        strTemp.fromUTF8( pItemElement->Attribute("ItemType") );

        nItemType = GetItemTypeByString( strTemp.c_str());
        if( nItemType < 0 || nItemType >=ItemDefine::ITEMTYPE_MAX )
        {
            OutputSlkLoadingMessage( "数据错 ItemType列"  );
            return false;
        }

        itemCommon.ucItemType = nItemType;

        Common::_tstring itemDescription;
        itemDescription.fromUTF8( pItemElement->Attribute("Description") );
        itemCommon.dwItemDescAddr = AllocStringCopy(itemDescription.c_str());

        pItemElement->Attribute("UseTime", &iValue);
        itemCommon.nUseTime = iValue;

        pItemElement->Attribute("UserTarget", &iValue);
        itemCommon.byUserTarget = iValue;

        //加载外观属性
        MeXmlElement *pAppearanceAttr = pItemElement->FirstChildElement("Appearance");

        itemCommon.cItemClass =ItemDefine::ItemClass_Normal;

        pAppearanceAttr->Attribute("Weight", &iValue);
        itemCommon.fWeight = iValue;

        pAppearanceAttr->Attribute("IconID", &iValue);
        itemCommon.ustIconId = iValue;

        Common::_tstring IconInItemBag;
        IconInItemBag.fromUTF8( pAppearanceAttr->Attribute("IconFile") );
        itemCommon.dwIconInItemBagAddr = AllocStringCopy(IconInItemBag.c_str());

        pAppearanceAttr->Attribute("DropItemModel", &iValue);
        itemCommon.ustModelIDOverGround = iValue;

        pAppearanceAttr->Attribute("HoldGridWidth", &iValue);
        itemCommon.ustItemW = iValue;

        pAppearanceAttr->Attribute("HoldGridHeight", &iValue);
        itemCommon.ustItemH = iValue;

        pAppearanceAttr->Attribute("StackNum", &iValue);
        itemCommon.nStackNum = iValue;

        //加载价格属性
        MeXmlElement *pPriceAttr = pItemElement->FirstChildElement("Price");

        pPriceAttr->Attribute("Bill", &iValue);
        itemCommon.nBill = iValue;

        pPriceAttr->Attribute("CostType", &iValue);
        itemCommon.costType = iValue;

        pPriceAttr->Attribute("Cost", &iValue);
        itemCommon.dwCost = iValue;

        pPriceAttr->Attribute("CostItemID", &iValue);
        itemCommon.costItemID = iValue;

        pPriceAttr->Attribute("SpecialCost", &iValue);
        itemCommon.dwSpecialCost = iValue;

        //加载操作属性
        MeXmlElement *pOperationAttr = pItemElement->FirstChildElement("Operation");

        pOperationAttr->Attribute("CanMoved", &iValue);
        itemCommon.bIsCanMove = iValue;

        pOperationAttr->Attribute("CanDroped", &iValue);
        itemCommon.bIsCanDrop = iValue;

        pOperationAttr->Attribute("CanDeleted", &iValue);
        itemCommon.bIsCanDestory = iValue;

        pOperationAttr->Attribute("CanTrade", &iValue);
        itemCommon.bIsCanTrade = iValue;

        pOperationAttr->Attribute("CanSold", &iValue);
        itemCommon.bIsCanSellShop = iValue;

        pOperationAttr->Attribute("CanStored", &iValue);
        itemCommon.bIsCanPushInStorage = iValue;

        pOperationAttr->Attribute("CanLocked", &iValue);
        itemCommon.bIsCanLocked = iValue;

        pOperationAttr->Attribute("CanBound", &iValue);
        itemCommon.bIsCanBound = iValue;

        pOperationAttr->Attribute("CanSplit", &iValue);
        itemCommon.bIsCanSplit = iValue;

        //加载特效属性
        MeXmlElement *pEffectAttr = pItemElement->FirstChildElement("Effect");

        pEffectAttr->Attribute("IfShowEquipEffect", &iValue);
        itemCommon.bShowEquipEffect = iValue;

        Common::_tstring strCastEffectPath;
        strCastEffectPath.fromUTF8( pEffectAttr->Attribute("CastEffectPath") );
        itemCommon.dwSingEffect = AllocStringCopy(strCastEffectPath.c_str());    

        Common::_tstring strFireEffectPath;
        strFireEffectPath.fromUTF8( pEffectAttr->Attribute("FireEffectPath") );
        itemCommon.dwAssoilEffect = AllocStringCopy(strFireEffectPath.c_str());  

        Common::_tstring strHitEffectPath;
        strHitEffectPath.fromUTF8( pEffectAttr->Attribute("HitEffectPath") );
        itemCommon.dwHurtEffect = AllocStringCopy(strHitEffectPath.c_str()); 

        Common::_tstring strUsingItemSound;
        strUsingItemSound.fromUTF8( pEffectAttr->Attribute("UsingItemSound") );
        itemCommon.dwIconSoundAddr = AllocStringCopy(strUsingItemSound.c_str());

        pEffectAttr->Attribute("UseSingTime", &iValue);
        itemCommon.dwUseSingTime = iValue;

        pEffectAttr->Attribute("CanSingingInterrupt", &iValue);
        itemCommon.bCanSingingInterrupt = iValue;

        //加载阈值属性
        MeXmlElement *pThresholdAttr = pItemElement->FirstChildElement("Threshold");

        pThresholdAttr->Attribute("DropControlCount", &iValue);
        itemCommon.nDropControlCount = iValue;

        pThresholdAttr->Attribute("ClearControlCount", &iValue);
        itemCommon.bIsClearControlCount = iValue;

        pThresholdAttr->Attribute("DropMaxCount", &iValue);
        itemCommon.nDropMaxCount = iValue;

        //////////////////////////////////////////////////////////////////////////

        MeXmlElement *pStatusElement = pItemElement->FirstChildElement("Status");
        if (pStatusElement == NULL)
        { continue; }

        while(pStatusElement != NULL)
        {
            ItemDefine::SItemStatus *pStatus = NULL;
            if ( mode != ConfigLoadMode_Normal)
            {
                int nStatusLevel = 0;
                pStatusElement->Attribute("StatusLevel", &nStatusLevel);
                pStatus = GetStatus(itemCommon.ustItemID , nStatusLevel);
            }

            if ( NULL == pStatus)
            { pStatus = (ItemDefine::SItemStatus*)AllocItem( 0, sizeof( ItemDefine::SItemStatus ) ); }

            if( !pStatus )
            {
                OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
                GetErrorLog()->logString( "Error:内存分配出错!" );
                return false;    
            }

            CopyCommon( pStatus, itemCommon );

            pStatusElement->Attribute("StatusLevel", &iValue);
            pStatus->ustLevel = iValue; 

            pStatusElement->Attribute("StatusType", &iValue);
            pStatus->stType = iValue;


            //特效属性
            MeXmlElement *pStatusEffect =  pStatusElement->FirstChildElement("Effect"); 
            if (pStatusEffect == NULL)
                continue;

            Common::_tstring strEffect;
            strEffect.fromUTF8( pStatusEffect->Attribute("StatusEffect") );
            pStatus->dwStatusEffectAddr = AllocStringCopy( strEffect.c_str() ); 

            Common::_tstring strAction;
            strAction.fromUTF8( pStatusEffect->Attribute("StatusAction") );
            pStatus->dwStatusActionAddr = AllocStringCopy( strAction.c_str() ); 

            Common::_tstring strAnimationName;
            strAnimationName.fromUTF8( pStatusEffect->Attribute("AnimationName") );
            pStatus->dwAnimationAddr = AllocStringCopy( strAnimationName.c_str() );

            Common::_tstring strStatusAnim;
            strStatusAnim.fromUTF8( pStatusEffect->Attribute("StatusAnim") );
            pStatus->nStatusAnim = HelperFunc::GetIDByConstString( (char*)strStatusAnim.c_str(), 
                ItemDefine::g_szStatusAnimType, sizeof(ItemDefine::g_szStatusAnimType)/sizeof( char* ) );


            //攻击属性
            MeXmlElement *pStatusAttack = pStatusElement->FirstChildElement("Attack"); 
            if (pStatusAttack == NULL)
                continue;

            pStatusAttack->Attribute("ChangePhyAttackPer", &iValue);
            pStatus->changePhyAttackPer = iValue;

            pStatusAttack->Attribute("ChangePhyAttack", &iValue);
            pStatus->changePhyAttack = iValue;

            pStatusAttack->Attribute("ChangeMagAttackPer", &iValue);
            pStatus->changeMagAttackPer = iValue;

            pStatusAttack->Attribute("ChangeMagAttack", &iValue);
            pStatus->changeMagAttack = iValue;

            pStatusAttack->Attribute("AddtionalHit", &iValue);
            pStatus->stChanged_Hit = iValue;

            pStatusAttack->Attribute("ChangeCritical",  &iValue);
            pStatus->changed_Critical = iValue;

            pStatusAttack->Attribute("ChangeCriticalIntensity", &iValue);
            pStatus->changed_CriticalIntensity = iValue;

            pStatusAttack->Attribute("AddtionalTenacity", &iValue);
            pStatus->changeTenacity = iValue;

            pStatusAttack->Attribute("AbsorbHp", &iValue);
            pStatus->stAbsorbExtraHPVal = iValue;

            pStatusAttack->Attribute("MoveSpeed", &dValue);
            pStatus->fMoveSpeedChanged = dValue;

            pStatusAttack->Attribute("MoveSpeedPer", &dValue);
            pStatus->nMoveSpeedPer = dValue;

            pStatusAttack->Attribute("AtkSpeedPer", &dValue);
            pStatus->fAttSpeedPer = dValue;

            pStatusAttack->Attribute("SuckHpRate", &dValue);
            pStatus->fSuckHpRate = dValue;

            pStatusAttack->Attribute("SuckHpProbability", &iValue);
            pStatus->nSuckHpProbability = iValue;

            //防御属性
            MeXmlElement *pStatusDefend =  pStatusElement->FirstChildElement("Defend"); 
            if (pStatusDefend == NULL)
                continue;

            pStatusDefend->Attribute("ChangeShortDefendPer", &iValue );
            pStatus->changeDefendPer[EDefendType_Physical] = iValue;

            //pStatusDefend->Attribute("ChangeLongDefendPer", &iValue );
            //pStatus->changeDefendPer[EDefendType_Long] = iValue;

            pStatusDefend->Attribute("ChangeMagicDefendPer", &iValue );
            pStatus->changeDefendPer[EDefendType_Magic] = iValue;

            pStatusDefend->Attribute("ChangeShortDefend", &dValue);
            pStatus->changeDefend[EDefendType_Physical] = dValue;

            //pStatusDefend->Attribute("ChangeLongDefend", &dValue);
            //pStatus->changeDefend[EDefendType_Long] = dValue;

            pStatusDefend->Attribute("ChangeMagicDefend", &dValue);
            pStatus->changeDefend[EDefendType_Magic] = dValue;

            pStatusDefend->Attribute("AddtionalFlee", &iValue);
            pStatus->stChanged_Hedge = iValue;

            pStatusDefend->Attribute("DamReflectPer", &dValue);
            pStatus->fChanged_ReboundVal = dValue; 

            pStatusDefend->Attribute("ChangedFightPoint", &iValue);
            pStatus->stChangedFightPoint = iValue;

            pStatusDefend->Attribute("DamageReflectProability", &iValue);
            pStatus->nDamageReflectProability = iValue;

            pStatusDefend->Attribute("Invincible", &iValue);
            pStatus->bInvincible = iValue;

            pStatusDefend->Attribute("BeCSedAddBufferID", &iValue);
            pStatus->stBeCsedAddBufferMeId = iValue;

            pStatusDefend->Attribute("BeCSedAddBufferLevel", &iValue);
            pStatus->stBeCsedAddBufferMeLevel = iValue;

            //恢复属性
            MeXmlElement *pStatusRestore = pStatusElement->FirstChildElement("Restore"); 
            if (pStatusRestore == NULL)
                continue;

            pStatusRestore->Attribute("MaxHpPer", &dValue);
            pStatus->changeHPMaxPer = dValue;

            pStatusRestore->Attribute("MaxHp", &iValue);
            pStatus->stChanged_HPMax = iValue;

            pStatusRestore->Attribute("MaxMpPer", &dValue);
            pStatus->changeMPMaxPer = dValue;

            pStatusRestore->Attribute("MaxMp", &iValue);
            pStatus->stChanged_MPMax = iValue;

            pStatusRestore->Attribute("RecoverHPPer", &dValue);
            pStatus->resumeHPPer = dValue;

            pStatusRestore->Attribute("RecoverHP", &iValue);
            pStatus->resumeHP = iValue;

            pStatusRestore->Attribute("RecoverMPPer", &dValue);
            pStatus->resumeMPPer = dValue;

            pStatusRestore->Attribute("RecoverMP", &iValue);
            pStatus->resumeMP = iValue;

            pStatusRestore->Attribute("ChangeHp", &iValue);
            pStatus->stChanged_HP = iValue;

            pStatusRestore->Attribute("ChangeHpPer", &iValue);
            pStatus->recoverHPBasePer = iValue;

            pStatusRestore->Attribute("ChangeHpMaxPer", &iValue);
            pStatus->recoverHPMaxPer = iValue;

            pStatusRestore->Attribute("ChangeMp", &iValue);
            pStatus->stChanged_MP = iValue;

            pStatusRestore->Attribute("ChangeMpPer", &iValue);
            pStatus->recoverMPBasePer = iValue;

            pStatusRestore->Attribute("ChangeMpMaxPer", &iValue);
            pStatus->recoverMPMaxPer = iValue;

            pStatusRestore->Attribute("ChangeActivityMax", &iValue);
            pStatus->changeActivityMax = iValue;

            //操作判断
            MeXmlElement *pStatusWhether = pStatusElement->FirstChildElement("Whether"); 
            if (pStatusWhether == NULL)
                continue;

            pStatusWhether->Attribute("CanReplacable", &iValue);
            pStatus->bIsCanCong = iValue;//可否叠加

            pStatusWhether->Attribute("CanMove", &iValue);
            pStatus->bIsMove = iValue;

            pStatusWhether->Attribute("CanPhyAtk", &iValue);
            pStatus->bIsAtt = iValue;

            pStatusWhether->Attribute("CanSkillUse", &iValue);
            pStatus->bIsUsingMagic = iValue;

            pStatusWhether->Attribute("CanBePhyAttack", &iValue);
            pStatus->bIsBePhyAttack = iValue;

            pStatusWhether->Attribute("CanBeMagAttack", &iValue);
            pStatus->bIsBeMagAttack = iValue;

            pStatusWhether->Attribute("CanItemUse", &iValue);
            pStatus->bIsUsingTools = iValue;

            pStatusWhether->Attribute("CanCancel", &iValue);
            pStatus->canCancel = iValue; 

            pStatusWhether->Attribute("IfStatusAdvantageous", &iValue);
            pStatus->bAvail = iValue;

            pStatusWhether->Attribute("IfDispelWhenGetAtk", &iValue);
            pStatus->bAttckedNoStatus = iValue; 

            pStatusWhether->Attribute("IfDispelWhenAtk", &iValue);
            pStatus->bAttckNoStatus = iValue; 

            pStatusWhether->Attribute("IfManaShield", &iValue);
            pStatus->stMagicShield = iValue; 

            pStatusWhether->Attribute("IfUseStatusColour", &iValue);
            pStatus->bUseStateColour = iValue;

            pStatusWhether->Attribute("IfChangeAnimationPlay", &iValue);
            pStatus->bIsChangActionTime = iValue;

            pStatusWhether->Attribute("IfHide", &iValue);
            pStatus->bIsHide = iValue;

            pStatusWhether->Attribute("IsFlyAir", &iValue);
            pStatus->bIsFlyAir = iValue;

            pStatusWhether->Attribute("IfClearStatus", &iValue);
            pStatus->bIsClearDamgeStatus = iValue;

            pStatusWhether->Attribute("IsReplaceOldStatus", &iValue);
            pStatus->bIsReplaceOldStatus = iValue;

            pStatusWhether->Attribute("IsBeCsedAddBuffer", &iValue);
            pStatus->bIsAddBufferBeCSed = iValue;

            pStatusWhether->Attribute("IsAddDeBufferForAttacker", &iValue);
            pStatus->bIsAddDeBufferToAttacker = iValue;

            pStatusWhether->Attribute("IsRandRun", &iValue);
            pStatus->bIsRandRun = iValue;

            pStatusWhether->Attribute("IfDispelWhenBackAttack", &iValue);
            pStatus->bBackAttckedDispel = iValue;

            pStatusWhether->Attribute("IfDispelWhenMove", &iValue);
            pStatus->bMoveDispel = iValue;

            pStatusWhether->Attribute("IfDisableCallGraphic", &iValue);
            pStatus->bDisableCallGraphic = iValue;

            pStatusWhether->Attribute("IfConsumeEnergy", &iValue);
            pStatus->ifConsumeEnergy = iValue;

            pStatusWhether->Attribute("IfStatusIntonate", &iValue);
            pStatus->ifStatusIntonate = iValue;

            //吸收相关
            MeXmlElement *pStatusAbsorb = pStatusElement->FirstChildElement("Absorb"); 
            if (pStatusAbsorb == NULL)
                continue;

            pStatusAbsorb->Attribute("AbsorbDamPer", &dValue);
            pStatus->fSuckDamagePer = dValue;

            pStatusAbsorb->Attribute("MaxAbsorb", &iValue);
            pStatus->stSuckDamageMax = iValue;

            //增加属性
            MeXmlElement *pStatusAdditional = pStatusElement->FirstChildElement("Additional"); 
            if (pStatusAdditional == NULL)
                continue;

            pStatusAdditional->Attribute("AdditionalStr", &iValue);
            pStatus->stAddBaseAttr[EBaseAttr_Strength] = iValue;

            pStatusAdditional->Attribute("AdditionalAgi", &iValue);
            pStatus->stAddBaseAttr[EBaseAttr_Agility] = iValue;

            pStatusAdditional->Attribute("AdditionalCon", &iValue);
            pStatus->stAddBaseAttr[EBaseAttr_Stamina] = iValue;

            pStatusAdditional->Attribute("AdditionalInt", &iValue);
            pStatus->stAddBaseAttr[EBaseAttr_Intelligence] = iValue;

            pStatusAdditional->Attribute("AdditionalStrPer", &iValue);
            pStatus->stAddBaseAttrPer[EBaseAttr_Strength] = iValue;

            pStatusAdditional->Attribute("AdditionalAgiPer", &iValue);
            pStatus->stAddBaseAttrPer[EBaseAttr_Agility] = iValue;

            pStatusAdditional->Attribute("AdditionalConPer", &iValue);
            pStatus->stAddBaseAttrPer[EBaseAttr_Stamina] = iValue;

            pStatusAdditional->Attribute("AdditionalIntPer", &iValue);
            pStatus->stAddBaseAttrPer[EBaseAttr_Intelligence] = iValue;

            pStatusAdditional->Attribute("AddDeBufferForAttackerByHp", &dValue);
            pStatus->fAddDeBufferByHpPer = dValue;

            pStatusAdditional->Attribute("AddDeBufferID", &iValue);
            pStatus->stAddDeBufferID = iValue;

            pStatusAdditional->Attribute("AddDeBufferLevel", &iValue);
            pStatus->stAddDeBufferLevel = iValue;

            pStatusAdditional->Attribute("AddStatusCount",&iValue);
            pStatus->nSuperpositionCount = iValue;

            pStatusAdditional->Attribute("AddExpMul", &dValue);
            pStatus->fAddExpMul = dValue;

            pStatusAdditional->Attribute("AddSkillExpMul", &dValue);
            pStatus->fAddSkillExpMul = dValue;

            pStatusAdditional->Attribute("AddMoney",&iValue);
            pStatus->addMoney = iValue;

            pStatusAdditional->Attribute("AddReputation",&iValue);
            pStatus->addReputation = iValue;

            pStatusAdditional->Attribute("AddExploit",&iValue);
            pStatus->addExploit = iValue;

            pStatusAdditional->Attribute("AddHonour",&iValue);
            pStatus->addHonour = iValue;

            pStatusAdditional->Attribute("AddMasterValue",&iValue);
            pStatus->addMasterValue = iValue;

            pStatusAdditional->Attribute("AddBattleScore",&iValue);
            pStatus->addBattleScore = iValue;

            pStatusAdditional->Attribute("ReputationMul", &dValue);
            pStatus->reputationMul = dValue; 

            pStatusAdditional->Attribute("ExploitMul", &dValue);
            pStatus->exploitMul = dValue; 

            pStatusAdditional->Attribute("HonourMul", &dValue);
            pStatus->honourMul = dValue; 

            pStatusAdditional->Attribute("MasterValueMul", &dValue);
            pStatus->masterValueMul = dValue; 

            pStatusAdditional->Attribute("BattleScoreMul", &dValue);
            pStatus->battleScoreMul = dValue; 

            pStatusAdditional->Attribute("AddHonourLimit",&iValue);
            pStatus->addHonourLimit = iValue;

            //颜色
            MeXmlElement *pStatusColor = pStatusElement->FirstChildElement("Color");
            if (pStatusColor == NULL)
                continue;

            pStatusColor->Attribute("StatusColourRed", &dValue);
            pStatus->fStateColourR = dValue;

            pStatusColor->Attribute("StatusColourGreen", &dValue);
            pStatus->fStateColourG = dValue;

            pStatusColor->Attribute("StatusColourBlue", &dValue);
            pStatus->fStateColourB = dValue;


            //经验
            MeXmlElement *pStatusExpMul = pStatusElement->FirstChildElement("ExpMul");  
            if (pStatusExpMul == NULL)
                continue;

            for (int i=0; i < ItemDefine::SItemStatus::ECD_TimeExpMulModulusCount; ++i)
            {
                char szTmp[65] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "TimeExpMulModulus%d", i+1);
                pStatusExpMul->Attribute(szTmp, &dValue);
                pStatus->timeExpModulus[i] = dValue;
            }

            pStatusExpMul->Attribute("TimeExpMul",&dValue);
            pStatus->timeExpMul = dValue; 

            //其他属性
            MeXmlElement *pStatusOther = pStatusElement->FirstChildElement("Other"); 
            if (pStatusOther == NULL)
                continue;

            pStatusOther->Attribute("KeepTimeOfStatusMs", &iValue);
            pStatus->iDurationTime = iValue;//持续时间

            pStatusOther->Attribute("EffectIntervalTime", &iValue);
            pStatus->iBalanceDelayTime = iValue;

            pStatusOther->Attribute("ChangeAnimationPlay", &dValue);
            pStatus->fChangActionTime = dValue;

            pStatusOther->Attribute("PriorLevel", &iValue);
            pStatus->stPriority = iValue;//优先级

            Common::_tstring strStatusFormula;
            strStatusFormula.fromUTF8(pStatusOther->Attribute("StatusFormula"));
            pStatus->stBalanceType = HelperFunc::GetIDByConstString( (char*)strStatusFormula.c_str(),
                ItemDefine::g_szStatusBalanceType, sizeof(ItemDefine::g_szStatusBalanceType)/sizeof(char*) );//结算公式

            pStatusOther->Attribute("MonsterId", &iValue);
            pStatus->nChangeMonsterID = iValue;

            pStatusOther->Attribute("RestoreType", &iValue);
            pStatus->restoreType = iValue;

            pStatusOther->Attribute("StandingEnmity", &iValue);
            pStatus->nStandingEnmity = iValue;

            pStatusOther->Attribute("ClearStatusByDead", &iValue);
            pStatus->bIsClearByDead = iValue;

            pStatusOther->Attribute("ActualTime", &iValue);
            pStatus->stActualTime = iValue;

            pStatusOther->Attribute("NegativeType", &iValue);
            pStatus->negativeType = iValue;

            pStatusOther->Attribute("DamagetoHp", &iValue);
            pStatus->damagetohp = iValue;

            pStatusOther->Attribute("HurtImmunity", &iValue);
            pStatus->hurtImmunity = iValue;

            pStatusOther->Attribute("ActionMapConfigId",&iValue);
            pStatus->actionMapConfigId = iValue;

            pStatusOther->Attribute("AttackModulus",&iValue);
            pStatus->attackModulus = iValue;

            pStatusOther->Attribute("DefendModulus",&iValue);
            pStatus->defendModulus = iValue;

            for ( int i=0; i<ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize; ++i)
            {
                char szTmp[65] = { 0 };

                sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillId%d",i+1);
                pStatusOther->Attribute(szTmp, &iValue);
                pStatus->changeSkillIds[i] = iValue;

                sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillTimes%d",i+1);
                pStatusOther->Attribute(szTmp, &iValue);
                pStatus->changeSkillTimes[i] = iValue;
            }

            pStatusOther->Attribute("ActivityMul", &dValue);
            pStatus->activityMul = dValue;

            pStatusOther->Attribute("ReduceTax", &iValue);
            pStatus->reduceTax = iValue;

            pStatusOther->Attribute("DeathDurabilityPer", &iValue);
            pStatus->deathDurabilityPer = iValue;

            pStatusOther->Attribute("DeathMountHPDropPer", &iValue);
            pStatus->deathMountHPDropPer = iValue;

            pStatusOther->Attribute("LapoverNum", &iValue);
            pStatus->lapoverNum = iValue;

            pStatusOther->Attribute("LapoverValue", &iValue);
            pStatus->lapoverValue = iValue;

            pStatusOther->Attribute("LapoverMod", &iValue);
            pStatus->lapoverMod = iValue;

            pStatusOther->Attribute("BreakStrike", &iValue);
            pStatus->breakStrike = iValue;
            pStatusOther->Attribute("StabStrike", &iValue);
            pStatus->stabStrike = iValue;
            pStatusOther->Attribute("ElementStrike", &iValue);
            pStatus->elementStrike = iValue;
            pStatusOther->Attribute("ToxinStrike", &iValue);
            pStatus->toxinStrike = iValue;
            pStatusOther->Attribute("SpiritStrike", &iValue);
            pStatus->spiritStrike = iValue;

            pStatusOther->Attribute("BreakResist", &iValue);
            pStatus->breakResist = iValue;
            pStatusOther->Attribute("StabResist", &iValue);
            pStatus->stabResist = iValue;
            pStatusOther->Attribute("ElementResist", &iValue);
            pStatus->elementResist = iValue;
            pStatusOther->Attribute("ToxinResist", &iValue);
            pStatus->toxinResist = iValue;
            pStatusOther->Attribute("SpiritResist", &iValue);
            pStatus->spiritResist = iValue;

            pStatusOther->Attribute("AddEquipAttrType", &iValue);
            pStatus->addEquipAttrType = iValue;

            pStatusOther->Attribute("AddEquipAttrValuePer", &iValue);
            pStatus->addEquipAttrValuePer = iValue;

            pStatusOther->Attribute("AddCatchRate", &iValue);
            pStatus->addCatchPetRate = iValue;

			pStatusOther->Attribute("CanRide", &iValue);
			pStatus->canRide = iValue;
			pStatusOther->Attribute("BeDamagePerHpMax", &iValue);
			pStatus->BeDamagePerHpMax = iValue;

			pStatusOther->Attribute("CanGetHonour", &iValue);
			pStatus->canGetHonour = iValue;
			pStatusOther->Attribute("CanBeGetHonour", &iValue);
			pStatus->canBeGetHonour = iValue;

            //放入相应容器中
            if(pStatus->ustItemID >= ItemDefine::StartID_Status)
            {
                int index;
                index = pStatus->ustItemID-ItemDefine::StartID_Status;
                m_StatusArray[index][pStatus->ustLevel] = *pStatus;

                if(pStatus->ustLevel==1)
                {
                    m_StatusArray[index][ 0 ] = *pStatus;
                }
            }

            m_vecStatusItem.push_back(pStatus);

            AddItemToContainer(pStatus);

            pStatusElement = pStatusElement->NextSiblingElement();

        }

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveStatusItem      ( const char *szFileName )//+保存状态
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

    MeXmlElement *pStatusType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pStatusType == NULL)
    { return false; }

    pStatusType->SetAttribute("Id", ItemDefine::ITEMTYPE_STATUS);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_STATUS  )
        { continue; }

        ItemDefine::SItemStatus *pStatusIter = (ItemDefine::SItemStatus *)*iterBegin;

        MeXmlElement *pItem = pStatusType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pStatusIter->ustItemID);
        Common::_tstring strName = pStatusIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pStatusIter->ucItemType]);
        Common::_tstring strDescription = pStatusIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pStatusIter->nUseTime);
        pItem->SetAttribute("UserTarget", pStatusIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Rare", pStatusIter->cItemClass);
        pAppearance->SetAttribute("Weight", pStatusIter->fWeight);
        pAppearance->SetAttribute("IconID", pStatusIter->ustIconId);
        Common::_tstring strIconFile = pStatusIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pStatusIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pStatusIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pStatusIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pStatusIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pStatusIter->nBill);
        pPrice->SetAttribute("CostType", pStatusIter->costType);
        pPrice->SetAttribute("Cost", pStatusIter->dwCost);
        pPrice->SetAttribute("CostItemID", pStatusIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pStatusIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pStatusIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pStatusIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pStatusIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pStatusIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pStatusIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pStatusIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pStatusIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pStatusIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pStatusIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pStatusIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pStatusIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pStatusIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pStatusIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pStatusIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pStatusIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pStatusIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pStatusIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pStatusIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pStatusIter->nDropMaxCount);

        //////////////////////////////////////////////////////////////////////////
        int index = 0;
        for(int j=1; j < ItemDefine::MaxLevel_Status ; ++j)
        {
            MeXmlElement *pStatus = pItem->InsertEndChild(("Status"))->ToElement();
            if (pStatus == NULL)
                continue;

            if(pStatusIter->ustItemID>=ItemDefine::StartID_Status)
            {
                index = pStatusIter->ustItemID-ItemDefine::StartID_Status;
            }

            pStatus->SetAttribute( "StatusID", pStatusIter->ustItemID );
            Common::_tstring strName = pStatusIter->GetItemName();
            pStatus->SetAttribute( "StatusName", strName.toUTF8().c_str() );
            pStatus->SetAttribute("StatusLevel", m_StatusArray[index][j].ustLevel);
            pStatus->SetAttribute("StatusType", m_StatusArray[index][j].stType);

            //特效属性
            MeXmlElement *pStatusEffect = pStatus->InsertEndChild(("Effect"))->ToElement();
            if (pStatusEffect == NULL)
                continue;

            Common::_tstring strStatusEffect = m_StatusArray[index][j].GetStatusEffectName();
            pStatusEffect->SetAttribute("StatusEffect", strStatusEffect.c_str());
            Common::_tstring strStatusAction = m_StatusArray[index][j].GetStatusAction();
            pStatusEffect->SetAttribute("StatusAction", strStatusAction.c_str());
            Common::_tstring strAnimation = m_StatusArray[index][j].GetAnimationName();
            pStatusEffect->SetAttribute("AnimationName", strAnimation.toUTF8().c_str());
            pStatusEffect->SetAttribute("StatusAnim", ItemDefine::g_szStatusAnimType[m_StatusArray[index][j].nStatusAnim]);

            //攻击属性
            MeXmlElement *pStatusAttack = pStatus->InsertEndChild(("Attack"))->ToElement();
            if (pStatusAttack == NULL)
                continue;

            pStatusAttack->SetAttribute("ChangePhyAttackPer", m_StatusArray[index][j].changePhyAttackPer);
            pStatusAttack->SetDoubleAttribute("ChangePhyAttack", m_StatusArray[index][j].changePhyAttack);
            pStatusAttack->SetAttribute("ChangeMagAttackPer", m_StatusArray[index][j].changeMagAttackPer);
            pStatusAttack->SetDoubleAttribute("ChangeMagAttack", m_StatusArray[index][j].changeMagAttack);

            pStatusAttack->SetAttribute("AddtionalHit", m_StatusArray[index][j].stChanged_Hit);
            pStatusAttack->SetAttribute("ChangeCritical", m_StatusArray[index][j].changed_Critical);
            pStatusAttack->SetAttribute("ChangeCriticalIntensity", m_StatusArray[index][j].changed_CriticalIntensity);
            pStatusAttack->SetAttribute("AddtionalTenacity", m_StatusArray[index][j].changeTenacity);
            pStatusAttack->SetAttribute("AbsorbHp", m_StatusArray[index][j].stAbsorbExtraHPVal);
            pStatusAttack->SetDoubleAttribute("MoveSpeed", m_StatusArray[index][j].fMoveSpeedChanged);
            pStatusAttack->SetAttribute("MoveSpeedPer", m_StatusArray[index][j].nMoveSpeedPer);
            pStatusAttack->SetDoubleAttribute("AtkSpeedPer", m_StatusArray[index][j].fAttSpeedPer);
            pStatusAttack->SetDoubleAttribute("SuckHpRate", m_StatusArray[index][j].fSuckHpRate);
            pStatusAttack->SetAttribute("SuckHpProbability", m_StatusArray[index][j].nSuckHpProbability);

            //防御属性
            MeXmlElement *pStatusDefend = pStatus->InsertEndChild(("Defend"))->ToElement();
            if (pStatusDefend == NULL)
                continue;

            pStatusDefend->SetDoubleAttribute("ChangeShortDefendPer", m_StatusArray[index][j].changeDefendPer[EDefendType_Physical] );
            //pStatusDefend->SetAttribute("ChangeLongDefendPer", m_StatusArray[index][j].changeDefendPer[EDefendType_Long]); 
            pStatusDefend->SetAttribute("ChangeMagicDefendPer", m_StatusArray[index][j].changeDefendPer[EDefendType_Magic]); 
            pStatusDefend->SetAttribute("ChangeShortDefend", m_StatusArray[index][j].changeDefend[EDefendType_Physical]);
            //pStatusDefend->SetAttribute("ChangeLongDefend", m_StatusArray[index][j].changeDefend[EDefendType_Long]);
            pStatusDefend->SetAttribute("ChangeMagicDefend", m_StatusArray[index][j].changeDefend[EDefendType_Magic]);
            pStatusDefend->SetAttribute("AddtionalFlee", m_StatusArray[index][j].stChanged_Hedge);
            pStatusDefend->SetDoubleAttribute("DamReflectPer", m_StatusArray[index][j].fChanged_ReboundVal);
            pStatusDefend->SetAttribute("ChangedFightPoint", m_StatusArray[index][j].stChangedFightPoint);
            pStatusDefend->SetAttribute("DamageReflectProability", m_StatusArray[index][j].nDamageReflectProability);
            pStatusDefend->SetAttribute("Invincible", m_StatusArray[index][j].bInvincible);
            pStatusDefend->SetAttribute("BeCSedAddBufferID", m_StatusArray[index][j].stBeCsedAddBufferMeId);
            pStatusDefend->SetAttribute("BeCSedAddBufferLevel", m_StatusArray[index][j].stBeCsedAddBufferMeLevel);

            //恢复属性
            MeXmlElement *pStatusRestore = pStatus->InsertEndChild(("Restore"))->ToElement();
            if (pStatusRestore == NULL)
                continue;

            pStatusRestore->SetAttribute("MaxHpPer", m_StatusArray[index][j].changeHPMaxPer);
            pStatusRestore->SetAttribute("MaxHp", m_StatusArray[index][j].stChanged_HPMax);
            pStatusRestore->SetAttribute("MaxMpPer", m_StatusArray[index][j].changeMPMaxPer);
            pStatusRestore->SetAttribute("MaxMp", m_StatusArray[index][j].stChanged_MPMax);
            pStatusRestore->SetAttribute("RecoverHPPer", m_StatusArray[index][j].resumeHPPer);
            pStatusRestore->SetAttribute("RecoverHP", m_StatusArray[index][j].resumeHP);
            pStatusRestore->SetAttribute("RecoverMPPer", m_StatusArray[index][j].resumeMPPer);
            pStatusRestore->SetAttribute("RecoverMP", m_StatusArray[index][j].resumeMP);
            pStatusRestore->SetAttribute("ChangeHp", m_StatusArray[index][j].stChanged_HP);
            pStatusRestore->SetAttribute("ChangeHpPer", m_StatusArray[index][j].recoverHPBasePer);
            pStatusRestore->SetAttribute("ChangeHpMaxPer", m_StatusArray[index][j].recoverHPMaxPer);
            pStatusRestore->SetAttribute("ChangeMp", m_StatusArray[index][j].stChanged_MP);
            pStatusRestore->SetAttribute("ChangeMpPer", m_StatusArray[index][j].recoverMPBasePer);
            pStatusRestore->SetAttribute("ChangeMpMaxPer", m_StatusArray[index][j].recoverMPMaxPer);
            pStatusRestore->SetAttribute("ChangeActivityMax", m_StatusArray[index][j].changeActivityMax);

            //操作判断
            MeXmlElement *pStatusWhether = pStatus->InsertEndChild(("Whether"))->ToElement();
            if (pStatusWhether == NULL)
                continue;

            pStatusWhether->SetAttribute("CanReplacable", m_StatusArray[index][j].bIsCanCong);
            pStatusWhether->SetAttribute("CanMove", m_StatusArray[index][j].bIsMove);
            pStatusWhether->SetAttribute("CanPhyAtk", m_StatusArray[index][j].bIsAtt);
            pStatusWhether->SetAttribute("CanSkillUse", m_StatusArray[index][j].bIsUsingMagic);
            pStatusWhether->SetAttribute("CanBePhyAttack", m_StatusArray[index][j].bIsBePhyAttack);
            pStatusWhether->SetAttribute("CanBeMagAttack", m_StatusArray[index][j].bIsBeMagAttack);
            pStatusWhether->SetAttribute("CanItemUse", m_StatusArray[index][j].bIsUsingTools);
            pStatusWhether->SetAttribute("CanCancel", m_StatusArray[index][j].canCancel);
            pStatusWhether->SetAttribute("IfStatusAdvantageous", m_StatusArray[index][j].bAvail);
            pStatusWhether->SetAttribute("IfDispelWhenGetAtk", m_StatusArray[index][j].bAttckedNoStatus);
            pStatusWhether->SetAttribute("IfDispelWhenAtk", m_StatusArray[index][j].bAttckNoStatus);
            pStatusWhether->SetAttribute("IfManaShield", m_StatusArray[index][j].stMagicShield);
            pStatusWhether->SetAttribute("IfUseStatusColour", m_StatusArray[index][j].bUseStateColour);
            pStatusWhether->SetAttribute("IfChangeAnimationPlay", m_StatusArray[index][j].bIsChangActionTime);
            pStatusWhether->SetAttribute("IfHide", m_StatusArray[index][j].bIsHide);
            pStatusWhether->SetAttribute("IsFlyAir", m_StatusArray[index][j].bIsFlyAir);
            pStatusWhether->SetAttribute("IfClearStatus", m_StatusArray[index][j].bIsClearDamgeStatus);
            pStatusWhether->SetAttribute("IsReplaceOldStatus", m_StatusArray[index][j].bIsReplaceOldStatus);
            pStatusWhether->SetAttribute("IsBeCsedAddBuffer", m_StatusArray[index][j].bIsAddBufferBeCSed);
            pStatusWhether->SetAttribute("IsAddDeBufferForAttacker", m_StatusArray[index][j].bIsAddDeBufferToAttacker);
            pStatusWhether->SetAttribute("IsRandRun", m_StatusArray[index][j].bIsRandRun);
            pStatusWhether->SetAttribute("IfDispelWhenBackAttack", m_StatusArray[index][j].bBackAttckedDispel);
            pStatusWhether->SetAttribute("IfDispelWhenMove", m_StatusArray[index][j].bMoveDispel);
            pStatusWhether->SetAttribute("IfDisableCallGraphic", m_StatusArray[index][j].bDisableCallGraphic);

            pStatusWhether->SetAttribute("IfConsumeEnergy", m_StatusArray[index][j].ifConsumeEnergy);
            pStatusWhether->SetAttribute("IfStatusIntonate", m_StatusArray[index][j].ifStatusIntonate);

            //吸收相关
            MeXmlElement *pStatusAbsorb = pStatus->InsertEndChild(("Absorb"))->ToElement();
            if (pStatusAbsorb == NULL)
                continue;

            pStatusAbsorb->SetDoubleAttribute("AbsorbDamPer", m_StatusArray[index][j].fSuckDamagePer);
            pStatusAbsorb->SetAttribute("MaxAbsorb", m_StatusArray[index][j].stSuckDamageMax);

            //增加属性
            MeXmlElement *pStatusAdditional = pStatus->InsertEndChild(("Additional"))->ToElement();
            if (pStatusAdditional == NULL)
                continue;

            pStatusAdditional->SetAttribute("AdditionalStr", m_StatusArray[index][j].stAddBaseAttr[EBaseAttr_Strength]);
            pStatusAdditional->SetAttribute("AdditionalAgi", m_StatusArray[index][j].stAddBaseAttr[EBaseAttr_Agility]);
            pStatusAdditional->SetAttribute("AdditionalCon", m_StatusArray[index][j].stAddBaseAttr[EBaseAttr_Stamina]);
            pStatusAdditional->SetAttribute("AdditionalInt", m_StatusArray[index][j].stAddBaseAttr[EBaseAttr_Intelligence]);
            pStatusAdditional->SetAttribute("AdditionalStrPer", m_StatusArray[index][j].stAddBaseAttrPer[EBaseAttr_Strength]);
            pStatusAdditional->SetAttribute("AdditionalAgiPer", m_StatusArray[index][j].stAddBaseAttrPer[EBaseAttr_Agility]);
            pStatusAdditional->SetAttribute("AdditionalConPer", m_StatusArray[index][j].stAddBaseAttrPer[EBaseAttr_Stamina]);
            pStatusAdditional->SetAttribute("AdditionalIntPer", m_StatusArray[index][j].stAddBaseAttrPer[EBaseAttr_Intelligence]);
            pStatusAdditional->SetDoubleAttribute("AddDeBufferForAttackerByHp", m_StatusArray[index][j].fAddDeBufferByHpPer);
            pStatusAdditional->SetAttribute("AddDeBufferID", m_StatusArray[index][j].stAddDeBufferID);
            pStatusAdditional->SetAttribute("AddDeBufferLevel", m_StatusArray[index][j].stAddDeBufferLevel);
            pStatusAdditional->SetAttribute("AddStatusCount", m_StatusArray[index][j].nSuperpositionCount);
            pStatusAdditional->SetDoubleAttribute("AddExpMul", m_StatusArray[index][j].fAddExpMul);
            pStatusAdditional->SetDoubleAttribute("AddSkillExpMul", m_StatusArray[index][j].fAddSkillExpMul);

            pStatusAdditional->SetAttribute("AddMoney", m_StatusArray[index][j].addMoney);
            pStatusAdditional->SetAttribute("AddReputation", m_StatusArray[index][j].addReputation);
            pStatusAdditional->SetAttribute("AddExploit", m_StatusArray[index][j].addExploit);
            pStatusAdditional->SetAttribute("AddHonour", m_StatusArray[index][j].addHonour);
            pStatusAdditional->SetAttribute("AddMasterValue", m_StatusArray[index][j].addMasterValue);
            pStatusAdditional->SetAttribute("AddBattleScore", m_StatusArray[index][j].addBattleScore);

            pStatusAdditional->SetDoubleAttribute("ReputationMul", m_StatusArray[index][j].reputationMul);
            pStatusAdditional->SetDoubleAttribute("ExploitMul", m_StatusArray[index][j].exploitMul);
            pStatusAdditional->SetDoubleAttribute("HonourMul", m_StatusArray[index][j].honourMul);
            pStatusAdditional->SetDoubleAttribute("MasterValueMul", m_StatusArray[index][j].masterValueMul);
            pStatusAdditional->SetDoubleAttribute("BattleScoreMul", m_StatusArray[index][j].battleScoreMul);

            pStatusAdditional->SetAttribute("AddHonourLimit", m_StatusArray[index][j].addHonourLimit);

            //颜色
            MeXmlElement *pStatusColor = pStatus->InsertEndChild(("Color"))->ToElement();
            if (pStatusColor == NULL)
                continue;

            pStatusColor->SetDoubleAttribute("StatusColourRed", m_StatusArray[index][j].fStateColourR);
            pStatusColor->SetDoubleAttribute("StatusColourGreen", m_StatusArray[index][j].fStateColourG);
            pStatusColor->SetDoubleAttribute("StatusColourBlue", m_StatusArray[index][j].fStateColourB);

            //经验
            MeXmlElement *pStatusExpMul = pStatus->InsertEndChild(("ExpMul"))->ToElement();
            if (pStatusExpMul == NULL)
                continue;

            for (int k=0; k<ItemDefine::SItemStatus::ECD_TimeExpMulModulusCount; ++k)
            {
                char szTmp[65] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "TimeExpMulModulus%d", k+1);
                pStatusExpMul->SetDoubleAttribute(szTmp, m_StatusArray[index][j].timeExpModulus[k]); 
            }

            pStatusExpMul->SetDoubleAttribute("TimeExpMul", m_StatusArray[index][j].timeExpMul);

            //其他属性
            MeXmlElement *pStatusOther = pStatus->InsertEndChild(("Other"))->ToElement();
            if (pStatusOther == NULL)
                continue;

            pStatusOther->SetAttribute("KeepTimeOfStatusMs", m_StatusArray[index][j].iDurationTime);
            pStatusOther->SetAttribute("EffectIntervalTime", m_StatusArray[index][j].iBalanceDelayTime);
            pStatusOther->SetDoubleAttribute("ChangeAnimationPlay", m_StatusArray[index][j].fChangActionTime);
            pStatusOther->SetAttribute("PriorLevel", m_StatusArray[index][j].stPriority);
            pStatusOther->SetAttribute("StatusFormula", ItemDefine::g_szStatusBalanceType[m_StatusArray[index][j].stBalanceType]);
            pStatusOther->SetAttribute("MonsterId", m_StatusArray[index][j].nChangeMonsterID);
            pStatusOther->SetAttribute("RestoreType", m_StatusArray[index][j].restoreType);
            pStatusOther->SetAttribute("StandingEnmity", m_StatusArray[index][j].nStandingEnmity);
            pStatusOther->SetAttribute("ClearStatusByDead", m_StatusArray[index][j].bIsClearByDead);
            pStatusOther->SetAttribute("ActualTime", m_StatusArray[index][j].stActualTime);
            pStatusOther->SetAttribute("NegativeType", m_StatusArray[index][j].negativeType);
            pStatusOther->SetAttribute("DamagetoHp", m_StatusArray[index][j].damagetohp);
            pStatusOther->SetAttribute("HurtImmunity", m_StatusArray[index][j].hurtImmunity);
            pStatusOther->SetAttribute("ActionMapConfigId", m_StatusArray[index][j].actionMapConfigId);

            pStatusOther->SetAttribute("AttackModulus", m_StatusArray[index][j].attackModulus);
            pStatusOther->SetAttribute("DefendModulus", m_StatusArray[index][j].defendModulus);

            for ( int k=0; k<ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize; ++k)
            {
                char szTmp[65] = { 0 };
                sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillId%d",k+1);
                pStatusOther->SetAttribute(szTmp, m_StatusArray[index][j].changeSkillIds[k]);

                sprintf_s(szTmp, sizeof(szTmp) - 1, "ChangeSkillTimes%d",k+1);
                pStatusOther->SetAttribute(szTmp, m_StatusArray[index][j].changeSkillTimes[k]);
            }

            pStatusOther->SetDoubleAttribute("ActivityMul", m_StatusArray[index][j].activityMul);

            pStatusOther->SetAttribute("ReduceTax", m_StatusArray[index][j].reduceTax);
            pStatusOther->SetAttribute("DeathDurabilityPer", m_StatusArray[index][j].deathDurabilityPer);
            pStatusOther->SetAttribute("DeathMountHPDropPer", m_StatusArray[index][j].deathMountHPDropPer);

            pStatusOther->SetAttribute("LapoverNum", m_StatusArray[index][j].lapoverNum);
            pStatusOther->SetAttribute("LapoverValue", m_StatusArray[index][j].lapoverValue);
            pStatusOther->SetAttribute("LapoverMod", m_StatusArray[index][j].lapoverMod);

            pStatusOther->SetAttribute("BreakStrike", m_StatusArray[index][j].breakStrike);
            pStatusOther->SetAttribute("StabStrike", m_StatusArray[index][j].stabStrike);
            pStatusOther->SetAttribute("ElementStrike", m_StatusArray[index][j].elementStrike);
            pStatusOther->SetAttribute("ToxinStrike", m_StatusArray[index][j].toxinStrike);
            pStatusOther->SetAttribute("SpiritStrike", m_StatusArray[index][j].spiritStrike);

            pStatusOther->SetAttribute("BreakResist", m_StatusArray[index][j].breakResist);
            pStatusOther->SetAttribute("StabResist", m_StatusArray[index][j].stabResist);
            pStatusOther->SetAttribute("ElementResist", m_StatusArray[index][j].elementResist);
            pStatusOther->SetAttribute("ToxinResist", m_StatusArray[index][j].toxinResist);
            pStatusOther->SetAttribute("SpiritResist", m_StatusArray[index][j].spiritResist);

            pStatusOther->SetAttribute("AddEquipAttrType", m_StatusArray[index][j].addEquipAttrType);
            pStatusOther->SetAttribute("AddEquipAttrValuePer", m_StatusArray[index][j].addEquipAttrValuePer);

            pStatusOther->SetAttribute("AddCatchRate", m_StatusArray[index][j].addCatchPetRate);
			pStatusOther->SetAttribute("CanRide", m_StatusArray[index][j].canRide);
			pStatusOther->SetAttribute("BeDamagePerHpMax", m_StatusArray[index][j].BeDamagePerHpMax);

			pStatusOther->SetAttribute("CanGetHonour", m_StatusArray[index][j].canGetHonour);
			pStatusOther->SetAttribute("CanBeGetHonour", m_StatusArray[index][j].canBeGetHonour);
        }

    }

    return MeXmlDoc.SaveFile(szFileName);
}

#pragma warning( pop )