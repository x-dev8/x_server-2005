
#define OutputDepth 1

float4x4 world;
float4x4 view;
float4x4 projection;
float4x4 worldViewProj;
float4	 globalAmbient = { 0.3f, 0.3f, 0.3f, 0.3f };
float4	 ambient  = { 0.3f, 0.3f, 0.3f, 0.3f };
float4	 diffuse  = { 1.0f, 1.0f, 1.0f, 1.0f };
float	 specular = 1.0f;
float    power    = 20.0f;
float3	 eye;
float3	 lightDir = { 0,-1,0 };
float4   lightColor = { 1,1,1,1 };
float4	 lightAmbient  = { 0.3f, 0.3f, 0.3f, 0.3f };
float4	 lightDiffuse  = { 1.0f, 1.0f, 1.0f, 1.0f };
float4	 lightSpecular = { 1.0f, 1.0f, 1.0f, 1.0f };
float	 time;
float	 g_FarPlane = 200.f;
bool	 g_bRenderShadow;


float4x4 g_matShadowTex;
float4x4 g_mLightViewProj;


float	 alpha = 1.0f;

#define SMAP_SIZE 2048
#define SHADOW_EPSILON 0.00005f

static const int g_cBlurSize = 4;
float2 BlurUV[ g_cBlurSize ] = 
{
	{ 0, 0 },
	{ 1.0 / SMAP_SIZE, 0 },
	{ 0, 1.0 / SMAP_SIZE },
	{ 1.0 / SMAP_SIZE, 1.0 / SMAP_SIZE }	
};


//----------------------------------------------------
//		Texture
//----------------------------------------------------
texture baseTex;
texture brightTex;
texture animTex;

/** shadow map
*/
texture g_txShadowMap : register(s3);

sampler g_samShadowMap =
sampler_state
{
    Texture = <g_txShadowMap>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};


sampler baseSam = sampler_state
{
	Texture = <baseTex>;
    MinFilter = Linear;
    //MipFilter = Linear;
    MagFilter = Linear;
    //AddressU = Wrap;
    //AddressV = Wrap;
};

sampler brightSam = sampler_state
{
	Texture = <brightTex>;
    MinFilter = Linear;
    MipFilter = Linear;
    MagFilter = Linear;
    //AddressU = Wrap;
    //AddressV = Wrap;
};

sampler animSam = sampler_state
{
	Texture = <animTex>;
    MinFilter = Linear;
    MipFilter = Linear;
    MagFilter = Linear;
    //AddressU = Wrap;
    //AddressV = Wrap;
};


//----------------------------------------------------
//		Output Struct
//----------------------------------------------------
struct Input_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float3 normal	: NORMAL;
	float2 uv		: TEXCOORD0;
};

struct Output_ps
{
	float4 color : COLOR0;
#if OutputDepth == 1
	float4 depth : COLOR1;
#endif
};

struct ObjectOutput_ps
{
	float4 StdColor : COLOR0;
	float4 PosColor : COLOR1;
};

//----------------------------------------------------
//		Shader Model 2
//----------------------------------------------------

#include "Lighting.fx"
#include "NoLighting.fx"
#include "AlphaTest.fx"
#include "Diffuse.fx"
#include "Specular.fx"
#include "SkyBox.fx"
#include "Collision.fx"
#include "Particle.fx"

technique NoLighting
{
	pass p0
	{
		VertexShader = compile vs_2_0 NoLight_vs();
		PixelShader  = compile ps_2_0 NoLight_ps();
	}
}

technique Diffuse
{
	pass p0
	{
		VertexShader = compile vs_2_0 Diffuse_vs();
		PixelShader  = compile ps_2_0 Diffuse_ps();
	}
}

technique Specular
{
	pass p0
	{
		VertexShader = compile vs_2_0 Specular_vs();
		PixelShader  = compile ps_2_0 Specular_ps();
	}
}


technique AlphaTest
{
	pass p0
	{
		VertexShader = compile vs_2_0 AlphaTest_vs();
		PixelShader  = compile ps_2_0 AlphaTest_ps();
		AlphaTestEnable = TRUE;
		AlphaRef = 128;
		AlphaFunc = GREATER;
		//AlphaBlendEnable = false;
	}
}

technique SkyBox
{
	pass p0
	{
		VertexShader = compile vs_2_0 SkyBox_vs();
		PixelShader  = compile ps_2_0 SkyBox_ps();
		FogEnable = false;
		ZEnable = false;
		ZWriteEnable = false;
        CULLMODE = CW;
        AlphaBlendEnable = true;
        AlphaTestEnable = false;
        Lighting = false;
	}
}

technique Collision
{
	pass p0
	{
		VertexShader = compile vs_2_0 Collision_vs();
		PixelShader  = compile ps_2_0 Collision_ps();
	}
}

technique Particle
{
	pass p0
	{
		VertexShader = compile vs_2_0 Particle_vs();
		PixelShader  = compile ps_2_0 Particle_ps();
	}
}

