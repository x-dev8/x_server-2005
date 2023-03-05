#include "ScriptFunctionDefine.h"
#include "ScriptKeyWord.h"
#include "ScriptVM.h"
#include "ScriptAbstract.h"
#include "WordParser.h"
#include "GlobalDef.h"
#include "ScriptVarMgr.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( IsHaveFamily, CScriptCmd_IsHaveFamily );
SCRIPT_DECLARE( IsFamilyMaster, CScriptCmd_IsFamilyMaster );
SCRIPT_DECLARE( IsExistFamily, CScriptCmd_IsExistFamily );

BOOL CScriptCmd_IsHaveFamily::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsHaveFamily::Execute( CScriptVM* vm )
{
	int nReturn = GetScriptInterface()->IsHaveFamily();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param m_params[1];
		m_params[0].SetNumber( nReturn );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	//
	vm->NextIP();
}

BOOL CScriptCmd_IsFamilyMaster::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsFamilyMaster::Execute( CScriptVM* vm )
{
	bool bCheck = GetScriptInterface()->IsFamilyMaster();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param    m_params[1];
		m_params[0].SetNumber( bCheck );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	//
	vm->NextIP();

}

BOOL CScriptCmd_IsExistFamily::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_IsExistFamily::Execute( CScriptVM* vm )
{
	bool bCheck = GetScriptInterface()->IsExistFamily();
	if ( m_nReturnKey != -1 )
	{
		CScriptCmd__SetVar::Param    m_params[1];
		m_params[0].SetNumber( bCheck );
		GetScriptInterface()->SetVar( m_nReturnKey, SKW_SET, m_params, 1 );
	}
	//
	vm->NextIP();

}

