/********************************************************************
    Filename:    CharChunkWR.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __DATABASE_CHARTEMPCHUNK_H__
#define __DATABASE_CHARTEMPCHUNK_H__

#pragma once

#include "GlobalDef.h"

union ReadCharData
{
    BYTE*   byte;
    bool*   boolean;
    int*    i;
    DWORD*  dw;
    char*   c;
    void*   p;
    float*  f;
    short*  s;

    ReadCharData(void* in) :p(in)
    {}
};

class CharChunkWR
{
public:
    enum EConstDefine
    {
        // ChunkBuffer大小
        CD_CharBaseInfoBufferSize = 1024 * 100,
        CD_ItemInfoBufferSize     = 1024 * 40,
        CD_VisualInfoBufferSize   = 1024 * 40,
        CD_OtherInfoBufferSize    = 1024 * 400,
        CD_ExtendInfoBufferSize   = 1024 * 400,
        CD_MountInfoBufferSize    = 1024 * 40,   
        CD_AchieveDataBufferSize  = 1024 * 100,

        // Zip需要的Buffer大小
        CD_ZipTempBufferSize      = 1024 * 40,

        // Encode需要的Buffer大小
        CD_EncodeFieldBufferSize  = 1024 * 10,
        CD_EncodeFieldBufferSize_Guild = 1024 * 6,

        // UnZip需要的Buffer大小
        CD_UnZipTempBufferSize_Char  = 1024 * 300,
        CD_UnZipTempBufferSize_Item  = 1024 * 40,
        CD_UnZipTempBufferSize_Guild = 1024 * 20,

        // Decode需要的Buffer大小
        CD_DecodeFieldBufferSize_Char  = 1024 * 300,
        CD_DecodeFieldBufferSize_Item  = 1024 * 40,
        CD_DecodeFieldBufferSize_Guild = 1024 * 10,
    };

public:
    bool WriteCharData  ( SCharBaseInfo* pInfo,       uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );    
    bool WriteItemData  ( SCharItem* pItem,           uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteVisualData( SCharVisual* pInfo,         uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteOtherData ( SCharOtherData* pOtherData, uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteExtendData( SExtendData* pExtendData,   uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteAchieveData( SAchieveData* pAchieveData,uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
    bool WriteMountData ( SMountItem* pMount,         uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );

    bool LoadCharData    ( uint8* buffer,    uint32 bufferSize, SCharBaseInfo* pInfo );
    void LoadCharApto    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );
    void LoadCharLive    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );    
    bool LoadOtherData   ( uint8* buffer,    uint32 bufferSize, SCharOtherData* pOtherData );
    bool LoadExtendData  ( uint8* buffer,    uint32 bufferSize, SExtendData* pExtendData );
    bool LoadAchieveData ( uint8* buffer,    uint32 bufferSize, SAchieveData* pAchieveData );
    bool LoadVisuals     ( uint8* buffer,    uint32 bufferSize, SCharVisual* pInfo );

    bool LoadItemData    ( uint8* bybuff, DWORD dwsize, SCharItem*  pItem );
    bool LoadMountData   ( uint8* bybuff, DWORD dwsize, SMountItem* pItem );
};

#endif // __DATABASE_CHARCHUNKMANAGER_H__
