/********************************************************************
	Filename: 	ThreadBuffer.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
 *	�̱߳���buffer
 */

#ifndef __GAMESERVER_THREADBUFFER_H__
#define __GAMESERVER_THREADBUFFER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Mutex.h"
#include "Memory_pool.h"

const unsigned int MAX_POINTARRAYSIZE = 10000;
const unsigned int MAX_THREAD = 1024;
const unsigned int BUFFER_SIZE = 1024*1024;        //ÿ���̸߳���buffer��С

class CThreadBuffer : public CSemiAutoIntLock
{
    typedef struct tagBuffer// : public Common::TObject_pool<tagBuffer, 20>
    {
        char szBuffer[BUFFER_SIZE];
    }BUFFER;

    typedef struct tagThreadBufferInfo
    {
        DWORD dwThreadID;
        BUFFER* pBuffer;
    }THREADBUFFERINFO;

public:
    CThreadBuffer();
    virtual ~CThreadBuffer();

public:
    char* GetBuffer();
    void ReleaseBuffer(DWORD dwThreadID);

protected:
    BUFFER* m_dwThreadList[MAX_POINTARRAYSIZE];        //�����߳�IDΪ10000���ڵ��̣߳��ṩ�������±�ֱ�Ӳ���Buffer(win�¾�������߳�ID���ᳬ��10000)
    THREADBUFFERINFO m_list[MAX_THREAD];
};

extern CThreadBuffer& GettheThreadBuffer();

#endif //__GAMESERVER_THREADBUFFER_H__