/********************************************************************
	Filename: 	NewWithDebug.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_NEWWITHDEBUG_H__
#define __UTILITY_NEWWITHDEBUG_H__

#include "MeRTLibs.h"
//#include "Mutex.h"
using std::map;
using std::pair;

//ÿ����;���ڴ�ʹ����Ϣ
typedef struct AllocMemoryInfo
{
    unsigned int nExistCount;   // ��ǰδ�ͷŵ��������
    unsigned int nAllocCount;   // ����;���ڴ湲�����˶��ٴ�
    unsigned int nAllUseMemory; // ����;���ڴ���ռ�õ��ڴ��С
}ALLOCMEMORYINFO;

typedef struct PointerInfo
{
    unsigned int nSize;
    unsigned int nAllocCount; // ��ָ�������������͵ĸ����������ж�ɾ��ʱ���� delete p ���� delete [] p��
    const char*  szNote;      // ��ָ��������;
}POINTERINFO;

extern map<const char*, ALLOCMEMORYINFO>& GetAllocInfo();
extern map<void*, POINTERINFO>&           GetPointerInfo();
//extern CSemiAutoIntLock&                  GetAutoIntLock();

//ʹ���߱���ʹ��CNewWithDebug<typename>::Alloc
template <typename T>
class CNewWithDebug
{
public:
    CNewWithDebug();
    virtual ~CNewWithDebug();

    static T* Alloc (unsigned int nCount = 1, const char* szNote = NULL)
    {
        //��׼c++�����new���飬��ʹ����Ԫ��Ϊ0��Ҳ������Ϊ1
        //new int[0] ��ͬ�� new int[1];
        if (nCount == 0)
        {
            nCount = 1;
        }

        T* p = NULL;
        if (nCount > 1)
        {
            p = new T[nCount];
        }
        else
        {
            p = new T;
        }

        POINTERINFO pinfo = {0};
        pinfo.nAllocCount = nCount;
        pinfo.nSize = sizeof(T)*nCount;
        pinfo.szNote = szNote;

#ifdef _MT
//        CSALocker locker(GetAutoIntLock());
#endif
        GetPointerInfo()[p] = pinfo;

        map<const char*, ALLOCMEMORYINFO>::iterator itr = GetAllocInfo().find(szNote);

        if (itr == GetAllocInfo().end())
        {
            ALLOCMEMORYINFO ainfo = {0};
            ainfo.nAllocCount = 1;
            ainfo.nExistCount = 1;
            ainfo.nAllUseMemory += pinfo.nSize;
            GetAllocInfo().insert(pair<const char*, ALLOCMEMORYINFO>(szNote, ainfo));
        }
        else
        {
            itr->second.nAllocCount ++;
            itr->second.nExistCount ++;
            itr->second.nAllUseMemory += pinfo.nSize;
        }

        return p;
    }

    static void Free(T* p)
    {
        unsigned int nCount;
#ifdef _MT
        {
//        CSALocker locker(GetAutoIntLock());
#endif
        if (p == NULL)
        {
            return;
        }
        map<void*, POINTERINFO>::iterator itr = GetPointerInfo().find(p);
        if (itr != GetPointerInfo().end())
        {
            map<const char*, ALLOCMEMORYINFO>::iterator allinfoitr = GetAllocInfo().find(itr->second.szNote);
            if (allinfoitr != GetAllocInfo().end())
            {
                allinfoitr->second.nExistCount --;
                allinfoitr->second.nAllUseMemory -= itr->second.nSize;
            }
            nCount = itr->second.nAllocCount;
            GetPointerInfo().erase(itr);
        }
        else
        {
            return;
        }
#ifdef _MT
        }
#endif
        if (nCount >1)
        {
            delete [] p;
        }
        else
        {
            delete p;
        }
    }
};

//����ʹ���ڴ���Ϣ������ļ�
void OutHeapMemoryInfoToFile(const char* szFileName);

#endif // __UTILITY_NEWWITHDEBUG_H__
