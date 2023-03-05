#pragma once

#include "BaseHead.h"
#include <windows.h>
#include <vector>
#include "MapContainer.h"
#define MTLANIM_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )
union UMtlAnimPointer;

struct SMtlAnimVersion
{
	SMtlAnimVersion():	dwVersion(100){}
	DWORD	dwVersion;
	BOOL	Read( UMtlAnimPointer inP, int nSize );
};

struct SMtlAnimKeyframe : public MeCommonAllocObj
{
	DWORD	dwTime;
	// 根据现在的情况，只需要4个元素就可以满足所有的情况，
	float	fValues[4];

	SMtlAnimKeyframe():	dwTime(0)
	{
		fValues[0] = 0.0f;
		fValues[1] = 0.0f;
		fValues[2] = 0.0f;
		fValues[3] = 0.0f;
	}
	// 从两个keyframe blend结果，
	// nElement是blend几个元素，
	// 比如rgb是3个，uv是两个
	void	BlendFrame( SMtlAnimKeyframe* pKeyframeLeft, 
						SMtlAnimKeyframe* pKeyframeRight, 
						float t,
						int nElement );


};

struct SMtlAnimTrack : public MeCommonAllocObj
{
	DWORD	dwLength;
	std::vector<SMtlAnimKeyframe*> vectorKeyframe;

	SMtlAnimTrack();
	~SMtlAnimTrack();
	BOOL	Read( UMtlAnimPointer inP, int nSize );
	
	void	SetLength( DWORD l ){ dwLength = l; }
	BOOL	GetKeyframe(	DWORD dwTime, 
							SMtlAnimKeyframe** ppKeyframeLeft, 
							SMtlAnimKeyframe** ppKeyframeRight, 
							float* t );

	SMtlAnimKeyframe*	AddKeyframe( DWORD dwTime, float t0 = 0.0f, float t1 = 0.0f, float t2 = 0.0f, float t3 = 0.0f );
	SMtlAnimKeyframe*	AddKeyframe( SMtlAnimKeyframe* pKeyframe );
	BOOL	DelKeyframe( SMtlAnimKeyframe* pKeyframe );

	//   added 2004.06.16
	BOOL	AdjustKeyframe( SMtlAnimKeyframe* pKeyframe, float fTimeT );

};

struct SMtlAnimBlendMode
{
	DWORD	dwMethod;
	DWORD	dwFlag;
	SMtlAnimBlendMode();

						

	BOOL	Read( UMtlAnimPointer inP, int nSize );
};

struct SMtlAnimProperty
{
	DWORD	dwLength;
	DWORD	dwAffectRange;

	//BOOL	bRender1Pass;
	BOOL	bRender2Pass;

	SMtlAnimProperty():	dwLength(1000),	
						dwAffectRange(0),
						bRender2Pass(FALSE){}
	BOOL	Read( UMtlAnimPointer inP, int nSize );
};

struct SMtlAnimTexture : public MeCommonAllocObj
{
	SMtlAnimTexture();
	~SMtlAnimTexture();
	void	Destroy();
	char	szFilename[MAX_PATH];
	int		nTextureId;
	BOOL	Read( UMtlAnimPointer inP, int nSize );
	void	AssignFilename( const char* pszFilename ){ strcpy( szFilename, pszFilename ); }
	int		Register();
	void	UnRegister();

};

union UMtlAnimPointer
{
	BYTE*			byte;
	bool*			boolean;
	int*			i;
	DWORD*			dw;
	char*			c;
	void*			p;
	float*			f;

	UMtlAnimPointer(void* in) :p(in)
	{
	}
};
namespace ModelPart
{
	enum
	{
		eHair	=	1<<0,
		eFace	=	1<<1,
		eBody	=	1<<2,

		eWeaponEdge		=	1<<16,
		eWeaponHandle	=	1<<17,
	};

};
class MtlAnim : public MeCommonAllocObj
{
public:
	enum
	{
		eRenderExclude,	// 仅仅渲染自己，
	};
	struct SSetting
	{
		float	fUOffset, fVOffset;
		DWORD	dwColor;
		int		nTextureId;
		DWORD	dwBlendMode;
		
		BOOL	bRender2Pass;

		//   added 2004.11.19
		BOOL	bGlobalTransparent;
		float	fAlpha;	// [0.0~1.0];

		//// 高光参数
		//BOOL	bHasSpecular;
		//float	fSpecularPower;
		//float	fSpecularRed;
		//float	fSpecularGreen;
		//float	fSpecularBlue;
		SSetting();
	};
public:
	MtlAnim(void);
	~MtlAnim(void);
	void	Destroy();

	BOOL	LoadFromFile( const char* pszFilename );
	BOOL	LoadFromFile2( const char* pszFilename );
	BOOL	SaveToFile( const char* pszFilename );

	void	CreateUVTrack(){ m_pUVTrack = MeNew SMtlAnimTrack; }
	void	CreateColorTrack(){ m_pColorTrack = MeNew SMtlAnimTrack; }
	void	CreateAlphaTrack(){ m_pAlphaTrack = MeNew SMtlAnimTrack; }
	void	CreateTexture(){ m_pTexture = MeNew SMtlAnimTexture; }

	void	GetSetting( DWORD dwTime, SSetting* pSetting );
	void	SetStartTime( DWORD dwTime ){ m_dwStartTime = dwTime; }

public:
	DWORD				m_dwLength;
	SMtlAnimVersion		m_Version;
	SMtlAnimBlendMode	m_BlendMode;
	SMtlAnimProperty	m_Property;
	
	SMtlAnimTexture*	m_pTexture;
	SMtlAnimTrack*		m_pUVTrack;
	SMtlAnimTrack*		m_pColorTrack;
	SMtlAnimTrack*		m_pAlphaTrack;

	//BYTE*				m_pbyBuffer;
	int					m_nLayerCount;
	DWORD				m_dwStartTime;
	BOOL				m_bHasSpecular;
	float				m_fSpecularPower;
	float				m_fSpecularRed;
	float				m_fSpecularGreen;
	float				m_fSpecularBlue;
};

class CMtlEffectMgr
{
public:
	enum
	{
		eExternalBase = 10000000,
	};
public:
	CMtlEffectMgr();
	~CMtlEffectMgr();
	BOOL	LoadEffects( const char* pszFileName );
	int		AddEffect( const char* pszFileName );
	BOOL	AddEffect( int nID, MtlAnim* pEffect );
	void	Destroy();
	MtlAnim* GetEffect( int nID ){ return m_Effects.Find( nID ); }
protected:
	CMapContainer<int,MtlAnim*> m_Effects;
	int		m_nExternalID;
};
extern CMtlEffectMgr* GetMtlEffectMgr();