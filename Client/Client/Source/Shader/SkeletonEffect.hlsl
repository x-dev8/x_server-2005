
float4x4 viewProj;
float4 lightDiffuse;
float alpha;
float4x3 boneWorldMatrix[56];

void SkeletonEffect_vp(
				float4 position   : POSITION,
				float4 blendWeights : BLENDWEIGHT,
				float4 blendIndices : BLENDINDICES,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0
				)
{
	oUV		  = uv;
	oDiffuse  = lightDiffuse;
	oDiffuse.a *= alpha;

	float3  Pos = 0.0f;
    
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 4; iBone++)
    {
        Pos += mul(position, boneWorldMatrix[blendIndices[iBone]]).xyz * blendWeights[iBone];
    }

    // transform position from world space into view and then projection space
    oPosition = mul(float4(Pos.xyz, 1.0f), viewProj);
}

void SkeletonEffect_fp(
				float4 diffuse  : COLOR0,
				float2 uv		: TEXCOORD0,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0)
				)
{
	float4 baseColor = tex2D( baseSam, uv );
	oColor.rgb = diffuse.rgb * baseColor.rgb;
	oColor.a   = baseColor.a * diffuse.a;
}
