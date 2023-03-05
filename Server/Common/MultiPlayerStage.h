#ifndef __MULTIPLAYERSTAGE_H__
#define __MULTIPLAYERSTAGE_H__

/************************************************************************
        // 多人副本
************************************************************************/
#include "EctypeStage.h"

class MultiPlayerStage : public EctypeStage, INHERIT_POOL_PARAM( MultiPlayerStage, 20 )
{
public:
    MultiPlayerStage();
    virtual ~MultiPlayerStage(){};

    // 释放场景
    virtual void Release();

protected:
    // 是否能进入场景
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // 处理进入副本
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // 是否有某玩家
    bool HavePlayer( GameObjectId nPlayerID );
};

///////////////////////////////////////////////////////////////////
inline void MultiPlayerStage::Release()
{
    ReleaseStage< MultiPlayerStage >( this );
}

#endif
