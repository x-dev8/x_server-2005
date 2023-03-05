#ifndef __STARLEVELUPCONFIG_H__
#define __STARLEVELUPCONFIG_H__

/************************************************************************
    MinEquipmentLevel       装备最小限制等级
    MaxEquipmentLevel       装备最大限制等级
    StarLevel               装备目前星级
    LossToLevel             失败掉落到星级
    Probability             升星概率
    Price                   升星加钱
************************************************************************/

#include "MeRTLibs.h"
#include "GlobalDef.h"
#include "Singleton.h"

class StarLevelUpData
{
public:
    StarLevelUpData()
    {
        ustMinEquipmentLevel = 0;
        ustMaxEquipmentLevel = 0;
        uchStarLevel         = 0;
        uchLossToLevel       = 0;
        fProbability         = 0.0f;
        nCostMoney           = 0;
    }

    const unsigned short GetMinEquipmentLevel() const { return ustMinEquipmentLevel; }
    const unsigned short GetMaxEquipmentLevel() const { return ustMaxEquipmentLevel; }
    const unsigned char  GetStarLevel()   const { return uchStarLevel; }
    const unsigned char  GetLossToLevel() const { return uchLossToLevel; }
    const float          GetProbability() const { return fProbability; }
    const int            GetCostMoney()   const { return nCostMoney; }

    void SetMinEquipmentLevel( unsigned short ustMinLevel ) { ustMinEquipmentLevel = ustMinLevel; }
    void SetMaxEquipmentLevel( unsigned short ustMaxLevel ) { ustMaxEquipmentLevel = ustMaxLevel; }
    void SetStarLevel( unsigned char uchLevel ) { uchStarLevel = uchLevel; }
    void SetLossToLevel( unsigned char uchLevel ) { uchLossToLevel = uchLevel; }
    void SetProbability( float fPro ) { fProbability = fPro; }
    void SetCostMoney( int nMoney ) { nCostMoney = nMoney; }

private:
    unsigned short ustMinEquipmentLevel;    // 装备限制最小等级
    unsigned short ustMaxEquipmentLevel;    // 装备限制最大等级
    unsigned char uchStarLevel;             // 当前等级
    unsigned char uchLossToLevel;           // 失败掉到的等级
    float         fProbability;             // 升星概率
    int           nCostMoney;               // 花费金钱
};

class MoveStarLevelUp
{
protected:
    typedef std::vector< float > ModulusVector;
public:
    MoveStarLevelUp()
    {
        m_ustItemID = 0;
        m_ustMaterialID = 0;
        m_ustNewItemID = 0;
        m_nCostMoney = 0;
        m_ustMaxCount = 0;
        m_vecModulus.clear();
    }

    unsigned short GetItemID() const { return m_ustItemID; }
    unsigned short GetMaterialID() const { return m_ustMaterialID; }
    unsigned short GetNewItemID() const { return m_ustNewItemID; }
    unsigned short GetMaxCount() const { return m_ustMaxCount; }    
    unsigned int GetCostMoney() const { return m_nCostMoney; }
    float GetModulus( unsigned char uchCount ) const
    {
        if ( uchCount >= m_vecModulus.size() )
        { return 0.0f; }

        return m_vecModulus.at( uchCount );
    }

    void SetItemID( unsigned short ustValue ) { m_ustItemID = ustValue; }
    void SetMaterialID( unsigned short ustValue ) { m_ustMaterialID = ustValue; }
    void SetNewItemID( unsigned short ustValue ) { m_ustNewItemID = ustValue; }
    void SetMaxCount( unsigned short ustValue ) { m_ustMaxCount = ustValue; }
    void SetCostMoney( unsigned int nValue ) { m_nCostMoney = nValue; }

    void ResizeModulus( unsigned char uchCount ) { m_vecModulus.resize( uchCount ); }
    bool AddModulus( unsigned char uchCount, float fModulus )
    {
        if ( uchCount >= m_vecModulus.size() )
        { return false; }

        m_vecModulus[ uchCount ] = fModulus;
        return true;
    }

private:
    unsigned short m_ustItemID;             // 要升级的物品ID
    unsigned short m_ustMaterialID;         // 需要使用的材料
    unsigned short m_ustNewItemID;          // 升级成功的新的ID
    unsigned short m_ustMaxCount;           // 最大个数
    unsigned int m_nCostMoney;              // 花费的金钱
    ModulusVector m_vecModulus;
};

struct SStarActivation
{
    enum EConstDefine
    {
        EConstDefine_StarActivationStartLevel = 7, // 有同星激活属性开始星等级
        EConstDefine_StarActivationStartCount = 8, // 同星至少有属性的件数
    };

    struct SEffect
    {
        uint8  startCount       ; // 开始区间个数
        uint8  endCount         ; // 结束区间个数
        uint8  type             ; // 加的效果类型
        CustomValue value       ; // 值
    };

    typedef std::vector<SEffect>      EffectContainer;
    typedef EffectContainer::iterator EffectContainerItr;

    struct SStarInfo 
    {
        uint8           level;   // 星的等级
        EffectContainer effects; // 效果值

        SEffect* GetEffect( uint8 count );
    };

    typedef std::vector<SStarInfo>       SStarInfoContainer;
    typedef SStarInfoContainer::iterator SStarInfoContainerItr;

    SStarInfoContainer starInfos;

    SStarActivation::SEffect* GetEffect( uint8 level, uint8 count );
};

struct SStampActivation
{
    struct SEffect
    {
        uint8  type ;       // 加的效果类型
        CustomValue value;  // 值
    };

    typedef std::vector<SEffect>      EffectContainer;
    typedef EffectContainer::iterator EffectContainerItr;

    struct SStampInfo 
    {
        uint8           count;   // 个数
        EffectContainer effects; // 效果值

        bool GetEffect( OUT SStampActivation::EffectContainer& outputEffect );
    };

    typedef std::vector<SStampInfo>       SStampInfoContainer;
    typedef SStampInfoContainer::iterator SStampInfoContainerItr;

    SStampInfoContainer stampInfos;

    bool GetEffect( uint8 stampCount ,OUT SStampActivation::EffectContainer& outputEffect );
};

struct SSoul
{
	SSoul()
	{
		nMinPer = 0;
		nMaxPer = 0;
	}
	int nMinPer;
	int nMaxPer;
};

class TransferStarMaterial
{
	struct SMaterial
	{
		SMaterial()
		{
			fModulus = 0.0f;
			fDropOne = 0.0f;
			fDropTwo = 0.0f;
			fDropThree = 0.0f;
			nMoney = 0;
		}

		float fModulus;		//成功概率
		float fDropOne;		//掉1星概率
		float fDropTwo;		//掉2星概率
		float fDropThree;	//掉3星概率
		int	  nMoney;		//花费
	};

	typedef std::vector< SMaterial > ModulusVector;

public:
	TransferStarMaterial()
	{
		m_ustMaterialID = 0;
		m_vecModulus.clear();
		m_vecModulus.resize(SCharItem::EL_StarMax);
	}

	unsigned short GetMaterialID() const { return m_ustMaterialID; }
	float GetModulus( unsigned char uchStarLevel ) const
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0)
			return 0.0f; 

		return m_vecModulus[uchStarLevel - 1].fModulus;
	}
	float GetDropOne( unsigned char uchStarLevel ) const
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0)
			return 0.0f; 

		return m_vecModulus[uchStarLevel - 1].fDropOne;
	}
	float GetDropTwo( unsigned char uchStarLevel ) const
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0)
			return 0.0f; 

		return m_vecModulus[uchStarLevel - 1].fDropTwo;
	}
	float GetDropThree( unsigned char uchStarLevel ) const
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0)
			return 0.0f; 

		return m_vecModulus[uchStarLevel - 1].fDropThree;
	}
	int GetCostMoney( unsigned char uchStarLevel ) const
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0)
			return 0; 

		return m_vecModulus[uchStarLevel - 1].nMoney;
	}

	void SetMaterialID( unsigned short ustValue ) { m_ustMaterialID = ustValue; }

	bool AddModulus( unsigned char uchStarLevel, float fModulus )
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0 )
			return false; 

		m_vecModulus[uchStarLevel - 1].fModulus = fModulus;
		return true;
	}
	bool AddDropOne( unsigned char uchStarLevel, float fDropOne )
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0 )
			return false; 

		m_vecModulus[uchStarLevel - 1].fDropOne = fDropOne;
		return true;
	}
	bool AddDropTwo( unsigned char uchStarLevel, float fDropTwo )
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0 )
			return false; 

		m_vecModulus[uchStarLevel - 1].fDropTwo = fDropTwo;
		return true;
	}
	bool AddDropThree( unsigned char uchStarLevel, float fDropThree )
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0 )
			return false; 

		m_vecModulus[uchStarLevel - 1].fDropThree = fDropThree;
		return true;
	}
	bool AddMoney( unsigned char uchStarLevel, int nMoney )
	{
		if ( uchStarLevel > m_vecModulus.size() || uchStarLevel <= 0 )
			return false; 

		m_vecModulus[uchStarLevel - 1].nMoney = nMoney;
		return true;
	}

private:
	 unsigned short m_ustMaterialID;         // 需要使用的材料ID
	 ModulusVector	m_vecModulus;
};

class StarLevelUpConfig : public ICfgSingletion<StarLevelUpConfig>
{
public:
    struct SEffectLink
    {
        uint32 type;
        uint16 effectId;
    };

    struct SStarLevelEffect
    {
        typedef std::vector<float>              LevelModulusContainer;
        typedef LevelModulusContainer::iterator ItrLevelModulusContainer;
        
        uint16                id;
        LevelModulusContainer levelModulus;
    };

    typedef std::vector<StarLevelUpData>                        StarLevelUpDataContainer;
    typedef StarLevelUpDataContainer::iterator                  VectorIter;
    typedef std::map<unsigned short, StarLevelUpDataContainer > LevelStarLevelUpDataContainer;
    typedef LevelStarLevelUpDataContainer::iterator             MapIter;

    typedef std::map< uint16, SStarLevelEffect > StarLevelEffectContainer;
    typedef StarLevelEffectContainer::iterator   ItrStarLevelEffectContainer;

    typedef std::vector< SEffectLink >    EffectLinkContainer;
    typedef EffectLinkContainer::iterator ItrEffectLinkContainer;

    typedef std::map< unsigned short , MoveStarLevelUp > MoveStarLevelUpMap;
    typedef MoveStarLevelUpMap::iterator MoveStarLevelUpMapIter;
    typedef MoveStarLevelUpMap::const_iterator MoveStarLevelUpMapConstIter;

	typedef std::map< unsigned short, TransferStarMaterial > TransferStarMaterialMap;
	typedef TransferStarMaterialMap::iterator TransferStarMaterialMapIter;
	typedef TransferStarMaterialMap::const_iterator TransferStarMaterialMapConstIter;

public: // 方法
	StarLevelUpConfig() { m_mapStarLevelUpData.clear();} 
    ~StarLevelUpConfig() {}
// by cloud
//     static StarLevelUpConfig& Instance()
//     {
//         static StarLevelUpConfig s_xStarLevelUp;
//         return s_xStarLevelUp;
//     }

	virtual bool              LoadResourceConfig( const char* pszConfig );
	virtual void			  OnReloadFinished();

    bool                      AddStarLevelUpData( const StarLevelUpData& xData );
    uint16                    GetStarLevelUpDataCount() { return static_cast<unsigned short>( m_mapStarLevelUpData.size() ); }
    StarLevelUpData*          GetStarLevelUpData( unsigned short ustEquipmentLevel, unsigned char uchStarLevel );   // 装备等级, 星等级 获得属性
    StarLevelUpDataContainer* GetStarLevelUpDataByIndex( int nIndex );
    
    float                     GetItemStarLevelModulus( uint32 equipType, uint16 starlevel );                        // 得到指定装备类型指定星级的系数
    const MoveStarLevelUp*    GetMoveStarLevelUp( unsigned short ustItemID ) const;
    SStarActivation::SEffect* GetStarActivationEffect( uint8 level, uint8 count );
    bool                      GetStampActivationEffect( uint8 stampCount ,OUT SStampActivation::EffectContainer& outputEffect );
	const TransferStarMaterial* GetTransferStarMaterial( unsigned short ustItemID ) const;
	SSoul					  GetSoulData() { return _sSoul; }

    //uint8                     GetEquipStampAttrAddition( SCharItem* pCharItem, uint16 attrType );                   // 获得装备铭刻属性加成
        
protected: // 方法
    bool AddMoveStarLevelUp( const MoveStarLevelUp& xData );
	bool AddTransferStarMaterial( const TransferStarMaterial& xData );

private: // 属性
    LevelStarLevelUpDataContainer m_mapStarLevelUpData; // 用装备最大限制等级做索引
    StarLevelEffectContainer      _starLeveEffects;
    EffectLinkContainer           _effectLinks;
    MoveStarLevelUpMap            m_mapMoveStarLevelUp; // 移星石升级
    SStarActivation               _starActivation;      // 星激活
    SStampActivation              _stampActivation;     // 铭刻激活
	TransferStarMaterialMap		  m_mapTransferStarMaterial; //转星
	SSoul						  _sSoul;				//铭刻加成百分比
};

#define theStarLevelUpConfig StarLevelUpConfig::Instance()

#endif // __STARLEVELUPCONFIG_H__
