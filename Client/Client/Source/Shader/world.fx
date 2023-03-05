
float4x4 g_mLightViewProj;

void VertShadow( float4 vPos : POSITION,
				 //float3 vNormal : NORMAL,
				 float2 vTexUV : TEXCOORD0,
				 out float4 oPos : POSITION,
				 out float2 oTexUV : TEXCOORD1,
				 out float2 oDepth : TEXCOORD0 )
{
	oPos= mul( vPos, g_mLightViewProj );
	oDepth = oPos.zw;
	oTexUV = vTexUV;
}

float4 PixShadow( float4 vPos : POSITION, float2 vTexUV : TEXCOORD1,float2  vDepth : TEXCOORD0 ) : COLOR0
{
	float fColor = min( 1, vDepth.x / vDepth.y );
	fColor = max( 0, fColor );
	return  float4( fColor,fColor, fColor, 1.f );
}

technique RenderShadow
{
    pass P0
    {
		//AlphaBlendEnable = true;
        VertexShader = compile vs_2_0 VertShadow();
        PixelShader  = compile ps_2_0 PixShadow();
        ZEnable = false;
        ZWriteEnable = false;
        CULLMODE=NONE;
        AlphaBlendEnable = false;
        AlphaTestEnable = false;
		Lighting = false;
		FogEnable = false;
    }
}
 