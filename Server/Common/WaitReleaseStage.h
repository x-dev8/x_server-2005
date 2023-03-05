/********************************************************************
    Filename:     WaitReleaseStage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef _H_WAITRELEASESTAGE_
#define _H_WAITRELEASESTAGE_

#include "MeRTLibsServer.h"
#include "BaseCharacter.h"
#include "GameStage.h"
#include "GameArea.h"
#include "Mutex.h"

#define theCWaitReleaseStag GettheWaitReleaseStage()

//ֻҪ��ӵ������˾�û���ڷ��ص������
class CWaitReleaseStage : public CSemiAutoIntLock
{
public:
    struct SReleaseStageInfo
    {
        SReleaseStageInfo()
        {
            pStage      = NULL;
            dwDelayTime = 0;
        }

        GameStage* pStage;
        uint32     dwDelayTime;
    };

public:
    CWaitReleaseStage();
    virtual ~CWaitReleaseStage();
    
    bool AddReleaseStage( GameStage* pStage, uint32 dwDelayTime = 30000/*60000*/); // �����Ҫɾ���ĵ�ͼ���趨ɾ����ʱ��Ĭ����ʱ30�룩
    uint32 GetReleaseStageListSize() const;                               // ��ȡɾ�����г���

    void Run();

protected:
    typedef std::list<SReleaseStageInfo>         ReleaseStageInfoContainer;
    typedef ReleaseStageInfoContainer::iterator ItrReleaseStageInfoContainer;

    ReleaseStageInfoContainer m_stagelist;
};

CWaitReleaseStage& GettheWaitReleaseStage();

#endif //_H_WAITRELEASESTAGE_