#ifndef __CENTERSERVER_GAMESTAGE_H__
#define __CENTERSERVER_GAMESTAGE_H__

#include "MeRTLibsServer.h"
#include "GlobalDef.h"
#include "Memory_Pool.h"

class GameStage : public Common::TObject_pool<GameStage>
{
public:
    static GameStage* CreateInstance() {return CNewWithDebug<GameStage>::Alloc(1, "GameStage::CreateInstance中创建GameStage实例");}
    void Release() { CNewWithDebug<GameStage>::Free(this);}

    GameStage();
    virtual ~GameStage(){}

private:
    SGameStage _sGameStage;
};

#endif // __CENTERSERVER_GAMESTAGE_H__
