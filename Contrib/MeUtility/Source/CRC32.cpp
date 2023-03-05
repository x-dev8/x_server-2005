

#include "CRC32.h"
#include <fstream>
#include "tstring.h"

namespace Crypto
{

#ifndef NULL
#define NULL 0
#endif

//ʹ�ú�ʹ�������չ����ʹ֮����Ч������ת����ٶ�
/* ========================================================================= */
#define DO1 crc = crc_table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8)
#define DO8 DO1; DO1; DO1; DO1; DO1; DO1; DO1; DO1
/* ========================================================================= */

CCRC32::CCRC32()
{
}

CCRC32::~CCRC32()
{
}

unsigned long CCRC32::GetMemCRC32(const unsigned char* pBuffer, unsigned int nLen)
{
    unsigned long crc = 0;
    return crc32(crc, pBuffer, nLen);
}


unsigned long CCRC32::GetFileCRC32(const char* szFileName)
{
    if (szFileName == NULL)
    {
        return 0UL;
    }

    //********************************************
    //Ϊ��ӦVC2005��fstream������·������BUG����szFileNameת��Unicode�ٴ���
    //std::wstring strFileName = _tUNICODECHAR(szFileName);
    std::fstream file(_tUNICODECHAR(szFileName), std::ios::in | std::ios::binary);
    //********************************************

    if (!file.is_open())
    {
        return 0UL;
    }

    
    file.seekg(0, std::ios::end);
    size_t filesize = file.tellg();
    file.seekg(0, std::ios::beg);

    unsigned long crc = 0;

    //�ֶζ�ȡ����CRCУ��,�Է��ļ������޷�һ���������ڴ�
    while (filesize >0)
    {
        std::streamsize readlength;
        if (filesize > TMP_BUFFERSIZE)
        {
            readlength = TMP_BUFFERSIZE;
        }
        else
        {
            readlength = static_cast<std::streamsize>(filesize);
        }
        file.read(szTmpBuffer, readlength);
        crc = crc32(crc, (unsigned char*)szTmpBuffer, readlength);
        filesize -= readlength;
    }
    file.close();

    return crc;
}

unsigned long CCRC32::crc32(unsigned long crc, const unsigned char* buf, unsigned int len)
{
    if (buf == NULL)
    {
        return 0UL;
    }

    crc = crc ^ 0xffffffffUL;
    while (len >= 8) {
        DO8;
        len -= 8;
    }
    if (len) do {
        DO1;
    } while (--len);
    return crc ^ 0xffffffffUL;
}

};