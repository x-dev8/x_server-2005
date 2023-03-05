/********************************************************************
	Filename: 	DataChunkMgr.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_DATACHUNKMGR_H__
#define __COMMON_DATACHUNKMGR_H__

#pragma once

#include "MeRTLibs.h"

union UDataChunkPointer
{
    BYTE*			byte;
    bool*			boolean;
    int*			i;
    DWORD*			dw;
    char*			c;
    void*			p;
    float*			f;
    UDataChunkPointer(void* in) :p(in)
    {
    }
};

class CAppDataChunkClassID
{
public:
    CAppDataChunkClassID();
    CAppDataChunkClassID( DWORD dwPartA, DWORD dwPartB );;
    CAppDataChunkClassID( const CAppDataChunkClassID& cid);
    CAppDataChunkClassID& operator=(const CAppDataChunkClassID& cid);
    int operator==(const CAppDataChunkClassID& cid) const;
    int operator!=(const CAppDataChunkClassID& cid) const;
    DWORD GetPartA(){ return m_dwPartA; }
    DWORD GetPartB(){ return m_dwPartB; }
protected:
    DWORD m_dwPartA;
    DWORD m_dwPartB;
};
class CAppDataChunk
{
public:
    CAppDataChunk();
    CAppDataChunk(	CAppDataChunkClassID ClassID, 
        CAppDataChunkClassID SuperClassID,
        DWORD dwSubID,
        DWORD dwLength,
        void* pvData );
    ~CAppDataChunk();


public:
    CAppDataChunkClassID m_ClassID;
    CAppDataChunkClassID m_SuperClassID;
    DWORD m_dwSubID;
    DWORD m_dwLength;
    BYTE* m_pbyData;
};
class CDataChunkMgr
{
public:
    CDataChunkMgr();
    ~CDataChunkMgr();

    BOOL AddAppDataChunk( 
        CAppDataChunkClassID ClassID, 
        CAppDataChunkClassID SuperClassID, 
        DWORD dwSubID, 
        DWORD dwLength, 
        void* pvData );
    CAppDataChunk* GetAppDataChunk( 
        CAppDataChunkClassID ClassID, 
        CAppDataChunkClassID SuperClassID, 
        DWORD dwSubID );
    BOOL RemoveAppDataChunk( 
        CAppDataChunkClassID ClassID, 
        CAppDataChunkClassID SuperClassID, 
        DWORD dwSubID );
    void Clear();
    BOOL SaveToFile( const char* pszFilename );
    BOOL LoadFromFile( const char* pszFilename );

    BOOL LoadFromMemory(unsigned char* pData, size_t nSize);
    BOOL SaveToMemory(unsigned char* pData, size_t& nSize);

protected:
    std::vector<CAppDataChunk*> m_chunks;
};
extern CDataChunkMgr* GetDataChunkMgr();

#endif // __COMMON_DATACHUNKMGR_H__
