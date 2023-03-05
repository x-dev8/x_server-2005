
float4x4 lightViewProj;
float4x3 boneWorldMatrix[56];

void SkeletonShadow_vp(float4 position : POSITION,
				float4 blendWeights : BLENDWEIGHT,
				float4 blendIndices : BLENDINDICES,

				out float4 oPosition : POSITION,
				out float2 oDepth	 : TEXCOORD0 )
{

	float3  Pos = 0.0f;
    
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 4; iBone++)
    {
        Pos += mul(position, boneWorldMatrix[blendIndices[iBone]]).xyz * blendWeights[iBone];
    }

    // transform position from world space into view and then projection space
    oPosition = mul(float4(Pos.xyz, 1.0f), lightViewProj);
    
	oDepth    = oPosition.zw;
}

void SkeletonShadow_fp(float4 position  : POSITION,
				float2 depth	: TEXCOORD0,

				out float4 oColor : COLOR0)
{
	float fColor = min( 1, depth.x / depth.y );
	fColor = max( 0, fColor );
	oColor = float4( fColor,fColor, fColor, 1.f );
}
