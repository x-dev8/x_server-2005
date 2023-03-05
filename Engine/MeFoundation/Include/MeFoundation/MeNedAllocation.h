#pragma once
#include "MeFoundation/MeFoundationLibType.h"
#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NED

class MEFOUNDATION_ENTRY MeNedAllocImpl
{
public:
	static void* allocBytes(size_t count, 
		const char* file, int line, const char* func);
	static void deallocBytes(void* ptr);
	static void* allocBytesAligned(size_t align, size_t count, 
		const char* file, int line, const char* func);
	static void deallocBytesAligned(size_t align, void* ptr);
protected:
	/** 
	*/
	static unsigned int ms_uiAllocatedObject;

};
class MEFOUNDATION_ENTRY MeNedAllocation
{
public:
	static inline void* allocateBytes(size_t count, 
		const char* file = 0, int line = 0, const char* func = 0)
	{
		return MeNedAllocImpl::allocBytes(count, file, line, func);
	}
	static inline void deallocateBytes(void* ptr)
	{
		MeNedAllocImpl::deallocBytes(ptr);
	}

private:
	// No instantiation
	MeNedAllocation()
	{ }
};

/**	An allocation policy for use with AllocatedObject and 
STLAllocator, which aligns memory at a given boundary (which should be
a power of 2). This is the class that actually does the allocation
and deallocation of physical memory, and is what you will want to 
provide a custom version of if you wish to change how memory is allocated.
@par
This allocation policy uses nedmalloc 
(http://nedprod.com/programs/portable/nedmalloc/index.html). 
@note
template parameter Alignment equal to zero means use default
platform dependent alignment.
*/
template <size_t Alignment = 0>
class NedAlignedAllocPolicy
{
public:
	// compile-time check alignment is available.
	typedef int IsValidAlignment
		[Alignment <= 128 && ((Alignment & (Alignment-1)) == 0) ? +1 : -1];

	static inline void* allocateBytes(size_t count, 
		const char* file = 0, int line = 0, const char* func = 0)
	{
		return MeNedAllocImpl::allocBytesAligned(Alignment, count, file, line, func);
	}

	static inline void deallocateBytes(void* ptr)
	{
		MeNedAllocImpl::deallocBytesAligned(Alignment, ptr);
	}

	/// Get the maximum size of a single allocation
// 	static inline size_t getMaxAllocationSize()
// 	{
// 		return std::numeric_limits<size_t>::max();
// 	}
private:
	// no instantiation allowed
	NedAlignedAllocPolicy()
	{ }
};

#endif //ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NED

#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_STD

class MEFOUNDATION_ENTRY MeStdAllocImpl
{
public:
	static void* allocBytes(size_t count, 
		const char* file, int line, const char* func);
	static void deallocBytes(void* ptr);
	static void* allocBytesAligned(size_t align, size_t count, 
		const char* file, int line, const char* func);
	static void deallocBytesAligned(size_t align, void* ptr);
protected:
	/** 
	*/
	static unsigned int ms_uiAllocatedObject;

};
class MEFOUNDATION_ENTRY MeStdAllocation
{
public:
	static inline void* allocateBytes(size_t count, 
		const char* file = 0, int line = 0, const char* func = 0)
	{
		return MeStdAllocImpl::allocBytes(count, file, line, func);
	}
	static inline void deallocateBytes(void* ptr)
	{
		MeStdAllocImpl::deallocBytes(ptr);
	}

private:
	// No instantiation
	MeStdAllocation()
	{ }
};

#endif //ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_STD