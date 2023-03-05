
float4x4 worldViewProj;
float4x4 world;
float3 lightDir;
float4 lightAmbient;
float4 lightDiffuse;
float alpha;

float2 vLightmapScale;
float2 vLightmapOffset;

void AlphaTest_vp(float4 position : POSITION,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0 )
{
	oPosition = mul( position, worldViewProj );
	oUV		  = uv;
	
	float3 l = normalize( -lightDir );
	float3 n = normalize( mul( normal, world ).xyz );
	float ndotl = saturate( dot( n, l ) );
	
	oDiffuse.rgb = ( ndotl * lightDiffuse + lightAmbient * 2.0f ).rgb;
	oDiffuse.rgb *= diffuse.rgb;
	oDiffuse.a = alpha;
}

void AlphaTest_fp(float4 diffuse  : COLOR0,
				float2 uv		  : TEXCOORD0,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0) )
{
	float4 baseColor = tex2D( baseSam, uv );
	oColor.rgb = baseColor.rgb * diffuse.rgb;
	oColor.a   = baseColor.a * diffuse.a;
}

void AlphaTestLM_vp(float4 position : POSITION,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv		  : TEXCOORD0,
				float2 uvlm		  : TEXCOORD1,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV1		 : TEXCOORD0,
				out float2 oUV2		 : TEXCOORD1)
{
	oPosition = mul( position, worldViewProj );
	oUV1	= uv;
	oUV2	= uvlm * vLightmapScale + vLightmapOffset;
	
	oDiffuse = lightAmbient * 2.0f;
	oDiffuse.rgb *= diffuse.rgb;
	oDiffuse.a *= alpha;
}

void AlphaTestLM_fp(float4 diffuse  : COLOR0,
				float2 uv1			: TEXCOORD0,
				float2 uv2			: TEXCOORD1,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0),
				uniform sampler2D lightmapSam : register(s1) )
{
	float4 baseColor = tex2D( baseSam, uv1 );
	float4 lightmapColor = tex2D( lightmapSam, uv2 );
	oColor.rgb = baseColor.rgb * ( lightmapColor.rgb + diffuse.rgb );
	oColor.a   = baseColor.a * diffuse.a;
}
