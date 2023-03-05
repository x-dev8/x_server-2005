/*******************************************************************************
* Copyright ShenWang 2009 - All Rights Reserved
* 
* File: 	TileQuadTree.h
* Create: 	03/03/2009
* Desc:		地表四叉树，用于可视剪裁
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __TILEQUADTREE_H__
#define __TILEQUADTREE_H__

class TileQuadTreeNode;
class CWorldTile;
class CWorldChunk;
class FrustumEx;
class TileQuadTree : public MeCommonAllocObj<TileQuadTree>
{
public:
	TileQuadTree();
	~TileQuadTree();
	BOOL	Create( CWorldTile* pTile );
	void	Destroy();
	BOOL	IsNeedCull(FrustumEx* pFrustumEx);
	void	ClearVisible() {m_vctVisibleChunk.clear(); m_bNeedSetFrustumEx = TRUE;}
	std::vector<CWorldChunk*>& GetVisible() { return m_vctVisibleChunk; }
	//void	ClearVisited();
	int		Cull( FrustumEx* pFrustumEx, TileQuadTreeNode* pNode );
	void	CreateNode( TileQuadTreeNode* pRoot, int nDepth );
	//void	RenderBBox();
	TileQuadTreeNode* GetRootNode(){ return m_pRoot; }
	//void	DeleteObject( TileQuadTreeNode* pRoot, void* pPointer );
	void	UpdateQuadTree( CWorldChunk* pChangeChunk );
	BOOL	UpdateChunkNode( CWorldChunk* pChangeChunk, TileQuadTreeNode* pNode );	// 更新并返回ChunkNode高度是否有变化

	int		Intersect( D3DXVECTOR3* pvFrom, D3DXVECTOR3* pvDir, TileQuadTreeNode* pNode );
	void    SetCameraPos(const D3DXVECTOR3& pos)
	{
		m_camPos.x = pos.x;
		m_camPos.y = pos.y;
	}

	void    SetCameraDir(const D3DXVECTOR3& dir)
	{
		m_camDir.x = dir.x;
		m_camDir.y = dir.y;
	}
	void SetNeedSetFrustumEx(BOOL val) { m_bNeedSetFrustumEx = val; }

protected:
	bool BoxCross( const D3DXVECTOR3& vBoxAMin, const D3DXVECTOR3& vBoxAMax, const D3DXVECTOR3& vBoxBMin, const D3DXVECTOR3& vBoxBMax );	// 判断两个包围盒水平平面是否相交
	TileQuadTreeNode* m_pRoot;
	int				m_nObjectCount;
	BOOL			m_bRenderBBox;
	D3DXVECTOR2     m_camPos;
	D3DXVECTOR2     m_camDir;
	std::vector<CWorldChunk*> m_vctVisibleChunk;	// Cull后把可见chunk保存在列表里
	BOOL			*m_arrVisibleChunkId;			// 记录可见chunk Id
	int				m_nChunkTotal;
	FrustumEx*	m_pOldFrustumEx;
	BOOL			m_bNeedSetFrustumEx;
};
#endif