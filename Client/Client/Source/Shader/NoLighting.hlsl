
float4x4 worldViewProj;
float4x4 world;
float alpha;
float4x4 shadowTexMatrix;
float4x4 lightViewProj;
bool bRenderShadow;

float2 vLightmapScale;
float2 vLightmapOffset;

void NoLighting_vp(float4 position : POSITION,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0,
				out float2 oTexCoord : TEXCOORD1,
				out float2 oObjDepth : TEXCOORD2 )
{
	oPosition = mul( position, worldViewProj );
	oUV		  = uv;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;
	
	float4 worldPos = mul( position, world );
	oTexCoord = mul( worldPos, shadowTexMatrix ).xy;
	oObjDepth = mul( worldPos, lightViewProj ).zw;
}

void NoLighting_fp(float4 diffuse  : COLOR0,
				float2 uv		: TEXCOORD0,
				float2 TexCoord : TEXCOORD1,
				float2 ObjDepth : TEXCOORD2,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0),
				uniform sampler2D shadowMapSam : register(s1) )
{
	
	float4 baseColor = tex2D( baseSam, uv );
	float3 color = baseColor.rgb * diffuse.rgb;
	
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
		LightAmount = max( 0.4f, LightAmount );
	}
	oColor.rgb = color * LightAmount;
	oColor.a   = baseColor.a * diffuse.a;
}


void NoLightingLM_vp(float4 position : POSITION,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv		  : TEXCOORD0,
				float2 uvlm		  : TEXCOORD1,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV1		 : TEXCOORD0,
				out float2 oUV2		 : TEXCOORD1,
				out float2 oTexCoord : TEXCOORD2,
				out float2 oObjDepth : TEXCOORD3 )
{
	oPosition = mul( position, worldViewProj );
	oUV1	= uv;
	oUV2	= uvlm * vLightmapScale + vLightmapOffset;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;
	
	float4 worldPos = mul( position, world );
	oTexCoord = mul( worldPos, shadowTexMatrix ).xy;
	oObjDepth = mul( worldPos, lightViewProj ).zw;
}

void NoLightingLM_fp(float4 diffuse  : COLOR0,
				float2 uv1		: TEXCOORD0,
				float2 uv2		: TEXCOORD1,
				float2 TexCoord : TEXCOORD2,
				float2 ObjDepth : TEXCOORD3,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0),
				uniform sampler2D lightmapSam : register(s1),
				uniform sampler2D shadowMapSam : register(s2) )
{
	
	float4 baseColor = tex2D( baseSam, uv1 );
	float4 lightmapColor = tex2D( lightmapSam, uv2 );
	float3 color = baseColor.rgb * diffuse.rgb * lightmapColor.rgb;
	
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
		LightAmount = max( 0.4f, LightAmount );
	}
	oColor.rgb = color * LightAmount;
	oColor.a   = baseColor.a * diffuse.a;
}
