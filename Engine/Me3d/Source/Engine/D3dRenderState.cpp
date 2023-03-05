/*=============================================================================
D3DRenderState.cpp: Unreal Direct3D deferred state implementation.
Copyright 2001 Epic Games, Inc. All Rights Reserved.

Revision history:
* Created by Daniel Vogel
=============================================================================*/

#include "Me3d/Me3d.h"
#include "Me3d/Engine/D3dRenderState.h"
#include "FuncPerformanceLog.h"
#ifdef _DEBUG
#define SET_RENDERSTATE( a, b )																		\
	{																								\
	r->SetRenderState( a, b	);																\
	HardwareState.RenderState[a] = b;																\
	}
#define SET_SAMPLERSTATE( s, a, b )																	\
	{																							\
	r->SetSamplerState( s, ##a, b );								\
	HardwareState.Samplerstate[s][a] = b;															\
	}
#define SET_STAGESTATE( s, a, b )																	\
	{																								\
	r->SetTextureStageState( s, a, b );														\
	HardwareState.StageState[s][a] = b;																\
	}

#define COMMIT_RENDERSTATE( a )																		\
	if( WantedState.RenderState[a] != HardwareState.RenderState[a] )								\
	{																								\
	r->SetRenderState( a, WantedState.RenderState[a] );										\
	RenderStateDiff[a] = true;																					\
	StateChanges++;																					\
	RenderStateChangeCount[a]++;																					\
	}

#define COMMIT_STAGESTATE( s, a )																	\
	if( WantedState.StageState[s][a] != HardwareState.StageState[s][a] )								\
	{																								\
	r->SetTextureStageState( s, a, WantedState.StageState[s][a] );									\
	StageDiff[s][a] = true;																					\
	StageChanges++;																					\
	StageChangeCount[s][a]++;																					\
	}								
#define COMMIT_SAMPLERSTATE( s, a )																	\
	if( WantedState.Samplerstate[s][a] != HardwareState.Samplerstate[s][a] )								\
	{																								\
	r->SetSamplerState( s, a, WantedState.Samplerstate[s][a] );								\
	SamplerDiff[s][a] = true;																					\
	SamplerChanges++;																					\
	SamplerChangeCount[s][a]++;																					\
	}	
#else
#define SET_RENDERSTATE( a, b )																		\
	{																								\
	r->SetRenderState( a, b	);																\
	}
#define SET_SAMPLERSTATE( s, a, b )																	\
	{																							\
	r->SetSamplerState( s, ##a, b );								\
	}
#define SET_STAGESTATE( s, a, b )																	\
	{																								\
	r->SetTextureStageState( s, a, b );														\
	}

#define COMMIT_RENDERSTATE( a )																		\
	if( WantedState.RenderState[a] != HardwareState.RenderState[a] )								\
	{																								\
	r->SetRenderState( a, WantedState.RenderState[a] );										\
	}

#define COMMIT_STAGESTATE( s, a )																	\
	if( WantedState.StageState[s][a] != HardwareState.StageState[s][a] )								\
	{																								\
	r->SetTextureStageState( s, a, WantedState.StageState[s][a] );									\
	}								
#define COMMIT_SAMPLERSTATE( s, a )																	\
	if( WantedState.Samplerstate[s][a] != HardwareState.Samplerstate[s][a] )								\
	{																								\
	r->SetSamplerState( s, a, WantedState.Samplerstate[s][a] );								\
	}	
#endif


// #define COMMIT_TRANSFORM( t )																		\
// 	if (   (WantedState.IsDirty_Matrices & (1 << t) )												\
// 	/*&& (WantedState.StageState[t][D3DTSS_TEXTURETRANSFORMFLAGS] != D3DTTFF_DISABLE)*/				\
// 	&& memcpy( &WantedState.Matrices[t], &HardwareState.Matrices[t], sizeof(D3DMATRIX)) )		\
// 	{																								\
// 	r->SetTransform( t, &WantedState.Matrices[t] );										\
// 	TransformChanges++;																				\
// 	}
// #define SET_TRANSFORM( t, m )																		\
// 	{																								\
// 	r->SetTransform( t, (D3DMATRIX*) &m );												\
// 	memcpy( &HardwareState.Matrices[t], &m, sizeof( D3DMATRIX) );									\
// 	}

static D3DXMATRIX	GIdentity;

void CD3DDeferredState::SetSamplerState ( DWORD dwStage, DWORD dwType, DWORD dwValue )
{
	guardfunc;

	WantedState.Samplerstate[dwStage][dwType]  = dwValue;

	unguard;
}

void CD3DDeferredState::Init( IRenderer*	InRenDev )
{
	guardfunc;
	GIdentity = D3DXMATRIX(  1.0f, 0.0f, 0.0f, 0.0f
							,0.0f, 1.0f, 0.0f, 0.0f
							,0.0f, 0.0f, 1.0f, 0.0f
							,0.0f, 0.0f, 0.0f, 1.0f);
	RenDev = InRenDev;
//	WantedState;
//	HardwareState;

	memset( &WantedState, 0, sizeof(FD3DInternalState) );
	memset( &HardwareState, 0, sizeof(FD3DInternalState) );

	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();		
	

	FLOAT Dummy = 0;

	
	SET_RENDERSTATE( D3DRS_SPECULARMATERIALSOURCE , D3DMCS_COLOR2		);
	SET_RENDERSTATE( D3DRS_SPECULARENABLE		, FALSE				);
	SET_RENDERSTATE( D3DRS_DITHERENABLE			, TRUE				);
	SET_RENDERSTATE( D3DRS_NORMALIZENORMALS		, TRUE				);
	SET_RENDERSTATE( D3DRS_RANGEFOGENABLE		, FALSE				);
	SET_RENDERSTATE( D3DRS_FOGTABLEMODE			, D3DFOG_LINEAR		);

	// Doesn't have a performance impact on T&L cards but needed for e.g. Kyro cards.
	r->SetRenderState( D3DRS_CLIPPING, TRUE );

	SET_RENDERSTATE( D3DRS_FILLMODE			,		D3DFILL_SOLID		);
	SET_RENDERSTATE( D3DRS_SHADEMODE,				D3DSHADE_GOURAUD );
	SET_RENDERSTATE( D3DRS_ZWRITEENABLE		,		TRUE				);
	SET_RENDERSTATE( D3DRS_ALPHATESTENABLE	,		FALSE				);
	SET_RENDERSTATE( D3DRS_SRCBLEND			,		D3DBLEND_SRCALPHA	);
	SET_RENDERSTATE( D3DRS_DESTBLEND		,		D3DBLEND_INVSRCALPHA);
	SET_RENDERSTATE( D3DRS_CULLMODE			,		D3DCULL_CCW		);
	SET_RENDERSTATE( D3DRS_ZFUNC			,		D3DCMP_LESSEQUAL	);
	SET_RENDERSTATE( D3DRS_ALPHAREF			,		0x00000080			);
	SET_RENDERSTATE( D3DRS_ALPHAFUNC			,	D3DCMP_GREATER		);
	SET_RENDERSTATE( D3DRS_ALPHABLENDENABLE	,		FALSE				);
	SET_RENDERSTATE( D3DRS_FOGENABLE			,	FALSE				);
	SET_RENDERSTATE( D3DRS_FOGCOLOR			,		0					);
	SET_RENDERSTATE( D3DRS_FOGSTART			,		0					);
	SET_RENDERSTATE( D3DRS_FOGEND				,	0					);
//	SET_RENDERSTATE( D3DRS_ZBIAS				,	0					);
	//SET_RENDERSTATE( D3DRS_STENCILENABLE		,	TRUE				);
	SET_RENDERSTATE( D3DRS_STENCILENABLE		,	FALSE				);
	SET_RENDERSTATE( D3DRS_STENCILFAIL			,	D3DSTENCILOP_KEEP	);
	SET_RENDERSTATE( D3DRS_STENCILZFAIL		,		D3DSTENCILOP_KEEP	);
	SET_RENDERSTATE( D3DRS_STENCILPASS			,	D3DSTENCILOP_KEEP	);
	SET_RENDERSTATE( D3DRS_STENCILFUNC			,	D3DCMP_ALWAYS		);
	SET_RENDERSTATE( D3DRS_STENCILREF			,	0					); 
	SET_RENDERSTATE( D3DRS_STENCILMASK			,	0xFF				);
	SET_RENDERSTATE( D3DRS_STENCILWRITEMASK	,		0xFF				);
	SET_RENDERSTATE( D3DRS_TEXTUREFACTOR		,	0					);
	SET_RENDERSTATE( D3DRS_LIGHTING			,		0					);
	SET_RENDERSTATE( D3DRS_AMBIENT				,	0					);
    SET_RENDERSTATE( D3DRS_COLORVERTEX			,	TRUE				);
    SET_RENDERSTATE( D3DRS_MULTISAMPLEANTIALIAS	,	TRUE				);

//	SET_TRANSFORM( D3DTS_VIEW					, GIdentity );
//	SET_TRANSFORM( D3DTS_PROJECTION				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE0				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE1				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE2				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE3				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE4				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE5				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE6				, GIdentity );
//	SET_TRANSFORM( D3DTS_TEXTURE7				, GIdentity );
//	SET_TRANSFORM( D3DTS_WORLD					, GIdentity );	


	for( DWORD StageIndex=0; StageIndex<2; StageIndex++ )
	{
		if( StageIndex == 0 )
		{
			SET_STAGESTATE(StageIndex, D3DTSS_COLOROP,D3DTOP_MODULATE );
			SET_STAGESTATE(StageIndex, D3DTSS_COLORARG1,D3DTA_TEXTURE );
			SET_STAGESTATE(StageIndex, D3DTSS_COLORARG2,D3DTA_DIFFUSE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAOP,D3DTOP_MODULATE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );
		}
		else
		{
			SET_STAGESTATE(StageIndex, D3DTSS_COLOROP,D3DTOP_DISABLE );
			SET_STAGESTATE(StageIndex, D3DTSS_COLORARG1,D3DTA_TEXTURE );
			SET_STAGESTATE(StageIndex, D3DTSS_COLORARG2,D3DTA_DIFFUSE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAOP,D3DTOP_DISABLE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
			SET_STAGESTATE(StageIndex, D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );
		}

		SET_SAMPLERSTATE(StageIndex, D3DSAMP_MAGFILTER,D3DTEXF_LINEAR );
		SET_SAMPLERSTATE(StageIndex, D3DSAMP_MINFILTER,D3DTEXF_LINEAR );
		SET_SAMPLERSTATE(StageIndex, D3DSAMP_MIPFILTER,D3DTEXF_LINEAR );
		SET_SAMPLERSTATE(StageIndex, D3DSAMP_MIPMAPLODBIAS, 0 );

		SET_STAGESTATE( StageIndex, D3DTSS_COLOROP					, D3DTOP_DISABLE					);
		SET_STAGESTATE( StageIndex, D3DTSS_COLORARG1				, D3DTA_TEXTURE						);
		SET_STAGESTATE( StageIndex, D3DTSS_COLORARG2				, D3DTA_DIFFUSE						);
		SET_STAGESTATE( StageIndex, D3DTSS_ALPHAOP					, D3DTOP_DISABLE					);
		SET_STAGESTATE( StageIndex, D3DTSS_ALPHAARG1				, D3DTA_DIFFUSE						);
		SET_STAGESTATE( StageIndex, D3DTSS_ALPHAARG2				, D3DTA_DIFFUSE						);
		SET_STAGESTATE( StageIndex, D3DTSS_TEXCOORDINDEX			, StageIndex						);
	//	SET_STAGESTATE( StageIndex, D3DTSS_ADDRESSU				, RenDev->CubemapTextureAddressing	);
	//	SET_STAGESTATE( StageIndex, D3DTSS_ADDRESSV				, RenDev->CubemapTextureAddressing	);
		SET_STAGESTATE( StageIndex, D3DTSS_TEXTURETRANSFORMFLAGS	, D3DTTFF_DISABLE					);
//		SET_STAGESTATE( StageIndex, D3DTSS_ADDRESSW				, RenDev->CubemapTextureAddressing	);
		SET_STAGESTATE( StageIndex, D3DTSS_COLORARG0				, D3DTA_CURRENT						);
		SET_STAGESTATE( StageIndex, D3DTSS_ALPHAARG0				, D3DTA_CURRENT						);
		SET_STAGESTATE( StageIndex, D3DTSS_RESULTARG				, D3DTA_CURRENT						);

		r->SetTexture( StageIndex, NULL );
		HardwareState.Textures[StageIndex] = NULL;
	}

	//RenDev->Direct3DDevice8->GetVertexShader( &HardwareState.VertexShaderHandle );
	HardwareState.VertexShaderHandle = D3DFVF_XYZ;
	HardwareState.PixelShaderHandle = 0;	

	
	memset( &HardwareState.Material, 0, sizeof(D3DMATERIAL9) );
	
	HardwareState.Material.Diffuse.r = HardwareState.Material.Ambient.r = 1.0f;//1.0f;
	HardwareState.Material.Diffuse.g = HardwareState.Material.Ambient.g = 1.0f;;
	HardwareState.Material.Diffuse.b = HardwareState.Material.Ambient.b = 1.0f;;
	HardwareState.Material.Diffuse.a = HardwareState.Material.Ambient.a = 1.0f;;

//GetEngine()->GetRenderer()->SetMaterial( (BYTE*)&mtrl );
								
	//r->SetFVF( HardwareState.VertexShaderHandle );

	for( INT StreamIndex = 0; StreamIndex < 16/*MIN(16,RenDev->DeviceCaps8.MaxStreams)*/; StreamIndex++ )
	{
		
		r->SetStreamSource( 
			StreamIndex, 
			NULL,
			0, 
			0
			);
		HardwareState.VertexStreams[StreamIndex].StreamData		= NULL;
		HardwareState.VertexStreams[StreamIndex].StreamStride	= 0;
		HardwareState.VertexStreams[StreamIndex].StreamDiffer	= true;
	}
	//LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetDevice();									
	r->SetIndices( NULL );
	HardwareState.IndexBufferData		= NULL;
	HardwareState.IndexBufferBaseVertex	= 0;

	for( INT LightIndex = 0; LightIndex < 8; LightIndex++ )
	{
		memset( &HardwareState.Lights[LightIndex], 0, sizeof(HardwareState.Lights[LightIndex]) );
		memset( &HardwareState.LightsEnabled[LightIndex], 0, sizeof(HardwareState.LightsEnabled[LightIndex]) );
		memset( &HardwareState.LightsDiffer[LightIndex], 0, sizeof(HardwareState.LightsDiffer[LightIndex]) );
	}

	memcpy( &WantedState, &HardwareState, sizeof(FD3DInternalState) );

	// 初始化Fog参数
	dwFogColor = 0;
	dwFogNear = 0;
	dwFogFar = 100;
	unguard;
}	

void CD3DDeferredState::MexCommit()
{
	guardfunc;
	ClearCount();
	//	//clock(//GStatsDWORDStats(RenDev->D3DStats.STATS_StateChangeCycles));
	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();									
	// Stats.

	// Kyro specific optimization.
	//!!vogel: TODO: benchmark when particles use alphatest
	if( /*RenDev->IsKyro &&*/ (WantedState.RenderState[ D3DRS_ALPHAREF ] == 0) )
		WantedState.RenderState[ D3DRS_ALPHATESTENABLE ] = 0;

	COMMIT_RENDERSTATE( D3DRS_FILLMODE				);
	COMMIT_RENDERSTATE( D3DRS_SHADEMODE );
	COMMIT_RENDERSTATE( D3DRS_ZWRITEENABLE			);
	COMMIT_RENDERSTATE( D3DRS_ALPHATESTENABLE		);
	COMMIT_RENDERSTATE( D3DRS_SRCBLEND				);
	COMMIT_RENDERSTATE( D3DRS_DESTBLEND			);
	COMMIT_RENDERSTATE( D3DRS_CULLMODE				);
	COMMIT_RENDERSTATE( D3DRS_ZFUNC				);
	COMMIT_RENDERSTATE( D3DRS_ALPHAREF				);
	COMMIT_RENDERSTATE( D3DRS_ALPHAFUNC			);
	COMMIT_RENDERSTATE( D3DRS_ALPHABLENDENABLE		);
	COMMIT_RENDERSTATE( D3DRS_FOGENABLE			);
	COMMIT_RENDERSTATE( D3DRS_ZENABLE			);
	// Avoid unnecessary fog state changes - especially for Kyro cards.
	if( WantedState.RenderState[ D3DRS_FOGENABLE ] )
	{
		WantedState.RenderState[ D3DRS_FOGCOLOR ] = dwFogColor;
		WantedState.RenderState[ D3DRS_FOGSTART ] = dwFogNear;
		WantedState.RenderState[ D3DRS_FOGEND   ] = dwFogFar;
		COMMIT_RENDERSTATE( D3DRS_FOGCOLOR			);
		COMMIT_RENDERSTATE( D3DRS_FOGSTART			);
		COMMIT_RENDERSTATE( D3DRS_FOGEND			);
	}
	else
	{
		// Forget we ever tried to set it.
		WantedState.RenderState[ D3DRS_FOGCOLOR ] = HardwareState.RenderState[ D3DRS_FOGCOLOR ];
		WantedState.RenderState[ D3DRS_FOGSTART ] = HardwareState.RenderState[ D3DRS_FOGSTART ];
		WantedState.RenderState[ D3DRS_FOGEND   ] = HardwareState.RenderState[ D3DRS_FOGEND   ];
	}
	//	COMMIT_RENDERSTATE( D3DRS_ZBIAS				);
	COMMIT_RENDERSTATE( D3DRS_STENCILENABLE		);
	COMMIT_RENDERSTATE( D3DRS_STENCILFAIL			);
	COMMIT_RENDERSTATE( D3DRS_STENCILZFAIL			);
	COMMIT_RENDERSTATE( D3DRS_STENCILPASS			);
	COMMIT_RENDERSTATE( D3DRS_STENCILFUNC			);
	COMMIT_RENDERSTATE( D3DRS_STENCILREF			);
	COMMIT_RENDERSTATE( D3DRS_STENCILMASK			);
	COMMIT_RENDERSTATE( D3DRS_STENCILWRITEMASK		);
	COMMIT_RENDERSTATE( D3DRS_TEXTUREFACTOR		);
	COMMIT_RENDERSTATE( D3DRS_LIGHTING				);
	COMMIT_RENDERSTATE( D3DRS_AMBIENT				);
	COMMIT_RENDERSTATE( D3DRS_COLORVERTEX			);
	COMMIT_RENDERSTATE( D3DRS_SPECULARENABLE		);

	COMMIT_RENDERSTATE( D3DRS_SPECULARMATERIALSOURCE		);

	COMMIT_RENDERSTATE( D3DRS_DIFFUSEMATERIALSOURCE );
	COMMIT_RENDERSTATE( D3DRS_MULTISAMPLEANTIALIAS  );

	for( INT StageIndex=0; StageIndex<eMaxTextureStage/*(INT)RenDev->DeviceCaps8.MaxTextureBlendStages*/; StageIndex++ )
	{
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLOROP				);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLORARG1			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLORARG2			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAOP				);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAARG1			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAARG2			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_TEXCOORDINDEX		);
	}

	for( INT StageIndex=0; StageIndex<eMaxTextureSample; StageIndex++ )
	{
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MINFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MAGFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MIPFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MAXMIPLEVEL			);

		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_ADDRESSU				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_ADDRESSV				);

		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MIPMAPLODBIAS				);		

	}

	for( INT StageIndex=0; StageIndex<eMaxTexture; StageIndex++ )
	{
		if( WantedState.Textures[StageIndex] != HardwareState.Textures[StageIndex] )
		{
			r->SetTexture( StageIndex, WantedState.Textures[StageIndex]);
#ifdef _DEBUG
			TextureChanges++;
#endif
		}
	}

	for( INT LightIndex = 0; LightIndex < 8; LightIndex++ )
	{
		if(WantedState.LightsEnabled[LightIndex] && WantedState.LightsDiffer[LightIndex])
		{
			r->SetLight( LightIndex, &WantedState.Lights[LightIndex] );
#ifdef _DEBUG
			LightChanges++;
#endif
			ClearLightChange(LightIndex);
		}

		if( WantedState.LightsEnabled[LightIndex] != HardwareState.LightsEnabled[LightIndex] )
		{
			r->LightEnable( LightIndex, WantedState.LightsEnabled[LightIndex] );
#ifdef _DEBUG
			LightSetChanges++;
#endif
		}
	}

	{
		r->SetMaterial( &WantedState.Material );
	}

	if (WantedState.IndexBufferData != 0)
	{
		r->SetIndices( WantedState.IndexBufferData/*, WantedState.IndexBufferBaseVertex*/ );
	}

	memcpy( &HardwareState, &WantedState, sizeof(FD3DInternalState) );
	WantedState.IsDirty_Matrices = 0;
	WantedState.IndexBufferData = 0;
	unguard;

}

void CD3DDeferredState::Commit()
{
	guardfunc;
	ClearCount();
//	//clock(//GStatsDWORDStats(RenDev->D3DStats.STATS_StateChangeCycles));
	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();									
	// Stats.
	// Kyro specific optimization.
	//!!vogel: TODO: benchmark when particles use alphatest
	if( /*RenDev->IsKyro &&*/ (WantedState.RenderState[ D3DRS_ALPHAREF ] == 0) )
		WantedState.RenderState[ D3DRS_ALPHATESTENABLE ] = 0;

	COMMIT_RENDERSTATE( D3DRS_FILLMODE				);
	COMMIT_RENDERSTATE( D3DRS_SHADEMODE );
	COMMIT_RENDERSTATE( D3DRS_ZWRITEENABLE			);
	COMMIT_RENDERSTATE( D3DRS_ALPHATESTENABLE		);
	COMMIT_RENDERSTATE( D3DRS_SRCBLEND				);
	COMMIT_RENDERSTATE( D3DRS_DESTBLEND			);
	COMMIT_RENDERSTATE( D3DRS_CULLMODE				);
	COMMIT_RENDERSTATE( D3DRS_ZFUNC				);
	COMMIT_RENDERSTATE( D3DRS_ALPHAREF				);
	COMMIT_RENDERSTATE( D3DRS_ALPHAFUNC			);
	COMMIT_RENDERSTATE( D3DRS_ALPHABLENDENABLE		);
	COMMIT_RENDERSTATE( D3DRS_FOGENABLE			);
	COMMIT_RENDERSTATE( D3DRS_ZENABLE			);
	// Avoid unnecessary fog state changes - especially for Kyro cards.
	if( WantedState.RenderState[ D3DRS_FOGENABLE ] )
	{
		WantedState.RenderState[ D3DRS_FOGCOLOR ] = dwFogColor;
		WantedState.RenderState[ D3DRS_FOGSTART ] = dwFogNear;
		WantedState.RenderState[ D3DRS_FOGEND   ] = dwFogFar;
		COMMIT_RENDERSTATE( D3DRS_FOGCOLOR			);
		COMMIT_RENDERSTATE( D3DRS_FOGSTART			);
		COMMIT_RENDERSTATE( D3DRS_FOGEND			);
	}
	else
	{
		// Forget we ever tried to set it.
		WantedState.RenderState[ D3DRS_FOGCOLOR ] = HardwareState.RenderState[ D3DRS_FOGCOLOR ];
		WantedState.RenderState[ D3DRS_FOGSTART ] = HardwareState.RenderState[ D3DRS_FOGSTART ];
		WantedState.RenderState[ D3DRS_FOGEND   ] = HardwareState.RenderState[ D3DRS_FOGEND   ];
	}
//	COMMIT_RENDERSTATE( D3DRS_ZBIAS				);
	COMMIT_RENDERSTATE( D3DRS_STENCILENABLE		);
	COMMIT_RENDERSTATE( D3DRS_STENCILFAIL			);
	COMMIT_RENDERSTATE( D3DRS_STENCILZFAIL			);
	COMMIT_RENDERSTATE( D3DRS_STENCILPASS			);
	COMMIT_RENDERSTATE( D3DRS_STENCILFUNC			);
	COMMIT_RENDERSTATE( D3DRS_STENCILREF			);
	COMMIT_RENDERSTATE( D3DRS_STENCILMASK			);
	COMMIT_RENDERSTATE( D3DRS_STENCILWRITEMASK		);
	COMMIT_RENDERSTATE( D3DRS_TEXTUREFACTOR		);
	COMMIT_RENDERSTATE( D3DRS_LIGHTING				);
	COMMIT_RENDERSTATE( D3DRS_AMBIENT				);
	COMMIT_RENDERSTATE( D3DRS_COLORVERTEX			);
	COMMIT_RENDERSTATE( D3DRS_SPECULARENABLE		);

	COMMIT_RENDERSTATE( D3DRS_SPECULARMATERIALSOURCE		);
	
	COMMIT_RENDERSTATE( D3DRS_DIFFUSEMATERIALSOURCE );
    COMMIT_RENDERSTATE( D3DRS_MULTISAMPLEANTIALIAS  );

	for( INT StageIndex=0; StageIndex<eMaxTextureStage/*(INT)RenDev->DeviceCaps8.MaxTextureBlendStages*/; StageIndex++ )
	{
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLOROP				);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLORARG1			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_COLORARG2			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAOP				);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAARG1			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_ALPHAARG2			);
		COMMIT_STAGESTATE( StageIndex, D3DTSS_TEXCOORDINDEX		);
	}

	for( INT StageIndex=0; StageIndex<eMaxTextureSample; StageIndex++ )
	{
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MINFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MAGFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MIPFILTER				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MAXMIPLEVEL			);

		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_ADDRESSU				);
		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_ADDRESSV				);

		COMMIT_SAMPLERSTATE( StageIndex, D3DSAMP_MIPMAPLODBIAS				);		

	}
	//unclock(//GStatsDWORDStats(RenDev->D3DStats.STATS_StateChangeCycles));

	//clock(//GStatsDWORDStats(RenDev->D3DStats.STATS_TransformChangeCycles));
	//COMMIT_TRANSFORM( D3DTS_TEXTURE0				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE1				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE2				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE3				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE4				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE5				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE6				);
	//COMMIT_TRANSFORM( D3DTS_TEXTURE7				);

//	SET_TRANSFORM( D3DTS_VIEW,		WantedState.Matrices[D3DTS_VIEW]			);
//	SET_TRANSFORM( D3DTS_PROJECTION,WantedState.Matrices[D3DTS_PROJECTION]		);
//	SET_TRANSFORM( D3DTS_WORLD,		WantedState.Matrices[D3DTS_WORLD]			);

	//unclock(//GStatsDWORDStats(RenDev->D3DStats.STATS_TransformChangeCycles));
//	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();

//	r->SetMaterial()
	//clock(//GStatsDWORDStats(RenDev->D3DStats.STATS_TextureChangeCycles));
	for( INT StageIndex=0; StageIndex<eMaxTexture; StageIndex++ )
	{
		if( WantedState.Textures[StageIndex] != HardwareState.Textures[StageIndex] )
		{
			r->SetTexture( StageIndex, WantedState.Textures[StageIndex]);
#ifdef _DEBUG
			TextureChanges++;
#endif
		}
	}
	//unclock(//GStatsDWORDStats(RenDev->D3DStats.STATS_TextureChangeCycles));

	//clock(//GStatsDWORDStats(RenDev->D3DStats.STATS_LightChangeCycles));
	for( INT LightIndex = 0; LightIndex < 8; LightIndex++ )
	{
		if(WantedState.LightsEnabled[LightIndex] && WantedState.LightsDiffer[LightIndex])
		{
			r->SetLight( LightIndex, &WantedState.Lights[LightIndex] );
#ifdef _DEBUG
			LightChanges++;
#endif
			WantedState.LightsDiffer[LightIndex] = false;
		}

		if( WantedState.LightsEnabled[LightIndex] != HardwareState.LightsEnabled[LightIndex] )
		{
			r->LightEnable( LightIndex, WantedState.LightsEnabled[LightIndex] );
#ifdef _DEBUG
			LightSetChanges++;
#endif
		}
	}

	//if( WantedState.dwFVF != HardwareState.dwFVF )
	{
		//r->SetFVF( WantedState.dwFVF );
		r->SetFVF( WantedState.dwFVF );
	}

	//if( WantedState.Matrices != HardwareState.Matrices )
	{
		r->SetMaterial( &WantedState.Material );
	}

	for( INT StreamIndex = 0; StreamIndex < 16/*MIN(16,RenDev->DeviceCaps8.MaxStreams)*/; StreamIndex++ )
	{
		if (WantedState.VertexStreams[StreamIndex].StreamDiffer)
		{		
			r->SetStreamSource( 
				StreamIndex, 
				WantedState.VertexStreams[StreamIndex].StreamData,
				0,
				WantedState.VertexStreams[StreamIndex].StreamStride
				);
			WantedState.VertexStreams[StreamIndex].StreamDiffer = false;
#ifdef _DEBUG
			StreamSourceChanges++;
#endif
		}
	}

	//if( WantedState.PixelShaderHandle != HardwareState.PixelShaderHandle )
	//{
	//	r->SetPixelShader( WantedState.PixelShaderHandle );
	//}

	//if( WantedState.IndexBufferData != HardwareState.IndexBufferData ||
	//	WantedState.IndexBufferBaseVertex != HardwareState.IndexBufferBaseVertex 
	//	)
	if (WantedState.IndexBufferData != 0)
	{
		r->SetIndices( WantedState.IndexBufferData/*, WantedState.IndexBufferBaseVertex*/ );
	}

    //r->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    //r->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    //r->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

    //r->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    //r->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    //r->SetSamplerState( 1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	memcpy( &HardwareState, &WantedState, sizeof(FD3DInternalState) );
	WantedState.IsDirty_Matrices = 0;
	WantedState.IndexBufferData = 0;
	unguard;
}

void CD3DDeferredState::SetMaterial( D3DMATERIAL9* Mtl )
{
	guardfunc;
	memcpy( &WantedState.Material, Mtl, sizeof(D3DMATERIAL9) );
	unguard;

}

void CD3DDeferredState::SetRenderState( DWORD State, DWORD Value )
{
	guardfunc;
	WantedState.RenderState[State] = Value;
	unguard;
}
void CD3DDeferredState::SetTextureStageState( DWORD Stage, DWORD State, DWORD Value )
{
	guardfunc;
	WantedState.StageState[Stage][State]  = Value;
	unguard;
}
void CD3DDeferredState::SetPixelShader( DWORD Handle )
{
	guardfunc;
	WantedState.PixelShaderHandle = Handle;
	unguard;
}
void CD3DDeferredState::SetStreamSource( DWORD StreamNumber, IDirect3DVertexBuffer9* StreamData, DWORD StreamStride )
{
	guardfunc;
// 	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();									
// 	r->SetStreamSource( 
// 		StreamNumber, 
// 		StreamData,
// 		0,
// 		StreamStride
// 		);

	WantedState.VertexStreams[StreamNumber].StreamData   = StreamData;
	WantedState.VertexStreams[StreamNumber].StreamStride = StreamStride;
	WantedState.VertexStreams[StreamNumber].StreamDiffer = true;
	unguard;
}
void CD3DDeferredState::SetIndices( IDirect3DIndexBuffer9* IndexData, DWORD BaseVertexIndex )
{
	guardfunc;
	WantedState.IndexBufferData	= IndexData;
	WantedState.IndexBufferBaseVertex = BaseVertexIndex;
	unguard;
}
void CD3DDeferredState::SetTexture( DWORD Stage, IDirect3DBaseTexture9* Texture )
{
	guardfunc;
	WantedState.Textures[Stage]	= Texture;
	unguard;
}

void CD3DDeferredState::SetTextureHardware( DWORD Stage, IDirect3DBaseTexture9* Texture )
{
	guardfunc;
	HardwareState.Textures[Stage]	= Texture;
	unguard;
}

// void CD3DDeferredState::SetTransform( DWORD State, CONST D3DMATRIX* MeMatrix )
// {
// 	guardfunc;
// 	memcpy( &WantedState.Matrices[State], MeMatrix, sizeof( D3DMATRIX ) );
// 	WantedState.IsDirty_Matrices |= (1 << State);
// 	unguard;
// }

void CD3DDeferredState::SetFVF( DWORD dwFvf )
{
	guardfunc;
	WantedState.dwFVF = dwFvf;
	unguard;
}

void CD3DDeferredState::SetLight( DWORD Index, CONST D3DLIGHT9* Light )
{
	guardfunc;
	memcpy( &WantedState.Lights[Index], Light, sizeof(D3DLIGHT9) );
	WantedState.LightsDiffer[Index] = true;
	unguard;
}

bool CD3DDeferredState::IsLightChange( DWORD Index )
{
	return WantedState.LightsDiffer[Index];
}

void CD3DDeferredState::GetLight( DWORD Index, D3DLIGHT9* pLight )
{
	guardfunc;
	memcpy( pLight,&WantedState.Lights[Index], sizeof(D3DLIGHT9) );
	unguard;
}

void CD3DDeferredState::ClearLightChange( INT LightIndex )
{
	WantedState.LightsDiffer[LightIndex] = false;
}

void CD3DDeferredState::LightEnable( DWORD LightIndex, BOOL bEnable )
{
	guardfunc;
	WantedState.LightsEnabled[LightIndex] = bEnable;
	WantedState.LightsDiffer[LightIndex] = true;
	unguard;
}

void CD3DDeferredState::DeleteVertexShader( DWORD Handle )
{	
	guardfunc;
	unguard;
}
void CD3DDeferredState::DeletePixelShader( DWORD Handle )
{	
	guardfunc;
	//LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetRealDevice();
	//if( HardwareState.PixelShaderHandle == Handle )
	//{
	//	HardwareState.PixelShaderHandle = 0;		
	//	r->SetPixelShader( 0 );
	//}
	//HRESULT	Result = r->DeletePixelShader(Handle);
	//if( FAILED(Result) )
	//{
	////	Failed
	//}
	unguard;
}

#define MIN(a,b) ((a) < (b) ? (a) : (b))

void CD3DDeferredState::UnSetVertexBuffer( IDirect3DVertexBuffer9* StreamData )
{
	guardfunc;
	LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RenDev->GetDevice();
	for( INT StreamIndex = 0; StreamIndex < /*MIN(16,RenDev->DeviceCaps8.MaxStreams)*/16; StreamIndex++ )
	{
		if( HardwareState.VertexStreams[StreamIndex].StreamData == StreamData )
		{
			HardwareState.VertexStreams[StreamIndex].StreamData   = NULL;
			HardwareState.VertexStreams[StreamIndex].StreamStride = 0;
			r->SetStreamSource( StreamIndex, NULL, 0, 0 );
		}
		if( WantedState.VertexStreams[StreamIndex].StreamData == StreamData )
		{
			WantedState.VertexStreams[StreamIndex].StreamData   = NULL;
			WantedState.VertexStreams[StreamIndex].StreamStride = 0;
		}
	}
	unguard;
}



// bool CD3DDeferredState::IsLightEqual( D3DLIGHT9& first,D3DLIGHT9&  )
// {
// 	return abs(first.Diffuse.r - second.Diffuse.r) < 0.0001
// 		&& abs(first.Diffuse.g - second.Diffuse.g) < 0.0001
// 		&& abs(first.Diffuse.b - second.Diffuse.b) < 0.0001
// 		&& abs(first.Diffuse.a - second.Diffuse.a) < 0.0001
// 		&& abs(first.Specular.r - second.Specular.r) < 0.0001
// 		&& abs(first.Specular.g - second.Specular.g) < 0.0001
// 		&& abs(first.Specular.b - second.Specular.b) < 0.0001
// 		&& abs(first.Specular.a - second.Specular.a) < 0.0001
// 		&& abs(first.Ambient.r - second.Ambient.r) < 0.0001
// 		&& abs(first.Ambient.g - second.Ambient.g) < 0.0001
// 		&& abs(first.Ambient.b - second.Ambient.b) < 0.0001
// 		&& abs(first.Ambient.a - second.Ambient.a) < 0.0001
// 		;
// }


void CD3DDeferredState::ClearCount()
{
#ifdef _DEBUG
	TextureChanges		= 0,
		LightSetChanges		= 0,
		LightChanges		= 0,
		StateChanges		= 0,
		StageChanges		= 0,
		SamplerChanges		= 0,
		StreamSourceChanges	= 0;
	memset(RenderStateDiff,0,sizeof(bool)*300);
	memset(StageDiff,0,sizeof(bool)*eMaxTextureStage*40);
	memset(SamplerDiff,0,sizeof(bool)*eMaxTextureSample*20);
#endif
}

void CD3DDeferredState::ClearFrame()
{
#ifdef _DEBUG
	memset(RenderStateChangeCount,0,sizeof(DWORD)*300);
	memset(StageChangeCount,0,sizeof(DWORD)*eMaxTextureStage*40);
	memset(SamplerChangeCount,0,sizeof(DWORD)*eMaxTextureSample*20);
#endif
}
static char* s_StateName[300] = 
{
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"D3DRS_ZENABLE",
	"D3DRS_FILLMODE",
	"D3DRS_SHADEMODE",
	"10",
	"1",
	"2",
	"3",
	"D3DRS_ZWRITEENABLE",
	"D3DRS_ALPHATESTENABLE",
	"D3DRS_LASTPIXEL",
	"7",
	"8",
	"D3DRS_SRCBLEND",
	"D3DRS_DESTBLEND",
	"1",
	"D3DRS_CULLMODE",
	"D3DRS_ZFUNC",
	"D3DRS_ALPHAREF",
	"D3DRS_ALPHAFUNC",
	"D3DRS_DITHERENABLE",
	"D3DRS_ALPHABLENDENABLE",
	"D3DRS_FOGENABLE",
	"D3DRS_SPECULARENABLE",
	"30",
	"1",
	"2",
	"3",
	"D3DRS_FOGCOLOR",
	"D3DRS_FOGTABLEMODE",
	"D3DRS_FOGSTART",
	"D3DRS_FOGEND",
	"D3DRS_FOGDENSITY",
	"9",
	"40",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"D3DRS_RANGEFOGENABLE",
	"9",
	"50",
	"1",
	"D3DRS_STENCILENABLE",
	"D3DRS_STENCILFAIL",
	"D3DRS_STENCILZFAIL",
	"D3DRS_STENCILPASS",
	"D3DRS_STENCILFUNC",
	"D3DRS_STENCILREF",
	"D3DRS_STENCILMASK",
	"D3DRS_STENCILWRITEMASK",
	"D3DRS_TEXTUREFACTOR",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"70",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"80",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"90",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",

	"100",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"110",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"120",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"D3DRS_WRAP0",
	"D3DRS_WRAP1",
	"D3DRS_WRAP2",
	"D3DRS_WRAP3",
	"D3DRS_WRAP4",
	"D3DRS_WRAP5",
	"D3DRS_WRAP6",
	"D3DRS_WRAP7",
	"D3DRS_CLIPPING",
	"D3DRS_LIGHTING",
	"8",
	"D3DRS_AMBIENT",
	"D3DRS_FOGVERTEXMODE",
	"D3DRS_COLORVERTEX",
	"D3DRS_LOCALVIEWER",
	"D3DRS_NORMALIZENORMALS",
	"4",
	"D3DRS_DIFFUSEMATERIALSOURCE",
	"D3DRS_SPECULARMATERIALSOURCE",
	"D3DRS_AMBIENTMATERIALSOURCE",
	"D3DRS_EMISSIVEMATERIALSOURCE",
	"9",
	"150",
	"D3DRS_VERTEXBLEND",
	"D3DRS_CLIPPLANEENABLE",
	"3",
	"D3DRS_POINTSIZE",
	"D3DRS_POINTSIZE_MIN",
	"D3DRS_POINTSPRITEENABLE",
	"D3DRS_POINTSCALEENABLE",
	"D3DRS_POINTSCALE_A",
	"D3DRS_POINTSCALE_B",
	"D3DRS_POINTSCALE_C",
	"D3DRS_MULTISAMPLEANTIALIAS",
	"D3DRS_MULTISAMPLEMASK",
	"D3DRS_PATCHEDGESTYLE",
	"4",
	"D3DRS_DEBUGMONITORTOKEN",
	"D3DRS_POINTSIZE_MAX",
	"D3DRS_INDEXEDVERTEXBLENDENABLE",
	"D3DRS_COLORWRITEENABLE",
	"9",
	"D3DRS_TWEENFACTOR",
	"D3DRS_BLENDOP",
	"D3DRS_POSITIONDEGREE",
	"D3DRS_NORMALDEGREE",
	"D3DRS_SCISSORTESTENABLE",
	"D3DRS_SLOPESCALEDEPTHBIAS",
	"D3DRS_ANTIALIASEDLINEENABLE",
	"7",
	"D3DRS_MINTESSELLATIONLEVEL",
	"D3DRS_MAXTESSELLATIONLEVEL",
	"D3DRS_ADAPTIVETESS_X",
	"D3DRS_ADAPTIVETESS_Y",
	"D3DRS_ADAPTIVETESS_Z",
	"D3DRS_ADAPTIVETESS_W",
	"D3DRS_ENABLEADAPTIVETESSELLATION",
	"D3DRS_TWOSIDEDSTENCILMODE",
	"D3DRS_CCW_STENCILFAIL",
	"D3DRS_CCW_STENCILZFAIL",
	"D3DRS_CCW_STENCILPASS",
	"D3DRS_CCW_STENCILFUNC",
	"D3DRS_COLORWRITEENABLE1",
	"D3DRS_COLORWRITEENABLE2",
	"D3DRS_COLORWRITEENABLE3",
	"D3DRS_BLENDFACTOR",
	"D3DRS_SRGBWRITEENABLE",
	"D3DRS_DEPTHBIAS",
	"6",
	"7",
	"D3DRS_WRAP8",
	"D3DRS_WRAP9",

	"D3DRS_WRAP10",
	"D3DRS_WRAP11",
	"D3DRS_WRAP12",
	"D3DRS_WRAP13",
	"D3DRS_WRAP14",
	"D3DRS_WRAP15",
	"D3DRS_SEPARATEALPHABLENDENABLE",
	"D3DRS_SRCBLENDALPHA",
	"D3DRS_DESTBLENDALPHA",
	"D3DRS_BLENDOPALPHA",
	"210",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"220",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"230",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"240",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"250",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"260",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"270",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"280",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"290",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",

};

static char* s_TextureStage[40] = {
	"0",
	"D3DTSS_COLOROP",
	"D3DTSS_COLORARG1",
	"D3DTSS_COLORARG2",
	"D3DTSS_ALPHAOP",
	"D3DTSS_ALPHAARG1",
	"D3DTSS_ALPHAARG2",
	"D3DTSS_BUMPENVMAT00",
	"D3DTSS_BUMPENVMAT01",
	"D3DTSS_BUMPENVMAT10",
	"D3DTSS_BUMPENVMAT11",
	"D3DTSS_TEXCOORDINDEX",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"20",
	"1",
	"D3DTSS_BUMPENVLSCALE",
	"D3DTSS_BUMPENVLOFFSET",
	"D3DTSS_TEXTURETRANSFORMFLAGS",
	"5",
	"D3DTSS_COLORARG0",
	"D3DTSS_ALPHAARG0",
	"D3DTSS_RESULTARG",
	"9",
	"30",
	"1",
	"D3DTSS_CONSTANT",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
};

static char* s_SamplerState[20] = {
	"0",
	"D3DSAMP_ADDRESSU",
	"D3DSAMP_ADDRESSV",
	"D3DSAMP_ADDRESSW",
	"D3DSAMP_BORDERCOLOR",
	"D3DSAMP_MAGFILTER",
	"D3DSAMP_MINFILTER",
	"D3DSAMP_MIPFILTER",
	"D3DSAMP_MIPMAPLODBIAS",
	"D3DSAMP_MAXMIPLEVEL",
	"D3DSAMP_MAXANISOTROPY",
	"D3DSAMP_SRGBTEXTURE",
	"D3DSAMP_ELEMENTINDEX",
	"D3DSAMP_DMAPOFFSET",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
};

void CD3DDeferredState::DumpCount()
{
#ifdef _DEBUG
	char temp[2048];
	OutputDebugString("状态变化\n");
	for(int i = 0; i < 300; i++ )
	{
		if (RenderStateChangeCount[i] != 0)
		{
			sprintf_s(temp,2048,"RenderState: %s : %d\n",s_StateName[i],RenderStateChangeCount[i]);
			OutputDebugString(temp);
		}
	}
	OutputDebugString("\nTextureStage变化\n");
	for(int i = 0; i < eMaxTextureStage; ++i)
	{
		for (int j = 0; j < 40; ++j)
		{
			if (StageChangeCount[i][j] != 0)
			{
				sprintf_s(temp,2048,"TextureStage:%d,%s:%d\n",i,s_TextureStage[j],StageChangeCount[i][j]);
				OutputDebugString(temp);
			}
		}
	}
	OutputDebugString("\nSampler状态变化\n");
	for(int i = 0; i < eMaxTextureSample; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (SamplerChangeCount[i][j] != 0)
			{
				sprintf_s(temp,2048,"SamplerStage:%d,%s:%d\n",i,s_SamplerState[j],SamplerChangeCount[i][j]);
				OutputDebugString(temp);
			}
		}
	}
#endif
}


