/********************************************************************
    Filename:    Cache.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#ifndef __VFS_CACHE_H__
#define __VFS_CACHE_H__

#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include "_ImpVFS.h"
#include "Memory_Pool.h"
#include "tstring.h"

using Common::_tstring;
using FileIO::_ImpVFS;
using FileIO::_ImpVFSUnit;
using std::map;
using std::list;

namespace FileIO
{
    class CVFS;
    class CVFSUnit;

    template <unsigned int CacheSize>           //Unit���ͣ������С
    class CUnitCache
    {
        //�ļ���
        typedef struct tagFileBlock
        {
            size_t nSize;                       //����
            unsigned int nRefCount;             //���ü���
            unsigned char* pData;               //�ڴ����ݿ��ַ
        }FILEBLOCK;

        //�ļ���Ϣ(���ڻ����ͷ�)
        typedef struct tagFileInfo
        {
            _tstring strVFSFileName;
            _tstring strUnitFileName;
            size_t nSize;
        }FILEINFO;

    public:
        CUnitCache() : m_UseCacheSize(0) {}

        virtual ~CUnitCache()
        {
            //�ͷ�ȫ���ڴ��
            while (!m_VFSCacheIndex.empty())
            {
                map<_tstring, FILEBLOCK>& secondindex = m_VFSCacheIndex.begin()->second;
                while (!secondindex.empty())
                {
                    s_Mempool.deallocate(secondindex.begin()->second.pData);
                    secondindex.erase(secondindex.begin());
                }
                m_VFSCacheIndex.erase(m_VFSCacheIndex.begin());
            }
        }

    public:
        //ͨ���ļ�����ȡ�ļ����棬�����ڴ��ַָ���Լ�ͨ�����÷���nUnitSize
        //����ļ��������򷵻�NULL
        unsigned char* GetFileBlockFromCache(_tstring strFileName, size_t& nUnitSize)
        {
            //�Ա��ص�cache�н��в���
            _tstring strUnitFileName = ConvFileName(strFileName);
            map<_tstring, FILEBLOCK>::iterator itr = m_LocalFileCacheIndex.find(strUnitFileName);
            if (itr != m_LocalFileCacheIndex.end())
            {
                nUnitSize = itr->second.nSize;
                //�����С�ı�
                if (itr->second.nRefCount == 0)
                {
                    m_UseCacheSize-=nUnitSize;
                    FILEINFO info;
                    info.strUnitFileName = strUnitFileName;
                    info.nSize = nUnitSize;
                    RemoveCacheList(info);
                }
                itr->second.nRefCount++;
                return itr->second.pData;
            }
            else
            {
                //��cache��δ�ҵ����ļ������������
                std::fstream file(_tUNICODECHAR(strUnitFileName), std::ios::in | std::ios::binary);
                if (!file.is_open())
                {
                    nUnitSize = 0;
                    return NULL;
                }

                file.seekg(0, std::ios::end);
                size_t filesize = file.tellg();

                FILEBLOCK block = {0};
                block.pData = s_Mempool.allocate(filesize+1);
                if (block.pData == NULL)
                {
                    file.close();
                    nUnitSize = 0;
                    return false;
                }

                file.seekg(0, std::ios::beg);
                file.read((char*)block.pData, static_cast<std::streamsize>(filesize));

                block.pData[filesize] = '\0';       //Ϊ�˷��㴿�ı��ļ�ʹ�ã���������һ���ֽڲ�����Ϊ���ַ���
                block.nRefCount = 1;
                block.nSize = filesize;

                file.close();

                m_LocalFileCacheIndex.insert(pair<_tstring, FILEBLOCK>(strUnitFileName, block));

                nUnitSize = filesize;
                return block.pData;
            }
        }

        //ͨ��VFS�����Լ��ļ�����ȡ�ļ����档����ֵͬ��
        unsigned char* GetFileBlockFromCache(_tstring strFileName, size_t& nUnitSize, CVFS& vfs)
        {
            _tstring strVFSFileName = ConvFileName(vfs.GetFileName());
            _tstring strUnitFileName = ConvFileName(strFileName);
            map<_tstring, map<_tstring, FILEBLOCK> >::iterator itr = m_VFSCacheIndex.find(strVFSFileName);
            if (itr != m_VFSCacheIndex.end())
            {
                //���ҵ��ڶ�������
                map<_tstring, FILEBLOCK>& cache = itr->second;
                map<_tstring, FILEBLOCK>::iterator unititr = cache.find(strUnitFileName);

                if (unititr != cache.end())
                {
                    //����ļ��Ѵ��ڣ��򷵻ص�ַ
                    nUnitSize = unititr->second.nSize;
                    if (unititr->second.nRefCount == 0)
                    {
                        m_UseCacheSize-=nUnitSize;
                        FILEINFO info;
                        info.strUnitFileName = strUnitFileName;
                        info.strVFSFileName = strVFSFileName;
                        info.nSize = nUnitSize;
                        RemoveCacheList(info);
                    }
                    unititr->second.nRefCount++;
                    return unititr->second.pData;
                }
            }

            size_t size = 0;
            if (!vfs.GetUnitLength(strFileName.c_str(), size))
            {
                return NULL;
            }

            unsigned char* pData = s_Mempool.allocate(size+1);
            if (vfs.GetUnit(strFileName.c_str(), pData, size))
            {
                pData[size] = '\0';                 //Ϊ�˷��㴿�ı��ļ�ʹ�ã���������һ���ֽڲ�����Ϊ���ַ���
                nUnitSize = size;

                FILEBLOCK block = {0};
                block.nRefCount = 1;
                block.nSize = size;
                block.pData = pData;

                //�������м���
                if (itr != m_VFSCacheIndex.end())
                {
                    map<_tstring, FILEBLOCK>& cache = itr->second;
                    cache.insert(pair<_tstring, FILEBLOCK>(strUnitFileName, block));
                }
                else
                {
                    m_VFSCacheIndex.insert(pair<_tstring, map<_tstring, FILEBLOCK> >(strVFSFileName, map<_tstring, FILEBLOCK>()));
                    map<_tstring, map<_tstring, FILEBLOCK> >::iterator itrsecond = m_VFSCacheIndex.find(strVFSFileName);
                    if (itrsecond != m_VFSCacheIndex.end())
                    {
                        map<_tstring, FILEBLOCK>& secondindex = itrsecond->second;
                        secondindex.insert(pair<_tstring, FILEBLOCK>(strUnitFileName, block));
                    }
                }
                return pData;
            }
            else
            {
                nUnitSize = 0;
                s_Mempool.deallocate(pData);
                return NULL;
            }
        }

        //�ͷ��ļ�
        bool ReleaseFileFromCache(const CVFSUnit& unit)
        {
            RefreshCache();
            _tstring strUnitFileName = ConvFileName(unit.GetUnitFileName());
            _tstring strVFSFileName = ConvFileName(unit.GetVFSFileName());

            if (strUnitFileName == _T(""))
            {
                return false;
            }

            if (strVFSFileName == _T(""))
            {
                map<_tstring, FILEBLOCK>::iterator unititr = m_LocalFileCacheIndex.find(strUnitFileName);
                if (unititr != m_LocalFileCacheIndex.end())
                {
                    unititr->second.nRefCount--;
                    if (unititr->second.nRefCount == 0)
                    {
                        m_UseCacheSize+=unititr->second.nSize;
                        FILEINFO info;
                        info.nSize = unititr->second.nSize;
                        info.strUnitFileName = strUnitFileName;
                        info.strVFSFileName = strVFSFileName;
                        AddCacheList(info);
                    }
                    return true;
                }
            }
            else
            {
                map<_tstring, map<_tstring, FILEBLOCK> >::iterator itr = m_VFSCacheIndex.find(strVFSFileName);
                if (itr != m_VFSCacheIndex.end())
                {
                    //���ҵ��ڶ�������
                    map<_tstring, FILEBLOCK>& cache = itr->second;
                    map<_tstring, FILEBLOCK>::iterator unititr = cache.find(strUnitFileName);

                    if (unititr != cache.end())
                    {
                        unititr->second.nRefCount--;
                        if (unititr->second.nRefCount == 0)
                        {
                            m_UseCacheSize+=unititr->second.nSize;
                            FILEINFO info;
                            info.nSize = unititr->second.nSize;
                            info.strUnitFileName = strUnitFileName;
                            info.strVFSFileName = strVFSFileName;
                            AddCacheList(info);
                        }
                        return true;
                    }
                }
            }
            return false;
        }

    protected:
        //ˢ�»����С�������ͷ���Щ
        void RefreshCache()
        {
            if (m_UseCacheSize < CacheSize*1024*1024)           //���ʹ���ڴ����CacheSize(CacheSize��λΪMbyte)������Cache
            {
                return;
            }
            //	return;
            size_t ReleaseCacheSize = m_UseCacheSize;
            while (m_UseCacheSize > ReleaseCacheSize/2)
            {
                FILEINFO& info = m_CacheList.front();
                if (info.strVFSFileName == _T(""))
                {
                    map<_tstring, FILEBLOCK>::iterator itr = m_LocalFileCacheIndex.find(info.strUnitFileName);
                    unsigned char* pData = itr->second.pData;
                    this->s_Mempool.deallocate(pData);
                    m_LocalFileCacheIndex.erase(itr);
                    m_UseCacheSize-=info.nSize;
                }
                else
                {
                    map<_tstring, FILEBLOCK>& secondindex = m_VFSCacheIndex.find(info.strVFSFileName)->second;
                    map<_tstring, FILEBLOCK>::iterator itr = secondindex.find(info.strUnitFileName);
                    unsigned char* pData = itr->second.pData;
                    s_Mempool.deallocate(pData);
                    secondindex.erase(itr);
                    m_UseCacheSize-=info.nSize;
                }
                m_CacheList.pop_front();
            }

        }

        //��ӵ������б���
        void AddCacheList(FILEINFO info)
        {
            m_CacheList.push_back(info);
        }

        //�ӻ����б����Ƴ�
        void RemoveCacheList(FILEINFO info)
        {
            for (list<FILEINFO>::iterator itr = m_CacheList.begin(); itr != m_CacheList.end(); itr++)
            {
                if (itr->strUnitFileName == info.strUnitFileName &&
                    itr->strVFSFileName == info.strVFSFileName &&
                    itr->nSize == info.nSize)
                {
                    m_CacheList.erase(itr);
                    break;
                }
            }
        }

    private:
        static Common::TAllocator<unsigned char, 1024*1024, 50> s_Mempool;      //�ڴ��
        map<_tstring, map<_tstring, FILEBLOCK> > m_VFSCacheIndex;               //����map����(�洢����CVFS������ļ�)
        map<_tstring, FILEBLOCK> m_LocalFileCacheIndex;                         //�����ļ���������
        list<FILEINFO> m_CacheList;                                             //���ü���Ϊ0(�ѱ�ɾ��)����
        size_t m_UseCacheSize;                                                  //��ǰCache��ռ�õĴ�С

    private:
        CUnitCache(const CUnitCache&) {}
        CUnitCache& operator = (const CUnitCache&) {}

    };

    template <unsigned int CacheSize>
    Common::TAllocator<unsigned char, 1024*1024, 50> CUnitCache<CacheSize>::s_Mempool;
};

#endif // __VFS_CACHE_H__
