/********************************************************************
	Filename: 	MapStrToID.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_MAPSTRTOID_H__
#define __UTILITY_MAPSTRTOID_H__

#pragma once

#include "MeRTLibs.h"

#pragma warning ( push )
#pragma warning ( disable : 4312)

class CMapStrToIDMgr
{
public:
    enum
    {
        eMaxName = 256
    };
    struct Record
    {
        char*	pszName;
        void*	pDst;
        Record():	pszName(NULL),
            pDst(NULL){}
    } ;
    struct RecordSet
    {
        std::vector<Record> vectorRecord;
        ~RecordSet();
        int FindName( const char* pszName );
    };
public:
    CMapStrToIDMgr();
    ~CMapStrToIDMgr();
    void	Destroy();
    int		GetSize();

    DWORD	Register( const char* pszName, void* pElement );
    DWORD   Register( const char* pszName, int i ){ return Register( pszName, (void*)i); }
    DWORD	GenID( const char* pszName );
    BOOL	UnRegister( const char* pszName );

    void	SupportSameNameElement( BOOL bSupport ){ m_bSupportSameNameElement = bSupport; }
    BOOL	IsSupportSameNameElement(){ return m_bSupportSameNameElement; }


    RecordSet* GetRecordSetByName( const char* pszName );
    RecordSet* GetRecordSetByID( DWORD dwID );

    void*	GetDstByName( const char* pszName );
    void*	GetDstByID( DWORD dwID );
    void*	operator []( const char* pszName )
    {
        return GetDstByName( pszName );
    };

protected:
    std::map< DWORD, RecordSet* > m_mapRecordSet;
    BOOL m_bSupportSameNameElement;
};

#pragma warning ( pop )

#endif // __UTILITY_MAPSTRTOID_H__
