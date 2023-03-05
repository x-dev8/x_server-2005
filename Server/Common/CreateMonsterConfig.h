#ifndef _CREATEMONSTERCONFIG_
#define _CREATEMONSTERCONFIG_

#include "MeRTLibs.h"
#include "RapidXml/MeRapidXml.h"

class CreateMonsterConfig
{
public:
	struct SData
	{
		SData()
		{
			nYear = -1;
			nMonth = -1;
			nDay = -1;
			nHour = -1;
			nMinute = -1;
			nWeek = -1;

			nMonsterId = -1;
			nMapId = -1;
			nX = -1;
			nY = -1;
			nCount = 0;

			bIsOnly = true;
		}

		int nYear;
		int nMonth;
		int nDay;
		int nHour;
		int nMinute;
		int nWeek;

		int nMonsterId;
		int nMapId;
		int nX;
		int nY;
		int nCount;

		bool bIsOnly;
		std::string strSay;
	};

	typedef std::vector< SData > VecMonster;
	typedef VecMonster::iterator vecIter;

public:
	CreateMonsterConfig();
	virtual ~CreateMonsterConfig();

	bool LoadCreateMonsterConfig( const char* pszConfig );

	VecMonster& GetMonsterVec() { return m_vecMonster; }

	static CreateMonsterConfig& Instance()
	{
		static CreateMonsterConfig s_xCreateMonste;
		return s_xCreateMonste;
	}

private:
	VecMonster m_vecMonster;
};

#define theCreateMonsterConfig CreateMonsterConfig::Instance()

#endif //_CREATEMONSTERCONFIG_