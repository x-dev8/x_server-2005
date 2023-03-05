#pragma once
#include "RollSystemBase.h"

//----------------------------------------------------------------------
template< bool bPlayOnce >
class RollSound
{
public:
	typedef bool (*PlaySoundFuncPtr)( const char *name, D3DXVECTOR3* vPos ,bool bLoop);
public:
	RollSound(){
		memset( m_acSoundFilename, 0, sizeof( char ) * MAX_PATH );		
	}

	void Reset(){
		m_bHavePlayedSound = false;
	}

	/** 设置声音，在uv动画后播放
	*/
	void SetUVSoundPath( const char* pcSound ){
		strncpy_s( m_acSoundFilename, MAX_PATH, pcSound, MAX_PATH - 1 );		
	}

	/** 设置声音回调函数
	*/
	void SetSoundFunc( PlaySoundFuncPtr pfFunc ){
		m_pfUVSound = pfFunc;
	}

	/** 播放声音
	*/
	void PlaySound(){
		PlaySound( Int2Type<bPlayOnce>() );
	}

protected:
	/** 播放声音, 只播放一次
	*/
	void PlaySound( Int2Type<true> ){
		if( m_pfUVSound && !m_bHavePlayedSound )
		{
			if( m_acSoundFilename[0] != '\0' )
			{
				m_pfUVSound( m_acSoundFilename, 0, false );
				m_bHavePlayedSound = true;
			}		
		}
	}
	/** 播放声音, 不限制次数
	*/
	void PlaySound( Int2Type<false> ){
		if( m_pfUVSound )
		{
			if( m_acSoundFilename[0] != '\0' )
			{
				m_pfUVSound( m_acSoundFilename, 0, false );				
			}		
		}
	}	

protected:
	char m_acSoundFilename[MAX_PATH];
	PlaySoundFuncPtr m_pfUVSound;	
	/// 如果设置了只播放一次，此值有效
	bool m_bHavePlayedSound;	
};