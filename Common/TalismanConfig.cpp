#include "TalismanConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "GameDefineTalisman.h"

TalismanConfig::TalismanConfig()
{
    memset( this, 0, sizeof(TalismanConfig) );
}

TalismanConfig::~TalismanConfig()
{

}

void TalismanConfig::InitTalismanEquipAttr( int itemId, int quality, int element, uint16* pBaseRand )
{
    std::vector< STalismanEquipAttr >::iterator iter = vecTalismanEquipAttr.begin();
    for ( ; iter != vecTalismanEquipAttr.end(); ++iter )
    {
        if ( iter->nTalismanID == itemId && iter->nQuality == quality && iter->nElement == element )
        { memcpy( pBaseRand, iter->nRandAttr , sizeof( uint16 ) * SCharItem::EConstDefine_BaseRandMaxCount ); }
    }
}

void TalismanConfig::InitTalismanRandAttr ( int poolId, uint16* pTalismanRand )
{
    if (poolId >= vecTalismanRandAttrPool.size() )
    { return; }

    SRandAttrPool* pRandAttrPool = &vecTalismanRandAttrPool[poolId];
    if (pRandAttrPool == NULL)
    { return; }

    for ( int i=0; i < SCharItem::EConstDefine_TalismanRandMaxCount; ++i )
    {
        pTalismanRand[i] = pRandAttrPool->nRandAttr[ theRand.rand16() % EPoolRandAttrMaxSize ];
    }
}

int64  TalismanConfig::GetLevelExperience( int level ) 
{
    if ( level <=0 || level >= const_iCharMaxLevel )
    { return 0; }

    return _TalismanExperiences[ level ];
}

TalismanConfig::STalismanRandAttr* TalismanConfig::GetTalismanRandAttr( int randId )
{
    if ( randId >= vecTalismanRandAttr.size() )
    { return NULL; }

    return &vecTalismanRandAttr[randId];
}

bool TalismanConfig::LoadTalismanConfig(const char* szFile)
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

    MeXmlElement* pTalismanSetting = pRoot->FirstChildElement("TalismanSetting");
    if (pTalismanSetting == NULL) 
    { return false; }

    int     iValue = 0;
    double  dValue = 0.0;

    //法宝品质随机概率
    MeXmlElement* pQualityElement = pTalismanSetting->FirstChildElement("Quality");
    while (pQualityElement != NULL)
    {	
        for (int i=0;i<ETalismanQuality_Count;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Rate%d",i);
            pQualityElement->Attribute(szTmp, &iValue);
            _TalismanQuality[i] = iValue;
        }

        pQualityElement = pQualityElement->NextSiblingElement("Quality");
    }

    //法宝修炼属性数目
    MeXmlElement* pAttrNumber = pTalismanSetting->FirstChildElement("AttrNumber");
    while (pAttrNumber != NULL)
    {
        int nQuality = 0;
        pAttrNumber->Attribute("Quality", &nQuality);
        pAttrNumber->Attribute("Number", &iValue);

        _TalismanAttrNumber[nQuality] = iValue;

        pAttrNumber = pAttrNumber->NextSiblingElement("AttrNumber");
    }

    //法宝装备属性表
    MeXmlElement* pEquipAttrTable = pTalismanSetting->FirstChildElement("EquipAttrTable");
    if (pEquipAttrTable == NULL)
    { return false; }

    MeXmlElement* pEquipAttr = pEquipAttrTable->FirstChildElement("EquipAttr");
    while (pEquipAttr != NULL)
    {
        STalismanEquipAttr xTalismanEquipAttr;

        pEquipAttr->Attribute("Talisman", &iValue);
        xTalismanEquipAttr.nTalismanID = iValue;

        pEquipAttr->Attribute("Element", &iValue);
        xTalismanEquipAttr.nElement = iValue;

        pEquipAttr->Attribute("Quality", &iValue);
        xTalismanEquipAttr.nQuality = iValue;

        for (int i=0;i<SCharItem::EConstDefine_BaseRandMaxCount;++i)
        {
            char szTmp[65] = { 0 };
            sprintf_s(szTmp, sizeof(szTmp) - 1, "Attr%d",i+1);
            pEquipAttr->Attribute(szTmp, &iValue);
            xTalismanEquipAttr.nRandAttr[i] = iValue;
        }

        vecTalismanEquipAttr.push_back( xTalismanEquipAttr );
        pEquipAttr = pEquipAttr->NextSiblingElement("EquipAttr");
    }

    //法宝修炼属性随机表
    MeXmlElement* pRandAttrTable = pTalismanSetting->FirstChildElement("RandAttrTable");
    if (pRandAttrTable == NULL)
    { return false; }

    MeXmlElement* pRandAttr = pRandAttrTable->FirstChildElement("RandAttr");
    while (pRandAttr != NULL)
    {
        STalismanRandAttr xTalismanRandAttr;

        pRandAttr->Attribute("ID", &iValue);
        xTalismanRandAttr.nRandID = iValue;

        Common::_tstring strType;
        strType.fromUTF8( pRandAttr->Attribute("Type") );
        iValue = iValue = HelperFunc::GetIDByConstString( (char*)strType.c_str(), g_szTalismanAttributeType,sizeof(g_szTalismanAttributeType)/sizeof(char*) );
        xTalismanRandAttr.nAttrType = iValue;

        pRandAttr->Attribute("Value", &iValue);
        xTalismanRandAttr.nAttrValue = iValue;

        Common::_tstring strDesc;
        strType.fromUTF8( pRandAttr->Attribute("Desc") );
        xTalismanRandAttr.strDesc = strDesc;

        if( xTalismanRandAttr.nRandID >= vecTalismanRandAttr.size() )
        {  vecTalismanRandAttr.resize( 100 ); }

        vecTalismanRandAttr[xTalismanRandAttr.nRandID] = xTalismanRandAttr;
        pRandAttr = pRandAttr->NextSiblingElement("RandAttr");
    }

    //法宝修炼属性池
    MeXmlElement* pRandPoolTable = pTalismanSetting->FirstChildElement("RandPoolTable");
    if (pRandPoolTable == NULL)
    { return false; }

    MeXmlElement* pRandPool = pRandPoolTable->FirstChildElement("RandPool");
    while (pRandPool != NULL)
    {
        SRandAttrPool xRandAttrPool;
        pRandPool->Attribute("ID", &iValue);
        xRandAttrPool.nPoolID = iValue;

        int index = 0;
        MeXmlElement* pRandAttr_ = pRandPool->FirstChildElement("RandAttr");
        while (pRandAttr_ != NULL)
        {
            if ( index >= EPoolRandAttrMaxSize )
            { break; }

            pRandAttr_->Attribute("ID", &iValue);
            xRandAttrPool.nRandAttr[index] = iValue;

            ++index;
            pRandAttr_ = pRandAttr_->NextSiblingElement("RandAttr");
        }

        if( xRandAttrPool.nPoolID >= vecTalismanRandAttrPool.size() )
        {  vecTalismanRandAttrPool.resize( 10 ); }

        vecTalismanRandAttrPool[xRandAttrPool.nPoolID] = xRandAttrPool;
        pRandPool = pRandPool->NextSiblingElement("RandPool");
    }

    // 法宝经验属性
    MeXmlElement* pLevelExperienceTable = pTalismanSetting->FirstChildElement("LevelExperienceTable");
    if (pLevelExperienceTable == NULL)
    { return false; }

    MeXmlElement* pLevelExperience = pLevelExperienceTable->FirstChildElement("LevelExperience");
    while (pLevelExperience != NULL)
    {
        int nLevel = 0;
        pLevelExperience->Attribute("Level", &nLevel);

        if ( nLevel >= const_iCharMaxLevel )
        { continue; }

        Common::_tstring strExperience;
        strExperience.fromUTF8( pLevelExperience->Attribute("Experience") );

        _TalismanExperiences[nLevel] = _atoi64( strExperience.c_str() ) ;

        pLevelExperience = pLevelExperience->NextSiblingElement("LevelExperience");
    }

	return true;
}
