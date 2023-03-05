#include "MeFoundation/MeFoundationPCH.h"
#include "MeAudio/MeAudio.h"
#include "MeAudio/SoundFileManager.h"
#include "Me3d/MathLib.h"
#include "Me3d/Global.h"
#include "FuncPerformanceLog.h"
#include <string>


//#define MAXSOUNDCHANNELS 32
//int		g_nHardware2Dchannels = MAXSOUNDCHANNELS;
//int		g_nHardware3Dchannels = MAXSOUNDCHANNELS;
//int		g_nTotalHardwarechannels = MAXSOUNDCHANNELS*2;

FMOD::System     *GAudioSystem = NULL;
FMOD::Channel    *GAudioChannel = NULL;
std::string		GRootPath;
#define MAX_MUSIC 2
#define CLAMP(var, min, max)   (((var) < (min)) ? (var) = (min) : ((var) > (max)) ? (var) = (max) : (var))





#define INTERFACE_UPDATETIME 50      // 50ms update for interface
#define DISTANCEFACTOR       1.0f    // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.



HRMusic			GMusic;
HRSound			GSound;

//
//
//
HRAUIDO_API VOID InitAudioSystem( HWND hWnd )
{	
	FMOD_RESULT       result;

	//int               key;
	unsigned int      version;

	/*
	Create a System object and initialize.
	*/
	result = FMOD::System_Create(&GAudioSystem);

	if( GAudioSystem )
	{
		//New Project
		result = GAudioSystem->getVersion( &version );
		// SoundChannel 24 MusicChannel 3
		result = GAudioSystem->init( 32, FMOD_INIT_3D_RIGHTHANDED, NULL );
		result = GAudioSystem->set3DSettings( 1.0, DISTANCEFACTOR, 1.0f );

		//int num3d = 0, num2d = 0, ntotal = 0;
		//result = GAudioSystem->getHardwareChannels( &num2d, &num3d, &ntotal );

		////if( num2d < g_nHardware2Dchannels )
		////	g_nHardware2Dchannels = num2d;

		////if( num3d < g_nHardware3Dchannels )
		////	g_nHardware3Dchannels = num3d;

		////if( ntotal < g_nTotalHardwarechannels )
		////	g_nTotalHardwarechannels = ntotal;

		//GSound.SetCurMaxHardware3Dchannels( num3d );
	}
}

HRAUIDO_API VOID UpdateAudio( DWORD dwTime )
{
	if( GAudioSystem )
	{
		try
		{
			GAudioSystem->update();
		}
		catch (...)
		{//如果发现异常，关闭声音
			GAudioSystem = NULL;
			return;
		}
		GMusic.UpDateFadeChannel( dwTime );
	}
}

HRAUIDO_API VOID DestoryAudio( )
{
	if( GAudioSystem )
	{
		try
		{
			GMusic.StopMusic();
			GSound.StopSound();
			GMusic.Destory();
			GSound.Destory();
			GAudioSystem->close();
			GAudioSystem->release();
			GAudioSystem = NULL;
		}
		catch (...)
		{//如果发现异常，关闭声音
			GAudioSystem = NULL;
			return;
		}
	}
}


HRMusic::HRMusic() :m_fSoundVal(0.125f),
m_nFadeOrder(eFrontToBack),
m_bMusicFade(FALSE),
m_IsPaused(FALSE)
,m_IsStop(FALSE)

{
	for( int i=0;i < eMaxMusic; i++ )
	{
		m_Music[i] = NULL;
		m_Channel[i] = NULL;
	}
}
struct HRPlayerState
{
	HRPlayerState()
		:szSaveName("")
		,bLoop(FALSE)
		,bFade(FALSE)
	{
	}
	std::string szSaveName;
	BOOL		bLoop;
	BOOL		bFade;
}SaveState;

int HRMusic::PlayMusic( const char* szName, BOOL bLoop, BOOL bFade )
{
	MeScopeProfileAudioFun
	DWORD time_cost = HQ_TimeGetTime();
	if( !GAudioSystem )
		return -1;
	if( !szName || *szName == '\0')
	{
		return -1;
	}

    m_bCurMusicLoop = bLoop;
    m_bCurMusicFade = bFade;

	m_IsStop = FALSE;

	std::string strLowerRelativePath;
	GetLowerRelativePath( szName, strLowerRelativePath );

	if( m_IsPaused )
	{
		SaveState.szSaveName = szName;
		SaveState.bFade = bFade;
		SaveState.bLoop = bLoop;
		return -2;
	}

	m_nSelIdx = -1;
	if( bFade )
	{
		for ( int i=0; i< eFadeMusic ; i++ )
		{//先找该音乐是不是正在播放中，如果是，选定该频道，不做fade的处理
			if( m_szMusicName[i] == strLowerRelativePath )
			{
				bool IsPlaying = false;
				if( m_Channel[i] )
				{
					m_Channel[i]->isPlaying( &IsPlaying );
				}
				if (IsPlaying)
				{
					m_nSelIdx = i;
					break;
				}
			}
		}
		if (-1== m_nSelIdx)
		{
			for ( int i=0; i< eFadeMusic ; i++ )
			{
				bool IsPlaying = false;
				if( m_Channel[i] )
				{
					m_Channel[i]->isPlaying( &IsPlaying );
				}
				if( !IsPlaying )
				{
					m_nSelIdx = i;
					break;
				}
			}
		}
		if( m_nSelIdx == -1 )
		{
			m_nSelIdx = 0;
		}
	}
	else
	{
		m_nSelIdx = ePlayMusicIdx;
	}



	if( m_szMusicName[m_nSelIdx] != strLowerRelativePath )
	{	
		if( m_Music[m_nSelIdx] )
		{
			bool bFoundDup = false;
			for ( int i=0; i< eFadeMusic ; i++ )
			{
				if (i != m_nSelIdx && m_szMusicName[m_nSelIdx] == m_szMusicName[i])
				{
					bFoundDup = true;
				}
			}
			if (!bFoundDup)
			{
				m_Music[m_nSelIdx]->release();
				GetSoundMgr()->Release(m_szMusicName[m_nSelIdx].c_str());
				m_Music[m_nSelIdx] = NULL;
			}
			m_szMusicName[m_nSelIdx].clear();
		}

		int nSize = 0;
		void* pBuffer = NULL;
		if( GetSoundMgr()->GetSoundFileFromMemory( strLowerRelativePath.c_str(), &pBuffer, &nSize ) )
		{
			FMOD_MODE mode = FMOD_OPENMEMORY | FMOD_HARDWARE |FMOD_LOOP_NORMAL| FMOD_2D;
			if( !bLoop )
			{
				mode = FMOD_OPENMEMORY | FMOD_HARDWARE | FMOD_2D;
			}
			FMOD_CREATESOUNDEXINFO exinfo;
			memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
			exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
			exinfo.length = nSize;
			FMOD_RESULT  ret = GAudioSystem->createStream( (char *)pBuffer, mode, &exinfo, &m_Music[m_nSelIdx] );
// 			int i = 3;

		}
		else
		{
			SMusicUnreadyPlayReq* pReq = MeNew SMusicUnreadyPlayReq;
			pReq->m_FileName = strLowerRelativePath;
			pReq->bLoop = bLoop;
			pReq->bFade = bFade;
			GetSoundMgr()->AddUnreadyPlayReq(pReq);
#if _DEBUG
			time_cost = HQ_TimeGetTime() - time_cost;
			if(time_cost > 20)
			{
				char cOutputString[2048];
				sprintf_s( cOutputString, 2048, "\n PlayMusic 1111111111111111 %d\n", time_cost );
				OutputDebugStr(cOutputString);
			}
			time_cost = HQ_TimeGetTime();
#endif
			return -1;
		}


		GAudioSystem->playSound(FMOD_CHANNEL_FREE, m_Music[m_nSelIdx], true, &m_Channel[m_nSelIdx] );	
		m_szMusicName[m_nSelIdx] = strLowerRelativePath;
		if( bFade )
		{
			if(m_Channel[m_nSelIdx])
				m_Channel[m_nSelIdx]->setVolume( 0.0f );
			m_bMusicFade = TRUE;
// 			CalcFadeChannel();
			if (m_nSelIdx == 0)
			{
				m_nFadeOrder = eBackToFront;
			}
			else
			{
				m_nFadeOrder = eFrontToBack;
			}
			
		}
		else
		{
			if(m_Channel[m_nSelIdx])
				m_Channel[m_nSelIdx]->setVolume( m_fSoundVal );
		}
		if(m_Channel[m_nSelIdx])
		{
			m_Channel[m_nSelIdx]->setPaused(false);
		}
	}
	else
	{
		bool IsPlaying = false;
		if( m_Channel[m_nSelIdx] )
		{
			m_Channel[m_nSelIdx]->isPlaying( &IsPlaying );
		}
		if( !IsPlaying )
		{
			GAudioSystem->playSound(FMOD_CHANNEL_FREE, m_Music[m_nSelIdx], false, &m_Channel[m_nSelIdx] );	
			if( bFade )
			{
				if(m_Channel[m_nSelIdx])
					m_Channel[m_nSelIdx]->setVolume( 0.0f );
				m_bMusicFade = TRUE;
// 				CalcFadeChannel();
				if (m_nSelIdx == 0)
				{
					m_nFadeOrder = eBackToFront;
				}
				else
				{
					m_nFadeOrder = eFrontToBack;  
				}
			}
			else
			{
				if(m_Channel[m_nSelIdx])
					m_Channel[m_nSelIdx]->setVolume( m_fSoundVal );
			}
			if(m_Channel[m_nSelIdx])
			{
				m_Channel[m_nSelIdx]->setPaused(false);
			}
		}
	}
#if _DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost > 20)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\n PlayMusic 22222222222222222222222 %d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
	time_cost = HQ_TimeGetTime();
#endif
	return 0;
}

void HRMusic::Paused( bool bPaused )
{
	if( !GAudioSystem )
		return ;
	for( int i=0;i < eMaxMusic; i++ )
	{
		if( m_Channel[i] )
			m_Channel[i]->setPaused ( bPaused );
	}
	m_IsPaused = bPaused;
	if( !m_IsPaused )
	{
		PlayMusic( SaveState.szSaveName.c_str(), SaveState.bLoop, SaveState.bFade );
		SaveState.szSaveName.clear();
	}
}

void HRMusic::Destory()
{
	if( !GAudioSystem )
		return ;
	for( int i=0;i < eMaxMusic; i++ )
	{
		if( m_Music[i] )
		{
			m_Music[i]->release();
			m_Music[i] = NULL;
		}
		if( m_Channel[i] )
		{

		}
	}
}

void HRMusic::UpDateFadeChannel( DWORD msElapsed )
{
	MeScopeProfileAudioFun
	if( !GAudioSystem )
		return ;
	if( m_bMusicFade && !m_IsPaused)
	{
		INT Idx0 = 0,
			Idx1 = 1;
// 		if( m_nFadeOrder == eFrontToBack )
// 		{
// 			Idx0 = 0;
// 			Idx1 = 1;
// 		}
		if( m_nFadeOrder == eBackToFront )
		{
			Idx0 = 1;
			Idx1 = 0;
		}	
		if( !m_Channel[Idx1] )
		{
			m_bMusicFade = FALSE;
			return;
		}
		FLOAT fVal0 = 0.0f,
			fVal1 = 0.0f;
		if (m_Channel[Idx0])
		{
			m_Channel[Idx0]->getVolume(&fVal0);
			FLOAT fVal = fVal0 - 0.002f;				
			CLAMP( fVal, 0, m_fSoundVal );
			m_Channel[Idx0]->setVolume(fVal); //0-
		}

		{
			m_Channel[Idx1]->getVolume(&fVal1);
			FLOAT fVal = fVal1 + 0.002f;				
			CLAMP( fVal, 0, m_fSoundVal );
			m_Channel[Idx1]->setVolume(fVal); //0-
		}

// 		m_Channel[Idx0]->getVolume(&fVal0);
		m_Channel[Idx1]->getVolume(&fVal1);
		if( /*
		fVal0 >= m_fSoundVal 
					||*/
		 fVal1 >= m_fSoundVal )
		{
// 			if( fVal0 < fVal1 )
			{
				if (m_Channel[Idx0])
				{
					m_Channel[Idx0]->stop();
				}
				m_Channel[Idx1]->setVolume(m_fSoundVal);
			}
// 			else
// 			{
// 				m_Channel[Idx1]->stop();
// 				m_Channel[Idx0]->setVolume(m_fSoundVal);
// 			}

			m_bMusicFade = FALSE;
		}
	}
}

void HRMusic::CalcFadeChannel()
{
	MeScopeProfileAudioFun
	if( m_bMusicFade )
	{
		float	fVal0 = 0.0f,
			fVal1 = 0.0f;
		if( !m_Channel[0] 
		|| !m_Channel[1]
		|| abs(m_fSoundVal) < 0.00001
		)
		{
			if( m_Channel[0] )
			{
				m_Channel[0]->setVolume( m_fSoundVal );
			}
			if( m_Channel[1] )
			{
				m_Channel[1]->setVolume( m_fSoundVal );
			}
			m_bMusicFade = FALSE;
			return;
		}

		if( m_Channel[0] )
		{
			m_Channel[0]->getVolume(&fVal0);
		}
		else
		{
			m_bMusicFade = FALSE;
		}

		if( m_Channel[1] )
		{
			m_Channel[1]->getVolume(&fVal1);
		}
		else
		{
			m_bMusicFade = FALSE;
		}

		if( fVal0 > fVal1 )
		{
			m_nFadeOrder = eFrontToBack;	//0-, 1+
		}
		else
		{
			m_nFadeOrder = eBackToFront;	//0+, 1-
		}
	}
}

void HRMusic::SetVolume( FLOAT fVal )
{
	if( !GAudioSystem )
		return ;
	m_fSoundVal = fVal;
	for( int i=0;i < eMaxMusic; i++ )
	{
		if( m_Channel[i] )
			m_Channel[i]->setVolume( fVal );
	}
	//m_Channel->setVolume( fVal );
}

void HRMusic::StopMusic()
{
	if( !GAudioSystem )
		return ;
	m_IsStop = TRUE;
	for( int i=0;i < eMaxMusic; i++ )
	{
		if( m_Channel[i] )
			m_Channel[i]->stop();
		m_szMusicName[i].clear();
	}
}

bool HRMusic::GetCurrentMusicInfo( OUT std::string& strMusicName, OUT bool& bLoop, OUT bool& bFade )
{
    if( !GAudioSystem )
    {
        strMusicName.clear();
        bLoop = false;
        bFade = false;
        return false;
    }

    if( m_IsStop || m_nSelIdx < 0 || m_nSelIdx >= eMaxMusic )
    {
        strMusicName.clear();
        bLoop = false;
        bFade = false;
        return false;
    }
	strMusicName = GetRootPath();
	strMusicName.append( "\\" );
	strMusicName.append( m_szMusicName[ m_nSelIdx ].c_str() );
    
    bLoop = m_bCurMusicLoop;
    bFade = m_bCurMusicFade;
    return true;
}

bool HRMusic::IsCurrMusicOver( DWORD offset )
{
	if (m_nSelIdx == -1)
	{
		return true;
	}
	if (m_bCurMusicLoop)
	{
		return false;
	}
	if (m_Music[m_nSelIdx] == NULL)
	{//还没有多线程加载完成
		return false;
	}
	unsigned int nTotalLength = 0, nCurrentLength = 0;
	m_Music[m_nSelIdx]->getLength(&nTotalLength,FMOD_TIMEUNIT_MS);
	m_Channel[m_nSelIdx]->getPosition(&nCurrentLength,FMOD_TIMEUNIT_MS);
	if (nCurrentLength + offset > nTotalLength)
	{
		return true;
	}
	return false;
}

FMOD::Sound* HRMusic::GetCurrMusic()
{
	if(m_nSelIdx != -1) 
		return m_Music[m_nSelIdx];
	return NULL;
}

unsigned int HRMusic::GetCurrMusicLength()
{
	FMOD::Sound* pCurrSound = GetCurrMusic();
	if (pCurrSound)
	{
		unsigned int nTotalLength = 0;
		pCurrSound->getLength(&nTotalLength,FMOD_TIMEUNIT_MS);
		return nTotalLength;
	}
	return 0;
}
HRSound::HRSound() :
m_fSoundVal(0.125f),
m_IsPaused(FALSE)
,m_IsStop(FALSE)
{
	for( int i=0;i < eMaxSound; i++ )
	{
		m_Sound[i] = NULL;
		m_Channel[i] = NULL;
	}
}

void HRSound::UpdatePos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir )
{
	MeScopeProfileAudioFun
	if( !GAudioSystem )
		return ;
	m_vListernerPos = vPos;
	m_vListernerDir = vDir;

	FMOD_VECTOR listenerpos;
	listenerpos.x = m_vListernerPos.x;
	listenerpos.y = m_vListernerPos.y;
	listenerpos.z = m_vListernerPos.z;

	FMOD_VECTOR listenerdir;
	listenerdir.x = m_vListernerDir.x;
	listenerdir.y = m_vListernerDir.y;
	listenerdir.z = m_vListernerDir.z;


	static FMOD_VECTOR lastpos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR vel;

	forward = listenerdir;

	// ********* NOTE ******* READ NEXT COMMENT!!!!!
	// vel = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
	vel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
	vel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
	vel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);

	// store pos for next time
	lastpos = listenerpos;

	//result = FMOD_System_Set3DListenerAttributes(system, 0, &listenerpos, &vel, &forward, &up);
	GAudioSystem->set3DListenerAttributes( 0, &listenerpos, &vel, &forward, &up );
}

void HRSound::GetSoundCPUUsage( float* fDsp, float* fStream, float* fUpdate, float* fTotal )
{
	if( !GAudioSystem )
		return ;
	GAudioSystem->getCPUUsage( fDsp, fStream, fUpdate, fTotal );
}

void HRSound::GetInMemorySoundFileCount( int* nFinderSize, int* nListSize )
{
	*nFinderSize = GetSoundMgr()->GetSoundFileFinderSize();
	*nListSize = GetSoundMgr()->GetSoundFileListSize();
}

int HRSound::PlaySound( const char* szName ,bool bLoop, D3DXVECTOR3* vPos ,float fMinDistance,float fMaxDistance)
{
	MeScopeProfileAudioFun
	guardfunc;
	guard(PlaySound::test1);

	OutputDebugString(szName);

	if( !GAudioSystem || !szName || szName[0] == '\0')
		return -1;

	m_IsStop = FALSE;
	if( m_IsPaused )
	{
		return -1;
	}
	unguard;

	std::string strLowerRelativePath;
	GetLowerRelativePath( szName, strLowerRelativePath );	

	INT nSelIdx = -1;

	guard(PlaySound::test2);
	DWORD dwCurTime = HQ_TimeGetTime();
	for ( int i = 0; i< eMaxSound && -1 == nSelIdx; i++ )
	{
		BOOL bCanPlay = FALSE;

		if( m_Channel[i] )
		{
			bool bPlaying = false;
			m_Channel[i]->isPlaying( &bPlaying );

			if( !bPlaying )
			{
				bCanPlay = TRUE;
			}
		}
		else
		{
			bCanPlay = TRUE;
		}

		if( bCanPlay )
		{
			nSelIdx = i;
		}
		//else
		//{
		//	char szBuf[256];
		//	_snprintf( szBuf, 256, "m_Channel[i] = %d", i );
		//	OutputDebugString( szBuf );
		//}
	}

	if( nSelIdx == -1 )
	{
		return nSelIdx;
		nSelIdx = 0;
	}

	if( m_Sound[nSelIdx] )
	{
		m_Sound[nSelIdx]->release();
		m_Sound[nSelIdx] = NULL;
	}
	unguard;

	guard(PlaySound::createStream);
	int nSize = 0;
	void* pBuffer = NULL;
	if( GetSoundMgr()->GetSoundFileFromMemory( strLowerRelativePath.c_str(), &pBuffer, &nSize ) )
	{
		int nflag = FMOD_HARDWARE|FMOD_OPENMEMORY;
		if (vPos)
		{
			nflag |= FMOD_3D|FMOD_3D_LINEARROLLOFF;
		}
		else
		{
			nflag |= FMOD_2D;
		}
		if (bLoop)
		{
			nflag |= FMOD_LOOP_NORMAL;
		}

		FMOD_CREATESOUNDEXINFO exinfo;
		memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
		exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
		exinfo.length = nSize;

		FMOD_RESULT ret = GAudioSystem->createSound( (const char *)pBuffer, nflag, &exinfo, &(m_Sound[nSelIdx]) );
// 		int i = 345;
	}
	else
	{
		SSoundUnreadyPlayReq* pReq = MeNew SSoundUnreadyPlayReq;
		pReq->bLoop = bLoop;
		if (vPos)
		{
			pReq->vPos = *vPos;
		}
		pReq->m_FileName = strLowerRelativePath;
		pReq->fMaxDistance = fMaxDistance;
		pReq->fMinDistance = fMinDistance;
		GetSoundMgr()->AddUnreadyPlayReq(pReq);
		return -1;
	}
	unguard;

	m_szSoundName[nSelIdx] = strLowerRelativePath;
	guard(PlaySound::test3);
	if( vPos )
	{
		m_Sound[nSelIdx]->set3DMinMaxDistance( fMinDistance,fMaxDistance);

		guard(PlaySound::playSound);
		GAudioSystem->playSound(FMOD_CHANNEL_FREE, m_Sound[nSelIdx], true, &(m_Channel[nSelIdx]) );
		unguard;

		if( m_Channel[nSelIdx] )
		{
			FMOD_VECTOR vel = {  0.0f, 0.0f, 0.0f };
			FMOD_VECTOR fmod_vOffsetPos;
			fmod_vOffsetPos.x = vPos->x;
			fmod_vOffsetPos.y = vPos->y;
			fmod_vOffsetPos.z = vPos->z;

			m_Channel[nSelIdx]->set3DAttributes( &fmod_vOffsetPos, &vel );
			m_Channel[nSelIdx]->setVolume( m_fSoundVal );
			m_Channel[nSelIdx]->setPaused( FALSE );
		}
	}
	else
	{
		guard(PlaySound::playSound);
		GAudioSystem->playSound(FMOD_CHANNEL_FREE, m_Sound[nSelIdx], true, &(m_Channel[nSelIdx]) );
		unguard;

		if( m_Channel[nSelIdx] )
		{
			m_Channel[nSelIdx]->setVolume( m_fSoundVal );
			m_Channel[nSelIdx]->setPaused( FALSE );
		}
	}

	return nSelIdx;

	unguard;
	unguard;
}

void HRSound::Paused( bool bPaused )
{
	for( int Idx=0; Idx<eMaxSound; Idx++ )
	{
		if( m_Channel[Idx] )
			m_Channel[Idx]->setPaused ( bPaused );
	}
	m_IsPaused = bPaused;
}

void HRSound::StopSound( int nIdx )
{
	if( !GAudioSystem )
		return ;

	if( nIdx < 0 || nIdx >= eMaxSound )
	{ return; }

	if( m_Channel[nIdx] )
	{ m_Channel[nIdx]->stop(); }
	
}

void HRSound::StopSound()
{
	if( !GAudioSystem )
		return ;
	m_IsStop = TRUE;
	for( int Idx=0; Idx<eMaxSound; Idx++ )
	{
		if( m_Channel[Idx] )
			m_Channel[Idx]->stop();
	}
}

void HRSound::SetVolume( int nIdx, float fValue )
{
	if( !GAudioSystem )
		return ;

	if( nIdx < 0 || nIdx >= eMaxSound )
	{ return; }

	if( m_Channel[nIdx] )
	{ m_Channel[nIdx]->setVolume( fValue ); }
	
}

float HRSound::GetVolume( int nIdx )
{
	if( !GAudioSystem )
	{ return 0.f; }

	if( nIdx < 0 || nIdx >= eMaxSound )
	{ return 0.f; }

	if( m_Channel[nIdx] )
	{
		float fValue = 0.f;
		m_Channel[nIdx]->getVolume( &fValue );
		return fValue;
	}
	return 0.f;
}

void HRSound::SetVolume( FLOAT fVal )
{
	if( !GAudioSystem )
		return ;
	m_fSoundVal = fVal;
	for( int i=0;i < eMaxSound; i++ )
	{
		if( m_Channel[i] )
			m_Channel[i]->setVolume( fVal );
	}
	//	if(m_Channel)
	//		m_Channel->setVolume( fVal );
}

void HRSound::Destory()
{
	if( !GAudioSystem )
		return ;
	for( int Idx=0; Idx<eMaxSound; Idx++ )
	{
		if( m_Sound[Idx] )
		{
			m_Sound[Idx]->release();
			m_Sound[Idx] = NULL;
		}
		if( m_Channel[Idx] )
		{

		}
	}
}

void HRSound::ReleaseSound( const char* szName )
{
	std::string strLowerRelativePath;
	GetLowerRelativePath( szName, strLowerRelativePath );
	
	GetSoundMgr()->Release( strLowerRelativePath.c_str() );
}

bool HRSound::IsSoundInPlay( const char* szName )
{
	std::string strLowerRelativePath;
	GetLowerRelativePath( szName, strLowerRelativePath );
	
	for (int i = 0; i < eMaxSound; ++i)
	{
		if( m_Channel[i] )
		{
			bool bPlaying = false;
			m_Channel[i]->isPlaying( &bPlaying );

			if( bPlaying && m_szSoundName[i] == strLowerRelativePath )
			{
				return true;
			}
		}
	}
	return false;
}
