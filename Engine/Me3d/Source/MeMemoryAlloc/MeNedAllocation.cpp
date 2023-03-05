#include "Me3d/MeNedAllocation.h"
#include "Me3d/MeMemoryTracker.h"
#pragma warning( push, 0 )
#include <nedmalloc/nedmalloc.c>
#pragma warning( pop )

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