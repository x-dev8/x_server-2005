/********************************************************************
    Filename:    BlockStore.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_BLOCKSTORE_H__
#define __UTILITY_BLOCKSTORE_H__

#include "MeRTLibs.h"
#include "NewWithDebug.h"

#ifdef _MT
#include <windows.h>
#endif

namespace Common
{
    class BlockStore
    {
    public:
         BlockStore(size_t blockSize, size_t blockPerBatch=100, size_t blockAlignment=4)
            : m_ppNextBlock(NULL), 
              m_blockSize((blockSize+blockAlignment-1)&(~(blockAlignment-1))), 
              m_blockPerBatch(blockPerBatch), m_blockAlignment(blockAlignment)
              //,_allocCount( 0 )
        {
    #ifdef _MT
            //�������ɶ��߳�,������
            InitializeCriticalSection( &m_cs );
    #endif
        }
        virtual ~BlockStore()
        {
            //����ڴ��������������ڴ�
            size_t iNum = m_batches.size();
            for (size_t i=0; i<iNum; ++i)
            {
                unsigned char* p = (unsigned char*)m_batches[i];
                CNewWithDebug<unsigned char>::Free( p );
                //delete [] p;
                //GlobalFree(p);
            }

    #ifdef _MT        
                //�������ɶ��߳�,������
            DeleteCriticalSection( &m_cs );
    #endif
        }


    #ifdef _MT
            //�������ɶ��߳�,������
        void Lock() { EnterCriticalSection( &m_cs ); }
        void Unlock() { LeaveCriticalSection( &m_cs ); }
    #endif

        void* AllocateBlock()
        {  
    #ifdef _MT
            //�������ɶ��߳�,������
            Lock();
    #endif

            //��������ڴ�û�����¿���һ���ڴ�
            if (m_ppNextBlock == NULL || *m_ppNextBlock == NULL)
            {
                //ȷ��T�ڴ��С,�ٸ����ڴ����ó���Ҫ����ĵ���T�ڴ���С
 //               static const size_t blockSize = (m_blockSize+m_blockAlignment-1)&(~(m_blockAlignment-1));

                //�¿�һ���ڴ�(������ڴ��ԭ���ڴ��15�ֽ�,����������ֽڶ���)
                //unsigned char* pNewBatch =  new unsigned char[m_blockPerBatch*m_blockSize+15];
                unsigned char* pNewBatch =  CNewWithDebug<unsigned char>::Alloc(m_blockPerBatch*m_blockSize+15, "BlockStore�����ڴ�");
                
                //unsigned char* pNewBatch = (unsigned char*)GlobalAlloc(NULL, m_blockPerBatch*blockSize+15);

                //��Ϊ�¿����ڴ���ԭ�����ڴ沢��������,�����Ҫ��vector������ɢ���ڴ��ָ��
                m_batches.push_back(pNewBatch);

                //��ʱ����������
                #pragma warning(disable : 4311 4312)
                //16�ֽڶ���
                unsigned char* pAlignedPtr =(unsigned char*)((unsigned int)(pNewBatch+15)&(~15));

                //������Ԫ�ؿ��Է��õĵ�ַȷ��
                m_ppNextBlock = (unsigned char**)pAlignedPtr;
                for (size_t i=0; i<m_blockPerBatch-1; ++i)
                {
                    *((unsigned int*)(pAlignedPtr + i*m_blockSize)) = (unsigned int)(pAlignedPtr + (i+1)*m_blockSize);
                }
                *((unsigned int*)(pAlignedPtr + (m_blockPerBatch-1)*m_blockSize)) = (unsigned int)0;
            }

            unsigned char* pBlock = (unsigned char*)m_ppNextBlock;
            m_ppNextBlock = (unsigned char**)*m_ppNextBlock;
#ifdef _MT
            //�������ɶ��߳�,������
            Unlock();
#endif
            //if ( pBlock != NULL )
            //{ ++_allocCount; }
            return (void*)pBlock;
        }

        void ReleaseBlock(void* pBlock)
        {
#ifdef _MT
            //�������ɶ��߳�,������
            Lock();
#endif
            if( pBlock )
            {
                //��ʱ����������
                #pragma warning(disable : 4311)
                *((unsigned int*)pBlock) = (unsigned int)m_ppNextBlock;
                m_ppNextBlock = (unsigned char**)((unsigned char*)pBlock);

                //if ( _allocCount > 0 )
                //{ --_allocCount; }
            }
#ifdef _MT
            //�������ɶ��߳�,������
            Unlock();
#endif
        }

        //size_t GetAllocCount() { return _allocCount; }

    private:
        explicit BlockStore() : m_ppNextBlock(NULL), m_blockSize(1),  m_blockPerBatch(100), m_blockAlignment(4)
        {
    #ifdef _MT
            //�������ɶ��߳�,������
            InitializeCriticalSection( &m_cs );
    #endif              
        }

        explicit BlockStore(const BlockStore&)
            : m_ppNextBlock(NULL), 
              m_blockSize(1), 
              m_blockPerBatch(100),
              m_blockAlignment(4)
        {
    #ifdef _MT
            //�������ɶ��߳�,������
            InitializeCriticalSection( &m_cs );
    #endif
        }
        BlockStore& operator=(const BlockStore&){}

    public:

        typedef std::vector<unsigned char*> BatchPtrVector;

        unsigned char** m_ppNextBlock   ; // ָ���ڴ��Ԫ����һ��λ�õ�ָ��
        BatchPtrVector  m_batches       ; // ������ɢ���ڴ��ָ��
        const size_t    m_blockSize     ; // ÿ������ṹ���ڴ���ֽ���
        const size_t    m_blockPerBatch ; // ÿ��������ڴ������
        const size_t    m_blockAlignment; // �ڴ�����ֽ���
        //size_t          _allocCount     ; // ��������

#ifdef _MT
        //�������ɶ��߳�,������
        CRITICAL_SECTION    m_cs;
#endif
    };

}

#endif // __UTILITY_BLOCKSTORE_H__