#ifndef __GUILDEFINE_H__
#define __GUILDEFINE_H__

/************************************************************************
                公会结构定义
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
namespace GuildDefine
{
    enum EConstDefine
    {
        // 帮派的各种权限....
        Right_None     = 0,
        Right_View     = 0x1,       // 查看权
        Right_Donate   = 0x2,       // 发起捐献权
        Right_Collect  = 0x4,       // 募集权       
        Right_Build    = 0x8,       // 帮贡建设
        Right_Leave    = 0x10,      // 离开帮派
        Right_Delate   = 0x20,      // 弹劾权
        Right_Invite   = 0x40,      // 邀请权
        Right_Transfer = 0x80,      // 禅让职位
        Right_Assign   = 0x100,     // 授予职位
        Right_Resign   = 0x200,     // 辞去职位
        Right_Notice   = 0x400,     // 修改公告
        Right_Kick     = 0x800,     // 踢出帮派
        Right_League   = 0x1000,    // 帮派联盟
        Right_Family   = 0x2000,    // 家族权限( 包括 家族改名.等一系列 )
        Right_LevelUp  = 0x4000,    // 家族升级
        Right_Release  = 0x8000,    // 任务发布权
        Right_Shop     = 0x10000,   // 帮派商店权限
        Right_Convene  = 0x20000,   // 帮派召集权
		Right_InFamily = 0x40000,	// 转入分堂
		Right_OutFamily = 0x80000,	// 本堂成员转出分堂
		Right_OutFamilyOther = 0x100000,	// 非本堂成员转出分堂
		Right_Aim	   = 0x200000,	// 修改宗旨

        // 普通帮众权限
        Right_Member = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Leave,
        // 家族长权限
        Right_FamilyMaster = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Transfer | Right_Resign | Right_InFamily | Right_OutFamily,
        // 副帮主权限
        Right_ViceMaster = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Invite /*| Right_Transfer*/ | Right_Resign | Right_Convene | Right_Kick | Right_InFamily | Right_OutFamily | Right_OutFamilyOther,
        // 帮主的权限
        Right_Master = Right_View | Right_Donate | Right_Collect | Right_Build | Right_Invite | Right_Transfer | Right_Notice | Right_Kick | Right_League | Right_Assign | Right_Family | Right_LevelUp | Right_Release | Right_Shop | Right_Convene | Right_InFamily | Right_OutFamily | Right_OutFamilyOther | Right_Aim,

        // 帮派的职位定义
        Position_None = 0,         // 
        Position_Member,           // 普通帮众
        Position_FamilyMaster,     // 家族长
        Position_ViceMaster,       // 副帮主
        Position_Master,           // 帮主

        ///////////////////////////////////////////////////////////////////
        MaxCreateLength = 17,      // 创建公会的最大长度
        MaxNameLength = 33,        // 名字最大长度
        MaxNoticeLength = 61,      // 公告最大长度
		MaxAimLength = 61,		   // 宗旨最大长度
        MaxFamilyLength = 17,      // 家族名字最大长度
        MaxFamilyCount  = 5,       // 最大家族个数
        MaxGuildVarCount = 500,    // 帮会记数变量的个数
        InitID = 0,                // 初始ID

        UpdateSpaceTime = 10000,   // 10秒更新一次
        SaveSpaveTime   = 300000,  // 10分钟数据保存一次
        InviteKeepTime  = 90000,   // 邀请和申请的保持时间
        LoadSpaceTime   = 1200000, // 20分钟请求一次
        DelateKeepTime  = 180000,  // 弹劾3分钟内有效
        DonateKeepTime  = 300000,  // 捐献5分钟内有效
        ReleaseKeepTime = 7200000, // 任务发布持续时间 2小时
        ConveneKeepTime = 300000,  // 帮派召集5分钟内有效
        //////////////////////////////////////////////////////////////
        UpdateNormal = 1,   // 
        UpdateDiaband,      // 解散
        ////////////////////////////////////////////////////////////////
        // 成员信息更新标志
        UpdateMemberOnLine = 1,     // 更新在线
        UpdateMemberLevel,          // 更新等级
        UpdateMemberPosition,       // 更新职位
        UpdateMemberFamily,         // 更新家族
        UpdateMemberActivity,       // 更新活跃度
        UpdateMemberOffer,          // 更新帮贡
        UpdateMemberProfession,     // 更新职业
        UpdateMemberExp,            // 更新玩家经验( 客户端不用处理 )
		UpdateMemberCampBattleValue,// 更新玩家的战场权限

        // 帮派信息更新标记 
        UpdateGuildLevel = 1,       // 更新帮派等级
        UpdateGuildMoney,           // 更新帮派金钱
        UpdateGuildExp,             // 更新帮派经验
        UpdateGuildMission,         // 更新帮派使命点
        UpdateGuildMaster,          // 更新帮派帮主
        UpdateGuildVar,             // 更新帮派记数变量
        UpdateGuildDonate,          // 更新帮派捐献的金钱( 客户端不用处理 )
        UpdateGuildShopLevel,       // 更新帮派商店等级
        UpdateGuildDisbandTime,     // 更新帮派解散时间
        UpdateGuildSalary,          // 更新帮派津贴
		UpdateGuildMissionCount,	// 更新帮派
		UpdateGuildBattleSum,		//
		UpdateGuildChangeName,		//
		UpdateGuildCampBattlePoint, // 更新帮派战场点数

        ////////////////////////////////////////////////////////////////
        OperateAdd = 1,             // +
        OperateSub,                 // -
        OperateSet,                 // =
        ////////////////////////////////////////////////////////////////

        DecodeFieldBufferSize = 1024 * 10,
        UnZipTempBufferSize   = 1024 * 20,
        ZipTempBufferSize     = 1024 * 40,
        EncodeFieldBufferSize = 1024 * 10,
		PlayerLvIsThirty = 30,		// 玩家到达30级，通知给所有帮派的帮主
		MissionFirst	 = 1,		// 使命点不足，第一次
		MissionSecond	 = 2,		// 使命点不足，第二次
		MissionThird	 = 3,		// 使命点不足，第三次

		CampBattleCountry  = 1,
		CampBattleGuild    = 2,
		CampBattleGuildUnion = 4,
		GameBattleGuildGeneral = 8,
    };

    static unsigned int GetRightByPositon( unsigned char uchPositon )
    {
        unsigned int nRight = Position_None;
        switch ( uchPositon )
        {
        case Position_Member:
            nRight = Right_Member;
        	break;
        case Position_FamilyMaster:
            nRight = Right_FamilyMaster;
            break;
        case Position_ViceMaster:
            nRight = Right_ViceMaster;
            break;
        case Position_Master:
            nRight = Right_Master;
            break;
        default:
            break;
        }

        return nRight;
    }
}

// 家族信息( 和武神的堂一样 )
class FamilyData
{
public:
    FamilyData()
    {
        memset( m_szName, 0, sizeof( m_szName ) );
    }

    const char* GetName() const { return m_szName; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }

    bool IsEmpty() const { return m_szName[0] == 0; }

protected:
    char m_szName[ GuildDefine::MaxFamilyLength ];      // 家族名字
};

class GuildData
{
public:
    GuildData() : m_nID( GuildDefine::InitID ), m_uchCountry( 0 ), m_uchLevel( 0 ), m_nMasterID( GuildDefine::InitID ), m_nMoney( 0 ), m_nExp( 0 ), m_nMission( 0 ), m_n64CreateTime( 0 ),
                    m_ustReleaseQuest( 0 ), m_n64ReleaseTime( 0 ), m_nShopLevel( 0 ), m_nSalary( 0 ), m_nMissionCount( 0 ),m_BattleSum(0),m_ChangeName(false),m_GuildCampBattlePoint(0)
    {
        memset( m_szName, 0, sizeof( m_szName ) );
        memset( m_szNotice, 0, sizeof( m_szNotice ) );
		memset( m_szAim, 0, sizeof( m_szAim ) );
    }

    unsigned int GetID() const { return m_nID; }
    unsigned char GetLevel() const { return m_uchLevel; }
    unsigned int GetCountry() const { return m_uchCountry; }
    const char* GetName() const { return m_szName; }
    const char* GetNotice() const { return m_szNotice; }
	const char* GetAim() const { return m_szAim; }
    unsigned int GetMasterID() const { return m_nMasterID; }
    unsigned int GetShopLevel() const { return m_nShopLevel; }
    unsigned int GetMoney() const { return m_nMoney; }
    unsigned int GetExp() const { return m_nExp; }
    unsigned int GetMission() const { return m_nMission; }
    unsigned int GetSalary() const { return m_nSalary; }
	unsigned int GetMissionCount() const { return m_nMissionCount; }
    __int64 GetCreateTime() const { return m_n64CreateTime; }
    unsigned short GetReleaseQuest() const { return m_ustReleaseQuest; }
    __int64 GetReleaseTime() const { return m_n64ReleaseTime; }
	unsigned int GetStrength() const {return m_nGuildStrength;}
	unsigned int GetBattleSum() const {return m_BattleSum;}
	bool GetIsCanChangeName() const{return m_ChangeName;}
	unsigned int GetGuildCampBattlePoint() const{return m_GuildCampBattlePoint;}

    void SetID( unsigned int nValue ) { m_nID = nValue; }
    void SetLevel( unsigned char uchValue ) { m_uchLevel = uchValue; }
    void SetCountry( unsigned char uchValue ) { m_uchCountry = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }
    void SetNotice( const char* szValue ) { strncpy_s( m_szNotice, sizeof( m_szNotice ), szValue, sizeof( m_szNotice ) - 1 ); }
	void SetAim( const char* szValue ) { strncpy_s( m_szAim, sizeof( m_szAim ), szValue, sizeof( m_szAim ) - 1 ); }
    void SetMasterID( unsigned int nValue ) { m_nMasterID = nValue; }
    void SetShopLevel( unsigned int nValue ) { m_nShopLevel = nValue; }
    void SetMoney( unsigned int nValue ) { m_nMoney = nValue; }
    void SetExp( unsigned int nValue ) { m_nExp = nValue; }
    void SetMission( unsigned int nValue ) { m_nMission = nValue; }
    void SetSalary( unsigned int nValue ) { m_nSalary = nValue; }
    void SetCreateTime( __int64 n64Value ) { m_n64CreateTime = n64Value; }
    void SetReleaseQuest( unsigned short ustValue ) { m_ustReleaseQuest = ustValue; }
    void SetReleaseTime( __int64 n64Value ) { m_n64ReleaseTime = n64Value; }
	void SetMissionCount( unsigned int nCount ) { m_nMissionCount = nCount; }
	void SetStrength(unsigned int Strength){m_nGuildStrength = Strength;}
	void SetBattleSum(unsigned int BattleSum){m_BattleSum = BattleSum;}
	void SetChangeName(bool IsCan){m_ChangeName = IsCan;}
	void SetGuildCampBattlePoint(unsigned int Point){m_GuildCampBattlePoint = Point;}

    // 传入家族ID ( 1- 5 )
    FamilyData* GetFamily( unsigned char uchID );
    // 获得家族名字
    const char* GetFamilyName( unsigned char uchID );
    // 设置家族名字
    void SetFamilyName( unsigned char uchID, const char* szName );
    // 添加一个家族, 返回ID
    unsigned char AddFamily( const char* szName );
    // 获得家族ID
    unsigned char GetFamilyID( const char* szName ) const;
    // 获得家族个数
    unsigned char GetFamliyCount() const;
    // 获得一个空的家族
    unsigned char GetEmptyFamilyID() const;
    // 是否有家族
    bool HaveFamily( unsigned char uchID );

    // 设置帮派数据
    void SetGuildData( GuildData& xData );

    // 获得帮派数据
    void GetGuildData( GuildData& xData ) const;

    // 设置商店等级激活状态
    void SetShopActive( unsigned char uchLevel );

    // 判断商店等级是否激活
    bool CheckShopActive( unsigned char uchLevel ) const;

protected:
    unsigned int m_nID;                                 // 帮派ID
    unsigned char m_uchLevel;                           // 帮派等级
    unsigned char m_uchCountry;                         // 国家
    char m_szName[ GuildDefine::MaxNameLength ];        // 帮派名字
    char m_szNotice[ GuildDefine::MaxNoticeLength ];    // 帮派公告
	char m_szAim[ GuildDefine::MaxAimLength ];			// 帮派宗旨
    unsigned int m_nMasterID;                           // 帮主ID
    unsigned int m_nShopLevel;                          // 帮派商店等级
    unsigned int m_nMoney;                              // 帮派资金
    unsigned int m_nExp;                                // 帮派经验
    unsigned int m_nMission;                            // 帮派使命点
	unsigned int m_nMissionCount;						// 帮派使命点不足 计数 luo.qin 4.21
    unsigned int m_nSalary;                             // 帮派津贴
    __int64 m_n64CreateTime;                            // 创建时间
    FamilyData xFamily[ GuildDefine::MaxFamilyCount ];  // 家族信息
    unsigned short m_ustReleaseQuest;                   // 发布的任务
    __int64 m_n64ReleaseTime;                           // 发布任务的时间
	unsigned int m_nGuildStrength;						// 只是用来保存到数据库中
	unsigned int m_BattleSum;							// 经历公会战场的轮数
	bool		 m_ChangeName;							// 是否可以改名
	unsigned int m_GuildCampBattlePoint;				// 血战沙场的点数
    // 帮会旗帜..
};

// 服务器使用
class GuildDataToServer : public GuildData
{
public:
    GuildDataToServer() : GuildData(), m_n64DisbandTime( 0 ), m_nDonateMoney( 0 )
    {
        memset( m_stGuildVars, 0 , sizeof( m_stGuildVars ) );
    }

    __int64 GetDisbandTime() const { return m_n64DisbandTime; }
    unsigned int GetDonateMoney() const { return m_nDonateMoney; }
    
    void SetDisbandTime( __int64 n64Value ) { m_n64DisbandTime = n64Value; }
    void SetDonateMoney( unsigned int nValue ) { m_nDonateMoney = nValue; }

    short* GetVarAddress() { return m_stGuildVars; }
    void InitGuildVar( short* stValue, int nCount );
    short GetGuildVar( unsigned short ustIndex ) const;
    void SetGuildVar( unsigned short ustIndex, short stValue );

    // 设置帮派数据
    void SetGuildDataToServer( GuildDataToServer& xData );
    // 获得帮派数据
    void GetGuildDataToServer( GuildDataToServer& xData );

protected:
    short m_stGuildVars[ GuildDefine::MaxGuildVarCount ]; // 公会记数变量
    __int64 m_n64DisbandTime;                             // 满足解散条件的时间( == 0 没有设置时间 ) 

    unsigned int m_nDonateMoney;                          // 累计捐献的帮会金钱
};

// 帮会成员数据
class GuildMember
{
public:
    GuildMember() : m_nID( GuildDefine::InitID ), m_ustLevel( 0 ), m_uchProfession( 0 ), m_nOffer( 0 ), m_ustActivity( 0 ), m_nGuildID( 0 ), m_uchPosition( 0 ), m_uchFamilyID( 0 ), m_bOnLine( false ),
                    m_ustLastActivity( 0 ),m_CampBattleValue(0),LastOnLineTime(0)
    {
        memset( m_szName, 0, sizeof( m_szName ) );
    }

    unsigned int GetID() const { return m_nID; }
    const char* GetName() const { return m_szName; }
    unsigned short GetLevel() const { return m_ustLevel; }
    unsigned char GetProfession() const { return m_uchProfession; }
    unsigned int GetOffer() const { return m_nOffer; }
    unsigned short GetActivity() const { return m_ustActivity; }
    unsigned short GetLastActivity() const { return m_ustLastActivity; }
    unsigned int GetGuildID() const { return m_nGuildID; }
    unsigned char GetPosition() const { return m_uchPosition; }
    unsigned char GetFamilyID() const { return m_uchFamilyID; }
    bool GetOnLine() const { return m_bOnLine; }
	unsigned int GetCampBattleValue() const {return m_CampBattleValue;}
	__int64 GetOnLineTime() const {return LastOnLineTime;}

    void SetID( unsigned int nValue ) { m_nID = nValue; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }
    void SetLevel( unsigned short ustValue ) { m_ustLevel = ustValue; }
    void SetProfession( unsigned char uchValue ) { m_uchProfession = uchValue; }
    void SetOffer( unsigned int nValue ) { m_nOffer = nValue; }
    void SetActivity( unsigned short ustValue ) { m_ustActivity = ustValue; }
    void SetLastActivity( unsigned short ustValue ) { m_ustLastActivity = ustValue; }
    void SetGuildID( unsigned int nValue ) { m_nGuildID = nValue; }
    void SetPosition( unsigned char uchValue ) { m_uchPosition = uchValue; }
    void SetFamilyID( unsigned char uchValue ) { m_uchFamilyID = uchValue; }
    void SetOnLine( bool bValue ) { m_bOnLine = bValue; }
	void SetCampBattleValue(unsigned int Value){m_CampBattleValue = Value;}
	void SetOnLineTime(__int64 Time){LastOnLineTime = Time;}
protected:
    unsigned int m_nID;                             // ID
    char m_szName[ GuildDefine::MaxNameLength ];    // 名字
    unsigned short m_ustLevel;                      // 等级
    unsigned char m_uchProfession;                  // 职业  
    unsigned int m_nOffer;                          // 帮贡
    unsigned short m_ustActivity;                   // 活跃度( 本周 )
    unsigned short m_ustLastActivity;               // 活跃度( 上周 )
    unsigned int m_nGuildID;                        // 帮派ID
    unsigned char m_uchPosition;                    // 帮派职位
    unsigned char m_uchFamilyID;                    // 家族ID
    bool m_bOnLine;                                 // 是否在线
	unsigned int m_CampBattleValue;					// 战场的值 标记在公会参与战场的时候会员可以进入那些战场
	__int64 LastOnLineTime;							// 最后在线时间 记录玩家上次上线的时间
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
inline FamilyData* GuildData::GetFamily( unsigned char uchID )
{
    if ( uchID == GuildDefine::InitID || uchID > GuildDefine::MaxFamilyCount )
    { return NULL; }

    return &( xFamily[ uchID - 1 ] );
}

inline const char* GuildData::GetFamilyName( unsigned char uchID )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return ""; }

    return pFamily->GetName();
}

inline void GuildData::SetFamilyName( unsigned char uchID, const char* szName )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return; }

    pFamily->SetName( szName );
}

inline unsigned char GuildData::AddFamily( const char* szName )
{
    if ( szName == NULL || szName[0] == 0 )
    { return GuildDefine::InitID; }

    unsigned char uchIndex = GuildDefine::InitID;
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( !xFamily[i].IsEmpty() )
        { continue; }

        xFamily[i].SetName( szName );
        uchIndex = i + 1;
        break;
    }

    return uchIndex;
}

inline unsigned char GuildData::GetFamilyID( const char* szName ) const
{
    if ( szName == NULL || szName[0] == 0 )
    { return GuildDefine::InitID; }

    unsigned char uchIndex = GuildDefine::InitID;

    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { continue; }

        if ( strcmp( xFamily[i].GetName(), szName ) != 0 )
        { continue; }

        uchIndex = i + 1;
        break;
    }

    return uchIndex;
}

inline unsigned char GuildData::GetFamliyCount() const
{
    unsigned char uchCount = 0;
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { continue; }
        
        ++uchCount;
    }

    return uchCount;
}

inline unsigned char GuildData::GetEmptyFamilyID() const
{
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { 
            return i + 1;
        }
    }

    return GuildDefine::InitID;
}

inline bool GuildData::HaveFamily( unsigned char uchID )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return false; }

    return !pFamily->IsEmpty();
}

inline void GuildDataToServer::InitGuildVar( short* stValue, int nCount )
{
    memcpy_s( m_stGuildVars, sizeof( m_stGuildVars ), stValue, nCount * sizeof( short ) );
}

inline short GuildDataToServer::GetGuildVar( unsigned short ustIndex ) const
{
    if ( ustIndex >= GuildDefine::MaxGuildVarCount )
    { return 0; }

    return m_stGuildVars[ustIndex];
}

inline void GuildDataToServer::SetGuildVar( unsigned short ustIndex, short stValue )
{
    if ( ustIndex >= GuildDefine::MaxGuildVarCount )
    { return; }

    m_stGuildVars[ustIndex] = stValue;
}


inline void GuildData::SetGuildData( GuildData& xData )
{
    SetID( xData.GetID() );
    SetLevel( xData.GetLevel() );
    SetName( xData.GetName() );
    SetCountry( xData.GetCountry() );
    SetNotice( xData.GetNotice() );
    SetMasterID( xData.GetMasterID() );
    SetShopLevel( xData.GetShopLevel() );
    SetMoney( xData.GetMoney() );
    SetExp( xData.GetExp() );
    SetMission( xData.GetMission() );
    SetSalary( xData.GetSalary() );
    SetCreateTime( xData.GetCreateTime() );
	SetBattleSum(xData.GetBattleSum());
	SetChangeName(xData.GetIsCanChangeName());
    memcpy_s( xFamily, sizeof( xFamily ), xData.xFamily, sizeof( xFamily ) );
    SetReleaseQuest( xData.GetReleaseQuest() );
    SetReleaseTime( xData.GetReleaseTime() );
	SetGuildCampBattlePoint(xData.GetGuildCampBattlePoint());
}

inline void GuildData::GetGuildData( GuildData& xData ) const
{
    xData.SetID( GetID() );
    xData.SetLevel( GetLevel() );
    xData.SetCountry( GetCountry() );
    xData.SetName( GetName() );
    xData.SetNotice( GetNotice() );
    xData.SetMasterID( GetMasterID() );
    xData.SetShopLevel( GetShopLevel() );
    xData.SetMoney( GetMoney() );
    xData.SetExp( GetExp() );
    xData.SetMission( GetMission() );
    xData.SetSalary( GetSalary() );
    xData.SetCreateTime( GetCreateTime() );
	xData.SetBattleSum(GetBattleSum());
	xData.SetChangeName(GetIsCanChangeName());
    memcpy_s( xData.xFamily, sizeof( xFamily ), xFamily, sizeof( xFamily ) );
    xData.SetReleaseQuest( GetReleaseQuest() );
    xData.SetReleaseTime( GetReleaseTime() );
	xData.SetGuildCampBattlePoint(GetGuildCampBattlePoint());
}


inline void GuildData::SetShopActive( unsigned char uchLevel )
{
    m_nShopLevel |= ( 1 << uchLevel );
}

inline bool GuildData::CheckShopActive( unsigned char uchLevel ) const
{
    return ( m_nShopLevel & ( 1 << uchLevel ) ) != 0;
}

inline void GuildDataToServer::SetGuildDataToServer( GuildDataToServer& xData )
{
    SetGuildData( xData );

    SetDisbandTime( xData.GetDisbandTime() );
    memcpy_s( m_stGuildVars, sizeof( m_stGuildVars ), xData.m_stGuildVars, sizeof( m_stGuildVars ) );
}

inline void GuildDataToServer::GetGuildDataToServer( GuildDataToServer& xData )
{
    GetGuildData( xData );

    xData.SetDisbandTime( GetDisbandTime() );
    memcpy_s( xData.m_stGuildVars, sizeof( m_stGuildVars ), m_stGuildVars, sizeof( m_stGuildVars ) );
}

class GuildInvite
{
public:
    GuildInvite() : m_nPlayerID( 0 ), m_nTargetID( 0 ), m_nInviteTime( 0 ) {}

    unsigned int GetPlayerID() const { return m_nPlayerID; }
    unsigned int GetTargetID() const { return m_nTargetID; }
    unsigned int GetInviteTime() const { return m_nInviteTime; }

    void SetPlayerID( unsigned int nValue ) { m_nPlayerID = nValue; }
    void SetTargetID( unsigned int nValue ) { m_nTargetID = nValue; }
    void SetInviteTime( unsigned int nValue ) { m_nInviteTime = nValue; }

protected:
    unsigned int m_nPlayerID;     // 邀请人
    unsigned int m_nTargetID;     // 要进入帮派的目标
    unsigned int m_nInviteTime;   // 邀请时间
};

class GuildRequest
{
public:
    const GuildMember& GetMember() const { return m_xMember; }
    unsigned int GetRequestTime() const { return m_nRequestTime; }

    void SetMember( GuildMember& xMember ) { m_xMember = xMember; }
    void SetRequestTime( unsigned int nValue ){ m_nRequestTime = nValue; }

protected:
    GuildMember m_xMember;         // 申请的玩家
    unsigned int m_nRequestTime;   // 申请时间
};

// 客户端帮派列表信息
class GuildListInfo
{
public:
    unsigned int GetID() const { return nGuildID; }
	unsigned int GetMemberNum() const { return nMemberNum; }
    unsigned char GetCountry() const { return uchCountry; }
    unsigned char GetLevel() const { return uchLevel; }
    const char* GetName() const { return szName; }
	const char* GetMasterName() const { return szMasterName; }

    void SetID( unsigned int nValue ) { nGuildID = nValue; }
	void SetMemberNum( unsigned int nMemNum ) { nMemberNum = nMemNum; }
    void SetCountry( unsigned char uchValue ) { uchCountry = uchValue; }
    void SetLevel( unsigned char uchValue ) { uchLevel = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
	void SetMasterName (const char* szValue ) { strncpy_s( szMasterName, sizeof( szMasterName ), szValue, sizeof( szMasterName) - 1 );}

protected:
    unsigned char uchCountry;
    unsigned char uchLevel;
    unsigned int nGuildID;
	unsigned int nMemberNum;
	char szMasterName[GuildDefine::MaxNameLength];
    char szName[ GuildDefine::MaxNameLength ];
};

#endif