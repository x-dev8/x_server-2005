//ս���������Ļ��� Ӧ�þ����ٵ���Ϊ
//һ��ս���������������ͬһ���ͼ��ͬһ���͵Ķ��ս������
//����ս���Ƿ���� ��������һ�����ڵ� ���ǵ�ǰGameServer ��ָ����ͼ ���ǻ״̬
#pragma once
class BaseGameBattleManager
{
public:
	//BaseGameBattleManager();
	//~BaseGameBattleManager();
	virtual void RunUpdate( unsigned int nCurrentTime ) = 0;

	void SetGameBattleType(unsigned int Type){GameBattleType = Type;}
	void SetGameBattleMapID(unsigned int MapID){BattleMapID = MapID;}

	unsigned int GetGameBattleMapID(){return BattleMapID;}
	unsigned int GetGameBattleType(){return GameBattleType;}

	virtual void Init() =0;
	virtual void Destroy()=0;
protected:
	unsigned int GameBattleType;//ս������ ������ʱ�����õ�
	unsigned int BattleMapID;//ս���ĵ�ͼID �����ļ����ȡ������
};
//inline BaseGameBattleManager::BaseGameBattleManager()
//{
//	Init();
//}
//inline BaseGameBattleManager::~BaseGameBattleManager()
//{
//	Destroy();
//}