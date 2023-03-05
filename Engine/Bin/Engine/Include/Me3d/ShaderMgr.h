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
	eTemporalBlur	= 1<<1,	//ʱ��ģ��
	eBlur			= 1<<2,	//ģ��

	eBright			= 1<<3,	//����
	eMonochrome		= 1<<4,	//�Ҷ�
	eInverse		= 1<<5,	//��ɫ
	eNoise			= 1<<6,	//������
	eTint			= 1<<7	//��ƫɫ��ɫ��

};
enum ShadowType
{
	eShadow_None,
	eShadow_Fake,
	eShadow_RealTime,
	eShadow_Count
};

// shader����
class CShaderMgr
{

public:
	CShaderMgr(void);
	~CShaderMgr(void);

	bool CheckShaderVersion(void);				// ���shader�İ汾
	void InitShader(void);						// ��ʼ��shader
	void ResetEffect(void);						// ���¶���hlsl
	void ResetTexture(void);					// ����...

	void RenderScene();							// ȫ��shadow��Ⱦ
	void RenderScene(DWORD dwEffect);			// ȫ��shadow��Ⱦ
	void RenderBlurScene(void);					// ȫ��ģ����Ⱦ
	void RenderFinalScene(void);				// ���ջ�����Ⱦ
	void RenderTemporalBlurScene(void);			// ȫ���߶�̬ģ����Ⱦ

	void RenderBlurSceneNoShader(void);			// ȫ��ģ����Ⱦ
	void RenderFinalSceneNoShader(void);		// ���ջ�����Ⱦ
	void RenderTemporalBlurSceneNoShader(void);	// ȫ���߶�̬ģ����Ⱦ

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
	LPDIRECT3DVERTEXBUFFER9	g_pQuadVB[3];		//��Ļ1/4�Ķ��㻺��	= NULL;

	IDirect3DVertexDeclaration9* m_pBlendDecl;// Vertex declaration for the Blend volume
	ID3DXEffect*		m_pSceneEffect;		// scene��Ⱦʱ�õ�Ч��
	ID3DXEffect*		m_pWorldEffect;		// world��Ⱦʱ�õ�Ч��

	LPDIRECT3DTEXTURE9	m_pWaterRefTex;		// ˮ��Ⱦ����ͼ 
	LPDIRECT3DSURFACE9	m_pWaterRefSur;		// ˮ��Ⱦ����ͼ�ı���

	// water normal [11/25/2010 zhangjiayi]
	LPDIRECT3DTEXTURE9 m_pWaterNormalTex1;
	LPDIRECT3DTEXTURE9 m_pWaterNormalTex2;

	// ˮ�淴����ʱ���ã���ע��[QL]
	//LPDIRECT3DTEXTURE9	m_pWaterRefraTex;		// ˮ��Ⱦ����ͼ 
	LPDIRECT3DSURFACE9	m_pWaterRefraSur;		// ˮ��Ⱦ����ͼ�ı���

	LPDIRECT3DTEXTURE9	m_pWaterLightTex;	// ˮ����Ⱦ����ͼ 
	LPDIRECT3DSURFACE9	m_pWaterLightSur;	// ˮ����Ⱦ����ͼ�ı���

	
	D3DXHANDLE			m_hRenderWater;		// ��Ⱦˮ

	D3DXHANDLE			m_hTime;			// ʱ��
	D3DXHANDLE			m_hWaterHeight;		// ˮλ
	D3DXHANDLE			m_hWaterColor;		// ˮ����ɫ
	D3DXHANDLE			m_hTxReflect;		// ��������
	D3DXHANDLE			m_hTxRefract;		// ��������
	D3DXHANDLE			m_hTxWaterLight;	// ��������
	D3DXHANDLE			m_hFresnelPower;
	D3DXHANDLE			m_hFresnelScale;
	D3DXHANDLE			m_hWaterBlendWeight;

	D3DXHANDLE			m_hWorldViewPro;	// ���
	D3DXHANDLE			m_hMaterialDiffuse;	// ���
	D3DXHANDLE			m_hMaterialAmbient;	// ���
	D3DXHANDLE			m_hLightDir;		// ���
	D3DXHANDLE			m_hMatBlendArray;	// ���

	D3DXHANDLE			m_hBlend;			// ���
	D3DXHANDLE			m_hBright;			// ���

	D3DXHANDLE			m_hRenderBlend;		// ���
	D3DXHANDLE			m_hMaterialAlpha;		// ���

protected:
	D3DXHANDLE			m_hRenderScene;		// ��Ⱦ��Ļ
	D3DXHANDLE			m_hRenderSToD;		// ��Ⱦ���-s2d
	D3DXHANDLE			m_hRenderDToS;		// ��Ⱦ���-d2s
	D3DXHANDLE			m_hRenderFinalScene;// ��Ⱦ���-����
	//RenderScene
	D3DXHANDLE			m_hRS_TemporalBlur;	// ��Ⱦ���-����

	D3DXHANDLE			m_hTintColol;		// ���-ɫ����ɫ

	// ������Ⱦ����ͼ����̫�ϣ�ɾ��[QL]
	//LPDIRECT3DTEXTURE9	m_pSceneTexture;	// ������Ⱦ����ͼ 
	//LPDIRECT3DTEXTURE9	m_pSceneTexture0;	// ������Ⱦģ������ͼ
	//LPDIRECT3DTEXTURE9	m_pSceneTexture1;	// ������Ⱦģ������ͼ
	//LPDIRECT3DSURFACE9	m_pSceneSurface;	// ������Ⱦ����ͼ�ı���
	//LPDIRECT3DSURFACE9	m_pSceneSurface0;	// ������Ⱦģ���ı���
	//LPDIRECT3DSURFACE9	m_pSceneSurface1;	// ������Ⱦģ���ı���

	DWORD				m_dwSceneEffect;	// ��Ļ��ȾЧ��

	bool				m_bCanUseShader;	// �ܷ�ʹ��Shader
	bool				m_bIsUseingShader;	// �Ƿ�����ʹ��Shader

	int					m_nWaterType;		// ˮ��Ⱦ����
	int					m_nShadowType;		// ��Ӱ��Ⱦ����
	int					m_nBlurType;		// ģ���ȼ�

	float				m_fBrightVal;		// ����
	float				m_fBlurVal;			// ģ������
	D3DXVECTOR4			m_vTintColol;		// ƫɫ
	D3DXVECTOR4			m_vAddColol;		// �Ӽ�ɫ

	bool				m_bShadowMap;		// ʵʱ��Ӱ����
	bool				m_bPixWater;		// ˮ��Ⱦ����
	bool				m_bBlur;			// ģ������
	// water
	DWORD				m_dwWaterColor;		// ˮ����ɫ
	float				m_fWaterHeight;		// ˮλ
	float				m_fFresnelPower;	
	float				m_fFresnelScale;
	float				m_fWaterBlendWeight;
	//private:
};

CShaderMgr* GetShaderMgr();