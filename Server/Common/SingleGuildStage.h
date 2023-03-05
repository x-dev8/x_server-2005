#ifndef __SINGLEGUILDSTAGE_H__
#define __SINGLEGUILDSTAGE_H__
/************************************************************************
        // ���ɸ���
************************************************************************/

#include "EctypeStage.h"

class SingleGuildStage : public EctypeStage, INHERIT_POOL_PARAM( SingleGuildStage, 10 )
{
public:
    SingleGuildStage();
    virtual ~SingleGuildStage(){};

    // �ͷų���
    virtual void Release();

protected:
    virtual eEctypeKickType WhyKickOutPlayer( GamePlayer* pPlayer );

    // ������븱��
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SingleGuildStage::Release()
{
    ReleaseStage< SingleGuildStage >( this );
}

#endif
