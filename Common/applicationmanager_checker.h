#pragma once

#include "MeRTLibs.h"

class ApplicationManagerChecker
{
public:
    static ApplicationManagerChecker& Instance()
    {
        static ApplicationManagerChecker applicationManagerChecker;
        return applicationManagerChecker;
    }

    bool IsApplicationManagerOn( const std::string& strName, HWND& hApplicationManager);
};


inline bool ApplicationManagerChecker::IsApplicationManagerOn(const std::string& strName, HWND& hApplicationManager)
{
#ifndef _DEBUG
    hApplicationManager = ::FindWindow(NULL, strName.c_str());
    if ( NULL != hApplicationManager )
        return true;
    else
    {

        MessageBox( NULL, TEXT("Please startup from protector[application manager]"),"Error", MB_OK | MB_ICONERROR );
        exit( 1 );
    }
#endif
    return false;

}

