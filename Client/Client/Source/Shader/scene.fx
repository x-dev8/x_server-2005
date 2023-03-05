//--------------------------------------------------------------------------------------
// File: scene.fx
//
// 用来实现scene的特殊效果,包括全屏泛光,水底世界,灵魂世界等
// 
//--------------------------------------------------------------------------------------


#define LIGHT_FALLOFF 1.2f


//--------------------------------------------------------------------------------------
// 全局变量
//--------------------------------------------------------------------------------------
texture	g_txScene;					// 屏幕纹理
texture	g_txScene0;					// 屏幕纹理
texture	g_txScene1;					// 屏幕纹理
texture	g_txBufferScene;			// 屏幕纹理
texture	g_txWater;					// 水折射效果法线图
float	g_fTime;					// 时间
float 	g_fBright;					// 发亮度
float 	g_fBlur;					// 模糊度
float 	g_fBlend;					// 混合比
bool	g_bBright;
bool	g_bMono;
bool	g_bInv;
bool	g_bNoise;
bool	g_bTint;
float3	g_vTintColol;

//-----------------------------------------------------------------------------
// 纹理Texture samplers
//-----------------------------------------------------------------------------
sampler g_samScene =
sampler_state
{
    Texture = <g_txScene>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler g_samScene0 =
sampler_state
{
    Texture = <g_txScene0>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler g_samScene1 =
sampler_state
{
    Texture = <g_txScene1>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler g_samBufferScene =
sampler_state
{
    Texture = <g_txBufferScene>;
    //MinFilter = Linear;
    //MagFilter = Linear;
    //MipFilter = Linear;
};
sampler g_samWater =
sampler_state
{
    Texture = <g_txWater>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
static const int g_cKernelSize = 13;

float2 PixelKernelH[g_cKernelSize] =
{
	{ -6, 0 },
	{ -5, 0 },
	{ -4, 0 },
	{ -3, 0 },
	{ -2, 0 },
	{ -1, 0 },
	{  0, 0 },
	{  1, 0 },
	{  2, 0 },
	{  3, 0 },
	{  4, 0 },
	{  5, 0 },
	{  6, 0 },
};

float2 PixelKernelV[g_cKernelSize] =
{
	{ 0, -6 },
	{ 0, -5 },
	{ 0, -4 },
	{ 0, -3 },
	{ 0, -2 },
	{ 0, -1 },
	{ 0,  0 },
	{ 0,  1 },
	{ 0,  2 },
	{ 0,  3 },
	{ 0,  4 },
	{ 0,  5 },
	{ 0,  6 },
};

float2 TexelKernelH[g_cKernelSize]
<
	string ConvertPixelsToTexels = "PixelKernelH";
>;

float2 TexelKernelV[g_cKernelSize]
<
	string ConvertPixelsToTexels = "PixelKernelV";
>;

static const float BlurWeights[g_cKernelSize] = 
{
	0.002216,
	0.008764,
	0.026995,
	0.064759,
	0.120985,
	0.176033,
	0.199471,
	0.176033,
	0.120985,
	0.064759,
	0.026995,
	0.008764,
	0.002216,
};

float BloomScale = 1.0f;


float3 LuminanceConv = { 0.2125f, 0.7154f, 0.0721f };
//--------------------------------------------------------------------------------------
// shader 函数
//--------------------------------------------------------------------------------------

void VertDown4x( float4 vPos : POSITION,
				float2 vTexUV : TEXCOORD0,
				out float4 oPos : POSITION,
				out float2 oTexUV : TEXCOORD0)
{
	oPos=vPos;
	oTexUV=vTexUV;
}

void VertScene( float4 vPos : POSITION,
				float2 vTexUV : TEXCOORD0,
				out float4 oPos : POSITION,
				out float2 oTexUV : TEXCOORD0)
{
	oPos=vPos;
	oTexUV=vTexUV;
}

//横向模糊
float4 PixHBlur( float2 Tex : TEXCOORD0 ) : COLOR0
{
	//return tex2D( g_samScene0, Tex);
	float4 Color = 0;
    for (int i = 0; i < g_cKernelSize; i++)
	{    
		Color += tex2D( g_samScene0, Tex + TexelKernelH[i].xy ) * BlurWeights[i];
	}
	return Color;
}

//纵向模糊
float4 PixVBlur( float2 Tex : TEXCOORD0 ) : COLOR0
{
	//return tex2D( g_samScene1, Tex);
	float4 Color = 0;
	for (int i = 0; i < g_cKernelSize; i++)
	{    
		Color += tex2D( g_samScene1, Tex + TexelKernelV[i].xy ) * BlurWeights[i];
	}
	//return saturate(1-pow(1-Color,2));
	return Color;
}

float3 PixColor(float3 color)
{
	if (g_bBright) color += g_fBright;
	if (g_bMono) color  = dot( color, LuminanceConv );
	if (g_bInv)  color  = 1-color;
	if (g_bNoise) color= noise(100);
	if (g_bTint) color *= g_vTintColol;
	//color +=sin(9000)*1;
    return (color);
}

float4 Pix_All( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	return float4(PixColor((float3)tex2D( g_samScene, Tex)),1);
}

float4 Pix_Blur( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	float3 color0 = tex2D( g_samScene, Tex);
	float3 color1 = tex2D( g_samScene0, Tex);

	float3 color  = lerp(PixColor(color0),color1,g_fBlend);

	return float4(color,1);
}

float4 Pix_TBlur( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	float3 color0 = tex2D( g_samScene, Tex);
	float3 color1 = tex2D( g_samScene0, Tex);

	float3 color  = lerp(PixColor(color0),color1,g_fBlend);

	return float4(color,1);
}

//混合
float4 PixBlend( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	float4 color0 = tex2D( g_samScene, Tex);
	float4 color1 = tex2D( g_samScene0, Tex);

	float4 color  = lerp(color0,color1,g_fBlend);//g_fMix0*(g_fBright-g_fBlur*g_fBright)+color1*g_fBlur*g_fBright//lerp(color0,color1,g_fBlur)*g_fBright;
	color*=min(max(sin(Tex.y*1000),0.95),1);
	color=dot( color.xyz, LuminanceConv )*float4(1,0.9,0.7,1);
	return color;
}

//黑白
float4 PixMonochrome( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	return dot( (float3)tex2D( g_samScene, Tex ), LuminanceConv );
}
//黑白+混合
float4 PixMonochrome_Blend( in float2 Tex : TEXCOORD0 ) : COLOR0
{
	float4 color0 = tex2D( g_samScene, Tex);
	float4 color1 = tex2D( g_samScene0, Tex);
	float4 color  = lerp(color0,color1,g_fBlend);
	return dot( color.xyz, LuminanceConv );
}

void VertWater( float4 vPos : POSITION,
				float2 vTexUV : TEXCOORD0,
				out float4 oPos : POSITION,
				out float2 oTexUV : TEXCOORD0,
				out float2 oWaterUV : TEXCOORD1)
{
	oPos=vPos;
	oTexUV=vTexUV;
	oWaterUV=(oTexUV)+g_fTime/10;
}

//画面扭曲--水下
float4 PixUnderWater( in float2 Tex : TEXCOORD0, in float2 oWaterUV : TEXCOORD1 ) : COLOR0
{
	float4 bump = tex2D(g_samWater, oWaterUV);
	bump = (bump-0.5)/16;
	Tex+=bump.xy;
	return tex2D( g_samBufferScene, Tex)*0.8+float4(0.1,0.4,0.4,1.0)*0.5;
}

//--------------------------------------------------------------------------------------
// 技术
//--------------------------------------------------------------------------------------
technique RenderUnderWater
{
    pass P0
    {
        VertexShader = compile vs_2_0 VertWater();
        PixelShader  = compile ps_2_0 PixUnderWater();
    }
}

technique RenderSToD
{
    pass P0
    {
        PixelShader  = compile ps_2_0 PixHBlur();
    }
}

technique RenderDToS
{
    pass P0
    {
        PixelShader  = compile ps_2_0 PixVBlur();
    }
}

technique RenderBlendScene
{
    pass P0
    {
        PixelShader  = compile ps_2_0 Pix_Blur();
    }
}

technique RS_Blur
{
    pass P0
    {
        PixelShader  = compile ps_2_0 Pix_Blur();
    }
}

technique RS_TBlur
{
    pass P0
    {
        PixelShader  = compile ps_2_0 Pix_TBlur();
    }
}


technique RS_Others
{
    pass P0
    {
        //VertexShader = compile vs_2_0 VertScene();
        PixelShader  = compile ps_2_0 Pix_All();
    }
}