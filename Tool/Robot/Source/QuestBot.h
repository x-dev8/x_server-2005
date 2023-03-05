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
		Quest_NotActive = 0,	 //����û��
		Quest_Refer,			//�Ѿ���������
		Quest_CasterState,		//��������ύ
		Quest_Done,			//�����Ѿ������

		Quest_End,
	};

    enum DoneConditionType  // ���������������
    {
       EDCT_Error       = 0,     // ����
       EDCT_KillMonster = 1,     // ɱһ�������Ĺ���
       EDCT_NeedItem    = 2,     // ��õ���
       EDCT_NoNeed      = 3,     // ʲô������Ҫ ֻҪ˵��
       EDCT_Action      = 4,     // ����һ��
       EDCT_KillMonsterItem = 5, // ɱ���õ���
       EDCT_NeedLevel = 6,
       EDCT_NeedVar   = 7,
       EDCT_NeedQuest = 8,       // ǰ������
    };
public:  
	CQuestBot();
	virtual ~CQuestBot();

   virtual void InitPlayGame(UINT mapid = 0);
	virtual void PlayGame();
	virtual void PlayQuest();
	void SaveQuestLog();
   static bool ParseQuestForMap(QuestInfo::SQuests& m_pQuests);

   unsigned short ParseQuestForType( SQuest* quest ); // �������������
   
   void GetNpcByMap(int MapId);
   void GetUnActiveQustDone(int curmapid);
   //bool IsQuestDone(SQuest* quest);
   void LoadAllRoleVars(MsgTellCharVar * pVar);
   void DoneQuestInface(int QuestId);
   
   static bool LoadQuest();
private:
	SQuest* GetRunQuest(int id = -1);							//���һ��ִ�е�����
	void SetMoveNpcPoint();							//���ý������NPC������
	bool MoveToNpcPoint();							//�ƶ���NPC
	//bool MoveToPoint(D3DXVECTOR3& xPos);
	bool ReceiveQuest();							//������
	bool ReferQuest();								//�ύ����
   void PushToRunQuest( SQuest* quest);
   bool CheckBag(SCharItem *Addr,int ItemId,int &ItemCount);
   bool CheckBagItem(short BagType,int ItemId,int &ItemCount);
   bool LoadMonsetDropItem(const char* FilePath);
   bool DoQuest(unsigned short usQuestType);
   void CheckQuest();                               //��ʼ����ʱ���鵱ǰ��ͼ�Ѿ���ɵ�����,
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
   static MapForQustType m_MapForQuset;   // <��ͼ,����>
private:
   int m_nNpcId;			//npc��̬ID
	static bool m_bLoad;
	static bool m_bLoadSuccessed;  //�Ƿ���سɹ�

	DWORD m_dwNextRunTime;			//�´�ִ�ж���ʱ��
	NpcPoint m_xTargetNpcPoint;			//ִ������ĵص�����
	bool m_bRunQuestStart;			//��ʼִ������
	Quest_State m_eQuestState;		//��ǰ���̵�״̬

   bool IsSendRecvQuest;



   short LocalVars[ More_iMaxVars ];
   DWORD NoQuestTime;
typedef  std::map<int,NpcInfo::Npc*> MapForNpcType;
   MapForNpcType m_NpcForMap;
   typedef std::list<SQuest*> QuestList;
   QuestList    CurRunQuest;
typedef  std::vector<stDropItem>     DropItemContainer;
   static DropItemContainer DorpItemList;          //���л����˹���
   static bool IsLoadQust;
   bool bFirst;

   unsigned short TotalDoneQuestCondition; // ��ɵ�ǰ������Ҫ����������
   unsigned short CurDoneQuestCondition;     // ��ǰ���˵ڼ���

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

   int CurQuestId;         // ��ǰ�����ID

   DWORD ReqNpcScriptTime;
};


/**********************************************************************
1. ��ȡ���������ļ�  (�漴ѡһ���������)
2. �жϽ�����Ŀ��, �ҵ���ͼ
3. �ɵ��õ�ͼ,�ҵ���NPC (��Ϊ������ͽ�������ͬһ��NPC
4. ������, �ȴ�3��, ������, ����֮...


// new

**********************************************************************/