#include "license.h"
#include "md5.h"
#include "mac.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <cassert>

#ifdef _WIN32
#include <time.h>
#include <Windows.h>
#else
#endif

#pragma warning( push )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4127 )

LicenseMaker& LicenseMaker::Instance( void )
{
	static LicenseMaker instance;
	return instance;
}

LicenseMaker::LicenseMaker()
{

}

const unsigned long nKey = 0x55;
// 异或操作
class ExclusiveOR : public std::unary_function< char, void >
{
public:
	void operator() ( char& inputChar ) const
	{
		inputChar = inputChar ^ nKey;
	}
};

std::string LicenseMaker::generateLicenseContent( LicenseType type, const std::string& strMac )
{
	std::string strContent;
	char szBuffer[ MAX_PATH ] = {};

	SYSTEMTIME time;
	GetLocalTime( &time );    

	if ( LT_YEAR == type )
	{
		memset( szBuffer, 0, MAX_PATH );
		itoa( time.wYear, szBuffer, 10 );
		strContent += szBuffer;
	}
	else if ( LT_MONTH == type )
	{
		memset( szBuffer, 0, MAX_PATH );
		itoa( time.wMonth, szBuffer, 10 );
		strContent += szBuffer;
	}

	std::string strLower = strMac;
	std::transform( strMac.begin(), strMac.end(), strLower.begin(), tolower );
	strContent += strLower;

	strContent += "ABC";

	std::string strMd5Value = MD5(strContent).toString();

	std::for_each( strMd5Value.begin(), strMd5Value.end(), ExclusiveOR());
	return strMd5Value;
}

bool LicenseMaker::saveLicense(const std::string& licenseFileName, const std::string& strLicenseContent )
{
	if ( strLicenseContent.empty())
		return false;

	std::ofstream licenseFile;
	licenseFile.open( licenseFileName.c_str(), std::ios_base::out | std::ios_base::trunc | std::ios_base::binary );
	if ( !licenseFile.is_open() )
	{
		return false;
	}

	licenseFile.write( strLicenseContent.c_str(), (std::streamsize)strLicenseContent.size() );
	licenseFile.flush();
	licenseFile.close();
	return true;
}

LicenseChecker& LicenseChecker::Instance( void )
{ 
	static LicenseChecker instance;
	return instance; 
}

LicenseChecker::LicenseChecker()
{
	setup();
}

bool LicenseChecker::loadLicenseFile( const std::string& strFilename )
{
	licenseFile_.open( strFilename.c_str(), std::ios_base::in | std::ios_base::binary );
	if ( !licenseFile_.is_open())
		return false;

	return true;
}

int LicenseChecker::validateLicenseContent( const char* szContent, unsigned long nLength )
{
	if ( !szContent || 0 == nLength)
		return -1;

	if ( strlen(szContent) > nLength )
		return -1;

	std::string strMac;
	//BOOL bResult = GetMacByIpconfig(strMac);
	BOOL bResult = GetMac(strMac);
	if ( !bResult )
		return -1;

	std::string strGenerate = LicenseMaker::Instance().generateLicenseContent( LicenseMaker::LT_YEAR, strMac );
	if ( 0 == strGenerate.compare(szContent) )
		return 0;

	strGenerate = LicenseMaker::Instance().generateLicenseContent( LicenseMaker::LT_MONTH, strMac );
	if ( 0 == strGenerate.compare(szContent) )
		return 0;

	return -1;
}

#include <set>

void LicenseChecker::setup()
{
	// 校正
	std::string strContent;
	char szBuffer[PERLINE_SIZE] = {0};
	int nRet = -1;

	std::string strMac;
	//BOOL bResult = GetMac(strMac);
	BOOL bResult = GetMacByIpconfig(strMac);
	if ( !bResult)
	{
		exit( 1 );
	}

	// 读入license
	if ( !loadLicenseFile( "license" ) )
	{
		MessageBox( NULL, "Load license file failed.", "Application Manager", MB_OK | MB_ICONERROR );
		MessageBox( NULL, strMac.c_str(), "Check Key:",MB_OK);
		exit( 1 );
	}

	//#ifdef _DEBUG 
	//    MessageBox( NULL, "Check.", "Application Manager", MB_OK | MB_ICONERROR );
	//#endif    

	std::string strGenerateYear  = LicenseMaker::Instance().generateLicenseContent( LicenseMaker::LT_YEAR, strMac );
	std::string strGenerateMonth = LicenseMaker::Instance().generateLicenseContent( LicenseMaker::LT_MONTH, strMac );

	std::set<std::string> setString;
	while(true)
	{
		memset( szBuffer, 0, sizeof(szBuffer));
		licenseFile_.getline( szBuffer, PERLINE_SIZE);
		if (szBuffer[0] == '\0')
			break;
		if ( szBuffer[32] == 13)
			szBuffer[32] = 0;

		setString.insert(szBuffer);
	}
	if ( setString.find(strGenerateYear) != setString.end())
	{
		nRet = 0;
	}
	else if ( setString.find(strGenerateMonth) != setString.end() )
	{
		nRet = 0;
	}

	if ( 0 != nRet)
	{
		MessageBox( NULL, "Check license failed.", "Application Manager", MB_OK);
		MessageBox( NULL, strMac.c_str(), "Check Key:",MB_OK);
		exit( 1 );
	}
}

#pragma warning( pop )
