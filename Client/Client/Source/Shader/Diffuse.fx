
struct OutputDiffuse_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
	float3 lightDir : TEXCOORD1;
	float3 normal	: TEXCOORD2;
#if OutputDepth == 1
	float  depth	: TEXCOORD3;
#endif
	float2 TexCoord : TEXCOORD4;
	float2 ObjDepth	: TEXCOORD5;
};

// vertex shader.
OutputDiffuse_vs Diffuse_vs( Input_vs In )
{
	OutputDiffuse_vs Out = (OutputDiffuse_vs)0;
	
	Out.position = mul( In.position, worldViewProj );
	Out.uv		 = In.uv;
	Out.diffuse  = In.diffuse;
	Out.lightDir = -lightDir;
	Out.normal   = mul( In.normal, world );
	
	Out.TexCoord = mul( In.position, g_matShadowTex ).xy;
	Out.ObjDepth = mul( In.position, g_mLightViewProj ).zw;
	
#if OutputDepth == 1
	Out.depth = Out.position.w / g_FarPlane;
#endif
	
	return Out;
}

// struct InputDiffuse_vs
// {
// 	float4 diffuse	: COLOR0;
// 	float2 uv		: TEXCOORD0;
// 	float3 lightDir : TEXCOORD1;
// 	float3 normal	: TEXCOORD2;
// #if OutputDepth == 1
// 	float  depth	: TEXCOORD3;
// #endif
// };

// pixel shader.
Output_ps Diffuse_ps( OutputDiffuse_vs In )
{
	Output_ps Out = (Output_ps)0;
	
	float4 baseColor = tex2D( baseSam, In.uv );
	float4 diff = {1.0f, 1.0f, 1.0f, 1.0f};	
	
	CalcDiffuseLightShadow( In.ObjDepth, In.TexCoord, normalize( In.lightDir ), normalize( In.normal ), lightAmbient, lightDiffuse, diff );
	
	float3 color = In.diffuse.rgb * baseColor.rgb * diff.rgb;
	
	Out.color = float4( color, baseColor.a * In.diffuse.a );
	
#if OutputDepth == 1
	Out.depth = float4( In.depth, In.depth, In.depth, 1.0f );
#endif
	
	return Out;
}
