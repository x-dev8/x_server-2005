/********************************************************************
Filename:    RandPropertyEvaluate.cpp
Description: 随机属性评估
*********************************************************************/
#include "RandPropertyEvaluate.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

CRandPropertyEvaluate theRandPropEvaluate;

CRandPropertyEvaluate::CRandPropertyEvaluate()
{
    m_mapPropertyEvaluate.clear();
}

CRandPropertyEvaluate::~CRandPropertyEvaluate()
{
    Reset();
}

bool CRandPropertyEvaluate::LoadConfig( const char* szFileName )
{
    Reset();

    MeXmlDocument PropertyEvaluateXMLDocument;
    bool bRet = PropertyEvaluateXMLDocument.LoadFile( szFileName );
    if( !bRet )
        return false;

    MeXmlElement* pRoot = PropertyEvaluateXMLDocument.FirstChildElement( "Project" );
    if( !pRoot )
        return false;

    const char* szValue = NULL;

    MeXmlElement* pEvaluateElem = pRoot->FirstChildElement("Evaluate");
    for( ; pEvaluateElem; pEvaluateElem = pEvaluateElem->NextSiblingElement() )
    {
        SPropertyEvaluate kEvalAttribute;
        for( int i=0; i<PropEvalEquipmentTypeCount; i++)
            kEvalAttribute._EquipmentEval[i].clear();

        // 评估类型
        szValue = pEvaluateElem->Attribute("Type");
        if( stricmp( szValue, "Identify" ) == 0 )
        {
            kEvalAttribute.usEvalType = PropertyEvaluate_Identify;
        }
        else if( stricmp( szValue, "OpenLight" ) == 0 )
        {
            kEvalAttribute.usEvalType = PropertyEvaluate_OpenLight;
        }

        MeXmlElement* pEquipmentsElem = pEvaluateElem->FirstChildElement("Equipments");
        for( ; pEquipmentsElem; pEquipmentsElem = pEquipmentsElem->NextSiblingElement() )
        {
            // 装备类型
            szValue = pEquipmentsElem->Attribute("Type");
            unsigned short usEquipType = 0;
            if( stricmp( szValue, "Armour" ) == 0 )
            {
                usEquipType = PropEvalEquipment_Aumour;
            }
            else if( stricmp( szValue, "Weapon" ) == 0 )
            {
                usEquipType = PropEvalEquipment_Weapon;
            }

            // 装备评估数据
            MeXmlElement* pEquipElem = pEquipmentsElem->FirstChildElement("Equipment");
            for( ; pEquipElem; pEquipElem = pEquipElem->NextSiblingElement() )
            {
                SEquipmentEval kEquipmentEval;
                memset(&kEquipmentEval, 0, sizeof(SEquipmentEval) );

                kEquipmentEval.usEquipType = usEquipType;

                int nValue = 0;
                float fValue = 0.f;
                pEquipElem->QueryIntAttribute("Level", &nValue);
                kEquipmentEval.usLevel = nValue;

                pEquipElem->QueryIntAttribute("RandLevel", &nValue);
                kEquipmentEval.usRandLevel = nValue;

                pEquipElem->QueryFloatAttribute("EvalNormal", &fValue);
                kEquipmentEval.fEvalNormal = fValue;

                pEquipElem->QueryFloatAttribute("EvalLiangPin", &fValue);
                kEquipmentEval.fEvalLiangPin = fValue;

                pEquipElem->QueryFloatAttribute("EvalJingPin", &fValue);
                kEquipmentEval.fEvalJingPin = fValue;

                pEquipElem->QueryFloatAttribute("EvalJiPin", &fValue);
                kEquipmentEval.fEvalJiPin = fValue;

                pEquipElem->QueryFloatAttribute("EvalShenPin", &fValue);
                kEquipmentEval.fEvalShenPin = fValue;

                kEvalAttribute._EquipmentEval[usEquipType].push_back(kEquipmentEval);
            }
        }

        m_mapPropertyEvaluate.insert( mapPropertyEvaluate::value_type( kEvalAttribute.usEvalType, kEvalAttribute ) ); 
    }
    return true;
}

const CRandPropertyEvaluate::SEquipmentEval* CRandPropertyEvaluate::GetEquipmentEval( unsigned short usEvaluateType, unsigned short usEquipType, unsigned short usItemLevel )
{
    if( usEvaluateType >= PropertyEvaluateTypeCount )
        return NULL;

    if( usEquipType >= PropEvalEquipmentTypeCount )
        return NULL;

    mapPropertyEvaluate::iterator iter_map = m_mapPropertyEvaluate.find(usEvaluateType);
    if( iter_map != m_mapPropertyEvaluate.end() )
    {
        SPropertyEvaluate& kPropEval = iter_map->second;
        vectorEquipmentEval::iterator iter = kPropEval._EquipmentEval[usEquipType].begin();
        while( iter != kPropEval._EquipmentEval[usEquipType].end() )
        {
            const SEquipmentEval& kEquipEval = *iter;
            if( kEquipEval.usLevel >= usItemLevel )
                return &kEquipEval;
            else
                ++iter;
        }
    }

    return NULL;
}

void CRandPropertyEvaluate::Reset()
{
    mapPropertyEvaluate::iterator iter_map = m_mapPropertyEvaluate.begin();
    while( iter_map != m_mapPropertyEvaluate.end() )
    {
        SPropertyEvaluate& kPropEval = iter_map->second;
        for( int i=0; i<PropEvalEquipmentTypeCount; i++)
            kPropEval._EquipmentEval[i].clear();
        ++iter_map;
    }
    m_mapPropertyEvaluate.clear();
}