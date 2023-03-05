#include "MeRTLibs.h"
#include "MeFoundation/MeAllocatedObject.h"

#ifdef _DEBUG

void CMeMemoryDetailDump::DumpDetailInfo()
{
	char szBuf[2560] = {0};
	for (std::multimap<std::string,int>::iterator iter = m_MemoryDetail.begin();iter != m_MemoryDetail.end();++iter)
	{
		_snprintf( szBuf, 2559, "%d\t = %s\n", iter->second,iter->first.c_str() );
		OutputDebugString( szBuf );
	}
#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NEDPOOLING
	GeneralAllocPolicy::DumpPoolmallinfo();
#endif
}
#endif


