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
#define MAX_VECTOR_Z 30			// �������zֵ��
#define RAIN_OFFSETVALUE 0.06f	// ������ƫ��ֵ
#define RAINSPRAY_WIDTH 0.5f	// ˮ���Ŀ�Ⱥ͸߶�
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
static int s_nRainSprayShowtime = 100;// ���롣ˮ������֡ÿ֡��ʾʱ�䡣
static DWORD s_VisibleColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
static DWORD s_InvisibleColor = D3DCOLOR_ARGB( 0, 255, 255, 255 );

void MeTimelineRainyEvent::InitializeEvent()
{
	MeTimelineShadeEvent::InitializeEvent();

	// ����Ƿ񱻳�ʼ������
	if( ms_nRainTextureId != -1 )
	{ return; }

	/*	���ǰ����������ɣ��ڲ����򶥵��ܼ����ⲿ�Ƚ�ϡ�衣����Բ��
		����뾶Ϊ100�ס�
	*/
	// ���岼�㡣	
	int nIndex = 0;
	for( ; nIndex < s_nOutterCount; nIndex += 3 )
	{		
		// �������һ�������档
		GenerateRainVertex( nIndex, ms_nRainyRange );
	}
	//�ڲ����㡣
	for( ; nIndex < s_nOutterCount + s_nInnerCount; nIndex += 3 )
	{
		GenerateRainVertex( nIndex, ms_nRainyRange / 2 );
	}

	ms_nRenderCount = 0;
	
	// ������ͼ��
	// 1.���
	char acFilename[MAX_PATH] = {0};
	sprintf_s( acFilename, ms_strRainTextureFilename.c_str(), GetRootPath());
	ms_nRainTextureId = GetEngine()->GetTextureManager()->RegisterTexture( acFilename, NULL, NULL );

	// 2.ˮ��
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

	// ��һ�����㡣//
	float fRangeX = MeUtilityStaff::GetRandValueF( -fRadius, 2 * fRadius );
	float fRangeY = MeUtilityStaff::GetRandValueF( -fRadius, 2 * fRadius );
	float fRangeZ = MeUtilityStaff::GetRandValueF( -MAX_VECTOR_Z, 2 * MAX_VECTOR_Z );
	if( FLOAT_EQUAL( fRangeZ, 0.f ) )
	{ fRangeZ = 0.2f; }
	MeRainVertex kRainVertex0;
	kRainVertex0.m_kPosition = Vector( fRangeX, fRangeY, fRangeZ );		
	kRainVertex0.m_kUV = Vector2( 0, 1 );		
	ms_kRainVertices[nStartPosition] = kRainVertex0;

	// ԭ�����һ���㷽��Ĵ�ֱ�������ɵڶ����㡣
	// ��ֱ����
	MeRainVertex kRainVertex1;
	Vector kRainDir = kRainVertex0.m_kPosition.crossProduct( Vector::UNIT_Z );
	kRainDir.normalize();
	kRainVertex1.m_kPosition = kRainVertex0.m_kPosition + RAIN_OFFSETVALUE * kRainDir;
	kRainVertex1.m_kUV = Vector2( 1, 1 );
	ms_kRainVertices[nStartPosition + 1] = kRainVertex1;

	// z���������ɵ������㣬�������ƫ��0.3 - 1����λ��
	float fZOffset = GetRandomZOffsetValue();
	if( FLOAT_EQUAL( fZOffset, 0.f ) )
	{ fZOffset = 0.4f; }
	MeRainVertex kRainVertex2;
	kRainVertex2.m_kPosition = kRainVertex0.m_kPosition + RAIN_OFFSETVALUE * kRainDir / 2;
	
	// ������
	kRainVertex2.m_kPosition.z  = fRangeZ + fZOffset;

	kRainVertex2.m_kUV = Vector2( 0.5f, 0 );
	ms_kRainVertices[nStartPosition + 2] = kRainVertex2;

	// ˮ����һ�����㡣
	kRainVertex0.m_kPosition.z = 0.f;
	ms_kRainSprayVerticesOffset[nStartPosition] = kRainVertex0.m_kPosition;
	ms_kRainSprayVertices[nStartPosition].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition].m_kUV = Vector2( 0.125f, 0.f );

	// ����ˮ��б�ȡ�
	static float sf3root2Lenth = 0.866f * RAINSPRAY_WIDTH;
	float fLength = kRainVertex0.m_kPosition.lengthsq();
	Vector kSprayDir = kRainVertex0.m_kPosition;
	kSprayDir.normalize();
	kSprayDir =  kSprayDir * 50;
	kSprayDir.z = fLength;
	kSprayDir.normalize();
	Vector kHalfPoint = kRainVertex0.m_kPosition - kSprayDir * sf3root2Lenth;

	// ˮ���ڶ������㡣
	ms_kRainSprayVerticesOffset[nStartPosition + 1] = kHalfPoint - ( RAINSPRAY_WIDTH + fLength / 10000 )* kRainDir / 2;
	ms_kRainSprayVertices[nStartPosition + 1].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition + 1].m_kUV = Vector2( 0.f, 0.25f );

	// ˮ�����������㡣
	ms_kRainSprayVerticesOffset[nStartPosition + 2] = kHalfPoint + ( RAINSPRAY_WIDTH + fLength / 10000 ) * kRainDir / 2;
	ms_kRainSprayVertices[nStartPosition + 2].m_kColor = D3DCOLOR_ARGB( 255, 255, 255, 255 );
	ms_kRainSprayVertices[nStartPosition + 2].m_kUV = Vector2( 0.25f, 0.25f );
}

void MeTimelineRainyEvent::UpdateBeginToFull( const MeTimeValue& kTime )
{
	if( kTime == 0 )// �տ�ʼ
	{ ms_nRenderCount = 0; }

	ms_nRenderCount = Get1_Divide_ToFull_Minus_Start() * ( kTime - GetStartTime() ) * ms_ncRainVecticesCount;

	ms_nRenderCount = min( ms_ncRainVecticesCount, max( 0, ms_nRenderCount ) );	
	ms_nRenderCount = ms_nRenderCount - ms_nRenderCount % 3;
	// ֻ���´�Ȧ���㡣
	UpdateRainVertexZ( ms_nRenderCount, kTime );
	UpdateRainSprayUVnColor( ms_ncRainVecticesCount, kTime );
}

void MeTimelineRainyEvent::UpdateInFull( const MeTimeValue& kTime )
{
	// �������ж��㡣
	ms_nRenderCount = ms_ncRainVecticesCount;
	UpdateRainVertexZ( ms_nRenderCount, kTime );
	UpdateRainSprayUVnColor( ms_ncRainVecticesCount, kTime );
}

void MeTimelineRainyEvent::UpdateFullToEnd( const MeTimeValue& kTime )
{
	// ֻ���´�Ȧ���㡣
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
	// ��ǰ��λ�ò�ͬ�����z��Ϣ��
	if( ( skLastPosition != ms_kPosition ) || ( suiLastCount != uiCount ) )
	{ 
		skLastPosition = ms_kPosition;
		suiLastCount = uiCount;
		bNeedUpdateZValue = true; 
	}

	int nSprayIndex = 0;// Ϊ�˼��ٳ������㣬�����¼ˮ��������
	for( int i = 0 ; i < uiCount; i += 3 )
	{		
		if( !ms_bRainSprayVisible[nSprayIndex].m_bVisible )
		{
			// ����ˮ���߶ȣ�������ˮ��û������ʾ��ʱ��Ÿ��¡�
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

		// �ж��Ƿ����ʾˮ����
		if (ms_kRainVertices[i].m_kPosition.z <= (ms_kRainSprayVertices[i].m_kPosition.z - ms_kPosition.z  + ms_fRaindropHeight))
		{	
			// ˮ����ʼʱ�䡣
			ms_bRainSprayVisible[nSprayIndex].m_kStartTime = kTimeValue;

			// ������ˮ��������ʾ��
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
	
	// ֻ�ڵ�һ��Ҫ��ʾ��ʱ�����һ��λ�ã����ҵ�ǰ��ˮ��û������ʾ��
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
	int nSprayIndex = 0;// Ϊ�˼��ٳ������㣬�����¼ˮ��������
	for( int i = 0 ; i < uiCount ; i += 3 )
	{
		// �����ʾ��ˮ���������uv��
		if( ms_bRainSprayVisible[nSprayIndex].m_bVisible )
		{
			if( ms_kRainSprayVertices[i].m_kUV.x + 0.25f >= 1 )
			{
				ms_kRainSprayVertices[i].m_kUV.x = 0.125f;
				ms_kRainSprayVertices[i + 1].m_kUV.x = 0.f;
				ms_kRainSprayVertices[i + 2].m_kUV.x = 0.25f;
				// ����ȡǰһ������֡uv�е�x��Ϊ������֡��y��������仯��
				if( ( i - 2 ) >= 0 )
				{
					ms_kRainSprayVertices[i].m_kUV.y = ms_kRainSprayVertices[i - 2].m_kUV.x;
					ms_kRainSprayVertices[i + 1].m_kUV.y = ms_kRainSprayVertices[i].m_kUV.y + 0.25f;
					ms_kRainSprayVertices[i + 2].m_kUV.y = ms_kRainSprayVertices[i + 1].m_kUV.y;
				}
				// ����һ���ط���Ϊfalse��
				ms_bRainSprayVisible[nSprayIndex].m_bVisible = false;
				ms_kRainSprayVertices[i].m_kColor = s_InvisibleColor;
				ms_kRainSprayVertices[i + 1].m_kColor = s_InvisibleColor;
				ms_kRainSprayVertices[i + 2].m_kColor = s_InvisibleColor;
				++ nSprayIndex;
				continue;
			}

			// �����δ������¼��ʱ�䣬��������UV����ɫ��
			if( ( kTimeValue - ms_bRainSprayVisible[nSprayIndex].m_kStartTime ) < s_nRainSprayShowtime )
			{
				++ nSprayIndex;
				continue;
			}
			ms_kRainSprayVertices[i].m_kUV.x += 0.25f;
			ms_kRainSprayVertices[i + 1].m_kUV.x += 0.25f;
			ms_kRainSprayVertices[i + 2].m_kUV.x += 0.25f;

			// �´θ���UVʱ�䡣
			ms_bRainSprayVisible[nSprayIndex].m_kStartTime = kTimeValue;

			// ����alphaʹ֮�ɼ���
			ms_kRainSprayVertices[i].m_kColor = s_VisibleColor;
			ms_kRainSprayVertices[i + 1].m_kColor = s_VisibleColor;
			ms_kRainSprayVertices[i + 2].m_kColor = s_VisibleColor;

		}
		else
		{
			// ����alphaʹ֮���ɼ���
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

	// ���������
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