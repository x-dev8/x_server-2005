#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include <vector>
#include "EffectHollywood.h"
/*
	HitFlash 设计
	很多游戏中,命中效果,都是一个闪耀的光环,
	表现这个光环是有规律的,

	我们要做的光环
	出现后,位置相对参照物不动,
	只进行大小的变化,
	透明度的变化,
	颜色的变化,
	可见性的变化,

	一个HitFlash由若干billboard构成，
	每个billboard都有自己的keyframe
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
		eBbrd_Quad,				// 正方形的bbrd
		eBbrd_Strip,			// 长条形的bbrd
	};
	enum
	{
		eStrip_One,				// 一条穿过中心的长条，
		eStrip_Half,			// 一条不穿过中心的长条

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
		char	szPath[MAX_PATH];		// 路径
		int		nTextureId;				// 系统注册的纹理id
		Texture():nTextureId(-1){ memset( szPath, 0x00, MAX_PATH ); }
	};
	struct Strip
	{
		float	fRot;
	};
	struct Billboard
	{
		int		nType;
		DWORD	dwStartTime;	// 诞生的时间，
		DWORD	dwLife;			// life的长度是最后一个keyframe的开始时间
		D3DXVECTOR3 vPos;		// 相对参照物的位置，基本上只考虑z
		int		nTexture;		// 贴图的id

		int		nNumDrawTime;	// 绘制次数,一般用来叠加
		Track	tracks[eTrackMax]; // 轨迹

		// stricp相关
		int		nNumStrip;		// stricp数量
		//int		nStripType;		// stricp类型，分为穿越型和一般型
		BOOL	bHalfStrip;
		float	fHalfStripInnerRadius;// half型内圈半径
		float	fStripThickness;// stricp的粗细
		BOOL	bStripAverage;	// 均匀分布的strip
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
