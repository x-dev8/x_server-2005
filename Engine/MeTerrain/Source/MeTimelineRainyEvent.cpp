#include <MeFoundation/MeFoundationPCH.h>
#include "MeTerrain/WorldPrecompiled.hpp"
#include <MeCommon/HeightMapData.h>
#include "Me3d/Me3d.h"
#include "Me3d/Global.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDX.h"
#include "Me3d/Config.h"
#include "Me3d/Camera.h"
#include "MeTerrain/MeTimelineRainyEvent.h"
//////////////////////////////////////////////////////////////////////////
#define MAX_VECTOR_Z 30			// 雨点的最高z值。
#define RAIN_OFFSETVALUE 0.06f	// 雨点横向偏移值
#define RAINSPRAY_WIDTH 0.5f	// 水花的宽度和高度
#define RAINSPRAY_SLOPE 
//////////////////////////////////////////////////////////////////////////
MeTimelineRainyEvent::MeRainVertex MeTimelineRainyEvent::ms_kRainVertices[ms_ncRainVecticesCount];
MeTimelineRainyEvent::MeRainSprayVertex MeTimelineRainyEvent::ms_kRainSprayVertices[ms_ncRainSprayVecticesCount];
Vector MeTimelineRainyEvent::ms_kRainSprayVerticesOffset[ms_ncRainSprayVecticesCount];
MeTimelineRainyEvent::RainSprayVisible MeTimelineRainyEvent::ms_bRainSprayVisible[ms_ncRainDropCount];
int MeTimelineRainyEvent::ms_nRenderCount = -1;
int MeTimelineRainyEvent::ms_nRainTextureId = -1;
int MeTimelineRainyEvent::ms_nRainSprayTextureId = -1;
std::string MeTimelineRainyEvent::ms_strRainTextureFilename = "./data/texture/Raintex.dds";
std::string MeTimelineRainyEvent::ms_strRainSprayTextureFilename = "./data/texture/RainSprayTex.dds";
int MeTimelineRainyEvent::ms_nRainyRange = 50;
float MeTimelineRainyEvent::ms_fRainSpeed = 0.4f;
float MeTimelineRainyEvent::ms_fRaindropHeight = 1.5f;
Vector MeTimelineRainyEvent::ms_kPosition = Vector( 0, 0, 0 );

static int s_nOutterCount = MeTimelineRainyEvent::ms_ncRainDropCount * 2;
static int s_nInnerCount = MeTimelineRainyEvent::ms_ncRainDropCount;
static int s_nRainSprayShowtime = 100;// 毫秒。水花序列帧每帧显示时间。
static DWORD s_VisibleColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
static DWORD s_InvisibleColor = D3DCOLOR_ARGB( 0, 255, 255, 255 );

void MeTimelineRainyEvent::InitializeEvent()
{
	MeTimelineShadeEvent::InitializeEvent();

	// 检查是否被初始化过。
	if( ms_nRainTextureId != -1 )
	{ return; }

	/*	我们按两部分生成，内部区域顶点密集，外部比较稀疏。总体圆形
		区域半径为100米。
	*/
	// 整体布点。	
	int nIndex = 0;
	for( ; nIndex < s_nOutterCount; nIndex += 3 )
	{		
		// 随机生成一个三角面。
		GenerateRainVertex( nIndex, ms_nRainyRange );
	}
	//内部布点。
	for( ; nIndex < s_nOutterCount + s_nInnerCount; nIndex += 3 )
	{
		GenerateRainVertex( nIndex, ms_nRainyRange / 2 );
	}

	ms_nRenderCount = 0;
	
	// 缓冲贴图。
	// 1.雨点
	char acFilename[MAX_PATH] = {0};
	sprintf_s( acFilename, ms_strRainTextureFilename.c_str(), GetRootPath());
	ms_nRainTextureId = GetEngine()->GetTextureManager()->RegisterTexture( acFilename, NULL, NULL );

	// 2.水花
	sprintf_s( acFilename, ms_strRainSprayTextureFilename.c_str(), GetRootPath() );
	ms_nRainSprayTextureId = GetEngine()->GetTextureManager()->RegisterTexture( acFilename, NULL, NULL );

	memset( ms_bRainSprayVisible, 0, sizeof( ms_bRainSprayVisible ) );
}

void MeTimelineRainyEvent::DestroyEvent()
{}

void MeTimelineRainyEvent::ResetEvent()
{
	MeTimelineShadeEvent::ResetEvent();
	ms_nRenderCount = 0;
}

void MeTimelineRainyEvent::RenderEvent(const Vector &playerPos)
{
	RenderRainSpray();
	RenderRain();
}

void MeTimelineRainyEvent::GenerateRainVertex( int nStartPosition, float fRadius )
{
	if( nStartPosition + 2 >= ms_ncRainVecticesCount || nStartPosition < 0 )
		return;

	// 第一个顶点。//
	float fRangeX = MeUtilityStaff::GetRandValueF( -fRadius, 2 * fRadius );
	float fRangeY = MeUtilityStaff::GetRandValueF( -fRadius, 2 * fRadius );
	float fRangeZ = MeUtilityStaff::GetRandValueF( -MAX_VECTOR_Z, 2 * MAX_VECTOR_Z );
	if( FLOAT_EQUAL( fRangeZ, 0.f ) )
	{ fRangeZ = 0.2f; }
	MeRainVertex kRainVertex0;
	kRainVertex0.m_kPosition = Vector( fRangeX, fRangeY, fRangeZ );		
	kRainVertex0.m_kUV = Vector2( 0, 1 );		
	ms_kRainVertices[nStartPosition] = kRainVertex0;

	// 原点与第一个点方向的垂直方向生成第二个点。
	// 求垂直方向。
	MeRainVertex kRainVertex1;
	Vector kRainDir = kRainVertex0.m_kPosition.crossProduct( Vector::UNIT_Z );
	kRainDir.normalize();
	kRainVertex1.m_kPosition = kRainVertex0.m_kPosition + RAIN_OFFSETVALUE * kRainDir;
	kRainVertex1.m_kUV = Vector2( 1, 1 );
	ms_kRainVertices[nStartPosition + 1] = kRainVertex1;

	// z正向上生成第三个点，纵向随机偏移0.3 - 1个单位。
	float fZOffset = GetRandomZOffsetValue();
	if( FLOAT_EQUAL( fZOffset, 0.f ) )
	{ fZOffset = 0.4f; }
	MeRainVertex kRainVertex2;
	kRainVertex2.m_kPosition = kRainVertex0.m_kPosition + RAIN_OFFSETVALUE * kRainDir / 2;
	
	// 测试用
	kRainVertex2.m_kPosition.z  = fRangeZ + fZOffset;

	kRainVertex2.m_kUV = Vector2( 0.5f, 0 );
	ms_kRainVertices[nStartPosition + 2] = kRainVertex2;

	// 水花第一个顶点。
	kRainVertex0.m_kPosition.z = 0.f;
	ms_kRainSprayVerticesOffset[nStartPosition] = kRainVertex0.m_kPosition;
	ms_kRainSprayVertices[nStartPosition].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition].m_kUV = Vector2( 0.125f, 0.f );

	// 计算水花斜度。
	static float sf3root2Lenth = 0.866f * RAINSPRAY_WIDTH;
	float fLength = kRainVertex0.m_kPosition.lengthsq();
	Vector kSprayDir = kRainVertex0.m_kPosition;
	kSprayDir.normalize();
	kSprayDir =  kSprayDir * 50;
	kSprayDir.z = fLength;
	kSprayDir.normalize();
	Vector kHalfPoint = kRainVertex0.m_kPosition - kSprayDir * sf3root2Lenth;

	// 水花第二个顶点。
	ms_kRainSprayVerticesOffset[nStartPosition + 1] = kHalfPoint - ( RAINSPRAY_WIDTH + fLength / 10000 )* kRainDir / 2;
	ms_kRainSprayVertices[nStartPosition + 1].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition + 1].m_kUV = Vector2( 0.f, 0.25f );

	// 水花第三个顶点。
	ms_kRainSprayVerticesOffset[nStartPosition + 2] = kHalfPoint + ( RAINSPRAY_WIDTH + fLength / 10000 ) * kRainDir / 2;
	ms_kRainSprayVertices[nStartPosition + 2].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition + 2].m_kUV = Vector2( 0.25f, 0.25f );
}

void MeTimelineRainyEvent::UpdateBeginToFull( const MeTimeValue& kTime )
{
	if( kTime == 0 )// 刚开始
	{ ms_nRenderCount = 0; }

	ms_nRenderCount = Get1_Divide_ToFull_Minus_Start() * ( kTime - GetStartTime() ) * ms_ncRainVecticesCount;

	ms_nRenderCount = min( ms_ncRainVecticesCount, max( 0, ms_nRenderCount ) );	
	ms_nRenderCount = ms_nRenderCount - ms_nRenderCount % 3;
	// 只更新大圈顶点。
	UpdateRainVertexZ( ms_nRenderCount, kTime );
	UpdateRainSprayUVnColor( ms_ncRainVecticesCount, kTime );
}

void MeTimelineRainyEvent::UpdateInFull( const MeTimeValue& kTime )
{
	// 更新所有顶点。
	ms_nRenderCount = ms_ncRainVecticesCount;
	UpdateRainVertexZ( ms_nRenderCount, kTime );
	UpdateRainSprayUVnColor( ms_ncRainVecticesCount, kTime );
}

void MeTimelineRainyEvent::UpdateFullToEnd( const MeTimeValue& kTime )
{
	// 只更新大圈顶点。
	ms_nRenderCount = ms_ncRainVecticesCount - 
		Get1_Divide_End_Minus_ToEnd() * ( kTime - GetToEnd() ) * ms_ncRainVecticesCount;

	ms_nRenderCount = min( ms_ncRainVecticesCount, max( 0, ms_nRenderCount ) );
	ms_nRenderCount = ms_nRenderCount - ms_nRenderCount % 3;

	UpdateRainVertexZ( ms_nRenderCount, kTime );
	UpdateRainSprayUVnColor( ms_ncRainVecticesCount, kTime );
}

void MeTimelineRainyEvent::UpdateRainVertexZ( unsigned int uiCount, const MeTimeValue& kTimeValue )
{
	static Vector skLastPosition = Vector( -1, -1, -1 );
	static unsigned int suiLastCount = 0;
	bool bNeedUpdateZValue = false;
	CWorldTile* pTile = CURRENTTILE;
	CHeightMapData* pHeightData = pTile->GetHeightMapData();
	// 与前次位置不同则更新z信息。
	if( ( skLastPosition != ms_kPosition ) || ( suiLastCount != uiCount ) )
	{ 
		skLastPosition = ms_kPosition;
		suiLastCount = uiCount;
		bNeedUpdateZValue = true; 
	}

	int nSprayIndex = 0;// 为了减少除法运算，这里记录水花索引。
	for( int i = 0 ; i < uiCount; i += 3 )
	{		
		if( !ms_bRainSprayVisible[nSprayIndex].m_bVisible )
		{
			// 更新水花高度，仅当该水花没有在显示的时候才更新。
			if( bNeedUpdateZValue && pHeightData )
			{ UpdateRainSprayPosition( i, nSprayIndex, kTimeValue, pHeightData ); }
		}

		ms_kRainVertices[i].m_kPosition.z -= ms_fRainSpeed;
		if (ms_kRainVertices[i].m_kPosition.z <= ( ms_kRainSprayVertices[i].m_kPosition.z - ms_kPosition.z - ms_fRaindropHeight))
		{
			float fZ = MAX_VECTOR_Z;
			ms_kRainVertices[i].m_kPosition.z = fZ;	
			ms_kRainVertices[i + 1].m_kPosition.z = fZ;
			ms_kRainVertices[i + 2].m_kPosition.z = fZ + GetRandomZOffsetValue();	

			++nSprayIndex;

			continue;
		}

		// 判断是否可显示水花。
		if (ms_kRainVertices[i].m_kPosition.z <= (ms_kRainSprayVertices[i].m_kPosition.z - ms_kPosition.z  + ms_fRaindropHeight))
		{	
			// 水花起始时间。
			ms_bRainSprayVisible[nSprayIndex].m_kStartTime = kTimeValue;

			// 标明该水花正在显示。
			ms_bRainSprayVisible[nSprayIndex].m_bVisible = true;
		}

		ms_kRainVertices[i + 1].m_kPosition.z -= ms_fRainSpeed;
		ms_kRainVertices[i + 2].m_kPosition.z -= ms_fRainSpeed;		
		++nSprayIndex;
	}
}

void MeTimelineRainyEvent::UpdateRainSprayPosition( int nVertexIndex, int nSprayIndex,
												   const MeTimeValue& kTimeValue, CHeightMapData* pHeightData )
{
	static float s_fOffset = -0.6f;
	
	// 只在第一次要显示的时候更新一次位置，并且当前该水花没有在显示。
	ms_kRainSprayVertices[nVertexIndex].m_kPosition = ms_kPosition + ms_kRainSprayVerticesOffset[nVertexIndex];
	ms_kRainSprayVertices[nVertexIndex + 1].m_kPosition = ms_kPosition + ms_kRainSprayVerticesOffset[nVertexIndex + 1];
	ms_kRainSprayVertices[nVertexIndex + 2].m_kPosition = ms_kPosition + ms_kRainSprayVerticesOffset[nVertexIndex + 2];

	float fZ = pHeightData->GetHeightbyXY( ms_kRainSprayVertices[nVertexIndex].m_kPosition.x, 
		ms_kRainSprayVertices[nVertexIndex].m_kPosition.y ) - s_fOffset;

	ms_kRainSprayVertices[nVertexIndex].m_kPosition.z = fZ + RAINSPRAY_WIDTH;
	ms_kRainSprayVertices[nVertexIndex + 1].m_kPosition.z = fZ;
	ms_kRainSprayVertices[nVertexIndex + 2].m_kPosition.z = fZ;
	
}

float MeTimelineRainyEvent::GetRandomZOffsetValue()
{
	float fZOffset = ms_fRaindropHeight;//MeUtilityStaff::GetRandValueF( 0.3f, 0.5f );
// 	if( FLOAT_EQUAL( fZOffset, 0.f ) )
// 	{ fZOffset = 0.4f; }

	return fZOffset;
}

void MeTimelineRainyEvent::UpdateRainSprayUVnColor( unsigned int uiCount, const MeTimeValue& kTimeValue )
{
	int nSprayIndex = 0;// 为了减少除法运算，这里记录水花索引。
	for( int i = 0 ; i < uiCount ; i += 3 )
	{
		// 如果显示该水花，则更新uv。
		if( ms_bRainSprayVisible[nSprayIndex].m_bVisible )
		{
			if( ms_kRainSprayVertices[i].m_kUV.x + 0.25f >= 1 )
			{
				ms_kRainSprayVertices[i].m_kUV.x = 0.125f;
				ms_kRainSprayVertices[i + 1].m_kUV.x = 0.f;
				ms_kRainSprayVertices[i + 2].m_kUV.x = 0.25f;
				// 这里取前一个序列帧uv中的x作为此序列帧的y，可随机变化。
				if( ( i - 2 ) >= 0 )
				{
					ms_kRainSprayVertices[i].m_kUV.y = ms_kRainSprayVertices[i - 2].m_kUV.x;
					ms_kRainSprayVertices[i + 1].m_kUV.y = ms_kRainSprayVertices[i].m_kUV.y + 0.25f;
					ms_kRainSprayVertices[i + 2].m_kUV.y = ms_kRainSprayVertices[i + 1].m_kUV.y;
				}
				// 仅此一个地方设为false！
				ms_bRainSprayVisible[nSprayIndex].m_bVisible = false;
				ms_kRainSprayVertices[i].m_kColor = s_InvisibleColor;
				ms_kRainSprayVertices[i + 1].m_kColor = s_InvisibleColor;
				ms_kRainSprayVertices[i + 2].m_kColor = s_InvisibleColor;
				++ nSprayIndex;
				continue;
			}

			// 如果尚未到达更新间隔时间，跳过更新UV和颜色。
			if( ( kTimeValue - ms_bRainSprayVisible[nSprayIndex].m_kStartTime ) < s_nRainSprayShowtime )
			{
				++ nSprayIndex;
				continue;
			}
			ms_kRainSprayVertices[i].m_kUV.x += 0.25f;
			ms_kRainSprayVertices[i + 1].m_kUV.x += 0.25f;
			ms_kRainSprayVertices[i + 2].m_kUV.x += 0.25f;

			// 下次更新UV时间。
			ms_bRainSprayVisible[nSprayIndex].m_kStartTime = kTimeValue;

			// 更改alpha使之可见。
			ms_kRainSprayVertices[i].m_kColor = s_VisibleColor;
			ms_kRainSprayVertices[i + 1].m_kColor = s_VisibleColor;
			ms_kRainSprayVertices[i + 2].m_kColor = s_VisibleColor;

		}
		else
		{
			// 更改alpha使之不可见。
			ms_kRainSprayVertices[i].m_kColor = s_InvisibleColor;
			ms_kRainSprayVertices[i + 1].m_kColor = s_InvisibleColor;
			ms_kRainSprayVertices[i + 2].m_kColor = s_InvisibleColor;
		}
		++ nSprayIndex;
	}
}

void MeTimelineRainyEvent::RenderRain()
{
	if( GetEventState() != EES_Running )
		return;

	RendererDx* pRenderer = ( RendererDx* )GetEngine()->GetRenderer();
	if( !pRenderer )
	{ return; }

	pRenderer->SetRenderState( D3DRS_ZENABLE, TRUE );
	pRenderer->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	pRenderer->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	pRenderer->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pRenderer->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	pRenderer->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pRenderer->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// 	pRenderer->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT );
	// 	pRenderer->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	pRenderer->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTA_TEXTURE );
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); 

	pRenderer->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	// 调整相机。
	D3DXMATRIX matView;
	D3DXVECTOR3 vPos( 0, 0, 0 );
	if (GetMe3dConfig()->GetCamera()->IsLeftHand())
	{
		D3DXMatrixLookAtLH( &matView, &vPos, &GetMe3dConfig()->GetCamera()->GetViewDir(), &D3DXVECTOR3(0,0,1) );
	}
	else
	{
		D3DXMatrixLookAtRH( &matView, &vPos, &GetMe3dConfig()->GetCamera()->GetViewDir(), &D3DXVECTOR3(0,0,1) );
	}
	LPDIRECT3DDEVICE9 pDevice = ( LPDIRECT3DDEVICE9 )pRenderer->GetRealDevice();

	D3DXMATRIX matOldView = pRenderer->GetViewMatrix();

	pRenderer->SetTransform(D3DTS_VIEW, (FLOAT *) &matView);
	D3DXMatrixIdentity(&matView);
	pRenderer->SetTransform(D3DTS_WORLD, (FLOAT *) &matView);

	pRenderer->SetFVF( MeRainVertex::RainVertexFVF );
	pRenderer->SetStreamSource( 0, NULL, 0 );
	pRenderer->SetIndices( NULL );
	pRenderer->SetTexture( 0, NULL );
	// Set texture.
	TextureDx8* pTexture8 = ( TextureDx8* )GetEngine()->GetTextureManager()->GetTextureNoLock( ms_nRainTextureId );
	if( pTexture8 )
	{
		LPDIRECT3DTEXTURE9 pTex = ( LPDIRECT3DTEXTURE9 )pTexture8->GetTexture();
		if( pTex )
		{
			pRenderer->SetTexture( 0, pTex );
		}
	}

	pRenderer->MexCommit();
	pDevice->SetIndices( NULL );
	pRenderer->DrawPrimitiveUP( D3DPT_TRIANGLELIST, ms_nRenderCount / 3, ( void* )&ms_kRainVertices, sizeof( MeRainVertex ) );

	// restore old view
	pRenderer->SetTransform(D3DTS_VIEW, (FLOAT *) &matOldView);
}

void MeTimelineRainyEvent::RenderRainSpray()
{
	if( GetEventState() != EES_Running )
		return;

	RendererDx* pRenderer = ( RendererDx* )GetEngine()->GetRenderer();
	if( !pRenderer )
	{ return; }

	pRenderer->SetRenderState( D3DRS_ZENABLE, TRUE );
	pRenderer->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	pRenderer->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	pRenderer->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	pRenderer->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	pRenderer->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	pRenderer->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// 	pRenderer->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_CURRENT );
	// 	pRenderer->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	pRenderer->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTA_TEXTURE );
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
	pRenderer->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); 

	pRenderer->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	LPDIRECT3DDEVICE9 pDevice = ( LPDIRECT3DDEVICE9 )pRenderer->GetRealDevice();

	pRenderer->SetFVF( MeRainSprayVertex::RainSprayVertexFVF );
	pRenderer->SetStreamSource( 0, NULL, 0 );
	pRenderer->SetIndices( NULL );
	pRenderer->SetTexture( 0, NULL );
	// Set texture.
	TextureDx8* pTexture8 = ( TextureDx8* )GetEngine()->GetTextureManager()->GetTextureNoLock( ms_nRainSprayTextureId );
	if( pTexture8 )
	{
		LPDIRECT3DTEXTURE9 pTex = ( LPDIRECT3DTEXTURE9 )pTexture8->GetTexture();
		if( pTex )
		{
			pRenderer->SetTexture( 0, pTex );
		}
	}

	pRenderer->MexCommit();
	pDevice->SetIndices( NULL );

	pRenderer->DrawPrimitiveUP( D3DPT_TRIANGLELIST, ms_nRenderCount / 3, ( void* )&ms_kRainSprayVertices, sizeof( MeRainSprayVertex ) );
}