#include "ScriptVM.h"
#include "ScriptAbstract.h"

extern IScriptInterface* GetScriptInterface();
CScriptVMStack::CScriptVMStack() : m_nStackSize(0)
{}

void CScriptVMStack::Clear()
{
	m_nStackSize = 0;
}
BOOL CScriptVMStack::Push( int n )
{
	if( m_nStackSize < eMaxStackSize )
	{
		m_nStack[m_nStackSize++] = n;
		return TRUE;
	}
	return FALSE;
}
BOOL CScriptVMStack::Pop()
{
	if( m_nStackSize == 0 )
		return FALSE;
	m_nStackSize--;
	return TRUE;
}
int	CScriptVMStack::Top()
{
	if( IsEmpty() )
		return 0;
	return m_nStack[m_nStackSize-1];
}
BOOL CScriptVMStack::Clone( CScriptVMStack* pStack )
{
	if( !pStack )
	{
		return FALSE;
	}
	m_nStackSize = pStack->m_nStackSize;
	for( int i = 0; i < m_nStackSize; i++ )
		m_nStack[i] = pStack->m_nStack[i];
	return TRUE;
}
CScriptVM::CScriptVM():
m_dwIPAddr(0),
m_state(0)
{
    m_dwIPAddr = 0;
    for( int i = 0; i < MAX_PROC; i++ )
        m_anProcAddr[i] = -1;

	// Luo_157 added 2004.10.16
//	m_stNpcId = -1;
}

CScriptVM::~CScriptVM()
{
	Destroy();
}

void CScriptVM::Reset()
{ 
	m_dwIPAddr = 0; 
	m_state = ERunState_CONTINUE; 
	m_IPStack.Clear();
}

void CScriptVM::Destroy()
{
	for( int i = 0; i < (int)m_vectorCmd.size(); i++ )
	{
		if( m_vectorCmd[i] )
		{
			m_vectorCmd[i]->Release();
		}
	}
	m_vectorCmd.clear();
}

BOOL CScriptVM::PopIPAddr()
{ 
	if( m_IPStack.IsEmpty() )
		return FALSE;
	m_dwIPAddr = m_IPStack.Top();
	m_IPStack.Pop();
	return TRUE;
}

BOOL CScriptVM::JumpToProc( int nProcId )
{
	if( nProcId < 0 || nProcId >= MAX_PROC )
		return FALSE;
	if( m_anProcAddr[nProcId] == -1 )
		return FALSE;
	m_dwIPAddr = m_anProcAddr[nProcId];
	return TRUE;
}
void CScriptVM::SaveThread( CScriptVMThread* thread )
{ 
	thread->Reset();
	thread->Set( m_dwIPAddr, ERunState_HANGUP );
	thread->GetIPStack()->Clone( &m_IPStack );
}

BOOL CScriptVM::LoadThread( CScriptVMThread* thread )
{ 
	if( !thread )
		return FALSE;
	if( thread->GetIPAddr() >= m_vectorCmd.size() )
		return FALSE;
	m_dwIPAddr = thread->GetIPAddr(); 

	m_state = ERunState_CONTINUE;


	m_IPStack.Clone( thread->GetIPStack() );

	// 设置当前触发script的char id

	//GetScriptEngine()->SetCurCharID( thread->GetCharId() );
	//GetScriptEngine()->SetCurCharID( m_stNpcId );
	GetScriptInterface()->SetCurCharId( thread->GetCharId() );
	GetScriptInterface()->SetDstId( thread->GetDstId() );

	return TRUE;
}
int	CScriptVM::GetProcAddr( int nProcId )
{
	if( nProcId < 0 || nProcId >= MAX_PROC )
		return -1;
	return m_anProcAddr[nProcId];
}

BOOL CScriptVM::Execute( CScriptVMThread* thread )
{
	if( m_vectorCmd.size() == 0 )
		return FALSE;
	if( !thread )
	{
		m_dwIPAddr = 0;
		m_state = ERunState_CONTINUE;

		GetScriptInterface()->SetCurCharId( -1 );
		GetScriptInterface()->SetDstId( -1 );
	}
	else if( !LoadThread( thread ) )
		return FALSE;
	
	BOOL bQuit = FALSE;
	
    const uint16 nLimitCount = 5000;   // 最大的执行次数
    uint16 nCurrentCount = 0;          // 脚本执行次数
    static bool bHaveShowOnce = false; // 是否已经打出错误log
	while( !bQuit )
	{
        ++nCurrentCount;
        if ( nCurrentCount >= nLimitCount )
        { 
            if ( !bHaveShowOnce )
            { 
                // 脚本死循环的严重错误
                if ( thread )
                { LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_CRITICAL, "Script dead loop[%d:%d]", thread->GetScriptType(), thread->GetDstId() ); }

                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "Script dead loop" );
                bHaveShowOnce = true; 
            }
            return FALSE;
        }

		if( m_dwIPAddr < 0 || m_dwIPAddr >= (int)m_vectorCmd.size() )
		{
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script address pointer[%d] is slop over", m_dwIPAddr );
			m_dwIPAddr = 0;
			return FALSE;
		}
				
		CScriptCommand* pCmd = m_vectorCmd[m_dwIPAddr];
		if( pCmd == NULL )
		{
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "Script address pointer is null", m_dwIPAddr );
			m_dwIPAddr = 0;
			return FALSE;
		}

		GetScriptInterface()->HighLightSourceLine( pCmd->GetSourceLine() );
		
		pCmd->Execute( this );

		switch( m_state )
		{ 
		case ERunState_RETURN:
			// vm执行完毕
			if( thread )
			{
				thread->Set( 0, ERunState_RETURN );
			}
			bQuit = TRUE;
			break;
		case ERunState_CONTINUE:
			break;
		case ERunState_HANGUP:
			if( thread )
			{
				thread->Set( m_dwIPAddr, ERunState_HANGUP );
				thread->GetIPStack()->Clone( &m_IPStack );
			}
			bQuit = TRUE;
			break;
		case ERunState_CRASH:
			//GetScriptInterface()->HighLightSourceLine( 0 );
			return FALSE;
			break;
		}
	}

	return TRUE;
}

BOOL CScriptVMThread::SetEntrance( int nProcId )
{
    if( !m_pVM )
        return FALSE;
    int nIPAddr = m_pVM->GetProcAddr( nProcId );
    if( nIPAddr == -1 )
        return FALSE;
    m_dwIPAddr = nIPAddr;
    return TRUE;
}

BOOL CScriptVMThread::Restore()
{
	if( !m_pVM )
		return FALSE;
	return m_pVM->Execute( this );
}

void CScriptVMThread::CreateId()
{
	static DWORD dwLastId = 0;
	_threadId = dwLastId++;
}
