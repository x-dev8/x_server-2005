
#include "timecooling_configure.h"
#include "FuncPerformanceLog.h"
// #include "Tinyxml/tinyxml.h"
#include "Cfg.h"

CTimeCooling_Configure g_TimeCooling_Config;

#define TIMECOLLING_CONFIGURE_XML_ROOT "TimeCoolingRoot"

CTimeCooling_Configure::CTimeCooling_Configure()
{
	guardfunc;
	time_cooling_configure.clear();
	unguard;
}

CTimeCooling_Configure::~CTimeCooling_Configure()
{
	guardfunc;
	unguard;
}

void CTimeCooling_Configure::load()
{
	guardfunc;
    time_cooling_configure[0] = 500;
    time_cooling_configure[1] = 20000;

	unguard;
}

int	CTimeCooling_Configure::getTimeCooling(TimeCoolingConfigure type)
{
	guardfunc;

	if( type < 0 || type >= TCC_MAX)
		return 0;

	std::map<int, int>::iterator iter = time_cooling_configure.find( type );
	if( iter != time_cooling_configure.end() )
	{
		return iter->second;
	}

	return -1;

	unguard;
}