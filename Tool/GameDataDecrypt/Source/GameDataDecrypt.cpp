#include "GameDataDecrypt.h"
#include "zlib/zlib.h"

#pragma warning(disable:4018)

unsigned char GameDataDecrypt::Decode6BitMask[BITMASKSIZE] = { 0xfc, 0xf8, 0xf0, 0xe0, 0xc0 };

GameDataDecrypt::GameDataDecrypt()
{
    ClearAllBuffer();
}

GameDataDecrypt& GameDataDecrypt::GetInstance()
{
    static GameDataDecrypt parsedata;
    return parsedata;
}


void GameDataDecrypt::ClearAllBuffer()
{
    ClearTempBuffer();
    ClearTempUnzipBuffer();
}

int GameDataDecrypt::DeCodeToBuffer(const unsigned char *pszSrc, uint8 *pszDest, size_t nDestLen)
{
    int nLen = (int)strlen((const char *)pszSrc);
    if (0 == nLen)
        return -1;

    int nDestPos = 0, nBitPos = 2;
    int nMadeBit = 0;
    unsigned char ch, chCode, tmp = 0;

    for (int i = 0; i < nLen; i++)
    {
        if ((pszSrc[i] - 0x3c) >= 0)
            ch = pszSrc[i] - 0x3c;
        else
        {
            nDestPos = 0;
            break;
        }

        if (nDestPos >= nDestLen) break;

        if ((nMadeBit + 6) >= 8)
        {
            chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
            pszDest[nDestPos++] = chCode;

            nMadeBit = 0;

            if (nBitPos < 6) 
                nBitPos += 2;
            else
            {
                nBitPos = 2;
                continue;
            }
        }

        tmp = ((ch << nBitPos) & Decode6BitMask[nBitPos - 2]);

        nMadeBit += (8 - nBitPos);
    }
    return nDestPos;
}

long GameDataDecrypt::ParseCharBaseInfo(const char* IN buffer,unsigned int IN bufSize,SCharBaseInfo* OUT pCharBaseInfo)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pCharBaseInfo)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), (unsigned char*)bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Char );
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    /*
        uncompress returns Z_OK if success, Z_MEM_ERROR if there was not
        enough memory, Z_BUF_ERROR if there was not enough room in the output
        buffer, or Z_DATA_ERROR if the input data was corrupted or incomplete.
    */

    long zipResult = uncompress( TempUnzipDataBuffer, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadCharData( TempUnzipDataBuffer, unzipBufferSize, pCharBaseInfo);
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharVirsualData(const char* IN buffer,unsigned int IN bufSize,SCharVisual* OUT pCharVisual)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pCharVisual)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), (unsigned char*)bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char );
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress( TempUnzipDataBuffer, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadVisuals( TempUnzipDataBuffer, unzipBufferSize, pCharVisual );
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharOtherData(const char* IN buffer,unsigned int IN bufSize,SCharOtherData* OUT pCharOtherData)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pCharOtherData)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), (unsigned char*)bufferDecodeField, CharChunkWR::CD_UnZipTempBufferSize_Char);
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress( TempUnzipDataBuffer, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize );
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadOtherData( TempUnzipDataBuffer, nDecodeBufferActualSize, pCharOtherData );
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharExtenData(const char* IN buffer,unsigned int IN bufSize,SExtendData* OUT pExtendData)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pExtendData)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), bufferDecodeField, CharChunkWR::CD_DecodeFieldBufferSize_Char);
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress(TempUnzipDataBuffer, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadExtendData( TempUnzipDataBuffer, nDecodeBufferActualSize, pExtendData);
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharAchieveData(const char* IN buffer,unsigned int IN bufSize,SAchieveData* OUT pAchieveData)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pAchieveData)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), bufferDecodeField, CharChunkWR::CD_UnZipTempBufferSize_Char);
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress(TempUnzipDataBuffer, &unzipBufferSize, bufferDecodeField, nDecodeBufferActualSize);
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadAchieveData( TempUnzipDataBuffer, nDecodeBufferActualSize, pAchieveData);
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharItemData(const char* IN buffer,unsigned int IN bufSize,SCharItem* OUT pCharItem)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pCharItem)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    DWORD dwDataSize = UNZIPBUFFERSIZE;
    int nSize = DeCodeToBuffer((const unsigned char*)(buffer), (unsigned char*)bufferDecodeField, sizeof(bufferDecodeField));
    if (nSize <= 0)
    {
        if (nSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress(TempUnzipDataBuffer, &dwDataSize, (unsigned char*)bufferDecodeField, sizeof(bufferDecodeField));
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadItemData( TempUnzipDataBuffer, dwDataSize, pCharItem);
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}

long GameDataDecrypt::ParseCharMountData(const char* IN buffer,unsigned int IN bufSize,SMountItem* OUT pMountItem)
{
    if (NULL == buffer)
        return Error_InputBufferNULL;

    if (NULL == pMountItem)
        return Error_OutputStructNULL;

    ClearAllBuffer();
    uint32 unzipBufferSize = CharChunkWR::CD_UnZipTempBufferSize_Char;
    uint32 nDecodeBufferActualSize = DeCodeToBuffer((const unsigned char*)(buffer), (unsigned char*)bufferDecodeField,  CharChunkWR::CD_DecodeFieldBufferSize_Char );
    if (nDecodeBufferActualSize <= 0)
    {
        if (nDecodeBufferActualSize == -1)
            return Error_InputNullBuffer;

        return Error_DeCodeError;
    }

    long zipResult = uncompress(TempUnzipDataBuffer, &unzipBufferSize, (unsigned char*)bufferDecodeField, nDecodeBufferActualSize);
    if (zipResult != Z_OK)
    {
        switch (zipResult)
        {
        case Z_MEM_ERROR:
            return Error_UnzipNotEnoughMemory;
        case Z_BUF_ERROR:
            return Error_UnzipNotEnoughBuffer;
        case Z_DATA_ERROR:
            return Error_UnzipInputDataIncomplete;
        case Z_STREAM_ERROR:
            return Error_UnzipStreamError;
        default:
            return Error_UnzipUnknowError;
        }
    }

    bool bflag = _charDataWR.LoadMountData( TempUnzipDataBuffer, unzipBufferSize, pMountItem);
    if (!bflag)
        return Error_LoadAttributError;

    return Error_Succeed;
}
