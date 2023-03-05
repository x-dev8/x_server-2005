#include "SearchFile.h"

std::vector<std::string> SearchFileToVector( const char *szDefaultPath, const char *szFormat )
{
    std::vector<std::string> vectorFile;
    
    std::string strSearchString;
    strSearchString += szDefaultPath;
    strSearchString += "\\";
    strSearchString += szFormat;

    WIN32_FIND_DATA wfd;
    HANDLE handle = FindFirstFile( strSearchString.c_str(), &wfd );

    if( handle != INVALID_HANDLE_VALUE )
    {
        do 
        {
            std::string strFileName;
            strFileName = wfd.cFileName;
            vectorFile.push_back( strFileName );
        } while( FindNextFile( handle, &wfd ) );
    }
        
    FindClose( handle );

    return vectorFile;
}