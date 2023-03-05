/********************************************************************
Filename: 	ZipWrapper.h
MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Revision History:
添加使用hash表对文件进行快速定位，以替换ZIP库自带的线性查找方式 26-Apr-2006
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

    const int WARP_APPEND_STATUS_CREATE = 0;            //创建新文件
    const int WARP_APPEND_STATUS_CREATEAFTER = 1;       //覆盖现有文件
    const int WARP_APPEND_STATUS_ADDINZIP = 2;          //附加至现有文件

    const int TMPBUFFSIZE = 1024*100;                  //临时操作数据的BUFF
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
        unsigned long GetFileTime(_tstring strFileName, uLong& time);   //获取文件时间
        unsigned long GetFileCrc(_tstring strFileName);                 //获取文件CRC值
        bool SetFileChangeTime(_tstring strFileName, uLong time);       //修改文件日期时间
        bool MakeDir(_tstring strFolder);                               //创建深层目录
        _tstring GetFolder(_tstring strFullFilePath);                   //获取一个完整路径的文件夹
        void MakeIndex();                                               //创建文件位置索引表

    private:

        friend CZipWrapper;                              //为方便CZipWrapper之间数据传递，设置自身类为友元

        unzFile m_pUnZipFile;                           //zip解压文件句柄
        zipFile m_pZipFile;                             //zip压缩文件句柄
        size_t m_count;                                 //zip文件中的文件个数

        _tstring m_strZipFile;                          //Zip文件名
        char m_sztmpbuff[TMPBUFFSIZE];                  //用于临时操作文件的BUFFER大小
        int m_compresslevel;                            //压缩等级
        hash_map<string, unz_file_pos> m_index;         //文件位置索引
        unz_file_pos m_endpos;                          //zip文件当前最后位置
        bool m_bUseIndexPos;                            //是否使用哈尔表查找文件位置
        _tstring m_strPassword;

    private:
        CZipWrapper(const CZipWrapper&);
        CZipWrapper& operator = (const CZipWrapper&);
    };

};
#endif // __UTILITY_ZIPWRAPPER_H__
