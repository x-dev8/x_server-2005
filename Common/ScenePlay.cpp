#include "ScenePlay.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

CScenePlay::CScenePlay(void)
{
}

CScenePlay::~CScenePlay(void)
{
}

bool CScenePlay::LoadSceneConfig(const char* pszPath)
{
	if(!pszPath)
		return false;

	m_vecSet.clear();
	MeXmlDocument xMeXml;
	if(!xMeXml.LoadFile(pszPath,1))
		return false;


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot )
		return false;

	MeXmlElement* pActions = pRoot->FirstChildElement("Actions");
	if ( !pActions ) 
		return false;

	MeXmlElement* pAcion = pActions->FirstChildElement("Action");
	while (pAcion != NULL)
	{			
		SceneAction xAction;

		int id;
		if (pAcion->Attribute("Id", &id) == NULL)
			return false;

		xAction.nId = id;

		int nModelId = -1;
		if(pAcion->Attribute("ModelID",&nModelId) == NULL)
			return false;

		xAction.nModelID = nModelId;

		float fx = 0.0f,fy = 0.0f,fz = 0.0f,fRot = 0.0f;
		if(pAcion->Attribute("Mx",&fx) == NULL)
			return false;

		xAction.fx = fx;

		if(pAcion->Attribute("My",&fy) == NULL)
			return false;

		xAction.fy = fy;

		if(pAcion->Attribute("Mz",&fz) == NULL)
			return false;

		xAction.fz = fz;

		if(pAcion->Attribute("Rot",&fRot) == NULL)
			return false;

		xAction.fRot = fRot;

		MeXmlElement *pElapse = pAcion->FirstChildElement("ElapseTime");
		if(!pElapse)
			return false;

		while( NULL != pElapse )
		{
			ElapseTime xTime;
			int nElapID = 0;
			if(pElapse->Attribute("Id",&nElapID) == NULL)
				return false;

			xTime.nId = nElapID;

			int nTime = 0;
			if(pElapse->Attribute("Time",&nTime) == NULL)
				return false;

			xTime.nTime = nTime;

			int nNextId = 0;
			if(pElapse->Attribute("NextTimeId",&nNextId) == NULL)
				return false;

			xTime.nNextId = nNextId;

			MeXmlElement *pSegment = pElapse->FirstChildElement("Segment");
			if(!pSegment)
				return false;

			Segment seg;

			Common::_tstring playAnim;
			playAnim.fromUTF8(pSegment->Attribute("AnimStart"));
			seg.strAnimBegin = playAnim;


			playAnim.fromUTF8(pSegment->Attribute("AnimEnd"));
			seg.strAnimEnd = playAnim;

			int nTalkId = 0;
			if(pSegment->Attribute("talkId",&nTalkId) == NULL)
				return false;

			seg.nTalkId = nTalkId;

			Common::_tstring trackAnim;
			trackAnim.fromUTF8(pSegment->Attribute("Track"));
			seg.strTrack = trackAnim;

			Common::_tstring mountAnim;
			mountAnim.fromUTF8(pSegment->Attribute("MountAnimStart"));
			seg.strMountAnimBegin = mountAnim;

			mountAnim.fromUTF8(pSegment->Attribute("MountAnimEnd"));
			seg.strMountAnimEnd = mountAnim;

			xTime.set.push_back(seg);

			xAction.vecSet.push_back(xTime);

			pElapse  = pElapse->NextSiblingElement();
		}

		m_vecSet.push_back(xAction);

		pAcion = pAcion->NextSiblingElement();
	}

	return true;
}

SceneAction* CScenePlay::GetActionInfoById(int nId)
{
	for (int i = 0;i < m_vecSet.size();++i)
	{
		SceneAction *pSceneAction = &m_vecSet[i];
		if(!pSceneAction)
			continue;

		if(pSceneAction->nId == nId)
			return pSceneAction;
	}

	return NULL;
}
