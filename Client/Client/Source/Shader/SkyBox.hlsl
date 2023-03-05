
float4x4 worldViewProj;

void SkyBox_vp(float4 position : POSITION,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float2 oUV		 : TEXCOORD0 )
{
	oPosition = mul( position, worldViewProj );
	oUV		  = uv;
}

void SkyBox_fp(float2 uv		  : TEXCOORD0,

				out float4 oColor : COLOR0,
				
				uniform sampler2D baseSam : register(s0) )
{
	oColor = tex2D( baseSam, uv );
}
