/********************************************************************
    Filename:     Bot.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"
//#include "NetworkNode.h"
#include "Dxsdk\d3dx9math.h"
#include "MsgStatistician.h"
#include "RobotItemBag.h"
#include "GameDefineBot.h"
#include "MessageDefine.h"
#include "GameTimer.h"
#include "RelationDefine.h"
#include "NpcInfo.h"
#include "NetworkInput.h"

#define Msg_Send 0
#define Msg_Recv 1

#pragma warning(disable:4389)

#define CHARACTOR_COUNT 5
#define ROBOT_REQUEST_COMMAND "$BotReq "

#define MAP_COUNT 10
#define Begin_Map_xPos  157
#define Begin_Map_yPos  90

//luo.qin 4.15 Begin
#define Monster_Map_xPos		 34				// 怪物出生点x坐标
#define Monster_Map_yPos		 35				// 怪物出生点y坐标
#define Monster_Create_TimeSpace 2000			// 单个机器人每隔多少秒发送一次怪物创建命令
#define Monster_Num_PerSecond	 5				// 单个机器人每隔Monster_Create_TimeSpace秒创建怪物数
#define Monster_Num_Total		 10				// 单个机器人总共可创建多少怪物数
//luo.qin 4.15 End

//机器人名字的第一个 (PK 时候判断是否是敌人)
const static int s_nNameCount = 2;
const static char* s_pszName[s_nNameCount] = {"T", "H", };

struct SSetInfo;

//2D坐标信息 luo.qin 3.28 
struct fPoint
{
	fPoint()
	{
		x = 0.0;
		y = 0.0;
	}
	fPoint(float x,float y)
	{
		this->x = x;
		this->y = y;
	}
	float x;
	float y;
	void Clear()
	{
		x = 0.0;
		y = 0.0;
	}
};




struct PlayerInfo
{
    PlayerInfo():dwCharacterID(0),shPlayerID(0),
        shCharType(0),shMonsterType(0),influence(0),
        dwMapID(0),nHP(0),m_vPos(0,0,0)
    {
        memset(szName, 0, dr_MaxPlayerName);
    }
    inline friend bool operator == (const PlayerInfo &info, const GameObjectId &id)
    {
        return (info.shPlayerID == id);
    }

    inline friend bool operator == (const PlayerInfo &info, const std::string &NpcName)
    {
        return (NpcName == info.szName);
    }

    PlayerInfo& operator = (const PlayerInfo &other)
    {
        dwCharacterID = other.dwCharacterID;
        shPlayerID = other.shPlayerID;
        shCharType = other.shCharType;
        shMonsterType = other.shMonsterType;
        strncpy_s(szName, sizeof(szName),other.szName,sizeof(other.szName)-1);
        dwMapID = other.dwMapID;
        nHP = other.nHP;
        m_vPos = other.m_vPos;
        influence = other.influence;
        return *this;
    }

    void Reset()
    {
        dwCharacterID = 0;
        shPlayerID = 0;
        shCharType = 0;
        shMonsterType = 0;
        dwMapID = 0;
        nHP = 0;
        m_vPos.x = 0;
        m_vPos.y = 0;
        m_vPos.z = 0;
        influence = 0;
        memset(szName,0,dr_MaxPlayerName);
    }

    DWORD dwCharacterID;
    GameObjectId shPlayerID;
    short shCharType;
    short shMonsterType;
    char szName[dr_MaxPlayerName];
    DWORD dwMapID;
    int nHP;
    D3DXVECTOR3 m_vPos;
    short influence;
};

struct PackageItem
{
    PackageItem()
    {
        PackageId = MAXWORD;
        PackageShortId = 0;
        FloatX = 0.0;
        FloatY = 0.0;
    }
    unsigned short PackageId;// 包裹id
    unsigned short PackageShortId;
    float FloatX,FloatY;
};

struct SAccountInfo
{
	enum
	{
		eMaxString = 128
	};
	SAccountInfo()
	{
		memset( this, 0, sizeof(*this) );
	}
	char szID[eMaxString];
	char szPwd[eMaxString];

	char szCryptID[eMaxString];   //加密后帐号密码,作为网络发送用
	char szCryptPWD[eMaxString];
};

class BaseRobot:public INetworkNode
{
public:
    BaseRobot();
    virtual ~BaseRobot();

    // 基类派生
    virtual void ProcessMsgs();
/*    virtual void OnConnectToServer();*/
    virtual void Update();

    // 自身类函数
    virtual void SendMsg  ( Msg* pMsg );

    SCharBaseAttr&  GetBaseAttr() { return m_CharInfo.baseinfo.baseProperty.baseAttr; }
    SCharFightAttr& GetFightAttr(){ return m_CharInfo.baseinfo.baseProperty.fightAttr; }
    
    void            SetBotID(int nID)                    { m_nID = nID;  }
    int             GetBotID()                           { return m_nID; }
    void            SetAccount(const char* pszAccount)   { strncpy_s(m_szBotName, sizeof(m_szBotName),pszAccount, sizeof(m_szBotName) - 1); }
    char*           GetAccount()                         { return m_szBotName;}
    void            SetPassword(const char* pszPassword) { strncpy_s(m_szPassWord,sizeof(m_szPassWord), pszPassword, sizeof(m_szPassWord) - 1); }
    const char*     GetPassword()                        { return m_szPassWord; }

    
    uint8           GetLastBotState() { return _lastState; }
    virtual void            SetBotState( uint8 nState);

    void            SetType( uint16 nType) { m_BotType = nType; }
    uint16          GetType() { return m_BotType; }

    void            SetTipsInfo( const char* pszTips );            // 需要加锁
    char*           GetBotTips() { return m_szTips;}               // 它在SetTipsInfo内嵌内调用不需要加锁

    const char*     GetChannelName() { return _targetChannelName.c_str(); }
    void            SetChannelName( const char* szChannelName);

    const char*     GetMapName(); // 地图
    uint32          GetMapID() { return m_CharInfo.otherdataclient.pos.dwMapID; }
    void            SetMapID( uint32 mapId ); 

 //   void            SetGLSAddress( const char* szIP, uint32 port); // 设置GLS地址
 //   char*           GetGLSIP()   { return _szGLSIP; }              // 得到GLSIP
 //   uint32          GetGLSPort() { return _GLSPort; }              // 得到GLSPort

 //   void            SetLoginErrorCode( uint32 dwError){ m_dwLoginError = dwError; }
 //   DWORD           GetLoginErrorCode(){ return m_dwLoginError;  }

 //   bool            AsynGLSLoginLan();                                // 内网异步GLS登录
//     //////////////////////////////////////////////////////////////////////////
//     bool            GetGlsId( const char* szAcount, std::string& glsid);
//     bool            GetPwdMd5( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1);
// 	bool			GetPwdSha1( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1);
//     bool            AsynGLSLoginWan();                                // 外网异步GLS登录
    //////////////////////////////////////////////////////////////////////////
    void            SetPos(float x, float y, float z);
    bool            CheckTime(unsigned int nMax, bool bSpace = false, bool bClose = true);
	virtual void    SwitchMsg( Msg* pMsg );
	
	virtual void    ReGetCharacterlist(){}
	virtual void	try_comfirm_account();
	
	void EnterWorld(int nIndex);        // EnterWorld 操作
protected:    

    bool            HandleStateEnd();               // 处理 End
/*    bool            HandleStateEnterCharacterS();   // 处理 EnterCharacter*/
    bool            HandleStateCreateChar();        // 处理 CreateChar    
/*	bool            HandleStateEnterGameS();        // 处理 EnterGameS*/
    bool            HandleStatePlay();              // 处理 Play

	// 请求添加宠物
	void ReqAddPet( unsigned int nPetId, unsigned int nQuality = 1, unsigned int nSex = 0 );

    //////////////////////////////////////////////////////////////////////////
    // MessageHandle 响应消息
    //////////////////////////////////////////////////////////////////////////
    #include "RobotMessageHandle.h"

	bool EncodeAccountInfo(SAccountInfo* pAccountInfo);
public:
    typedef std::vector<GameTimerEx>      StateTimerContainer;
    typedef StateTimerContainer::iterator ItrStateTimerContainer;
    typedef std::vector<SCharBaseInfo>    CharInfoContainer;
    typedef std::vector<uint32>           CharDBIdContainer;

    SCharInfoClient     m_CharInfo;
    SCharItem*          m_pItemBag;       // 背包的指针 ITEM_BAGMAX是背包最大数
    SCharItem*          m_pMaterialBag;
    SCharItem*          m_pTaskItemBag;
    SCharSkill*         m_pSkillBag;
    SMountItem*         m_BromeItems;
	SPetItem*           m_PetItems;
    StateTimerContainer m_vLastProTime;
    CharInfoContainer   m_vectorCharInfo;
    CharDBIdContainer   m_vCharacterID;   // 角色ID,一个职业有个4个角色    
    GameObjectId        m_shPlayerId;     // 角色在服务器上的动态ID

	uint32           _accountId;          // 帐号Id
	std::string      _targetGateIp;       // 将要去的目标GateIp
	uint16           _targetGatePort;     // 将要去的目标GatePort 
	uint32           _charDbId;           // Char Db Id
protected:
    
//     char             _szGLSIP[20];        // GLS IP
//     uint16           _GLSPort;            // GLS 端口
    int              m_nID;               // 机器人Id
    char             m_szBotName[20];     // 机器人名字
    char             m_szPassWord[20];    // 机器人密码
	DWORD            nTimeLastConfirm;
    
    GameTimerEx      _pingTime;           // ping的时间
   

    uint32           m_dwLoginError;    
    std::string      _targetChannelName;  // 频道名字
   
    char             m_szTips[512];       // 机器人状态提示信息
    volatile uint16           m_BotType;           // 机器人类型
    int              m_nMapID;            // 当前地图Id
    std::string      m_strMap;            // 当前地图名字
    uint16           _BotNation;          // 机器人国家

    //int             m_nBotSpace;        // 机器人间距
public:
    //int  GetBotSpace() { return m_nBotSpace;}
    //void SetBotSpace(int nSpace) { m_nBotSpace = nSpace;} // Get Set机器人间距

//////////////////////////////////////////////////////////////////////////
public: // 需要整理
    void SetSleep(DWORD Time);
    unsigned char GetSelfSex(){return m_CharInfo.baseinfo.aptotic.ucSex;}
    unsigned short GetSelfProfession(){return m_CharInfo.baseinfo.aptotic.usProfession;}


public:
    void PushChatMsgInList(Msg* pMsg);
    string PopChatMsgFormList();

    short GetWhoKillMe();
    BOOL Init( SSetInfo* pSetInfo );

	void RandChangeEquip();					//随机换装备 luo.qin 3.21
	void RandChangeEquip_BotCommand();		//随机换装备 luo.qin 3.24
	void ChangeEquipByProfession();			//不同职业的装备luo.qin 3.29
	void BotCreateMonster( DWORD dwDBID, DWORD dwMonsterID, float fPos_X, float fPos_Y, DWORD dwMonsterNum = 1, DWORD dwMapID = 0,
		 DWORD dwMonsterType = 0, float fRadius = 0.0f );									//机器人命令:机器人创建怪物luo.qin 3.17 
	void ChangeEquip( DWORD dwDBID );														//机器人命令;换装备luo.qin 3.21
	void ReqCreateItemForBot(int nDBID, int nItemID, int nCount, int nFlag);				//BOT命令:请求创建装备，并在创建之前清理自身和服务器的玩家包裹和装备栏数据luo.qin 3.24
	void ReqRemoveAllEquip(int nDBID);														//BOT命令:在创建之前清理自身和服务器的玩家包裹和装备栏数据luo.qin 3.24

    void InitPlayerSkill();

    char* GetBotRoleName()
    { 
        if(GetBotState() == State_Play)
        {
            return m_CharInfo.baseinfo.aptotic.szCharacterName;
        }
        return NULL;
    }

    int     GetNullItemIndex();
    void    SetBotMoney(DWORD money){ m_CharInfo.baseinfo.liveinfo.dwMoney = money;}
    DWORD   GetBotMoney() { return m_CharInfo.baseinfo.liveinfo.dwMoney; }
    void    ReqBotMoney(unsigned long Money);
    int     GetBotMp(){ return m_CharInfo.baseinfo.liveinfo.nMp; }
    void    ReqLvlUp(int nLvl);
    void    AddHp(); // 回血
    unsigned short GetBotLevel(){ return m_CharInfo.baseinfo.liveinfo.ustLevel;}
    //SPrivateShopItemInfo* GetBotPrivateShopBag(){return m_CharInfo.otherdataclient.stPrivateShopItem;}
    //void    SetBotPrivateShopBag(SPrivateShopItemInfo * Item,int Idex );
    //SPrivateShopItemInfo* GetPrivateShopBag(int Idex);
    bool    IsPrivateShopBagEmpty();
    bool    IsPrivateShopBagFull();

    virtual bool IsNormalBagFull();
    virtual bool IsMaterialBagFull();
    bool IsPlayingGame(){return bIsPlayTime;}
    void ClearNormalBagItem();
    void ClearMaterialBagItem();

    bool MoveToPoint(D3DXVECTOR3& xPos,float Distance_Error = 2.0);
    bool Move2Point(D3DXVECTOR3& xPos ,float Distance_Error = 1.0);
    bool MoveToItemPackage(float X,float Y);
    unsigned long GetBotDBID(){ return _charDbId;}


    GameObjectId GetBotShortId(){return m_shPlayerId;}

    bool IsHavePackage(){ return !m_listPackageList.empty();}
    bool ViewPackageItem();


    void SetMoveStep(int nMoveStep) { m_nMoveStep = nMoveStep; }

    int GetBotHP(){return m_CharInfo.baseinfo.liveinfo.nHp;}

    float GetPosX() { return m_vPos.x; }
    float GetPosY() { return m_vPos.y; }

    void SetMovePos(int nPosX, int nPosY) { m_vMovePos.x = nPosX; m_vMovePos.y = nPosY; m_vMovePos.z; }
    void ClearMovePos() { m_vMovePos.x = 0; m_vMovePos.y = 0; m_vMovePos.z = 0; }


    PlayerInfo* RandPlayer();
    PlayerInfo* GetMonster(GameObjectId shID);
    PlayerInfo* GetNPC(GameObjectId shID);
    PlayerInfo* GetNPCByName(const std::string& Name);
    PlayerInfo* GetPlayer(GameObjectId shID);
    PlayerInfo* GetPlayerByName(const std::string &TargetName);
    void RemovePlayer(GameObjectId shID);
    int GetPlayerNum();
    int GetNPCNum();
    int GetMonsterNum();

    bool LoginServerNew();

    void ReqGetItem(int nPackPos);
    void ReqGetItem(int nItemID, int nCount, int nFlag);

    void EquipItem(int nItemID, int nPackIndex);

    void ReqItem(unsigned int ItemId, unsigned int nCount = 1, unsigned int nType = 0);
    void UseItem(unsigned int ItemId,EBagType type,short targetType = 0,short TargetId = 0);
    void FlyToMap(short shMap, short shAreaX, short shAreaY);
    void LearnAllSkill();
    void LoadRandFlyMap();
    void RandFly();
    void UpdateBotState();
    bool IsHaveItem(int ItemId);
    bool AStarMove(int map,float x,float y);

    virtual bool IsInArea(int nMap, D3DXVECTOR3& xPos);
    virtual void MoveToArea();

    DWORD GetPingTime();// 取出来
    virtual void PlayGame();
    virtual void Move();
    virtual void Say(const char *pszChat);
    virtual void InitPlayGame(UINT mapid = 0);
    virtual bool InitGetItem();
    virtual void InitLevel();
    virtual GameObjectId LockTarget(){ return -1; }

    virtual void StatMsgInfo(int nType, Msg* pMsg);						// 统计消息数据

    virtual void ReqCharInfo(GameObjectId shID);
    virtual void RandReqCharInfo(GameObjectId shID);

	bool GetbFirstInWorld() { return m_bFirstInWorld; }
	void SetbFirstInWorld( bool bFlag ) { m_bFirstInWorld = bFlag; }

	SPetItem* FindPetByGuid(__int64 FindGuid);
	SPetItem* FindPetByIndex(int Index);

    typedef std::map<unsigned int,RelationDataToClient> RelationList;
    typedef RelationList::iterator ItrRelation;
    RelationList Relations;
	
	
	void SwitchGate(bool _connect);

public:
 //   bool m_bNeedAckAgain;
	bool g_bSwitchGate;
	int sPlayerSlot;
	BOOL			g_bEndGetCharacter;
	DWORD		g_dwSwitchGateTime;
	DWORD		g_dwSwitchGatePeriod;
	bool			m_bNeedAckAgain;//需要再次出发switchgate消息
	bool isDisconnected;
	bool isReadyEnterGame;
	
	bool isEnterWorldQueue;
	DWORD dwEnterWorldQueueStartTime;
	
	//std::string m_strSessionKey;
	__int64            SessionKey;         //帐号session
    DWORD m_dwLastLoopTime;
    bool m_bAckLogin;
    bool m_bSpaceCheck;												    // 只是单纯的一个执行时间间隔
    bool m_bClose;														// 是否要断开连接

    DWORD m_ReqLogRoleInfo;
    DWORD m_dwMoveSpaceTime;
    int m_nMoveStep;

    typedef std::list<PlayerInfo> PlayerInfoContainer;
    typedef PlayerInfoContainer::iterator IterPlayerInfoContainer;


    PlayerInfoContainer m_listPlayerList;								// 进入视野消息处理中push_back
    PlayerInfoContainer m_listMonsterList;
    PlayerInfoContainer m_listItemMonsterList;							// 道具怪物
    PlayerInfoContainer m_listNPCList;
    std::list<PackageItem> m_listPackageList;
    std::vector<MsgPackageViewAck::PackageItemInfo>         ItemList;	// 查看杀怪以后拾取包裹的Item
    std::vector<MsgPackageitemAccessAck::PackageItemInfo>   PickAcessLevelList;

    D3DXVECTOR3 m_vPos;					// 自己的坐标
    D3DXVECTOR3 m_vDir;					// 自己的朝向

    int m_nTotalMsgNum;
    int m_nTotalPosPack;
    int m_nTotalPosMsg;
    int m_nTotalSightPack;
    int m_nTotalSightMsg;

    DWORD m_SendPackNum;				// 发送消息包的数量
    DWORD m_RecvPackNum;				// 接收消息包的数量
    DWORD ShowPackTime;					// 
    bool m_FirstSendPackage;			// 
    DWORD m_RecvPackSize;				// 接收的消息大小
    DWORD m_SendPackSize;				// 发送的消息大小

    MsgStatistician m_xMsgStatistician; // 统计信息
    RobotItemBag ItemNormalBag;
    std::vector<short> KillMeTarget;
    int m_nMapWidth;
    int m_nMapHeight;

    bool m_bFlyMap;						// 进入游戏后要随机飞一下地图
    bool m_bGetItem;					// 如果刚创建角色就请求一次装备
    DWORD m_dwInitStartTime;
	bool m_hasCreateRole;               //已经请求过了创建角色,不再请求,永远等待


    bool m_bLoadMapOver;				// 飞地图的时候是否收到MsgMapInfoReady
    DWORD m_WaitUpdateSightTime;		// 进入地图以后开始计时等服务器刷新怪物进入视野的信息

    bool IsLearn;						// 是否学习过技能
    SSetInfo* m_pSetInfo;

    static bool m_bIsLoginGLS;

	DWORD m_dwReEquipItemTime;			// 解决由可能丢包的问题，如果收到请求装备物品的消息数< 10，则用这个时间来解决
	bool  m_bCanEquip;					// 可以装备了
	DWORD m_MonsterNum;					// luo.qin 3.18
	DWORD m_LastCreateTime;				// luo.qin 3.17
	DWORD m_ChangeEquipTime;			// luo.qin 3.21
    
protected:
    D3DXVECTOR3 m_vMovePos;				//随即移动要去的坐标
    
    bool m_bVerifyPos;
    char m_cMoveSerial;
    
    float m_fMoveSpeed;
    DWORD m_dwStartMovingTime;

    std::list<string> m_listChatMsg;

    std::vector<int> vecMap;
    int nMapCount;
    SAreaInfo m_xAreaInfo;				// 指定的机器的坐标

    bool isTest;

    short influence;					// 自己的阵营标识
    bool CanControl;
    DWORD dw_SleepTime;
    DWORD dw_SleepCurTime;

    DWORD dw_LoginTotalTime;			// 登录花费总时间
    DWORD dw_LoginGLSTime;				// 登录GLS花费的时间
    DWORD dw_LoginSelectRoleTime;		// 选择角色花费总时间包含
    DWORD dw_EnterWorldTime;			// EnterWorld花费总时间

    DWORD dw_FirstLoginGLSTime;			// 登录GLS花费的时间
    DWORD dw_FirstLoginSelectRoleTime;  // 选择角色花费总时间包含
    DWORD dw_FirstEnterWorldTime;		// EnterWorld花费总时间
    DWORD dw_FirstLoginTotalTime;		// 第一次总时间
    bool  bIsFirstReqLogin;				// 是否是第一次请求登录
    bool  bIsFirstReqGetCharacter;

    bool  bIsPlayTime;					// 是否进入游戏



    bool NeedCheckLoginTime;
    DWORD CheckLoginTime;
    typedef std::list<D3DXVECTOR3> AutoMoveList;
    AutoMoveList AutoRunPosList;
    std::list<DWORD> PingList;
    DWORD m_LastSeeAttactTime;
    uint32 m_LoginStaticTime;

	typedef std::vector<SPetItem> SPetContainer;
	typedef SPetContainer::iterator ItrSPetContainer;

	SPetContainer  SPets;


private:
    DWORD m_dwLastTime;
    int m_nMoveSpaceTimes;

    DWORD m_dwReqCharInfoTime;			// 上次请求角色的时间
    int m_nReqCharInfoCount;			// 请求的数量

    int m_ReqConnectNum;

    DWORD LastSummonPetTime;
	DWORD m_dwDeadTime;					// 死亡时间 luo.qin 4.2
	DWORD m_dwEquipDoneTime;			// 最后装备时间 luo.qin 4.2
	bool  m_bFirstInWorld;				// 第一次进入游戏

};

extern int g_nTotalMsgNum;
extern int g_nTotalPosPack;
extern int g_nTotalPosMsg;
extern int g_nTotalSightPack;
extern int g_nTotalSightMsg;

//////////////////////////////////////////////////////////////////////////
inline void BaseRobot::SetMapID( uint32 mapId )
{ 
    if ( mapId  != ErrorUnsignedLongID)
    { m_CharInfo.otherdataclient.pos.dwMapID = mapId; }
}

inline void BaseRobot::SetChannelName(const char* szChannelName)
{ 
    if (NULL == szChannelName) 
    { return; }
    _targetChannelName = szChannelName; 
}
