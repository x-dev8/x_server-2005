#include "MeFoundation/MeLoopThread.h"
#include "MeFoundation/MeLoopThreadMan.h"
#include "MeFoundation/MeLoopThreadProcedure.h"
#include "MeFoundation/MeFoundationPCH.h"
#include "MeAudio/SoundFileManager.h"
#include "FuncPerformanceLog.h"
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "MeFoundation/MeThread.h"
#include "MeAudio/MeAudio.h"
#include "Me3d/Global.h"

#define ClearUselessSoundFileInMemoryRate 60000			//将每次清理内存中声音的间隔设置成60秒

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
// #ifdef _DEBUG
// #define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
// #ifndef _NEW_SW
// #define _NEW_SW				new(_NORMAL_BLOCK, __FILE__, __LINE__)
// #endif
// #ifndef new
// #define new _NEW_SW
// #endif
// #endif

// static CSoundFileManager gs_SoundManager;
using namespace std;

bool LoadFileIntoMemory( const char* pName, void** ppBuff, int* pLength )
{
    std::string strLowerRelativePath;
    GetLowerRelativePath( pName, strLowerRelativePath );
    std::string strFullFileName = GetRootPath();
    strFullFileName.append( "\\" );
    strFullFileName.append( strLowerRelativePath.c_str() );

	f_Handle* pFile = packet_namespace::w_fopen( strFullFileName.c_str(), "rb" );
	if( pFile )
	{
		packet_namespace::w_fseek( pFile, 0, SEEK_END );
		int nLength = packet_namespace::w_ftell( pFile );
		packet_namespace::w_fseek( pFile, 0, SEEK_SET );

        if( nLength > 0 )
        {
            *ppBuff = new BYTE[ nLength ];
            if( *ppBuff )
            {
                packet_namespace::w_fread( *ppBuff, nLength, 1, pFile );
                *pLength = nLength;
            }
        }
		packet_namespace::w_fclose( pFile );
	}

	return ( pFile && ( *ppBuff ) );
}

class MultiSoundReq : public MeLoopThreadReq
{
public:
	MultiSoundReq()
		:m_pSoundCache(NULL)
	{m_nObjectType = 1000;}
	virtual bool ProcessInThread( bool bFailed = false ){return true;}
	virtual void Process()
	{
		GetSoundMgr()->PlayReadySound(m_szFileName,m_pSoundCache);
	}
	virtual void Destroy(){;}
	CSoundFileManager::SoundMemoryCache* m_pSoundCache;
};

class SoundLoadProcedure : public MeLoopThreadProcedure
{
protected:
	virtual bool LoadMexFromReq2( MeLoopThreadReq* pReq )
	{
		MultiSoundReq* pSoundReq = dynamic_cast<MultiSoundReq*>(pReq);
		if (pSoundReq)
		{
			void *pBuff = 0;
			int nLength = 0;

			if( LoadFileIntoMemory( pReq->m_szFileName, &pBuff, &nLength) )
			{
				CSoundFileManager::SoundMemoryCache* pSoundCache = new CSoundFileManager::SoundMemoryCache;
				pSoundCache->pBuffer = pBuff;
				pSoundCache->nSize = nLength;
				pSoundReq->m_pSoundCache = pSoundCache;
			}
		}
		return true;
	}
	virtual void MainThreadProcess()
	{
		if (!TryEnterCriticalSection( &m_MexLoadingCS ))
		{
			return;
		}
		for( std::list<MeLoopThreadReq*>::iterator iter = m_MexLoadingReqsCache.begin(); iter != m_MexLoadingReqsCache.end(); ++iter )
		{
			MeLoopThreadReq* req = *iter;
			MultiSoundReq* pPlayerReq = dynamic_cast< MultiSoundReq* >( req );
			bool bInBack = false;
			if(( req->m_szFileName && strcmp( req->m_szFileName, "" ) != 0 )  &&  m_MexBackListString.find( req->m_szFileName ) != m_MexBackListString.end() )
			{
				bInBack = true;
			}
			m_MexLoadingReqs.push_back( req );
		}
		if( !m_MexLoadingReqs.empty() )
			SetEvent( m_hMexLoadingEvent );

		m_MexLoadingReqsCache.clear();



		if (m_MexLoadingAcks.empty())
		{
			LeaveCriticalSection( &m_MexLoadingCS );
			return;
		}

		// 每次对1个人物进行换装处理
		int count = m_MexLoadingAcks.size();
		for(int i=0; i<count; i++ )
		{
			if( m_MexLoadingAcks.empty() )
				break;
			MeLoopThreadReq* pReq = m_MexLoadingAcks.front();
			if( pReq  )
			{
				pReq->Process();
				pReq->Destroy();	
			}	
			m_MexLoadingAcks.pop_front();
			MeDelete pReq;
			pReq = 0;
		}
		LeaveCriticalSection( &m_MexLoadingCS );

	}
	virtual void ClearAckList()
	{

	}
protected:
	// store string list
	typedef std::map< std::string, bool > MexBackListStrings;
	MexBackListStrings m_MexBackListString;

};

CSoundFileManager* GetSoundMgr()
{
	return CSoundFileManager::Instance();
}

CSoundFileManager::CSoundFileManager()
{
	m_dwLastClearSoundFileInMemoryTime = HQ_TimeGetTime();
	MeLoopThread* pkSoundLoadingThread = MeLoopThread::CreateThread(MeNew SoundLoadProcedure,1000 );	
	MeLoopThreadMan::Instance()->StartThreads( pkSoundLoadingThread );

}

CSoundFileManager::~CSoundFileManager()
{
	Destroy();
	m_SoundFileFinder.Destroy();
	m_SoundFileList.clear();
}

void CSoundFileManager::PlayReadySound( const char* pszFilename,SoundMemoryCache* pCache )
{
	assert(pszFilename);
	std::string strLowerRelativePath;
	GetLowerRelativePath( pszFilename, strLowerRelativePath );

	if( pCache )
	{
		SoundMemoryCache* pFound = ( SoundMemoryCache* )m_SoundFileFinder.GetDstByName( strLowerRelativePath.c_str() );
		if( pFound )
		{//重复了，连续发送两次加载需求的话，有可能重复，删掉后来的那个就好了
			delete pCache;
		}
		else
		{
			SoundFile soundfile;
			soundfile.dwFileID = m_SoundFileFinder.Register( strLowerRelativePath.c_str(), pCache );
			strcpy( soundfile.szFileName, strLowerRelativePath.c_str() );  
			m_SoundFileList.push_back( soundfile );
		}
	}

	for( std::list<SUnreadyPlayReq*>::iterator iter = mUnreadyPlayReqList.begin(); iter != mUnreadyPlayReqList.end(); ++iter )
	{
		if( ( *iter )->m_FileName == strLowerRelativePath )
		{
			if( pCache )
			{
				if( eMusicUnready == ( *iter )->GetType() )
				{
					if( GMusic.m_IsStop )
					{
						break;
					}
					SMusicUnreadyPlayReq* pReq = ( SMusicUnreadyPlayReq* )( *iter );
// 					bool isPause = (GMusic.m_IsPaused);
					//GMusic已经处理了paused时候播放声音的状况，这里不再特殊处理了
					GMusic.PlayMusic( pszFilename, pReq->bLoop, pReq->bFade );
// 					if (isPause)
// 					{
// 						GMusic.Paused(true);
// 					}
				}
				else
				{
					if (GSound.m_IsStop)
					{
						break;
					}
					SSoundUnreadyPlayReq* pReq = (SSoundUnreadyPlayReq*)(*iter);
					bool isPause = (GSound.m_IsPaused);
					if (isPause)
					{
						GSound.Paused(false);
					}
					GSound.PlaySound(pszFilename,pReq->bLoop,&pReq->vPos,pReq->fMinDistance,pReq->fMaxDistance);
					if (isPause)
					{
						GSound.Paused(true);
					}
					GSound.SetVolume(GSound.m_fSoundVal);
				}
			}
			MeDelete (*iter);
			mUnreadyPlayReqList.erase(iter);
			break;
		}
	}
}

void CSoundFileManager::AddUnreadyPlayReq( SUnreadyPlayReq* pReq )
{
	mUnreadyPlayReqList.push_back(pReq);
}

void CSoundFileManager::ClearUselessSoundFileInMemory()
{
	guardfunc;
	list<SoundFile>::iterator itNextSoundFile;

	////////////////////////////////////
	for( list<SoundFile>::iterator itSoundFile = m_SoundFileList.begin(); itSoundFile != m_SoundFileList.end(); )
	{
		itNextSoundFile = itSoundFile;
		itNextSoundFile++;
		SoundFile& sf = *itSoundFile;

		SoundMemoryCache* pFound = (SoundMemoryCache*)m_SoundFileFinder.GetDstByName( sf.szFileName );
		if( pFound )
		{
			if( pFound->nUsedCount < 6 && HQ_TimeGetTime() - pFound->dwLastUsedTime > 60000 )
			{
				//清除使用次数少，而且6分钟内都不用的音效
				if( pFound->pBuffer )
				{
					delete[] pFound->pBuffer;
				}
				delete pFound;
				pFound = NULL;
				m_SoundFileFinder.UnRegister( sf.szFileName );

				m_SoundFileList.erase( itSoundFile );
				itSoundFile = itNextSoundFile;
				continue;
			}
			else if( HQ_TimeGetTime() - pFound->dwLastUsedTime > 300000 )
			{
				//清除半个小时都不用的音效
				if( pFound->pBuffer )
				{
					delete[] pFound->pBuffer;
				}
				delete pFound;
				pFound = NULL;
				m_SoundFileFinder.UnRegister( sf.szFileName );

				m_SoundFileList.erase( itSoundFile );
				itSoundFile = itNextSoundFile;
				continue;
			}
		}
		else
		{
			m_SoundFileList.erase( itSoundFile );
			itSoundFile = itNextSoundFile;
			continue;
		}

		itSoundFile = itNextSoundFile;
	}
	unguard;
}

void CSoundFileManager::LoadSoundFileToMemory( const char* pszFilename )
{
	guardfunc;
    std::string strLowerRelativePath;
    GetLowerRelativePath( pszFilename, strLowerRelativePath );

	if( HQ_TimeGetTime() - m_dwLastClearSoundFileInMemoryTime > ClearUselessSoundFileInMemoryRate )
	{
		// TEMPORARY COMMENT THIS LINE. -- 2008-8-8 ZJJ.
		//ClearUselessSoundFileInMemory();
		m_dwLastClearSoundFileInMemoryTime = HQ_TimeGetTime();
	}

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	SoundMemoryCache* pFound = ( SoundMemoryCache* )m_SoundFileFinder.GetDstByName( strLowerRelativePath.c_str() );
	if( pFound )
	{
		return;
	}

	void *pBuff = 0;
	int nLength = 0;

	if( LoadFileIntoMemory( strLowerRelativePath.c_str(), &pBuff, &nLength ) )
	{
		SoundMemoryCache* pSoundMemoryCache = new SoundMemoryCache;
		pSoundMemoryCache->pBuffer = pBuff;
		pSoundMemoryCache->nSize = nLength;

		SoundFile soundfile;
		soundfile.dwFileID = m_SoundFileFinder.Register( strLowerRelativePath.c_str(), pSoundMemoryCache );
		strcpy( soundfile.szFileName, strLowerRelativePath.c_str() );  
		m_SoundFileList.push_back( soundfile );
	}
	unguard;
}

BOOL CSoundFileManager::GetSoundFileFromMemory( const char* pszFilename, void** pBuffer, int* nSize )
{
	guardfunc;
    std::string strLowerRelativePath;
    GetLowerRelativePath( pszFilename, strLowerRelativePath );

	SoundMemoryCache* pFound = ( SoundMemoryCache* )m_SoundFileFinder.GetDstByName( strLowerRelativePath.c_str() );
	if( pFound )
	{
		pFound->nUsedCount++;
		pFound->dwLastUsedTime = HQ_TimeGetTime();
		*pBuffer = pFound->pBuffer;
		*nSize = pFound->nSize;
		return TRUE;
	}
	else
	{
		MultiSoundReq* pSoundReq = MeNew MultiSoundReq;
		std::string strFullFileName = GetRootPath();
		strFullFileName.append( "\\" );
		strFullFileName.append( strLowerRelativePath.c_str() );
		strcpy_s( pSoundReq->m_szFileName, MAX_PATH - 1, strFullFileName.c_str() );
		MeLoopThreadMan::Instance()->PostMexLoadingReq( pSoundReq );
		return FALSE;
	}
	return FALSE;
	unguard;
}

void CSoundFileManager::Destroy()
{
	guardfunc;
	list<SoundFile>::iterator itNextSoundFile;

	////////////////////////////////////
	for( list<SoundFile>::iterator itSoundFile = m_SoundFileList.begin(); itSoundFile != m_SoundFileList.end(); )
	{
		itNextSoundFile = itSoundFile;
		itNextSoundFile++;
		SoundFile& sf = *itSoundFile;
		SoundMemoryCache* pFound = (SoundMemoryCache*)m_SoundFileFinder.GetDstByName( sf.szFileName );

		if( pFound )
		{
			if( pFound->pBuffer )
			{
				delete[] pFound->pBuffer;
                pFound->pBuffer = NULL;
			}
			delete pFound;
			pFound = NULL;
			m_SoundFileFinder.UnRegister( sf.szFileName );

			m_SoundFileList.erase( itSoundFile );
			itSoundFile = itNextSoundFile;
			continue;
		}
		else
		{
			m_SoundFileList.erase( itSoundFile );
			itSoundFile = itNextSoundFile;
			continue;
		}
	}
	for (std::list<SUnreadyPlayReq*>::iterator iter = mUnreadyPlayReqList.begin(); iter != mUnreadyPlayReqList.end();++iter)
	{
		MeDelete (*iter);
	}
	mUnreadyPlayReqList.clear();
	unguard;
}

int CSoundFileManager::GetSoundFileFinderSize()
{
	return m_SoundFileFinder.GetSize();
}

int CSoundFileManager::GetSoundFileListSize()
{
	return m_SoundFileList.size();
}

void CSoundFileManager::Release( const char* pszFilename )
{
	if (pszFilename == NULL)
	{
		return;
	}
	SoundMemoryCache* pFound = (SoundMemoryCache*)m_SoundFileFinder.GetDstByName( pszFilename );
	if( pFound )
	{
		{
			if( pFound->pBuffer )
			{
				delete[] pFound->pBuffer;
			}
			delete pFound;
			pFound = NULL;
			m_SoundFileFinder.UnRegister( pszFilename );

			for( list<SoundFile>::iterator itSoundFile = m_SoundFileList.begin(); itSoundFile != m_SoundFileList.end(); ++itSoundFile)
			{
				if (strcmp(pszFilename,(*itSoundFile).szFileName) == 0)
				{
					m_SoundFileList.erase( itSoundFile );
					break;
				}
			}
		}
	}
}