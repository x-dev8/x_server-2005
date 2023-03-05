#ifndef __MULTITEAMSTAGE_H__
#define __MULTITEAMSTAGE_H__

/************************************************************************
        // 多队伍副本
************************************************************************/
#include "EctypeStage.h"

class MultiTeamStage : public EctypeStage, INHERIT_POOL_PARAM( MultiTeamStage, 20 )
{
public:
    MultiTeamStage();
    virtual ~MultiTeamStage(){};

    // 释放场景
    virtual void Release();

    // 是否有该玩家的队伍
    bool HaveTeam( uint32 nTeamID );

protected:
    // 判断是否需要T掉玩家
    eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // 进入场景
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // 判断是否能进入场景
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // 更新副本队伍列表
    void UpdateStageTeam();

private:
    typedef std::set< uint32 > TeamList;
    typedef TeamList::iterator TeamListIter;

    // 队伍列表
    TeamList m_setTeam;
};

///////////////////////////////////////////////////////////////////
inline void MultiTeamStage::Release()
{
    ReleaseStage< MultiTeamStage >( this );
}

#endif
