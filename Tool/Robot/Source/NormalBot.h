#pragma once

#define PER_SPACE_TIME 60 * 1000
#include "AttackBot.h"


class CNormalBot : public CAttackBot
{
public:
	CNormalBot(void);
	virtual ~CNormalBot(void);

	virtual void PlayGame();

	virtual void InitPlayGame(UINT mapid = 0);

	virtual bool LoginOutGame();
	virtual bool RandFlyToMap();
	virtual void RunTeam();

	void SetFlySpaceTime(int nSpaceTime) { m_nFlySpaceTime = nSpaceTime * 1000;}

private:
	void RandLoginOutSpaceTime();

private:	
	DWORD m_dwLoginOutSpace;		//�����˵ǳ���Ϸ�ļ��ʱ��
	DWORD m_dwNextRunTimeSpace;			

	DWORD m_dwStartPlayTime;

	int m_nFlySpaceTime;	//����ʱ����
	DWORD m_dwLastFlyTime;  //�ϴη���ʱ��

};
