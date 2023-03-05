#ifndef __LEVELLIMITCENTERMANAGER_H__
#define __LEVELLIMITCENTERMANAGER_H__

#include "LevelLimitDefine.h"
#include "LevelLimitConfig.h"
#include "LevelLimitMessage.h"
#include "GameTimer.h"

class CLevelLimitCenterManager
{
public:
	CLevelLimitCenterManager();
	~CLevelLimitCenterManager();

	static CLevelLimitCenterManager& Instance()
	{
		static CLevelLimitCenterManager cllcm;
		return cllcm;
	}

	void ProceeMySqlData(MsgAckMySQLData* pData);
	bool InitLevelLimit(SLevelLimitInfo* pLLInfo,int last_done_level = 0);

	void ProcessActiveLimit();                                //������ķ�ӡ
	void AddPlayer(int add_count);                            //���ӵ���ȼ�����
	void ActiveLimit(const char* player_name);                //���󼤻��ӡ
	bool IsInit(){return isInit;}
	void RunUpdate(unsigned int nCurrentTime);
	void UpdateToMySql();
	void SendLevelLimitInfoToAllGame();
	// ��������������ⶨʱ��
	void StartSaveTimer( unsigned int nCurrentTime );
	void UpdatePlayerCount2GS();
	Msg2AllGameInfo* GetLimitInfoToGame(Msg2AllGameInfo& allgame);
private:
	short           limit_state;   //��ӡ״̬
	short			player_count;  //����ȼ�Ҫ���player����
	short			trigger_lv;    //������ӡ�ĵȼ�
	short           trigger_count; //������ӡ��player����
	short           per_count;     //ÿ���Ӷ��ٸ�player,״̬�ı�:����ʱ��	
	unsigned long   active_time;   //����ʱ��
	unsigned long   done_time;     //���ʱ��
	unsigned long   time_max;      //������ʱ��
	unsigned long   time_min;      //��С����ʱ��
	char            active_name[eLimitGlobal_name];   //�����ӡ�Ľ�ɫ����
	bool            isInit;        //�Ƿ��ʼ��
	GameTimerEx     m_saveLevelLimitTime;       // �����ӡTimer
};

#define  theLevelLimitCenterManager CLevelLimitCenterManager::Instance()

#endif