//-----------------------------------------------------------------------------
// File: PP_LightShaft.fx
//
// Desc: fuck
//
// author: jiayi
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

Texture sunTex;

sampler2D sunSampler = sampler_state
{
	Texture = <sunTex>;
    ADDRESSU = CLAMP;
	ADDRESSV = CLAMP;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
	MIPFILTER = LINEAR;
};

float4x4 View;
float4x4 WorldViewProjection;

float Density = 3.f;
float Weight = 0.9f;
float Decay = 0.7f;
float Exposition = 0.5f;

float4 vDWDE = ( 0.8f, 0.3f, 1.1f, 0.08f );//density,weight,decay,exposition

float4 LightPosition;
float4 LightDirection;
float4 CameraPos;
float4 LightSSPosition;

int numSamples = 15;




//-----------------------------------------------------------------------------
// Pixel Shader: lightshaft
// Desc: lightshaft
//-----------------------------------------------------------------------------
float4 PostProcessPS( float2 texCoord : TEXCOORD0 ) : COLOR0
{
     float4 screenPos = mul(LightPosition.xyz, WorldViewProjection); 
     
     float2 ssPos = screenPos.xy / screenPos.w 
  			* float2(0.125,-0.125) + 0.125;
			
	float2 oriTexCoord = texCoord;
			
	float2 deltaTexCoord = (texCoord - ssPos);
    
    deltaTexCoord *= 1.0f / numSamples * vDWDE.x;
    
    float4 color = tex2D(g_samSrcColor, texCoord);    
    
    float illuminationDecay = 1.1f;
    
	for (int i=0; i < 12; i++)
	{		
		texCoord -= deltaTexCoord;
			
		float4 sample = tex2D(g_samSrcColor, texCoord);
		sample *= illuminationDecay * vDWDE.y;
		color += sample;
			
		illuminationDecay *= vDWDE.z;
	}
	float4 lightDir = LightDirection;
	
	float amount = dot(mul(lightDir.xyz,View), float3(0.0f,0.0f,1.f));
	
 	//amount = clamp( amount, -0.5f, 5.f );
// 	amount = abs( amount );
    return float4( saturate( amount - 0.3f ) * color.rgb * vDWDE.w, 1);
}


//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: Performs post-processing effect that converts a colored image to
//       black and white.
//-----------------------------------------------------------------------------
technique PostProcess
<    
	string Parameter0 = "LightPosition";
	string Parameter1 = "LightDirection";
	string Parameter2 = "vDWDE";	
	float4 Parameter2Def = float4( 0.6f, 0.3f, 1.1f, 0.07f );
    string Parameter3 = "View";
	string Parameter4 = "WorldViewProjection";
>
{
	
    pass p0 
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PostProcessPS();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
    pass p1
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PostProcessPS();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
    pass p2
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PostProcessPS();
        ZEnable = false;
        ZWRITEENABLE = false;
        FogEnable = false;
        AlphaBlendEnable = false;
        ALPHATESTENABLE = false;
        CullMode = CCW;
    }
//     pass p3
//     {
//         VertexShader = null;
//         PixelShader = compile ps_2_0 PostProcessPS();
//         ZEnable = false;
//         ZWRITEENABLE = false;
//         FogEnable = false;
//         AlphaBlendEnable = false;
//         ALPHATESTENABLE = false;
//         CullMode = CCW;
//     }
//     pass p4
//     {
//         VertexShader = null;
//         PixelShader = compile ps_2_0 PostProcessPS();
//         ZEnable = false;
//         ZWRITEENABLE = false;
//         FogEnable = false;
//         AlphaBlendEnable = false;
//         ALPHATESTENABLE = false;
//         CullMode = CCW;
//     }

}
