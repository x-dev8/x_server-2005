#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include <vector>
#include "EffectHollywood.h"
/*
	HitFlash ���
	�ܶ���Ϸ��,����Ч��,����һ����ҫ�Ĺ⻷,
	��������⻷���й��ɵ�,

	����Ҫ���Ĺ⻷
	���ֺ�,λ����Բ����ﲻ��,
	ֻ���д�С�ı仯,
	͸���ȵı仯,
	��ɫ�ı仯,
	�ɼ��Եı仯,

	һ��HitFlash������billboard���ɣ�
	ÿ��billboard�����Լ���keyframe
*/
class CHitFlashEffect:public CBaseEffect
{
public:
	enum
	{
		eTrackSize,
		eTrackColor,
		eTrackAlpha,
		eTrackVisible,
		eTrackMax,
	};
	enum
	{
		eBbrd_Quad,				// �����ε�bbrd
		eBbrd_Strip,			// �����ε�bbrd
	};
	enum
	{
		eStrip_One,				// һ���������ĵĳ�����
		eStrip_Half,			// һ�����������ĵĳ���

	};
	enum
	{
		eKeyStart,
		eKeyEnd,
		eKeyAny,
		eKeyNotFound,
	};
	enum
	{
		eActionStand,
		eActionFollow,
		eActionMax,
	};
	struct KeyFrame
	{
		float	fTime;
		DWORD	dwTime;
		float	fAlpha;
		float	fRed;
		float	fGreen;
		float	fBlue;
		float	fSize;
		BOOL	bVisible;

		KeyFrame():
			fTime(0.0f),
			dwTime(0),
			fAlpha(1.0f),
			fRed(1.0f),
			fGreen(1.0f),
			fBlue(1.0f),
			fSize(1.0f),
			bVisible(TRUE)
		{}
		void	Blend( float t, KeyFrame& key );
	};
	struct Track 
	{
		KeyFrame	keyStart;
		KeyFrame	keyEnd;
		std::vector<KeyFrame> keyframes;
		BOOL		AddKeyFrame( KeyFrame& key );
		int			FindKeyFrame( float fTime, KeyFrame& lkey, KeyFrame& rkey );
		void		GetKeyAtTime( float fTime, KeyFrame& key );
		Track();
	};
	struct Texture
	{
		char	szPath[MAX_PATH];		// ·��
		int		nTextureId;				// ϵͳע�������id
		Texture():nTextureId(-1){ memset( szPath, 0x00, MAX_PATH ); }
	};
	struct Strip
	{
		float	fRot;
	};
	struct Billboard
	{
		int		nType;
		DWORD	dwStartTime;	// ������ʱ�䣬
		DWORD	dwLife;			// life�ĳ��������һ��keyframe�Ŀ�ʼʱ��
		D3DXVECTOR3 vPos;		// ��Բ������λ�ã�������ֻ����z
		int		nTexture;		// ��ͼ��id

		int		nNumDrawTime;	// ���ƴ���,һ����������
		Track	tracks[eTrackMax]; // �켣

		// stricp���
		int		nNumStrip;		// stricp����
		//int		nStripType;		// stricp���ͣ���Ϊ��Խ�ͺ�һ����
		BOOL	bHalfStrip;
		float	fHalfStripInnerRadius;// half����Ȧ�뾶
		float	fStripThickness;// stricp�Ĵ�ϸ
		BOOL	bStripAverage;	// ���ȷֲ���strip
		std::vector<Strip> strips;
		Billboard():
		nType(eBbrd_Quad),
			dwStartTime(0),
			dwLife(0),
			nTexture(0),
			nNumDrawTime(1),
			//nStripType(eStrip_One),
			bHalfStrip(FALSE),
			fHalfStripInnerRadius(0.0f),
			fStripThickness(0.0f),
			nNumStrip(0),
			bStripAverage(FALSE)
		{
			vPos.x = vPos.y = vPos.z = 0.0f;
		}
	};

public:
	CHitFlashEffect();
	virtual BOOL IsDead( DWORD dwTime );
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );
	virtual void Release();
	virtual void SetDead();
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance );
	BOOL		LoadSetting( const char* pszFilename );
	BOOL		Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize );
	BOOL		LoadFromMemory( BYTE* pbyBuffer, int nBufferSize );
	void		Destroy();
	void		Start();
	void		Render();
	void		DrawBillboard( Billboard& bbrd, D3DXVECTOR3 vPos, float fRadius, int nTextureId, DWORD dwColor );
	//void		DrawStrip( D3DXVECTOR3 vPos, float fRadius, int nTextureId, int nNumStrip, DWORD dwColor );
	void		GetKey( DWORD dwTime, const Billboard& bbrd, KeyFrame& key );

public:
	D3DXVECTOR3 m_vPos;
	IEffectHelper* m_pMaster;
	int			m_nAction;
	char		m_szSound[MAX_PATH];

protected:
	DWORD		m_dwStartTime;
	DWORD		m_dwLife;
	float		m_fScale;
	bool		m_bOutOfLookerView;

	std::vector<Billboard>	m_bbrds;
	std::vector<Texture>	m_textures;
};
