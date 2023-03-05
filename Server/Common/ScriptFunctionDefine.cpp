#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "FuncPerformanceLog.h"
#include "WordParser.h"
#include "QuestManager.h"
#include "Helper.h"
#include "ScriptVarMgr.h" 
#include "GlobalDef.h"

extern IScriptInterface* GetScriptInterface();

////////////////////////////////////////////////////////////////////////////
//// [KEY]
//SCRIPT_BEGIN( [KEY] )
//virtual BOOL Create( WordParser* words )
//{
//    if( words->GetWordCount() != 2 )
//    {
//        GetScriptInterface()->Printf( "error:[KEY]" );
//        return FALSE;
//    }
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* vm )
//{
//    vm->NextIP();
//}
//
//SCRIPT_PARAM
//SCRIPT_END



SCRIPT_DECLARE( _SetVar,        CScriptCmd__SetVar );
SCRIPT_DECLARE( dlg,            CScriptCmd_Dlg );
SCRIPT_DECLARE( shop,           CScriptCmd_Shop );
SCRIPT_DECLARE( flytomap,       CScriptCmd_FlyToMap );
SCRIPT_DECLARE( callallteamplayerflytomap, CScriptCmd_CallAllTeamPlayerFlyToMap);
SCRIPT_DECLARE( bc,             CScriptCmd_Broadcast );
SCRIPT_DECLARE( ask,            CScriptCmd_Ask );
SCRIPT_DECLARE( RemoveAllEquip, CScriptCmd_RemoveAllEquip );
SCRIPT_DECLARE( SetBornPoint,   CScriptCmd_SetBornPoint );
SCRIPT_DECLARE( HaveThisItem,   CScriptCmd_HaveThisItem );
SCRIPT_DECLARE( RemoveThisItem, CScriptCmd_RemoveThisItem );
SCRIPT_DECLARE( IsThisItemEquipped, CScriptCmd_IsThisItemEquipped );
SCRIPT_DECLARE( IsThisSkillActived, CScriptCmd_IsThisSkillActived );

SCRIPT_DECLARE( HaveThisItem_Byid,   CScriptCmd_HaveThisItem_Byid );
SCRIPT_DECLARE( RemoveThisItem_Byid, CScriptCmd_RemoveThisItem_Byid );
SCRIPT_DECLARE( IsThisItemEquipped_Byid, CScriptCmd_IsThisItemEquipped_Byid );

SCRIPT_DECLARE( HaveThisTitle, CScriptCmd_HaveThisTitle);

SCRIPT_DECLARE( NpcMainDlg,     CScriptCmd_NpcMainDlg );

SCRIPT_DECLARE( GetWeekKillNum, CScriptCmd_GetWeekKillNum );
SCRIPT_DECLARE( GetAllKillNum, CScriptCmd_GetAllKillNum );
SCRIPT_DECLARE( GetSeriesKillNum, CScriptCmd_GetSeriesKillNum );
SCRIPT_DECLARE( ProcTimeStep, CScriptCmd_ProcTimeStep );

SCRIPT_DECLARE( ChangeTimeHandleStates, CScriptCmd_ChangeTimeHandleStates );
SCRIPT_DECLARE( ResetTimeHandleStates, CScriptCmd_ResetTimeHandleStates );
SCRIPT_DECLARE( ClearTimeHandle, CScriptCmd_ClearTimeHandle );

SCRIPT_DECLARE( SetWorldBattleCountry, CScriptCmd_SetWorldBattleCountry );
SCRIPT_DECLARE( AddEquipRandAttrItem, CScriptCmd_AddEquipRandAttrItem );
SCRIPT_DECLARE( UseItem, CScriptCmd_UseItem );

SCRIPT_DECLARE( ChangeGamePlayerDuration, CScriptCmd_ChangeGamePlayerDuration );

SCRIPT_DECLARE( ChangePetMode, CScriptCmd_ChangePetMode );

SCRIPT_DECLARE( GetPlayerStates, CScriptCmd_GetPlayerStates );
SCRIPT_DECLARE( AddCard, CScriptCmd_AddCard );

SCRIPT_DECLARE( GetGamePlayerDuration, CScriptCmd_GetGamePlayerDuration );

SCRIPT_DECLARE( TriggerSevenDays, CScriptCmd_TriggerSevenDays );
SCRIPT_DECLARE( AddFriendPoint,       CScriptCmd_AddFriendPoint );
SCRIPT_DECLARE( IsInFight,       CScriptCmd_IsInFight );
SCRIPT_DECLARE( IsMountFull,       CScriptCmd_IsMountFull );
SCRIPT_DECLARE( SetScriptStates,       CScriptCmd_SetScriptStates );
SCRIPT_DECLARE( CanFlyToCouple,       CScriptCmd_CanFlyToCouple );


SCRIPT_DECLARE( DropQuestEntrust,       CScriptCmd_DropQuestEntrust );
SCRIPT_DECLARE( DoneQuestEntrust,       CScriptCmd_DoneQuestEntrust );
SCRIPT_DECLARE( CanelQuestEntrust,       CScriptCmd_CanelQuestEntrust );

SCRIPT_DECLARE( GetTodayHuntingCount,       CScriptCmd_GetTodayHuntingCount );
SCRIPT_DECLARE( OperateHuntingCount,       CScriptCmd_OperateHuntingCount );
SCRIPT_DECLARE( DoneHuntingQuest,       CScriptCmd_DoneHuntingQuest );

SCRIPT_DECLARE( FlytoPosition,       CScriptCmd_FlytoPosition );


SCRIPT_DECLARE( AddHonourByTeam,       CScriptCmd_AddHonourByTeam );

SCRIPT_DECLARE( GetStrongCountry,       CScriptCmd_GetStrongCountry );
SCRIPT_DECLARE( GetWeakCountry,         CScriptCmd_GetWeakCountry );

SCRIPT_DECLARE( ChangePlayerPoint,         CScriptCmd_ChangePlayerPoint );


SCRIPT_DECLARE( SetMonsterArray,         CScriptCmd_SetMonsterArray );
SCRIPT_DECLARE( GetMonsterArray,         CScriptCmd_GetMonsterArray );


//SCRIPT_DECLARE( MonsterAIScript_StateChangeBringOn, CScriptCmd_StateChangeBringOn );
//SCRIPT_DECLARE( MonsterAIScript_NormalAttack, CScriptCmd_NormalAttack );


void ScriptSprintf( char* szBuf, int nBufSize,
                   const char* szText, const std::vector<std::string>& vtVar )
{
    int nCount = vtVar.size();
    if ( nCount == 0 )
        strncpy( szBuf, szText, nBufSize-1 );
    else if ( nCount == 1 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str() );
    else if ( nCount == 2 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str() );
    else if ( nCount == 3 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str(),
        vtVar[2].c_str() );
    else if ( nCount == 4 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str(),
        vtVar[2].c_str(),
        vtVar[3].c_str() );
    else if ( nCount == 5 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str(),
        vtVar[2].c_str(),
        vtVar[3].c_str(),
        vtVar[4].c_str() );
    else if ( nCount == 6 )
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str(),
        vtVar[2].c_str(),
        vtVar[3].c_str(),
        vtVar[4].c_str(),
        vtVar[5].c_str() );
    else
        sprintf_s( szBuf, nBufSize, szText,
        vtVar[0].c_str(),
        vtVar[1].c_str(),
        vtVar[2].c_str(),
        vtVar[3].c_str(),
        vtVar[4].c_str(),
        vtVar[5].c_str(),
        vtVar[6].c_str() );
}


//////////////////////////////////////////////////////////////////////////
//
// set
void CScriptCmd__SetVar::Param::SetString( const char* p )
{
    if( !p ) return;
    int nLength = strlen( p );
    if( nLength == 0 )
        return ;
    pszString = new char[nLength+1];
    HelperFunc::SafeNCpy( pszString, p, nLength+1 );
}
// money = 100
// money += 100
BOOL CScriptCmd__SetVar::Create( WordParser* words )
{
    m_nParamCount = words->GetWordCount();
    const char *szWord = NULL;
    if ( m_nParamCount <= 0 || m_nParamCount > MAX_SCRIPT_SET_PARAM )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "_SetVar ParamCount[%d] too big", m_nParamCount);
        return FALSE;
    }
    for ( int n=0; n<m_nParamCount; n++ )
    {
        szWord = words->GetWord( n );
        if( WordParser::IsNumber( szWord ) )
        {
            m_params[n].SetNumber( atoi( szWord ) );
            m_params[n].SetIsKey( false );
        }
        else
        {
            int nKey = GetScriptVarMgr()->GetVarId( szWord );
            if ( nKey != -1 )
            {
                m_params[n].SetNumber( nKey );
                m_params[n].SetIsKey( true );
            }
            else
            {
                m_params[n].SetString( szWord );
                return FALSE;
            }
        }
    }
    return TRUE;
}
void CScriptCmd__SetVar::Execute( CScriptVM* vm )
{
    if ( m_nParamCount <= 0 ||
        m_nParamCount > MAX_SCRIPT_SET_PARAM )
    {
        return;
    }
    Param    params[MAX_SCRIPT_SET_PARAM];
    Param *pSrc, *pDst;
    for ( int n=0; n<m_nParamCount; n++ )
    {
        pSrc = &m_params[n];
        pDst = &params[n];
        if ( pSrc->IsKey() )
        {
            int nKey = pSrc->GetNumber();
            int nVar = GetScriptInterface()->GetVar( nKey );
            pDst->SetNumber( nVar );
        }
        else
        {
            pDst->SetNumber( pSrc->GetNumber() );
            pDst->SetString( pSrc->GetString() );
        }
    }
    if ( m_nReturnKey != -1 )
    {
        GetScriptInterface()->SetVar( m_nReturnKey, m_nOp, params, m_nParamCount );
    }
    vm->NextIP();
}

// dlg 0 hello
// dlg 0 有馒头%s个 $n id
BOOL CScriptCmd_Dlg::Create( WordParser* words )
{
    if( words->GetWordCount() < 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error, param count < 3");
        return FALSE;
    }

    iButtionFlag = atoi( words->GetWord(0) );

    const char* szWord = words->GetWord(1);
    if( WordParser::IsNumber( szWord ) )
    {   
        _paramValue.SetNumber( atoi( szWord ) );
        _paramValue.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetPlayerVar error" );
            return FALSE;
        }
        _paramValue.SetNumber( nKey );
        _paramValue.SetIsKey( true );
    }

    m_strText = words->GetWord(2);
    for ( int n = 3; n<words->GetWordCount(); ++n )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }

    int nCount = 0;
    for ( int n=0; n<m_strText.size()-1; ++n )
    {
        if ( m_strText[n] == '%' )
        {
            if ( m_strText[n+1] == 's' )
            {
                ++nCount;
            }
            else if (m_strText[n+1] == 'd' )
            {
                ++nCount;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
        return FALSE;
    }
    return TRUE;
}

// 对话
void CScriptCmd_Dlg::Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    
    int iValue = 0;
    if ( _paramValue.IsKey() )
    {
        int nKey = _paramValue.GetNumber();
        iValue = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        iValue = _paramValue.GetNumber();
    }

    char szText[1024] = {0};
    ScriptSprintf( szText, sizeof(szText)-1, m_strText.c_str(), vtVar );
    GetScriptInterface()->Dlg( szText, iButtionFlag ,iValue );
    
    vm->NextIP();
    vm->Hangup();
}


BOOL CScriptCmd_NpcMainDlg::Create( WordParser* words )
{
    if( words->GetWordCount() < 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error, param count < 3");
        return FALSE;
    }

    iButtionFlag = atoi( words->GetWord(0) );

    const char* szWord = words->GetWord(1);
    if( WordParser::IsNumber( szWord ) )
    {   
        _paramValue.SetNumber( atoi( szWord ) );
        _paramValue.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetPlayerVar error" );
            return FALSE;
        }
        _paramValue.SetNumber( nKey );
        _paramValue.SetIsKey( true );
    }

    m_strText = words->GetWord(2);
    for ( int n = 3; n<words->GetWordCount(); ++n )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }

    int nCount = 0;
    for ( int n=0; n<m_strText.size()-1; ++n )
    {
        if ( m_strText[n] == '%' )
        {
            if ( m_strText[n+1] == 's' )
            {
                ++nCount;
            }
            else if (m_strText[n+1] == 'd' )
            {
                ++nCount;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
        return FALSE;
    }
    return TRUE;
}

// 对话
void CScriptCmd_NpcMainDlg::Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }

    int iValue = 0;
    if ( _paramValue.IsKey() )
    {
        int nKey = _paramValue.GetNumber();
        iValue = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        iValue = _paramValue.GetNumber();
    }

    char szText[1024] = {0};
    ScriptSprintf( szText, sizeof(szText)-1, m_strText.c_str(), vtVar );
    GetScriptInterface()->NpcMainDlg( szText, iButtionFlag ,iValue );

    vm->NextIP();
    vm->Hangup();
}

// 商店
static SShopItem g_stShopItems[SHOP_ITEM_MAXCOUNT];
static int       g_nShopItemCount = 0;
//////////////////////////////////////////////////////////////////////////
// Shop_Item id price mincount maxcount percount X
SCRIPT_BEGIN( Shop_Item )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() == 4 )
    {
        SShopItem stItem;
        stItem.nId        = atoi( words->GetWord(0) );
        stItem.nBasePrice = atoi( words->GetWord(1) );
        stItem.nMaxCount  = atoi( words->GetWord(2) );
        stItem.nPerCount  = atoi( words->GetWord(3) );
        stItem.nCurCount  = -1;
        stItem.bIsBound   = true;
        g_stShopItems[g_nShopItemCount++] = stItem;
        
        return TRUE;
    }

    if( words->GetWordCount() == 5 )
    {
        SShopItem stItem;
        stItem.nId        = atoi( words->GetWord(0) );
        stItem.nBasePrice = atoi( words->GetWord(1) );
        stItem.nMaxCount  = atoi( words->GetWord(2) );
        stItem.nPerCount  = atoi( words->GetWord(3) );
        stItem.bIsBound   = atoi( words->GetWord(4) );
        stItem.nCurCount  = -1;
        g_stShopItems[g_nShopItemCount++] = stItem;
        return TRUE;
    }

    if ( g_nShopItemCount >= SHOP_ITEM_MAXCOUNT || g_nShopItemCount < 0)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Shop_Item count is more then %d", SHOP_ITEM_MAXCOUNT );
        return FALSE;
    }
    
    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Shop_Item" );
    return FALSE;
}

virtual void Execute( CScriptVM* vm )
{
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

// shop id rate type
BOOL CScriptCmd_Shop::Create( WordParser* words )
{
    int nRate = 0;
    int nType = 0;
    bool bIsBound = true;

    if( words->GetWordCount() == 3 )
    {
        m_nShopId = atoi( words->GetWord(0) );
        nRate = atoi( words->GetWord(1) );
        nType = atoi( words->GetWord(2) );
    }

    if( words->GetWordCount() == 4 )
    {
        m_nShopId = atoi( words->GetWord(0) );
        nRate = atoi( words->GetWord(1) );
        nType = atoi( words->GetWord(2) );
        bIsBound = atoi( words->GetWord(3) );
    }

    if ( g_nShopItemCount <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:shop can`t find Shop_Item" );
        return FALSE;
    }

    bool bSuccess = GetScriptInterface()->InitShop( m_nShopId, nRate, nType, bIsBound, g_stShopItems, g_nShopItemCount );
    g_nShopItemCount = 0;

    if ( bSuccess )
    { return TRUE; }

    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:shop" );
    return FALSE;
}
void CScriptCmd_Shop::Execute( CScriptVM* vm )
{
    int nCharId = GetScriptInterface()->GetCurCharId();
    GetScriptInterface()->Shop( m_nShopId, nCharId );
    vm->NextIP();
//    vm->Hangup();
}

// 切换地图
// flytomap 0 47 47
BOOL CScriptCmd_FlyToMap::Create( WordParser* words )
{
    int nWordCount = words->GetWordCount();
    if( nWordCount != 7 && nWordCount != 6 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "flytomap create error, param count != 6 and != 7" );
        return FALSE;
    }
    // MapId变量
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_nMapId.SetNumber(atoi(szMapId));
        m_nMapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "flytomap param MapId error" );
            return FALSE;
        }
        m_nMapId.SetNumber(nKey);
        m_nMapId.SetIsKey(true);
    }
    // X坐标变量
    const char* szLocX = words->GetWord(1);
    if ( WordParser::IsNumber(szLocX) )
    {
        m_LocX.SetNumber( atoi(szLocX) );
        m_LocX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szLocX);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "flytomap param X error");
            return FALSE;
        }
        m_LocX.SetNumber(nKey);
        m_LocX.SetIsKey(true);
    }
    // Y坐标变量
    const char* szLocY = words->GetWord(2);
    if ( WordParser::IsNumber(szLocY) )
    {
        m_LocY.SetNumber( atoi(szLocY) );
        m_LocY.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szLocY);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "flytomap param Y error");
            return FALSE;
        }
        m_LocY.SetNumber(nKey);
        m_LocY.SetIsKey(true);
    }
    // 朝向
    int nAngle = atoi( words->GetWord( 3 ) );
    if (nAngle < -360)
        nAngle = -360;
    if (nAngle > 360)
        nAngle = 360;

    m_fDir = nAngle * PI / 180.f;
    // 飞行类型
    m_chFlyType = atoi( words->GetWord(4) );
    m_bCheckHeader = atoi( words->GetWord(5) );
    // 任务Id
    if (nWordCount == 7)
    {
        //m_nQuestID = atoi( words->GetWord(6) );
        const char* szQuestId = words->GetWord(6);
        if ( WordParser::IsNumber(szQuestId) )
        {
            m_QuestId.SetNumber( atoi(szQuestId) );
            m_QuestId.SetIsKey(false);
        }
        else
        {
            int nKey = GetScriptVarMgr()->GetVarId(szQuestId);
            if ( nKey == -1 )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "flytomap param QuestId error" );
                return FALSE;
            }
            m_QuestId.SetNumber(nKey);
            m_QuestId.SetIsKey(true);
        }
    }
    else
    {
        //m_nQuestID = -1;
        m_QuestId.SetNumber(-1);
    }

    return TRUE;
}
void CScriptCmd_FlyToMap::Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_nMapId.IsKey() )
    {
        int nKey = m_nMapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nMapId = m_nMapId.GetNumber();
    }
    if ( nMapId <= 0 )
    {// 地图Id不能小于0
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:FlyToMap MapId[%d]", nMapId );
        return;
    }

    int nLocX = 0;
    if ( m_LocX.IsKey() )
    {
        int nKey = m_LocX.GetNumber();
        nLocX = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nLocX = m_LocX.GetNumber();
    }

    int nLocY = 0;
    if ( m_LocY.IsKey() )
    {
        int nKey = m_LocY.GetNumber();
        nLocY = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nLocY = m_LocY.GetNumber();
    }

    int nQuestId = 0;
    if ( m_QuestId.IsKey() )
    {
        int nKey = m_QuestId.GetNumber();
        nQuestId = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nQuestId = m_QuestId.GetNumber();
    }

    FlyMapParam xFlyMapParam;
    xFlyMapParam.nMapId       = nMapId;
    xFlyMapParam.x            = nLocX;
    xFlyMapParam.y            = nLocY;
    xFlyMapParam.fDir         = m_fDir;
    xFlyMapParam.chFlyType    = m_chFlyType;
    xFlyMapParam.bCheckHeader = m_bCheckHeader;
    xFlyMapParam.m_nQuestID   = nQuestId;

    bool bResult = GetScriptInterface()->FlyToMap( xFlyMapParam );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

BOOL CScriptCmd_CallAllTeamPlayerFlyToMap::Create( WordParser* words )
{
    if( words->GetWordCount() != 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CallAllTeamPlayerFlyToMap create error, param count != 4" );
        return FALSE;
    }
    if( !words->IsNumber( 0 ) ||
        !words->IsNumber( 1 ) ||
        !words->IsNumber( 2 ) ||
        !words->IsNumber( 3 ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CallAllTeamPlayerFlyToMap create error, some param is not number" );
        return FALSE;
    }

    if( words->IsNumber( 0 ) )
    {
        m_nMapId = atoi( words->GetWord( 0 ) );
    }
    else
    {
        m_nMapId = GetScriptInterface()->GetMapIdByName( words->GetWord(0) );
    }

    m_ptLoc.x = atoi( words->GetWord( 1 ) );
    m_ptLoc.y = atoi( words->GetWord( 2 ) );

    int nAngle = atoi( words->GetWord( 3 ) );
    if (nAngle < -360)
        nAngle = -360;
    if (nAngle > 360)
        nAngle = 360;

    m_fDir = nAngle * PI / 180.f;

    return TRUE;
}

void CScriptCmd_CallAllTeamPlayerFlyToMap::Execute( CScriptVM* vm )
{
    bool bResult = GetScriptInterface()->CallAllTeamPlayerFlyToMap( m_nMapId, m_ptLoc.x, m_ptLoc.y, m_fDir );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_GetWeekKillNum::Create( WordParser* words )
{
    return TRUE;
}
void CScriptCmd_GetWeekKillNum::Execute( CScriptVM* vm )
{
	int num = GetScriptInterface()->GetWeekKillNum();
	CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber( num );
    GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    vm->NextIP();
}

BOOL CScriptCmd_GetAllKillNum::Create( WordParser* words )
{
    return TRUE;
}
void CScriptCmd_GetAllKillNum::Execute( CScriptVM* vm )
{
	int num =GetScriptInterface()->GetAllKillNum();
	CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber( num );
    GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    vm->NextIP();
}

BOOL CScriptCmd_GetSeriesKillNum::Create( WordParser* words )
{
    return TRUE;
}
void CScriptCmd_GetSeriesKillNum::Execute( CScriptVM* vm )
{
	int num =GetScriptInterface()->GetSeriesKillNum();
	CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber( num );
    GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    vm->NextIP();
}

// 广播
// BC count color aaaaaa%s $n
BOOL CScriptCmd_Broadcast::Create( WordParser* words )
{
    if( words->GetWordCount() < 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "BC create error." );
        return FALSE;
    }

    m_nType = 0;    // 广播类型, 0 = 本服务器广播     1 = 全世界广播
    int nIndex = 1;
    string strTemp = words->GetWord( 0 );
    if ( !WordParser::IsNumber( strTemp.c_str() ) )     //不是数字, 兼容以前的版本形式 ( bc zzzzzzZZZZZZZZ )
    {
        m_strMsg = strTemp;
    }
    else
    {
        m_nType  = atoi( strTemp.c_str() );
        m_strMsg = words->GetWord( 1 );
        nIndex = 2;
    }

    for ( int n = nIndex; n < words->GetWordCount(); ++n )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "BC create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strMsg.size()-1; n++ )
    {
        if ( m_strMsg[n] == '%' )
        {
            if ( m_strMsg[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "BC create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "BC create error");
        return FALSE;
    }
    return TRUE;
}

void CScriptCmd_Broadcast::Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, sizeof( szText ) - 1, m_strMsg.c_str(), vtVar );
    GetScriptInterface()->Broadcast( m_nType, szText );
    vm->NextIP();
}

BOOL CScriptCmd_Ask::Create( WordParser* words )
{
    if ( true)
    { // 使用字符串Id模式 ask 1
        if( words->GetWordCount() != 1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error, param count != 1" );
            return FALSE;
        }

        int nIndex = 0;
        const char* pWord = words->GetWord( 0 );
        if ( !pWord )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error" );
            return FALSE;
        }
        int nLen = strlen( pWord );
        if ( nLen <= 0 || nLen+nIndex >= eBufferLength-1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error" );
            return FALSE;
        }

        strncpy_s( m_szItems, sizeof(m_szItems), pWord, nLen );
    }
    else
    { // 使用字符串模式 ask quest yes no ask quest item0 item1 item2
        if( words->GetWordCount() < 2 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error, param count < 2" );
            return FALSE;
        }

        int nIndex = 0;
        for ( int n=0; n<words->GetWordCount(); n++ )
        {
            const char* pWord = words->GetWord(n);
            if ( !pWord )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error" );
                return FALSE;
            }
            int nLen = strlen( pWord );
            if ( nLen <= 0 || nLen+nIndex >= eBufferLength-1 )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ask create error" );
                return FALSE;
            }
            for ( int i=0; i<nLen; i++ )
            {
                m_szItems[nIndex] = pWord[i];
                if ( m_szItems[nIndex] == ' ' )
                {
                    m_szItems[nIndex] = '^';
                }
                nIndex++;
            }
            if ( n != words->GetWordCount()-1 )
            {
                m_szItems[nIndex] = ' ';
                nIndex++;
            }
        }
        m_szItems[nIndex] = 0;
   }
    return TRUE;
}

void CScriptCmd_Ask::Execute( CScriptVM* vm )
{
    GetScriptInterface()->Ask( m_nReturnKey, m_szItems );
    vm->NextIP();
    vm->Hangup();
}

//RemoveAllEquip
BOOL CScriptCmd_RemoveAllEquip::Create( WordParser* words )
{
    return TRUE; 
}

void CScriptCmd_RemoveAllEquip::Execute( CScriptVM* vm )
{   
    GetScriptInterface()->RemoveAllEquip( );
    vm->NextIP();
}

//SetBornPoint 2 45 45
BOOL CScriptCmd_SetBornPoint::Create( WordParser* words )
{
    m_dwMapID = atoi(words->GetWord( 0 ));
    m_iPosX      = atoi(words->GetWord( 1 ));
    m_iPosY   = atoi(words->GetWord( 2 ));
    return TRUE;
}

void CScriptCmd_SetBornPoint::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetBornPoint( m_dwMapID, m_iPosX, m_iPosY );
    vm->NextIP( );
}

//{ add by ^^
// HaveThisItem 小刀
BOOL CScriptCmd_HaveThisItem::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:HaveThisItem" );
        return FALSE;
    }
    strncpy(m_ItemName, words->GetWord( 0 ), sizeof(m_ItemName)-1);
    return TRUE;
}

void CScriptCmd_HaveThisItem::Execute( CScriptVM* vm )
{
    CScriptCmd__SetVar::Param    m_params[1];
    //
    int retNum = GetScriptInterface()->HaveThisItem( m_ItemName );
    m_params[0].SetNumber( retNum );
    //

    if ( m_nReturnKey != -1)
    {
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP( );
}

// RemoveThisItem 小刀 1
BOOL CScriptCmd_RemoveThisItem::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:RemoveThisItem" );
        return FALSE;
    }
    strncpy(m_ItemName, words->GetWord( 0 ), sizeof(m_ItemName)-1);
    m_ItemNumber = atoi( words->GetWord( 1 ) );
    //
    return TRUE;
}

void CScriptCmd_RemoveThisItem::Execute( CScriptVM* vm )
{
    GetScriptInterface()->RemoveThisItem( m_ItemName, m_ItemNumber );
    vm->NextIP( );
}

// IsThisItemEquipped 衣服
BOOL CScriptCmd_IsThisItemEquipped::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsThisItemEquipped" );
        return FALSE;
    }
    strncpy(m_ItemName, words->GetWord( 0 ), sizeof(m_ItemName)-1);
    return TRUE;
}

void CScriptCmd_IsThisItemEquipped::Execute( CScriptVM* vm )
{
    BOOL bEquipped = GetScriptInterface()->IsThisItemEquipped( m_ItemName );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( bEquipped );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP( );
}


BOOL CScriptCmd_ProcTimeStep::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ProcTimeStep" );
        return FALSE;
    }
    const char* szStringId = words->GetWord(0);
    if (WordParser::IsNumber(szStringId))
    {
        m_StringID.SetNumber( atoi(szStringId) );
        m_StringID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szStringId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ProcTimeStep");
            return FALSE;
        }
        m_StringID.SetNumber(nKey);
        m_StringID.SetIsKey(true);
    }

    const char* szTimeStep = words->GetWord(1);
    if (WordParser::IsNumber(szTimeStep))
    {
        m_TimeStep.SetNumber( atoi(szTimeStep) );
        m_TimeStep.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szTimeStep);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ProcTimeStep");
            return FALSE;
        }
        m_TimeStep.SetNumber(nKey);
        m_TimeStep.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_ProcTimeStep::Execute( CScriptVM* vm )
{
    int nStringId = 0;
    int nTimeStep = 0;
    if (m_StringID.IsKey())
    {
        int nKey = m_StringID.GetNumber();
        nStringId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nStringId = m_StringID.GetNumber();
    }

    if (m_TimeStep.IsKey())
    {
        int nKey = m_TimeStep.GetNumber();
        nTimeStep = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nTimeStep = m_TimeStep.GetNumber();
    }
    GetScriptInterface()->ProcTimeStep( nStringId, nTimeStep );
    vm->NextIP( );
}



// IsThisSkillActived 技能 2
BOOL CScriptCmd_IsThisSkillActived::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsThisSkillActived" );
        return FALSE;
    }
    //
    //ustSkillItemID = atoi( words->GetWord( 0 ) );
    //ustSkillLevel = atoi( words->GetWord( 1 ) );
    const char* szSkillId = words->GetWord(0);
    if (WordParser::IsNumber(szSkillId))
    {
        m_SkillId.SetNumber( atoi(szSkillId) );
        m_SkillId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsThisSkillActived");
            return FALSE;
        }
        m_SkillId.SetNumber(nKey);
        m_SkillId.SetIsKey(true);
    }

    const char* szSkillLevel = words->GetWord(1);
    if (WordParser::IsNumber(szSkillLevel))
    {
        m_SkillLevel.SetNumber( atoi(szSkillLevel) );
        m_SkillLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillLevel);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsThisSkillActived");
            return FALSE;
        }
        m_SkillLevel.SetNumber(nKey);
        m_SkillLevel.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_IsThisSkillActived::Execute( CScriptVM* vm )
{
    int nSkillId = 0;
    int nSkillLevel = 0;
    if (m_SkillId.IsKey())
    {
        int nKey = m_SkillId.GetNumber();
        nSkillId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nSkillId = m_SkillId.GetNumber();
    }

    if (m_SkillLevel.IsKey())
    {
        int nKey = m_SkillLevel.GetNumber();
        nSkillLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nSkillLevel = m_SkillLevel.GetNumber();
    }
    BOOL bActived = GetScriptInterface()->IsThisSkillActived( nSkillId, nSkillLevel );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( bActived );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP( );
}

// skillshop 1000 1001 1002
SCRIPT_BEGIN( teachskill )
virtual BOOL Create( WordParser* words )
{
    for( int i = 0; i < words->GetWordCount(); i++ )
    {
        vectorSkill.push_back( atoi( words->GetWord( i ) ) );
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->TeashSkill( vectorSkill );
    vm->NextIP();
}

SCRIPT_PARAM
std::vector<int> vectorSkill;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( AddSkill )
virtual BOOL Create( WordParser* words )
{
    if (words->GetWordCount() != 2 && words->GetWordCount() != 3)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddSkill error" );
        return FALSE;
    }

    const char* szSkillId = words->GetWord(0);
    if (WordParser::IsNumber(szSkillId))
    {
        m_SkillId.SetNumber( atoi(szSkillId) );
        m_SkillId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddSkill");
            return FALSE;
        }
        m_SkillId.SetNumber(nKey);
        m_SkillId.SetIsKey(true);
    }
    const char* szSkillLevel = words->GetWord(1);
    if ( WordParser::IsNumber(szSkillLevel) )
    {
        m_SkillLevel.SetNumber( atoi(szSkillLevel) );
        m_SkillLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillLevel);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddSkill");
            return FALSE;
        }
        m_SkillLevel.SetNumber(nKey);
        m_SkillLevel.SetIsKey(true);
    }

    if( words->GetWordCount() == 2 )
    {
        bMessageDialog = true;
        return TRUE;
    }

    if( words->GetWordCount() == 3 )
    {
        bMessageDialog = atoi( words->GetWord(2) );
        return TRUE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSkillId = 0;
    if ( m_SkillId.IsKey() )
    {
        int nKey = m_SkillId.GetNumber();
        nSkillId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nSkillId = m_SkillId.GetNumber();
    }

    int nSkillLevel = 0;
    if ( m_SkillLevel.IsKey() )
    {
        int nKey = m_SkillLevel.GetNumber();
        nSkillLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nSkillLevel = m_SkillLevel.GetNumber();
    }

    GetScriptInterface()->AddSkill( nSkillId, nSkillLevel,bMessageDialog );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_SkillId;
CScriptCmd__SetVar::Param m_SkillLevel;
bool   bMessageDialog;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( AddXinFa )
virtual BOOL Create( WordParser* words )
{
    if ( words->GetWordCount() != 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddXinFa" );
        return FALSE;
    }

    const char* szXinFaId = words->GetWord(0);
    if (WordParser::IsNumber(szXinFaId))
    {
        m_XinFaId.SetNumber( atoi(szXinFaId) );
        m_XinFaId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szXinFaId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddXinFa");
            return FALSE;
        }
        m_XinFaId.SetNumber(nKey);
        m_XinFaId.SetIsKey(true);
    }
    const char* szXinFaLevel = words->GetWord(1);
    if ( WordParser::IsNumber(szXinFaLevel) )
    {
        m_XinFaLevel.SetNumber( atoi(szXinFaLevel) );
        m_XinFaLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szXinFaLevel);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddXinFa");
            return FALSE;
        }
        m_XinFaLevel.SetNumber(nKey);
        m_XinFaLevel.SetIsKey(true);
    }

    const char* szCheck = words->GetWord(2);
    if ( WordParser::IsNumber(szCheck) )
    {
        m_Check.SetNumber( atoi(szCheck) );
        m_Check.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szCheck);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddXinFa");
            return FALSE;
        }
        m_Check.SetNumber(nKey);
        m_Check.SetIsKey(true);
    }

    const char* szShowDlg = words->GetWord(3);
    if ( WordParser::IsNumber(szShowDlg) )
    {
        m_ShowDialog.SetNumber( atoi(szShowDlg) );
        m_ShowDialog.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szShowDlg);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddXinFa");
            return FALSE;
        }
        m_ShowDialog.SetNumber(nKey);
        m_ShowDialog.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nXinFaId = 0;
    if ( m_XinFaId.IsKey() )
    {
        int nKey = m_XinFaId.GetNumber();
        nXinFaId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nXinFaId = m_XinFaId.GetNumber();
    }

    int nXinFaLevel = 0;
    if ( m_XinFaLevel.IsKey() )
    {
        int nKey = m_XinFaLevel.GetNumber();
        nXinFaLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nXinFaLevel = m_XinFaLevel.GetNumber();
    }

    bool bCheck = 0;
    if ( m_Check.IsKey() )
    {
        int nKey = m_Check.GetNumber();
        bCheck = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        bCheck = m_Check.GetNumber();
    }

    bool bShowDlg = 0;
    if ( m_ShowDialog.IsKey() )
    {
        int nKey = m_ShowDialog.GetNumber();
        bShowDlg = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        bShowDlg = m_ShowDialog.GetNumber();
    }

    GetScriptInterface()->AddXinFa( nXinFaId, nXinFaLevel, bCheck, bShowDlg );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_XinFaId;
CScriptCmd__SetVar::Param m_XinFaLevel;
CScriptCmd__SetVar::Param m_Check;
CScriptCmd__SetVar::Param m_ShowDialog;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( GMAddXinFa )
virtual BOOL Create( WordParser* words )
{
    if ( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GMAddXinFa" );
        return FALSE;
    }

    const char* szXinFaId = words->GetWord(0);
    if (WordParser::IsNumber(szXinFaId))
    {
        m_XinFaId.SetNumber( atoi(szXinFaId) );
        m_XinFaId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szXinFaId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GMAddXinFa");
            return FALSE;
        }
        m_XinFaId.SetNumber(nKey);
        m_XinFaId.SetIsKey(true);
    }
    const char* szXinFaLevel = words->GetWord(1);
    if ( WordParser::IsNumber(szXinFaLevel) )
    {
        m_XinFaLevel.SetNumber( atoi(szXinFaLevel) );
        m_XinFaLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szXinFaLevel);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GMAddXinFa");
            return FALSE;
        }
        m_XinFaLevel.SetNumber(nKey);
        m_XinFaLevel.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nXinFaId = 0;
    if ( m_XinFaId.IsKey() )
    {
        int nKey = m_XinFaId.GetNumber();
        nXinFaId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nXinFaId = m_XinFaId.GetNumber();
    }

    int nXinFaLevel = 0;
    if ( m_XinFaLevel.IsKey() )
    {
        int nKey = m_XinFaLevel.GetNumber();
        nXinFaLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nXinFaLevel = m_XinFaLevel.GetNumber();
    }

    GetScriptInterface()->GMAddXinFa( nXinFaId, nXinFaLevel );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_XinFaId;
CScriptCmd__SetVar::Param m_XinFaLevel;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( GetSkillLevel )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetSkillLevel error" );
        return FALSE;
    }
    //m_nSkillId = atoi( words->GetWord(0) );
    const char* szSkillId = words->GetWord(0);
    if ( WordParser::IsNumber(szSkillId) )
    {
        m_SkillId.SetNumber( atoi(szSkillId) );
        m_SkillId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetSkillLevel");
            return FALSE;
        }
        m_SkillId.SetNumber(nKey);
        m_SkillId.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSkillId = 0;
    if (m_SkillId.IsKey())
    {
        int nKey = m_SkillId.GetNumber();
        nSkillId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nSkillId = m_SkillId.GetNumber();
    }
    
    int level = GetScriptInterface()->GetSkillLevel( nSkillId);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( level );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
//int    m_nSkillId;
CScriptCmd__SetVar::Param m_SkillId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( GetXinFaLevel )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetXinFaLevel error" );
        return FALSE;
    }
    
    const char* szXinFaId = words->GetWord(0);
    if ( WordParser::IsNumber(szXinFaId) )
    {
        m_XinFaId.SetNumber( atoi(szXinFaId) );
        m_XinFaId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szXinFaId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetXinFaLevel");
            return FALSE;
        }
        m_XinFaId.SetNumber(nKey);
        m_XinFaId.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nXinFaId = 0;
    if (m_XinFaId.IsKey())
    {
        int nKey = m_XinFaId.GetNumber();
        nXinFaId = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nXinFaId = m_XinFaId.GetNumber();
    }

    int level = GetScriptInterface()->GetXinFaLevel( nXinFaId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( level );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_XinFaId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( GetXinFaMaxLevel )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetXinFaMaxLevel error" );
        return FALSE;
    }
    
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int level = GetScriptInterface()->GetXinFaMaxLevel( );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( level );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// &var = CanLearnSkill 1000 1
//
SCRIPT_BEGIN( CanLearnSkill )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CanLearnSkill" );
        return FALSE;
    }
    //
    //m_nSkillId = atoi( words->GetWord( 0 ) );
    //m_nSkillLevel = atoi( words->GetWord( 1 ) );
    const char* szSkillId = words->GetWord(0);
    if (WordParser::IsNumber(szSkillId))
    {
        m_SkillId.SetNumber( atoi(szSkillId) );
        m_SkillId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:CanLearnSkill");
            return FALSE;
        }
        m_SkillId.SetNumber(nKey);
        m_SkillId.SetIsKey(true);
    }

    const char* szSkillLevel = words->GetWord(1);
    if (WordParser::IsNumber(szSkillLevel))
    {
        m_SkillLevel.SetNumber( atoi(szSkillLevel) );
        m_SkillLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szSkillLevel);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:CanLearnSkill");
            return FALSE;
        }
        m_SkillLevel.SetNumber(nKey);
        m_SkillLevel.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSkillId = 0;
    int nSkillLevel = 0;
    if (m_SkillId.IsKey())
    {
        int nKey = m_SkillId.GetNumber();
        nSkillId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nSkillId = m_SkillId.GetNumber();
    }

    if (m_SkillLevel.IsKey())
    {
        int nKey = m_SkillLevel.GetNumber();
        nSkillLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nSkillLevel = m_SkillLevel.GetNumber();
    }
    int result = GetScriptInterface()->CanLearnSkill( nSkillId, nSkillLevel );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nSkillId;
//int m_nSkillLevel;
CScriptCmd__SetVar::Param m_SkillId;
CScriptCmd__SetVar::Param m_SkillLevel;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
// add_item 大刀 1
SCRIPT_BEGIN( add_item )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item error" );
        return FALSE;
    }

    HelperFunc::SafeNCpy( szItemname, words->GetWord( 0 ), dr_MaxItemName );
    const char* szWord = words->GetWord( 1 );
    if( WordParser::IsNumber( szWord ) )
    {
        m_stParam.SetNumber( atoi( szWord ) );
        m_stParam.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item error" );
            return FALSE;
        }
        m_stParam.SetNumber( nKey );
        m_stParam.SetIsKey( true );
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = 0;
    if ( m_stParam.IsKey() )
    {
        int nKey = m_stParam.GetNumber();
        nCount = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nCount = m_stParam.GetNumber();
    }
    if ( nCount <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:add_item %s %d",szItemname, nCount );
        return;
    }
    //
    GetScriptInterface()->AddItem( szItemname, nCount );
    //
    vm->NextIP();
}

SCRIPT_PARAM
char    szItemname[dr_MaxItemName];
//short stItemCount;
CScriptCmd__SetVar::Param    m_stParam;
SCRIPT_END


SCRIPT_BEGIN( add_item_byid )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 4 && words->GetWordCount() != 2 && words->GetWordCount() != 6 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
        return FALSE;
    }

	m_ParamSum = words->GetWordCount();
    // ItemId
    const char* szItemid = words->GetWord( 0 );
    if( WordParser::IsNumber( szItemid ) )
    {
        m_stParamid.SetNumber( atoi( szItemid ) );
        m_stParamid.SetIsKey( false );
    }
    else
    {
        int nKeyId = GetScriptVarMgr()->GetVarId( szItemid );
        if ( nKeyId == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
            return FALSE;
        }
        m_stParamid.SetNumber( nKeyId );
        m_stParamid.SetIsKey( true );
    }
    // Number
    const char* szWord = words->GetWord( 1 );
    if( WordParser::IsNumber( szWord ) )
    {
        m_stParamCount.SetNumber( atoi( szWord ) );
        m_stParamCount.SetIsKey( false );
    }
    else
    {
        int nKeyCount = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKeyCount == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
            return FALSE;
        }
        m_stParamCount.SetNumber( nKeyCount );
        m_stParamCount.SetIsKey( true );
    }

	// BindBool
	if(words->GetWordCount() > 2)
	{
		const char* szBindBool = words->GetWord( 2 );
		if( WordParser::IsNumber( szBindBool ) )
		{
			m_stParamUnBindBool.SetNumber( atoi( szBindBool ) );
			m_stParamUnBindBool.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindBool );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamUnBindBool.SetNumber( nKeyCount );
			m_stParamUnBindBool.SetIsKey( true );
		}

		const char* szBindSum = words->GetWord( 3 );
		if( WordParser::IsNumber( szBindSum ) )
		{
			m_stParamUnBindSum.SetNumber( atoi( szBindSum ) );
			m_stParamUnBindSum.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindSum );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamUnBindSum.SetNumber( nKeyCount );
			m_stParamUnBindSum.SetIsKey( true );
		}
	}

	if ( words->GetWordCount() > 4 )
	{
		const char* szSysType = words->GetWord( 4 );
		if( WordParser::IsNumber( szSysType ) )
		{
			m_stParamSysType.SetNumber( atoi( szSysType ) );
			m_stParamSysType.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szSysType );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamSysType.SetNumber( nKeyCount );
			m_stParamSysType.SetIsKey( true );
		}

		const char* szTypeID = words->GetWord( 5 );
		if( WordParser::IsNumber( szTypeID ) )
		{
			m_stParamTypeID.SetNumber( atoi( szTypeID ) );
			m_stParamTypeID.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szTypeID );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamTypeID.SetNumber( nKeyCount );
			m_stParamTypeID.SetIsKey( true );
		}
	}
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = 0;
    unsigned short ustItemID = InvalidLogicNumber;

	bool unBindBool = false;
	unsigned short unBindSum = 0;

	bool bBound = true;
	int nSysType = 0;
	int nTypeID = -1;

    if (m_stParamid.IsKey())
    {
        int nkeyId = m_stParamid.GetNumber();
        ustItemID = GetScriptInterface()->GetVar(nkeyId);
    }
    else
    {
        ustItemID = m_stParamid.GetNumber();
    }

    if (ustItemID == InvalidLogicNumber)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:add_item_byid !");
        return;
    }

    if ( m_stParamCount.IsKey() )
    {
        int nKey = m_stParamCount.GetNumber();
        nCount = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nCount = m_stParamCount.GetNumber();
    }
    if ( nCount <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:add_item_byid %d %d",
            ustItemID, nCount );
        return;
    }
	if(m_ParamSum > 2)
	{
		if ( m_stParamUnBindBool.IsKey() )
		{
			int nKey = m_stParamUnBindBool.GetNumber();
			unBindBool = GetScriptInterface()->GetVar( nKey ) == 1 ? true:false;
		}
		else
		{
			unBindBool = m_stParamUnBindBool.GetNumber()==1?true:false;
		}

		if ( m_stParamUnBindSum.IsKey() )
		{
			int nKey = m_stParamUnBindSum.GetNumber();
			unBindSum = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			unBindSum = m_stParamUnBindSum.GetNumber();
		}
		if(unBindSum == 0xFFFF && unBindBool)
			unBindBool = false;
	}

	if (m_ParamSum > 4)
	{
		if ( m_stParamSysType.IsKey() )
		{
			int nKey = m_stParamSysType.GetNumber();
			nSysType = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nSysType = m_stParamSysType.GetNumber();
		}

		if ( m_stParamTypeID.IsKey() )
		{
			int nKey = m_stParamTypeID.GetNumber();
			nTypeID = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nTypeID = m_stParamTypeID.GetNumber();
		}
	}
    GetScriptInterface()->AddItemByItemid( ustItemID, nCount ,true,unBindBool,unBindSum, nSysType, nTypeID);
    vm->NextIP();
}

SCRIPT_PARAM
//unsigned short ustItemID;
CScriptCmd__SetVar::Param    m_stParamid;
CScriptCmd__SetVar::Param    m_stParamCount;
CScriptCmd__SetVar::Param    m_stParamUnBindBool;
CScriptCmd__SetVar::Param    m_stParamUnBindSum;
CScriptCmd__SetVar::Param    m_stParamSysType;
CScriptCmd__SetVar::Param    m_stParamTypeID;
short						 m_ParamSum;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
SCRIPT_BEGIN( AddUnboundItemById )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 4 && words->GetWordCount() != 2 && words->GetWordCount() != 6 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddUnboundItemById error" );
        return FALSE;
    }
	m_ParamSum = words->GetWordCount();
    // ItemId
    const char* szItemid = words->GetWord( 0 );
    if( WordParser::IsNumber( szItemid ) )
    {
        m_stParamid.SetNumber( atoi( szItemid ) );
        m_stParamid.SetIsKey( false );
    }
    else
    {
        int nKeyId = GetScriptVarMgr()->GetVarId( szItemid );
        if ( nKeyId == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddUnboundItemById error" );
            return FALSE;
        }
        m_stParamid.SetNumber( nKeyId );
        m_stParamid.SetIsKey( true );
    }
    // Number
    const char* szWord = words->GetWord( 1 );
    if( WordParser::IsNumber( szWord ) )
    {
        m_stParamCount.SetNumber( atoi( szWord ) );
        m_stParamCount.SetIsKey( false );
    }
    else
    {
        int nKeyCount = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKeyCount == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddUnboundItemById error" );
            return FALSE;
        }
        m_stParamCount.SetNumber( nKeyCount );
        m_stParamCount.SetIsKey( true );
    }


	// BindBool
   // BindBool
	if(words->GetWordCount() > 2)
	{
		const char* szBindBool = words->GetWord( 2 );
		if( WordParser::IsNumber( szBindBool ) )
		{
			m_stParamUnBindBool.SetNumber( atoi( szBindBool ) );
			m_stParamUnBindBool.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindBool );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddUnboundItemById error" );
				return FALSE;
			}
			m_stParamUnBindBool.SetNumber( nKeyCount );
			m_stParamUnBindBool.SetIsKey( true );
		}

		const char* szBindSum = words->GetWord( 3 );
		if( WordParser::IsNumber( szBindSum ) )
		{
			m_stParamUnBindSum.SetNumber( atoi( szBindSum ) );
			m_stParamUnBindSum.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindSum );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddUnboundItemById error" );
				return FALSE;
			}
			m_stParamUnBindSum.SetNumber( nKeyCount );
			m_stParamUnBindSum.SetIsKey( true );
		}
	}

	if ( words->GetWordCount() > 4 )
	{
		const char* szSysType = words->GetWord( 4 );
		if( WordParser::IsNumber( szSysType ) )
		{
			m_stParamSysType.SetNumber( atoi( szSysType ) );
			m_stParamSysType.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szSysType );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamSysType.SetNumber( nKeyCount );
			m_stParamSysType.SetIsKey( true );
		}

		const char* szTypeID = words->GetWord( 5 );
		if( WordParser::IsNumber( szTypeID ) )
		{
			m_stParamTypeID.SetNumber( atoi( szTypeID ) );
			m_stParamTypeID.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szTypeID );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamTypeID.SetNumber( nKeyCount );
			m_stParamTypeID.SetIsKey( true );
		}
	}

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = 0;
    uint16 ustItemID = InvalidLogicNumber;
    bool bIsBound = true;


	bool unBindBool = false;
	unsigned short unBindSum = 0;

	int nSysType = 0;
	int nTypeID = -1;

    if (m_stParamid.IsKey())
    {
        int nkeyId = m_stParamid.GetNumber();
        ustItemID = GetScriptInterface()->GetVar(nkeyId);
    }
    else
    {
        ustItemID = m_stParamid.GetNumber();
    }

    if (ustItemID == InvalidLogicNumber)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddUnboundItemById !");
        return;
    }

    if ( m_stParamCount.IsKey() )
    {
        int nKey = m_stParamCount.GetNumber();
        nCount = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nCount = m_stParamCount.GetNumber();
    }

    if ( nCount <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddUnboundItemById %s %d",
            ustItemID, nCount );
        return;
    }
	if(m_ParamSum > 2)
	{
		if ( m_stParamUnBindBool.IsKey() )
		{
			int nKey = m_stParamUnBindBool.GetNumber();
			unBindBool = GetScriptInterface()->GetVar( nKey ) == 1 ? true:false;
		}
		else
		{
			unBindBool = m_stParamUnBindBool.GetNumber()==1?true:false;
		}

		if ( m_stParamUnBindSum.IsKey() )
		{
			int nKey = m_stParamUnBindSum.GetNumber();
			unBindSum = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			unBindSum = m_stParamUnBindSum.GetNumber();
		}
		if(unBindSum == 0xFFFF && unBindBool)
			unBindBool = false;
	}

	if (m_ParamSum > 4)
	{
		if ( m_stParamSysType.IsKey() )
		{
			int nKey = m_stParamSysType.GetNumber();
			nSysType = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nSysType = m_stParamSysType.GetNumber();
		}

		if ( m_stParamTypeID.IsKey() )
		{
			int nKey = m_stParamTypeID.GetNumber();
			nTypeID = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nTypeID = m_stParamTypeID.GetNumber();
		}
	}

    GetScriptInterface()->AddItemByItemid( ustItemID, nCount, false ,unBindBool,unBindSum, nSysType, nTypeID);
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
CScriptCmd__SetVar::Param    m_stParamCount;
CScriptCmd__SetVar::Param    m_stParamUnBindBool;
CScriptCmd__SetVar::Param    m_stParamUnBindSum;
CScriptCmd__SetVar::Param    m_stParamSysType;
CScriptCmd__SetVar::Param    m_stParamTypeID;
short						 m_ParamSum;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
SCRIPT_BEGIN(AddEquipByItemId)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() == 3 )
    {
        nItemId     = atoi( words->GetWord(0) ); 
        bStarRandom = atoi( words->GetWord(1) ); 
        nStarLevel  = atoi( words->GetWord(2) ); 
		bIsBound = true;
		bChangeBound = false;
		nUnBindeSum = 0;
		nSysType = 0;
		nTypeID = -1;
        return TRUE;
    }

    if( words->GetWordCount() == 4 )
    {
        nItemId     = atoi( words->GetWord(0) ); 
        bStarRandom = atoi( words->GetWord(1) ); 
        nStarLevel  = atoi( words->GetWord(2) ); 
        bIsBound    = atoi( words->GetWord(3) ); 
		bChangeBound = false;
		nUnBindeSum = 0;
		nSysType = 0;
		nTypeID = -1;
        return TRUE;
    }

	if ( words->GetWordCount() == 6 )
	{
		nItemId     = atoi( words->GetWord(0) ); 
		bStarRandom = atoi( words->GetWord(1) ); 
		nStarLevel  = atoi( words->GetWord(2) ); 
		bIsBound    = atoi( words->GetWord(3) ); 
		bChangeBound = atoi( words->GetWord(4));
		nUnBindeSum = atoi( words->GetWord(5));
		nSysType = 0;
		nTypeID = -1;
		return TRUE;
	}

	if ( words->GetWordCount() == 8 )
	{
		nItemId     = atoi( words->GetWord(0) ); 
		bStarRandom = atoi( words->GetWord(1) ); 
		nStarLevel  = atoi( words->GetWord(2) ); 
		bIsBound    = atoi( words->GetWord(3) ); 
		bChangeBound = atoi( words->GetWord(4));
		nUnBindeSum = atoi( words->GetWord(5));
		nSysType = atoi( words->GetWord(6));
		nTypeID = atoi( words->GetWord(7));
		return TRUE;
	}

    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[AddEquipByItemId] " );
    return FALSE;    
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->AddEquipByItemId( nItemId, bStarRandom, nStarLevel, bIsBound, bChangeBound, nUnBindeSum, nSysType, nTypeID );

    pVM->NextIP();
}
SCRIPT_PARAM
int   nItemId;
bool  bStarRandom;
int16 nStarLevel;
bool  bIsBound;
bool  bChangeBound;
unsigned short nUnBindeSum;
int   nSysType;
int   nTypeID;
SCRIPT_END

//是否有这个称号
BOOL CScriptCmd_HaveThisTitle::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:HaveThisTitle" );
        return FALSE;
    }

    const char* szTitleId = words->GetWord( 0 );
    if( WordParser::IsNumber( szTitleId ) )
    {
        m_TitleID.SetNumber( atoi( szTitleId ) );
        m_TitleID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szTitleId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "HaveThisTitle error" );
            return FALSE;
        }
        m_TitleID.SetNumber(nKey);
        m_TitleID.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_HaveThisTitle::Execute( CScriptVM* vm )
{
    int nTitleId = 0;
    if ( m_TitleID.IsKey() )
    {
        int nKey = m_TitleID.GetNumber();
        nTitleId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nTitleId = m_TitleID.GetNumber();
    }
    if ( nTitleId == 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:HaveThisTitle !");
        return;
    }

    int retNum = GetScriptInterface()->HaveThisTitle( nTitleId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP( );
}

//添加配方
SCRIPT_BEGIN( AddRecipe )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "addrecipe error" );
        return FALSE;
    }
    const char* szRecipeID = words->GetWord( 0 );

    if( WordParser::IsNumber( szRecipeID ) )
    {
        m_stParamid.SetNumber( atoi( szRecipeID ) );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szRecipeID);
        if ( nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "addrecipe error" );
            return FALSE;
        }
        m_stParamid.SetNumber(nKey);
        m_stParamid.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    unsigned short ustRecipeID = 0;
    if ( m_stParamid.IsKey() )
    {
        int nKey = m_stParamid.GetNumber();
        ustRecipeID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        ustRecipeID = m_stParamid.GetNumber();
    }
    if (ustRecipeID == 0)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:addrecipe !");
        return;
    }
    GetScriptInterface()->AddRecipe( ustRecipeID );
    vm->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
SCRIPT_BEGIN( HaveRecipe )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "HaveRecipe error" );
        return FALSE;
    }
    const char* szRecipeID = words->GetWord( 0 );

    if( WordParser::IsNumber( szRecipeID ) )
    {
        m_stParamid.SetNumber( atoi( szRecipeID ) );
    }
    else
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "HaveRecipe error" );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = 0;
    uint16 nRecipeID =  m_stParamid.GetNumber();

    if (nRecipeID == 0)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:HaveRecipe !");
        return;
    }

    //
    int retKey = GetScriptInterface()->HaveRecipe( nRecipeID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( retKey );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
SCRIPT_END


//添加称号
SCRIPT_BEGIN( add_title )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_title error" );
        return FALSE;
    }
    const char* szTitleId = words->GetWord( 0 );

    if( WordParser::IsNumber( szTitleId ) )
    {
        m_stParamid.SetNumber( atoi( szTitleId ) );
        m_stParamid.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szTitleId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_title error" );
            return FALSE;
        }
        m_stParamid.SetNumber(nKey);
        m_stParamid.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    unsigned short ustTitleID = 0;

    if ( m_stParamid.IsKey() )
    {
        int nKey = m_stParamid.GetNumber();
        ustTitleID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        ustTitleID = m_stParamid.GetNumber();
    }

    if (ustTitleID == 0)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:add_title");
        return;
    }
   
    GetScriptInterface()->AddTitle( ustTitleID );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
SCRIPT_END

//删除称号
SCRIPT_BEGIN( remove_title )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "remove_title error" );
        return FALSE;
    }
    const char* szTitleId = words->GetWord( 0 );

    if( WordParser::IsNumber( szTitleId ) )
    {
        m_stParamid.SetNumber( atoi( szTitleId ) );
        m_stParamid.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szTitleId);
        if ( nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "remove_title error" );
            return FALSE;
        }
        m_stParamid.SetNumber(nKey);
        m_stParamid.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    unsigned short ustTitleID = 0;


    if ( m_stParamid.IsKey() )
    {
        int nKey = m_stParamid.GetNumber();
        ustTitleID = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        ustTitleID = m_stParamid.GetNumber();
    }
    if (ustTitleID == 0)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:remove_title !");
        return;
    }
    GetScriptInterface()->RemoveTitle( ustTitleID );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
SCRIPT_END


SCRIPT_BEGIN( AddItemInWorld )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 && words->GetWordCount() != 4 && words->GetWordCount() != 6 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddItemInWorld" );
        return FALSE;
    }

	m_ParamSum = words->GetWordCount();
    const char* szItemid = words->GetWord( 0 );
    const char* szWord   = words->GetWord( 1 );

    if( WordParser::IsNumber( szItemid ) )
    {
        m_stParamid.SetNumber( atoi( szItemid ) );
        m_stParamid.SetIsKey( false );
        
        if( WordParser::IsNumber( szWord ) )
        {
            m_stParamCount.SetNumber( atoi( szWord ) );
            m_stParamCount.SetIsKey( false );
        }
        else
        {
            int nKeyCount = GetScriptVarMgr()->GetVarId( szWord );
            if ( nKeyCount == -1 )
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddItemInWorld error" );
                return FALSE;
            }
            m_stParamCount.SetNumber( nKeyCount );
            m_stParamCount.SetIsKey( true );
        }
    }
    else
    {
        int nKeyId = GetScriptVarMgr()->GetVarId( szItemid );
        if ( nKeyId == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddItemInWorld error" );
            return FALSE;
        }
        m_stParamid.SetNumber( nKeyId );
        m_stParamid.SetIsKey( true );
    }

	// BindBool
	if(words->GetWordCount() > 2)
	{
		const char* szBindBool = words->GetWord( 2 );
		if( WordParser::IsNumber( szBindBool ) )
		{
			m_stParamUnBindBool.SetNumber( atoi( szBindBool ) );
			m_stParamUnBindBool.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindBool );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamUnBindBool.SetNumber( nKeyCount );
			m_stParamUnBindBool.SetIsKey( true );
		}

		const char* szBindSum = words->GetWord( 3 );
		if( WordParser::IsNumber( szBindSum ) )
		{
			m_stParamUnBindSum.SetNumber( atoi( szBindSum ) );
			m_stParamUnBindSum.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szBindSum );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamUnBindSum.SetNumber( nKeyCount );
			m_stParamUnBindSum.SetIsKey( true );
		}
	}

	if ( words->GetWordCount() > 4 )
	{
		const char* szSysType = words->GetWord( 4 );
		if( WordParser::IsNumber( szSysType ) )
		{
			m_stParamSysType.SetNumber( atoi( szSysType ) );
			m_stParamSysType.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szSysType );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamSysType.SetNumber( nKeyCount );
			m_stParamSysType.SetIsKey( true );
		}

		const char* szTypeID = words->GetWord( 5 );
		if( WordParser::IsNumber( szTypeID ) )
		{
			m_stParamTypeID.SetNumber( atoi( szTypeID ) );
			m_stParamTypeID.SetIsKey( false );
		}
		else
		{
			int nKeyCount = GetScriptVarMgr()->GetVarId( szTypeID );
			if ( nKeyCount == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "add_item_byid error" );
				return FALSE;
			}
			m_stParamTypeID.SetNumber( nKeyCount );
			m_stParamTypeID.SetIsKey( true );
		}
	}
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = 0;
    unsigned short ustItemID = InvalidLogicNumber;

	bool unBindBool = false;
	unsigned short unBindSum = 0;

	int nSysType = 0;
	int nTypeID = -1;

    if (m_stParamid.IsKey())
    {
        int nkeyId = m_stParamid.GetNumber();
        ustItemID = GetScriptInterface()->GetVar(nkeyId);
    }
    else
    {
        ustItemID = m_stParamid.GetNumber();
    }

    if (ustItemID == InvalidLogicNumber)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddItemInWorld !");
        return;
    }

    if ( m_stParamCount.IsKey() )
    {
        int nKey = m_stParamCount.GetNumber();
        nCount = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nCount = m_stParamCount.GetNumber();
    }
    if ( nCount <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddItemInWolrdById %s %d",
            ustItemID, nCount );
        return;
    }

	if(m_ParamSum > 2)
	{
		if ( m_stParamUnBindBool.IsKey() )
		{
			int nKey = m_stParamUnBindBool.GetNumber();
			unBindBool = GetScriptInterface()->GetVar( nKey ) == 1 ? true:false;
		}
		else
		{
			unBindBool = m_stParamUnBindBool.GetNumber()==1?true:false;
		}

		if ( m_stParamUnBindSum.IsKey() )
		{
			int nKey = m_stParamUnBindSum.GetNumber();
			unBindSum = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			unBindSum = m_stParamUnBindSum.GetNumber();
		}
		if(unBindSum == 0xFFFF && unBindBool)
			unBindBool = false;
	}

	if (m_ParamSum > 4)
	{
		if ( m_stParamSysType.IsKey() )
		{
			int nKey = m_stParamSysType.GetNumber();
			nSysType = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nSysType = m_stParamSysType.GetNumber();
		}

		if ( m_stParamTypeID.IsKey() )
		{
			int nKey = m_stParamTypeID.GetNumber();
			nTypeID = GetScriptInterface()->GetVar( nKey );
		}
		else
		{
			nTypeID = m_stParamTypeID.GetNumber();
		}
	}
    GetScriptInterface()->AddItemInWorld( ustItemID, nCount, unBindBool, unBindSum, nSysType, nTypeID );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param    m_stParamid;
CScriptCmd__SetVar::Param    m_stParamCount;
CScriptCmd__SetVar::Param    m_stParamUnBindBool;
CScriptCmd__SetVar::Param    m_stParamUnBindSum;
CScriptCmd__SetVar::Param    m_stParamSysType;
CScriptCmd__SetVar::Param    m_stParamTypeID;
short						 m_ParamSum;
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
//
// cast_quest 3000
//SCRIPT_BEGIN( cast_quest )
//virtual BOOL Create( WordParser* words )
//{
//    if( words->GetWordCount() < 2 )
//    {
//        GetScriptInterface()->Printf( "cast quest failed" );
//        return FALSE;
//    }
//
//    nQuestId = atoi( words->GetWord( 1 ) );
//    if( nQuestId < dr_MinQuestId ||
//        nQuestId > dr_MaxQuestId )
//        return FALSE;
//    
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* vm )
//{
//    GetScriptInterface()->Quest_CastQuest( nQuestId );
//    //
//    vm->NextIP();
//}
//
//SCRIPT_PARAM
//int nQuestId;
//SCRIPT_END


////////////////////////////////////////////////////////////////////////////
////
//// get_quest 3000
//SCRIPT_BEGIN( get_quest )
//virtual BOOL Create( WordParser* words )
//{
//    if( words->GetWordCount() < 2 )
//    {
//        GetScriptInterface()->Printf( "cast quest failed" );
//        return FALSE;
//    }
//
//    nQuestId = atoi( words->GetWord( 1 ) );
//    if( nQuestId < dr_MinQuestId ||
//        nQuestId > dr_MaxQuestId )
//        return FALSE;
//
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* vm )
//{
//    GetScriptInterface()->Quest_GetQuest( nQuestId );
//    //
//    vm->NextIP();
//}
//
//SCRIPT_PARAM
//int nQuestId;
//SCRIPT_END

////////////////////////////////////////////////////////////////////////////
////
//// cancel_quest 3000
SCRIPT_BEGIN( cancel_quest )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:cancel_quest" );
        return FALSE;
    }

    nQuestId = atoi( words->GetWord( 0 ) );
    if( nQuestId < dr_MinQuestId ||
        nQuestId > dr_MaxQuestId )
        return FALSE;

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->Quest_CancelQuest( nQuestId );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int nQuestId;
SCRIPT_END

////////////////////////////////////////////////////////////////////////////
////
//// done_quest 3000
SCRIPT_BEGIN( DoneQuest )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:DoneQuest" );
        return FALSE;
    }
    const char* szQuestId = words->GetWord(0);
    if ( WordParser::IsNumber(szQuestId) )
    {
        m_QuestId.SetNumber( atoi(szQuestId) );
        m_QuestId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szQuestId);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoneQuest error");
            return FALSE;
        }
        m_QuestId.SetNumber(nKey);
        m_QuestId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nQuestId = 0;
    if (m_QuestId.IsKey())
    {
        int nKey = m_QuestId.GetNumber();
        nQuestId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nQuestId = m_QuestId.GetNumber();
    }
    // 判断QuestId是否合法
    if ( nQuestId < dr_MinQuestId || nQuestId > dr_MaxQuestId )
    {
        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoneQuest QuestId[%d] error", nQuestId);
        return;
    }

    int retNum = GetScriptInterface()->Quest_DoneQuest(nQuestId);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int nQuestId;
CScriptCmd__SetVar::Param m_QuestId;
SCRIPT_END

////////////////////////////////////////////////////////////////////////////
////
//// set_quest_state 3000 1
SCRIPT_BEGIN( set_quest_state )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:set_quest_state" );
        return FALSE;
    }
    
    const char* szWord = words->GetWord(0);
    if( WordParser::IsNumber( szWord ) )
    {   
        _nQuestId.SetNumber( atoi( szWord ) );
        _nQuestId.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetPlayerVar error" );
            return FALSE;
        }
        _nQuestId.SetNumber( nKey );
        _nQuestId.SetIsKey( true );
    }

    if ( !_nQuestId.IsKey())
    {
        int nQuestId = _nQuestId.GetNumber();
        if( nQuestId < dr_MinQuestId || nQuestId > dr_MaxQuestId )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:set_quest_state" );
            return FALSE;
        }
    }
    
    chState = atoi( words->GetWord( 1 ) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nQuestId = 0;
    if ( _nQuestId.IsKey() )
    {
        int nKey = _nQuestId.GetNumber();
        nQuestId = GetScriptInterface()->GetVar( nKey );
        
    }
    else
    {
        nQuestId = _nQuestId.GetNumber();
    }
    
    int nValue  = GetScriptInterface()->Quest_SetQuestState( nQuestId, chState );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param _nQuestId;
char chState;
SCRIPT_END
////////////////////////////////////////////////////////////////////////////
////
//// get_quest_state 3000
SCRIPT_BEGIN( get_quest_state )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:get_quest_state" );
        return FALSE;
    }

    //nQuestId = atoi( words->GetWord( 0 ) );
    const char* szWord = words->GetWord(0);
    if ( WordParser::IsNumber(szWord) )
    {
        m_QuestId.SetNumber( atoi(szWord) );
        m_QuestId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "get_quest_state error");
            return FALSE;
        }
        m_QuestId.SetNumber(nKey);
        m_QuestId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nQuestId = 0;
    if ( m_QuestId.IsKey() )
    {
        int nKey = m_QuestId.GetNumber();
        nQuestId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nQuestId = m_QuestId.GetNumber();
    }
    // 判断QuestId是否合法
    if( nQuestId < dr_MinQuestId || nQuestId > dr_MaxQuestId )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "cast quest failed, quest id out of range" );
        return;
    }
    GetScriptInterface()->Quest_GetQuestState( nQuestId, m_nReturnKey );
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int nQuestId;
CScriptCmd__SetVar::Param m_QuestId;
SCRIPT_END
////////////////////////////////////////////////////////////////////////////
////
//// relate_quest 3000 3
SCRIPT_BEGIN( relate_quest )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "[Error] relate_quest");
        return FALSE;
    }

    nQuestId = atoi( words->GetWord( 0 ) );
    if( nQuestId < dr_MinQuestId ||
        nQuestId > dr_MaxQuestId )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "[Error] relate_quest");
        return FALSE;
    }
    chState = atoi( words->GetWord( 1 ) );
    m_nEnter = atoi( words->GetWord(2) );
    if( m_nEnter == 0 )
        m_nEnter = 1;

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->Quest_RelateQuest( nQuestId, chState, m_nEnter );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int nQuestId;
char chState;
int m_nEnter;
SCRIPT_END
////////////////////////////////////////////////////////////////////////////
////
//// can_get_new_quest
SCRIPT_BEGIN( can_get_new_quest )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:can_get_new_quest" );
        return FALSE; 
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    bool states = GetScriptInterface()->Quest_CanGetNewQuest( m_nReturnKey );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( states?1:0 );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


////////////////////////////////////////////////////////////////////////////
////
//// Rand 100
SCRIPT_BEGIN( Rand )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Rand" );
        return FALSE;
    }
    m_nValue = atoi( words->GetWord( 0 ) );
    if ( m_nValue == 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Rand" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    params[1];
        params[0].SetNumber( theRand.rand32()%m_nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nValue;
SCRIPT_END

////////////////////////////////////////////////////////////////////////////
////
//// RefreshMonster 0 4 5 3
SCRIPT_BEGIN( RefreshMonster )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateMonster" );
        return FALSE;
    }
    m_nMapId = atoi( words->GetWord(0) );
    m_nX = atoi( words->GetWord(1) );
    m_nY = atoi( words->GetWord(2) );
    m_strArea = words->GetWord(3);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->RefreshMonster( m_nMapId, m_nX, m_nY,
                                            m_strArea.c_str() );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMapId;
int m_nX, m_nY;
std::string m_strArea;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// PlayMusic 0 filename
SCRIPT_BEGIN( PlayerMusic )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:PlayMusic" );
        return FALSE;
    }
    m_stParameter = atoi(words->GetWord(0));
    m_strFileName = words->GetWord(1);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->PlayerMusic( m_strFileName.c_str(), m_stParameter );
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strFileName;
short        m_stParameter;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// 声明变量
// var n
// var n = 1234
SCRIPT_BEGIN( var )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 &&
        words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "'var' failed" );
        return FALSE;
    }
    m_nVar = 0;
    if ( words->GetWordCount() == 3  )
    {
        if ( strcmp( words->GetWord(1), "=" ) != 0 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "'var' failed" );
            return FALSE;
        }
        m_nVar = atoi( words->GetWord(2) );
    }
    m_nKey = GetScriptVarMgr()->Register( words->GetWord(0), m_nVar );
    if ( m_nKey == -1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:Variable [%s] create failed!", words->GetWord(0) );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    switch( CScriptVarMgr::GetKeyType(m_nKey) )
    {
    case CScriptVarMgr::VT_TEMP:
        {
            if ( m_nKey != -1 )
            {
                CScriptCmd__SetVar::Param params[1];
                params[0].SetNumber( m_nVar );
                GetScriptInterface()->SetVar( m_nKey, SKW_SET, params, 1 );
            }
        }
        break;
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nKey;
int m_nVar;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// MakeItem    合成/精炼/强化
// MakeItem maketype rate equiptype itemtype x1 x2 x3 x4 y a x waste id1begin id1end id2begin id2end ...
SCRIPT_BEGIN( MakeItem )
#define MAX_MAKEITEM_ITEM    32
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "'MakeItem' failed" );
        return FALSE;
    }
    m_byCreatNewOrOld = atoi(words->GetWord(0));
    /*m_nMakeType = atoi(words->GetWord(1));*/
    m_nRate = atoi(words->GetWord(1));
    //m_byEquipType = atoi(words->GetWord(3));
    //m_byItemType = atoi(words->GetWord(4));
    //m_fX1 = atof(words->GetWord(5));
    //m_fX2 = atof(words->GetWord(6));
    //m_fX3 = atof(words->GetWord(7));
    //m_fX4 = atof(words->GetWord(8));
    //m_fY = atof(words->GetWord(9));
    //m_fA = atof(words->GetWord(10));
    //m_fX = atof(words->GetWord(11));
    //m_fWaste = atof(words->GetWord(12));
    m_nItemCount = atoi(words->GetWord(2));/*(words->GetWordCount() - 2)/2;*/
    if( m_nItemCount > MAX_MAKEITEM_ITEM || m_nItemCount < 0 )
    {
        m_nItemCount = MAX_MAKEITEM_ITEM;
    }
    for( int i = 0; i < m_nItemCount; i++ )
    {
        int nIndex = 3+i;
        m_nIdBegin[i] = atoi( words->GetWord( nIndex ) );        
        //m_nIdBegin[i] = atoi( words->GetWord( nIndex ) );
        //m_nIdEnd[i] = atoi( words->GetWord( nIndex+1 ) );
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->MakeItem( m_byCreatNewOrOld,/*m_nMakeType,*/ m_nRate, /*m_byEquipType,
                                    m_byItemType, m_fX1,m_fX2,m_fX3,m_fX4, m_fY, m_fA,m_fX,*/
                                    m_nIdBegin, m_nIdEnd, m_nItemCount/*, m_fWaste*/);
    //
    vm->NextIP();
}

SCRIPT_PARAM
BYTE    m_byCreatNewOrOld;
//int        m_nMakeType;
int        m_nRate;
//BYTE    m_byEquipType;
//BYTE    m_byItemType;    //生成物品具体类型
//float    m_fX1;            //生成合成物品数值的系数
//float    m_fX2;            //生成合成物品数值的系数
//float    m_fX3;            //生成合成物品数值的系数
//float    m_fX4;            //生成合成物品数值的系数
//float    m_fY;            //生成合成物品数值的系数
//float    m_fA;            //生成合成物品数值的系数
//float    m_fX;            //生成合成物品数值的系数
int        m_nItemCount;
int        m_nIdBegin[MAX_MAKEITEM_ITEM];
int        m_nIdEnd[MAX_MAKEITEM_ITEM];
//float   m_fWaste;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// Talk Type text
SCRIPT_BEGIN( Talk )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Talk" );
        return FALSE;
    }
    nType = atoi( words->GetWord(0));
    m_strMsg = words->GetWord(1);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->Talk( nType, m_strMsg.c_str() );
    vm->NextIP();
}

SCRIPT_PARAM
int nType;
std::string m_strMsg;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
//
// TalkAll Type 变量%s $n
SCRIPT_BEGIN( TalkAll )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:TalkAll" );
        return FALSE;
    }
    nType = atoi( words->GetWord(0) );
    m_strMsg = words->GetWord(1);
    //
    for ( int n=2; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strMsg.size()-1; n++ )
    {
        if ( m_strMsg[n] == '%' )
        {
            if ( m_strMsg[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
    GetScriptInterface()->TalkToAll( nType, szText );
    vm->NextIP();
}

SCRIPT_PARAM
int nType;
std::string m_strMsg;
std::vector<int> m_vtKey;
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
//
// TalkTeam Type 变量%s $n
SCRIPT_BEGIN( TalkTeam )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:TalkTeam" );
        return FALSE;
    }
    nType = atoi( words->GetWord(0) );
    m_strMsg = words->GetWord(1);
    for ( int n=2; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkTeam create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strMsg.size()-1; n++ )
    {
        if ( m_strMsg[n] == '%' )
        {
            if ( m_strMsg[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkTeam create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkTeam create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
    GetScriptInterface()->TalkToTeam( nType, szText );
    vm->NextIP();
}

SCRIPT_PARAM
int nType;
std::string m_strMsg;
std::vector<int> m_vtKey;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
// Tell Hello!
SCRIPT_BEGIN( Tell )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Tell" );
        return FALSE;
    }
    m_strText = words->GetWord(0);
    for ( int n=1; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Tell create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strText.size()-1; n++ )
    {
        if ( m_strText[n] == '%' )
        {
            if ( m_strText[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Tell create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "dlg create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[1024] = {0};
    ScriptSprintf( szText, sizeof(szText)-1, m_strText.c_str(), vtVar );
    GetScriptInterface()->Tell( szText );
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strText;
std::vector<int> m_vtKey;
SCRIPT_END
/////////////////////////////////////////////////////////////////////////////
// TalkMap mapid Type 变量%s $n
SCRIPT_BEGIN( TalkMap )
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() < 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:TalkMap" );
		return FALSE;
	}
	mapid = atoi( words->GetWord(0) );
	nType = atoi( words->GetWord(1) );
	m_strMsg = words->GetWord(2);
	for ( int n=3; n<words->GetWordCount(); n++ )
	{
		const char* sz = words->GetWord(n);
		int nVar = GetScriptVarMgr()->GetVarId( sz );
		if ( nVar == -1 )
		{
			LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
			return FALSE;
		}
		m_vtKey.push_back( nVar );
	}
	int nCount = 0;
	for ( int n=0; n<m_strMsg.size()-1; n++ )
	{
		if ( m_strMsg[n] == '%' )
		{
			if ( m_strMsg[n+1] == 's' )
			{
				nCount++;
			}
			else
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
				return FALSE;
			}
		}
	}
	if ( nCount != m_vtKey.size() )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
		return FALSE;
	}
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	std::vector<std::string> vtVar;
	for ( unsigned int n=0; n<m_vtKey.size(); n++ )
	{
		const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
		vtVar.push_back( sz );
	}
	char szText[512] = {0};
	ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
	GetScriptInterface()->TalkToMap(mapid,nType, szText );
	vm->NextIP();
}

SCRIPT_PARAM
int nType;
int mapid;
std::string m_strMsg;
std::vector<int> m_vtKey;
SCRIPT_END
/////////////////////////////////////////////////////////////////////////////
// TalkCountry countryid Type 变量%s $n
SCRIPT_BEGIN( TalkCountry )
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() < 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:TalkCountry" );
		return FALSE;
	}
	countryid = atoi( words->GetWord(0) );
	nType = atoi( words->GetWord(1) );
	m_strMsg = words->GetWord(2);
	for ( int n=3; n<words->GetWordCount(); n++ )
	{
		const char* sz = words->GetWord(n);
		int nVar = GetScriptVarMgr()->GetVarId( sz );
		if ( nVar == -1 )
		{
			LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
			return FALSE;
		}
		m_vtKey.push_back( nVar );
	}
	int nCount = 0;
	for ( int n=0; n<m_strMsg.size()-1; n++ )
	{
		if ( m_strMsg[n] == '%' )
		{
			if ( m_strMsg[n+1] == 's' )
			{
				nCount++;
			}
			else
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
				return FALSE;
			}
		}
	}
	if ( nCount != m_vtKey.size() )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkMap create error");
		return FALSE;
	}
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	std::vector<std::string> vtVar;
	for ( unsigned int n=0; n<m_vtKey.size(); n++ )
	{
		const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
		vtVar.push_back( sz );
	}
	char szText[512] = {0};
	ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
	GetScriptInterface()->TalkToCountry(countryid,nType, szText );
	vm->NextIP();
}

SCRIPT_PARAM
int nType;
int countryid;
std::string m_strMsg;
std::vector<int> m_vtKey;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
// ShowQuestDlg 请问你有何事?
SCRIPT_BEGIN( ShowQuestDlg )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ShowQuestDlg" );
        return FALSE;
    }
    m_strInfo = words->GetWord(0);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ShowQuestDlg( m_nReturnKey, m_strInfo.c_str() );
    //
    vm->NextIP();
    vm->Hangup();
}

SCRIPT_PARAM
std::string        m_strInfo;
SCRIPT_END


// ShowPubQuestDlg 请问你有何事?
SCRIPT_BEGIN( ShowPubQuestDlg )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ShowPubQuestDlg" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord( 0 ) );
    m_strInfo = words->GetWord(1);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ShowPubQuestDlg( m_nReturnKey, m_nType, m_strInfo.c_str() );
    //
    vm->NextIP();
    vm->Hangup();
}

SCRIPT_PARAM
int m_nType;         
std::string        m_strInfo;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
//
// UseSkill id level
SCRIPT_BEGIN( UseSkill )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:UseSkill" );
        return FALSE;
    }
    m_nSkillId = atoi( words->GetWord(0) );
    m_nSkillLevel = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->UseSkill( m_nSkillId, m_nSkillLevel );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nSkillId;
int m_nSkillLevel;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( PopNpcList )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->PopNpcList();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetWorldTime time type
SCRIPT_BEGIN( GetWorldTime )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetWorldTime" );
        return FALSE;
    }
    const char *szType = words->GetWord(0);
    if ( stricmp(szType,"Year") != 0 &&
        stricmp(szType,"Month") != 0 &&
        stricmp(szType,"Week") != 0 &&
        stricmp(szType,"Day") != 0 &&
        stricmp(szType,"Hour") != 0 &&
        stricmp(szType,"Minute") != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetWorldTime" );
        return FALSE;
    }
    m_strTimeType = szType;
    //
    m_bRealTime = false;
    if( words->GetWordCount() >= 2 )
    {
        if ( atoi( words->GetWord(1) ) > 0 )
        {
            m_bRealTime = true;
        }
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nTime = GetScriptInterface()->GetWorldTime( m_strTimeType.c_str(), m_bRealTime );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nTime );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strTimeType;
bool        m_bRealTime;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetBirthday type
SCRIPT_BEGIN( GetBirthday )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetBirthday" );
        return FALSE;
    }
    const char *szType = words->GetWord(0);
    if ( stricmp(szType,"Year") == 0 )
    {
        m_nTimeType = 0;
    }
    else if ( stricmp(szType,"Month") == 0 )
    {
        m_nTimeType = 1;
    }
    else if ( stricmp(szType,"Day") == 0 )
    {
        m_nTimeType = 2;
    }
    else
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetBirthday" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nTime = GetScriptInterface()->GetBirthday( m_nTimeType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nTime );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nTimeType;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( ShowBank )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ShowBank();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
/*
@仓库脚本指令
*/
SCRIPT_BEGIN( SetStorage )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->SetStorage();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nValue );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( SetMountStorage )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->SetMountStorage();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( NpcMoveNext )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcMoveNext();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// NpcPlayAnim sayhi 1 end npcid
SCRIPT_BEGIN( NpcPlayAnim )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "NpcPlayAnim err" );
        return FALSE;
    }
    m_strName = words->GetWord(0);
    m_nTimes = atoi( words->GetWord(1) );
    m_strEndName = words->GetWord(2);
    if ( words->GetWordCount() >= 4 )
    {
        m_nNpcId = atoi( words->GetWord(3) );
    }
    else
    {
        m_nNpcId = -1;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcPlayAnim( m_strName.c_str(),
                                        m_nTimes,
                                        m_strEndName.c_str(),
                                        false, m_nNpcId );
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string    m_strName;
int            m_nTimes;
std::string    m_strEndName;
int            m_nNpcId;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// IsNpcPlayAnim npcid endAnim
SCRIPT_BEGIN( IsNpcPlayAnim )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsNpcPlayAnim err" );
        return FALSE;
    }
    m_nNpcId = atoi( words->GetWord(0) );
    m_strName = words->GetWord(1);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    BOOL bPlay = GetScriptInterface()->IsNpcPlayAnim( m_nNpcId, m_strName.c_str() );
    //
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( bPlay );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int            m_nNpcId;
std::string    m_strName;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// NpcPlayAnimForAll sayhi 1 end npcid
SCRIPT_BEGIN( NpcPlayAnimForAll )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "NpcPlayAnimForAll err" );
        return FALSE;
    }
    m_strName = words->GetWord(0);
    m_nTimes = atoi( words->GetWord(1) );
    m_strEndName = words->GetWord(2);
    if ( words->GetWordCount() >= 4 )
    {
        m_nNpcId = atoi( words->GetWord(3) );
    }
    else
    {
        m_nNpcId = -1;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcPlayAnim( m_strName.c_str(),
                                        m_nTimes,
                                        m_strEndName.c_str(),
                                        true, m_nNpcId );
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string    m_strName;
int            m_nTimes;
std::string    m_strEndName;
int            m_nNpcId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// ScenePlay
SCRIPT_BEGIN( ScenePlay )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ScenePlay err" );
        return FALSE;
    }
    m_nSceneID  = atoi( words->GetWord(0) );
    m_bView     = atoi( words->GetWord(1) );
 
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ScenePlay( m_nSceneID, m_bView );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int     m_nSceneID;
bool    m_bView;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// BlackScreen
SCRIPT_BEGIN( BlackScreen )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "BlackScreen err" );
        return FALSE;
    }
    m_nTime     = atoi( words->GetWord(0) );
    m_bView     = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->BlackScreen( m_nTime, m_bView );
    vm->NextIP();
}

SCRIPT_PARAM
int     m_nTime;
bool    m_bView;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// NpcScenePlay
SCRIPT_BEGIN( NpcScenePlay )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "NpcScenePlay err" );
        return FALSE;
    }

    m_nNpcID    = atoi( words->GetWord(0) );
    m_nSceneID  = atoi( words->GetWord(1) );
    m_bView     = atoi( words->GetWord(2) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcScenePlay( m_nNpcID, m_nSceneID, m_bView );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int     m_nNpcID;
int     m_nSceneID;
bool    m_bView;
SCRIPT_END

/**********************************************************************
author:liaojie
date:2012/08/28
Desc:能否召唤副将
**********************************************************************/
SCRIPT_BEGIN( IsCanPet )
virtual BOOL Create( WordParser* words )
{
	if ( words->GetWordCount() != 0 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanPet err" );
		return FALSE;
	}
	return true;
}
virtual void Execute( CScriptVM* vm )
{
	bool bResult = GetScriptInterface()->IsCanPet();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( bResult?1:0 );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	//
	vm->NextIP();
}
SCRIPT_END

SCRIPT_BEGIN(DoPet)
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoPet err" );
		return FALSE;
	}

	const char* szId = words->GetWord(0);
	if (WordParser::IsNumber(szId))
	{
		m_Id.SetNumber( atoi(szId) );
		m_Id.SetIsKey(false);
	} 
	else
	{
		int nKey = GetScriptVarMgr()->GetVarId(szId);
		if (nKey == -1)
		{
			LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DoPet" );
			return FALSE;
		}
		m_Id.SetNumber(nKey);
		m_Id.SetIsKey(true);
	}
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	int nId = 0;
	if (m_Id.IsKey())
	{
		int nKey = m_Id.GetNumber();
		nId = GetScriptInterface()->GetVar(nKey);
	} 
	else
	{
		nId = m_Id.GetNumber();
	}
	GetScriptInterface()->DoPet( nId );
	//
	vm->NextIP();
}

SCRIPT_PARAM
//int     m_nId;
CScriptCmd__SetVar::Param m_Id;
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
// IsCanRide
SCRIPT_BEGIN( IsCanRide )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanRide err" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    bool bResult = GetScriptInterface()->IsCanRide();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult?1:0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// DoRide 1000
SCRIPT_BEGIN( DoRide )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoRide err" );
        return FALSE;
    }

    const char* szId = words->GetWord(0);
    if (WordParser::IsNumber(szId))
    {
        m_Id.SetNumber( atoi(szId) );
        m_Id.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szId);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DoRide" );
            return FALSE;
        }
        m_Id.SetNumber(nKey);
        m_Id.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nId = 0;
    if (m_Id.IsKey())
    {
        int nKey = m_Id.GetNumber();
        nId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nId = m_Id.GetNumber();
    }
    GetScriptInterface()->DoRide( nId );
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int     m_nId;
CScriptCmd__SetVar::Param m_Id;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddSkillToFristMount
SCRIPT_BEGIN( AddSkillToFristMount )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddSkillToFristMount err" );
        return FALSE;
    }
    m_nSkillId = atoi( words->GetWord(0) );
    m_nSkillLv = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddSkillToFristMount( m_nSkillId, m_nSkillLv );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int     m_nSkillId;
int     m_nSkillLv;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// DoRideFristMount
SCRIPT_BEGIN( DoRideFristMount )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoRideFristMount err" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->DoRideFristMount(  );
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// DoHitch
SCRIPT_BEGIN( DoHitch )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoHitch err" );
        return FALSE;
    }

    m_nId = atoi( words->GetWord(0) );
    m_bBack = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->DoHitch( m_nId, m_bBack );
    vm->NextIP();
}

SCRIPT_PARAM
int        m_nId;
bool    m_bBack;
SCRIPT_END

SCRIPT_BEGIN( DoHitchByTeam )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DoHitchByTeam err" );
        return FALSE;
    }

    m_nId = atoi( words->GetWord(0) );
	m_TeamID= atoi( words->GetWord(1) );
    m_bBack = atoi( words->GetWord(2) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->DoHitchByTeam( m_nId,m_TeamID, m_bBack );
    vm->NextIP();
}
SCRIPT_PARAM
int     m_nId;
int     m_TeamID;
bool    m_bBack;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetRideId
SCRIPT_BEGIN( GetRideId )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetRideId" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    short nId = GetScriptInterface()->GetRideId();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int     m_nId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// SetDialogName name
SCRIPT_BEGIN( SetDialogName )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetDialogName" );
        return FALSE;
    }
    m_strName = words->GetWord(0);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetDialogName( m_strName.c_str() );
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strName;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// SetHotkey index id
SCRIPT_BEGIN( SetHotkey )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error: SetHotkey" );
        return FALSE;
    }
    m_nIndex = atoi( words->GetWord(0) );
    m_nID = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetHotkey( m_nIndex, m_nID );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nIndex;
int m_nID;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// LogInfoToDB info
SCRIPT_BEGIN( LogInfoToDB )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 1 )
    {
        GetScriptInterface()->Printf( "error:LogInfoToDB" );
        return FALSE;
    }
    m_strMsg = words->GetWord(0);
    for ( int n=1; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "LogInfoToDB create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strMsg.size()-1; n++ )
    {
        if ( m_strMsg[n] == '%' )
        {
            if ( m_strMsg[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "LogInfoToDB create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "LogInfoToDB create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
    int nReturn = GetScriptInterface()->LogInfoToDB( szText );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nReturn );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string            m_strMsg;
std::vector<int>    m_vtKey;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// TalkArea mapid x y color 变量%s $n
SCRIPT_BEGIN( TalkArea )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 5 )
    {
        GetScriptInterface()->Printf( "error:TalkArea" );
        return FALSE;
    }
    m_nMapId = atoi( words->GetWord(0) );
    m_nX = atoi( words->GetWord(1) );
    m_nY = atoi( words->GetWord(2) );
    m_dwColor = strtoul( words->GetWord(3), NULL, 16);
    m_strMsg = words->GetWord(4);
    //
    for ( int n=5; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }
    int nCount = 0;
    for ( int n=0; n<m_strMsg.size()-1; n++ )
    {
        if ( m_strMsg[n] == '%' )
        {
            if ( m_strMsg[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TalkAll create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, 511, m_strMsg.c_str(), vtVar );
    GetScriptInterface()->TalkToArea( m_nMapId, m_nX, m_nY, m_dwColor, szText );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMapId;
int m_nX;
int m_nY;
DWORD m_dwTime;
DWORD m_dwColor;
std::string m_strMsg;
std::vector<int> m_vtKey;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetTeamPlayerCount
SCRIPT_BEGIN( GetTeamPlayerCount )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetTeamPlayerCount" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetTeamPlayerCount();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetTeamID
SCRIPT_BEGIN( GetTeamID )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetTeamID" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int id = GetScriptInterface()->GetTeamID();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( id );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetTeamPlayerLevel 0
SCRIPT_BEGIN( GetTeamPlayerLevel )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:GetTeamPlayerLevel" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetTeamPlayerLevel( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int        m_nType;
SCRIPT_END

SCRIPT_BEGIN( GetTeamAverageLevel )
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetTeamAverageLevel();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// SetTeamVar key var
SCRIPT_BEGIN( SetTeamVar )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:SetTeamVar" );
        return FALSE;
    }
    const char *szKey = words->GetWord(0);
    if ( WordParser::IsNumber(szKey) )
    {
        m_paramKey.SetNumber( atoi(szKey) );
        m_paramKey.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szKey);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetTeamVar");
            return FALSE;
        }
        m_paramKey.SetNumber(nKey);
        m_paramKey.SetIsKey(true);
    }
    const char* szVar = words->GetWord(1);
    if ( WordParser::IsNumber(szVar) )
    {
        m_paramVar.SetNumber( atoi(szVar) );
        m_paramVar.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVar);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetTeamVar");
            return FALSE;
        }
        m_paramVar.SetNumber(nKey);
        m_paramVar.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int m_nKey = 0;
    int m_nVar = 0;
    if (m_paramKey.IsKey())
    {
        int nKey = m_paramKey.GetNumber();
        m_nKey = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        m_nKey = m_paramKey.GetNumber();
    }
    if (m_paramVar.IsKey())
    {
        int nKey = m_paramVar.GetNumber();
        m_nVar = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        m_nVar = m_paramVar.GetNumber();
    }

    CScriptCmd__SetVar::Param params;
    params.SetNumber( m_nVar );
    GetScriptInterface()->SetTeamVar( m_nKey, SKW_SET, &params, 1 );
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int    m_nKey;
//int    m_nVar;
CScriptCmd__SetVar::Param m_paramKey;
CScriptCmd__SetVar::Param m_paramVar;
SCRIPT_END

// SetAreaVar nVarId nValue nRadius nType
SCRIPT_BEGIN( SetAreaVar )
virtual BOOL Create( WordParser* words )
{
    if ( words->GetWordCount() != 4 )
    {
        GetScriptInterface()->Printf("error:SetAreaVar");
        return FALSE;
    }
    const char* szKey = NULL;
    szKey = words->GetWord(0);
    nVarId = GetScriptVarMgr()->GetVarId(szKey);
    if ( nVarId == -1 )
    {
        GetScriptInterface()->Printf("error:SetAreaVar");
        return FALSE;
    }
    nValue  = atoi( words->GetWord(1) );
    nRadius = atoi( words->GetWord(2) );
    nType   = atoi( words->GetWord(3) );
    if (nType != ECountryType && nType != EGuildType)
    {
        GetScriptInterface()->Printf("error:SetAreaVar");
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetAreaVar( nVarId, nValue, nRadius, nType );
    vm->NextIP();
}

SCRIPT_PARAM
enum EnumType
{
    ECountryType    = 0,
    EGuildType      = 1,
};
int nVarId;
int nValue;
int nRadius;
int nType;
SCRIPT_END

// AddTeamVar key var
SCRIPT_BEGIN( AddTeamVar )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:AddTeamVar" );
        return FALSE;
    }
    const char *szKey = words->GetWord(0);
    if (WordParser::IsNumber(szKey))
    {
        m_paramKey.SetNumber( atoi(szKey) );
        m_paramKey.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szKey);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddTeamVar");
            return FALSE;
        }
        m_paramKey.SetNumber(nKey);
        m_paramKey.SetIsKey(TRUE);
    }

    const char* szVar = words->GetWord(1);
    if ( WordParser::IsNumber(szVar) )
    {
        m_paramVar.SetNumber( atoi(szVar) );
        m_paramVar.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVar);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddTeamVar");
            return FALSE;
        }
        m_paramVar.SetNumber(nKey);
        m_paramVar.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int m_nKey = 0;
    int m_nVar = 0;
    if (m_paramKey.IsKey())
    {
        int nKey = m_paramKey.GetNumber();
        m_nKey = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        m_nKey = m_paramKey.GetNumber();
    }
    if (m_paramVar.IsKey())
    {
        int nKey = m_paramVar.GetNumber();
        m_nVar = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        m_nVar = m_paramVar.GetNumber();
    }

    CScriptCmd__SetVar::Param params;
    params.SetNumber( m_nVar );
    GetScriptInterface()->SetTeamVar( m_nKey, SKW_SETADD, &params, 1 );
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int    m_nKey;
//int    m_nVar;
CScriptCmd__SetVar::Param m_paramKey;
CScriptCmd__SetVar::Param m_paramVar;
SCRIPT_END

SCRIPT_BEGIN( IsTeamVarAllLess )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:IsTeamVarAllLess" );
        return FALSE;
    }
/*
    const char *szKey = NULL;
    szKey = words->GetWord(0);
    m_nKey = GetScriptVarMgr()->GetVarId( szKey );
    if ( m_nKey == -1 )
    {
        GetScriptInterface()->Printf( "error:IsTeamVarAllLess" );
        return FALSE;
    }
    m_nVar = atoi( words->GetWord(1) );*/
    const char *szKey = words->GetWord(0);
    if (WordParser::IsNumber(szKey))
    {
        m_paramKey.SetNumber( atoi(szKey) );
        m_paramKey.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szKey);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsTeamVarAllLess");
            return FALSE;
        }
        m_paramKey.SetNumber(nKey);
        m_paramKey.SetIsKey(TRUE);
    }

    const char* szVar = words->GetWord(1);
    if ( WordParser::IsNumber(szVar) )
    {
        m_paramVar.SetNumber( atoi(szVar) );
        m_paramVar.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVar);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsTeamVarAllLess");
            return FALSE;
        }
        m_paramVar.SetNumber(nKey);
        m_paramVar.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int m_nKey = 0;
    int m_nVar = 0;
    if (m_paramKey.IsKey())
    {
        int nKey = m_paramKey.GetNumber();
        m_nKey = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        m_nKey = m_paramKey.GetNumber();
    }
    if (m_paramVar.IsKey())
    {
        int nKey = m_paramVar.GetNumber();
        m_nVar = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        m_nVar = m_paramVar.GetNumber();
    }

    int nResult = GetScriptInterface()->IsTeamVarAllLess( m_nKey, m_nVar );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
//int    m_nKey;
//int    m_nVar;
CScriptCmd__SetVar::Param m_paramKey;
CScriptCmd__SetVar::Param m_paramVar;
SCRIPT_END

SCRIPT_BEGIN( IsTeamVarAllGreater )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:IsTeamVarAllGreater" );
        return FALSE;
    }
    const char *szKey = words->GetWord(0);
    if (WordParser::IsNumber(szKey))
    {
        m_paramKey.SetNumber( atoi(szKey) );
        m_paramKey.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szKey);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsTeamVarAllLess");
            return FALSE;
        }
        m_paramKey.SetNumber(nKey);
        m_paramKey.SetIsKey(TRUE);
    }

    const char* szVar = words->GetWord(1);
    if ( WordParser::IsNumber(szVar) )
    {
        m_paramVar.SetNumber( atoi(szVar) );
        m_paramVar.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVar);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsTeamVarAllLess");
            return FALSE;
        }
        m_paramVar.SetNumber(nKey);
        m_paramVar.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int m_nKey = 0;
    int m_nVar = 0;
    if (m_paramKey.IsKey())
    {
        int nKey = m_paramKey.GetNumber();
        m_nKey = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        m_nKey = m_paramKey.GetNumber();
    }
    if (m_paramVar.IsKey())
    {
        int nKey = m_paramVar.GetNumber();
        m_nVar = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        m_nVar = m_paramVar.GetNumber();
    }

    int nResult = GetScriptInterface()->IsTeamVarAllGreater( m_nKey, m_nVar );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_paramKey;
CScriptCmd__SetVar::Param m_paramVar;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetTeamPlayerID index
SCRIPT_BEGIN( GetTeamPlayerID )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:GetTeamPlayerID" );
        return FALSE;
    }
    m_nIndex = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetTeamPlayerID( m_nIndex );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int    m_nIndex;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetCurPlayerID
SCRIPT_BEGIN( GetCurPlayerID )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetCurPlayerID" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetCurCharId();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetPlayerVar id key
SCRIPT_BEGIN( GetPlayerVar )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:GetPlayerVar" );
        return FALSE;
    }
    const char* szWord = words->GetWord(0);
    if( WordParser::IsNumber( szWord ) )
    {
        m_stPlayerId.SetNumber( atoi( szWord ) );
        m_stPlayerId.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetPlayerVar error" );
            return FALSE;
        }
        m_stPlayerId.SetNumber( nKey );
        m_stPlayerId.SetIsKey( true );
    }

    const char* szKey = words->GetWord(1);
    if ( WordParser::IsNumber(szKey) )
    {
        m_Key.SetNumber( atoi(szKey) );
        m_Key.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szKey);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetPlayerVar param 2 VarId error" );
            return FALSE;
        }
        m_Key.SetNumber(nKey);
        m_Key.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nPlayerId = 0;
    if ( m_stPlayerId.IsKey() )
    {
        int nKey = m_stPlayerId.GetNumber();
        nPlayerId = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nPlayerId = m_stPlayerId.GetNumber();
    }
    int nVarKey = 0;
    if ( m_Key.IsKey() )
    {
        int nKey = m_Key.GetNumber();
        nVarKey = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarKey = m_Key.GetNumber();
    }
    int retNum = GetScriptInterface()->GetVar( nVarKey, nPlayerId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_stPlayerId;      // 玩家ID
CScriptCmd__SetVar::Param m_Key;             // 计数变量ID
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// SetDstPlayer    id
SCRIPT_BEGIN( SetDstPlayer )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:SetDstPlayer" );
        return FALSE;
    }
    m_nPlayerId = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetDstPlayer( m_nPlayerId );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nPlayerId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CreateMonster mapId x y r bodysize index num
SCRIPT_BEGIN( CreateMonster )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 7 )
    {
        GetScriptInterface()->Printf( "error:CreateMonster" );
        return FALSE;
    }
    // MapId
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_nMapId.SetNumber( atoi(szMapId) );
        m_nMapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param MapId error");
            return FALSE;
        }
        m_nMapId.SetNumber(nKey);
        m_nMapId.SetIsKey(true);
    }
    // X
    const char* szPosX = words->GetWord(1);
    if ( WordParser::IsNumber(szPosX) )
    {
        m_PosX.SetNumber( atoi(szPosX) );
        m_PosX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosX);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param X error");
            return FALSE;
        }
        m_PosX.SetNumber(nKey);
        m_PosX.SetIsKey(true);
    }
    // Y
    const char* szPosY = words->GetWord(2);
    if ( WordParser::IsNumber(szPosY) )
    {
        m_PosY.SetNumber( atoi(szPosY) );
        m_PosY.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosY);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param Y error");
            return FALSE;
        }
        m_PosY.SetNumber(nKey);
        m_PosY.SetIsKey(true);
    }
    m_fRadius = atof( words->GetWord(3) );
    m_fBodySize = atof( words->GetWord(4) );
    // MonsterIndex
    const char* szMonsterIndex = words->GetWord(5);
    if ( WordParser::IsNumber(szMonsterIndex) )
    {
        m_nMonsterIndex.SetNumber( atoi(szMonsterIndex) );
        m_nMonsterIndex.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterIndex);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param MonsterId error");
            return FALSE;
        }
        m_nMonsterIndex.SetNumber(nKey);
        m_nMonsterIndex.SetIsKey(true);
    }
    // Monster Number
    const char* szNum = words->GetWord(6);
    if ( WordParser::IsNumber(szNum) )
    {
        m_MonsterNum.SetNumber( atoi(szNum) );
        m_MonsterNum.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szNum);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param MonsterNum error");
            return FALSE;
        }
        m_MonsterNum.SetNumber(nKey);
        m_MonsterNum.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_nMapId.IsKey() )
    {
        int nKey = m_nMapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMapId = m_nMapId.GetNumber();
    }

    int nPosX = 0;
    if ( m_PosX.IsKey() )
    {
        int nKey = m_PosX.GetNumber();
        nPosX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosX = m_PosX.GetNumber();
    }

    int nPosY = 0;
    if ( m_PosY.IsKey() )
    {
        int nKey = m_PosY.GetNumber();
        nPosY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosY = m_PosY.GetNumber();
    }

    int nMonsterIndex = 0;
    if ( m_nMonsterIndex.IsKey() )
    {
        int nKey = m_nMonsterIndex.GetNumber();
        nMonsterIndex = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterIndex = m_nMonsterIndex.GetNumber();
    }

    int nMonsterNum = 0;
    if ( m_MonsterNum.IsKey() )
    {
        int nKey = m_MonsterNum.GetNumber();
        nMonsterNum = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterNum = m_MonsterNum.GetNumber();
    }
    GetScriptInterface()->CreateMonster( nMapId, nPosX, nPosY, 
                                         m_fRadius, m_fBodySize,
                                         nMonsterIndex, nMonsterNum);
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_nMapId;
CScriptCmd__SetVar::Param m_PosX, m_PosY;
float    m_fRadius;
float    m_fBodySize;
CScriptCmd__SetVar::Param m_nMonsterIndex;
CScriptCmd__SetVar::Param m_MonsterNum;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CreateMonsterEx
SCRIPT_BEGIN( CreateMonsterEx )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 8 && words->GetWordCount() != 9 )
    {
        GetScriptInterface()->Printf( "error:CreateMonsterEx" );
        return FALSE;
    }
	m_Count = words->GetWordCount();
    // MapId
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_nMapId.SetNumber( atoi(szMapId) );
        m_nMapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param MapId error");
            return FALSE;
        }
        m_nMapId.SetNumber(nKey);
        m_nMapId.SetIsKey(true);
    }
    // X
    const char* szPosX = words->GetWord(1);
    if ( WordParser::IsNumber(szPosX) )
    {
        m_PosX.SetNumber( atoi(szPosX) );
        m_PosX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosX);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param X error");
            return FALSE;
        }
        m_PosX.SetNumber(nKey);
        m_PosX.SetIsKey(true);
    }
    // Y
    const char* szPosY = words->GetWord(2);
    if ( WordParser::IsNumber(szPosY) )
    {
        m_PosY.SetNumber( atoi(szPosY) );
        m_PosY.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosY);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param Y error");
            return FALSE;
        }
        m_PosY.SetNumber(nKey);
        m_PosY.SetIsKey(true);
    }
    m_fRadius = atof( words->GetWord(3) );

    // MonsterIndex
    const char* szMonsterIndex = words->GetWord(4);
    if ( WordParser::IsNumber(szMonsterIndex) )
    {
        m_nMonsterIndex.SetNumber( atoi(szMonsterIndex) );
        m_nMonsterIndex.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterIndex);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param MonsterId error");
            return FALSE;
        }
        m_nMonsterIndex.SetNumber(nKey);
        m_nMonsterIndex.SetIsKey(true);
    }
    // Monster nFightCamp
    const char* szFightCamp = words->GetWord(5);
    if ( WordParser::IsNumber(szFightCamp) )
    {
        m_nFightCamp.SetNumber( atoi(szFightCamp) );
        m_nFightCamp.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szFightCamp);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nFightCamp.SetNumber(nKey);
        m_nFightCamp.SetIsKey(true);
    }

    // Monster nForce
    const char* szForce = words->GetWord(6);
    if ( WordParser::IsNumber(szForce) )
    {
        m_nForce.SetNumber( atoi(szForce) );
        m_nForce.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szForce);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nForce.SetNumber(nKey);
        m_nForce.SetIsKey(true);
    }

    // Monster nRouteID
    const char* szRouteID = words->GetWord(7);
    if ( WordParser::IsNumber(szRouteID) )
    {
        m_nRouteID.SetNumber( atoi(szRouteID) );
        m_nRouteID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szRouteID);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nRouteID.SetNumber(nKey);
        m_nRouteID.SetIsKey(true);
    }

	// Monster Country
	if ( m_Count == 9 )
	{
		const char* szCountry = words->GetWord(8);
		if ( WordParser::IsNumber(szCountry) )
		{
			m_nCountry.SetNumber( atoi(szCountry) );
			m_nCountry.SetIsKey(false);
		}
		else
		{
			int nKey = GetScriptVarMgr()->GetVarId(szCountry);
			if ( nKey == -1 )
			{
				LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
				return FALSE;
			}
			m_nCountry.SetNumber(nKey);
			m_nCountry.SetIsKey(true);
		}
	}

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_nMapId.IsKey() )
    {
        int nKey = m_nMapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMapId = m_nMapId.GetNumber();
    }

    int nPosX = 0;
    if ( m_PosX.IsKey() )
    {
        int nKey = m_PosX.GetNumber();
        nPosX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosX = m_PosX.GetNumber();
    }

    int nPosY = 0;
    if ( m_PosY.IsKey() )
    {
        int nKey = m_PosY.GetNumber();
        nPosY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosY = m_PosY.GetNumber();
    }

    int nMonsterIndex = 0;
    if ( m_nMonsterIndex.IsKey() )
    {
        int nKey = m_nMonsterIndex.GetNumber();
        nMonsterIndex = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterIndex = m_nMonsterIndex.GetNumber();
    }

    int nFightCamp = 0;
    if ( m_nFightCamp.IsKey() )
    {
        int nKey = m_nFightCamp.GetNumber();
        nFightCamp = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nFightCamp = m_nFightCamp.GetNumber();
    }

    int nForce = 0;
    if ( m_nForce.IsKey() )
    {
        int nKey = m_nForce.GetNumber();
        nForce = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nForce = m_nForce.GetNumber();
    }

    int nRouteID = 0;
    if ( m_nRouteID.IsKey() )
    {
        int nKey = m_nRouteID.GetNumber();
        nRouteID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nRouteID = m_nRouteID.GetNumber();
    }

	int nCountry = 0;
	if ( m_Count == 9 )
	{
		if ( m_nCountry.IsKey() )
		{
			int nKey = m_nCountry.GetNumber();
			nCountry = GetScriptInterface()->GetVar(nKey);
		}
		else
		{
			nCountry = m_nCountry.GetNumber();
		}
	}

    GetScriptInterface()->CreateMonsterEx( nMapId, nPosX, nPosY, 
        m_fRadius, nMonsterIndex, nFightCamp, nForce, nRouteID, nCountry );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_nMapId;
CScriptCmd__SetVar::Param m_PosX, m_PosY;
float    m_fRadius;
CScriptCmd__SetVar::Param m_nMonsterIndex;
CScriptCmd__SetVar::Param m_nFightCamp;
CScriptCmd__SetVar::Param m_nForce;
CScriptCmd__SetVar::Param m_nRouteID;
CScriptCmd__SetVar::Param m_nCountry;
int m_Count;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CreateSpecialMonster mapId x y r bodysize index num
SCRIPT_BEGIN( CreateSpecialMonster )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 7 )
    {
        GetScriptInterface()->Printf( "error:CreateSpecialMonster" );
        return FALSE;
    }
    // MapId
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateSpecialMonster [MapId]" );
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }
    // X
    const char* szPosX = words->GetWord(1);
    if ( WordParser::IsNumber(szPosX) )
    {
        m_PosX.SetNumber( atoi(szPosX) );
        m_PosX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosX);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateSpecialMonster [X]" );
            return FALSE;
        }
        m_PosX.SetNumber(nKey);
        m_PosX.SetIsKey(true);
    }
    // Y
    const char* szPosY = words->GetWord(2);
    if ( WordParser::IsNumber(szPosY) )
    {
        m_PosY.SetNumber( atoi(szPosY) );
        m_PosY.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosY);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateSpecialMonster [Y]" );
            return FALSE;
        }
        m_PosY.SetNumber(nKey);
        m_PosY.SetIsKey(true);
    }
    m_fRadius = atof( words->GetWord(3) );
    m_fBodySize = atof( words->GetWord(4) );
    // MonsterIndex
    const char* szMonsterIndex = words->GetWord(5);
    if ( WordParser::IsNumber(szMonsterIndex) )
    {
        m_MonsterIndex.SetNumber( atoi(szMonsterIndex) );
        m_MonsterIndex.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterIndex);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateSpecialMonster [MonsterIndex]" );
            return FALSE;
        }
        m_MonsterIndex.SetNumber(nKey);
        m_MonsterIndex.SetIsKey(true);
    }
    // MonsterNumber
    const char* szMonsterNum = words->GetWord(6);
    if ( WordParser::IsNumber(szMonsterNum) )
    {
        m_MonsterNum.SetNumber( atoi(szMonsterNum) );
        m_MonsterNum.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterNum);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CreateSpecialMonster [MonsterIndex]" );
            return FALSE;
        }
        m_MonsterNum.SetNumber(nKey);
        m_MonsterNum.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_MapId.IsKey() )
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMapId = m_MapId.GetNumber();
    }

    int nPosX = 0;
    if ( m_PosX.IsKey() )
    {
        int nKey = m_PosX.GetNumber();
        nPosX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosX = m_PosX.GetNumber();
    }

    int nPosY = 0;
    if ( m_PosY.IsKey() )
    {
        int nKey = m_PosY.GetNumber();
        nPosY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosY = m_PosY.GetNumber();
    }

    int nMonsterIndex = 0;
    if ( m_MonsterIndex.IsKey() )
    {
        int nKey = m_MonsterIndex.GetNumber();
        nMonsterIndex = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterIndex = m_MonsterIndex.GetNumber();
    }

    int nMonsterNum = 0;
    if ( m_MonsterNum.IsKey() )
    {
        int nKey = m_MonsterNum.GetNumber();
        nMonsterNum = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterNum = m_MonsterNum.GetNumber();
    }
    GetScriptInterface()->CreateSpecialMonster( nMapId, nPosX, nPosY,
                                            m_fRadius, m_fBodySize,
                                            nMonsterIndex, nMonsterNum );
    //
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_PosX;
CScriptCmd__SetVar::Param m_PosY;
float    m_fRadius;
float    m_fBodySize;
CScriptCmd__SetVar::Param m_MonsterIndex;
CScriptCmd__SetVar::Param m_MonsterNum;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CreateSpecialMonsterEx
SCRIPT_BEGIN( CreateSpecialMonsterEx )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 8 )
    {
        GetScriptInterface()->Printf( "error:CreateSpecialMonsterEx" );
        return FALSE;
    }
    // MapId
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_nMapId.SetNumber( atoi(szMapId) );
        m_nMapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateSpecialMonsterEx param MapId error");
            return FALSE;
        }
        m_nMapId.SetNumber(nKey);
        m_nMapId.SetIsKey(true);
    }
    // X
    const char* szPosX = words->GetWord(1);
    if ( WordParser::IsNumber(szPosX) )
    {
        m_PosX.SetNumber( atoi(szPosX) );
        m_PosX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosX);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateSpecialMonsterEx param X error");
            return FALSE;
        }
        m_PosX.SetNumber(nKey);
        m_PosX.SetIsKey(true);
    }
    // Y
    const char* szPosY = words->GetWord(2);
    if ( WordParser::IsNumber(szPosY) )
    {
        m_PosY.SetNumber( atoi(szPosY) );
        m_PosY.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosY);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateSpecialMonsterEx param Y error");
            return FALSE;
        }
        m_PosY.SetNumber(nKey);
        m_PosY.SetIsKey(true);
    }

    m_fRadius = atof( words->GetWord(3) );

    // MonsterIndex
    const char* szMonsterIndex = words->GetWord(4);
    if ( WordParser::IsNumber(szMonsterIndex) )
    {
        m_nMonsterIndex.SetNumber( atoi(szMonsterIndex) );
        m_nMonsterIndex.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterIndex);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateSpecialMonsterEx param MonsterId error");
            return FALSE;
        }
        m_nMonsterIndex.SetNumber(nKey);
        m_nMonsterIndex.SetIsKey(true);
    }
    // Monster nFightCamp
    const char* szFightCamp = words->GetWord(5);
    if ( WordParser::IsNumber(szFightCamp) )
    {
        m_nFightCamp.SetNumber( atoi(szFightCamp) );
        m_nFightCamp.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szFightCamp);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nFightCamp.SetNumber(nKey);
        m_nFightCamp.SetIsKey(true);
    }

    // Monster nForce
    const char* szForce = words->GetWord(6);
    if ( WordParser::IsNumber(szForce) )
    {
        m_nForce.SetNumber( atoi(szForce) );
        m_nForce.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szForce);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nForce.SetNumber(nKey);
        m_nForce.SetIsKey(true);
    }

    // Monster nRouteID
    const char* szRouteID = words->GetWord(7);
    if ( WordParser::IsNumber(szRouteID) )
    {
        m_nRouteID.SetNumber( atoi(szRouteID) );
        m_nRouteID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szRouteID);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterEx param error");
            return FALSE;
        }
        m_nRouteID.SetNumber(nKey);
        m_nRouteID.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_nMapId.IsKey() )
    {
        int nKey = m_nMapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMapId = m_nMapId.GetNumber();
    }

    int nPosX = 0;
    if ( m_PosX.IsKey() )
    {
        int nKey = m_PosX.GetNumber();
        nPosX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosX = m_PosX.GetNumber();
    }

    int nPosY = 0;
    if ( m_PosY.IsKey() )
    {
        int nKey = m_PosY.GetNumber();
        nPosY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosY = m_PosY.GetNumber();
    }

    int nMonsterIndex = 0;
    if ( m_nMonsterIndex.IsKey() )
    {
        int nKey = m_nMonsterIndex.GetNumber();
        nMonsterIndex = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterIndex = m_nMonsterIndex.GetNumber();
    }

    int nFightCamp = 0;
    if ( m_nFightCamp.IsKey() )
    {
        int nKey = m_nFightCamp.GetNumber();
        nFightCamp = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nFightCamp = m_nFightCamp.GetNumber();
    }

    int nForce = 0;
    if ( m_nForce.IsKey() )
    {
        int nKey = m_nForce.GetNumber();
        nForce = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nForce = m_nForce.GetNumber();
    }

    int nRouteID = 0;
    if ( m_nRouteID.IsKey() )
    {
        int nKey = m_nRouteID.GetNumber();
        nRouteID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nRouteID = m_nRouteID.GetNumber();
    }

    GetScriptInterface()->CreateSpecialMonsterEx( nMapId, nPosX, nPosY, 
        m_fRadius, nMonsterIndex, nFightCamp, nForce, nRouteID );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_nMapId;
CScriptCmd__SetVar::Param m_PosX, m_PosY;
float    m_fRadius;
CScriptCmd__SetVar::Param m_nMonsterIndex;
CScriptCmd__SetVar::Param m_nFightCamp;
CScriptCmd__SetVar::Param m_nForce;
CScriptCmd__SetVar::Param m_nRouteID;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CreateRouteMonster 
SCRIPT_BEGIN( CreateRouteMonster )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 6 )
    {
        GetScriptInterface()->Printf( "error:CreateMonster" );
        return FALSE;
    }
    // MapId
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_nMapId.SetNumber( atoi(szMapId) );
        m_nMapId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param MapId error");
            return FALSE;
        }
        m_nMapId.SetNumber(nKey);
        m_nMapId.SetIsKey(true);
    }
    // X
    const char* szPosX = words->GetWord(1);
    if ( WordParser::IsNumber(szPosX) )
    {
        m_PosX.SetNumber( atoi(szPosX) );
        m_PosX.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosX);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param X error");
            return FALSE;
        }
        m_PosX.SetNumber(nKey);
        m_PosX.SetIsKey(true);
    }
    // Y
    const char* szPosY = words->GetWord(2);
    if ( WordParser::IsNumber(szPosY) )
    {
        m_PosY.SetNumber( atoi(szPosY) );
        m_PosY.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szPosY);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param Y error");
            return FALSE;
        }
        m_PosY.SetNumber(nKey);
        m_PosY.SetIsKey(true);
    }
    m_fRadius = atof( words->GetWord(3) );
    
    // MonsterIndex
    const char* szMonsterIndex = words->GetWord(4);
    if ( WordParser::IsNumber(szMonsterIndex) )
    {
        m_nMonsterIndex.SetNumber( atoi(szMonsterIndex) );
        m_nMonsterIndex.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMonsterIndex);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param MonsterId error");
            return FALSE;
        }
        m_nMonsterIndex.SetNumber(nKey);
        m_nMonsterIndex.SetIsKey(true);
    }
    // m_nRouteID
    const char* szNum = words->GetWord(5);
    if ( WordParser::IsNumber(szNum) )
    {
        m_nRouteID.SetNumber( atoi(szNum) );
        m_nRouteID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szNum);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateMonster param m_nRouteID error");
            return FALSE;
        }
        m_nRouteID.SetNumber(nKey);
        m_nRouteID.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if ( m_nMapId.IsKey() )
    {
        int nKey = m_nMapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMapId = m_nMapId.GetNumber();
    }

    int nPosX = 0;
    if ( m_PosX.IsKey() )
    {
        int nKey = m_PosX.GetNumber();
        nPosX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosX = m_PosX.GetNumber();
    }

    int nPosY = 0;
    if ( m_PosY.IsKey() )
    {
        int nKey = m_PosY.GetNumber();
        nPosY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nPosY = m_PosY.GetNumber();
    }

    int nMonsterIndex = 0;
    if ( m_nMonsterIndex.IsKey() )
    {
        int nKey = m_nMonsterIndex.GetNumber();
        nMonsterIndex = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nMonsterIndex = m_nMonsterIndex.GetNumber();
    }

    int nRouteID = 0;
    if ( m_nRouteID.IsKey() )
    {
        int nKey = m_nRouteID.GetNumber();
        nRouteID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nRouteID = m_nRouteID.GetNumber();
    }
    GetScriptInterface()->CreateRouteMonster( nMapId, nPosX, nPosY, m_fRadius, nMonsterIndex, nRouteID );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_nMapId;
CScriptCmd__SetVar::Param m_PosX, m_PosY;
float    m_fRadius;
CScriptCmd__SetVar::Param m_nMonsterIndex;
CScriptCmd__SetVar::Param m_nRouteID;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetNullItemCount
SCRIPT_BEGIN( GetNullItemCount )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {        
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetNullItemCount" );
        return FALSE;
    }
    
    nBagType = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{ // BT_NormalItemBag
    int retNum = GetScriptInterface()->GetNullItemCount( nBagType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
    int nBagType;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// NpcStartMove
SCRIPT_BEGIN( NpcStartMove )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:NpcStartMove" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcStartMove();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// NpcStopMove
SCRIPT_BEGIN( NpcStopMove )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:NpcStopMove" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->NpcStopMove();
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// Sleep    time
SCRIPT_BEGIN( Sleep )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:Sleep" );
        return FALSE;
    }
    m_dwTime = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->Sleep( m_dwTime );
    //
    vm->NextIP();
    vm->Hangup();
}

SCRIPT_PARAM
DWORD    m_dwTime;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CallScript filename scriptid playerid
SCRIPT_BEGIN( CallScript )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() <= 1 )
    {
        GetScriptInterface()->Printf( "error:CallScript" );
        return FALSE;
    }
    m_strFileName = words->GetWord(0);
    m_nEnterId = atoi( words->GetWord(1) );
    if ( m_nEnterId <= -1 )
    {
        GetScriptInterface()->Printf( "error:CallScript" );
        return FALSE;
    }
    if( words->GetWordCount() >= 3 )
    {
        const char* szWord = words->GetWord(2);
        if( WordParser::IsNumber( szWord ) )
        {
            m_nPlayerId = atoi( szWord );
            if ( m_nPlayerId != -1 )
            {
                GetScriptInterface()->Printf( "error:CallScript" );
                return FALSE;
            }
        }
        else
        {
            m_nPlayerId = GetScriptVarMgr()->GetVarId( szWord );
        }
    }
    else
    {
        m_nPlayerId = -1;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nId = -1;
    if ( m_nPlayerId != -1 )
    {
        nId = GetScriptInterface()->GetVar( m_nPlayerId );
    }
    GetScriptInterface()->CallScript( m_strFileName.c_str(), m_nEnterId, nId, false );

//    vm->NextIP();
    vm->Return();
}

SCRIPT_PARAM
std::string m_strFileName;
int            m_nEnterId;
int            m_nPlayerId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// CloseDlg
SCRIPT_BEGIN( CloseDlg )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:CloseDlg" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->CloseDlg();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

// IsTeamHeader
SCRIPT_BEGIN( IsTeamHeader )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:IsTeamHeader" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nReturn = GetScriptInterface()->IsTeamHeader();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nReturn );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddTeamFriendly
SCRIPT_BEGIN( AddTeamFriendly )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:AddTeamFriendly" );
        return FALSE;
    }
    nFriendlyValue = atoi( words->GetWord(0) ) ;
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    bool b = GetScriptInterface()->AddTeamFriendly( nFriendlyValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( b );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int    nFriendlyValue;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetMapId
SCRIPT_BEGIN( GetMapId )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetMapId" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetMapId();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// IsInZone name
SCRIPT_BEGIN( IsInZone )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:IsInZone" );
        return FALSE;
    }
    m_strName = words->GetWord(0);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    bool b = GetScriptInterface()->IsInZone( m_strName.c_str() );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( b );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
std::string    m_strName;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// PlayEffect name
SCRIPT_BEGIN( PlayEffect )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 && words->GetWordCount() != 2 && words->GetWordCount() != 4 && words->GetWordCount() != 5 )
    {
        GetScriptInterface()->Printf( "error:PlayEffect" );
        return FALSE;
    }
    m_strName = words->GetWord(0);
    m_fX = 0.0f;
    m_fY = 0.0f;
    m_fZ = 0.0f;
    bIsCast = false;

    switch ( words->GetWordCount() )
    {
    case 1:
    case 2:
        if ( words->GetWordCount() == 2 )
        {
            bIsCast = atoi( words->GetWord(1) );
        }
    	break;
    case 4:
        {
            m_fX = atof(words->GetWord( 1 ));
            m_fY = atof(words->GetWord( 2 ));
            m_fZ = atof(words->GetWord( 3 ));
        }
    case 5:
        {
            m_fX = atof( words->GetWord( 1 ) );
            m_fY = atof( words->GetWord( 2 ) );
            m_fZ = atof( words->GetWord( 3 ) );
            bIsCast = atoi( words->GetWord(4) );
        }
        break;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->PlayEffect( m_strName.c_str(),  m_fX, m_fY, m_fZ, bIsCast );
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strName;
float m_fX;
float m_fY;
float m_fZ;
bool  bIsCast;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// ShowIntonateBar time
SCRIPT_BEGIN( ShowIntonateBar )
virtual BOOL Create( WordParser* words )
{
    m_dwTime       = 0;
    m_nStringID    = 0;
    m_nActionID    = 0;
    m_nType        = 0;
    m_nID          = 0;

    if( words->GetWordCount() == 2 )
    {
        m_dwTime    = atoi( words->GetWord(0) );
        m_nStringID = atoi( words->GetWord(1) );
        m_nActionID = 0;
        return TRUE;
    }

    if( words->GetWordCount() == 3 )
    {
        m_dwTime    = atoi( words->GetWord(0) );
        m_nStringID = atoi( words->GetWord(1) );
        m_nActionID = atoi( words->GetWord(2) );
        return TRUE;
    }

    if( words->GetWordCount() == 5 )
    {
        m_dwTime    = atoi( words->GetWord(0) );
        m_nStringID = atoi( words->GetWord(1) );
        m_nActionID = atoi( words->GetWord(2) );
        m_nType     = atoi( words->GetWord(3) );
        m_nID       = atoi( words->GetWord(4) );
        return TRUE;
    }
    
    GetScriptInterface()->Printf( "error:ShowIntonateBar" );
    return FALSE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ShowIntonateBar( m_dwTime, m_nStringID, m_nActionID, m_nType, m_nID );
    //
    vm->NextIP();
    vm->Hangup();
}

SCRIPT_PARAM
DWORD m_dwTime   ;
int   m_nStringID;
int   m_nActionID;
int   m_nType    ;
int   m_nID      ;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddPkValue
SCRIPT_BEGIN( AddPkValue )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:AddPkValue" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    dailypkvalue = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddPkValue(nValue,dailypkvalue);
    vm->NextIP();
}

SCRIPT_PARAM
int nValue;
int dailypkvalue;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// DecPkValue
SCRIPT_BEGIN( DecPkValue )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:DecPkValue" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->DecPkValue(nValue);
    vm->NextIP();
}

SCRIPT_PARAM
int nValue;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// SetPkValue
SCRIPT_BEGIN( SetPkValue )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:SetPkValue" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetPkValue(nValue); 
    vm->NextIP();
}

SCRIPT_PARAM
int nValue;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetPkValue
SCRIPT_BEGIN( GetPkValue )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetPkValue" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->GetPkValue();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetPkState
SCRIPT_BEGIN( GetPkState )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetPkState" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nState = GetScriptInterface()->GetPkState();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nState );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetPkMode
SCRIPT_BEGIN( GetPkMode )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetPkMode" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMode = GetScriptInterface()->GetPkMode();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nMode );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// SetPkMode
SCRIPT_BEGIN( SetPkMode )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:SetPkMode" );
        return FALSE;
    }
    nMode = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetPkMode(nMode); 
    vm->NextIP();
}

SCRIPT_PARAM
int nMode;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// OPenClientUI
SCRIPT_BEGIN( OpenClientUI )
virtual BOOL Create( WordParser* words )
{
    nUIFlag     = 0;
    nOpenType   = 0;
    nOpenParam  = 0;

    if( words->GetWordCount() == 1 )
    {
        nUIFlag = atoi(words->GetWord(0));
        return TRUE;
    }

    if( words->GetWordCount() == 3 )
    {
        nUIFlag     = atoi(words->GetWord(0));
        nOpenType   = atoi(words->GetWord(1));
        nOpenParam  = atoi(words->GetWord(2));
        return TRUE;
    }
    
    GetScriptInterface()->Printf( "error:OpenUI" );
    return FALSE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->OpenClientUI( nUIFlag, nOpenType, nOpenParam );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int nUIFlag     ;
int nOpenType   ;
int nOpenParam  ;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetBagSize
SCRIPT_BEGIN( GetBagSize )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetBagSize" );
        return FALSE;
    }
    _bagType = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSize = GetScriptInterface()->GetBagSize( _bagType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nSize );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
    int _bagType;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// AddBagSize
SCRIPT_BEGIN( AddBagSize )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:AddBagSize" );
        return FALSE;
    }
    _bagType = atoi(words->GetWord(0));
    m_nSize = atoi(words->GetWord(1));

    if ( m_nSize <= 0 )
    { return FALSE; }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddBagSize( _bagType, m_nSize );

    vm->NextIP();
}

SCRIPT_PARAM
int _bagType;
int m_nSize;
SCRIPT_END

////////////////////////////////////////////////////////////////////////////
//// NotarizationSuccess
SCRIPT_BEGIN( NotarizationSuccess )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 3 )
    {
        GetScriptInterface()->Printf( "error:NotarizationSuccess" );
        return FALSE;
    }

    nIndex1 = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
    nIndex2 = GetScriptVarMgr()->GetVarId( words->GetWord(1) );
    nValue = atoi(words->GetWord(2));
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int id1 = GetScriptInterface()->GetVar( nIndex1 );
    int id2 = GetScriptInterface()->GetVar( nIndex2 );
    GetScriptInterface()->NotarizationSuccess(id1,id2,nValue);
    vm->NextIP();
}

SCRIPT_PARAM
int    nIndex1;
int nIndex2;
int nValue;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// NoticeNotarizationResult
SCRIPT_BEGIN(NoticeNotarizationResult)
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 9 )
    {
        GetScriptInterface()->Printf( "error:NoticeNotarizationResult" );
        return FALSE;
    }
    iPlayer1 = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
    pszAnd    = words->GetWord(1);
    iPlayer2 = GetScriptVarMgr()->GetVarId( words->GetWord(2) );
    pszText    =    words->GetWord(3);
    nMapId    =    atoi(words->GetWord(4));
    nX            =    atoi(words->GetWord(5));
    nY            =    atoi(words->GetWord(6));
    time        =    atoi(words->GetWord(7));
    color        = strtoul(words->GetWord(8), NULL, 16);
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nId1 = GetScriptInterface()->GetVar( iPlayer1 );
    int nId2 = GetScriptInterface()->GetVar( iPlayer2 );
    GetScriptInterface()->NoticeNotarizationResult(nId1,pszAnd.c_str(),nId2,pszText.c_str(),nMapId,nX,nY,time,color);
    vm->NextIP();
}

SCRIPT_PARAM
int iPlayer1;
std::string pszAnd;
int iPlayer2;
std::string pszText;
int nMapId;
int nX;
int nY;
DWORD time;
DWORD color;
SCRIPT_END

////IsEverybodyAllHere
SCRIPT_BEGIN( IsEverybodyAllHere )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:[KEY]" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    bool result = GetScriptInterface()->IsEverybodyAllHere();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END
////////////////////////////////////////////////////////////////////////////
// IsEverybodyAllReady
SCRIPT_BEGIN(IsEverybodyAllReady)
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        GetScriptInterface()->Printf( "error:IsEverybodyAllReady" );
        return FALSE;
    }
    iplayer = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
    isociety = atoi(words->GetWord(1));
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int id1 = GetScriptInterface()->GetVar( iplayer );
    bool result = GetScriptInterface()->IsEverybodyAllReady(id1,isociety);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int    iplayer;
int    isociety;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// IsMapActive mapid
SCRIPT_BEGIN( IsMapActive )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:IsMapActive" );
        return FALSE;
    }
    m_nMapId = atoi(words->GetWord(0));
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->IsMapActive( m_nMapId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMapId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetMapCount mapid
SCRIPT_BEGIN( GetMapCount )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:GetMapCount" );
        return FALSE;
    }
    m_nMapId = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nCount = GetScriptInterface()->GetMapCount( m_nMapId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nCount );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMapId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//  GetOfflineHookExp 
SCRIPT_BEGIN(  GetOfflineHookExp )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:GetGetOfflineHookExp" );
        return FALSE;
    }
    m_nHookLevel = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->GetOfflineHookExp( m_nHookLevel );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nHookLevel;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//  IsOfflinePassOneWeek 
SCRIPT_BEGIN(  IsOfflinePassOneWeek )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() > 0 )
    {
        GetScriptInterface()->Printf( "error:IsOfflinePassOneWeek" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nIndex = GetScriptInterface()->IsOfflinePassOneWeek();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nIndex );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//  AddSysDoubleExpTime 
SCRIPT_BEGIN(  AddSysDoubleExpTime )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:AddSysDoubleExpTime" );
        return FALSE;
    }
    m_nMinute = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nRetValue = GetScriptInterface()->AddSysDoubleExpTime( m_nMinute );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nRetValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMinute;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//  AddItemDoubleExpTime 
SCRIPT_BEGIN(  AddItemDoubleExpTime )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:AddItemDoubleExpTime" );
        return FALSE;
    }
    m_nMinute = atoi( words->GetWord(0) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nRetValue = GetScriptInterface()->AddItemDoubleExpTime( m_nMinute );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nRetValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMinute;
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// CreateProtect
SCRIPT_BEGIN( CreateProtect )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR,"error:CreateProtect Count != 2");
        return FALSE;
    }

    m_nMonsterId = atoi( words->GetWord(0) );
    const char* szVarId = words->GetWord(1);
    if ( WordParser::IsNumber(szVarId) )
    {
        m_VarId.SetNumber( atoi(szVarId) );
        m_VarId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVarId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:CreateProtect");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }
	
	m_bCanRide = atoi( words->GetWord(2) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    GetScriptInterface()->CreateProtectChar( m_nMonsterId , nVarId, m_bCanRide );
    vm->NextIP();
}

SCRIPT_PARAM
int    m_nMonsterId;
bool   m_bCanRide;
//int    varId;
CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetProtect
SCRIPT_BEGIN( GetProtect )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:GetProtect" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nIndex = GetScriptInterface()->GetProtectCharMonsterIndex();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nIndex );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// LostProtect
SCRIPT_BEGIN( LostProtect )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        GetScriptInterface()->Printf( "error:LostProtect" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->LostProtectChar();
    //
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


//////////////////////////////////////////////////////////////////////////
// GetProtect
SCRIPT_BEGIN( GetRankLevel )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:GetRankLevel" );
        return FALSE;
    }
    index = atoi(words->GetWord(0));
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nIndex = GetScriptInterface()->GetRankLevel(index);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nIndex );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int index;
SCRIPT_END


// IsHaveStatus statusID
SCRIPT_BEGIN( IsHaveStatus )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:IsHaveStatus" );
        return FALSE;
    }
    shStatusID = atoi(words->GetWord(0));
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->IsHaveStatus( shStatusID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
short shStatusID;
SCRIPT_END

// AddIntegral
SCRIPT_BEGIN( AddIntegralMax )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:AddIntegral" );
        return FALSE;
    }
    m_nIntegralMax = atoi(words->GetWord(0));
    if ( m_nIntegralMax <= 0 )
    {
        GetScriptInterface()->Printf( "error:AddIntegral" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddPlayerIntegralMax( m_nIntegralMax);
    //
    vm->NextIP();
}

SCRIPT_PARAM
int    m_nIntegralMax;
SCRIPT_END
SCRIPT_BEGIN( AddGuildBuff )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddGuildBuff" );
        return FALSE;
    }
    m_nStatusId = atoi( words->GetWord(0) );
    m_nStatusLevel = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddStatusByScript(m_nStatusId, m_nStatusLevel);
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nStatusId;
int m_nStatusLevel;
SCRIPT_END

SCRIPT_BEGIN( SetStatusbyScript )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetStatusbyScript" );
        return FALSE;
    }
    m_nStatusId = atoi( words->GetWord(0) );
    m_nStatusLevel = atoi( words->GetWord(1) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetStatusByScript(m_nStatusId, m_nStatusLevel);
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nStatusId;
int m_nStatusLevel;
SCRIPT_END

BOOL CScriptCmd_HaveThisItem_Byid::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:HaveThisItem" );
        return FALSE;
    }
    const char* szWord = words->GetWord( 0 );
    if( WordParser::IsNumber( szWord ) )
    {
        m_ItemId.SetNumber( atoi( szWord ) );
        m_ItemId.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "HaveThisItem error" );
            return FALSE;
        }
        m_ItemId.SetNumber( nKey );
        m_ItemId.SetIsKey( true );
    }

    return TRUE;
}

void CScriptCmd_HaveThisItem_Byid::Execute( CScriptVM* vm )
{
    int nItemId = 0;
    if ( m_ItemId.IsKey() )
    {
        int nKey = m_ItemId.GetNumber();
        nItemId = GetScriptInterface()->GetVar( nKey );
    }
    else
    {
        nItemId = m_ItemId.GetNumber();
    }
    if ( nItemId <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:HaveThisItem %d", nItemId );
        return;
    }

    int retNum = GetScriptInterface()->HaveThisItem_Byid( nItemId );

    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( retNum );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP( );
}

BOOL CScriptCmd_RemoveThisItem_Byid::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:RemoveThisItem" );
        return FALSE;
    }
    //m_ItemId = atoi(words->GetWord( 0 ));
    //m_ItemNumber = atoi( words->GetWord( 1 ) );
    const char* szItemId = words->GetWord(0);
    if ( WordParser::IsNumber(szItemId) )
    {
        m_ItemId.SetNumber( atoi(szItemId) );
        m_ItemId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szItemId);
        if (nKey == -1)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "RemoveThisItem_Byid param 0 error" );
            return FALSE;
        }
        m_ItemId.SetNumber(nKey);
        m_ItemId.SetIsKey(true);
    }

    const char* szItemNum = words->GetWord(1);
    if ( WordParser::IsNumber(szItemNum) )
    {
        m_ItemNumber.SetNumber( atoi(szItemNum) );
        m_ItemNumber.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szItemNum);
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "RemoveThisItem_Byid param 1 error" );
            return FALSE;
        }
        m_ItemNumber.SetNumber(nKey);
        m_ItemNumber.SetIsKey(true);
    }
    //
    return TRUE;
}

void CScriptCmd_RemoveThisItem_Byid::Execute( CScriptVM* vm )
{
    int nItemId = 0;
    if ( m_ItemId.IsKey() )
    {
        int nKey = m_ItemId.GetNumber();
        nItemId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nItemId = m_ItemId.GetNumber();
    }
    
    int nItemNum = 0;
    if ( m_ItemNumber.IsKey() )
    {
        int nKey = m_ItemNumber.GetNumber();
        nItemNum = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nItemNum = m_ItemNumber.GetNumber();
    }
    if ( nItemId <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "RemoveThisItem_Byid ItemId[%d] error", nItemId );
        return;
    }
    GetScriptInterface()->RemoveThisItem_Byid( nItemId, nItemNum );
    vm->NextIP( );
}

BOOL CScriptCmd_IsThisItemEquipped_Byid::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsThisItemEquipped" );
        return FALSE;
    }
    m_ItemId = atoi(words->GetWord( 0 ));    
    return TRUE;
}

void CScriptCmd_IsThisItemEquipped_Byid::Execute( CScriptVM* vm )
{
    BOOL bEquipped = GetScriptInterface()->IsThisItemEquipped_Byid( m_ItemId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( bEquipped );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP( );
}

/////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( Get_Player_Count_Var )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:Get_player_Count_Var" );
        return FALSE;
    }

    nCountVarId = atoi( words->GetWord( 0 ) );
    if( nCountVarId < 0 ||
        nCountVarId > 2999 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "cast Get_player_Count_Var failed, quest id out of range" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->GetPlayerCountVar( nCountVarId, m_nReturnKey );
    //
    vm->NextIP();
}

SCRIPT_PARAM
int nCountVarId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetStorageItemGrid
SCRIPT_BEGIN( GetStorageItemGrid )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetStorageItemGrid err" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nStakeValue = GetScriptInterface()->GetStorageItemGrid();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nStakeValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetStorageMountGrid
SCRIPT_BEGIN( GetStorageMountGrid )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetStorageMountGrid err" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nStakeValue = GetScriptInterface()->GetStorageMountGrid();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nStakeValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddStorageItemGrid
SCRIPT_BEGIN( AddStorageItemGrid )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddStorageItemGrid err" );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber( szWord ) )
    {
        _param.SetNumber( atoi(szWord));
        _param.SetIsKey( false );
    }
    else
    {
        _param.SetNumber( GetScriptVarMgr()->GetVarId( szWord ) );
        _param.SetIsKey( true );
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    unsigned char nValue = 0;
    if ( _param.IsKey() )
    {
        int nKeyId = _param.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKeyId);
    }
    else
    {
        nValue = _param.GetNumber();
    }

    int nStakeValue = GetScriptInterface()->AddStorageItemGrid( nValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nStakeValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param _param;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddStorageMountGrid
SCRIPT_BEGIN( AddStorageMountGrid )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddStorageMountGrid err" );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber( szWord ) )
    {
        _param.SetNumber( atoi(szWord));
        _param.SetIsKey( false );
    }
    else
    {
        _param.SetNumber( GetScriptVarMgr()->GetVarId( szWord ) );
        _param.SetIsKey( true );
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    unsigned char nValue = 0;
    if ( _param.IsKey() )
    {
        int nKeyId = _param.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKeyId);
    }
    else
    {
        nValue = _param.GetNumber();
    }

    int nStakeValue = GetScriptInterface()->AddStorageMountGrid( nValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nStakeValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param _param;
SCRIPT_END

SCRIPT_BEGIN( UpdateDailyPkValueMax )
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        GetScriptInterface()->Printf( "error:[UpdateDailyPkValueMax]" );
        return FALSE;
    }
    m_nOffset = atoi( words->GetWord( 0 ) );
    return TRUE;
}
virtual void Execute(CScriptVM* vm )
{
    GetScriptInterface()->UpdatePkValueMaxDaily(m_nOffset);
    vm->NextIP();
}
SCRIPT_PARAM
int m_nOffset;
SCRIPT_END


SCRIPT_BEGIN(delayscript)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf( "error:[delayscript]" );
        return FALSE;
    }
    delaytime = atoi(pWords->GetWord(0));
    scriptindex = atoi(pWords->GetWord(1));
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->InsertDelayScript(delaytime,scriptindex);
    pVM->NextIP();
}
SCRIPT_PARAM
int delaytime;
int scriptindex;
SCRIPT_END


SCRIPT_BEGIN(ScriptLog)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf( "error:[ScriptLog]" );
        return FALSE;
    }
    strKeyWord = pWords->GetWord(0);
    strContent = pWords->GetWord(1);
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->ScriptLog(strKeyWord.c_str(),strContent.c_str());
    pVM->NextIP();
}
SCRIPT_PARAM
std::string strKeyWord;
std::string strContent;
SCRIPT_END

SCRIPT_BEGIN(delayscriptforplayer)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf( "error:[delayscriptforplayer]" );
        return FALSE;
    }
    delaytime = atoi(pWords->GetWord(0));
    scriptindex = atoi(pWords->GetWord(1));
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->InsertDelayScript(delaytime,scriptindex,true);
    pVM->NextIP();
}
SCRIPT_PARAM
int delaytime;
int scriptindex;
SCRIPT_END

SCRIPT_BEGIN(killdelayscript)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf("error:[killdelayscript]");
        return FALSE;
    }
    scriptindex = atoi(pWords->GetWord(0));
    forplayer = atoi(pWords->GetWord(1));
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->RemoveDelayScript(scriptindex,forplayer);
    pVM->NextIP();
}
SCRIPT_PARAM
int scriptindex;
int forplayer;
SCRIPT_END

SCRIPT_BEGIN(showtimetop)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 1)
    {
        GetScriptInterface()->Printf("error:[showtimetop]");
        return FALSE;
    }
    showtime = atoi(pWords->GetWord(0));
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->ShowTimeTop(showtime);
    pVM->NextIP();
}
SCRIPT_PARAM
DWORD showtime;
SCRIPT_END

SCRIPT_BEGIN(shutdowntimetop)
virtual BOOL Create(WordParser* pWords)
{
    if (pWords->GetWordCount() != 0)
    {
        GetScriptInterface()->Printf("error:[showtimetop]");
        return FALSE;
    }    
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->ShutDownTimeTop();
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

// BeckonPlayer
SCRIPT_BEGIN(BeckonPlayer)
virtual BOOL Create(WordParser* words)
{
    if (words->GetWordCount() != 1)
    {
        GetScriptInterface()->Printf("error:[BeckonPlayer]");
        return FALSE;
    }
    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber( szWord ) )
    {
        _param.SetNumber( atoi(szWord));
        _param.SetIsKey( false );
    }
    else
    {
        _param.SetNumber( GetScriptVarMgr()->GetVarId( szWord ) );
        _param.SetIsKey( true );
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nPlayerId = -1;
    if ( _param.IsKey() )
    {
        int nKeyId = _param.GetNumber();
        nPlayerId = GetScriptInterface()->GetVar(nKeyId);
    }
    else
    {
        nPlayerId = _param.GetNumber();
    }

    GetScriptInterface()->BeckonPlayer( nPlayerId );
    pVM->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param _param;
SCRIPT_END

// CallScriptTeam
SCRIPT_BEGIN(CallScriptTeam)
virtual BOOL Create(WordParser* words)
{
    if (words->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf("error:[CallScriptTeam]");
        return FALSE;
    }
    m_strFileName = words->GetWord( 0 );
    m_nEnterId = atoi(words->GetWord( 1 ));
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{   
    GetScriptInterface()->CallScriptTeam( m_strFileName.c_str(), m_nEnterId);
    pVM->NextIP();
}

SCRIPT_PARAM
std::string m_strFileName;
int            m_nEnterId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddLevel
SCRIPT_BEGIN(AddLevel)
virtual BOOL Create(WordParser* words)
{
    if (words->GetWordCount() != 1)
    {
        GetScriptInterface()->Printf("error:[AddLevel]");
        return FALSE;
    }
    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber( szWord ) )
    {
        _param.SetNumber( atoi(szWord));
        _param.SetIsKey( false );
    }
    else
    {
        _param.SetNumber( GetScriptVarMgr()->GetVarId( szWord ) );
        _param.SetIsKey( true );
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nChangeLevel = 0;
    if ( _param.IsKey() )
    {
        int nKeyId = _param.GetNumber();
        nChangeLevel = GetScriptInterface()->GetVar(nKeyId);
    }
    else
    {
        nChangeLevel = _param.GetNumber();
    }

    GetScriptInterface()->AddLevel( nChangeLevel );
    pVM->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param _param;
SCRIPT_END

SCRIPT_BEGIN(IsInArea)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsInArea]" );
        return FALSE;
    }
    //for (int i = 0;i<4;++i)
    //{
    //    const char* szWord = words->GetWord( i );
    //    if (WordParser::IsNumber(szWord))
    //    {
    //        switch (i)
    //        {
    //        case 0:
    //            m_lpx = atoi(szWord);
    //            break;
    //        case 1:
    //            m_lpy = atoi(szWord);
    //            break;
    //        case 2:
    //            m_rpx = atoi(szWord);
    //            break;
    //        case 3:
    //            m_rpy = atoi(szWord);
    //            break;
    //        }
    //    }
    //    else
    //        return FALSE;
    //}
    for (int i=0; i<4; ++i)
    {
        const char* szWord = words->GetWord(i);
        switch ( i )
        {
        case 0:
            {
                if ( WordParser::IsNumber(szWord) )
                {
                    m_lpx.SetNumber( atoi(szWord) );
                    m_lpx.SetIsKey(false);
                }
                else
                {
                    int nKey = GetScriptVarMgr()->GetVarId(szWord);
                    if (nKey == -1)
                    {
                        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsInArea left X");
                        return FALSE;
                    }
                    m_lpx.SetNumber(nKey);
                    m_lpx.SetIsKey(true);
                }
            }
        	break;
        case 1:
            {
                if ( WordParser::IsNumber(szWord) )
                {
                    m_lpy.SetNumber( atoi(szWord) );
                    m_lpy.SetIsKey(false);
                }
                else
                {
                    int nKey = GetScriptVarMgr()->GetVarId(szWord);
                    if (nKey == -1)
                    {
                        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsInArea left X");
                        return FALSE;
                    }
                    m_lpy.SetNumber(nKey);
                    m_lpy.SetIsKey(true);
                }
            }
            break;
        case 2:
            {
                if ( WordParser::IsNumber(szWord) )
                {
                    m_rpx.SetNumber( atoi(szWord) );
                    m_rpx.SetIsKey(false);
                }
                else
                {
                    int nKey = GetScriptVarMgr()->GetVarId(szWord);
                    if (nKey == -1)
                    {
                        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsInArea left X");
                        return FALSE;
                    }
                    m_rpx.SetNumber(nKey);
                    m_rpx.SetIsKey(true);
                }
            }
            break;
        case 3:
            {
                if ( WordParser::IsNumber(szWord) )
                {
                    m_rpy.SetNumber( atoi(szWord) );
                    m_rpy.SetIsKey(false);
                }
                else
                {
                    int nKey = GetScriptVarMgr()->GetVarId(szWord);
                    if (nKey == -1)
                    {
                        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:IsInArea left X");
                        return FALSE;
                    }
                    m_rpy.SetNumber(nKey);
                    m_rpy.SetIsKey(true);
                }
            }
            break;
        }
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int isInArea = 0;
    //isInArea = static_cast<int>(GetScriptInterface()->IsInArea(m_lpx,m_lpy,m_rpx ,m_rpy));
    int nlpX = 0;
    int nlpY = 0;
    int nrpX = 0;
    int nrpY = 0;
    if ( m_lpx.IsKey() )
    {
        int nKey = m_lpx.GetNumber();
        nlpX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nlpX = m_lpx.GetNumber();
    }

    if ( m_lpy.IsKey() )
    {
        int nKey = m_lpy.GetNumber();
        nlpY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nlpY = m_lpy.GetNumber();
    }

    if ( m_rpx.IsKey() )
    {
        int nKey = m_rpx.GetNumber();
        nrpX = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nrpX = m_rpx.GetNumber();
    }

    if ( m_rpy.IsKey() )
    {
        int nKey = m_rpy.GetNumber();
        nrpY = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nrpY = m_rpy.GetNumber();
    }
    
    isInArea = static_cast<int>(GetScriptInterface()->IsInArea(nlpX, nlpY, nrpX ,nrpY));
    if (m_nReturnKey != -1)
    {
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &isInArea );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
//int            m_lpx,m_lpy,m_rpx,m_rpy;
CScriptCmd__SetVar::Param m_lpx;    // 左边X,Y
CScriptCmd__SetVar::Param m_lpy;
CScriptCmd__SetVar::Param m_rpx;
CScriptCmd__SetVar::Param m_rpy;
SCRIPT_END

SCRIPT_BEGIN(SelfPosX)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[SelfPosX]" );
        return FALSE;
    }
    return TRUE;
}
virtual void Execute( CScriptVM* pVM )
{
    int PosX = GetScriptInterface()->SelfPosX();
    if (m_nReturnKey != -1)
    {
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &PosX );
    }
    pVM->NextIP();
}
SCRIPT_PARAM

SCRIPT_END


SCRIPT_BEGIN(SelfPosY)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[SelfPosY]" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int PosY =  GetScriptInterface()->SelfPosY();
    if (m_nReturnKey != - 1)
    {
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &PosY );
    }
    pVM->NextIP();
}
SCRIPT_PARAM

SCRIPT_END

SCRIPT_BEGIN(DropItem)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() < 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[DropItem] " );
        return FALSE;
    }
	nobelong = true;
    for (int i = 0;i<words->GetWordCount();++i)
    {
        const char* szWord = words->GetWord( i );
        if (WordParser::IsNumber(szWord))
        {
            switch (i)
            {
            case 0:
                ItemId = atoi(szWord);
                break;
            case 1:
                ItemNum = atoi(szWord);
                break;
			case 2:
				nobelong = atoi(szWord);
				break;
            }
        }
        else
            return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->DropItem(ItemId,ItemNum,nobelong);
    
    pVM->NextIP();
}
SCRIPT_PARAM
    int ItemId;
    int ItemNum;
	bool nobelong;
SCRIPT_END

SCRIPT_BEGIN(AddMount)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[AddMount] " );
        return FALSE;
    }
    
    const char* szWord = words->GetWord( 0 );
    nMountId = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->AddMount( nMountId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
    int nMountId;
SCRIPT_END

SCRIPT_BEGIN(AddPet)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[AddPet] " );
        return FALSE;
    }

    const char* szWord1 = words->GetWord( 0 );
    monsterId = atoi(szWord1); 

    const char* szWord2 = words->GetWord( 1 );
    quality   = atoi(szWord2); 

    const char* szWord3 = words->GetWord( 2 );
    sex       = atoi(szWord3); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->AddPet( monsterId, quality, sex );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
int monsterId;
int quality;
int sex;
SCRIPT_END

SCRIPT_BEGIN(AddPetIdentify)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[AddPetIdentify] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    petType = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->AddPetIdentify( petType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
int petType;
SCRIPT_END

SCRIPT_BEGIN(IsPetFull)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsPetFull] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->IsPetFull();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN(GetPetNumber)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[GetPetNumber] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->GetPetNumber();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN(HaveBreedPet)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[HaveBreedPet] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->HaveBreedPet();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN(PetBreedAcquire)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[PetBreedAcquire] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->PetBreedAcquire();
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetPetMaxLevel
SCRIPT_BEGIN(GetPetMaxLevel)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[GetPetMaxLevel] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->GetPetMaxLevel();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetActivePetIndex
SCRIPT_BEGIN(GetActivePetIndex)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[GetActivePetIndex] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->GetActivePetIndex();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// GetDaoxing
SCRIPT_BEGIN(GetDaoxing)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[GetDaoxing] " );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->GetDaoxing();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// AddDaoxing
SCRIPT_BEGIN(AddDaoxing)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[AddDaoxing] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    nValue = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    GetScriptInterface()->AddDaoxing( nValue );
    pVM->NextIP();
}
SCRIPT_PARAM
int nValue;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//HasMount
SCRIPT_BEGIN(HasMount)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[HasMount] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    nMountId = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->HasMount( nMountId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
int nMountId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//RestoreMountEnjoyment
SCRIPT_BEGIN(RestoreMountEnjoyment)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RestoreMountEnjoyment] " );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nResult = GetScriptInterface()->RestoreMountEnjoyment();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN(CreateScriptNpc)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 5 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    if (!words->IsNumber( szWord ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Param 1 " );
        return FALSE;
    }
    else
    {
        nNpcId = atoi(szWord); 
    }

    const char* szMapId = words->GetWord( 1 );
    if (!words->IsNumber( szMapId ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Param 2" );
        return FALSE;
    }
    else
    {
        nMapId = atoi(szMapId); 
    }

    const char* szPosX = words->GetWord( 2 );
    if (!words->IsNumber( szPosX ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Param 3" );
        return FALSE;
    }
    else
    {
        nPosX = atoi(szPosX); 
    }

    const char* szPosY = words->GetWord( 3 );
    if (!words->IsNumber( szPosY ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Param 4" );
        return FALSE;
    }
    else
    {
        nPosY = atoi(szPosY); 
    }

    const char* szTime = words->GetWord( 4 );
    if (!words->IsNumber( szTime ))
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Param 4" );
        return FALSE;
    }
    else
    {
        unOnTime = atoi(szTime); 
        if (unOnTime < 1 && unOnTime > 86400)
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[CreateScriptNpc]:Online time too long!" );
            return FALSE;
        }
        unOnTime = unOnTime * 1000;
    }


    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
	//by vvx 2012.8.2  开启脚本创建NPC,不晓得有没有问题
	BOOL ReturnKey = GetScriptInterface()->CreateScriptNpc(nNpcId,nMapId,nPosX,nPosY,unOnTime);
	if (m_nReturnKey > -1)
	{
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &ReturnKey );
	}
	pVM->NextIP();
}
SCRIPT_PARAM
int nNpcId;
int nMapId;
int nPosX;
int nPosY;
unsigned int unOnTime;
SCRIPT_END

//SCRIPT_BEGIN(DeleteScriptNpc)
//virtual BOOL Create(WordParser* words)
//{
//    if( words->GetWordCount() != 2 )
//    {
//        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[DeleteScriptNpc] " );
//        return FALSE;
//    }
//
//    const char* szWord1 = words->GetWord( 0 );
//    if (szWord1&&words->IsNumber(szWord1))
//    {
//        nBeginNpcId = atoi(szWord1);
//    }
//    else
//    {
//        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[DeleteScriptNpc]:Param1 " );
//        return FALSE;
//    }
//    
//    const char* szWord2 = words->GetWord( 1 );
//    if (szWord2&&words->IsNumber(szWord2))
//    {
//        nEndNpcId = atoi(szWord2);
//    }
//    else
//    {
//        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[DeleteScriptNpc]:Param2 " );
//        return FALSE;
//    }
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* pVM )
//{
//    BOOL ReturnKey = GetScriptInterface()->DeleteScriptNpc(nBeginNpcId,nEndNpcId);
//    if (m_nReturnKey > -1)
//    {
//        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &ReturnKey );
//    }
//    pVM->NextIP();
//}
//SCRIPT_PARAM
//int nBeginNpcId;
//int nEndNpcId;
//SCRIPT_END


SCRIPT_BEGIN(RecordTime)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RecordTime] " );
        return FALSE;
    }
    
    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:RecordTime");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    bool bResult = GetScriptInterface()->RecordTime( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
    //int nVarId;
    CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END

SCRIPT_BEGIN(IsExpired)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 4)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsExpired] " );
        return FALSE;
    }
    
    const char* szWord = NULL;
    szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsExpired");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    szWord = words->GetWord( 1 );
    keyHour = atoi(szWord); 

    szWord = words->GetWord( 2 );
    keyMinute = atoi(szWord); 

    szWord = words->GetWord( 3 );
    minDuration = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    bool bResult = GetScriptInterface()->IsExpired( nVarId, keyHour, keyMinute, minDuration );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
    //int nVarId;
    CScriptCmd__SetVar::Param m_VarId;
    int keyHour;
    int keyMinute;
    int minDuration;
SCRIPT_END

SCRIPT_BEGIN(RecordTeamTime)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RecordTeamTime] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    //nVarId = atoi(szWord); 
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:RecordTeamTime");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    bool bResult = GetScriptInterface()->RecordTeamTime( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
//int nVarId;
CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END

SCRIPT_BEGIN(IsTeamExpired)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 4)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsTeamExpired] " );
        return FALSE;
    }

    const char* szWord = NULL;
    szWord = words->GetWord( 0 );
    nVarId = atoi(szWord); 

    szWord = words->GetWord( 1 );
    keyHour = atoi(szWord); 

    szWord = words->GetWord( 2 );
    keyMinute = atoi(szWord); 

    szWord = words->GetWord( 3 );
    minDuration = atoi(szWord); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->IsTeamExpired( nVarId, keyHour, keyMinute, minDuration );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
int nVarId;
int keyHour;
int keyMinute;
int minDuration;
SCRIPT_END

SCRIPT_BEGIN(ClearTeamExpiredVar)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 5)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[ClearTeamExpiredVar] " );
        return FALSE;
    }

    const char* szWord = NULL;
    szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearTeamExpiredVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    szWord = words->GetWord( 1 );
    keyHour = atoi(szWord); 

    szWord = words->GetWord( 2 );
    keyMinute = atoi(szWord); 

    szWord = words->GetWord( 3 );
    minDuration = atoi(szWord); 

    //szWord = words->GetWord( 4 );
    //nClearVarId = atoi(szWord);
    szWord = words->GetWord(4);
    if ( WordParser::IsNumber(szWord) )
    {
        m_ClearVarId.SetNumber( atoi(szWord) );
        m_ClearVarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearTeamExpiredVar");
            return FALSE;
        }
        m_ClearVarId.SetNumber(nKey);
        m_ClearVarId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    int nClearVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    if (m_ClearVarId.IsKey())
    {
        int nKey = m_ClearVarId.GetNumber();
        nClearVarId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nClearVarId = m_ClearVarId.GetNumber();
    }
    GetScriptInterface()->ClearTeamExpiredVar( nVarId, keyHour, keyMinute, minDuration, nClearVarId );
    pVM->NextIP();
}
SCRIPT_PARAM
//int nVarId;
CScriptCmd__SetVar::Param m_VarId;
int keyHour;
int keyMinute;
int minDuration;
//int nClearVarId;
CScriptCmd__SetVar::Param m_ClearVarId;
SCRIPT_END

///////////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN(RecordTimeVar)
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RecordTimeVar] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:RecordTime");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    GetScriptInterface()->RecordTimeVar( nVarId );
    pVM->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END


SCRIPT_BEGIN(IsTimeVarPassOneDay)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsTimeVarPassOneDay] " );
        return FALSE;
    }

    const char* szWord = NULL;
    szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:IsExpired");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    bool bResult = GetScriptInterface()->IsTimeVarPassOneDay( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END

SCRIPT_BEGIN(RecordTeamTimeVar)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RecordTeamTimeVar] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:RecordTeamTimeVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    GetScriptInterface()->RecordTeamTimeVar( nVarId );
    pVM->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param m_VarId;
SCRIPT_END

SCRIPT_BEGIN(IsTeamTimeVarPassOneDay)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsTeamTimeVarPassOneDay] " );
        return FALSE;
    }

    nVarId = atoi( words->GetWord( 0 ) ); 
    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->IsTeamTimeVarPassOneDay( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
SCRIPT_PARAM
int nVarId;
SCRIPT_END

SCRIPT_BEGIN(ClearTeamTimeVar)
virtual BOOL Create(WordParser* words)
{
    if( words->GetWordCount() != 2)
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[ClearTeamTimeVar] " );
        return FALSE;
    }

    const char* szWord = NULL;
    szWord = words->GetWord( 0 );
    if ( WordParser::IsNumber(szWord) )
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearTeamTimeVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    szWord = words->GetWord(1);
    if ( WordParser::IsNumber(szWord) )
    {
        m_ClearVarId.SetNumber( atoi(szWord) );
        m_ClearVarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearTeamTimeVar");
            return FALSE;
        }
        m_ClearVarId.SetNumber(nKey);
        m_ClearVarId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* pVM )
{
    int nVarId = 0;
    int nClearVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }

    if (m_ClearVarId.IsKey())
    {
        int nKey = m_ClearVarId.GetNumber();
        nClearVarId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nClearVarId = m_ClearVarId.GetNumber();
    }
    GetScriptInterface()->ClearTeamTimeVar( nVarId, nClearVarId );
    pVM->NextIP();
}
SCRIPT_PARAM
//int nVarId;
CScriptCmd__SetVar::Param m_VarId;
CScriptCmd__SetVar::Param m_ClearVarId;
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
//
SCRIPT_BEGIN( RecordExploitTime )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() > 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "RecordExploitTime error" );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->RecordExploitTime();
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
//
SCRIPT_BEGIN( CreateStage )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 2 || words->GetWordCount() > 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreateStage error" );
        return FALSE;
    }
    m_dwMapDataID     = atoi( words->GetWord( 0 ) );
    m_nMapCount       = atoi( words->GetWord( 1 ) );
    m_bUsePlayerLevel = false;
    m_ustMapLevel     = 0;

    if ( words->GetWordCount() == 3 )
    {
        m_bUsePlayerLevel = atoi( words->GetWord( 2 ) );
    }
    else if ( words->GetWordCount() == 4 )
    {
        m_bUsePlayerLevel = atoi( words->GetWord( 2 ) );
        m_ustMapLevel = atoi( words->GetWord( 3 ) );
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->ScriptCreateStage( m_dwMapDataID, m_nMapCount, m_bUsePlayerLevel, m_ustMapLevel );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
unsigned int m_dwMapDataID;
unsigned int m_nMapCount;
bool m_bUsePlayerLevel;       
unsigned short m_ustMapLevel;
SCRIPT_END

SCRIPT_BEGIN( IsStageExist )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsStageExist error" );
        return FALSE;
    }
    m_ustMapDataID = atoi( words->GetWord( 0 ) );
  
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsStageExist( m_ustMapDataID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
unsigned short m_ustMapDataID;
SCRIPT_END

SCRIPT_BEGIN( IsStageWaitRelease )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsStageWaitRelease error" );
        return FALSE;
    }
    m_nMapDataID = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsStageWaitRelease( m_nMapDataID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
unsigned int m_nMapDataID;
SCRIPT_END

SCRIPT_BEGIN( LeaveStage )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 5 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "LeaveStage error" );
        return FALSE;
    }
    m_ustMapDataID = atoi( words->GetWord( 0 ) );
    m_nX           = atoi( words->GetWord( 1 ) );
    m_nY           = atoi( words->GetWord( 2 ) );
    m_bTeamLeave   = atoi( words->GetWord( 3 ) );
    m_ustTime      = atoi( words->GetWord( 4 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->LeaveStage( m_ustMapDataID, m_nX, m_nY, m_bTeamLeave, m_ustTime );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
unsigned short m_ustMapDataID;
int m_nX;
int m_nY;
bool m_bTeamLeave;
unsigned short m_ustTime;
SCRIPT_END

// 幸运15关相关内容
SCRIPT_BEGIN( GetLuckRewardLevel )          // 获得幸运15关的当前第几关
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetLuckReward error" );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->GetLuckRewardLevel();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( EnterLuckReward )         // 进入幸运15关
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "EnterLuckReward error" );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->EnterLuckReward();
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( UpdateLuckReward )                // 更新幸运15关内容
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "UpdateLuckReward error" );
        return FALSE;
    }

    m_nType = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->UpdateLuckReward( m_nType );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nType;
SCRIPT_END

SCRIPT_BEGIN( IsCanLuckReward )                // 是否能摇奖
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanLuckReward error" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsCanLuckReward();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( IsCanNextLuckLevel )                // 是否能摇奖
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanNextLuckLevel error" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsCanNextLuckLevel();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


SCRIPT_BEGIN( IsCanAcceptQuest )                // 是否能摇奖
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanAcceptQuest error" );
        return FALSE;
    }

    m_uchLevel = atoi( words->GetWord( 0 ) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsCanAcceptQuest( m_uchLevel );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
unsigned char m_uchLevel;
SCRIPT_END

SCRIPT_BEGIN( IsCanReceiveReward )                // 能否领奖
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCanReceiveReward error" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->IsCanReceiveReward();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( SetCanLuckReward )                // 设置能玩
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetCanLuckReward error" );
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetCanLuckReward();
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( SetLuckSummonCount )                // 设置幸运15关召唤怪物次数
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetLuckSummonCount error" );
        return FALSE;
    }

    m_ustCount = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetLuckSummonCount( m_ustCount );
    vm->NextIP();
}

SCRIPT_PARAM
unsigned short m_ustCount;
SCRIPT_END

SCRIPT_BEGIN( GetLuckSummonCount )                // 设置幸运15关召唤怪物次数
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetLuckSummonCount error" );
        return FALSE;
    }

    m_ustCount = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->GetLuckSummonCount();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
unsigned short m_ustCount;
SCRIPT_END



SCRIPT_BEGIN( OperateJinDing )                // 操作金锭
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "OperateJinDing error" );
        return FALSE;
    }

    m_bOperate = atoi( words->GetWord( 0 ) );
    m_nValue   = atoi( words->GetWord( 1 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->OperateJinDing( m_bOperate, m_nValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
bool m_bOperate;
int m_nValue;
SCRIPT_END

SCRIPT_BEGIN( OperateJinPiao )                // 操作金票
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "OperateJinPiao error" );
        return FALSE;
    }

    m_bOperate = atoi( words->GetWord( 0 ) );
    const char* szWord = words->GetWord( 1 );
    if( WordParser::IsNumber( szWord ) )
    {
        m_nParam.SetNumber( atoi( szWord ) );
        m_nParam.SetIsKey( false );
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId( szWord );
        if ( nKey == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "OperateJinPiao error" );
            return FALSE;
        }
        m_nParam.SetNumber( nKey );
        m_nParam.SetIsKey( true );
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = 0;
    if ( m_nParam.IsKey() )
    {
        int nKey = m_nParam.GetNumber();
        nValue = GetScriptInterface()->GetVar( nKey );
    }
    else
    { nValue = m_nParam.GetNumber(); }

    if ( nValue <= 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:OperateJinPiao %d %d",m_bOperate, nValue );
        return;
    }

    int nSuccess = GetScriptInterface()->OperateJinPiao( m_bOperate, nValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
bool m_bOperate;
//int m_nValue;
CScriptCmd__SetVar::Param    m_nParam;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( OperateHonour )                // 操作
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "OperateHonour error" );
        return FALSE;
    }

    m_bOperate = atoi( words->GetWord( 0 ) );
    m_nValue   = atoi( words->GetWord( 1 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nSuccess = GetScriptInterface()->OperateHonour( m_bOperate, m_nValue );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nSuccess );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
bool m_bOperate;
int m_nValue;
SCRIPT_END


SCRIPT_BEGIN( ShowTreasureBox ) // 显示宝箱界面
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ShowTreasureBox error" );
        return FALSE;
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ShowTreasureBox();
    vm->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( DrawFromPlatform ) // 领取东西向平台
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DrawFromPlatform error" );
        return FALSE;
    }

    type = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->DrawFromPlatform( type );
    vm->NextIP();
}

SCRIPT_PARAM
uint16 type;
SCRIPT_END

SCRIPT_BEGIN( SetAreaCurrentReputation )  // 设置当前最大声望
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetAreaCurrentReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if (WordParser::IsNumber(szMapId))
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetAreaCurrentReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if (WordParser::IsNumber(szValue))
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetAreaCurrentReputation");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }
    GetScriptInterface()->SetAreaCurrentReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( AddAreaCurrentReputation )  // 
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddAreaCurrentReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if (WordParser::IsNumber(szMapId))
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddAreaCurrentReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if (WordParser::IsNumber(szValue))
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddAreaCurrentReputation");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }
    GetScriptInterface()->AddAreaCurrentReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( SubAreaCurrentReputation )  // 
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubAreaCurrentReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if (WordParser::IsNumber(szMapId))
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubAreaCurrentReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if (WordParser::IsNumber(szValue))
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubAreaCurrentReputation");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->SubAreaCurrentReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( GetAreaCurrentReputation )  //
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetAreaCurrentReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    const char* szMapId = words->GetWord(0);
    if (WordParser::IsNumber(szMapId))
    {
        m_mapId.SetNumber( atoi(szMapId) );
        m_mapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetAreaCurrentReputation");
            return FALSE;
        }
        m_mapId.SetNumber(nKey);
        m_mapId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_mapId.IsKey())
    {
        int nKey = m_mapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_mapId.GetNumber();
    }
    int nValue = GetScriptInterface()->GetAreaCurrentReputation( nMapId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
CScriptCmd__SetVar::Param m_mapId;
SCRIPT_END

SCRIPT_BEGIN( SetAreaMaxReputation )  // 设置区域最大声望
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetAreaMaxReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetAreaMaxReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }
    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
         int nKey = GetScriptVarMgr()->GetVarId(szValue);
         if (nKey == -1)
         {
             LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetAreaMaxReputation");
             return FALSE;
         }
         m_Value.SetNumber(nKey);
         m_Value.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_MapId.GetNumber();
    }
    GetScriptInterface()->SetAreaMaxReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( AddAreaMaxReputation )  // 增加区域最大声望
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddAreaMaxReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddAreaMaxReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }
    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddAreaMaxReputation");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_MapId.GetNumber();
    }
    GetScriptInterface()->AddAreaMaxReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( SubAreaMaxReputation )  // 减少区域最大声望
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubAreaMaxReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szMapId = words->GetWord(0);
    if ( WordParser::IsNumber(szMapId) )
    {
        m_MapId.SetNumber( atoi(szMapId) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubAreaMaxReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }
    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubAreaMaxReputation");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_MapId.GetNumber();
    }
    GetScriptInterface()->SubAreaMaxReputation( nMapId, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
//int m_nValue;
CScriptCmd__SetVar::Param m_MapId;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( GetAreaMaxReputation )  // 获得当前最大声望
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetAreaMaxReputation error" );
        return FALSE;
    }

    //m_nMapID = atoi( words->GetWord( 0 ) );
    const char* szMapid = words->GetWord(0);
    if (WordParser::IsNumber(szMapid))
    {
        m_MapId.SetNumber( atoi(szMapid) );
        m_MapId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapid);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetAreaMaxReputation");
            return FALSE;
        }
        m_MapId.SetNumber(nKey);
        m_MapId.SetIsKey(true);
    }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nMapId = 0;
    if (m_MapId.IsKey())
    {
        int nKey = m_MapId.GetNumber();
        nMapId = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nMapId = m_MapId.GetNumber();
    }

    int nValue = GetScriptInterface()->GetAreaMaxReputation( nMapId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
//int m_nMapID;
CScriptCmd__SetVar::Param m_MapId;
SCRIPT_END

SCRIPT_BEGIN( SetNextStage )  //
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetNextStage error" );
        return FALSE;
    }

    m_nNextStage = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->SetNextStage( m_nNextStage );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int m_nNextStage;
SCRIPT_END


SCRIPT_BEGIN( InitBattle )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 7 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "InitBattle error" );
        return FALSE;
    }

    m_nMapID        = atoi( words->GetWord( 0 ) );
    m_nType         = atoi( words->GetWord( 1 ) );
    m_nLevel        = atoi( words->GetWord( 2 ) );
    m_uchTurns      = atoi( words->GetWord( 3 ) );
    m_nSignTime     = atoi( words->GetWord( 4 ) );
    m_nFightTime    = atoi( words->GetWord( 5 ) );
    m_nMaxUnitCount = atoi( words->GetWord( 6 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->InitBattle( m_nMapID, m_nType, m_nLevel, m_uchTurns, m_nSignTime, m_nFightTime, m_nMaxUnitCount );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int m_nMapID;       // 战场中等待的地图
int m_nLevel;       // 战场的等级
int m_nType;        // 战场类型  1 = 个人 1v1擂台  2 = 队伍  3 = 公会
unsigned char m_uchTurns;     // 战场重复几次
int m_nSignTime;    // 报名持续时间
int m_nFightTime;   // 战斗时间
int m_nMaxUnitCount;// 每次报名允许的最大玩家数
SCRIPT_END

SCRIPT_BEGIN( ShowBattleSignUpDlg )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ShowBattleSignUpDlg" );
        return FALSE;
    }
    m_nType    = atoi( words->GetWord( 0 ) );
    m_strInfo  = words->GetWord( 1 );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->ShowBattleSignUpDlg( m_nType, m_strInfo.c_str() );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

SCRIPT_PARAM
int m_nType;        // 战场类型  1 = 个人 1v1擂台  2 = 队伍  3 = 公会
std::string m_strInfo;   // 显示的内容
SCRIPT_END


SCRIPT_BEGIN( SetChallengeScore )  // 设置当前个人擂台积分
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetChallengeScore error" );
        return FALSE;
    }

    m_nValue = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetChallengeScore( m_nValue, SKW_SET );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nValue;
SCRIPT_END

SCRIPT_BEGIN( AddChallengeScore )       // 增加当前个人擂台积分
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddChallengeScore error" );
        return FALSE;
    }

    m_nValue = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetChallengeScore( m_nValue, SKW_SETADD );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nValue;
SCRIPT_END

SCRIPT_BEGIN( SubChallengeScore )       // 减少当前个人擂台积分
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubChallengeScore error" );
        return FALSE;
    }

    m_nValue = atoi( words->GetWord( 0 ) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetChallengeScore( m_nValue, SKW_SETSUB );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nValue;
SCRIPT_END

SCRIPT_BEGIN( GetChallengeScore )       // 获得当前个人擂台积分
virtual BOOL Create( WordParser* words )
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->GetChallengeScore();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


SCRIPT_BEGIN( checkSecondPassword )       // 打开寄卖界面
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "checkSecondPassword error" );
		return FALSE;
	}
	checktype = atoi( words->GetWord( 0 ) );

	return TRUE;
}
virtual void Execute( CScriptVM* vm )
{
	int nValue = GetScriptInterface()->checkSecondPassword(checktype);
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nValue );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}
SCRIPT_PARAM
int checktype;
SCRIPT_END

SCRIPT_BEGIN( CallMailList )   
virtual BOOL Create( WordParser* words )
{ return TRUE; }

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->CallMailList();
    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END


// 飞行到玩家旁边, 特殊道具使用
SCRIPT_BEGIN( FlyToPlayer )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "FlyToPlayer error" );
        return FALSE;
    }

    m_nType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->FlyToPlayer( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
int m_nType;
SCRIPT_END

SCRIPT_BEGIN( AddTeamBattleIntegral )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddTeamBattleIntegral error" );
        return FALSE;
    }

    m_nIntegral = atoi( words->GetWord( 0 ) );
    return TRUE; 
}
virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddTeamBattleIntegral( m_nIntegral );
    vm->NextIP();
}

SCRIPT_PARAM
int m_nIntegral;
SCRIPT_END

SCRIPT_BEGIN( SetNpcShow )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetNpcShow error" );
        return FALSE;
    }

    ustNpcID = atoi( words->GetWord( 0 ) );
    nSpaceTime = atoi( words->GetWord( 1 ) );
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetNpcShow( ustNpcID, nSpaceTime );
    vm->NextIP();
}

SCRIPT_PARAM
unsigned short ustNpcID;
unsigned int nSpaceTime;
SCRIPT_END

SCRIPT_BEGIN( SetNpcHide )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetNpcHide error" );
        return FALSE;
    }

    ustNpcID   = atoi( words->GetWord( 0 ) );
    nSpaceTime = atoi( words->GetWord( 1 ) );
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetNpcHide( ustNpcID, nSpaceTime );
    vm->NextIP();
}

SCRIPT_PARAM
unsigned short ustNpcID;
unsigned int nSpaceTime;
SCRIPT_END

SCRIPT_BEGIN( AddSkillPoint )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddSkillPoint error" );
        return FALSE;
    }

    //nType   = atoi( words->GetWord( 0 ) );
    //nValue = atoi( words->GetWord( 1 ) );
    const char* szType = words->GetWord(0);
    if (WordParser::IsNumber(szType))
    {
        m_Type.SetNumber( atoi(szType) );
        m_Type.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szType);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddSkillPoint");
            return FALSE;
        }
        m_Type.SetNumber(nKey);
        m_Type.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddSkillPoint");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int nType = 0;
    if ( m_Type.IsKey() )
    {
        int nKey = m_Type.GetNumber();
        nType = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nType = m_Type.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->AddSkillPoint( nType, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
//int nType;
//int nValue;
CScriptCmd__SetVar::Param m_Type;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END


SCRIPT_BEGIN( SubSkillPoint )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubSkillPoint error" );
        return FALSE;
    }

    const char* szType = words->GetWord(0);
    if (WordParser::IsNumber(szType))
    {
        m_Type.SetNumber( atoi(szType) );
        m_Type.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szType);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubSkillPoint");
            return FALSE;
        }
        m_Type.SetNumber(nKey);
        m_Type.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubSkillPoint");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int nType = 0;
    if ( m_Type.IsKey() )
    {
        int nKey = m_Type.GetNumber();
        nType = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nType = m_Type.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->SubSkillPoint( nType, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_Type;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( SetSkillPoint )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetSkillPoint error" );
        return FALSE;
    }

    const char* szType = words->GetWord(0);
    if (WordParser::IsNumber(szType))
    {
        m_Type.SetNumber( atoi(szType) );
        m_Type.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szType);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetSkillPoint");
            return FALSE;
        }
        m_Type.SetNumber(nKey);
        m_Type.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SetSkillPoint");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int nType = 0;
    if ( m_Type.IsKey() )
    {
        int nKey = m_Type.GetNumber();
        nType = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nType = m_Type.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->SetSkillPoint( nType, nValue );
    vm->NextIP();
}

SCRIPT_PARAM
CScriptCmd__SetVar::Param m_Type;
CScriptCmd__SetVar::Param m_Value;
SCRIPT_END

SCRIPT_BEGIN( GetSkillPoint )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetSkillPoint error" );
        return FALSE;
    }

    //nType   = atoi( words->GetWord( 0 ) );
    const char* szType = words->GetWord(0);
    if ( WordParser::IsNumber(szType) )
    {
        m_Type.SetNumber( atoi(szType) );
        m_Type.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szType);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetSkillPoint");
            return FALSE;
        }
        m_Type.SetNumber(nKey);
        m_Type.SetIsKey(true);
    }
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int nType = 0;
    if (m_Type.IsKey())
    {
        int nKey = m_Type.GetNumber();
        nType = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nType = m_Type.GetNumber();
    }
    int result = GetScriptInterface()->GetSkillPoint( nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

SCRIPT_PARAM
//int nType;
//int nValue;
CScriptCmd__SetVar::Param m_Type;
SCRIPT_END

SCRIPT_BEGIN( TriggerAchieveByType )
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TriggerAchieveByType error" );
        return FALSE; 
    }

    nValueType  = atoi( words->GetWord( 0 ) );
    nValue      = atoi( words->GetWord( 1 ) );
    bAddValue   = atoi( words->GetWord( 2 ) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->TriggerAchieveByType( nValueType, nValue, bAddValue );

    vm->NextIP();
}

SCRIPT_PARAM
int     nValueType;
int     nValue;
bool    bAddValue;
SCRIPT_END

SCRIPT_BEGIN( TriggerAchieveByID )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TriggerAchieveByID error" );
        return FALSE;
    }

    nId   = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->TriggerAchieveByID( nId );

    vm->NextIP();
}

SCRIPT_PARAM
int nId;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// 触发死亡成就
SCRIPT_BEGIN( TriggerDeathAchieveByType )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TriggerDeathAchieveByType error" );
        return FALSE; 
    }

    nValueType  = atoi( words->GetWord( 0 ) );
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->TriggerDeathAchieveByType( nValueType );

    vm->NextIP();
}

SCRIPT_PARAM
int     nValueType;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
SCRIPT_BEGIN( OnNpcShip )   
virtual BOOL Create( WordParser* words )
{ 
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "TriggerAchieveByID error" );
        return FALSE;
    }
    
    return TRUE; 
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->OnNpcShip();

    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber(retNum);
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }

    vm->NextIP();
}

SCRIPT_PARAM
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
// AddPlayerVar nVarID Value 添加玩家变量
SCRIPT_BEGIN( AddPlayerVar )
virtual BOOL Create( WordParser* words )
{
    if ( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddPlayerVar error" );
        return FALSE;
    }
    const char* szVarId = words->GetWord(0);
    if ( WordParser::IsNumber(szVarId) )
    {
        m_VarId.SetNumber( atoi(szVarId) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVarId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddPlayerVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddPlayerVar");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nValue = m_Value.GetNumber();
    }

    CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber( nValue );
    GetScriptInterface()->SetTeamVar( nVarId, SKW_SETADD, m_params, 1 );
    vm->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param m_VarId;  // 玩家的计数变量名
CScriptCmd__SetVar::Param m_Value;  // 计数变量的值
SCRIPT_END
//////////////////////////////////////////////////////////////////////////
// SetPlayerVar nVarID Value 设置玩家计数变量
SCRIPT_BEGIN( SetPlayerVar )
virtual BOOL Create( WordParser* words )
{
    if ( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetPlayerVar error");
        return FALSE;
    }

    const char* szVarId = words->GetWord(0);
    if ( WordParser::IsNumber(szVarId) )
    {
        m_VarId.SetNumber( atoi(szVarId) );
        m_VarId.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVarId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddPlayerVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }

    const char* szValue = words->GetWord(1);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddPlayerVar");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nVarId = 0;
    if (m_VarId.IsKey())
    {
        int nKey = m_VarId.GetNumber();
        nVarId = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nVarId = m_VarId.GetNumber();
    }
    int nValue = 0;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        nValue = m_Value.GetNumber();
    }

    CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber(nValue);
    GetScriptInterface()->SetVar( nVarId, SKW_SET, m_params, 1 );
    vm->NextIP();
}
SCRIPT_PARAM
CScriptCmd__SetVar::Param m_VarId;  // 玩家的计数变量名
CScriptCmd__SetVar::Param m_Value;  // 计数变量的值
SCRIPT_END

//SCRIPT_BEGIN( GetNpcId )
//virtual BOOL Create( WordParser* words )
//{
//    if ( words->GetWordCount() != 0 )
//    {
//        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetNpcID params number != 0");
//        return FALSE;
//    }
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* vm )
//{
//    int retNum =  GetScriptInterface()->GetNpcId();
//    if ( m_nReturnKey != -1 )
//    {
//        CScriptCmd__SetVar::Param    m_params[1];
//        m_params[0].SetNumber( retNum );
//        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
//    }
//    vm->NextIP();
//}
//SCRIPT_PARAM
//SCRIPT_END
//
//SCRIPT_BEGIN( GetMonsterId )
//virtual BOOL Create( WordParser* words )
//{
//    if (words->GetWordCount() != 0)
//    {
//        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetMonsterId params number != 0");
//        return FALSE;
//    }
//    return TRUE;
//}
//
//virtual void Execute( CScriptVM* vm )
//{
//    int retNum = GetScriptInterface()->GetMonsterId();
//    if ( m_nReturnKey != -1 )
//    {
//        CScriptCmd__SetVar::Param m_params[1];
//        m_params[0].SetNumber(retNum);
//        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
//    }
//    vm->NextIP();
//}
//SCRIPT_PARAM
//SCRIPT_END
SCRIPT_BEGIN( GetTargetId )
virtual BOOL Create( WordParser* words )
{
    if (words->GetWordCount() != 0)
    {
        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:GetTargetId params number != 0");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int retNum = GetScriptInterface()->GetTargetId();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber(retNum);
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// PlayMovie MovieId PlayTime StatusId StatusLevel
SCRIPT_BEGIN( PlayMovie )
virtual BOOL Create( WordParser* words)
{
    if ( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:PlayMovie params is not 2");
        return FALSE;
    }

    nMovieId     = atoi( words->GetWord(0) );
    dwPlayTime   = atoi( words->GetWord(1) );

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->PlayMovie( nMovieId, dwPlayTime );
    vm->NextIP();
}
SCRIPT_PARAM
unsigned int nMovieId;    // 影片ID
DWORD dwPlayTime;         // 影片播放时间
SCRIPT_END

SCRIPT_BEGIN( GetMonsterTypeStatus )
virtual BOOL Create( WordParser* words)
{
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->GetMonsterTypeStatus();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( ChangeMonsterTypeStatus )
virtual BOOL Create( WordParser* words)
{
    m_nStatus = 0;
    if ( words->GetWordCount() == 1 )
    { m_nStatus = atoi( words->GetWord( 0 ) ); }

    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangeMonsterTypeStatus( m_nStatus );
    vm->NextIP();
}
SCRIPT_PARAM
int m_nStatus;
SCRIPT_END

SCRIPT_BEGIN( StartEventByID )
virtual BOOL Create( WordParser* words )
{
    m_nEventID = 0;
    m_bBroadcast = false;
    if ( words->GetWordCount() == 2 )
    { 
        m_nEventID = atoi( words->GetWord( 0 ) ); 
        m_bBroadcast = atoi( words->GetWord( 1 ) );
    }
    return TRUE;
}
virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->StartEventByID( m_nEventID, m_bBroadcast );
    vm->NextIP();
}
SCRIPT_PARAM
uint16 m_nEventID;
bool m_bBroadcast;
SCRIPT_END

//////////////////////////////////////////////////////////////////////////
// DBGPrint
SCRIPT_BEGIN( DBGPrint )
virtual BOOL Create( WordParser* words )
{
    if( words->GetWordCount() < 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:DBGPrint" );
        return FALSE;
    }
    
    m_strParam = words->GetWord(0);
    
    for ( int n = 1; n<words->GetWordCount(); n++ )
    {
        const char* sz = words->GetWord(n);
        int nVar = GetScriptVarMgr()->GetVarId( sz );
        if ( nVar == -1 )
        {
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DBGPrint create error");
            return FALSE;
        }
        m_vtKey.push_back( nVar );
    }

    int nCount = 0;
    for ( int n=0; n<m_strParam.size()-1; n++ )
    {
        if ( m_strParam[n] == '%' )
        {
            if ( m_strParam[n+1] == 's' )
            {
                nCount++;
            }
            else
            {
                LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DBGPrint create error");
                return FALSE;
            }
        }
    }
    if ( nCount != m_vtKey.size() )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DBGPrint create error");
        return FALSE;
    }
    return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
    std::vector<std::string> vtVar;
    for ( unsigned int n=0; n<m_vtKey.size(); n++ )
    {
        const char *sz = GetScriptInterface()->GetStringFormVar( m_vtKey[n] );
        vtVar.push_back( sz );
    }
    char szText[512] = {0};
    ScriptSprintf( szText, sizeof( szText ) - 1, m_strParam.c_str(), vtVar );
    GetScriptInterface()->DBGPrint( szText );
    vm->NextIP();
}

SCRIPT_PARAM
std::string m_strParam;
std::vector<int> m_vtKey;
SCRIPT_END


SCRIPT_BEGIN( GetTPHJRank )
virtual BOOL Create( WordParser* words)
{
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	int nResult = GetScriptInterface()->GetTPHJRank();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nResult );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( SetTPHJRank )
virtual BOOL Create( WordParser* words )
{

    if ( words->GetWordCount() != 1 && words->GetWordCount() != 2)
    {
        GetScriptInterface()->Printf("error:SetTPHJRank");
        return FALSE;
    }
/////////////////////////////////////////////////////////////////////////////
	const char* szVarId = words->GetWord(0);
	if ( WordParser::IsNumber(szVarId) )
	{
		nVarId = atoi(szVarId);
	}
	else
	{
		int nKey = GetScriptVarMgr()->GetVarId(szVarId);
		if (nKey == -1)
		{
			LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetTPHJRank");
			return FALSE;
		}
		nVarId = nKey;
	}

	const char* szOperId = words->GetWord(1);
	if ( WordParser::IsNumber(szOperId) )
	{
		nOper = atoi(szOperId);
	}
	else
	{
		int nOperKey = GetScriptVarMgr()->GetVarId(szOperId);
		if (nOperKey == -1)
		{
			LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetTPHJRank");
			return FALSE;
		}
		nOper = nOperKey;
	}
	if (nOper < EOT_Add || nOper > EOT_Set)
	{
		LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetTPHJRank");
		return FALSE;
	}
	return true;

}

virtual void Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetTPHJRank( nVarId, nOper);
    vm->NextIP();
}

SCRIPT_PARAM

int nVarId;
int nOper;
SCRIPT_END

SCRIPT_BEGIN (SetPetUnactive)
virtual BOOL Create( WordParser* words )
{
	return true;
}

virtual void Execute( CScriptVM* vm )
{
	GetScriptInterface()->SetPetUnactive();
	vm->NextIP();
}

SCRIPT_END

//角色播放动作
SCRIPT_BEGIN( PlayAnim )
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() < 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:PlayAnim" );
		return FALSE;
	}

	m_strAnim = words->GetWord(0);
	m_nTimes = atoi(words->GetWord(1));
	m_strEndName = words->GetWord(2);
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	GetScriptInterface()->PlayAnim(m_strAnim.c_str(),m_nTimes,m_strEndName.c_str());
	vm->NextIP();
}

SCRIPT_PARAM
std::string m_strAnim;
int            m_nTimes;
std::string    m_strEndName;
SCRIPT_END

//请求平台的活动奖励
SCRIPT_BEGIN( AskPlatformAvtivity )
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() < 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AskPlatformAvtivity" );
		return FALSE;
	}
	_type = atoi(words->GetWord(0));	
	return TRUE;
}
virtual void Execute( CScriptVM* vm )
{
	GetScriptInterface()->AskPlatformActivity(_type);
	vm->NextIP();
}

SCRIPT_PARAM
int            _type;
SCRIPT_END


SCRIPT_BEGIN( IsOnBiaoche )
virtual BOOL Create( WordParser* words)
{
	return TRUE;
}

virtual void Execute( CScriptVM* vm )
{
	int nResult = GetScriptInterface()->IsOnBiaoChe();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nResult );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}
SCRIPT_PARAM
SCRIPT_END

SCRIPT_BEGIN( ClearStatusById )
virtual BOOL Create( WordParser* words )
{
	if( words->GetWordCount() < 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ClearStatusById" );
		return FALSE;
	}
	m_statusid = atoi(words->GetWord(0));	
	return TRUE;
}
virtual void Execute( CScriptVM* vm )
{
	GetScriptInterface()->ClearStatusByid(m_statusid);
	vm->NextIP();
}

SCRIPT_PARAM
int m_statusid;
SCRIPT_END


BOOL CScriptCmd_ChangeTimeHandleStates::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ChangeTimeHandleStates" );
        return FALSE;
    }
	Index = static_cast<unsigned int>(_atoi64(words->GetWord( 0 )));
	StatesValue = atoi(words->GetWord(1));
    return TRUE;
}

void CScriptCmd_ChangeTimeHandleStates::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangeTimeHandleStates( Index,StatesValue );
    vm->NextIP( );
}

BOOL CScriptCmd_ResetTimeHandleStates::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ResetTimeHandleStates" );
        return FALSE;
    }
	Index = static_cast<unsigned int>(_atoi64(words->GetWord( 0 )));
    return TRUE;
}

void CScriptCmd_ResetTimeHandleStates::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ResetTimeHandleStates(Index);
    vm->NextIP( );
}

BOOL CScriptCmd_ClearTimeHandle::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ClearTimeHandle" );
        return FALSE;
    }
	Index = static_cast<unsigned int>(_atoi64(words->GetWord( 0 )));
    return TRUE;
}
void CScriptCmd_ClearTimeHandle::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ClearTimeHandle(Index);
    vm->NextIP( );
}

BOOL CScriptCmd_SetWorldBattleCountry::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetWorldBattleCountry" );
        return FALSE;
    }
	CountryID = atoi(words->GetWord( 0 ));
    return TRUE;
}
void CScriptCmd_SetWorldBattleCountry::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetWorldBattleCountry(CountryID);
    vm->NextIP( );
}

BOOL CScriptCmd_AddEquipRandAttrItem::Create( WordParser* words )
{
	if( words->GetWordCount() != 9 && words->GetWordCount() != 11 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddEquipRandAttrItem" );
		return FALSE;
	}

	if ( words->GetWordCount() == 9 )
	{
		ustItemid = atoi(words->GetWord(0));
		bIsBound = atoi(words->GetWord(1));
		nRandId1 = atoi(words->GetWord(2));
		nRandId2 = atoi(words->GetWord(3));
		nRandId3 = atoi(words->GetWord(4));
		nRandId4 = atoi(words->GetWord(5));
		nRandId5 = atoi(words->GetWord(6));
		nRandId6 = atoi(words->GetWord(7));
		nRandId7 = atoi(words->GetWord(8));
		nSysType = 0;
		nTypeID = -1;

		return TRUE;
	}
	
	if ( words->GetWordCount() == 11 )
	{
		ustItemid = atoi(words->GetWord(0));
		bIsBound = atoi(words->GetWord(1));
		nRandId1 = atoi(words->GetWord(2));
		nRandId2 = atoi(words->GetWord(3));
		nRandId3 = atoi(words->GetWord(4));
		nRandId4 = atoi(words->GetWord(5));
		nRandId5 = atoi(words->GetWord(6));
		nRandId6 = atoi(words->GetWord(7));
		nRandId7 = atoi(words->GetWord(8));
		nSysType = atoi(words->GetWord(9));
		nTypeID = atoi(words->GetWord(10));

		return TRUE;
	}

	return TRUE;
}

void CScriptCmd_AddEquipRandAttrItem::Execute( CScriptVM* vm )
{
	GetScriptInterface()->AddEquipRandAttrItem(ustItemid, bIsBound, nRandId1, nRandId2, nRandId3, nRandId4, nRandId5, nRandId6, nRandId7, nSysType, nTypeID);
	vm->NextIP( );
}
BOOL CScriptCmd_ChangeGamePlayerDuration::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ChangeGamePlayerDuration" );
        return FALSE;
    }
	Count = atoi(words->GetWord( 0 ));
    return TRUE;
}
void CScriptCmd_ChangeGamePlayerDuration::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangeGamePlayerDuration(Count);
    vm->NextIP( );
}

BOOL CScriptCmd_ChangePetMode::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ChangePetMode" );
        return FALSE;
    }
	ModeID = atoi(words->GetWord( 0 ));
	Sec = atoi(words->GetWord( 1 ));
    return TRUE;
}
void CScriptCmd_ChangePetMode::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangePetMode(ModeID,Sec);
    vm->NextIP( );
}

BOOL CScriptCmd_UseItem::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:UseItem" );
		return FALSE;
	}

	ustItemid = atoi(words->GetWord(0));

	return TRUE;
}

void CScriptCmd_UseItem::Execute( CScriptVM* vm )
{
	GetScriptInterface()->UseItem( ustItemid );
	vm->NextIP( );
}

BOOL CScriptCmd_GetPlayerStates::Create( WordParser* words )
{
	if( words->GetWordCount() != 0 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetPlayerStates" );
		return FALSE;
	}
	return TRUE;
}
void CScriptCmd_GetPlayerStates::Execute( CScriptVM* vm )
{
	//获取玩家当前的状态
	unsigned short states = GetScriptInterface()->GetPlayerStates();
	if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( states );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
	vm->NextIP( );
}

BOOL CScriptCmd_AddCard::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddCard" );
		return FALSE;
	}

	stCardID = atoi(words->GetWord(0));
	stLevel = atoi(words->GetWord(1));

	return TRUE;
}

void CScriptCmd_AddCard::Execute( CScriptVM* vm )
{
	GetScriptInterface()->AddCard( stCardID, stLevel );
	vm->NextIP( );
}

BOOL CScriptCmd_GetGamePlayerDuration::Create( WordParser* words )
{
    return TRUE;
}
void CScriptCmd_GetGamePlayerDuration::Execute( CScriptVM* vm )
{
	int num =GetScriptInterface()->GetGamePlayerDuration();
	CScriptCmd__SetVar::Param m_params[1];
    m_params[0].SetNumber( num );
    GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    vm->NextIP();
}

BOOL CScriptCmd_TriggerSevenDays::Create( WordParser* words )
{
	if( words->GetWordCount() != 0 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:TriggerSevenDays" );
		return FALSE;
	}
	return TRUE;
}

void CScriptCmd_TriggerSevenDays::Execute( CScriptVM* vm )
{
	GetScriptInterface()->TriggerSevenDays();
	vm->NextIP( );
}

BOOL CScriptCmd_AddFriendPoint::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddFriendPoint" );
		return FALSE;
	}

	distance = atoi(words->GetWord(0));
   FriendlyPoint = atoi(words->GetWord(1));

	return TRUE;
}

void CScriptCmd_AddFriendPoint::Execute( CScriptVM* vm )
{
	//执行游戏中的操作，返回错误信息 并设置给脚本调用 脚本根据错误信息 打印不同的提示
	int num = GetScriptInterface()->AddFriendPoint(distance,FriendlyPoint);
	CScriptCmd__SetVar::Param m_params[1];
	m_params[0].SetNumber( num );
	GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	vm->NextIP();
}


BOOL CScriptCmd_IsInFight::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsInFight::Execute( CScriptVM* vm )
{
	int states = GetScriptInterface()->IsInFight();
	if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( states );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
	vm->NextIP( );
}

BOOL CScriptCmd_IsMountFull::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsMountFull::Execute( CScriptVM* vm )
{
	int states = GetScriptInterface()->IsMountFull();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( states );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}


BOOL CScriptCmd_SetScriptStates::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetScriptStates" );
		return FALSE;
	}

	States = (unsigned short)atoi(words->GetWord(0));
	return TRUE;
}

void CScriptCmd_SetScriptStates::Execute( CScriptVM* vm )
{
	GetScriptInterface()->SetScriptStates(States);
	vm->NextIP( );
}



BOOL CScriptCmd_CanFlyToCouple::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_CanFlyToCouple::Execute( CScriptVM* vm )
{
	//判断自己和 目标的地图类型是否可以飞过去 副本 战场不可以 只可以飞普通地图
	bool IsCan = GetScriptInterface()->CanFlyToCouple();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( IsCan );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}


BOOL CScriptCmd_DropQuestEntrust::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_DropQuestEntrust::Execute( CScriptVM* vm )
{
	GetScriptInterface()->DropQuestEntrust();
	vm->NextIP( );
}

BOOL CScriptCmd_DoneQuestEntrust::Create( WordParser* words )
{
	return TRUE;
}
void CScriptCmd_DoneQuestEntrust::Execute( CScriptVM* vm )
{
	GetScriptInterface()->DoneQuestEntrust();
	vm->NextIP( );
}

BOOL CScriptCmd_GetTodayHuntingCount::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_GetTodayHuntingCount::Execute( CScriptVM* vm )
{
	int states = GetScriptInterface()->GetTodayHuntingCount();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( states );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}

BOOL CScriptCmd_OperateHuntingCount::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:OperateHuntingCount" );
		return FALSE;
	}

	nType = atoi(words->GetWord(0));
	nValue = atoi(words->GetWord(1));

	return TRUE;
}

void CScriptCmd_OperateHuntingCount::Execute( CScriptVM* vm )
{
	GetScriptInterface()->OperateHuntingCount( nType, nValue );
	vm->NextIP( );
}

BOOL CScriptCmd_DoneHuntingQuest::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:DoneHuntingQuest" );
		return FALSE;
	}

	nId = atoi(words->GetWord(0));

	return TRUE;
}

void CScriptCmd_DoneHuntingQuest::Execute( CScriptVM* vm )
{
	GetScriptInterface()->DoneHuntingQuest( nId );
	vm->NextIP( );
}


BOOL CScriptCmd_CanelQuestEntrust::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:CanelQuestEntrust" );
		return FALSE;
	}

	QuestID = atoi(words->GetWord(0));
	
	return TRUE;
}

void CScriptCmd_CanelQuestEntrust::Execute( CScriptVM* vm )
{
	GetScriptInterface()->CanelQuestEntrust(QuestID);
	vm->NextIP( );
}


BOOL CScriptCmd_FlytoPosition::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:FlytoPosition" );
		return FALSE;
	}
	Type = atoi(words->GetWord(0));
	return TRUE;
}

void CScriptCmd_FlytoPosition::Execute( CScriptVM* vm )
{
	int Result = GetScriptInterface()->FlytoPosition(Type);
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( Result );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}


BOOL CScriptCmd_AddHonourByTeam::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddHonourByTeam" );
		return FALSE;
	}
	Num = atoi(words->GetWord(0));
	return TRUE;
}

void CScriptCmd_AddHonourByTeam::Execute( CScriptVM* vm )
{
	GetScriptInterface()->AddHonourByTeam(Num);
	vm->NextIP( );
}


BOOL CScriptCmd_GetStrongCountry::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_GetStrongCountry::Execute( CScriptVM* vm )
{
	int Result = GetScriptInterface()->GetStrongCountry();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( Result );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}


BOOL CScriptCmd_GetWeakCountry::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_GetWeakCountry::Execute( CScriptVM* vm )
{
	int Result = GetScriptInterface()->GetWeakCountry();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( Result );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}

BOOL CScriptCmd_ChangePlayerPoint::Create( WordParser* words )
{
	if( words->GetWordCount() != 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:ChangePlayerPoint" );
		return FALSE;
	}
	Op = atoi(words->GetWord(0));
	Value = atoi(words->GetWord(1));
	States = atoi(words->GetWord(2));
	return TRUE;
}

void CScriptCmd_ChangePlayerPoint::Execute( CScriptVM* vm )
{
	GetScriptInterface()->ChangePlayerPoint(Op,Value,States);
	vm->NextIP( );
}


BOOL CScriptCmd_SetMonsterArray::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:SetMonsterArray" );
		return FALSE;
	}
	Index = atoi(words->GetWord(0));
	Value = atoi(words->GetWord(1));
	return TRUE;
}

void CScriptCmd_SetMonsterArray::Execute( CScriptVM* vm )
{
	GetScriptInterface()->SetMonsterArray(Index,Value);
	vm->NextIP( );
}


BOOL CScriptCmd_GetMonsterArray::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GetMonsterArray" );
		return FALSE;
	}
	Index = atoi(words->GetWord(0));
	return TRUE;
}

void CScriptCmd_GetMonsterArray::Execute( CScriptVM* vm )
{
	int Result = GetScriptInterface()->GetMonsterArray(Index);
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( Result );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP( );
}
