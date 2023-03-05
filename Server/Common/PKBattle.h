/********************************************************************
Filename: 	PKBattle.h
MaintenanceMan Mail: lufeipeng@163.com
brief: ��Ӫս������
*********************************************************************/
#ifndef _PK_BATTLE_H_
#define _PK_BATTLE_H_

#include "MeRTLibsServer.h"
#include "GlobalDef.h"
#include "Singleton.h"
#include "GameStage.h"
#include "aTime.h"
#include "Memory_Pool.h"

class GamePlayer;

//��һ����Ӫ����,������������
class PKCopyScene: INHERIT_POOL(PKCopyScene)
{
public:
		enum
		{
			PKScript_CheckPackFull = 1,		//��������
			PKScript_AddPresent	   = 2,		//���ӽ���
			PKBattle_FAILBUFF	   = 2533,  //ս��ʧ��buff
			PKBattle_DeadBuff	   = 3653,	//ս������buff
            PKBattle_GOTOBUFF      = 3353,  //��ȴbuff
		};
		enum
		{
			enumCopySceneState_Stop		 = 0,		 //����״̬
			enumCopySceneState_Running   = 1,		//����PK״̬
			enumCopySceneState_WaitThrow = 2,		//�ȴ�����
		};
public:
		DECLARE_POOL_FUNC( PKCopyScene )
		PKCopyScene():pStage(NULL), freshScoreTimer(10 * 1000L), addScoreTimer(5 * 1000L),waitThrowTimer(60 * 1000L), 
			state(enumCopySceneState_Stop), redScore(0), blueScore(0), start_pktime(0)
		{
			redUsers.clear();
			blueUsers.clear();
			userKillList.clear();
			dotaKillList.clear();
			resourceOccuptList.clear();
		}
		~PKCopyScene()
		{
			
		}   
		//������Ӫ����
		static GameStage* CreateStage();
		//��ʼ��ս�����
		void InitScene();
		//��ҽ���ս����ʼ����Ϣ,�Ƿ��һ�ν���
		bool InitUser(GamePlayer *player, BYTE which, bool firstEnter = true);
		//��ս��ɾ�����
		void DestroyBattleUser(GamePlayer *player);
		//ˢ��ս������Դ��
		void FreshBattleResouce();
		//ѭ��
		void Loop();
		//ˢ����Ӫ�������ָ��������
		void SendPKBattleScoreToAllUser();
		//������Ϣ��ս�����
		void SendPKBattleScoreToUser(GamePlayer *player);
		void SendPKBattleScoreToUser(DWORD characterID);
		//������Ӫ������ǰ״̬
		void SendPKBattleState(GamePlayer *user);
		//�����ҵ���Ӫ
		enumBattleInfluence GetUserInfluence(DWORD characterID);
		//��Դ���Ӧ��npc
		BaseCharacter* GetNpcByResourcePos(enumBattleResouce pos);
		//�����Դ���ռ����
		enumBattleInfluence GetResourcePosOwner(enumBattleResouce pos);
		//������Դ���ռ����
		bool SetResourcePosOwner(GamePlayer *player, enumBattleResouce pos);
		//����ս��״̬
		void SetState(BYTE state)
		{
			this->state = state;
		}
		BYTE GetState()
		{
			return this->state;
		}
		//����Stage
		void SetStage(GameStage *stage)
		{
			pStage = stage;
		}
		GameStage* GetStage()
		{
			return pStage;
		}
		void SetPKBattleResult(uint8 winner)
		{
			result = winner;
		}
		//���ս�����
		uint8 GetPKBattleResult()
		{
			return result;
		}
		//���û�ø�����ʼʱ��
		void SetStartPKTime(DWORD startTime)
		{
			start_pktime = startTime;
		}
		DWORD GetStartPKTime()
		{
			return start_pktime;
		}
		//�жϸ����Ƿ����
		void CheckBattleOver();
		//ʱ�䵽���жϽ���
		void BattleTimeOver();
		//�����������Գ��������
		void ThrowCopyUser();
		//����������
		void EndBattle(enumBattleInfluence winner);
		//֪ͨɱ��
		void NotifyKillUser(GamePlayer *killer, GamePlayer *beKiller);
		//���ýű�
		void DoPKScript(GamePlayer *user, DWORD which);
		//����ս������
		void AddPKBattleScore(BYTE influence, WORD score);
		//ʧ���߼�buff
		void AddFailBuff(BYTE influence);
		//���ͱ���Ӫ���λ��
		void SendPKBattleUserPos(GamePlayer *user);
		//��������뿪������б�
		void ClearUserData(GamePlayer *user);
        //�Ƿ��Ѿ���ȡ������
        bool IsHaveGetPresent(GamePlayer *user);
        //������ȡ����
        void SetHaveGetPresent(GamePlayer *user);
        // ս����Ӫ����Ƶ��
        void SendChatMessageToInfluence( Msg* pMsg, enumBattleInfluence eInfluence );
protected:
			//��һ����Ӫս����ҹ�����
		  typedef std::set<DWORD>			PKBattleUsers;
		  typedef std::set<DWORD>::iterator PKBattleUsers_Iter;
		  //��������Ӫ��������Դ��
		  typedef std::map<uint8, uint8>			ResourceOccupyList;
		  typedef std::map<uint8, uint8>::iterator  ResourceOccupyList_Iter;
		  //ɱ����,��ɱ��
		  typedef std::map<DWORD, std::pair<WORD, WORD> >			UserKillList;
		  typedef std::map<DWORD, std::pair<WORD, WORD> >::iterator UserKillList_Iter;
		  //Dotaɱ�˰�
		  typedef std::map<DWORD, WORD >			DotaUserKillList;
		  typedef std::map<DWORD, WORD >::iterator  DotaUserKillList_Iter;
		  //ռ����Դ�ĸ���
		  typedef std::map<DWORD, DWORD>		   UserOccupyResourceList;
		  typedef std::map<DWORD, DWORD>::iterator UserOccupyResourceList_Iter;
		  //�췽���
		  std::set<DWORD> redUsers;
		  //�������
		  std::set<DWORD> blueUsers;
		  //��Դ��ռ���б�
		  ResourceOccupyList		resourceOccuptList;
		  //ɱ�˱�ɱ��
		  UserKillList				userKillList;
		  //Dota����ɱ��
		  DotaUserKillList			dotaKillList;
		  //��ȡ��Դ�ĸ���
		  UserOccupyResourceList	userOccuptResourceList;
		  //�췽����
		  DWORD redScore;
		  //��������
		  DWORD blueScore;
		  //��������״̬
		  uint8 state;
		  //���
		  uint8 result;
		  //��ǰս������
		  GameStage* pStage;
		  //ˢ����Դ���ͻ��˶�ʱ�� 
		  HRTimer freshScoreTimer;
		  //5���Ӽ���Դ��ʱ��
		  HRTimer addScoreTimer;
		  //�ȴ����Ͷ�ʱ��
		  HRTimer waitThrowTimer;
		  //������ʼʱ��
		  DWORD start_pktime;
          //�Ѿ���ȡ���������
          std::set<DWORD> getpresent_user;
};

#define thePKBattleManager PKBattleManager::Instance()

class PKBattleManager: public ISingletion<PKBattleManager> 
{
	enum enumPKBattleState
	{
		enumPKBattleState_Stop,	//δ��ʼ
		enumPKBattleState_Sign,	//�����׶�
		enumPKBattleState_PK,	//ս���׶�
	};
public:
	//��ʼ����Ӫ������
	void Init();
	//�����Ŷ�
	void RequestWaitBattleQueue(GamePlayer *user, WORD influence, WORD doorNum);
	//������븱��
	bool RequestIntoPKBattle(GamePlayer *user, bool isEnter);
	//�����͵ȴ�����
	void RequestSendWaitBattleQueue(GamePlayer *user);
	//���͵�ǰ������ѱ����б�
	void RequestPKBattleSignList(GamePlayer *user, WORD influence, WORD doorNum);
	//�˳��ŶӶ���
	void RemoveFromWaitQueue(GamePlayer *user);
	//ѭ��
	void Loop();
	//ƥ��
	void Match();
	//������Ӫ����
	void TestBattle(GamePlayer *user, const char * param);
	//����Ƿ�ʼ��Ӫ����
	bool CheckBattleStart()
	{
		return start;
	}
	void SetBattleStart(int round, int addScore, int successScore, int battleTime, int waitTime, int matchNum)
	{
		if(enumPKBattleState_PK == state)
		{
			return;
		}
		this->ClearPKBattleData();
		start = true;
		this->round = round;
		this->addScorePerFiveSec = addScore;
		this->successScore = successScore;
		this->battleTime = battleTime;	
		this->wait_time = waitTime;
		this->match_num = matchNum;
	}
	//���һ����ǰ����ʹ�õĸ���
	PKCopyScene* GetOneReadyCopyScene();
	//����û��Ѿ��ڵȴ�����
	bool CheckUserInWaitBattleQueue(GamePlayer *user);
	//�������Ŷӵ���Ӫ�ͷ���
	void GetUserInfluenceAndDoorNum(GamePlayer *user, uint8 &influence, uint8 &doorNum);
	//������ҽ��븱������Ϣ 
	void PKBattleManager::PushUserToPKBattle(PKCopyScene *scene, DWORD pCharID, BYTE which);
	//����ID
	PKCopyScene* GetCopySceneByID(DWORD nMapID);
	//֪ͨ���и�������
	void NotifyPKBattleEnd();
	//�����������ͷŸ���
	void DeleteStage(PKCopyScene *scene);
	//�ͷŹ�������Դ
	void ClearPKBattleData();
	//�����ҵ���Ӫ����
	PKCopyScene* GetUserPKBattleScene(GamePlayer *user,BYTE& influence);
    //֪ͨ���û��ƥ����
    void NotifyPlayerNoMatch();
public:
	//ÿ����������Դ��
	int addScorePerFiveSec;
	//���˳������Դ��
	int successScore;
private:
	typedef std::set<DWORD> BattleWaitQueue;
	typedef std::set<DWORD>::iterator BattleWaitQueue_Iter;
	typedef std::map<DWORD, BattleWaitQueue> InfluenceWaitQueue;
	typedef std::map<DWORD, BattleWaitQueue>::iterator InfluenceWaitQueue_Iter;
	//����������Ӫ�ŶӶ���
	InfluenceWaitQueue queueRed;	//�췽��Ӫ
	InfluenceWaitQueue queueBlue;	//������Ӫ
	enumPKBattleState state;		//��Ӫ������ǰ״̬
	//�������еĸ���
	typedef std::list<PKCopyScene*> PKBattleList;
	typedef std::list<PKCopyScene*>::iterator PKBattleList_Iter;
	PKBattleList copySceneList;
	//5���ӱ�����ʱ��
	HRTimer *fiveMinTimer;
	//һ��ս��ʱ�䶨ʱ��
	HRTimer *fightTimer;
	//��Ӫ�����Ƿ�ʼ
	bool start;	
	//��ǰ��Ӫ�������ִ�
	int round;
	//ս��ʱ��, ����
	int battleTime;
	//�����ȴ�ʱ��
	int wait_time;
	//ƥ����С����
	int match_num;
};

#endif