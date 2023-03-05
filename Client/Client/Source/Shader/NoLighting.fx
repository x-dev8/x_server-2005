

struct OutputNoLight_vs
{
	float4 position : POSITION;
	float4 diffuse	: COLOR0;
	float2 uv		: TEXCOORD0;
	float2 TexCoord : TEXCOORD1;
	float2 ObjDepth : TEXCOORD2;
#if OutputDepth == 1
	float  depth	: TEXCOORD3;
#endif
};

// vertex shader.
OutputNoLight_vs NoLight_vs( Input_vs In )
{
	OutputNoLight_vs Out = (OutputNoLight_vs)0;
	
	Out.position = mul( In.position, worldViewProj );
	Out.diffuse  = In.diffuse;
	Out.uv		 = In.uv;	
	Out.TexCoord = mul( In.position, g_matShadowTex ).xy;
	Out.ObjDepth = mul( In.position, g_mLightViewProj ).zw;
#if OutputDepth == 1
	Out.depth = Out.position.w / g_FarPlane;
#endif
	return Out;
}

// vertex shader.
Output_ps NoLight_ps( OutputNoLight_vs In )
{
	float4 baseColor = tex2D( baseSam, In.uv );
	float3 color = baseColor.rgb * In.diffuse.rgb;
	
	Output_ps Out = (Output_ps)0;
	// Ìí¼ÓÒõÓ°
	float LightAmount = 1.0f;

	if ( g_bRenderShadow && In.TexCoord.x > 0 && In.TexCoord.x < 1 && In.TexCoord.y > 0 && In.TexCoord.y < 1 )
	{
		float B = min( 1, In.ObjDepth.x / In.ObjDepth.y );

		float2 ShadowTexC = In.TexCoord.xy;	      
		
		float Color = 0;
		for( int i = 0 ; i < 4 ; ++ i )
		{
			Color += (tex2D( g_samShadowMap, ShadowTexC + BlurUV[i] ).r + SHADOW_EPSILON < B ) ? 0.f: 1.0f;  
		}	               

		LightAmount = Color / 4;
		LightAmount = max( 0.4f, LightAmount );

	}	
	Out.color = float4( color * LightAmount, baseColor.a * In.diffuse.a );
	
#if OutputDepth == 1
	Out.depth = float4( In.depth, In.depth, In.depth, 1.0f );
#endif
	return Out;
}
