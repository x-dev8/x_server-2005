#ifndef __CAMPGUILDBATTLEMANAGER_H__
#define __CAMPGUILDBATTLEMANAGER_H__

/************************************************************************
            帮派争夺战管理, 类似DOTA玩法
            FileName    CampGuildBattleManager.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "CampBattleManager.h"

class CampGuildBattleManager : public CampBattleManager
{
public:
    CampGuildBattleManager();
    virtual ~CampGuildBattleManager(){};

    virtual bool SignUpCampBattle( GamePlayer* pPlayer );

    virtual bool ShowCampBattleEnter( GamePlayer* pPlayer );

    virtual bool EnterCampBattle( GamePlayer* pPlayer );

protected:
    // 处理转换到准备状态逻辑
    virtual void ProcessChangeToPrepareStatus();

    // 处理转换到进入状态逻辑
    virtual void ProcessChangeToEnterStatus();

private:

};

#endif