#ifndef __COMMON_GAMEDATADECRYPT_H__
#define __COMMON_GAMEDATADECRYPT_H__

#pragma once

#include "GlobalDef.h"
#include "CharChunkWR.h"

#define TEMPBUFFSIZE    40000
#define BITMASKSIZE     5
#define UNZIPBUFFERSIZE 1024*256

class GameDataDecrypt
{
public:
    enum eErrorResult
    {
        Error_Succeed = 0,      // 成功
        Error_InputBufferNULL,  // 传入的指针为空
        Error_OutputStructNULL, // 返回的结构指针为空
        Error_LoadAttributError,// 解析数据错误,可能是版本不匹配
        Error_BuffTooBig,       // 传的buffsize大于零时缓冲的buffsize
        Error_InputNullBuffer,  // 传入的字符串为空
        Error_DeCodeError,      // 解码失败,传入的buff非法
        // 解压缩失败
        Error_UnzipNotEnoughMemory,     // 解压缩时内存不足
        Error_UnzipNotEnoughBuffer,     // 解压缩时buffer空间不足
        Error_UnzipInputDataIncomplete, // 解压缩时传入的数据不正确
        Error_UnzipStreamError,         // 解压缩时流错误
        Error_UnzipUnknowError,         // 解压缩时未知错误
    };
public:
    ~GameDataDecrypt(){}

    static GameDataDecrypt& GetInstance();

    /**
    * @brief:解析角色的基本数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharBaseInfo解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharBaseInfo(const char* IN buffer,unsigned int IN bufSize,SCharBaseInfo* OUT pCharBaseInfo);

    /**
    * @brief:解析角色的装备数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharVisual解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharVirsualData(const char* IN buffer,unsigned int IN bufSize,SCharVisual* OUT pCharVisual);

    /**
    * @brief:解析角色的辅助数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharOtherData解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharOtherData(const char* IN buffer,unsigned int IN bufSize,SCharOtherData* OUT pCharOtherData);

    /**
    * @brief:解析角色的扩展数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pExtendData解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharExtenData(const char* IN buffer,unsigned int IN bufSize,SExtendData* OUT pExtendData);

    /**
    * @brief:解析角色的成就数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharItem解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharAchieveData(const char* IN buffer,unsigned int IN bufSize,SAchieveData* OUT pAchieveData);

   /**
    * @brief:解析角色的道具数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharItem解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharItemData(const char* IN buffer,unsigned int IN bufSize,SCharItem* OUT pCharItem);

    /**
    * @brief:解析角色的马匹数据
    * @param:buffer加密前的buffer指针
    * @param:bufSize加密前的buffer的大小
    * @param:pCharItem解密后的结构指针,
    * @return:返回结果查看错误返回列表
    */
    long ParseCharMountData(const char* IN buffer,unsigned int IN bufSize,SMountItem* OUT pMountItem);

private:
    static unsigned char Decode6BitMask[BITMASKSIZE];

    unsigned char bufferDecodeField  [ CharChunkWR::CD_DecodeFieldBufferSize_Char ];
    unsigned char TempUnzipDataBuffer[ CharChunkWR::CD_UnZipTempBufferSize_Char   ];

    CharChunkWR _charDataWR;
    
private:
    GameDataDecrypt();
    GameDataDecrypt(const GameDataDecrypt&);
    GameDataDecrypt& operator = (const GameDataDecrypt&);

    void ClearTempBuffer(){ ZeroMemory(bufferDecodeField,sizeof(bufferDecodeField));}
    void ClearTempUnzipBuffer(){ ZeroMemory(bufferDecodeField,sizeof(bufferDecodeField)); }
    void ClearAllBuffer();
    int  DeCodeToBuffer(const unsigned char *pszSrc, unsigned char *pszDest, size_t nDestLen);
};

#endif  //__COMMON_GAMEDATADECRYPT_H__
