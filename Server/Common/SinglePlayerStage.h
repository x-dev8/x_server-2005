#ifndef __SINGLEPLAYERSTAGE_H__
#define __SINGLEPLAYERSTAGE_H__

/************************************************************************
        // ���˸���, ֻ��һ�����
************************************************************************/
#include "EctypeStage.h"

class SinglePlayerStage : public EctypeStage, INHERIT_POOL_PARAM( SinglePlayerStage, 20 )
{
public:
    SinglePlayerStage();
    virtual ~SinglePlayerStage(){};

    // �ͷų���
    virtual void Release();

protected:
    // ������븱��
    bool ProcessEnterStage( GamePlayer* pPlayer );
};

///////////////////////////////////////////////////////////////////
inline void SinglePlayerStage::Release()
{
    ReleaseStage< SinglePlayerStage >( this );
}

#endif
