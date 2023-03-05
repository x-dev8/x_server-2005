#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( EnterGameGuildGeneralBattle, CScriptCmd_EnterGameGuildGeneralBattle );
SCRIPT_DECLARE( IsInGameGuildGeneralBattle, CScriptCmd_IsInGameGuildGeneralBattle );
SCRIPT_DECLARE( GetPlayerGameGuildGeneralBattleFigh, CScriptCmd_GetPlayerGameGuildGeneralBattleFigh );
SCRIPT_DECLARE( GetGameGuildGeneralBattleStates, CScriptCmd_GetGameGuildGeneralBattleStates );
SCRIPT_DECLARE( GetGameGuildGeneralBattleSource, CScriptCmd_GetGameGuildGeneralBattleSource );
SCRIPT_DECLARE( ChangeGameGuildGeneralBattleSource, CScriptCmd_ChangeGameGuildGeneralBattleSource );
SCRIPT_DECLARE( CreateGameGuildGeneralBattleMonster1, CScriptCmd_CreateGameGuildGeneralBattleMonsterByPlayer );
SCRIPT_DECLARE( CreateGameGuildGeneralBattleMonster2, CScriptCmd_CreateGameGuildGeneralBattleMonsterBySetting );

BOOL CScriptCmd_EnterGameGuildGeneralBattle::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_EnterGameGuildGeneralBattle::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->EnterGameGuildGeneralBattle();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}



BOOL CScriptCmd_IsInGameGuildGeneralBattle::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_IsInGameGuildGeneralBattle::Execute( CScriptVM* vm )
{
	int nId = GetScriptInterface()->IsInGameGuildGeneralBattle()?1:0;
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetPlayerGameGuildGeneralBattleFigh::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetPlayerGameGuildGeneralBattleFigh::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetPlayerGameGuildGeneralBattleFigh();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetGameGuildGeneralBattleStates::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGameGuildGeneralBattleStates::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetGameGuildGeneralBattleStates();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetGameGuildGeneralBattleSource::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:GetGameGuildGeneralBattleSource" );
        return FALSE;
    }
    Fight = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_GetGameGuildGeneralBattleSource::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetGameGuildGeneralBattleSource(Fight);
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_ChangeGameGuildGeneralBattleSource::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:ChangeGameGuildGeneralBattleSource" );
        return FALSE;
    }
    Fight = atoi( words->GetWord(0) );
	Value = atoi( words->GetWord(1) );
    return TRUE;
}

void CScriptCmd_ChangeGameGuildGeneralBattleSource::Execute( CScriptVM* vm )
{
    GetScriptInterface()->ChangeGameGuildGeneralBattleSource(Fight,Value);
    vm->NextIP();
}

BOOL CScriptCmd_CreateGameGuildGeneralBattleMonsterByPlayer::Create( WordParser* words )
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

void CScriptCmd_CreateGameGuildGeneralBattleMonsterByPlayer::Execute( CScriptVM* vm )
{
    GetScriptInterface()->CreateGameGuildGeneralBattleMonster( m_nMonsterID, m_nCount, m_fRadius, m_fBodySize, m_nRouteID );
    vm->NextIP();
}

BOOL CScriptCmd_CreateGameGuildGeneralBattleMonsterBySetting::Create( WordParser* words )
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

void CScriptCmd_CreateGameGuildGeneralBattleMonsterBySetting::Execute( CScriptVM* vm )
{
    GetScriptInterface()->CreateGameGuildGeneralBattleMonster( m_nMonsterID, m_nCount, m_nMapID, m_fPosX, m_fPosY, m_nFightCamp, m_fRadius, m_fBodySize, m_nRouteID );
    vm->NextIP();
}