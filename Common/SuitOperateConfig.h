#ifndef __SUITLEVELUPCONFIG_H__
#define __SUITLEVELUPCONFIG_H__

#include <map>
#include <vector>
#include <algorithm>
#include <set>

enum ESuitLevelUpDefine
{
    ECD_Attribute_Level = 1, 
    ECD_Attribute_ID    = 2,
};

class SuitLevelUp
{
public:
    SuitLevelUp() : uchLevel( 0 ), uchAttributeType( 0 ), ustAttributeValue( 0 ), ustModulus( 0 ) { }

    void SetLevel( unsigned char chValue )           { uchLevel = chValue; }
    void SetAttributeType( unsigned char chValue )   { uchAttributeType = chValue; }
    void SetAttributeValue( unsigned short stValue ) { ustAttributeValue = stValue; }
    void SetModulus( unsigned short stValue )        { ustModulus = stValue; }

    const unsigned char GetLevel() const           { return uchLevel; }
    const unsigned char GetAttributeType() const   { return uchAttributeType; }
    const unsigned short GetAttributeValue() const { return ustAttributeValue; }
    const unsigned short GetModulus() const        { return ustModulus; }

private:
    unsigned char uchLevel;           // װ��ǿ���ȼ�
    unsigned char uchAttributeType;   // ��Ӧ���Ա����������  1 = �ȼ�  2 = ID
    unsigned short ustAttributeValue; // ��Ӧ���Ա������ֵ
    unsigned short ustModulus;        // ǿ���ɹ��Ļ���ϵ��
};

class SkillSuitLevelUp : public SuitLevelUp
{
public:
    SkillSuitLevelUp() : SuitLevelUp(), ustExtendModulus( 0 ) {}

    void SetExtendModulus( unsigned short stValue ) { ustExtendModulus = stValue; }
    const unsigned short GetExtendModulus() const   { return ustExtendModulus; }

    static void SetMaxLevel( unsigned char chValue ) { uchMaxLevel = chValue; }
    static unsigned char GetMaxLevel() { return uchMaxLevel; }

private:
    static unsigned char uchMaxLevel; // װ��ǿ�������ȼ�
    unsigned short ustExtendModulus;  // ǿ���ɹ��ļӳ�ϵ�� ָ������+2��ʯͷǿ���ȼ�0����װ�ļӳ�ϵ����ʽ ����ʯ�ȼ�-�����ȼ���* ϵ��
};

class ChangeCostInfo
{
public:
    void SetCostType( unsigned char chType ) { m_uchType = chType; }
    void SetCostValue( unsigned int nValue ) { m_nValue = nValue; }
    void SetCostCount( unsigned int nValue ) { m_nCount = nValue; }

    const unsigned char GetCostType() const { return m_uchType; }
    const unsigned int GetCostValue() const { return m_nValue; }
    const unsigned int GetCostCount() const { return m_nCount; }
private:
    unsigned char m_uchType;    // ��Ӧ��Item.slk �е�CostType
    unsigned int m_nValue;      // ��Ӧ��Item.slk �е�CostValue
    unsigned int m_nCount;      // ��Ӧ��Item.slk �� ��Ʒ��Ϊ���ҵ�����
};

class ElementSuitLevelUp : public SuitLevelUp, public ChangeCostInfo
{
public:
    ElementSuitLevelUp() : SuitLevelUp(), ChangeCostInfo() {}

    static void SetMaxLevel( unsigned char chValue ) { uchMaxLevel = chValue; }
    static unsigned char GetMaxLevel() { return uchMaxLevel; }

private:
    static unsigned char uchMaxLevel; // װ��ǿ�������ȼ�
};

class SkillSuitChange
{
protected:
    typedef std::set< unsigned short > EquipIDSet;
    typedef EquipIDSet::iterator EquipIDSetIter;
    typedef EquipIDSet::const_iterator EquipIDSetConstIter;

public:
    bool AddEquipID( unsigned char uchSex, unsigned short ustID )
    {
        if( uchSex >= 2 )
        { return false; }

        return setEquipID[uchSex].insert( ustID ).second;
    }

    void GetEquipID( std::vector< unsigned short >& vecEquipID, unsigned char uchSex, unsigned short ustExceptID ) const
    {
        vecEquipID.clear();
        if ( uchSex >= 2 )
        { return; }

        for ( EquipIDSetConstIter iter = setEquipID[uchSex].begin(); iter != setEquipID[uchSex].end(); ++iter )
        {
            if ( *iter != ustExceptID )
            {
                vecEquipID.push_back( *iter );
            }
        }
    }
private:
    EquipIDSet setEquipID[2];
};

class ElementMove
{
protected:
    typedef std::vector< float > ModulusVector;
public:
    ElementMove() : fBaseModulus( 0.0f ), ustMaterialID( 0 ), ustMaxCount( 0 ), nCostMoney ( 0 )
    {
        vecModulus.clear();
    }

    void SetBaseModulus( float fValue ) { fBaseModulus = fValue; }
    void SetMaterialID( unsigned short ustValue ) { ustMaterialID = ustValue; }
    void SetMaxCount( unsigned short ustValue ) { ustMaxCount = ustValue; }
    void SetCostMoney( unsigned int nValue ) { nCostMoney = nValue; }
    bool AddModulus( unsigned short ustCount, float fValue )
    {
        if ( ustCount >= vecModulus.size() )
        { return false; }

        vecModulus[ustCount] = fValue; 
        return true;
    }

    float GetBaseModulus() const { return fBaseModulus; }
    unsigned short GetMaterialID() const { return ustMaterialID; }
    unsigned short GetMaxCount() const { return ustMaxCount; }
    unsigned int GetCostMoney() const { return nCostMoney; }
    float GetModulus( unsigned short ustCount ) const
    {
        if ( ustCount >= vecModulus.size() )
        { return 0.0f; }

        return vecModulus.at( ustCount );
    }

    void ResizeModulus( unsigned short ustCount ) { vecModulus.resize( ustCount ); }

private:
    float fBaseModulus;                 // ��������
    unsigned short ustMaterialID;       // ��Ҫ�ļӳɸ��ʵ���ID
    unsigned short ustMaxCount;         // ���ӳɸ��ʵ�������
    unsigned int nCostMoney;            // ���ѵĽ�Ǯ
    ModulusVector vecModulus;           // ��������
};

#ifdef GAME_CLIENT
struct SkillSuitAttribute
{
	std::string attributeName;
	std::string attributePicture;
	unsigned int attributePictureWidth;
	unsigned int attributePictureHeight;

	typedef std::map<unsigned short, SkillSuitAttribute> AttributeSet;
};
#endif

#define theSuitOperateConfig SuitOperateConfig::Instance()

class SuitOperateConfig
{
protected:
    typedef std::vector< SkillSuitLevelUp > SkillSuitLevelUpVertor;
    typedef SkillSuitLevelUpVertor::iterator SkillSuitLevelUpVertorIter;
    typedef SkillSuitLevelUpVertor::const_iterator SkillSuitLevelUpVertorConstIter;

    typedef std::map< unsigned char, SkillSuitLevelUpVertor > SkillSuitLevelUpMap;
    typedef SkillSuitLevelUpMap::iterator SkillSuitLevelUpMapIter;
    typedef SkillSuitLevelUpMap::const_iterator SkillSuitLevelUpMapConstIter;

    typedef std::map< unsigned char, SkillSuitLevelUpMap > LevelSkillSuitLevelUpMap;
    typedef LevelSkillSuitLevelUpMap::iterator LevelSkillSuitLevelUpMapIter;
    typedef LevelSkillSuitLevelUpMap::const_iterator LevelSkillSuitLevelUpMapConstIter;

    // �����ᴿ
    typedef std::vector< ElementSuitLevelUp > ElementSuitLevelUpVertor;
    typedef ElementSuitLevelUpVertor::iterator ElementSuitLevelUpVertorIter;
    typedef ElementSuitLevelUpVertor::const_iterator ElementSuitLevelUpVertorConstIter;

    typedef std::map< unsigned char, ElementSuitLevelUpVertor > ElementSuitLevelUpMap;
    typedef ElementSuitLevelUpMap::iterator ElementSuitLevelUpMapIter;
    typedef ElementSuitLevelUpMap::const_iterator ElementSuitLevelUpMapConstIter;

    typedef std::map< unsigned char, unsigned int > ElementModulusMap;
    typedef ElementModulusMap::iterator ElementModulusMapIter;
    typedef ElementModulusMap::const_iterator ElementModulusMapConstIter;

    // ������װת��
    typedef std::map< unsigned char, SkillSuitChange > SkillSuitChangeMap;
    typedef SkillSuitChangeMap::iterator SkillSuitChangeMapIter;
    typedef SkillSuitChangeMap::const_iterator SkillSuitChangeMapConstIter;

    typedef std::map< unsigned char, SkillSuitChangeMap> LevelSkillSuitChangeMap;
    typedef LevelSkillSuitChangeMap::iterator LevelSkillSuitChangeMapIter;
    typedef LevelSkillSuitChangeMap::const_iterator LevelSkillSuitChangeMapConstIter;

    typedef std::vector< ChangeCostInfo > SuitChangeCost;
    typedef SuitChangeCost::iterator SuitChangeCostIter;
    typedef SuitChangeCost::const_iterator SuitChangeCostConstIter;

    typedef std::map< unsigned char, SuitChangeCost > LevelSuitChangeCostMap;
    typedef LevelSuitChangeCostMap::iterator LevelSuitChangeCostMapIter;
    typedef LevelSuitChangeCostMap::const_iterator LevelSuitChangeCostMapConstIter;

    typedef std::map< unsigned char, unsigned int > CostMoneyMap;
    typedef CostMoneyMap::iterator CostMoneyMapIter;
    typedef CostMoneyMap::const_iterator CostMoneyMapConstIter;

public:
    static SuitOperateConfig& Instance()
    {
        static SuitOperateConfig s_xConfig;
        return s_xConfig;
    }

    const SkillSuitLevelUp* GetSkillEquipData( unsigned char uchEquipLevel, unsigned char uchEquipID, unsigned char uchLevel ) const;
    const ElementSuitLevelUp* GetElementEquipData( unsigned char uchEquipLevel, unsigned char uchLevel ) const;
    unsigned int GetElementTotalModulus( unsigned char uchEquipLevel ) const;
    unsigned char GetElementEquipLevelByRand( unsigned char uchEquipLevel, unsigned int nRandNumber ) const;

    bool IsCheckSkillSuitChangeLevel() const { return m_bCheckSkillSuitChangeLevel; }
    unsigned char GetMinSkillSuitChangeLevel() const { return m_uchMinSkillSuitChangeLevel; } 
    const ChangeCostInfo* GetSkillSuitChangeCostInfo( unsigned char uchEquipLevel, unsigned char uchSuitLevel ) const;

    unsigned short GetEquipIDByRand( unsigned char uchEquipLevel, unsigned char uchEquipID, unsigned int nRandNumber, unsigned char uchSex, unsigned short ustDefaultID ) const;

    unsigned int GetSkillSuitLevelUpCostMoney( unsigned char uchEquipLevel ) const;
    unsigned int GetElementSuitLevelUpCostMoney( unsigned char uchEquipLevel ) const;
    unsigned int GetElementSuitChangeCostMoney( unsigned char uchEquipLevel ) const;
    unsigned int GetSkillSuitChangeCostMoney( unsigned char uchEquipLevel ) const;

    bool IsExistElementSuitLevelLevel(unsigned char uchEquipLevel);
    unsigned char GetMinElementSuitChangeLevel() const { return m_uchMinElementSuitChangeLevel; }

    const ElementMove& GetElementMove() const { return m_xElementMove; }
    
    bool LoadSuitLevelUpConfig( const char* szFile );

protected:
    SuitOperateConfig()
    {
        m_mapSkillEquip.clear();
        m_mapElemnetEquip.clear();
        m_mapElementTotalModulus.clear();
        m_mapSkillSuitChangeCost.clear();
    }

    bool AddSkillEquipData( unsigned char uchEquipLevel, unsigned char uchEquipID, SkillSuitLevelUp& xData );
    bool AddElementEquipData( unsigned char uchEquipLevel, ElementSuitLevelUp& xData );
    bool AddElementTotalModulus( unsigned char uchEquipLevel, unsigned int nModulus );
    bool AddSkillSuitChange( unsigned char uchEquipLevel, unsigned char uchEquipID, SkillSuitChange& xChange );
    bool AddSkillSuitChangeCost( unsigned char uchEquipLevel, unsigned char uchSuitLevel, unsigned char uchMaxLevel, ChangeCostInfo& xCost );
    bool AddCostMoney( CostMoneyMap& xCostMoneyMap, unsigned char uchEquipLevel, unsigned int nCostMoney );
    unsigned int GetCostMoney( const CostMoneyMap& xCostMoneyMap, unsigned char uchEquipLevel ) const;
private:
    LevelSkillSuitLevelUpMap m_mapSkillEquip;         // ������װ����
    ElementSuitLevelUpMap m_mapElemnetEquip;          // ������װ�ᴿ
    ElementModulusMap m_mapElementTotalModulus;       // ������ 5���ȼ��ᴿ���ܸ���

    bool m_bCheckSkillSuitChangeLevel;                // ������װת���Ƿ�Ҫ�жϼ�����װ�����ľ����ȼ�
    unsigned char m_uchMinSkillSuitChangeLevel;       // ������װת��Ҫ�����С�����ȼ�
    unsigned char m_uchMinElementSuitChangeLevel;     // ������װת��Ҫ�����С�ᴿ�ȼ�
    LevelSkillSuitChangeMap m_mapSkillSuitChange;     // ������װת��
    LevelSuitChangeCostMap m_mapSkillSuitChangeCost;  // ������װת���ĵ���

    CostMoneyMap m_mapSkillSuitLevelUpCostMoney;      // ������װ�������ѽ�Ǯ
    CostMoneyMap m_mapElementSuitLevelUpCostMoney;    // ������װ�ᴿ���ѽ�Ǯ
    CostMoneyMap m_mapSkillSuitChangeCostMoney;       // ������װת�����ѵĽ�Ǯ
	CostMoneyMap m_mapElementSuitChangeCostMoney;     // ������װת�����ѽ�Ǯ

    ElementMove m_xElementMove;                     // ����ת��

#ifdef GAME_CLIENT
public:
	void AddSkillSuitAttribute(unsigned short ustSuitID,const std::string& attributeName,
		const std::string& attributePicture, unsigned int attributePictureWidth, unsigned int attributePictureHeight) {
		SkillSuitAttribute attr;
		attr.attributeName = attributeName;
		attr.attributePicture = attributePicture;
		attr.attributePictureWidth = attributePictureWidth;
		attr.attributePictureHeight = attributePictureHeight;
		m_attributeSet[ustSuitID] = attr;
	}

	const SkillSuitAttribute& GetSkillSuitAttribute(unsigned short ustSuitID) {
		return m_attributeSet[ustSuitID];
	}

private:
	SkillSuitAttribute::AttributeSet m_attributeSet;  // ������װ��������������
#endif
};

#endif