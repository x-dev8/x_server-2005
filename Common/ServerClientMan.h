#pragma once

#include "StaticArray.h"
//#include "GateClient.h"

//����GateClient
//��ʵ��һ�����ж���
class CServerClientMan
{
	//���еļ��뵽�����
	CStaticArray< void * >	m_free;
	int						m_iBlockSize;
public:
	CServerClientMan( int iFreeQueueSize,int iBlockSize );
	~CServerClientMan(void);

	void *AllocClient( void );
	void FreeClient( void *pClient,bool bRealFree = false );
	void Clear(void);
};