#ifndef __NORMALSTAGE_H__
#define __NORMALSTAGE_H__
#include "GameStage.h"

class NormalStage : public GameStage, INHERIT_POOL_PARAM( NormalStage, 20 )
{
public:
    NormalStage();
    virtual ~NormalStage();

    virtual void Release();

    virtual void CheckStageValid(){}
    virtual void SetStageWaitRelease( bool bRelease ,bool bNow = false){};
    virtual bool IsStageWaitingRelease() { return false; }
    virtual bool IsStageRelease(){ return false; }
    virtual void CheckKickOutPlayer( BaseCharacter* pChar ){}
    virtual bool CheckCanEnterStage( GamePlayer* pPlayer ) { return true; }

protected:
    virtual bool ProcessEnterStage( GamePlayer* pPlayer ) { return true; }
    virtual void ProcessLeaveStage( GamePlayer* pPlayer ) {}
};


///////////////////////////////////////////////////////////////////////////////
inline void NormalStage::Release()
{
    ReleaseStage< NormalStage >( this );
}


#endif
