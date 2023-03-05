#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"
#include "ScriptVarMgr.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( IsHaveTeacher, CScriptCmd_IsHaveTeacher );
SCRIPT_DECLARE( GetMasterLevel, CScriptCmd_GetMasterLevel );
SCRIPT_DECLARE( MasterLevelUp, CScriptCmd_MasterLevelUp );
SCRIPT_DECLARE( AddMasterValue, CScriptCmd_AddMasterValue );
SCRIPT_DECLARE( SubMasterValue, CScriptCmd_SubMasterValue );
SCRIPT_DECLARE( GetMasterValue, CScriptCmd_GetMasterValue );
SCRIPT_DECLARE( RegisterTeacher, CScriptCmd_RegisterTeacher );
SCRIPT_DECLARE( RegisterStudent, CScriptCmd_RegisterStudent );
SCRIPT_DECLARE( QueryTeacher, CScriptCmd_QueryTeacher );
SCRIPT_DECLARE( QueryStudent, CScriptCmd_QueryStudent );
SCRIPT_DECLARE( CheckCanMarriage, CScriptCmd_CheckCanMarriage );
SCRIPT_DECLARE( AddMarriage, CScriptCmd_AddMarriage );
SCRIPT_DECLARE( RemoveMarriage, CScriptCmd_RemoveMarriage );
SCRIPT_DECLARE( CheckCanReceiveMarriageQuest, CScriptCmd_CheckCanReceiveMarriageQuest );
SCRIPT_DECLARE( CreageMarriageStage, CScriptCmd_CreageMarriageStage );
SCRIPT_DECLARE( FlyToMarriageMap, CScriptCmd_FlyToMarriageMap );
SCRIPT_DECLARE( GetMaxFriendlyLevel, CScriptCmd_GetMaxFriendlyLevel );
SCRIPT_DECLARE( IsCanReceiveFriendlyQuest, CScriptCmd_IsCanReceiveFriendlyQuest );
SCRIPT_DECLARE( SaveReceiveFriendlyQuest, CScriptCmd_SaveReceiveFriendlyQuest );
SCRIPT_DECLARE( GetReqRemoveMarriage, CScriptCmd_GetReqRemoveMarriage );
SCRIPT_DECLARE( GetForceRemove, CScriptCmd_GetForceRemove );
SCRIPT_DECLARE( AddStudent, CScriptCmd_AddStudent );
SCRIPT_DECLARE( RemoveTeacher, CScriptCmd_RemoveTeacher );
SCRIPT_DECLARE( IsCanRegisterTeacher, CScriptCmd_IsCanRegisterTeacher );
SCRIPT_DECLARE( IsCanRegisterStudent, CScriptCmd_IsCanRegisterStudent );
SCRIPT_DECLARE( GetStudentCount, CScriptCmd_GetStudentCount );
SCRIPT_DECLARE( QueryAddStudentLeftTime, CScriptCmd_QueryAddStudentLeftTime );
SCRIPT_DECLARE( QueryAddTeacherLeftTime, CScriptCmd_QueryAddTeacherLeftTime );

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


BOOL CScriptCmd_IsHaveTeacher::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_IsHaveTeacher::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->IsHaveTeacher();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_GetMasterLevel::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetMasterLevel::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->GetMasterLevel();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_MasterLevelUp::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_MasterLevelUp::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->MasterLevelUp();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_AddMasterValue::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddMasterValue error" );
        return FALSE;
    }

    //m_ustValue = atoi( words->GetWord( 0 ) );
    const char* szValue = words->GetWord(0);
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
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddMasterValue");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_AddMasterValue::Execute( CScriptVM* vm )
{
    unsigned short ustValue;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        ustValue = (unsigned short)( GetScriptInterface()->GetVar(nKey) );
    } 
    else
    {
        ustValue = (unsigned short)( m_Value.GetNumber() );
    }
    GetScriptInterface()->AddMasterValue( ustValue );
    vm->NextIP();
}


BOOL CScriptCmd_SubMasterValue::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SubMasterValue error" );
        return FALSE;
    }

    //m_ustValue = atoi( words->GetWord( 0 ) );
    const char* szValue = words->GetWord(0);
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
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:SubMasterValue");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_SubMasterValue::Execute( CScriptVM* vm )
{
    unsigned short ustValue;
    if (m_Value.IsKey())
    {
        int nKey = m_Value.GetNumber();
        ustValue = (unsigned short)( GetScriptInterface()->GetVar(nKey) );
    } 
    else
    {
        ustValue = (unsigned short)( m_Value.GetNumber() );
    }

    GetScriptInterface()->SubMasterValue( ustValue );
    vm->NextIP();
}

BOOL CScriptCmd_GetMasterValue::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetMasterValue::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->GetMasterValue();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_RegisterTeacher::Create( WordParser* words )
{
    return TRUE;
}


void CScriptCmd_RegisterTeacher::Execute( CScriptVM* vm )
{
    GetScriptInterface()->RegisterTeacher();
    vm->NextIP();
}

BOOL CScriptCmd_RegisterStudent::Create( WordParser* words )
{
    return TRUE;
}


void CScriptCmd_RegisterStudent::Execute( CScriptVM* vm )
{
    GetScriptInterface()->RegisterStudent();
    vm->NextIP();
}


BOOL CScriptCmd_QueryTeacher::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_QueryTeacher::Execute( CScriptVM* vm )
{
    GetScriptInterface()->QueryTeacher();
    vm->NextIP();
}

BOOL CScriptCmd_QueryStudent::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_QueryStudent::Execute( CScriptVM* vm )
{
    GetScriptInterface()->QueryStudent();
    vm->NextIP();
}

BOOL CScriptCmd_CheckCanMarriage::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_CheckCanMarriage::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->CheckCanMarriage();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddMarriage::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_AddMarriage::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->AddMarriage();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_RemoveMarriage::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "RemoveMarriage error" );
        return FALSE;
    }

    m_bForceRemove = atoi( words->GetWord( 0 ) );

    return TRUE;
}

void CScriptCmd_RemoveMarriage::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->RemoveMarriage( m_bForceRemove );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_CheckCanReceiveMarriageQuest::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CheckCanReceiveMarriageQuest error" );
        return FALSE;
    }

    m_bMarriage = atoi( words->GetWord( 0 ) );
    return TRUE;
}

void CScriptCmd_CheckCanReceiveMarriageQuest::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->CheckCanReceiveMarriageQuest( m_bMarriage );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_CreageMarriageStage::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreageMarriageStage error" );
        return FALSE;
    }

    m_ustMapID = atoi( words->GetWord( 0 ) );

    return TRUE;
}

void CScriptCmd_CreageMarriageStage::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->CreageMarriageStage( m_ustMapID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_FlyToMarriageMap::Create( WordParser* words )
{
    if( words->GetWordCount() != 4 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "CreageMarriageStage error" );
        return FALSE;
    }

    m_ustMapID = atoi( words->GetWord( 0 ) );
    m_fX       = atof( words->GetWord( 1 ) );
    m_fY       = atof( words->GetWord( 2 ) );
    m_fDir     = atof( words->GetWord( 3 ) );

    return TRUE;
}

void CScriptCmd_FlyToMarriageMap::Execute( CScriptVM* vm )
{
    int nValue = GetScriptInterface()->FlyToMarriageMap( m_ustMapID, m_fX, m_fY, m_fDir );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_GetMaxFriendlyLevel::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetMaxFriendlyLevel::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->GetMaxFriendlyLevel( );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsCanReceiveFriendlyQuest::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_IsCanReceiveFriendlyQuest::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->IsCanReceiveFriendlyQuest( );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_SaveReceiveFriendlyQuest::Create( WordParser* words )
{ 
    return TRUE; 
}
void CScriptCmd_SaveReceiveFriendlyQuest::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SaveReceiveFriendlyQuest();
    vm->NextIP();
}

BOOL CScriptCmd_GetReqRemoveMarriage::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetReqRemoveMarriage::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->GetReqRemoveMarriage();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetForceRemove::Create( WordParser* words )
{ 
    return TRUE; 
}
void CScriptCmd_GetForceRemove::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->GetForceRemove();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_AddStudent::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_AddStudent::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddStudent();
    vm->NextIP();
}

BOOL CScriptCmd_RemoveTeacher::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_RemoveTeacher::Execute( CScriptVM* vm )
{
    GetScriptInterface()->RemoveTeacher();
    vm->NextIP();
}

BOOL CScriptCmd_IsCanRegisterTeacher::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_IsCanRegisterTeacher::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->IsCanRegisterTeacher();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_IsCanRegisterStudent::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_IsCanRegisterStudent::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->IsCanRegisterStudent();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_GetStudentCount::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_GetStudentCount::Execute( CScriptVM* vm )
{
    int result = GetScriptInterface()->GetStudentCount();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( result );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_QueryAddStudentLeftTime::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_QueryAddStudentLeftTime::Execute( CScriptVM* vm )
{
    GetScriptInterface()->QueryAddStudentLeftTime();
    vm->NextIP();
}


BOOL CScriptCmd_QueryAddTeacherLeftTime::Create( WordParser* words )
{ 
    return TRUE; 
}

void CScriptCmd_QueryAddTeacherLeftTime::Execute( CScriptVM* vm )
{
    GetScriptInterface()->QueryAddTeacherLeftTime();
    vm->NextIP();
}
