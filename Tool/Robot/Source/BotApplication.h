/********************************************************************
	Filename: 	BotApplication.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibsServer.h"
//#include "NetworkApp.h"
#include "WorkThread.h"
#include "GameDefineBot.h"
#include "BotAppDataCenter.h"
#include "GuiLogicMessage.h"
#include "Mutex.h"
#include "GameTimer.h"
#include "ConsoleWindow.h"
#include "memory_pool.h"

class BaseRobot;

//#define theNetworkApp GetNetworkApp()

// gui线程会访问 逻辑线程数据 为了效率 需要牺牲部分准确同步的准确性 不加锁
// 1.机器人队列,通过得到单个机器人指针 所以运行期间不加锁，所以机器人创建后，在整个运行期都不删除。
// 2.访问单个机器人的成员数据时候 可能其他线程在对他进行写操作 所以读出的数据是赃数据 不过马上会在下 一次Render中麻烦纠正

class BotApplication/* : public INetworkApp */
{
public:
    enum EAppStateType
    {
        EAppStateType_Init,    // 初始化状态
        EAppStateType_Update,  // Update状态
        EAppStateType_Exist,   // 退出状态
        EAppStateType_Exiting, // 正在退出状态
        EAppStateType_InitFail,// 初始化状态失败
    };

public:
    BotApplication();
    virtual ~BotApplication();
    virtual uint32 Init( const char* szConfig );
    virtual void   Update();
    virtual void   UnInit();    

    uint32  GetAppState()              { return _appState;  }
    void    SetAppState( uint8 state ) { _appState = state; }

	//是否可创建怪物的 开关 luo.qin 3.18
	bool	SetBCreateMonster( bool bCreateMonster );
	bool	SetBChangeEquip( bool bChangeEquip );
	bool    SetBRandRide( bool bRandRide );
	bool	SetBCountryFight( bool bCountryFight );

    // 添加机器人
    void    AddBot( const SAddInfo& xAddInfo);
    void    AddBot( int nPerCount, int nStartId, int nType, int nOnlineTime = 0, int nFlySpace = 120, int nMoveStep = 500, SAreaInfo* pAreaInfo = NULL );

    // 向逻辑线程发送消息
    void    PushMessage( SBaseGuiLogicMessage* pGuiMessage);
    void    ProcessGuiMessage();

    BaseRobot* GetBot   ( int nID );
    bool       DeleteBot( int nID );

    bool    AddBotInMapList   ( BaseRobot* pBot, int nStartId, int nType, int nMoveStep = 500 );
    bool    AddClientInMapList( BaseRobot *pBot, int nSetp = 1000 );

protected:
    void    SetAddBot(SAddInfo& addInfo);
    void    AddRobotInformation();
    void    HandleGMsgAddRobot( GMsgAddRobot* pMessage );
    void    HandleGMsgShowRobot( GMsgShowRobot* pMessage );
    void    HandleGMsgPauseAddBot( GMsgPauseBot* pMessage );
    void    HandleGMsgPlaySkill( GMsgPlaySkill* pMessage );
    void    HandleGMsgBotMoving( GMsgBotMoving* pMessage );
    void    HandleGMsgBotPlayAttack( GMsgBotPlayAttack* pMessage );
    void    HandleGMsgBotRide( GMsgBotRide* pMessage);
    void    HandleGMsgReloadLuaScript(GMsgReLoadLuaScript* pMessage);
	void	HandlePrepareSuit( GMsgPrepareSuit* pMessage );

private:
    typedef std::map<int, BaseRobot*>          RobotContainer;
    typedef RobotContainer::iterator           ItrRobotContainer;

    uint8                    _appState;

    GuiLogicMessageContainer _messages; // Ui2Logic 消息队列
    CSemiAutoIntLock         _messageLock;
    Common::TAllocator<uint8, 256, 100> _messageAlloc;

    RobotContainer           _robots;
    CSemiAutoIntLock         _lockRobots;
    GameTimerEx              _addTime;
    GameTimerEx              _lastShowTime;
    int32                    m_nAliveBotCount; // 实际的机器人个数

//////////////////////////////////////////////////////////////////////////
public:
	void ScriptAddBot();
	void SetBotSetInfo (SSetInfo *pSetInfo);
	SSetInfo* GetBotSetInfo() { return m_pSetInfo; }
    void SetCurSel(int nSel) { m_nCurSel = nSel; }
    int GetCurSel() { return m_nCurSel; }
	int GetTotalBotCount() { return m_nAliveBotCount; }
	int GetAttackBotCount() { return m_nAttackBotCount; }
	int GetMoveBotCount() { return m_nMoveBotCount; }
	int GetOnLineBotCount() { return m_nOnLineBot; }
	void DisPerseBot(char* pszMap, int nCount);   
	void ShowBotCountInformation();
	void AddBotMapDistributing(string strMap);

public:
    std::map<std::string, int> m_mapMapDistributing;
    typedef std::map<std::string, int>::iterator IterMapDistributing;
	std::vector<SAddInfo> m_vecAddInfo;
    struct skillStruct 
    {
        unsigned short id;
        unsigned short SkillLevel;
        unsigned short targetType;
    };
    typedef std::multimap<unsigned short,skillStruct> SkillMap;
    typedef SkillMap::iterator ItrSkillMap;
    SkillMap  RoleSkillMap; // 职业,技能id

    static bool Exit;

    int m_nCurSel;
	SAddInfo m_xAddInfo;
	SSetInfo* m_pSetInfo;
	
	int m_nAttackBotCount;
	int m_nMoveBotCount;
	int m_nOnLineBot;
    static int      nBotID;//  当前机器人ID[10/8/2010 pengbo.yang]
    void SetBotID(int nID)
    {
        if (nID == 0)
        { return;}

        nBotID = nID;
    }

    int GetRobotID(){ return nBotID;}
    bool GetAllBotInfo(LMsgShowAllRobotInfo& msg);
	DWORD m_dwCreateTime;
    int nCurrentIndex;
private:
    SAddInfo m_AddInfo;
    GMsgAddRobot* pMsgOld;
    int nAddCount;
    //int nSpace;
public:
    CustomConsole myConsole;
};
