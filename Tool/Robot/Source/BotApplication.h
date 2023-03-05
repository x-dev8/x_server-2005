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

// gui�̻߳���� �߼��߳����� Ϊ��Ч�� ��Ҫ��������׼ȷͬ����׼ȷ�� ������
// 1.�����˶���,ͨ���õ�����������ָ�� ���������ڼ䲻���������Ի����˴����������������ڶ���ɾ����
// 2.���ʵ��������˵ĳ�Ա����ʱ�� ���������߳��ڶ�������д���� ���Զ����������������� �������ϻ����� һ��Render���鷳����

class BotApplication/* : public INetworkApp */
{
public:
    enum EAppStateType
    {
        EAppStateType_Init,    // ��ʼ��״̬
        EAppStateType_Update,  // Update״̬
        EAppStateType_Exist,   // �˳�״̬
        EAppStateType_Exiting, // �����˳�״̬
        EAppStateType_InitFail,// ��ʼ��״̬ʧ��
    };

public:
    BotApplication();
    virtual ~BotApplication();
    virtual uint32 Init( const char* szConfig );
    virtual void   Update();
    virtual void   UnInit();    

    uint32  GetAppState()              { return _appState;  }
    void    SetAppState( uint8 state ) { _appState = state; }

	//�Ƿ�ɴ�������� ���� luo.qin 3.18
	bool	SetBCreateMonster( bool bCreateMonster );
	bool	SetBChangeEquip( bool bChangeEquip );
	bool    SetBRandRide( bool bRandRide );
	bool	SetBCountryFight( bool bCountryFight );

    // ��ӻ�����
    void    AddBot( const SAddInfo& xAddInfo);
    void    AddBot( int nPerCount, int nStartId, int nType, int nOnlineTime = 0, int nFlySpace = 120, int nMoveStep = 500, SAreaInfo* pAreaInfo = NULL );

    // ���߼��̷߳�����Ϣ
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

    GuiLogicMessageContainer _messages; // Ui2Logic ��Ϣ����
    CSemiAutoIntLock         _messageLock;
    Common::TAllocator<uint8, 256, 100> _messageAlloc;

    RobotContainer           _robots;
    CSemiAutoIntLock         _lockRobots;
    GameTimerEx              _addTime;
    GameTimerEx              _lastShowTime;
    int32                    m_nAliveBotCount; // ʵ�ʵĻ����˸���

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
    SkillMap  RoleSkillMap; // ְҵ,����id

    static bool Exit;

    int m_nCurSel;
	SAddInfo m_xAddInfo;
	SSetInfo* m_pSetInfo;
	
	int m_nAttackBotCount;
	int m_nMoveBotCount;
	int m_nOnLineBot;
    static int      nBotID;//  ��ǰ������ID[10/8/2010 pengbo.yang]
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
