#ifndef _RANKTITLECONFIG_
#define _RANKTITLECONFIG_

#include "MeRTLibs.h"

class RankTitleConfig
{
public:

	enum EDefine
	{
		ED_AnYuan = 20, //安远将军的Id
	};
	struct SData
	{
		SData()
		{
			nId = -1;
			nCurSalary = 0;
			nNeedHonour = 0;
			nNeedMoney = 0;
			nBuffId = 0;
			nBuffLevel = 0;
			nPicHeight = 0;
			nPicWidth = 0;
		}

		int nId;
		std::string strName;
		std::string strDescription;
		int nCurSalary;
		int nNeedHonour;
		int nNeedMoney;
		int nBuffId;
		int nBuffLevel;
		std::string strPic;
		int nPicHeight;
		int nPicWidth;
	};

	typedef std::vector< SData > RankTitleVector;

public:
	RankTitleConfig();
	virtual ~RankTitleConfig();

	bool LoadRankTitleConfig( const char* pszConfig );

	static RankTitleConfig& Instance()
	{
		static RankTitleConfig s_xRankTitle;
		return s_xRankTitle;
	}

	std::vector< SData >& GetRankTitleVec() { return m_vecRankTitle; }
	int GetShowCount() { return m_nShowCount; }

private:
	RankTitleVector m_vecRankTitle;
	int m_nShowCount;
};

#define theRankTitleConfig RankTitleConfig::Instance()

#endif //_RANKTITLECONFIG_