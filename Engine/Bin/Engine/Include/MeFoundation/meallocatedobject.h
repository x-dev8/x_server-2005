#pragma once
#include "MeFoundation/MeMemoryAllocatorConfig.h"
#ifdef _DEBUG
#include "Singleton.h"
class MEFOUNDATION_ENTRY CMeMemoryDetailDump :public Singleton<CMeMemoryDetailDump>
{
public:
	void								AddDetail(const char* pClassType)
	{
		std::multimap<std::string,int>::iterator iter = m_MemoryDetail.find(pClassType);
		if (iter != m_MemoryDetail.end())
		{
			++iter->second;
		}
		else
		{
			m_MemoryDetail.insert(std::make_pair(pClassType, 1));
		}
	}
	void								DeleteDetail(const char* pClassType)
	{
		std::multimap<std::string,int>::iterator iter = m_MemoryDetail.find(pClassType);
		if (iter != m_MemoryDetail.end())
		{
			--iter->second ;
		}
		else
		{
			assert(0);
		}
	}
	void								DumpDetailInfo();

protected:		
	std::multimap<std::string,int>			m_MemoryDetail;
};
#endif


template <class T>
class MEFOUNDATION_ENTRY MeAllocatedObject
{
public:
	explicit MeAllocatedObject()
	{ }

	~MeAllocatedObject()
	{ }

	/// operator new, with debug line info
	void* operator new(size_t sz, const char* file, int line, const char* func)
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->AddDetail(typeid(T).name());
		if (0)
		{
			CMeMemoryDetailDump::Instance()->DumpDetailInfo();
		}
#endif
		return GeneralAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new(size_t sz)
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->AddDetail(typeid(T).name());
#endif
		return GeneralAllocPolicy::allocateBytes(sz);
	}

	/// placement operator new
	void* operator new(size_t sz, void* ptr)
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->AddDetail(typeid(T).name());
#endif
		return ptr;
	}

	/// array operator new, with debug line info
	void* operator new[] ( size_t sz, const char* file, int line, const char* func )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->AddDetail(typeid(T).name());
#endif
		return GeneralAllocPolicy::allocateBytes(sz, file, line, func);
	}

	void* operator new[] ( size_t sz )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->AddDetail(typeid(T).name());
#endif
		return GeneralAllocPolicy::allocateBytes(sz);
	}

	void operator delete( void* ptr )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->DeleteDetail(typeid(T).name());
#endif
		GeneralAllocPolicy::deallocateBytes(ptr);
	}

	// Corresponding operator for placement delete (second param same as the first)
	void operator delete( void* ptr, void* )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->DeleteDetail(typeid(T).name());
#endif
		GeneralAllocPolicy::deallocateBytes(ptr);
	}

	// only called if there is an exception in corresponding 'new'
	void operator delete( void* ptr, const char* , int , const char*  )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->DeleteDetail(typeid(T).name());
#endif
		GeneralAllocPolicy::deallocateBytes(ptr);
	}

	void operator delete[] ( void* ptr )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->DeleteDetail(typeid(T).name());
#endif
		GeneralAllocPolicy::deallocateBytes(ptr);
	}


	void operator delete[] ( void* ptr, const char* , int , const char*  )
	{
#ifdef _DEBUG
		CMeMemoryDetailDump::Instance()->DeleteDetail(typeid(T).name());
#endif
		GeneralAllocPolicy::deallocateBytes(ptr);
	}
};
//template class MeAllocatedObject<MeNedAllocation>;
// typedef MeAllocatedObject MeCommonAllocObj;
// typedef MeAllocatedObject MeStateAllocObj;
// typedef MeAllocatedObject MeReferenceAllocObj;
#define MeCommonAllocObj MeAllocatedObject
#define MeStateAllocObj MeAllocatedObject
#define MeReferenceAllocObj MeAllocatedObject

// typedef MeCommonAllocObj MeCommonAlloc;
// typedef MeStateAllocObj MeRollStateAlloc;
// typedef MeReferenceAllocObj MeRefAlloc;

#define MeCommonAlloc MeAllocatedObject
#define MeRollStateAlloc MeAllocatedObject
#define MeRefAlloc MeAllocatedObject

class MeClockTimer;
class MePerformanceTimer;
typedef MeCommonAlloc<MeClockTimer> MeClockTimerAlloc;
typedef MeCommonAlloc<MePerformanceTimer> MePerformanceTimerAlloc;
