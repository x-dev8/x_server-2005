#include "NpcAction.h"
#include "tstring.h"

CNpcAction::CNpcAction(void)
{
}

CNpcAction::~CNpcAction(void)
{
	Clear();
}


bool CNpcAction::ParseAction(MeXmlElement *pRoot)
{
	if(!pRoot)
		return false;
	MeXmlElement *pAction = pRoot->FirstChildElement("Action");
	for (;pAction != NULL;pAction = pAction->NextSiblingElement())
	{
		Action act;
		MeXmlElement *pReqs = pAction->FirstChildElement("Requires");
		MeXmlElement *pReq = pReqs->FirstChildElement("Require");
		for(;pReq != NULL;pReq = pReq->NextSiblingElement())
		{
			Require req;
			int nValue = 0;
			pReq->QueryIntAttribute("Type",&nValue);
			req.eType = (ReqType)nValue;

			if ( req.eType == Req_Sex )
			{
				pReq->QueryIntAttribute("Sex",&nValue);
				req.nSex = nValue;
			}
			else if ( req.eType == Req_Dislen || req.eType == Req_Level )
			{
				float fValue = 0;
				pReq->QueryFloatAttribute("Min",&fValue);
				req.fMin = fValue;

				pReq->QueryFloatAttribute("Max",&fValue);
				req.fMax = fValue;

			}
			else if ( req.eType == Req_Task )
			{
				pReq->QueryIntAttribute("TaskID",&nValue);
				req.nTaskID = nValue;
			}


			pReq->QueryIntAttribute("Need",&nValue);
			if(nValue)
				act.vecMustTerm.push_back(req);
			else
				act.vecProbilityTerm.push_back(req);
		}
		MeXmlElement *pEvents = pAction->FirstChildElement("Events");
		MeXmlElement *pEvent  = pEvents->FirstChildElement("Event");
		for (;pEvent != NULL;pEvent = pEvent->NextSiblingElement())
		{
			int nValue = 0;
			pEvent->Attribute("Type",&nValue);
			if((EventType)nValue == Event_Talk)
			{
				pEvent->Attribute("StringId",&nValue);
				act.talk.nStringId = nValue;
				pEvent->Attribute("Probability",&nValue);
				act.talk.nProbability = nValue;

				pEvent->Attribute("DelayTime",&nValue);
				act.talk.nDelayTime = nValue;
			}
			else if((EventType)nValue == Event_Anim)
			{
				Common::_tstring strName;
				strName.fromUTF8(pEvent->Attribute("Name",&nValue));
				act.anim.strType = strName;

				pEvent->Attribute("Probability",&nValue);
				act.anim.nProbability = nValue;

				pEvent->Attribute("DelayTime",&nValue);
				act.anim.nDelayTime = nValue;
			}
			else if ( (EventType)nValue == Event_AutoFace )
			{
				pEvent->Attribute("AutoFace",&nValue);
				if ( nValue == 1 )
				{
					act.autoFace.bIsAutoFace = true;
				}
				else
				{
					act.autoFace.bIsAutoFace = false;
				}
				pEvent->Attribute("Probability",&nValue);
				act.autoFace.nProbability = nValue;

				pEvent->Attribute("DelayTime",&nValue);
				act.autoFace.nDelayTime = nValue;
			}

		}
		m_ActSet.push_back(act);
	}
	return true;
}

Action* CNpcAction::GetOneActionByIndex(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_ActSet.size())
	   return NULL;

	return &m_ActSet[nIndex];
}