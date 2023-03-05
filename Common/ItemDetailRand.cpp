#include "ItemDetailConfig.h"
#include "SlkReader.h"
#include "Helper.h"
#include "Official.h"
#include "SystemConfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "ProcessCharInfo.h"
#include "NewWithDebug.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "core/Name.h"
#include "application_config.h"
#include "TitleConfig.h"
//#include "Cipher/cipher_factory.h"
//#include "Launcher/DataLauncher.h"
#include "SplitItemConfig.h"
#include "ErrorCode.h"
#include "tstring.h"

#pragma warning( push, 0 )

ItemDefine::SRandAttribute *CItemDetail::GetRandByID(unsigned short usRandID)
{
    RandContainerById::iterator it = _RandsById.find(usRandID);
    if ( it != _RandsById.end())
        return it->second;

    return NULL;
}

float CItemDetail::GetEquipQualityIntensity(uint8 nQuality)
{
	EquipQualityIntensityContainer::iterator it = m_mapEquipQualityIntensity.find(nQuality);
	if ( it != m_mapEquipQualityIntensity.end())
		return (float)(it->second->nIntensity) / 10000.0f;

	return 0;
}

float CItemDetail::GetEquipRandAttrValue( float fRandValue, uint8 nQuality )
{
	float fIntensity = GettheItemDetail().GetEquipQualityIntensity(nQuality);
	float fValue = fRandValue * fIntensity;
	if ( fValue > 0.0f && fValue < 1.0f )
	{ fValue = 1.0f; }

	return fValue; 
}

bool CItemDetail::HaveSameRandType(unsigned short usRandID1, unsigned short usRandID2)
{
    ItemDefine::SRandAttribute* pItemEquipRand1 = GettheItemDetail().GetRandByID( usRandID1 );
    if ( pItemEquipRand1 == NULL )
    { return true; }

    ItemDefine::SRandAttribute* pItemEquipRand2 = GettheItemDetail().GetRandByID( usRandID2 );
    if ( pItemEquipRand1 == NULL )
    { return true; }

    for ( int i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
    {
        if (pItemEquipRand1->type[i] != InvalidLogicNumber)
        {
            if (pItemEquipRand1->type[i] == pItemEquipRand2->type[i])
            { return true; }
        }
    }  

    return false;
}

long CItemDetail::GetRandByLevel( short level, OUT RandContainer& result )
{
    result.clear();
    RandPairResult pairResult = _RandsByLevel.equal_range(level);
    ItrRandContainerByLevel it = pairResult.first;
    for ( ; it!=pairResult.second; ++it)
    {
        ItemDefine::SRandAttribute* pRand = it->second;
        if ( !pRand)
            continue;

        result.push_back( pRand->id );
    }
    return 0;
}

long CItemDetail::GetRandByLevel( short level, OUT RandAttrContainer& result )
{
	result.clear();
	RandPairResult pairResult = _RandsByLevel.equal_range(level);
	ItrRandContainerByLevel it = pairResult.first;
	for ( ; it!=pairResult.second; ++it)
	{
		ItemDefine::SRandAttribute* pRand = it->second;
		if ( !pRand)
			continue;

		ItemDefine::RandAttr	randAttr;
		randAttr.usID = pRand->id;
		randAttr.usType = pRand->type[0];
		result.push_back(randAttr);
	}
	return 0;
}

void CItemDetail::SetRandValueLevelType(float value, short level, unsigned short type)
{
    mapRandMaxValueByLevelType::iterator it = _RandMaxValueByLevelType.find(level);
    if ( it != _RandMaxValueByLevelType.end())
    {
        mapRandMaxValueByType* pRandMaxValueByType = &it->second;
        mapRandMaxValueByType::iterator iter = pRandMaxValueByType->find(type);
        if ( iter != pRandMaxValueByType->end())
        {
            if( iter->second < value )
            {
                iter->second = value;
            }
        }
        else
        {
            pRandMaxValueByType->insert( mapRandMaxValueByType::value_type( type, value ) ); 
        }
    }
    else
    {
        mapRandMaxValueByType _mapRandMaxValueByType;
        _mapRandMaxValueByType.clear();
        _mapRandMaxValueByType.insert( mapRandMaxValueByType::value_type( type, value ) ); 
        _RandMaxValueByLevelType.insert( mapRandMaxValueByLevelType::value_type( level, _mapRandMaxValueByType) );
    }
}

float CItemDetail::GetMaxValueByRandLevelType( short level, unsigned short type )
{
    mapRandMaxValueByLevelType::iterator it = _RandMaxValueByLevelType.find(level);
    if ( it != _RandMaxValueByLevelType.end())
    {
        mapRandMaxValueByType* pRandMaxValueByType = &it->second;
        mapRandMaxValueByType::iterator iter = pRandMaxValueByType->find(type);
        if ( iter != pRandMaxValueByType->end())
        {
            return iter->second;
        }
    }
    return -1.f;
}

bool CItemDetail::LoadSlkRand( const char* szFileName)
{
    CSlkReader pReader;

    if(!pReader.ReadFromFile( szFileName ))
    { return false; }

    bool bReadSucc = true;
    int iRow       = 3;
    int iCol       = 0;
    int iRet       = 0;

    std::string strValue;
    int         iValue = 0;
    float       fValue = 0.0f;


    while(CSlkReader::ret_readover!=(iRet=pReader.GotoNextLine(iRow++)))
    {
        if(CSlkReader::ret_nothisline==iRet)
            continue;

        ItemDefine::SRandAttribute* pRandAttribute = (ItemDefine::SRandAttribute*)AllocItem( 0, sizeof( ItemDefine::SRandAttribute ) );
        if(!pRandAttribute)
        {
            OutputSlkLoadingMessage( "\tError:内存分配出错!\r\n" );
            return false;
        }

        SLK_GET_INT( pRandAttribute->id , "ID");
        OutputSlkLoadingMessage( "\t Load RandAttribute(%d)\r\n" , pRandAttribute->id );

        SLK_GET_INT( pRandAttribute->level, "Level");

        for ( int i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            SLK_GET_INT( iValue, szTypeTmp);
            pRandAttribute->type[i] = iValue;

            SLK_GET_FLOAT( fValue, szValueTmp);
            pRandAttribute->value[i].fValue = fValue;

        }

        // 加入查找
        _RandsById.insert( RandContainerById::value_type( pRandAttribute->id, pRandAttribute ) ); 
        _RandsByLevel.insert(RandContainerByLevel::value_type( pRandAttribute->level, pRandAttribute));
    }


    return true;
}

bool CItemDetail::LoadXmlEquipQualityIntensity( const char* szFileName )
{
	if (szFileName == NULL)
	{ return false; }

	MeXmlDocument mMeXmlDoc;
	if (!mMeXmlDoc.LoadFile(szFileName))
	{ return false; }

	MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL)
	{ return false; }

	MeXmlElement *pQualityTree = pRoot->FirstChildElement("QualityIntensities");
	if (pQualityTree == NULL)
	{ return false; }

	MeXmlElement *pQualityElement = pQualityTree->FirstChildElement("QualityIntensity");
	if (pQualityElement == NULL)
	{ return false; }

	int iValue = 0;
	double dValue = 0.000000;

	while ( pQualityElement != NULL )
	{
		ItemDefine::SEquipQualityIntensity *pQuality = (ItemDefine::SEquipQualityIntensity *)AllocItem( 0, sizeof(ItemDefine::SEquipQualityIntensity) );
		if( pQuality == NULL )
		{ return false; }

		if( pQualityElement->Attribute("Quality", &iValue) == NULL )
		{ return false; }
		pQuality->nQuality = iValue;

		if( pQualityElement->Attribute("Color", &iValue) == NULL )
		{ return false; }
		pQuality->nColor = iValue;

		if( pQualityElement->Attribute("Intensity", &iValue) == NULL )
		{ return false; }
		pQuality->nIntensity = iValue;

		m_mapEquipQualityIntensity.insert( make_pair(pQuality->nQuality, pQuality) );

		pQualityElement = pQualityElement->NextSiblingElement();
	}

	return true;
}

bool CItemDetail::SaveXmlEquipQualityIntensity( const char* szFileName )
{
	if(szFileName == NULL)
	{ return false; }

	MeXmlDocument EquipQualityIntensityMeXml;
	EquipQualityIntensityMeXml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
	MeXmlElement *pRoot = EquipQualityIntensityMeXml.InsertEndChild(("Project"))->ToElement();
	if (pRoot == NULL)
	{ return false; }

	MeXmlElement *pQualityIntensities = pRoot->InsertEndChild(("QualityIntensities"))->ToElement();
	if (pQualityIntensities == NULL)
	{ return false; }

	EquipQualityIntensityContainer::iterator iterBegin = m_mapEquipQualityIntensity.begin();
	EquipQualityIntensityContainer::iterator iterEnd = m_mapEquipQualityIntensity.end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		ItemDefine::SEquipQualityIntensity *pIter = iterBegin->second;
		MeXmlElement *pQualityIntensity = pQualityIntensities->InsertEndChild(("QualityIntensity"))->ToElement();

		pQualityIntensity->SetAttribute("Quality", pIter->nQuality);
		pQualityIntensity->SetAttribute("Color", pIter->nColor);
		pQualityIntensity->SetAttribute("Intensity", pIter->nIntensity);
	}

	return EquipQualityIntensityMeXml.SaveFile(szFileName);
}

bool CItemDetail::LoadXmlRand( const char* szFileName )
{
    if (szFileName == NULL)
    { return false; }

    MeXmlDocument mMeXmlDoc;
    if (!mMeXmlDoc.LoadFile(szFileName))
    { return false; }

    MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pRandomTree = pRoot->FirstChildElement("Rands");
    if (pRandomTree == NULL)
    { return false; }

    MeXmlElement *pRandomElement = pRandomTree->FirstChildElement("Rand");
    if (pRandomElement == NULL)
    { return false; }

    int iValue = 0;
    double dValue = 0.000000;

    while ( pRandomElement != NULL )
    {
        ItemDefine::SRandAttribute *pRandom = (ItemDefine::SRandAttribute *)AllocItem( 0, sizeof(ItemDefine::SRandAttribute) );
        if( pRandom == NULL )
        { return false; }

        if( pRandomElement->Attribute("ID", &iValue) == NULL )
        { return false; }

        pRandom->id = iValue;
        pRandomElement->Attribute("Level", &iValue);
        pRandom->level = iValue;

        for ( int i=0; i < ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            pRandomElement->Attribute(szTypeTmp, &iValue);
            pRandom->type[i] = iValue;

            pRandomElement->Attribute( szValueTmp, &dValue );
            pRandom->value[i].fValue = dValue;
            
            if (i == 0)
            { SetRandValueLevelType(dValue, pRandom->level, pRandom->type[0]); }
        }

        // 加入查找
        _RandsById.insert( RandContainerById::value_type( pRandom->id, pRandom) ); 
        _RandsByLevel.insert(RandContainerByLevel::value_type( pRandom->level, pRandom) );

        pRandomElement = pRandomElement->NextSiblingElement();
    }

    return true;
}

bool CItemDetail::SaveXmlRand( const char* szFileName )
{
    if(szFileName == NULL)
    { return false; }

    MeXmlDocument RandMeXml;
    RandMeXml.InsertEndChild(MeXmlDeclaration("1.0", "utf-8", "yes"));
    MeXmlElement *pRoot = RandMeXml.InsertEndChild(("Project"))->ToElement();
    if (pRoot == NULL)
    { return false; }

    MeXmlElement *pRands = pRoot->InsertEndChild(("Rands"))->ToElement();
    if (pRands == NULL)
    { return false; }

    RandContainerById::iterator iterBegin = _RandsById.begin();
    RandContainerById::iterator iterEnd = _RandsById.end();

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        ItemDefine::SRandAttribute *pRandIter = iterBegin->second;
        MeXmlElement *pRand = pRands->InsertEndChild(("Rand"))->ToElement();

        pRand->SetAttribute("ID", pRandIter->id);
        pRand->SetAttribute("Level", pRandIter->level);
        for ( int i=0; i < ItemDefine::SRandAttribute::CD_TypeCount; ++i)
        {
            char szTypeTmp[33]  = {0};
            char szValueTmp[33] = {0};

            sprintf_s( szTypeTmp, sizeof(szTypeTmp) - 1,  "Type%d", i+1);
            sprintf_s( szValueTmp, sizeof(szTypeTmp) - 1, "Value%d", i+1);

            pRand->SetAttribute(szTypeTmp, pRandIter->type[i]);
            pRand->SetDoubleAttribute(szValueTmp, pRandIter->value[i].fValue);

        }
    }

    return RandMeXml.SaveFile(szFileName);
}

#pragma warning( pop )