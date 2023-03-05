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

	/** ������������uv�����󲥷�
	*/
	void SetUVSoundPath( const char* pcSound ){
		strncpy_s( m_acSoundFilename, MAX_PATH, pcSound, MAX_PATH - 1 );		
	}

	/** ���������ص�����
	*/
	void SetSoundFunc( PlaySoundFuncPtr pfFunc ){
		m_pfUVSound = pfFunc;
	}

	/** ��������
	*/
	void PlaySound(){
		PlaySound( Int2Type<bPlayOnce>() );
	}

protected:
	/** ��������, ֻ����һ��
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
	/** ��������, �����ƴ���
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
	/// ���������ֻ����һ�Σ���ֵ��Ч
	bool m_bHavePlayedSound;	
};