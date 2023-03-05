/********************************************************************
	Filename: 	Vfs.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Module Name:
    VFS.h
    VFS.cpp
    Cache.h
    ZipWrapper.h
    ZipWrapper.cpp
    ./PRIV/_ImpVFS.h

Abstract:
    �����ļ�ϵͳʵ����
    Ŀǰ��ʱʹ��Zip��Ϊ�ļ�����
    Zip����Zlib�ṩ
    ʹ�����ڴ��ΪCVFSUnit�����ṩ�洢�ռ�
    �ڴ����Common::TObject_pool��Common::TAllocator�ṩ
 */

#ifndef __COMMON_VFS_H__
#define __COMMON_VFS_H__

#include "MeRTLibs.h"
#include "_ImpVFS.h"
#include "tstring.h"
#include "Cache.h"
#include "ZipWrapper.h"
#include "Mutex.h"

using Common::_tstring;
using std::map;
using std::vector;

namespace FileIO
{

//����ͨ�ļ���ת����Ϊ�ض���FileIO�е�����ʹ�õ��ļ���
_tstring ConvFileName(_tstring strFileName);

template <unsigned int CacheSize>           //Unit���ͣ������С
class CUnitCache;

class CVFS;

class CVFSUnit : public _ImpVFSUnit, CSemiAutoIntLock
{
    typedef struct tagFileInfo
    {
        _tstring strUnitFileName;
        _tstring strVFSFileName;
        size_t nFileSize;
    }FileInfo;

public:
    CVFSUnit();
    virtual ~CVFSUnit();

public:
    //����VFS�ļ�ϵͳ�е��ļ�����
    bool LoadUnit(const TCHAR* szUnitName, _ImpVFS& vfs);
    /*++

    Routine Description:

        ���������ļ�ϵͳ�еĸ����ļ�
        ���������ͬ·���µı��ش����ļ����ڵĻ���������������ļ�ϵͳ��ֱ�Ӵӱ��ش����������ļ�

    Arguments:

        szUnitName - �����ļ�ϵͳ�и����ļ�·�����ļ���
        vfs - �����ļ�ϵͳ

    Return Value:

        true - ����ɹ�
        false - ����ʧ��

    --*/


    bool LoadUnit(const TCHAR* szUnitName);
    /*++

    Routine Description:

        ���뱾�ش����д��ڵ��ļ�

    Arguments:

        szUnitName - ���ش����ļ�·�����ļ���

    Return Value:

        true - ����ɹ�
        false - ����ʧ��

    --*/

    void ReleaseUnit();
    /*++

    Routine Description:

        �ͷ��Ѿ�������ļ�����
        �����ͷŶ�Σ��������Ӱ�졣
        �������ɱ��ش�������������������ļ�ϵͳ����

    Arguments:

        None

    Return Value:

        None

    --*/

public:

    unsigned char* GetData() const;
    /*++

    Routine Description:

        ��ȡ���ݿ���ʼ��ַ

    Arguments:

        None

    Return Value:

        unsigned char* - ���ݿ���ʼ��ַ�����δ�����ļ����򷵻�NULLָ��

    --*/

    unsigned char* operator ()() const;
    /*++

    Routine Description:

        ��ȡ���ݿ���ʼ��ַ

    Arguments:

        None

    Return Value:

        unsigned char* - ���ݿ���ʼ��ַ�����δ�����ļ����򷵻�NULLָ��

    --*/


    //��ȡ�ļ�����
    size_t GetFileLength() const;
    /*++

    Routine Description:

        ��ȡ����ĸ����ļ�����

    Arguments:

        None

    Return Value:
    
        size_t - �ļ����ȡ����δ�����ļ����򷵻�0

    --*/

    _tstring GetUnitFileName() const;
    /*++

    Routine Description:

        ��ȡ�����ļ���

    Arguments:

        None

    Return Value:
    
        _tstring - ���صĸ����ļ��������δ�����ļ����򷵻� _tstring(_T("")) ���ִ�

    --*/


    _tstring GetVFSFileName() const;


    bool IsOpen() const;
    /*++

    Routine Description:

        �ж��Ƿ��������ļ���Դ

    Arguments:

        None

    Return Value:
    
        true - ������
        false - δ����

    --*/

private:

    unsigned char* m_bData;     //ָ���ļ��ڴ��λ��
    FileInfo m_info;            //���ڴ洢�ļ���Ϣ
    

private:

    //����Cache�Ļ����СΪ50M  
    //ע�⣺50Mֻ���ļ���ռ�õ�ʵ�ʴ�С��Ϊ�����Ч�ʣ��ڴ�������ʵ���ڴ���ܻ�����ֵ��
    //ʵ���ڴ��������Ĵ�СΪ�������ڴ��С < ʵ���ڴ��С < �����ڴ��С*2
    static CUnitCache<10> s_Cache;

    friend CVFS;

private:
    CVFSUnit(const CVFSUnit&);
    CVFSUnit& operator = (const CVFSUnit&);
};


class CVFS : public _ImpVFS, CSemiAutoIntLock
{
    typedef struct tagAddUnitSave
    {
        _tstring strUnitName;           //�����ļ�ϵͳ�е�����
        _tstring strDiskFileName;       //�洢�ڴ����ϵ���ʱ�ļ�
    }ADDUNITSAVE;

public:

    typedef struct tagCallBackArgument
    {
        _tstring strCurrFileName;
        size_t nCurrFileCount;
        size_t nAllFileCount;
    }CALLBACKARGUMENT;
    //�ڽ���VFS�Ĳ����ı��������ļ�ʱ���̻ص�������strcurrfilenameΪ��ǰ���ĵ��ļ��� changedcountΪ�Ѹ��ĵ��ļ�����allchangcountΪ���и��ĵ��ļ���
    typedef void (*ChangeProcCallBack)(const CALLBACKARGUMENT*);

public:
    //�����б�
    typedef struct tagUnitInfo
    {
        _tstring strFile;
        size_t nLength;
        unsigned long nCrc;
    }UNITINFO;
    typedef map<_tstring, UNITINFO> UNITLIST;

public:
    CVFS();
    virtual ~CVFS();

public:

    void SetPassword(_tstring strPassword);

    bool LoadVFS(const TCHAR* szFileName);
    /*++

    Routine Description:

        ������Դ��

    Arguments:

        szFileName - VFS����Դ������Ŀǰ��ʵ�ַ�ʽ����Դ��ΪZIP�ĵ���

    Return Value:
    
        true - ��ȡ�ɹ�
        false - ��ȡʧ��

    --*/

    bool AppendVFS(const TCHAR* szFileName);
    /*++

    Routine Description:

        ������Դ�� Խ�����渽����ȥ����Դ������������ȼ�Խ�ߡ�
        ������渽�ӽ�ȥ����Դ�������һ�������е���Դ����ͬ���ֵ��ļ���
        ��ô��ֻ���ʸ��ӽ�ȥ����Դ�����ļ�

    Arguments:

        szFileName - VFS����Դ������Ŀǰ��ʵ�ַ�ʽ����Դ��ΪZIP�ĵ���

    Return Value:
    
        true - ��ȡ�ɹ�
        false - ��ȡʧ��

    --*/


    void Release();
    /*++

    Routine Description:

        �ͷ�VFS�ļ�ϵͳ��Դ��
        ��ʹ��Դ��û�����룬�����������Ҳ��������κθ���Ӱ��
        ͬʱ���Ѿ��������ݵ�VFSUnitҲ��������ܵ�Ӱ��

    Arguments:

        None

    Return Value:
    
        None

    --*/

    bool GetUnit(const TCHAR* szUnitName, void* pDst, size_t& dstSize);
    /*++

    Routine Description:

        �������ļ�ϵͳ�е�ĳ���ļ�����

    Arguments:

        szUnitName - �����ļ�ϵͳ�е��ļ�·�����ļ���
        pDst - ����ļ����ڴ��ַ
        dstSize - ����֪ͨGetUnit����pDstΪ�׵�ַ���ڴ���С���Լ�����������Ϻ󷵻�pDstʵ���������ݵ��ڴ��С

    Return Value:
    
        true - ����ɹ�
        false - ����ʧ��

    --*/

    bool GetUnitLength(const TCHAR* szUnitName, size_t& size);
    /*++

    Routine Description:

        ��ȡ�����ļ�ϵͳ��ĳ���ļ���ʵ�ʴ�С����ѹ��

    Arguments:

        szUnitName - �����ļ�ϵͳ�е��ļ�·�����ļ���
        size - ����������Ϻ󷵻��ļ��Ĵ�С

    Return Value:
    
        true - ��ȡ�ɹ�
        false - ��ȡʧ��

    --*/

    bool IsOpen() const;
    /*++

    Routine Description:

        �ж������ļ�ϵͳ�Ƿ��Ѿ�����Դ��

    Arguments:

        None

    Return Value:
    
        true - �Ѵ�
        false - δ��

    --*/

    bool IsEmpty() const;
    /*++

    Routine Description:

        �ж������ļ�ϵͳ�Ƿ�Ϊ��

    Arguments:

        None

    Return Value:
    
        true - �Ѵ�
        false - δ��

    --*/

    bool UnitIsExist(const TCHAR* szUnitName);
    /*++

    Routine Description:

        �ж������ļ�ϵͳ���Ƿ����ĳ���ļ�

    Arguments:

        szUnitName - ��Ҫ�ж��Ƿ���ڵ��ļ�

    Return Value:
    
        true - ����
        false - ������

    --*/
    UNITLIST GetUnitList();

    bool SaveUnitToFile(const TCHAR* szUnitName, const TCHAR* szLocalPath);

//VFS�ļ�����
public:
    //��Unit������ļ�ϵͳ��
    bool AddUnit(const TCHAR* szUnitName, const char* pSrc, size_t len);
    bool AddUnit(const TCHAR* szUnitName, const TCHAR* szLocalFilePath);
    bool AddUnit(const CVFSUnit& unit);
    
    //��VFS�ļ���ĳ��UNITɾ��
    bool DelUnit(const TCHAR* szUnitName);

    //�����/ɾ���������棨AddUnit��DelUnitֻ�����ڴ��н��в������������Save��֮�����ڴ����ļ�ʵ�壩
    bool Save(ChangeProcCallBack proc = NULL);

public:
    //�½�һ��VFS�ļ�
    bool NewVFSFile(const TCHAR* szSaveName);

public:
    //��ȡVFS�е�Unit����
    unsigned int GetUnitCount();

    _tstring GetFileName() const;
    /*++

    Routine Description:

        ��ȡ�����ļ�ϵͳ��Դ���ڱ��ش����е��ļ���

    Arguments:

        None

    Return Value:

        _tstring - �����ļ��� ���δ�����򷵻ؿ��ִ� _tstring(_T(""))

    --*/

private:
    _tstring m_strFileName;                         //zip�ļ���
    vector<CZipWrapper*> m_ziplist;                  //zip�����ӿ�
    map<_tstring, _tstring> m_addlist;              //��ӵ�Unit�б�
    map<_tstring, _tstring> m_dellist;              //ɾ��Unit�б�
    _tstring m_strPassword;

//��ֹ�������캯��
private:
    CVFS(const CVFS&);
    CVFS& operator = (const CVFS&);
};

}


#endif