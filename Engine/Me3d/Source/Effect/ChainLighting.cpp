#include "Me3d/Me3d.h"
#include "WordParser.h"
//#include "CfgFileLoader.h"
#include "helper.h"
#include "FuncPerformanceLog.h"
#include "Me3d/engine/Engine.h"
#include "Me3d/include.h"
#include "DataChunkWriter.h"
#include "Me3d/MathLib.h"
#include "Me3d/effect/chainlighting.h"
CChainLightingEffect::CChainLightingEffect():
m_dwStartTime(0),
m_dwLife(0),
m_dwNoiseInterval(0),
m_dwLastNoiseTime(0),
m_fThick(0.0f),
m_fThickVar(0.0f),
m_fFlowSpeed(0.0f),
m_nNumSegment(0),
m_nAction(eActionNotFloat),
m_fFadeOutStart(1.0f),
m_nBind(eBindBody),
m_nTargetBind(eBindBody),
m_pMaster(NULL),
m_pTarget(NULL)
{
	guardfunc;
	ZeroMemory( m_szSound, MAX_PATH );
	ZeroMemory( m_texture.szPath, MAX_PATH );
	unguard;
}
BOOL CChainLightingEffect::IsDead( DWORD dwTime )
{
	guardfunc;
	if( m_pMaster && m_pMaster->IsDestroy() )
	{
		m_pMaster = NULL;
		return TRUE;
	}

	if( m_pTarget && m_pTarget->IsDestroy() )
	{
		m_pTarget = NULL;
		return TRUE;
	}

	return dwTime >= m_dwStartTime + m_dwLife;
	unguard;
}
void CChainLightingEffect::Release()
{
	guardfunc;
	Destroy();
	delete this;
	unguard;
}
void CChainLightingEffect::Destroy()
{
	guardfunc;
	if( m_texture.nTextureId != -1 )
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture( m_texture.nTextureId );
		m_texture.nTextureId = -1;
	}
	m_verts.clear();
	m_segments.clear();
	unguard;
}
BOOL CChainLightingEffect::LoadFromMemory( BYTE* pbyBuffer, int nBufferSize )
{
	if( !pbyBuffer || nBufferSize == NULL )
		return FALSE;
	CDataChunkLoader l( pbyBuffer, nBufferSize );
	while( !l.IsEndOfMemory() )
	{
		if( l.IsChunk( 'text' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_texture.szPath, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.IsChunk( 'sund' ) )
		{
			l.OpenChunk();
			l.ReadToBuffer( (BYTE*)m_szSound, MAX_PATH );
			l.CloseChunk();
		}
		else if( l.TryReadDwordChunk( 'life', m_dwLife ) ){}
		else if( l.TryReadFloatChunk( 'fotm', m_fFadeOutStart ) ){}
		else if( l.TryReadDwordChunk( 'nint', m_dwNoiseInterval ) ){}
		else if( l.TryReadFloatChunk( 'thik', m_fThick ) ){}
		else if( l.TryReadFloatChunk( 'tkvr', m_fThickVar ) ){}
		else if( l.TryReadFloatChunk( 'fspd', m_fFlowSpeed ) ){}
		else if( l.TryReadIntChunk(	'segm', m_nNumSegment ) ){}
		else if( l.TryReadIntChunk( 'act0', m_nAction ) ){}
		else if( l.TryReadIntChunk( 'bind', m_nBind ) ){}
		else if( l.TryReadIntChunk( 'tbnd', m_nTargetBind ) ){}
		else l.SkipChunk();
	}
	return  TRUE;
}
BOOL CChainLightingEffect::Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize )
{
// 	CDataChunkWriter w;
// 	CCfgFileLoader l;
// 	if( !l.LoadFromFile( pszFilename ) )
// 		return FALSE;
// 	if( l.HasKey( "Texture" ) )
// 	{
// 		char szPath[MAX_PATH] = "";
// 		strcpy( szPath, l.GetStringValue( "Texture" ) );
// 		w.WriteBufferChunk( 'text', szPath, MAX_PATH );
// 	}
// 	if( l.HasKey( "Sound" ) )
// 	{
// 		char szPath[MAX_PATH] = "";
// 		strcpy( szPath, l.GetStringValue( "Sound" ) );
// 		w.WriteBufferChunk( 'sund', szPath, MAX_PATH );
// 	}
// 	if( l.HasKey( "Life" ) )
// 	{
// 		//m_dwLife = l.GetIntValue( "Life" );
// 		w.WriteDwordChunk( 'life', l.GetIntValue( "Life" ) );
// 	}
// 	if( l.HasKey( "FadeOutTime" ) )
// 	{
// 		//m_fFadeOutStart = l.GetFloatValue( "FadeOutTime" );
// 		w.WriteFloatChunk( 'fotm', l.GetFloatValue( "FadeOutTime" ) );
// 	}
// 	if( l.HasKey( "NoiseInterval" ) )
// 	{
// 		//m_dwNoiseInterval = l.GetIntValue( "NoiseInterval" );
// 		w.WriteDwordChunk( 'nint', l.GetIntValue( "NoiseInterval" ) );
// 	}
// 	if( l.HasKey( "Thick" ) )
// 	{
// 		//m_fThick = l.GetFloatValue( "Thick" );
// 		w.WriteFloatChunk( 'thik', l.GetFloatValue( "Thick" ) );
// 	}
// 	if( l.HasKey( "ThickVar" ) )
// 	{
// 		//m_fThickVar = l.GetFloatValue( "ThickVar" );
// 		w.WriteFloatChunk( 'tkvr', l.GetFloatValue( "ThickVar" ) );
// 	}
// 	if( l.HasKey( "FloatSpeed" ) )
// 	{
// 		//m_fFlowSpeed = l.GetFloatValue( "FloatSpeed" );
// 		w.WriteFloatChunk( 'fspd', l.GetFloatValue( "FloatSpeed" ) );
// 	}
// 	if( l.HasKey( "Segment" ) )
// 	{
// 		//m_nNumSegment = l.GetIntValue( "Segment" );
// 		w.WriteIntChunk( 'segm', l.GetIntValue( "Segment" ) );
// 	}
// 	if( l.HasKey( "Action" ) )
// 	{
// 		const char* pszAction = l.GetStringValue( "Action" );
// 		int nAction = eActionNotFloat;
// 		if( stricmp( pszAction, "flowin" ) == 0 )
// 		{
// 			nAction = eActionFlowIn;
// 		}
// 		else if( stricmp( pszAction, "flowout" ) == 0 )
// 		{
// 			nAction = eActionFlowOut;
// 		}
// 		w.WriteIntChunk( 'act0', nAction );
// 	}
// 	if( l.HasKey( "Bind" ) )
// 	{
// 		const char* pszBind = l.GetStringValue( "Bind" );
// 		int nBind = eBindBody;
// 		if( stricmp( pszBind, "RightHand" ) == 0 )
// 		{
// 			nBind = eBindRightHand;
// 		}
// 		else if( stricmp( pszBind, "LeftHand" ) == 0 )
// 		{
// 			nBind = eBindLeftHand;
// 		}
// 		else if( stricmp( pszBind, "Body" ) == 0 )
// 		{
// 			nBind = eBindBody;
// 		}
// 		w.WriteIntChunk( 'bind', nBind );
// 	}
// 	if( l.HasKey( "TargetBind" ) )
// 	{
// 		const char* pszBind = l.GetStringValue( "TargetBind" );
// 		int nTargetBind = eBindBody;
// 		if( stricmp( pszBind, "RightHand" ) == 0 )
// 		{
// 			nTargetBind = eBindRightHand;
// 		}
// 		else if( stricmp( pszBind, "LeftHand" ) == 0 )
// 		{
// 			nTargetBind = eBindLeftHand;
// 		}
// 		else if( stricmp( pszBind, "Body" ) == 0 )
// 		{
// 			nTargetBind = eBindBody;
// 		}
// 		w.WriteIntChunk( 'tbnd', nTargetBind );
// 	}
// 	int nUsed = w.GetUsedSize();
// 	BYTE* pbyBuffer = MeDefaultNew BYTE[nUsed];
// 	memcpy( pbyBuffer, w.GetBuffer(), nUsed );
// 	if( ppbyBuffer )
// 		*ppbyBuffer = pbyBuffer;
// 	if( pnBufferSize )
// 		*pnBufferSize = nUsed;
// 	w.Destroy();
	return TRUE;
}
BOOL CChainLightingEffect::LoadSetting( const char* pszFilename )
{
	BYTE* pbyBuffer = NULL;
	int nBufferSize = 0;
	if( !Compile( pszFilename, &pbyBuffer, &nBufferSize ) )
		return FALSE;
	LoadFromMemory( pbyBuffer, nBufferSize );
	delete[] pbyBuffer;

	return TRUE;

	//CCfgFileLoader l;
	//if( !l.LoadFromFile( pszFilename ) )
	//	return FALSE;
	//if( l.HasKey( "Texture" ) )
	//{
	//	strcpy( m_texture.szPath, l.GetStringValue( "Texture" ) );
	//}
	//if( l.HasKey( "Life" ) )
	//{
	//	m_dwLife = l.GetIntValue( "Life" );
	//}
	//if( l.HasKey( "FadeOutTime" ) )
	//{
	//	m_fFadeOutStart = l.GetFloatValue( "FadeOutTime" );
	//}
	//if( l.HasKey( "NoiseInterval" ) )
	//{
	//	m_dwNoiseInterval = l.GetIntValue( "NoiseInterval" );
	//}
	//if( l.HasKey( "Thick" ) )
	//{
	//	m_fThick = l.GetFloatValue( "Thick" );
	//}
	//if( l.HasKey( "ThickVar" ) )
	//{
	//	m_fThickVar = l.GetFloatValue( "ThickVar" );
	//}
	//if( l.HasKey( "FloatSpeed" ) )
	//{
	//	m_fFlowSpeed = l.GetFloatValue( "FloatSpeed" );
	//}
	//if( l.HasKey( "Segment" ) )
	//{
	//	m_nNumSegment = l.GetIntValue( "Segment" );
	//}
	//if( l.HasKey( "Action" ) )
	//{
	//	const char* pszAction = l.GetStringValue( "Action" );
	//	if( stricmp( pszAction, "flowin" ) == 0 )
	//	{
	//		m_nAction = eActionFlowIn;
	//	}
	//	else if( stricmp( pszAction, "flowout" ) == 0 )
	//	{
	//		m_nAction = eActionFlowOut;
	//	}
	//}
	//if( l.HasKey( "Bind" ) )
	//{
	//	const char* pszBind = l.GetStringValue( "Bind" );
	//	if( stricmp( pszBind, "RightHand" ) == 0 )
	//	{
	//		m_nBind = eBindRightHand;
	//	}
	//	else if( stricmp( pszBind, "LeftHand" ) == 0 )
	//	{
	//		m_nBind = eBindLeftHand;
	//	}
	//	else if( stricmp( pszBind, "Body" ) == 0 )
	//	{
	//		m_nBind = eBindBody;
	//	}
	//}
	//if( l.HasKey( "TargetBind" ) )
	//{
	//	const char* pszBind = l.GetStringValue( "TargetBind" );
	//	if( stricmp( pszBind, "RightHand" ) == 0 )
	//	{
	//		m_nTargetBind = eBindRightHand;
	//	}
	//	else if( stricmp( pszBind, "LeftHand" ) == 0 )
	//	{
	//		m_nTargetBind = eBindLeftHand;
	//	}
	//	else if( stricmp( pszBind, "Body" ) == 0 )
	//	{
	//		m_nTargetBind = eBindBody;
	//	}
	//}
	//return TRUE;
}
void CChainLightingEffect::Start()
{
	m_dwStartTime = HQ_TimeGetTime();
	m_texture.nTextureId = GetEngine()->GetTextureManager()->RegisterTexture( 
		m_texture.szPath, FALSE ,TRUE);
	m_verts.reserve( m_nNumSegment*4 );
	m_verts.resize( m_nNumSegment*4 );
	m_segments.reserve( m_nNumSegment+1 );
	m_segments.resize( m_nNumSegment+1 );
}
void CChainLightingEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	DWORD dwPassed = dwTime-m_dwStartTime;
	float t = dwPassed/(float)m_dwLife;
	if( t >= 1.0f )
		return;

	//if( !m_pMaster || !m_pTarget )
	//	return;
	D3DXVECTOR3 vStart;
	if( m_pMaster )
		m_pMaster->GetPos( (float*)&vStart );
	else 
		vStart = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 vTarget;
	if( m_pTarget )
		m_pTarget->GetPos( (float*)&vTarget );
	else
		vTarget = D3DXVECTOR3( 1000, 1000, 1000 );
	D3DXVECTOR3 vRay = vTarget-vStart;
	D3DXVECTOR3 vRayDir;
	D3DXVec3Normalize( &vRayDir, &vRay );

	D3DXVECTOR3 vAntiView = GetMe3dConfig()->GetCamera()->GetViewDir();
	vAntiView *= -1;
	//D3DXVECTOR3 vAntiView(0,0,1);

	D3DXVECTOR3 vRight;
	D3DXVec3Cross( (D3DXVECTOR3*)&vRight, (D3DXVECTOR3*)&vAntiView, (D3DXVECTOR3*)&vRayDir );
	D3DXVec3Normalize( (D3DXVECTOR3*)&vRight, (D3DXVECTOR3*)&vRight );

	D3DXVECTOR3 up = vRay/2;
	D3DXVECTOR3 right = vRight;


	DWORD dwParticleColor = 0xffffffff;
	if( t >= m_fFadeOutStart )
	{
		float dt = (t-m_fFadeOutStart)/(1.0f-m_fFadeOutStart);
		DWORD alpha = DWORD((1.0f-dt)*255);
		dwParticleColor = alpha<<24|0x00ffffff;
	}

	int nNumSegment = m_nNumSegment;

	float dv = 1.0f/nNumSegment;
	D3DXVECTOR3 dl = vRay/nNumSegment;
	SVertex* vertex = &m_verts[0];
	//float const s = m_fThick;
	float fVScroll = 0.0f;
	if( m_nAction == eActionFlowOut )
		fVScroll = -t*m_fFlowSpeed;
	else if( m_nAction == eActionFlowIn )
		fVScroll = t*m_fFlowSpeed;

	float fGlobalScale = GetMe3dConfig()->m_fMdlSpaceScale;
	if( dwTime-m_dwLastNoiseTime >= m_dwNoiseInterval )
	{
		m_dwLastNoiseTime = dwTime;
		for( int nSeg = 0; nSeg < nNumSegment+1; nSeg++ )
		{
			m_segments[nSeg].fPoint[0] = (m_fThick+Random(m_fThickVar))/2*fGlobalScale;
			m_segments[nSeg].fPoint[1] = (m_fThick+Random(m_fThickVar))/2*fGlobalScale;
		}
	}

	for( int nSeg = 0; nSeg < nNumSegment; nSeg++ )
	{
		D3DXVECTOR3 c = vStart+dl*nSeg;
		vertex[nSeg*4+0].p = c+dl-right*m_segments[nSeg+1].fPoint[0];
		vertex[nSeg*4+0].color = dwParticleColor;
		vertex[nSeg*4+0].u = dv*nSeg+dv+fVScroll;
		vertex[nSeg*4+0].v = 0;

		vertex[nSeg*4+1].p = c-right*m_segments[nSeg].fPoint[0];
		vertex[nSeg*4+1].color = dwParticleColor;
		vertex[nSeg*4+1].u = dv*nSeg+fVScroll;
		vertex[nSeg*4+1].v = 0;


		vertex[nSeg*4+2].p = c+dl+right*m_segments[nSeg+1].fPoint[1];
		vertex[nSeg*4+2].color = dwParticleColor;
		vertex[nSeg*4+2].u = dv*nSeg+dv+fVScroll;
		vertex[nSeg*4+2].v = 1;


		vertex[nSeg*4+3].p = c+right*m_segments[nSeg].fPoint[1];
		vertex[nSeg*4+3].color = dwParticleColor;
		vertex[nSeg*4+3].u = dv*nSeg+fVScroll;
		vertex[nSeg*4+3].v = 1;

	}
}
void CChainLightingEffect::Render()
{
	//if( !m_pMaster || !m_pTarget )
	//{
	//	return;
	//}

	float t = (HQ_TimeGetTime()-m_dwStartTime)/(float)m_dwLife;
	if( t >= 1.0f )
		return;



	GetEngine()->GetRenderer()->DirectPushSurface(
		m_texture.nTextureId,
		-1, 
		MEX2_SHADER,
		D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
		sizeof(SVertex),
		(BYTE*)&m_verts[0], 
		(m_nNumSegment)*4,
		//(BYTE*)index, 
		(BYTE*)Emitter::GetCWIndexBuffer(),
		m_nNumSegment*2, 
		eOpModulate1X|eAlphaBlend|eDstBlendOne|eTwoSided|eZWriteDisable|eSortByFarZ|eLightingDisable );
}

void CChainLightingEffect::SetDead()
{
	guardfunc;
	m_dwLife = 0;
	unguard;
}

//void CChainLightingEffect::Cull( D3DXVECTOR3 vPos, float fDistance )
//{
//	guardfunc;
//
//	unguard;
//}