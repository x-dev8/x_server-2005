//���ڹ���֮���ս�� ����ս�� һ��4�� ������
//ֻ�е�һ�ֿ��Ա��� ���������Ա��� 
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