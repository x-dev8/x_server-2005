//============hh add 2007-2-10=============
#pragma once
#include "Me3d/include.h"

#define SHADOW_MAP_SIZE	2048
#define WATER_REFLECT_SIZE	512
#define WATER_REFRACT_SIZE 512
// This is the vertex format used with the quad during post-process.
struct QUADVERT
{
	D3DXVECTOR4 p;
	D3DXVECTOR2 t;
	static DWORD FVF;
	//const static D3DVERTEXELEMENT9 Decl[4];
};


struct BLENDVERT
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	float u,v;
	D3DXVECTOR4 weight;
	D3DXVECTOR4 index;
	//DWORD color;

	static D3DVERTEXELEMENT9 Decl[6];
};

enum SceneEffect
{
	eNone			= 1<<0,
	eTemporalBlur	= 1<<1,	//时间模糊
	eBlur			= 1<<2,	//模糊

	eBright			= 1<<3,	//亮度
	eMonochrome		= 1<<4,	//灰度
	eInverse		= 1<<5,	//反色
	eNoise			= 1<<6,	//带噪点的
	eTint			= 1<<7	//带偏色的色调

};
enum ShadowType
{
	eShadow_None,
	eShadow_Fake,
	eShadow_RealTime,
	eShadow_Count
};

// shader管理
class CShaderMgr
{

public:
	CShaderMgr(void);
	~CShaderMgr(void);

	bool CheckShaderVersion(void);				// 检查shader的版本
	void InitShader(void);						// 初始化shader
	void ResetEffect(void);						// 重新读入hlsl
	void ResetTexture(void);					// 重新...

	void RenderScene();							// 全屏shadow渲染
	void RenderScene(DWORD dwEffect);			// 全屏shadow渲染
	void RenderBlurScene(void);					// 全屏模糊渲染
	void RenderFinalScene(void);				// 最终画面渲染
	void RenderTemporalBlurScene(void);			// 全屏高动态模糊渲染

	void RenderBlurSceneNoShader(void);			// 全屏模糊渲染
	void RenderFinalSceneNoShader(void);		// 最终画面渲染
	void RenderTemporalBlurSceneNoShader(void);	// 全屏高动态模糊渲染

	bool IsPixWater(void);
	bool IsShadowMap(void);
	bool IsBlur(void);
	bool IsCanUseShader(void)		{return m_bCanUseShader;}

	int	GetWaterType(void)			{return m_nWaterType;}
	int GetShadowType(void)			{return m_nShadowType;}
	int GetBlurType(void)			{return m_nBlurType;}

	bool SetShadowType(int nType)	{m_nShadowType = nType;return true;}

	void SetBlurVal(float fVal);
	void SetBrightVal(float fVal);
	void SetTintColol(float fR,float fG,float fB);

	void UpdataSceneEffect();
	void SetSceneEffectOn(DWORD dwEffect);
	void SetSceneEffectOff(DWORD dwEffect);
	void SetSceneEffect(DWORD dwEffect, DWORD dwVal);

	// water
	bool SetWaterType(int nType)	{m_nWaterType = nType;return true;}

	void SetWaterColor(DWORD dwColor);
	DWORD GetWaterColor(){ return m_dwWaterColor; }

	void SetWaterHeight(float fHeight);
	
	void SetFresnelPower( float fP ){ m_fFresnelPower = fP; }
	float GetFresnelPower(){ return m_fFresnelPower; }

	void SetFresnelScale(float val) { m_fFresnelScale = val; }
	float GetFresnelScale() const { return m_fFresnelScale; }

	void SetWaterBlendWeight(float val) { m_fWaterBlendWeight = val; }
	float GetWaterBlendWeight() const { return m_fWaterBlendWeight; }

	void Enable(bool bVal)		{m_bCanUseShader = bVal&CheckShaderVersion();}

    // add [5/30/2008 whu]
    void DestroyDeviceOjbects();


public:
	LPDIRECT3DVERTEXBUFFER9	g_pQuadVB[3];		//屏幕1/4的顶点缓冲	= NULL;

	IDirect3DVertexDeclaration9* m_pBlendDecl;// Vertex declaration for the Blend volume
	ID3DXEffect*		m_pSceneEffect;		// scene渲染时用的效果
	ID3DXEffect*		m_pWorldEffect;		// world渲染时用的效果

	LPDIRECT3DTEXTURE9	m_pWaterRefTex;		// 水渲染到贴图 
	LPDIRECT3DSURFACE9	m_pWaterRefSur;		// 水渲染到贴图的表面

	// water normal [11/25/2010 zhangjiayi]
	LPDIRECT3DTEXTURE9 m_pWaterNormalTex1;
	LPDIRECT3DTEXTURE9 m_pWaterNormalTex2;

	// 水面反光暂时不用，先注掉[QL]
	//LPDIRECT3DTEXTURE9	m_pWaterRefraTex;		// 水渲染到贴图 
	LPDIRECT3DSURFACE9	m_pWaterRefraSur;		// 水渲染到贴图的表面

	LPDIRECT3DTEXTURE9	m_pWaterLightTex;	// 水光渲染到贴图 
	LPDIRECT3DSURFACE9	m_pWaterLightSur;	// 水光渲染到贴图的表面

	
	D3DXHANDLE			m_hRenderWater;		// 渲染水

	D3DXHANDLE			m_hTime;			// 时间
	D3DXHANDLE			m_hWaterHeight;		// 水位
	D3DXHANDLE			m_hWaterColor;		// 水的颜色
	D3DXHANDLE			m_hTxReflect;		// 反射纹理
	D3DXHANDLE			m_hTxRefract;		// 折射纹理
	D3DXHANDLE			m_hTxWaterLight;	// 反射纹理
	D3DXHANDLE			m_hFresnelPower;
	D3DXHANDLE			m_hFresnelScale;
	D3DXHANDLE			m_hWaterBlendWeight;

	D3DXHANDLE			m_hWorldViewPro;	// 句柄
	D3DXHANDLE			m_hMaterialDiffuse;	// 句柄
	D3DXHANDLE			m_hMaterialAmbient;	// 句柄
	D3DXHANDLE			m_hLightDir;		// 句柄
	D3DXHANDLE			m_hMatBlendArray;	// 句柄

	D3DXHANDLE			m_hBlend;			// 句柄
	D3DXHANDLE			m_hBright;			// 句柄

	D3DXHANDLE			m_hRenderBlend;		// 句柄
	D3DXHANDLE			m_hMaterialAlpha;		// 句柄

protected:
	D3DXHANDLE			m_hRenderScene;		// 渲染屏幕
	D3DXHANDLE			m_hRenderSToD;		// 渲染句柄-s2d
	D3DXHANDLE			m_hRenderDToS;		// 渲染句柄-d2s
	D3DXHANDLE			m_hRenderFinalScene;// 渲染句柄-最终
	//RenderScene
	D3DXHANDLE			m_hRS_TemporalBlur;	// 渲染句柄-最终

	D3DXHANDLE			m_hTintColol;		// 句柄-色调颜色

	// 泛光渲染到贴图功能太老，删除[QL]
	//LPDIRECT3DTEXTURE9	m_pSceneTexture;	// 泛光渲染到贴图 
	//LPDIRECT3DTEXTURE9	m_pSceneTexture0;	// 泛光渲染模糊的贴图
	//LPDIRECT3DTEXTURE9	m_pSceneTexture1;	// 泛光渲染模糊的贴图
	//LPDIRECT3DSURFACE9	m_pSceneSurface;	// 泛光渲染到贴图的表面
	//LPDIRECT3DSURFACE9	m_pSceneSurface0;	// 泛光渲染模糊的表面
	//LPDIRECT3DSURFACE9	m_pSceneSurface1;	// 泛光渲染模糊的表面

	DWORD				m_dwSceneEffect;	// 屏幕渲染效果

	bool				m_bCanUseShader;	// 能否使用Shader
	bool				m_bIsUseingShader;	// 是否正在使用Shader

	int					m_nWaterType;		// 水渲染类型
	int					m_nShadowType;		// 阴影渲染类型
	int					m_nBlurType;		// 模糊等级

	float				m_fBrightVal;		// 亮度
	float				m_fBlurVal;			// 模糊因素
	D3DXVECTOR4			m_vTintColol;		// 偏色
	D3DXVECTOR4			m_vAddColol;		// 加减色

	bool				m_bShadowMap;		// 实时阴影开关
	bool				m_bPixWater;		// 水渲染开关
	bool				m_bBlur;			// 模糊开关
	// water
	DWORD				m_dwWaterColor;		// 水的颜色
	float				m_fWaterHeight;		// 水位
	float				m_fFresnelPower;	
	float				m_fFresnelScale;
	float				m_fWaterBlendWeight;
	//private:
};

CShaderMgr* GetShaderMgr();