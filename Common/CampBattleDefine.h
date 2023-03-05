#ifndef __CAMPDEFINE_H__
#define __CAMPDEFINE_H__

namespace CampDefine
{
    enum EConstDefine
    {
        // 战场类型
        BattleTypeNone = 0,
        BattleTypeGuild,     // 帮派争夺战
        BattleTypeKing,      // 国王争夺战
        BattleTypeDragon,    // 青龙争夺战
        BattleTypeRosefinch, // 朱雀争夺战
		BattleTypeGuildUnion,//公会联合站
        BattleTypeMax,       // 最大值

        ////////////////////////////////////////////////////////////////////
        // 所有阵营都区分开, 为了在不同的阵营战场中区分
        NoneCamp     = 0,       // 无阵营
        BaseCampRed  = 1,       // 基本红方阵营
        BaseCampBlue = 2,       // 基本蓝方阵营

        // 帮派争夺战阵营
        GuildCampRed,       // 红方
        GuildCampBlue,      // 蓝方

        // 国王争夺战
        KingCampRed,       // 红方
        KingCampBlue,      // 蓝方

        // 青龙争夺战
        DragonCampRed,       // 红方
        DragonCampBlue,      // 蓝方

        // 朱雀争夺战
        RosefinchCampRed,       // 红方
        RosefinchCampBlue,      // 蓝方

		GuildUnionRed,
		GuildUnionBlue,

        ////////////////////////////////////////////////////////////////
        NameLength = 33,            // 玩家名字长度
        ReleaseSapceTime = 60000,   // 1分钟后战场销毁
        UpdateSpaceTime = 5000,     // 5秒刷新一次

        DefaultReliveIndex = 0,     // 默认重生点
        RedReliveIndex = 2,         // 红方复活点
        BlueReliveIndex = 3,        // 蓝方复活点
        ////////////////////////////////////////////////////////////////
        // 战场状态
        StatusInit = 0,     // 初始状态
        StatusSignUp,       // 报名状态
        StatusPrepare,      // 准备状态
        StatusEnter,        // 进入战场状态
        StatusFight,        // 战场战斗状态
        StatusEnd,          // 结束状态
        StatusRelease,      // 战场销毁, 释放资源( 服务器使用 )
        ////////////////////////////////////////////////////////////////////
        // 报名结果返回
        SignUp_Success = 0,         // 成功
        SignUp_NotSignUpStatus,     // 不是报名时间
        SignUp_MustGuildMaster,     // 必须是帮主
        SignUp_GuildMemberLess,     // 帮派成员不足
        SignUp_AlreadySignUp,       // 已经报名了 不能重复报名
        SignUp_CanNotSignUp,        // 你的帮派不能报名此战场
        SignUp_GuildLevelLess,      // 帮派等级不足
        SignUp_NotEnoughGuildMoney, // 没有足够的帮派金钱
        SignUp_GuildStrengthLess,   // 帮派实力不足, 无法顶替已报名帮派报名
		SignUp_GuildUnionBattleSumError,//当前轮数不可以报名
		SignUp_GuildUnionBattleNone,//当前战场不需要报名 开始后可以直接参与
		SignUp_GuildBattleFull,
        /////////////////////////////////////////////////////////////////////
        // 进入战场结果返回
        Enter_NotEnterStatus = 1,   // 不是进入战场阶段
        Enter_MustSignUpGuild,      // 必须是报名帮派才能进入
        Enter_LevelLess,            // 等级不足, 无法进入
        Enter_MaxCount,             // 战场进入人数已满
		Enter_BattleSumError,		//不是指定胜利公会
    };

    // 获得基础阵营信息
    static unsigned char GetBaseFightCamp( unsigned char uchFightCamp )
    {
        // 判断阵营( 红方阵营都为奇数, 蓝方都为偶数 )
        if ( uchFightCamp == NoneCamp )
        { return NoneCamp; }

        if ( uchFightCamp % 2 == BaseCampRed )
        { return BaseCampRed; }

        return BaseCampBlue;
    }

    // 阵营获得战场类型
    static unsigned char GetBattleTypeByCamp( unsigned char uchFightCamp )
    {
        switch ( uchFightCamp )
        {
        case GuildCampRed:
        case GuildCampBlue:
            return BattleTypeGuild;
            break;
        case KingCampRed:
        case KingCampBlue:
            return BattleTypeKing;
            break;
        case DragonCampRed:
        case DragonCampBlue:
            return BattleTypeDragon;
            break;
        case RosefinchCampRed:
        case RosefinchCampBlue:
            return BattleTypeRosefinch;
            break;
		case GuildUnionRed:
		case GuildUnionBlue:
			return BattleTypeGuildUnion;
			break;
        default:
            break;
        }

        return BattleTypeNone;
    }
}

// 战场中的玩家的信息
class BattlePlayer
{
public:
    BattlePlayer() : m_uchFightCamp( CampDefine::NoneCamp ), m_nResource( 0 ), m_nTotalKillCount( 0 ), m_nTotalDeathCount( 0 ), m_nKeepKillCount ( 0 )
    {
        memset( m_szName, 0 , sizeof( m_szName ) );
    }

    // 阵营
    unsigned char GetFightCamp() const { return m_uchFightCamp; } 
    void SetFightCamp( unsigned char uchValue ) { m_uchFightCamp = uchValue; }

    // 名字
    const char* GetName() const { return m_szName; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }

    // 职业
    unsigned char GetProfession() const { return m_uchProfession; }
    void SetProfession( unsigned char uchValue ) { m_uchProfession = uchValue; }

    // 等级
    unsigned char GetLevel() const { return m_uchLevel; }
    void SetLevel( unsigned char uchValue ) { m_uchLevel = uchValue; }

    // 积分
    unsigned int GetResource() const { return m_nResource; }
    void SetResource( unsigned int nValue ) { m_nResource = nValue; }
    void AddResource( unsigned int nValue ) { m_nResource += nValue; }

    // 杀人总数
    unsigned int GetTotalKillCount() const { return m_nTotalKillCount; }
    void SetTotalKillCount( unsigned int nValue ) { m_nTotalKillCount = nValue; }
    void AddTotalKillCount( unsigned int nValue ) { m_nTotalKillCount += nValue; }

    // 死亡总数
    unsigned int GetTotalDeathCount() const { return m_nTotalDeathCount; }
    void SetTotalDeathCount( unsigned int nValue ) { m_nTotalDeathCount = nValue; }
    void AddTotalDeathCount( unsigned int nValue ) { m_nTotalDeathCount += nValue; }

    // 当前连杀数
    unsigned int GetKeepKillCount() const { return m_nKeepKillCount; }
    void SetKeepKillCount( unsigned int nValue ) {  m_nKeepKillCount = nValue; }
    void AddKeepKillCount( unsigned int nValue ) { m_nKeepKillCount += nValue; }

    // 判断是否有效的战场玩家( 什么记录都没有, 当作无效的玩家 )
    bool CheckValid() const { return m_nResource != 0 || m_nTotalDeathCount != 0 || m_nTotalKillCount != 0; }

private:
    // 阵营
    unsigned char m_uchFightCamp;

    // 玩家名字
    char m_szName[ CampDefine::NameLength ];

    // 职业
    unsigned char m_uchProfession;

    // 等级
    unsigned char m_uchLevel;

    // 获得的积分
    unsigned int m_nResource;

    // 玩家的杀人总数
    unsigned int m_nTotalKillCount;

    // 玩家死亡总数
    unsigned int m_nTotalDeathCount;

    // 当前连杀数量
    unsigned int m_nKeepKillCount;
};


#endif