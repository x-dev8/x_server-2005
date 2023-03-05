#ifndef _EQUIPSCORERATIOCONFIG_
#define _EQUIPSCORERATIOCONFIG_

#include "MeRTLibs.h"
#include "GameDefineChar.h"

class EquipScoreRatioConfig
{
	struct SData
	{
		SData()
		{
			nId = 0;
			fRatio = 0.0f;
		}

		int nId;
		float fRatio;
	};

public:
	EquipScoreRatioConfig()
	{
		m_vecRatios.resize(RT_AddAttrMaxSize - 1);
	}

	float GetAttrRatio(int nId) const
	{
		if (nId >= m_vecRatios.size() || nId < 0)
			return 0.0f;

		return m_vecRatios[nId].fRatio;
	}

	bool AddAttrRatio(int nId, float fRatio)
	{
		if (nId < 0 || nId >= m_vecRatios.size())
			return false;

		m_vecRatios[nId].nId = nId + 1;
		m_vecRatios[nId].fRatio = fRatio;

		return true;
	}

	static EquipScoreRatioConfig& Instance()
	{
		static EquipScoreRatioConfig s_xEquipScoreRatio;
		return s_xEquipScoreRatio;
	}

	bool LoadEquipScoreRatioConfig( const char* pszConfig );

private:
	typedef std::vector< SData > RatioVector;
	RatioVector m_vecRatios;
};

#define theEquipScoreRatioConfig EquipScoreRatioConfig::Instance()

#endif //_EQUIPSCORERATIOCONFIG_