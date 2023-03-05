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

        //����VFS�ļ�ϵͳ�е��ļ�����
        virtual bool LoadUnit(const TCHAR* szUnitName, _ImpVFS& vfs) = 0;
        virtual bool LoadUnit(const TCHAR* szUnitName) = 0;
        virtual void ReleaseUnit() = 0;             // �ͷ���Դ
        virtual unsigned char* GetData() const = 0; // ��ȡ�ļ���Դ

    protected:
        _ImpVFSUnit() {};
    };

    class _ImpVFS
    {
    public:
        virtual ~_ImpVFS() {};

        virtual bool LoadVFS(const TCHAR* szFileName) = 0;                               // ���룬�ͷ�VSF�ļ���Դ
        virtual void Release() = 0;
        virtual bool GetUnit(const TCHAR* szUnitName, void* pDst, size_t& size) = 0;     // �������ļ�ϵͳ�е�ĳ���ļ�����
        virtual bool AddUnit(const TCHAR* szFileName, const char* pSrc, size_t len) = 0; // VFS�ļ����� ��Unit������ļ�ϵͳ��
        virtual bool DelUnit(const TCHAR* szUnitName) = 0;                               // ��VFS�ļ���ĳ��UNITɾ��
        virtual bool NewVFSFile(const TCHAR* szSaveName) = 0;                            // �½�һ��VFS�ļ�
        virtual unsigned int GetUnitCount() = 0;                                         // ��ȡVFS�е�Unit����
    protected:
        _ImpVFS() {};
    };
}

#endif // __IMP_VIRTUAL_FILE_SYSTEM_H__
