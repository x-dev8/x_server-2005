
float4x4 worldViewProj		: register(c0);
float4 lightDiffuse			: register(c4);

void Collision_vp(float4 position : POSITION,

				out float4 oPosition : POSITION
				)
{
	oPosition = mul( position, worldViewProj );
}

void Collision_fp( out float4 oColor : COLOR0 )
{
	oColor = lightDiffuse;
}
