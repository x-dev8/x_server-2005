#include "PositionInfo.h"

// #include <tinyxml/tinyxml.h>
#include "RapidXml\MeRapidXml.h"
#include "tstring.h"

int PositionInfo::LoadConfig(const char *path)
{
	if (path == NULL || *path == 0)
	{
		return Param_Error;
	}

	positions_.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(path, 1))
	{	
		return File_Error;
	}


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return Attribute_Error;


	MeXmlElement* pPositions = pRoot->FirstChildElement("Positions");
	if ( NULL == pPositions ) return Attribute_Error;

	MeXmlElement* pPosition = pPositions->FirstChildElement("Position");
	while (pPosition != NULL)
	{			
		Position xData;

		Common::_tstring name;
		name.fromUTF8(pPosition->Attribute("Name"));
		xData.name = name;
		
		if (pPosition->Attribute("TargetId", &xData.id) != NULL)
		{
			pPosition->Attribute("Type", &xData.type);

			double x;
			pPosition->Attribute("PositionX", &x);
			xData.x = x;

			double y;
			pPosition->Attribute("PositionY", &y);
			xData.y = y;

			pPosition->Attribute("MapID", &xData.mapId);

			int show;
			pPosition->Attribute("IsShow", &show);
			xData.isShow = show;

			int NeedMount;
			pPosition->Attribute("NeedMount",&NeedMount);
			xData.needMount = NeedMount;

			int nCampType = 0;
			pPosition->Attribute("Camp", &nCampType);
			xData.campType = nCampType;

			positions_.insert(make_pair(xData.id, xData));
		}
		//next 
		pPosition = pPosition->NextSiblingElement();
	}

	return File_Success;
}

void PositionInfo::InsertPos(const Position &pos_)
{
	positions_.insert(make_pair(pos_.id, pos_));
}

PositionInfo::Position* PositionInfo::GetPositionById(int id)
{
	if (id < 0)
	{
		return NULL;
	}

	PositionsIter iter = positions_.find(id);
	if (iter != positions_.end())
	{
		return &(iter->second);
	}

	return NULL;
}

PositionInfo::Position* PositionInfo::GetPositionByName(std::string name)
{
	if (name.empty())
	{
		return NULL;
	}

	PositionsIter iter = positions_.begin();
	PositionsIter end = positions_.end();

	for ( ; iter != end; ++iter)
	{
		if (iter->second.name == name)
		{
			return &(iter->second);
		}
	}

	return NULL;
}
