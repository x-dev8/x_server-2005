
struct OutputAlphaTest_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
#if OutputDepth == 1
	float  depth	: TEXCOORD1;
#endif
};

// vertex shader.
OutputAlphaTest_vs AlphaTest_vs( Input_vs In )
{
	OutputAlphaTest_vs Out = (OutputAlphaTest_vs)0;
	
	Out.position = mul( In.position, worldViewProj );
	Out.uv		 = In.uv;
	
	float3 l = normalize( -lightDir );
	float3 n = normalize( mul( In.normal, world ).xyz );
	
	CalcDiffuseLight( l, n, lightAmbient * 2.0f, lightDiffuse, Out.diffuse );
	Out.diffuse *= In.diffuse;
	Out.diffuse.a = In.diffuse.a;
	
#if OutputDepth == 1
	Out.depth = Out.position.w / g_FarPlane;
#endif
	
	return Out;
}

struct InputAlphaTest_ps
{
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
#if OutputDepth == 1
	float  depth	: TEXCOORD1;
#endif
};

// pixel shader.
Output_ps AlphaTest_ps( InputAlphaTest_ps In )
{
	Output_ps Out = (Output_ps)0;

	float4 baseColor = tex2D( baseSam, In.uv );
	
	float3 color = baseColor.rgb * In.diffuse.rgb;
	
	Out.color = float4( color, baseColor.a * In.diffuse.a );
	
#if OutputDepth == 1
	Out.depth = float4( In.depth, In.depth, In.depth, 1.0f );
#endif

	return Out;
}
