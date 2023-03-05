#ifndef __CAMPGUILDBATTLEMANAGER_H__
#define __CAMPGUILDBATTLEMANAGER_H__

/************************************************************************
            ��������ս����, ����DOTA�淨
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
    // ����ת����׼��״̬�߼�
    virtual void ProcessChangeToPrepareStatus();

    // ����ת��������״̬�߼�
    virtual void ProcessChangeToEnterStatus();

private:

};

#endif