#pragma once

class MEFOUNDATION_ENTRY MeMemoryTracker
{
public:
	struct MeMemInfo
	{
		MeMemInfo(){
			memset( m_acFile, 0, sizeof( m_acFile ) );
			memset( m_acFunction, 0, sizeof( m_acFunction ) );
			m_nLine = 0;
			m_dwBornTime = 0;
		}
		MeMemInfo( const char* pcFile, int nLine, const char* pcFunc, __time64_t dwBornTime )
		{
			strcpy_s( m_acFile, MAX_PATH, pcFile );
			strcpy_s( m_acFunction, MAX_PATH, pcFunc );
			m_nLine = nLine;
			m_dwBornTime = dwBornTime;
		}
		__time64_t m_dwBornTime;
		char m_acFile[MAX_PATH];
		int  m_nLine;
		char m_acFunction[MAX_PATH];
	};
public:	
	static MeMemoryTracker* Instance();
	static void Init();
	static void Shutdown();

public:
	void Allocate( void* pMem, const char* pcFile, int nLine, const char* pcFunction );
	void Deallocate( void* pMem );
	void OutputMemInfo();
	
protected:
	static MeMemoryTracker* ms_This;
	static __time64_t ms_dwInitTime;
private:
	MeMemoryTracker() : m_uiTotalObjectCount(0){
		::InitializeCriticalSection( &m_csAccess );
	}
	~MeMemoryTracker(){
		::DeleteCriticalSection( &m_csAccess );
	}
	typedef std::map< DWORD, MeMemInfo > MeMemInfoContainer; 
	MeMemInfoContainer m_MemInfos;
	unsigned int m_uiTotalObjectCount;
	CRITICAL_SECTION m_csAccess;
};