#pragma once
#include "QuestManager.h"
#include "QuestData.h"
#include "NpcInfo.h"
#include "PositionInfo.h"
#include "MonsterConfig.h"
#include "Attackbot.h"

class CQuestBot : public CAttackBot
{

public:
	struct NpcPoint
	{
		NpcPoint() { Clear(); }
		void Clear()
		{
			nNpcId = -1;
			nMapId = -1;
			nQuestId = -1;
			x = 0.0f;
			y = 0.0f;
		}

		bool Empty() { return (nNpcId == -1 || nQuestId == -1 || nMapId == -1); }

		int nNpcId;
		int nQuestId;
		int nMapId;
		float x;
		float y;
	};

   struct stDropItem
   {
       stDropItem()
       {
           MonsterId = 0;
           QuestId = 0;
           ItemId = 0;
           MonsterMapId = -1;
           MonsterPosX = -1;
           MonsterPosY = -1;
       }

       unsigned int MonsterId;
       int QuestId;
       int     ItemId;
       int     MonsterMapId;
       int     MonsterPosX;
       int     MonsterPosY;

       void Clear()
       {
           MonsterId = 0;
           QuestId = 0;
           ItemId = 0;
           MonsterMapId = -1;
           MonsterPosX = -1;
           MonsterPosY = -1;
       }
   };

	enum Quest_State
	{
		Quest_NotActive = 0,	 //任务还没接
		Quest_Refer,			//已经接了任务
		Quest_CasterState,		//任务可以提交
		Quest_Done,			//任务已经完成了

		Quest_End,
	};

    enum DoneConditionType  // 任务完成条件种类
    {
       EDCT_Error       = 0,     // 错误
       EDCT_KillMonster = 1,     // 杀一定数量的怪物
       EDCT_NeedItem    = 2,     // 获得道具
       EDCT_NoNeed      = 3,     // 什么都不需要 只要说话
       EDCT_Action      = 4,     // 护送一类
       EDCT_KillMonsterItem = 5, // 杀怪拿道具
       EDCT_NeedLevel = 6,
       EDCT_NeedVar   = 7,
       EDCT_NeedQuest = 8,       // 前置任务
    };
public:  
	CQuestBot();
	virtual ~CQuestBot();

   virtual void InitPlayGame(UINT mapid = 0);
	virtual void PlayGame();
	virtual void PlayQuest();
	void SaveQuestLog();
   static bool ParseQuestForMap(QuestInfo::SQuests& m_pQuests);

   unsigned short ParseQuestForType( SQuest* quest ); // 分析任务的种类
   
   void GetNpcByMap(int MapId);
   void GetUnActiveQustDone(int curmapid);
   //bool IsQuestDone(SQuest* quest);
   void LoadAllRoleVars(MsgTellCharVar * pVar);
   void DoneQuestInface(int QuestId);
   
   static bool LoadQuest();
private:
	SQuest* GetRunQuest(int id = -1);							//获得一个执行的任务
	void SetMoveNpcPoint();							//设置交任务的NPC的坐标
	bool MoveToNpcPoint();							//移动到NPC
	//bool MoveToPoint(D3DXVECTOR3& xPos);
	bool ReceiveQuest();							//接任务
	bool ReferQuest();								//提交任务
   void PushToRunQuest( SQuest* quest);
   bool CheckBag(SCharItem *Addr,int ItemId,int &ItemCount);
   bool CheckBagItem(short BagType,int ItemId,int &ItemCount);
   bool LoadMonsetDropItem(const char* FilePath);
   bool DoQuest(unsigned short usQuestType);
   void CheckQuest();                               //初始化的时候检查当前地图已经完成的任务,
   bool EreaseQuest(int QuestId);
   bool CheckKillVar();
   int GetNpcById();
   int TokenString(const std::string SplitString);
   short GetRoleVarValue(int index);
   CQuestBot::stDropItem* FindDropInfoByQuestId(int QuestId);
public:
   virtual void SwitchMsg(Msg* pMsg);
	virtual void OnMsg_TellMap_NpcQuest(Msg* pMsg);
	virtual void OnMsg_TellCharVar(Msg* pMsg);
   virtual void OnMsg_AllNpcInTheMap(Msg* pMsg);
   virtual void OnMsg_Ack_Script(Msg* pMsg);
	virtual void OnMsg_ScriptReqShowQuestDlg(Msg* pMsg);
   virtual void OnMsgChangeMap(Msg* pMsg);
   virtual void OnMsg_UnPlayerEnterSight(Msg* pMsg);

public:
   typedef  std::multimap<int,SQuest*> MapForQustType;
   static MapForQustType m_MapForQuset;   // <地图,任务>
private:
   int m_nNpcId;			//npc动态ID
	static bool m_bLoad;
	static bool m_bLoadSuccessed;  //是否加载成功

	DWORD m_dwNextRunTime;			//下次执行动作时间
	NpcPoint m_xTargetNpcPoint;			//执行任务的地点坐标
	bool m_bRunQuestStart;			//开始执行任务
	Quest_State m_eQuestState;		//当前流程的状态

   bool IsSendRecvQuest;



   short LocalVars[ More_iMaxVars ];
   DWORD NoQuestTime;
typedef  std::map<int,NpcInfo::Npc*> MapForNpcType;
   MapForNpcType m_NpcForMap;
   typedef std::list<SQuest*> QuestList;
   QuestList    CurRunQuest;
typedef  std::vector<stDropItem>     DropItemContainer;
   static DropItemContainer DorpItemList;          //所有机器人共用
   static bool IsLoadQust;
   bool bFirst;

   unsigned short TotalDoneQuestCondition; // 完成当前任务需要的条件总数
   unsigned short CurDoneQuestCondition;     // 当前完了第几个

   SMapMonsterInfo* TargetSMapMonsterInfo;
   int NeedItemId;
   DWORD InitRunTime;
   DWORD ReqItemTime;
   DWORD MoveTime;
   bool bMoveToMonster;
   bool NeedKillMonster;
   int MaxKillNum;
   int KillIndex;

   int FrontQuestId;

   int CurQuestId;         // 当前任务的ID

   DWORD ReqNpcScriptTime;
};


/**********************************************************************
1. 读取本地任务文件  (随即选一个任务接了)
2. 判断交任务目标, 找到地图
3. 飞到该地图,找到该NPC (因为接任务和交任务都是同一个NPC
4. 接任务, 等待3秒, 交任务, 反复之...


// new

**********************************************************************/