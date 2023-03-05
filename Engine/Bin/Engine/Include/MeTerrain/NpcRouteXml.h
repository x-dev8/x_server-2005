/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NPCRouteXml.h
* Create: 	11/07/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __NPC_ROUTE_XML_H__
#define __NPC_ROUTE_XML_H__
//#include "atlpath.h"

class CxImage;
class CToolWorld;
class CNPCRouteRes;
////////////////////////////////////////////////////////////////////////////////
class CNPCRouteXml : public Singleton<CNPCRouteXml>
{
public:	
					CNPCRouteXml();
	virtual				~CNPCRouteXml();

	bool			LoadNPCRoute();
		
	bool			WriteMapInfo(const char* worldPath);
	
	bool			RefreshTileNPCRoute(CWorldTile* tile);
	bool			RefreshTileNPCRoute(sInt32 tileId);

	void			WriteRoutePoint( MeXmlElement* pNPCRoute, CNPCRouteRes* flyRoute, size_t x );
	bool			DeleteTileNPCRoute(sInt32 tileId);

protected:
	void			InitializeNPCRoute();

	MeXmlElement*	AddMapElement(CWorldTile*  tile );

	void			VerifyRouteNPC(sInt32 nMapId,sInt32 targetId);

	MeXmlDocument	m_doc;
};








#endif //__NPC_ROUTE_XML_H__