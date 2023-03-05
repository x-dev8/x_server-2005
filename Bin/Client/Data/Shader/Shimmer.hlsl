
float4x4 worldViewProj;
float4x4 world;

float PerturbationMultiplier = 0.05;
float ShimmerBrightness = 1;

float timer;
float alpha = 1;

float3 lightDir;
float4 lightAmbient;
float4 lightDiffuse;

void Shimmer_vp(float4 position   : POSITION,
				float4 diffuse	  : COLOR0,
				float3 normal	  : NORMAL,
				float2 uv	      : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
    			out float2 oBaseTex  : TEXCOORD0,
				out float4 oScreenUV : TEXCOORD1,
				out float3 oLightDir : TEXCOORD2,
				out float3 oNormal   : TEXCOORD3
				)
{
	oPosition = mul( position, worldViewProj );
	oBaseTex  = uv;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;
	oScreenUV = oPosition;
	oLightDir = -lightDir;
	oNormal = mul( normal, world );
}

void Shimmer_fp(float4 Position : POSITION,
				float4 Diffuse  : COLOR0,
    			float2 BaseTex  : TEXCOORD0,
				float4 ScreenUV : TEXCOORD1,
				float3 LightDir : TEXCOORD2,
				float3 Normal   : TEXCOORD3,
				out float4 oColor : COLOR0,
				
				uniform sampler2D BaseSam : register(s0),
				uniform sampler2D HeatShimmerSam : register(s1),
				uniform sampler2D GraySam : register(s2) )
{
    float4 ScreenPos = ScreenUV;
    ScreenPos.xy = (ScreenPos.xy / ScreenPos.w) * 0.5f + 0.5f;
    ScreenPos.y = 1-ScreenPos.y;
	
    float2 NewBaseCoords = BaseTex;
    NewBaseCoords.y += timer * 0.0005f;

    float4 vHeatBright = tex2D(HeatShimmerSam, NewBaseCoords);
    float4 vHeatOri = tex2D(HeatShimmerSam, BaseTex );
    float2 vHeat = vHeatBright.rg;
    
    float2 vNewCoord = ScreenPos.xy;
    if (any(vHeat - 0.5))
    {
	 float2 vOffsetNewCoord = NewBaseCoords.xy + vHeat.xy * 0.1;	
	 if (any(tex2D(HeatShimmerSam, vOffsetNewCoord).rg - 0.5))
         {
             vNewCoord = vOffsetNewCoord;
         }	
    }

    float4 Base = tex2D(BaseSam, BaseTex);
    float4 HeatShimmer = tex2D(HeatShimmerSam, vNewCoord);
    float4 Gray = tex2D(GraySam, BaseTex);
	
    float ndl = saturate(dot(normalize(Normal), normalize(LightDir)));
    float4 Diff = ndl * lightDiffuse + lightAmbient;
	
    oColor.rgb = Diffuse.rgb * Base.rgb * Diff.rgb + HeatShimmer.rgb * Gray.g;
    oColor.a = Base.a * Gray.a;
}
