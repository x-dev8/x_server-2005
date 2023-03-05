/********************************************************************
	Filename: 	Official.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __COMMON_OFFICIAL_H__
#define __COMMON_OFFICIAL_H__

#pragma once

#include "GlobalDef.h"

class COfficialMgr
{
public:
	COfficialMgr();
	~COfficialMgr();
    enum 
    {
        eMaxLevel = 10
    };

    struct Record
    {
        // ��Ҫ��ѫֵ
        DWORD dwNeedExploit;		
        // ÿ�����ҵĹ���
        char szOfficialTitle[country_max][dr_MaxOfficialTitle];

    };

	Record* GetRecord( int i );
	BOOL	LoadSettingFromSlk( const char* pszFilename );

	BOOL	Load();

protected:
	Record	m_records[dr_MaxOfficialLevel+1];
};

extern COfficialMgr g_officialMgr;

#endif // __COMMON_OFFICIAL_H__
