#pragma once

#ifndef __PROJECT_APPLICATIONCONFIG_H__
#define __PROJECT_APPLICATIONCONFIG_H__

#ifndef TIXML_USE_STL  
#define TIXML_USE_STL
#endif

#include <string>
#include <map>
#include <vector>
#include <utility>

#define XML_VERSION		"1.0"
#define XML_ENCODING	"utf-8"
#define XML_STANDALONE	""

#define PROJECT_NAME	"Õ÷Èý¹ú"  

#define VERSION_MAJOR    0     // Application major version number.
#define VERSION_MINOR    1	   // Application minor version number.	
#define VERSION_BUILD    1    // Internal version number.
#define VERSION_REVISION 1780 // SVN revision number
#define VERSION_FIX      ""    // SVN Fix
#define VERSION_SECOND   -106214568

/**
 * @brief 
 */
class ApplicationConfig
{
// Construction.
public:

private:
    /// Constructor.
	ApplicationConfig();

    /// Destructor.
	~ApplicationConfig();

// Overload operator.
private:
    /// Disable copy constructor.
    ApplicationConfig( const ApplicationConfig& );

    /// Disable assignment operator.
    ApplicationConfig& operator =( const ApplicationConfig& );
	
// Method.
public:
    /// Instantiation ApplicationConfig object.
	static ApplicationConfig& Instance()
    {
        static ApplicationConfig config;
        return config;
    }

	const char*         GetProjectName();
	const char*         GetFullVersion();
	const unsigned long GetMajorVersion()    { return versionMajor_;    }
	const unsigned long GetMinorVersion()    { return versionMinor_;    }
	const unsigned long GetBuildVersion()    { return versionBuild_;    }
	const unsigned long GetRevisionVersion() { return versionRevision_; }

    bool IsCompatibleVersion( unsigned long major, unsigned long minor, unsigned long build, unsigned long revision  );

// Attribute.
private:
    std::string   xmlVersion_;
	std::string   xmlEncoding_;
	std::string   xmlStandalone_;
    std::string   projectName_;
    unsigned long versionMajor_;
    unsigned long versionMinor_;
    unsigned long versionBuild_;
    unsigned long versionRevision_;
    std::string   version_;
};

#define theApplicationConfig ApplicationConfig::Instance()

inline ApplicationConfig::ApplicationConfig()
{
	xmlVersion_      = XML_VERSION;
	xmlEncoding_     = XML_ENCODING;
	xmlStandalone_   = XML_STANDALONE;
	projectName_     = PROJECT_NAME;
	versionMajor_    = VERSION_MAJOR;
	versionMinor_    = VERSION_MINOR;
	versionBuild_    = VERSION_BUILD;
	versionRevision_ = VERSION_REVISION;

    char version[ MAX_PATH + 1] = {};
    if( strlen(VERSION_FIX) == 0 )
    { sprintf_s( version, MAX_PATH , "%u.%u.%u.%u", versionMajor_, versionMinor_, versionBuild_, versionRevision_ ); }
    else
    { sprintf_s( version, MAX_PATH , "%u.%u.%u.%u%s", versionMajor_, versionMinor_, versionBuild_, versionRevision_ , VERSION_FIX ); }

    version_ = version;
}

inline ApplicationConfig::~ApplicationConfig()
{

}

inline const char* ApplicationConfig::GetProjectName()
{
    return projectName_.c_str();
}

inline const char* ApplicationConfig::GetFullVersion()
{
    return version_.c_str();
}

inline bool ApplicationConfig::IsCompatibleVersion( unsigned long major, unsigned long minor, unsigned long build, unsigned long revision )
{
    if ( major != ApplicationConfig::Instance().GetMajorVersion() ||
         minor != ApplicationConfig::Instance().GetMinorVersion() ||
         build != ApplicationConfig::Instance().GetBuildVersion())
    {
        return false ;
    }

    return true;
}

#define thApplication ApplicationConfig::Instance()

#endif // __HEROONLINE_APPLICATIONCONFIG_H__
