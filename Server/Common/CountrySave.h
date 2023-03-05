#ifndef __GAMECOUNTRYSAVE_H__
#define __GAMECOUNTRYSAVE_H__

/************************************************************************
            国家结构保存
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/

#include "DataChunkWriter.h"
#include "Country.h"

class CountrySave
{
public:
    static void SaveGameCountry( CDataChunkWriter* pWriter, CountryData& xData );
    static void ReadGameCountry( BYTE* byBuff,DWORD dwsize, CountryData& xData );

    static bool WriteGameCountry( CountryData& xData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );

protected:
    static void SaveOfficialInfo( CDataChunkWriter* pWriter, OfficialInfo* pInfo );
    static void ReadOfficialInfo( BYTE* byBuff,DWORD dwSize, OfficialInfo* pInfo );

    static void SaveOperateTime( CDataChunkWriter* pWriter, OperateTime& xInfo );
    static void ReadOperateTime( BYTE* byBuff,DWORD dwSize, OperateTime& xInfo );
};


#endif