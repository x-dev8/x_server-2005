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
        Error_Succeed = 0,      // �ɹ�
        Error_InputBufferNULL,  // �����ָ��Ϊ��
        Error_OutputStructNULL, // ���صĽṹָ��Ϊ��
        Error_LoadAttributError,// �������ݴ���,�����ǰ汾��ƥ��
        Error_BuffTooBig,       // ����buffsize������ʱ�����buffsize
        Error_InputNullBuffer,  // ������ַ���Ϊ��
        Error_DeCodeError,      // ����ʧ��,�����buff�Ƿ�
        // ��ѹ��ʧ��
        Error_UnzipNotEnoughMemory,     // ��ѹ��ʱ�ڴ治��
        Error_UnzipNotEnoughBuffer,     // ��ѹ��ʱbuffer�ռ䲻��
        Error_UnzipInputDataIncomplete, // ��ѹ��ʱ��������ݲ���ȷ
        Error_UnzipStreamError,         // ��ѹ��ʱ������
        Error_UnzipUnknowError,         // ��ѹ��ʱδ֪����
    };
public:
    ~GameDataDecrypt(){}

    static GameDataDecrypt& GetInstance();

    /**
    * @brief:������ɫ�Ļ�������
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharBaseInfo���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharBaseInfo(const char* IN buffer,unsigned int IN bufSize,SCharBaseInfo* OUT pCharBaseInfo);

    /**
    * @brief:������ɫ��װ������
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharVisual���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharVirsualData(const char* IN buffer,unsigned int IN bufSize,SCharVisual* OUT pCharVisual);

    /**
    * @brief:������ɫ�ĸ�������
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharOtherData���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharOtherData(const char* IN buffer,unsigned int IN bufSize,SCharOtherData* OUT pCharOtherData);

    /**
    * @brief:������ɫ����չ����
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pExtendData���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharExtenData(const char* IN buffer,unsigned int IN bufSize,SExtendData* OUT pExtendData);

    /**
    * @brief:������ɫ�ĳɾ�����
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharItem���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharAchieveData(const char* IN buffer,unsigned int IN bufSize,SAchieveData* OUT pAchieveData);

   /**
    * @brief:������ɫ�ĵ�������
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharItem���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
    */
    long ParseCharItemData(const char* IN buffer,unsigned int IN bufSize,SCharItem* OUT pCharItem);

    /**
    * @brief:������ɫ����ƥ����
    * @param:buffer����ǰ��bufferָ��
    * @param:bufSize����ǰ��buffer�Ĵ�С
    * @param:pCharItem���ܺ�Ľṹָ��,
    * @return:���ؽ���鿴���󷵻��б�
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
