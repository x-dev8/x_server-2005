//#include "MeFoundation/MeFoundationPCH.h"
//#include "MeFoundation/MeNedAllocation.h"
//#pragma warning( push, 0 )
//#include <MeFoundation/nedmalloc/nedmalloc.c>
//#pragma warning( pop )
//
//#include "MeFoundation/MeMemoryNedPooling.h"
//#include "MeFoundation/MeMemoryTracker.h"
//
//#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NEDPOOLING
//
//
//	namespace _NedPoolingIntern
//	{
//		const size_t s_poolCount = 64; // Needs to be greater than 4
//		const size_t s_MaxSupportSize = ((s_poolCount - 3)<<4) + 1; 
//		void* s_poolFootprint = reinterpret_cast<void*>(0xBB1AA45A);
//		nedalloc::nedpool* s_pools[s_poolCount + 1] = { 0 };
//		nedalloc::nedpool* s_poolsAligned[s_poolCount + 1] = { 0 };
//
//		size_t poolIDFromSize(size_t a_reqSize)
//		{
//			// Requests size 16 or smaller are allocated at a 4 byte granularity.
//			// Requests size 17 or larger are allocated at a 16 byte granularity.
//			// With a s_poolCount of 14, requests size s_MaxSupportSize(177) or larger go in the default pool.
//
//			// spreadsheet style =IF(B35<=16; FLOOR((B35-1)/4;1); MIN(FLOOR((B35-1)/16; 1) + 3; 14))
//
//			size_t poolID = 0;
//
//			if (a_reqSize > 0)
//			{
//				if (a_reqSize <= 16)
//				{
//					poolID = (a_reqSize - 1) >> 2;
//				}
//				else
//				{
//					poolID = std::min<size_t>(((a_reqSize - 1) >> 4) + 3, s_poolCount);
//				}
//			}
//
//			return poolID;
//		}
//
//		void* internalAlloc(size_t a_reqSize)
//		{
//			size_t poolID = poolIDFromSize(a_reqSize);
//			nedalloc::nedpool* pool(0); // A pool pointer of 0 means the default pool.
//
//			if (poolID < s_poolCount)
//			{
//				if (s_pools[poolID] == 0)
//				{
//					// Init pool if first use
//
//					s_pools[poolID] = nedalloc::nedcreatepool(0, 8);
//					nedalloc::nedpsetvalue(s_pools[poolID], s_poolFootprint); // All pools are stamped with a footprint
//				}
//
//				pool = s_pools[poolID];
//// 				return nedalloc::nedpmalloc(pool, a_reqSize);
//// 			}
////  			return malloc(a_reqSize);//当size大于s_MaxSupportSize直接使用系统的malloc避免default pool不能被及时缩减
//			}
//			return nedalloc::nedpmalloc(pool, a_reqSize);
//		}
//
//		void* internalAllocAligned(size_t a_align, size_t a_reqSize)
//		{
//			size_t poolID = poolIDFromSize(a_reqSize);
//			nedalloc::nedpool* pool(0); // A pool pointer of 0 means the default pool.
//
//			if (poolID < s_poolCount)
//			{
//				if (s_poolsAligned[poolID] == 0)
//				{
//					// Init pool if first use
//
//					s_poolsAligned[poolID] = nedalloc::nedcreatepool(0, 8);
//					nedalloc::nedpsetvalue(s_poolsAligned[poolID], s_poolFootprint); // All pools are stamped with a footprint
//				}
//
//				pool = s_poolsAligned[poolID];
//			}
//
//			return nedalloc::nedpmemalign(pool, a_align, a_reqSize);
//		}
//
//		void internalFree(void* a_mem)
//		{
//			if (a_mem)
//			{
//				nedalloc::nedpool* pool(0);
//
//				// nedalloc lets us get the pool pointer from the memory pointer
//				void* footprint = nedalloc::nedgetvalue(&pool, a_mem);
//
//				// Check footprint
//				if (footprint == s_poolFootprint)
//				{
//					// If we allocated the pool, deallocate from this pool...
//					nedalloc::nedpfree(pool, a_mem);
//				}
//				else
//				{
//// 					free(a_mem);
//					// ...otherwise let nedalloc handle it.
//					nedalloc::nedfree(a_mem);
//				}
//			}
//		}
//		void DumpPoolmallinfo()
//		{
//			char cTemp[1024]= {0};
//			for (int i = 0; i < s_poolCount + 1; ++i)
//			{
//				if (s_pools[i])
//				{
//					mallinfo info = nedalloc::nedpmallinfo(s_pools[i]);
//					sprintf_s(cTemp,1024,"Pool %d:\n %d\t:non-mmapped space allocated from system\n %d\t:total free space\n %d\t:always 0\n %d\t:space in mmapped regions\n %d\t:releasable space\n %d\t:number of free chunks\n %d\t:total allocated space\n %d\t:maximum total allocated space\n"
//						,i,info.arena
//						,info.fordblks
//						,info.fsmblks
//						,info.hblkhd
//						,info.keepcost
//						,info.ordblks
//						,info.uordblks
//						,info.usmblks);
//					OutputDebugString( cTemp );
//				}
//			}
//			mallinfo info = nedalloc::nedpmallinfo(0);
//			sprintf_s(cTemp,1024,"Default Pool:\n %d\t:non-mmapped space allocated from system\n %d\t:total free space\n %d\t:always 0\n %d\t:space in mmapped regions\n %d\t:releasable space\n %d\t:number of free chunks\n %d\t:total allocated space\n %d\t:maximum total allocated space\n"
//				,info.arena
//				,info.fordblks
//				,info.fsmblks
//				,info.hblkhd
//				,info.keepcost
//				,info.ordblks
//				,info.uordblks
//				,info.usmblks);
//			OutputDebugString( cTemp );
//		}
//	}
//
//	//---------------------------------------------------------------------
//	void* NedPoolingImpl::allocBytes(size_t count, 
//		const char* file, int line, const char* func)
//	{
//		void* ptr = _NedPoolingIntern::internalAlloc(count);
//#ifdef _DEBUG
//		MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
//#else
//		// avoid unused params warning
//		file = func = "";
//        line = 0;
//#endif
//		return ptr;
//	}
//	//---------------------------------------------------------------------
//	void NedPoolingImpl::deallocBytes(void* ptr)
//	{
//		// deal with null
//		if (!ptr)
//			return;
//#ifdef _DEBUG
//		MeMemoryTracker::Instance()->Deallocate( ptr );
//#endif
//		_NedPoolingIntern::internalFree(ptr);
//	}
//	//---------------------------------------------------------------------
//	void* NedPoolingImpl::allocBytesAligned(size_t align, size_t count, 
//		const char* file, int line, const char* func)
//	{
//		// default to platform SIMD alignment if none specified
//		void* ptr =  align ? _NedPoolingIntern::internalAllocAligned(align, count)
//			: _NedPoolingIntern::internalAllocAligned(ME_SIMD_ALIGNMENT, count);
//#ifdef _DEBUG
//		MeMemoryTracker::Instance()->Allocate( ptr, file, line, func );	
//#else
//		// avoid unused params warning
//		file = func = "";
//        line = 0;
//#endif
//		return ptr;
//	}
//	//---------------------------------------------------------------------
//	void NedPoolingImpl::deallocBytesAligned(size_t align, void* ptr)
//	{
//		// deal with null
//		if (!ptr)
//			return;
//#ifdef _DEBUG
//		MeMemoryTracker::Instance()->Deallocate( ptr );
//#endif
//		_NedPoolingIntern::internalFree(ptr);
//	}
//
//#ifdef _DEBUG
//	void NedPoolingImpl::DumpPoolmallinfo( )
//	{
//		_NedPoolingIntern::DumpPoolmallinfo();
//	}
//#endif
//
//
//#endif
//
//