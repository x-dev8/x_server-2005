#ifndef __CAMPGUILDBATTLECONFIG_H__
#define __CAMPGUILDBATTLECONFIG_H__

#include "CampBattleConfig.h"

#define theCampGuildBattleConfig CampGuildBattleConfig::Instance()

class CampGuildBattleConfig : public CampBattleConfig
{
public:
    static CampGuildBattleConfig& Instance()
    {
        static CampGuildBattleConfig s_xConfig;
        return s_xConfig;
    }

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
           // typedef std::vector< MonsterDataList > MonsterVector;
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

	class OtherReward
	{
	public:
		int GetWinItemID() const {return WinItemID;}
		int GetLoseItemID() const {return LoseItemID;}
		int GetOtherSum() const {return OtheSum;}
		int GetOtherItemID() const {return OtherItemID;}
		int GetWinPoint() const {return WinBattlePoint;}
		int GetLosePoint() const {return LoseBattlePoint;}

		void SetWinItemID(int ID){WinItemID = ID;}
		void SetLoseItemID(int ID){LoseItemID = ID;}
		void SetOtherSum(int Sum){OtheSum = Sum;}
		void SetOtherItemID(int ID){OtherItemID = ID;}
		void SetWinPoint(int Sum){WinBattlePoint = Sum;}
		void SetLosePoint(int Sum){LoseBattlePoint = Sum;}
	private:
		int WinItemID;
		int LoseItemID;
		int OtheSum;
		int OtherItemID;
		int WinBattlePoint;//积分点数 胜利方
		int LoseBattlePoint;//失败方积分点数 可以为负数
	};

    // 加载设定
    virtual bool LoadConfig( const char* szFile );

    const SignUpSetting& GetSignUpSetting() const;

    const RefreshSetting* GetRefreshSetting( int nBarracksID ) const;

    int GetGetRefreshSettingCount() const;
    const RefreshSetting* GetRefreshSettingByIndex( unsigned int nIndex ) const;

    int GetRedCampMonsterCount() const;
    const CampMonster* GetRedCampMonster( int nIndex ) const;

    int GetBlueCampMonsterCount() const;
    const CampMonster* GetBlueCampMonster( int nIndex ) const;

	const void GetNormalMonster(std::map< int,NormalMonster>& map) const;

	const OtherReward& GetOtherReward() const;

	const BossMonster& GetRedBoss() const {return m_RedBoss;}

	const BossMonster& GetBlueBoss() const {return m_BlueBoss;}
protected:
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
	OtherReward m_OtherRweard;
};

inline const CampGuildBattleConfig::SignUpSetting& CampGuildBattleConfig::GetSignUpSetting() const
{
    return xSignUpSetting;
}

inline const CampGuildBattleConfig::RefreshSetting* CampGuildBattleConfig::GetRefreshSetting( int nBarracksID ) const
{
    RefreshSettingMapIter iter = mapRefreshSetting.find( nBarracksID );
    if ( iter == mapRefreshSetting.end() )
    { return NULL; }

    return &( iter->second );
}

inline int CampGuildBattleConfig::GetGetRefreshSettingCount() const
{
     return static_cast< int >( mapRefreshSetting.size() );
}

inline const CampGuildBattleConfig::RefreshSetting* CampGuildBattleConfig::GetRefreshSettingByIndex( unsigned int nIndex ) const
{
    if ( nIndex >= mapRefreshSetting.size() )
    { return NULL; }

    RefreshSettingMapIter iter = mapRefreshSetting.begin();
    advance( iter, nIndex );

    return &( iter->second );
}

inline int CampGuildBattleConfig::GetRedCampMonsterCount() const
{
    return static_cast< int >( vecRedCampMonster.size() );
}

inline const CampGuildBattleConfig::CampMonster* CampGuildBattleConfig::GetRedCampMonster( int nIndex ) const
{
    if ( nIndex >= GetRedCampMonsterCount() )
    { return NULL; }

    return &( vecRedCampMonster.at( nIndex ) );
}

inline int CampGuildBattleConfig::GetBlueCampMonsterCount() const
{
    return static_cast< int >( vecBlueCampMonster.size() );
}

inline const CampGuildBattleConfig::CampMonster* CampGuildBattleConfig::GetBlueCampMonster( int nIndex ) const
{
    if ( nIndex >= GetBlueCampMonsterCount() )
    { return NULL; }

    return &( vecBlueCampMonster.at( nIndex ) );
}
inline const void CampGuildBattleConfig::GetNormalMonster(std::map< int,NormalMonster>& map) const
{
	map = xNormalMonster;
}
inline const CampGuildBattleConfig::OtherReward& CampGuildBattleConfig::GetOtherReward() const
{
	return m_OtherRweard;
}

#endif