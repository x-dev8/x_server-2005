#include "SuitOperateConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"

unsigned char SkillSuitLevelUp::uchMaxLevel = 5;
unsigned char ElementSuitLevelUp::uchMaxLevel = 5;

bool SuitOperateConfig::AddSkillEquipData( unsigned char uchEquipLevel, unsigned char uchEquipID, SkillSuitLevelUp& xData )
{
    if ( xData.GetLevel() > SkillSuitLevelUp::GetMaxLevel() )
    { return false; }

    LevelSkillSuitLevelUpMapIter iter = m_mapSkillEquip.find( uchEquipLevel );
    if ( iter == m_mapSkillEquip.end() )
    {
        SkillSuitLevelUpVertor vecData;
        vecData.resize( SkillSuitLevelUp::GetMaxLevel() + 1 );

        vecData[ xData.GetLevel() ] = xData;

        SkillSuitLevelUpMap mapData;
        mapData.insert( std::make_pair( uchEquipID, vecData ) );
        m_mapSkillEquip.insert( std::make_pair( uchEquipLevel, mapData ) );
    }
    else
    {
        SkillSuitLevelUpMapIter miter = iter->second.find( uchEquipID );
        if ( miter == iter->second.end() )
        {
            SkillSuitLevelUpVertor vecData;
            vecData.resize( SkillSuitLevelUp::GetMaxLevel() + 1 );

            vecData[ xData.GetLevel() ] = xData;
            iter->second.insert( std::make_pair( uchEquipID, vecData ) );
        }
        else
        {
            miter->second[ xData.GetLevel() ] = xData;
        }
    }

    return true;
}

const SkillSuitLevelUp* SuitOperateConfig::GetSkillEquipData( unsigned char uchEquipLevel, unsigned char uchEquipID, unsigned char uchLevel ) const
{
    if ( uchLevel > SkillSuitLevelUp::GetMaxLevel() )
    { return NULL; }

    LevelSkillSuitLevelUpMapConstIter iter = m_mapSkillEquip.find( uchEquipLevel );
    if ( iter == m_mapSkillEquip.end() )
    { return NULL; }

    SkillSuitLevelUpMapConstIter miter = iter->second.find( uchEquipID );
    if ( miter == iter->second.end() )
    { return NULL; }

    if ( uchLevel >= miter->second.size() )
    { return NULL; }
    
    return &( miter->second.at( uchLevel ) );
}

bool SuitOperateConfig::AddElementEquipData( unsigned char uchEquipLevel, ElementSuitLevelUp& xData )
{
    if ( xData.GetLevel() > ElementSuitLevelUp::GetMaxLevel() )
    { return false; }

    ElementSuitLevelUpMapIter iter = m_mapElemnetEquip.find( uchEquipLevel );
    if ( iter == m_mapElemnetEquip.end() )
    {
        ElementSuitLevelUpVertor vecData;
        vecData.resize( ElementSuitLevelUp::GetMaxLevel() + 1 );

        vecData[ xData.GetLevel() ] = xData;

        m_mapElemnetEquip.insert( std::make_pair( uchEquipLevel, vecData ) );
    }
    else
    {
        iter->second[ xData.GetLevel() ] = xData;
    }


    return AddElementTotalModulus( uchEquipLevel, xData.GetModulus() );
}

bool SuitOperateConfig::AddElementTotalModulus( unsigned char uchEquipLevel, unsigned int nModulus )
{
    ElementModulusMapIter iter = m_mapElementTotalModulus.find( uchEquipLevel );
    if ( iter == m_mapElementTotalModulus.end() )
    {
        m_mapElementTotalModulus.insert( std::make_pair( uchEquipLevel, nModulus ) );
    }
    else
    {
        iter->second += nModulus;
    }
    return true;
}

const ElementSuitLevelUp* SuitOperateConfig::GetElementEquipData( unsigned char uchEquipLevel, unsigned char uchLevel ) const
{
    ElementSuitLevelUpMapConstIter iter = m_mapElemnetEquip.find( uchEquipLevel );
    if ( iter == m_mapElemnetEquip.end() )
    { return NULL; }

    if ( uchLevel >= iter->second.size() )
    { return NULL; }

    return &( iter->second.at( uchLevel ) );
}

unsigned char SuitOperateConfig::GetElementEquipLevelByRand( unsigned char uchEquipLevel, unsigned int nRandNumber ) const
{
    unsigned int nTotalModulus = GetElementTotalModulus( uchEquipLevel );
    if ( nTotalModulus == 0 )
    { return 1; }

    int nRand = nRandNumber % nTotalModulus;

    ElementSuitLevelUpMapConstIter iter = m_mapElemnetEquip.find( uchEquipLevel );
    if ( iter == m_mapElemnetEquip.end() )
    { return 1; }

    int nValue = 0;
    int nLevel = 0;
    for ( ElementSuitLevelUpVertorConstIter viter = iter->second.begin(); viter != iter->second.end(); ++viter, ++nLevel )
    {
        nValue += viter->GetModulus();
        if ( nRand < nValue )
        { return nLevel; }
    }

    return 1;
}

unsigned int SuitOperateConfig::GetElementTotalModulus( unsigned char uchEquipLevel ) const
{
    ElementModulusMapConstIter iter = m_mapElementTotalModulus.find( uchEquipLevel );
    if ( iter == m_mapElementTotalModulus.end() )
    { return 0; }

    return iter->second;
}

bool SuitOperateConfig::AddSkillSuitChange( unsigned char uchEquipLevel, unsigned char uchEquipID, SkillSuitChange& xChange )
{
    LevelSkillSuitChangeMapIter iter = m_mapSkillSuitChange.find( uchEquipLevel );
    if ( iter == m_mapSkillSuitChange.end() )
    {
        SkillSuitChangeMap mapSuitChange;

        mapSuitChange.insert( std::make_pair( uchEquipID, xChange ) );

        m_mapSkillSuitChange.insert( std::make_pair( uchEquipLevel, mapSuitChange ) );
    }
    else
    {
        SkillSuitChangeMapIter miter = iter->second.find( uchEquipID );
        if ( miter != iter->second.end() )
        { return false; }

        iter->second.insert( std::make_pair( uchEquipID, xChange ) );
    }
    return true;
}

// uchEquipLevel = 装备等级  uchSuitLevel = 强化等级
bool SuitOperateConfig::AddSkillSuitChangeCost( unsigned char uchEquipLevel, unsigned char uchSuitLevel, unsigned char uchMaxLevel, ChangeCostInfo& xCost )
{
    if ( uchSuitLevel > uchMaxLevel )
    { return false; }

    LevelSuitChangeCostMapIter iter = m_mapSkillSuitChangeCost.find( uchEquipLevel );
    if ( iter == m_mapSkillSuitChangeCost.end() )
    {
        SuitChangeCost vecChangeCost;
        
        vecChangeCost.resize( uchMaxLevel + 1 );

        vecChangeCost[ uchSuitLevel ] = xCost;

        m_mapSkillSuitChangeCost.insert( std::make_pair( uchEquipLevel, vecChangeCost ) );
    }
    else
    {
        iter->second[ uchSuitLevel ] = xCost;
    }

    return true;
}

const ChangeCostInfo* SuitOperateConfig::GetSkillSuitChangeCostInfo( unsigned char uchEquipLevel, unsigned char uchSuitLevel ) const
{
    LevelSuitChangeCostMapConstIter iter = m_mapSkillSuitChangeCost.find( uchEquipLevel );
    if ( iter == m_mapSkillSuitChangeCost.end() )
    { return NULL; }

    if ( uchSuitLevel >= iter->second.size() )
    { return NULL; }

    return &( iter->second.at( uchSuitLevel ) );
}

unsigned short SuitOperateConfig::GetEquipIDByRand( unsigned char uchEquipLevel, unsigned char uchEquipID, unsigned int nRandNumber, unsigned char uchSex, unsigned short ustDefaultID ) const
{
    LevelSkillSuitChangeMapConstIter iter = m_mapSkillSuitChange.find( uchEquipLevel );
    if ( iter == m_mapSkillSuitChange.end() )
    { return ustDefaultID; }

    SkillSuitChangeMapConstIter miter = iter->second.find( uchEquipID );
    if ( miter == iter->second.end() )
    { return ustDefaultID; }

    std::vector< unsigned short > vecEquipID;
    miter->second.GetEquipID( vecEquipID, uchSex, ustDefaultID );

    if ( vecEquipID.empty() )
    { return ustDefaultID; }

    int nIndex = nRandNumber % vecEquipID.size();

    return vecEquipID.at( nIndex );
}

bool SuitOperateConfig::AddCostMoney( CostMoneyMap& xCostMoneyMap, unsigned char uchEquipLevel, unsigned int nCostMoney )
{
    CostMoneyMapIter iter = xCostMoneyMap.find( uchEquipLevel );
    if ( iter != xCostMoneyMap.end() )
    { return false; }

    return xCostMoneyMap.insert( std::make_pair( uchEquipLevel, nCostMoney ) ).second;
}

unsigned int SuitOperateConfig::GetCostMoney( const CostMoneyMap& xCostMoneyMap, unsigned char uchEquipLevel ) const
{
    CostMoneyMapConstIter iter = xCostMoneyMap.find( uchEquipLevel );
    if ( iter == xCostMoneyMap.end() )
    { return 10000; }

    return iter->second;
}

unsigned int SuitOperateConfig::GetSkillSuitLevelUpCostMoney( unsigned char uchEquipLevel ) const
{
    return GetCostMoney( m_mapSkillSuitLevelUpCostMoney, uchEquipLevel );
}

unsigned int SuitOperateConfig::GetElementSuitLevelUpCostMoney( unsigned char uchEquipLevel ) const
{
    return GetCostMoney( m_mapElementSuitLevelUpCostMoney, uchEquipLevel );
}

unsigned int SuitOperateConfig::GetSkillSuitChangeCostMoney( unsigned char uchEquipLevel ) const
{
    return GetCostMoney( m_mapSkillSuitChangeCostMoney, uchEquipLevel );
}

unsigned int SuitOperateConfig::GetElementSuitChangeCostMoney( unsigned char uchEquipLevel ) const
{
    return GetCostMoney( m_mapElementSuitChangeCostMoney, uchEquipLevel );
}

bool SuitOperateConfig::IsExistElementSuitLevelLevel(unsigned char uchEquipLevel)
{
    ElementSuitLevelUpMapIter iter = m_mapElemnetEquip.find( uchEquipLevel );
    if ( iter == m_mapElemnetEquip.end() )
        return false;

    return true;
}

bool SuitOperateConfig::LoadSuitLevelUpConfig( const char* szFile )
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    m_mapSkillEquip.clear();
    m_mapElementTotalModulus.clear();
    m_mapElemnetEquip.clear();
    m_mapSkillSuitChange.clear();
    m_mapSkillSuitChangeCost.clear();
    m_mapSkillSuitChangeCostMoney.clear();
    m_mapSkillSuitLevelUpCostMoney.clear();
    m_mapElementSuitLevelUpCostMoney.clear();
    m_mapElementSuitChangeCostMoney.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    // 技能套装精炼
    MeXmlElement* pSkillSuit = pRoot->FirstChildElement( "SkillLevelUp" );
    if ( pSkillSuit == NULL )
    { return false; }

    int nMaxSkillLevel;
    if ( pSkillSuit->Attribute( "MaxLevel", &nMaxSkillLevel ) == NULL )
    { return false; }
    SkillSuitLevelUp::SetMaxLevel( nMaxSkillLevel );

    MeXmlElement* pLevelSuitEquip = pSkillSuit->FirstChildElement( "SuitEquipLevel" );
    while ( pLevelSuitEquip != NULL )
    {
        int nEquipLevel;
        if ( pLevelSuitEquip->Attribute( "Level", &nEquipLevel ) == NULL )
        { return false; }

        int nSkillLevelUpMoney;
        if ( pLevelSuitEquip->Attribute( "CostMoney", &nSkillLevelUpMoney ) == NULL )
        { return false; }

        if ( !AddCostMoney( m_mapSkillSuitLevelUpCostMoney, nEquipLevel, nSkillLevelUpMoney ) )
        { return false; }

        MeXmlElement* pSkillSuitEquip = pLevelSuitEquip->FirstChildElement( "SuitEquip" );
        while ( pSkillSuitEquip != NULL )
        {
            int nSkillEquipID;
            if ( pSkillSuitEquip->Attribute( "Value", &nSkillEquipID ) == NULL )
            { return false; }

            MeXmlElement* pLevel = pSkillSuitEquip->FirstChildElement( "Level" );
            while ( pLevel != NULL )
            {
                SkillSuitLevelUp xData;

                int nLevel;
                if ( pLevel->Attribute( "Value", &nLevel ) == NULL )
                { return false; }
                xData.SetLevel( nLevel );

                int nBaseModulus;
                if ( pLevel->Attribute( "BaseModulus", &nBaseModulus ) == NULL )
                { return false; }
                xData.SetModulus( nBaseModulus );

                int nExtendModulus;
                if ( pLevel->Attribute( "ExtendModulus", &nExtendModulus ) == NULL )
                { return false; }
                xData.SetExtendModulus( nExtendModulus );

                int nType;
                if ( pLevel->Attribute( "AttributeType", &nType ) == NULL )
                { return false; }
                xData.SetAttributeType( nType );

                int nValue;
                if ( pLevel->Attribute( "AttributeValue", &nValue ) == NULL )
                { return false; }
                xData.SetAttributeValue( nValue );

                if ( !AddSkillEquipData( nEquipLevel, nSkillEquipID, xData ) )
                { return false; }

                pLevel = pLevel->NextSiblingElement();
            }

            pSkillSuitEquip = pSkillSuitEquip->NextSiblingElement();
        }
        pLevelSuitEquip = pLevelSuitEquip->NextSiblingElement();
    }

    // 技能套装转换
    MeXmlElement* pSkillChange = pRoot->FirstChildElement( "SkillChange" );
    if ( pSkillChange == NULL )
    { return false; }

    // 是否要判断装备精炼等级
    int nCheckSuitLevel;
    if ( pSkillChange->Attribute( "IsCheckLevel", &nCheckSuitLevel ) == NULL )
    { return false; }
    m_bCheckSkillSuitChangeLevel = ( nCheckSuitLevel == 0 ? false : true ) ;

    // 转化最小要求的精炼等级
    int nMinSuitLevel;
    if ( pSkillChange->Attribute( "MinChangeLevel", &nMinSuitLevel ) == NULL )
    { return false; }
    m_uchMinSkillSuitChangeLevel = nMinSuitLevel ;

    MeXmlElement* pLevelSkillChange = pSkillChange->FirstChildElement( "EquipLevel" );
    while ( pLevelSkillChange != NULL )
    { 
        int nEquipLevel;
        if ( pLevelSkillChange->Attribute( "Level", &nEquipLevel ) == NULL )
        { return false; }

        int nChangeMoney;   // 钱
        if ( pLevelSkillChange->Attribute( "CostMoney", &nChangeMoney ) == NULL )
        { return false; }
        if ( !AddCostMoney( m_mapSkillSuitChangeCostMoney, nEquipLevel, nChangeMoney ) )
        { return false; }

        MeXmlElement* pChangeCost = pLevelSkillChange->FirstChildElement( "ChangeCost" );
        if ( pChangeCost == NULL )
        { return false; }

        // 最大精炼等级
        int nChangeMaxLevel;
        pChangeCost->Attribute( "MaxLevel", &nChangeMaxLevel );

        // 转化消耗
        MeXmlElement* pCostInfo = pChangeCost->FirstChildElement( "Change" );
        while ( pCostInfo != NULL )
        { 
            int nLevel;
            if ( pCostInfo->Attribute( "Level", &nLevel ) == NULL || nLevel > nChangeMaxLevel )
            { return false; }

            ChangeCostInfo xCost;

            int nType;
            if ( pCostInfo->Attribute( "CostType", &nType ) == NULL )
            { return false; }
            xCost.SetCostType( nType );

            int nValue;
            if ( pCostInfo->Attribute( "CostValue", &nValue ) == NULL )
            { return false; }
            xCost.SetCostValue( nValue );

            int nCount;
            if ( pCostInfo->Attribute( "CostCount", &nCount ) == NULL )
            { return false; }
            xCost.SetCostCount( nCount );

            if ( !AddSkillSuitChangeCost( nEquipLevel, nLevel, nChangeMaxLevel, xCost ) )
            { return false; }

            pCostInfo = pCostInfo->NextSiblingElement();
        }

        // 所有的装备部件
        MeXmlElement* pEquipID = pLevelSkillChange->FirstChildElement( "Equip" );
        while ( pEquipID != NULL )
        {
            int nEquipID;
            if ( pEquipID->Attribute( "Value", &nEquipID ) == NULL )
            { return false; }

            SkillSuitChange xChange;

            MeXmlElement* pID = pEquipID->FirstChildElement( "ID" );
            while ( pID != NULL )
            {
                int nID;
                if ( pID->Attribute( "MaleValue", &nID ) == NULL )
                { return false; }

                if ( !xChange.AddEquipID( 0, nID ) )
                { return false; }

                if ( pID->Attribute( "FemaleValue", &nID ) == NULL )
                { return false; }

                if ( !xChange.AddEquipID( 1, nID ) )
                { return false; }

                pID = pID->NextSiblingElement();
            }

            if( !AddSkillSuitChange( nEquipLevel, nEquipID, xChange ) )
            { return false; }

            pEquipID = pEquipID->NextSiblingElement();
        }

        pLevelSkillChange = pLevelSkillChange->NextSiblingElement();
    }


    // 五行套装提纯
    MeXmlElement* pElementSuit = pRoot->FirstChildElement( "ElementLevelUp" );
    if ( pElementSuit == NULL )
    { return false; }

    int nMaxElementLevel;
    pElementSuit->Attribute( "MaxLevel", &nMaxElementLevel );
    ElementSuitLevelUp::SetMaxLevel( nMaxElementLevel );

    MeXmlElement* pElementSuitLevel = pElementSuit->FirstChildElement( "EquipLevel" );
    while ( pElementSuitLevel != NULL )
    { 
        int nEquipLevel;
        if ( pElementSuitLevel->Attribute( "Level", &nEquipLevel ) == NULL )
        { return false; }

        int nElementLevelMoney;
        if ( pElementSuitLevel->Attribute( "CostMoney", &nElementLevelMoney ) == NULL )
        { return false; }
        if ( !AddCostMoney( m_mapElementSuitLevelUpCostMoney, nEquipLevel, nElementLevelMoney ) )
        { return false; }

        MeXmlElement* pLevel = pElementSuitLevel->FirstChildElement( "Level" );
        while ( pLevel != NULL )
        {
            ElementSuitLevelUp xData;

            int nLevel;
            if ( pLevel->Attribute( "Value", &nLevel ) == NULL )
            { return false; }
            xData.SetLevel( nLevel );

            int nBaseModulus;
            if ( pLevel->Attribute( "Modulus", &nBaseModulus ) == NULL )
            { return false; }
            xData.SetModulus( nBaseModulus );

            int nType;
            if ( pLevel->Attribute( "CostType", &nType ) == NULL )
            { return false; }
            xData.SetCostType( nType );

            int nValue;
            if ( pLevel->Attribute( "CostValue", &nValue ) == NULL )
            { return false; }
            xData.SetCostValue( nValue );

            int nCount;
            if ( pLevel->Attribute( "CostCount", &nCount ) == NULL )
            { return false; }
            xData.SetCostCount( nCount );

            if ( !AddElementEquipData( nEquipLevel, xData ) )
            { return false; }

            pLevel = pLevel->NextSiblingElement();
        }

        pElementSuitLevel = pElementSuitLevel->NextSiblingElement();
    }

   // 五行转化
    MeXmlElement* pElementChange = pRoot->FirstChildElement( "ElementChange" );
    if ( pElementChange == NULL )
    { return false; }

    int nMinElementChangeLevel;
    if ( pElementChange->Attribute( "MinChangeLevel", &nMinElementChangeLevel ) == NULL )
    { return false; }
    m_uchMinElementSuitChangeLevel = nMinElementChangeLevel;

    MeXmlElement* pElementChangeLevel = pElementChange->FirstChildElement( "EquipLevel" );
    while ( pElementChangeLevel != NULL )
    {
        int nEquipLevel;
        if ( pElementChangeLevel->Attribute( "Level", &nEquipLevel ) == NULL )
        { return false; }

        int nElementLevelMoney;
        if ( pElementChangeLevel->Attribute( "CostMoney", &nElementLevelMoney ) == NULL )
        { return false; }
        if ( !AddCostMoney( m_mapElementSuitChangeCostMoney, nEquipLevel, nElementLevelMoney ) )
        { return false; }

        pElementChangeLevel = pElementChangeLevel->NextSiblingElement();
    }

    MeXmlElement* pElementMove = pRoot->FirstChildElement( "ElementMove" );
    if ( pElementMove == NULL )
    { return false; }

    double dBaseModulus;
    if ( pElementMove->Attribute( "BaseModulus", &dBaseModulus ) == NULL )
    { return false; }
    m_xElementMove.SetBaseModulus( static_cast< double >( dBaseModulus ) );

    int nMaterialID;
    if ( pElementMove->Attribute( "MaterialID", &nMaterialID ) == NULL )
    { return false; }
    m_xElementMove.SetMaterialID( nMaterialID );

    int nMaxCount;
    if ( pElementMove->Attribute( "MaxCount", &nMaxCount ) == NULL )
    { return false; }
    m_xElementMove.SetMaxCount( nMaxCount );

    m_xElementMove.ResizeModulus( nMaxCount + 1 );

    int nCostMoney;
    if ( pElementMove->Attribute( "CostMoney", &nCostMoney ) == NULL )
    { return false; }
    m_xElementMove.SetCostMoney( nCostMoney );

    MeXmlElement* pMoveModulus = pElementMove->FirstChildElement( "Count" );
    while ( pMoveModulus != NULL )
    { 
        int nCount;
        if ( pMoveModulus->Attribute( "Value", &nCount ) == NULL )
        { return false; }

        double dModulus;
        if ( pMoveModulus->Attribute( "Modulus", &dModulus ) == NULL )
        { return false; }

        if ( !m_xElementMove.AddModulus( nCount, static_cast< float >( dModulus ) ) )
        { return false; }

        pMoveModulus = pMoveModulus->NextSiblingElement();
    }

#ifdef GAME_CLIENT
	// 技能套装部件升级后属性
	MeXmlElement* pSkillSuitAttributes = pRoot->FirstChildElement( "SkillSuitAttributes" );
	if ( pSkillSuitAttributes == NULL )
	{ return false; }

	MeXmlElement* pSkillSuitAttribute = pSkillSuitAttributes->FirstChildElement( "Attribute" );
	while ( pSkillSuitAttribute != NULL )
	{
		int nSuitID;
		if ( pSkillSuitAttribute->Attribute( "SuitID", &nSuitID ) == NULL )
		{ return false; }

		const char* szName = pSkillSuitAttribute->Attribute("AttrName");
		if (!szName)
		{ return false; }

		const char* szPicture = pSkillSuitAttribute->Attribute("AttrPicture");
		if (!szPicture)
		{ return false; }

		int nWidth;
		if ( pSkillSuitAttribute->Attribute( "AttrPictureWidth", &nWidth ) == NULL )
		{ return false; }

		int nHeigth;
		if ( pSkillSuitAttribute->Attribute( "AttrPictureHeigth", &nHeigth ) == NULL )
		{ return false; }

		AddSkillSuitAttribute(nSuitID,
			Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(szName).c_str()),
			Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(szPicture).c_str()),
			nWidth, nHeigth);

		pSkillSuitAttribute = pSkillSuitAttribute->NextSiblingElement();
	}
#endif

    return true;
}