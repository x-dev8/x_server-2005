
float4 particleColor[3];

struct InputParticle_vs
{
	float4 position : POSITION;
	//float4 diffuse	: COLOR0;
	float2  tc		: BLENDWEIGHT;
	float2 uv		: TEXCOORD0;
};

struct OutputParticle_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
};

// vertex shader.
OutputParticle_vs Particle_vs( InputParticle_vs In )
{
	OutputParticle_vs Out = (OutputParticle_vs)0;

	Out.position = mul( In.position, worldViewProj );
	//Out.diffuse  = In.diffuse;
	int index = In.tc.y;
	Out.diffuse  = lerp(particleColor[index], particleColor[index + 1], In.tc.x);
	Out.diffuse.a *= alpha;
	Out.uv		 = In.uv;
	
	return Out;
}

struct InputParticle_ps
{
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
};

// pixel shader.
Output_ps Particle_ps( InputParticle_ps In )
{
	Output_ps Out = (Output_ps)0;

	float4 baseColor = tex2D( baseSam, In.uv );
	float3 color = baseColor.rgb * In.diffuse.rgb;
	
	Out.color = float4( color, baseColor.a * In.diffuse.a );
	return Out;
}
