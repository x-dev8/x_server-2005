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
#define Monster_Map_xPos		 34				// ���������x����
#define Monster_Map_yPos		 35				// ���������y����
#define Monster_Create_TimeSpace 2000			// ����������ÿ�������뷢��һ�ι��ﴴ������
#define Monster_Num_PerSecond	 5				// ����������ÿ��Monster_Create_TimeSpace�봴��������
#define Monster_Num_Total		 10				// �����������ܹ��ɴ������ٹ�����
//luo.qin 4.15 End

//���������ֵĵ�һ�� (PK ʱ���ж��Ƿ��ǵ���)
const static int s_nNameCount = 2;
const static char* s_pszName[s_nNameCount] = {"T", "H", };

struct SSetInfo;

//2D������Ϣ luo.qin 3.28 
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
    unsigned short PackageId;// ����id
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

	char szCryptID[eMaxString];   //���ܺ��ʺ�����,��Ϊ���緢����
	char szCryptPWD[eMaxString];
};

class BaseRobot:public INetworkNode
{
public:
    BaseRobot();
    virtual ~BaseRobot();

    // ��������
    virtual void ProcessMsgs();
/*    virtual void OnConnectToServer();*/
    virtual void Update();

    // �����ຯ��
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

    void            SetTipsInfo( const char* pszTips );            // ��Ҫ����
    char*           GetBotTips() { return m_szTips;}               // ����SetTipsInfo��Ƕ�ڵ��ò���Ҫ����

    const char*     GetChannelName() { return _targetChannelName.c_str(); }
    void            SetChannelName( const char* szChannelName);

    const char*     GetMapName(); // ��ͼ
    uint32          GetMapID() { return m_CharInfo.otherdataclient.pos.dwMapID; }
    void            SetMapID( uint32 mapId ); 

 //   void            SetGLSAddress( const char* szIP, uint32 port); // ����GLS��ַ
 //   char*           GetGLSIP()   { return _szGLSIP; }              // �õ�GLSIP
 //   uint32          GetGLSPort() { return _GLSPort; }              // �õ�GLSPort

 //   void            SetLoginErrorCode( uint32 dwError){ m_dwLoginError = dwError; }
 //   DWORD           GetLoginErrorCode(){ return m_dwLoginError;  }

 //   bool            AsynGLSLoginLan();                                // �����첽GLS��¼
//     //////////////////////////////////////////////////////////////////////////
//     bool            GetGlsId( const char* szAcount, std::string& glsid);
//     bool            GetPwdMd5( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1);
// 	bool			GetPwdSha1( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1);
//     bool            AsynGLSLoginWan();                                // �����첽GLS��¼
    //////////////////////////////////////////////////////////////////////////
    void            SetPos(float x, float y, float z);
    bool            CheckTime(unsigned int nMax, bool bSpace = false, bool bClose = true);
	virtual void    SwitchMsg( Msg* pMsg );
	
	virtual void    ReGetCharacterlist(){}
	virtual void	try_comfirm_account();
	
	void EnterWorld(int nIndex);        // EnterWorld ����
protected:    

    bool            HandleStateEnd();               // ���� End
/*    bool            HandleStateEnterCharacterS();   // ���� EnterCharacter*/
    bool            HandleStateCreateChar();        // ���� CreateChar    
/*	bool            HandleStateEnterGameS();        // ���� EnterGameS*/
    bool            HandleStatePlay();              // ���� Play

	// ������ӳ���
	void ReqAddPet( unsigned int nPetId, unsigned int nQuality = 1, unsigned int nSex = 0 );

    //////////////////////////////////////////////////////////////////////////
    // MessageHandle ��Ӧ��Ϣ
    //////////////////////////////////////////////////////////////////////////
    #include "RobotMessageHandle.h"

	bool EncodeAccountInfo(SAccountInfo* pAccountInfo);
public:
    typedef std::vector<GameTimerEx>      StateTimerContainer;
    typedef StateTimerContainer::iterator ItrStateTimerContainer;
    typedef std::vector<SCharBaseInfo>    CharInfoContainer;
    typedef std::vector<uint32>           CharDBIdContainer;

    SCharInfoClient     m_CharInfo;
    SCharItem*          m_pItemBag;       // ������ָ�� ITEM_BAGMAX�Ǳ��������
    SCharItem*          m_pMaterialBag;
    SCharItem*          m_pTaskItemBag;
    SCharSkill*         m_pSkillBag;
    SMountItem*         m_BromeItems;
	SPetItem*           m_PetItems;
    StateTimerContainer m_vLastProTime;
    CharInfoContainer   m_vectorCharInfo;
    CharDBIdContainer   m_vCharacterID;   // ��ɫID,һ��ְҵ�и�4����ɫ    
    GameObjectId        m_shPlayerId;     // ��ɫ�ڷ������ϵĶ�̬ID

	uint32           _accountId;          // �ʺ�Id
	std::string      _targetGateIp;       // ��Ҫȥ��Ŀ��GateIp
	uint16           _targetGatePort;     // ��Ҫȥ��Ŀ��GatePort 
	uint32           _charDbId;           // Char Db Id
protected:
    
//     char             _szGLSIP[20];        // GLS IP
//     uint16           _GLSPort;            // GLS �˿�
    int              m_nID;               // ������Id
    char             m_szBotName[20];     // ����������
    char             m_szPassWord[20];    // ����������
	DWORD            nTimeLastConfirm;
    
    GameTimerEx      _pingTime;           // ping��ʱ��
   

    uint32           m_dwLoginError;    
    std::string      _targetChannelName;  // Ƶ������
   
    char             m_szTips[512];       // ������״̬��ʾ��Ϣ
    volatile uint16           m_BotType;           // ����������
    int              m_nMapID;            // ��ǰ��ͼId
    std::string      m_strMap;            // ��ǰ��ͼ����
    uint16           _BotNation;          // �����˹���

    //int             m_nBotSpace;        // �����˼��
public:
    //int  GetBotSpace() { return m_nBotSpace;}
    //void SetBotSpace(int nSpace) { m_nBotSpace = nSpace;} // Get Set�����˼��

//////////////////////////////////////////////////////////////////////////
public: // ��Ҫ����
    void SetSleep(DWORD Time);
    unsigned char GetSelfSex(){return m_CharInfo.baseinfo.aptotic.ucSex;}
    unsigned short GetSelfProfession(){return m_CharInfo.baseinfo.aptotic.usProfession;}


public:
    void PushChatMsgInList(Msg* pMsg);
    string PopChatMsgFormList();

    short GetWhoKillMe();
    BOOL Init( SSetInfo* pSetInfo );

	void RandChangeEquip();					//�����װ�� luo.qin 3.21
	void RandChangeEquip_BotCommand();		//�����װ�� luo.qin 3.24
	void ChangeEquipByProfession();			//��ְͬҵ��װ��luo.qin 3.29
	void BotCreateMonster( DWORD dwDBID, DWORD dwMonsterID, float fPos_X, float fPos_Y, DWORD dwMonsterNum = 1, DWORD dwMapID = 0,
		 DWORD dwMonsterType = 0, float fRadius = 0.0f );									//����������:�����˴�������luo.qin 3.17 
	void ChangeEquip( DWORD dwDBID );														//����������;��װ��luo.qin 3.21
	void ReqCreateItemForBot(int nDBID, int nItemID, int nCount, int nFlag);				//BOT����:���󴴽�װ�������ڴ���֮ǰ��������ͷ���������Ұ�����װ��������luo.qin 3.24
	void ReqRemoveAllEquip(int nDBID);														//BOT����:�ڴ���֮ǰ��������ͷ���������Ұ�����װ��������luo.qin 3.24

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
    void    AddHp(); // ��Ѫ
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

    DWORD GetPingTime();// ȡ����
    virtual void PlayGame();
    virtual void Move();
    virtual void Say(const char *pszChat);
    virtual void InitPlayGame(UINT mapid = 0);
    virtual bool InitGetItem();
    virtual void InitLevel();
    virtual GameObjectId LockTarget(){ return -1; }

    virtual void StatMsgInfo(int nType, Msg* pMsg);						// ͳ����Ϣ����

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
	bool			m_bNeedAckAgain;//��Ҫ�ٴγ���switchgate��Ϣ
	bool isDisconnected;
	bool isReadyEnterGame;
	
	bool isEnterWorldQueue;
	DWORD dwEnterWorldQueueStartTime;
	
	//std::string m_strSessionKey;
	__int64            SessionKey;         //�ʺ�session
    DWORD m_dwLastLoopTime;
    bool m_bAckLogin;
    bool m_bSpaceCheck;												    // ֻ�ǵ�����һ��ִ��ʱ����
    bool m_bClose;														// �Ƿ�Ҫ�Ͽ�����

    DWORD m_ReqLogRoleInfo;
    DWORD m_dwMoveSpaceTime;
    int m_nMoveStep;

    typedef std::list<PlayerInfo> PlayerInfoContainer;
    typedef PlayerInfoContainer::iterator IterPlayerInfoContainer;


    PlayerInfoContainer m_listPlayerList;								// ������Ұ��Ϣ������push_back
    PlayerInfoContainer m_listMonsterList;
    PlayerInfoContainer m_listItemMonsterList;							// ���߹���
    PlayerInfoContainer m_listNPCList;
    std::list<PackageItem> m_listPackageList;
    std::vector<MsgPackageViewAck::PackageItemInfo>         ItemList;	// �鿴ɱ���Ժ�ʰȡ������Item
    std::vector<MsgPackageitemAccessAck::PackageItemInfo>   PickAcessLevelList;

    D3DXVECTOR3 m_vPos;					// �Լ�������
    D3DXVECTOR3 m_vDir;					// �Լ��ĳ���

    int m_nTotalMsgNum;
    int m_nTotalPosPack;
    int m_nTotalPosMsg;
    int m_nTotalSightPack;
    int m_nTotalSightMsg;

    DWORD m_SendPackNum;				// ������Ϣ��������
    DWORD m_RecvPackNum;				// ������Ϣ��������
    DWORD ShowPackTime;					// 
    bool m_FirstSendPackage;			// 
    DWORD m_RecvPackSize;				// ���յ���Ϣ��С
    DWORD m_SendPackSize;				// ���͵���Ϣ��С

    MsgStatistician m_xMsgStatistician; // ͳ����Ϣ
    RobotItemBag ItemNormalBag;
    std::vector<short> KillMeTarget;
    int m_nMapWidth;
    int m_nMapHeight;

    bool m_bFlyMap;						// ������Ϸ��Ҫ�����һ�µ�ͼ
    bool m_bGetItem;					// ����մ�����ɫ������һ��װ��
    DWORD m_dwInitStartTime;
	bool m_hasCreateRole;               //�Ѿ�������˴�����ɫ,��������,��Զ�ȴ�


    bool m_bLoadMapOver;				// �ɵ�ͼ��ʱ���Ƿ��յ�MsgMapInfoReady
    DWORD m_WaitUpdateSightTime;		// �����ͼ�Ժ�ʼ��ʱ�ȷ�����ˢ�¹��������Ұ����Ϣ

    bool IsLearn;						// �Ƿ�ѧϰ������
    SSetInfo* m_pSetInfo;

    static bool m_bIsLoginGLS;

	DWORD m_dwReEquipItemTime;			// ����ɿ��ܶ��������⣬����յ�����װ����Ʒ����Ϣ��< 10���������ʱ�������
	bool  m_bCanEquip;					// ����װ����
	DWORD m_MonsterNum;					// luo.qin 3.18
	DWORD m_LastCreateTime;				// luo.qin 3.17
	DWORD m_ChangeEquipTime;			// luo.qin 3.21
    
protected:
    D3DXVECTOR3 m_vMovePos;				//�漴�ƶ�Ҫȥ������
    
    bool m_bVerifyPos;
    char m_cMoveSerial;
    
    float m_fMoveSpeed;
    DWORD m_dwStartMovingTime;

    std::list<string> m_listChatMsg;

    std::vector<int> vecMap;
    int nMapCount;
    SAreaInfo m_xAreaInfo;				// ָ���Ļ���������

    bool isTest;

    short influence;					// �Լ�����Ӫ��ʶ
    bool CanControl;
    DWORD dw_SleepTime;
    DWORD dw_SleepCurTime;

    DWORD dw_LoginTotalTime;			// ��¼������ʱ��
    DWORD dw_LoginGLSTime;				// ��¼GLS���ѵ�ʱ��
    DWORD dw_LoginSelectRoleTime;		// ѡ���ɫ������ʱ�����
    DWORD dw_EnterWorldTime;			// EnterWorld������ʱ��

    DWORD dw_FirstLoginGLSTime;			// ��¼GLS���ѵ�ʱ��
    DWORD dw_FirstLoginSelectRoleTime;  // ѡ���ɫ������ʱ�����
    DWORD dw_FirstEnterWorldTime;		// EnterWorld������ʱ��
    DWORD dw_FirstLoginTotalTime;		// ��һ����ʱ��
    bool  bIsFirstReqLogin;				// �Ƿ��ǵ�һ�������¼
    bool  bIsFirstReqGetCharacter;

    bool  bIsPlayTime;					// �Ƿ������Ϸ



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

    DWORD m_dwReqCharInfoTime;			// �ϴ������ɫ��ʱ��
    int m_nReqCharInfoCount;			// ���������

    int m_ReqConnectNum;

    DWORD LastSummonPetTime;
	DWORD m_dwDeadTime;					// ����ʱ�� luo.qin 4.2
	DWORD m_dwEquipDoneTime;			// ���װ��ʱ�� luo.qin 4.2
	bool  m_bFirstInWorld;				// ��һ�ν�����Ϸ

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
