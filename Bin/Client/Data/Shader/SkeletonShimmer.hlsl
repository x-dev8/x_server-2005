
float4x4 viewProj;
float alpha;
float timer;
float4x3 boneWorldMatrix[56];
float PerturbationMultiplier = 0.05;
float ShimmerBrightness = 3;

void SkeletonShimmer_vp(
				float4 position   : POSITION,
				float4 blendWeights : BLENDWEIGHT,
				float4 blendIndices : BLENDINDICES,
				float3 normal	  : NORMAL,
				float4 diffuse	  : COLOR0,
				float2 uv		  : TEXCOORD0,

				out float4 oPosition : POSITION,
				out float4 oDiffuse  : COLOR0,
    				out float2 oBaseTex  : TEXCOORD0,
				out float4 oScreenUV : TEXCOORD1
				)
{
	oBaseTex		  = uv;
	oDiffuse  = diffuse;
	oDiffuse.a *= alpha;

	float3  Pos = 0.0f;
    
    // calculate the pos/normal using the "normal" weights 
    //        and accumulate the weights to calculate the last weight
    for (int iBone = 0; iBone < 4; iBone++)
    {
        Pos += mul(position, boneWorldMatrix[blendIndices[iBone]]).xyz * blendWeights[iBone];
    }
    
	float4 worldPos = float4(Pos.xyz, 1.0f);

    // transform position from world space into view and then projection space
    oPosition = mul(worldPos, viewProj);
    oScreenUV = oPosition;	
}

// void SkeletonShimmer_fp(
// 				float4 Position : POSITION,
// 				float4 Diffuse  : COLOR0,
//     				float2 BaseTex  : TEXCOORD0,
// 				float4 ScreenUV : TEXCOORD1,
// 
// 				out float4 oColor : COLOR0,
// 				
// 				sampler2D HeatSam : register(s0),
// 				sampler2D FrameSam : register(s1)
// 				)
// {
// 	float4 ScreenPos = ScreenUV;
//     ScreenPos.xy = (ScreenPos.xy / ScreenPos.w) * 0.5f + 0.5f;
//     ScreenPos.y = 1-ScreenPos.y;
// 
//     float2 vNewTexCoord = ScreenPos.xy;
// 	
//     float2 NewBaseCoords = BaseTex;
//     NewBaseCoords.y += timer * 0.0001f;
//     
//     float4 vHeatBright = tex2D(HeatSam, NewBaseCoords);
//     float2 vHeat = vHeatBright.rg;
//         if (any(vHeat - 0.5))
//     {
// 	
//         //vHeat = vHeat * 2 - 1;
//         float2 vOffsetTexCoord = ScreenPos.xy + (vHeat.xy 
//             * PerturbationMultiplier);
// 
//         if (any(tex2D(HeatSam, vOffsetTexCoord).rg - 0.5))
//         {
//             vNewTexCoord = vOffsetTexCoord;
//         }
//     }
//       
//     float4 HeatResult = tex2D(FrameSam, vNewTexCoord) * (1 
//         + ShimmerBrightness * vHeatBright.b);  
// 
//   //  oColor = float4(HeatResult.xyz, Diffuse.x * alpha);
// oColor = float4(HeatResult.xyz, 1);
// //oColor = tex2D(FrameSam, ScreenPos.xy) * saturate(timer);
// //oColor = tex2D(HeatSam, NewBaseCoords) * saturate(timer);
// //oColor = float4(1 * saturate(timer),1,1,1);
// }
void SkeletonShimmer_fp(
				float4 Position : POSITION,
				float4 Diffuse  : COLOR0,
    				float2 BaseTex  : TEXCOORD0,
				float4 ScreenUV : TEXCOORD1,

				out float4 oColor : COLOR0,		
				uniform sampler2D HeatSam : register(s0),
				uniform sampler2D FrameSam : register(s1)
				)
{
   float4 ScreenPos = ScreenUV;
    ScreenPos.xy = (ScreenPos.xy / ScreenPos.w) * 0.5f + 0.5f;
    ScreenPos.y = 1-ScreenPos.y;

    float2 vNewTexCoord = ScreenPos.xy;
	
    float2 NewBaseCoords = BaseTex;
    NewBaseCoords.y += timer * 0.0001f;    
    
    float4 vHeatBright = tex2D(HeatSam, NewBaseCoords);
    float4 vHeatOri = tex2D( HeatSam, BaseTex );
    float2 vHeat = vHeatBright.rg;
//     oColor = tex2D(FrameSam, ScreenPos.xy -  ( vHeat / 100 /** ( ScreenPos.xy )*/ ) ) * ( 1 + ShimmerBrightness * vHeatBright.r );    
//     oColor.a = 1;
    
    float2 vNewCoord = ScreenPos.xy;
    if( any( vHeat - 0.5 ) )
    {
	     float2 vOffsetNewCoord = ScreenPos.xy - vHeat * vHeatOri.b / 70;	
		 if (any(tex2D(HeatSam, vOffsetNewCoord).rg - 0.5))
         {
             vNewCoord = vOffsetNewCoord;
         }	
    }
    oColor = tex2D(FrameSam, vNewCoord + 0.007f * vHeatOri.b ) /** ( 1 + ShimmerBrightness * vHeatBright.g )*/;    
}
