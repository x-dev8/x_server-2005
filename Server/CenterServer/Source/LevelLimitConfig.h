#ifndef __CENTERSERVER_LEVELLIMITCONFIG_H__
#define __CENTERSERVER_LEVELLIMITCONFIG_H__

#pragma once
#include <map>
#include "LevelLimitDefine.h"

using namespace std;
class CLevelLimitConfig
{	
public:
	CLevelLimitConfig(void);
	~CLevelLimitConfig(void);

	static CLevelLimitConfig& Instance()
	{
		static CLevelLimitConfig cllc;
		return cllc;
	}

	void ClearData();
	bool LoadLevelLimitConfig();

	SLevelLimitConfig* GetLevelLimitConfig(int lv);
	SLevelLimitConfig* GetFirstLimitConfig();
private:
	typedef map<short,SLevelLimitConfig*> mapLevelLimitConfig;
	mapLevelLimitConfig _mapLevelLimitConfig;
};
#define theLevelLimitConfig CLevelLimitConfig::Instance()

#endif // __CENTERSERVER_LEVELLIMITCONFIG_H__