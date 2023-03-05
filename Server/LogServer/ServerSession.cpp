#include "ServerSession.h"

CServerSession::CServerSession(void)
{
	m_IConnecter = NULL;
	m_in_list_state = enum_in_list_unknow;
	server_id = -1;
}

CServerSession::~CServerSession(void)
{
	if (m_IConnecter)
	{
		Socketer_release(m_IConnecter);
		m_IConnecter = NULL;
	}
}

bool CServerSession::SendMsg( Msg *pMsg )
{
	if (!pMsg)
		return false;
	if (!GetIConnecter())
		return false;
	return GetIConnecter()->SendMsg(pMsg);
}

void CServerSession::Reset()
{
	if (m_IConnecter)
	{
		Socketer_release(m_IConnecter);
		m_IConnecter = NULL;
	}
	m_IConnecter = NULL;
	m_in_list_state = enum_in_list_unknow;
}

//�����䴦��������������
void CServerSession::SetInNormalList()
{
	m_in_list_state = enum_in_list_state_nor_normal;
}

//�����䴦�ڵȴ��رյ�������
void CServerSession::SetInWaiteList()
{
	m_in_list_state = enum_in_list_state_waite_close;
}

//��¼��ʱ�����ϵ�
void CServerSession::SetConnect (unsigned long current)
{
	m_connecttime = current;
}

void CServerSession::SetCloseTime (unsigned long current)
{
	m_closetime = current;
}

bool CServerSession::CanClose( unsigned long current )
{
	if( current - m_closetime >= 5000)
		return true;
	return false;
}

bool CServerSession::IsOverTime( unsigned long current, unsigned long overtime )
{
	if( current - m_connecttime >= overtime )
		return true;
	return false;
}