#ifndef __MULTIPLAYERSTAGE_H__
#define __MULTIPLAYERSTAGE_H__

/************************************************************************
        // ���˸���
************************************************************************/
#include "EctypeStage.h"

class MultiPlayerStage : public EctypeStage, INHERIT_POOL_PARAM( MultiPlayerStage, 20 )
{
public:
    MultiPlayerStage();
    virtual ~MultiPlayerStage(){};

    // �ͷų���
    virtual void Release();

protected:
    // �Ƿ��ܽ��볡��
    bool CheckCanEnterStage( GamePlayer* pPlayer );

    // ������븱��
    bool ProcessEnterStage( GamePlayer* pPlayer );

    // �Ƿ���ĳ���
    bool HavePlayer( GameObjectId nPlayerID );
};

///////////////////////////////////////////////////////////////////
inline void MultiPlayerStage::Release()
{
    ReleaseStage< MultiPlayerStage >( this );
}

#endif
