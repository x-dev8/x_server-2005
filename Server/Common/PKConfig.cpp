#include "PKConfig.h"
#include "RapidXml/MeRapidXml.h"
bool PKConfig::LoadConfigFile(const char* FilePath)
{
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if(pRoot == NULL)
		return false;
	MeXmlElement* pPKRoot = pRoot->FirstChildElement("PK");
	if(pPKRoot == NULL)
		return false;
	
	if (pPKRoot->Attribute("EnterJianYu",&EnterJianYu) == NULL)
		return false;

	if (pPKRoot->Attribute("LeaveJianYu",&LeaveJianYu) == NULL)
		return false;

	if (pPKRoot->Attribute("MaxPKValue",&MaxPKValue) == NULL)
		return false;

	if (pPKRoot->Attribute("MinPKValue",&MinPKValue) == NULL)
		return false;

	if (pPKRoot->Attribute("PKKillValue",&PKKillValue) == NULL)
		return false;

	if (pPKRoot->Attribute("PKValueUpdateTime",&PKValueUpdateTime) == NULL)
		return false;

	if (pPKRoot->Attribute("EnterCritical",&EnterCriticalPK) == NULL)
		return false;

	if (pPKRoot->Attribute("CommonID",&CommonID) == NULL)
		return false;

	return true;
}
