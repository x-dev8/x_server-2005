#include "Kwamemap.h"
#include "RapidXml/MeRapidXml.h"

CKwamemap::CKwamemap(void)
{
	_mapKwamemaps.clear();
}

CKwamemap::~CKwamemap(void)
{
	Destry();
}

void CKwamemap::Destry()
{
	/*mapKwamemaps::iterator itrMaps = _mapKwamemaps.begin();
	while(itrMaps != _mapKwamemaps.end())
	{
		mapSKwamemap::iterator itrMap = itrMaps->second->_mapSKwamemap.begin();
		while (itrMap != itrMaps->second->_mapSKwamemap.end())
		{
			delete itrMaps->second;
			itrMaps++;
		}
		itrMaps->second->_mapSKwamemap.clear();
		delete itrMaps->second;
		itrMaps++;
	}
	_mapKwamemaps.clear();*/
}

bool CKwamemap::LoadConfigFile(const char* file_name)
{
	if (file_name == NULL)
	{
		return false;
	}

	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(file_name))
	{
		return false;
	}

	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL)
	{
		return false;
	}

	MeXmlElement* pKwamemaps = pRoot->FirstChildElement("Kwamemaps");
	int start_id = -1;
	int target_id = -1;
	int npc_id = -1;
	int through_id = -1;
	while(pKwamemaps)
	{
		if (pKwamemaps->Attribute("StartId",&start_id) == NULL)
		{
			pKwamemaps = pKwamemaps->NextSiblingElement("Kwamemaps");
			continue;
		}
		if (start_id >= 0)
		{
			SKwameMaps* pKwames = new SKwameMaps;
			pKwames->nStartMap_id = start_id;
			if (start_id == 6)
			{
				int mmm = 0;
				mmm++;
			}

			MeXmlElement* pKwamemap = pKwamemaps->FirstChildElement("Kwamemap");
			while(pKwamemap)
			{
				if (!pKwamemap->Attribute("TargetId",&target_id))
				{
					pKwamemap = pKwamemap->NextSiblingElement("Kwamemap");
					continue;
				}
				if (target_id >= 0)
				{
					SKwameMap* pMap = new SKwameMap;
					pMap->nTargetMap_id = target_id;

					//读取行走路线
					MeXmlElement* pwalkline = pKwamemap->FirstChildElement("walkline");
					if(pwalkline)
					{
						MeXmlElement* pThroughId = pwalkline->FirstChildElement("ThroughId");
						while(pThroughId)
						{
							if (!pThroughId->Attribute("mapid",&through_id))
							{
								pThroughId = pThroughId->NextSiblingElement("ThroughId");
								continue;
							}
							if (through_id >= 0)
							{
								pMap->_SWalkLine._vecThroughid.push_back(through_id);
							}
							pThroughId = pThroughId->NextSiblingElement("ThroughId");
						}
					}

					//读取传送路线
					MeXmlElement* ptransmit = pKwamemap->FirstChildElement("transmit");
					if(ptransmit)
					{
						if (!ptransmit->Attribute("next_npcid",&pMap->_STransmitLine.npc_id))
						{
						}
						MeXmlElement* pThroughId = ptransmit->FirstChildElement("ThroughId");
						while(pThroughId)
						{
							through_id = -1;
							if (!pThroughId->Attribute("mapid",&through_id))
							{
								pThroughId = pThroughId->NextSiblingElement("ThroughId");
								continue;
							}
							if (!pThroughId->Attribute("next_npcid",&npc_id))
							{
								npc_id = -1;
							}
							if (through_id >= 0)
							{
								STransmitThrough* pTransmitThrough = new STransmitThrough;
								pTransmitThrough->mapid = through_id;
								pTransmitThrough->npc_id = npc_id;

								pMap->_STransmitLine._vecTransmit.push_back(pTransmitThrough);
							}
							pThroughId = pThroughId->NextSiblingElement("ThroughId");
						}
					}
					pKwames->_mapSKwamemap.insert(make_pair(pMap->nTargetMap_id,pMap));
				}
				pKwamemap = pKwamemap->NextSiblingElement("Kwamemap");
			}
			_mapKwamemaps.insert(make_pair(pKwames->nStartMap_id,pKwames));
		}
		pKwamemaps = pKwamemaps->NextSiblingElement("Kwamemaps");
	}
	return true;
}

CKwamemap::SKwameMap* CKwamemap::FindKwameMap(int start_id,int traget_id)
{
	if (start_id < 0 || traget_id < 0)
	{
		return NULL;
	}
	mapKwamemaps::iterator itrMaps = _mapKwamemaps.find(start_id);
	if (itrMaps == _mapKwamemaps.end())
	{
		return NULL;
	}

	mapSKwamemap::iterator itrMap = itrMaps->second->_mapSKwamemap.find(traget_id);
	if (itrMap == itrMaps->second->_mapSKwamemap.end())
	{
		return NULL;
	}
	
	return itrMap->second;
}