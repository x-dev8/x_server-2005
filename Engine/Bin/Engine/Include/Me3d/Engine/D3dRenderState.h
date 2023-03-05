/*=============================================================================
D3dRenderState.h: Unreal Direct3D deferred state header.
Copyright 2001 Epic Games, Inc. All Rights Reserved.

Revision history:
* Created by Daniel Vogel
=============================================================================*/

#ifndef HEADER_D3DRENDERSTATE
#define HEADER_D3DRENDERSTATE

#include "MeRTLibs.h"
#include "Dxsdk/d3dx9.h"
#include "Dxsdk/d3d9types.h"
#include "Renderer.h"

//
//enum ED3DRenderState
//{
//	D3DRS_FILLMODE							= 0,
//	RS_ZWRITEENABLE,
//	RS_ALPHATESTENABLE,
//	RS_SRCBLEND,
//	RS_DESTBLEND,
//	RS_CULLMODE,
//	RS_ZFUNC,
//	RS_ALPHAREF,
//	RS_ALPHAFUNC,
//	RS_ALPHABLENDENABLE,
//	RS_FOGENABLE,
//	RS_FOGCOLOR,
//	RS_FOGSTART,
//	RS_FOGEND,
//	RS_ZBIAS,
//	RS_STENCILENABLE,
//	RS_STENCILFAIL,
//	RS_STENCILZFAIL,
//	RS_STENCILPASS,
//	RS_STENCILFUNC,
//	RS_STENCILREF,
//	RS_STENCILMASK,
//	RS_STENCILWRITEMASK,
//	RS_TEXTUREFACTOR,
//	RS_LIGHTING,
//	RS_AMBIENT,
//	RS_COLORVERTEX,
//	RS_MAX
//};
//
//enum ED3DTextureStateStage
//{
//	TSS_COLOROP							= 0,
//	TSS_COLORARG1,
//	TSS_COLORARG2,
//	TSS_ALPHAOP,
//	TSS_ALPHAARG1,
//	TSS_ALPHAARG2,
//	TSS_TEXCOORDINDEX,
//	TSS_ADDRESSU,
//	TSS_ADDRESSV,
//	TSS_TEXTURETRANSFORMFLAGS,
//	TSS_ADDRESSW,
//	TSS_COLORARG0,
//	TSS_ALPHAARG0,
//	TSS_RESULTARG,
//	TSS_MAX
//};
//
//
//enum ED3DTransformState
//{
//	TS_TEXTURE0				= 0,	//!! vogel: this order is required.
//	TS_TEXTURE1,
//	TS_TEXTURE2,
//	TS_TEXTURE3,
//	TS_TEXTURE4,
//	TS_TEXTURE5,
//	TS_TEXTURE6,
//	TS_TEXTURE7,
//	TS_VIEW,
//	TS_PROJECTION,
//	TS_WORLD,						//!! macro in D3D
//	TS_MAX
//};

class CD3DDeferredState
{
public:
	enum
	{
		eMaxTextureStage = 2,
		eMaxTexture = 8,
		eMaxTextureSample = 8,
	};
public:
	void Init( IRenderer* InRenDev );
	void Commit();
	void MexCommit();

	void SetRenderState( DWORD State, DWORD Value );
	void SetTextureStageState( DWORD Stage, DWORD State, DWORD Value );
	void SetStreamSource( DWORD StreamNumber, IDirect3DVertexBuffer9* StreamData, DWORD Stride );
	void SetIndices( IDirect3DIndexBuffer9* pIndexData, DWORD BaseVertexIndex );
	void SetTexture( DWORD Stage, IDirect3DBaseTexture9* pTexture );
	void SetTextureHardware( DWORD Stage, IDirect3DBaseTexture9* pTexture );
// 	void SetTransform( DWORD State, CONST D3DMATRIX* pMatrix );
	void SetLight( DWORD Index, CONST D3DLIGHT9* pLight );
	void GetLight( DWORD Index, D3DLIGHT9* pLight );
	bool IsLightChange(DWORD Index);
	void ClearLightChange( INT LightIndex );
	void SetFVF( DWORD dwFvf );
	void SetMaterial( D3DMATERIAL9* Mtl );
	void LightEnable( DWORD LightIndex, BOOL bEnable );
	void DeleteVertexShader( DWORD Handle );
	void UnSetVertexBuffer( IDirect3DVertexBuffer9* StreamData );
	void SetPixelShader( DWORD Handle );
	void DeletePixelShader( DWORD Handle );
	void SetSamplerState ( DWORD dwStage, DWORD dwType, DWORD dwValue );

	void SetFogColor( DWORD fogcolor ) {dwFogColor = fogcolor;};
	void SetFogNear( DWORD fognear ) {dwFogNear = fognear;};
	void SetFogFar( DWORD fogfar ) {dwFogFar = fogfar;};

	DWORD GetRenderState( DWORD State ) { return WantedState.RenderState[State]; }
	void					ClearFrame();
	void					DumpCount();

protected:
// 	bool IsLightEqual(D3DLIGHT9& first,D3DLIGHT9& second);
	struct FD3DInternalState
	{
		DWORD						RenderState[300];
		DWORD						StageState[eMaxTextureStage][40];
		DWORD						Samplerstate[eMaxTextureSample][20];	//SAMPLERSTATE
		D3DMATRIX					Matrices[4];
		DWORD						IsDirty_Matrices;

		DWORD						VertexShaderHandle;
		DWORD						PixelShaderHandle;
		DWORD						dwFVF;
		IDirect3DVertexShader9*		pShader;

		struct FD3DDeferredVertexStream
		{
			IDirect3DVertexBuffer9*		StreamData;
			UINT						StreamStride;
			BOOL						StreamDiffer;
		}								VertexStreams[16];

		IDirect3DIndexBuffer9*		IndexBufferData;
		UINT						IndexBufferBaseVertex;

		IDirect3DBaseTexture9*		Textures[eMaxTexture];
		D3DLIGHT9					Lights[8];
		BOOL						LightsEnabled[8];
		BOOL						LightsDiffer[8];

		D3DMATERIAL9				Material;
	};

	IRenderer*					RenDev;
	FD3DInternalState				WantedState;
	FD3DInternalState				HardwareState;

	DWORD							dwFogColor;
	DWORD							dwFogNear;
	DWORD							dwFogFar;

	void					ClearCount();
#ifdef _DEBUG
	//state change count
	INT TextureChanges		;
	INT LightSetChanges		;
	INT LightChanges		;
	INT StateChanges		;
	INT StageChanges		;
	INT SamplerChanges		;
	INT StreamSourceChanges	;
	bool RenderStateDiff[300];
	bool StageDiff[eMaxTextureStage][40];
	bool SamplerDiff[eMaxTextureSample][20];
	DWORD RenderStateChangeCount[300];
	DWORD StageChangeCount[eMaxTextureStage][40];
	DWORD SamplerChangeCount[eMaxTextureSample][20];
#endif

};

#endif