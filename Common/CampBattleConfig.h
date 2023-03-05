#ifndef __CAMPBATTLECONFIG_H__
#define __CAMPBATTLECONFIG_H__

#include <vector>
#include <map>
#include "RapidXml/MeRapidXml.h"
#include "CountryDefine.h"

class CampBattleConfig
{
public:
    // 地图设定
    class MapSetting
    {
    public:
        int GetMapID() const { return nMapID; }
        int GetCountryID() const { return nCountryID; }

        void SetMapID( int nValue ) { nMapID = nValue; }
        void SetCountryID( int nValue ) { nCountryID = nValue; }

    private:
        int nMapID;
        int nCountryID;
    };

    // 时间设定
    class TimeSetting
    {
    public:
        int GetDayOfWeek() const { return nDayOfWeek; }
        int GetHour() const { return nHour; }
        int GetMinute() const { return nMinute; }
        int GetKeepTime() const { return nKeepTime; }

        void SetDayOfWeek( int nValue ) { nDayOfWeek = nValue; }
        void SetHour( int nValue ) { nHour = nValue; }
        void SetMinute( int nValue ) { nMinute = nValue; }
        void SetKeepTime( int nValue ) { nKeepTime = nValue; }
    private:
        int nDayOfWeek;
        int nHour;
        int nMinute;
        int nKeepTime;      // 多久时间( 单位: 分钟 )
    };

    // 进入设定
    class EnterSetting
    {
    public:
        int GetMaxCount() const { return nMaxCount; }
        int GetMinLevel() const { return nMinLevel; }

        void SetMaxCount( int nValue ) { nMaxCount = nValue; }
        void SetMinLevel( int nValue ) { nMinLevel = nValue; }
    private:
        int nMaxCount;
        int nMinLevel;
    };

    // 杀人设定
    class KillSetting
    {
    public:
        int GetCount() const { return nCount; }
        int GetString() const { return nStringID; }

        void SetCount( int nValue ) { nCount = nValue; }
        void SetString( int nValue ) { nStringID = nValue; }
    private:
        int nCount;
        int nStringID;
    };

    // 积分( 资源 )设定
    class ResourceSetting
    {
    public:
        ResourceSetting() : nMaxResource( 100 ), nKillResource ( 0 ){}

        int GetMaxResource() const { return nMaxResource; }
        int GetKillResource() const { return nKillResource; }

        void SetMaxResource( int nValue ) { nMaxResource = nValue; }
        void SetKillResource( int nValue ) { nKillResource = nValue; }
    private:
        int nMaxResource;       // 最大积分
        int nKillResource;      // 杀人获得积分
    };

    // 怪物设定
    class MonsterSetting
    {
    public:
        int GetID() const { return nMonsterID; }
        int GetResource() const { return nResource; }
        int GetString() const { return nStringID; }

        void SetID( int nValue ) { nMonsterID = nValue; }
        void SetResource( int nValue ) { nResource = nValue; }
        void SetString( int nValue ) { nStringID = nValue; }
    private:
        int nMonsterID;
        int nResource;
        int nStringID;  // 广播的StringID
    };

    // 奖励设定
    class RewardSetting
    {
    public:
        RewardSetting() : nType( RewardNone ) {}

        enum EConstDefine
        {
            RewardNone = 0,
            RewardGuildExp,         // 帮派经验
            RewardGuildMission,     // 帮派使命点
            RewardPlayerGuildOffer, // 玩家帮贡
            RewardPlayerExp,        // 玩家经验
            RewardGuildSalary,      // 帮派津贴
        };

        int GetType() const { return nType; }
        int GetWinValue() const { return nWinValue; }
        int GetLoseValue() const { return nLoseValue; }

        void SetType( int nValue ) { nType = nValue; }
        void SetWinValue( int nValue ) { nWinValue = nValue; }
        void SetLoseValue( int nValue ) { nLoseValue = nValue; }
    private:
        int nType;
        int nWinValue;
        int nLoseValue;
    };

	class CKingdomMap
	{
	public:
		CKingdomMap():map_id(0),map_x(0),map_y(0) {}

		int GetMapID() const {return map_id;}
		float GetMapX() const {return map_x;}
		float GetMapY() const {return map_y;}

		void SetMapID(int nValue){map_id = nValue;}
		void SetMapX(float nValue){map_x = nValue;}
		void SetMapY(float nValue){map_y = nValue;}

	private:
		int map_id;
		float map_x;
		float map_y;
	};

	class EnterBuff
	{
	public:
		EnterBuff():BuffID(0),level(0){}
		int GetBuffID() const {return BuffID;}
		void SetBuffID(int ID){BuffID = ID;}

		int GetLevel() const {return level;}
		void SetLevel(int Value){level = Value;}
	private:
		int BuffID;
		int level;
	};

    // 获得地图设定数量
    int GetMapSettingCount() const;

    // 获得地图设定( 通过索引 )
    const MapSetting* GetMapSetting( unsigned int nIndex ) const;

    const EnterSetting& GetEnterSetting() const;

    // 获得资源设定
    const ResourceSetting& GetResourceSetting() const { return xResourceSetting; }

    // 获得第一次杀人设定
    const KillSetting& GetFirstKillSetting() const { return xFirstKillSetting; }

    // 获得杀人设定
    const KillSetting* GetKillerSetting( int nCount ) const;

    // 获得被杀设定
    const KillSetting* GetBeKillSetting( int nCount ) const;

    // 获得杀人总数设定
    const KillSetting* GetTotalKillSetting( int nCount ) const;

    // 判断报名时间
    virtual const TimeSetting* CheckSignUpTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // 判断准备时间
    virtual const TimeSetting* CheckPrepareTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const; 

    // 判断进入时间
    virtual const TimeSetting* CheckEnterTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const; 

    // 判断战斗时间
    virtual const TimeSetting* CheckFightTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // 判断结束时间
    virtual const TimeSetting* CheckEndTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // 获得怪物设定
    const MonsterSetting* GetMonsterSetting( int nMonsterId ) const;

    // 获得奖励个数
    int GetRewardSettingCount() const;

    // 获得奖励
    const RewardSetting* GetRewardSetting( unsigned int nIndex ) const;

    // 加载设定
	virtual bool LoadConfig( const char* szFile ,unsigned char countryid = CountryDefine::Country_Init );

	const CKingdomMap& GetKingdomMap() const {return xKongdomMap;}
	
	const EnterBuff& GetEnterBuff() const {return xEnterBuff;}
protected:
    typedef std::vector< MapSetting > MapSettingVector;


    typedef std::vector< TimeSetting > TimeSettingVector;
    typedef TimeSettingVector::const_iterator TimeSettingVectorIter;

    typedef std::map< int, KillSetting > KillSettingMap;
    typedef KillSettingMap::const_iterator KillSettingMapIter;
    
    typedef std::vector< KillSetting > KillSettingVector;
    typedef KillSettingVector::const_reverse_iterator KillSettingVectorIter;

    typedef std::map< int, MonsterSetting > MonsterSettingMap;
    typedef MonsterSettingMap::const_iterator MonsterSettingMapIter;

    typedef std::vector< RewardSetting > RewardSettingVector;
    typedef RewardSettingVector::const_iterator RewardSettingVectorIter;

    virtual bool LoadMapSetting( MeXmlElement* pElement );
    virtual bool LoadTimeSetting( MeXmlElement* pElement );
    virtual bool LoadEnterSetting( MeXmlElement* pElement );
    virtual bool LoadResourceSetting( MeXmlElement* pElement );
    virtual bool LoadKillSetting( MeXmlElement* pElement );
    virtual bool LoadMonsterSetting( MeXmlElement* pElement );
    virtual bool LoadRewardSetting( MeXmlElement* pElement );
	virtual bool LoadKingdomMapSetting( MeXmlElement* pElement );
	virtual bool LoadEnterBuff( MeXmlElement* pElement );
protected:
    MapSettingVector vecMapSetting;             // 地图设定
    TimeSettingVector vecSignUpTimeSetting;     // 报名时间
    TimeSettingVector vecPrepareTimeSetting;    // 准备时间
    TimeSettingVector vecEnterTimeSetting;      // 进入时间
    TimeSettingVector vecFightTimeSetting;      // 战斗时间
    TimeSettingVector vecEndTimeSetting;        // 结束时间
    EnterSetting xEnterSetting;                 // 进入设定
    KillSettingMap mapKillerSetting;            // 杀人设定
    KillSettingVector vecBeKillSetting;         // 被杀设定
    KillSettingMap mapTotalKillSetting;         // 杀人总数设定
    ResourceSetting xResourceSetting;           // 积分设定
    KillSetting xFirstKillSetting;              // 第一次杀人设定
    MonsterSettingMap mapMonsterSetting;        // 怪物设定
    RewardSettingVector vecRewardSetting;       // 奖励设定
	CKingdomMap xKongdomMap;					// 主城地图设定
	EnterBuff xEnterBuff;						// 进入的时候添加的BUff
};

inline int CampBattleConfig::GetMapSettingCount() const
{
    return static_cast< int >( vecMapSetting.size() );
}

inline const CampBattleConfig::MapSetting* CampBattleConfig::GetMapSetting( unsigned int nIndex ) const
{
    if ( nIndex >= vecMapSetting.size() )
    { return NULL; }

    return &( vecMapSetting.at( nIndex ) );
}

inline const CampBattleConfig::EnterSetting& CampBattleConfig::GetEnterSetting() const
{
    return xEnterSetting;
}

inline const CampBattleConfig::TimeSetting* CampBattleConfig::CheckSignUpTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const
{
    for ( TimeSettingVectorIter iter = vecSignUpTimeSetting.begin(); iter != vecSignUpTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::TimeSetting* CampBattleConfig::CheckPrepareTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const
{
    for ( TimeSettingVectorIter iter = vecPrepareTimeSetting.begin(); iter != vecPrepareTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::TimeSetting* CampBattleConfig::CheckEnterTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const
{
    for ( TimeSettingVectorIter iter = vecEnterTimeSetting.begin(); iter != vecEnterTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::TimeSetting* CampBattleConfig::CheckFightTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const
{
    for ( TimeSettingVectorIter iter = vecFightTimeSetting.begin(); iter != vecFightTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::TimeSetting* CampBattleConfig::CheckEndTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const
{
    for ( TimeSettingVectorIter iter = vecEndTimeSetting.begin(); iter != vecEndTimeSetting.end(); ++iter )
    {
        if ( ( iter->GetMinute() == nMinute ) && ( iter->GetHour() == nHour ) && ( iter->GetDayOfWeek() == nDayOfWeek ) )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::KillSetting* CampBattleConfig::GetKillerSetting( int nCount ) const
{
    KillSettingMapIter iter = mapKillerSetting.find( nCount );
    if ( iter == mapKillerSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline const CampBattleConfig::KillSetting* CampBattleConfig::GetTotalKillSetting( int nCount ) const
{
    KillSettingMapIter iter = mapTotalKillSetting.find( nCount );
    if ( iter == mapTotalKillSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline const CampBattleConfig::KillSetting* CampBattleConfig::GetBeKillSetting( int nCount ) const
{
    for ( KillSettingVectorIter iter = vecBeKillSetting.rbegin(); iter != vecBeKillSetting.rend(); ++iter )
    {
        if ( nCount >= iter->GetCount() )
        { return &( *iter ); }
    }

    return NULL;
}

inline const CampBattleConfig::MonsterSetting* CampBattleConfig::GetMonsterSetting( int nMonsterID ) const
{
    MonsterSettingMapIter iter = mapMonsterSetting.find( nMonsterID );
    if ( iter == mapMonsterSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline int CampBattleConfig::GetRewardSettingCount() const
{
    return static_cast< int >( vecRewardSetting.size() );
}

// 获得奖励
inline const CampBattleConfig::RewardSetting* CampBattleConfig::GetRewardSetting( unsigned int nIndex ) const
{
    if ( nIndex >= vecRewardSetting.size() )
    { return NULL; }

    return &( vecRewardSetting.at( nIndex ) );
}

#endif