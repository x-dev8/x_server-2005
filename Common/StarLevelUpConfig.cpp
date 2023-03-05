#include "StarLevelUpConfig.h"
#include "GlobalDef.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"
#ifndef GAME_CLIENT
#include "ConfigReloader.h"
#endif
#include "helper.h"
#include "ItemDetail.h"

bool StarLevelUpConfig::AddStarLevelUpData( const StarLevelUpData &xData )
{
    if ( xData.GetStarLevel() < SCharItem::EL_Min || xData.GetStarLevel() >= SCharItem::EL_Max )
    { return false; }

    MapIter iter = m_mapStarLevelUpData.find( xData.GetMaxEquipmentLevel() );
    if ( iter == m_mapStarLevelUpData.end() )
    {
        std::vector<StarLevelUpData> vecData;
        //vecData.resize( SCharItem::EL_Max );

        //vecData[xData.GetStarLevel()] = xData;
		vecData.push_back( xData );

        m_mapStarLevelUpData.insert( make_pair( xData.GetMaxEquipmentLevel(), vecData ) );
    }
    else
    {
        iter->second.push_back( xData );
    }

    return true;
}

StarLevelUpData* StarLevelUpConfig::GetStarLevelUpData( unsigned short ustEquipmentLevel, unsigned char uchStarLevel )
{
    if ( uchStarLevel < SCharItem::EL_Min || uchStarLevel >= SCharItem::EL_Max )
    { return NULL; }

    MapIter end = m_mapStarLevelUpData.end();
    for (MapIter iter = m_mapStarLevelUpData.begin(); iter != end; ++iter)
    {
        if( ustEquipmentLevel <= iter->first )
        {
            if ( uchStarLevel < iter->second.size() )
            {
            	return &(iter->second[uchStarLevel]);
            }
			break;
        }
    }

    return NULL;
}

StarLevelUpConfig::StarLevelUpDataContainer* StarLevelUpConfig::GetStarLevelUpDataByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex > GetStarLevelUpDataCount() )
    {
        return NULL;
    }

    MapIter iter = m_mapStarLevelUpData.begin();
    advance( iter, nIndex );

    return &( iter->second );
}

bool StarLevelUpConfig::AddMoveStarLevelUp( const MoveStarLevelUp& xData )
{
    MoveStarLevelUpMapIter iter = m_mapMoveStarLevelUp.find( xData.GetItemID() );
    if ( iter != m_mapMoveStarLevelUp.end() )
    { return false; }

    return m_mapMoveStarLevelUp.insert( std::make_pair( xData.GetItemID(), xData ) ).second;
}

const MoveStarLevelUp* StarLevelUpConfig::GetMoveStarLevelUp( unsigned short ustItemID ) const
{
    MoveStarLevelUpMapConstIter iter = m_mapMoveStarLevelUp.find( ustItemID );
    if ( iter == m_mapMoveStarLevelUp.end() )
    { return NULL; }

    return &( iter->second );
}

bool StarLevelUpConfig::AddTransferStarMaterial( const TransferStarMaterial& xData )
{
	TransferStarMaterialMapIter iter = m_mapTransferStarMaterial.find( xData.GetMaterialID() );
	if (iter != m_mapTransferStarMaterial.end())
		return false;

	return m_mapTransferStarMaterial.insert( std::make_pair(xData.GetMaterialID(), xData)).second;
}

const TransferStarMaterial* StarLevelUpConfig::GetTransferStarMaterial( unsigned short ustItemID ) const
{
	TransferStarMaterialMapConstIter iter = m_mapTransferStarMaterial.find( ustItemID );
	if (iter == m_mapTransferStarMaterial.end())
		return NULL;

	return &(iter->second);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//* */<LevelUp MinEquipmentLevel="1" MaxEquipmentLevel="40" StarLevel="0" LossToLevel="0" Probability="1" Price="1000" />
#define Root_Key		      "Project"
#define StarLevelUp_Key		  "StarLevelUp"
#define LevelUp_Key		      "LevelUp"
#define MinEquipmentLevel_Key "MinEquipmentLevel"
#define MaxEquipmentLevel_Key "MaxEquipmentLevel"
#define StarLevel_Key         "StarLevel"
#define LossToLevel_Key       "LossToLevel"
#define Probability_Key       "Probability"
#define Price_Key             "Price"

bool StarLevelUpConfig::LoadResourceConfig( const char* pszConfig )
{
    if (pszConfig == NULL || *pszConfig == 0)
    { return false;	}

    m_mapStarLevelUpData.clear();
    m_mapMoveStarLevelUp.clear();

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(pszConfig, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement(Root_Key);
    if (pRoot == NULL )
    { return false; }

    //版本(是否需要检查)
    //////////////////////////////////////////////////////////
    MeXmlElement* pStarLevelUp = pRoot->FirstChildElement(StarLevelUp_Key);
    if (pStarLevelUp == NULL) { return false; }

    MeXmlElement* pLevelUp = pStarLevelUp->FirstChildElement(LevelUp_Key);
    while (pLevelUp != NULL)
    {	
        StarLevelUpData xData;

        //MinEquipmentLevel
        int nMinEquipmentLevel;
        if ( pLevelUp->Attribute(MinEquipmentLevel_Key, &nMinEquipmentLevel) == NULL ) 
        { return false; }
        xData.SetMinEquipmentLevel( nMinEquipmentLevel );

        //MaxEquipmentLevel
        int nMaxEquipmentLevel;
        if ( pLevelUp->Attribute(MaxEquipmentLevel_Key, &nMaxEquipmentLevel) == NULL )
        { return false; }
        xData.SetMaxEquipmentLevel( nMaxEquipmentLevel );

        //StarLeve
        int nStarLevel;
        if ( pLevelUp->Attribute(StarLevel_Key, &nStarLevel) == NULL )
        { return false; }
        xData.SetStarLevel( nStarLevel );

        //LossToLevel
        int nLossToLevel;
        if ( pLevelUp->Attribute(LossToLevel_Key, &nLossToLevel) == NULL )
        { return false; }
        xData.SetLossToLevel( nLossToLevel );

        //Probability
        double fProbability;
        if ( pLevelUp->Attribute( Probability_Key, &fProbability ) == NULL )
        { return false; }
        xData.SetProbability( fProbability );
       
        //Price
        int nPrice;
        if ( pLevelUp->Attribute(Price_Key, &nPrice) == NULL )
        { return false; }
        xData.SetCostMoney(nPrice);

        if ( !AddStarLevelUpData(xData) ) 
        { return false; }

        //next
        pLevelUp = pLevelUp->NextSiblingElement();
    }
    
    int nValue   = 0;
    float fValue = 0.00f; 

    MeXmlElement* pStarLeveEffects = pRoot->FirstChildElement("StarLeveEffects");
    if ( pStarLeveEffects == NULL )
    { return false; }

    MeXmlElement* pStarLevelEffect = pStarLeveEffects->FirstChildElement("StarLevelEffect");
    while (pStarLevelEffect != NULL)
    {	
        SStarLevelEffect data;

        if ( pStarLevelEffect->Attribute( "Id", &nValue) == NULL ) 
        { return false; }
        data.id = nValue;

        MeXmlElement* pLevelModulus = pStarLevelEffect->FirstChildElement("LevelModulus");
        while ( pLevelModulus != NULL )
        {   
            pLevelModulus->QueryFloatAttribute( "Value", &fValue);

            data.levelModulus.push_back( fValue );
            pLevelModulus = pLevelModulus->NextSiblingElement();
        }

        bool bResult = _starLeveEffects.insert( StarLevelEffectContainer::value_type(data.id, data )).second;
        if ( !bResult )
        { return false; }
        
        // next
        pStarLevelEffect = pStarLevelEffect->NextSiblingElement();
    }
    
    MeXmlElement* pStarLeveEffectLinks = pRoot->FirstChildElement("StarLeveEffectLinks");
    if ( pStarLeveEffectLinks == NULL )
    { return false; }

    MeXmlElement* pEffectLink = pStarLeveEffectLinks->FirstChildElement("EffectLink");

    while ( pEffectLink != NULL)
    {
        SEffectLink data;

        const char* pValue = pEffectLink->Attribute( "Type");
        if (  pValue == NULL ) 
        { return false; } 
        data.type = GetEquipTypeByName(pValue);

        if ( pEffectLink->Attribute( "EffectId", &nValue) == NULL ) 
        { return false; }
        data.effectId = nValue;
        _effectLinks.push_back( data );

        pEffectLink = pEffectLink->NextSiblingElement();
    }

    MeXmlElement* pMoveStarLevelUp = pRoot->FirstChildElement("MoveStarLevelUp");
    if ( pMoveStarLevelUp == NULL )
    { return false; }
    MeXmlElement* pMoveStarItem = pMoveStarLevelUp->FirstChildElement("StarItem");
    while ( pMoveStarItem != NULL )
    {
        MoveStarLevelUp xData;
        int nItemID;
        if ( pMoveStarItem->Attribute( "ItemID", &nItemID ) == NULL || nItemID == 0 )
        { return false; }
        xData.SetItemID( nItemID );

        int nMaterialID;
        if ( pMoveStarItem->Attribute( "MaterialID", &nMaterialID ) == NULL || nMaterialID == 0 )
        { return false; }
        xData.SetMaterialID( nMaterialID );

        int nNewItemID;
        if ( pMoveStarItem->Attribute( "NewItemID", &nNewItemID ) == NULL || nNewItemID == 0 )
        { return false; }
        xData.SetNewItemID( nNewItemID );

        int nMaxCount;
        if ( pMoveStarItem->Attribute( "MaxCount", &nMaxCount ) == NULL || nMaxCount == 0 )
        { return false; }
        xData.SetMaxCount( nMaxCount );
        xData.ResizeModulus( nMaxCount + 1 );

        int nCostMoney;
        if ( pMoveStarItem->Attribute( "Money", &nCostMoney ) == NULL )
        { return false; }
        xData.SetCostMoney( nCostMoney );

        MeXmlElement* pModulusCount = pMoveStarItem->FirstChildElement("Count");
        while ( pModulusCount != NULL )
        {
            int nCount;
            if ( pModulusCount->Attribute( "Value", &nCount ) == NULL )
            { return false; }

            double dModulus;
            if ( pModulusCount->Attribute( "Modulus", &dModulus ) == NULL )
            { return false; }
            if ( !xData.AddModulus( nCount, static_cast< float >( dModulus ) ) )
            { return false; }

            pModulusCount = pModulusCount->NextSiblingElement();
        }

        if ( !AddMoveStarLevelUp( xData ) )
        { return false; }

        pMoveStarItem = pMoveStarItem->NextSiblingElement();
    }

    // StarActivation 星激活
    MeXmlElement* pStarActivation = pRoot->FirstChildElement("StarActivation");
    if ( pStarActivation == NULL )
    { return false; }
    MeXmlElement* pStar = pStarActivation->FirstChildElement("Star");
    while ( pStar != NULL )
    {
        SStarActivation::SStarInfo xData;
        int nValue = 0;
        double dValue = 0.0f;
        if ( pStar->Attribute( "Level", &nValue ) == NULL )
        { return false; }
        xData.level = nValue;
        nValue = 0;

        MeXmlElement* pEffect = pStar->FirstChildElement("Effect");
        while ( pEffect != NULL )
        {
            SStarActivation::SEffect xEffect;

            if ( pEffect->Attribute( "StartCount", &nValue ) == NULL)
            { return false; }
            xEffect.startCount = nValue;
            nValue = 0;

            if ( pEffect->Attribute( "EndCount", &nValue ) == NULL)
            { return false; }
            xEffect.endCount = nValue;
            nValue = 0;

            if ( pEffect->Attribute( "Type", &nValue ) == NULL )
            { return false; }
            xEffect.type = nValue;
            nValue = 0;

            if ( pEffect->Attribute( "Value", &dValue ) == NULL )
            { return false; }
            xEffect.value.fValue = dValue;
            dValue = 0.0f;

            xData.effects.push_back( xEffect );
            pEffect = pEffect->NextSiblingElement();
        }

        _starActivation.starInfos.push_back( xData );

        pStar = pStar->NextSiblingElement();
    }

    // StampActivation 铭刻激活
    MeXmlElement* pStampActivation= pRoot->FirstChildElement("StampActivation");
    if ( pStampActivation == NULL )
    { return false; }
    MeXmlElement* pStamp = pStampActivation->FirstChildElement("Stamp");
    while ( pStamp != NULL )
    {
        SStampActivation::SStampInfo xData;
        int nValue = 0;
        double dValue = 0.0f;
        if ( pStamp->Attribute( "Count", &nValue ) == NULL )
        { return false; }
        xData.count = nValue;
        nValue = 0;

        MeXmlElement* pEffect = pStamp->FirstChildElement("Effect");
        while ( pEffect != NULL )
        {
            SStampActivation::SEffect xEffect;

            if ( pEffect->Attribute( "Type", &nValue ) == NULL )
            { return false; }
            xEffect.type = nValue;
            nValue = 0;

            if ( pEffect->Attribute( "Value", &dValue ) == NULL )
            { return false; }
            xEffect.value.fValue = dValue;
            dValue = 0.0f;

            xData.effects.push_back( xEffect );
            pEffect = pEffect->NextSiblingElement();
        }

        _stampActivation.stampInfos.push_back( xData );

        pStamp = pStamp->NextSiblingElement();
    }

	//转星材料
	MeXmlElement* pTransferStarMaterial = pRoot->FirstChildElement("TransferStar");
	if ( pTransferStarMaterial == NULL )
	{ return false; }
	MeXmlElement* pTransferMaterial = pTransferStarMaterial->FirstChildElement("TransferMaterial");
	while ( pTransferMaterial != NULL )
	{
		TransferStarMaterial xData;

		int nMaterialID;
		if ( pTransferMaterial->Attribute( "MaterialID", &nMaterialID ) == NULL || nMaterialID == 0 )
		{ return false; }
		xData.SetMaterialID( nMaterialID );


		MeXmlElement* pModulusCount = pTransferMaterial->FirstChildElement("Count");
		while ( pModulusCount != NULL )
		{
			int nStarLevel;
			if ( pModulusCount->Attribute( "StarLevel", &nStarLevel ) == NULL )
			{ return false; }

			double dModulus;
			if ( pModulusCount->Attribute( "Modulus", &dModulus ) == NULL )
			{ return false; }
			if ( !xData.AddModulus( nStarLevel, static_cast< float >( dModulus ) ) )
			{ return false; }

			double dDropOne;
			if ( pModulusCount->Attribute( "DropOne", &dDropOne ) == NULL )
			{ return false; }
			if ( !xData.AddDropOne( nStarLevel, static_cast< float >( dDropOne ) ) )
			{ return false; }

			double dDropTwo;
			if ( pModulusCount->Attribute( "DropTwo", &dDropTwo ) == NULL )
			{ return false; }
			if ( !xData.AddDropTwo( nStarLevel, static_cast< float >( dDropTwo ) ) )
			{ return false; }

			double dDropThree;
			if ( pModulusCount->Attribute( "DropThree", &dDropThree ) == NULL )
			{ return false; }
			if ( !xData.AddDropThree( nStarLevel, static_cast< float >( dDropThree ) ) )
			{ return false; }

			int nMoney;
			if ( pModulusCount->Attribute( "Money", &nMoney ) == NULL )
			{ return false; }
			if ( !xData.AddMoney( nStarLevel, nMoney ) )
			{ return false; }

			pModulusCount = pModulusCount->NextSiblingElement();
		}

		if ( !AddTransferStarMaterial( xData ) )
		{ return false; }

		pTransferMaterial = pTransferMaterial->NextSiblingElement();
	}

	//铭刻加成百分比
	MeXmlElement* pSoul = pRoot->FirstChildElement("Soul");
	if ( pSoul == NULL )
		return false;
	int nMinPer = 0;
	pSoul->Attribute("MinPer", &nMinPer);
	_sSoul.nMinPer = nMinPer;

	int nMaxPer = 0;
	pSoul->Attribute("MaxPer", &nMaxPer);
	_sSoul.nMaxPer = nMaxPer;

	
    return true;
}

void StarLevelUpConfig::OnReloadFinished()
{
#ifndef GAME_CLIENT
	theConfigReloader.OnReloadFinishedForRegister(eRCFGTYPE_STARLEVELUP,this);
#endif

}
float StarLevelUpConfig::GetItemStarLevelModulus( uint32 equipType, uint16 starlevel )
{ // 找到此部且等级对应的系数
    ItrEffectLinkContainer it    = _effectLinks.begin();
    ItrEffectLinkContainer itEnd = _effectLinks.end();
    int16 id = -1;
    for ( ; it!=itEnd; ++it)
    {
        if ( it->type == equipType )
        { 
            id = it->effectId;
            break;
        }
    }

    if ( id == -1)
    { return 1.0f; }

    ItrStarLevelEffectContainer itFind = _starLeveEffects.find( id );
    if ( itFind == _starLeveEffects.end() )
    { return 1.0f; }

    SStarLevelEffect::LevelModulusContainer& levelModulus = itFind->second.levelModulus;
    if ( starlevel >= levelModulus.size())
    { return 1.0f;}

    return levelModulus[starlevel];
}

SStarActivation::SEffect* SStarActivation::SStarInfo::GetEffect( uint8 count )
{
    EffectContainerItr it = effects.begin();
    for ( ; it!=effects.end(); ++it )
    {
        SStarActivation::SEffect& rEffect = *it;
        if ( count >= rEffect.startCount && count <= rEffect.endCount )
        { return &(*it); }
    }
    return NULL;
}

SStarActivation::SEffect* SStarActivation::GetEffect( uint8 level, uint8 count )
{
    // 至少EConstDefine_StarActivationStartLevel以上 EConstDefine_StarActivationStartCount 以上 才有逻辑 
    if ( level < EConstDefine_StarActivationStartLevel || count < EConstDefine_StarActivationStartCount )
    { return NULL; }

    SStarInfoContainerItr it = starInfos.begin();
    for ( ; it!=starInfos.end(); ++it )
    {
        SStarInfo& rStarInfo = *it;
        if ( rStarInfo.level != level )
        { continue; }

        return rStarInfo.GetEffect( count );
    }
    return NULL;
}

bool SStampActivation::SStampInfo::GetEffect( OUT SStampActivation::EffectContainer& outputEffect )
{
    outputEffect = effects;
    return true;
}

bool SStampActivation::GetEffect( uint8 stampCount ,OUT SStampActivation::EffectContainer& outputEffect )
{
    bool bIsEffect = false;
    SStampInfoContainerItr it = stampInfos.begin();
    for ( ; it!=stampInfos.end(); ++it )
    {
        SStampInfo& rStampInfo = *it;
        if ( stampCount >= rStampInfo.count )
        {
            bIsEffect = rStampInfo.GetEffect( outputEffect );
        }
    }
    return bIsEffect;
}

SStarActivation::SEffect* StarLevelUpConfig::GetStarActivationEffect( uint8 level, uint8 count )
{
    return _starActivation.GetEffect( level, count );
}

bool StarLevelUpConfig::GetStampActivationEffect( uint8 stampCount ,OUT SStampActivation::EffectContainer& outputEffect )
{
    return _stampActivation.GetEffect( stampCount, outputEffect );
}

//////////////////////////////////////////////////////////////////////////
//  参数 attrType 传入值
//
//  RT_AddShortAttack
//  RT_AddLongAttack 
//  RT_AddMagicAttack
//
//  RT_AddShortDefend
//  RT_AddMagicDefend
//  RT_AddLongDefend 
//
//
//uint8 StarLevelUpConfig::GetEquipStampAttrAddition( SCharItem* pCharItem, uint16 attrType )
//{
//    if (pCharItem == NULL)
//    { return 0; }
//
//    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
//    if ( pItemCommon == NULL)
//    { return 0; }
//
//    float fStampAddition = SCharItem::EEquipEvolve_SoulStampAddition * DEF_PERCENT;
//
//    if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
//    {
//        ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon*)pItemCommon;
//
//        return  pItemWeapon->attack * fStampAddition;
//    }
//
//    if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
//    {
//        ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;
//
//        if (attrType == RT_AddPhysicsAttack || attrType == RT_AddLongAttack || attrType == RT_AddMagicAttack  )
//        { return  pItemArmour->attack * fStampAddition; }
//
//        if (attrType == RT_AddPhysicsDefend)
//        { return  pItemArmour->defendShort * fStampAddition; }
//
//        if (attrType == RT_AddMagicDefend)
//        { return  pItemArmour->defendMagic * fStampAddition; }
//
//        if (attrType == RT_AddLongDefend)
//        { return  pItemArmour->defendLong * fStampAddition; }
//    
//    }
//
//    return 0;    
//}
