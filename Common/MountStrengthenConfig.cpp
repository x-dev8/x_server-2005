#include "MountStrengthenConfig.h"
#include "GlobalDef.h"
#include "RapidXml/MeRapidXml.h"
#ifndef GAME_CLIENT
#include "ConfigReloader.h"
#endif

bool MountStrengthenConfig::LoadResourceConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	m_mapMountStrengthenData.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pMountStrengthen = pRoot->FirstChildElement("MountStrengthen");
	if (!pMountStrengthen)
		return false;
	MeXmlElement* pMount = pMountStrengthen->FirstChildElement("Mount");

	while (pMount)
	{
		MountStrengthenData xData;

		int nMountID;
		if ( !pMount->Attribute( "MountID", &nMountID ) || nMountID == 0 )
			return false; 
		xData.SetMountID( nMountID );

		MeXmlElement* pStrengthen = pMount->FirstChildElement("Strengthen");
		while (pStrengthen)
		{
			int nMountLevel;
			if (!pStrengthen->Attribute( "MountLevel", &nMountLevel ))
				return false;

			int nLoseToLevel;
			if (!pStrengthen->Attribute( "LossToLevel", &nLoseToLevel ))
				return false;
			if (!xData.AddLossToLevel(nMountLevel, nLoseToLevel))
				return false;

			double dProbability;
			if (!pStrengthen->Attribute( "Probability", &dProbability ))
				return false;
			if (!xData.AddProbability(nMountLevel, static_cast<float>(dProbability)))
				return false;

			int nStrength;
			if (!pStrengthen->Attribute( "Strength", &nStrength ))
				return false;
			if (!xData.AddStrength(nMountLevel, nStrength))
				return false;

			int nStamina;
			if (!pStrengthen->Attribute( "Stamina", &nStamina ))
				return false;
			if (!xData.AddStamina(nMountLevel, nStamina))
				return false;

			int nAgility;
			if (!pStrengthen->Attribute( "Agility", &nAgility ))
				return false;
			if (!xData.AddAgility(nMountLevel, nAgility))
				return false;

			int nIntelligence;
			if (!pStrengthen->Attribute( "Intelligence", &nIntelligence ))
				return false;
			if (!xData.AddIntelligence(nMountLevel, nIntelligence))
				return false;

			int nPrice;
			if (!pStrengthen->Attribute( "Price", &nPrice ))
				return false;
			if (!xData.AddPrice(nMountLevel, nPrice))
				return false;

			pStrengthen = pStrengthen->NextSiblingElement();
		}

		if (!AddMountStrengthenData(xData))
			return false;

		pMount = pMount->NextSiblingElement();
	}
	return true;
}

const MountStrengthenData* MountStrengthenConfig::GetMountStrengthenData( unsigned short ustItemID ) const
{
	MountStrengthenDataMapConstIter iter = m_mapMountStrengthenData.find( ustItemID );
	if (iter == m_mapMountStrengthenData.end())
		return NULL;

	return &(iter->second);
}

bool MountStrengthenConfig::AddMountStrengthenData( const MountStrengthenData& xData )
{
	MountStrengthenDataMapIter iter = m_mapMountStrengthenData.find( xData.GetMountID() );
	if (iter != m_mapMountStrengthenData.end())
		return false;

	return m_mapMountStrengthenData.insert( std::make_pair(xData.GetMountID(), xData)).second;
}
void MountStrengthenConfig::OnReloadFinished()
{
#ifndef GAME_CLIENT
	theConfigReloader.OnReloadFinishedForRegister(eRCFGTYPE_MOUNTSTRENGTHEN,this);
#endif
}