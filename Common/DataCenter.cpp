#include "DataCenter.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "ErrorCode.h"
DataCenter& DataCenter::GetInstance()
{
    static DataCenter instance; 
    return instance;
}

DataCenter::DataCenter()
{
}

long DataCenter::LoadArmsParamModulus( const char* szFileName )
{
    MeXmlDocument doc;
    if( !doc.LoadFile( szFileName ) )
        return ER_FileNotFound;

    MeXmlElement* pRoot = doc.FirstChildElement("Root");
    if(!pRoot)
        return ER_Failed;

    // Common Param
    MeXmlElement* pElementCommon = pRoot->FirstChildElement("Common");
    if ( !pElementCommon )
        return ER_Failed;

    MeXmlElement* pElementParam = pElementCommon->FirstChildElement("Param");
    if ( !pElementParam)
        return ER_Failed;

    MeXmlElement* pSpeedElement = pElementParam->FirstChildElement("Speed");
    if ( !pSpeedElement)
        return ER_Failed;

    int nValue = 0;
    float fValue = 0.0f;

    pSpeedElement->QueryFloatAttribute("MoveRate", &fValue);
    _armsParamModulusCommon.fSpeedMove = fValue;

    pSpeedElement->QueryIntAttribute("NormalAttack", &nValue);
    _armsParamModulusCommon.sSpeedNormalAttack = nValue;

    //////////////////////////////////////////////////////////////////////////
    // 战斗系数
    MeXmlElement* pFightModulus = pElementCommon->FirstChildElement("FightModulus");
    if ( !pFightModulus)
    { return ER_Failed; }

    pFightModulus->Attribute("ExactMin", &nValue );
    _armsParamModulusCommon.exactMin = nValue;

    pFightModulus->Attribute("Exact", &nValue );
    _armsParamModulusCommon.exactModulus = nValue;

    pFightModulus->Attribute("AttackModulus", &nValue );
    _armsParamModulusCommon.attackModulus = nValue;

    pFightModulus->Attribute("DefendModulus", &nValue );
    _armsParamModulusCommon.defendModulus = nValue;

    pFightModulus->Attribute("BackStrikeModulus", &nValue );
    _armsParamModulusCommon.backStrikeModulus = nValue;

    pFightModulus->Attribute("CriticalMin", &nValue );
    _armsParamModulusCommon.criticalMin = nValue;

    pFightModulus->Attribute("CriticalModulus", &nValue );
    _armsParamModulusCommon.criticalModulus = nValue;

    pFightModulus->Attribute("CriticalIntensityModulus", &nValue );
    _armsParamModulusCommon.criticalIntensityModulus = nValue;

    pFightModulus->Attribute("DamageMin", &nValue );
    _armsParamModulusCommon.damageMinValue = nValue;

    pFightModulus->Attribute("AttackMonsterModulus", &nValue );
    _armsParamModulusCommon.attackMonsterModulus = nValue;

    pFightModulus->Attribute("AttackPlayerModulus", &nValue );
    _armsParamModulusCommon.attackPlayerModulus = nValue;

    //////////////////////////////////////////////////////////////////////////
    // 潜力点
    _armsParamModulusCommon.vecBaseAttrPotential.clear();
    MeXmlElement* pBaseAttrPotential = pElementCommon->FirstChildElement("BaseAttrPotential");
    if ( pBaseAttrPotential != NULL)
    {
        MeXmlElement* pLevelElement = pBaseAttrPotential->FirstChildElement("Level");
        if (pLevelElement == NULL)
        { return ER_Failed; }

        while( pLevelElement )
        {   
            SBaseAttrPotential xPotential;

            pLevelElement->Attribute("Begin", &nValue );
            xPotential.beginLevel = nValue;

            pLevelElement->Attribute("End", &nValue );
            xPotential.endLevel = nValue;

            pLevelElement->Attribute("Potential", &nValue );
            xPotential.potential = nValue;

            _armsParamModulusCommon.vecBaseAttrPotential.push_back(xPotential);

            pLevelElement = pLevelElement->NextSiblingElement("Level");
        }
    }
    else
    { return ER_Failed; }
 

    //////////////////////////////////////////////////////////////////////////
    // Every Arms
    MeXmlElement* pArmsElement = pRoot->FirstChildElement("Arms");
    while( pArmsElement )
    {   
        int  nTypeId = 0;
        pArmsElement->QueryIntAttribute("TypeId", &nTypeId );
        if ( nTypeId < 0 || nTypeId>=EArmType_MaxSize )
            return ER_Failed;

        _armParamModulusExtends[nTypeId].armsType = nTypeId;        
        
        const char* szName = pArmsElement->Attribute("Name");
        if ( !szName )
            return ER_Failed;

        strncpy_s( _armParamModulusExtends[nTypeId].armsName, sizeof( _armParamModulusExtends[nTypeId].armsName ), szName, MAX_NAME_STRING );

        MeXmlElement* pAttackFloating = pArmsElement->FirstChildElement("AttackFloating");
        if ( !pAttackFloating )
            return ER_Failed;

        int nValue = 0;
        for ( int i=0; i<ATTACK_FLOAT_COUNT; ++i)
        {
            char szTmpBuffer[128] = {0};
            sprintf_s( szTmpBuffer, sizeof( szTmpBuffer ) - 1, "Value%d", i+1);
            pAttackFloating->QueryIntAttribute( szTmpBuffer, &nValue);
            _armParamModulusExtends[nTypeId].sAttackFloating[i]= nValue;
        }

        MeXmlElement* pBaseAttrToFightAttr = pArmsElement->FirstChildElement("BaseAttrToFightAttr");
        if ( pBaseAttrToFightAttr != NULL )
        {
            MeXmlElement* pStrength = pBaseAttrToFightAttr->FirstChildElement("Strength");
            if (pStrength == NULL)
            { return ER_Failed; }

            pStrength->Attribute("PhysicsAttack", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fStrengthToPhysicsAttack = fValue;
            
            MeXmlElement* pIntelligence = pBaseAttrToFightAttr->FirstChildElement("Intelligence");
            if (pIntelligence == NULL)
            { return ER_Failed; }

            pIntelligence->Attribute("MagicAttack", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fIntelligenceToMagicAttack = fValue;

            MeXmlElement* pStamina = pBaseAttrToFightAttr->FirstChildElement("Stamina");
            if (pStamina == NULL)
            { return ER_Failed; }

            pStamina->Attribute("HPMax", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fStaminaToHPMax = fValue;
            pStamina->Attribute("PhysicsDefend", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fStaminaToPhysicsDefend = fValue;
            pStamina->Attribute("MagicDefend", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fStaminaToMagicDefend = fValue;

            MeXmlElement* pAgility = pBaseAttrToFightAttr->FirstChildElement("Agility");
            if (pAgility == NULL)
            { return ER_Failed; }

            pAgility->Attribute("Exact", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fAgilityToExact = fValue;
            pAgility->Attribute("Dodge", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fAgilityToDodge = fValue;
            pAgility->Attribute("Critical", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fAgilityToCritical = fValue;
            pAgility->Attribute("Tenacity", &fValue );
            _armParamModulusExtends[nTypeId].baseFightAttr.fAgilityToTenacity = fValue;

        }
        else
        { return ER_Failed; }

        pArmsElement = pArmsElement->NextSiblingElement("Arms");
    }
    
    return ER_Success;
}

uint32 DataCenter::LoadItemSymbol( const char* szFileName )
{
    _itemSymbols.clear();

    MeXmlDocument doc;
    if( !doc.LoadFile( szFileName ) )
    { return ER_Failed; }

    MeXmlElement* pProject = doc.FirstChildElement("Project");
    if( pProject == NULL )
    { return ER_Failed; }

    // Common Param
    MeXmlElement* pItemSymbols = pProject->FirstChildElement("ItemSymbols");
    if ( !pItemSymbols )
    { return ER_Failed; }
    
    MeXmlElement* pElement = pItemSymbols->FirstChildElement("ItemSymbol");
    
    while( pElement )
    {
        int id = 0;
        int itemId = 0;
        pElement->QueryIntAttribute("Id",     &id     );
        pElement->QueryIntAttribute("ItemId", &itemId );        

        if ( id >= 0 && itemId > 0 )
        { _itemSymbols[ id ] = itemId; }
        
        pElement = pElement->NextSiblingElement("ItemSymbol");
    }

    MeXmlElement* pTileSymbols = pProject->FirstChildElement("TileSymbols");
    if ( !pItemSymbols )
    { return ER_Failed; }

    pElement = pTileSymbols->FirstChildElement("TileSymbol");

    while( pElement )
    {
        int id = 0;
        int tileId = 0;
        pElement->QueryIntAttribute("Id",     &id     );
        pElement->QueryIntAttribute("TileId", &tileId );        

        if ( id >= 0 && tileId > 0 )
        { _tileSymbols[ id ] = tileId; }

        pElement = pElement->NextSiblingElement("TileSymbol");
    }

    MeXmlElement* pVarSymbols = pProject->FirstChildElement("VarSymbols");
    if ( !pVarSymbols )
    { return ER_Failed; }

    pElement = pVarSymbols->FirstChildElement("VarSymbol");

    while( pElement )
    {
        int id = 0;
        int varId = 0;
        pElement->QueryIntAttribute("Id",    &id     );
        pElement->QueryIntAttribute("VarId", &varId );        

        if ( id >= 0 && varId > 0 )
        { _varSymbols[ id ] = varId; }

        pElement = pElement->NextSiblingElement("VarSymbol");
    }

    return ER_Success;
}

uint16 DataCenter::GetItemSymbol( uint16 itemSymbolId )
{
    if( itemSymbolId < 0 || itemSymbolId >= AN_MI_MAX)
    { return InvalidLogicNumber; }

    ItrSymbolContainer it = _itemSymbols.find( itemSymbolId );
    if( it != _itemSymbols.end() )
    { return it->second; }

    return InvalidLogicNumber;
}

uint16 DataCenter::GetTileSymbol ( uint16 tileSymbolId )
{
    if( tileSymbolId < 0 || tileSymbolId >= TS_MAX)
    { return InvalidLogicNumber; }

    ItrSymbolContainer it = _tileSymbols.find( tileSymbolId );
    if( it != _tileSymbols.end() )
    { return it->second; }

    return InvalidLogicNumber;
}


int16 DataCenter::GetVarSymbol( uint16 varSymbolId )
{
    if( varSymbolId < 0 || varSymbolId >= VS_MAX)
    { return -1; }

    ItrVarSymbolContainer it = _varSymbols.find( varSymbolId );
    if( it != _varSymbols.end() )
    { return it->second; }

    return -1;
}

bool CChangeItemID::LoadIDChangeList( )
{
	m_changeidmap.clear();
	char* szFile;
	szFile="config\\changeitemid.xml";
	if (!szFile)
	{
		// ToLog(false && "reading changeitemid.xml error!");
		return false;
	}
	else
	{
		MeXmlDocument doc;
		if( !doc.LoadFile( szFile ) )
		{
			// ToLog(false && "CChangeItemID::LoadIDChangeList() reading changeitemid.xml error!");
			return false;
		}
		MeXmlElement* lpRoot = doc.FirstChildElement("root");
		if (lpRoot)
		{
			MeXmlElement* lpRenegade = lpRoot->FirstChildElement("itemid");
			while(lpRenegade)
			{
				int source = 0;
				int dst = 0;
				lpRenegade->QueryIntAttribute("sourceid",&source);
				lpRenegade->QueryIntAttribute("dstid",&dst);
				if (source >= 0 && dst >= 0)
				{
					SProcessId* pId = new SProcessId;
					pId->sourceid = source;
					pId->dstid = dst;
					m_changeidmap.insert(mapChangeItemID::value_type(pId->sourceid,pId));					
				}
				lpRenegade = lpRenegade->NextSiblingElement("itemid");				
			}
			return true;
		}
        return false;
	}
}