#pragma once
#include <string.h>
namespace GameBattleDefine
{
	enum EConstDefine
    {
		//战场的常量定义
		GameBattle_None = 0,
		GameBattle_Red = 1,//红发
		GameBattle_Blue = 2,//蓝方
		GameBattle_Three = 3,//第三方 或者是值观察方 目前没用 

		GameBattle_Type_Init = 0,
		GameBattle_Type_GuildGeneral = 1,//公会约战的战场类型
		GameBattle_Type_Max,

		GameBattle_Control_UpdateSpace = 5000,//Control的更新间隔


		// 战场状态
        StatusInit = 0,     // 初始状态
        StatusSignUp,       // 报名状态
        StatusPrepare,      // 准备状态
        StatusEnter,        // 进入战场状态
        StatusFight,        // 战场战斗状态
        StatusEnd,          // 结束状态
        StatusRelease,      // 战场销毁, 释放资源( 服务器使用 )

		DefaultReliveIndex = 0,     // 默认重生点
        RedReliveIndex = 2,         // 红方复活点
        BlueReliveIndex = 3,        // 蓝方复活点

		ReleaseSapceTime = 60000,   // 1分钟后战场销毁
        UpdateSpaceTime = 5000,     // 5秒刷新一次
		NameLength = 33,            // 玩家名字长度

		Enter_NotEnterStatus = 1,   // 不是进入战场阶段
        Enter_MustSignUpGuild,      // 必须是报名帮派才能进入
        Enter_LevelLess,            // 等级不足, 无法进入
        Enter_MaxCount,             // 战场进入人数已满
		Enter_BattleSumError,		//不是指定胜利公会

		MaxGameGuildGeneralBattleInfoLength = 256,
		//WaitBattleTime = 10*60,//单位秒
		WaiteAddMsgBattleTime = 30*60,//单位秒
		//CampBattleMaxLastTime  = 4 *60*60,//战场约战最长持续时间
	};
	class BattlePlayer
	{
	public:
		BattlePlayer() : m_uchFight( GameBattle_None ), m_nResource( 0 ), m_nTotalKillCount( 0 ), m_nTotalDeathCount( 0 ), m_nKeepKillCount ( 0 )
		{
			memset( m_szName, 0 , sizeof( m_szName ) );
		}

		// 阵营
		unsigned char GetFight() const { return m_uchFight; } 
		void SetFight( unsigned char uchValue ) { m_uchFight = uchValue; }

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
		unsigned char m_uchFight;

		// 玩家名字
		char m_szName[ NameLength ];

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
	struct GuildCampBattle
	{
		unsigned int ID;
		unsigned int MapID;
		unsigned int SrcGuildID;
		unsigned int DestGuildID;
		unsigned int MoneySum;
		unsigned int GuildMoneySum;
		unsigned int GuildMissionSum;
		__int64 BeginTime;
		bool IsWrite;
		bool IsChange(GuildCampBattle& other)
		{
			if(SrcGuildID != other.SrcGuildID || DestGuildID != other.DestGuildID || MoneySum != other.MoneySum || GuildMoneySum != other.GuildMoneySum 
				|| GuildMissionSum != other.GuildMissionSum)
				return true;
			else
				return false;
		}
	};
};