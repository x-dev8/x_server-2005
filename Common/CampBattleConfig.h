#ifndef __CAMPBATTLECONFIG_H__
#define __CAMPBATTLECONFIG_H__

#include <vector>
#include <map>
#include "RapidXml/MeRapidXml.h"
#include "CountryDefine.h"

class CampBattleConfig
{
public:
    // ��ͼ�趨
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

    // ʱ���趨
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
        int nKeepTime;      // ���ʱ��( ��λ: ���� )
    };

    // �����趨
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

    // ɱ���趨
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

    // ����( ��Դ )�趨
    class ResourceSetting
    {
    public:
        ResourceSetting() : nMaxResource( 100 ), nKillResource ( 0 ){}

        int GetMaxResource() const { return nMaxResource; }
        int GetKillResource() const { return nKillResource; }

        void SetMaxResource( int nValue ) { nMaxResource = nValue; }
        void SetKillResource( int nValue ) { nKillResource = nValue; }
    private:
        int nMaxResource;       // ������
        int nKillResource;      // ɱ�˻�û���
    };

    // �����趨
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
        int nStringID;  // �㲥��StringID
    };

    // �����趨
    class RewardSetting
    {
    public:
        RewardSetting() : nType( RewardNone ) {}

        enum EConstDefine
        {
            RewardNone = 0,
            RewardGuildExp,         // ���ɾ���
            RewardGuildMission,     // ����ʹ����
            RewardPlayerGuildOffer, // ��Ұﹱ
            RewardPlayerExp,        // ��Ҿ���
            RewardGuildSalary,      // ���ɽ���
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

    // ��õ�ͼ�趨����
    int GetMapSettingCount() const;

    // ��õ�ͼ�趨( ͨ������ )
    const MapSetting* GetMapSetting( unsigned int nIndex ) const;

    const EnterSetting& GetEnterSetting() const;

    // �����Դ�趨
    const ResourceSetting& GetResourceSetting() const { return xResourceSetting; }

    // ��õ�һ��ɱ���趨
    const KillSetting& GetFirstKillSetting() const { return xFirstKillSetting; }

    // ���ɱ���趨
    const KillSetting* GetKillerSetting( int nCount ) const;

    // ��ñ�ɱ�趨
    const KillSetting* GetBeKillSetting( int nCount ) const;

    // ���ɱ�������趨
    const KillSetting* GetTotalKillSetting( int nCount ) const;

    // �жϱ���ʱ��
    virtual const TimeSetting* CheckSignUpTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // �ж�׼��ʱ��
    virtual const TimeSetting* CheckPrepareTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const; 

    // �жϽ���ʱ��
    virtual const TimeSetting* CheckEnterTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const; 

    // �ж�ս��ʱ��
    virtual const TimeSetting* CheckFightTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // �жϽ���ʱ��
    virtual const TimeSetting* CheckEndTimeSetting( int nDayOfWeek, int nHour, int nMinute ) const;

    // ��ù����趨
    const MonsterSetting* GetMonsterSetting( int nMonsterId ) const;

    // ��ý�������
    int GetRewardSettingCount() const;

    // ��ý���
    const RewardSetting* GetRewardSetting( unsigned int nIndex ) const;

    // �����趨
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
    MapSettingVector vecMapSetting;             // ��ͼ�趨
    TimeSettingVector vecSignUpTimeSetting;     // ����ʱ��
    TimeSettingVector vecPrepareTimeSetting;    // ׼��ʱ��
    TimeSettingVector vecEnterTimeSetting;      // ����ʱ��
    TimeSettingVector vecFightTimeSetting;      // ս��ʱ��
    TimeSettingVector vecEndTimeSetting;        // ����ʱ��
    EnterSetting xEnterSetting;                 // �����趨
    KillSettingMap mapKillerSetting;            // ɱ���趨
    KillSettingVector vecBeKillSetting;         // ��ɱ�趨
    KillSettingMap mapTotalKillSetting;         // ɱ�������趨
    ResourceSetting xResourceSetting;           // �����趨
    KillSetting xFirstKillSetting;              // ��һ��ɱ���趨
    MonsterSettingMap mapMonsterSetting;        // �����趨
    RewardSettingVector vecRewardSetting;       // �����趨
	CKingdomMap xKongdomMap;					// ���ǵ�ͼ�趨
	EnterBuff xEnterBuff;						// �����ʱ����ӵ�BUff
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

// ��ý���
inline const CampBattleConfig::RewardSetting* CampBattleConfig::GetRewardSetting( unsigned int nIndex ) const
{
    if ( nIndex >= vecRewardSetting.size() )
    { return NULL; }

    return &( vecRewardSetting.at( nIndex ) );
}

#endif