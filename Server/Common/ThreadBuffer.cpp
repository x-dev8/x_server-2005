
#include "ThreadBuffer.h"

CThreadBuffer& GettheThreadBuffer()
{
    static CThreadBuffer s_tb;
    return s_tb;
}

CThreadBuffer::CThreadBuffer()
{
}

CThreadBuffer::~CThreadBuffer()
{
}

char* CThreadBuffer::GetBuffer()
{
    DWORD dwID = ::GetCurrentThreadId();
    if (dwID < MAX_POINTARRAYSIZE)
    {
        if (m_dwThreadList[dwID] == NULL)
        {
            m_dwThreadList[dwID] = CNewWithDebug<BUFFER>::Alloc(1, "CThreadBuffer::GetBuffer中创建m_dwThreadList[dwID]");
        }
        return m_dwThreadList[dwID]->szBuffer;
    }
    else
    {
        CSALocker locker(this);
        int nEmptyPos = -1;
        for (int i=0; i<MAX_THREAD; i++)
        {
            if (m_list[i].dwThreadID == dwID)
            {
                if (m_list[i].pBuffer == NULL)
                {
                    m_list[i].pBuffer = CNewWithDebug<BUFFER>::Alloc(1, "CThreadBuffer::GetBuffer中创建m_list[i].pBuffer");
                }
                return m_list[i].pBuffer->szBuffer;
            }
            if (m_list[i].dwThreadID == 0 && nEmptyPos == -1)
            {
                nEmptyPos = i;
            }
        }

        //已满 无法再申请新的内存块
        if (nEmptyPos == -1)
        {
            return NULL;
        }

        m_list[nEmptyPos].dwThreadID = dwID;
        m_list[nEmptyPos].pBuffer = CNewWithDebug<BUFFER>::Alloc(1, "CThreadBuffer::GetBuffer中创建m_list[nEmptyPos].pBuffer");
        return m_list[nEmptyPos].pBuffer->szBuffer;
    }
}

void CThreadBuffer::ReleaseBuffer(DWORD dwThreadID)
{
    //DWORD dwID = ::GetCurrentThreadId();
    DWORD dwID = dwThreadID;
    if (dwID < MAX_POINTARRAYSIZE)
    {
        //就不事先判断是否为空了
        CNewWithDebug<BUFFER>::Free(m_dwThreadList[dwID]);
        m_dwThreadList[dwID] = NULL;
    }
    else
    {
        for (int i=0; i<MAX_THREAD; i++)
        {
            if (m_list[i].dwThreadID == dwID)
            {
                CNewWithDebug<BUFFER>::Free(m_list[i].pBuffer);
                m_list[i].dwThreadID = 0;
                m_list[i].pBuffer = NULL;
                return;
            }
        }
    }
}
