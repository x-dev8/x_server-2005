#include "MailModule.h"
#include "PlatformWorkSpace.h"

CMailModule::CMailModule(void)
{
}

CMailModule::~CMailModule(void)
{
}

bool CMailModule::ProcessMailTask(SMailTaskInfo* pInfo)
{
	if (!pInfo)
	{
		return false;
	}

	//if (pInfo->itemcount > 0 && pInfo->itemid > 0)
	{
		MsgPFSendMail pfsm;
		pfsm.characterid = pInfo->characterid;
		strncpy_s(pfsm.charactername,sizeof(pfsm.charactername),pInfo->charactername,sizeof(pfsm.charactername) -1);
		strncpy_s(pfsm.content,sizeof(pfsm.content),pInfo->content,sizeof(pfsm.content) -1);
		strncpy_s(pfsm.title,sizeof(pfsm.title),pInfo->title,sizeof(pfsm.title) -1);
		pfsm.money = pInfo->money;
		pfsm.itemid = pInfo->itemid;
		pfsm.itemcount = pInfo->itemcount;

		if(pInfo->serverid == eTaskResult_AllServer)
		{
			thePlatFormWorkSpace.SendMsgToAllServer(&pfsm);
		}
		else
			return thePlatFormWorkSpace.SendMsgToSingleServer(&pfsm,pInfo->serverid);
	}
	return true;
}