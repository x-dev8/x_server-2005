#pragma once
#include <vector>
#include <map>
#include "RapidXml/MeRapidXml.h"
#include "CountryDefine.h"
#include "BaseGameBattleConfig.h"
class GameGuildGeneralBattleConfig:public BaseGameBattleConfig
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
        int GetKeepTime() const { return nKeepTime; }

        void SetKeepTime( int nValue ) { nKeepTime = nValue; }
    private:
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

	class SignUpSetting
    {
    public:
        unsigned int GetMinMemberCount() const { return nMinMemberCount; }
        void SetMinMemberCount( unsigned int nValue ) { nMinMemberCount = nValue; }
    private:
        unsigned int nMinMemberCount;
    };

    // 刷怪设定
    class RefreshSetting
    {
    public:
        class MonsterData
        {
        public:
            int GetMonsterID() const { return nMonsterID; }
            int GetRouteID() const { return nRouteID; }
			float GetPosX() const { return fPosX; }
            float GetPosY() const { return fPosY; }
			int GetAngle() const {return nAngle;}

            void SetMonsterID( int nValue ) { nMonsterID = nValue; }
            void SetRouteID( int nValue ) { nRouteID = nValue; }
			void SetPosX( float fValue ) { fPosX = fValue; }
            void SetPosY( float fValue ) { fPosY = fValue; }
			void SetAngle(int ID){nAngle = ID;}		
        private:
            int nMonsterID;
            int nRouteID;
			float	fPosX;
			float	fPosY;
			int     nAngle;
        };
		class MonsterDataList
		{
		public:
			int GetIndex() const {return IndexID;}
			void GetAllMonster(std::vector<MonsterData>& vec) const { vec = vecMonster;}

			void SetIndex(int Index) {IndexID = Index;}
			void AddMonsterData(MonsterData data){vecMonster.push_back(data);}
		private:
			int IndexID;
			std::vector<MonsterData> vecMonster;
		};
        class BarracksSetting
        {
        public:
            float GetPosX() const { return fPosX; }
            float GetPosY() const { return fPosY; }
            float GetDirX() const { return fDirX; }
            float GetDirY() const { return fDirY; }
			int GetMonsterID() const {return MonsterID;}
            int GetMonsterCount() const { return static_cast< int >( vecMonster.size() ); }
            const MonsterDataList* GetMonster( int nIndex ) const
            {
                if(vecMonster.count(nIndex) == 0)
					return 0;
				else
				{	
					return &vecMonster.find(nIndex)->second;
				}
            }
			

            void SetPosX( float fValue ) { fPosX = fValue; }
            void SetPosY( float fValue ) { fPosY = fValue; }
            void SetDirX( float fValue ) { fDirX = fValue; }
            void SetDirY( float fValue ) { fDirY = fValue; }
			void AddMonster( MonsterDataList& xData ) { vecMonster.insert(std::map<int,MonsterDataList>::value_type(xData.GetIndex(),xData)); }
			void SetMonsterID(int ID){MonsterID = ID;}

			void SetAngle(int ID){nAngle = ID;}
			int GetAngle() const {return nAngle;}
        private:
			int MonsterID;
            float fPosX;
            float fPosY;
            float fDirX;
            float fDirY;

			int  nAngle;
			std::map<int,MonsterDataList> vecMonster;
        };

        static int GetTimeSpace() { return nTimeSpace; }
        static int GetCount() { return nCount; }
        static int GetRadius() { return nRadius; }
        static int GetType() { return nType; }

        static void SetTimeSpace( int nValue ){ nTimeSpace = nValue; }
        static void SetCount( int nValue ) { nCount = nValue; }
        static void SetRadius( int nValue ) { nRadius = nValue; }
        static void SetType( int nValue ) { nType = nValue; }

        int GetBarracksID() const { return nBarracksID; }
        const BarracksSetting& GetRedBarracksSetting() const { return xRedBarracksSetting; }
        const BarracksSetting& GetBlueBarracksSetting() const { return xBlueBarracksSetting; }

        void SetBarracksID( int nValue ) { nBarracksID = nValue; }
        void SetRedBarracksSetting( BarracksSetting& xSetting ) { xRedBarracksSetting = xSetting; }
        void SetBlueBarracksSetting( BarracksSetting& xSetting ) { xBlueBarracksSetting = xSetting; }

    private:
        static int nTimeSpace;  // 刷怪间隔时间( 单位: 秒 )
        static int nCount;      // 每次刷怪数量
        static int nRadius;     // 刷怪半径
        static int nType;       // 刷怪阵营, 目前只能为 0

        int nBarracksID;        // 兵营ID
        BarracksSetting xRedBarracksSetting;
        BarracksSetting xBlueBarracksSetting;
    };

    class CampMonster
    {
    public:
        int GetID() const { return nID; }
        float GetPosX() const { return fPosX; }
        float GetPosY() const { return fPosY; }
        float GetDirX() const { return fDirX; }
        float GetDirY() const { return fDirY; }
        float GetBodySize() const { return fBodySize; }

        void SetID( int nValue ) { nID = nValue; }
        void SetPosX( float fValue ) { fPosX = fValue; }
        void SetPosY( float fValue ) { fPosY = fValue; }
        void SetDirX( float fValue ) { fDirX = fValue; }
        void SetDirY( float fValue ) { fDirY = fValue; }
        void SetBodySize( float fValue ) { fBodySize = fValue; }

		void SetAngle(int ID){nAngle = ID;}
		int GetAngle() const {return nAngle;}
    private:
        int nID;
        float fPosX;
        float fPosY;
        float fDirX;
        float fDirY;
        float fBodySize;

		int  nAngle;
    };

	class BossMonster : public CampMonster
	{
	public:
		int GetRouteID() const { return nRouteID; }
		 void SetRouteID( int nValue ) { nRouteID = nValue; }
	private:
		int nRouteID;
	};

    class NormalMonster : public CampMonster
    {
    public:
        int GetTimeSpace() const { return nTimeSpace; }
        int GetString() const { return nStringID; }

        void SetTimeSpace( int nValue ) { nTimeSpace = nValue; }
        void SetString( int nValue ) { nStringID = nValue; }
    private:
        int nTimeSpace;     // 刷新间隔( 单位分钟 )
        int nStringID;      // 刷新时的广播字串
    };

    // 获得地图设定( 通过索引 )
    const MapSetting* GetMapSetting() const;

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

	//int GetSignUpKeepTime() const {return vecSignUpTimeSetting.GetKeepTime();}
	//int GetPrepareTimeKeepTime() const {return vecPrepareTimeSetting.GetKeepTime();}
	int GetEnterTimeKeepTime() const {return vecEnterTimeSetting.GetKeepTime();}
	int GetFightTimeKeepTime() const {return vecFightTimeSetting.GetKeepTime();}
	int GetEndTimeKeepTime() const {return vecEndTimeSetting.GetKeepTime();}

    // 获得怪物设定
    const MonsterSetting* GetMonsterSetting( int nMonsterId ) const;

    // 加载设定
	virtual bool LoadGameBattleConfig(const char* FilePath);//加载函数

	const CKingdomMap& GetKingdomMap() const {return xKongdomMap;}
	
	const EnterBuff& GetEnterBuff() const {return xEnterBuff;}

	const SignUpSetting& GetSignUpSetting() const;

    const RefreshSetting* GetRefreshSetting( int nBarracksID ) const;

    int GetGetRefreshSettingCount() const;
    const RefreshSetting* GetRefreshSettingByIndex( unsigned int nIndex ) const;

    int GetRedCampMonsterCount() const;
    const CampMonster* GetRedCampMonster( int nIndex ) const;

    int GetBlueCampMonsterCount() const;
    const CampMonster* GetBlueCampMonster( int nIndex ) const;

	const void GetNormalMonster(std::map< int,NormalMonster>& map) const;

	const BossMonster& GetRedBoss() const {return m_RedBoss;}

	const BossMonster& GetBlueBoss() const {return m_BlueBoss;}

	int GetMaxGameGuildGeneralBattleMaxTime() const {return GetEnterTimeKeepTime() + GetFightTimeKeepTime() + GetEndTimeKeepTime()+GetGameGuildGeneralBattleDiffTime();}
	int GetGameGuildGeneralBattleDiffTime() const {return BattleDiffTime;}
protected:

    typedef std::map< int, KillSetting > KillSettingMap;
    typedef KillSettingMap::const_iterator KillSettingMapIter;
    
    typedef std::vector< KillSetting > KillSettingVector;
    typedef KillSettingVector::const_reverse_iterator KillSettingVectorIter;

    typedef std::map< int, MonsterSetting > MonsterSettingMap;
    typedef MonsterSettingMap::const_iterator MonsterSettingMapIter;

    virtual bool LoadMapSetting( MeXmlElement* pElement );
    virtual bool LoadTimeSetting( MeXmlElement* pElement );
    virtual bool LoadEnterSetting( MeXmlElement* pElement );
    virtual bool LoadResourceSetting( MeXmlElement* pElement );
    virtual bool LoadKillSetting( MeXmlElement* pElement );
    virtual bool LoadMonsterSetting( MeXmlElement* pElement );
	virtual bool LoadKingdomMapSetting( MeXmlElement* pElement );
	virtual bool LoadEnterBuff( MeXmlElement* pElement );
protected:
    MapSetting		  vecMapSetting;            // 地图设定
    //TimeSetting		vecSignUpTimeSetting;     // 报名时间
   //TimeSetting		vecPrepareTimeSetting;    // 准备时间
    TimeSetting		vecEnterTimeSetting;      // 进入时间
    TimeSetting		vecFightTimeSetting;      // 战斗时间
    TimeSetting		vecEndTimeSetting;        // 结束时间
    EnterSetting xEnterSetting;                 // 进入设定
    KillSettingMap mapKillerSetting;            // 杀人设定
    KillSettingVector vecBeKillSetting;         // 被杀设定
    KillSettingMap mapTotalKillSetting;         // 杀人总数设定
    ResourceSetting xResourceSetting;           // 积分设定
    KillSetting xFirstKillSetting;              // 第一次杀人设定
    MonsterSettingMap mapMonsterSetting;        // 怪物设定
	CKingdomMap xKongdomMap;					// 主城地图设定
	EnterBuff xEnterBuff;						// 进入的时候添加的BUff

	typedef std::map< int, RefreshSetting > RefreshSettingMap;
    typedef RefreshSettingMap::const_iterator RefreshSettingMapIter;

    typedef std::vector< CampMonster > CampMonsterVector;

    SignUpSetting xSignUpSetting;
    RefreshSettingMap mapRefreshSetting;
    CampMonsterVector vecRedCampMonster;
    CampMonsterVector vecBlueCampMonster;
	std::map< int,NormalMonster> xNormalMonster;       // 中立怪刷新

	BossMonster m_RedBoss;
	BossMonster m_BlueBoss;

	int BattleDiffTime;
};
inline const GameGuildGeneralBattleConfig::RefreshSetting* GameGuildGeneralBattleConfig::GetRefreshSetting( int nBarracksID ) const
{
    RefreshSettingMapIter iter = mapRefreshSetting.find( nBarracksID );
    if ( iter == mapRefreshSetting.end() )
    { return NULL; }

    return &( iter->second );
}
inline int GameGuildGeneralBattleConfig::GetRedCampMonsterCount() const
{
    return static_cast< int >( vecRedCampMonster.size() );
}

inline const GameGuildGeneralBattleConfig::CampMonster* GameGuildGeneralBattleConfig::GetRedCampMonster( int nIndex ) const
{
    if ( nIndex >= GetRedCampMonsterCount() )
    { return NULL; }

    return &( vecRedCampMonster.at( nIndex ) );
}
inline int GameGuildGeneralBattleConfig::GetBlueCampMonsterCount() const
{
    return static_cast< int >( vecBlueCampMonster.size() );
}
inline const GameGuildGeneralBattleConfig::CampMonster* GameGuildGeneralBattleConfig::GetBlueCampMonster( int nIndex ) const
{
    if ( nIndex >= GetBlueCampMonsterCount() )
    { return NULL; }

    return &( vecBlueCampMonster.at( nIndex ) );
}

inline int GameGuildGeneralBattleConfig::GetGetRefreshSettingCount() const
{
     return static_cast< int >( mapRefreshSetting.size() );
}

inline const GameGuildGeneralBattleConfig::RefreshSetting* GameGuildGeneralBattleConfig::GetRefreshSettingByIndex( unsigned int nIndex ) const
{
    if ( nIndex >= mapRefreshSetting.size() )
    { return NULL; }

    RefreshSettingMapIter iter = mapRefreshSetting.begin();
    advance( iter, nIndex );

    return &( iter->second );
}
inline const GameGuildGeneralBattleConfig::MapSetting* GameGuildGeneralBattleConfig::GetMapSetting() const
{
   return &vecMapSetting;
}

inline const GameGuildGeneralBattleConfig::EnterSetting& GameGuildGeneralBattleConfig::GetEnterSetting() const
{
    return xEnterSetting;
}

inline const GameGuildGeneralBattleConfig::KillSetting* GameGuildGeneralBattleConfig::GetKillerSetting( int nCount ) const
{
    KillSettingMapIter iter = mapKillerSetting.find( nCount );
    if ( iter == mapKillerSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline const GameGuildGeneralBattleConfig::KillSetting* GameGuildGeneralBattleConfig::GetTotalKillSetting( int nCount ) const
{
    KillSettingMapIter iter = mapTotalKillSetting.find( nCount );
    if ( iter == mapTotalKillSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline const GameGuildGeneralBattleConfig::KillSetting* GameGuildGeneralBattleConfig::GetBeKillSetting( int nCount ) const
{
    for ( KillSettingVectorIter iter = vecBeKillSetting.rbegin(); iter != vecBeKillSetting.rend(); ++iter )
    {
        if ( nCount >= iter->GetCount() )
        { return &( *iter ); }
    }

    return NULL;
}

inline const GameGuildGeneralBattleConfig::MonsterSetting* GameGuildGeneralBattleConfig::GetMonsterSetting( int nMonsterID ) const
{
    MonsterSettingMapIter iter = mapMonsterSetting.find( nMonsterID );
    if ( iter == mapMonsterSetting.end() )
    { return NULL; }

    return &( iter->second );
}
inline const GameGuildGeneralBattleConfig::SignUpSetting& GameGuildGeneralBattleConfig::GetSignUpSetting() const
{
    return xSignUpSetting;
}
inline const void GameGuildGeneralBattleConfig::GetNormalMonster(std::map< int,NormalMonster>& map) const
{
	map = xNormalMonster;
}