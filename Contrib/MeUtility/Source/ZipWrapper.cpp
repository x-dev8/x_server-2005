#include "ZipWrapper.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

namespace FileIO
{

CZipWrapper::CZipWrapper() : m_pUnZipFile(0), m_pZipFile(0), m_count(0), m_compresslevel(Z_DEFAULT_COMPRESSION), m_bUseIndexPos(false)
{
}

CZipWrapper::~CZipWrapper()
{
    CloseZipFile();
}

CZipWrapper::CZipWrapper(const TCHAR* szZipFile, int nOpenMode) : m_pUnZipFile(0), m_pZipFile(0), m_count(0), m_compresslevel(Z_DEFAULT_COMPRESSION), m_bUseIndexPos(false)
{
    OpenZipFile(szZipFile, nOpenMode);
}

bool CZipWrapper::OpenZipFile(const TCHAR* szFile, int nOpenMode)
{
    if (szFile == NULL)
    {
        return false;
    }
    _tstring strFileName = szFile;
    strFileName.Replace(_T("/"), _T("\\"));

    //如果已经打开文件，则关闭
    CloseZipFile();

    //如果是创建文件，则自动创建深层目录
    if (nOpenMode == WARP_APPEND_STATUS_CREATE)
    {
        MakeDir(GetFolder(strFileName));
    }

    m_pUnZipFile = unzOpen(_tANSICHAR(strFileName));
    m_pZipFile = zipOpen(_tANSICHAR(strFileName), nOpenMode);
    
    //只判断zip句柄是否为空
    if (m_pZipFile == NULL)
    {
        return false;
    }

    //获取文件的总数
    if (m_pUnZipFile != NULL)
    {
        unz_global_info gi;
        unzGetGlobalInfo(m_pUnZipFile, &gi);
        m_count = gi.number_entry;
    }
    
    MakeIndex();
    m_strZipFile = szFile;
    return true;
}

void CZipWrapper::CloseZipFile()
{
    //如果已经打开文件，则关闭
    if (m_pUnZipFile != NULL)
    {
        unzClose(m_pUnZipFile);
        m_pUnZipFile = NULL;
    }
    if (m_pZipFile != NULL)
    {
        zipClose(m_pZipFile, NULL);
        m_pZipFile = NULL;
    }
    memset(&m_endpos, 0, sizeof(m_endpos));
    m_index.clear();
    m_bUseIndexPos = false;
    m_strZipFile.clear();
}

bool CZipWrapper::AddFileFromLocalFile(const TCHAR* szLocalFile, const TCHAR* szUnitName)
{
    //检查文件指针是否为空及文件是否已存在
    if (szLocalFile == NULL || UnitIsExist(szUnitName))
    {
        return false;
    }

    _tstring strLocalFile = szLocalFile;
    _tstring strUnitName;
    if (szUnitName == NULL)
    {
        strUnitName = strLocalFile;
    }
    else
    {
        strUnitName = szUnitName;
    }

    if (!strLocalFile.empty())
    {
        fstream file(_tUNICODECHAR(strLocalFile), std::ios::in | std::ios::binary);
        if (!file.is_open())
        {
            return false;
        }

        zip_fileinfo zi = {0};
        GetFileTime(strLocalFile, zi.dosDate);
        unsigned long crc = GetFileCrc(strLocalFile);

        int err;
        if (m_strPassword.empty())
        {
            err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                                 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                 NULL, crc);
        }
        else
        {
            err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                                 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                 _tANSICHAR(m_strPassword), crc);
        }

        if (err != ZIP_OK)
        {
            return false;
        }

        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        while (size > 0)
        {
            size_t size_read;
            if (size > sizeof(m_sztmpbuff))
            {
                size_read = sizeof(m_sztmpbuff);
            }
            else
            {
                size_read = size;
            }
            file.read(m_sztmpbuff, static_cast<std::streamsize>(size_read));
            zipWriteInFileInZip(m_pZipFile, m_sztmpbuff, static_cast<unsigned int>(size_read));
            size -= size_read;
        }

        err = zipCloseFileInZip(m_pZipFile);
        if (err != ZIP_OK)
        {
            return false;
        }
    }
    else
    {
        zip_fileinfo zi = {0};

        int err;
        if (m_strPassword.empty())
        {
            err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                                 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                 NULL, 0);
        }
        else
        {
            err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                                 -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                 _tANSICHAR(m_strPassword), 0);
        }

        if (err != ZIP_OK)
        {
            return false;
        }
        err = zipCloseFileInZip(m_pZipFile);
        if (err != ZIP_OK)
        {
            return false;
        }
    }

    m_count ++;
    zipClose(m_pZipFile, NULL);
    m_pZipFile = NULL;

    unzClose(m_pUnZipFile);
    m_pUnZipFile = NULL;

    m_pZipFile = zipOpen(_tANSICHAR(m_strZipFile), WARP_APPEND_STATUS_ADDINZIP);
    m_pUnZipFile = unzOpen(_tANSICHAR(m_strZipFile));


    m_bUseIndexPos = false;
    //把文件列表插入m_index中，不过位置信息无效，只用于快速查找是否存在某个文件
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();

    pair<string, unz_file_pos> hashinfo(strUnitName.toNarrowString(), m_endpos);
    m_index.insert(hashinfo);
    return true;
}
bool CZipWrapper::AddFileFromMemory(const TCHAR* szUnitName, const void* pBuf, size_t len, uLong crc, uLong time)
{
    if (szUnitName == NULL || UnitIsExist(szUnitName))
    {
        return false;
    }

    _tstring strUnitName = szUnitName;
    zip_fileinfo zi = {0};
    zi.dosDate = time;
    unsigned long memcrc = crc;
    if (pBuf != NULL && crc == 0)
    {
        memcrc = crc32(memcrc, (Bytef*)pBuf, static_cast<uInt>(len));
    }

    int err;
    if (m_strPassword.empty())
    {
        err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                             -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                             NULL, memcrc);
    }
    else
    {
        err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strUnitName), &zi, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                             -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                             _tANSICHAR(m_strPassword), memcrc);
    }

    if (pBuf != NULL)
    {
        zipWriteInFileInZip(m_pZipFile, pBuf, static_cast<unsigned int>(len));
    }

    err = zipCloseFileInZip(m_pZipFile);
    if (err != ZIP_OK)
    {
        return false;
    }
    m_count ++;
    zipClose(m_pZipFile, NULL);
    m_pZipFile = NULL;

    unzClose(m_pUnZipFile);
    m_pUnZipFile = NULL;

    m_pZipFile = zipOpen(_tANSICHAR(m_strZipFile), WARP_APPEND_STATUS_ADDINZIP);
    m_pUnZipFile = unzOpen(_tANSICHAR(m_strZipFile));


    m_bUseIndexPos = false;
    //把文件列表插入m_index中，不过位置信息无效，只用于快速查找是否存在某个文件
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();

    pair<string, unz_file_pos> hashinfo(strUnitName.toNarrowString(), m_endpos);
    m_index.insert(hashinfo);
    return true;
}

bool CZipWrapper::AddFileFromAnotherZipWrapper(CZipWrapper& zip, const TCHAR* szUnitNameInAnoterZip, const TCHAR* szNewUnitName)
{
    if (szUnitNameInAnoterZip == NULL || zip.IsEmpty())
    {
        return false;
    }
    size_t size = 0;
    _tstring strUnitName = szUnitNameInAnoterZip;
    _tstring strNewUnitName;
    if (szNewUnitName == NULL)
    {
        strNewUnitName = strUnitName;
    }
    else
    {
        strNewUnitName = szNewUnitName;
    }

    strNewUnitName.Replace(_T("\\"), _T("/"));
    strNewUnitName.MakeLower();
    string strFindName = strNewUnitName.toNarrowString();

    if (!zip.m_bUseIndexPos)
    {
        zip.MakeIndex();
    }
    hash_map<string, unz_file_pos>::iterator itr = zip.m_index.find(strFindName);
    if (itr == zip.m_index.end())
    {
        return false;
    }

    int nRet = unzGoToFilePos(zip.m_pUnZipFile, &itr->second);
    if (nRet != UNZ_OK)
    {
        return false;
    }

    //int unzerr = unzLocateFile(zip.m_pUnZipFile, _tANSICHAR(strUnitName), CASESENSITIVITY);
    //if (unzerr != UNZ_OK)
    //{
    //    return false;
    //}

    unz_file_info unzinfo;
    zip_fileinfo zipinfo;
    char filename_inzip[256];
    int unzerr = unzGetCurrentFileInfo(zip.m_pUnZipFile, &unzinfo, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);
    if (unzerr != UNZ_OK)
    {
        return false;
    }

    if (zip.m_strPassword.empty())
    {
        unzerr = unzOpenCurrentFilePassword(zip.m_pUnZipFile, NULL);
    }
    else
    {
        unzerr = unzOpenCurrentFilePassword(zip.m_pUnZipFile, _tANSICHAR(zip.m_strPassword));
    }

    if (unzerr != UNZ_OK)
    {
        return false;
    }

    zipinfo.dosDate = unzinfo.dosDate;

    int err;
    if (m_strPassword.empty())
    {
        err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strNewUnitName), &zipinfo, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                         -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                         NULL, unzinfo.crc);
    }
    else
    {
        err = zipOpenNewFileInZip3(m_pZipFile, _tANSICHAR(strNewUnitName), &zipinfo, NULL, 0, NULL, 0, NULL, (m_compresslevel != 0) ? Z_DEFLATED : 0, m_compresslevel, 0,
                         -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                         _tANSICHAR(m_strPassword), unzinfo.crc);
    }

    if (err != ZIP_OK)
    {
        return false;
    }

    size = unzinfo.uncompressed_size;
    while (size > 0)
    {
        size_t readsize;
        if (size > sizeof(m_sztmpbuff))
        {
            readsize = sizeof(m_sztmpbuff);
        }
        else
        {
            readsize = size;
        }

        unzReadCurrentFile(zip.m_pUnZipFile, m_sztmpbuff, static_cast<unsigned int>(readsize));
        zipWriteInFileInZip(m_pZipFile, m_sztmpbuff, static_cast<unsigned int>(readsize));
        size -= readsize;
    }

    zipCloseFileInZip(m_pZipFile);
    unzCloseCurrentFile(zip.m_pUnZipFile);

    m_count ++;
    zipClose(m_pZipFile, NULL);
    m_pZipFile = NULL;

    unzClose(m_pUnZipFile);
    m_pUnZipFile = NULL;

    m_pZipFile = zipOpen(_tANSICHAR(m_strZipFile), WARP_APPEND_STATUS_ADDINZIP);
    m_pUnZipFile = unzOpen(_tANSICHAR(m_strZipFile));


    m_bUseIndexPos = false;
    //把文件列表插入m_index中，不过位置信息无效，只用于快速查找是否存在某个文件
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();

    pair<string, unz_file_pos> hashinfo(strUnitName.toNarrowString(), m_endpos);
    m_index.insert(hashinfo);
    return true;
}

bool CZipWrapper::UnitIsExist(const TCHAR* szUnitName)
{
    if (szUnitName == NULL || IsEmpty())
    {
        return false;
    }
    _tstring strUnitName = szUnitName;
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();
    string strFindName = strUnitName.toNarrowString();

    if (m_index.find(strFindName) != m_index.end())
    {
        return true;
    }
    else
    {
        return false;
    }

    //int nRet = unzLocateFile(m_pUnZipFile, _tANSICHAR(strUnitName), CASESENSITIVITY);
    //if (nRet != UNZ_OK)
    //{
    //    return false;
    //}
    //unzCloseCurrentFile(m_pUnZipFile);
    //return true;
}

bool CZipWrapper::IsOpen() const
{
    return (m_pZipFile != NULL);
}

bool CZipWrapper::IsEmpty() const
{
    return (m_pUnZipFile == NULL);
}

size_t CZipWrapper::GetCount() const
{
    return m_count;
}

void CZipWrapper::SetCompressLevel(int CompressLevel)
{
    m_compresslevel = CompressLevel;
}

bool CZipWrapper::GetUnitSize(const TCHAR* szUnitName, size_t& size)
{
    if (szUnitName == NULL || IsEmpty())
    {
        return false;
    }
    _tstring strUnitName = szUnitName;
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();
    string strFindName = strUnitName.toNarrowString();

    if (!m_bUseIndexPos)
    {
        MakeIndex();
    }
    hash_map<string, unz_file_pos>::iterator itr = m_index.find(strFindName);
    if (itr != m_index.end())
    {
        int err = unzGoToFilePos(m_pUnZipFile, &itr->second);
        if (err != UNZ_OK)
        {
            return false;
        }
        
    }
    else
    {
        return false;
    }
    //else
    //{
    //    int nRet = unzLocateFile(m_pUnZipFile, _tANSICHAR(strUnitName), CASESENSITIVITY);
    //    if (nRet != UNZ_OK)
    //    {
    //        return false;
    //    }
    //}

    unz_file_info file_info;
    char filename_inzip[256] = {0};
    int nRet = unzGetCurrentFileInfo(m_pUnZipFile, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);

    if (nRet != UNZ_OK)
    {
        return false;
    }

    size = file_info.uncompressed_size;
    unzCloseCurrentFile(m_pUnZipFile);
    return true;
}

_tstring CZipWrapper::GetZipFileName() const
{
    return m_strZipFile;
}

void CZipWrapper::SetPassword(_tstring strPassword)
{
    m_strPassword = strPassword;
}

CZipWrapper::UnitInfoList CZipWrapper::GetUnitList()
{
    CZipWrapper::UnitInfoList list;
    unzGoToFirstFile(m_pUnZipFile);

    //获取所包含的Unit个数
    unz_global_info info;
    int ret = unzGetGlobalInfo(m_pUnZipFile, &info);
    if (ret != UNZ_OK)
    {
        return list;
    }
    unzGoToFirstFile(m_pUnZipFile);

    for (uLong i=0; i<info.number_entry; i++)
    {
        CZipWrapper::UNITINFO info;
        char filename_inzip[256];
        int unzerr = unzGetCurrentFileInfo(m_pUnZipFile, &info.info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);
        if (unzerr != UNZ_OK)
        {
            unzGoToNextFile(m_pUnZipFile);
            //return false;
            continue;
        }
        info.strFileName = filename_inzip;

        //如果名字为空或者最后为 \ 或者是 / 则表示可能是文件夹，没有意义
        if (info.strFileName.empty() ||
            info.strFileName[info.strFileName.length()-1] == _T('\\') ||
            info.strFileName[info.strFileName.length()-1] == _T('/'))
        {
            unzGoToNextFile(m_pUnZipFile);
            continue;
        }
        list.push_back(info);
        unzGoToNextFile(m_pUnZipFile);
    }

    return list;
}

bool CZipWrapper::GetUnitToMemory(const TCHAR* szUnitName, void* pDst, size_t& dstSize)
{
    if (szUnitName == NULL || pDst == NULL || IsEmpty())
    {
        return false;
    }

    _tstring strUnitName = szUnitName;
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();
    string strFindName = strUnitName.toNarrowString();

    //重建索引
    if (!m_bUseIndexPos)
    {
        MakeIndex();
    }

    hash_map<string, unz_file_pos>::iterator itr = m_index.find(strFindName);
    if (itr == m_index.end())
    {
        return false;
    }

    int nRet = unzGoToFilePos(m_pUnZipFile, &itr->second);
    if (nRet != UNZ_OK)
    {
        return false;
    }

    ////读取zip中的文件
    //int nRet = unzLocateFile(m_pUnZipFile, _tANSICHAR(strUnitName), CASESENSITIVITY);
    //if (nRet != UNZ_OK)
    //{
    //    return false;
    //}

    unz_file_info file_info;
    char filename_inzip[256] = {0};
    nRet = unzGetCurrentFileInfo(m_pUnZipFile, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);

    if (nRet != UNZ_OK)
    {
        return false;
    }

    //pDst内存块大小少于文件解压后的大小
    if (dstSize < file_info.uncompressed_size)
    {
        return false;
    }

    if (m_strPassword.empty())
    {
        nRet = unzOpenCurrentFilePassword(m_pUnZipFile, NULL);
    }
    else
    {
        nRet = unzOpenCurrentFilePassword(m_pUnZipFile, _tANSICHAR(m_strPassword));
    }

    if (nRet != UNZ_OK)
    {
        return false;
    }

    nRet = unzReadCurrentFile(m_pUnZipFile, pDst, file_info.uncompressed_size);
    if (nRet < 0 || (unsigned int)nRet != file_info.uncompressed_size)
    {
        unzCloseCurrentFile(m_pUnZipFile);
        return false;
    }

    unzCloseCurrentFile(m_pUnZipFile);
    dstSize = file_info.uncompressed_size;
    return true;
}

bool CZipWrapper::SaveUnitToFile(const TCHAR* szUnitName, const TCHAR* szFilePath)
{
    if (szUnitName == NULL || szFilePath == NULL || IsEmpty())
    {
        return false;
    }
    _tstring strUnitName = szUnitName;
    strUnitName.Replace(_T("\\"), _T("/"));
    strUnitName.MakeLower();

    string strFindName = strUnitName.toNarrowString();

    if (!m_bUseIndexPos)
    {
        MakeIndex();
    }

    hash_map<string, unz_file_pos>::iterator itr = m_index.find(strFindName);
    if (itr == m_index.end())
    {
        return false;
    }

    int nRet = unzGoToFilePos(m_pUnZipFile, &itr->second);
    if (nRet != UNZ_OK)
    {
        return false;
    }

    _tstring strFilePath = szFilePath;
    //读取zip中的文件
    //int nRet = unzLocateFile(m_pUnZipFile, _tANSICHAR(strUnitName), CASESENSITIVITY);
    //if (nRet != UNZ_OK)
    //{
    //    return false;
    //}

    unz_file_info file_info;
    char filename_inzip[256] = {0};
    nRet = unzGetCurrentFileInfo(m_pUnZipFile, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);

    if (nRet != UNZ_OK)
    {
        return false;
    }

    if (m_strPassword.empty())
    {
        nRet = unzOpenCurrentFilePassword(m_pUnZipFile, NULL);
    }
    else
    {
        nRet = unzOpenCurrentFilePassword(m_pUnZipFile, _tANSICHAR(m_strPassword));
    }

    nRet = unzOpenCurrentFilePassword(m_pUnZipFile, NULL);
    if (nRet != UNZ_OK)
    {
        return false;
    }

    _tstring strFolder = GetFolder(strFilePath);
    if (!strFolder.empty() && !MakeDir(strFolder))
    {
        return false;
    }
    fstream file(_tUNICODECHAR(strFilePath), std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }
    size_t size = file_info.uncompressed_size;
    while (size >0)
    {
        size_t readsize;
        if (size > sizeof(m_sztmpbuff))
        {
            readsize = sizeof(m_sztmpbuff);
        }
        else
        {
            readsize = size;
        }
        nRet = unzReadCurrentFile(m_pUnZipFile, m_sztmpbuff, static_cast<unsigned int>(readsize));
        file.write(m_sztmpbuff, static_cast<std::streamsize>(readsize));
        size -= readsize;
    }

    file.close();
    unzCloseCurrentFile(m_pUnZipFile);

    SetFileChangeTime(strFilePath, file_info.dosDate);
    return true;
}

unsigned long CZipWrapper::GetFileTime(_tstring strFileName, uLong& time)
{
    int ret = 0;
    {
        FILETIME ftLocal;
        HANDLE hFind;
        WIN32_FIND_DATA ff32;

        hFind = FindFirstFile(strFileName.c_str(), &ff32);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
            FileTimeToDosDateTime(&ftLocal,((LPWORD)(&time))+1,((LPWORD)&time)+0);
            FindClose(hFind);
            ret = 1;
        }
    }
    return ret;
}

unsigned long CZipWrapper::GetFileCrc(_tstring strFileName)
{
    fstream file(_tUNICODECHAR(strFileName), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        return 0;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    uLong calculate_crc = 0;

    while (size > 0)
    {
        size_t size_read;
        if (size > TMPBUFFSIZE)
        {
            size_read = TMPBUFFSIZE;
        }
        else
        {
            size_read = size;
        }
        file.read(m_sztmpbuff, static_cast<std::streamsize>(size_read));
        calculate_crc = crc32(calculate_crc, (Bytef*)m_sztmpbuff, static_cast<uInt>(size_read));
        size -= size_read;
    }
    return calculate_crc;
}

void CZipWrapper::MakeIndex()
{
    if (IsEmpty())
    {
        return;
    }

    m_index.clear();

    //建立索引
    unzGoToFirstFile(m_pUnZipFile);
    for (size_t i=0; i<m_count; i++)
    {
        pair<string, unz_file_pos> info;
        char filename_inzip[256];
        unz_file_info unzinfo;
        int unzerr = unzGetCurrentFileInfo(m_pUnZipFile, &unzinfo, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0);
        if (unzerr != UNZ_OK)
        {
            unzGoToNextFile(m_pUnZipFile);
            //return false;
            continue;
        }

        _tstring strFile = filename_inzip;
        //如果名字为空或者最后为 \ 或者是 / 则表示可能是文件夹，没有意义
        if (strFile.empty() ||
            strFile[strFile.length()-1] == _T('\\') ||
            strFile[strFile.length()-1] == _T('/'))
        {
            unzGoToNextFile(m_pUnZipFile);
            continue;
        }

        strFile.Replace(_T("\\"), _T("/"));
        strFile.MakeLower();
        info.first = strFile.toNarrowString();
        unzGetFilePos(m_pUnZipFile, &info.second);       //获取文件偏移
        pair<hash_map<string, unz_file_pos>::iterator, bool> ret = m_index.insert(info);
        if (!ret.second)
        {
            //如果已存在相同文件名的文件，暂不处理
        }
        if ((i+1) <m_count)
        {
            unzGoToNextFile(m_pUnZipFile);
        }

        //获取最后文件位置
        if ((i+1) == m_count)
        {
            m_endpos = info.second;
        }
    }
    m_bUseIndexPos = true;
}

_tstring CZipWrapper::GetFolder(_tstring strFullFilePath)
{
    _tstring strFolder;
    if (strFullFilePath.empty())
    {
        return strFolder;
    }
    strFullFilePath.Replace(_T("/"), _T("\\"));
    size_t nlength = strFullFilePath.length();
    for (size_t i=nlength; i>0; i--)
    {
        if (strFullFilePath[i-1] == _T('\\'))
        {
            strFolder = strFullFilePath.substr(0, i-1);
            return strFolder;
        }
    }
    return strFolder;
}

bool CZipWrapper::MakeDir(_tstring strFolder)
{
    if (strFolder.empty())
    {
        return false;
    }

    strFolder.Replace(_T("/"), _T("\\"));
    if (strFolder[strFolder.length()-1] != _T('\\'))
    {
        strFolder += _T("\\");
    }
    size_t nLength = strFolder.length();
    for (size_t i = 0; i<nLength; i++)
    {
        if (strFolder[i] == _T('\\'))
        {
            _tstring strTmpFolder = strFolder.substr(0, i);
            if (_mkdir(_tANSICHAR(strTmpFolder)) == ENOENT)
            {
                return false;
            }
        }
    }
    return true;
}

bool CZipWrapper::SetFileChangeTime(_tstring strFileName, uLong time)
{
    HANDLE fileHandle = CreateFile(strFileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
        FILETIME filetime;
        FILETIME localtime;
        DosDateTimeToFileTime((WORD)(time>>16), (WORD)time, &localtime);
        LocalFileTimeToFileTime(&localtime, &filetime);
        SetFileTime(fileHandle, (LPFILETIME)NULL, (LPFILETIME)NULL, &filetime);
	}
    else
    {
        return false;
    }

	CloseHandle( fileHandle );
    return true;
}

};