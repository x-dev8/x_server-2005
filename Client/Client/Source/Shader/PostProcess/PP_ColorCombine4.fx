//-----------------------------------------------------------------------------
// File: PP_ColorCombine4.fx
//
// Desc: Effect file for image post-processing sample.  This effect contains
//       a single technique with a pixel shader that scales images up 4 times
//       and combines it with the original scene render buffer.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------




texture g_txSrcColor;
texture g_txSrcNormal;
texture g_txSrcPosition;
texture g_txSrcVelocity;

texture g_txSceneColor;
texture g_txSceneNormal;
texture g_txScenePosition;
texture g_txSceneVelocity;

sampler2D g_samSrcColor =
sampler_state
{
    Texture = <g_txSrcColor>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
    MIPMAPLODBIAS = 0.0f;
};
sampler2D g_samSrcNormal =
sampler_state
{
    Texture = <g_txSrcNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcPosition =
sampler_state
{
    Texture = <g_txSrcPosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcVelocity =
sampler_state
{
    Texture = <g_txSrcVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D g_samSceneColor = sampler_state
{
    Texture = <g_txSceneColor>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneNormal = sampler_state
{
    Texture = <g_txSceneNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samScenePosition = sampler_state
{
    Texture = <g_txScenePosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneVelocity = sampler_state
{
    Texture = <g_txSceneVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};




float2 PixelCoordsDownFilter[16] =
{
    { 1.5,  -1.5 },
    { 1.5,  -0.5 },
    { 1.5,   0.5 },
    { 1.5,   1.5 },

    { 0.5,  -1.5 },
    { 0.5,  -0.5 },
    { 0.5,   0.5 },
    { 0.5,   1.5 },

    {-0.5,  -1.5 },
    {-0.5,  -0.5 },
    {-0.5,   0.5 },
    {-0.5,   1.5 },

    {-1.5,  -1.5 },
    {-1.5,  -0.5 },
    {-1.5,   0.5 },
    {-1.5,   1.5 },
};

float2 TexelCoordsDownFilter[16]
<
    string ConvertPixelsToTexels = "PixelCoordsDownFilter";
>;



float3 DarkScale = float3(1.0f,1.0f,1.0f);
//-----------------------------------------------------------------------------
// Pixel Shader: Combine
// Desc: Combine the source image with the original image.
//-----------------------------------------------------------------------------
float4 Combine( float2 Tex : TEXCOORD0,
                float2 Tex2 : TEXCOORD1 ) : COLOR0
{
    float3 ColorOrig = tex2D( g_samSceneColor, Tex2 ) * DarkScale;

    ColorOrig += tex2D( g_samSrcColor, Tex );
    
    //ColorOrig = (ColorOrig.r + ColorOrig.b + ColorOrig.g) / 3.f;

    return float4( ColorOrig, 1.0f );
    //return tex2D( g_samSrcColor, Tex );
}




//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: Performs post-processing effect that down-filters.
//-----------------------------------------------------------------------------
technique PostProcess
<
	string Parameter0 = "DarkScale";
    float4 Parameter0Def = float4( 1.0f, 1.0f, 1.0f, 1.0f );
    int Parameter0Size = 3;
    string Parameter0Desc = " (float3)";
>
{
    pass p0
    <
        float fScaleX = 4.0f;
        float fScaleY = 4.0f;
    >
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 Combine();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
}
