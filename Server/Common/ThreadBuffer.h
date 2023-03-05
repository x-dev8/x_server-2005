/********************************************************************
	Filename: 	ThreadBuffer.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
 *	线程本地buffer
 */

#ifndef __GAMESERVER_THREADBUFFER_H__
#define __GAMESERVER_THREADBUFFER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "Mutex.h"
#include "Memory_pool.h"

const unsigned int MAX_POINTARRAYSIZE = 10000;
const unsigned int MAX_THREAD = 1024;
const unsigned int BUFFER_SIZE = 1024*1024;        //每个线程给的buffer大小

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
    BUFFER* m_dwThreadList[MAX_POINTARRAYSIZE];        //对于线程ID为10000以内的线程，提供用数组下标直接查找Buffer(win下绝大多数线程ID不会超过10000)
    THREADBUFFERINFO m_list[MAX_THREAD];
};

extern CThreadBuffer& GettheThreadBuffer();

#endif //__GAMESERVER_THREADBUFFER_H__