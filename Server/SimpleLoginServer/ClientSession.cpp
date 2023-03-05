#include "ClientSession.h"
//#include "FuncPerformanceLog.h"
//#include "MessageDefine.h"
#include <string>
#include <assert.h>

CClientSession::CClientSession(void)
{
	m_socketer = NULL;
	memset( m_ip, 0, sizeof(m_ip) );
	memset( m_account, 0, sizeof(m_account) );
	m_in_list_state = enum_in_list_unknow;
	account_id = 0xffffffff;
}

CClientSession::~CClientSession(void)
{
	if (m_socketer)
	{
		Socketer_release(m_socketer);
		m_socketer = NULL;
	}
}

void CClientSession::SendMsg( Msg *pMsg )
{
	assert(pMsg);
	if(!pMsg)
		return;
	if (!m_socketer)
		return;
	//assert(pMsg->GetType() < MSG_MAX);
	m_socketer->SendMsg(pMsg);
}

//设置此客户端账号
void CClientSession::SetAccount( const char *account ,unsigned long accountid)
{
	account_id = accountid;
	if( !account )
	{
		memset( m_account, 0, sizeof(m_account) );
		return;
	}
	strncpy( m_account, account, sizeof(m_account)-1 );
	m_account[sizeof(m_account)-1] = 0;
}

//获取此客户端的ip
const char *CClientSession::GetIP()
{
	if(strlen(m_ip) == 0)
	{
		m_socketer->GetIP(m_ip, sizeof(m_ip));
	}
	return m_ip;
}

//设置其处于正常连接链表
void CClientSession::SetInNormalList()
{
	m_in_list_state = enum_in_list_state_nor_normal;
}

//设置其处于等待关闭的链表中
void CClientSession::SetInWaiteList()
{
	m_in_list_state = enum_in_list_state_waite_close;
}

//记录何时连接上的
void CClientSession::SetConnect (unsigned long current)
{
	m_connecttime = current;
}

void CClientSession::SetCloseTime (unsigned long current)
{
	m_closetime = current;
}

bool CClientSession::CanClose( unsigned long current )
{
	if( current - m_closetime >= 5000)
		return true;
	return false;
}

bool CClientSession::IsOverTime( unsigned long current, unsigned long overtime )
{
	if( current - m_connecttime >= overtime )
		return true;
	return false;
}