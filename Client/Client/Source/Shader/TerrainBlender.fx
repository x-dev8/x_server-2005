float4x4 worldViewProj ;
float4	 LOD2Color  = {0.46f,0.46f,0.46f,1.f};
float3	 LightDirection;
float4	 LightAmbientColor;
float4	 LightDiffuseColor;
float4	 LightSpecularColor;
float4	 SunLessColor;
float4	 InvViewTranspose;
float4	 MaterialPower;
float4x4 world;
float    power = 20.0f;
float3	 eye;
float	 g_time;
int 	 SpecialTextureLevel = 0;
float	 g_FarPlane;

float4	 fogColor = { 1.0f, 0.0f, 0.0f, 1.0f };
float    fogStart = 50.0f;
float    fogEnd = 150.0f;
float4x4 viewMatrix; 

#define	WaveNum	3
struct	Wave_T
{
	float2	WaveDir;
	float	WaveAmplitude;
	float	WaveFrequency;
	float	WavePhase;
};

Wave_T	Wave[WaveNum];

//float3	WaterColor_Deep;
//float3	WaterColor_Shallow;

/////////shadow map
#define SMAP_SIZE 2048
#define SHADOW_EPSILON 0.00005f

bool	 g_bRenderShadow;
float4x4 g_matShadowTex;
float4x4 g_mLightViewProj;

texture g_txShadowMap;
sampler g_samShadowMap =
sampler_state
{
    Texture = <g_txShadowMap>;
};

struct Input_vs_LOD2
{
	float4 position : POSITION;
};

struct VS_OUTPUT_Standard_LOD2 
{
  float4 Pos  :     POSITION;
	float4 Ambient	: COLOR0;
};

// LOD2 vertex shader.
VS_OUTPUT_Standard_LOD2 VSLOD2_Terrain( Input_vs_LOD2 In )
{
	VS_OUTPUT_Standard_LOD2 Out = (VS_OUTPUT_Standard_LOD2)0;
	Out.Pos = mul( In.position, worldViewProj );
	Out.Ambient = LOD2Color;
	return Out;
}

struct Input_vs_Liquid
{
	float4 position : POSITION;
	float4 Ambient	: COLOR0;
	float2 uv		: TEXCOORD0;
};

struct VS_OUTPUT_Standard_Liquid 
{
	float4 Pos		: POSITION; 	
	float4 Ambient	: COLOR0;
	float2 uv		: TEXCOORD0;
	float4 viewCoord: TEXCOORD1;
	float3 eyeVec	: TEXCOORD2;
	float3 normal	: TEXCOORD3;
	//float2 bump		: TEXCOORD3;
	//float3 rotMat1	: TEXCOORD4;
	//float3 rotMat2	: TEXCOORD5;
	//float3 rotMat3	: TEXCOORD6;
};

struct Input_vs
{
	float4 position : POSITION;
	float3 normal	: NORMAL;
	float4 Ambient	: COLOR0;
	float2 uv		: TEXCOORD0;
	float2 uv1		: TEXCOORD1;
	float2 uv2		: TEXCOORD2;
	float2 uv3		: TEXCOORD3;
	float2 uvShadow		: TEXCOORD4;//for shadow
};

struct VS_OUTPUT_Standard 
{
	float4 Pos				: POSITION;
	float4 Ambient			: COLOR0;
	float3 worldNormal   	: TEXCOORD0; 
    float3 lightVec    		: TEXCOORD1; 
    float3 eyeVec	    	: TEXCOORD2; 	
	float4 uv01				: TEXCOORD3;
	float4 uv23				: TEXCOORD4;	
	float2 uvShadow			: TEXCOORD5;
	float2 TexCoord			: TEXCOORD6;
	float3 ObjDepth			: TEXCOORD7; //lyh改为 float3 不然不够用了
};

texture texture0Tex;
texture texture1Tex;
texture texture2Tex;
texture texture3Tex;
texture maskTex;

sampler texture0Sam = sampler_state
{
	Texture = <texture0Tex>;
};

sampler texture1Sam = sampler_state
{
	Texture = <texture1Tex>;
};
sampler texture2Sam = sampler_state
{
	Texture = <texture2Tex>;
};
sampler texture3Sam = sampler_state
{
	Texture = <texture3Tex>;
};
sampler maskSam = sampler_state
{
	Texture = <maskTex>;
};

//反射与折射
texture g_txReflect;
sampler g_samReflect =
sampler_state
{
    Texture = <g_txReflect>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

texture g_txRefract;
sampler g_samRefract =
sampler_state
{
    Texture = <g_txRefract>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

//水normal
texture g_waterNormalTex;
sampler g_samWaterNormal = 
sampler_state
{
	Texture = <g_waterNormalTex>;
	AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

VS_OUTPUT_Standard VS_Terrain( Input_vs In )
{
	VS_OUTPUT_Standard Out = (VS_OUTPUT_Standard)0;
	Out.Pos = mul( In.position, worldViewProj );
		
	Out.uv01 = float4( In.uv, In.uv1 );	
	Out.uv23 = float4( In.uv2, In.uv3 );
		
	Out.uvShadow = In.uvShadow;
	
	float4 p = mul( In.position, world );
	float3 viewVec	 = normalize( eye - p );
	Out.worldNormal = normalize(mul(In.normal, world).xyz);
	Out.lightVec = normalize(-LightDirection);//lightPosition - worldSpacePos; //light vector in world space
	Out.eyeVec = viewVec;
	
	Out.Ambient  = In.Ambient;
	
	Out.TexCoord = mul( In.position, g_matShadowTex ).xy;
	Out.ObjDepth.xy = mul( In.position, g_mLightViewProj ).zw;
	
	//lyh++ 在ObjDepth z中存雾的系数 ，不然3.0中雾效不起作用。
	float d = distance( p, eye );
	Out.ObjDepth.z = saturate( (fogEnd - d) / (fogEnd - fogStart) );
	return Out;
}



struct VS_OUTPUT_Low
{
	float4 Pos				: POSITION;
	float4 Ambient			: COLOR0;
	float4 uv01				: TEXCOORD1;	
	float4 uv23				: TEXCOORD2;
	float2 uvShadow			: TEXCOORD3;
	float  fog				: TEXCOORD4;
	float2 TexCoord			: TEXCOORD5;
	float2 ObjDepth			: TEXCOORD6;
};

static const int g_cBlurSize = 4;
float2 BlurUV[ g_cBlurSize ] = 
{
	{ 0, 0 },
	{ 1.0/SMAP_SIZE, 0 },
	{ 0, 1.0/SMAP_SIZE },
	{ 1.0/SMAP_SIZE, 1.0/SMAP_SIZE }	
};

VS_OUTPUT_Low VS_Terrain_Low( Input_vs In )
{
	VS_OUTPUT_Low Out = (VS_OUTPUT_Low)0;
	
	Out.Pos = mul( In.position, worldViewProj );	
	
	Out.uv01	 = float4( In.uv, In.uv1 );	
	Out.uv23	 = float4( In.uv2, In.uv3 );
	Out.uvShadow = In.uvShadow;
	
	float3 worldNormal = mul(In.normal, world).xyz;	
	
	float ndotl = saturate( dot( worldNormal, -LightDirection ) );
	Out.Ambient	= ndotl * LightDiffuseColor;
	
	float4 p = mul( In.position, world );
	float d = distance( p, eye );
	Out.fog = saturate( (fogEnd - d) / (fogEnd - fogStart) );
	
	Out.TexCoord = mul( In.position, g_matShadowTex ).xy;
	Out.ObjDepth.xy = mul( In.position, g_mLightViewProj ).zw;
	
	return Out;
}

VS_OUTPUT_Standard VS_Terrain_Pos( Input_vs In )
{
	VS_OUTPUT_Standard Out = (VS_OUTPUT_Standard)0;
	Out.Pos = mul( In.position, worldViewProj );
	
	
	
	float3 vPos = mul( In.position, viewMatrix ); //视图空间中的位置
	float d = distance( vPos, eye );  //眼镜到这个点的距离
	
	Out.ObjDepth.xyz = d /g_FarPlane;
	             
	return Out;
}


//lyh++ 绘制位置图片
float4 PS_Terrain_Pos( VS_OUTPUT_Standard In ) : COLOR
{ 
   return float4(In.ObjDepth,1);
}

float4 ProcessLight(float4 blendedTex, VS_OUTPUT_Standard In) : COLOR
{	
	float3 N = (In.worldNormal);
	float3 V = (In.eyeVec);		//creating the eye vector  
	float3 L = (In.lightVec);		//creating the light vector
	float glossiness = 10;					//the Glossiness socket was empty - using default value 
	float3 H = normalize(L + V);			//Compute the half angle  
	float NdotH = saturate(dot(N,H));		//Compute NdotH  	
	float NdotL = saturate(dot(N,L));	
	float4 litv = lit( NdotL, NdotH, glossiness );	
	//ambient
// 	float4 ambientColor = LightAmbientColor;
	//diffuse
	float4 diffuseColor = litv.y * LightDiffuseColor;
	//specular	
	float4 spec = LightSpecularColor * litv.z * blendedTex.a;
	
	float LightAmount = 1.0f;
	if ( g_bRenderShadow && In.TexCoord.x > 0 && In.TexCoord.x < 1 && In.TexCoord.y > 0 && In.TexCoord.y < 1 )
	{
		float B = min( 1, In.ObjDepth.x / In.ObjDepth.y ) /*- SHADOW_EPSILON*/; 

		float2 ShadowTexC = In.TexCoord.xy;	        

		//read in bilerp stamp, doing the shadow checks
		float Color = 0;
		for( int i = 0 ; i < 2 ; ++ i )
		{
			Color += (tex2D( g_samShadowMap, ShadowTexC + BlurUV[i] ).r  < B ) ? 0.0f: 0.5f;  
		}
		                     			                 
		 LightAmount = Color;
	}	
	float fRefDiff = litv.y > 0 ? 2 : 0;	
	return (diffuseColor * LightAmount + LightAmbientColor)* blendedTex * In.Ambient * In.Ambient.a * 13  + spec * fRefDiff;
}

float4 ProcessLight_Low( float4 blendedTex, VS_OUTPUT_Low In ) : COLOR
{
	float B = min( 1, In.ObjDepth.x / In.ObjDepth.y ) - SHADOW_EPSILON; 

	float LightAmount = 1.0f;
	if ( g_bRenderShadow && In.TexCoord.x > 0 && In.TexCoord.x < 1 && In.TexCoord.y > 0 && In.TexCoord.y < 1 )
	{
		float2 ShadowTexC = In.TexCoord.xy;	        

		//read in bilerp stamp, doing the shadow checks
		float Color = 0;
		for( int i = 0 ; i < 2 ; ++ i )
		{
			Color += (tex2D( g_samShadowMap, ShadowTexC + BlurUV[i] ).r  < B ) ? 0.0f: 1.0f;  
		}
		                     			                 
		LightAmount = Color / 2 ;
	}		
	return (  LightAmount + LightAmbientColor ) * blendedTex ;	
}

float4 FurtherProcess(float4 clr)
{
	//float h = clr.x * 0.3 + clr.y * 0.59 + clr.z * 0.11;
	return clr;
}


float4 PS_Terrain_4Layers( VS_OUTPUT_Standard In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);	
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );
	float4 texture3Color = tex2D( texture3Sam, In.uv23.zw );
	
	float4 maskColor = tex2D(maskSam, In.uvShadow);
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = lerp(texture3Color,ambient,maskColor.b);
	ambient = ambient* maskColor.a;
	
	float4 clr = ProcessLight(ambient, In);
	return FurtherProcess(clr);
}

float4 PS_Terrain_3Layers( VS_OUTPUT_Standard In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);	
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );		
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = ambient* maskColor.a;
	return ProcessLight(ambient, In);
}
//====================================================================
//3.0
float4 PS_Terrain_4Layers_30( VS_OUTPUT_Standard In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	texture0Color.rgb = texture0Color.rgb+ (texture0Color.a - 0.5f);
	
	
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);
	texture1Color.rgb = texture1Color.rgb+ (texture1Color.a - 0.5f);
	
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );
	texture2Color.rgb = texture2Color.rgb+ (texture2Color.a - 0.5f);
	
	float4 texture3Color = tex2D( texture3Sam, In.uv23.zw );
	texture3Color.rgb = texture3Color.rgb+ (texture3Color.a - 0.5f);
	
	float4 maskColor = tex2D(maskSam, In.uvShadow);
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = lerp(texture3Color,ambient,maskColor.b);
	ambient = ambient* maskColor.a;
	
	float4 clr = ProcessLight(ambient, In);
	float4 Ret = FurtherProcess(clr);
	
	return In.ObjDepth.z * Ret + (1 - In.ObjDepth.z) * fogColor;	
}

float4 PS_Terrain_3Layers_30( VS_OUTPUT_Standard In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	texture0Color.rgb = texture0Color.rgb+ (texture0Color.a - 0.5f);
	
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);
	texture1Color.rgb = texture1Color.rgb+ (texture1Color.a - 0.5f);
	
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );
	texture2Color.rgb = texture2Color.rgb+ (texture2Color.a - 0.5f);
		
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = ambient* maskColor.a;
	float4 Ret = ProcessLight(ambient, In);
	
	return In.ObjDepth.z * Ret + (1 - In.ObjDepth.z) * fogColor;	
}


float4 PS_Terrain_2Layers_30( VS_OUTPUT_Low In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	texture0Color.rgb = texture0Color.rgb+ (texture0Color.a - 0.5f);
	
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw );
	texture1Color.rgb = texture1Color.rgb+ (texture1Color.a - 0.5f);
		
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	float4 Ret = /*In.Ambient **/ ambient* maskColor.a * 1.5f;
	return In.fog * Ret + (1 - In.fog) * fogColor;	
}

//======================================================================


float4 PS_Terrain_4Layers_Low( VS_OUTPUT_Low In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );
	float4 texture3Color = tex2D( texture3Sam, In.uv23.zw );
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = lerp(texture3Color,ambient,maskColor.b);
	ambient = ambient* maskColor.a; //a 来控制烘焙的阴影
	return ProcessLight_Low( ambient, In );
}

float4 PS_Terrain_3Layers_Low( VS_OUTPUT_Low In ) : COLOR
{
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw);
	float4 texture2Color = tex2D( texture2Sam, In.uv23.xy );
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	ambient = lerp(texture2Color,ambient,maskColor.g);
	ambient = ambient* maskColor.a;
	return ProcessLight_Low( ambient, In );	
}

//2层的时候去掉光照和mrt
float4 PS_Terrain_2Layers( VS_OUTPUT_Low In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv01.xy );
	float4 texture1Color = tex2D( texture1Sam, In.uv01.zw );	
	float4 maskColor = tex2D( maskSam, In.uvShadow );
	
	float4 ambient = lerp(texture1Color,texture0Color,maskColor.r);
	float4 Ret = /*In.Ambient **/ ambient* maskColor.a * 1.5f;
	return In.fog * Ret + (1 - In.fog) * fogColor;	
}

VS_OUTPUT_Standard_Liquid VS_Liquid( Input_vs_Liquid In )
{
	VS_OUTPUT_Standard_Liquid Out = (VS_OUTPUT_Standard_Liquid)0;		
	float4 oPos = In.position;	
	
	//float fAngle=g_time/500+dot(float3(0.1,2,-0.5),oPos);
	//float fOffset = sin(fAngle) * sin(oPos.x) * sin(oPos.y) * 0.05f;
	//oPos.z += fOffset;
	
	float2 pos_xy = oPos.xy;
	//float fHeight1 = WaveAmplitude1 * sin( dot( WaveDir1.xy, pos_xy ) * WaveFrequency1 + g_time * WavePhase1 );
	//float fHeight2 = WaveAmplitude2 * sin( dot( WaveDir2.xy, pos_xy ) * WaveFrequency2 + g_time * WavePhase2 );
	//float fHeight3 = WaveAmplitude3 * sin( dot( WaveDir3.xy, pos_xy ) * WaveFrequency3 + g_time * WavePhase3 );
	//float fNormal1 = WaveFrequency1 * WaveDir1.x * oPos.x * WaveAmplitude1 * cos( dot( WaveDir1.xy, pos_xy ) * WaveFrequency1 + g_time * WavePhase1 );
	//float fNormal2 = WaveFrequency2 * WaveDir2.x * oPos.x * WaveAmplitude2 * cos( dot( WaveDir2.xy, pos_xy ) * WaveFrequency2 + g_time * WavePhase2 );
	//float fNormal3 = WaveFrequency3 * WaveDir3.x * oPos.x * WaveAmplitude3 * cos( dot( WaveDir3.xy, pos_xy ) * WaveFrequency3 + g_time * WavePhase3 );
	float angle, ddx = 0.f, ddy = 0.f, deriv;
	for( int i = 0; i < WaveNum; ++i )
	{
		angle = dot( Wave[i].WaveDir, pos_xy ) * Wave[i].WaveFrequency + g_time * Wave[i].WavePhase;
		oPos.z += Wave[i].WaveAmplitude * sin( angle );
		deriv = Wave[i].WaveFrequency * Wave[i].WaveAmplitude * cos( angle );
		ddx += deriv * Wave[i].WaveDir.x;
		ddy += deriv * Wave[i].WaveDir.y;
	}

	//Out.rotMat1 = normalize( float3( 1.f, 0.f, ddy ) );
	//Out.rotMat2 = normalize( float3( 0.f, 1.f, ddx ) );
	//Out.rotMat3 = normalize( float3( -ddx, -ddy, 1.f ) );
	Out.normal = normalize( float3( -ddx, -ddy, 1.f ) );
	
	Out.Pos = mul( oPos, worldViewProj );	
	Out.uv		 = In.uv;	
	float4 p = mul( oPos, world );
	float3 viewVec	 = normalize( eye - p );
	Out.eyeVec = viewVec;
	
	Out.Ambient = In.Ambient;
	Out.viewCoord = Out.Pos;
	Out.viewCoord.z += 0.25;
	Out.viewCoord.w = 1-Out.viewCoord.z/300;
	Out.viewCoord.xy+=Out.viewCoord.z;
	Out.viewCoord.z*=2;
	return Out;
}

float4 PS_Liquid( VS_OUTPUT_Standard_Liquid In ) : COLOR
{
	float4 texture0Color = tex2D( texture0Sam, In.uv );
	//texture0Color.xy -= 0.02;
	//texture0Color.xy *= saturate(In.viewCoord.w);
	
	//float3x3 rotMat;
	//rotMat[0] = In.rotMat1;
	//rotMat[1] = In.rotMat2;
	//rotMat[2] = In.rotMat3;
	
	//float3 N = tex2D( g_samWaterNormal, In.bump );
	//N = normalize( mul( mul( N, rotMat ), worldViewProj ) );
	
	float3 N = In.normal;
	float3 V = normalize(In.eyeVec);
	float3 L = normalize( -LightDirection );
	float3 H = normalize( V + L );
	float NdotL = saturate( dot( N, L ) );
	float NdotH = saturate( dot( N, H ) );
	float VdotN = saturate( dot( V, N ) );
	
	float4 litv = lit( NdotL, NdotH, 5 );
	
	//float4 diffuse = litv.y * LightDiffuseColor;
	float Spec = litv.z * LightSpecularColor * texture0Color.w * 1.5;	
	texture0Color.rgb += In.Ambient.rgb * LightAmbientColor;
	texture0Color += (Spec * In.Ambient.a);

	//float3 waterColor = lerp( WaterColor_Shallow, WaterColor_Deep, 1 - VdotN );
	//float3 rstColor =	texture0Color.rgb * LightAmbientColor +
						texture0Color.rgb * LightDiffuseColor * litv.y +
						texture0Color.rgb * LightSpecularColor * litv.z;
	//texture0Color.rgb = rstColor;
	//texture0Color.rgb = waterColor;
	texture0Color.a = In.Ambient.a;
	return ( texture0Color );
}

float4 PS_Liquid_High( VS_OUTPUT_Standard_Liquid In ) : COLOR
{	
	float4 texture0Color = tex2D( texture0Sam, In.uv );
	
// 	float2 waterUV = sin( g_time / 1000 ) * 0.02f + In.uv;
// 	float4 waterNormal = tex2D( g_samWaterNormal, waterUV );
		
 	texture0Color.xy -= 0.02f;
 	texture0Color.xy *= saturate(In.viewCoord.w) * 0.3f;	
	
	//lighting	
	float3 V = normalize(In.eyeVec);
	float3 N = In.normal;
	float3 L = normalize( -LightDirection );
	float3 H = normalize( In.eyeVec + L );
	float NdotL = saturate(dot(N,L));
	float NdotH = saturate(dot(N,H));
	float NdotV_fresnel = saturate(dot(N,V)); 		//clamped dot product 
	float4 litv = lit( NdotL, NdotH, 20 );
	float4 diffuse = litv.y * LightDiffuseColor;
	float Spec = litv.z /** LightSpecularColor */* texture0Color.w * litv.y;
	
	//texture	
	float2 projCoord = In.viewCoord.xy/In.viewCoord.z;	
    projCoord += texture0Color.xy ;
//     float2 projCoord1 = 1 - ( projCoord );
//     projCoord1.x = 1 - projCoord1.x;    
    
	float4 basecolor = tex2D( g_samReflect, projCoord);
	//float4 refract = tex2D( g_samRefract, projCoord1);
	//basecolor = lerp(basecolor, refract, 0.55f);	
	
	//float4 finalcolor = lerp(basecolor, refract, 0.5f/*saturate(cosangle/0.779f)*/);	
	//fresnel
 	float Pow_NdotV = pow(NdotV_fresnel,.5f/*FresnelPower*/);		//x to the power of y 
 	float timesFresnelScale = Pow_NdotV * 1.3f/*FresnelScale*/;
 	float plusFresnelBias = timesFresnelScale + 0.f/*FresnelBias*/;
 	float Saturate = saturate(plusFresnelBias); 
// 	float4 Lerp = float4(lerp(float3(0.f,0.7f,0.91f), basecolor.rgb, Saturate), 1.f);
	float4 Lerp = float4(lerp( basecolor.rgb, float3(0.0f,0.6f,0.7f),Saturate), 0.7f);
 	
 	//final collor
 	//basecolor *= (diffuse + In.Ambient);
 	basecolor *= Lerp;	
	basecolor += 2 * Spec;
	basecolor.w = In.Ambient.a;
	//waterNormal.a = 1.f;
	return (basecolor);
}

//输出位置图片
technique PosTexture
{
  pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain_Pos();
        PixelShader = compile ps_2_0 PS_Terrain_Pos();
     }


}
technique Terrain_4Layers_High
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain();
        PixelShader = compile ps_2_0 PS_Terrain_4Layers();
     }
}

technique Terrain_3Layers_High
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain();
        PixelShader = compile ps_2_0 PS_Terrain_3Layers();
     }
}

//============================================
technique Terrain_4Layers_High_30
{
    pass Single_Pass
    {
        VertexShader = compile vs_3_0 VS_Terrain();
        PixelShader = compile ps_3_0 PS_Terrain_4Layers_30();
     }
}

technique Terrain_3Layers_High_30
{
    pass Single_Pass
    {
        VertexShader = compile vs_3_0 VS_Terrain();
        PixelShader = compile ps_3_0 PS_Terrain_3Layers_30();
     }
}

technique Terrain_2Layers_High_30
{
    pass Single_Pass
    {
        VertexShader = compile vs_3_0 VS_Terrain_Low();
        PixelShader = compile ps_3_0 PS_Terrain_2Layers_30();
    }
}


//=============================================

technique Terrain_2Layers_High
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain_Low();
        PixelShader = compile ps_2_0 PS_Terrain_2Layers();
    }
}

technique Terrain_4Layers_Low
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain_Low();
        PixelShader = compile ps_2_0 PS_Terrain_4Layers_Low();
     }
}

technique Terrain_3Layers_Low
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain_Low();
        PixelShader = compile ps_2_0 PS_Terrain_3Layers_Low();
     }
}

technique Terrain_2Layers_Low
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Terrain_Low();
        PixelShader = compile ps_2_0 PS_Terrain_2Layers();
     }
}

technique LiquidRender
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Liquid();
        PixelShader = compile ps_2_0 PS_Liquid();
        CullMode = NONE;
		ZEnable = true; 
		ZWriteEnable = false;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		AlphaBlendEnable = true; 
		AlphaTestEnable = false;
		FillMode = solid;
     }
}

technique LiquidRender_High
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VS_Liquid();
        PixelShader = compile ps_2_0 PS_Liquid_High();
        CullMode = NONE;
		ZEnable = true; 
		ZWriteEnable = false;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		AlphaBlendEnable = true; 
		AlphaTestEnable = false;
		FillMode = solid;
     }
}

technique LOD2_Terrain
{
    pass Single_Pass
    {
        VertexShader = compile vs_1_1 VSLOD2_Terrain();
		PixelShader  = null;
        CullMode = CCW;
		ZEnable = true; 
		AlphaBlendEnable = false; 
		FillMode = solid;
    }
}