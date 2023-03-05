#ifndef __RELATIONDEFINE_H__
#define __RELATIONDEFINE_H__

/************************************************************************
                关系结构定义
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
namespace RelationDefine
{
    enum EConstDefine
    {
        // 1级关系, (只能有一种)
        InitRelation = 0,         // 无效值
        TempFriend = 0x1,       // 临时好友
        Friend     = 0x2,       // 好友
        Vendetta   = 0x4,       // 仇人
        BlackList  = 0x8,       // 黑名单( 黑名单可以和仇人并存 )


        // 2级关系( 只能在好友的基础上建立, 删除2级关系,好友关系仍然存在的 )
        Marriage   = 0x100,     // 夫妻
        Teacher    = 0x200,     // 师傅( 出师前 )
        Student    = 0x400,     // 徒弟( 出师前 )
        Brother    = 0x800,     // 结拜

        // 出师以后, 这些是永久的关系
        Master     = 0x1000,    // 徒弟出师以后 师傅的关系
        Prentice   = 0x2000,    // 徒弟出师以后 徒弟的关系

        MaxRelation = 0xFFFF,

        ///////////////////////////////////////////////////////////////////
        UpdateLevel = 1,        // 更新等级
        UpdateHeadPic,          // 更新头像
        UpdateCountry,
        UpdateProfession,
        UpdateSex,
        UpdateName,
        UpdateGuild,
        UpdatePosition,
		UpdateFamily,
        UpdateMasterLevel,
        UpdateMessageRefuse,
        UpdateRewardExp,
        UpdateRewardPrestige,
        UpdateLastStudentTime,
        UpdateLastTeacherTime,
        UpdateSignature,           // 更新签名
        UpdateTitle,
        UpdateMapID,
        UpdateIp,
        ///////////////////////////////////////////////////////////////////
        UpdateAddFriendly = 1,
        UpdateSubFriendly,
        UpdateSetFriendly,
        UpdateRelation,
        UpdateLocked,
        UpdateGroupID,
        UpdateRemark,
        ///////////////////////////////////////////////////////////////////dd

        MaxIpLength         = 16,
		ProvinceLength		= 17,
		CityLength			= 9,
		ProfessionLength	= 17,
		QQLength			= 20,
		MSNLength			= 30,
		IntructionLength	= 85,   

        MaxNameLength   = 33,   // 最大长度
        MaxSignLength   = 21,   // 签名最大长度
        ReMarkLength    = 21,   // 玩家备注的长度
        GroupLength     = 17,   // 分组的长度
        GroupCount      = 6,    // 分组的个数
        InitID          = 0,    // 无效的ID
        NotSendToClient = 0,    // 不发送消息
        SendToClient    = 1,    // 发送消息给客户端

        // 拒绝接受消息设置
        Refuse_None = 0,
        Refuse_Stranger,     // 拒绝陌生人
        Refuse_AllPlayer,    // 拒绝所有人

        RelationInviteTimeOunt = 100000,     // 申请加好友有效时间1分钟
        AutoSaveSpaceTime = 600000,          // 自动保存10分钟一次
        UpdateSpaceTime = 10000,       // 10秒更新一次邀请和申请记录
        ///////////////////////////////////////////////////////////////////////////
        //请求添加好有返回的错误信息
        AddRelationSuccess = 0,       // 添加成功
        CanAddRelation,               // 可以添加关系
        CanNotAddRelation,            // 不能添加此关系
        AlreadyHaveRelation,          // 已经有这种关系
        MustBeFriendRelation,         // 必须是好友关系
        NameError,                    // 要求添加的玩家不存在
        CanNotAddSelf,                // 不能添加自己
        NotOnLine,                    // 玩家不在线     
        RelationFull,                 // 自己该关系已经达到最大数
        TargetRelationFull,           // 自己该关系已经达到最大数
        AddStudentTimeLimit,          // 招收徒弟时间限制   3天只能收1个徒弟
        TargetAddStudentTimeLimit,    // 对方招收徒弟时间限制
        AddTeacherTimeLimit,          // 拜师时间限制       一天只能拜师一次
        TargetAddTeacherTimeLimit,    // 对方拜师时间限制
        StudentCountLimit,            // 招收徒弟数量限制       当前徒弟数量已经达到最大值
        TargetStudentCountLimit,      // 对方招收徒弟数量限制
        TargetNotAgree,               // 对方不同意
        AlreadyHaveTeacher,           // 已经有师傅了
        TargetAlreadyHaveTeacher,     // 对方已经有师傅了
        CanNotReceivePrentice,        // 还没有出师, 不能收徒弟
        TargetCanNotReceivePrentice,  // 对方还没有出师, 不能收徒弟
        AddStudentMustInArea,         // 拜师 收徒 时 必须在附件
        StudentMinLevelLimit,         // 徒弟最低等级限制( 等级在FriendlyConfig 中 )
        TeacherMinLevelLimit,         // 徒弟最高等级限制
        StudentMinLevelSpan,          // 师傅和徒弟最小等级差限制
        MustSameCountry,              // 必须是同一国家才可以添加此关系

        ////////////////////////////////////////////////////////////////////////////////
		// 查询玩家不限制条件
		UNLimitInit	= 0,
		UnLimitSex	= 0x1,	// 不限性别
		UnLimitAge	= 0x2,	// 年龄
		UnLimitPrv	= 0x4,	// 省份
		UnLimitCity	= 0x8,	// 城市
    };

    // 默认分组
    const static char* s_szDefaultGroup = "我的好友";
}
//qq上我的信息
struct PersonalInfo
{
	enum ERight
	{
		ER_Open,		// 完全公开
		ER_Friend,		// 好友可见
		ER_Close,		// 完全保密
	};
	PersonalInfo()
	{ 
		memset( this, 0, sizeof(*this)); 
		uchMonth	= 1;
		uchDay		= 1;
	}

	unsigned char GetPersonalSex() const { return uchSex; }
	unsigned char GetPersonalAge() const { return uchAge; }
	unsigned char GetPersonalMonth() const { return uchMonth; }
	unsigned char GetPersonalDay() const { return uchDay; }
	unsigned char GetShengXiao() const { return uchShengXiao; }
	unsigned char GetStar() const { return uchStar; }
	unsigned char GetPersonalRight() const { return uchRight; }
	const char * GetProvince() const { return szProvince; }
	const char * GetCity() const { return szCity; }
	const char * GetProfession() const { return szProfession; }
	const char * GetQQ() const { return szQQ; }
	const char * GetMSN() const { return szMSN; }
	const char * GetIntroduction() const { return szIntroduction; }
	
	void SetPersonalSex( unsigned char uchValue ) { uchSex = uchValue; }
	void SetPersonalAge( unsigned char uchValue ) { uchAge = uchValue; }
	void SetPersonalMonth( unsigned char uchValue ) { uchMonth = uchValue; }
	void SetPersonalDay( unsigned char uchValue ) { uchDay = uchValue; }
	void SetStar( unsigned char uchValue ) { uchStar = uchValue; }
	void SetShengXiao( unsigned char uchValue ) { uchShengXiao = uchValue; }
	void SetPersonalRight( unsigned char uchValue ) { uchRight = uchValue; }
	void SetProvince( const char * szValue ) { strncpy_s( szProvince, sizeof( szProvince ), szValue, sizeof( szProvince ) - 1 ); }
	void SetCity( const char * szValue ) { strncpy_s( szCity, sizeof( szCity ), szValue, sizeof( szCity ) - 1 ); }
	void SetProfession( const char * szValue ) { strncpy_s( szProfession, sizeof( szProfession ), szValue, sizeof( szProfession ) - 1 ); }
	void SetQQ( const char * szValue ) { strncpy_s( szQQ, sizeof( szQQ ), szValue, sizeof( szQQ ) - 1 ); }
	void SetMSN( const char * szValue ) { strncpy_s( szMSN, sizeof( szMSN ), szValue, sizeof( szMSN ) - 1 ); }
	void SetIntroduction( const char * szValue ) { strncpy_s( szIntroduction, sizeof( szIntroduction ), szValue, sizeof( szIntroduction ) - 1 ); }

	void SetInfo( const PersonalInfo& personInfo )
	{
		SetPersonalSex( personInfo.GetPersonalSex() );
		SetPersonalAge( personInfo.GetPersonalAge() );
		SetPersonalMonth( personInfo.GetPersonalMonth() );
		SetPersonalDay( personInfo.GetPersonalDay() );
		SetStar( personInfo.GetStar() );
		SetShengXiao( personInfo.GetShengXiao() );
		SetPersonalRight( personInfo.GetPersonalRight() );
		SetProvince( personInfo.GetProvince() );
		SetCity( personInfo.GetCity() );
		SetProfession( personInfo.GetProfession() );
		SetQQ( personInfo.GetQQ() );
		SetMSN( personInfo.GetMSN() );
		SetIntroduction( personInfo.GetIntroduction() );
	}

	unsigned char	uchSex;				// 性别 ESexType
	unsigned char	uchAge;				// 年龄
	unsigned char	uchMonth;			// 生日 月
	unsigned char	uchDay;				// 生日 日
	unsigned char	uchStar;			// 星座
	unsigned char	uchShengXiao;		// 生肖
	unsigned char	uchRight;			// 权限
	char	szProvince[RelationDefine::ProvinceLength];			// 省份
	char	szCity[RelationDefine::CityLength];					// 城市
	char	szProfession[RelationDefine::ProfessionLength];		// 职业
	char	szQQ[RelationDefine::QQLength];						// QQ
	char	szMSN[RelationDefine::MSNLength];					// MSN
	char	szIntroduction[RelationDefine::IntructionLength];	// 个人说明
};

// 关系的人物属性
class RelationAttribute
{
public:
    RelationAttribute() : uchCountry( 0 ), nGuildID( 0 ), uchPosition( 0 ), ustLevel( 0 ), nTitleID(0), bOnLine( false )
    {
        memset( szName, 0, sizeof( szName ) );
        memset( szSignature, 0, sizeof( szSignature ) );
        memset( szIp, 0, sizeof( szIp ) );
    }

    unsigned int   GetID() const { return dwDBID; }
    const char*    GetName() const { return szName; }
    unsigned short GetHeadPic() const { return uchHeadPic; }
    unsigned char  GetCountry() const { return uchCountry; }
    unsigned char  GetProfession() const { return uchProfession; }
    unsigned char  GetSex() const { return uchSex; }
    unsigned short GetLevel() const { return ustLevel; }
    unsigned int   GetGuildID() const { return nGuildID; }
    unsigned char  GetPosition() const { return uchPosition; }
    unsigned char  GetMasterLevel() const { return uchMasterLevel; }    
    const char*    GetSignature() const { return szSignature; } 
    const char*    GetIp() const { return szIp; } 
    unsigned short GetTitleID() const { return nTitleID; }
    unsigned int   GetMapID()   const { return nMapID; }
    bool           GetOnLine()  const { return bOnLine; }
	PersonalInfo&  GetPersonalInfo() { return xPersonalInfo; }
	unsigned int   GetFamilyID() const { return nFamilyID; }

    void SetID( unsigned int nValue ) { dwDBID = nValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
    void SetHeadPic( unsigned short ustValue ) { uchHeadPic = ustValue; }
    void SetCountry( unsigned char uchValue ) { uchCountry = uchValue; }
    void SetProfession( unsigned char uchValue ) { uchProfession = uchValue; }
    void SetSex( unsigned char uchValue ) { uchSex = uchValue; }
    void SetLevel( unsigned short ustValue ) { ustLevel = ustValue; }
    void SetGuildID( unsigned int nValue ) { nGuildID = nValue; }
    void SetPosition( unsigned char uchValue ) { uchPosition = uchValue; }
    void SetMasterLevel( unsigned char uchValue ) { uchMasterLevel = uchValue; }
    void SetTitleID( unsigned short ustValue ) { nTitleID = ustValue; }
    void SetSignature( const char* szValue ) { strncpy_s( szSignature, sizeof( szSignature ), szValue, sizeof( szSignature ) - 1 ); }
    void SetIp( const char* szValue ) { strncpy_s( szIp, sizeof( szIp ), szValue, sizeof( szIp ) - 1 ); }
    void SetMapID( unsigned int nValue ) { nMapID = nValue; }
    void SetOnLine( bool bValue ) { bOnLine = bValue; }
	void SetFamilyID( unsigned int nValue ) { nFamilyID = nValue; }

    void SetRelationAttribute( RelationAttribute& xAttribute )
    {
        SetID( xAttribute.GetID() );
        SetName( xAttribute.GetName() );
        SetHeadPic( xAttribute.GetHeadPic() );
        SetCountry( xAttribute.GetCountry() );
        SetProfession( xAttribute.GetProfession() );
        SetSex( xAttribute.GetSex() );
        SetLevel( xAttribute.GetLevel() );
        SetGuildID( xAttribute.GetGuildID() );
        SetPosition( xAttribute.GetPosition() );
        SetMasterLevel( xAttribute.GetMasterLevel() );
        SetTitleID( xAttribute.GetTitleID() );
        SetSignature( xAttribute.GetSignature() );
        SetOnLine( xAttribute.GetOnLine() );
        SetIp( xAttribute.GetIp() );
        SetMapID( xAttribute.GetMapID() );
		SetFamilyID( xAttribute.GetFamilyID() );
		xPersonalInfo.SetInfo( xAttribute.xPersonalInfo );
    }

    
protected:
    unsigned int dwDBID;            // 玩家DBID
    char szName[RelationDefine::MaxNameLength];    // 名字
    unsigned short uchHeadPic;      // 头像ID
    unsigned char  uchCountry;      // 国家
    unsigned char  uchProfession;   // 职业
    unsigned char  uchSex;          // 性别
    unsigned short ustLevel;        // 等级
    unsigned int   nGuildID;        // 当前所在的公会ID
    unsigned char  uchPosition;     // 公会职位( 定义在CountryDefine.h的title中
	unsigned int   nFamilyID;		// 当前所在的家族ID
    unsigned char  uchMasterLevel;  // 师傅威望等级
    unsigned short nTitleID;        // 称号
    char szSignature[ RelationDefine::MaxSignLength ];  // 个性签名

    bool bOnLine;                   // 是否在线 ( 这个不用入库 )
    unsigned int   nMapID;          // 当前地图 ( 这个不用入库 )
    char szIp[RelationDefine::MaxIpLength];         // IP地址   ( 这个不用入库 )

	// 个人资料
	PersonalInfo xPersonalInfo;
};

// 关系的关系属性
class RelationData 
{
public:
	RelationData()
	{
		stRelation = 0;
		nFriendly  = 0;
        bLocked    = false;
        uchGroupID = 0;

        memset( szRemark, 0, sizeof( szRemark ) );
    }

    unsigned short GetRelation() const { return stRelation; }
    unsigned int   GetFriendly() const { return nFriendly; }    
    bool           GetLocked() const   { return bLocked; }
    unsigned char  GetGroupID() const  { return uchGroupID; }
    const char*    GetRemark() const   { return szRemark; }

    void SetRelation( unsigned short stValue ) { stRelation = stValue; }
    void SetFriendly( unsigned int nValue ) { nFriendly = nValue; }
    void SetLocked( bool bValue ) { bLocked = bValue; }
    void SetGroupID( unsigned char uchValue ) { uchGroupID = uchValue; }
    void SetRemark( const char* szValue ) { strncpy_s( szRemark, sizeof( szRemark ), szValue, sizeof( szRemark ) - 1 ); }
    void AddFriendly( unsigned int nValue ) { nFriendly += nValue; }
    void SubFriendly( unsigned int nValue )   // 减少好友度  
    { 
        if ( nValue > GetFriendly() )
        { nValue = GetFriendly(); }

        nFriendly -= nValue;
    }  

    void AddRelation( unsigned short stValue );                                                     // 添加某种关系
    void RemoveRelation( unsigned short stValue ) { stRelation &= ~stValue; }                       // 删除某个关系
    bool HaveRelation() const { return ( stRelation & 0xFFFF ) != RelationDefine::InitRelation; }   // 是否存在关系
    bool HaveRelation( unsigned short stValue ) { return (stRelation & stValue) != 0; }             // 是否有某个关系
    unsigned short GetHigherRelation() const { return ( stRelation & 0xFFF0 ); }                    // 获得2级关系
    bool HaveHigherRelation() { return GetHigherRelation() != RelationDefine::InitRelation; }       // 是否有2级关系

    static bool HaveRelation( unsigned short stValue, unsigned short stRelation ) { return ( stValue & stRelation ) != 0; } // stValue关系中是否存在stRelaiton关系
    static bool IsHigherRelation( unsigned short stRelation ); // 判断此关系是否是2级关系

    void InitRelationData( RelationData& xData )
    {
        SetRelation( xData.GetRelation() );
        SetFriendly( xData.GetFriendly() );
        SetGroupID( xData.GetGroupID() );
        SetLocked( xData.GetLocked() );
        SetRemark( xData.GetRemark() );
    }
    
protected:
    unsigned short stRelation;                     // 关系
    unsigned int nFriendly;                        // 好友度
    bool bLocked;                                  // 是否锁定此玩家
    unsigned char uchGroupID;                      // 好友分组ID ( 0 就是默认分组 )
    char szRemark[ RelationDefine::ReMarkLength ]; // 好友备注
};

inline void RelationData::AddRelation( unsigned short stValue )
{
    RemoveRelation( RelationDefine::TempFriend );   // 先清除掉临时关系

    switch ( stValue )
    {
    case RelationDefine::Master:       // 出师后的师傅
        RemoveRelation( RelationDefine::Teacher );
        break;
    case RelationDefine::Prentice:     // 出师后的徒弟
        RemoveRelation( RelationDefine::Student );
        break;
    case RelationDefine::Friend:        // 好友
        RemoveRelation( RelationDefine::BlackList );
		RemoveRelation( RelationDefine::Vendetta );
        break;
    case RelationDefine::BlackList:     // 黑名单
        RemoveRelation( RelationDefine::Friend );
	case RelationDefine::Vendetta:		// 仇人
		RemoveRelation( RelationDefine::Friend );
        break;
    default:
        break;
    }
    
    stRelation |= stValue;
}

inline bool RelationData::IsHigherRelation( unsigned short stRelation )
{
    switch ( stRelation )
    {
        case RelationDefine::Marriage:
        case RelationDefine::Brother:
        case RelationDefine::Teacher:
        case RelationDefine::Student:
            return true;
        default:
            break;
    }

    return false;
}

// 发送给客户端的信息
class RelationDataToClient : public RelationAttribute, public RelationData
{
public:
    RelationDataToClient() : RelationData(), RelationAttribute()
    {
    }
};


// 服务端结构定义
class RelationDataToServer : public RelationData
{
public:
    RelationDataToServer() : RelationData() {}

    unsigned int GetID() const { return dwDBID; }
    void SetID( unsigned int nValue ) { dwDBID = nValue; }

protected:
    unsigned int dwDBID;
};

// 数据库消息结构定义
class RelationDataToDatabase
{
public:
    unsigned int nPlayerID;
    RelationDataToServer xDataToServer;
};

class RelationGroup
{
public:
    RelationGroup()
    {
        memset( szName, 0, sizeof( szName ) );
    }
    
    const char* GetName() const { return szName; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
    
    bool IsEmpty() const { return szName[0] == 0; }
    void ClearGroup() { memset( szName, 0, sizeof( szName ) ); }

protected:
    char szName[ RelationDefine::GroupLength ];
};

// 数据库消息结构定义
class RelationAttributeToServer : public RelationAttribute
{
public:
    RelationAttributeToServer() : RelationAttribute(), ustMessageRefuse( 0 ), nRewardExp( 0 ), nRewardPrestige( 0 ), n64LastAddStudentTime( 0 ), n64LastAddTeacherTime( 0 )
    {
    }

    unsigned short GetMessageRefuse() const { return ustMessageRefuse; }
    unsigned int GetRewardExp() const { return nRewardExp; }
    unsigned int GetRewardPrestige() const { return nRewardPrestige; }
    __int64 GetLastAddStudentTime() const { return n64LastAddStudentTime; }
    __int64 GetLastAddTeacherTime() const { return n64LastAddTeacherTime; }	
	
    void SetMessageRefuse( unsigned short ustValue ) { ustMessageRefuse = ustValue; }
    void SetRewardExp( unsigned int nValue ) { nRewardExp = nValue; }
    void SetRewardPrestige( unsigned int nValue ) { nRewardPrestige = nValue; }
    void SetLastAddStudentTime( __int64 n64Value ) { n64LastAddStudentTime = n64Value; }
    void SetLastAddTeacherTime( __int64 n64Value ) { n64LastAddTeacherTime = n64Value; }
	    
    const char* GetGroupName( unsigned int uchGroupID )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return ""; }

        return xGroup[uchGroupID].GetName();
    }

    void SetGroupName( unsigned int uchGroupID, const char* szValue )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return; }

        xGroup[uchGroupID].SetName( szValue );
    }

    bool IsEmptyGroup( unsigned char uchGroupID )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return true; }

        return xGroup[ uchGroupID ].IsEmpty();
    }
	// 拿RelationAttributeToServer初始化这个关系信息类
    void SetRelationAttributeToServer( RelationAttributeToServer& xAttribute )
    {
        SetRelationAttribute( xAttribute );

        SetMessageRefuse( xAttribute.GetMessageRefuse() );
        SetRewardExp( xAttribute.GetRewardExp() );
        SetRewardPrestige( xAttribute.GetRewardPrestige() );
        SetLastAddStudentTime( xAttribute.GetLastAddStudentTime() );
        SetLastAddTeacherTime( xAttribute.GetLastAddTeacherTime() );
        memcpy_s( xGroup, sizeof( xGroup ), xAttribute.xGroup, sizeof( xAttribute.xGroup ) );
    }

protected:
    unsigned short ustMessageRefuse;      // 拒绝接受消息设置
    unsigned int nRewardExp;              // 徒弟, 以及徒弟的徒弟升级, 奖励的经验 ( 不在线时, 存入数据库 )
    unsigned int nRewardPrestige;         // 徒弟, 以及徒弟的徒弟升级, 奖励的威望 ( 不在线时, 存入数据库 ) 
    __int64 n64LastAddStudentTime;        // 最后一次收徒弟的时间
    __int64 n64LastAddTeacherTime;        // 最后一次拜师傅的时间
    RelationGroup xGroup[ RelationDefine::GroupCount ]; // 好友的分组信息
};

#endif