#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"
#include "ScriptVarMgr.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( GetGuildId, CScriptCmd_GetGuildId );
SCRIPT_DECLARE( IsHaveGuild, CScriptCmd_IsHaveGuild );
SCRIPT_DECLARE( IsGuildMaster, CScriptCmd_IsGuildMaster );
SCRIPT_DECLARE( GetGuildOffer, CScriptCmd_GetGuildOffer );
SCRIPT_DECLARE( AddGuildOffer, CScriptCmd_AddGuildOffer );
SCRIPT_DECLARE( DecGuildOffer, CScriptCmd_DecGuildOffer );
SCRIPT_DECLARE( GetGuildActivity, CScriptCmd_GetGuildActivity );
SCRIPT_DECLARE( AddGuildActivity, CScriptCmd_AddGuildActivity );
SCRIPT_DECLARE( DecGuildActivity, CScriptCmd_DecGuildActivity );
SCRIPT_DECLARE( GetGuildBuild, CScriptCmd_GetGuildBuild );
SCRIPT_DECLARE( AddGuildBuild, CScriptCmd_AddGuildBuild );
SCRIPT_DECLARE( DecGuildBuild, CScriptCmd_DecGuildBuild );
SCRIPT_DECLARE( GetGuildMoney, CScriptCmd_GetGuildMoney );
SCRIPT_DECLARE( AddGuildMoney, CScriptCmd_AddGuildMoney );
SCRIPT_DECLARE( DecGuildMoney, CScriptCmd_DecGuildMoney );
SCRIPT_DECLARE( GetGuildMission, CScriptCmd_GetGuildMission );
SCRIPT_DECLARE( AddGuildMission, CScriptCmd_AddGuildMission );
SCRIPT_DECLARE( DecGuildMission, CScriptCmd_DecGuildMission );
SCRIPT_DECLARE( GetGuildSalary, CScriptCmd_GetGuildSalary );
SCRIPT_DECLARE( AddGuildSalary, CScriptCmd_AddGuildSalary );
SCRIPT_DECLARE( DecGuildSalary, CScriptCmd_DecGuildSalary );
SCRIPT_DECLARE( GetGuildLevel, CScriptCmd_GetGuildLevel );
SCRIPT_DECLARE( SetGuildLevel, CScriptCmd_SetGuildLevel );
SCRIPT_DECLARE( AddGuildVar, CScriptCmd_AddGuildVar );
SCRIPT_DECLARE( DecGuildVar, CScriptCmd_DecGuildVar );
SCRIPT_DECLARE( SetGuildVar, CScriptCmd_SetGuildVar );
SCRIPT_DECLARE( GetGuildVar, CScriptCmd_GetGuildVar );
SCRIPT_DECLARE( RecordGuildTimeVar, CScriptCmd_RecordGuildTimeVar );
SCRIPT_DECLARE( IsGuildTimeVarPassOneDay, CScriptCmd_IsGuildTimeVarPassOneDay );
SCRIPT_DECLARE( ClearGuildTimeVar, CScriptCmd_ClearGuildTimeVar );
SCRIPT_DECLARE( GuildLevelUp, CScriptCmd_GuildLevelUp );
SCRIPT_DECLARE( GuildOfferBuild, CScriptCmd_GuildOfferBuild );
SCRIPT_DECLARE( GuildCollect, CScriptCmd_GuildCollect );
SCRIPT_DECLARE( GuildMasterDelate, CScriptCmd_GuildMasterDelate );
SCRIPT_DECLARE( GuildDonate, CScriptCmd_GuildDonate );
SCRIPT_DECLARE( GuildQuestRelease, CScriptCmd_GuildQuestRelease );
SCRIPT_DECLARE( GuildShopLevelUp, CScriptCmd_GuildShopLevel );
SCRIPT_DECLARE( GuildConvene, CScriptCmd_GuildConvene );
SCRIPT_DECLARE( GetGuildReleaseQuest, CScriptCmd_GetGuildReleaseQuest );
SCRIPT_DECLARE( AddGuildBuffByMapID, CScriptCmd_AddGuildBuffByMapID );


SCRIPT_DECLARE( GetGuildMemberPosition, CScriptCmd_GetGuildMemberPosition );

////////////////////////////////////////////////////////////////////////
BOOL CScriptCmd_GetGuildId::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildId::Execute( CScriptVM* vm )
{
    int nId = GetScriptInterface()->GetGuildId();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param stParam;
        stParam.SetNumber( nId );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, &stParam, 1 );
    }
    //
    vm->NextIP();
}


BOOL CScriptCmd_IsHaveGuild::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_IsHaveGuild::Execute( CScriptVM* vm )
{
    int nReturn = GetScriptInterface()->IsHaveGuild();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nReturn );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

BOOL CScriptCmd_IsGuildMaster::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_IsGuildMaster::Execute( CScriptVM* vm )
{
    bool bCheck = GetScriptInterface()->IsGuildMaster();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( bCheck );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    //
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildOffer::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildOffer::Execute( CScriptVM* vm )
{
    int nOffer = GetScriptInterface()->GetGuildOffer();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nOffer );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildOffer::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:AddGuildOffer" );
        return FALSE;
    }
    //nCredit = atoi( words->GetWord(0) );
    const char* szCredit = words->GetWord(0);
    if ( WordParser::IsNumber(szCredit) )
    {
        m_Credit.SetNumber( atoi(szCredit) );
        m_Credit.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szCredit);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildOffer");
            return FALSE;
        }
        m_Credit.SetNumber(nKey);
        m_Credit.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_AddGuildOffer::Execute( CScriptVM* vm )
{
    int nCredit = 0;
    if (m_Credit.IsKey())
    {
        int nKey = m_Credit.GetNumber();
        nCredit = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nCredit = m_Credit.GetNumber();
    }
    GetScriptInterface()->AddGuildOffer(nCredit); 
    vm->NextIP();
}


BOOL CScriptCmd_DecGuildOffer::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildOffer");
        return FALSE;
    }

    //nCredit = atoi( words->GetWord(0) );
    const char* szCredit = words->GetWord(0);
    if ( WordParser::IsNumber(szCredit) )
    {
        m_Credit.SetNumber( atoi(szCredit) );
        m_Credit.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szCredit);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildOffer");
            return FALSE;
        }
        m_Credit.SetNumber(nKey);
        m_Credit.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_DecGuildOffer::Execute( CScriptVM* vm )
{
    int nCredit = 0;
    if (m_Credit.IsKey())
    {
        int nKey = m_Credit.GetNumber();
        nCredit = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nCredit = m_Credit.GetNumber();
    }

    GetScriptInterface()->DecGuildOffer(nCredit); 
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildActivity::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildActivity::Execute( CScriptVM* vm )
{
    int nOffer = GetScriptInterface()->GetGuildActivity();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nOffer );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildActivity::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR,"error:AddGuildActivity" );
        return FALSE;
    }
    nCredit = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_AddGuildActivity::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddGuildActivity(nCredit); 
    vm->NextIP();
}


BOOL CScriptCmd_DecGuildActivity::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildActivity");
        return FALSE;
    }

    nCredit = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_DecGuildActivity::Execute( CScriptVM* vm )
{
    GetScriptInterface()->DecGuildActivity(nCredit); 
    vm->NextIP();
}


BOOL CScriptCmd_GetGuildBuild::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildBuild::Execute( CScriptVM* vm )
{
    int nCredit = GetScriptInterface()->GetGuildBuild();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param    m_params[1];
        m_params[0].SetNumber( nCredit );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildBuild::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:AddGuildBuild" );
        return FALSE;
    }
    //nCredit = atoi( words->GetWord(0) );
    const char* szCredit = words->GetWord(0);
    if ( WordParser::IsNumber(szCredit) )
    {
        m_Credit.SetNumber( atoi(szCredit) );
        m_Credit.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szCredit);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildBuild");
            return FALSE;
        }
        m_Credit.SetNumber(nKey);
        m_Credit.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_AddGuildBuild::Execute( CScriptVM* vm )
{
    int nCredit = 0;
    if (m_Credit.IsKey())
    {
        int nKey = m_Credit.GetNumber();
        nCredit = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nCredit = m_Credit.GetNumber();
    }
    GetScriptInterface()->AddGuildBuild(nCredit); 
    vm->NextIP();
}

BOOL CScriptCmd_DecGuildBuild::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildBuild" );
        return FALSE;
    }
    //nCredit = atoi( words->GetWord(0) );
    const char* szCredit = words->GetWord(0);
    if ( WordParser::IsNumber(szCredit) )
    {
        m_Credit.SetNumber( atoi(szCredit) );
        m_Credit.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szCredit);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildBuild");
            return FALSE;
        }
        m_Credit.SetNumber(nKey);
        m_Credit.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_DecGuildBuild::Execute( CScriptVM* vm )
{
    int nCredit = 0;
    if (m_Credit.IsKey())
    {
        int nKey = m_Credit.GetNumber();
        nCredit = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nCredit = m_Credit.GetNumber();
    }

    GetScriptInterface()->DecGuildBuild(nCredit); 
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildMoney::Create( WordParser* words )
{
    if( words->GetWordCount() != 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:GetGuildMoney");
        return FALSE;
    }
    return TRUE;
}

void CScriptCmd_GetGuildMoney::Execute( CScriptVM* vm )
{
    int32 nValue = GetScriptInterface()->GetGuildMoney();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildMoney::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:AddGuildMoney" );
        return FALSE;
    }
    //nValue = atoi( words->GetWord(0) );
    const char* szValue = words->GetWord(0);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildMoney");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_AddGuildMoney::Execute( CScriptVM* vm )
{
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

    GetScriptInterface()->AddGuildMoney( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_DecGuildMoney::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildMoney" );
        return FALSE;
    }
    //nValue = atoi( words->GetWord(0) );
    const char* szValue = words->GetWord(0);
    if ( WordParser::IsNumber(szValue) )
    {
        m_Value.SetNumber( atoi(szValue) );
        m_Value.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szValue);
        if (nKey == 1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildMoney");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_DecGuildMoney::Execute( CScriptVM* vm )
{
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

    GetScriptInterface()->DecGuildMoney( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildMission::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildMission::Execute( CScriptVM* vm )
{
    int32 nValue = GetScriptInterface()->GetGuildMission();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildMission::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:AddGuildMission" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_AddGuildMission::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddGuildMission( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_DecGuildMission::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildMission" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_DecGuildMission::Execute( CScriptVM* vm )
{
    GetScriptInterface()->DecGuildMission( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildSalary::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildSalary::Execute( CScriptVM* vm )
{
    int32 nValue = GetScriptInterface()->GetGuildSalary();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildSalary::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:AddGuildSalary" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_AddGuildSalary::Execute( CScriptVM* vm )
{
    GetScriptInterface()->AddGuildSalary( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_DecGuildSalary::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:DecGuildSalary" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_DecGuildSalary::Execute( CScriptVM* vm )
{
    GetScriptInterface()->DecGuildSalary( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_GetGuildLevel::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GetGuildLevel::Execute( CScriptVM* vm )
{
    CScriptCmd__SetVar::Param m_params[1];
    int16 nLevel = GetScriptInterface()->GetGuildLevel();
    m_params[0].SetNumber( nLevel );
    GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    vm->NextIP();
}

BOOL CScriptCmd_SetGuildLevel::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT,LOG_PRIORITY_ERROR, "error:SetGuildLevel" );
        return FALSE;
    }
    nValue = atoi( words->GetWord(0) );
    return TRUE;
}

void CScriptCmd_SetGuildLevel::Execute( CScriptVM* vm )
{
    GetScriptInterface()->SetGuildLevel( nValue ); 
    vm->NextIP();
}

BOOL CScriptCmd_AddGuildVar::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "AddGuildVar error" );
        return FALSE;
    }

    //m_nIndex = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szIndex = words->GetWord(0);
    if ( WordParser::IsNumber(szIndex) )
    {
        m_Index.SetNumber( atoi(szIndex) );
        m_Index.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szIndex);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildVar");
            return FALSE;
        }
        m_Index.SetNumber(nKey);
        m_Index.SetIsKey(true);
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
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildVar");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_AddGuildVar::Execute( CScriptVM* vm )
{
    int nIndex = 0;
    if ( m_Index.IsKey() )
    {
        int nKey = m_Index.GetNumber();
        nIndex = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nIndex = m_Index.GetNumber();
    }
    int nValue = 0;
    if ( m_Value.IsKey() )
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->AddGuildVar( nIndex, nValue );
    vm->NextIP();
}

BOOL CScriptCmd_DecGuildVar::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "DecGuildVar error" );
        return FALSE;
    }

    //m_nIndex = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szIndex = words->GetWord(0);
    if ( WordParser::IsNumber(szIndex) )
    {
        m_Index.SetNumber( atoi(szIndex) );
        m_Index.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szIndex);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildVar");
            return FALSE;
        }
        m_Index.SetNumber(nKey);
        m_Index.SetIsKey(true);
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
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildVar");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }


    return TRUE;
}

void CScriptCmd_DecGuildVar::Execute( CScriptVM* vm )
{
    int nIndex = 0;
    if ( m_Index.IsKey() )
    {
        int nKey = m_Index.GetNumber();
        nIndex = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nIndex = m_Index.GetNumber();
    }
    int nValue = 0;
    if ( m_Value.IsKey() )
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->DecGuildVar( nIndex, nValue );
    vm->NextIP();
}


BOOL CScriptCmd_SetGuildVar::Create( WordParser* words )
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetGuildVar error" );
        return FALSE;
    }

    //m_nIndex = atoi( words->GetWord( 0 ) );
    //m_nValue = atoi( words->GetWord( 1 ) );
    const char* szIndex = words->GetWord(0);
    if ( WordParser::IsNumber(szIndex) )
    {
        m_Index.SetNumber( atoi(szIndex) );
        m_Index.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szIndex);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildVar");
            return FALSE;
        }
        m_Index.SetNumber(nKey);
        m_Index.SetIsKey(true);
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
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildVar");
            return FALSE;
        }
        m_Value.SetNumber(nKey);
        m_Value.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_SetGuildVar::Execute( CScriptVM* vm )
{
    int nIndex = 0;
    if ( m_Index.IsKey() )
    {
        int nKey = m_Index.GetNumber();
        nIndex = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nIndex = m_Index.GetNumber();
    }
    int nValue = 0;
    if ( m_Value.IsKey() )
    {
        int nKey = m_Value.GetNumber();
        nValue = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nValue = m_Value.GetNumber();
    }

    GetScriptInterface()->SetGuildVar( nIndex, nValue );
    vm->NextIP();
}


BOOL CScriptCmd_GetGuildVar::Create( WordParser* words )
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "GetGuildVar error" );
        return FALSE;
    }

    //m_nIndex = atoi( words->GetWord( 0 ) );
    const char* szIndex = words->GetWord(0);
    if ( WordParser::IsNumber(szIndex) )
    {
        m_Index.SetNumber( atoi(szIndex) );
        m_Index.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szIndex);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:DecGuildVar");
            return FALSE;
        }
        m_Index.SetNumber(nKey);
        m_Index.SetIsKey(true);
    }

    return TRUE;
}

void CScriptCmd_GetGuildVar::Execute( CScriptVM* vm )
{
    int nIndex = 0;
    if ( m_Index.IsKey() )
    {
        int nKey = m_Index.GetNumber();
        nIndex = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        nIndex = m_Index.GetNumber();
    }

    int nValue = GetScriptInterface()->GetGuildVar( nIndex );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( nValue );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    vm->NextIP();
}


BOOL CScriptCmd_RecordGuildTimeVar::Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[RecordGuildTimeVar] " );
        return FALSE;
    }

    const char* szWord = words->GetWord( 0 );
    //nVarId = atoi(szWord); 
    if (WordParser::IsNumber(szWord))
    {
        m_VarId.SetNumber( atoi(szWord) );
        m_VarId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szWord);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:RecordGuildTime");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_RecordGuildTimeVar::Execute( CScriptVM* pVM )
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
    bool bResult = GetScriptInterface()->RecordGuildTimeVar( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}

BOOL CScriptCmd_IsGuildTimeVarPassOneDay::Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[IsGuildTimeVarPassOneDay] " );
        return FALSE;
    }

    nVarId      = atoi( words->GetWord( 0 ) ); 
    return TRUE;
}

void CScriptCmd_IsGuildTimeVarPassOneDay::Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->IsGuildTimeVarPassOneDay( nVarId );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}

BOOL CScriptCmd_ClearGuildTimeVar::Create(WordParser* words)
{
    if( words->GetWordCount() != 2 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:[ClearGuildTimeVar] " );
        return FALSE;
    }

    //nVarId      = atoi( words->GetWord( 0 ) ); 
    const char* szVarId = words->GetWord(0);
    if (WordParser::IsNumber(szVarId))
    {
        m_VarId.SetNumber(atoi(szVarId));
        m_VarId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szVarId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearGuildTimeVar");
            return FALSE;
        }
        m_VarId.SetNumber(nKey);
        m_VarId.SetIsKey(true);
    }
    const char* szClearVarId = words->GetWord(1);
    if (WordParser::IsNumber(szClearVarId))
    {
        m_ClearVarId.SetNumber( atoi(szClearVarId) );
        m_ClearVarId.SetIsKey(false);
    } 
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szClearVarId);
        if (nKey == -1)
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:ClearGuildTimeVar");
            return FALSE;
        }
        m_ClearVarId.SetNumber(nKey);
        m_ClearVarId.SetIsKey(true);
    }
    return TRUE;
}

void CScriptCmd_ClearGuildTimeVar::Execute( CScriptVM* pVM )
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

    GetScriptInterface()->ClearGuildTimeVar( nVarId, nClearVarId );
    pVM->NextIP();
}

BOOL CScriptCmd_GuildLevelUp::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GuildLevelUp::Execute( CScriptVM* vm )
{
    GetScriptInterface()->GuildLevelUp();
    vm->NextIP();
}

BOOL CScriptCmd_GuildOfferBuild::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GuildOfferBuild::Execute( CScriptVM* vm )
{
    GetScriptInterface()->GuildOfferBuild();
    vm->NextIP();
}

BOOL CScriptCmd_GuildCollect::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GuildCollect::Execute( CScriptVM* vm )
{
    GetScriptInterface()->GuildCollect();
    vm->NextIP();
}

BOOL CScriptCmd_GuildMasterDelate::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GuildMasterDelate::Execute( CScriptVM* vm )
{
    GetScriptInterface()->GuildMasterDelate();
    vm->NextIP();
}

BOOL CScriptCmd_GuildDonate::Create( WordParser* words )
{
    return TRUE;
}

void CScriptCmd_GuildDonate::Execute( CScriptVM* vm )
{
    GetScriptInterface()->GuildDonate();
    vm->NextIP();
}


BOOL CScriptCmd_GuildQuestRelease::Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GuildQuestRelease " );
        return FALSE;
    }

    nQuestID = atoi( words->GetWord( 0 ) ); 

    return TRUE;
}

void CScriptCmd_GuildQuestRelease::Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->GuildQuestRelease( nQuestID );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}

BOOL CScriptCmd_GetGuildReleaseQuest::Create(WordParser* words)
{
	return TRUE;
}

void CScriptCmd_GetGuildReleaseQuest::Execute( CScriptVM* pVM )
{
	int16 _Result = GetScriptInterface()->GetGuildReleaseQuest();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( _Result);
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	pVM->NextIP();
}

BOOL CScriptCmd_AddGuildBuffByMapID::Create( WordParser* words )
{
	if( words->GetWordCount() != 3 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:AddGuildBuffByMapID" );
        return FALSE;
    }
	//MapID
    const char* szMapID = words->GetWord(0);
    if (WordParser::IsNumber(szMapID))
    {
        m_MapID.SetNumber( atoi(szMapID) );
        m_MapID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szMapID);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildBuffByMapID");
            return FALSE;
        }
        m_MapID.SetNumber(nKey);
        m_MapID.SetIsKey(true);
    }
	//BuffID
	const char* szBuffID = words->GetWord(1);
    if (WordParser::IsNumber(szBuffID))
    {
        m_BuffID.SetNumber( atoi(szBuffID) );
        m_BuffID.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szBuffID);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildBuffByMapID");
            return FALSE;
        }
        m_BuffID.SetNumber(nKey);
        m_BuffID.SetIsKey(true);
    }
	//BuffLevel
	const char* szBuffLevel = words->GetWord(2);
    if (WordParser::IsNumber(szBuffLevel))
    {
        m_BuffLevel.SetNumber( atoi(szBuffLevel) );
        m_BuffLevel.SetIsKey(false);
    }
    else
    {
        int nKey = GetScriptVarMgr()->GetVarId(szBuffLevel);
        if ( nKey == -1 )
        {
            LOG_MESSAGE(SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Error:AddGuildBuffByMapID");
            return FALSE;
        }
        m_BuffLevel.SetNumber(nKey);
        m_BuffLevel.SetIsKey(true);
    }
    return TRUE;
}
void CScriptCmd_AddGuildBuffByMapID::Execute( CScriptVM* pVM )
{
	//获取参数
	int MapID = 0;
	int BuffID = 0;
	int BuffLevel = 0;
    if (m_MapID.IsKey())
    {
        int nKey = m_MapID.GetNumber();
        MapID = GetScriptInterface()->GetVar(nKey);
    }
    else
    {
        MapID = m_MapID.GetNumber();
    }

	if (m_BuffID.IsKey())
    {
        int nKey = m_BuffID.GetNumber();
        BuffID = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        BuffID = m_BuffID.GetNumber();
    }

	if (m_BuffLevel.IsKey())
    {
        int nKey = m_BuffLevel.GetNumber();
        BuffLevel = GetScriptInterface()->GetVar(nKey);
    } 
    else
    {
        BuffLevel = m_BuffLevel.GetNumber();
    }

	GetScriptInterface()->AddGuildBuffByMapID(MapID,BuffID,BuffLevel);
	pVM->NextIP();
}

BOOL CScriptCmd_GuildShopLevel::Create(WordParser* words)
{
    if( words->GetWordCount() != 1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "error:GuildShopLevelUp " );
        return FALSE;
    }

    nLevel = atoi( words->GetWord( 0 ) ); 

    return TRUE;
}

void CScriptCmd_GuildShopLevel::Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->GuildShopLevelUp( nLevel );
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}

BOOL CScriptCmd_GuildConvene::Create(WordParser* words)
{
    return TRUE;
}

void CScriptCmd_GuildConvene::Execute( CScriptVM* pVM )
{
    bool bResult = GetScriptInterface()->GuildConvene();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( bResult ? 1 : 0 );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}

BOOL CScriptCmd_GetGuildMemberPosition::Create(WordParser* words)
{
    return TRUE;
}

void CScriptCmd_GetGuildMemberPosition::Execute( CScriptVM* pVM )
{
    int Pos = GetScriptInterface()->GetGuildMemberPosition();
    if ( m_nReturnKey != -1 )
    {
        CScriptCmd__SetVar::Param m_params[1];
        m_params[0].SetNumber( Pos );
        GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
    }
    pVM->NextIP();
}
