#pragma once

#include "MySQLWorkSpace.h"

class CWorkSpaceTaskModule
{
public:
	CWorkSpaceTaskModule(void);
	~CWorkSpaceTaskModule(void);

	static CWorkSpaceTaskModule& Instance()
	{
		static CWorkSpaceTaskModule cstm;
		return cstm;
	}

	bool ProcessWorkSpceTask(SWorkSpaceTask* pTask);

	void OnTaskAskForPresent(SWorkSpaceTask* pTask);
	short OnCheckSN(SWorkSpaceTask* pTask);
	SMailTaskInfo* TryProcessAskPresent(SWorkSpaceTask* pTask);
	void DoneAskPresent(SWorkSpaceTask* pTask);

	void OnTaskAskForActivity(SWorkSpaceTask* pTask);
	void OnTaskAskForEpistarPoint(SWorkSpaceTask* pTask);

	void DoneAskActivity(SWorkSpaceTask* pTask);

	void DoneEpistarPoint(SWorkSpaceTask* pTask);

private:
};

#define theWorkSpaceTaskModule CWorkSpaceTaskModule::Instance()