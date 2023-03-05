#ifndef __SINGLETEAMSTAGE_H__
#define __SINGLETEAMSTAGE_H__
/************************************************************************
        // 单队伍, 只有一个队伍
************************************************************************/

#include "EctypeStage.h"

class SingleTeamStage : public EctypeStage, INHERIT_POOL_PARAM( SingleTeamStage, 20 )
{
public:
    SingleTeamStage();
    virtual ~SingleTeamStage(){};

    // 释放场景
    virtual void Release();

protected:
    virtual eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // 处理进入副本
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SingleTeamStage::Release()
{
    ReleaseStage< SingleTeamStage >( this );
}

#endif
