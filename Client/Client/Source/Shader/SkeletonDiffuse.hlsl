
float4x4 viewProj;
float3 lightDir;
float4 lightAmbient;
float4 lightDiffuse;
float alpha;
float4x4 shadowTexMatrix;
float4x4 lightViewProj;
bool bRenderShadow;
float4x3 boneWorldMatrix[56];

void SkeletonDiffuse_vp(
				float4 position   : POSITION,
				float4 blendWeights : BLENDWEIGHT,
				float4 blendIndices : BLENDINDICES,
				float3 normal	  : NORMAL,
				float4 diffuse	  : COLOR0,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0,
				out float3 oLightDir : TEXCOORD1,
				out float3 oNormal   : TEXCOORD2,
				out float2 oTexCoord : TEXCOORD3,
				out float2 oObjDepth : TEXCOORD4
				)
{
	oUV		  = uv;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;
	oLightDir = -lightDir;

	float3  Pos = 0.0f;
    float3  Normal = 0.0f;
    
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 4; iBone++)
    {
        Pos += mul(position, boneWorldMatrix[blendIndices[iBone]]).xyz * blendWeights[iBone];
        Normal += mul(normal, boneWorldMatrix[blendIndices[iBone]]) * blendWeights[iBone];
    }
    
	float4 worldPos = float4(Pos.xyz, 1.0f);

    // transform position from world space into view and then projection space
    oPosition = mul(worldPos, viewProj);
    
    // normalize normals
    oNormal = normalize(Normal);
	
	oTexCoord = mul(worldPos, shadowTexMatrix).xy;
	oObjDepth = mul(worldPos, lightViewProj).zw;
}

void SkeletonDiffuse_fp(
				float4 diffuse  : COLOR0,
				float2 uv		: TEXCOORD0,
				float3 lightDir : TEXCOORD1,
				float3 normal   : TEXCOORD2,
				float2 TexCoord : TEXCOORD3,
				float2 ObjDepth : TEXCOORD4,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0),
				uniform sampler2D shadowMapSam : register(s1)
				)
{
	float4 baseColor = tex2D( baseSam, uv );
	float4 diff = {1.0f, 1.0f, 1.0f, 1.0f};	
		
	float ndotl = saturate( dot( normalize(normal), normalize(lightDir) ) );	

	float LightAmount = 1.0f;

	if ( bRenderShadow && TexCoord.x>0&&TexCoord.x<1&&TexCoord.y>0&&TexCoord.y<1 )
	{
		float B = min( 1, ObjDepth.x / ObjDepth.y );

		float2 BlurUV[ 4 ] = 
		{
			{ 0, 0 },
			{ 1.0 / 2048, 0 },
			{ 0, 1.0 / 2048 },
			{ 1.0 / 2048, 1.0 / 2048 }	
		};
		
		float Color = 0;
		for( int i = 0 ; i < 4 ; ++ i )
		{
			Color += (tex2D( shadowMapSam, TexCoord.xy + BlurUV[i] ).r + 0.00005f < B ) ? 0.f: 1.0f;  
		}	               

		LightAmount = Color / 4;

	}
	diff = ndotl * lightDiffuse * LightAmount + lightAmbient;
	
	oColor.rgb = diffuse.rgb * baseColor.rgb * diff.rgb;
	oColor.a   = baseColor.a * diffuse.a;
}
