//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
texture g_txScene : TEXTURE;		// texture for scene rendering
float4x4 g_mWorld : WORLD : register(c0); // World matrix for object
float4x4 g_mView : VIEW : register(c4);			// World matrix for object
float4x4 g_mProj : PROJECTION : register(c8);		// World matrix for object
float3	 LightDirection;
float4	 LightAmbientColor;
float4	 LightDiffuseColor;
float4	 LightSpecularColor;
float3	 g_PlayerPos;
float	 g_FarPlane;

//-----------------------------------------------------------------------------
// Texture samplers
//-----------------------------------------------------------------------------
sampler g_samScene =
sampler_state
{
    Texture = <g_txScene>; 
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;

};

struct ps_Output
{
	float4 StdColor : COLOR0;
	float4 PosColor : COLOR1;
};

//-----------------------------------------------------------------------------
// Name: VS_HWInstancing
// Type: Vertex shader (HW Instancing)
// Desc: This shader computes standard transform and lighting for unlit, texture-mapped triangles.
//-----------------------------------------------------------------------------
void VS_HWInstancing( float4 vPos : POSITION,
					float3 vNormal : NORMAL,
					float4 vColor : COLOR0,
					float2 vTex0 : TEXCOORD0,
					float4 vBoxInstance : COLOR1,
					float  fScale : COLOR2,
					float  fShadow : COLOR3,
					out float4 oPos : POSITION,
					out float2 oTex0 : TEXCOORD0,
					out float  oPosInfo : COLOR0,
					out float4 oLight : COLOR1
					
					 )
{
	float4x4 Scale;
	Scale[0] = float4(fScale, 0, 0, 0);
	Scale[1] = float4(0, fScale, 0, 0);
	Scale[2] = float4(0, 0, fScale, 0);
	Scale[3] = float4(0, 0, 0, 1);

	float4 vRotatedPos = vPos;
	//set rotate	
	vBoxInstance.w *= 2 * 3.1415;
	vRotatedPos.x = vPos.x * cos(vBoxInstance.w) - vPos.y * sin(vBoxInstance.w);
	vRotatedPos.y = vPos.y * cos(vBoxInstance.w) + vPos.x * sin(vBoxInstance.w);
	//set scale
	vRotatedPos= mul( vRotatedPos, Scale );	
	
	vRotatedPos += float4( vBoxInstance.xyz , 0 );	
	//受力变形
	float3 centerPos = vRotatedPos.xyz;
	float3 vPressPos=float3(g_PlayerPos.x,g_PlayerPos.y,g_PlayerPos.z + 2.f);
	float fDistance=distance(vPressPos,centerPos);
	float3 vOffset = float3(0.f,0.f,0.f);
	if (fDistance<1.6f)
	vOffset+=normalize(centerPos-vPressPos)*(1.3f-fDistance);
	vRotatedPos += float4(vOffset.xy, 0, 0);

	// Transform the position from object space to homogeneous projection space
	oPos = mul( vRotatedPos, g_mWorld );
	oPos = mul( oPos, g_mView );	
	oPos = mul( oPos, g_mProj );
	oPosInfo = oPos.w / g_FarPlane;
	
	// Just copy the texture coordinate & color through
	oTex0 = vTex0;
	
	float3 l = normalize( -LightDirection );
	float  ndotl = saturate(dot( vNormal, l ));
	oLight = LightAmbientColor + LightDiffuseColor * ndotl;
	oLight.rgb *= fShadow;
	
}

//-----------------------------------------------------------------------------
// Name: PS
// Type: Pixel shader
// Desc: This shader outputs the pixel's color by modulating the texture's
//		 color with diffuse material color
//-----------------------------------------------------------------------------
ps_Output PS(	float2 vTex0 : TEXCOORD0 , float vPosInfo : COLOR0, float4 vLight : COLOR1)
{
	ps_Output outColor = (ps_Output)0;
	outColor.StdColor = tex2D( g_samScene, vTex0 ) * vLight;
    outColor.PosColor = float4( vPosInfo,vPosInfo,vPosInfo, 1.f );
    
    return outColor;
    
}

float4 PS_Low(	float2 vTex0 : TEXCOORD0 , float vPosInfo : COLOR0, float4 vLight : COLOR1) : COLOR0
{	
	return tex2D( g_samScene, vTex0 ) * vLight;    
}


//-----------------------------------------------------------------------------
// Name: THW_Instancing
// Type: Technique
// Desc: Renders scene through Hardware instancing
//-----------------------------------------------------------------------------
technique THW_Instancing_High
{
    pass P0
    {
        VertexShader = compile vs_2_0 VS_HWInstancing();
        PixelShader  = compile ps_2_0 PS();
        ZEnable = true;
        ZWriteEnable = false;
        AlphaBlendEnable = TRUE;
		AlphaTestEnable = false; 
		AlphaRef = 128; 
		AlphaFunc = GREATER; 
		FogEnable = true;
    }
}

technique THW_Instancing_Low
{
    pass P0
    {
        VertexShader = compile vs_2_0 VS_HWInstancing();
        PixelShader  = compile ps_2_0 PS_Low();
        ZEnable = true;
         ZWriteEnable = false;
        AlphaBlendEnable = TRUE;
		AlphaTestEnable = false; 
		AlphaRef = 128; 
		AlphaFunc = GREATER; 
		FogEnable = true;
    }
}