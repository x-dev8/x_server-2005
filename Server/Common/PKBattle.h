/********************************************************************
Filename: 	PKBattle.h
MaintenanceMan Mail: lufeipeng@163.com
brief: 阵营战场管理
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

//定一下阵营副本,处理副本的流程
class PKCopyScene: INHERIT_POOL(PKCopyScene)
{
public:
		enum
		{
			PKScript_CheckPackFull = 1,		//检测包裹满
			PKScript_AddPresent	   = 2,		//增加奖励
			PKBattle_FAILBUFF	   = 2533,  //战场失败buff
			PKBattle_DeadBuff	   = 3653,	//战场虚弱buff
            PKBattle_GOTOBUFF      = 3353,  //冷却buff
		};
		enum
		{
			enumCopySceneState_Stop		 = 0,		 //结束状态
			enumCopySceneState_Running   = 1,		//正在PK状态
			enumCopySceneState_WaitThrow = 2,		//等待传送
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
		//创建阵营副本
		static GameStage* CreateStage();
		//初始化战场相关
		void InitScene();
		//玩家进入战场初始化信息,是否第一次进入
		bool InitUser(GamePlayer *player, BYTE which, bool firstEnter = true);
		//从战场删除玩家
		void DestroyBattleUser(GamePlayer *player);
		//刷新战场的资源点
		void FreshBattleResouce();
		//循环
		void Loop();
		//刷新阵营副本积分给副本玩家
		void SendPKBattleScoreToAllUser();
		//发送消息给战场玩家
		void SendPKBattleScoreToUser(GamePlayer *player);
		void SendPKBattleScoreToUser(DWORD characterID);
		//请求阵营副本当前状态
		void SendPKBattleState(GamePlayer *user);
		//获得玩家的阵营
		enumBattleInfluence GetUserInfluence(DWORD characterID);
		//资源点对应的npc
		BaseCharacter* GetNpcByResourcePos(enumBattleResouce pos);
		//获得资源点的占领者
		enumBattleInfluence GetResourcePosOwner(enumBattleResouce pos);
		//设置资源点的占领者
		bool SetResourcePosOwner(GamePlayer *player, enumBattleResouce pos);
		//设置战场状态
		void SetState(BYTE state)
		{
			this->state = state;
		}
		BYTE GetState()
		{
			return this->state;
		}
		//设置Stage
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
		//获得战场结果
		uint8 GetPKBattleResult()
		{
			return result;
		}
		//设置获得副本开始时间
		void SetStartPKTime(DWORD startTime)
		{
			start_pktime = startTime;
		}
		DWORD GetStartPKTime()
		{
			return start_pktime;
		}
		//判断副本是否结束
		void CheckBattleOver();
		//时间到，判断结束
		void BattleTimeOver();
		//副本结束，仍出所有玩家
		void ThrowCopyUser();
		//结束，奖励
		void EndBattle(enumBattleInfluence winner);
		//通知杀人
		void NotifyKillUser(GamePlayer *killer, GamePlayer *beKiller);
		//调用脚本
		void DoPKScript(GamePlayer *user, DWORD which);
		//增加战场积分
		void AddPKBattleScore(BYTE influence, WORD score);
		//失败者加buff
		void AddFailBuff(BYTE influence);
		//发送本阵营玩家位置
		void SendPKBattleUserPos(GamePlayer *user);
		//玩家主动离开，清空列表
		void ClearUserData(GamePlayer *user);
        //是否已经领取过奖励
        bool IsHaveGetPresent(GamePlayer *user);
        //设置领取奖励
        void SetHaveGetPresent(GamePlayer *user);
        // 战场阵营发言频道
        void SendChatMessageToInfluence( Msg* pMsg, enumBattleInfluence eInfluence );
protected:
			//定一下阵营战场玩家管理器
		  typedef std::set<DWORD>			PKBattleUsers;
		  typedef std::set<DWORD>::iterator PKBattleUsers_Iter;
		  //定义下阵营副本的资源点
		  typedef std::map<uint8, uint8>			ResourceOccupyList;
		  typedef std::map<uint8, uint8>::iterator  ResourceOccupyList_Iter;
		  //杀人数,被杀数
		  typedef std::map<DWORD, std::pair<WORD, WORD> >			UserKillList;
		  typedef std::map<DWORD, std::pair<WORD, WORD> >::iterator UserKillList_Iter;
		  //Dota杀人榜
		  typedef std::map<DWORD, WORD >			DotaUserKillList;
		  typedef std::map<DWORD, WORD >::iterator  DotaUserKillList_Iter;
		  //占领资源的个数
		  typedef std::map<DWORD, DWORD>		   UserOccupyResourceList;
		  typedef std::map<DWORD, DWORD>::iterator UserOccupyResourceList_Iter;
		  //红方玩家
		  std::set<DWORD> redUsers;
		  //蓝方玩家
		  std::set<DWORD> blueUsers;
		  //资源点占领列表
		  ResourceOccupyList		resourceOccuptList;
		  //杀人被杀数
		  UserKillList				userKillList;
		  //Dota公告杀人
		  DotaUserKillList			dotaKillList;
		  //夺取资源的个数
		  UserOccupyResourceList	userOccuptResourceList;
		  //红方积分
		  DWORD redScore;
		  //蓝方积分
		  DWORD blueScore;
		  //副本运行状态
		  uint8 state;
		  //结果
		  uint8 result;
		  //当前战场场景
		  GameStage* pStage;
		  //刷新资源给客户端定时器 
		  HRTimer freshScoreTimer;
		  //5秒钟加资源定时器
		  HRTimer addScoreTimer;
		  //等待传送定时器
		  HRTimer waitThrowTimer;
		  //副本开始时间
		  DWORD start_pktime;
          //已经领取奖励的玩家
          std::set<DWORD> getpresent_user;
};

#define thePKBattleManager PKBattleManager::Instance()

class PKBattleManager: public ISingletion<PKBattleManager> 
{
	enum enumPKBattleState
	{
		enumPKBattleState_Stop,	//未开始
		enumPKBattleState_Sign,	//报名阶段
		enumPKBattleState_PK,	//战斗阶段
	};
public:
	//初始化阵营管理器
	void Init();
	//申请排队
	void RequestWaitBattleQueue(GamePlayer *user, WORD influence, WORD doorNum);
	//请求加入副本
	bool RequestIntoPKBattle(GamePlayer *user, bool isEnter);
	//请求发送等待队列
	void RequestSendWaitBattleQueue(GamePlayer *user);
	//发送当前房间的已报名列表
	void RequestPKBattleSignList(GamePlayer *user, WORD influence, WORD doorNum);
	//退出排队队列
	void RemoveFromWaitQueue(GamePlayer *user);
	//循环
	void Loop();
	//匹配
	void Match();
	//测试阵营副本
	void TestBattle(GamePlayer *user, const char * param);
	//检测是否开始阵营副本
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
	//获得一个当前可以使用的副本
	PKCopyScene* GetOneReadyCopyScene();
	//检测用户已经在等待队列
	bool CheckUserInWaitBattleQueue(GamePlayer *user);
	//获得玩家排队的阵营和房间
	void GetUserInfluenceAndDoorNum(GamePlayer *user, uint8 &influence, uint8 &doorNum);
	//设置玩家进入副本的信息 
	void PKBattleManager::PushUserToPKBattle(PKCopyScene *scene, DWORD pCharID, BYTE which);
	//副本ID
	PKCopyScene* GetCopySceneByID(DWORD nMapID);
	//通知所有副本结束
	void NotifyPKBattleEnd();
	//副本结束，释放副本
	void DeleteStage(PKCopyScene *scene);
	//释放管理器资源
	void ClearPKBattleData();
	//获得玩家的阵营副本
	PKCopyScene* GetUserPKBattleScene(GamePlayer *user,BYTE& influence);
    //通知玩家没有匹配上
    void NotifyPlayerNoMatch();
public:
	//每五秒增加资源数
	int addScorePerFiveSec;
	//获得顺利的资源数
	int successScore;
private:
	typedef std::set<DWORD> BattleWaitQueue;
	typedef std::set<DWORD>::iterator BattleWaitQueue_Iter;
	typedef std::map<DWORD, BattleWaitQueue> InfluenceWaitQueue;
	typedef std::map<DWORD, BattleWaitQueue>::iterator InfluenceWaitQueue_Iter;
	//红蓝两个阵营排队队列
	InfluenceWaitQueue queueRed;	//红方阵营
	InfluenceWaitQueue queueBlue;	//蓝方阵营
	enumPKBattleState state;		//阵营副本当前状态
	//管理所有的副本
	typedef std::list<PKCopyScene*> PKBattleList;
	typedef std::list<PKCopyScene*>::iterator PKBattleList_Iter;
	PKBattleList copySceneList;
	//5分钟报名定时器
	HRTimer *fiveMinTimer;
	//一轮战斗时间定时器
	HRTimer *fightTimer;
	//阵营副本是否开始
	bool start;	
	//当前阵营副本的轮次
	int round;
	//战场时间, 分钟
	int battleTime;
	//报名等待时间
	int wait_time;
	//匹配最小人数
	int match_num;
};

#endif