#include "ArmourElementsConfig.h"
// // #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"
bool ArmourElementsConfig::LoadArmourElementsConfig( const char* szFile )
{
    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    m_mapElementsData.clear();
    m_mapElementsModulus.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pArmourElements = pRoot->FirstChildElement( "ArmourElements" );
    if ( pArmourElements == NULL ) 
    { return false; }

    MeXmlElement* pElement = pArmourElements->FirstChildElement( "Element" );
    while ( pElement != NULL ) 
    {
        int nElement;
        if ( pElement->Attribute( "Value", &nElement ) == NULL || nElement <= 0 )
        { return false; }
        
        ElementsData xData;
        
        int nForbear;
        pElement->Attribute( "Forbear", &nForbear );
        xData.SetForbear( nForbear );

        int nAssist;
        pElement->Attribute( "Assist", &nAssist );
        xData.SetAssist( nAssist );

        if ( !AddElementsData( nElement, xData ) )
        { return false; }

        pElement = pElement->NextSiblingElement();
    }

    MeXmlElement* pElementsModulus = pRoot->FirstChildElement( "ElementsModulus" );
    if ( pElementsModulus == NULL ) 
    { return false; }

    MeXmlElement* pLevel = pElementsModulus->FirstChildElement( "Level" );
    while ( pLevel != NULL )
    {
        int nLevel;
        if ( pLevel->Attribute( "Value", &nLevel ) == NULL || nLevel <= 0 )
        { return false; }
        
        MeXmlElement* pModulus = pLevel->FirstChildElement( "Modulus" );
        while ( pModulus != NULL ) 
        {
            int nElementCount;
            if ( pModulus->Attribute( "Element", &nElementCount ) == NULL || nElementCount <= 0 )
            { return false; }

            ModulusData xData;

            int nForbear;
            pModulus->Attribute( "Forbear", &nForbear );
            xData.SetForbear( nForbear );

            int nAssist;
            pModulus->Attribute( "Assist", &nAssist );
            xData.SetAssist( nAssist );

            if ( !AddElementsModulus( nLevel, nElementCount, xData ) )
            { return false; }

            pModulus = pModulus->NextSiblingElement();
        }

        pLevel = pLevel->NextSiblingElement();
    }


    // 五行装备附加的一些属性
    MeXmlElement* pElementsAttribute = pRoot->FirstChildElement( "ElementAttribute" );
    if ( pElementsAttribute == NULL ) 
    { return false; }

    int nMaxLevel;
    if ( pElementsAttribute->Attribute( "MaxLevel", &nMaxLevel ) == NULL )
    { return false; }
    m_uchElementMaxLevel = nMaxLevel;

    MeXmlElement* pEquipLevel = pElementsAttribute->FirstChildElement( "Equip" );
    while ( pEquipLevel != NULL ) 
    {
        int nEquipLevel;
        if ( pEquipLevel->Attribute( "Level", &nEquipLevel ) == NULL )
        { return false; }

        // 附加伤害
        MeXmlElement* pExtendAttack = pEquipLevel->FirstChildElement( "ExtendAttack" );
        if ( pExtendAttack == NULL )
        { return false; }

        MeXmlElement* pAttack = pExtendAttack->FirstChildElement( "Level" );
        while ( pAttack != NULL )
        {
            int nLevel;
            if ( pAttack->Attribute( "Value", &nLevel ) == NULL )
            { return false; }

            int nAttack;
            if ( pAttack->Attribute( "Attack", &nAttack ) == NULL )
            { return false; }

            if ( !AddExtendAttack( nEquipLevel, nLevel, nAttack ) )
            { return false; }

            pAttack = pAttack->NextSiblingElement();
        }

        // 隐藏属性
        MeXmlElement* pHideAttribute = pEquipLevel->FirstChildElement( "HideAttribute" );
        if ( pHideAttribute == NULL )
        { return false; }

        int nMaxHideAttriCount;
        if ( pHideAttribute->Attribute( "AttriCount", &nMaxHideAttriCount ) == NULL )
        { return false; }

        int nMinHideLevel;
        if ( pHideAttribute->Attribute( "MinLevel", &nMinHideLevel ) != NULL )
        {
            m_uchHideAttributeLevel = nMinHideLevel; 
        }

        MeXmlElement* pHideLevel = pHideAttribute->FirstChildElement( "Level" );
        while ( pHideLevel != NULL )
        {
            int nLevel;
            if ( pHideLevel->Attribute( "Value", &nLevel ) == NULL )
            { return false; }

            MeXmlElement* pAttribute = pHideLevel->FirstChildElement( "Attribute" );
            int nIndex = 0;
            while ( pAttribute != NULL )
            {
                int nAttriID;
                if ( pAttribute->Attribute( "ID", &nAttriID ) == NULL )
                { return false; }

                if ( !AddHideAttribute( nEquipLevel, nLevel, nIndex, nMaxHideAttriCount, nAttriID ) )
                { return false; }

                ++nIndex;
                pAttribute = pAttribute->NextSiblingElement();
            }

            pHideLevel = pHideLevel->NextSiblingElement();
        }

        // 基础属性
        MeXmlElement* pBaseAttribute = pEquipLevel->FirstChildElement( "BaseAttribute" );
        if ( pBaseAttribute == NULL )
        { return false; }

        int nMaxElementCount;
        if ( pBaseAttribute->Attribute( "MaxElementCount", &nMaxElementCount ) == NULL )
        { return false; }
        m_uchElementMaxCount = nMaxElementCount;

        int nMaxBaseAttriCount;
        if ( pBaseAttribute->Attribute( "AttriCount", &nMaxBaseAttriCount ) == NULL )
        { return false; }

        MeXmlElement* pEAttribute = pBaseAttribute->FirstChildElement( "Element" );
        while ( pEAttribute != NULL )
        {
            int nElement;
            if ( pEAttribute->Attribute( "Value", &nElement ) == NULL )
            { return false; }

            MeXmlElement* pCount = pEAttribute->FirstChildElement( "Count" );
            while ( pCount != NULL )
            {
                int nCount;
                if ( pCount->Attribute( "Value", &nCount ) == NULL )
                { return false; }

                MeXmlElement* pAttribute = pCount->FirstChildElement( "Attribute" );
                int nIndex = 0;
                while ( pAttribute != NULL )
                {
                    int nAttriID;
                    if ( pAttribute->Attribute( "ID", &nAttriID ) == NULL )
                    { return false; }

                    if ( !AddBaseAttribute( nEquipLevel, nElement, nCount, nIndex, nMaxBaseAttriCount, nAttriID ) )
                    { return false; }

                    ++nIndex;
                    pAttribute = pAttribute->NextSiblingElement();
                }

                pCount = pCount->NextSiblingElement();
            }


            pEAttribute = pEAttribute->NextSiblingElement();
        }


        pEquipLevel = pEquipLevel->NextSiblingElement();
    }

    return true;
}