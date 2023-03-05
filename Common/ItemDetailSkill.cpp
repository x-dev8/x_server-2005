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

ItemDefine::SItemSkill * CItemDetail::GetSkillByID(unsigned short ustSkillItemID,  unsigned short ustSkillLevel)
{
    if( !GetItemByID( ustSkillItemID ) )
        return NULL;

    if(ustSkillItemID<ItemDefine::StartID_Skill)
        return NULL;

    int index = ustSkillItemID-ItemDefine::StartID_Skill;

    if (index<0 || index>=ItemDefine::MaxNum_Skill)
        return NULL;

    if (ustSkillLevel<= 0 || ustSkillLevel>=ItemDefine::MaxLevel_Skill)
        return NULL;

    ItemDefine::SItemSkill* pSkill = &(m_SkillArray[index][ustSkillLevel]);
    if (ustSkillLevel > pSkill->ustSkillMaxLvl)
        return NULL;
    return pSkill;
}

ItemDefine::SItemSkill * CItemDetail::GetSkillByIndex( int iIndex )
{
    if( iIndex < 0 || iIndex >= (int)m_vecSkill.size() )
        return 0;
  ItemDefine::SItemCommon * pCommon = GetItemByID( m_vecSkill[ iIndex ] );
    if( !pCommon || pCommon->ucItemType != ItemDefine::ITEMTYPE_SKILL )
        return 0;
    return (ItemDefine::SItemSkill*)pCommon;
}

int CItemDetail::GetSkillIndexByID( unsigned short ustSkillItemID )
{
    mapSkillNO::iterator it;
    it = m_mapSkillNO.find( ustSkillItemID );
    if( it == m_mapSkillNO.end() )
        return -1;
    return it->second;
}

DWORD CItemDetail::GetSkillHoldTime(unsigned short ustSkillID, unsigned short ustSkillLevel)
{
    return GetSkillHoldTime( GetSkillByID( ustSkillID, ustSkillLevel));
}

DWORD CItemDetail::GetSkillHoldTime(ItemDefine::SItemSkill *pSkill)
{
    if ( NULL == pSkill )
    { return 0; }

    return pSkill->ustHoldTime;
}

BOOL CItemDetail::GetSkillNeedInfo( SCharBaseInfo *pCharBaseInfo,
                                   SCharOtherDataClient *pCharOtherInfo,int nSkillCurExp,
                                   int nId, int nLevel, char* szSkillInfo, size_t SkillInfoSize )
{
    if ( !pCharBaseInfo || !pCharOtherInfo )
    {
        // ToLog( pCharBaseInfo );
        // ToLog( pCharOtherInfo );
        return FALSE;
    }
    //
    BOOL bResutl = TRUE;
    char szInfo[512] = {0};
    char szTemp[128] = {0};
    //
    ItemDefine::SItemSkill *pSkill = NULL;
    pSkill = GettheItemDetail().GetSkillByID( nId, nLevel );
    if ( !pSkill )
    {
        //    // ToLog( pSkill );
        return FALSE;
    }
    //
    if ( pSkill->stLearnLevelReq != 0 )
    {
        if( pCharBaseInfo->liveinfo.ustLevel < pSkill->stLearnLevelReq )
        {
            size_t freesize = sizeof(szInfo) - strlen(szInfo);
            strncat(szInfo, "<#ffff0000=", freesize-1);
            bResutl = FALSE;
        }
        _snprintf( szTemp, sizeof(szTemp)-1,theXmlString.GetString(eTip_LearnSkillLevelReq)  /*"需要等级:%ld\n"*/, pSkill->stLearnLevelReq );
        HelperFunc::AddNCpy(szTemp,"\n", sizeof(szTemp)-1);
        size_t freesize = sizeof(szInfo) - strlen(szInfo);
        strncat( szInfo, szTemp, freesize-1 );
    }
    if ( pSkill->stMoneyNeed != 0 )
    {
        if ( pCharBaseInfo->liveinfo.dwMoney < pSkill->stMoneyNeed )
        {
            size_t freesize = sizeof(szInfo) - strlen(szInfo);
            strncat( szInfo, "<#ffff0000=", freesize-1 );
            bResutl = FALSE;
        }
        _snprintf( szTemp, sizeof(szTemp)-1,theXmlString.GetString(eTip_LearnSkillMoneyNeed) /*"需要金钱:%ld\n"*/, pSkill->stMoneyNeed );
        HelperFunc::AddNCpy(szTemp,"\n", sizeof(szTemp)-1);
        size_t freesize = sizeof(szInfo) - strlen(szInfo);
        strncat( szInfo, szTemp, freesize-1 );
    }
    //if( pSkill->stRankNeed > 0 )
    //{
    //    if ( pCharBaseInfo->byOfficialLevel < pSkill->stRankNeed )
    //    {
    //        strcat( szInfo, "<#ffff0000=" );
    //        bResutl = false;
    //    }
    //    int nCountry = pCharBaseInfo->ucCountry;
    //    COfficialMgr::Record* r = g_officialMgr.GetRecord( pSkill->stRankNeed );
    //    sprintf( szTemp, "需要官衔:%s\n",r->szOfficialTitle[nCountry] );
    //    strcat( szInfo, szTemp );
    //}
    //////////////////////////////////////////////////////////////////////////
    //    学习时的 技能牵制条件
    for(int idx = 0; idx<3; idx++)
    {
        if ( pSkill->stSkillNeed[idx] != -1 && pSkill->stSkillLevelNeed[idx] != -1 )
        {
            ItemDefine::SItemSkill *pPreSkill = 
                GettheItemDetail().GetSkillByID( pSkill->stSkillNeed[idx], pSkill->stSkillLevelNeed[idx] );
            if ( pPreSkill )
            {
                int nSkillLevel = -1;
                for ( int n = 0; n<More_iMaxSkillKnown; n++ )
                {
                    if ( pCharOtherInfo->skills.skill[n].ustSkillID == pSkill->stSkillNeed[idx] )
                    {
                        nSkillLevel = pCharOtherInfo->skills.skill[n].stSkillLevel;
                        break;
                    }
                }
                if ( nSkillLevel < pSkill->stSkillLevelNeed[idx] )
                {
                    size_t freesize = sizeof(szInfo) - strlen(szInfo);
                    strncat( szInfo, "<#ffff0000=", freesize-1 );
                    bResutl = false;
                }
                _snprintf( szTemp, sizeof(szTemp)-1,/* "需要技能:%ld级%s\n"*/theXmlString.GetString(eTip_LearnSkillLevelNeed),
                    pSkill->stSkillLevelNeed[idx], 
                    //pPreSkill->szItemName.c_str() );
                    GetString( pPreSkill->dwItemNameAddr ) );
                HelperFunc::AddNCpy(szTemp,"\n", sizeof(szTemp)-1);
                size_t freesize = sizeof(szInfo) - strlen(szInfo);
                strncat( szInfo, szTemp, freesize-1 );
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////

    //if ( pSkill->stSkillNeed != -1 && pSkill->stSkillLevelNeed != -1 )
    //{
    //    ItemDefine::SItemSkill *pPreSkill = 
    //        GettheItemDetail().GetSkillByID( pSkill->stSkillNeed, pSkill->stSkillLevelNeed );
    //    if ( pPreSkill )
    //    {
    //        int nSkillLevel = -1;
    //        for ( int n = 0; n<More_iMaxSkillKnown; n++ )
    //        {
    //            if ( pCharOtherInfo->skills.skill[n].ustSkillID == pSkill->stSkillNeed )
    //            {
    //                nSkillLevel = pCharOtherInfo->skills.skill[n].stSkillLevel;
    //                break;
    //            }
    //        }
    //        if ( nSkillLevel < pSkill->stSkillLevelNeed )
    //        {
    //            strcat( szInfo, "<#ffff0000=" );
    //            bResutl = false;
    //        }
    //        sprintf( szTemp, "需要技能:%ld级%s\n",
    //            pSkill->stSkillLevelNeed, 
    //            //pPreSkill->szItemName.c_str() );
    //            GetString( pPreSkill->dwItemNameAddr ) );
    //        strcat( szInfo, szTemp );
    //    }
    //}
    /*if ( pSkill->stVITNeed != 0 )
    {
    if ( pCharBaseInfo->baseAttribute[EBaseAttr_Constitution].fFinal < pSkill->stVITNeed )
    {
    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, "<#ffff0000=", freesize-1 );
    bResutl = FALSE;
    }
    _snprintf( szTemp, sizeof(szTemp)-1, "需要体力:%d\n", pSkill->stVITNeed );

    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, szTemp, freesize-1 );
    }
    if ( pSkill->stSTRNeed != 0 )
    {
    if ( pCharBaseInfo->baseAttribute[EBaseAttr_Strength].fFinal < pSkill->stSTRNeed )
    {
    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, "<#ffff0000=", freesize-1 );
    bResutl = FALSE;
    }
    _snprintf( szTemp, sizeof(szTemp)-1, "需要力量:%d\n", pSkill->stSTRNeed );

    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, szTemp, freesize-1 );
    }
    if ( pSkill->stAGINeed != 0 )
    {
    if ( pCharBaseInfo->baseAttribute[EBaseAttr_Agility].fFinal < pSkill->stAGINeed )
    {
    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, "<#ffff0000=", freesize-1 );
    bResutl = FALSE;
    }
    _snprintf( szTemp, sizeof(szTemp)-1, "需要敏捷:%d\n", pSkill->stAGINeed );

    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, szTemp, freesize-1 );
    }
    if ( pSkill->stINTNeed != 0 )
    {
    if ( pCharBaseInfo->baseAttribute[EBaseAttr_Intelligence].fFinal < pSkill->stINTNeed )
    {
    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, "<#ffff0000=", freesize-1 );
    bResutl = FALSE;
    }
    _snprintf( szTemp, sizeof(szTemp)-1, "需要智力:%d\n", pSkill->stINTNeed );

    size_t freesize = sizeof(szInfo) - strlen(szInfo);
    strncat( szInfo, szTemp, freesize-1 );
    }*/
    //技能经验点需求
    //     if( pCharBaseInfo->liveinfo.dwSkillExp < pSkill->nLearnNeedExp )
    //     {
    //         size_t freesize = sizeof(szInfo) - strlen(szInfo);
    //         strncat( szInfo, "<#ffff0000=", freesize-1 );
    //         bResutl = FALSE;
    //     }

    //     char chTemp[256] = {0};
    //     if( pSkill->nLearnNeedExp > 0)
    //     {
    //         _snprintf(chTemp,sizeof(chTemp)-1,theXmlString.GetString(eTip_SkillLearnNeedExp) /*"技能修炼值【%d/%d·%0.2f％】"*/ ,nSkillCurExp, pSkill->nLearnNeedExp,
    //             (float)nSkillCurExp*100/pSkill->nLearnNeedExp );
    //         HelperFunc::AddNCpy(chTemp,"\n", sizeof(chTemp)-1);
    //         size_t freesize = sizeof(szInfo) - strlen(szInfo);
    //         strncat( szInfo, chTemp, freesize-1 );
    //     }
    /*sprintf( szInfo, "%s \n需要 %d 点技能点", pSkill->stNeedPoitToLearskill );*/
    //
    if ( szSkillInfo )
    {
        strncpy_s(szSkillInfo, SkillInfoSize, szInfo, SkillInfoSize-1);
    }
    return bResutl;
}

bool CItemDetail::AddSkillItem( const char *szFileName )
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

    int     iValue;
    int     nValue;
    float   fValue;

    char  szTemp[256] = {0};
    std::string strTemp;
    std::string strValue;

    while ( CSlkReader::ret_readover != ( iRet = pReader.GotoNextLine( offset++ ) ) ) 
    {   
        if( CSlkReader::ret_nothisline == iRet )
            continue;

        int nItemID = -1;
        if( !GetIntField( &pReader,"SkillID",nItemID ) )
        {
            OutputSlkLoadingMessage( "\t%s  错误:读取 SkillID 出错，行号 %d \r\n",szFileName,offset );
            return false;
        }

      ItemDefine::SItemCommon *pCommon = GetItemByID( nItemID );

        if(pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_SKILL)
        {
            OutputSlkLoadingMessage( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            GetErrorLog()->logString( "\t%s 警告:ItemID: %d 在 Item.slk 中无记录  \r\n",szFileName,nItemID );
            continue;
            //return false;   
        }

        ItemDefine::SItemSkill *pItemSkill = (ItemDefine::SItemSkill *)pCommon;

        SLK_GET_STRING( strValue,   "SkillName" );
        pItemSkill->dwSkillNameAddr = AllocStringCopy( strValue.c_str() );
		
		SLK_GET_STRING( strValue,   "RideAction" );
		pItemSkill->dwRideAction = AllocStringCopy( strValue.c_str() );

        for ( int i=0; i<ItemDefine::SItemSkill::EItemSkillConst_ActionMaxSize; ++i)
        {
            sprintf_s( szTemp, sizeof(szTemp), "SkillAct%d", i+1 );
            SLK_GET_STRING( strValue, szTemp );
            pItemSkill->dwSkillAction[i] = AllocStringCopy( strValue.c_str() );
        }

        SLK_GET_INT   ( pItemSkill->groupId,    "GroupID" );
        SLK_GET_INT   ( pItemSkill->groupLevel, "GroupLevel" );

        SLK_GET_INT   ( pItemSkill->ustLevel,     "SkillLv"   );
        SLK_GET_INT   ( pItemSkill->ustPrepTime,  "CastSpeed" );
        SLK_GET_INT   ( pItemSkill->bShowIntonateBar, "IfShowIntonateBar" );

        SLK_GET_STRING( strValue, "CastAct"   );
        pItemSkill->dwIntonateAction = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "CastEffect(Male)" );
        pItemSkill->dwIntonateEffectAddr = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "ReleaseEffect(Male)" );
        pItemSkill->dwAttackerEffectAddr = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "TraceEffect(Male)" );
        pItemSkill->dwSkillEffectAddr = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "HitEffect(Male)" );
        pItemSkill->dwTargetEffectAddr = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "CastEffect(Female)" );
        pItemSkill->dwIntonateEffectAddr2 = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "ReleaseEffect(Female)" );
        pItemSkill->dwAttackerEffectAddr2 = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "TraceEffect(Female)" );
        pItemSkill->dwSkillEffectAddr2 = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING( strValue, "HitEffect(Female)" );
        pItemSkill->dwTargetEffectAddr2 = AllocStringCopy( strValue.c_str() );

        SLK_GET_STRING   ( strValue,  "HurtAct" );
        pItemSkill->ustIDTargetHitAction = FindActionIdByName( strValue.c_str() );

        SLK_GET_INT  ( pItemSkill->triggerType , "TriggerType" );
        SLK_GET_FLOAT( pItemSkill->actionRatio , "ActionRatio" );

        SLK_GET_INT   ( pItemSkill->normalAttackRatio, "NormalAttackRatio" );

        SLK_GET_INT   ( pItemSkill->ustMeAddStatusID[0]    , "AddStatus1(me)"   );
        SLK_GET_INT   ( pItemSkill->ustMeAddStatusLevel[0] , "AddStatusLv1(me)" );
        SLK_GET_INT   ( pItemSkill->ustMeAddStatusID[1]    , "AddStatus2(me)"   );
        SLK_GET_INT   ( pItemSkill->ustMeAddStatusLevel[1] , "AddStatusLv2(me)" );

        SLK_GET_INT   ( pItemSkill->ustDstAddStatusID[0]   , "AddStatus1(Target)"   );
        SLK_GET_INT   ( pItemSkill->ustDstAddStatusLevel[0], "AddStatusLv1(Target)" );
        SLK_GET_INT   ( pItemSkill->ustDstAddStatusID[1]   , "AddStatus2(Target)"   );
        SLK_GET_INT   ( pItemSkill->ustDstAddStatusLevel[1], "AddStatusLv2(Target)" );

        SLK_GET_INT   ( pItemSkill->ustStatusHitRate    , "StatusHitRate"       );
        SLK_GET_INT   ( pItemSkill->dwSubComboStatus    , "StatusDispel"        );

        for ( int i=0; i<ItemDefine::CLEAR_MAX_STATUS; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "StatusDispel%d", i );
            SLK_GET_INT( pItemSkill->dwClearStatus[i], szTemp );
        }

        SLK_GET_INT   ( pItemSkill->ustHoldTime, "FreezeTime" );

        SLK_GET_STRING( strValue, "UseFormula" );
        pItemSkill->ustDamageBalanceType = HelperFunc::GetIDByConstString( (char*)strValue.c_str(),ItemDefine::g_szBalanceType, sizeof(ItemDefine::g_szBalanceType)/sizeof( char *) );

        for ( int i=0; i<ItemDefine::SItemSkill::EItemSkillConst_ActionSpeedMaxSize; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "SkillActPlaySpd%d", i+1 );
            SLK_GET_INT( pItemSkill->ustSkillActionSpeed[i], szTemp );
        }

        SLK_GET_INT   ( pItemSkill->ustCostHP,    "UseHp"  );
        SLK_GET_INT   ( pItemSkill->ustCostHPPer, "UseHp%" );
        SLK_GET_INT   ( pItemSkill->ustCostMP,    "UseMp"  );
        SLK_GET_INT   ( pItemSkill->ustCostMPPer, "UseMp%" );

        SLK_GET_STRING( strValue, "SkillType" );
        pItemSkill->stSkillType = HelperFunc::GetIDByConstString((char*)strValue.c_str(), ItemDefine::g_szSkillType,sizeof(ItemDefine::g_szSkillType)/sizeof( char* ) );

        SLK_GET_STRING( strValue, "GeneralType" );
        pItemSkill->stGeneralType = HelperFunc::GetIDByConstString((char*)strValue.c_str(), ItemDefine::g_szSkillGeneralType, sizeof(ItemDefine::g_szSkillGeneralType)/sizeof( char* ) );

        SLK_GET_STRING( strValue, "TargetType" );
        pItemSkill->stTargetType = HelperFunc::GetIDByConstString( (char*)strValue.c_str(), ItemDefine::g_szTargetString,sizeof(ItemDefine::g_szTargetString)/sizeof(char*) );

        SLK_GET_INT   ( pItemSkill->iDurationTime, "KeepTime" );
        SLK_GET_INT   ( pItemSkill->iDamageBalanceDelay, "internaltime" );
        SLK_GET_INT   ( pItemSkill->bMoveInterrupt, "IfMoveInterrupt" );

        SLK_GET_STRING( strValue, "centertargettype" );
        pItemSkill->stEffectCenterType = GetIDByConstString( strValue.c_str(),ItemDefine::g_szEffectCenter,sizeof(ItemDefine::g_szEffectCenter)/sizeof(char*) );

        SLK_GET_INT( pItemSkill->cLearnProfessionReq, "jobneed" );
        SLK_GET_INT( pItemSkill->stLearnLevelReq,     "lvneed" );            

        SLK_GET_FLOAT( pItemSkill->fRangeCanCast,        "maxcastdistance" );
        SLK_GET_FLOAT( pItemSkill->fRangeCanCastMin,     "mincastdistance" );
        SLK_GET_INT( pItemSkill->stDamageEffectDistance, "damdistance"     );

        SLK_GET_STRING( strValue, "CastType" );
        pItemSkill->shCastType = HelperFunc::GetIDByConstString( (char*)strValue.c_str(), ItemDefine::g_szCastType ,sizeof(ItemDefine::g_szCastType)/sizeof(char*) );

        SLK_GET_INT( pItemSkill->shMaxTargetNum, "aoenum" );

        SLK_GET_FLOAT( pItemSkill->fAOEradius,   "aoerange" );

        SLK_GET_INT( pItemSkill->bNeedWeapon,    "weaponneed" );

        SLK_GET_INT( pItemSkill->stUseItem,      "itemneed" );

        SLK_GET_INT( pItemSkill->bHoldSkill,      "ifkeepstatus" );

        SLK_GET_INT( pItemSkill->ustHoldEffect,       "keepeffect" );
        SLK_GET_INT( pItemSkill->dwSkillCoolDownTime, "colddowntime" );
        SLK_GET_INT( pItemSkill->nSkillCoolDownType,  "colddowntype" );

        SLK_GET_STRING( strValue, "casttarget" );
        pItemSkill->ustCastTarget = HelperFunc::GetIDByConstString( (char*)strValue.c_str(), ItemDefine::g_szSkillCastTarget,sizeof(ItemDefine::g_szSkillCastTarget)/sizeof( char* ) );

        // 分析 easyusedata;
        if( ItemDefine::target_friend == pItemSkill->stTargetType )
        { pItemSkill->easyusedata.bApplyToFriend = true; }

        // 普通攻击的 作用目标肯定是敌人
        if (IsNormalAttack( pItemSkill->ustItemID ) )
        { pItemSkill->easyusedata.bApplyToFriend = false; }

        // 判断是否是供给
        if (IsNormalAttack( pItemSkill->ustItemID ))
        { pItemSkill->easyusedata.bSkillWithDamage = true; }

        switch (pItemSkill->ustDamageBalanceType)
        {
        case ItemDefine::balancetype_damagephysicaldefend:      // 对物理防做伤害结算
        case ItemDefine::balancetype_damagemagicdefend:         // 对魔法防做伤害结算
            pItemSkill->easyusedata.bSkillWithDamage = true;
            break;
        case ItemDefine::balancetype_none:          // 没有任何结算
        case ItemDefine::balancetype_restorehpmp:   // 回HP结算
        case ItemDefine::balancetype_relive:        // 复活结算
        default:
            break;
        }

        for ( int i=0; i<ItemDefine::SItemSkill::EItemSkillConst_SkillNeedMaxSize; ++i)
        {
            sprintf_s( szTemp, sizeof(szTemp), "formerskill%d", i+1 );
            SLK_GET_INT( pItemSkill->stSkillNeed[i], szTemp );

            sprintf_s( szTemp, sizeof(szTemp), "formerskilllv%d", i+1 );
            SLK_GET_INT( pItemSkill->stSkillLevelNeed[i], szTemp );
        }

        SLK_GET_INT( pItemSkill->stMoneyNeed,           "needmoney" );

        SLK_GET_STRING( strValue, "weapontype" );
        pItemSkill->stWeaponNeed = GetIDByConstString( strValue.c_str(),ItemDefine::g_szWeaponType,sizeof(ItemDefine::g_szWeaponType)/sizeof(char*) );

        SLK_GET_INT( pItemSkill->stEnmity, "enmity" );

        SLK_GET_INT( pItemSkill->bContinueAtt, "ifkeepatk" );

        SLK_GET_INT( pItemSkill->stSkillHitRate, "skillhit" );

        SLK_GET_INT( pItemSkill->ustSkillMaxLvl, "maxskilllv" );

        SLK_GET_INT( pItemSkill->bNeedTestBackStrike, "ifbackstrike" );

        SLK_GET_FLOAT( pItemSkill->fBackStrikePlus, "backstrikeaffixed" );

        SLK_GET_INT( pItemSkill->bNeedTestAngle, "IfNeedAngle" );

        SLK_GET_INT( iValue, "Angle" );
        pItemSkill->fAngle = (float)iValue/180*D3DX_PI;

        SLK_GET_INT( pItemSkill->bEmissionSkill, "IfTrace" );

        SLK_GET_INT( pItemSkill->bAssaultSkill, "IfAssault" );

        SLK_GET_INT( pItemSkill->bHideSkill, "IfHide" );

        SLK_GET_INT( pItemSkill->bCancelHideSkill, "ReleaseHide" );

        SLK_GET_INT( pItemSkill->bAutoAttackTarget, "AutoAtk" );

        SLK_GET_INT( pItemSkill->nLearnNeedExp , "SkillExp" )

        SLK_GET_INT( pItemSkill->nSuckHpAtt ,    "AbsorbHp" );

        SLK_GET_INT( pItemSkill->nSuckMpAtt ,    "AbsorbMp" );

        SLK_GET_INT( pItemSkill->bIsRelive ,    "ifRevive" );

        SLK_GET_FLOAT( pItemSkill->fReliveHp ,    "ReviveHpPer" );
        SLK_GET_FLOAT( pItemSkill->fReliveMp ,    "ReviveMpPer" );

        SLK_GET_INT( pItemSkill->bSummonSkill,     "IfSummon" );

        SLK_GET_INT( pItemSkill->nSummonMonsterId, "SunmmonMonsterId" );

        SLK_GET_STRING( strValue, "PassiveSkillTarget");
        pItemSkill->shPassiveSkillTarget = HelperFunc::GetIDByConstString( (char*)strValue.c_str(),
			ItemDefine::g_szPassiveSkillTargetString, sizeof(ItemDefine::g_szPassiveSkillTargetString)/sizeof(char*));

        SLK_GET_INT( pItemSkill->stBackStrikeMeStatus      , "AddBackStrikeStatus(me)"       );
        SLK_GET_INT( pItemSkill->stBackStrikeMeStatusLevel , "AddBackStrikeStatusLv(me)"     );
        SLK_GET_INT( pItemSkill->stBackStrikeDstStatus     , "AddBackStrikeStatus(target)"   );
        SLK_GET_INT( pItemSkill->stBackStrikeDstStatusLevel, "AddBackStrikeStatusLv(target)" );

        SLK_GET_FLOAT( pItemSkill->fBackStrikeStatusRate, "AddBackStrikeStatusRate" );

        SLK_GET_INT( pItemSkill->cHpLimitType, "HpLimitType" );

        SLK_GET_FLOAT( pItemSkill->fHpPerLimit, "HpPerLimit");

        SLK_GET_INT( pItemSkill->ustInstantMovingType, "InstantMovingType" );
        SLK_GET_INT( pItemSkill->bIsAfterIllusion,     "IfAfterIllusion" );

        SLK_GET_INT( pItemSkill->nInterruptIntonatingAbility, "InterruptIntonatingAbility" );

        SLK_GET_INT( pItemSkill->bEnterFightStatus, "IfEnterFightStatus" );

        SLK_GET_INT( pItemSkill->bIsCatchNurturePet, "IsCatchNurturePet" );
        SLK_GET_INT( pItemSkill->iskillpet,          "IsKillPet" );
        SLK_GET_INT( pItemSkill->ispettouseskill,    "IsPetUseSkill" );
        SLK_GET_INT( pItemSkill->ustPetSkillID,      "PetUseSkillID" );
        SLK_GET_INT( pItemSkill->ustPetSkillLevel,   "PetUseSkillLevel");
        SLK_GET_INT( pItemSkill->needpet,            "NeedPetToUseSkill");
        SLK_GET_INT( pItemSkill->iSkillActionFlags,  "SkillActionFlags");
        SLK_GET_INT( pItemSkill->usConsumeFightPower,  "ConsumeFightPower");
        SLK_GET_INT( pItemSkill->usIncreaseFightPower, "IncreaseFightPower");

        SLK_GET_STRING( strValue, "SkillDescription");
        pItemSkill->dwSkillDescription = AllocStringCopy( strValue.c_str() );
		SLK_GET_INT( pItemSkill->nAddonDesc1, "AddonDesc1");
		SLK_GET_INT( pItemSkill->nAddonDesc2, "AddonDesc2");
		SLK_GET_INT( pItemSkill->nXinFaID, "XinFaID");
		SLK_GET_INT( pItemSkill->nLearnNeedXinFaLevel, "LearnNeedXinFaLevel");

	
        SLK_GET_INT( pItemSkill->dwCommonCoolDownTime, "CommonCoolDownTime");

        SLK_GET_FLOAT( pItemSkill->fDamageRate, "DamageRate");

        SLK_GET_INT( pItemSkill->dwDamageDelayBalanceTime, "DamageDelayBalanceTime");


        SLK_GET_INT( pItemSkill->cFightStateCastType,        "FightStateCastType");
        SLK_GET_INT( pItemSkill->bMustInBackUse,             "MustInBackUse");
        SLK_GET_INT( pItemSkill->usSpecialTargetType,        "SpecialTargetType");

        SLK_GET_FLOAT( pItemSkill->fFPDamageRatio,           "FPDamageRatio");

        SLK_GET_INT( pItemSkill->bNextNotIntonate,           "IfNextNotIntonate");
        SLK_GET_INT( pItemSkill->nNextNotIntonateNum,        "NextNotIntonateNum");
        SLK_GET_INT( pItemSkill->sSkillCategory,             "SkillCategory");
        SLK_GET_INT( pItemSkill->bScriptRunSkill,            "ScriptRunSkill");

        SLK_GET_INT( pItemSkill->iMountSkillProfessionType,  "ProfessionMountSkill");

        SLK_GET_INT( pItemSkill->usConsumeVigor,             "ConsumeVigor");
        SLK_GET_INT( pItemSkill->specialSkillType,           "SpecialSkillType");

        SLK_GET_INT( pItemSkill->additionalDamageType,       "AdditionalDamageType"); 
        SLK_GET_INT( pItemSkill->additionalDamageStatus,     "AdditionalDamageStatus"); 
        SLK_GET_INT( pItemSkill->additionalDamagePer,        "AdditionalDamagePer");

        SLK_GET_INT( pItemSkill->releaseLapoverStatus,       "ReleaseLapoverStatus"); 

        SLK_GET_INT( pItemSkill->breakStrike,                "BreakStrike"      ); 
        SLK_GET_INT( pItemSkill->stabStrike,                 "StabStrike"       ); 
        SLK_GET_INT( pItemSkill->elementStrike,              "ElementStrike"    ); 
        SLK_GET_INT( pItemSkill->toxinStrike,                "ToxinStrike"      ); 
        SLK_GET_INT( pItemSkill->spiritStrike,               "SpiritStrike"     ); 

        SLK_GET_STRING( strValue, "AdditionalDamageProfession" );
        if ( strValue.empty()   || strValue == "" || strValue == "NULL" || strValue == "null")
            pItemSkill->additionalDamageProfession = -1;
        else
            pItemSkill->additionalDamageProfession = HelperFunc::GetIDByConstString( (char *) strValue.c_str(), 
			ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );

        SLK_GET_INT( pItemSkill->addtionalCritical,           "AddtionalCritical");

        SLK_GET_INT( pItemSkill->additionalPhyAttack,         "AdditionalPhyAttack");
        SLK_GET_INT( pItemSkill->additionalMagAttack,         "AdditionalMagAttack");

        for ( int i=0; i< ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize; ++i )
        {
            sprintf_s( szTemp, sizeof(szTemp), "DispelNegativeType%d", i+1 );
            SLK_GET_INT( pItemSkill->dispelNegativeType[i], szTemp );
        }

        SLK_GET_INT( pItemSkill->mountSkillCategory,           "MountSkillCategory"     );
        SLK_GET_INT( pItemSkill->mountAptitudeCategory,        "MountAptitudeCategory"  );
        SLK_GET_INT( pItemSkill->mountAptitudeModulus,         "MountAptitudeModulus"   );

        SLK_GET_INT( pItemSkill->petSkillCategory,             "PetSkillCategory"       );
        SLK_GET_INT( pItemSkill->petAutoSkillType,             "PetAutoSkillType"       );
        SLK_GET_INT( pItemSkill->petAutoSkillTriggerRate,      "PetAutoSkillTriggerRate");

        SLK_GET_INT( pItemSkill->bGiddyDischarge,              "IfGiddyDischarge"       );

		SLK_GET_STRING( strValue, "RideCastAct"   );
		pItemSkill->dwRideIntonateAction = AllocStringCopy( strValue.c_str() );

        // 技能职业需求
        for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
        {
            pItemSkill->arrayProfessionReq[ iLoop ] = false;
        }

        SLK_GET_STRING( strValue, "UseSkillProfession");
        if ( strValue.empty())
        {
            for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
            {    
                pItemSkill->arrayProfessionReq[ iLoop ] = true;
            }
        }
        else
        {  
            //适用多个职业
            char *szSpn = ",";
            char *szStr;
            int iIndex;
            szStr = strtok( const_cast<char*>(strValue.c_str()),szSpn );
            while( szStr )
            {

                iIndex = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                if( iIndex >= 0 && iIndex < EArmType_MaxSize )
                {
                    pItemSkill->arrayProfessionReq[ iIndex ] = true;
                }
                szStr = strtok( NULL,szSpn );
            }
        }

        //建立一个技能物品ID到技能序号的 转换
        m_mapSkillNO.insert( mapSkillNO::value_type( pItemSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
        m_vecSkill.push_back( pItemSkill->ustItemID );

        //建立一个技能数组(只限法术)
        if(pItemSkill->ustItemID>=ItemDefine::StartID_Skill)
        {
            int index = pItemSkill->ustItemID-ItemDefine::StartID_Skill;

            m_SkillArray[index][pItemSkill->ustLevel] = *pItemSkill;

            if(pItemSkill->ustLevel==1)
            {
                m_SkillArray[index][ 0 ] = *pItemSkill;
            }
        }

        m_vecSkillItem.push_back(pItemSkill);
    }

    return true;
}

// bool CItemDetailConfig::LoadEffectFile(int skillID_, int level_)
// {
// 	SItemSkill *pSkill = GetSkillByID(skillID_, level_);
// 	if(NULL == pSkill)
// 		return false;
// 
// 	return true;
// }

bool CItemDetailConfig::LoadSkillItem(const char *fileName_, int mode_/* = ConfigLoadMode_Normal*/)
{
	//ASSERT(fileName_ != NULL);
	if(NULL == fileName_)
		return false;

	MeXmlDocument MeXmlSkillDoc ;
	if(!MeXmlSkillDoc.LoadFile(fileName_))
	{ 
		return FALSE; 
	}

	// 	if (ConfigLoadMode_Reload  == mode_)
	// 	{
	m_vecSkillItem.clear();
	// 	}

	return LoadSkillItem(&MeXmlSkillDoc, mode_);
}

bool CItemDetailConfig::LoadSkillItem      ( MeXmlDocument *pXmlDoc, int mode )//技能
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

        MeXmlElement *pSkillElement = pItemElement->FirstChildElement("Skill");
        if (pSkillElement == NULL)
        { continue; }

        while(pSkillElement != NULL)
        {
            ItemDefine::SItemSkill *pSkill = NULL;

            if ( mode != ConfigLoadMode_Normal)
            {
                int nSkillLevel = 0;
                pSkillElement->Attribute("SkillLevel", &nSkillLevel);
                pSkill = GetSkillByID(itemCommon.ustItemID , nSkillLevel);
            }

            if ( NULL == pSkill )
            { pSkill = (ItemDefine::SItemSkill*)AllocItem( 0, sizeof( ItemDefine::SItemSkill ) ); }

            if( !pSkill )
            {
                OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
                GetErrorLog()->logString( "Error:内存分配出错!" );
                return false;    
            }

            CopyCommon( pSkill, itemCommon );

            //技能属性

            Common::_tstring strTemp;
            strTemp.fromUTF8( pSkillElement->Attribute("SkillName") );
            pSkill->dwSkillNameAddr = AllocStringCopy( strTemp.c_str() );

			strTemp.fromUTF8( pSkillElement->Attribute("RideAction"));
			pSkill->dwRideAction = AllocStringCopy( strTemp.c_str() );

            pSkillElement->Attribute("GroupID", &iValue);
            pSkill->groupId = iValue;

            pSkillElement->Attribute("GroupLevel", &iValue);
            pSkill->groupLevel = iValue;

            pSkillElement->Attribute("SkillLevel", &iValue);
            pSkill->ustLevel = iValue;//技能等级

            Common::_tstring strSkillDescription;
            strSkillDescription.fromUTF8( pSkillElement->Attribute("Description") );
            pSkill->dwSkillDescription = AllocStringCopy( strSkillDescription.c_str() );//技能描述

			pSkillElement->Attribute("AddonDesc1", &iValue);
			pSkill->nAddonDesc1 = iValue;
			
			pSkillElement->Attribute("AddonDesc2", &iValue);
			pSkill->nAddonDesc2 = iValue;

			pSkillElement->Attribute("XinFaID", &iValue);
			pSkill->nXinFaID = iValue;

			pSkillElement->Attribute("LearnNeedXinFaLevel", &iValue);
			pSkill->nLearnNeedXinFaLevel = iValue;			

            pSkillElement->Attribute("ActionFlags", &iValue);
            pSkill->iSkillActionFlags = iValue;

            pSkillElement->Attribute("MaxSkillLevel", &iValue);
            pSkill->ustSkillMaxLvl = iValue;

            //特效属性
            MeXmlElement *pSkillEffect = pSkillElement->FirstChildElement("Effect");
            if (pSkillEffect == NULL)
            { continue; }

            Common::_tstring strCastEffectMale;
            strCastEffectMale.fromUTF8( pSkillEffect->Attribute("CastEffectMale") );
            pSkill->dwIntonateEffectAddr = AllocStringCopy( strCastEffectMale.c_str() );

            Common::_tstring strReleaseEffectMale;
            strReleaseEffectMale.fromUTF8( pSkillEffect->Attribute("ReleaseEffectMale") );
            pSkill->dwAttackerEffectAddr = AllocStringCopy( strReleaseEffectMale.c_str() );

            Common::_tstring strTraceEffectMale;
            strTraceEffectMale.fromUTF8( pSkillEffect->Attribute("TraceEffectMale") );
            pSkill->dwSkillEffectAddr = AllocStringCopy( strTraceEffectMale.c_str() );

            Common::_tstring strHitEffectMale;
            strHitEffectMale.fromUTF8( pSkillEffect->Attribute("HitEffectMale") );
            pSkill->dwTargetEffectAddr = AllocStringCopy( strHitEffectMale.c_str() );

            Common::_tstring strCastEffectFemale;
            strCastEffectFemale.fromUTF8( pSkillEffect->Attribute("CastEffectFemale") );
            pSkill->dwIntonateEffectAddr2 = AllocStringCopy( strCastEffectFemale.c_str() );

            Common::_tstring strReleaseEffectFemale;
            strReleaseEffectFemale.fromUTF8( pSkillEffect->Attribute("ReleaseEffectFemale") );
            pSkill->dwAttackerEffectAddr2 = AllocStringCopy( strReleaseEffectFemale.c_str() );

            Common::_tstring strTraceEffectFemale;
            strTraceEffectFemale.fromUTF8( pSkillEffect->Attribute("TraceEffectFemale") );
            pSkill->dwSkillEffectAddr2 = AllocStringCopy( strTraceEffectFemale.c_str() );

            Common::_tstring strHitEffectFemale;
            strHitEffectFemale.fromUTF8( pSkillEffect->Attribute("HitEffectFemale") );
            pSkill->dwTargetEffectAddr2 = AllocStringCopy( strHitEffectFemale.c_str() );

            pSkillEffect->Attribute("KeepEffect", &iValue);
            pSkill->ustHoldEffect = iValue;

            //阈值属性
            MeXmlElement *pSkillThreshold = pSkillElement->FirstChildElement("Threshold");
            if (pSkillThreshold == NULL)
            { continue; }

            pSkillThreshold->Attribute("HpPerLimit", &dValue);
            pSkill->fHpPerLimit = dValue;

            pSkillThreshold->Attribute("ConsumeFightPower", &iValue);
            pSkill->usConsumeFightPower = iValue;

            pSkillThreshold->Attribute("ConsumeVigor", &iValue);
            pSkill->usConsumeVigor = iValue;

            pSkillThreshold->Attribute("BackStrikeAffixed", &dValue);
            pSkill->fBackStrikePlus = dValue;

            pSkillThreshold->Attribute("ColdDownTime", &iValue);
            pSkill->dwSkillCoolDownTime = iValue;

            pSkillThreshold->Attribute("CommonCoolDownTime", &dValue);
            pSkill->dwCommonCoolDownTime = dValue;

            pSkillThreshold->Attribute("FreezeTime", &iValue);
            pSkill->ustHoldTime = iValue;

            pSkillThreshold->Attribute("CastSpeed", &iValue);
            pSkill->ustPrepTime = iValue;

            pSkillThreshold->Attribute("IfShowIntonateBar", &iValue);
            pSkill->bShowIntonateBar = ( iValue != 0 ? true : false );

            pSkillThreshold->Attribute("AOENum", &iValue);
            pSkill->shMaxTargetNum = iValue;

            pSkillThreshold->Attribute("InternalTime", &iValue);
            pSkill->iDamageBalanceDelay = iValue;

            pSkillThreshold->Attribute("DamageDelayBalanceTime", &iValue);
            pSkill->dwDamageDelayBalanceTime = iValue;

            pSkillThreshold->Attribute("Enmity", &iValue);
            pSkill->stEnmity = iValue;

            //状态属性
            MeXmlElement *pSkillStatus = pSkillElement->FirstChildElement("Status");
            if (pSkillStatus == NULL)
            { continue; }

            pSkillStatus->Attribute("AddStatusMe1", &iValue);
            pSkill->ustMeAddStatusID[0] = iValue; 

            pSkillStatus->Attribute("AddStatusLvMe1", &iValue);
            pSkill->ustMeAddStatusLevel[0] = iValue; 

            pSkillStatus->Attribute("AddStatusMe2", &iValue);
            pSkill->ustMeAddStatusID[1] = iValue; 

            pSkillStatus->Attribute("AddStatusLvMe2", &iValue);
            pSkill->ustMeAddStatusLevel[1] = iValue; 

            pSkillStatus->Attribute("AddStatusTarget1", &iValue);
            pSkill->ustDstAddStatusID[0] = iValue; 

            pSkillStatus->Attribute("AddStatusLvTarget1", &iValue);
            pSkill->ustDstAddStatusLevel[0] = iValue; 

            pSkillStatus->Attribute("AddStatusTarget2", &iValue);
            pSkill->ustDstAddStatusID[1] = iValue; 

            pSkillStatus->Attribute("AddStatusLvTarget2", &iValue);
            pSkill->ustDstAddStatusLevel[1] = iValue; 

            pSkillStatus->Attribute("StatusHitRate", &iValue);
            pSkill->ustStatusHitRate = iValue; 

            pSkillStatus->Attribute("StatusDispel", &iValue);
            pSkill->dwSubComboStatus = iValue; 

            for(int i=0; i < ItemDefine::CLEAR_MAX_STATUS; ++i)
            {
                char szTmp[21] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "StatusDispel%d", i);
                pSkillStatus->Attribute(szTmp, &iValue);
                pSkill->dwClearStatus[i] = iValue; 
            }

            for ( int i=0; i< ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize; ++i )
            {
                char szTemp[64] = {0};
                sprintf_s( szTemp, sizeof(szTemp), "DispelNegativeType%d", i+1 );

                pSkillStatus->Attribute(szTemp, &iValue);
                pSkill->dispelNegativeType[i] = iValue; 
            }

            pSkillStatus->Attribute("AddBackStrikeStatusMe", &iValue);
            pSkill->stBackStrikeMeStatus = iValue; 

            pSkillStatus->Attribute("AddBackStrikeStatusLvMe", &iValue);
            pSkill->stBackStrikeMeStatusLevel = iValue; 

            pSkillStatus->Attribute("AddBackStrikeStatusTarget", &iValue);
            pSkill->stBackStrikeDstStatus = iValue; 

            pSkillStatus->Attribute("AddBackStrikeStatusLvTarget", &iValue);
            pSkill->stBackStrikeDstStatusLevel = iValue; 

            //消耗恢复相关
            MeXmlElement *pSkillUseRes= pSkillElement->FirstChildElement("UseRes");
            if (pSkillUseRes == NULL)
            { continue; }

            pSkillUseRes->Attribute("UseHp", &iValue);
            pSkill->ustCostHP = iValue;

            pSkillUseRes->Attribute("UseHpPer", &iValue);
            pSkill->ustCostHPPer = iValue;

            pSkillUseRes->Attribute("UseMp", &iValue);
            pSkill->ustCostMP = iValue;

            pSkillUseRes->Attribute("UseMpPer", &iValue);
            pSkill->ustCostMPPer = iValue;

            pSkillUseRes->Attribute("AbsorbHp", &iValue);
            pSkill->nSuckHpAtt = iValue;

            pSkillUseRes->Attribute("AbsortMp", &iValue);
            pSkill->nSuckMpAtt = iValue;

            pSkillUseRes->Attribute("ReviveHpPer", &dValue);
            pSkill->fReliveHp = dValue;

            pSkillUseRes->Attribute("ReviveMpPer", &dValue);
            pSkill->fReliveMp = dValue;

            pSkillUseRes->Attribute("IncreaseFightPower", &iValue);
            pSkill->usIncreaseFightPower = iValue;

            //需求属性
            MeXmlElement *pSkillRequirement = pSkillElement->FirstChildElement("Requirement");
            if (pSkillRequirement == NULL)
            { continue; }

            pSkillRequirement->Attribute("JobNeed", &iValue);
            pSkill->cLearnProfessionReq = iValue;//学习职业要求

            pSkillRequirement->Attribute("LevelNeed", &iValue);
            pSkill->stLearnLevelReq = iValue;//学习等级要求

            pSkillRequirement->Attribute("SkillExp", &iValue);
            pSkill->nLearnNeedExp = iValue;

            pSkillRequirement->Attribute("WeaponNeed", &iValue);
            pSkill->bNeedWeapon = iValue > 0 ? true : false;

            pSkillRequirement->Attribute("ItemNeed", &iValue);
            pSkill->stUseItem = iValue;

            Common::_tstring strWeaponType;
            strWeaponType.fromUTF8( pSkillRequirement->Attribute("WeaponType") );
            if (strWeaponType == "NULL")
            {
                pSkill->stWeaponNeed = -1;
            }
            else
            {
                pSkill->stWeaponNeed = GetIDByConstString( strWeaponType.c_str(),ItemDefine::g_szWeaponType,sizeof(ItemDefine::g_szWeaponType)/sizeof(char*) );//武器类型要求
            }

            pSkillRequirement->Attribute("NeedMoney", &iValue);
            pSkill->stMoneyNeed = iValue;

            for (int i = 0; i < 3; ++i)
            {
                char szTmp[21] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "FormerSkill%d", i+1);
                pSkillRequirement->Attribute(szTmp, &iValue);
                pSkill->stSkillNeed[i] = iValue;//学习牵制技能条件1-3

                sprintf_s(szTmp, sizeof(szTmp) -1, "FormerSkillLevel%d", i+1);
                pSkillRequirement->Attribute(szTmp, &iValue);
                pSkill->stSkillLevelNeed[i] = iValue;//学习牵制技能等级1-3
            }


            //判断属性
            MeXmlElement *pSkillWhether = pSkillElement->FirstChildElement("Whether");  
            if (pSkillWhether == NULL)
            { continue; }

            pSkillWhether->Attribute("IfKeepAtk", &iValue);
            pSkill->bContinueAtt = iValue > 0 ? true : false;

            pSkillWhether->Attribute("IfRevive", &iValue);
            pSkill->bIsRelive = iValue > 0 ? true : false;

            pSkillWhether->Attribute("IfBackStrike", &iValue);
            pSkill->bNeedTestBackStrike = iValue;

            pSkillWhether->Attribute("IfNeedAngle", &iValue);
            pSkill->bNeedTestAngle = iValue;

            pSkillWhether->Attribute("IfTrace", &iValue);
            pSkill->bEmissionSkill = iValue;

            pSkillWhether->Attribute("IfAssault", &iValue);
            pSkill->bAssaultSkill = iValue;

            pSkillWhether->Attribute("IfHide", &iValue);
            pSkill->bHideSkill = iValue;

            pSkillWhether->Attribute("IfSummon", &iValue);
            pSkill->bSummonSkill = iValue; 

            pSkillWhether->Attribute("IfKeepStatus", &iValue);
            pSkill->bHoldSkill = iValue;

            pSkillWhether->Attribute("IfAfterIllusion", &iValue);
            pSkill->bIsAfterIllusion = iValue;

            pSkillWhether->Attribute("IfEnterFightStatus", &iValue);
            pSkill->bEnterFightStatus = iValue;

            pSkillWhether->Attribute("IsCatchNurturePet", &iValue);
            pSkill->bIsCatchNurturePet = iValue;

            pSkillWhether->Attribute("IsKillPet", &iValue);
            pSkill->iskillpet = iValue;

            pSkillWhether->Attribute("IsPetUseSkill", &iValue);
            pSkill->ispettouseskill = iValue;

            pSkillWhether->Attribute("IfNextNotIntonate", &iValue);
            pSkill->bNextNotIntonate = iValue;

            pSkillWhether->Attribute("IfGiddyDischarge", &iValue);
            pSkill->bGiddyDischarge = iValue;

            pSkillWhether->Attribute("IfMoveInterrupt", &iValue);
            pSkill->bMoveInterrupt = iValue;

            //概率属性
            MeXmlElement *pSkillRate = pSkillElement->FirstChildElement("Rate"); 
            if (pSkillRate == NULL)
            { continue; }

            pSkillRate->Attribute("ActionRatio", &dValue);
            pSkill->actionRatio = dValue;

            pSkillRate->Attribute("NormalAttackRatio", &iValue);
            pSkill->normalAttackRatio = iValue;

            pSkillRate->Attribute("SkillHit", &iValue);
            pSkill->stSkillHitRate = iValue;

            pSkillRate->Attribute("DamageRate", &dValue);
            pSkill->fDamageRate = dValue;

            pSkillRate->Attribute("FPDamageRatio", &dValue);
            pSkill->fFPDamageRatio = dValue;

            pSkillRate->Attribute("AddBackStrikeStatusRate", &dValue);
            pSkill->fBackStrikeStatusRate = dValue;

            pSkillRate->Attribute("PetAutoSkillTriggerRate", &dValue);
            pSkill->petAutoSkillTriggerRate = dValue;

            //类型属性
            MeXmlElement *pSkillType = pSkillElement->FirstChildElement("SkillType"); 
            if (pSkillType == NULL)
            { continue; }

            Common::_tstring strSkillType;
            strSkillType.fromUTF8( pSkillType->Attribute("SkillType") );
            pSkill->stSkillType = HelperFunc::GetIDByConstString( (char*)strSkillType.c_str(),
                ItemDefine::g_szSkillType,sizeof(ItemDefine::g_szSkillType)/sizeof( char* ) ); 

            Common::_tstring strSkillGeneralType;
            strSkillGeneralType.fromUTF8( pSkillType->Attribute("GeneralType") );
            pSkill->stGeneralType = HelperFunc::GetIDByConstString((char*)strSkillGeneralType.c_str(),
                ItemDefine::g_szSkillGeneralType, sizeof(ItemDefine::g_szSkillGeneralType)/sizeof( char* ) ); 

            Common::_tstring strTargetType;
            strTargetType.fromUTF8( pSkillType->Attribute("TargetType") );
            pSkill->stTargetType = HelperFunc::GetIDByConstString( (char*)strTargetType.c_str(),
                ItemDefine::g_szTargetString,sizeof(ItemDefine::g_szTargetString)/sizeof(char*) ); 

            Common::_tstring strCenterTargetType;
            strCenterTargetType.fromUTF8( pSkillType->Attribute("CenterTargetType") );
            pSkill->stEffectCenterType = HelperFunc::GetIDByConstString( (char*)strCenterTargetType.c_str(),
                ItemDefine::g_szEffectCenter,sizeof(ItemDefine::g_szEffectCenter)/sizeof(char*) ); 

            pSkillType->Attribute("ColdDownType", &iValue);
            pSkill->nSkillCoolDownType = iValue; 

            Common::_tstring strCastTarget;
            strCastTarget.fromUTF8( pSkillType->Attribute("CastTarget") );
            pSkill->ustCastTarget = HelperFunc::GetIDByConstString( (char*)strCastTarget.c_str(),
                ItemDefine::g_szSkillCastTarget,sizeof(ItemDefine::g_szSkillCastTarget)/sizeof( char* ) ); 

            Common::_tstring strCastType;
            strCastType.fromUTF8( pSkillType->Attribute("CastType") );
            pSkill->shCastType = HelperFunc::GetIDByConstString( (char*)strCastType.c_str(),
                ItemDefine::g_szCastType ,sizeof(ItemDefine::g_szCastType)/sizeof(char*) ); 

            pSkillRate->Attribute("TriggerType", &iValue);
            pSkill->triggerType = iValue;

            pSkillType->Attribute("FightStateCastType", &iValue);
            pSkill->cFightStateCastType = iValue; 

            pSkillType->Attribute("HpLimitType", &iValue);
            pSkill->cHpLimitType = iValue; 

            pSkillType->Attribute("InstantMovingType", &iValue);
            pSkill->ustInstantMovingType = iValue; 

            pSkillType->Attribute("SkillCategory", &iValue);
            pSkill->sSkillCategory = iValue; 

            pSkillType->Attribute("SpecialTargetType", &iValue);
            pSkill->usSpecialTargetType = iValue; 

            pSkillType->Attribute("SpecialSkillType", &iValue);
            pSkill->specialSkillType = iValue; 

            pSkillType->Attribute("MountSkillCategory", &iValue);
            pSkill->mountSkillCategory  = iValue; 

            pSkillType->Attribute("MountAptitudeCategory", &iValue);
            pSkill->mountAptitudeCategory  = iValue; 

            pSkillType->Attribute("PetSkillCategory", &iValue);
            pSkill->petSkillCategory  = iValue; 

            pSkillType->Attribute("PetAutoSkillType", &iValue);
            pSkill->petAutoSkillType  = iValue; 

            //方位属性
            MeXmlElement *pSkillPosition = pSkillElement->FirstChildElement("Position");  
            if (pSkillPosition == NULL)
            { continue; }

            pSkillPosition->Attribute("MaxcastDistance", &dValue);
            pSkill->fRangeCanCast = dValue; 

            pSkillPosition->Attribute("MincastDistance", &dValue);
            pSkill->fRangeCanCastMin = dValue; 

            pSkillPosition->Attribute("DamDistance", &iValue);
            pSkill->stDamageEffectDistance = iValue; 

            pSkillPosition->Attribute("AOERange", &dValue);
            pSkill->fAOEradius = dValue;//AOE半径

            pSkillPosition->Attribute("Angle", &dValue);
            pSkill->fAngle = dValue;

            pSkillPosition->Attribute("MustInBackUse", &iValue);
            pSkill->bMustInBackUse = iValue;

            //攻击属性
            MeXmlElement *pSkillAttack =  pSkillElement->FirstChildElement("Attack");  
            if (pSkillAttack == NULL)
            { continue; }

            pSkillAttack->Attribute("HurtAct", &iValue);
            pSkill->ustIDTargetHitAction = iValue;

            pSkillAttack->Attribute("KeepTime", &iValue);
            pSkill->iDurationTime = iValue;

            pSkillAttack->Attribute("AutoAtk", &iValue);
            pSkill->bAutoAttackTarget = iValue;

            pSkillAttack->Attribute("AdditionalDamageType", &iValue);
            pSkill->additionalDamageType = iValue; 

            pSkillAttack->Attribute("AdditionalDamageStatus", &iValue);
            pSkill->additionalDamageStatus = iValue; 

            Common::_tstring strValue;
            strValue.fromUTF8(pSkillAttack->Attribute("AdditionalDamageProfession"));

            if ( strValue.empty()   || strValue == "" || strValue == "NULL" || strValue == "Null"  || strValue == "null")
                pSkill->additionalDamageProfession = -1;
            else
                pSkill->additionalDamageProfession = HelperFunc::GetIDByConstString((char *) strValue.c_str(), 
				ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );

            pSkillAttack->Attribute("AdditionalDamagePer", &iValue);
            pSkill->additionalDamagePer = iValue; 

            pSkillAttack->Attribute("AddtionalCritical", &iValue);
            pSkill->addtionalCritical = iValue; 

            pSkillAttack->Attribute("AdditionalPhyAttack", &iValue);
            pSkill->additionalPhyAttack = iValue; 

            pSkillAttack->Attribute("AdditionalMagAttack", &iValue);
            pSkill->additionalMagAttack = iValue; 

            pSkillAttack->Attribute("MountAptitudeModulus", &iValue);
            pSkill->mountAptitudeModulus  = iValue; 

            pSkillAttack->Attribute("ReleaseLapoverStatus", &iValue);
            pSkill->releaseLapoverStatus  = iValue; 

            pSkillAttack->Attribute("BreakStrike", &iValue);
            pSkill->breakStrike  = iValue; 

            pSkillAttack->Attribute("StabStrike", &iValue);
            pSkill->stabStrike  = iValue; 

            pSkillAttack->Attribute("ElementStrike", &iValue);
            pSkill->elementStrike  = iValue; 

            pSkillAttack->Attribute("ToxinStrike", &iValue);
            pSkill->toxinStrike  = iValue; 

            pSkillAttack->Attribute("SpiritStrike", &iValue);
            pSkill->spiritStrike  = iValue; 


            //宠物属性
            MeXmlElement *pSkillPet = pSkillElement->FirstChildElement("Pet");  
            if (pSkillPet == NULL)
            { continue; }

            pSkillPet->Attribute("SunmmonMonsterId", &iValue);
            pSkill->nSummonMonsterId = iValue; 

            pSkillPet->Attribute("PetUseSkillID", &iValue);
            pSkill->ustPetSkillID = iValue;

            pSkillPet->Attribute("PetUseSkillLevel", &iValue);
            pSkill->ustPetSkillLevel = iValue; 

            pSkillPet->Attribute("NeedPetToUseSkill", &iValue);
            pSkill->needpet = iValue; 

            //动作属性
            MeXmlElement *pSkillAction = pSkillElement->FirstChildElement("Action");
            if (pSkillAction == NULL)
            { continue; }

			Common::_tstring strSkillAct;
			
			strSkillAct.fromUTF8( pSkillAction->Attribute("RideAction") );
			pSkill->dwRideAction = AllocStringCopy( strSkillAct.c_str() );
            
            for (int i = 0; i < 10;++i )
            {
                strSkillAct.clear();
                char szTmp[65] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "SkillAct%d", i+1 );

                strSkillAct.fromUTF8( pSkillAction->Attribute(szTmp) );
                pSkill->dwSkillAction[i] = AllocStringCopy( strSkillAct.c_str() );
            }

            for (int i = 0; i< 20 ; ++i)
            {
                char szTmp[21] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "SkillActPlaySpd%d", i+1);
                pSkillAction->Attribute(szTmp, &iValue);
                pSkill->ustSkillActionSpeed[i] = iValue;//技能动作播放速度1-20
            }

            //其他属性
            MeXmlElement *pSkillOther = pSkillElement->FirstChildElement("Other"); 
            if (pSkillOther == NULL)
            { continue; }

            Common::_tstring strBalanceType;
            strBalanceType.fromUTF8(pSkillOther->Attribute("UseFormula"));
            pSkill->ustDamageBalanceType = HelperFunc::GetIDByConstString( (char*)strBalanceType.c_str(),
                ItemDefine::g_szBalanceType, sizeof(ItemDefine::g_szBalanceType)/sizeof( char *) ); 

            Common::_tstring strCastAct;
            strCastAct.fromUTF8( pSkillOther->Attribute("CastAct") );
            pSkill->dwIntonateAction = AllocStringCopy( strCastAct.c_str() );

			Common::_tstring strRideCastAct;
			strRideCastAct.fromUTF8( pSkillOther->Attribute("RideCastAct") );
			pSkill->dwRideIntonateAction = AllocStringCopy( strRideCastAct.c_str() );

            pSkillOther->Attribute("InterruptIntonatingAbility", &iValue);
            pSkill->nInterruptIntonatingAbility = iValue;

            pSkillOther->Attribute("ReleaseHide", &iValue);
            pSkill->bCancelHideSkill = iValue;

            Common::_tstring strPassiveSkillTarget;
            strPassiveSkillTarget.fromUTF8( pSkillOther->Attribute("PassiveSkillTarget") );
            pSkill->shPassiveSkillTarget = HelperFunc::GetIDByConstString( (char*)strPassiveSkillTarget.c_str(), 
                ItemDefine::g_szPassiveSkillTargetString, sizeof(ItemDefine::g_szPassiveSkillTargetString)/sizeof(char*));

            pSkillOther->Attribute("ScriptRunSkill", &iValue);
            pSkill->bScriptRunSkill = iValue; 

            pSkillOther->Attribute("ProfessionMountSkill", &iValue);
            pSkill->iMountSkillProfessionType = iValue; 

            pSkillOther->Attribute("NextNotIntonateNum", &iValue);
            pSkill->nNextNotIntonateNum = iValue; 

            for(int iLoop = 0 ; iLoop < EArmType_MaxSize ; ++iLoop )
            {
                pSkill->arrayProfessionReq[ iLoop ] = false;
            }

            Common::_tstring strProfessionReq;
            strProfessionReq.fromUTF8( pSkillOther->Attribute("UseSkillProfession") );
            if ( strProfessionReq.empty())
            {
                for(int iLoop = 0 ; iLoop < EArmType_MaxSize; iLoop ++ )
                {    
                    pSkill->arrayProfessionReq[ iLoop ] = true;
                }
            }
            else
            {  
                //适用多个职业
                char *szSpn = ",";
                char *szStr;
                int iIndex;
                szStr = strtok( const_cast<char*>(strProfessionReq.c_str()),szSpn );
                while( szStr )
                {

                    iIndex = HelperFunc::GetIDByConstString( szStr, ItemDefine::g_szProfessionType, sizeof( ItemDefine::g_szProfessionType )/sizeof(char*) );
                    if( iIndex >= 0 && iIndex < EArmType_MaxSize )
                    {
                        pSkill->arrayProfessionReq[ iIndex ] = true;
                    }
                    szStr = strtok( NULL,szSpn );
                }
            }

            // 分析 easyusedata;
            if( ItemDefine::target_friend == pSkill->stTargetType )
            { pSkill->easyusedata.bApplyToFriend = true; }

            // 普通攻击的 作用目标肯定是敌人
            if (IsNormalAttack( pSkill->ustItemID ) )
            { pSkill->easyusedata.bApplyToFriend = false; }

            // 判断是否是供给
            if (IsNormalAttack( pSkill->ustItemID ))
            { pSkill->easyusedata.bSkillWithDamage = true; }

            switch (pSkill->ustDamageBalanceType)
            {
            case ItemDefine::balancetype_damagephysicaldefend:   // 对物理防做伤害结算
            case ItemDefine::balancetype_damagemagicdefend:     // 对魔法防做伤害结算
                pSkill->easyusedata.bSkillWithDamage = true;
                break;
            case ItemDefine::balancetype_none:          // 没有任何结算
            case ItemDefine::balancetype_restorehpmp:   // 回HP结算
            case ItemDefine::balancetype_relive:        // 复活结算
            default:
                break;
            }

            //放入相应容器中
            m_mapSkillNO.insert( mapSkillNO::value_type( pSkill->ustItemID,(unsigned short)m_mapSkillNO.size()) );
            m_vecSkill.push_back( pSkill->ustItemID );

            if(pSkill->ustItemID>=ItemDefine::StartID_Skill)
            {
                int index = pSkill->ustItemID-ItemDefine::StartID_Skill;

                m_SkillArray[index][pSkill->ustLevel] = *pSkill;

                if( pSkill->ustLevel == 1 )
                {
                    m_SkillArray[index][ 0 ] = *pSkill;
                }
            }

            m_vecSkillItem.push_back(pSkill);

            // 根据职业划分
            if(pSkill->ustLevel == 1)
            {
                if (pSkill->cLearnProfessionReq >= 0 && pSkill->cLearnProfessionReq < EArmType_MaxSize)
                {
                    m_ArmSkillArray[pSkill->cLearnProfessionReq].push_back( pSkill->ustItemID );
                }
            }

            AddItemToContainer(pSkill);

            pSkillElement = pSkillElement->NextSiblingElement();

        }

        pItemElement = pItemElement->NextSiblingElement();

    }

    return true;
}


bool CItemDetailConfig::SaveSkillItem       ( const char *szFileName )//+保存技能
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

    MeXmlElement *pSkillType = pItems->InsertEndChild(("Type"))->ToElement();
    if (pSkillType == NULL)
    { return false; }

    pSkillType->SetAttribute("Id", ItemDefine::ITEMTYPE_SKILL);

    vectorItem::iterator iterBegin = m_vectorItem.begin();
    vectorItem::iterator iterEnd = m_vectorItem.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (*iterBegin == NULL)
        { continue; }

        if ( (*iterBegin)->ucItemType != ItemDefine::ITEMTYPE_SKILL  )
        { continue; }

        ItemDefine::SItemSkill *pSkillIter = (ItemDefine::SItemSkill *)*iterBegin;
        if (pSkillIter == NULL)
        { continue;}


        MeXmlElement *pItem = pSkillType->InsertEndChild(("Item"))->ToElement();
        if (pItem == NULL)
        { continue; }

        pItem->SetAttribute("Id", pSkillIter->ustItemID);
        Common::_tstring strName = pSkillIter->GetItemName();
        pItem->SetAttribute("ItemName", strName.toUTF8().c_str());
        pItem->SetAttribute("ItemType", ItemDefine::g_szItemType[pSkillIter->ucItemType]);
        Common::_tstring strDescription = pSkillIter->GetItemDesc();
        pItem->SetAttribute("Description", strDescription.toUTF8().c_str());
        pItem->SetAttribute("UseTime", pSkillIter->nUseTime);
        pItem->SetAttribute("UserTarget", pSkillIter->byUserTarget);


        //外观属性
        MeXmlElement *pAppearance = pItem->InsertEndChild(("Appearance"))->ToElement();
        if (pAppearance == NULL)
        { continue; }

        pAppearance->SetAttribute("Rare", pSkillIter->cItemClass);
        pAppearance->SetAttribute("Weight", pSkillIter->fWeight);
        pAppearance->SetAttribute("IconID", pSkillIter->ustIconId);
        Common::_tstring strIconFile = pSkillIter->GetIconInItemBag();
        pAppearance->SetAttribute("IconFile", strIconFile.toUTF8().c_str());
        pAppearance->SetAttribute("DropItemModel", pSkillIter->ustModelIDOverGround);
        pAppearance->SetAttribute("HoldGridWidth", pSkillIter->ustItemW);
        pAppearance->SetAttribute("HoldGridHeight", pSkillIter->ustItemH);
        pAppearance->SetAttribute("StackNum", pSkillIter->nStackNum);

        //价格属性
        MeXmlElement *pPrice = pItem->InsertEndChild(("Price"))->ToElement();
        if (pPrice == NULL)
        { continue; }

        pPrice->SetAttribute("Bill", pSkillIter->nBill);
        pPrice->SetAttribute("CostType", pSkillIter->costType);
        pPrice->SetAttribute("Cost", pSkillIter->dwCost);
        pPrice->SetAttribute("CostItemID", pSkillIter->costItemID);
        pPrice->SetAttribute("SpecialCost", pSkillIter->dwSpecialCost);

        //操作属性
        MeXmlElement *pOperation = pItem->InsertEndChild(("Operation"))->ToElement();
        if (pOperation == NULL)
        { continue; }

        pOperation->SetAttribute("CanMoved", pSkillIter->bIsCanMove);
        pOperation->SetAttribute("CanDroped", pSkillIter->bIsCanDrop);
        pOperation->SetAttribute("CanDeleted", pSkillIter->bIsCanDestory);
        pOperation->SetAttribute("CanTrade", pSkillIter->bIsCanTrade);
        pOperation->SetAttribute("CanSold", pSkillIter->bIsCanSellShop);
        pOperation->SetAttribute("CanStored", pSkillIter->bIsCanPushInStorage);
        pOperation->SetAttribute("CanLocked", pSkillIter->bIsCanLocked);
        pOperation->SetAttribute("CanBound", pSkillIter->bIsCanBound);
        pOperation->SetAttribute("CanSplit", pSkillIter->bIsCanSplit);

        //特效属性
        MeXmlElement *pEffect = pItem->InsertEndChild(("Effect"))->ToElement();
        if (pEffect == NULL)
        { continue; }

        pEffect->SetAttribute("IfShowEqipEffect", pSkillIter->bShowEquipEffect);
        Common::_tstring strCastEffect = pSkillIter->GetSingEffect();
        pEffect->SetAttribute("CastEffectPath", strCastEffect.toUTF8().c_str());
        Common::_tstring strAssoilEffect = pSkillIter->GetAssoilEffect();
        pEffect->SetAttribute("FireEffectPath", strAssoilEffect.toUTF8().c_str());
        Common::_tstring strHurtEffect = pSkillIter->GetHurtEffect();
        pEffect->SetAttribute("HitEffectPath", strHurtEffect.toUTF8().c_str());
        Common::_tstring strSound = pSkillIter->GetIconSoundFile();
        pEffect->SetAttribute("UsingItemSound", strSound.toUTF8().c_str());
        pEffect->SetAttribute("UseSingTime", pSkillIter->dwUseSingTime);
        pEffect->SetAttribute("CanSingingInterrupt", pSkillIter->bCanSingingInterrupt);

        //阈值属性
        MeXmlElement *pThreshold = pItem->InsertEndChild(("Threshold"))->ToElement();
        if (pThreshold == NULL)
        { continue; }

        pThreshold->SetAttribute("DropControlCount", pSkillIter->nDropControlCount);
        pThreshold->SetAttribute("ClearControlCount", pSkillIter->bIsClearControlCount);
        pThreshold->SetAttribute("DropMaxCount", pSkillIter->nDropMaxCount);

        //////////////////////////////////////////////////////////////////////////

        int index = 0;
        for (int j=1; j<ItemDefine::MaxLevel_Skill; ++j)
        {

            //技能属性
            MeXmlElement *pSkill = pItem->InsertEndChild(("Skill"))->ToElement();
            if (pSkill == NULL)
            { continue; }

            if(pSkillIter->ustItemID>=ItemDefine::StartID_Skill)
            {
                index = pSkillIter->ustItemID-ItemDefine::StartID_Skill;
            }

            pSkill->SetAttribute("SkillID", pSkillIter->ustItemID);

            Common::_tstring strSkillName = pSkillIter->GetSkillName();
            pSkill->SetAttribute("SkillName", strSkillName.toUTF8().c_str());

            pSkill->SetAttribute("GroupID", m_SkillArray[index][j].groupId);
            pSkill->SetAttribute("GroupLevel", m_SkillArray[index][j].groupLevel);

            pSkill->SetAttribute("SkillLevel", m_SkillArray[index][j].ustLevel);

            Common::_tstring strSkillDesc = m_SkillArray[index][j].GetSkillDescription();
            pSkill->SetAttribute("Description", strSkillDesc.toUTF8().c_str());

			pSkill->SetAttribute("AddonDesc1", m_SkillArray[index][j].nAddonDesc1);
			pSkill->SetAttribute("AddonDesc2", m_SkillArray[index][j].nAddonDesc2);
			pSkill->SetAttribute("XinFaID", m_SkillArray[index][j].nXinFaID);
			pSkill->SetAttribute("LearnNeedXinFaLevel", m_SkillArray[index][j].nLearnNeedXinFaLevel);


            pSkill->SetAttribute("ActionFlags", m_SkillArray[index][j].iSkillActionFlags);
            pSkill->SetAttribute("MaxSkillLevel", m_SkillArray[index][j].ustSkillMaxLvl);

            //特效属性
            MeXmlElement *pSkillEffect = pSkill->InsertEndChild(("Effect"))->ToElement();
            if (pSkillEffect == NULL)
            { continue; }

            Common::_tstring strCastEffect = m_SkillArray[index][j].GetIntonateEffectName();
            pSkillEffect->SetAttribute("CastEffectMale", strCastEffect.toUTF8().c_str());

            Common::_tstring strReleaseEffect = m_SkillArray[index][j].GetAttackerEffectName();
            pSkillEffect->SetAttribute( "ReleaseEffectMale", strReleaseEffect.toUTF8().c_str() );

            Common::_tstring strSkillEffect = m_SkillArray[index][j].GetSkillEffectName();
            pSkillEffect->SetAttribute("TraceEffectMale", strSkillEffect.toUTF8().c_str());

            Common::_tstring strTargetEffect = m_SkillArray[index][j].GetTargetEffectName();
            pSkillEffect->SetAttribute("HitEffectMale", strTargetEffect.toUTF8().c_str());

            Common::_tstring strCastEffect2 = m_SkillArray[index][j].GetIntonateEffectName2();
            pSkillEffect->SetAttribute("CastEffectFemale", strCastEffect2.toUTF8().c_str());

            Common::_tstring strReleaseEffect2 = m_SkillArray[index][j].GetAttackerEffectName2();
            pSkillEffect->SetAttribute( "ReleaseEffectFemale", strReleaseEffect2.toUTF8().c_str() );

            Common::_tstring strSkillEffect2 = m_SkillArray[index][j].GetSkillEffectName2();
            pSkillEffect->SetAttribute("TraceEffectFemale", strSkillEffect2.toUTF8().c_str());

            Common::_tstring strTargetEffect2 = m_SkillArray[index][j].GetTargetEffectName2();
            pSkillEffect->SetAttribute("HitEffectFemale", strTargetEffect2.toUTF8().c_str());

            pSkillEffect->SetAttribute("KeepEffect", m_SkillArray[index][j].ustHoldEffect);

            //阈值属性
            MeXmlElement *pSkillThreshold = pSkill->InsertEndChild(("Threshold"))->ToElement();
            if (pSkillThreshold == NULL)
            { continue; }

            pSkillThreshold->SetDoubleAttribute("HpPerLimit", m_SkillArray[index][j].fHpPerLimit);
            pSkillThreshold->SetAttribute("ConsumeFightPower", m_SkillArray[index][j].usConsumeFightPower);
            pSkillThreshold->SetAttribute("ConsumeVigor", m_SkillArray[index][j].usConsumeVigor);
            pSkillThreshold->SetDoubleAttribute("BackStrikeAffixed", m_SkillArray[index][j].fBackStrikePlus);
            pSkillThreshold->SetAttribute("ColdDownTime", m_SkillArray[index][j].dwSkillCoolDownTime);
            pSkillThreshold->SetAttribute("CommonCoolDownTime", m_SkillArray[index][j].dwCommonCoolDownTime);
            pSkillThreshold->SetAttribute("FreezeTime", m_SkillArray[index][j].ustHoldTime);
            pSkillThreshold->SetAttribute("CastSpeed", m_SkillArray[index][j].ustPrepTime);
            pSkillThreshold->SetAttribute("IfShowIntonateBar", m_SkillArray[index][j].bShowIntonateBar);
            pSkillThreshold->SetAttribute("AOENum", m_SkillArray[index][j].shMaxTargetNum);
            pSkillThreshold->SetAttribute("InternalTime", m_SkillArray[index][j].iDamageBalanceDelay);
            pSkillThreshold->SetAttribute("DamageDelayBalanceTime", m_SkillArray[index][j].dwDamageDelayBalanceTime);
            pSkillThreshold->SetAttribute("Enmity", m_SkillArray[index][j].stEnmity);

            //状态属性
            MeXmlElement *pSkillStatus = pSkill->InsertEndChild(("Status"))->ToElement();
            if (pSkillStatus == NULL)
            { continue; }

            pSkillStatus->SetAttribute("AddStatusMe1", m_SkillArray[index][j].ustMeAddStatusID[0]);
            pSkillStatus->SetAttribute("AddStatusLvMe1", m_SkillArray[index][j].ustMeAddStatusLevel[0]);
            pSkillStatus->SetAttribute("AddStatusMe2", m_SkillArray[index][j].ustMeAddStatusID[1]);
            pSkillStatus->SetAttribute("AddStatusLvMe2", m_SkillArray[index][j].ustMeAddStatusLevel[1]);
            pSkillStatus->SetAttribute("AddStatusTarget1", m_SkillArray[index][j].ustDstAddStatusID[0]);
            pSkillStatus->SetAttribute("AddStatusLvTarget1", m_SkillArray[index][j].ustDstAddStatusLevel[0]);
            pSkillStatus->SetAttribute("AddStatusTarget2", m_SkillArray[index][j].ustDstAddStatusID[1]);
            pSkillStatus->SetAttribute("AddStatusLvTarget2", m_SkillArray[index][j].ustDstAddStatusLevel[1]);
            pSkillStatus->SetAttribute("StatusHitRate", m_SkillArray[index][j].ustStatusHitRate);
            pSkillStatus->SetAttribute("StatusDispel", m_SkillArray[index][j].dwSubComboStatus);

            for (int k=0; k<ItemDefine::CLEAR_MAX_STATUS; ++k)
            {
                char szTmp[65] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "StatusDispel%d", k);
                pSkillStatus->SetAttribute(szTmp, m_SkillArray[index][j].dwClearStatus[k]);//0-4
            }

            for ( int i=0; i< ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize; ++i )
            {
                char szTemp[64] = {0};
                sprintf_s( szTemp, sizeof(szTemp), "DispelNegativeType%d", i+1 );
                pSkillStatus->SetAttribute(szTemp, m_SkillArray[index][j].dispelNegativeType[i]);
            }

            pSkillStatus->SetAttribute("AddBackStrikeStatusMe", m_SkillArray[index][j].stBackStrikeMeStatus);
            pSkillStatus->SetAttribute("AddBackStrikeStatusLvMe", m_SkillArray[index][j].stBackStrikeMeStatusLevel);
            pSkillStatus->SetAttribute("AddBackStrikeStatusTarget", m_SkillArray[index][j].stBackStrikeDstStatus);
            pSkillStatus->SetAttribute("AddBackStrikeStatusLvTarget", m_SkillArray[index][j].stBackStrikeDstStatusLevel);

            //动作属性
            MeXmlElement *pSkillAction = pSkill->InsertEndChild(("Action"))->ToElement();
            if (pSkillAction == NULL)
            { continue; }

            Common::_tstring strSkillAct;

			strSkillAct = m_SkillArray[index][j].GetSkillRideAction();
			pSkillAction->SetAttribute("RideAction", strSkillAct.toUTF8().c_str());

            for (int k=0; k<10; ++k)
            {
                strSkillAct.clear();
                char szTmp[65] = {0};
                sprintf_s( szTmp, sizeof(szTmp) - 1, "SkillAct%d", k+1 );
                strSkillAct = m_SkillArray[index][j].GetSkillAction(k);
                pSkillAction->SetAttribute(szTmp, strSkillAct.toUTF8().c_str());
            }

            for (int k=0; k<20; ++k)
            {
                char szTmp[65] = {0};
                sprintf_s(szTmp, sizeof(szTmp) - 1, "SkillActPlaySpd%d", k+1);
                pSkillAction->SetAttribute( szTmp, m_SkillArray[index][j].ustSkillActionSpeed[k] );
            }

            //消耗恢复相关
            MeXmlElement *pSkillUseRes= pSkill->InsertEndChild(("UseRes"))->ToElement();
            if (pSkillUseRes == NULL)
            { continue; }

            pSkillUseRes->SetAttribute("UseHp", m_SkillArray[index][j].ustCostHP);
            pSkillUseRes->SetAttribute("UseHpPer", m_SkillArray[index][j].ustCostHPPer);
            pSkillUseRes->SetAttribute("UseMp", m_SkillArray[index][j].ustCostMP);
            pSkillUseRes->SetAttribute("UseMpPer", m_SkillArray[index][j].ustCostMPPer);
            pSkillUseRes->SetAttribute("AbsorbHp", m_SkillArray[index][j].nSuckHpAtt);
            pSkillUseRes->SetAttribute("AbsorbMp", m_SkillArray[index][j].nSuckMpAtt);
			//skill表读取bug修改
			pSkillUseRes->SetDoubleAttribute("ReviveHpPer", m_SkillArray[index][j].fReliveHp);
			pSkillUseRes->SetDoubleAttribute("ReviveMpPer", m_SkillArray[index][j].fReliveMp);
            pSkillUseRes->SetAttribute("IncreaseFightPower", m_SkillArray[index][j].usIncreaseFightPower);

            //需求属性
            MeXmlElement *pSkillRequirement = pSkill->InsertEndChild(("Requirement"))->ToElement();
            if (pSkillRequirement == NULL)
            { continue; }

            pSkillRequirement->SetAttribute("JobNeed", m_SkillArray[index][j].cLearnProfessionReq);
            pSkillRequirement->SetAttribute("LevelNeed", m_SkillArray[index][j].stLearnLevelReq);
            pSkillRequirement->SetAttribute("SkillExp", m_SkillArray[index][j].nLearnNeedExp);
            pSkillRequirement->SetAttribute("WeaponNeed", m_SkillArray[index][j].bNeedWeapon);
            pSkillRequirement->SetAttribute("ItemNeed", m_SkillArray[index][j].stUseItem);

            if(m_SkillArray[index][j].stWeaponNeed == -1)
                pSkillRequirement->SetAttribute("WeaponType", "NULL");
            else
                pSkillRequirement->SetAttribute("WeaponType", ItemDefine::g_szWeaponType[m_SkillArray[index][j].stWeaponNeed]);

            pSkillRequirement->SetAttribute("NeedMoney", m_SkillArray[index][j].stMoneyNeed);

            for (int k=0;k<3;++k)
            {
                char SkillNeed[65] = {0};
                char SkillLevelNeed[65] = {0};
                sprintf_s(SkillNeed, sizeof(SkillNeed) - 1, "FormerSkill%d", k+1);
                sprintf_s(SkillLevelNeed, sizeof(SkillLevelNeed) - 1, "FormerSkillLevel%d", k+1);
                pSkillRequirement->SetAttribute(SkillNeed, m_SkillArray[index][j].stSkillNeed[k]);
                pSkillRequirement->SetAttribute(SkillLevelNeed, m_SkillArray[index][j].stSkillLevelNeed[k]);
            }

            //判断属性
            MeXmlElement *pSkillWhether = pSkill->InsertEndChild(("Whether"))->ToElement();
            if (pSkillWhether == NULL)
            { continue; }

            pSkillWhether->SetAttribute("IfKeepAtk", m_SkillArray[index][j].bContinueAtt);
            pSkillWhether->SetAttribute("IfRevive", m_SkillArray[index][j].bIsRelive);
            pSkillWhether->SetAttribute("IfBackStrike", m_SkillArray[index][j].bNeedTestBackStrike);
            pSkillWhether->SetAttribute("IfNeedAngle", m_SkillArray[index][j].bNeedTestAngle);
            pSkillWhether->SetAttribute("IfTrace", m_SkillArray[index][j].bEmissionSkill); 
            pSkillWhether->SetAttribute("IfAssault", m_SkillArray[index][j].bAssaultSkill);  
            pSkillWhether->SetAttribute("IfHide", m_SkillArray[index][j].bHideSkill);
            pSkillWhether->SetAttribute("IfSummon", m_SkillArray[index][j].bSummonSkill);
            pSkillWhether->SetAttribute("IfKeepStatus", m_SkillArray[index][j].bHoldSkill);
            pSkillWhether->SetAttribute("IfAfterIllusion", m_SkillArray[index][j].bIsAfterIllusion);
            pSkillWhether->SetAttribute("IfEnterFightStatus", m_SkillArray[index][j].bEnterFightStatus);
            pSkillWhether->SetAttribute("IsCatchNurturePet", m_SkillArray[index][j].bIsCatchNurturePet);
            pSkillWhether->SetAttribute("IsKillPet", m_SkillArray[index][j].iskillpet);
            pSkillWhether->SetAttribute("IsPetUseSkill", m_SkillArray[index][j].ispettouseskill);
            pSkillWhether->SetAttribute("IfNextNotIntonate", m_SkillArray[index][j].bNextNotIntonate);
            pSkillWhether->SetAttribute("IfGiddyDischarge", m_SkillArray[index][j].bGiddyDischarge);
            pSkillWhether->SetAttribute("IfMoveInterrupt", m_SkillArray[index][j].bMoveInterrupt);

            //概率属性
            MeXmlElement *pSkillRate = pSkill->InsertEndChild(("Rate"))->ToElement();
            if (pSkillRate == NULL)
            { continue; }

            pSkillRate->SetDoubleAttribute("ActionRatio", m_SkillArray[index][j].actionRatio);
            pSkillRate->SetAttribute("NormalAttackRatio", m_SkillArray[index][j].normalAttackRatio);
            pSkillRate->SetAttribute("SkillHit", m_SkillArray[index][j].stSkillHitRate);
            pSkillRate->SetDoubleAttribute("DamageRate", m_SkillArray[index][j].fDamageRate);
            pSkillRate->SetDoubleAttribute("FPDamageRatio", m_SkillArray[index][j].fFPDamageRatio);
            pSkillRate->SetDoubleAttribute("AddBackStrikeStatusRate", m_SkillArray[index][j].fBackStrikeStatusRate);
            pSkillRate->SetDoubleAttribute("PetAutoSkillTriggerRate", m_SkillArray[index][j].petAutoSkillTriggerRate);

            //类型属性
            MeXmlElement *pSkillType = pSkill->InsertEndChild(("SkillType"))->ToElement();
            if (pSkillType == NULL)
            { continue; }

            pSkillType->SetAttribute("SkillType", ItemDefine::g_szSkillType[m_SkillArray[index][j].stSkillType]);
            pSkillType->SetAttribute("GeneralType", ItemDefine::g_szSkillGeneralType[m_SkillArray[index][j].stGeneralType]);
            pSkillType->SetAttribute("TargetType", ItemDefine::g_szTargetString[m_SkillArray[index][j].stTargetType]);
            pSkillType->SetAttribute("CenterTargetType", ItemDefine::g_szEffectCenter[m_SkillArray[index][j].stEffectCenterType]);
            pSkillType->SetAttribute("ColdDownType", m_SkillArray[index][j].nSkillCoolDownType);
            pSkillType->SetAttribute("CastTarget", ItemDefine::g_szSkillCastTarget[m_SkillArray[index][j].ustCastTarget]);
            pSkillType->SetAttribute("CastType", ItemDefine::g_szCastType[m_SkillArray[index][j].shCastType]);
            pSkillRate->SetAttribute("TriggerType", m_SkillArray[index][j].triggerType);
            pSkillType->SetAttribute("FightStateCastType", m_SkillArray[index][j].cFightStateCastType);
            pSkillType->SetAttribute("HpLimitType", m_SkillArray[index][j].cHpLimitType);
            pSkillType->SetAttribute("InstantMovingType", m_SkillArray[index][j].ustInstantMovingType);
            pSkillType->SetAttribute("SkillCategory", m_SkillArray[index][j].sSkillCategory);
            pSkillType->SetAttribute("SpecialTargetType", m_SkillArray[index][j].usSpecialTargetType);
            pSkillType->SetAttribute("SpecialSkillType", m_SkillArray[index][j].specialSkillType);
            pSkillType->SetAttribute("MountSkillCategory", m_SkillArray[index][j].mountSkillCategory);
            pSkillType->SetAttribute("MountAptitudeCategory", m_SkillArray[index][j].mountAptitudeCategory);
            pSkillType->SetAttribute("PetSkillCategory", m_SkillArray[index][j].petSkillCategory);
            pSkillType->SetAttribute("PetAutoSkillType", m_SkillArray[index][j].petAutoSkillType);

            //方位属性
            MeXmlElement *pSkillPosition = pSkill->InsertEndChild(("Position"))->ToElement();
            if (pSkillPosition == NULL)
            { continue; }

            pSkillPosition->SetDoubleAttribute("MaxcastDistance", m_SkillArray[index][j].fRangeCanCast);
            pSkillPosition->SetDoubleAttribute("MincastDistance", m_SkillArray[index][j].fRangeCanCastMin);
            pSkillPosition->SetAttribute("DamDistance", m_SkillArray[index][j].stDamageEffectDistance); 
            pSkillPosition->SetDoubleAttribute("AOERange", m_SkillArray[index][j].fAOEradius); 
            pSkillPosition->SetDoubleAttribute("Angle", m_SkillArray[index][j].fAngle);
            pSkillPosition->SetAttribute("MustInBackUse", m_SkillArray[index][j].bMustInBackUse);

            //攻击属性
            MeXmlElement *pSkillAttack = pSkill->InsertEndChild(("Attack"))->ToElement();
            if (pSkillAttack == NULL)
            { continue; }

            pSkillAttack->SetAttribute("HurtAct", m_SkillArray[index][j].ustIDTargetHitAction);
            pSkillAttack->SetAttribute("KeepTime", m_SkillArray[index][j].iDurationTime);
            pSkillAttack->SetAttribute("AutoAtk", m_SkillArray[index][j].bAutoAttackTarget); 

            pSkillAttack->SetAttribute("AdditionalDamageType", m_SkillArray[index][j].additionalDamageType);
            pSkillAttack->SetAttribute("AdditionalDamageStatus", m_SkillArray[index][j].additionalDamageStatus	);

            if (m_SkillArray[index][j].additionalDamageProfession != -1)
            {
                pSkillAttack->SetAttribute("AdditionalDamageProfession", ItemDefine::g_szProfessionType[m_SkillArray[index][j].additionalDamageProfession]);
            }
            else
            {
                pSkillAttack->SetAttribute("AdditionalDamageProfession", "NULL");
            }


            pSkillAttack->SetAttribute("AdditionalDamagePer", m_SkillArray[index][j].additionalDamagePer);
            pSkillAttack->SetAttribute("AddtionalCritical", m_SkillArray[index][j].addtionalCritical);
            pSkillAttack->SetAttribute("AdditionalPhyAttack", m_SkillArray[index][j].additionalPhyAttack);
            pSkillAttack->SetAttribute("AdditionalMagAttack", m_SkillArray[index][j].additionalMagAttack);
            pSkillAttack->SetAttribute("MountAptitudeModulus", m_SkillArray[index][j].mountAptitudeModulus);
            pSkillAttack->SetAttribute("ReleaseLapoverStatus", m_SkillArray[index][j].releaseLapoverStatus);

            pSkillAttack->SetAttribute("BreakStrike", m_SkillArray[index][j].breakStrike    );
            pSkillAttack->SetAttribute("StabStrike", m_SkillArray[index][j].stabStrike      );
            pSkillAttack->SetAttribute("ElementStrike", m_SkillArray[index][j].elementStrike);
            pSkillAttack->SetAttribute("ToxinStrike", m_SkillArray[index][j].toxinStrike    );
            pSkillAttack->SetAttribute("SpiritStrike", m_SkillArray[index][j].spiritStrike  );

            //宠物属性
            MeXmlElement *pSkillPet = pSkill->InsertEndChild(("Pet"))->ToElement();
            if (pSkillPet == NULL)
            { continue; }

            pSkillPet->SetAttribute("SunmmonMonsterId", m_SkillArray[index][j].nSummonMonsterId);
            pSkillPet->SetAttribute("PetUseSkillID", m_SkillArray[index][j].ustPetSkillID);
            pSkillPet->SetAttribute("PetUseSkillLevel", m_SkillArray[index][j].ustPetSkillLevel);
            pSkillPet->SetAttribute("NeedPetToUseSkill", m_SkillArray[index][j].needpet);

            //其他属性
            MeXmlElement *pSkillOther = pSkill->InsertEndChild(("Other"))->ToElement();
            if (pSkillOther == NULL)
            { continue; }

            pSkillOther->SetAttribute("UseFormula", ItemDefine::g_szBalanceType[m_SkillArray[index][j].ustDamageBalanceType]);
            Common::_tstring strIntonateAction = m_SkillArray[index][j].GetIntonateAction();
            pSkillOther->SetAttribute("CastAct",strIntonateAction.toUTF8().c_str());
			Common::_tstring strRideIntonateAction = m_SkillArray[index][j].GetRideIntonateAction();
			pSkillOther->SetAttribute("RideCastAct",strRideIntonateAction.toUTF8().c_str());
            pSkillOther->SetAttribute("InterruptIntonatingAbility", m_SkillArray[index][j].nInterruptIntonatingAbility);
            pSkillOther->SetAttribute("ReleaseHide", m_SkillArray[index][j].bCancelHideSkill);
            pSkillOther->SetAttribute("PassiveSkillTarget", ItemDefine::g_szPassiveSkillTargetString[m_SkillArray[index][j].shPassiveSkillTarget]);
            pSkillOther->SetAttribute("ScriptRunSkill", m_SkillArray[index][j].bScriptRunSkill);
            pSkillOther->SetAttribute("ProfessionMountSkill", m_SkillArray[index][j].iMountSkillProfessionType);
            pSkillOther->SetAttribute("NextNotIntonateNum", m_SkillArray[index][j].nNextNotIntonateNum);

            Common::_tstring strProfessionReq;
            Common::_tstring strSpn = ",";
            for (int i=0; i<EArmType_MaxSize; ++i)
            {
                if (m_SkillArray[index][j].arrayProfessionReq[i] == true)
                {
                    strProfessionReq = strProfessionReq + string(ItemDefine::g_szProfessionType[i]);
                    strProfessionReq = strProfessionReq + strSpn ;
                }
            } 
            pSkillOther->SetAttribute("UseSkillProfession" , strProfessionReq.substr(0,strProfessionReq.length() - 1).c_str());

        }


    }

    return MeXmlDoc.SaveFile(szFileName);
}


#pragma warning( pop )