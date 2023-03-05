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

    template <unsigned int CacheSize>           //Unit类型，缓冲大小
    class CUnitCache
    {
        //文件块
        typedef struct tagFileBlock
        {
            size_t nSize;                       //长度
            unsigned int nRefCount;             //引用计数
            unsigned char* pData;               //内存数据块地址
        }FILEBLOCK;

        //文件信息(用于缓存释放)
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
            //释放全部内存块
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
        //通过文件名获取文件缓存，返回内存地址指针以及通过引用返回nUnitSize
        //如果文件不存在则返回NULL
        unsigned char* GetFileBlockFromCache(_tstring strFileName, size_t& nUnitSize)
        {
            //对本地的cache中进行查找
            _tstring strUnitFileName = ConvFileName(strFileName);
            map<_tstring, FILEBLOCK>::iterator itr = m_LocalFileCacheIndex.find(strUnitFileName);
            if (itr != m_LocalFileCacheIndex.end())
            {
                nUnitSize = itr->second.nSize;
                //缓存大小改变
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
                //当cache中未找到此文件，则进行载入
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

                block.pData[filesize] = '\0';       //为了方便纯文本文件使用，最后多申请一个字节并且置为空字符。
                block.nRefCount = 1;
                block.nSize = filesize;

                file.close();

                m_LocalFileCacheIndex.insert(pair<_tstring, FILEBLOCK>(strUnitFileName, block));

                nUnitSize = filesize;
                return block.pData;
            }
        }

        //通过VFS对象以及文件名获取文件缓存。返回值同上
        unsigned char* GetFileBlockFromCache(_tstring strFileName, size_t& nUnitSize, CVFS& vfs)
        {
            _tstring strVFSFileName = ConvFileName(vfs.GetFileName());
            _tstring strUnitFileName = ConvFileName(strFileName);
            map<_tstring, map<_tstring, FILEBLOCK> >::iterator itr = m_VFSCacheIndex.find(strVFSFileName);
            if (itr != m_VFSCacheIndex.end())
            {
                //查找到第二级索引
                map<_tstring, FILEBLOCK>& cache = itr->second;
                map<_tstring, FILEBLOCK>::iterator unititr = cache.find(strUnitFileName);

                if (unititr != cache.end())
                {
                    //如果文件已存在，则返回地址
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
                pData[size] = '\0';                 //为了方便纯文本文件使用，最后多申请一个字节并且置为空字符。
                nUnitSize = size;

                FILEBLOCK block = {0};
                block.nRefCount = 1;
                block.nSize = size;
                block.pData = pData;

                //在索引中加入
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

        //释放文件
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
                    //查找到第二级索引
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
        //刷新缓存大小，决定释放哪些
        void RefreshCache()
        {
            if (m_UseCacheSize < CacheSize*1024*1024)           //如果使用内存大于CacheSize(CacheSize单位为Mbyte)则清理Cache
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

        //添加到缓冲列表中
        void AddCacheList(FILEINFO info)
        {
            m_CacheList.push_back(info);
        }

        //从缓存列表中移除
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
        static Common::TAllocator<unsigned char, 1024*1024, 50> s_Mempool;      //内存池
        map<_tstring, map<_tstring, FILEBLOCK> > m_VFSCacheIndex;               //二级map索引(存储所有CVFS管理的文件)
        map<_tstring, FILEBLOCK> m_LocalFileCacheIndex;                         //本地文件缓存索引
        list<FILEINFO> m_CacheList;                                             //引用计数为0(已被删除)队列
        size_t m_UseCacheSize;                                                  //当前Cache所占用的大小

    private:
        CUnitCache(const CUnitCache&) {}
        CUnitCache& operator = (const CUnitCache&) {}

    };

    template <unsigned int CacheSize>
    Common::TAllocator<unsigned char, 1024*1024, 50> CUnitCache<CacheSize>::s_Mempool;
};

#endif // __VFS_CACHE_H__
