#pragma once
#include "WorldBattleConfig.h"
//����ս�� Ұ��ս�� 
//1.ʱ����� ����ȷ�ϸ���ʱ���ս����PK״̬
//2.��ͬ�׶ε�ˢ�� ɾ�ֵȲ���
//3.�Կͻ��˶�ͨ�� ������
class WorldBattleManager
{
public:
	enum WorldBattleStates
	{
		WBS_StatusInit = 0,		//ս����ʼ��״̬
		WBS_StatusPrepare,		//ս��׼���׶�
		WBS_StatusFight,		//ս����ʼ�׶�
		WBS_StatusEnd			//ս�������׶�
	};
	WorldBattleManager():m_Init(false),m_States(WBS_StatusInit){}
	~WorldBattleManager(){}
	void Init();//��ʼ��
	void Update(unsigned int nCurrentTime);//����
	bool LoadFilePath(const char* FilePaht);
	static WorldBattleManager& Instance()
    {
        static WorldBattleManager s_xManager;
        return s_xManager;
    }
	void SetWorldBattleIsResult();
private:
	void ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	void ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	void ProcessBattleEndStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
private:
	bool				m_Init;//�Ƿ��ʼ�����
	unsigned char		m_States;
	int					m_MapPkType;
	WorldBattleConfig	m_config;
};
#define theWorldBattleManager WorldBattleManager::Instance()