/********************************************************************
Filename: 	ZipWrapper.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Revision History:
���ʹ��hash����ļ����п��ٶ�λ�����滻ZIP���Դ������Բ��ҷ�ʽ 26-Apr-2006
*/

#ifndef __UTILITY_ZIPWRAPPER_H__
#define __UTILITY_ZIPWRAPPER_H__

#include "MeRTLibs.h"
#include "tstring.h"

extern "C"
{
#include "Zlib/Zlib.h"
#include "Zlib/Minizip/zip.h"
#include "Zlib/Minizip/unzip.h"
}
//#pragma comment(lib, "../ReleaseDll/zlibwapi.lib")

using Common::_tstring;
using std::vector;
using std::fstream;
using stdext::hash_map;
using std::pair;
using std::string;

namespace FileIO
{

    const int WARP_APPEND_STATUS_CREATE = 0;            //�������ļ�
    const int WARP_APPEND_STATUS_CREATEAFTER = 1;       //���������ļ�
    const int WARP_APPEND_STATUS_ADDINZIP = 2;          //�����������ļ�

    const int TMPBUFFSIZE = 1024*100;                  //��ʱ�������ݵ�BUFF
    class CZipWrapper
    {
    public:
        typedef struct tagUnitInfo
        {
            _tstring strFileName;
            unz_file_info info;
        }UNITINFO;

        typedef std::vector<UNITINFO> UnitInfoList;

    public:
        CZipWrapper();
        virtual ~CZipWrapper();

    public:
        CZipWrapper(const TCHAR* szZipFile, int nOpenMode = WARP_APPEND_STATUS_ADDINZIP);

    public:
        bool OpenZipFile(const TCHAR* szFile, int nOpenMode = WARP_APPEND_STATUS_ADDINZIP);
        void CloseZipFile();

        bool AddFileFromLocalFile(const TCHAR* szLocalFile, const TCHAR* szUnitName = NULL);
        bool AddFileFromMemory(const TCHAR* szUnitName, const void* pBuf, size_t len, uLong crc = 0, uLong time = 0);
        bool AddFileFromAnotherZipWrapper(CZipWrapper& zip, const TCHAR* szUnitNameInAnoterZip, const TCHAR* szNewUnitName = NULL);

    public:
        bool IsOpen() const;
        bool IsEmpty() const;
        size_t GetCount() const;

        void SetCompressLevel(int CompressLevel);

        bool GetUnitSize(const TCHAR* szUnitName, size_t& size);
        UnitInfoList GetUnitList();
        bool UnitIsExist(const TCHAR* szUnitName);

        bool GetUnitToMemory(const TCHAR* szUnitName, void* pDst, size_t& dstSize);
        bool SaveUnitToFile(const TCHAR* szUnitName, const TCHAR* szFilePath);

        _tstring GetZipFileName() const;

        void SetPassword(_tstring strPassword);

    private:
        unsigned long GetFileTime(_tstring strFileName, uLong& time);   //��ȡ�ļ�ʱ��
        unsigned long GetFileCrc(_tstring strFileName);                 //��ȡ�ļ�CRCֵ
        bool SetFileChangeTime(_tstring strFileName, uLong time);       //�޸��ļ�����ʱ��
        bool MakeDir(_tstring strFolder);                               //�������Ŀ¼
        _tstring GetFolder(_tstring strFullFilePath);                   //��ȡһ������·�����ļ���
        void MakeIndex();                                               //�����ļ�λ��������

    private:

        friend CZipWrapper;                              //Ϊ����CZipWrapper֮�����ݴ��ݣ�����������Ϊ��Ԫ

        unzFile m_pUnZipFile;                           //zip��ѹ�ļ����
        zipFile m_pZipFile;                             //zipѹ���ļ����
        size_t m_count;                                 //zip�ļ��е��ļ�����

        _tstring m_strZipFile;                          //Zip�ļ���
        char m_sztmpbuff[TMPBUFFSIZE];                  //������ʱ�����ļ���BUFFER��С
        int m_compresslevel;                            //ѹ���ȼ�
        hash_map<string, unz_file_pos> m_index;         //�ļ�λ������
        unz_file_pos m_endpos;                          //zip�ļ���ǰ���λ��
        bool m_bUseIndexPos;                            //�Ƿ�ʹ�ù���������ļ�λ��
        _tstring m_strPassword;

    private:
        CZipWrapper(const CZipWrapper&);
        CZipWrapper& operator = (const CZipWrapper&);
    };

};
#endif // __UTILITY_ZIPWRAPPER_H__
