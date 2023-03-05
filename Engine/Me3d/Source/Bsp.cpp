
#include "Me3d/Include.h"
#include "math.h"
#include "Me3d/Bsp.h"
#include "Me3d/Prim.h"
//#include "shader.h"
#include "Me3d/Global.h"

//#include "Mex2.h"
#include "Me3d/BaseGraphics.h"
#include "Me3d/Engine/Engine.h" 
#include "Me3d/MathLib.h"

#include "FuncPerformanceLog.h"
#include "Dxsdk/D3D9.h"
#include "Dxsdk/d3dx9.h"
//#include "texture.h"
long const MAX_INTERSECT = 256;
static BspTree::SIntersect g_bspIntersects[MAX_INTERSECT];

BspTree::BspTree()
{
	guardfunc;

	m_pRootNode = 0;
	m_pMex = NULL;
	m_pRenderFaceIDs = NULL;
	Create();

	unguard;
}

BspTree::~BspTree()
{
	guardfunc;

	assert(	m_pRootNode == 0 );
	assert( m_vectorVertex.empty() );
	assert( m_vectorFace.empty() );
	//assert( m_vectorMapname.empty() );
	unguard;
}

bool BspTree::Create()
{
	guardfunc;
	m_nMaxDepth = 12;
	m_nMinNodeLeafCount = 32;
	m_pRootNode = 0;
	m_fMinLeftSize = 0.0f;
	return true;
	unguard;
}

void BspTree::Destroy()
{
	guardfunc;
	DeleteNode( &m_pRootNode );
	m_vectorVertex.clear();
	m_vectorFace.clear();
	if( m_pRenderFaceIDs )
	{
		delete[] m_pRenderFaceIDs;
		m_pRenderFaceIDs = NULL;
	}
	unguard;	
}

void BspTree::DeleteNode( BspNode** ppNode )
{
	guardfunc;
	if( *ppNode == 0 )
		return;
	DeleteNode( &(*ppNode)->pLeftNode );
	DeleteNode( &(*ppNode)->pRightNode );
	(*ppNode)->vectorFaceId.clear();
	delete *ppNode;
	*ppNode = 0;
	unguard;
}

void BspTree::ClearNode( BspNode* pNode )
{
	guardfunc;
	if( pNode == 0 )
		return;
	pNode->pLeftNode = 0;
	pNode->pRightNode = 0;
	pNode->nAxis = 0;
	pNode->nDepth = 0;
	pNode->fSplit = 0;
	float MAX = 10000000.0f;
	pNode->vMax = Vector( -MAX, -MAX, -MAX );
	pNode->vMin = Vector( MAX, MAX, MAX );
	pNode->vectorFaceId.clear();
	unguard;
}
void BspTree::GetAABB( std::vector<int>& vectorFaceId, Vector& vMin, Vector& vMax )
{	
	guardfunc;
	for( int nFaceId = 0; nFaceId < vectorFaceId. size(); nFaceId++ )
	{
		for( int nVert = 0; nVert < 3; nVert++ )
		{
			int f = vectorFaceId[nFaceId];
			Face* pFace = &m_vectorFace[f];
		//	if( pFace->nChunkID == -1 )
		//		continue;
			int nVertexId = pFace->nVertexId[nVert];
//			assert( nVertexId <= m_vectorVertex.size() && "bsp get aabb error" );
			if ( nVertexId >= m_vectorVertex.size() )
			{
				continue;
			}
			Min( &vMin, &m_vectorVertex[nVertexId].p, &vMin );
			Max( &vMax, &m_vectorVertex[nVertexId].p, &vMax );
		}
	}
	unguard;
}

void BspTree::SplitFace( int nFaceId, float fSplit, int nAxis, int* pLeftCount, int* pRightCount, int* pBothCount )
{
	guardfunc;

	assert( nAxis == X_AXIS || nAxis == Y_AXIS || nAxis == Z_AXIS );

	Face* pFace = &m_vectorFace[nFaceId];
	if( pFace->nVertexId[0] < 0 
		|| pFace->nVertexId[1] < 0
		|| pFace->nVertexId[2] < 0
		)
	{
		return;
	}
	int nLeftCount = 0;
	int nRightCount = 0;
	int nBothCount = 0;
	float t[3];
	switch( nAxis )
	{
	case X_AXIS:
		t[0] = m_vectorVertex[pFace->nVertexId[0]].p.x;
		t[1] = m_vectorVertex[pFace->nVertexId[1]].p.x;
		t[2] = m_vectorVertex[pFace->nVertexId[2]].p.x;
		break;
	case Y_AXIS:
		t[0] = m_vectorVertex[pFace->nVertexId[0]].p.y;
		t[1] = m_vectorVertex[pFace->nVertexId[1]].p.y;
		t[2] = m_vectorVertex[pFace->nVertexId[2]].p.y;
		break;
	case Z_AXIS:
		t[0] = m_vectorVertex[pFace->nVertexId[0]].p.z;
		t[1] = m_vectorVertex[pFace->nVertexId[1]].p.z;
		t[2] = m_vectorVertex[pFace->nVertexId[2]].p.z;
		break;
	}
	for( int i = 0; i < 3; i++ )
	{
		int c = FloatCmp( t[i], fSplit );

		if( c < 0 )			// 左边
			nLeftCount++;
		else if( c > 0 )	// 右边
			nRightCount++;
		else				// 正中间
			nBothCount++;
	}
	*pLeftCount = nLeftCount;
	*pRightCount = nRightCount;
	*pBothCount = nBothCount;

	unguard;

}

void BspTree::SplitSpace( BspNode* pRootNode, int nDepth, int nAxis )
{
	guardfunc;
	assert( nAxis == X_AXIS || nAxis == Y_AXIS || nAxis == Z_AXIS );
	
	if( pRootNode == 0 )
		return;
	if( nDepth > m_nMaxDepth )
		return;

	Vector v = pRootNode->vMax-pRootNode->vMin;
	if( v.x < m_fMinLeftSize ||
		v.y < m_fMinLeftSize ||
		v.z < m_fMinLeftSize )
		return;
	// 记录深度
	pRootNode->nDepth = nDepth;
	
	// 需要继续分
	if( pRootNode->vectorFaceId.size() > m_nMinNodeLeafCount )
	{
		pRootNode->pLeftNode = MeNew BspNode;
		pRootNode->pRightNode = MeNew BspNode;
		
		ClearNode( pRootNode->pLeftNode );
		ClearNode( pRootNode->pRightNode );

		pRootNode->nAxis = nAxis;
		
		// 记录bbox
		pRootNode->pLeftNode->vMax = pRootNode->vMax;
		pRootNode->pLeftNode->vMin = pRootNode->vMin;

		pRootNode->pRightNode->vMax = pRootNode->vMax;
		pRootNode->pRightNode->vMin = pRootNode->vMin;
		
		float fSplit = 0.0f;
		
		// 得到最长的那个轴,然后split那个轴，
		float fLengthX = pRootNode->vMax.x-pRootNode->vMin.x;
		float fLengthY = pRootNode->vMax.y-pRootNode->vMin.y;
		float fLengthZ = pRootNode->vMax.z-pRootNode->vMin.z;

		float fMaxAxisLength = fLengthX;
		int nNextAxis = X_AXIS;
		if( fLengthY > fMaxAxisLength )
		{
			nNextAxis = Y_AXIS;
			fMaxAxisLength = fLengthY;
		}
		if( fLengthZ > fMaxAxisLength )
		{
			nNextAxis = Z_AXIS;
			fMaxAxisLength = fLengthZ;
		}
		switch( nNextAxis )
		{
		case X_AXIS:
			fSplit = ( pRootNode->vMin.x+pRootNode->vMax.x )/2;
			pRootNode->pLeftNode->vMax.x = fSplit;
			pRootNode->pRightNode->vMin.x = fSplit;
			break;
		case Y_AXIS:
			fSplit = ( pRootNode->vMin.y+pRootNode->vMax.y )/2;
			pRootNode->pLeftNode->vMax.y = fSplit;
			pRootNode->pRightNode->vMin.y = fSplit;
			break;
		case Z_AXIS:
			fSplit = ( pRootNode->vMin.z+pRootNode->vMax.z )/2;
			pRootNode->pLeftNode->vMax.z = fSplit;
			pRootNode->pRightNode->vMin.z = fSplit;
			break;
		}
		pRootNode->fSplit = fSplit;
		pRootNode->pLeftNode->TryBuildAABB();
		pRootNode->pRightNode->TryBuildAABB();
	
		int nFaceCount = pRootNode->vectorFaceId.size();
		for( int i = 0; i < nFaceCount; i++ )
		{
			int nLeftCount = 0;
			int nRightCount = 0;
			int nBothCount = 0;
			int nFaceId = pRootNode->vectorFaceId[i];
			SplitFace( nFaceId, fSplit, nNextAxis, &nLeftCount, &nRightCount, &nBothCount );

			// 如果左边有
			if( nLeftCount > 0 || nBothCount > 0 )
				pRootNode->pLeftNode->vectorFaceId.push_back( nFaceId );
			if( nRightCount > 0 || nBothCount > 0 )
				pRootNode->pRightNode->vectorFaceId.push_back( nFaceId );
		}
	
		pRootNode->vectorFaceId.clear();
	
		// 递归
		SplitSpace( pRootNode->pLeftNode, nDepth+1, nNextAxis );
		SplitSpace( pRootNode->pRightNode, nDepth+1, nNextAxis );
		
	}
	else
	{
		pRootNode->pLeftNode = 0;
		pRootNode->pRightNode = 0;
	}
	unguard;
}



int BspTree::GetFace( BspNode* pNode, short* pIndexBuffer )
{
	guardfunc;

	if( pNode == 0 )
		return 0;

	int nFaceCount = 0;
	if( pNode->pLeftNode || pNode->pRightNode )
	{
		nFaceCount += GetFace( pNode->pLeftNode, &pIndexBuffer[nFaceCount*3] );
		nFaceCount += GetFace( pNode->pRightNode, &pIndexBuffer[nFaceCount*3] );
	}
	else if( pNode->vectorFaceId.size() > 0 )
	{
		for( int i = 0; i < pNode->vectorFaceId.size(); i++ )
		{
			Face* face = &m_vectorFace[pNode->vectorFaceId[i]];
			pIndexBuffer[nFaceCount*3] = face->nVertexId[0];
			pIndexBuffer[nFaceCount*3+1] = face->nVertexId[1];
			pIndexBuffer[nFaceCount*3+2] = face->nVertexId[2];
			nFaceCount++;
		}
	}
	return nFaceCount;
	
	unguard;
}

void BspTree::GetMaxDepth( BspNode* pNode, int* pDepth )
{
	guardfunc;

	if( pNode == 0 )
		return;
	
	if( pNode->pLeftNode )
		(*pDepth)++;

	GetMaxDepth( pNode->pLeftNode, pDepth );

	unguard;
}
void BspTree::CullFace2( Frustum* frustum, 
							 BspNode* pNode, 
							 D3DXVECTOR3& vPos,
							 float	fOutOfRangeDistance,
							 int nFaceIds[], 
							 int* pnFaceCount )
{
	guardfunc;
	if( pNode == 0 )
		return;
	if( !pNode->bBBoxHasBuilded )
	{
		assert( false );
	}
	//if( fOutOfRangeDistance != 0.0f )
	//{
	//	//float fDist = D3DXVec3Length( &( vPos-*((D3DXVECTOR3*)&pNode->vCenter ) ) );
	//	BOOL bOutOfRange = TRUE;
	//	for( int i = 0; i < 8; i++ )
	//	{
	//		float fDist = D3DXVec3Length( &( vPos-*((D3DXVECTOR3*)&pNode->bbox.v[i] ) ) );
	//		// 距离过远,也要剔除
	//		if( fDist < fOutOfRangeDistance )
	//		{
	//			//return;
	//			bOutOfRange = FALSE;
	//			break;
	//		}

	//	}
	//	if( bOutOfRange )
	//		return;
	//}
	
	if( !frustum->Cull( pNode->bbox ) )
		return;

	//std::vector
	// 到达叶结点
	if( pNode->pLeftNode == 0 && pNode->pRightNode == 0 )
	{
		if( !pNode->bBBoxHasBuilded )
		{
			assert( false );
		}
		if( fOutOfRangeDistance != 0.0f )
		{
			float fDist = D3DXVec3Length( &( vPos-*((D3DXVECTOR3*)&pNode->vCenter ) ) );
			if( fDist > fOutOfRangeDistance )
				return;
		}
		int nNodeFaceCount = pNode->vectorFaceId.size();
		if( nNodeFaceCount > 0 )
		{
			int* pnNodeFaceList = &pNode->vectorFaceId[0];
			BOOL* pbFlags = (BOOL*)&m_vectorFaceFlag[0];
			for( int nFace = 0; nFace < nNodeFaceCount; nFace++ )
			{
				if( !pbFlags[pnNodeFaceList[nFace]] )
				{
					pbFlags[pnNodeFaceList[nFace]] = true;
					if( nFaceIds )
						nFaceIds[(*pnFaceCount)] = pnNodeFaceList[nFace];
					(*pnFaceCount)++;
				}
			}
		}
	}
	else
	{
		CullFace2( frustum, pNode->pLeftNode, vPos, fOutOfRangeDistance, nFaceIds, pnFaceCount );
		CullFace2( frustum, pNode->pRightNode, vPos, fOutOfRangeDistance, nFaceIds, pnFaceCount );
	}
	unguard;
}
void BspTree::RenderBBox( BspNode* node, DWORD dwColor )
{
	guardfunc;

	if( !node )
	{
		return;
		//node = m_pRootNode;
	}
	GetDrawer()->DrawBox3D( 
		*(D3DXVECTOR3*)&node->vMin,
		*(D3DXVECTOR3*)&node->vMax,
		dwColor );
	
	//if( node->vectorFaceId.size() > 0 )
	//{
	//	for( int nFace = 0; nFace < node->vectorFaceId.size(); nFace++ )
	//	{
	//		//GetDrawer()->DrawFlatModel()
	//		Face* pFace = &m_vectorFace[node->vectorFaceId[nFace]];
	//		Vector p0 = m_vectorVertex[pFace->nVertexId[0]].p;
	//		Vector p1 = m_vectorVertex[pFace->nVertexId[1]].p;
	//		Vector p2 = m_vectorVertex[pFace->nVertexId[2]].p;
	//		GetDrawer()->DrawLine3D( *(D3DXVECTOR3*)&p0, *(D3DXVECTOR3*)&p1, 0xffffffff );
	//		GetDrawer()->DrawLine3D( *(D3DXVECTOR3*)&p1, *(D3DXVECTOR3*)&p2, 0xffffffff );
	//		GetDrawer()->DrawLine3D( *(D3DXVECTOR3*)&p2, *(D3DXVECTOR3*)&p0, 0xffffffff );
	//		
	//	}
	//}
	RenderBBox( node->pLeftNode, dwColor );
	RenderBBox( node->pRightNode, dwColor );

	unguard;
}
int BspTree::MakeVisibleList( Frustum* pFrustumEx, D3DXVECTOR3 vPos, float fOutOfRangeDistance )
{
	guardfunc;
	if( m_pRootNode == 0 )
		return 0;
	if( m_vectorFace.size() == 0 )
		return 0;
	memset( &m_vectorFaceFlag[0], 0x00, sizeof( BOOL )*m_vectorFaceFlag.size() );
	m_nNumRenderFace = 0;
	//D3DXVECTOR3 vPos;
	if( pFrustumEx )
		CullFace2( pFrustumEx, m_pRootNode, vPos, fOutOfRangeDistance, m_pRenderFaceIDs, &m_nNumRenderFace );

	Face* pFaceList = &m_vectorFace[0];
	BOOL* pbFaceFlagList = (BOOL*)&m_vectorFaceFlag[0];
	int nNumFace = m_vectorFace.size();
	for( int nFace = 0; nFace < nNumFace; nFace++ )
	{
		// 如果这个面不可见
		if( !pbFaceFlagList[nFace] )
			continue;
	}
	return 0;
	unguard;
}

BspTree::SIntersect* 
BspTree::GetNearestIntersectCmpZ( Vector& vPos, Vector& vDir, BOOL bNormal, float fCurrZ )
{
	guardfunc;
	//	long const MAX_INTERSECT = 128;
	//	static SIntersect intersects[MAX_INTERSECT];
	int nIntersectsCount = GetIntersects(  m_pRootNode, vPos, vDir, g_bspIntersects, bNormal );

	if( nIntersectsCount > 0 )
	{
		int id = -1;
// 		for( int i = 0; i < nIntersectsCount; i++ )
// 		{
// 			if( fCurrZ - g_bspIntersects[i].pos.z < 80.0f*Config::m_fMdlSpaceScale )
// 				return &g_bspIntersects[i];
// 		}
		Vector vUp(0,0,1);
		for( int i = 0; i < nIntersectsCount; i++ )
		{
			bool bSameDir = true;
			if( bNormal && g_bspIntersects[i].vNormal.dot(vUp) < 0 )
				bSameDir = false;

			if( bSameDir )
			{
				if( id == -1 )
					id = i;
				else if( g_bspIntersects[i].t < g_bspIntersects[id].t )
					id = i;
			}
		}
		if( id >= 0 )
			return &g_bspIntersects[id];
		else
			return NULL;
	}
	return NULL;
	unguard;
}

BspTree::SIntersect* 
BspTree::GetNearestIntersect( Vector& vPos, Vector& vDir, BOOL bNormal/*= FALSE*/, BOOL bPickFirst/*= FALSE*/ )
{
	guardfunc;
//	long const MAX_INTERSECT = 128;
//	static SIntersect intersects[MAX_INTERSECT];
	int nIntersectsCount = GetIntersects(  m_pRootNode, vPos, vDir, g_bspIntersects, bNormal, bPickFirst );
	
	if( nIntersectsCount > 0 )
	{
		int id = 0;
		for( int i = 1; i < nIntersectsCount; i++ )
		{
			if( g_bspIntersects[i].t < g_bspIntersects[id].t )
				id = i;
		}
		return &g_bspIntersects[id];
	}
	return NULL;
	unguard;
}

BspTree::SIntersect* BspTree::GetCameraNearestIntersect( Vector& vPos, Vector& vDir )
{
	guardfunc;

	int nIntersectsCount = GetCameraIntersects(  m_pRootNode, vPos, vDir, g_bspIntersects );

	if( nIntersectsCount > 0 )
	{
		int id = 0;
		for( int i = 1; i < nIntersectsCount; i++ )
		{
			if( g_bspIntersects[i].t < g_bspIntersects[id].t )
				id = i;
		}
		return &g_bspIntersects[id];
	}
	return NULL;

	unguard;
}

void BspTree::CameraCorrect( Vector& vPos, Vector& vDir )
{
	guardfunc;
	int nIntersectsCount = CameraCorrect(  m_pRootNode, vPos, vDir );
	return;
	unguard;
}

BOOL BspTree::IsIntersects( BspNode* node, Vector& pos, Vector& dir )
{
	guardfunc;

	if( node == 0 )
		return FALSE;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
	}
	if( !node->bbox.Intersect( pos, dir ) )
		return FALSE;

	int nFaceCount = node->vectorFaceId.size();
	if( nFaceCount > 0 )
	{
		//return FALSE;
		Face* faces = &m_vectorFace[0];
		int* ids = NULL;
		if( node->vectorFaceId.size() > 0 )
			ids = &node->vectorFaceId[0];
		Vertex* vertices = NULL;
		if( m_vectorVertex.size() > 0 )
			vertices = &m_vectorVertex[0];

		Face* f = NULL;
		for( int i = 0; i < nFaceCount; i++ )
		{
			f = &faces[ids[i]];
			D3DXVECTOR3 p0 = *(D3DXVECTOR3*)&(vertices[f->nVertexId[0]].p);
			D3DXVECTOR3 p1 = *(D3DXVECTOR3*)&(vertices[f->nVertexId[1]].p);
			D3DXVECTOR3 p2 = *(D3DXVECTOR3*)&(vertices[f->nVertexId[2]].p);
			float tu, tv, t;

			if( IntersectTri( 
				&p0, 
				&p1, 
				&p2, 
				&pos, 
				&dir,
				&tu, 
				&tv,
				&t ) )
			{
				if( FloatCmp( t, 0 ) <= 0 )
					continue;
				return TRUE;
			}

		}

	}
	// 叶结点

	if( node->pLeftNode )
	{
		if( IsIntersects( node->pLeftNode, pos, dir  ) )
			return TRUE;
	}
	if( node->pRightNode )
	{
		if( IsIntersects( node->pRightNode, pos, dir ) )
			return TRUE;

	}
	return FALSE;

	unguard;
}

int BspTree::Render( BspNode* node )
{
	guardfunc;
	if( node == 0 )
		return 0;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
	}

	int nIntersects = 0;

	if( m_vectorFace.size() == 0 )
		return 0;
	Face* faces = &m_vectorFace[0];
	if( node->vectorFaceId.size() > 0 )
	{

		int* ids = &node->vectorFaceId[0];
		for( int i = 0; i < node->vectorFaceId.size(); i++ )
		{
			Vector p0 = m_vectorVertex[faces[ids[i]].nVertexId[0]].p;
			Vector p1 = m_vectorVertex[faces[ids[i]].nVertexId[1]].p;
			Vector p2 = m_vectorVertex[faces[ids[i]].nVertexId[2]].p;

			GetDrawer()->FillTri( *(D3DXVECTOR3*)&p0, *(D3DXVECTOR3*)&p1, *(D3DXVECTOR3*)&p2, 0x900fffff);
			//GetDrawer()->DrawLine3D( *(D3DXVECTOR3*)&p0,*(D3DXVECTOR3*)&p1, 0x900fffff);
		}
	}
	// 叶结点
	if( node->pLeftNode )
		nIntersects += Render( node->pLeftNode );
	if( node->pRightNode )
		nIntersects += Render( node->pRightNode );
	return nIntersects;
	unguard;
}

void BspTree::Render()
{
	Render( m_pRootNode );
}

bool BspTree::GetIntersectsQuick(BspNode* node, Vector& pos, Vector& dir, BOOL bNormal /* = FALSE */ )
{
	guardfunc;
	if( node == 0 )
		return 0;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
	}
	if( !node->bbox.Intersect( pos, dir ) )
		return 0;
	Face* faces = &m_vectorFace[0];
	if( node->vectorFaceId.size() > 0 )
	{
		int* ids = &node->vectorFaceId[0];
		for( int i = 0; i < node->vectorFaceId.size(); i++ )
		{
			Vector p0 = m_vectorVertex[faces[ids[i]].nVertexId[0]].p;
			Vector p1 = m_vectorVertex[faces[ids[i]].nVertexId[1]].p;
			Vector p2 = m_vectorVertex[faces[ids[i]].nVertexId[2]].p;

			float tu = 0, tv = 0, t = 0;

			if( IntersectTri( &p0, &p1, &p2, &pos, &dir, &tu, &tv,	&t ) )
			{
				if( FloatCmp( t, 0 ) <= 0 )
					continue;
				Vector vNormal;
				if( bNormal )
				{
					//	float tu, tv, t;
					Vector e0 = (p1 - p0);
					Vector e1 = (p2 - p0);
					D3DXVec3Cross( (D3DXVECTOR3*)&vNormal, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
					D3DXVec3Normalize( (D3DXVECTOR3*)&vNormal, (D3DXVECTOR3*)&vNormal );
				}

				return true;
				
			}
		}
	}

	// 叶结点
	if( node->pLeftNode )
		if( GetIntersectsQuick( node->pLeftNode, pos, dir, bNormal  ))
			return true;
	if( node->pRightNode )
		if( GetIntersectsQuick( node->pRightNode, pos, dir, bNormal ))
			return true;

	return false;

	unguard;
}

int	BspTree::GetIntersects( BspNode* node, 
								Vector& pos, 
								Vector& dir, 
								SIntersect* pIntersects,
								BOOL bNormal/* = FALSE*/,
								BOOL bPickFirst/* = FALSE*/ )
{
	guardfunc;
	if( node == 0 )
		return 0;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
        return 0;
	}
	if( !node->bbox.Intersect( pos, dir ) )
		return 0;
	int nIntersects = 0;

	if( m_vectorFace.size() == 0 )
		return 0;
	Face* faces = &m_vectorFace[0];
	if( node->vectorFaceId.size() > 0 )
	{
		int* ids = &node->vectorFaceId[0];
		for( int i = 0; i < node->vectorFaceId.size(); i++ )
		{
			Vector p0 = m_vectorVertex[faces[ids[i]].nVertexId[0]].p;
			Vector p1 = m_vectorVertex[faces[ids[i]].nVertexId[1]].p;
			Vector p2 = m_vectorVertex[faces[ids[i]].nVertexId[2]].p;

			float tu = 0, tv = 0, t = 0;

			if( IntersectTri( &p0, &p1, &p2, &pos, &dir, &tu, &tv,	&t ) )
			{
				if( FloatCmp( t, 0 ) <= 0 )
					continue;
				Vector vNormal;
				if( bNormal )
				{
				//	float tu, tv, t;
					Vector e0 = (p1 - p0);
					Vector e1 = (p2 - p0);
					D3DXVec3Cross( (D3DXVECTOR3*)&vNormal, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
					D3DXVec3Normalize( (D3DXVECTOR3*)&vNormal, (D3DXVECTOR3*)&vNormal );
				}
                
                //防止不正常的坐标导致周围人客户端崩溃下线
                if (&pIntersects[nIntersects] > &g_bspIntersects[MAX_INTERSECT-1] ||
                    &pIntersects[nIntersects] < &g_bspIntersects[0])
                {
                    //__asm {int 3}
                    return 0;
                }

				pIntersects[nIntersects].nFaceId = ids[i];
				pIntersects[nIntersects].u = tu;
				pIntersects[nIntersects].v = tv;
				pIntersects[nIntersects].t = t;
				pIntersects[nIntersects].pos = pos+t*dir;
				pIntersects[nIntersects].vFacePos[0] = *(Vector*)&p0;
				pIntersects[nIntersects].vFacePos[1] = *(Vector*)&p1;
				pIntersects[nIntersects].vFacePos[2] = *(Vector*)&p2;
				pIntersects[nIntersects].vNormal = vNormal;
				nIntersects++;

				if( bPickFirst )
					return nIntersects;

				if( nIntersects >= MAX_INTERSECT )
				{
					OutputDebugString("Bsp Intersects Error");
					return 0;
				}
			}
		}
	}

	// 叶结点
	if( node->pLeftNode )
		nIntersects += GetIntersects( node->pLeftNode, pos, dir, &pIntersects[nIntersects], bNormal, bPickFirst );
	if( nIntersects > 0 && bPickFirst )
		return nIntersects;

	if( node->pRightNode )
		nIntersects += GetIntersects( node->pRightNode, pos, dir, &pIntersects[nIntersects], bNormal, bPickFirst );
	return nIntersects;

	unguard;

}

int BspTree::GetCameraIntersects( BspNode* node, Vector& pos, Vector& dir, SIntersect* pIntersects )
{
	guardfunc;
	if( node == 0 )
		return 0;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
	}
	if( !node->bbox.Intersect( pos, dir ) )
		return 0;
	int nIntersects = 0;

	if( m_vectorFace.size() == 0 )
		return 0;
	Face* faces = &m_vectorFace[0];
	if( node->vectorFaceId.size() > 0 )
	{

		int* ids = &node->vectorFaceId[0];
		for( int i = 0; i < node->vectorFaceId.size(); i++ )
		{
			D3DXVECTOR3 p0 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[0]].p);
			D3DXVECTOR3 p1 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[1]].p);
			D3DXVECTOR3 p2 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[2]].p);
			float tu, tv, t;

			//D3DXVECTOR3 vNormal;
			//D3DXVECTOR3 e0 = p1 - p0;
			//D3DXVECTOR3 e1 = p2 - p0;
			//D3DXVec3Cross( &vNormal, &e0, &e1 );
			//D3DXVec3Normalize( &vNormal, &vNormal );

			//p0 = p0 - vNormal*0.3f;
			//p1 = p1 - vNormal*0.3f;
			//p2 = p2 - vNormal*0.3f;

			if( IntersectTri( 
				&p0, 
				&p1, 
				&p2, 
				&pos, 
				&dir,
				&tu, 
				&tv,
				&t ) )
			{
				if( FloatCmp( t, 0 ) <= 0 )
					continue;

				D3DXVECTOR3 vNormal;
				D3DXVECTOR3 e0 = p1 - p0;
				D3DXVECTOR3 e1 = p2 - p0;
				D3DXVec3Cross( &vNormal, &e0, &e1 );
				D3DXVec3Normalize( &vNormal, &vNormal );

				pIntersects[nIntersects].nFaceId = ids[i];
				pIntersects[nIntersects].u = tu;
				pIntersects[nIntersects].v = tv;
				pIntersects[nIntersects].t = t;
				pIntersects[nIntersects].pos = pos+t*dir;
				pIntersects[nIntersects].vFacePos[0] = *(Vector*)&p0;
				pIntersects[nIntersects].vFacePos[1] = *(Vector*)&p1;
				pIntersects[nIntersects].vFacePos[2] = *(Vector*)&p2;
				pIntersects[nIntersects].vNormal = *(Vector*)&vNormal;
				nIntersects++;
				if( nIntersects >= MAX_INTERSECT )
				{
					OutputDebugString("Bsp Intersects Error");
					return 0;
				}
			}
		}
	}
	// 叶结点
	if( node->pLeftNode )
		nIntersects += GetCameraIntersects( node->pLeftNode, pos, dir, &pIntersects[nIntersects]  );
	if( node->pRightNode )
		nIntersects += GetCameraIntersects( node->pRightNode, pos, dir, &pIntersects[nIntersects] );
	return nIntersects;
	unguard;
}

int BspTree::CameraCorrect( BspNode* node, Vector& pos, Vector& dir )//, SIntersect* pIntersects )
{
	guardfunc;

	if( node == 0 )
		return 0;

	if( !node->bBBoxHasBuilded )
	{
		assert( false );
	}

	if( !node->bbox.Intersect( pos, dir ) )
		return 0;

	int nIntersects = 0;

	if( m_vectorFace.size() == 0 )
		return 0;

	Face* faces = &m_vectorFace[0];
	if( node->vectorFaceId.size() > 0 )
	{
		int* ids = &node->vectorFaceId[0];
		for( int i = 0; i < node->vectorFaceId.size(); i++ )
		{
			D3DXVECTOR3 p0 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[0]].p);
			D3DXVECTOR3 p1 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[1]].p);
			D3DXVECTOR3 p2 = *(D3DXVECTOR3*)&(m_vectorVertex[faces[ids[i]].nVertexId[2]].p);
			D3DXVECTOR3 vPos = *(D3DXVECTOR3*)&pos;
			float tu, tv, t;

			D3DXVECTOR3 vNormal;
			D3DXVECTOR3 e0 = p1 - p0;
			D3DXVECTOR3 e1 = p2 - p0;
			D3DXVec3Cross( &vNormal, &e0, &e1 );
			D3DXVec3Normalize( &vNormal, &vNormal );
			vNormal = -vNormal;

			float fd = D3DXVec3Dot( &p0, &vNormal );

			float fDistToSphere = D3DXVec3Dot( &vNormal, (D3DXVECTOR3*)&pos ) - fd;

			if( fDistToSphere > 0 )
			{
				if( fDistToSphere < 0.4f )
				{
					//vPos = vPos + vNormal*0.4f;

					//char szBuf[256];
					//_snprintf( szBuf, 256, "vNormal X = %f Y = %f Z = %f", vNormal.x, vNormal.y, vNormal.z );
					//OutputDebugString(szBuf );

					//pos = pos + (*(Vector*)&vNormal)*2.0f;
					if( IntersectTri( 
						&p0, 
						&p1, 
						&p2, 
						&vPos, 
						&(-vNormal),
						&tu, 
						&tv,
						&t ) )
					{
						if( FloatCmp( t, 0 ) <= 0 )
							continue;

						pos = pos + (*(Vector*)&vNormal)*(0.4f - fDistToSphere);
					}
				}
			}
		}
	}
	// 叶结点
	if( node->pLeftNode )
		nIntersects += CameraCorrect( node->pLeftNode, pos, dir );//, &pIntersects[nIntersects]  );
	if( node->pRightNode )
		nIntersects += CameraCorrect( node->pRightNode, pos, dir );//, &pIntersects[nIntersects] );
	return nIntersects;
	unguard;
}

BOOL BspTree::AddMesh( float* pVertices, 
						   int nVertexCount, 
						   short* pFaces, 
						   int nFaceCount )
{
	guardfunc;

	int nIndexStart = m_vectorVertex.size();
	for( int i = 0; i < nVertexCount; i++ )
	{
		Vertex v;
		v.p.x = pVertices[i*3];
		v.p.y = pVertices[i*3+1];
		v.p.z = pVertices[i*3+2];
		m_vectorVertex.push_back( v );
	}
	for(int  i = 0; i < nFaceCount; i++ )
	{
		Face f;
		f.nVertexId[0] = pFaces[i*3]+nIndexStart;
		f.nVertexId[1] = pFaces[i*3+1]+nIndexStart;
		f.nVertexId[2] = pFaces[i*3+2]+nIndexStart;
		m_vectorFace.push_back( f );
		m_vectorFaceFlag.push_back( 0 );
	}
	return TRUE;

	unguard;
}
void BspTree::BspNode::TryBuildAABB()
{
	guardfunc;

	if( bBBoxHasBuilded )
		return;
	bbox.BuildAABB( vMin, vMax );
	vCenter = ( vMax+vMin )/2;
	bBBoxHasBuilded = TRUE;

	unguard;
}
BOOL BspTree::CreateTree2()
{
	guardfunc;
	m_pRootNode = MeNew BspNode;
	ClearNode( m_pRootNode );
	for( int nFaceId = 0; nFaceId < m_vectorFace.size(); nFaceId++ )
		m_pRootNode->vectorFaceId.push_back( nFaceId );
	GetAABB( m_pRootNode->vectorFaceId, m_pRootNode->vMin, m_pRootNode->vMax );	
	
	
	Vector v = m_pRootNode->vMax-m_pRootNode->vMin;
	float fMax = v.x;
	if( v.y > fMax )
		fMax = v.y;
	if( v.z > fMax )
		fMax = v.z;
	m_pRootNode->vMax = m_pRootNode->vMin+Vector(fMax,fMax,fMax);
	m_pRootNode->TryBuildAABB();
	
	SplitSpace( m_pRootNode, 0, X_AXIS );
	return TRUE;

	unguard;
}

BOOL BspTree::Transform( float x, float y, float z, float fScale, BspNode* pNode )
{
	guardfunc;

	if( pNode == NULL )
		return FALSE;
	if( pNode == m_pRootNode )
	{
		for( int nVert = 0; nVert < m_vectorVertex.size(); nVert++ )
		{
			m_vectorVertex[nVert].p *= fScale;
		}
	}

	for( int i = 0; i < 8; i++ )
	{
		pNode->bbox.v[i] *= fScale;
		pNode->bbox.v[i].x += x;
		pNode->bbox.v[i].y += y;
		pNode->bbox.v[i].z += z;
	}
	Transform( x, y, z, fScale, pNode->pLeftNode );
	Transform( x, y, z, fScale, pNode->pRightNode );
	
	return TRUE;

	unguard;
}