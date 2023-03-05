/********************************************************************
    Filename:     DatabaseInterface.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "Mutex.h"
#include "MessageDefine.h"
#include "Memory_Pool.h"
#include "SqlMessages.h"

class DatabaseServerWorkThread;

class DatabaseInterface
{
public:
    enum EConstDefine
    {
        CD_BufferSizeResult    = 1024 * 100,
        CD_BufferSizeQuery     = 1024 * 75,
        ECD_NormalWorkThread   = 1,
        ECD_OrganizeWorkThread = 2,
    };

    //class Query
    //{
    //public:
    //    int   nClientId;
    //    BYTE* m_pBuffer;

    //    Query(): nClientId(-1), m_pBuffer(NULL)
    //    {}

    //    virtual ~Query()
    //    {
    //        ReleaseBuffer();
    //    }

    //    void ReleaseBuffer()
    //    {
    //        if (m_pBuffer != NULL)
    //        {
    //            delete [] m_pBuffer;
    //            m_pBuffer = NULL;
    //        }
    //    }

    //    bool AllocBuffer(unsigned int nSize)
    //    {
    //        ReleaseBuffer();
    //        m_pBuffer = new unsigned char[nSize];
    //        if ( !m_pBuffer )
    //        { return false; }
    //        return true;
    //    }
    //};

#pragma pack ( push, 1 )
    struct Result : INHERIT_POOL(Result)
    {
        uint32 dwType;
        uint32 dwFlag;
        int16  nClientId;
        uint8  byBuffer[CD_BufferSizeResult];

        Result(): dwType(0), dwFlag(0), nClientId(-1){}
    };
#pragma pack ( pop )

public:
    DatabaseInterface();
    ~DatabaseInterface();

    BOOL Init();
    void ShutDown();
    
    BOOL LockQuery();
    BOOL UnlockQuery();

    BOOL LockResult();
    BOOL UnlockResult();

    void Update(); // 更新

    BOOL PushMessage        ( Msg* pMsg, int32 nClientId  );
    BOOL PushSqlMessageQuery( BaseSqlMessage* pSqlMessage );

    void PushResult( Result* pResult );
    void PushResult( int nClientId, Msg* pMsg );
    
    void CheckExitCondition(); // 检查程序是否可以退出的条件

protected:
    CIntLock m_csQuery;  // sqlMessage Query  队列锁
    CIntLock m_csResult; // sqlMessage Result 队列锁

    typedef std::vector<BaseSqlMessage*> QueryContainer;
    QueryContainer _querys;

    typedef std::vector<Result*> ResultContainer;
    ResultContainer m_vectorResult;

    DatabaseServerWorkThread* _pNormalWorkThread;   // 平时普通的工作线程
    DatabaseServerWorkThread* _pOrganizeWorkThread; // 组织公会的工作线程
};

DatabaseInterface* GetDatabaseInterface();
