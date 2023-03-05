#include "MeFoundation/MeFoundationPCH.h"
#include "MeFoundation/MeNedAllocation.h"
#pragma warning( push, 0 )
#include <MeFoundation/nedmalloc/nedmalloc.c>
#pragma warning( pop )

#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NED

//---------------------------------------------------------------------
unsigned int MeNedAllocImpl::ms_uiAllocatedObject = 0;
//---------------------------------------------------------------------
const unsigned char ms_ucDefaultAlignment = 4;
//---------------------------------------------------------------------
void* MeNedAllocImpl::allocBytes(size_t count, 
							   const char* file, int line, const char* func)
{
	void* ptr = nedalloc::nedmalloc(count);	
	//void* ptr = _aligned_malloc( count, ms_ucDefaultAlignment );
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
#endif //_DEBUG
	return ptr;
}
//---------------------------------------------------------------------
void MeNedAllocImpl::deallocBytes(void* ptr)
{
	// deal with null
	if (!ptr)
		return;
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Deallocate( ptr );
#endif //_DEBUG
	nedalloc::nedfree(ptr);
	//_aligned_free( ptr );
}

//---------------------------------------------------------------------
void* MeNedAllocImpl::allocBytesAligned(size_t align, size_t count, 
									  const char* file, int line, const char* func)
{
	// default to platform SIMD alignment if none specified
	void* ptr =  align ? nedalloc::nedmemalign(align, count)
		: nedalloc::nedmemalign(ME_SIMD_ALIGNMENT, count);
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
#endif //_DEBUG
	return ptr;
}
//---------------------------------------------------------------------
void MeNedAllocImpl::deallocBytesAligned(size_t align, void* ptr)
{
	// deal with null
	if (!ptr)
		return;
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Deallocate( ptr );
#endif //_DEBUG
	nedalloc::nedfree(ptr);
}

#endif //ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NED

#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_STD

//---------------------------------------------------------------------
unsigned int MeStdAllocImpl::ms_uiAllocatedObject = 0;
//---------------------------------------------------------------------
const unsigned char ms_ucDefaultAlignment = 4;
//---------------------------------------------------------------------
void* MeStdAllocImpl::allocBytes(size_t count, 
								 const char* file, int line, const char* func)
{	
	void* ptr = _aligned_malloc( count, ms_ucDefaultAlignment );
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
#endif //_DEBUG
	return ptr;
}
//---------------------------------------------------------------------
void MeStdAllocImpl::deallocBytes(void* ptr)
{
	// deal with null
	if (!ptr)
		return;
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Deallocate( ptr );
#endif //_DEBUG	
	_aligned_free( ptr );
}

//---------------------------------------------------------------------
void* MeStdAllocImpl::allocBytesAligned(size_t align, size_t count, 
										const char* file, int line, const char* func)
{
	// default to platform SIMD alignment if none specified
	void* ptr = _aligned_malloc( count, ms_ucDefaultAlignment );
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
#endif //_DEBUG
	return ptr;
}
//---------------------------------------------------------------------
void MeStdAllocImpl::deallocBytesAligned(size_t align, void* ptr)
{
	// deal with null
	if (!ptr)
		return;
#ifdef _DEBUG
	MeMemoryTracker::Instance()->Deallocate( ptr );
#endif //_DEBUG
	_aligned_free( ptr );
}

#endif //ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_STD

