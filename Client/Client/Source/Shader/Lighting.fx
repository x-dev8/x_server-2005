


void CalcDiffuseLightShadow( float2 vDepth, float2 vTexCoord, float3 lightDir, float3 normal, float4 ambient, float4 diffuse,
	out float4 oDiffuse)
{
	float ndotl = saturate( dot( normal, lightDir ) );	

	float LightAmount = 1.0f;

	if ( g_bRenderShadow && vTexCoord.x>0&&vTexCoord.x<1&&vTexCoord.y>0&&vTexCoord.y<1 )
	{
		float B = min( 1, vDepth.x / vDepth.y );

		float2 ShadowTexC = vTexCoord.xy;	      
		
		float Color = 0;
		for( int i = 0 ; i < 4 ; ++ i )
		{
			Color += (tex2D( g_samShadowMap, ShadowTexC + BlurUV[i] ).r + SHADOW_EPSILON < B ) ? 0.f: 1.0f;  
		}	               

		LightAmount = Color / 4;

	}	
	oDiffuse	= ndotl * diffuse * LightAmount + ambient;
	
}

void CalcDiffuseLight( float3 lightDir, float3 normal, float4 ambient, float4 diffuse,
	out float4 oDiffuse)
{
	float ndotl = saturate( dot( normal, lightDir ) );
	oDiffuse = ndotl * diffuse + ambient;		
}

void CalcSpecularLight( float3 lightDir, float3 normal, float3 viewDir,
	float4 ambient, float4 diffuse, float4 specular, float power,
	out float4 oDiffuse, out float4 oSpecular)
{
	float3 H = normalize( lightDir + viewDir );
	float NdotH = dot( normal, H );
	float NdotL = dot( normal, lightDir );
	float4 ret = lit( NdotL, NdotH, power );
	
	oDiffuse  = ret.y * diffuse + ambient;
	oSpecular = ret.z * specular;
}
