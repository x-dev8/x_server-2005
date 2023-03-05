#ifndef __IMP_VIRTUAL_FILE_SYSTEM_H__
#define __IMP_VIRTUAL_FILE_SYSTEM_H__

#pragma once

#include <TCHAR.H>

namespace FileIO
{
    class _ImpVFS;
    class _ImpVFSUnit
    {
    public:
        virtual ~_ImpVFSUnit() {};

        //载入VFS文件系统中的文件个体
        virtual bool LoadUnit(const TCHAR* szUnitName, _ImpVFS& vfs) = 0;
        virtual bool LoadUnit(const TCHAR* szUnitName) = 0;
        virtual void ReleaseUnit() = 0;             // 释放资源
        virtual unsigned char* GetData() const = 0; // 获取文件资源

    protected:
        _ImpVFSUnit() {};
    };

    class _ImpVFS
    {
    public:
        virtual ~_ImpVFS() {};

        virtual bool LoadVFS(const TCHAR* szFileName) = 0;                               // 载入，释放VSF文件资源
        virtual void Release() = 0;
        virtual bool GetUnit(const TCHAR* szUnitName, void* pDst, size_t& size) = 0;     // 将虚拟文件系统中的某个文件载入
        virtual bool AddUnit(const TCHAR* szFileName, const char* pSrc, size_t len) = 0; // VFS文件操作 将Unit添加至文件系统中
        virtual bool DelUnit(const TCHAR* szUnitName) = 0;                               // 将VFS文件中某个UNIT删除
        virtual bool NewVFSFile(const TCHAR* szSaveName) = 0;                            // 新建一个VFS文件
        virtual unsigned int GetUnitCount() = 0;                                         // 获取VFS中的Unit个数
    protected:
        _ImpVFS() {};
    };
}

#endif // __IMP_VIRTUAL_FILE_SYSTEM_H__
