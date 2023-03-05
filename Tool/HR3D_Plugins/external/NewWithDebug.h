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

//每个用途的内存使用信息
typedef struct AllocMemoryInfo
{
    unsigned int nExistCount;   // 当前未释放的申请次数
    unsigned int nAllocCount;   // 此用途的内存共申请了多少次
    unsigned int nAllUseMemory; // 此用途的内存所占用的内存大小
}ALLOCMEMORYINFO;

typedef struct PointerInfo
{
    unsigned int nSize;
    unsigned int nAllocCount; // 此指针申请的相关类型的个数（用于判断删除时是用 delete p 还是 delete [] p）
    const char*  szNote;      // 此指针的相关用途
}POINTERINFO;

extern map<const char*, ALLOCMEMORYINFO>& GetAllocInfo();
extern map<void*, POINTERINFO>&           GetPointerInfo();
//extern CSemiAutoIntLock&                  GetAutoIntLock();

//使用者必须使用CNewWithDebug<typename>::Alloc
template <typename T>
class CNewWithDebug
{
public:
    CNewWithDebug();
    virtual ~CNewWithDebug();

    static T* Alloc (unsigned int nCount = 1, const char* szNote = NULL)
    {
        //标准c++中如果new数组，即使数组元素为0，也会申请为1
        //new int[0] 等同于 new int[1];
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

//将堆使用内存信息输出至文件
void OutHeapMemoryInfoToFile(const char* szFileName);

#endif // __UTILITY_NEWWITHDEBUG_H__
