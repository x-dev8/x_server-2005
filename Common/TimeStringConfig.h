#ifndef _TIMESTRINGCONFIG_H_
#define _TIMESTRINGCONFIG_H_

#include <string>
#include <map>
#include <list>
#include "MeRTLibs.h"

class TimeStringManager
{
public:
	struct TimeData
	{
		TimeData()
		{
			nTime = 0;
			nStringId = 0;
			nStartTime = 0;
		}

		uint32 nTime; //Ê±¼ä
		uint32 nStringId; //timestring id
		uint32 nStartTime;
	};

	TimeStringManager();
	~TimeStringManager();

	void AddTimeData(uint32 time, uint32 id, uint32 starttime);

	std::list<TimeData>& GetTimeData() { return m_TimeData; }
	int GetSize() { return m_TimeData.size(); }

	static TimeStringManager& Instance()
	{
		static TimeStringManager s_xTimeStringManager;
		return s_xTimeStringManager;
	}

private:
	std::list<TimeData> m_TimeData;
};

class TimeStringConfig
{
public:
	TimeStringConfig();
	~TimeStringConfig();

	bool LoadTimeStringConfig( const char* pszConfig );
	const char* GetString(const int nId);

	static TimeStringConfig& Instance()
	{
		static TimeStringConfig s_xTimeString;
		return s_xTimeString;
	}

private:
	typedef std::map<int, std::string>::iterator mapiter;
	std::map<int,std::string> m_mapString;
};

#define theTimeStringConfig TimeStringConfig::Instance()
#define theTimeStringManager TimeStringManager::Instance()

#endif //_TIMESTRINGCONFIG_H_