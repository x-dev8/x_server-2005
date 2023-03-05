
float4x4 viewProj;
float3 lightDir;
float4 lightAmbient;
float4 lightDiffuse;
float alpha;
float3 eye;
float specular;
float4x3 boneWorldMatrix[56];

void SkeletonSpecular_vp(float4 position : POSITION,
				float4 blendWeights : BLENDWEIGHT,
				float4 blendIndices : BLENDINDICES,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0,
				out float3 oLightDir : TEXCOORD1,
				out float3 oNormal   : TEXCOORD2,
				out float3 oViewDir  : TEXCOORD3 )
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

    // transform position from world space into view and then projection space
    oPosition = mul(float4(Pos.xyz, 1.0f), viewProj);
    
    // normalize normals
    oNormal = normalize(Normal);

	// view direction
	oViewDir  = eye - Pos;
}

void SkeletonSpecular_fp(float4 diffuse : COLOR0,
				float2 uv		: TEXCOORD0,
				float3 lightDir : TEXCOORD1,
				float3 normal   : TEXCOORD2,
				float3 viewDir  : TEXCOORD3,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0),
				uniform sampler2D brightSam : register(s1) )
{
	float4 baseColor = tex2D( baseSam, uv );
	
	float3 N = normalize( normal );
	float3 L = normalize( lightDir );
	
	float4 diff = {1.0f, 1.0f, 1.0f, 1.0f};
	if (specular > 0.0f)
	{
		float4 spec = {1.0f, 1.0f, 1.0f, 1.0f};
		float4 bright = tex2D( brightSam, uv );
		float3 V = normalize( viewDir ); 
		float3 H = normalize( L + V );
		float NdotH = dot( N, H );
		float NdotL = dot( N, L );
		float4 ret = lit( NdotL, NdotH, 20.0f/*power*/ );
		
		diff = ret.y * lightDiffuse + lightAmbient;
		spec = ret.z * bright.r * specular;
	
		oColor.rgb = diffuse.rgb * baseColor.rgb * diff.rgb + spec.rgb;
		oColor.a   = baseColor.a * diffuse.a;
	}
	else
	{
		float ndotl = saturate( dot( N, L ) );
		diff = ndotl * lightDiffuse + lightAmbient;		
	
		oColor.rgb = diffuse.rgb * baseColor.rgb * diff.rgb;
		oColor.a   = baseColor.a * diffuse.a;
	}
}
