
struct OutputSpecular_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
	float3 lightDir : TEXCOORD1;
	float3 normal	: TEXCOORD2;
	float3 viewDir	: TEXCOORD3;
#if OutputDepth == 1
	float  depth	: TEXCOORD4;
#endif
};

// vertex shader.
OutputSpecular_vs Specular_vs( Input_vs In )
{
	OutputSpecular_vs Out = (OutputSpecular_vs)0;
	
	float4 p	 = mul( In.position, world );
	
	Out.position = mul( In.position, worldViewProj );
	Out.uv		 = In.uv;
	Out.diffuse  = In.diffuse;
	Out.lightDir = -lightDir;
	Out.normal   = mul( In.normal, world );
	Out.viewDir  = eye - p;
	
#if OutputDepth == 1
	Out.depth = Out.position.w / g_FarPlane;
#endif
	
	return Out;
}

struct InputSpecular_ps
{
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
	float3 lightDir : TEXCOORD1;
	float3 normal	: TEXCOORD2;
	float3 viewDir	: TEXCOORD3;
#if OutputDepth == 1
	float  depth	: TEXCOORD4;
#endif
};

// pixel shader.
Output_ps Specular_ps( InputSpecular_ps In )
{
	Output_ps Out = (Output_ps)0;
	
	float4 baseColor = tex2D( baseSam, In.uv );
	
	float3 N = normalize( In.normal );
	float3 L = normalize( In.lightDir );
	
	float4 diff = {1.0f, 1.0f, 1.0f, 1.0f};
	float3 color;
	if (specular > 0.0f)
	{
		float4 spec = {1.0f, 1.0f, 1.0f, 1.0f};
		float4 bright = tex2D( brightSam, In.uv );
		float3 V = normalize( In.viewDir ); 
	
		CalcSpecularLight( L, N, V, lightAmbient, lightDiffuse, bright.r * specular, power,
			diff, spec );
	
		color = In.diffuse.rgb * baseColor.rgb * diff.rgb + spec.rgb;
	}
	else
	{
		CalcDiffuseLight( normalize( In.lightDir ), normalize( In.normal ), lightAmbient, lightDiffuse, diff );
	
		color = In.diffuse.rgb * baseColor.rgb * diff.rgb;
	}
	
	Out.color = float4( color, baseColor.a * In.diffuse.a );
	
#if OutputDepth == 1
	Out.depth = float4( In.depth, In.depth, In.depth, 1.0f );
#endif

	return Out;
}
