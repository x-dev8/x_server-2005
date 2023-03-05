//用于公会之间的战场 特殊战场 一月4轮 进阶赛
//只有第一轮可以报名 其他不可以报名 
#pragma once
#include "CampBattleManager.h"
class CampGuildUnionBattleManager : public CampBattleManager
{
public:
    CampGuildUnionBattleManager();
    virtual ~CampGuildUnionBattleManager(){};
    virtual bool SignUpCampBattle( GamePlayer* pPlayer );
	virtual bool ShowCampBattleEnter( GamePlayer* pPlayer );
	virtual bool EnterCampBattle( GamePlayer* pPlayer );
protected:
    virtual void ProcessChangeToPrepareStatus();
    virtual void ProcessChangeToEnterStatus();
	virtual void ProcessChangeToSignUpStatus();
	virtual void ProcessChangeToEndStatus();
	virtual void ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
};