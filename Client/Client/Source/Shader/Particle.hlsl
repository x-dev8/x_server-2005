
float4x4 worldViewProj;

void Particle_vp(float4 position : POSITION,
				float4 diffuse	  : COLOR0,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
				out float2 oUV		 : TEXCOORD0 )
{
	oPosition = mul( position, worldViewProj );
	oUV		  = uv;
	
	oDiffuse = diffuse;
}

void Particle_fp(float4 diffuse  : COLOR0,
				float2 uv		  : TEXCOORD0,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0) )
{
	float4 baseColor = tex2D( baseSam, uv );
	oColor.rgb = baseColor.rgb * diffuse.rgb;
	oColor.a   = baseColor.a * diffuse.a;
}
