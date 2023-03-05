
struct OutputSkyBox_vs
{
	float4 position : POSITION;
	float2 uv		: TEXCOORD0;
#if OutputDepth == 1
	float  depth	: TEXCOORD1;
#endif
};

// vertex shader.
OutputSkyBox_vs SkyBox_vs( Input_vs In )
{
	OutputSkyBox_vs Out = (OutputSkyBox_vs)0;
	
	Out.position = mul( In.position, worldViewProj );
	Out.uv		 = In.uv;
	
#if OutputDepth == 1
	Out.depth = Out.position.w / g_FarPlane;
#endif
	
	return Out;
}

struct InputSkyBox_vs
{
	float2 uv		: TEXCOORD0;
#if OutputDepth == 1
	float  depth	: TEXCOORD1;
#endif
};

// vertex shader.
Output_ps SkyBox_ps( OutputSkyBox_vs In )
{
	Output_ps Out = (Output_ps)0;
	
	Out.color = tex2D( baseSam, In.uv );
	
#if OutputDepth == 1
	Out.depth = float4( In.depth, In.depth, In.depth, 1.0f );
#endif

	return Out;
}
