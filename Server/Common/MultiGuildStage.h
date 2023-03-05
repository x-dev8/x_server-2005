#ifndef __MULTIGUILDSTAGE_H__
#define __MULTIGUILDSTAGE_H__

/************************************************************************
        // 多帮派副本
************************************************************************/
#include "EctypeStage.h"

class MultiGuildStage : public EctypeStage, INHERIT_POOL_PARAM( MultiGuildStage, 20 )
{
public:
    MultiGuildStage();
    virtual ~MultiGuildStage(){};

    // 释放场景
    virtual void Release();

    // 是否有该玩家的帮派
    bool HaveGuild( uint32 nGuildID );

protected:
    // 判断是否需要T掉玩家
    eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // 进入场景
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // 判断是否能进入场景
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // 更新副本队伍列表
    void UpdateStageGuild();

private:
    typedef std::set< uint32 > GuildList;
    typedef GuildList::iterator GuildListIter;

    // 队伍列表
    GuildList m_setGuild;
};

///////////////////////////////////////////////////////////////////
inline void MultiGuildStage::Release()
{
    ReleaseStage< MultiGuildStage >( this );
}

#endif
