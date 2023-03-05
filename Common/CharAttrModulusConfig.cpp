#include "CharAttrModulusConfig.h"
#include "RapidXml/MeRapidXml.h"

CharAttrModulusConfig::CharAttrModulusConfig()
{
}

CharAttrModulusConfig::~CharAttrModulusConfig()
{
}

bool CharAttrModulusConfig::LoadCharAttrModulusConfig(char* szFileName)
{
    if ( szFileName == NULL || *szFileName == 0 )
    { return false; }

    mapProfessionModulus.clear();
    mapAttackFloatModulus.clear();
    fTotalDamageModulus   = 0.0f;
    fMonsterDamageModulus = 0.0f;
    fPlayerDamageModulus  = 0.0f;

    int nValue = 0;
    float fValue = 0.0f;

    MeXmlDocument xDoc;
    if ( !xDoc.LoadFile( szFileName ) )
    { return false; }

    MeXmlElement* pRoot = xDoc.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pProfessions = pRoot->FirstChildElement( "Professions" );
    if ( pProfessions == NULL )
    { return false; }

    MeXmlElement* pProfession = pProfessions->FirstChildElement( "Profession" );
    while ( pProfession != NULL )
    {
        ProfessionModulus xProfessionModulus;

        pProfession->Attribute( "Type", &nValue );
        xProfessionModulus.nProfessionId = nValue;

        // 一级属性对二级属性影响系数
        MeXmlElement* pBaseAttrs = pProfession->FirstChildElement( "BaseAttrs" );
        if ( pBaseAttrs == NULL )
        { return false; }

        MeXmlElement* pBaseAttr = pBaseAttrs->FirstChildElement( "BaseAttr" );
        while ( pBaseAttr != NULL )
        {
            AttrModulus xAttrModulus;

            pBaseAttr->Attribute( "Id", &nValue );
            xAttrModulus.nBaseAttrId = nValue;

            for ( int i = 0; i < EC_MAX; ++i )
            {
                char szTemp[20] = { 0 };
                memset( szTemp, 0, sizeof(szTemp) );
                sprintf_s( szTemp, sizeof( szTemp ) - 1, "Mode%d", i );
                pBaseAttr->Attribute( szTemp, &fValue );
                xAttrModulus.Modulus[i] = fValue;
            }

            xProfessionModulus.mapAttrModulus.insert( std::make_pair( xAttrModulus.nBaseAttrId, xAttrModulus ) );
            pBaseAttr = pBaseAttr->NextSiblingElement();
        }

        // 物理与魔法伤害结算伤害
        MeXmlElement* pPhyModulus = pProfession->FirstChildElement( "PhyModulus" );
        if ( pPhyModulus == NULL  )
        { return false; }

        pPhyModulus->Attribute( "Value", &fValue );
        xProfessionModulus.phyDamageModulus = fValue;

        MeXmlElement* pMagicModulus = pProfession->FirstChildElement( "MagicModulus" );
        if ( pMagicModulus == NULL )
        { return false; }

        pMagicModulus->Attribute( "Value", &fValue );
        xProfessionModulus.magicDamageModulus = fValue;

        // 属性伤害系数
        MeXmlElement* pAttrAttackModuluses = pProfession->FirstChildElement( "AttrAttackModuluses" );
        if ( pAttrAttackModuluses == NULL )
        { return false; }

        MeXmlElement* pAttrAttackModulus = pAttrAttackModuluses->FirstChildElement( "AttrAttackModulus" );
        if ( pAttrAttackModulus == NULL )
        { return false; }

        while ( pAttrAttackModulus != NULL )
        {
            AttrAttackModulus xAttrAttackModulus;
            pAttrAttackModulus->Attribute( "Type", &nValue );
            xAttrAttackModulus.nType = nValue;

            pAttrAttackModulus->Attribute( "AttackModulus", &fValue );
            xAttrAttackModulus.fAttackModulus = fValue;

            pAttrAttackModulus->Attribute( "AttackFixPer", &nValue );
            xAttrAttackModulus.nAttackFixPer = nValue;

            xProfessionModulus.mapAttrAttackModulus.insert( std::make_pair( xAttrAttackModulus.nType, xAttrAttackModulus ) );
            pAttrAttackModulus = pAttrAttackModulus->NextSiblingElement();
        }

        mapProfessionModulus.insert( std::make_pair( xProfessionModulus.nProfessionId, xProfessionModulus ) );
        pProfession = pProfession->NextSiblingElement();
    }

    // 其他Char的控制系数
    MeXmlElement* pOtherAttackModulus = pRoot->FirstChildElement( "OtherAttackModulus" );
    if ( pOtherAttackModulus == NULL )
    { return NULL; }

    pOtherAttackModulus->Attribute( "PhyAtkValue", &fValue );
    fOtherPhyAtkModulus = fValue;

    pOtherAttackModulus->Attribute( "MagicAtkValue", &fValue );
    fOtherMagicAtkModulus = fValue;

    MeXmlElement* pPetAttackModulus = pRoot->FirstChildElement( "PetAttackModulus" );
    if ( pPetAttackModulus == NULL )
    { return false; }

    MeXmlElement* pPet = pPetAttackModulus->FirstChildElement( "Pet" );
    while ( pPet != NULL )
    {
        PetAtkModulus xPetAtkModulus;

        pPet->Attribute( "AtkType", &nValue );
        xPetAtkModulus.nPetAtkType = nValue;

        pPet->Attribute( "PhyAtkValue", &fValue );
        xPetAtkModulus.fPhyAtkModulus = fValue;

        pPet->Attribute( "MagicAtkValue", &fValue );
        xPetAtkModulus.fMagicAtkModulus = fValue;

        mapPetAtkModulus.insert( std::make_pair( xPetAtkModulus.nPetAtkType, xPetAtkModulus ) );
        pPet = pPet->NextSiblingElement();
    }

    MeXmlElement* pTotalDamageModulus = pRoot->FirstChildElement( "TotalDamageModulus" );
    if ( pTotalDamageModulus == NULL )
    { return false; }

    pTotalDamageModulus->Attribute( "Value", &fValue );
    fTotalDamageModulus = fValue;

    MeXmlElement* pMonsterDamageModulus = pRoot->FirstChildElement( "MonsterDamageModulus" );
    if ( pMonsterDamageModulus == NULL )
    { return false; }

    pMonsterDamageModulus->Attribute( "Value", &fValue );
    fMonsterDamageModulus = fValue;

    MeXmlElement* pPlayerDamageModulus = pRoot->FirstChildElement( "PlayerDamageModulus" );
    if ( pPlayerDamageModulus == NULL )
    { return false; }

    pPlayerDamageModulus->Attribute( "Value", &fValue );
    fPlayerDamageModulus = fValue;

    MeXmlElement* pAttackFloatModuluses = pRoot->FirstChildElement( "AttackFloatModuluses" );
    if ( pAttackFloatModuluses == NULL )
    { return false; }

    MeXmlElement* pAttackFloatModulus = pAttackFloatModuluses->FirstChildElement( "AttackFloatModulus" );
    if ( pAttackFloatModulus == NULL )
    { return false; }

    while ( pAttackFloatModulus != NULL )
    {
        AttackFloatModulus xAttackFloatModulus;

        pAttackFloatModulus->Attribute( "Type", &nValue );
        xAttackFloatModulus.nType = nValue;

        pAttackFloatModulus->Attribute( "Min", &nValue );
        xAttackFloatModulus.stMin = nValue;

        pAttackFloatModulus->Attribute( "Max", &nValue );
        xAttackFloatModulus.stMax = nValue;

        mapAttackFloatModulus.insert( std::make_pair( xAttackFloatModulus.nType, xAttackFloatModulus ) );
        pAttackFloatModulus = pAttackFloatModulus->NextSiblingElement();
    }

    return true;
}

CharAttrModulusConfig::AttrModulus* CharAttrModulusConfig::ProfessionModulus::GetAttrModulusById( unsigned short nId )
{
    if ( nId < 0 )
    { return NULL; }

    return &mapAttrModulus[ nId ];
}

CharAttrModulusConfig::AttrAttackModulus* CharAttrModulusConfig::ProfessionModulus::GetAttrAttackModulusByType( unsigned short nType )
{
    if ( nType < 0)
    { return NULL; }

    return &mapAttrAttackModulus[ nType ];
}

CharAttrModulusConfig::ProfessionModulus* CharAttrModulusConfig::GetProfessionModulusById( unsigned short nId )
{
    if ( nId < 0 )
    { return NULL; }

    return &mapProfessionModulus[ nId ];
}

float CharAttrModulusConfig::GetAttackModulusMinByType( unsigned short nType )
{
    if ( nType < 0 )
    { return 0.0f; }

    return mapAttackFloatModulus[ nType ].stMin;
}

float CharAttrModulusConfig::GetAttackModulusMaxByType( unsigned short nType )
{
    if ( nType < 0 )
    { return 0.0f; }

    return mapAttackFloatModulus[ nType ].stMax;
}

CharAttrModulusConfig::PetAtkModulus* CharAttrModulusConfig::GetPetModulusByType( uint8 nType )
{
    if ( nType <= 0 )
    { return NULL; }

    return &mapPetAtkModulus[nType];
}