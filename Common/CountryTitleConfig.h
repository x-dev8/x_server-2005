#ifndef _COUNTRYTITLECONFIG_
#define _COUNTRYTITLECONFIG_

#include "MeRTLibs.h"
#define CountryTitle_QueenMale 12 //Ç×Íõ

class CountryTitleConfig
{
public:
	struct SData
	{
		SData()
		{
			nTitleId = 0;
			nPicHeight = 0;
			nPicWidth = 0;
		}
		int nTitleId;
		std::string strPic;
		int nPicHeight;
		int nPicWidth;
	};

	typedef std::vector< SData > CountryTitleVector;

	typedef std::map< unsigned short, CountryTitleVector > CountryTitleMap;
	typedef CountryTitleMap::iterator CountryTitleMapIter;

	CountryTitleConfig();
	virtual ~CountryTitleConfig();

	bool LoadCountryTitleConfig( const char* pszConfig );

	void AddMapData( int nCountry, CountryTitleVector& data );
	CountryTitleVector* GetCountryTitleVec( int nCountryId );

	static CountryTitleConfig& Instance()
	{
		static CountryTitleConfig s_xCountryTitle;
		return s_xCountryTitle;
	}

private:
	CountryTitleMap m_mapCountryTitle;
};

#define theCountryTitleConfig CountryTitleConfig::Instance()

#endif //_COUNTRYTITLECONFIG_