#ifndef __TEAMMANAGER_H__
#define __TEAMMANAGER_H__

/************************************************************************
                队伍模块
                裁决中心在CenterServer CenterTeamManager.cpp
                逻辑在GameServer GameTeamManager.cpp

                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "Memory_pool.h"
#include <string>
#include <list>
#include <map>
#include <vector>
#include "RelationConfig.h"
namespace TeamDefine
{
    enum ETeamConstDefine
    {
        ErrorID           = 0,			// 错误的ID
        TeamUpdateTime    = 2000,       // 2秒更新一次队伍信息
        MaxTimeOut        = 300000,     // 队伍缓存保存5分钟
        NoneSessionID     = 0,          // 没有队伍ID
        InitSessionID     = 10000,      // 队伍的起始SessionID
        EndSessionID      = 10000000,   // 队伍的结束SeesionID
                                              
        // 删除队伍的结果             
        DoNothing         = 0,          // 啥都不干 
        ChangeHeader      = 1,          // 更换队长
        DeleteTeam        = 2,          // 删除队伍
                                      
        // 队伍更新操作               
        NotSendToGame     = 0,          // 不发送给GameServer
        SendToAllGame     = 1,          // 发送给所有GameServer
        SendToSomeGame    = 2,          // 发送给指定的某些GameServer
        NotSendToCenter   = 0,          // 不发送给CenterServer中转
        SendToCenter      = 1,          // 发送给CenterServer中转
        NotSendToClient   = 0,
        SendToClient      = 1,

        // 下面的错误宏, 和消息里定义的是一样的 所以看起来会比较乱
        CanJoinTeam       = 0,          // 能加入队伍
        AlreadyInTeam     = 0,          // 已经在队伍中
        TeamFull          = 3,          // 队伍已经满了
        JoinSuccess       = 9,          // 加入队伍成功
        NotTeamHeader     = 8,          // 自己不是队长
        InMyBlackList     = 16,         // 在自己黑名单中 
        InTargetBlackList = 13,         // 在对方黑名单中 


        // 小队buff类型
        Buffer_Team       = 0,          // 基本队伍附加的Buffer
        Buffer_Friend,                  // 好友度  附加Buffer
		Buffer_Guild,					// 军团    附加buffer
        Buffer_Max,        

        // 小队技能判断结果
        SkillCanUse		  = 0,			// 小队技能可使用
        SkillCanNotUse,					// 小队技能不能使用
        SkillCoolDown,					// 小队技能正在CD
    };

    // 玩家邀请或者申请队伍的记录信息
    struct TeamInvite
    {
        enum EConstDefine
        {
            ECD_Invite = 0,          // 邀请
            ECD_Request = 1,         // 申请

            ECD_TimeOut = 60000,     // 超时时间
            ECD_NameLength = 41,
        };

        char szAckName[ECD_NameLength];       // 被邀请者名字
        unsigned int dwReqID;                 // 请求者的id
        char szReqName[ECD_NameLength];       // 请求者名字
        int nHp;                              // 加入队伍时的HP
        int nMp;                              // 加入队伍时的MP 
        int nHpMax;                           // 加入队伍时的最大HP
        int nMpMax;                           // 加入队伍时的最大MP
        short stLevel;                        // 加入队伍时的等级
        unsigned char chProfession;           // 职业 
        unsigned char chSex;                  // 性别
        int nFaceId;                          // 预留脸部的Id
        int nHairId;                          // 头发ID
        int nHeadPicId;                       // 头像ID

        unsigned char AssignMode;			  // 队伍分配模式
        unsigned char AssignItemLevel;        // 队伍物品的分配等级

        unsigned int dwTimeOut;               // 请求超时
        unsigned char chInviteType;           // 请求类型
    };
}

// 基本队伍成员信息
class BaseTeamMember
{
public:
	BaseTeamMember() : dwID( TeamDefine::ErrorID ), dwTimeOut( 0 ), stManipleID( 0 ), bManipleHeader( false )
    {
        strName.clear();
		nTeamFollowMemberID = 0;
    }

    virtual ~BaseTeamMember(){ strName.clear(); }

    BaseTeamMember( const BaseTeamMember& xMember )
    {
        *this = xMember;
    }

    BaseTeamMember& operator = ( const BaseTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            strName        = xMember.GetName();
            dwID           = xMember.GetID();
            dwTimeOut      = xMember.GetTimeOut();
            stManipleID    = xMember.GetManipleID();
            bManipleHeader = xMember.GetManipleHeader();
        }

        return *this;
    }

    bool operator == ( unsigned int nValue ) { return dwID == nValue; }
    bool operator == ( const char* pszName ) { return strName == pszName; }

    bool IsErrorMember() { return ( dwID == TeamDefine::ErrorID || strName.empty() ); }     // 判断是否有效的队伍成员

    void SetName( const char* pszName )    { if ( *pszName != NULL ) { strName = pszName; } }
    void SetID( unsigned int nValue )      { dwID = nValue;			  }
    void SetTimeOut( unsigned int nValue ) { dwTimeOut = nValue;	  }
    void SetManipleID( short stValue )     { stManipleID = stValue;	  }
    void SetManipleHeader( bool bValue )   { bManipleHeader = bValue; }

    const char*		   GetName() const           { return strName.c_str(); }
    const unsigned int GetID() const			 { return dwID;			   }
    const unsigned int GetTimeOut() const		 { return dwTimeOut;	   }
    const short		   GetManipleID() const      { return stManipleID;	   }
    const bool		   GetManipleHeader() const  { return bManipleHeader;  }

	unsigned int GetTeamFollowMemberID() const						{ return nTeamFollowMemberID; }
	void		 SetTeamFollowMemberID( unsigned int nMemberID )	{ nTeamFollowMemberID = nMemberID; }
private:
    std::string strName;        // 队员名字
    unsigned int dwID;          // 队员ID
    unsigned int dwTimeOut;     // 异常离线超时时间

    short stManipleID;          // 小队的ID( 以后多队伍版本 )
    bool bManipleHeader;        // 是否小队队长

	unsigned int nTeamFollowMemberID;	// 队伍跟随队友的DBID
};

// CenterServer上的队伍成员信息
class CenterTeamMember : public BaseTeamMember
{
public:
    CenterTeamMember() : BaseTeamMember()
    {

    }

    CenterTeamMember( const CenterTeamMember& xMember )
    {
        *this = xMember;
    }

    CenterTeamMember& operator = ( const CenterTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            BaseTeamMember::operator = ( xMember );
        }
       
        return *this;
    }

    ~CenterTeamMember() {}
};

// GameServer上的队伍成员信息
class GameTeamMember : public BaseTeamMember
{
public:
    GameTeamMember() : BaseTeamMember(), nHp( 0 ), nMp( 0 ), nHpMax( 0 ), nMpMax( 0 ), 
		stLevel( 1 ), stSex( 0 ), nFaceId( 0 ), nHairId( 0 ), chProfession( 0 ) {}
    ~GameTeamMember() {}

    GameTeamMember( const GameTeamMember& xMember )
    {
        *this = xMember;
    }

    GameTeamMember& operator = ( const GameTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            BaseTeamMember::operator = ( xMember );

            nHp          = xMember.GetHP();
            nMp          = xMember.GetMP();
            nHpMax       = xMember.GetHPMax();
            nMpMax       = xMember.GetMPMax();
            stLevel      = xMember.GetLevel();
            stSex        = xMember.GetSex();
            chProfession = xMember.GetProfession();
            nFaceId      = xMember.GetFaceID();
            nHairId      = xMember.GetHairID();
            nHeadPicId   = xMember.GetHeadPicID();
        }

        return *this;
    }

    void SetHP( int nValue )                    { nHp = nValue; }
    void SetHPMax( int nValue )                 { nHpMax = nValue; }
    void SetMP( int nValue )                    { nMp = nValue; }
    void SetMPMax( int nValue )                 { nMpMax = nValue; }
    void SetLevel( short stValue )              { stLevel = stValue; }
    void SetProfession( unsigned char chValue ) { chProfession = chValue; }
    void SetFaceID( int nValue )                { nFaceId = nValue; }
    void SetHairID( int nValue )                { nHairId = nValue; }
    void SetHeadPicID( int nValue )             { nHeadPicId = nValue; }
    void SetSex( short stValue )                { stSex = stValue; }

    void AddTeamBuffer( unsigned char uchType, const TeamBuffer& xBuffer )
    {
        if ( uchType >= TeamDefine::Buffer_Max )
        { return; }

        xTeamBuffer[ uchType ] = xBuffer;
    }

    const int    GetHP() const                 { return nHp; }
    const int    GetHPMax() const              { return nHpMax; }
    const int    GetMP() const                 { return nMp; }
    const int    GetMPMax() const              { return nMpMax; }
    const short  GetLevel() const              { return stLevel; }
    const unsigned char  GetProfession() const { return chProfession; }
    const int    GetFaceID() const             { return nFaceId; }
    const int    GetHairID() const             { return nHairId; }
    const int    GetHeadPicID() const          { return nHeadPicId; }
    const short  GetSex() const                { return stSex; }
    
    TeamBuffer* GetTeamBuffer( unsigned char uchType )
    {
        if ( uchType >= TeamDefine::Buffer_Max )
        { return NULL; }
    
        return &( xTeamBuffer[uchType] );
    }

private:
    int nHp;                           // 玩家HP
    int nMp;                           // 玩家MP 
    int nHpMax;                        // 玩家最大HP
    int nMpMax;                        // 玩家最大MP
    short stLevel;                     // 玩家等级
    short stSex;                       // 性别 
    int nFaceId;                       // 脸部ID
    int nHairId;                       // 头发ID
    int nHeadPicId;                    // 头像ID
    unsigned char chProfession;        // 职业 

    TeamBuffer xTeamBuffer[ TeamDefine::Buffer_Max ];       // 附加的队伍Buffer
};

struct Msg;
class GameStage;
template< class T > class TeamManager;

typedef std::pair< unsigned long, unsigned long > CDTIME;

template< class T, class U > // T:队伍成员类型 U:成员关联对象
class Team : public Common::TObject_pool< Team< T, U > >
{
protected:
    typedef std::list< T > MemberList;
    typedef typename MemberList::iterator MemberListIter;

    typedef std::map< short, unsigned short > ManipleCountMap;  // 保存小队数量的map
    typedef ManipleCountMap::iterator ManipleCountMapIter;
    
    typedef T TeamMemberType;

public:
    Team() : m_bCrops( false ), m_dwTeamSessionID( 0 ), m_dwTeamHeaderID( TeamDefine::ErrorID ), m_nModeType( 0 ),
		m_chAssignItemLevel( 2 ), m_stAssignIndex( 0 ), m_dwLastUpdateFrienlyTime( HQ_TimeGetTime() ), 
		m_dwStartCoolDownTime( 0 ), m_dwCoolDownTime( 0 ),m_IsTransnationalTeam(false)
    {
        m_listTeamMember.clear();

        for ( int i = 0; i < TeamMaxManipleCount; ++i )       // 4个小队伍
        {
            m_mapManipleCount.insert( std::make_pair( i, 0 ) );
        }
    }

    ~Team() 
    { 
        m_dwTeamSessionID = TeamDefine::NoneSessionID;
        m_dwTeamHeaderID = TeamDefine::ErrorID;
        m_stAssignIndex = 0;
        m_listTeamMember.clear(); 
    }

    static Team* CreateTeam() { return CNewWithDebug< Team< T, U > >::Alloc( 1, "Team::CreateTeam中创建Team实例" ); }
    virtual void Release() { CNewWithDebug< Team< T,U > >::Free( this ); }

    

    void		SetTeamCrops( bool bCrops )							{ m_bCrops = bCrops; }       // 设置队伍是否为团
	void		SetTeamAssignModeType( unsigned char nModeType )	{ m_nModeType = nModeType; } // 设置队伍分配模式
	void		SetTeamAssignItemLevel( unsigned char chItemLevel ) { m_chAssignItemLevel = chItemLevel; }// 设置队伍物品分配等级
    void 		SetID( unsigned int dwSessionID )					{ m_dwTeamSessionID = dwSessionID; }  // 设置队伍
	void 		SetTeamHeaderID( unsigned int dwID )				{ m_dwTeamHeaderID = dwID; }          // 设置队长ID
	void		SetStartCoolDownTime( unsigned int dwTime )			{ m_dwStartCoolDownTime = dwTime; }
	void		SetCoolDownTime( unsigned int dwTime )				{ m_dwCoolDownTime = dwTime; }
	void		SetLastTeamFollowMember( unsigned int nMemberID )	{ m_dwLastTeamFollowMember = nMemberID; }
	void		SetIsTransnationalTeam(bool Result)					{ m_IsTransnationalTeam = Result;}

	bool				GetTeamCrops()					{ return m_bCrops; }           
    const unsigned char GetTeamAssignModeType() const	{ return m_nModeType; }			
    const unsigned char GetTeamAssignItemLevel() const	{ return m_chAssignItemLevel; }
    const unsigned int  GetID() const					{ return m_dwTeamSessionID; }
    const unsigned int  GetTeamHeaderID() const			{ return m_dwTeamHeaderID; }
	unsigned int		GetLastTeamFollowMember()		{ return m_dwLastTeamFollowMember; }
	bool				GetIsTransnationalTeam()		{ return m_IsTransnationalTeam;}

	// 增
	int		AddTeamMember( T& xMember, TeamManager< Team >& xTeamManager, TeamDefine::TeamInvite* pRecord );// 添加队员
	// 删
	int		RemoveTeamMember( unsigned int dwMemberID, TeamManager< Team >& xTeamManager );					// 删除队员
	void	RemoveTeamMemberAndReleaseTeam( unsigned int dwMemeberID, TeamManager< Team >& xTeamManager );	// 删除队员,如果队伍解散,释放资源
	void	DisbandTeam( TeamManager< Team >& xTeamManager );												// 解散队伍

	bool	ClearTeamBuffer( U* pTeamMember, unsigned char uchBufferType, unsigned char uchSendMessage = TeamDefine::SendToClient );
	
	// 改
	void	ProcessManipleInfo( T& xMember );																// 处理小队信息
	void	UpdateTeamTransnationalStates(bool IsAdd,unsigned int ID);										// 更新队伍状态(队伍成员国家纯不纯)
	bool	UpgradeTeamHeader( unsigned int dwMemberID );													// 更换队长
	int		RunTeamUpdate( unsigned char chOperate );														// 执行Team Update
	void	MemberOutLine( unsigned int dwMemberID );														// 设置队员离线
	void	MemberOnLine( unsigned int dwMemberID );														// 队员上面, 清除状态
	bool	UpdateTeamFriendly( U* pMemberPlayer, unsigned int nFriendly );									// 更新好友度
	void	UpdateTeamBuffer( unsigned int dwExceptMemberID = TeamDefine::ErrorID , bool bLeaveTeam = false );// 更新队伍Buffer  dwExceptMemberID为队伍中不计算此人的好友关系( 在删除队友时候使用 )
	void	UpdateTeamBuffer( T* pTeamMember, unsigned char uchCount = TeamMaxManipleMember, unsigned int dwExceptMemberID = TeamDefine::ErrorID );
	CDTIME		StartTeamSkillCoolDown( unsigned short ustSkillID, unsigned char uchLevel, unsigned int dwCoolDownTime );
	// 查
	// 获得队伍人数
	unsigned short 	TeamMemberCount() { return static_cast< unsigned short >( m_listTeamMember.size() ); }	
	unsigned int   	GetMemberIDByIndex( short nIndex );				  							// 通过索引找队员ID
	T*			   	GetTeamMemberByID( unsigned int dwMemberID );	  							// 通过ID找队员
	T*			   	GetTeamMemberByIndex( short nIndex );             							// 通过索引找队员
	U*				GetMemberPlayer( unsigned int dwMemberID, bool bIncludeNotInStage = false );// 获得队员的关联的角色属性
	unsigned char  	GetHeaderFriendCount( unsigned int dwExceptMemberID = TeamDefine::ErrorID );// 得到队长在队伍里面好友的数量
	bool 			IsTeamHeader( unsigned int dwMemberID ) { return ( dwMemberID == m_dwTeamHeaderID ); }  // 是否是队长
	bool 			IsInTeam( unsigned int dwMemberID );            							// 是否在队伍中
	bool 			IsTeamFull();                                   							// 判断队伍是否满了
	bool 			IsAllTeamMemberGreaterLevel( int nLevel );      							// 是否所有玩家都大于该等级
	int  			IsCanInviteJoinInTeam( unsigned int dwHeaderID, unsigned int dwNewAddID );  // 判断能否加入队伍
	int  			IsCanRequestJoinInTeam( unsigned int dwNewAddID );							// 判断能否入队
	unsigned int 	GetCurrentAssignTeamMemberID();												// 获得当前分配物品的队员的ID
	unsigned int 	GetTeamMemberNotHaveQuest( int nQuestID );									// 找到队伍中第一个没有该任务的玩家
	unsigned char   CheckTeamSkillCanUse( U* pPlayer, unsigned short ustSkillID, unsigned char uchSkillLevel );
	// 获得在范围内的所有队员ID
	void			GetTeamMemberInMapArea( unsigned int nMapID, float fX, float fY, std::vector< unsigned int >& vecTeamMemberID );   
	unsigned int	GetTeamMemberCountInMap( unsigned int nMapID, float fX, float fY );			// 某个地图内的队员个数
	// 获得队伍总等级和最大和最小等级差
	unsigned int	GetTeamMemberLevelDistance( unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel ); 
	float			GetTeamExpPercent( unsigned int nTeamCount, bool bIsEcType );							// 获得队伍经验百分比
	

    // 高级操作
    void SendMessageToTeamClient( Msg* pMessage, unsigned int nExceptID, unsigned char chOperate ); // 发送消息给队伍所有成员
    bool CallAllTeamPlayerFlyToMapReq( unsigned int nMapID, float fX, float fY, float fDir = 0.0f );
    //bool TeamChangeStage( GameStage* pGameStage, int nTileX, int nTileY, float dir );

    // 新加的时间函数 脚本相关
    unsigned long	IsTeamTimeVarPassOneDay( int nVarID );
    void			RecordNowTeamTimeVar( int nVarID );
    void			ClearTeamTimeVar( int nVarID, int nClearVarID );
	void			ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );//脚本相关
	bool			RecordTeamTime( int nVarId );																	//脚本相关
    unsigned long   IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration );	// 脚本相关

protected:
    void UpdateTeamMemberInfo( Msg* pMessage );
    bool ProcessUpgradeTeamHeader( T* pMember );				// 发送队长改变消息
    void ProcessAddTeamMember( T& xMember, TeamDefine::TeamInvite* pRecord ); // 发送添加队员消息
    void ProcessRemoveTeamMember( unsigned int dwMemberID );    // 发送删除队员消息
    void MemberOutLine( T* pTeamMember );                       // 设置队员离线
    void MemberOnLine( T* pTeamMember );                        // 刚进入游戏时, 更新队员信息给玩家

    void AddManipleCount( short stManipleID );              // 添加小队数量
    void SubManipleCount( short stManipleID );              // 减少小队数量

    void UpdateTeamFriendly();                              // 更新好友度
    void ClearTeamBuffer( U* pMemberPlayer );               // 清除小队Buffer
                             
    bool UpdateTeamBuffer( T* pTeamMember, U* pPlayer, unsigned char uchType, const TeamBuffer* pTeamBuffer );
    void ChangeTeamHeaderToOnLineMember();                  // 队长下线后找一个在线的当队长

    unsigned int GetMemberMinFriendly();					// 根据队长获得最小好友度

private:
    Team( const Team< T, U >& );
    Team< T, U >& operator = ( const Team< T, U >& );

private:
    MemberList m_listTeamMember;            // 队伍成员列表
	
	map<unsigned int,unsigned char>			m_MapCountry;//记录队员的国籍 中央服务器用的	

    unsigned int m_dwTeamSessionID;         // 队伍的SessionID;
    unsigned int m_dwTeamHeaderID;          // 队长ID
    bool		 m_bCrops;                  // 是否是团
    unsigned char m_nModeType;              // 分配模式
    unsigned char m_chAssignItemLevel;      // 物品分配的等级
    ManipleCountMap m_mapManipleCount;      // 4个小队,每个小队的人数

    unsigned short m_stAssignIndex;         // 该次掉落物品分配到某个队员身上 ( 队伍的索引 )
    unsigned int m_dwLastUpdateFrienlyTime; // 上次更新好友度时间

    unsigned int m_dwStartCoolDownTime;     // 队伍技能开始CoolDown时间
    unsigned int m_dwCoolDownTime;          // 队伍技能CD时间

	unsigned int m_dwLastTeamFollowMember;	// 当前队伍更随的最后一个玩家

	bool m_IsTransnationalTeam;//是否为跨国队伍 默认为false 如果队伍里所有玩家为同一国家的 或者说都没国家 就为false  否则就为true
};

template< class T >
class TeamManager
{
protected:
    typedef std::map< unsigned int, unsigned int > MapID;
    typedef MapID::iterator MapIDIter;

    typedef std::map< unsigned int, TeamDefine::TeamInvite > InviteInfoMap;
    typedef InviteInfoMap::iterator InviteInfoMapIter;
    typedef std::map< std::string, InviteInfoMap > InviteRecordMap;
    typedef InviteRecordMap::iterator InviteRecordMapIter;

    typedef typename std::map< unsigned int, T* > TeamMap;
    typedef typename TeamMap::iterator TeamMapIter;
public:
    ~TeamManager()
    {
        for ( TeamMapIter iter = m_mapTeam.begin(); iter != m_mapTeam.end(); ++iter )
        {
            if ( iter->second != NULL )
            {
                iter->second->Release();
            }
        }

        m_mapTeam.clear();
    }

    static TeamManager< T >& Instance()
    {
        static TeamManager< T > s_TeamManger;
        return s_TeamManger;
    }

    unsigned int CreateTeamSessionID();                     // 生成新的队伍SessionID
    T*	 GetTeam( unsigned int dwTeamSessionID );           // 查找队伍
    T*   CreateTeam( unsigned int dwTeamSessionID, unsigned char chAssignMode, unsigned char chAssignItemLevel );     // 创建队伍
    T*   GetTeamByMemberID( unsigned int dwMemberID );      // 通过队员ID查找队伍
    bool ReleaseTeam( unsigned int dwSessionID );           // 删除一个队伍
    void RemoveMemberByID( unsigned int dwMemberID );       // 删除队员
    void TeamMemberOutLine( unsigned int dwMemberID );      // 设置离线时间
    void TeamMemberOnLine( unsigned int dwMemberID );       // 队友上线了
    void SendOnLineMessage( unsigned int dwMemberID );      // 更新队员信息,当玩家第一次进入游戏世界
    void RunTeamManagerUpdate( unsigned int dwCurrentTime, unsigned char chOperate );    // 执行Update

    ////////////////////////////////////////////////////////////////////////////
    //角色id 和 teamsessionid 的关联
    bool AddMemberSessionID( unsigned int dwMemberID, unsigned int dwTeamSessionID );     // 添加玩家dbid和session的关联
    bool RemoveMemberSessionID( unsigned int dwMemberID );                                // 删除关联
    unsigned int GetMemberSessionID( unsigned int dwMemberID );                           // 查找关联
    ////////////////////////////////////////////////////////////////////////////////
    void AddInviteRecord( TeamDefine::TeamInvite& xInvite );                                 // 添加邀请信息
    void RemoveInviteRecord( std::string strAckName, unsigned int dwReqID );                 // 删除邀请信息
    TeamDefine::TeamInvite* GetInviteRecord( std::string strAckName, unsigned int dwReqID ); // 查找邀请信息
    //////////////////////////////////////////////////////////////////////////////////////
    void UpdateTeamBuffer( unsigned int dwReqPlayerID, unsigned int dwAckPlayerID, bool bAllTeamUpdate, bool bAddRelation );

protected:
    TeamManager() : m_dwNextTeamUpdateTime( 0 ), m_dwCreateSessionID( TeamDefine::InitSessionID )
    {
        m_mapTeam.clear();
        m_mapMemberSessionID.clear();      
        m_mapInviteRecord.clear();
    }

    bool AddTeam( T* pTeam );                                 // 添加一个队伍
    void SendCreateTeamMessage( T* pTeam );                   // 发送创建队伍信息
    void RunInviteRecordUpdate( unsigned int dwCurrentTime ); // 更新邀请组队信息
private:
    TeamManager( const TeamManager< T >& );
    TeamManager< T >& operator = ( const TeamManager< T >& );

private:
    TeamMap m_mapTeam;                     // 保存队伍的参数
    MapID m_mapMemberSessionID;            // 玩家id 关联 TeamSessionID
    unsigned int m_dwNextTeamUpdateTime;   // 上次更新队伍时间
    unsigned int m_dwCreateSessionID;      // 用这个来计算TeamSessionID
    InviteRecordMap m_mapInviteRecord;     // 组队的邀请记录
};

// 用ID找队员信息
template< class T, class U >
T* Team< T, U >::GetTeamMemberByID( unsigned int dwMemberID )
{
    MemberListIter iter = std::find( m_listTeamMember.begin(), m_listTeamMember.end(), dwMemberID );
    if ( iter == m_listTeamMember.end() )
    { return NULL; }

    return &( *iter );
}

// 通过索引找队员信息
template< class T, class U >
T* Team< T, U >::GetTeamMemberByIndex( short nIndex )           
{
    if ( nIndex < 0 || nIndex >= TeamMemberCount() )
    { return NULL; }

    MemberListIter iter = m_listTeamMember.begin();
    advance( iter, nIndex );

    return &( *iter );
}

// 用索引得到队员ID
template< class T, class U >
unsigned int Team< T, U >::GetMemberIDByIndex( short nIndex )
{
    T* pTeamMember = GetTeamMemberByIndex( nIndex );
    if ( pTeamMember == NULL )
    { return TeamDefine::ErrorID; }

    return pTeamMember->GetID();
}

// 判断队伍是否满了
template< class T, class U >
bool Team< T, U >::IsTeamFull()             
{
    int nMaxTeamCount = TeamMaxManipleMember;
    if ( m_bCrops )
    { nMaxTeamCount = TeamMaxMember; }

    return TeamMemberCount() >= nMaxTeamCount;
}

// 是否在队伍中
template< class T, class U >
bool Team< T, U >::IsInTeam( unsigned int dwMemberID )            
{
    T* pMember = GetTeamMemberByID( dwMemberID );
    return ( pMember != NULL );
}
// 添加队员
template< class T, class U >
int Team< T, U >::AddTeamMember( T& xMember, TeamManager< Team >& xTeamManager, TeamDefine::TeamInvite* pRecord )
{
    if ( IsInTeam( xMember.GetID() ) )
    { return TeamDefine::AlreadyInTeam; }

    if ( IsTeamFull() )
    { return TeamDefine::TeamFull; }

    // 处理小队信息 xMember 设置哪个小队 是否是小队长
    ProcessManipleInfo( xMember );

    //更新数量 所在小队的人数更新
    AddManipleCount( xMember.GetManipleID() );
    m_listTeamMember.push_back( xMember );  // 添加到队列

    // 加入关联 队员id <-> 队伍id
    xTeamManager.AddMemberSessionID( xMember.GetID(), GetID() );      //添加关联

    ProcessAddTeamMember( xMember, pRecord );        // 发送消息

	UpdateTeamTransnationalStates(true,xMember.GetID() );//更新队伍的状态
    return TeamDefine::JoinSuccess;
}

// 删除队员
template< class T, class U >
int Team< T, U >::RemoveTeamMember( unsigned int dwMemberID, TeamManager< Team >& xTeamManager )
{
    int nResult = TeamDefine::DoNothing;
    if ( !IsInTeam( dwMemberID ) )  //不是这个队伍中的
    { return nResult; }       

    ProcessRemoveTeamMember( dwMemberID );  // 发送消息

    if ( TeamMemberCount() <= 1 )
    {
        for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
        {
            xTeamManager.RemoveMemberSessionID( iter->GetID() );            //删除队伍关联
        }

        m_listTeamMember.clear();   
        m_mapManipleCount.clear();
        nResult = TeamDefine::DeleteTeam;
    }
    else 
    {
        // 删除该队员
        MemberListIter iter = std::find( m_listTeamMember.begin(), m_listTeamMember.end(), dwMemberID );
        if ( iter != m_listTeamMember.end() )
        { 
            SubManipleCount( iter->GetManipleID() );        // 更新小队数量
            m_listTeamMember.erase( iter );
        }

        xTeamManager.RemoveMemberSessionID( dwMemberID );

        if ( IsTeamHeader( dwMemberID ) )      // 如果原来是队长, 找到一个新队长
        {
            ChangeTeamHeaderToOnLineMember();
            nResult = TeamDefine::ChangeHeader;
        }

		UpdateTeamTransnationalStates(false,dwMemberID);
    }

    return nResult;
}

// 删除队员并释放队伍
template< class T, class U >
void Team< T, U >::RemoveTeamMemberAndReleaseTeam( unsigned int dwMemeberID, TeamManager< Team >& xTeamManager )
{
    if ( RemoveTeamMember( dwMemeberID, xTeamManager ) == TeamDefine::DeleteTeam )
    {
        xTeamManager.ReleaseTeam( GetID() );
    }
}

// 解散队伍
template< class T, class U >
void Team<T, U>::DisbandTeam( TeamManager< Team >& xTeamManager )
{
	for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
	{
		xTeamManager.RemoveMemberSessionID( iter->GetID() );            //删除队伍关联
	}

	m_listTeamMember.clear();   
	m_mapManipleCount.clear();

	xTeamManager.ReleaseTeam( GetID() );
}

// 更换队伍队长
template< class T, class U >
bool Team< T, U >::UpgradeTeamHeader( unsigned int dwMemberID )
{
    if ( IsTeamHeader( dwMemberID ) )
    { return false; }

    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return false; }

    SetTeamHeaderID( dwMemberID );      // 设置队长ID
    pTeamMember->SetManipleHeader( true );

    return ProcessUpgradeTeamHeader( pTeamMember );
}

template< class T, class U >
void Team< T, U >::MemberOutLine( unsigned int dwMemberID )
{
    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return; }

    MemberOutLine( pTeamMember );
}

template< class T, class U >
void Team< T, U >::MemberOnLine( unsigned int dwMemberID )
{
    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return; }

    MemberOnLine( pTeamMember );
}

// 添加小队数量
template< class T, class U >
void Team< T, U >::AddManipleCount( short stManipleID )
{
    ManipleCountMapIter iter = m_mapManipleCount.find( stManipleID );
    if ( iter == m_mapManipleCount.end() )
    { return; }

    ++iter->second;
    if ( iter->second > TeamMaxManipleMember )
    { iter->second = TeamMaxManipleMember; }
}

// 减少小队数量
template< class T, class U >
void Team< T, U >::SubManipleCount( short stManipleID )
{
    ManipleCountMapIter iter = m_mapManipleCount.find( stManipleID );
    if ( iter == m_mapManipleCount.end() )
    { return; }

    --iter->second;
    if ( iter->second < 0 )
    { iter->second = 0; }
}

// 获得当前分配的队员ID
template< class T, class U >
unsigned int Team< T, U >::GetCurrentAssignTeamMemberID()
{
    if ( m_stAssignIndex < 0 || m_stAssignIndex >= TeamMemberCount() )
    { m_stAssignIndex = 0; }

    return GetMemberIDByIndex( m_stAssignIndex++ );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建队伍的SessionID
template< class T >
unsigned int TeamManager< T >::CreateTeamSessionID()
{
    if(  m_dwCreateSessionID > TeamDefine::EndSessionID || m_dwCreateSessionID < TeamDefine::InitSessionID )
    { m_dwCreateSessionID = TeamDefine::InitSessionID; }

    return m_dwCreateSessionID++;
}

template< class T >
T* TeamManager< T >::CreateTeam( unsigned int dwTeamSessionID, unsigned char chAssignMode, unsigned char chAssignItemLevel )
{
    if ( dwTeamSessionID == TeamDefine::NoneSessionID )
    { return NULL; }

    T* pTeam = T::CreateTeam();
    if( pTeam == NULL )    // 分配失败
    { return NULL; }

    pTeam->SetID( dwTeamSessionID );
    pTeam->SetTeamAssignModeType( chAssignMode );
    pTeam->SetTeamAssignItemLevel( chAssignItemLevel );

    if ( !AddTeam( pTeam ) )
    {
        pTeam->Release();
        return NULL;
    }

    SendCreateTeamMessage( pTeam );        // 发送创建队伍消息
    return pTeam;
}

template< class T >
T* TeamManager< T >::GetTeamByMemberID( unsigned int dwMemberID )
{
    unsigned int dwTeamSessionID = GetMemberSessionID( dwMemberID );
    if ( dwTeamSessionID == TeamDefine::NoneSessionID )
    { return NULL; }

    T* pTeam = GetTeam( dwTeamSessionID );
    if ( pTeam == NULL || !pTeam->IsInTeam( dwMemberID ) )        // 没有队伍 
    {
        RemoveMemberSessionID( dwMemberID );
        return NULL;
    }

    return pTeam;
}

template< class T >
void TeamManager< T >::RemoveMemberByID( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        if ( pTeam->RemoveTeamMember( dwMemberID, *this ) == TeamDefine::DeleteTeam )
        {
            ReleaseTeam( pTeam->GetID() );
        }
    }
}

template< class T >
T* TeamManager< T >::GetTeam( unsigned int dwTeamSessionID )
{
    TeamMapIter iter = m_mapTeam.find( dwTeamSessionID );
    if ( iter == m_mapTeam.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
bool TeamManager< T >::AddTeam( T* pTeam )
{
    if ( pTeam == NULL || pTeam->GetID() == TeamDefine::NoneSessionID )
    { return false; }

    TeamMapIter iter = m_mapTeam.find( pTeam->GetID() );
    if ( iter != m_mapTeam.end() )
    { return false; }

    return m_mapTeam.insert( std::make_pair( pTeam->GetID(), pTeam ) ).second;
}

template< class T >
bool TeamManager< T >::ReleaseTeam( unsigned int dwSessionID )
{
    TeamMapIter iter = m_mapTeam.find( dwSessionID );
    if ( iter == m_mapTeam.end() )
    { return false; }

    if ( iter->second != NULL )
    {
        iter->second->Release();
    }
    
    iter->second = NULL;
    m_mapTeam.erase( iter );
    return true;
}

template< class T >
bool TeamManager< T >::AddMemberSessionID( unsigned int dwMemberID, unsigned int dwTeamSessionID )
{
    if ( dwMemberID == TeamDefine::ErrorID || dwTeamSessionID == TeamDefine::NoneSessionID )
    { return false; }

    m_mapMemberSessionID[ dwMemberID ] = dwTeamSessionID;
    return true;
}

template< class T >
bool TeamManager< T >::RemoveMemberSessionID( unsigned int dwMemberID )
{
    MapIDIter iter = m_mapMemberSessionID.find( dwMemberID );
    if ( iter == m_mapMemberSessionID.end() )
    { return false; }

    m_mapMemberSessionID.erase( iter );
    return true;
}

template< class T >
unsigned int TeamManager< T >::GetMemberSessionID( unsigned int dwMemberID )
{
    MapIDIter iter = m_mapMemberSessionID.find( dwMemberID );
    if ( iter == m_mapMemberSessionID.end() )
    { return TeamDefine::NoneSessionID; }

    return iter->second;
}

template< class T >
void TeamManager< T >::TeamMemberOutLine( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        pTeam->MemberOutLine( dwMemberID );     
    }
}

template< class T >
void TeamManager< T >::TeamMemberOnLine( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        pTeam->MemberOnLine( dwMemberID );
    }
}

template< class T >
void TeamManager< T >::AddInviteRecord( TeamDefine::TeamInvite& xInvite )
{
    if ( xInvite.szAckName[0] == 0 || xInvite.dwReqID == TeamDefine::ErrorID )
    { return; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( xInvite.szAckName );
    if ( iter == m_mapInviteRecord.end() )
    {
        InviteInfoMap mapInviteInfo;
        mapInviteInfo.insert( make_pair( xInvite.dwReqID, xInvite ) );

        m_mapInviteRecord.insert( make_pair( xInvite.szAckName, mapInviteInfo ) );
    }
    else
    {
        InviteInfoMapIter miter = iter->second.find( xInvite.dwReqID );
        if ( miter == iter->second.end() )
        {
            iter->second.insert( make_pair( xInvite.dwReqID, xInvite ) );
        }
        else
        {
            miter->second = xInvite;
        }
    }
}

template< class T >
void TeamManager< T >::RemoveInviteRecord( std::string strAckName, unsigned int dwReqID )
{
    if ( strAckName.empty() || dwReqID == TeamDefine::ErrorID )
    { return; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( strAckName );
    if ( iter == m_mapInviteRecord.end() )
    { return; }

    InviteInfoMapIter miter = iter->second.find( dwReqID );
    if ( miter == iter->second.end() )
    { return; }

    iter->second.erase( miter );
    if ( iter->second.empty() )
    {
        m_mapInviteRecord.erase( iter );
    }
}

template< class T >
TeamDefine::TeamInvite* TeamManager< T >::GetInviteRecord( std::string strAckName, unsigned int dwReqID )
{
    if ( strAckName.empty() || dwReqID == TeamDefine::ErrorID )
    { return NULL; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( strAckName );
    if ( iter == m_mapInviteRecord.end() )
    { return NULL; }

    InviteInfoMapIter miter = iter->second.find( dwReqID );
    if ( miter == iter->second.end() )
    { return NULL; }

    return &( miter->second );
}

template< class T >
void TeamManager< T >::RunTeamManagerUpdate( unsigned int dwCurrentTime, unsigned char chOperate )
{
    // 检查超时
    RunInviteRecordUpdate( dwCurrentTime );

    if ( !GameTime::IsPassCurrentTime( dwCurrentTime, m_dwNextTeamUpdateTime, TeamDefine::TeamUpdateTime ) )
    { return; }

    for( TeamMapIter iter = m_mapTeam.begin(); iter != m_mapTeam.end(); )
    {
        if ( iter->second == NULL )
        {
            iter = m_mapTeam.erase( iter );
            continue;
        }   

        if ( iter->second->RunTeamUpdate( chOperate ) == TeamDefine::DeleteTeam )
        {
            iter->second->Release();
            iter = m_mapTeam.erase( iter );
        }
        else
        {
            ++iter;
        }
    }

    m_dwNextTeamUpdateTime = dwCurrentTime;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

class ClientPeer;
typedef Team< CenterTeamMember, ClientPeer > CenterTeam;
typedef TeamManager< CenterTeam > CenterTeamManager;
#define theCenterTeamManager CenterTeamManager::Instance()  // CenterServer TeamManager

class GamePlayer;
typedef Team< GameTeamMember, GamePlayer > GameTeam;
typedef TeamManager< GameTeam > GameTeamManager;
#define theGameTeamManager GameTeamManager::Instance()    // GameServer TeamManager

#endif