/********************************************************************
    Filename:    WaitReleaseConnect.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

/*
Abstract:
    �������ݴ棬�ڴ�鲻���������ͷţ�Ϊ��Ϸ��������߳��߼�������ֹ��ͬ�̼߳����ӷ���ɾ����ͻ��
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

    //�����Ҫɾ�������Ӳ��趨ɾ����ʱ��Ĭ����ʱ30�룩
    bool AddReleaseConnect(/*IMeConnector*/Socketer* pCon, DWORD dwDelayTime = 30000);

    //��ȡɾ�����г���
    unsigned int GetReleaseConnectListSize() const;

    void Run();

    void UnInit();

protected:
    std::list<RELEASECONNECTINFO> m_conlist;
};

extern CWaitReleaseConnect& GettheWaitReleaseConnect();

#define thetheWaitReleaseConnect GettheWaitReleaseConnect()

#endif //_H_WAITRELEASECONNECT_