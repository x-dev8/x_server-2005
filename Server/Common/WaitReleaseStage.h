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

//只要添加到这里了就没有在返回的余地了
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
    
    bool AddReleaseStage( GameStage* pStage, uint32 dwDelayTime = 30000/*60000*/); // 添加需要删除的地图并设定删除延时（默认延时30秒）
    uint32 GetReleaseStageListSize() const;                               // 获取删除队列长度

    void Run();

protected:
    typedef std::list<SReleaseStageInfo>         ReleaseStageInfoContainer;
    typedef ReleaseStageInfoContainer::iterator ItrReleaseStageInfoContainer;

    ReleaseStageInfoContainer m_stagelist;
};

CWaitReleaseStage& GettheWaitReleaseStage();

#endif //_H_WAITRELEASESTAGE_