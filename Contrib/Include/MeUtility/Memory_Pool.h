/********************************************************************
    Filename:     Memory_Pool.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

/*
Abstract:
    提供一个简单的线程安全的内存池模板
    其中线程安全部分需要使用WIN32 API

    警告: TObject_pool只为类设计使用,所以并不需要连续内存块
    所以严禁一次性new出数组,像这样是被严格禁止的:

    class TestObject : public Common::TObject_pool<TestObject>
    new TestObject [xxx]

    正确使用方式:
    for (int i=0; i<xxx; ++i)
    {
        new TestObject;
    }

    而TAllocator则允许一次性分配连续的内存块：
    Common::TAllocator<TestObject> Allocator;
    TestObject* p = Allocator(100);
    等同于:
    TestObject* p = new TestObject[100];
*/

#ifndef __UTILITY_MEMORY_POOL_H__
#define __UTILITY_MEMORY_POOL_H__

#pragma once

#include "MeRTLibs.h"
#include "BlockStore.h"
#include "NewWithDebug.h"
#include "Mutex.h"
namespace Common
{
    /*++
    参数:
        blocksPerBatch: 每次申请的内存块大小
        blockAlignment: 机器CPU字节长度
    --*/
    template <typename T, size_t blocksPerBatch=100, size_t blockAlignment=4>
    class TObject_pool
    {
    public:
        __inline void* operator new(size_t)
        {
            return s_Store.AllocateBlock();
        }

		__inline void* operator new(size_t,int, const char *, int)
		{
			return s_Store.AllocateBlock();
		}

        __inline void operator delete(void* pBlock)
        {
            s_Store.ReleaseBlock((T*)pBlock);
        }

    //static T*   AllocateBlock()         { return s_Store.AllocateBlock(); }
    //static void ReleaseBlock(T* pBlock) { s_Store.ReleaseBlock(pBlock); }

        //static size_t GetAllocCount() { return s_Store.GetAllocCount(); }
    // 将构造函数设置成protected,使之成为一纯虚基类模板
    protected:
        TObject_pool() {}

    private:
        static BlockStore s_Store;
    };

    template<class T, size_t blocksPerBatch, size_t blockAlignment> 
    typename BlockStore TObject_pool<T, blocksPerBatch, blockAlignment>::s_Store(sizeof(T), blocksPerBatch, blockAlignment);


    //////////////////////////////////////////////////////////////////////////
    //仿STL的allocator
    //T:                需要申请内存池的类型
    //maxBlockSize:     内存池最大连续长度
    //blocksPerBatch:   内存池申请内存时一批数量
    //blockAlignment:   字节对齐长度
    template<class T, size_t maxBlockSize=4096, size_t blocksPerBatch=100, size_t blockAlignment=4>
    class TAllocator : public std::_Allocator_base<T>
    {
    public:
        //构造函数
        TAllocator()
        {
            InitMemPool();
        }
        TAllocator(const TAllocator<T>&)
        {
            InitMemPool();
        }

        virtual ~TAllocator()
        {
            DestroyMemPool();
        }

    public:

        typedef std::_Allocator_base<T> _Mybase;
        typedef typename _Mybase::value_type value_type;

        typedef value_type _FARQ *pointer;
        typedef value_type _FARQ& reference;
        typedef const value_type _FARQ *const_pointer;
        typedef const value_type _FARQ& const_reference;

        typedef _SIZT size_type;
        typedef _PDFT difference_type;

        template<class _Other>
        struct rebind
        {
            typedef TAllocator<_Other> other;
        };

        pointer address(reference _Val) const
        {
            return (&_Val);
        }

        const_pointer address(const_reference _Val) const
        {
            return (&_Val);
        }

        template<class _Other>
        TAllocator(const TAllocator<_Other>&)
        {
            InitMemPool();
        }

        template<class _Other>
        TAllocator<T>& operator=(const TAllocator<_Other>&)
        {
            return (*this);
        }

        //释放内存
        static void deallocate(pointer _Ptr, size_type)
        {
            deallocate(_Ptr);
        }
        
        static void deallocate(pointer _Ptr)
        {
            static CSemiAutoIntLock lock_cs;
            unsigned char* p = (unsigned char*)_Ptr;
            p -= blockAlignment;
            if (*p == 0xFF)
            {
                assert( false );
                CSALocker locker(lock_cs);
                for (vector<void*>::iterator itr = m_AddrList.begin();
                    itr != m_AddrList.end(); itr++ )
                {
                    if (*itr == p)
                    {
                        CNewWithDebug<unsigned char>::Free(p);
                        m_AddrList.erase(itr);
                        return;
                    }
                }
            }
            m_poollist[*p]->ReleaseBlock(p);
        }

        //申请内存
        //内存池大小在经过内存字节对齐计算后，再额外添加blockAlignment字节以维护每个申请的内存块信息
        static pointer allocate(size_type _Count)
        {
            static CSemiAutoIntLock lock_cs;
            unsigned char* p = NULL;
            if (_Count == 1 || _Count == 0)
            {
                p = (unsigned char*)m_poollist[0]->AllocateBlock();
                *p = 0x0;
                return (pointer)(p+blockAlignment);
            }

            size_t nIndex = 0;
            size_t nCount = 1;
            while (nCount < _Count)
            {
                ++nIndex;
                nCount *= 2;
            }

            if (nIndex < m_poollist.size())
            {
                p = (unsigned char*)m_poollist[nIndex]->AllocateBlock();
                *p = (unsigned char)nIndex;
                return (pointer)(p+blockAlignment);
            }

            //如果需要申请的内存块超出maxBlockSize,则交由系统分配
            //p = new unsigned char[sizeof(T)*_Count+blockAlignment];
            p = CNewWithDebug<unsigned char>::Alloc(sizeof(T)*_Count+blockAlignment, "TAllocator申请内存");
            {
                CSALocker locker(lock_cs);
                m_AddrList.push_back(p);
            }
            *p = 0xFF;
            assert( false );
            return (pointer)(p+blockAlignment);
        }

        static pointer allocate(size_type _Count, const void _FARQ*)
        {
            return (allocate(_Count));
        }

        void construct(pointer _Ptr, const T& _Val)
        {
            _Construct(_Ptr, _Val);
        }

        void destroy(pointer _Ptr)
        {
            _Destroy(_Ptr);
        }

        _SIZT max_size() const
        {
            _SIZT _Count = (_SIZT)(-1) / sizeof (T);
            return (0 < _Count ? _Count : 1);
        }

    private:
        //不允许从其他函数进行COPY构造
        TAllocator<T>& operator=(const TAllocator<T>&){}

    private:

        //初始化/释放内存池
        static void InitMemPool()
        {
            static CSemiAutoIntLock lock_cs;
            CSALocker locker(lock_cs);
            ++m_nCount;
            if (m_nCount != 1)
            {
                //引用计数，此内存池已经启用，则不再被初始化
                return;
            }
            //根据maxBlocksizee计算出需要多少个mempool
            size_t currsize = 1;
            BlockStore* pblockstore = NULL;
            while ((currsize <= maxBlockSize) || (currsize/maxBlockSize<2))
            {
                pblockstore = new BlockStore(currsize*sizeof(T)+blockAlignment, blocksPerBatch, blockAlignment);
                m_poollist.push_back(pblockstore);
                currsize *= 2;
            }
        }

        static void DestroyMemPool()
        {
            static CSemiAutoIntLock lock_cs;
            CSALocker locker(lock_cs);
            --m_nCount;
            if (m_nCount != 0)
            {
                //引用计数，如果还有使用此内存池的类，则不清除内存池
                return;
            }
            size_t nCnt = m_poollist.size();
            for (size_t i=0; i<nCnt; ++i)
            {
                delete m_poollist[i];
            }
            nCnt = m_AddrList.size();
            for (size_t i=0; i<nCnt; ++i)
            {
                CNewWithDebug<unsigned char>::Free(static_cast<unsigned char*>(m_AddrList[i]));
            }
        }

    private:
        static std::vector<BlockStore*> m_poollist;         //存放分配器中所包含不同大小内存池列表
        static std::vector<void*> m_AddrList;               //存放系统所分配的内存指针存放
        static unsigned int m_nCount;                           //初始化引用计数
    };

    template<class T, size_t maxBlockSize, size_t blocksPerBatch, size_t blockAlignment>
        std::vector<BlockStore*> TAllocator<T, maxBlockSize, blocksPerBatch, blockAlignment>::m_poollist;

    template<class T, size_t maxBlockSize, size_t blocksPerBatch, size_t blockAlignment>
        std::vector<void*> TAllocator<T, maxBlockSize, blocksPerBatch, blockAlignment>::m_AddrList;

    template<class T, size_t maxBlockSize, size_t blocksPerBatch, size_t blockAlignment>
        unsigned int TAllocator<T, maxBlockSize, blocksPerBatch, blockAlignment>::m_nCount;

};

#define INHERIT_POOL( className ) \
    public Common::TObject_pool<className>

#define INHERIT_POOL_PARAM( className, count ) \
    public Common::TObject_pool<className, count>

#define DECLARE_POOL_FUNC( className ) \
    static  className* CreateInstance() { return MES_NEW(className); } \
    virtual void       Release()        { MES_DELETE(className);     }

#define NEW_POOL( className ) \
    className::CreateInstance();

#endif // __UTILITY_MEMORY_POOL_H__ 
