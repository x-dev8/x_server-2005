#pragma once

#include "MeRTLibs.h"
#include "MessageDefine.h"

class CClientMsgQueue
{
	struct SMsgBuf
	{
		char szBuf[ MSGMAXSIZE ];
	};
	typedef std::list< SMsgBuf > msgqueuelist;
	msgqueuelist m_list;
public:
	CClientMsgQueue(void);
	~CClientMsgQueue(void);
	int GetSize(){ return (int)m_list.size(); }
	bool PopMsg( Msg *pMsg,short stBufSize )
	{
		msgqueuelist::iterator it;
		
		if( m_list.size() <= 0 )
			return false;
		it = m_list.begin();
		memcpy( pMsg,it->szBuf,MSGMAXSIZE );
		m_list.pop_front();
		return true;
	}
	bool PushMsg( Msg* pMsg )
	{
		SMsgBuf buf;
		memcpy( buf.szBuf,(char*)pMsg,pMsg->header.stLength );
		m_list.push_back( buf );
		return true;
	}
	bool PeekMsg( Msg *pMsg,short stBufSize )
	{
		msgqueuelist::iterator it;

		if( m_list.size() <= 0 )
			return false;
		it = m_list.begin();
		memcpy( pMsg,it->szBuf,MSGMAXSIZE );		
		return true;
	}
};



class CClientMsgQueueProxy
{
	CClientMsgQueue *m_pQueue;
	char *m_szBuf;
	short m_stBufSize;
public:	

	CClientMsgQueueProxy( void )
	{
		m_pQueue = 0;
		m_szBuf = 0;
		m_stBufSize = 0;
	}

	int GetSize(void)
	{
		if( !m_pQueue )
			return 0;
		return m_pQueue->GetSize();
	}

	void Init( CClientMsgQueue *pQueue,char *szBuf,short stBufSize)
	{
		m_pQueue = pQueue;
		m_szBuf = szBuf;
		m_stBufSize = stBufSize;
	}	

	void * GetBuffer( short stSize )
	{
		if( stSize <= m_stBufSize )
			return m_szBuf;
		return 0;
	}

	bool PopMsg( char *szBuf )
	{
		if( !m_pQueue )
			return false;

		//不能使用内部变量
		//char szBuf[ MSGMAXSIZE ];
		if( !m_pQueue->PopMsg( (Msg*)szBuf,MSGMAXSIZE) )
			return false;
		return true;;
	}

	bool PushMsg(Msg *pMsg)
	{
		if( !m_pQueue )
			return false;
		return m_pQueue->PushMsg( pMsg );
	}
};
