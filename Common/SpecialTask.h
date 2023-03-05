#pragma once

#include "GlobalDef.h"
#include <map>

#define		MAX_SPECIALTASK_VAR		10
class CSpecialTaskMgr
{
public:
	struct SSpecialTask
	{
		int					nTaskID;			//任务ID
		ESpecialTaskType	eType;				//任务类型
		map<int,int>		mapTaskVarReq;		//任务计数变量
	};

	CSpecialTaskMgr();
	~CSpecialTaskMgr();
	static	CSpecialTaskMgr& Instance()
	{
		static CSpecialTaskMgr instance;
		return instance;
	}

	typedef map<int,SSpecialTask*>						MapSpecialTask;
	typedef MapSpecialTask::iterator					IterSpecialTask;
	typedef multimap<ESpecialTaskType,SSpecialTask*>	MultiMapSpecialTask;
	typedef	MultiMapSpecialTask::iterator				IterMultiSpecialTask;
	typedef pair<IterMultiSpecialTask,IterMultiSpecialTask>		PairIter;
	bool LoadConfig(const char*	szPath);
	SSpecialTask* GetTaskByID(int nTaskID);
	PairIter GetTaskRangeByType(ESpecialTaskType eType);
private:
	MapSpecialTask			m_mapSTask;
	MultiMapSpecialTask		m_multimapTask;
};

#define TheSpecialTaskMgr	CSpecialTaskMgr::Instance()
