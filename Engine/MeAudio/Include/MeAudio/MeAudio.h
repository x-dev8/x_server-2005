#pragma once
#define  HRAUIDO_API

#include "MeRTLibs.h"
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include "Dxsdk/d3dx9math.h"

#include "fmod/fmod.hpp"

class HRAUIDO_API HRSampleFMOD;

class HRMusic
{
	enum
	{
		eMaxMusic = 3,
		//1,2用来渐变，3是直接播放的
		eFadeMusic = 2,
		ePlayMusicIdx = 2,


	};

	enum 
	{
		eChannel0 = 0,
		eChannel1,
	};

	enum
	{
		eFrontToBack,
		eBackToFront
	};

public:
	HRMusic();

	int PlayMusic( const char* szName, BOOL bLoop, BOOL bFade );

	void Paused( bool bPaused );

	void Destory();

	void UpDateFadeChannel( DWORD msElapsed );

	void CalcFadeChannel();

	void SetVolume( FLOAT fVal );

	void StopMusic();

    bool GetCurrentMusicInfo( OUT std::string& strMusicName, OUT bool& bLoop, OUT bool& bFade );

	bool IsCurrMusicOver(DWORD offset);
	FMOD::Sound*	GetCurrMusic();
	unsigned int	GetCurrMusicLength();
	BOOL			m_IsPaused;
	BOOL			m_IsStop;
	BOOL			m_bMusicFade;
	INT				m_nFadeOrder;
	FLOAT			m_fSoundVal;
    int             m_nSelIdx;
    BOOL            m_bCurMusicLoop;            // 无逻辑，仅用于保存播放时设置的参数
    BOOL            m_bCurMusicFade;            // 无逻辑，仅用于保存播放时设置的参数
	std::string		m_szMusicName[eMaxMusic];
	FMOD::Sound*	m_Music[eMaxMusic];
	FMOD::Channel*	m_Channel[eMaxMusic];
};

class HRSound
{
public:
	enum
	{ 
		eMaxSound  = 24
	};
	HRSound();

	int PlaySound( const char* szName ,bool bLoop, D3DXVECTOR3* vPos,float fMinDistance = 3.f,float fMaxDistance = 50.f);

	void UpdatePos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir );

	void GetSoundCPUUsage( float* fDsp, float* fStream, float* fUpdate, float* fTotal );

	void GetInMemorySoundFileCount( int* nFinderSize, int* nListSize );


	void Paused( bool bPaused );
	void StopSound();
	void StopSound( int nIdx );
	void ReleaseSound(const char* szName);

	void SetVolume( FLOAT fVal );
	void SetVolume( int nIdx, float fValue );

	float GetVolume( int nIdx );
	float GetVolume() const { return m_fSoundVal; }

	void Destory();

	bool IsSoundInPlay(const char* szName);
	BOOL			m_IsPaused;
	BOOL			m_IsStop;
	FLOAT			m_fSoundVal;
	D3DXVECTOR3		m_vListernerPos;
	D3DXVECTOR3		m_vListernerDir;
	std::string		m_szSoundName[eMaxSound];
	FMOD::Sound*	m_Sound[eMaxSound];
	FMOD::Channel*	m_Channel[eMaxSound];
};

extern HRMusic			GMusic;
extern HRSound			GSound;

//
//
//

HRAUIDO_API VOID InitAudioSystem( HWND hWnd );
HRAUIDO_API VOID UpdateAudio( DWORD dwTime );
HRAUIDO_API VOID DestoryAudio();
