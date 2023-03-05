
float4x4 worldViewProj;
float4x4 world;
float3 lightDir;
float4 lightAmbient;
float4 lightDiffuse;
float alpha;
float3 eye;
float specular;

void Specular_vp(float4 position : POSITION,
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
	float4 p  = mul( position, world );
	
	oPosition = mul( position, worldViewProj );
	oUV		  = uv;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;
	oLightDir = -lightDir;
	oNormal   = mul( normal, world );
	oViewDir  = eye - p;
}

void Specular_fp(float4 diffuse : COLOR0,
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
