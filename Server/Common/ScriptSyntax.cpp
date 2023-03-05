#include "ScriptSyntax.h"
#include "ScriptVM.h"

extern IScriptInterface* GetScriptInterface();

SCRIPT_DECLARE( proc_start,     CScriptCmd_ProcStart );
SCRIPT_DECLARE( proc_end,       CScriptCmd_ProcEnd );
SCRIPT_DECLARE( call,           CScriptCmd_Call );
SCRIPT_DECLARE( return,         CScriptCmd_Return );
SCRIPT_DECLARE( if,             CScriptCmd_If );
SCRIPT_DECLARE( else,           CScriptCmd_Else );
SCRIPT_DECLARE( jumptoendif,    CScriptCmd_JumpToEndIf );
SCRIPT_DECLARE( endif,          CScriptCmd_EndIf );
SCRIPT_DECLARE( jump,           CScriptCmd_Jump );

// proc_start 0
BOOL CScriptCmd_ProcStart::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "proc_start create error, params count != 1" );
		return FALSE;
	}
	if( !words->IsNumber( 0 ) )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "proc_start create error, param is not number" );
		return FALSE;
	}
	m_nProcId = atoi( words->GetWord( 0 ) );
	return TRUE;
}

void CScriptCmd_ProcStart::Execute( CScriptVM* vm )
{
	//vm->PushIPAddr();
	vm->NextIP();
}

// proc end
void CScriptCmd_ProcEnd::Execute( CScriptVM* vm )
{ 
	if( !vm->PopIPAddr() )
	{
		vm->Return();
		return;
	}
	//vm->NextIP();

	//if( !vm->PopIPAddr() )
	//  vm->Return();
}

// if money < 1000
BOOL CScriptCmd_If::Create( WordParser* words )
{
	if( words->GetWordCount() != 3 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "if create error, param count != 3" );
		return FALSE;
	}

	m_key = GetScriptVarMgr()->GetVarId( words->GetWord(0) );
	if( m_key == -1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script can't find variable [%s] ", words->GetWord(0));
		return FALSE;           
	}

	m_op = g_skwMgr.GetKeyWord( words->GetWord( 1 ) );
	if( !g_skwMgr.IsLogicOperator( m_op ) )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "if create error, param 1 is not logic operator" );
		return FALSE;
	}
	if( words->IsNumber( 2 ) )
	{
		m_bValIsKey = false;
		m_nValue = atoi( words->GetWord( 2 ) );
	}
	else
	{
		m_bValIsKey = true;
		m_nValue = GetScriptVarMgr()->GetVarId( words->GetWord( 2 ) );
		if ( m_nValue == -1 )
		{
			LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "if create error, param 2 is not var!" );
			return FALSE;
		}
	}
	return TRUE;
}

void CScriptCmd_If::Execute( CScriptVM* vm )
{
	int nSrc = GetScriptInterface()->GetVar( m_key );
	int nVar = 0;
	if ( m_bValIsKey )
	{
		nVar = GetScriptInterface()->GetVar( m_nValue );
	}
	else
	{
		nVar = m_nValue;
	}
	bool bTerm = false;
	switch( m_op )
	{
	case SKW_GREATER_EQUAL:
		bTerm = ( nSrc >= nVar );
		break;
	case SKW_GREATER:
		bTerm = ( nSrc > nVar );
		break;
	case SKW_LESS_EQUAL:
		bTerm = ( nSrc <= nVar );
		break;
	case SKW_LESS:
		bTerm = ( nSrc < nVar );
		break;
	case SKW_EQUAL:
		bTerm = ( nSrc == nVar );
		break;
	case SKW_NOT_EQUAL:
		bTerm = ( nSrc != nVar );
		break;
	}
	if( bTerm )
	{
		vm->NextIP();
	}
	else
	{	
		if( m_nMatchElseAddr >= 0 )
			vm->SetIPAddr( m_nMatchElseAddr );
		else
			vm->SetIPAddr( m_nMatchEndIfAddr );
	}
}

void CScriptCmd_Else::Execute( CScriptVM *vm )
{
	vm->NextIP();
}

void CScriptCmd_EndIf::Execute( CScriptVM* vm )
{
	vm->NextIP();
}

BOOL CScriptCmd_JumpToEndIf::Create( WordParser* words )
{
	return TRUE;
}

void CScriptCmd_JumpToEndIf::Execute( CScriptVM* vm )
{
	vm->SetIPAddr( m_nMatchEndIfAddr );
}

// call 2
BOOL CScriptCmd_Call::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "call create error, param count != 1" );
		return FALSE;
	}
	if( !words->IsNumber( 0 ) )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "call create error, param is not number" );
		return FALSE;
	}
	m_nProcId = atoi( words->GetWord( 0 ) );
	return TRUE;
}
void CScriptCmd_Call::Execute( CScriptVM* vm )
{
	vm->NextIP();
	vm->PushIPAddr();
	if( !vm->JumpToProc( m_nProcId ) )
		vm->Crash();
}

// return
void CScriptCmd_Return::Execute( CScriptVM* vm )
{
	//  if( !vm->PopIPAddr() )
	//      vm->Crash();	
	//  else
	//vm->Return();
	if( !vm->PopIPAddr() )
	{
		vm->Return();
		return;
	}
	//vm->NextIP();

}
// jump 3
BOOL CScriptCmd_Jump::Create( WordParser* words )
{
	if( words->GetWordCount() != 1 )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "jump create error, param count != 1" );
		return FALSE;
	}
	if( !words->IsNumber( 0 ) )
	{
		LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "jump create error, param is not number" );
		return FALSE;
	}
	m_nProcId = atoi( words->GetWord( 0 ) );
	return TRUE;
}
void CScriptCmd_Jump::Execute( CScriptVM* vm )
{
	vm->SetIPAddr( vm->GetProcAddr( m_nProcId ) );
}


