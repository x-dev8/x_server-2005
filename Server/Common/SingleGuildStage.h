#ifndef __SINGLEGUILDSTAGE_H__
#define __SINGLEGUILDSTAGE_H__
/************************************************************************
        // 帮派副本
************************************************************************/

#include "EctypeStage.h"

class SingleGuildStage : public EctypeStage, INHERIT_POOL_PARAM( SingleGuildStage, 10 )
{
public:
    SingleGuildStage();
    virtual ~SingleGuildStage(){};

    // 释放场景
    virtual void Release();

protected:
    virtual eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // 处理进入副本
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SingleGuildStage::Release()
{
    ReleaseStage< SingleGuildStage >( this );
}

#endif
