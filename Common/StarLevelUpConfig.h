#ifndef __STARLEVELUPCONFIG_H__
#define __STARLEVELUPCONFIG_H__

/************************************************************************
    MinEquipmentLevel       װ����С���Ƶȼ�
    MaxEquipmentLevel       װ��������Ƶȼ�
    StarLevel               װ��Ŀǰ�Ǽ�
    LossToLevel             ʧ�ܵ��䵽�Ǽ�
    Probability             ���Ǹ���
    Price                   ���Ǽ�Ǯ
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
    unsigned short ustMinEquipmentLevel;    // װ��������С�ȼ�
    unsigned short ustMaxEquipmentLevel;    // װ���������ȼ�
    unsigned char uchStarLevel;             // ��ǰ�ȼ�
    unsigned char uchLossToLevel;           // ʧ�ܵ����ĵȼ�
    float         fProbability;             // ���Ǹ���
    int           nCostMoney;               // ���ѽ�Ǯ
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
    unsigned short m_ustItemID;             // Ҫ��������ƷID
    unsigned short m_ustMaterialID;         // ��Ҫʹ�õĲ���
    unsigned short m_ustNewItemID;          // �����ɹ����µ�ID
    unsigned short m_ustMaxCount;           // ������
    unsigned int m_nCostMoney;              // ���ѵĽ�Ǯ
    ModulusVector m_vecModulus;
};

struct SStarActivation
{
    enum EConstDefine
    {
        EConstDefine_StarActivationStartLevel = 7, // ��ͬ�Ǽ������Կ�ʼ�ǵȼ�
        EConstDefine_StarActivationStartCount = 8, // ͬ�����������Եļ���
    };

    struct SEffect
    {
        uint8  startCount       ; // ��ʼ�������
        uint8  endCount         ; // �����������
        uint8  type             ; // �ӵ�Ч������
        CustomValue value       ; // ֵ
    };

    typedef std::vector<SEffect>      EffectContainer;
    typedef EffectContainer::iterator EffectContainerItr;

    struct SStarInfo 
    {
        uint8           level;   // �ǵĵȼ�
        EffectContainer effects; // Ч��ֵ

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
        uint8  type ;       // �ӵ�Ч������
        CustomValue value;  // ֵ
    };

    typedef std::vector<SEffect>      EffectContainer;
    typedef EffectContainer::iterator EffectContainerItr;

    struct SStampInfo 
    {
        uint8           count;   // ����
        EffectContainer effects; // Ч��ֵ

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

		float fModulus;		//�ɹ�����
		float fDropOne;		//��1�Ǹ���
		float fDropTwo;		//��2�Ǹ���
		float fDropThree;	//��3�Ǹ���
		int	  nMoney;		//����
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
	 unsigned short m_ustMaterialID;         // ��Ҫʹ�õĲ���ID
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

public: // ����
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
    StarLevelUpData*          GetStarLevelUpData( unsigned short ustEquipmentLevel, unsigned char uchStarLevel );   // װ���ȼ�, �ǵȼ� �������
    StarLevelUpDataContainer* GetStarLevelUpDataByIndex( int nIndex );
    
    float                     GetItemStarLevelModulus( uint32 equipType, uint16 starlevel );                        // �õ�ָ��װ������ָ���Ǽ���ϵ��
    const MoveStarLevelUp*    GetMoveStarLevelUp( unsigned short ustItemID ) const;
    SStarActivation::SEffect* GetStarActivationEffect( uint8 level, uint8 count );
    bool                      GetStampActivationEffect( uint8 stampCount ,OUT SStampActivation::EffectContainer& outputEffect );
	const TransferStarMaterial* GetTransferStarMaterial( unsigned short ustItemID ) const;
	SSoul					  GetSoulData() { return _sSoul; }

    //uint8                     GetEquipStampAttrAddition( SCharItem* pCharItem, uint16 attrType );                   // ���װ���������Լӳ�
        
protected: // ����
    bool AddMoveStarLevelUp( const MoveStarLevelUp& xData );
	bool AddTransferStarMaterial( const TransferStarMaterial& xData );

private: // ����
    LevelStarLevelUpDataContainer m_mapStarLevelUpData; // ��װ��������Ƶȼ�������
    StarLevelEffectContainer      _starLeveEffects;
    EffectLinkContainer           _effectLinks;
    MoveStarLevelUpMap            m_mapMoveStarLevelUp; // ����ʯ����
    SStarActivation               _starActivation;      // �Ǽ���
    SStampActivation              _stampActivation;     // ���̼���
	TransferStarMaterialMap		  m_mapTransferStarMaterial; //ת��
	SSoul						  _sSoul;				//���̼ӳɰٷֱ�
};

#define theStarLevelUpConfig StarLevelUpConfig::Instance()

#endif // __STARLEVELUPCONFIG_H__
