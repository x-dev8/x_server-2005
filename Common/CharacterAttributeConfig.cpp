#include "CharacterAttributeConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"
#include "ErrorCode.h"

CharacterAttributeConfig& CharacterAttributeConfig::GetInstance()
{
    static CharacterAttributeConfig instance; 
    return instance;
}

CharacterAttributeConfig::CharacterAttributeConfig()
{
}

uint32 CharacterAttributeConfig::LoadLevelBaseSecondAttribute( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    { return ER_Failed; }

    MeXmlDocument doc;
    if( !doc.LoadFile( szFileName ) )
    { return ER_FileNotFound; }

    MeXmlElement* lpRoot = doc.FirstChildElement("Root");
    if(!lpRoot) 
    { return ER_Failed; }

    MeXmlElement* pArms = lpRoot->FirstChildElement("Arms");
    if(!pArms)    
    { return ER_Failed; }

    while ( pArms )
    {
        int nTypeId = 0;
        pArms->QueryIntAttribute("TypeId",&nTypeId);
        if ( nTypeId < 0 || nTypeId >= EArmType_MaxSize )
        { return ER_Failed; }

        const char* szName = pArms->Attribute("Name");
        if ( !szName ) 
        { return ER_Failed; }

        strncpy_s( m_ArmCharacterAttributes[ nTypeId ].szArmName, sizeof( m_ArmCharacterAttributes[ nTypeId ].szArmName), szName, ARMS_NAME_LENGTH);

        MeXmlElement* pBaseAttributes = pArms->FirstChildElement("BaseAttributes");
        if(!pBaseAttributes) 
        { return ER_Failed; }

        MeXmlElement* pSubElement = pBaseAttributes->FirstChildElement("LevelAttribute");
        while ( pSubElement )
        {
            int nLevel = 0;

            pSubElement->QueryIntAttribute( "Level", &nLevel);
            int nIndex = nLevel - 1;
            if ( nIndex<0 || nIndex>=MAX_LEVEL_LIMIT)
            { return ER_Failed; }

            for(int iKey=0; iKey<EBaseAttr_MaxSize; ++iKey)
            {
                char szAttrKey[32] = {0};
                int nAttrValue = 0;

                sprintf_s( szAttrKey, sizeof(szAttrKey)-1, "baseValue%d", iKey );
                pSubElement->Attribute( szAttrKey, &nAttrValue);

                m_ArmCharacterAttributes[ nTypeId ].LevelAttribute[ nIndex ].baseAttribute[ iKey ] =  nAttrValue;

            }

            pSubElement = pSubElement->NextSiblingElement("LevelAttribute");
        }

        MeXmlElement* pSecondAttributes= pArms->FirstChildElement("SecondAttributes");
        if( !pSecondAttributes)
        { return ER_Failed; }

        pSubElement = pSecondAttributes->FirstChildElement("LevelSecondAttributeCorrect");
        while ( pSubElement )
        {
            int nLevel = 0;
            pSubElement->QueryIntAttribute( "Level", &nLevel);

            int nIndex = nLevel - 1;
            if ( nIndex<0 || nIndex>=MAX_LEVEL_LIMIT)
            { return ER_Failed; }

            for(int iKey=0;iKey<ESecondAttrFixType_MaxSize;iKey++)
            {
                char szAttrKey[32];
                int nAttrValue = 0;
                sprintf_s( szAttrKey, sizeof(szAttrKey)-1, "secondValue%d", iKey );
                pSubElement->Attribute( szAttrKey, &nAttrValue);
                m_ArmCharacterAttributes[ nTypeId ].LevelAttribute[ nIndex ].secondAttributeFix[ iKey ] =  nAttrValue;
            }

            pSubElement = pSubElement->NextSiblingElement("LevelSecondAttributeCorrect");
        }

        pArms = pArms->NextSiblingElement("Arms");
    }
    return ER_Success;
}

uint32 CharacterAttributeConfig::SaveLevelBaseSecondAttribute( const char* szFileName )
{
    if (szFileName == NULL || *szFileName == 0)
    { return ER_Failed; }

    MeXmlDocument xMeXmlDoc;
    xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Root"))->ToElement();
    if (pRoot == NULL) 
    { return ER_Failed; }

    for(int nTypeId=0; nTypeId<EArmType_MaxSize;++nTypeId)
    {
        MeXmlElement* pArms = pRoot->InsertEndChild(("Arms"))->ToElement();
        if (pArms == NULL)
        { return ER_Failed; }

        pArms->SetAttribute("TypeId", nTypeId);
        pArms->SetAttribute("Name",  m_ArmCharacterAttributes[ nTypeId ].szArmName);

        MeXmlElement* pBaseAttributes = pArms->InsertEndChild(("BaseAttributes"))->ToElement();
        if (pBaseAttributes == NULL) 
        { return ER_Failed; }

        MeXmlElement* pSecondAttributes = pArms->InsertEndChild(("SecondAttributes"))->ToElement();
        if (pSecondAttributes == NULL) 
        { return ER_Failed; }

        for(int nLevel=0;nLevel<MAX_LEVEL_LIMIT; ++nLevel)
        {
            MeXmlElement* pLevelAttribute = pBaseAttributes->InsertEndChild(("LevelAttribute"))->ToElement();
            if (pLevelAttribute == NULL)
            { return ER_Failed; }

            pLevelAttribute->SetAttribute("Level", nLevel + 1);

            for(int iKey=0;iKey<EBaseAttr_MaxSize; ++iKey)
            {
                char szAttrKey[32] = {0};
                sprintf_s( szAttrKey, sizeof(szAttrKey)-1, "baseValue%d", iKey );

                char szAttrValue[32] = {0};
                sprintf_s( szAttrValue, sizeof(szAttrValue)-1, "%d", m_ArmCharacterAttributes[ nTypeId ].LevelAttribute[ nLevel ].baseAttribute[ iKey ] );

                pLevelAttribute->SetAttribute(szAttrKey, szAttrValue);
            }

            MeXmlElement* pLevelSecondAttribute = pSecondAttributes->InsertEndChild(("LevelSecondAttributeCorrect"))->ToElement();
            if (pLevelSecondAttribute == NULL) 
            { return ER_Failed; }

            pLevelSecondAttribute->SetAttribute("Level", nLevel + 1);

            for(int iKey=0;iKey<ESecondAttrFixType_MaxSize;iKey++)
            {
                char szAttrKey[32] = {0};
                sprintf_s( szAttrKey, sizeof(szAttrKey)-1, "secondValue%d", iKey );

                char szAttrValue[32] = {0};
                sprintf_s( szAttrValue, sizeof(szAttrValue)-1, "%d", m_ArmCharacterAttributes[ nTypeId ].LevelAttribute[ nLevel ].secondAttributeFix[ iKey ] );

                pLevelSecondAttribute->SetAttribute(szAttrKey, szAttrValue);
            }
        }
    }

    return xMeXmlDoc.SaveFile(szFileName);
}
