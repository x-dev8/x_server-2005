/*******************************************************************************
* Copyright ShenWang 2009 - All Rights Reserved
* 
* File: 	TileQuadTree.cpp
* Create: 	03/03/2009
* Desc:		地表四叉树，用于可视剪裁
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/TileQuadTree.h"
#include "MeTerrain/TileQuadTreeNode.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "FuncPerformanceLog.h"

TileQuadTree::TileQuadTree():	
m_pRoot(NULL),
m_arrVisibleChunkId(NULL),
m_nChunkTotal(0),
m_bNeedSetFrustumEx(TRUE),
m_pOldFrustumEx(NULL),
m_nObjectCount( 0 )
{
	guardfunc;
	unguard;
}

TileQuadTree::~TileQuadTree()
{
	guardfunc;
	Destroy();
	unguard;
}

void TileQuadTree::Destroy()
{
	guardfunc;
	if( m_pRoot )
	{
		delete m_pRoot;
		m_pRoot = NULL;
	}

	if( m_arrVisibleChunkId )
	{
		delete[] m_arrVisibleChunkId;
		m_arrVisibleChunkId = NULL;
	}
	m_nObjectCount = 0;
	SAFE_DELETE(m_pOldFrustumEx);
	unguard;
}

BOOL TileQuadTree::Create( CWorldTile* pTile )
{
	guardfunc;
    if( !pTile )
        return FALSE;

	m_pRoot = MeNew TileQuadTreeNode;

	const float MAX_FLOAT = 10000.0f;
	m_pRoot->m_vMin = D3DXVECTOR3( MAX_FLOAT, MAX_FLOAT, MAX_FLOAT );
	m_pRoot->m_vMax = D3DXVECTOR3( -MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT );

    flt32 fTileHeight[2];   // 统计tile最大最小Z值
    fTileHeight[0] = 1000.f;
    fTileHeight[1] = -1000.f;
	for( int i = 0; i < pTile->GetChunkTotal(); i++ )
	{
		CWorldChunk* pChunk = pTile->GetChunk(i);
		// TODO: 计算chunk的World BBox，包括地表，水面和静态模型。
		flt32 fHeight[2];
		fHeight[0] = 1000.f;
		fHeight[1] = -1000.f;
		pChunk->CalculateChunkTotalHeight(pTile->GetCResMgr(), fHeight);
        fTileHeight[0] = min(fTileHeight[0], fHeight[0]);
        fTileHeight[1] = max(fTileHeight[1], fHeight[1]);

		// 获取chunk包围盒
		TileQuadTreeNode::ChunkNode kChunkNode;
		kChunkNode.chunk = pChunk;

		float fcenter_x = pChunk->Origin()[0];
		float fcenter_y = pChunk->Origin()[1];
		kChunkNode.vMin.x = fcenter_x - WORLD_CHUNKSIZE * 0.5f;
		kChunkNode.vMin.y = fcenter_y - WORLD_CHUNKSIZE * 0.5f;
		kChunkNode.vMin.z = fHeight[0];
		kChunkNode.vMax.x = kChunkNode.vMin.x + WORLD_CHUNKSIZE;
		kChunkNode.vMax.y = kChunkNode.vMin.y + WORLD_CHUNKSIZE;
		kChunkNode.vMax.z = fHeight[1];
		kChunkNode.sbbox.vecMax = kChunkNode.vMax;
		kChunkNode.sbbox.vecMin = kChunkNode.vMin;
		kChunkNode.Id = i;

		m_pRoot->m_vctChunkNode.push_back( kChunkNode );

		m_pRoot->m_vMin.x = min(kChunkNode.vMin.x,m_pRoot->m_vMin.x);
		m_pRoot->m_vMin.y = min(kChunkNode.vMin.y,m_pRoot->m_vMin.y);
		m_pRoot->m_vMin.z = min(kChunkNode.vMin.z,m_pRoot->m_vMin.z);

		m_pRoot->m_vMax.x = max(kChunkNode.vMax.x,m_pRoot->m_vMax.x);
		m_pRoot->m_vMax.y = max(kChunkNode.vMax.y,m_pRoot->m_vMax.y);
		m_pRoot->m_vMax.z = max(kChunkNode.vMax.z,m_pRoot->m_vMax.z);
	}
    pTile->SetTotalHeight(fTileHeight[0], fTileHeight[1]);

	m_pRoot->m_sbbox.vecMax = m_pRoot->m_vMax;
	m_pRoot->m_sbbox.vecMin = m_pRoot->m_vMin;

	CreateNode( m_pRoot, 0 );

	m_nChunkTotal = pTile->GetChunkTotal();
	m_arrVisibleChunkId = MeDefaultNew BOOL[m_nChunkTotal];
    m_bNeedSetFrustumEx = TRUE;

	return TRUE;
	unguard;
}
//void TileQuadTree::DeleteObject(TileQuadTreeNode* pRoot, void* pPointer )
//{
//	guardfunc;
//	if( !pRoot )
//	{
//		assert( false );
//		return ;
//	}
//	if( pRoot->m_vctChunkNode.size() > 0 )
//	{
//		for( int nObj = 0; nObj < pRoot->m_vctChunkNode.size(); nObj++ )
//		{
//			SceneBuilding* pBuilding = pRoot->m_vctChunkNode[nObj].pBuilding;
//			if( pBuilding == (SceneBuilding*)pPointer )
//			{
//				pRoot->m_vectorObject.erase( pRoot->m_vectorObject.begin()+nObj );
//				break;
//			}
//		}
//	}
//	for( int i = 0; i < 8; i ++ )
//	{
//		if( pRoot->m_pChildNode[i] )
//		{
//			DeleteObject( pRoot->m_pChildNode[i], pPointer );
//		}
//	}
//	unguard;
//}

void Split4( D3DXVECTOR3 vMin, D3DXVECTOR3 vMax, D3DXVECTOR3 vSubMin[4], D3DXVECTOR3 vSubMax[4] )
{
	guardfunc;
	D3DXVECTOR3 vPoint[3][3][3];
	D3DXVECTOR3 vCornor0( vMin.x, vMin.y, vMin.z );
	D3DXVECTOR3 vCornor1( vMax.x, vMax.y, vMax.z );
	D3DXVECTOR3 d = (vCornor1-vCornor0)/2;
	for( int z = 0; z < 3; z++ )
	{
		for( int y = 0; y < 3; y++ )
		{
			for( int x = 0; x < 3; x++ )
			{
				vPoint[x][y][z] = vCornor0+D3DXVECTOR3( d.x*x, d.y*y, d.z*z );
			}
		}
	}

	vSubMin[0] = vPoint[0][0][0];
	vSubMax[0] = vPoint[1][1][2];

	vSubMin[1] = vPoint[1][0][0];
	vSubMax[1] = vPoint[2][1][2];

	vSubMin[2] = vPoint[0][1][0];
	vSubMax[2] = vPoint[1][2][2];

	vSubMin[3] = vPoint[1][1][0];
	vSubMax[3] = vPoint[2][2][2];

	unguard;
}

void TileQuadTree::CreateNode( TileQuadTreeNode* pRoot, int nDepth )
{
	guardfunc;
	if( pRoot == NULL )
		return;

	pRoot->m_nDepth = nDepth;
	if( nDepth > 5 )
	{
		pRoot->m_bLeaf = TRUE;
		return;
	}

	if( pRoot->m_vctChunkNode.size() <= 4 )
	{
		pRoot->m_bLeaf = TRUE;
		return;
	}

	if( pRoot->m_vMax.x - pRoot->m_vMin.x <= WORLD_CHUNKSIZE * 4.f
	 || pRoot->m_vMax.y - pRoot->m_vMin.y <= WORLD_CHUNKSIZE * 4.f )
	{
		pRoot->m_bLeaf = TRUE;
		return;
	}

	// 需要继续分
	D3DXVECTOR3 vMins[4], vMaxs[4];
	Split4( pRoot->m_vMin, pRoot->m_vMax, vMins, vMaxs );
	for( int i = 0; i < 4; i++ )
	{
		TileQuadTreeNode* pChild = MeNew TileQuadTreeNode;
		float fMinZ = 10000.f;
		float fMaxZ = -10000.f;
		pChild->m_vMin = D3DXVECTOR3(vMins[i].x, vMins[i].y, vMins[i].z );
		pChild->m_vMax = D3DXVECTOR3(vMaxs[i].x, vMaxs[i].y, vMaxs[i].z );

		pChild->m_sbbox.vecMin = D3DXVECTOR3(vMins[i].x, vMins[i].y, vMins[i].z );
		pChild->m_sbbox.vecMax = D3DXVECTOR3(vMaxs[i].x, vMaxs[i].y, vMaxs[i].z );

		pChild->m_bHasBuiltBBox = TRUE;

		for( UINT nNode = 0; nNode < pRoot->m_vctChunkNode.size(); nNode++ )
		{
			TileQuadTreeNode::ChunkNode* pkChunkNode = &pRoot->m_vctChunkNode[nNode];
			if( BoxCross(pkChunkNode->vMin, pkChunkNode->vMax, pChild->m_vMin, pChild->m_vMax) )
			{
				// 可见
				pChild->m_vctChunkNode.push_back( *pkChunkNode );
				fMinZ = min(fMinZ, pkChunkNode->vMin.z);
				fMaxZ = max(fMaxZ, pkChunkNode->vMax.z);
			}
		}
		//// 如果有包含chunk
		if( pChild->m_vctChunkNode.size() > 0 )
		{
			pChild->m_vMin.z = fMinZ;
			pChild->m_vMax.z = fMaxZ;
			pChild->m_sbbox.vecMin.z = fMinZ;
			pChild->m_sbbox.vecMax.z = fMaxZ;
			CreateNode( pChild, nDepth+1 );
			pRoot->m_pChildNode[i] = pChild;
		}
		else
			delete pChild;
	}
	pRoot->m_vctChunkNode.clear();
	unguard;
}

int TileQuadTree::Cull( FrustumEx* pFrustumEx, TileQuadTreeNode* pNode )
{
	guardfunc;
	if( !pFrustumEx || !pNode )
		return 0;

	if( m_bNeedSetFrustumEx )
	{
		if( !m_pOldFrustumEx )
			m_pOldFrustumEx = MeNew FrustumEx;
		memcpy(m_pOldFrustumEx, pFrustumEx, sizeof(FrustumEx));		
		m_bNeedSetFrustumEx = FALSE;
	}

	if( m_pRoot == pNode )
	{
		memset(m_arrVisibleChunkId,0,m_nChunkTotal*sizeof(BOOL));
	}

	// 如果被视锥剔除
	if( !pNode->m_bHasBuiltBBox )
	{
		pNode->m_sbbox.vecMax = pNode->m_vMax;
		pNode->m_sbbox.vecMin = pNode->m_vMin;
		pNode->m_bHasBuiltBBox = TRUE;
	}

	if( pFrustumEx->BBoxCrossFrustum( pNode->m_sbbox, false ) != FrustumEx::cross_exclude )
	{
		pNode->m_bVisible = TRUE;
	}
	else
	{
		pNode->m_bVisible = FALSE;
		return 0;
	}


	int nNumObject = pNode->m_vctChunkNode.size();
	if( nNumObject > 0 )
	{
		for( int nObj = 0; nObj < nNumObject; nObj++ )
		{
			// 可见
			int chunkId = pNode->m_vctChunkNode[nObj].Id;
			if( chunkId < m_nChunkTotal && m_arrVisibleChunkId[chunkId] == FALSE )
			{
				if( pFrustumEx->BBoxCrossFrustum( pNode->m_vctChunkNode[nObj].sbbox, false ) != FrustumEx::cross_exclude )
				{
					m_vctVisibleChunk.push_back(pNode->m_vctChunkNode[nObj].chunk);
					m_arrVisibleChunkId[chunkId] = TRUE;
				}
			}
		}
	}
	else
	{
		for( int i = 0; i < 4; i++ )
		{
			if( pNode->m_pChildNode[i] )
				Cull( pFrustumEx, pNode->m_pChildNode[i] );
		}
	}

	return 0;
	unguard;
}

int	TileQuadTree::Intersect( D3DXVECTOR3* pvFrom, D3DXVECTOR3* pvDir, TileQuadTreeNode* pNode )
{
	guardfunc;
	//TRUETIMEFUNC();
	//if( pNode == NULL )
	//{
	//	assert( false && "terrain octree intersect null node" );
	//	return 0;
	//}
	//if( !pNode->m_bbox.Intersect( *(Vector*)pvFrom, *(Vector*)pvDir ) )
	//	return 0;
	//int nObjectCount = 0;
	//if( pNode->m_bLeaf )
	//{
	//	for( int i = 0; i < pNode->m_vectorObject.size(); i++ )
	//	{
	//		// 如果有命中其中的object
	//		//return 1;
	//		SceneBuilding* pBuilding = pNode->m_vectorObject[i].pBuilding;
	//		if( pBuilding->RayHit( pvFrom, pvDir ) )
	//		{
	//			//nObjectCount++;
	//			//break;
	//			return 1;
	//		}
	//	}
	//}
	//else
	//{
	//	for( int i = 0; i < 8; i++ )
	//	{
	//		if( pNode->m_pChildNode[i] )
	//		{
	//			//nObjectCount = Intersect( pvFrom, pvDir, pNode->m_pChildNode[i] );
	//			if( Intersect( pvFrom, pvDir, pNode->m_pChildNode[i] ) )
	//				return 1;
	//			//if( nObjectCount > 0 )
	//			//	break;
	//		}
	//	}
	//}
	//return nObjectCount;
	return 0;
	unguard;
}

bool TileQuadTree::BoxCross( const D3DXVECTOR3& vBoxAMin, const D3DXVECTOR3& vBoxAMax, const D3DXVECTOR3& vBoxBMin, const D3DXVECTOR3& vBoxBMax )
{
	D3DXVECTOR2 vPoint;
	vPoint.x = vBoxAMin.x;
	vPoint.y = vBoxAMin.y;
	// 判断顶点水平方向上是否在BoxB内部
	if( vPoint.x >= vBoxBMin.x && vPoint.y >= vBoxBMin.y && vPoint.x < vBoxBMax.x && vPoint.y < vBoxBMax.y )
		return true;

	vPoint.x = vBoxAMin.x;
	vPoint.y = vBoxAMax.y;
	// 判断顶点水平方向上是否在BoxB内部
	if( vPoint.x >= vBoxBMin.x && vPoint.y > vBoxBMin.y && vPoint.x < vBoxBMax.x && vPoint.y <= vBoxBMax.y )
		return true;

	vPoint.x = vBoxAMax.x;
	vPoint.y = vBoxAMin.y;
	// 判断顶点水平方向上是否在BoxB内部
	if( vPoint.x > vBoxBMin.x && vPoint.y >= vBoxBMin.y && vPoint.x <= vBoxBMax.x && vPoint.y < vBoxBMax.y )
		return true;

	vPoint.x = vBoxAMax.x;
	vPoint.y = vBoxAMax.y;
	// 判断顶点水平方向上是否在BoxB内部
	if( vPoint.x > vBoxBMin.x && vPoint.y > vBoxBMin.y && vPoint.x <= vBoxBMax.x && vPoint.y <= vBoxBMax.y )
		return true;

	return false;
}

void TileQuadTree::UpdateQuadTree( CWorldChunk* pChangeChunk )
{
	if( !pChangeChunk )
		return;

	if( !m_pRoot )
		Create(pChangeChunk->GetParentTile());
	else
		UpdateChunkNode( pChangeChunk, m_pRoot );
}

BOOL TileQuadTree::UpdateChunkNode( CWorldChunk* pChangeChunk, TileQuadTreeNode* pNode )
{
	BOOL bRet = FALSE;

	if( !pNode->m_vctChunkNode.empty() )
	{
		for(UINT chunk=0; chunk<pNode->m_vctChunkNode.size(); chunk++)
		{
			if( pNode->m_vctChunkNode[chunk].chunk == pChangeChunk )
			{
				// 更新父节点Z范围
				pNode->m_vctChunkNode[chunk].vMin.z = min(pNode->m_vctChunkNode[chunk].vMin.z, pChangeChunk->GetTotalHeight()[0]);
				pNode->m_vctChunkNode[chunk].vMax.z = max(pNode->m_vctChunkNode[chunk].vMax.z, pChangeChunk->GetTotalHeight()[1]);
				pNode->m_vctChunkNode[chunk].sbbox.vecMin = pNode->m_vctChunkNode[chunk].vMin;
				pNode->m_vctChunkNode[chunk].sbbox.vecMax = pNode->m_vctChunkNode[chunk].vMax;
				pNode->m_vMin.z = min(pNode->m_vMin.z, pChangeChunk->GetTotalHeight()[0]);
				pNode->m_vMax.z = max(pNode->m_vMax.z, pChangeChunk->GetTotalHeight()[1]);
				pNode->m_sbbox.vecMax = pNode->m_vMax;
				pNode->m_sbbox.vecMin = pNode->m_vMin;
				bRet = TRUE;
			}
		}
	}
	if( !bRet && !pNode->IsLeaf() )
	{
		float fcenter_x = pChangeChunk->Origin()[0];
		float fcenter_y = pChangeChunk->Origin()[1];
		for(int i=0; i<4; i++)
		{
			if( pNode->m_pChildNode[i] )
			{
				if( fcenter_x >= pNode->m_pChildNode[i]->m_vMin.x && fcenter_x < pNode->m_pChildNode[i]->m_vMax.x
					&& fcenter_y >= pNode->m_pChildNode[i]->m_vMin.y && fcenter_y < pNode->m_pChildNode[i]->m_vMax.y )
				{
					// pChangeChunk在第i个chind node
					BOOL bChange = UpdateChunkNode(pChangeChunk, pNode->m_pChildNode[i]);
					if( bChange )
					{
						// 更新父节点Z范围
						pNode->m_vMin.z = min(pNode->m_vMin.z, pNode->m_pChildNode[i]->m_vMin.z);
						pNode->m_vMax.z = max(pNode->m_vMax.z, pNode->m_pChildNode[i]->m_vMax.z);
						pNode->m_sbbox.vecMax = pNode->m_vMax;
						pNode->m_sbbox.vecMin = pNode->m_vMin;
						bRet = TRUE;
					}
					break;
				}
			}
		}
	}

	return bRet;
}

BOOL TileQuadTree::IsNeedCull( FrustumEx* pFrustumEx )
{
	if( m_bNeedSetFrustumEx )
		return TRUE;
	else
		return !(*m_pOldFrustumEx==*pFrustumEx);
}