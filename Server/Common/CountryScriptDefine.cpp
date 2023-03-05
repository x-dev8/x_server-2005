#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"

extern IScriptInterface* GetScriptInterface();


SCRIPT_DECLARE( IsHaveCountryMaster, CScriptCmd_IsHaveCountryMaster );
SCRIPT_DECLARE( ReceiveCountryMount, CScriptCmd_ReceiveCountryMount );
SCRIPT_DECLARE( CountryConenve, CScriptCmd_CountryConenve );
SCRIPT_DECLARE( IsCountryMaster, CScriptCmd_IsCountryMaster );
SCRIPT_DECLARE( IsCountryQueen, CScriptCmd_IsCountryQueen );
SCRIPT_DECLARE( AddCountryResource, CScriptCmd_AddCountryResource );
SCRIPT_DECLARE( SubCountryResource, CScriptCmd_SubCountryResource );
SCRIPT_DECLARE( GetCountryID, CScriptCmd_GetCountryID );
SCRIPT_DECLARE( IsCountryQuestOpen, CScriptCmd_IsCountryQuestOpen );
SCRIPT_DECLARE( GetCountryScore, CScriptCmd_GetCountryScore );
SCRIPT_DECLARE( AddCountryScore, CScriptCmd_AddCountryScore );
SCRIPT_DECLARE( SubCountryScore, CScriptCmd_SubCountryScore );
SCRIPT_DECLARE( SetCountryScore, CScriptCmd_SetCountryScore );
SCRIPT_DECLARE( IsCountryGuild, CScriptCmd_IsCountryGuild );
SCRIPT_DECLARE( GetCountryOfficial, CScriptCmd_GetCountryOfficial );
SCRIPT_DECLARE( GetWarSortIndex, CScriptCmd_GetWarSortIndex );
SCRIPT_DECLARE( IsInCountryWarFight, CScriptCmd_IsInCountryWarFight );
SCRIPT_DECLARE(	SetCountryKing , CScriptCmd_SetCountryKing);
SCRIPT_DECLARE(	SetCountryTribute , CScriptCmd_SetCountryTribute);
SCRIPT_DECLARE( GetCountryTribute, CScriptCmd_GetCountryTribute );
SCRIPT_DECLARE( AddCountryTribute, CScriptCmd_AddCountryTribute );
SCRIPT_DECLARE( SubCountryTribute, CScriptCmd_SubCountryTribute );
SCRIPT_DECLARE( IsPlayerKing, CScriptCmd_IsPlayerKing  );
SCRIPT_DECLARE( AddCountryInfo, CScriptCmd_AddCountryInfo  );


BOOL CScriptCmd_IsHaveCountryMaster::Create( WordParser* words )
{ 
    int nWordCount = words->GetWordCount();
    if( nWordCount < 1 || nWordCount > 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsHaveCountryMaster error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    uchCountry = 0;
    if ( nWordCount == 2 )
    {
        uchCountry = atoi( words->GetWord( 1 ) );
    }
    return TRUE; 
}

void CScriptCmd_IsHaveCountryMaster::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsHaveCountryMaster( uchType, uchCountry );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_ReceiveCountryMount::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ReceiveCountryMount error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_ReceiveCountryMount::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->ReceiveCountryMount( uchType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_CountryConenve::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_CountryConenve::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->CountryConenve();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsCountryMaster::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCountryMaster error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_IsCountryMaster::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsCountryMaster( uchType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsCountryGuild::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "IsCountryGuild error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_IsCountryGuild::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsCountryGuild( uchType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}



BOOL CScriptCmd_IsCountryQueen::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_IsCountryQueen::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsCountryQueen();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddCountryResource::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddCountryResource error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    nValue  = atoi( words->GetWord( 1 ) );
    return TRUE; 
}

void CScriptCmd_AddCountryResource::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddCountryResource( uchType, nValue );
    vm->NextIP();
}


BOOL CScriptCmd_SubCountryResource::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubCountryResource error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    nValue  = atoi( words->GetWord( 1 ) );
    return TRUE; 
}

void CScriptCmd_SubCountryResource::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SubCountryResource( uchType, nValue );
    vm->NextIP();
}

BOOL CScriptCmd_GetCountryID::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetCountryID::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->GetCountryID();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsCountryQuestOpen::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubCountryResource error" );
        return FALSE;
    }

    uchType = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_IsCountryQuestOpen::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsCountryQuestOpen( uchType );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_GetCountryScore::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetCountryScore::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->GetCountryScore();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddCountryScore::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddCountryScore error" );
        return FALSE;
    }

    nValue = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_AddCountryScore::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddCountryScore( nValue );
    vm->NextIP();
}

BOOL CScriptCmd_SubCountryScore::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubCountryScore error" );
        return FALSE;
    }

    nValue = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_SubCountryScore::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SubCountryScore( nValue );
    vm->NextIP();
}

BOOL CScriptCmd_SetCountryScore::Create( WordParser* words )
{ 
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetCountryScore error" );
        return FALSE;
    }

    nValue = atoi( words->GetWord( 0 ) );
    return TRUE; 
}

void CScriptCmd_SetCountryScore::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetCountryScore( nValue );
    vm->NextIP();
}

BOOL CScriptCmd_GetCountryOfficial::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetCountryOfficial::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->GetCountryOfficial();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetWarSortIndex::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetWarSortIndex::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->GetWarSortIndex();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsInCountryWarFight::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_IsInCountryWarFight::Execute( CScriptVM* vm )
{
    int nResult = GetScriptInterface()->IsInCountryWarFight();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nResult );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_SetCountryKing::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_SetCountryKing::Execute(CScriptVM *vm)
{
	int nResult = GetScriptInterface()->SetCountryKing();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nResult );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}

BOOL CScriptCmd_SetCountryTribute::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetCountryTribute error" );
		return FALSE;
	}

	nValue = atoi( words->GetWord( 0 ) );
	countryid = atoi( words->GetWord( 1 ) );
	return TRUE;
}

void CScriptCmd_SetCountryTribute::Execute(CScriptVM *vm)
{
	GetScriptInterface()->SetCountryTribute( nValue,countryid,EOT_Set);
	vm->NextIP();
}

BOOL CScriptCmd_AddCountryTribute::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddCountryTribute error" );
		return FALSE;
	}

	nValue = atoi( words->GetWord( 0 ) );
	countryid = atoi( words->GetWord( 1 ) );
	return TRUE;
}

void CScriptCmd_AddCountryTribute::Execute(CScriptVM *vm)
{
	GetScriptInterface()->SetCountryTribute( nValue,countryid,EOT_Add);
	vm->NextIP();
}

BOOL CScriptCmd_SubCountryTribute::Create( WordParser* words )
{
	if( words->GetWordCount() != 2 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubCountryTribute error" );
		return FALSE;
	}

	nValue = atoi( words->GetWord( 0 ) );
	countryid = atoi( words->GetWord( 1 ) );
	return TRUE;
}

void CScriptCmd_SubCountryTribute::Execute(CScriptVM *vm)
{
	GetScriptInterface()->SetCountryTribute( nValue,countryid,EOT_Sub);
	vm->NextIP();
}

BOOL CScriptCmd_GetCountryTribute::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetCountryTribute error" );
		return FALSE;
	}

	countryid = atoi( words->GetWord( 0 ) );
	return TRUE;
}

void CScriptCmd_GetCountryTribute::Execute(CScriptVM *vm)
{
	int nResult = GetScriptInterface()->GetCountryTribute(countryid);
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nResult );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}

BOOL CScriptCmd_IsPlayerKing::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsPlayerKing::Execute( CScriptVM* vm )
{
	int nResult = GetScriptInterface()->IsPlayerKing();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nResult );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	vm->NextIP();
}

BOOL CScriptCmd_AddCountryInfo::Create( WordParser* words )
{
	if( words->GetWordCount() != 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddCountryInfo error" );
		return FALSE;
	}
	Info = words->GetWord(0);
	//strcat_s(Info,CountryDefine::MaxCountryInfoLength,words->GetWord(0));
	IsUseName = atoi(words->GetWord(1)) == 1? true:false;
	Value = atoi(words->GetWord(2));
	return TRUE;
}

void CScriptCmd_AddCountryInfo::Execute(CScriptVM *vm)
{
	//Ö´ÐÐº¯Êý
	GetScriptInterface()->AddCountryInfo(Info.c_str(),IsUseName,Value);
	vm->NextIP();
}