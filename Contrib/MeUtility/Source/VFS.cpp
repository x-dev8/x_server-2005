#include "vfs.h"

using Common::_tstring;
using std::pair;
using std::ios;

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

namespace FileIO
{

CUnitCache<10> CVFSUnit::s_Cache;

_tstring ConvFileName(_tstring strFileName)
{
    //�� "\\"ת����"/"
    strFileName.Replace(_T("\\"), _T("/"));
    strFileName.MakeLower();
    return strFileName;
}


CVFS::CVFS()
{
}

CVFS::~CVFS()
{
    CVFS::Release();
}

void CVFS::SetPassword(_tstring strPassword)
{
    m_strPassword = strPassword;
    for (vector<CZipWrapper*>::iterator itr = m_ziplist.begin();
        itr != m_ziplist.end();
        itr ++)
    {
        CZipWrapper& zip = **itr;
        zip.SetPassword(strPassword);
    }
}

bool CVFS::AddUnit(const TCHAR* szUnitName, const TCHAR* szLocalFilePath)
{
	CSALocker locker(this);
    if (szUnitName == NULL || szLocalFilePath == NULL || !IsOpen())
    {
        return false;
    }

    //��鵱ǰ�Ƿ��Ѿ�������ͬ���ֵ��ļ�
    //�����ͬ����Ϊ�޷����
    _tstring strFileName = ConvFileName(szUnitName);
    _tstring strLocalFilePath = szLocalFilePath;

    map<_tstring, _tstring>::iterator itr = m_addlist.find(strFileName);
    if (itr != m_addlist.end())
    {
        return false;
    }

    if (UnitIsExist(strFileName.c_str()))
    {
        return false;
    }

    //���ڴ��д���ļ����ұ��浽add�б�
    m_addlist.insert(pair<_tstring, _tstring>(strFileName, strLocalFilePath));
    return true;
}

bool CVFS::AddUnit(const CVFSUnit& unit)
{
    return AddUnit(unit.GetUnitFileName().c_str(), (const char*)unit.GetData(), unit.GetFileLength());
}

bool CVFS::AddUnit(const TCHAR* szUnitName, const char* pSrc, size_t len)
{
	CSALocker locker(this);
    if (szUnitName == NULL || !IsOpen())
    {
        return false;
    }

    //��鵱ǰ�Ƿ��Ѿ�������ͬ���ֵ��ļ�
    //�����ͬ����Ϊ�޷����
    _tstring strFileName = ConvFileName(szUnitName);

    map<_tstring, _tstring>::iterator itr = m_addlist.find(strFileName);
    if (itr != m_addlist.end())
    {
        return false;
    }

    if (UnitIsExist(strFileName.c_str()))
    {
        return false;
    }
    
    //��ӿ�UNIT
    if (pSrc == NULL || len == 0)
    {
        m_addlist.insert(pair<_tstring, _tstring>(strFileName, _tstring()));
        return true;
    }
    //����tmpĿ¼
    _mkdir(_tANSICHAR(_T("tmp")));
    _tstring strFile;
    srand((unsigned int)time(NULL));

    strFile.Format(_T("tmp\\%d.tmp"), rand());

    //�ҳ���ǰ�����ڵ��ļ���
    while (_access(_tANSICHAR(strFile), 0) != -1)
    {
        strFile.Format(_T("tmp\\%d.tmp"), rand());
    }

    fstream filetmp(_tUNICODECHAR(strFile), ios::app | ios::binary | ios::in);
    
    if (!filetmp.is_open())
    {
        return false;
    }

    //д���ļ�����
    filetmp.write(pSrc, static_cast<std::streamsize>(len));
    filetmp.close();

    //���ڴ��д���ļ����ұ��浽add�б�
    m_addlist.insert(pair<_tstring, _tstring>(strFileName, strFile));
    return true;
}

bool CVFS::DelUnit(const TCHAR* szUnitName)
{
	CSALocker locker(this);
    if (szUnitName == NULL || !IsOpen())
    {
        return false;
    }

    //��鵱ǰZip�ļ����Ƿ��Ѿ�������ͬ���ֵ��ļ�
    //�����ͬ����Ϊ�޷����
    _tstring strFileName = ConvFileName(szUnitName);

    //���Ҫɾ�����ļ���������б��У���ɾ��
    map<_tstring, _tstring>::iterator itr = m_addlist.find(strFileName);
    if (itr != m_addlist.end())
    {
        //ɾ����ʱ�ļ�
        remove(_tANSICHAR(itr->second));
        m_addlist.erase(itr);
        return true;
    }

    if (!UnitIsExist(szUnitName))
    {
        return false;
    }

    //�Ѿ�����
    if (m_dellist.find(strFileName) != m_dellist.end())
    {
        return false;
    }

    m_dellist.insert(pair<_tstring, _tstring>(strFileName, _T("")));
    return true;
}

bool CVFS::Save(ChangeProcCallBack proc)
{
	CSALocker locker(this);
    if (!IsOpen())
    {
        return false;
    }

    CALLBACKARGUMENT argument;
    argument.nAllFileCount = 0;
    if (!m_dellist.empty())
    {
        argument.nAllFileCount += m_ziplist.front()->GetCount();
    }

    argument.nAllFileCount += m_addlist.size();

    if (!m_dellist.empty())
    {
        _tstring strOldVFS = GetFileName();
        _tstring strNewVFS;
        strNewVFS.Format(_T("%s.tmp"), GetFileName().c_str());

        CZipWrapper newzip(strNewVFS.c_str(), WARP_APPEND_STATUS_CREATE);
        if (!newzip.IsOpen())
        {
            return false;
        }
        newzip.SetCompressLevel(0);

        //��õ�ǰzip�ļ��������ļ��б�
        CZipWrapper::UnitInfoList list = m_ziplist.front()->GetUnitList();
        size_t size = list.size();
        for (size_t i=0; i<size; i++)
        {
            if (!m_dellist.empty())
            {
                map<_tstring, _tstring>::iterator itr = m_dellist.find(ConvFileName(list[i].strFileName));
                if (itr != m_dellist.end())
                {
                    m_dellist.erase(itr);
                    continue;
                }
            }
            if (!newzip.AddFileFromAnotherZipWrapper(*m_ziplist.front(), list[i].strFileName.c_str()))
            {
                return false;
                //continue;
            }
            if (proc != NULL)
            {
                argument.nCurrFileCount = i;
                argument.strCurrFileName = list[i].strFileName;
                proc(&argument);
            }
        }

        newzip.CloseZipFile();
        m_ziplist.front()->CloseZipFile();

        remove(_tANSICHAR(strOldVFS));
        rename(_tANSICHAR(strNewVFS), _tANSICHAR(strOldVFS));
        if (!m_ziplist.front()->OpenZipFile(strOldVFS.c_str()))
        {
            return false;
        }
    }

    //����ļ�
    while (!m_addlist.empty())
    {
        _tstring strLocalFile = m_addlist.begin()->second;
        _tstring strUnitName = m_addlist.begin()->first;
        if (!m_ziplist.front()->AddFileFromLocalFile(strLocalFile.c_str(), strUnitName.c_str()))
        {
            return false;
        }
        m_addlist.erase(m_addlist.begin());
        if (proc != NULL)
        {
            argument.nCurrFileCount = argument.nAllFileCount - m_addlist.size();
            argument.strCurrFileName = strUnitName;
            proc(&argument);
        }
    }

    return true;
}

bool CVFS::GetUnit(const TCHAR* szUnitName, void* pDst, size_t& dstSize)
{
	CSALocker locker(this);
    if (szUnitName == NULL || !IsOpen())
    {
        return false;
    }
    _tstring strUnitName = ConvFileName(szUnitName);

    map<_tstring, _tstring>::iterator itr = m_addlist.find(strUnitName);
    if (itr != m_addlist.end())
    {
        fstream file(_tUNICODECHAR(itr->second), ios::in | ios::binary);
        if (!file.is_open())
        {
            return false;
        }
        file.seekg(0, ios::end);
        size_t filesize = file.tellg();
        //BUFFERС���ļ���С
        if (dstSize < filesize)
        {
            file.close();
            return false;
        }
        file.seekg(0, ios::beg);
        file.read(static_cast<char*>(pDst), static_cast<std::streamsize>(filesize));
        file.close();
        dstSize = filesize;
        return true;
    }

    //����������ӵ�zip�ļ����ж�ȡ
    size_t size = m_ziplist.size();
    if (size != 0)
    {
        for (size_t i=size; i>0; i--)
        {
            if (m_ziplist[i-1]->GetUnitToMemory(szUnitName, pDst, dstSize))
            {
                return true;
            }
        }
    }
    return false;
}

bool CVFS::GetUnitLength(const TCHAR* szUnitName, size_t& size)
{
	CSALocker locker(this);
    if (szUnitName == NULL)
    {
        return false;
    }
    size_t listsize = m_ziplist.size();
    if (listsize != 0)
    {
        for (size_t i=listsize; i>0; i--)
        {
            if (m_ziplist[i-1]->GetUnitSize(szUnitName, size))
            {
                return true;
            }
        }
    }
    return false;
}

unsigned int CVFS::GetUnitCount()
{
	CSALocker locker(this);
    unsigned int nCount = 0;
    size_t listsize = m_ziplist.size();
    if (listsize != 0)
    {
        for (size_t i=listsize; i>0; i--)
        {
            nCount += static_cast<unsigned int>(m_ziplist[i-1]->GetCount());
        }
    }
    return nCount;
}

bool CVFS::IsOpen() const
{
    return (!m_ziplist.empty() && m_ziplist.front()->IsOpen());
}

bool CVFS::IsEmpty() const
{
    return !(!m_ziplist.empty() && !m_ziplist.front()->IsEmpty());
}

bool CVFS::UnitIsExist(const TCHAR* szUnitName)
{
	CSALocker locker(this);
    if (szUnitName == NULL)
    {
        return false;
    }
	_tstring sztemp = szUnitName;
	ConvFileName( sztemp );
    for (vector<CZipWrapper*>::iterator itr = m_ziplist.begin();
        itr != m_ziplist.end();
        itr ++)
    {
        CZipWrapper& zip = **itr;
        if (zip.UnitIsExist(sztemp.c_str()))
        {
            return true;
        }
    }
    return false;
}

//���������ļ�ϵͳ�ļ�
bool CVFS::LoadVFS(const TCHAR* szFileName)
{
	CSALocker locker(this);
    Release();
    CZipWrapper* zip = new CZipWrapper(szFileName);
    if (!zip->IsOpen())
    {
        delete zip;
        return false;
    }
    zip->SetCompressLevel(0);
    zip->SetPassword(m_strPassword);
    m_ziplist.push_back(zip);
    m_strFileName = ConvFileName(_tstring(szFileName));
    return true;
}

bool CVFS::AppendVFS(const TCHAR* szFileName)
{
	CSALocker locker(this);
    CZipWrapper* zip = new CZipWrapper(szFileName);
    if (!zip->IsOpen())
    {
        delete zip;
        return false;
    }
    zip->SetCompressLevel(0);
    zip->SetPassword(m_strPassword);
    m_ziplist.push_back(zip);
    return false;
}

bool CVFS::NewVFSFile(const TCHAR* szSaveName)
{
	CSALocker locker(this);
	Release();
	CZipWrapper* zip = new CZipWrapper(szSaveName, WARP_APPEND_STATUS_CREATE);
    if (!zip->IsOpen())
    {
        delete zip;
        return false;
    }
	zip->SetCompressLevel(0);
    zip->SetPassword(m_strPassword);
    m_ziplist.push_back(zip);
    return true;
}

void CVFS::Release()
{
	CSALocker locker(this);
    m_strFileName = "";
    while (!m_ziplist.empty())
    {
        m_ziplist.back()->CloseZipFile();
        delete m_ziplist.back();
        m_ziplist.pop_back();
    }

    //ɾ��������ӵ��ļ�
    while (!m_addlist.empty())
    {
        remove(_tANSICHAR(m_addlist.begin()->second));
        m_addlist.erase(m_addlist.begin());
    }

    return;
}

bool CVFS::SaveUnitToFile(const TCHAR* szUnitName, const TCHAR* szLocalPath)
{
	CSALocker locker(this);
    size_t length = m_ziplist.size();
    if (length == 0)
    {
        return false;
    }
    for (size_t i=length; i>0; i--)
    {
        if (m_ziplist[i-1]->SaveUnitToFile(szUnitName, szLocalPath))
        {
            return true;
        }
    }
    return false;
}

CVFS::UNITLIST CVFS::GetUnitList()
{
	CSALocker locker(this);
    CVFS::UNITLIST list;
    if (m_ziplist.empty())
    {
        return list;
    }
    size_t length = m_ziplist.size();
    for (size_t i=length; i>0; i--)
    {
        CZipWrapper::UnitInfoList ziplist = m_ziplist[i-1]->GetUnitList();
        while (!ziplist.empty())
        {
            UNITINFO info;
            CZipWrapper::UNITINFO& zipinfo = ziplist.back();
            info.nCrc = zipinfo.info.crc;
            info.nLength = zipinfo.info.uncompressed_size;
            info.strFile = zipinfo.strFileName;
            _tstring strFileName = zipinfo.strFileName;

            strFileName.Replace(_T("/"), _T("\\"));
            strFileName.MakeLower();

            list.insert(pair<_tstring, UNITINFO>(strFileName, info));
            ziplist.pop_back();
        }
    }
    return list;
}

_tstring CVFS::GetFileName() const
{
    return m_strFileName;
}


CVFSUnit::CVFSUnit() : m_bData(NULL)
{
    m_info.nFileSize = 0;
}

CVFSUnit::~CVFSUnit()
{
    CVFSUnit::ReleaseUnit();
}

unsigned char* CVFSUnit::GetData() const
{
    return m_bData;
}
unsigned char* CVFSUnit::operator ()() const
{
    return m_bData;
}

//����CVFS�е��ļ����뷽��
bool CVFSUnit::LoadUnit(const TCHAR* szUnitName, _ImpVFS& vfs)
{
	CSALocker locker(this);
    if (LoadUnit(szUnitName))
    {
        return true;
    }

    ReleaseUnit();
    if (szUnitName == NULL)
    {
        return false;
    }
    _tstring strUnitName = ConvFileName(szUnitName);
    CVFS& cvfs = (CVFS&)vfs;
    m_bData = s_Cache.GetFileBlockFromCache(strUnitName, m_info.nFileSize, cvfs);
    if (m_bData == NULL)
    {
        return false;
    }
    this->m_info.strUnitFileName = szUnitName;
    m_info.strVFSFileName = cvfs.GetFileName();
    return true;
}
bool CVFSUnit::IsOpen() const
{
    return (m_bData!=NULL);
}
//ֱ�ӴӴ�������
bool CVFSUnit::LoadUnit(const TCHAR* szUnitName)
{
	CSALocker locker(this);
    ReleaseUnit();
    if (szUnitName == NULL)
    {
        return false;
    }
    _tstring strUnitName = ConvFileName(szUnitName);
    m_bData = s_Cache.GetFileBlockFromCache(strUnitName, m_info.nFileSize);

    if (m_bData == NULL)
    {
        return false;
    }
    return true;
}

void CVFSUnit::ReleaseUnit()
{
	CSALocker locker(this);
    if (m_bData != NULL)
    {
        s_Cache.ReleaseFileFromCache(*this);
        m_bData = NULL;
    }
    m_info.nFileSize = 0;
    m_info.strUnitFileName = "";
    m_info.strVFSFileName = "";
    return;
}

_tstring CVFSUnit::GetUnitFileName() const
{
    return m_info.strUnitFileName;
}

_tstring CVFSUnit::GetVFSFileName() const
{
    return m_info.strVFSFileName;
}

size_t CVFSUnit::GetFileLength() const
{
    return m_info.nFileSize;
}

}