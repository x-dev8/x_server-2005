/********************************************************************
    Filename:    WaitReleaseConnect.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
Abstract:
    将连接暂存，内存块不会立即被释放（为配合服务器多线程逻辑处理，防止不同线程间连接访问删除冲突）
    Luo_157@hotmail.com
*/

#ifndef _H_WAITRELEASECONNECT_
#define _H_WAITRELEASECONNECT_

#include "MeRTLibsServer.h"
#include "mutex.h"
//#include "MeNetwork.h"
#include "network.h"

using namespace network;

class CWaitReleaseConnect : public CSemiAutoIntLock
{
    struct RELEASECONNECTINFO
    {
        /*IMeConnector*/Socketer* pConnetor;
        DWORD dwDelayTime;
    };

public:
    CWaitReleaseConnect();
    virtual ~CWaitReleaseConnect();

    //添加需要删除的连接并设定删除延时（默认延时30秒）
    bool AddReleaseConnect(/*IMeConnector*/Socketer* pCon, DWORD dwDelayTime = 30000);

    //获取删除队列长度
    unsigned int GetReleaseConnectListSize() const;

    void Run();

    void UnInit();

protected:
    std::list<RELEASECONNECTINFO> m_conlist;
};

extern CWaitReleaseConnect& GettheWaitReleaseConnect();

#define thetheWaitReleaseConnect GettheWaitReleaseConnect()

#endif //_H_WAITRELEASECONNECT_