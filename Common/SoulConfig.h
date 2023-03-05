#ifndef _SOULCONFIG_
#define _SOULCONFIG_

#include "MeRTLibs.h"

class SoulConfig
{
public:
	enum EDefine
	{
		ED_Max_Material = 2,
	};

	struct SMaterial
	{
		SMaterial()
		{
			nId = 0;
			nNum = 0;
		}
		int nId;
		int nNum;
	};

	struct SData
	{
		SData()
		{
			nLevel = 0;
			nMoney = 0;
		}
		int nLevel;
		SMaterial material[ED_Max_Material];
		int nMoney;
	};

	typedef std::vector< SData > SoulDataVec;

public:
	SoulConfig();
	virtual ~SoulConfig();

	bool LoadSoulConfig( const char* pszConfig );

	SData* GetLevelData( int nlevel );

	static SoulConfig& Instance()
	{
		static SoulConfig s_xSoul;
		return s_xSoul;
	}

private:
	SoulDataVec m_vecSoul;
};

#define theSoulConfig SoulConfig::Instance()

#endif //_SOULCONFIG_