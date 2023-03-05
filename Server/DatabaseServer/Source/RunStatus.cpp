#include "RunStatus.h"

DbRunStatus& GetRunStatus()
{
    static DbRunStatus instance;
    return instance;
}

DbRunStatus::DbRunStatus()
{
	_runstatus = RunStatus_PrepareData;
}

DbRunStatus::~DbRunStatus()
{
}

