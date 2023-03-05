///////////////////////////////////////////////////////////////////
//
// class:       SkyBox
///////////////////////////////////////////////////////////////////


#ifndef __SKYBOX_HEADERFILE__
#define __SKYBOX_HEADERFILE__

#include "Me3d\include.h"

#define CLOUDS_WIDTH				128
#define CLOUDS_HEIGHT				128
#define MAX_PRESSURE				1024
#define CLOUDS_SIZE					CLOUDS_WIDTH*CLOUDS_HEIGHT
#define CLOUDS_VB_SIZE				CLOUDS_WIDTH*CLOUDS_HEIGHT
#define CLOUDS_NUM_Of_TRIANGLES		(CLOUDS_WIDTH-1)*(CLOUDS_HEIGHT-1)*2
#define CLOUDS_IB_SIZE				CLOUDS_NUM_Of_TRIANGLES*3

#define SUN_SEGMENT					32
#define SUN_VB_SIZE					34		
#define SUN_NUM_Of_TRIANGLES		SUN_SEGMENT

#define NUM_STDFLAREIMGS			10 

#define FOG_HEIGHT					40 
class CSkyBox
{
public:
	CSkyBox();
	~CSkyBox();

	void Create(int nResolution, float fVertSweep, float fRadius, 
		float fHeightScale, const D3DXVECTOR3 &vOrigin);
	void Release(){}

	void RenderSunAndMoon( D3DXVECTOR3 vPos );
	void Render(D3DXVECTOR3 vPos);
	void RenderSunInWater(D3DXVECTOR3 vPos);
	void RenderSun(const D3DXMATRIX &vMat);
	void RenderSunshine(const D3DXMATRIX &vMat);
	void RenderMoon();
	virtual	void RestoreFog(){}
	void InitClouds();
	void SetupCloudsPressure();
	void SetupCloudsDensity();
	void ComputeClouds();

	void RenderFlare();
	void DrawFlarePart(float fPos, int nIndex, float fSize, float fRed, float fGreen, float fBlue, float fAlpha=1.0f);

	void SetSunColor(DWORD dwSunColor)			{m_dwSunColor		= dwSunColor;}
	void SetMoonColor(DWORD dwMoonColor)		{m_dwMoonColor		= dwMoonColor;}
	void SetCloudColor(DWORD dwCloudColor)		{m_dwCloudColor		= dwCloudColor;}
	void SetTopColor(DWORD dwTopColor)			{m_dwTopColor		= dwTopColor;}
	void SetBaseColor(DWORD dwBaseColor)		{m_dwBaseColor		= dwBaseColor;}
	void SetAmbientColor(DWORD dwAmbientColor)	{m_dwAmbientColor	= dwAmbientColor;}
	int GetSunTextureID() { return m_nTxSun; }


	void deleteDeviceObjects();
	bool restoreDeviceObjects();
	void SetSunPosition(const D3DXVECTOR3 vPosition);
	void SetTime(DWORD dwTime);
	void SetMoonPosition(const D3DXVECTOR3 vPosition);
	
	const D3DXVECTOR2& GetSunSSPosition(){return m_SunScreenPos;};
	const D3DXVECTOR3& GetSunPosition(){return m_vSunPos;};
	D3DXVECTOR3 GetSunNormal(){return D3DXVECTOR3(m_vSunNormal.x,m_vSunNormal.y,m_vSunNormal.z);};

	bool IsDisable(){return m_bDisable;}
	void SetEnable(bool bEnable){ m_bDisable=!bEnable; }
	bool						m_bCanRender;
protected:
	D3DXVECTOR3	m_vSunPos,m_vMoonPos;//日月
	D3DXVECTOR4 m_vSunColor,m_vMoonColor;

	int						m_nFlareTexID[NUM_STDFLAREIMGS];
	int						m_nTxSky;
	int						m_nTxSun,m_nTxMoon;

	D3DXVECTOR2				m_SunScreenPos;
	typedef struct LF_VERTEX
	{
		D3DXVECTOR3		pos;
		DWORD	color;
		float			u,v;
	};
	LF_VERTEX	m_LFVerts[4];

	DWORD		m_dwSunColor;		// 太阳的颜色
	DWORD		m_dwMoonColor;		// 月亮
	DWORD		m_dwCloudColor;		// 云
	DWORD		m_dwTopColor;		// 天空的顶部颜色
	DWORD		m_dwBaseColor;		// 天空的基调
	DWORD		m_dwAmbientColor;	// 天空的底层环绕色--雾色

	D3DXVECTOR3 m_vSunNormal,m_vMoonNormal;//光法线 星体方位

	D3DXVECTOR3 sizeH;

	bool						downSide;
	PDIRECT3DTEXTURE9			textures[6];
	PDIRECT3DVERTEXBUFFER9		m_pVB;
	IDirect3DIndexBuffer9*		m_pIB;
	int							m_nNumOfVertices;
	int							m_nNumOfTriangles;

	PDIRECT3DVERTEXBUFFER9		m_pFogVB;
	IDirect3DIndexBuffer9*		m_pFogIB;
	PDIRECT3DVERTEXBUFFER9		m_pAmbientVB;
	IDirect3DIndexBuffer9*		m_pAmbientIB;
	int							m_nNumOfAV;
	int							m_nNumOfAT;

	PDIRECT3DVERTEXBUFFER9		m_pSunVB;
	IDirect3DIndexBuffer9*		m_pSunIB;
	PDIRECT3DVERTEXBUFFER9		m_pSunshineVB;
	PDIRECT3DINDEXBUFFER9		m_pSunshineIB;

	PDIRECT3DVERTEXBUFFER9		m_pCloudsVB;
	PDIRECT3DINDEXBUFFER9		m_pCloudsIB;

	bool						m_bIsDaytime;
	bool						m_bDisable;

	struct Cloud
	{
		int nDensity;		// 气密度
		int nPressure;		// 压强
	};
	Cloud						m_Clouds[CLOUDS_SIZE];

	struct CloudsVB
	{
		float x,y,z;
		DWORD dwColor;
	};
	CloudsVB					m_CloudsVB[CLOUDS_VB_SIZE];

	WORD						m_CloudsIB[CLOUDS_IB_SIZE];
	// 天空盒的分辨率

	int				m_nResolution;

	// 天空盒的垂直伸展角度

	float			m_fVertSweep;

	// 天空盒的半径

	float			m_fRadius;

	// 天空盒的单位高度

	float			m_fHeightScale;

	// 天空盒的最高高度

	float			m_fMaxHeight;

	// 天空盒的源点

	D3DXVECTOR3		m_vOrigin;
};

CSkyBox* GetSkyBox();

#endif //__SKYBOX_HEADERFILE__
