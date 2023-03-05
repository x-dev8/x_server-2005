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
    虚拟文件系统实现类
    目前暂时使用Zip作为文件载体
    Zip库由Zlib提供
    使用了内存池为CVFSUnit数据提供存储空间
    内存池由Common::TObject_pool及Common::TAllocator提供
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

//将普通文件名转换成为特定的FileIO中的类所使用的文件名
_tstring ConvFileName(_tstring strFileName);

template <unsigned int CacheSize>           //Unit类型，缓冲大小
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
    //载入VFS文件系统中的文件个体
    bool LoadUnit(const TCHAR* szUnitName, _ImpVFS& vfs);
    /*++

    Routine Description:

        载入虚拟文件系统中的个体文件
        但是如果相同路径下的本地磁盘文件存在的话，将会忽略虚拟文件系统而直接从本地磁盘中载入文件

    Arguments:

        szUnitName - 虚拟文件系统中个体文件路径及文件名
        vfs - 虚拟文件系统

    Return Value:

        true - 载入成功
        false - 载入失败

    --*/


    bool LoadUnit(const TCHAR* szUnitName);
    /*++

    Routine Description:

        载入本地磁盘中存在的文件

    Arguments:

        szUnitName - 本地磁盘文件路径及文件名

    Return Value:

        true - 载入成功
        false - 载入失败

    --*/

    void ReleaseUnit();
    /*++

    Routine Description:

        释放已经载入的文件个体
        允许被释放多次，不会造成影响。
        忽略是由本地磁盘载入或者是由虚拟文件系统载入

    Arguments:

        None

    Return Value:

        None

    --*/

public:

    unsigned char* GetData() const;
    /*++

    Routine Description:

        获取数据块起始地址

    Arguments:

        None

    Return Value:

        unsigned char* - 数据块启始地址。如果未载入文件，则返回NULL指针

    --*/

    unsigned char* operator ()() const;
    /*++

    Routine Description:

        获取数据块起始地址

    Arguments:

        None

    Return Value:

        unsigned char* - 数据块启始地址。如果未载入文件，则返回NULL指针

    --*/


    //获取文件长度
    size_t GetFileLength() const;
    /*++

    Routine Description:

        获取载入的个体文件长度

    Arguments:

        None

    Return Value:
    
        size_t - 文件长度。如果未载入文件，则返回0

    --*/

    _tstring GetUnitFileName() const;
    /*++

    Routine Description:

        获取个体文件名

    Arguments:

        None

    Return Value:
    
        _tstring - 返回的个体文件名。如果未载入文件，则返回 _tstring(_T("")) 空字串

    --*/


    _tstring GetVFSFileName() const;


    bool IsOpen() const;
    /*++

    Routine Description:

        判断是否已载入文件资源

    Arguments:

        None

    Return Value:
    
        true - 已载入
        false - 未载入

    --*/

private:

    unsigned char* m_bData;     //指向文件内存块位置
    FileInfo m_info;            //用于存储文件信息
    

private:

    //设置Cache的缓冲大小为50M  
    //注意：50M只是文件所占用的实际大小，为了提高效率，内存池申请的实际内存可能会比这个值大
    //实际内存池所申请的大小为：设置内存大小 < 实际内存大小 < 设置内存大小*2
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
        _tstring strUnitName;           //虚拟文件系统中的名字
        _tstring strDiskFileName;       //存储在磁盘上的临时文件
    }ADDUNITSAVE;

public:

    typedef struct tagCallBackArgument
    {
        _tstring strCurrFileName;
        size_t nCurrFileCount;
        size_t nAllFileCount;
    }CALLBACKARGUMENT;
    //在将对VFS的操作改变至磁盘文件时过程回调函数，strcurrfilename为当前更改的文件名 changedcount为已更改的文件数，allchangcount为所有更改的文件数
    typedef void (*ChangeProcCallBack)(const CALLBACKARGUMENT*);

public:
    //返回列表
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

        载入资源包

    Arguments:

        szFileName - VFS的资源包（以目前的实现方式，资源包为ZIP文档）

    Return Value:
    
        true - 获取成功
        false - 获取失败

    --*/

    bool AppendVFS(const TCHAR* szFileName);
    /*++

    Routine Description:

        附加资源包 越被后面附加上去的资源包，其访问优先级越高。
        比如后面附加进去的资源包里存在一个与现有的资源包相同名字的文件，
        那么将只访问附加进去的资源包的文件

    Arguments:

        szFileName - VFS的资源包（以目前的实现方式，资源包为ZIP文档）

    Return Value:
    
        true - 获取成功
        false - 获取失败

    --*/


    void Release();
    /*++

    Routine Description:

        释放VFS文件系统资源包
        即使资源包没有载入，调用这个函数也不会产生任何负面影响
        同时，已经载入数据的VFSUnit也不会因此受到影响

    Arguments:

        None

    Return Value:
    
        None

    --*/

    bool GetUnit(const TCHAR* szUnitName, void* pDst, size_t& dstSize);
    /*++

    Routine Description:

        将虚拟文件系统中的某个文件载入

    Arguments:

        szUnitName - 虚拟文件系统中的文件路径及文件名
        pDst - 存放文件的内存地址
        dstSize - 用于通知GetUnit函数pDst为首地址的内存块大小，以及函数处理完毕后返回pDst实际载入数据的内存大小

    Return Value:
    
        true - 载入成功
        false - 载入失败

    --*/

    bool GetUnitLength(const TCHAR* szUnitName, size_t& size);
    /*++

    Routine Description:

        获取虚拟文件系统中某个文件的实际大小（解压后）

    Arguments:

        szUnitName - 虚拟文件系统中的文件路径及文件名
        size - 函数处理完毕后返回文件的大小

    Return Value:
    
        true - 获取成功
        false - 获取失败

    --*/

    bool IsOpen() const;
    /*++

    Routine Description:

        判断虚拟文件系统是否已经打开资源包

    Arguments:

        None

    Return Value:
    
        true - 已打开
        false - 未打开

    --*/

    bool IsEmpty() const;
    /*++

    Routine Description:

        判断虚拟文件系统是否为空

    Arguments:

        None

    Return Value:
    
        true - 已打开
        false - 未打开

    --*/

    bool UnitIsExist(const TCHAR* szUnitName);
    /*++

    Routine Description:

        判断虚拟文件系统中是否存在某个文件

    Arguments:

        szUnitName - 需要判断是否存在的文件

    Return Value:
    
        true - 存在
        false - 不存在

    --*/
    UNITLIST GetUnitList();

    bool SaveUnitToFile(const TCHAR* szUnitName, const TCHAR* szLocalPath);

//VFS文件操作
public:
    //将Unit添加至文件系统中
    bool AddUnit(const TCHAR* szUnitName, const char* pSrc, size_t len);
    bool AddUnit(const TCHAR* szUnitName, const TCHAR* szLocalFilePath);
    bool AddUnit(const CVFSUnit& unit);
    
    //将VFS文件中某个UNIT删除
    bool DelUnit(const TCHAR* szUnitName);

    //将添加/删除操作保存（AddUnit及DelUnit只是在内存中进行操作，必须调用Save将之保存在磁盘文件实体）
    bool Save(ChangeProcCallBack proc = NULL);

public:
    //新建一个VFS文件
    bool NewVFSFile(const TCHAR* szSaveName);

public:
    //获取VFS中的Unit个数
    unsigned int GetUnitCount();

    _tstring GetFileName() const;
    /*++

    Routine Description:

        获取虚拟文件系统资源包在本地磁盘中的文件名

    Arguments:

        None

    Return Value:

        _tstring - 返回文件名 如果未载入则返回空字串 _tstring(_T(""))

    --*/

private:
    _tstring m_strFileName;                         //zip文件名
    vector<CZipWrapper*> m_ziplist;                  //zip操作接口
    map<_tstring, _tstring> m_addlist;              //添加的Unit列表
    map<_tstring, _tstring> m_dellist;              //删除Unit列表
    _tstring m_strPassword;

//禁止拷贝构造函数
private:
    CVFS(const CVFS&);
    CVFS& operator = (const CVFS&);
};

}


#endif