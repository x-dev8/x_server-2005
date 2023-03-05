/********************************************************************
    Filename:    StringLanguageTranslator.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_STRINGLANGUAGETRANSLATOR_H__
#define __UTILITY_STRINGLANGUAGETRANSLATOR_H__

#pragma once

#include "MeRTLibs.h"
#include "StringLanguage.h"

#define UseStringLanguage 1

class StringLanguageTranslator
{
public:
    static StringLanguageTranslator& Instance() 
    { static StringLanguageTranslator intance; return intance; }

    long LoadStringLanguageInfo( const char* szFilename );

    std::string Translate( const char* szContent, unsigned long nContentCount = 0 );

protected:
    StringLanguageTranslator(){}
    StringLanguageTranslator( const StringLanguageTranslator& ) {}
    StringLanguageTranslator& operator= (const StringLanguageTranslator& ) {}

private:
    typedef std::map<std::string, std::string> StringLanguageContainer;
    typedef StringLanguageContainer::iterator ItrStringLanguageContainer;
    StringLanguageContainer _stringLanguageTables;

    std::string _strProjectName;
    std::string _strVersion;
    std::string _strLanguage;

protected:
    std::string _GetIdMappingValue( const std::string& strIdTag );
    std::string _MultibyteASUtf8( const std::string& strContent );
    std::string _Utf8ASMultibyte( const std::string& strContent );
};

#if (UseStringLanguage==1)    
    #define ST(x) STN(x,0)
    #define STN(x,n) StringLanguageTranslator::Instance().Translate(x,n).c_str()
#else
    #define ST(x) x
    #define STN(x,n) x
#endif

#endif // __UTILITY_STRINGLANGUAGETRANSLATOR_H__
