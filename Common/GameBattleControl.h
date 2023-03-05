//�µ�ս��������  ������ǰ��ս��
//����Ȩ ���� �������Ĵ��� ���� Update �� ��ȡ������ ���ݲ���  ���漰���������ľ������
//ע���
//1.һ�����͵�ս�������� ����һ����ͼ�Ķ��ս�� һ�����;�һ�������� �������ж�������� 
//2.�� �Թ������ֵ�3��ս�� κ���� ��Ҫ����3��ս������ �ֱ����κ���� ÿ������������һ���ͼ ��ͼID������ͬ
#pragma once
#include <vector>
#include "Singleton.h"
#include "BaseGameBattleManager.h"
#include "GameTimer.h"
class GameBattleControl:public ISingletion<GameBattleControl>
{
public:
	GameBattleControl();
	~GameBattleControl();
	void RunUpdate( unsigned int nCurrentTime );//Update���� ���¹��������е�ս��������
	//��ȡս�������� ս�������ǿ���֪���� ��ͼ��δ֪��  GamePlayer
	BaseGameBattleManager* GetGameBattleManager(unsigned int GameBattleType);
	bool DestroyGameBattleManagerByType(unsigned int GameBattleType);

	//�������͵Ĺ������Ĵ�������
	bool RegisterGuildGeneralBattleManger();//����µĹ���Լս��ս��������

	unsigned int GetMapIDByType(unsigned int Type);
	int GetMapMaxTimeByType(unsigned int Type);
	int GetMapDiffTimeByType(unsigned int Type);
private:
	void Init();//��ʼ������
	void Destroy();
protected:
	GameTimerEx m_xUpdateTimer;//��ʱ������
	std::vector<BaseGameBattleManager*> GameBattleVec;//ȫ���Ĺ������ļ���
	std::map<unsigned int,unsigned int> MapTypeList;
	std::map<unsigned int,int> MapTypeMaxTime;
	std::map<unsigned int,int> MapTypeDiffTime;
};
#define theGameBattleControl GameBattleControl::Instance()