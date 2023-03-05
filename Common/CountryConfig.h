#ifndef __COUNTRYCONFIG_H__
#define __COUNTRYCONFIG_H__

/************************************************************************
            国家配置定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

#include <vector>
#include <map>

#define theCountryConfig CountryConfig::Instance()

#define InitTribute 1000  //初始化兵书/贡品数量为2000

class CountryConfig
{
public:
    class BornMapSetting
    {
    public:
        BornMapSetting() : nCountry( 0 ), nMapID( 0 ), fPosX( 0.f ), fPosY( 0.f ), fDirX( 0.f ), fDirY( 0.f ){}

        unsigned int GetCountry() const { return nCountry; }
        unsigned int GetMapID() const { return nMapID; }
        float GetPosX() const { return fPosX; }
        float GetPosY() const { return fPosY; }
        float GetDirX() const { return fDirX; }
        float GetDirY() const { return fDirY; }

        void SetCountry( unsigned int nValue ) { nCountry = nValue; }
        void SetMapID( unsigned int nValue ) { nMapID = nValue; }
        void SetPosX( float fValue ) { fPosX = fValue; }
        void SetPosY( float fValue ) { fPosY = fValue; }
        void SetDirX( float fValue ) { fDirX = fValue; }
        void SetDirY( float fValue ) { fDirY = fValue; }
    private:
        unsigned int nCountry;
        unsigned int nMapID;
        float fPosX;
        float fPosY;
        float fDirX;
        float fDirY;
    };

    class SpecialMapSetting
    {
    public:
        SpecialMapSetting() : nCountry( 0 ), nMapID( 0 ), fPosX( 0.f ), fPosY( 0.f ), fDir( 0.f ){}

        unsigned int GetCountry() const { return nCountry; }
        unsigned int GetMapID() const { return nMapID; }
        float GetPosX() const { return fPosX; }
        float GetPosY() const { return fPosY; }
        float GetDir () const { return fDir; }


        void SetCountry( unsigned int nValue ) { nCountry = nValue; }
        void SetMapID( unsigned int nValue ) { nMapID = nValue; }
        void SetPosX( float fValue ) { fPosX = fValue; }
        void SetPosY( float fValue ) { fPosY = fValue; }
        void SetDir ( float fValue ) { fDir = fValue; }

    private:
        unsigned int nCountry;
        unsigned int nMapID;
        float fPosX;
        float fPosY;
        float fDir;
    };
    
    class RaiseSetting
    {
    public:
        RaiseSetting() : nLevel( 0 ), nMoney( 0 ){}

        unsigned int GetLevel() const { return nLevel; }
        unsigned int GetMoney() const { return nMoney; }

        void SetLevel( unsigned int nValue ) { nLevel = nValue; }
        void SetMoney( unsigned int nValue ) { nMoney = nValue; }

    private:
        unsigned int nLevel;        // 等级
        unsigned int nMoney;        // 小于该等级, 能募捐的最大金钱
    };

    class QuestSetting
    {
    public:
        unsigned int GetType() const { return nType; }
        unsigned int GetCount() const { return nCount; }
        unsigned int GetCostMoney() const { return nCostMoney; }
        unsigned int GetKeepTime() const { return nKeepTime; }
        const char* GetName() const { return strName.c_str(); }
        const char* GetPosition() const { return strPosition.c_str(); }
        const char* GetDescription() const { return strDescription.c_str(); }
		const char* GetBoardcast() const {return strBroadcast.c_str();}

        void SetType( unsigned int nValue ) { nType = nValue; }
        void SetCount( unsigned int nValue ) { nCount = nValue; }
        void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }
        void SetKeepTime( unsigned int nValue ) { nKeepTime = nValue; }
        void SetName( const char* szValue ) { strName = szValue; }
        void SetPosition( const char* szValue ) { strPosition = szValue; }
        void SetDescription( const char* szValue ) { strDescription = szValue; }
		void SetBroadcast(const char* szValue) {strBroadcast = szValue;}

    private:
        unsigned int nType;             // 国家发布任务类型 0( 国运任务 ) 1( 出国任务 ) 2( 天行任务 ) 3( 探宝任务 )
        unsigned int nCount;            // 每天发布的次数
        unsigned int nCostMoney;        // 发布消耗的金钱
        unsigned int nKeepTime;         // 任务发布的持续时间 ( 单位: 秒 )
        std::string strName;            // 名字
        std::string strPosition;        // 职位发布
        std::string strDescription;     // 描述
		std::string strBroadcast;      //发布时的系统公告
    };

    class BattleSetting
    {
    public:
        unsigned int GetType() const { return nType; }
        unsigned int GetMinGuildLevel() const { return nMinGuildLevel; }
        unsigned int GetMinMemberCount() const { return nMinMemberCount; }
        unsigned int GetCostGuildMoney() const { return nCostGuildMoney; }

        void SetType( unsigned int nValue ) { nType = nValue; }
        void SetMinGuildLevel( unsigned int nValue ) { nMinGuildLevel = nValue; }
        void SetMinMemberCount( unsigned int nValue ) { nMinMemberCount = nValue; }
        void SetCostGuildMoney( unsigned int nValue ) { nCostGuildMoney = nValue; }
    private:
        unsigned int nType;                 // 国家战场类型
        unsigned int nMinGuildLevel;        // 最少需要公会级别
        unsigned int nMinMemberCount;       // 最少需要公会成员数量
        unsigned int nCostGuildMoney;       // 花费的帮会资金
    };

    class MountSetting
    {
    public:
        unsigned int GetLevel() const { return nLevel; }
        unsigned int GetKingID() const { return nKingID; }
        unsigned int GetQueenID() const { return nQueenID; }
        unsigned int GetDragonID() const { return nDragonID; }
        unsigned int GetRostfinchID() const { return nRosefinchID; }

        void SetLevel( unsigned int nValue ) { nLevel = nValue; }
        void SetKingID( unsigned int nValue ) { nKingID = nValue; }
        void SetQueenID( unsigned int nValue ) { nQueenID = nValue; }
        void SetDragionID( unsigned int nValue ) { nDragonID = nValue; }
        void SetRosefinchID( unsigned int nValue ) { nRosefinchID = nValue; }

        bool operator == ( unsigned int nValue ) { return nLevel == nValue; }
        friend bool operator == ( const MountSetting& xSetting, unsigned int nValue ) { return xSetting.GetLevel() == nValue; }

    private:
        unsigned int nLevel;            // 坐骑等级
        unsigned int nKingID;           // 国王坐骑
        unsigned int nQueenID;          // 王后坐骑
        unsigned int nDragonID;         // 青龙坐骑
        unsigned int nRosefinchID;      // 朱雀坐骑
    };

    class ImpeachSetting
    {
    public:
        unsigned int GetRank() const { return nRank; }
        unsigned int GetAgreeGuild() const { return nAgreeGuild; }
        unsigned int GetAgreePercent() const { return nAgreePercent; }
        unsigned int GetCostGuildMoney() const { return nCostGuildMoney; }
        unsigned int GetMinLevel() const { return nMinLevel; }

        void SetRank( unsigned int nValue ) { nRank = nValue; }
        void SetAgreeGuild( unsigned int nValue ) { nAgreeGuild = nValue; }
        void SetAgreePercent( unsigned int nValue ) { nAgreePercent = nValue; }
        void SetCostGuildMoney( unsigned int nValue ) { nCostGuildMoney = nValue; }
        void SetMinLevel( unsigned int nValue ) { nMinLevel = nValue; }

    private:
        unsigned int nRank;             // 排行前几的公会
        unsigned int nAgreeGuild;       // 同意的公会数量
        unsigned int nAgreePercent;     // 同意的国民百分比
        unsigned int nCostGuildMoney;   // 花费的帮贡
        unsigned int nMinLevel;         // 最小国民资格等级
    };

    class StrengthSetting
    {
    public:
        unsigned int GetQuestModulus() const { return nQuestModulus; }
        unsigned int GetReleaseModulus() const { return nReleaseModulus; }

        void SetQuestModulus( unsigned int nValue ) { nQuestModulus = nValue; }
        void SetReleaseModulus( unsigned int nValue ) { nReleaseModulus = nValue; }

    private:
        unsigned int nQuestModulus;     // 完成出国任务增加的国家实力
        unsigned int nReleaseModulus;   // 发布出国令增加的国家实力
    };

    // 国家屠城战设置
    class WarFightSetting
    {
    public:
        unsigned int GetDayOfWeek() const { return nDayOfWeek; }
        unsigned int GetPrepareHour() const { return nPrepareHour; }
        unsigned int GetPrepareMinute() const { return nPrepareMinute; }
        unsigned int GetStartHour() const { return nStartHour; }
        unsigned int GetStartMinute() const { return nStartMinute; }
        unsigned int GetEndHour() const { return nEndHour; }
        unsigned int GetEndMinute() const { return nEndMinute; }
        unsigned int GetCountryScore() const { return nCountryScore; }
        unsigned int GetMaxCountryScore() const { return nMaxCountryScore; }
        unsigned int GetLevelLimit() const { return nLevelLimit; }

        void SetDayOfWeek( unsigned int nValue ) { nDayOfWeek = nValue; }
        void SetPrepareHour( unsigned int nValue ) { nPrepareHour = nValue; }
        void SetPrepareMinute( unsigned int nValue ) { nPrepareMinute = nValue; }
        void SetStartHour( unsigned int nValue ) { nStartHour = nValue; }
        void SetStartMinute( unsigned int nValue ) { nStartMinute = nValue; }
        void SetEndHour( unsigned int nValue ) { nEndHour = nValue; }
        void SetEndMinute( unsigned int nValue ) { nEndMinute = nValue; }
        void SetCountryScore( unsigned int nValue ) { nCountryScore = nValue; }
        void SetMaxCountryScore( unsigned int nValue ) { nMaxCountryScore = nValue; }
        void SetLevelLimit( unsigned int nValue ) { nLevelLimit = nValue; }

        bool CheckPrepareTime( unsigned int nMinute, unsigned int nHour, unsigned int nDay ) const
        {
            return ( nDay == nDayOfWeek && nHour == nPrepareHour && nMinute == nPrepareMinute );
        }

        bool CheckStartTime( unsigned int nMinute, unsigned int nHour, unsigned int nDay ) const
        {
            return ( nDay == nDayOfWeek && nHour == nStartHour && nMinute == nStartMinute );
        }

        bool CheckEndTime( unsigned int nMinute, unsigned int nHour, unsigned int nDay ) const
        {
            return ( nDay == nDayOfWeek && nHour == nEndHour && nMinute == nEndMinute );
        }

    private:
        unsigned int nDayOfWeek;   

        // 预备时间
        unsigned int nPrepareHour;
        unsigned int nPrepareMinute;

        // 开始时间
        unsigned int nStartHour;
        unsigned int nStartMinute;

        // 结束时间
        unsigned int nEndHour;
        unsigned int nEndMinute;

        // 每杀一人获得多少国战积分
        unsigned int nCountryScore;
        // 最多能获得多少国战积分
        unsigned int nMaxCountryScore;
        // 等级差限制
        unsigned int nLevelLimit;
    };

    class ReliveSetting
    {
    public:
        unsigned int    GetReliveTime()  const  { return nReliveTime; }
        unsigned short  GetLevelLimit()  const  { return nLevelLimit; }
        unsigned char   GetBeforeLevelLimit()  const  { return nBeforeLevelLimit; }
        unsigned char   GetAfterLevelLimit ()  const  { return nAfterLevelLimit ; }
		unsigned int    GetFullHpMpRand()  const  { return nFullHpMpRand; }
		int    GetReliveMoney()  const  { return nReliveMoney; }
		int    GetPerReliveMoney()  const  { return nPerReliveMoney; }
		unsigned int    GetBaoZouRand()  const  { return nBaoZouRand; }
		unsigned int    GetTrueBZRand()  const  { return nTrueBZRand; }
		int    GetBuffStatusID1()  const  { return nBuffStatusID1; }
		int    GetBuffStatusID2()  const  { return nBuffStatusID2; }
		int    GetBuffStatusLV1()  const  { return nBuffStatusLV1; }
		int    GetBuffStatusLV2()  const  { return nBuffStatusLV2; }

        void SetReliveTime( unsigned int nValue )   { nReliveTime = nValue; }
        void SetLevelLimit( unsigned short nValue ) { nLevelLimit = nValue; }
        void SetBeforeLevelLimit( unsigned char nValue ) { nBeforeLevelLimit = nValue; }
        void SetAfterLevelLimit( unsigned char nValue )  { nAfterLevelLimit = nValue;  }
		void SetFullHpMpRand( unsigned int nValue )  { nFullHpMpRand = nValue;  }
		void SetReliveMoney( int nValue )  { nReliveMoney = nValue;  }
		void SetPerReliveMoney( int nValue )  { nPerReliveMoney = nValue;  }
		void SetBaoZouRand( unsigned int nValue )  { nBaoZouRand = nValue;  }
		void SetTrueBZRand( unsigned int nValue )  { nTrueBZRand = nValue;  }

		void SetBuffStatusID1( int nValue )  { nBuffStatusID1 = nValue;  }
		void SetBuffStatusID2( int nValue )  { nBuffStatusID2 = nValue;  }
		void SetBuffStatusLV1( int nValue )  { nBuffStatusLV1 = nValue;  }
		void SetBuffStatusLV2( int nValue )  { nBuffStatusLV2 = nValue;  }

        unsigned char GetFreeReliveLimitByLevel( unsigned short nLevel ) const
        {
            if ( nLevel <= GetLevelLimit() )
            { return GetBeforeLevelLimit(); }
            else
            { return GetAfterLevelLimit() ; }

            return 0;
        }

		void AddRevileLevel(int Level ,int Sum){ReliveLevelLimit.insert(std::map<int,int>::value_type(Level,Sum));}
		int  GetReilvelSum(int Level) const;
		int  GetReviceMoney(int Level,int ReviceSum) const;

		void SetLevelReviceMoney(int Value) {nLevelReviceMoney = Value;}
		int GetLevelReviceMoney() const {return nLevelReviceMoney;}

		void SetReviceMaxMoneySum(int Value){nReviceMaxMoneySum = Value;}
		int GetReviceMaxMoneySum() const {return nReviceMaxMoneySum;}

		void SetReviceSumMoney(int Value){nReviceSumMoney = Value;}
		int GetReviceSumMoney() const {return nReviceSumMoney;}

		void SetReliveItemId(int itemId) { nItemId = itemId; }
		int GetReliveItemId() const { return nItemId; }

		void SetReliveItemCount(int itemcount) { nItemCount = itemcount; }
		int GetReliveItemCount() const { return nItemCount; }
    private:
        unsigned int   nReliveTime;         // 复活倒计时时间 单位毫秒
        unsigned short nLevelLimit;         // 免费复活等级限制
        unsigned char  nBeforeLevelLimit;   // 等级限制前免费复活次数
        unsigned char  nAfterLevelLimit ;   // 等级限制后免费复活次数
		int			   nReliveMoney;		// 原地复活需要的钱
		int			   nPerReliveMoney;		// 完美复活需要的钱
		unsigned int   nFullHpMpRand;		// 出现完美复活的概率
		unsigned int   nBaoZouRand;			// 出现暴走复活的概率
		unsigned int   nTrueBZRand;			// 出现真暴走复活的概率
		int		       nBuffStatusID1;		// 奖励的BuffID		
		int			   nBuffStatusLV1;
		int		       nBuffStatusID2;		// 奖励的BuffID		
		int			   nBuffStatusLV2;
		std::map<int,int> ReliveLevelLimit;//等级限制复活次数
		int		       nLevelReviceMoney;
		int			   nReviceSumMoney;
		int			   nReviceMaxMoneySum;
		int			   nItemId;
		int			   nItemCount;
    };

	class RandJoinReward
	{
	public:
		RandJoinReward(){nRewardID = 0;}
		int GetRewardID(){return nRewardID;}
		void SetRewardID(int nID){nRewardID = nID;}
	private:
		int nRewardID;				//点随机加入时奖励的物品ID
	};

    static CountryConfig& Instance()
    {
        static CountryConfig s_xConfig;
        return s_xConfig;
    }

    unsigned int GetMaxMoney() const { return nMaxMoney; }
	unsigned int GetMaxTribute() const { return nMaxTribute; }
	unsigned int GetMinTribute() const { return nMinTribute; }
	unsigned int GetFitstTribute() const { return nFirstTribute;}
    unsigned int GetPlacardCount() const { return nPlacardCount; }
    unsigned int GetPlacardCost() const { return nPlacardCost; }
    unsigned int GetBanSpeakCount() const { return nBanSpeakCount; }
    unsigned int GetBanSpeakCost() const { return nBanSpeakCost; }
    unsigned int GetBanSpeakTime() const { return nBanSpeakTime; }
    unsigned int GetRemitCount() const { return nRemitCount; }
    unsigned int GetRemitCost() const { return nRemitCost; }
    unsigned int GetChainCount() const { return nChainCount; }
    unsigned int GetChainCost() const { return nChainCost; }
    unsigned int GetChainStatus() const { return nChainStatus; }
    unsigned int GetConveneCount() const { return nConveneCount; }
    unsigned int GetConveneCost() const { return nConveneCost; }
    unsigned int GetConveneTime() const { return nConveneTime; }
    unsigned int GetAppointMinLevel() const { return nAppointMinLevel; }
    unsigned int GetRaiseCount() const { return nRaiseCount; }
    unsigned int GetMinRaiseLevel() const { return nRaiseMinLevel; }
    unsigned int GetRaiseKeepTime() const { return nRaiseKeepTime; }
    unsigned int GetRaiseRewardExp() const { return nRaiseRewardExp; }
    unsigned int GetMinConveneLevel() const { return nConveneMinLevel; }
    unsigned int GetMaxRaiseMoney( unsigned int nLevel ) const;
    unsigned int GetRaiseBoradMoney() const { return nRaiseBroadMoney; }
    unsigned int GetMaxRaiseIndex( unsigned int nLevel ) const;
    unsigned int GetCountrySpeakSpace() const { return nCountrySpeakSpace; }
    unsigned int GetRaiseSettingCount() const { return static_cast< unsigned int >( vecRaiseSetting.size() ); }
    const BornMapSetting* GetBornMapSetting( unsigned int nCountry, unsigned char uchIndex = 0 ) const;
    unsigned int GetBornMapSettingCount( unsigned int nCountry ) const;
    const SpecialMapSetting* GetPrisonMapSetting( unsigned int nCountry ) const;
    const SpecialMapSetting* GetReliveMapSetting( unsigned int nCountry ) const;
    const RaiseSetting* GetRaiseMoneyByIndex( unsigned int nIndex ) const;
    const QuestSetting* GetQuestSetting( unsigned int nType ) const; 
    
    const MountSetting* GetMountSettingByLevel( unsigned int nLevel ) const;
    unsigned int GetMountSettingCount() const { return static_cast< unsigned int >( vecMountSetting.size() ); }
    const MountSetting* GetMountSettingByIndex( unsigned int nIndex ) const;

    const ImpeachSetting& GetImpeachSetting() const{ return xImpeakSetting; }
    const StrengthSetting& GetStrengthSetting() const { return xStrengthSetting; }
    const WarFightSetting& GetWarFightSetting() const { return xWarFightSetting; }

    const ReliveSetting&   GetReliveSetting() const { return xReliveSetting; }

    unsigned int GetBordersFightCount() const { return nBordersFightCount; }

    unsigned int GetCountryChangeCostMoney() const { return nCountryChangeCostMoney; }

    bool LoadCountryConfig( const char* szFile );
	unsigned long GetSkipSameOverdueInfoTime() const { return m_SkipSameOverdueInfoTime; }

	RandJoinReward GetRandJoinReward(){return xRandJoinReward;}

protected:
    CountryConfig() : m_SkipSameOverdueInfoTime( 2000 ), nCountryChangeCostMoney( 0 ), nRaiseBroadMoney( 0 )
    {

    }

    typedef std::vector< BornMapSetting > BornMapSettingVector;
    typedef std::map< unsigned char, BornMapSettingVector > BornMapSettingMap;
    typedef BornMapSettingMap::iterator BornMapSettingMapIter;
    typedef BornMapSettingMap::const_iterator BornMapSettingMapConstIter;

    typedef std::vector< SpecialMapSetting > PrisonMapSettingVector;
    typedef std::vector< SpecialMapSetting > ReliveMapSettingVector;

    typedef std::vector< RaiseSetting > RaiseSettingVector;
    typedef RaiseSettingVector::const_iterator RaiseSettingVectorIter;

    typedef std::vector< QuestSetting > QuestSettingVector;
    typedef std::vector< BattleSetting > BattleSettingVector;

    typedef std::vector< MountSetting > MountSettingVector;
    typedef MountSettingVector::const_iterator MountSettingVectorIter;


   void AddBornMapSetting( const BornMapSetting& xSetting );

private:

    BornMapSettingMap mapBornMapSetting; // 国家出生点设置

    PrisonMapSettingVector vecPrisonMapSetting; // 国家监狱设置
    ReliveMapSettingVector vecReliveMapSetting; // 国家回魂殿设置

    unsigned int nMaxMoney;                 // 国家最大金钱
	unsigned int nMaxTribute;				// 国家最大贡品
	unsigned int nMinTribute;				// 国家最小贡品
	unsigned int nFirstTribute;				// 第一次初始化

    unsigned int nPlacardCount;             // 国家修改公告的次数
    unsigned int nPlacardCost;              // 国家修改公告花费的金钱

    unsigned int nBanSpeakCount;            // 国家禁言的次数
    unsigned int nBanSpeakCost;             // 国家禁言的花费
    unsigned int nBanSpeakTime;             // 禁言时间 ( 单位 : 分钟 )

    unsigned int nRemitCount;               // 国家赦免的次数
    unsigned int nRemitCost;                // 国家赦免的次数

    unsigned int nChainCount;               // 国家囚禁的次数
    unsigned int nChainCost;                // 国家囚禁的花费
    unsigned int nChainStatus;              // 国家囚禁的状态

    unsigned int nConveneCount;             // 国家召集的次数
    unsigned int nConveneCost;              // 国家召集的花费
    unsigned int nConveneTime;              // 国家召集的有效时间( 单位 : 分钟 )

    unsigned int nAppointMinLevel;          // 国家任命的最小等级
    unsigned int nConveneMinLevel;          // 国家召集的最小等级

    unsigned int nRaiseCount;               // 国家募集次数
    unsigned int nRaiseMinLevel;            // 募捐的最小等级
    unsigned int nRaiseKeepTime;            // 募捐发出后多久时间有效( 单位 : 分钟 )
    unsigned int nRaiseRewardExp;           // 募捐奖励的经验
    unsigned int nRaiseBroadMoney;          // 募捐的广播值
    RaiseSettingVector vecRaiseSetting;     // 募捐钱的限制

    QuestSettingVector vecQuestSetting;     // 国家发布任务配置
    MountSettingVector vecMountSetting;     // 国家坐骑
    ImpeachSetting xImpeakSetting;          // 弹劾设置
    StrengthSetting xStrengthSetting;       // 国家实力设置
    WarFightSetting xWarFightSetting;       // 国家屠城战设置
    ReliveSetting  xReliveSetting;          // 复活设置
	RandJoinReward xRandJoinReward;			// 随机加入时奖励设置

    unsigned int nBordersFightCount;        // 记录边境战斗记录数量
	unsigned long m_SkipSameOverdueInfoTime;//相同消息不显示间隔
    unsigned int nCountrySpeakSpace;        // 国家频道聊天间隔 ( 单位: 毫秒 )

    unsigned int nCountryChangeCostMoney;   // 叛国花费的金钱
};



#endif