#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( GetBattleCamp, CScriptCmd_GetBattleCamp );
SCRIPT_DECLARE( GetCampBattleStatus, CScriptCmd_GetCampBattleStatus );
SCRIPT_DECLARE( ShowCampBattleSignUp, CScriptCmd_ShowCampBattleSignUp );
SCRIPT_DECLARE( SignUpCampBattle, CScriptCmd_SignUpCampBattle );
SCRIPT_DECLARE( ShowCampBattleEnter, CScriptCmd_ShowCampBattleEnter );
SCRIPT_DECLARE( EnterCampBattle, CScriptCmd_EnterCampBattle );
SCRIPT_DECLARE( KillCampBattleMonster, CScriptCmd_KillCampBattleMonster );
SCRIPT_DECLARE( CreateCampMonster1, CScriptCmd_CreateCampMonsterByPlayer );
SCRIPT_DECLARE( CreateCampMonster2, CScriptCmd_CreateCampMonsterBySetting );
SCRIPT_DECLARE( QueryCampBattleSignUp, CScriptCmd_QueryCampBattleSignUp );
SCRIPT_DECLARE( ChangeCampBattleScore, CScriptCmd_ChangeCampBattleScore );
SCRIPT_DECLARE( GetCampBattleFight, CScriptCmd_GetCampBattleFight);

/////////////////////////////////////////////////////////////////

BOOL CScriptCmd_GetBattleCamp::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetBattleCamp::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetBattleCamp();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetCampBattleStatus::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:GetCampBattleStatus" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
	m_nCountryid = atoi( words->GetWord(1) );
    return TRUE;
}

void CScriptCmd_GetCampBattleStatus::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetCampBattleStatus( m_nType ,m_nCountryid);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_ShowCampBattleSignUp::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:ShowCampBattleSignUp" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_ShowCampBattleSignUp::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->ShowCampBattleSignUp( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_SignUpCampBattle::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:SignUpCampBattle" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_SignUpCampBattle::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->SignUpCampBattle( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_ShowCampBattleEnter::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:ShowCampBattleEnter" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_ShowCampBattleEnter::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->ShowCampBattleEnter( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_EnterCampBattle::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:EnterCampBattle" );
        return FALSE;
    }
    m_nType = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_EnterCampBattle::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->EnterCampBattle( m_nType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_KillCampBattleMonster::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:KillCampBattleMonster" );
        return FALSE;
    }
    m_nMonsterID = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_KillCampBattleMonster::Execute( CScriptVM* vm )
{
    GetScriptInterface()->KillCampBattleMonster( m_nMonsterID );
    vm->NextIP();
}

BOOL CScriptCmd_CreateCampMonsterByPlayer::Create( WordParser* words )
{
    if( words->GetWordCount() != 5 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:CreateCampMonster1" );
        return FALSE;
    }
    m_nMonsterID = atoi( words->GetWord( 0 ) );
    m_nCount     = atoi( words->GetWord( 1 ) );
    m_fRadius    = atof( words->GetWord( 2 ) );
    m_fBodySize  = atof( words->GetWord( 3 ) );
    m_nRouteID   = atoi( words->GetWord( 4 ) );
    return TRUE;
}

void CScriptCmd_CreateCampMonsterByPlayer::Execute( CScriptVM* vm )
{
    GetScriptInterface()->CreateCampMonster( m_nMonsterID, m_nCount, m_fRadius, m_fBodySize, m_nRouteID );
    vm->NextIP();
}

BOOL CScriptCmd_CreateCampMonsterBySetting::Create( WordParser* words )
{
    if( words->GetWordCount() != 9 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:CreateCampMonster2" );
        return FALSE;
    }
    m_nMonsterID = atoi( words->GetWord( 0 ) );
    m_nCount     = atoi( words->GetWord( 1 ) );
    m_nMapID     = atoi( words->GetWord( 2 ) );
    m_fPosX      = atof( words->GetWord( 3 ) );
    m_fPosY      = atof( words->GetWord( 4 ) );
    m_nFightCamp = atoi( words->GetWord( 5 ) );
    m_fRadius    = atof( words->GetWord( 6 ) );
    m_fBodySize  = atof( words->GetWord( 7 ) );
    m_nRouteID   = atoi( words->GetWord( 8 ) );
    return TRUE;
}

void CScriptCmd_CreateCampMonsterBySetting::Execute( CScriptVM* vm )
{
    GetScriptInterface()->CreateCampMonster( m_nMonsterID, m_nCount, m_nMapID, m_fPosX, m_fPosY, m_nFightCamp, m_fRadius, m_fBodySize, m_nRouteID );
    vm->NextIP();
}

BOOL CScriptCmd_QueryCampBattleSignUp::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "QueryCampBattleSignUp error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_QueryCampBattleSignUp::Execute( CScriptVM* vm )
{
    GetScriptInterface()->QueryCampBattleSignUp( uchType );
    vm->NextIP();
}


BOOL CScriptCmd_ChangeCampBattleScore::Create( WordParser* words )
{
    if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:ChangeCampBattleScore" );
        return FALSE;
    }
    IsRadOrBlue = atoi( words->GetWord(0) );
	ChangeType = atoi( words->GetWord(1) );
	Value = atoi( words->GetWord(2) );
    return TRUE;
}

void CScriptCmd_ChangeCampBattleScore::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangeCampBattleScore( IsRadOrBlue ,ChangeType,Value);
    vm->NextIP();
}

BOOL CScriptCmd_GetCampBattleFight::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetCampBattleFight::Execute( CScriptVM* vm )
{
	int nId = GetScriptInterface()->GetCampBattleFight();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}
