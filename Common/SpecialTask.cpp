#include "SpecialTask.h"
#include "RapidXml/MeRapidXml.h"
#include <assert.h>

CSpecialTaskMgr::CSpecialTaskMgr()
{
	m_mapSTask.clear();
	m_multimapTask.clear();
}
CSpecialTaskMgr::~CSpecialTaskMgr()
{
	IterSpecialTask	iter = m_mapSTask.begin();
	while(iter!=m_mapSTask.end())
	{
		delete iter->second;
		iter->second = NULL;
		iter++;
	}
	m_mapSTask.clear();
	m_multimapTask.clear();
}

bool CSpecialTaskMgr::LoadConfig(const char* szPath)
{
	if (szPath==NULL)
	{
		return false;
	}
	MeXmlDocument	xMeDoc;
	if (!xMeDoc.LoadFile(szPath))
	{
		return false;
	}
	MeXmlElement*	xMeElement = xMeDoc.FirstChildElement("Project");
	if (!xMeElement)
	{
		return false;
	}
	xMeElement = xMeElement->FirstChildElement("SpecialTask");
	if (!xMeElement)
	{
		return false;
	}
	xMeElement = xMeElement->FirstChildElement("Task");
	if (!xMeElement)
	{
		return false;
	}
	int nValue = 0;
	while (xMeElement)
	{
		SSpecialTask* pNode = new SSpecialTask;

		int nTaskType = 0;
		if (xMeElement->Attribute("Type",&nTaskType) == NULL)
		{
			assert(0 && "Load SpecialTask.config: Type Error");
			xMeElement = xMeElement->NextSiblingElement();
			continue;
		}
		pNode->eType = static_cast<ESpecialTaskType>(nTaskType);

		if (xMeElement->Attribute("TaskID",&nValue) == NULL)
		{
			assert(0 && "Load SpecialTask.config: TaskID Error");
			xMeElement = xMeElement->NextSiblingElement();
			continue;
		}
		pNode->nTaskID = nValue;

		MeXmlElement* pElementReq = xMeElement->FirstChildElement("Require");
		int nTaskVarID = 0;
		int nTaskVarNum = 0;
		while (pElementReq)
		{
			if (pElementReq->Attribute("TaskVarID",&nTaskVarID)==NULL)
			{
				continue;
			}
			if (pElementReq->Attribute("Num",&nTaskVarNum)==NULL)
			{
				continue;
			}
			pNode->mapTaskVarReq.insert(make_pair(nTaskVarID,nTaskVarNum));
			pElementReq = pElementReq->NextSiblingElement();
		}

		m_mapSTask.insert(make_pair(pNode->nTaskID,pNode));
		m_multimapTask.insert(make_pair(pNode->eType,pNode));
		xMeElement = xMeElement->NextSiblingElement();
	}
	return true;
}

CSpecialTaskMgr::SSpecialTask* CSpecialTaskMgr::GetTaskByID(int nTaskID)
{
	IterSpecialTask iter = m_mapSTask.find(nTaskID);
	if (iter == m_mapSTask.end())
	{
		return NULL;
	}
	return iter->second;
}

CSpecialTaskMgr::PairIter CSpecialTaskMgr::GetTaskRangeByType(ESpecialTaskType eType)
{
	return m_multimapTask.equal_range(eType);
}