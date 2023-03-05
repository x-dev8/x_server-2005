#ifndef __LICENSE_H__
#define __LICENSE_H__

#include <string>
#include <fstream>

#define MAX_PATH 260

enum LICENSE_CONST { LC_MAX_NOISE_CHAR = 5, };

class LicenseMaker
{   
public:
	enum LicenseType
	{
		LT_YEAR,  // Äêlicense
		LT_MONTH, // ÔÂlicense
	};

	static LicenseMaker& Instance( void );

	std::string generateLicenseContent( LicenseType type,const std::string& strMac );

	bool saveLicense(const std::string& licenseFileName, const std::string& strLicenseContent );

protected:
	LicenseMaker();

	LicenseMaker(const LicenseMaker&){};

	const LicenseMaker& operator= ( const LicenseMaker& ) {}
};

class LicenseChecker
{
public:
	enum { BUFFER_SIZE = 1024 * 4, PERLINE_SIZE = 256 };
	static LicenseChecker& Instance( void );

	bool loadLicenseFile( const std::string& strFileName );

	int validateLicenseContent( const char* szContent, unsigned long nLength );

	void setup();

protected:
	LicenseChecker();

	LicenseChecker(const LicenseChecker&){};

	const LicenseChecker& operator= (const LicenseChecker&) {}

private:
	std::ifstream licenseFile_;
};

#endif // __LICENSE_H__
