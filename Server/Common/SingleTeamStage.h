#ifndef __SINGLETEAMSTAGE_H__
#define __SINGLETEAMSTAGE_H__
/************************************************************************
        // ������, ֻ��һ������
************************************************************************/

#include "EctypeStage.h"

class SingleTeamStage : public EctypeStage, INHERIT_POOL_PARAM( SingleTeamStage, 20 )
{
public:
    SingleTeamStage();
    virtual ~SingleTeamStage(){};

    // �ͷų���
    virtual void Release();

protected:
    virtual eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // ������븱��
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SingleTeamStage::Release()
{
    ReleaseStage< SingleTeamStage >( this );
}

#endif
