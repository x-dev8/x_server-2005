#include "StringLanguageTranslator.h"
#include "RapidXml/MeRapidXml.h"

#pragma warning ( push )
#pragma warning ( disable : 4267 )

long StringLanguageTranslator::LoadStringLanguageInfo( const char* szFilename )
{
    MeXmlDocument doc;
    if( !doc.LoadFile( szFilename ) )
        return -1;

    MeXmlElement* lpRoot = doc.FirstChildElement("Project");
    if (!lpRoot)
        return -1;

    _strProjectName = lpRoot->Attribute("Name");

#if 0
    std::string strCorrecVersion = ApplicationConfig::Instance().GetFullVersion();
    size_t nPos = strCorrecVersion.find_last_of(".");
    if ( nPos == std::string::npos )
        return -3;
    strCorrecVersion = strCorrecVersion.substr(0,nPos);

    _strVersion = lpRoot->Attribute("Version");
    size_t nvPos = _strVersion.find_last_of(".");
    if ( nvPos == std::string::npos )
        return -3;
    std::string strVersionSub = strCorrecVersion.substr(0,nvPos);

    if ( strCorrecVersion.compare(strVersionSub) != 0)
        return -3;
#endif

    MeXmlElement* lpElement = lpRoot->FirstChildElement("StringTable");
    if ( !lpElement)
        return -1;
    _strLanguage = lpElement->Attribute("Language");

    lpElement = lpElement->FirstChildElement("String");
    while(lpElement)
    {
        std::string stdId = lpElement->Attribute("Id");     
        std::string strValue = _Utf8ASMultibyte(lpElement->Attribute("Value"));
        
        std::string strIdTag;
        strIdTag += STRING_TAG_BEGIN;
        strIdTag += stdId;
        strIdTag += STRING_TAG_END;
        _stringLanguageTables.insert( ItrStringLanguageContainer::value_type(strIdTag, strValue));
        lpElement = lpElement->NextSiblingElement("String");
    }
    return 0;
}

std::string StringLanguageTranslator::Translate( const char* szContent, unsigned long nContentCount )
{
    size_t nCount = nContentCount;
    if ( 0 == nCount)
        nCount = strlen(szContent);

    std::string strContent;
    strContent.resize( nCount + 1);
    strContent = szContent;
    //strcpy_s( const_cast<char*>(strContent.c_str()), nCount + 1, szContent);

    std::string strResult;

    size_t nBeginPos = strContent.find( STRING_TAG_BEGIN );    
    while ( nBeginPos != std::string::npos)
    {
        size_t nEndPos = strContent.find( STRING_TAG_END );
        if ( nEndPos==std::string::npos )
        { // error
            continue;
        }

        std::string strTag = strContent.substr( nBeginPos, nEndPos-nBeginPos + STRING_TAG_END_CHARCOUNT);
        strResult += strContent.substr( 0, nBeginPos );
        strResult += _GetIdMappingValue( strTag );

        strContent = strContent.substr( nEndPos + STRING_TAG_END_CHARCOUNT);
        nBeginPos = strContent.find( STRING_TAG_BEGIN );  
    }
    strResult += strContent;

    return strResult;
}

std::string StringLanguageTranslator::_GetIdMappingValue( const std::string& strIdTag  )
{
    ItrStringLanguageContainer it = _stringLanguageTables.find( strIdTag );
    if ( it != _stringLanguageTables.end())
    {
        return it->second;
    }
    return strIdTag;
}

std::string StringLanguageTranslator::_MultibyteASUtf8( const std::string& strContent )
{
    std::string strResult;

    std::wstring wtrResult;
    size_t nwChars = MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), strContent.size(), NULL, 0);
    wtrResult.resize(nwChars);
    MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), strContent.size(), const_cast<wchar_t*>(wtrResult.c_str()), nwChars);

    size_t nChars = WideCharToMultiByte(CP_UTF8, 0, wtrResult.c_str(), wtrResult.size(), NULL, 0, NULL, NULL); 
    strResult.resize(nChars) ;
    WideCharToMultiByte(CP_UTF8, 0,wtrResult.c_str(), wtrResult.size(), const_cast<char*>(strResult.c_str()), nChars, NULL, NULL);

    return strResult;
}

std::string StringLanguageTranslator::_Utf8ASMultibyte( const std::string& strContent )
{
    std::string strResult;

    std::wstring wtrResult;
    size_t nwChars = MultiByteToWideChar(CP_UTF8, 0, strContent.c_str(), strContent.size(), NULL, 0);
    wtrResult.resize(nwChars);
    MultiByteToWideChar(CP_UTF8, 0, strContent.c_str(), strContent.size(), const_cast<wchar_t*>(wtrResult.c_str()), nwChars);

    size_t nChars = WideCharToMultiByte(CP_ACP, 0, wtrResult.c_str(), wtrResult.size(), NULL, 0, NULL, NULL); 
    strResult.resize(nChars) ;
    WideCharToMultiByte(CP_ACP, 0,wtrResult.c_str(), wtrResult.size(), const_cast<char*>(strResult.c_str()), nChars, NULL, NULL);

    return strResult;
}

#pragma warning ( pop )
