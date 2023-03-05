#pragma once

#include "StaticArray.h"
//#include "GateClient.h"

//管理GateClient
//其实是一个空闲队列
class CServerClientMan
{
	//空闲的加入到这个中
	CStaticArray< void * >	m_free;
	int						m_iBlockSize;
public:
	CServerClientMan( int iFreeQueueSize,int iBlockSize );
	~CServerClientMan(void);

	void *AllocClient( void );
	void FreeClient( void *pClient,bool bRealFree = false );
	void Clear(void);
};