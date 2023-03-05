#ifndef __SINGLEPLAYERSTAGE_H__
#define __SINGLEPLAYERSTAGE_H__

/************************************************************************
        // 单人副本, 只有一个玩家
************************************************************************/
#include "EctypeStage.h"

class SinglePlayerStage : public EctypeStage, INHERIT_POOL_PARAM( SinglePlayerStage, 20 )
{
public:
    SinglePlayerStage();
    virtual ~SinglePlayerStage(){};

    // 释放场景
    virtual void Release();

protected:
    // 处理进入副本
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SinglePlayerStage::Release()
{
    ReleaseStage< SinglePlayerStage >( this );
}

#endif
