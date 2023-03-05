#include "EquipUpgradeConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"


bool EquipUpgradeConfig::LoadEquipUpgradeConfig( const char* szFile )
{
    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    m_mapUpgradeData.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pEquips = pRoot->FirstChildElement( "Equips" );
    if ( pEquips == NULL ) 
    { return false; }

    MeXmlElement* pEquip = pEquips->FirstChildElement( "Equip" );
    while ( pEquip != NULL ) 
    {
        UpgradeData xData;

        int nEquipID;
        if ( pEquip->Attribute( "EquipID", &nEquipID ) == NULL || nEquipID == 0 )
        { return false; }
        xData.SetEquipID( nEquipID );

        // Éý½×µ½µÄID
        MeXmlElement* pUpToEquip = pEquip->FirstChildElement( "Upgrade" );
        while ( pUpToEquip != NULL )
        { 
            UpToEquipInfo xInfo;

            int nUpToID;
            if ( pUpToEquip->Attribute( "EquipID", &nUpToID ) == NULL || nUpToID == 0 )
            { return false; }
            xInfo.SetUpToEquipID( nUpToID );

            int nCostMoney;
            pUpToEquip->Attribute( "CostMoney", &nCostMoney );
            xInfo.SetCostMoney( nCostMoney );

            MeXmlElement* pMaterial = pUpToEquip->FirstChildElement( "Material" );
            while( pMaterial != NULL )
            {
                MaterialInfo xMaterial;

                int nMaterialID;
                if ( pMaterial->Attribute( "ItemID", &nMaterialID ) == NULL || nMaterialID == 0 )
                { return false; }
                xMaterial.SetMaterialID( nMaterialID );

                int nMaterialCount;
                if ( pMaterial->Attribute( "Count", &nMaterialCount ) == NULL || nMaterialCount == 0 )
                { return false; }
                xMaterial.SetMaterialCount( nMaterialCount );

                int nEffect;
                if ( pMaterial->Attribute( "Effect", &nEffect ) == NULL )
                { return false; }
                xMaterial.SetMaterialEffect( nEffect );

                if ( !xInfo.AddMaterialInfo( xMaterial ) )
                { return false; }

                pMaterial = pMaterial->NextSiblingElement();
            }

            if ( xInfo.GetMaterialCount() == 0 )
            { return false; }

            if ( !xData.AddUpToEquipID( xInfo ) )
            { return false; }

            pUpToEquip = pUpToEquip->NextSiblingElement();
        }

        if ( xData.GetUpToEquipCount() == 0 )
        { return false; }

        if ( !AddEquipUpgradeData( xData ) )
        { return false; }

        pEquip = pEquip->NextSiblingElement();
    }

    return true;
}