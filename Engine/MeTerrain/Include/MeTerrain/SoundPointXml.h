/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SoundPointXml.h
* Create: 	11/07/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __SOUND_POINT_XML_H__
#define __SOUND_POINT_XML_H__
//#include "atlpath.h"

class CxImage;
class CToolWorld;
class CSoundPointRes;
////////////////////////////////////////////////////////////////////////////////
class CSoundPointXml : public Singleton<CSoundPointXml>
{
public:	
					CSoundPointXml();
	virtual				~CSoundPointXml();

	bool			LoadSoundPoint(bool bInitial = false);
		
	bool			WriteMapInfo(const char* worldPath);
	
	bool			RefreshTileSoundPoint(CWorldTile* tile);
// 	bool			RefreshTileSoundPoint(sInt32 tileId);

	bool			DeleteTileSoundPoint(sInt32 tileId);

protected:
	void			InitializeSoundPoint();

	MeXmlElement*	AddMapElement(CWorldTile*  tile );

	void			VerifyRouteFly(sInt32 nMapId,sInt32 targetId);

	MeXmlDocument	m_doc;
};








#endif //__SOUND_POINT_XML_H__