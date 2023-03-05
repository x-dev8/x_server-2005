
float4x4 lightViewProj;

void Shadow_vp(float4 position : POSITION,

				out float4 oPosition : POSITION,
				out float2 oDepth	 : TEXCOORD0 )
{
	oPosition = mul( position, lightViewProj );
	oDepth    = oPosition.zw;
}

void Shadow_fp(float4 position  : POSITION,
				float2 depth	: TEXCOORD0,

				out float4 oColor : COLOR0)
{
	float fColor = min( 1, depth.x / depth.y );
	fColor = max( 0, fColor );
	oColor = float4( fColor,fColor, fColor, 1.f );
}
