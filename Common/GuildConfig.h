#ifndef __GUILDCONFIG_H__
#define __GUILDCONFIG_H__

#include <vector>
#include <map>
#include <algorithm>

#define theGuildConfig GuildConfig::Instance()

class GuildConfig
{
public:
    // 创建帮派设定
    class CreateSetting
    {
    public:
        unsigned int GetLevel() const { return nLevel; }
        unsigned int GetCostMoney() const { return nCostMoney; }

        void SetLevel( unsigned int nValue ) { nLevel = nValue; }
        void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }
    private:
        unsigned int nLevel;
        unsigned int nCostMoney;
    };
    // 加入帮派设定
    class JoinSetting
    {
    public:
        unsigned int GetLevel() const { return nLevel; }
        unsigned int GetTimeLimit() const { return nTimeLimit; }

        void SetLevel( unsigned int nValue ) { nLevel = nValue; }
        void SetTimeLimit( unsigned int nValue ) { nTimeLimit = nValue; }
    private:
        unsigned int nLevel;
        unsigned int nTimeLimit;
    };
    // 帮派等级设定
    class LevelSetting
    {
    public:
        LevelSetting() : nMaxCount( 0 ), nMaxMission( 0 ), nMaxExp( 0 ), nMaxMoney( 0 ), nNeedExp( 0 ), nNeedMoney( 0 ),nNeedMission(0)
        {

        }

        unsigned int GetMaxCount() const { return nMaxCount; }
        unsigned int GetMaxMission() const { return nMaxMission; }
        unsigned int GetMaxExp() const { return nMaxExp; }
        unsigned int GetMaxMoney() const { return nMaxMoney; }
        unsigned int GetNeedExp() const { return nNeedExp; }
        unsigned int GetNeedMoney() const { return nNeedMoney; }
		unsigned int GetNeedMission() const { return nNeedMission;}

        void SetMaxCount( unsigned int nValue ) { nMaxCount = nValue; }
        void SetMaxMission( unsigned int nValue ) { nMaxMission = nValue; }
        void SetMaxExp( unsigned int nValue ) { nMaxExp = nValue; }
        void SetMaxMoney( unsigned int nValue ) { nMaxMoney = nValue; }
        void SetNeedExp( unsigned int nValue ) { nNeedExp = nValue; }
        void SetNeedMoney( unsigned int nValue ) { nNeedMoney = nValue; }
		void SetNeedMission(unsigned int nValue) {nNeedMission = nValue;}
    private:
        unsigned int nMaxCount;     // 最大成员数量
        unsigned int nMaxMission;   // 最大使命点数
        unsigned int nMaxExp;       // 最大帮会经验
        unsigned int nMaxMoney;     // 最大帮会金钱
        unsigned int nNeedExp;      // 升级需要的经验
        unsigned int nNeedMoney;    // 升级需要的钱
		unsigned int nNeedMission; // 升级需要的使命点
    };

    // 捐献设定
	class DonateMoneySetting
	{
	public:
		DonateMoneySetting() : nLevel( 0 ), nMoney( 0 ){}

		unsigned int GetLevel() const { return nLevel; }
		unsigned int GetMoney() const { return nMoney; }

		void SetLevel( unsigned int nValue ) { nLevel = nValue; }
		void SetMoney( unsigned int nValue ) { nMoney = nValue; }

	private:
		unsigned int nLevel;        // 等级
		unsigned int nMoney;        // 小于该等级, 能募捐的最大金钱
	};

    class DonateSetting
    {
    public:
        unsigned int GetMoney() const { return nMoney; }
        unsigned int GetActivity() const { return nActivity; }
        unsigned int GetOffer() const { return nOffer; }
        unsigned int GetMaxMoney() const { return nMaxMoney; }
		unsigned int GetMaxDonateMoneyByLevel(int nLevel) const; 
		
        void SetMoney( unsigned int nValue ) { nMoney = nValue; }
        void SetActivity( unsigned int nValue ) { nActivity = nValue; }
        void SetOffer( unsigned int nValue ) { nOffer = nValue; }
        void SetMaxMoney( unsigned int nValue ) { nMaxMoney = nValue; }
		void SetDonateMoney(const DonateMoneySetting& refDonateMoneySetting) { m_vctDonateMoney.push_back(refDonateMoneySetting); }
		void ClearDonateMoneyVct() { m_vctDonateMoney.clear(); };

    private:
        unsigned int nMoney;            // 捐献多少钱
        unsigned int nActivity;         // 奖励活跃度
        unsigned int nOffer;            // 奖励帮贡
        unsigned int nMaxMoney;         // 每天能捐献钱的最大值
		std::vector<DonateMoneySetting> m_vctDonateMoney;
    };

    // 募集设定
    class CollectSetting
    {
    public:
        unsigned int GetGuildExp() const { return nGuildExp; }
        unsigned int GetGuildMoney() const { return nGuildMoney; }
        unsigned int GetPlayerExp() const { return nPlayerExp; }
        unsigned int GetPlayerOffer() const { return nPlayerOffer; }

        void SetGuildExp( unsigned int nValue ) { nGuildExp = nValue; }
        void SetGuildMoney( unsigned int nValue ) { nGuildMoney = nValue; }
        void SetPlayerExp( unsigned int nValue ) { nPlayerExp = nValue; }
        void SetPlayerOffer( unsigned int nValue ) { nPlayerOffer = nValue; }
    private:
        unsigned int nGuildExp;         // 奖励帮会经验
        unsigned int nGuildMoney;       // 奖励帮会金钱
        unsigned int nPlayerExp;        // 奖励个人经验
        unsigned int nPlayerOffer;      // 奖励个人帮贡
    };

    // 帮贡建设
    class BuildSetting
    {
    public:
        unsigned int GetOffer() const { return nOffer; }
        unsigned int GetGuildExp() const { return nGuildExp; }
        unsigned int GetPlayerExp() const { return nPlayerExp; }

        void SetOffer( unsigned int nValue ) { nOffer = nValue; }
        void SetGuildExp( unsigned int nValue ) { nGuildExp = nValue; }
        void SetPlayerExp( unsigned int nValue ) { nPlayerExp = nValue; }

    private:
        unsigned int nOffer;         // 捐献帮贡
        unsigned int nGuildExp;     // 奖励帮会经验
        unsigned int nPlayerExp;    // 奖励个人经验
    };

    // 弹劾设定
    class DelateSetting
    {
    public:
        unsigned int GetDayOfWeek() const { return nDayOfWeek; }
        unsigned int GetStartHour() const { return nStartHour; }
        unsigned int GetEndHour() const { return nEndHour; }
        unsigned int GetLevel() const { return nLevel; }
        unsigned int GetCostMoney() const { return nCostMoney; }
        unsigned int GetMinCount() const { return nMinCount; }
        unsigned int GetRatio() const { return nRatio; }

        void SetDayOfWeek( unsigned int nValue ) { nDayOfWeek = nValue; }
        void SetStartHour( unsigned int nValue ) { nStartHour = nValue; }
        void SetEndHour( unsigned int nValue ) { nEndHour = nValue; }
        void SetLevel( unsigned int nValue ) { nLevel = nValue; }
        void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }
        void SetMinCount( unsigned int nValue ) { nMinCount = nValue; }
        void SetRatio( unsigned int nValue ) { nRatio = nValue; }
    private:
        unsigned int nDayOfWeek;        // 星期几
        unsigned int nStartHour;        // 开始时间
        unsigned int nEndHour;          // 结束时间
        unsigned int nLevel;            // 弹劾玩家的最小等级
        unsigned int nCostMoney;        // 花费的金钱
        unsigned int nMinCount;         // 最小在线成员个数
        unsigned int nRatio;            // 响应玩家比例
    };

    // 自动解散设定
    class DisbandSetting
    {
    public:
        unsigned int GetMinCount() const { return nMinCount; }
        unsigned int GetKeepTime() const { return nKeepTime; }

        void SetMinCount( unsigned int nValue ) { nMinCount = nValue; }
        void SetKeepTime( unsigned int nValue ) { nKeepTime = nValue; }

    private:
        unsigned int nMinCount;         // 成员最小个数
        unsigned int nKeepTime;         // 维持时间 : 小时
    };

    // 使命点设定
    class MissionSetting
    {
    public:
        class DateSetting
        {
        public:
            unsigned int GetDate() const { return nDate; }
            unsigned int GetHour() const { return nHour; }
            unsigned int GetMinute() const { return nMinute; }

            void SetDate( unsigned int nValue ) { nDate = nValue; }
            void SetHour( unsigned int nValue ) { nHour = nValue; }
            void SetMinute( unsigned int nValue ) { nMinute = nValue; }
        private:
            unsigned int nDate;
            unsigned int nHour;
            unsigned int nMinute;
        };

        typedef std::vector< DateSetting > DateSettingVector;
        typedef DateSettingVector::const_iterator DateSettingVectorIter;

        unsigned int GetGuildExp() const { return nGuildExp; }
        void SetGuildExp( unsigned int nValue ) { nGuildExp = nValue; }

        void AddDateStting( DateSetting& xSetting )
        {
            vecDateSetting.push_back( xSetting );
        }

        bool CheckDateSetting( int nDate, int nHour, int nMinute ) const
        {
            for ( DateSettingVectorIter iter = vecDateSetting.begin(); iter != vecDateSetting.end(); ++iter )
            {
                if ( iter->GetDate() != nDate )
                { continue; }

                if ( iter->GetHour() != nHour )
                { continue; }

                if ( iter->GetMinute() == nMinute )
                { return true; }
            }

            return false;
        }

    private:
        unsigned int nGuildExp;             // 每个使命点兑换的帮派经验
        DateSettingVector vecDateSetting;   // 清算日
    };

    // 任务发布
    class ReleaseSetting
    {
    public:
        class QuestSetting
        {
        public:
            unsigned int GetType() const { return nType; }
            unsigned int GetCostMoney() const { return nCostMoney; }
			unsigned int GetKeepTime() const { return nKeepTime; }
			const char* GetName() const { return strName.c_str(); }
            unsigned int GetMemberReward() const { return nMemberReward; }
            unsigned int GetViceReward() const { return nViceReward; }
            unsigned int GetMasterReward() const { return nMasterReward; }

            void SetType( unsigned int nValue ) { nType = nValue; }
            void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }
			void SetKeepTime( unsigned int nValue ) { nKeepTime = nValue; }
			void SetName( const char* szValue ) { strName = szValue; }
            void SetMemberReward( unsigned int nValue ){ nMemberReward = nValue; }
            void SetViceReward( unsigned int nValue ) { nViceReward = nValue; }
            void SetMasterReward( unsigned int nValue ) { nMasterReward = nValue; }

            void AddQuest( unsigned int nQuestID ) { vecQuest.push_back( nQuestID ); }
            bool CheckQuest( unsigned int nQusetID ) const
            {
                return std::find( vecQuest.begin(), vecQuest.end(), nQusetID ) != vecQuest.end();
            }

        private:
            typedef std::vector< unsigned int > QuestVector;

            unsigned int nType;         // 任务类型
            unsigned int nCostMoney;    // 花费金钱
			unsigned int nKeepTime;         // 任务发布的持续时间 ( 单位: minu )
			std::string strName;            // 名字
            unsigned int nMemberReward; // 成员奖励倍数
            unsigned int nViceReward;   // 副帮主奖励倍数
            unsigned int nMasterReward; // 帮主奖励倍数
            QuestVector vecQuest;       // 任务ID
        };

        unsigned int GetMinLevel() const { return nMinLevel; }
        unsigned int GetReleaseTime() const { return nReleaseTime; }

        void SetMinLevel( unsigned int nValue ) { nMinLevel = nValue; }
        void SetReleaseTime( unsigned int nValue ) { nReleaseTime = nValue; }

        void AddQuestSetting( QuestSetting& xQuest ) { mapQuest[ xQuest.GetType() ] = xQuest; }
        const QuestSetting* GetQuestSetting( unsigned int nType ) const
        {
            QuestSettingMapConstIter iter = mapQuest.find( nType );
            if ( iter == mapQuest.end() )
            { return NULL; }

            return &( iter->second );
        }

    private:
        typedef std::map< unsigned int, QuestSetting > QuestSettingMap;
        typedef QuestSettingMap::const_iterator QuestSettingMapConstIter;

        unsigned int nMinLevel;     // 帮派最小等级
        unsigned int nReleaseTime;  // 发布的最晚时间
        QuestSettingMap mapQuest;
    };

    // 帮派商店
    class ShopSetting
    {
    public:
        ShopSetting() : nCostExp( 0 )
        {
            mapShopItem.clear();
        }

        unsigned int GetCostExp() const { return nCostExp; }
        void SetCostExp( unsigned int nValue ) { nCostExp = nValue; }

        void AddShopItem( unsigned int nItemID, unsigned int nOffer )
        {
            mapShopItem[ nItemID ] = nOffer;
        }

        unsigned int GetItemCost( unsigned int nItemID) const 
        {
            ShopItemMapConstIter iter = mapShopItem.find( nItemID );
            if ( iter == mapShopItem.end() )
            { return 0; }

            return iter->second;
        }

		const std::map< unsigned int, unsigned int >& GetItemMap() const { return mapShopItem; }

    private:
        typedef std::map< unsigned int, unsigned int > ShopItemMap;
        typedef ShopItemMap::const_iterator ShopItemMapConstIter;

        unsigned int nCostExp;  // 花费帮派经验
        ShopItemMap mapShopItem;
    };

    // 帮派实力系数设定
    class StrengthSetting
    {
    public:
        float GetBaseModulus() const { return fBaseModulus; }
        float GetExtendModulus() const { return fExtendModulus; }

        void SetBaseModulus( float fValue ) { fBaseModulus = fValue; }
        void SetExtendModulus( float fValue ) { fExtendModulus = fValue; }
    private:
        float fBaseModulus;
        float fExtendModulus;
    };

	// 帮派宗旨改名CD,花费设定
	class ChangeAimSetting
	{
	public:
		__int64 GetChangeAimCD() const	{ return nChangeAimCD; }
		unsigned int GetChangeAimCost() const	{ return nChangeAimCost; }

		void SetChangeAimCD( __int64 nCD )	{ nChangeAimCD = nCD; }
		void SetChangeAimCost( unsigned int nCost )	{ nChangeAimCost = nCost; }

	private:
		__int64 nChangeAimCD;
		unsigned int nChangeAimCost;
	};

    static GuildConfig& Instance()
    {
        static GuildConfig s_xConfig;
        return s_xConfig;
    }

    const CreateSetting& GetCreateSetting() const { return m_xCreateSetting; }
    const JoinSetting& GetJoinSetting() const { return m_xJoinSetting; }
    const LevelSetting* GetLevelSetting( unsigned char uchLevel ) const;
    const DonateSetting& GetDonateSetting() const { return m_xDonateSetting; }
    const CollectSetting& GetCollectSetting() const { return m_xCollectSetting; }
    const BuildSetting& GetBuildSetting() const { return m_xBuildSetting; }
    const DelateSetting& GetDelateSetting() const { return m_xDelateSetting; }
    const DisbandSetting& GetDisbandSetting() const { return m_xDisbandSetting; }
    const MissionSetting& GetMissionSetting() const { return m_xMissionSetting; }
    const ReleaseSetting& GetReleaseSetting() const { return m_xReleaseSetting; }
    const ShopSetting* GetShopSetting( unsigned char uchLevel ) const;
    const StrengthSetting& GetStrengthSetting() const { return m_xStrengthSetting; }
	const ChangeAimSetting& GetChangeAimSetting() const { return m_changeAimSetting; }


    bool LoadConfig( const char* szFile );

protected:
    GuildConfig(){}

    typedef std::vector< LevelSetting > LevelSettingVector;

    typedef std::vector< ShopSetting > ShopSettingVector;

private:
    CreateSetting m_xCreateSetting;
    JoinSetting m_xJoinSetting;
    LevelSettingVector m_vecLevelSetting;
    DonateSetting m_xDonateSetting;
    CollectSetting m_xCollectSetting;
    BuildSetting m_xBuildSetting;
    DelateSetting m_xDelateSetting;
    DisbandSetting m_xDisbandSetting;
    MissionSetting m_xMissionSetting;
    ReleaseSetting m_xReleaseSetting;
    StrengthSetting m_xStrengthSetting;    
    ShopSettingVector m_vecShopSetting;
	ChangeAimSetting m_changeAimSetting;
};

inline const GuildConfig::LevelSetting* GuildConfig::GetLevelSetting( unsigned char uchLevel ) const
{
    if ( uchLevel == 0 || uchLevel >= m_vecLevelSetting.size() )
    { return NULL; }

    return &( m_vecLevelSetting.at( uchLevel ) );
}

inline const GuildConfig::ShopSetting* GuildConfig::GetShopSetting( unsigned char uchLevel ) const
{
    if ( uchLevel == 0 || uchLevel >= m_vecShopSetting.size() )
    { return NULL; }

    return &( m_vecShopSetting.at( uchLevel ) );
}

#endif