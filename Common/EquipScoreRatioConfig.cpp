#include "EquipScoreRatioConfig.h"
#include "RapidXml/MeRapidXml.h"

bool EquipScoreRatioConfig::LoadEquipScoreRatioConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pRatios = pRoot->FirstChildElement("Ratios");
	if (!pRatios)
		return false;
	MeXmlElement* pRatio = pRatios->FirstChildElement("Ratio");

	while (pRatio)
	{
		int nId = -1;
		if (!pRatio->Attribute("ID", &nId))
			return false;

		double fRatio = 0.0f;
		if (!pRatio->Attribute("Value", &fRatio))
			return false;

		if (!AddAttrRatio(nId - 1, static_cast<float>(fRatio)))
			return false;

		pRatio = pRatio->NextSiblingElement();
	}

	return true;
}