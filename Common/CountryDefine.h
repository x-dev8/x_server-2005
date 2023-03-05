#ifndef __GAMECOUNTRYDEFINE_H__
#define __GAMECOUNTRYDEFINE_H__

/************************************************************************
            国家结构属性定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "string.h"
#include "CountryConfig.h"

namespace CountryDefine
{
    enum EConstDefine
    {
        // 国籍定义
        Country_Init = 0,        // 无国籍
        Country_LouLan,          // 楼兰王国(魏国)
        Country_KunLun,          // 昆仑王国(蜀国)
        Country_DunHuang,        // 敦煌王国(吴国)
        Country_Max,            

        // 职位定义 
        Position_None = 0,       // 无职位
        Position_CaptorLeft,     // 金牌左捕
        Position_CaptorRight,    // 金牌右捕
        Position_CouncilorLeft,  // 左丞 太师
        Position_CouncilorRight, // 右相 太尉
        Position_General,        // 大将军
        Position_Queen,          // 王后
        Position_King,           // 国王
        Position_Max,          

        // 权利定义
        Right_None                = 0,       // 无权利
        Right_Convene             = 0x1,     // 召集权
        Right_Placard             = 0x2,     // 公告权
        Right_AppointKing         = 0x4,     // 国王任免权
        Right_AppointGeneral      = 0x8,     // 大将军任免权
        Right_Raise               = 0x10,    // 募集权
        Right_BanSpeak            = 0x20,    // 禁言权
        Right_Remit               = 0x40,    // 赦免权
        Right_Chain               = 0x80,    // 囚禁权
        Right_QuestKing           = 0x100,   // 国王发布任务权   ( 国运任务 ) 国运
        Right_QuestGeneral        = 0x200,   // 大将军发布任务权 ( 出国任务 ) 国探
        Right_QuestCouncilorLeft  = 0x400,   // 左丞发布任务权   ( 天行任务 ) 兵书
        Right_QuestCouncilorRight = 0x800,   // 右相发布任务权   ( 探宝任务 ) 护粮
        Right_WorldSpeak          = 0x1000,  // 免费世界小喇叭的权利
        Right_FlyToBorders        = 0x2000,  // 飞到边塞入侵地点的权利
        Right_ChangeName          = 0x4000,  // 修改国家名字的权利
		Right_PK				  = 0x8000,	 // PK不加PK值

		/*
		 *	Author 2013-1-4 zhuxincong
		 *	DESC: 修改，策划要求，国王，皇后，大都督都能使用召集
		 */
        // 国王权利
		Right_King = Right_PK | Right_ChangeName | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight | Right_QuestCouncilorLeft | Right_QuestKing | Right_Chain | Right_Remit | Right_BanSpeak | Right_Raise | Right_Convene | Right_Placard | Right_AppointKing | Right_QuestGeneral,
        //Right_King = Right_PK | Right_Placard | Right_AppointKing | Right_Raise | Right_BanSpeak | Right_Remit | Right_Chain | Right_QuestKing | Right_WorldSpeak | Right_ChangeName | Right_Convene, 
        // 王后权利
		//Right_Queen  = Right_Raise | Right_BanSpeak | Right_Remit | Right_Chain,
        Right_Queen = Right_WorldSpeak | Right_Convene,
        // 大将军权利
		//Right_General =  Right_PK | Right_AppointGeneral,
        Right_General = Right_PK | Right_AppointGeneral | Right_QuestGeneral | Right_Convene | Right_FlyToBorders | Right_WorldSpeak | Right_QuestKing,
        // 左丞权利
		//Right_CouncilorLeft =  Right_QuestGeneral | Right_QuestCouncilorRight,
        Right_CouncilorLeft = Right_QuestCouncilorLeft | Right_WorldSpeak,
        // 右相权利
		//Right_CouncilorRight = Right_QuestKing | Right_QuestCouncilorLeft,
        Right_CouncilorRight = Right_QuestCouncilorRight | Right_WorldSpeak,
        // 金牌左捕
		//Right_CaptorLeft = Right_PK,
        Right_CaptorLeft = Right_PK | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight,
        // 金牌右捕
		//Right_CaptorRight = Right_PK,
        Right_CaptorRight = Right_PK | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight,

        ErrorID = 0,             // 无效的玩家ID
        NoneID  = 0,             // 无效的公会ID
        MaxNoticeLength  = 101,  // 公告最大长度 ( 50个字 )
        MaxNameLength    = 33,   // 名字字串的长度
        MaxCountryLength = 5,    // 国加名字最多2个字

        // 国家战场类型
        Battle_None = 0,
        Battle_King,             // 国王争夺战
        Battle_Dragon,           // 青龙争夺战
        Battle_Rosefinch,        // 朱雀争夺战
        Battle_MaxType,          // 最大战场类型

        // 战场胜利方式
        BattleWin_FistTime = 0,  // 第一次申请成功
        BattleWin_Guard,         // 守护成功 ( 守护方胜利 )
        BattleWin_Challenge,     // 挑战成功 ( 挑战方胜利 )

        // 守护类型
        Guard_None = 0,
        Guard_Dragon,           // 青龙守护
        Guard_Rosefinch,        // 朱雀守护
        Guard_Max,

        // 国家称号
        Title_None = 0,          // 没有
        Title_King,              // 国王
        Title_General,           // 大将军
        Title_Queen,             // 王后
        Title_CouncilorLeft,     // 左丞
        Title_CouncilorRight,    // 右相
        Title_CaptorLeft,        // 左捕
        Title_CaptorRight,       // 右捕
        Title_KingGuard,         // 国王卫队
        Title_Dragon,            // 青龙之主
        Title_DragonGuard,       // 青龙守护
        Title_Rosefinch,         // 朱雀之主
        Title_RosefinchGuard,    // 朱雀守护
		Title_QueenMale,		 // 亲王
        Title_GuildMaster,       // 帮主
        Title_ViceMaster,        // 副帮主
        Title_FamilyMaster,      // 家族长
        Title_GuildMember,       // 普通帮众
		

        // 发布任务的类型
        QuestType_None = 0,
        QuestType_King,             // 国运任务 国运
        QuestType_General,          // 出国任务 国探
        QuestType_CouncilorLeft,    // 天行任务 兵书
        QuestType_CouncilorRight,   // 探宝任务 护粮
        QuestType_Max,

        MountType_None = 0,
        MountType_King,             // 国王坐骑( 包括王后 )
        MountType_Guard,            // 守护坐骑( 青龙 和 朱雀 )

        // 国家资源类型
        Resource_None = 0,
        Resource_Money,     

        MaxBordersFightCount = 10,  // 边境战斗记录长度
        UpdateSpaceTime = 5000,     // 更新间隔时间
        LoadSpaceTime = 600000,     // 10分钟请求一次
        SaveKeepTime = 500000,      // 10分钟保存一次
        UpdateWarKillTime = 10000,  // 10秒更新一次国战资源
        ////////////////////////////////////////////////////////////////
        OperateAdd = 1,             // +
        OperateSub,                 // -
        OperateSet,                 // =
        ////////////////////////////////////////////////////////////////
        UpdateMoney = 1,        // 更新国家金钱
		UpdateTribute,			// 更新国家贡品     
        CancelKingGuild,        // 删除国王帮
        UpdateKingGuild,        // 更新国王帮
        CancelDragonGuild,      // 删除青龙帮
        UpdateDragonGuild,      // 更新青龙帮
        CancelRosefinchGuild,   // 删除朱雀帮
        UpdateRosefinchGuild,   // 更新朱雀帮
        UpdateLastStrength,     // 更新上周实力
        UpdateNowStrength,      // 更新本周实力
        UpdateChangeName,       // 更新修改国家名字变量
        UpdateSortIndex,        // 更新国战杀人排行

        //////////////////////////////////////////////////////////////////
        // 国家战场状态
        BattleStatusInit = 0,
        BattleStatusSignUp,
        BattleStatusEnter,
        BattleStatusFight,
        BattleStatusEnd,

        BattleDefaultRelive   = 0,  // 默认复活点
        BattleGuardRelive     = 2,  // 守方复活点
        BattleChallengeRelive = 3,  // 攻方复活点
        /////////////////////////////////////////////////////////////////////
        WarStatusInit = 0,      // 屠城战初始状态
        WarStatusPrepare,       // 屠城战前30分钟
        WarStatusFight,         // 屠城战开始
        WarStatusEnd,           // 屠城战结束
        /////////////////////////////////////////////////////////////////////

		MaxCountryInfoLength = 256,
		MaxMsgCountryInfoSum = 20,//命令一次最多读20条 循环发送命令
		MaxCountryInfoSum	 = 7,
    };

    inline bool CheckEnmityCountry( int nFirst, int nSecond )
    {
        if ( nFirst == Country_Init || nSecond == Country_Init )
        { return false; }

        return nFirst != nSecond; 
    }

    // 国家任务类型 获得 相对应的发布权限
    inline unsigned int GetQuestRightByType( unsigned char uchType )
    {
        unsigned int nRight = Right_None;
        switch ( uchType )
        {
        case QuestType_King:
            nRight = Right_QuestKing;
            break;
        case QuestType_General:
            nRight = Right_QuestGeneral;
            break;
        case QuestType_CouncilorLeft:
            nRight = Right_QuestCouncilorLeft;
            break;
        case QuestType_CouncilorRight:
            nRight = Right_QuestCouncilorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // 通过任命的官职来获得需要的权限
    inline unsigned int GetAppointRightByPosition( unsigned char uchPosition )
    {
        unsigned int nRight = Right_None;
        switch ( uchPosition )
        {
        case Position_General:
        case Position_CouncilorLeft:
        case Position_CouncilorRight:
            nRight = Right_AppointKing;
            break;;
        case Position_CaptorLeft:
        case Position_CaptorRight:
            nRight = Right_AppointGeneral;
            break;
        default:
            break;
        }

        return nRight;
    }

    // 通知任免权来判断是否可以任命的官职
    inline bool IsCanAppointPosition( unsigned char uchPositon, unsigned int nRight )
    {
        switch ( nRight )
        {
        case Right_AppointKing:
            {
                switch ( uchPositon )
                {
                case Position_General:
                case Position_CouncilorLeft:
                case Position_CouncilorRight:
                    return true;
                    break;
                default:
                    break;
                }
            }
            break;
        case Right_AppointGeneral:
            {
                switch( uchPositon )
                {
                case Position_CaptorLeft:
                case Position_CaptorRight:
                    return true;
                    break;
                default:
                    break;
                }
            }
        default:
            break;
        }

        return false;
    }

    // 获得官职的权限
    inline unsigned int GetRightByPosition( unsigned char uchPosition )
    {
        unsigned int nRight = Right_None;
        switch ( uchPosition )
        {
        case Position_King:
            nRight = Right_King;
            break;
        case Position_General:
            nRight = Right_General;
            break;
        case Position_CouncilorLeft:
            nRight = Right_CouncilorLeft;
            break;
        case Position_CouncilorRight:
            nRight = Right_CouncilorRight;
            break;
        case Position_CaptorLeft:
            nRight = Right_CaptorLeft;
            break;
        case Position_CaptorRight:
            nRight = Right_CaptorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // 获得官职的国家称号
    inline unsigned char GetCountryTitleByPosition( unsigned char uchPosition )
    {
        unsigned char uchTitle = Title_None;
        switch ( uchPosition )
        {
        case Position_King:
            uchTitle = Title_King;
            break;
        case Position_General:
            uchTitle = Title_General;
            break;
        case Position_CouncilorLeft:
            uchTitle = Title_CouncilorLeft;
            break;
        case Position_CouncilorRight:
            uchTitle = Title_CouncilorRight;
            break;
        case Position_CaptorLeft:
            uchTitle = Title_CaptorLeft;
            break;
        case Position_CaptorRight:
            uchTitle = Title_CaptorRight;
            break;
        case Position_Queen:
            uchTitle = Title_Queen;
            break;
        default:
            break;
        }

        return uchTitle;
    }

    // 由称号获得国家权力
    inline unsigned int GetCountryRightByTitle( unsigned short ustTitle )
    {
        unsigned int nRight = Right_None;
        switch ( ustTitle )
        {
        case Title_King:
            nRight = Right_King;
            break;
        case Title_General:
            nRight = Right_General;
            break;
        case Title_Queen:
		case Title_QueenMale:
            nRight = Right_Queen;
            break;
        case Title_CouncilorLeft:
            nRight = Right_CouncilorLeft;
            break;
        case Title_CouncilorRight:
            nRight = Right_CouncilorRight;
            break;
        case Title_CaptorLeft:
            nRight = Right_CaptorLeft;
            break;
        case Title_CaptorRight:
            nRight = Right_CaptorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // 由称号获得国家职位
    inline unsigned char GetCountryPositionByTitle( unsigned short ustTitle )
    {
        switch ( ustTitle )
        {
        case Title_King:
            return Position_King;
            break;
        case Title_General:
            return Position_General;
            break;
        case Title_Queen:
            return Position_Queen;
            break;
        case Title_CouncilorLeft:
            return Position_CouncilorLeft;
            break;
        case Title_CouncilorRight:
            return Position_CouncilorRight;
            break;
        case Title_CaptorLeft:
            return Position_CaptorLeft;
            break;
        case Title_CaptorRight:
            return Position_CaptorRight;
            break;
        default:
            break;
        }

        return Position_None;
    }
}


// 国家官员属性
class OfficialInfo
{
public:
    OfficialInfo() : dwPlayerID( CountryDefine::ErrorID ), uchPosition( CountryDefine::Position_None ), dwRight( CountryDefine::Right_None ),sexID(-1),faceID(-1),headerID(-1),professionID(-1)
    {
        memset( szPlayerName, 0, sizeof( szPlayerName ) );
    }

    void SetID( unsigned int nValue )    { dwPlayerID = nValue; }
    void SetName( const char* szName )   { strncpy_s( szPlayerName, sizeof( szPlayerName ), szName, sizeof( szPlayerName ) - 1 ); }
    void SetRight( unsigned int nValue ) { dwRight = nValue; } 
    void SetPosition( unsigned char uchValue ) { uchPosition = uchValue; }

    unsigned int GetID() const           { return dwPlayerID; }
    const char* GetName() const          { return szPlayerName; }
    unsigned int GetRight() const        { return dwRight; }
    unsigned char GetPosition() const    { return uchPosition; }

    bool HaveRight( unsigned int nValue ) { return ( dwRight & nValue ) != 0; }         // 是否有权利
    bool HigherPosition( unsigned char uchValue ) { return uchPosition > uchValue; }    // 是否是更高的职位
    bool IsEmpty() const { return dwPlayerID == CountryDefine::ErrorID; }               // 是否有玩家担任此职位
    void ClearOfficial()
    {
        dwPlayerID = CountryDefine::ErrorID;
        memset( szPlayerName, 0 , sizeof( szPlayerName ) );
        dwRight = CountryDefine::Right_None;

		faceID = 0;
		headerID = 0;
		sexID = 0;
		professionID = 0;
    }

	unsigned char GetSexID() const {return sexID;}
	void SetSexID(unsigned char value ){sexID = value;}

	unsigned short GetFaceID() const {return faceID;}
	void SetFaceID(unsigned short value ){faceID = value;}

	unsigned short GetHeaderID() const {return headerID;}
	void SetHeaderID(unsigned short value ){headerID = value;}

	unsigned short GetProfessionID() {return professionID;}
	void SetProfessionID(unsigned short value){professionID = value;}
private:
    unsigned int dwPlayerID;                                // 官员DBID
    char szPlayerName[ CountryDefine::MaxNameLength ];      // 官员名称
    unsigned char uchPosition;                              // 官员职位
    unsigned int dwRight;                                   // 对应的权利
	unsigned short faceID;
	unsigned short headerID;
	unsigned char  sexID;
	unsigned short professionID;
};

// 时间内操作次数限制
class OperateTime
{
public:
    OperateTime() : n64StartTime( 0 ), uchOperateCount( 0 )
    {
    }

    unsigned char GetCount() const { return uchOperateCount; }
    void SetCount( unsigned char uchValue ) { uchOperateCount = uchValue; }
    __int64 GetStartTime() const { return n64StartTime; }

    void SetStartTime( __int64 nValue ) { n64StartTime = nValue; }
private:
    __int64 n64StartTime;           // 开始时间
    unsigned char uchOperateCount;  // 操作次数 
};

// 国家属性
class CountryData 
{
public:
	CountryData() : uchID( CountryDefine::Country_Init ), nMoney( 0 ), nTribute(InitTribute),
		nKingGuildID( CountryDefine::NoneID ), nDragonGuildID( CountryDefine::NoneID ), nRosefinchGuildID( CountryDefine::NoneID ), 
        nRecordTime( 0 ), uchChainCount( 0 ), uchPlacardCount( 0 ), uchConveneCount( 0 ), uchRaiseCount( 0 ), uchBanSpeakCount( 0 ), uchRemitCount( 0 ), nLastStrength( 0 ), nNowStrength( 0 ), bChangeName( false ),
        m_uchSorIndex( 0 ), m_nKillCount( 0 ), m_nDeathCount( 0 ) , nDoneQuestStrength(0) ,nCountryPlayerSum(0)
    {
        memset( szNotice, 0, sizeof( szNotice ) );
        memset( szName, 0, sizeof( szName ) );

        for ( int i = CountryDefine::Position_None; i < CountryDefine::Position_Max; ++i )
        {
            xOfficial[ i ].SetPosition( i );
        }

		for(int i =CountryDefine::QuestType_None;i<CountryDefine::QuestType_Max;++i)
		{
			nQuestSum[i] = 0;
		}
    }

    void SetID( unsigned char uchValue ) { uchID = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); } 
    void SetMoney( int nValue ) { if ( nValue < 0 ) { nValue = 0; } nMoney = nValue; }
	void SetTribute( int nValue) { if (nValue < 0 ) { nValue = 0; } nTribute = nValue; }
    void SetNotice( const char* szValue ) { strncpy_s( szNotice, sizeof( szNotice ), szValue, sizeof( szNotice ) - 1 ); }
    void SetKingGuild( unsigned int nValue ) { nKingGuildID = nValue; }
    void SetDragonGuild( unsigned int nValue ) { nDragonGuildID = nValue; }
    void SetRosefinchGuild( unsigned int nValue ) { nRosefinchGuildID = nValue; }
    void SetRecordTime( unsigned int nValue ) { nRecordTime = nValue; }
    void SetPlacardCount( unsigned char uchValue ) { uchPlacardCount = uchValue; }
    void SetConveneCount( unsigned char uchValue ) { uchConveneCount = uchValue; }
    void SetRaiseCount( unsigned char uchValue ) { uchRaiseCount = uchValue; }
    void SetBanSpeakCount( unsigned char uchValue ) { uchBanSpeakCount = uchValue; }
    void SetRemitCount( unsigned char uchValue ) { uchRemitCount = uchValue; }
    void SetChainCount( unsigned char uchValue ) { uchChainCount = uchValue; }
    void SetLastStrength( unsigned int nValue ) { nLastStrength = nValue; }
    void SetNowStrength( unsigned int nValue ) { nNowStrength = nValue; }
    void SetChangeName( bool bValue ) { bChangeName = bValue; }

    void SetSortIndex( unsigned char uchValue ) { m_uchSorIndex = uchValue; }
    void SetKillCount( unsigned int nValue ) { m_nKillCount = nValue; }
    void AddKillCount( unsigned int nValue ) { m_nKillCount += nValue; }
    void SetDeathCount( unsigned int nValue ) { m_nDeathCount = nValue; }
    void AddDeathCount( unsigned int nValue ) { m_nDeathCount += nValue; }

    unsigned char GetID() const { return uchID; }
    const char* GetName() const { return szName; }
    bool HaveName() const { return szName[0] != 0; }
	unsigned int GetMoney() const { return nMoney; }
	unsigned int GetTribute() const {return nTribute;}
    unsigned int GetKingGuild() const { return nKingGuildID; }
    const char* GetNotice() const { return szNotice; }
    unsigned int GetDragonGuild() const { return nDragonGuildID; }
    unsigned int GetRosefinchGuild() const { return nRosefinchGuildID; }

    unsigned int GetRecordTime() const { return nRecordTime; }
    unsigned char GetPlacardCount() const { return uchPlacardCount; }
    unsigned char GetConveneCount() const { return uchConveneCount; }
    unsigned char GetRaiseCount() const { return uchRaiseCount; }
    unsigned char GetBanSpeakCount() const { return uchBanSpeakCount; }
    unsigned char GetRemitCount() const { return uchRemitCount; }
    unsigned char GetChainCount() const { return uchChainCount; }
    unsigned int GetLastStrength() const { return nLastStrength; }
    unsigned int GetNowStrength() const { return nNowStrength; }
    bool GetChangeName() const { return bChangeName; }

    unsigned char GetSortIndex() const { return m_uchSorIndex; }
    unsigned int GetKillCount() const { return m_nKillCount; }
    unsigned int GetDeathCount() const { return m_nDeathCount; }

    bool AddOfficial( const OfficialInfo& xValue );
    OfficialInfo* GetOfficial( unsigned char uchPosition );
    OperateTime* GetQuestOperate( unsigned char uchType );

	
	void SetAddDoneQuestStrength(unsigned int Sum) {nDoneQuestStrength += Sum;}
	unsigned int GetDoneQuestAddStrength(){return nDoneQuestStrength;}
	void SetDoneQuestStrength(unsigned int Sum){nDoneQuestStrength = Sum;}

	void SetCountryPlayerSum(unsigned int Sum){ nCountryPlayerSum = Sum;}
	unsigned int GetCountryPlayerSum() {return nCountryPlayerSum;}

	void SetAddQuestCount(unsigned char QuestType);
	unsigned int GetAllQuestSum();
	unsigned int GetQuestSumByType(unsigned char QuestType);
	void SetQuestSumBytype(unsigned char QuestType,unsigned char num);
protected:
    unsigned char uchID;                                            // 国家ID
    char szName[ CountryDefine::MaxCountryLength ];                 // 国家名字
    unsigned int nMoney;                                            // 国家资源
	unsigned int nTribute;											// 国家贡品
    unsigned int nKingGuildID;                                      // 国家权力所属的公会
    char szNotice[ CountryDefine::MaxNoticeLength ];                // 国家公告
    OfficialInfo xOfficial[ CountryDefine::Position_Max ];          // 国家的官员列表
    unsigned int nDragonGuildID;                                    // 青龙守护帮会
    unsigned int nRosefinchGuildID;                                 // 朱雀守护帮会

    unsigned int nRecordTime;                                       // 记录日期
    unsigned char uchPlacardCount;                                  // 公告次数
    unsigned char uchConveneCount;                                  // 召集操作
    unsigned char uchRaiseCount;                                    // 募集操作
    unsigned char uchBanSpeakCount;                                 // 禁言操作
    unsigned char uchRemitCount;                                    // 赦免操作
    unsigned char uchChainCount;                                    // 囚禁权利
    OperateTime xOperate[ CountryDefine::QuestType_Max ];           // 任务发布
    unsigned int nLastStrength;                                     // 上周国家实力
    unsigned int nNowStrength;                                      // 本周国家实力
    bool bChangeName;                                               // 是否已经改变国家名字
 
	unsigned char nQuestSum[CountryDefine::QuestType_Max];			// 国家发布的任务总的计数 本周的
	unsigned int  nDoneQuestStrength;								// 因完成任务而增加的国力值 本周的
	unsigned int  nCountryPlayerSum;								// 当前国家人数 不存储到数据库

    // 国战杀人记录
    unsigned char m_uchSorIndex;    // 排名
    unsigned int m_nKillCount;      // 杀人记数
    unsigned int m_nDeathCount;     // 死亡次数                       
};
inline void CountryData::SetAddQuestCount(unsigned char QuestType)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return;
	++nQuestSum[QuestType];
}
inline unsigned int CountryData::GetQuestSumByType(unsigned char QuestType)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return -1;
	return nQuestSum[QuestType];
}
inline void CountryData::SetQuestSumBytype(unsigned char QuestType,unsigned char num)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return ;
	nQuestSum[QuestType] = num;
}
inline unsigned int CountryData::GetAllQuestSum()
{
	unsigned int Sum =0;
	for(int i =CountryDefine::QuestType_None;i<CountryDefine::QuestType_Max;++i)
	{
		Sum += nQuestSum[i];
	}
	return Sum;
}
inline bool CountryData::AddOfficial( const OfficialInfo& xValue )
{
    if ( xValue.GetPosition() >= CountryDefine::Position_Max )
    { return false; }

    xOfficial[ xValue.GetPosition() ] = xValue; 
    return true;
}

inline OfficialInfo* CountryData::GetOfficial( unsigned char uchPosition )
{
    if ( uchPosition >= CountryDefine::Position_Max )
    { return NULL; }

    return &xOfficial[ uchPosition ];
}

inline OperateTime* CountryData::GetQuestOperate( unsigned char uchType )
{
    if ( uchType >= CountryDefine::QuestType_Max )
    { return NULL; }

    return &( xOperate[ uchType ] );
}


///////////////////////////////////////////////////////////////////////////////////////////////
#endif